#include "cards_class.h"
#include "player.h"



using namespace std;
int main()
{
    Cards_class cards;

    while(true)
    {
    cards.shuffle();
    cards.show_order("zh","off");
    cards.drawcard();

    cards.show_order("zh","off");
    cards.sort_playercards();
    cards.show_playercards(4);


    Card_list cardlist;
    for(int i=0; i<13; i++)
    {
        cardlist.append(cards.card[cards.cards_order[cards.chang_nownum + i]]);
    }
    cardlist.show_list();
    cardlist.sorted();
    cardlist.show_list();
    cout << "count = " << cardlist.count(cardlist.list[0].card_str) << endl;
    

    Player_class PlayerA("cyx");
    PlayerA.cards_hand = cardlist;
    cout << "Player " << PlayerA.name << (PlayerA.has_quetou(PlayerA.cards_hand)?" has":" doesn\'t have") << " quetou.\n";
    system("pause");
    system("CLS");
    }
    return 0;
}
