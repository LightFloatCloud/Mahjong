#ifdef _WIN32
#include <windows.h>
#endif

#include "game_class.h"

#include <unistd.h>
#include <limits>
#include <cassert>


using namespace std;



int cosplay(Game_class &game, uint16_t &play_code);


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
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4m")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("1s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("1s")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("5s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("6s")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("2p")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("3p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4p")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("2z")));
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4z")));

// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("1z")));
// // game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("8p")));


// game.show_playercards(0);
// vector<uint16_t> ting_codes = game.player[0].is_ting();
// if(!ting_codes.empty()) {
//     cout << "听牌" <<endl;
//     for(auto code:ting_codes) {
//         cout << card_example::code2str(code) << " ";
//     }
//     return 0;
// }




    cin.get();

    //string input; //input == "q" || input == "Q"
    while(1 )
    {
        if(game.turn == 1)
            system("cls");
        

        // 听牌显示
        vector<uint16_t> ting_codes = game.player[game.turn].is_ting();
        if(!ting_codes.empty()) {
            cout << "\t听牌：" ;
            for(auto code:ting_codes) {
                cout << card_example::code2str(code) << " ";
            }
        }

        // 摸牌
        
        uint16_t newcard_code = game.drawcard();
        uint16_t play_code = newcard_code; // AI 默认出牌
        //int action_code = 0; // AI 不吃不碰不杠不胡

        game.show_playercards(4);
        
        // 判胡
        bool is_over = false;
        bool is_Hu = false; 
        string prompt;
        is_over = game.is_over(is_Hu, prompt);
        if(is_Hu) {
            cout << prompt <<endl;
            break;
        }


        // 玩家决定出牌
        int user_answer;
        do { 
            user_answer = cosplay(game, play_code) ;
        }while (user_answer == -2);
        if(user_answer == -1) { // 退出
            break;
        }

        // if(cosplay(game, turn, play_code) != 0) {
        //     break;
        // }; //用户扮演某个player


        // 打牌
        int index = game.player[game.turn].cards_hand.get_index(play_code);
        assert(index >= 0);
        card_example card_play = game.player[game.turn].cards_hand.list[index];
        game.player[game.turn].cards_hand.list.erase(game.player[game.turn].cards_hand.list.begin() + index);
        

        // 轮询吃碰杠胡


        
        game.player[game.turn].cards_river.append(card_play);
        //game.player[turn].cards_hand.remove(play_code);
        game.player[game.turn].cards_hand.sorted();

        
        
        // 流局
        if(game.chang_nownum == 137) {
            cout << "牌局结束" << endl;
            break;
        }

        // 下一轮
        game.turn ++;
        if(game.turn == 4) game.turn = 0;
        

        cout << endl;
    }

    cin.get();
    return 0;
}


int cosplay(Game_class &game, uint16_t &play_code)
{
    string input;
    if(game.turn == 0) {
        std::cout << "还有" << 137 - game.chang_nownum << "张牌, ";
        std::cout << "请输入str(q/Q退出): ";
        std::cin >> input;  
        // 清空输入缓冲区，直到遇到换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(input == "q" || input == "Q") {
            cout << "退出！" << endl;
            return -1;
        }
        // system("cls");
        play_code = card_example::str2code(input);

    }
    int count = game.player[game.turn].cards_hand.count(play_code);
    if(count == 0) {
        cout << "要打的牌不存在, 重新输入" <<endl;
        return -2;
    }
    return 0;
}
