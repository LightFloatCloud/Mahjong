#ifdef _WIN32
#include <windows.h>
#endif

#include "game_class.h"

#include <unistd.h>
#include <limits>



using namespace std;
int main()
{
#ifdef _WIN32
    system("cls");
#endif
    Game_class game;


    game.shuffle();
    game.show_order("en","off"); //显示牌谱
    game.all_drawcard(); //四家初始抓牌

    game.show_order("en","off");
    game.sort_playercards(); //四家理牌
    //game.show_playercards(4);


// game.player[0].cards_hand.clear();
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("3m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("3m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4m")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("5m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("5s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("6s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("7s")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("1p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("2p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("3p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("7p")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("7p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("5m")));


// game.show_playercards(0);
// bool is_Hu = game.player[0].is_3Nplus2(game.player[0].cards_hand);
// if(is_Hu) {
//     cout << "胡了！————自摸" <<endl;
//     return 0;
// }













    string input; //input == "q" || input == "Q"
    while(1 )
    {
        int turn = game.turn;
        

        uint16_t newcard_code = game.drawcard();
        uint16_t play_code = newcard_code;

        game.show_playercards(4);
        

        bool is_Hu = game.player[turn].is_3Nplus2(game.player[turn].cards_hand);
        if(is_Hu) {
            cout << "胡了！————自摸" <<endl;
            break;
        }


        if(turn == 0) {
            std::cout << "还有" << 137 - game.chang_nownum << "张牌, ";
            std::cout << "请输入str(q/Q退出): ";
            std::cin >> input;  
            // 清空输入缓冲区，直到遇到换行符
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(input == "q" || input == "Q") {
                cout << "退出！" << endl;
                break;
            }
            system("cls");
            play_code = card_example::str2code(input);

        }
        int count = game.player[turn].cards_hand.count(play_code);
        if(count == 0) {
            cout << "要打的牌不存在" <<endl;
            break;
        }
        game.player[turn].cards_hand.remove(play_code);
        game.player[turn].cards_hand.sorted();

        if(game.chang_nownum == 137) {
            cout << "牌局结束" << endl;
            break;
        }

        cout << endl;
    //cin.get();
    //pause();
    //system("CLS");
    }
    return 0;
}
