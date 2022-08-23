#include <sstream>

#include <algorithm> 
#include <ctime> 

#include "cards_class.h"
#include <windows.h>

//using std::random_shuffle; 

vector<uint16_t> player_handcards[4], player_fulu[4];

void Cards_class::card_init()
{
    
    card[0].id = 0;
    card[0].color_id = 0;
    card[0].num = 0;
    card[0].color = "空";
    card[0].card_str = "00";

    for(int id=1; id<=136; id++)
    {
        
        card[id].id = id;
        card[id].color_id = (id-1)/36 + 1;
        card[id].num = ((id-1)%36)/4 + 1;

        switch (card[id].color_id)
        {
        case 1:
            card[id].color = "万";
            card[id].card_str = to_string(card[id].num) + "m";
            card[id].card_name = to_string(card[id].num) + "万";
            break;
        case 2:
            card[id].color = "条";
            card[id].card_str = to_string(card[id].num) + "s";
            card[id].card_name = to_string(card[id].num) + "条";
            break;
        case 3:
            card[id].color = "筒";
            card[id].card_str = to_string(card[id].num) + "p";
            card[id].card_name = to_string(card[id].num) + "筒";
            break;
        case 4:
            card[id].color = "字";
            card[id].card_str = to_string(card[id].num) + "z";
            
            switch(card[id].num)
            {
            case 1:
                card[id].card_name = "东";
                break;
            case 2:
                card[id].card_name = "南";
                break;
            case 3:
                card[id].card_name = "西";
                break;
            case 4:
                card[id].card_name = "北";
                break;

            case 5:
                card[id].card_name = "中";
                break;
            case 6:
                card[id].card_name = "发";
                break;
            case 7:
                card[id].card_name = "白";
                break;
            default:
                break;
            }

            break;
        default:
            break;
        }
        //cout << id <<endl;
    }

    for(uint16_t order=1; order<=136; order++)
    {
        cards_order[order] = order;
    }

    srand(time(NULL));
    
}

uint16_t Cards_class::shuffle()
{

    random_shuffle(&cards_order[1],&cards_order[1] + 136);
    int touzi = rand()%6 + 1 + rand()%6 + 1;
    chang_startnum = (touzi + 1) * 2 + 1;
    chang_nownum = chang_startnum;
    cout << "骰子："<< touzi <<"，宝牌指示牌："<< card[cards_order[1]].card_name <<endl;
    return chang_startnum;
}
void Cards_class::drawcard()
{
    for(int player=0; player<4; player++)
    {
        player_handcards[player].clear();
    }
    for(int point=1; point<=13; point++)
    {
        for(int player=0; player<4; player++)
        {
            player_handcards[player].push_back(cards_order[chang_nownum]);
            chang_nownum ++;
        }
    }
}
void Cards_class::sort_playercards()
{
    for(int player=0; player<4; player++) //对每个player查看手牌
    {
        sort(player_handcards[player].begin(), player_handcards[player].end());
    }
}

void Cards_class::show_order(string lang="en",string index="off")
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    for(int order=1; order<=136; order++)
    {
        uint16_t id = cards_order[order];
        
        if(order == chang_nownum)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

        if(index == "on")
            cout << order << ":\t" ;

        if(lang == "zh")
            cout << card[id].card_name << "\t";
        else if (lang == "en")
            cout << card[id].card_str << "\t";

        if(index == "on")
            cout << endl ;
    }
    cout << "现在是第" << chang_nownum << "张。" << endl;
}
void Cards_class::show_playercards(int player_id=4)
{
    if(player_id==4)
    {
        for(int player=0; player<4; player++) //对每个player查看手牌
        {
            cout << "player" << player << ":" << endl;
            for(auto id_pointer=player_handcards[player].begin(); id_pointer!=player_handcards[player].end(); id_pointer++)
                cout << card[*id_pointer].card_name << "\t"; //id_pointer是vector指针，遍历player所有手牌id
            cout << endl;
        }
    }
    else if (player_id<4 && player_id>=0)
    {
        cout << "player" << player_id << ":" << endl;
        for(auto id_pointer=player_handcards[player_id].begin(); id_pointer!=player_handcards[player_id].end(); id_pointer++)
            cout << card[*id_pointer].card_name << "\t";
        cout << endl;
    }
    
    
}



bool Cards_class::is_yaojiu(uint16_t id)
{
    if(card[id].num==1 || card[id].num==9 || card[id].color_id==4)
        return true;
    else
        return false;
}



Cards_class::Cards_class(/* args */)
{
    card_init();
}

Cards_class::~Cards_class()
{
    cout << "Cards_class析构函数被调用" << endl;
}











void Card_list::Card_list_init(vector<card_example> __list = vector<card_example>(0))
{
    list = __list;
}
void Card_list::show_list()
{
    cout << "Show list:" << endl;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
        cout << (*card_pointer).card_name << "\t";
    cout << endl;
}
bool Card_list::is_contained(string cardstr)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).card_str == cardstr)
            return true;
    }
    return false;
}
int Card_list::__len__()
{
    return list.size();
}

int Card_list::get_index(string cardstr)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).card_str == cardstr)
            return card_pointer - list.begin();
    }
    cout << "Cardlist中无" << cardstr <<endl;
    return list.size();
}
void Card_list::append(card_example newcard)
{
    list.push_back(newcard);
}
void Card_list::remove(string cardstr)
{
    list.erase(list.begin() + get_index(cardstr));
}
int Card_list::count(string cardstr)
{
    int C = 0;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).card_str == cardstr)
            C++;
    }
    return C;
}


bool card_cmp(card_example cardA, card_example cardB)
{
    return cardA.id < cardB.id;
}
Card_list Card_list::sorted()
{
    sort(list.begin(), list.end(), card_cmp);
    return *this; 
}

void Card_list::clear()
{
    list.clear();
}
bool Card_list::is_empty()
{
    if(__len__()==0)
        return true;
    else
        return false;
}


bool is_wind(card_example a_card)
{
    if(a_card.color_id == 4 && a_card.num <= 4)
        return true;
    else
        return false;
}
bool is_zhong(card_example a_card)
{
    if(a_card.color_id == 4 && a_card.num >= 5 && a_card.num <= 7)
        return true;
    else
        return false;
}

