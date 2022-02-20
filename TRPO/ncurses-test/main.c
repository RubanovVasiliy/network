#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 30
#define HEIGHT 10
int startx = 0;
int starty = 0;
char* choices[] = {
    "Ярик",
    "норм",
    "работает?",
    "а? а?",
    "Exit",
};
int n_choices = sizeof(choices) / sizeof(char*);
void print_menu(WINDOW* menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int* p_choice);
int main()
{
    int c, choice = 0;
    setlocale(0, "");
    WINDOW* menu_win;
    MEVENT event;
    /* Initialize curses */
    initscr();
    clear();
    noecho();
    cbreak(); //Line buffering disabled. pass on everything
    /* Try to put the window in the middle of screen */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    attron(A_REVERSE);
    mvprintw(23, 1, "Click on Exit to quit (Works best in a virtual console)");
    refresh();
    attroff(A_REVERSE);
    /* Print the menu for the first time */
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    print_menu(menu_win, 1);
    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    while (1) {
        c = wgetch(menu_win);
        switch (c) {
        case KEY_MOUSE:
            if (getmouse(&event) == OK) { /* When the user clicks left mouse button */
                if (event.bstate & BUTTON1_PRESSED) {
                    report_choice(event.x + 1, event.y + 1, &choice);
                    if (choice == -1) //Exit chosen
                        goto end;
                    mvprintw(22, 1, "Choice made is : %d String Chosen is \"%10s\"", choice, choices[choice - 1]);
                    refresh();
                }
            }
            print_menu(menu_win, choice);
            break;
        }
    }
end:
    endwin();
    return 0;
}
void print_menu(WINDOW* menu_win, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
/* Report the choice according to mouse position */ void report_choice(int mouse_x, int mouse_y, int* p_choice)
{
    int i, j, choice;
    i = startx + 2;
    j = starty + 3;
    for (choice = 0; choice < n_choices; ++choice)
        if (mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice])) {
            if (choice == n_choices - 1)
                *p_choice = -1;
            else
                *p_choice = choice + 1;
            break;
        }
}

/*int main()
{
    
    setlocale(0, "");
    const char* message_0_0 = "Irregular Verbs";
    const char* message_0_2 = "Greetings, this is a program for verifying irregular verbs, let's get started!";
    const char* message_0_4 = "Enter any character to display the menu.";
    const char* message_0_9 = "!ВНИМАНИЕ!";
    const char* message_0_10 = "Для корректного отображения всех объектов, рекомендуется проходить тестирование в полноэкранном режиме.";

    // MENU
    const char menu[4][20] = {
        "1 слово",
        "10 слов",
        "15 слов",
        "25 слов"
    };

    // ENTER MENU
    const char* message_0_5 = "Выберите сложность.";

    const char* message_0_6 = "Вы хотите продолжить тест?";
    const char* message_0_7 = "1 - Да";
    const char* message_0_8 = "2 - Нет";
    const char* message_enter_0 = "Ввод: ";

    initscr();
    //bool enter = false; // Переход в curses-режим.
    unsigned lines, columns;

    getmaxyx(stdscr, lines, columns);
    attron(A_BOLD);
    mvwprintw(stdscr, (lines / 2) - 2, (columns - strlen(message_0_0)) / 2, message_0_0);
    attroff(A_BOLD);
    mvwprintw(stdscr, (lines / 2) - 0, (columns - strlen(message_0_2)) / 2, message_0_2);
    attron(A_BLINK);
    mvwprintw(stdscr, (lines / 2) + 2, (columns - strlen(message_0_4)) / 2, message_0_4);
    attroff(A_BLINK);
    //mvwprintw(stdscr, lines - 6, (columns - strlen(message_0_9) / 2) / 2, message_0_9);
    //mvwprintw(stdscr, lines - 4, (columns - strlen(message_0_10) / 2) / 2, message_0_10);
    getch(); 

    curs_set(0); // Выключение курсора.
    keypad(stdscr, true);
    endwin();
    return 0;
}*/