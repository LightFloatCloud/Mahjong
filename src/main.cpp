#include "game_class.h"

#include <unistd.h>


using namespace std;
int main()
{
    Game_class game;

    while(true)
    {
    game.shuffle();
    game.show_order("en","off"); //显示牌谱
    game.drawcard(); //四家初始抓牌

    game.show_order("en","off");
    game.sort_playercards(); //四家理牌
    game.show_playercards(4);


    //Player_class PlayerA("cyx");
    //PlayerA.cards_hand = cardlist;
    //cout << "Player " << PlayerA.name << (PlayerA.has_quetou()?" has":" doesn\'t have") << " quetou.\n";
    cin.get();
    //pause();
    //system("CLS");
    }
    return 0;
}
