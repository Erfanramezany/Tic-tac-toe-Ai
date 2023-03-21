#include "Main.h"
#include "Ai_module.h"

Move bestMove;
win_pos position1;
win_pos position2;
win_pos position3;

Base::Base()
{
    position1.row = position2.row = position3.row = -1;
    position1.col = position2.col = position3.col = -1;
}

void Base::showUi(bool playerTurn = false)
{
    // convert positions to a varble to call them easier
    char a = p[0][0];
    char b = p[0][1];
    char c = p[0][2];
    char d = p[1][0];
    char e = p[1][1];
    char f = p[1][2];
    char g = p[2][0];
    char h = p[2][1];
    char i = p[2][2];

    // convert available choices to a varble to call them easier
    char j = num_p[0][0];
    char k = num_p[0][1];
    char l = num_p[0][2];
    char m = num_p[1][0];
    char n = num_p[1][1];
    char o = num_p[1][2];
    char p = num_p[2][0];
    char q = num_p[2][1];
    char r = num_p[2][2];

    // show them via using format string in c++
    cout << endl;
    if (isFinished == true)
    {
        printf("          Final match               Winner moves       \n\n");
    }
    else
        printf("          Game match             Available chioces       \n\n");
    printf("            |     |                   |     |             \n");
    printf("         %c  |  %c  |  %c             %c  |  %c  |  %c       \n", a, b, c, j, k, l);
    printf("        ____|_____|_____          ____|_____|_____        \n");
    printf("            |     |                   |     |             \n");
    printf("         %c  |  %c  |  %c     ==>     %c  |  %c  |  %c       \n", d, e, f, m, n, o);
    printf("        ____|_____|_____          ____|_____|_____        \n");
    printf("            |     |                   |     |             \n");
    printf("         %c  |  %c  |  %c             %c  |  %c  |  %c       \n", g, h, i, p, q, r);
    printf("            |     |                   |     |             \n\n\n");
    if (playerTurn)
    {
        cout << "\033[103m"
             << "\033[41m"
             << "You :" << showTurn("pl") << "\tBot :" << showTurn("op") << endl
             << "\033[0m"
             << "\033[31m";
    }

    if (isFinished == true)
    {
        printf("\033[0m Final resault: ");
        printf("     \033[33;44m Bot :%i \033[0m    vs    \033[33;44m You :%i ", player_won[0], player_won[1]);
        printf("\033[0m");
        // printf("\033[33m");
    }
}
char Base::showTurn(const string st)
{
    if (st == "pl")
        return opponent;

    return Bot;
}

void Base::checkWinner()
{

    for (int i = 0; i < 3; i++)
    {
        // for loop to check 3 rows

        //  _*_|_*_|_*_
        //  ___|___|___
        //     |   |
        if (p[i][0] == p[i][1] && p[i][1] == p[i][2])
        {
            if (p[i][0] != '_')
            {
                // if 3 index are same  (X or O)  isFinished set
                // to true to end execute and set winner
                isFinished = true;
                position1.row = position2.row = position3.row = i;
                position1.col = 0;
                position2.col = 1;
                position3.col = 2;
                set_winner(p[i][0]);
                break;
            }
        }

        // for loop to check 3 coulms

        //  _*_|___|___
        //  _*_|___|___
        //   * |   |
        else if (p[0][i] == p[1][i] && p[1][i] == p[2][i])
        {
            if (p[0][i] != '_')
            {
                isFinished = true;
                position1.col = position2.col = position3.col = i;
                position1.row = 0;
                position2.row = 1;
                position3.row = 2;
                set_winner(p[0][i]);
                break;
            }
        }
    }

    // for loop to check orib

    //  _*_|___|___
    //  ___|_*_|___
    //     |   | *
    if (p[0][0] == p[1][1] && p[1][1] == p[2][2])
    {
        if (p[0][0] != '_')
        {
            isFinished = true;
            position1.row = position1.col = 0;
            position2.row = position2.col = 1;
            position3.row = position3.col = 2;
            set_winner(p[0][0]);
        }
    }

    // for loop to check orib

    //  ___|___|_*_
    //  ___|_*_|___
    //   * |   |
    else if (p[0][2] == p[1][1] && p[1][1] == p[2][0])
    {
        if (p[0][2] != '_')
        {
            isFinished = true;
            position1.row = 0;
            position1.col = 2;
            position2.row = 1;
            position2.col = 1;
            position3.row = 2;
            position3.col = 0;
            set_winner(p[0][2]);
        }
    }
    // if the games end and has no winner this will set winner to N
    else if (isMovesLeft(p) == false)
    {
        isFinished = true;
        set_winner('N');
    }
}

void Base::getPosition()
{
    int pos;

    // check if chosen number is empty and to prevent overwrite
    while (1)
    {
        cout << "Plese enter number where do you want to  :  ";
        cin >> pos;

        if (isMovesSame(p, pos) == true)
        {
            cout << "It was choosen before \n\n";
            continue;
        }

        if (pos < 1 || pos > 9)
        {
            continue;
        }

        able_to_exit = true;

        if (able_to_exit == true)
            break;
    }

    // assign chosen number and symbol to right index
    switch (pos)
    {
    case 7:
        p[0][0] = opponent;
        num_p[0][0] = ' ';
        break;

    case 8:
        p[0][1] = opponent;
        num_p[0][1] = ' ';
        break;

    case 9:
        p[0][2] = opponent;
        num_p[0][2] = ' ';
        break;

    case 4:
        p[1][0] = opponent;
        num_p[1][0] = ' ';
        break;

    case 5:
        p[1][1] = opponent;
        num_p[1][1] = ' ';
        break;

    case 6:
        p[1][2] = opponent;
        num_p[1][2] = ' ';
        break;

    case 1:
        p[2][0] = opponent;
        num_p[2][0] = ' ';
        break;

    case 2:
        p[2][1] = opponent;
        num_p[2][1] = ' ';
        break;

    case 3:
        p[2][2] = opponent;
        num_p[2][2] = ' ';
        break;

    default:
        cout << "\nNumber invalid !!\n\n";
        break;
    }
}

void Base::playerExecution()
{
    // clear text
    system("clear");
    showUi(true);
    getPosition();

    checkWinner();

    if (isFinished == false)
    {
        lead_road(Bot);
    }
}

void Base::bot_execute()
{
    system("clear");
    showUi();

    if (mode == "med")
    {
        if (med_switch == "hard")
        {
            mode = "hard";
            bestMove = findBestMove(p);
            p[bestMove.row][bestMove.col] = Bot;
            num_p[bestMove.row][bestMove.col] = ' ';
            mode = "med";
            med_switch = "easy";
        }
        else
        {
            mode = "easy";
            bestMove = findBestMove(p);
            p[bestMove.row][bestMove.col] = Bot;
            num_p[bestMove.row][bestMove.col] = ' ';
            mode = "med";
            med_switch = "hard";
        }
    }
    else
    {
        bestMove = findBestMove(p);
        p[bestMove.row][bestMove.col] = Bot;
        num_p[bestMove.row][bestMove.col] = ' ';
        // cout << mode;
    }
    // check if games end or not
    checkWinner();

    if (isFinished == false)
    {
        lead_road(opponent);
    }
}

void Base::lead_road(char turn)
{
    if (turn == Bot)
    {
        bot_execute();
    }
    else
    {
        playerExecution();
    }
}

void Base::set_winner(char result)
{
    printf("\033[33m");

    if (result == Bot)
    {
        system("clear");
        cout << "\n        you lose !!!\n\n\t\tBot won the match\n\n";
        player_won[0] += 1;
        showWin();
        showUi();
        reset_game();
    }
    else if (result == opponent)
    {
        system("clear");
        cout << "\n        congratulations !!!\n\n\t\t you won the match\n\n";
        player_won[1] += 1;
        showWin();
        showUi();
        reset_game();
    }
    else if (result == 'N')
    {
        system("clear");
        cout << "\n        Draw !\n\n\t\tGame ends without a winner\n\n";
        showUi();
        reset_game();
    }
}

void Base::showWin()

{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (num_p[i][j] != ' ')
            {
                num_p[i][j] = ' ';
            }
        }
    }
    // set win positions
    num_p[position1.row][position1.col] = '*';
    num_p[position2.row][position2.col] = '*';
    num_p[position3.row][position3.col] = '*';
}

void Base::start_game()
{
    char ask = '_';
    printf("\033[31m");

    cout << "which would start first ?\n\t";
    cout << "enter b for bot | any character for you to start the game :  ";
    cin >> ask;

    cout << "\n\nok and which mode ?\n\t";
    cout << "enter b for beginner | enter i for intermediate | p for professional :  ";
    cin >> mode;

    if (mode == "b")
    {
        mode = "easy";
    }
    else if (mode == "p")
    {
        mode = "hard";
    }
    else
    {
        mode = "med";
    }

    if (ask == 'b')
    {
        lead_road(Bot);
    }
    else
    {
        lead_road(opponent);
    }
}

void Base::reset_game()
{
    string ask_again = "default";
    bool can_exit = false;
    bool play_aagain = false;
    int k = 0;
    char numss[] = "789456123";

    while (1)
    {
        try
        {
            cout << "\n\n\tDo you want to have another chance to play (y/n) ? ";
            cin >> ask_again;

            if (ask_again == "yes" || ask_again == "y")
            {
                can_exit = true;
                play_aagain = true;
            }
            else if (ask_again == "no" || ask_again == "n")
            {
                can_exit = true;
            }
            else
            {
                throw "eror";
            }
        }
        catch (...)
        {
            cout << "invalid entry !!!";
        }

        if (can_exit == true)
        {
            break;
        }
    }
    // if yes reset list and array and call start_game() to start the game

    if (play_aagain)
    {
        printf("\033[33m");
        system("clear");
        able_to_exit = false;
        isFinished = false;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                p[i][j] = '_';

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                num_p[i][j] = numss[k];
                k += 1;
            }

        start_game();
    }
}