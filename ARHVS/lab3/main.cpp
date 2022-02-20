#include <iostream>
#include <string>
#include "CLI11.hpp"
#include <cstdlib>
#include <random>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>

double wtime() {
    struct timeval t{};
    gettimeofday(&t, nullptr);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

class Benchmark {
public:
    std::string memory_type;
    int block_size;
    int count;
    std::string block;
    int buffer_size{0};

private:
    std::string timer = "clock_gettime";
    std::string element_type = "int";
    std::string filename = "results.csv";

    double time{0};
    double average_time{0};
    double bandwidth{0};
    double abs_error{0};
    double rel_error{0};

    std::vector<std::string> results;

public:
    Benchmark(const std::string &memoryType, int blockSize, int count, const std::string &block) : memory_type(
            memoryType), block_size(blockSize), count(count), block(block) {
        this->memory_type = memoryType;
        this->block_size = blockSize;
        this->count = count;
        this->block = block;
    }

    void execute() {
        if (memory_type == "RAM") {
            buffer_size = 1;
            write_read("-");
        } else if (memory_type == "HDD" || memory_type == "SSD" || memory_type == "SWAP") {
            buffer_size = block_size;
            write_read("test.txt");
        } else if (memory_type == "flash") {
            buffer_size = block_size;
            auto path = get_command_output("lsblk | grep /media | awk '{printf $NF\"/test.txt\"}'");
            write_read(path);
        }
        //log();
        log_to_csv();
    }

private:
    void log_to_csv() const {
        std::ofstream outfile;

        struct stat buf{};
        if (stat(filename.c_str(), &buf) != -1) {
            outfile.open(filename, std::ios_base::app);
        } else {
            outfile.open(filename);
            outfile
                    << "MemoryType;BlockSize;ElementType;BufferSize;LaunchNum;Timer;WriteTime;AverageWriteTime;WriteBandwidth;"
                       "AbsError(write);RelError(write);ReadTime;AverageReadTime;ReadBandwidth;AbsError(read);RelError(read);\n";
        }
        std::for_each(results.begin(), results.end(), [&](auto &n) { outfile << n + "\n"; });
        outfile.close();
    }

    void log() {
        std::cout <<
                  "MemoryType – тип памяти (RAM|HDD|SSD|flash) или модель устройства, на котором проводятся испытания; " +
                  memory_type + "\n";
        std::cout << "BlockSize – размер блока данных для записи и чтения на каждом испытании; " +
                     std::to_string(block_size) + "\n";
        std::cout << "ElementType – тип элементов используемых для заполнения массива данных; " + element_type + "\n";
        std::cout << "BufferSize – размер буфера, т.е. порции данных для выполнения одно операции записи или чтения; " +
                     std::to_string(buffer_size) + "\n";
        std::cout << "LaunchNum – порядковый номер испытания; " + std::to_string(count) + "\n";
        std::cout << "Timer – название функции обращения к таймеру (для измерения времени); " + timer + "\n";

        std::for_each(results.begin(), results.end(), [](auto &n) { std::cout << n + "\n"; });
    }

    static inline double calcSec(struct timespec ts1, struct timespec ts2) {
        return (1000.0 * (double) ts2.tv_sec + 1e-6 * (double) ts2.tv_nsec -
                (1000.0 * (double) ts1.tv_sec + 1e-6 * (double) ts1.tv_nsec));
    }

    void write_read(const std::string &path) {
        struct timespec ts1{};
        struct timespec ts2{};

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(1, RAND_MAX);

        int temp;
        double time_w = 0;
        double time_r = 0;
        int size = block_size / 4;

        if (path == "-") {

            for (int i = 1; i <= count; i++) {
                int *arr = new int[size];
                std::string result_string = memory_type + ";" + std::to_string(block_size) + ";"
                                            + element_type + ";" + std::to_string(buffer_size) + ";"
                                            + std::to_string(i) + ";" + timer + ";";
                temp = dist(mt);
                double t = wtime();
                for (int j = 1; j <= size; j++) {
                    arr[j] = temp;
                }
                time = wtime() - t;

                calculate_stat(time_w, i);
                result_string += stat_string();
                result_string += ";";


                t = wtime();
                for (int j = 0; j < size; j++) {
                    temp = arr[j];
                }
                time = wtime() - t;

                calculate_stat(time_r, i);
                result_string += stat_string();

                results.push_back(result_string);
                delete[] arr;
            }
        } else {
            FILE *file;

            for (int i = 1; i <= count; i++) {
                int *arr = new int[size];
                std::string result_string = memory_type + ";" + std::to_string(block_size) + ";"
                                            + element_type + ";" + std::to_string(buffer_size) + ";"
                                            + std::to_string(i) + ";" + timer + ";";

                double t = wtime();
                if ((file = fopen(path.c_str(), "w")) != nullptr) {
                    fwrite(arr, sizeof(int), size, file);
                    fclose(file);
                } else {
                    std::cout << "Cannot open" << path << " for write\n", exit(1);
                }
                time = wtime() - t;

                calculate_stat(time_w, i);
                result_string += stat_string();
                result_string += ";";

                t = wtime();
                if ((file = fopen(path.c_str(), "r")) != nullptr) {
                    fread(arr, sizeof(int), size, file);
                    fclose(file);
                } else {
                    std::cout << "Cannot open" << path << " for write\n", exit(1);
                }
                time = wtime() - t;

                calculate_stat(time_r, i);
                result_string += stat_string();


                results.push_back(result_string);

                delete[] arr;
            }
        }
    }

    static std::string get_command_output(const char *cmd) {
        char buffer[128];
        std::string result = "";
        FILE *pipe = popen(cmd, "r");
        if (pipe != nullptr) {
            while (fgets(buffer, sizeof buffer, pipe) != nullptr)
                result += buffer;
            pclose(pipe);
        } else {
            throw std::runtime_error("popen() failed!");
        }
        return result;
    }

    inline void calculate_stat(double &time_wr, int i) {
        time_wr += time;
        average_time = time_wr / i;
        bandwidth = block_size / 1048576.0 / time;
        abs_error = std::abs(count / (3600.0 * 1000 * 100000) - time / count);
        rel_error = abs_error / (time / count);
    }

    [[nodiscard]] inline std::string stat_string() const {
        return std::to_string(time) + ";" + std::to_string(average_time) + ";"
               + std::to_string(bandwidth) + ";" + std::to_string(abs_error) + ";"
               + std::to_string(rel_error);
    }
};


int main(int argc, char **argv) {
    int count = 10;
    std::string block = "b";
    int block_size = 256;
    std::string memory_type = "RAM";


    CLI::App app("Benchmark");
    app.add_option("-l,--launch-count", count, "launch count\nin the range 10 to 1000000\ndefault 10")->
            check(CLI::Range(1, 1000000000));
    app.add_option("-b,--block", block, "set block block_size: Kb|Mb\ndefault byte")->
            check(CLI::IsMember({"Kb", "Mb"}));
    app.add_option("-s,--block-size", block_size, "launch count\nin the range 10 to 1000000\ndefault 10")->
            check(CLI::Range(1, 1024 * 1024 * 1024));
    app.add_option("-m,--memory-type", memory_type, "select memory type: RAM|HDD|SSD|flash\ndefault RAM")->
            check(CLI::IsMember({"RAM", "HDD", "SSD", "flash"}));
    CLI11_PARSE(app, argc, argv)

    auto benchmark = new Benchmark(memory_type, block_size, count, block);
    benchmark->execute();

    return 0;
}