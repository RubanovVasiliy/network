#include <iostream>
#include <string>
#include <cstdio>
#include "CLI11.hpp"
#include <cstdlib>
#include <sys/stat.h>


template<typename T>
inline T customRand() {
    const T min = 0;
    const T max = RAND_MAX;
    double f = (double) random() / RAND_MAX;
    return (T) (min + f * (max - min));
}

class Benchmark {
public:
    int count;
    std::string filename;
    std::string task;
    std::string operandType;

private:
    double time;
    double singleTime;
    double absError;
    double relError;

public:
    Benchmark(int count, const std::string &filename, const std::string &optimization, const std::string &task,
              const std::string &operandType) : count(count), filename(filename),
                                                task(task),
                                                operandType(operandType) {
        this->count = count;
        this->filename = filename;
        this->task = task;
        this->operandType = operandType;
        this->time = 0l;
        this->singleTime = 0l;
        this->absError = 0l;
        this->relError = 0l;
    }

    void launchTest() {
        struct timespec ts1{};
        struct timespec ts2{};

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);
        execute();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);

        time = calcSec(ts1, ts2);
        absError = abs(count / (3600.0 * 1000 * 100000) - time / count);
        relError = absError / (time / count);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);
        singleTest();
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);

        singleTime = calcSec(ts1, ts2);

        printf("CPU time used per %9d: %.6f ms\n", count, time);
        printf("single time %.6f ms\n", singleTime);
        printf("%f %f \n", absError, relError);
    }

    void logTime() const {
        std::ofstream outfile("time.txt",std::ios_base::out);
        if (outfile) {
          outfile << time;
          outfile << ' ';
          outfile << singleTime;
          outfile << ' ';
          outfile << absError;
          outfile << ' ';
          outfile << relError;
        }
        outfile.close();
    }

private:
    static inline double calcSec(struct timespec ts1, struct timespec ts2) {
        return (1000.0 * (double) ts2.tv_sec + 1e-6 * (double) ts2.tv_nsec -
                (1000.0 * (double) ts1.tv_sec + 1e-6 * (double) ts1.tv_nsec));
    }

    inline void singleTest() const {
        if (task == "sin") {
            if (operandType == "int") {
                sin(customRand<int>());
            } else if (operandType == "float") {
                sin(customRand<float>());
            } else {
                (double) sin(customRand<float>());
            }
        } else if (task == "log") {
            if (operandType == "int") {
                log(customRand<int>());
            } else if (operandType == "float") {
                log(customRand<float>());
            } else {
                (double) log(customRand<float>());
            }
        }
    }

    void execute() {
        for (int i = 0; i < count; i++) {
            singleTest();
        }
    }
};


int main(int argc, char **argv) {

    srand(time(nullptr));

    auto benchmark = new Benchmark(10, "time.txt", "O0", "sin", "int");

    CLI::App app("Benchmark");
    app.add_option("-n,--num", benchmark->count, "number of executions\nin the range 1000 to 1000000")->
            check(CLI::Range(10, 1000000000));
    app.add_option("-f,--file", benchmark->filename, "filename to output results");
    app.add_option("-t,--task", benchmark->task, "set task\nvalues: sin | log | ...\nsin by default")->
            check(CLI::IsMember({"sin", "log"}));
    app.add_option("-p,--operandType", benchmark->operandType, "select operand type: int or float")->
            check(CLI::IsMember({"int", "float"}));
    CLI11_PARSE(app, argc, argv)

    benchmark->launchTest();
    benchmark->logTime();
    return 0;
}