#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

#include <algorithm> 
#include <ctime> 

#include "game_class.h"


//using std::random_shuffle; 

//Card_list player_handcards[4], player_fulu[4];




void Game_class::card_init()
{
    
    card[0].id = 0;
    card[0].color_id = Other;
    card[0].num = 0;

    for(int id=1; id<=136; id++)
    {
        
        card[id].id = id;
        switch ((id-1)/36 + 1)
        {
        case 1:
            card[id].color_id = Wan;
            break;
        case 2:
            card[id].color_id = Tiao;
            break;
        case 3:
            card[id].color_id = Tong;
            break;
        case 4:
            card[id].color_id = Zi;
            break;
        default:
            break;
        }
        //card[id].color_id = (id-1)/36 + 1;
        card[id].num = ((id-1)%36)/4 + 1;
    }
    
}

uint16_t Game_class::shuffle()
{
    cout << "洗牌：" << endl;
    random_shuffle(&cards_order[1],&cards_order[1] + 136);
    int touzi = rand()%6 + 1 + rand()%6 + 1;
    chang_startnum = (touzi + 1) * 2 + 1;
    chang_nownum = chang_startnum;
    cout << "骰子："<< touzi <<"，宝牌指示牌："<< card[cards_order[1]].card_name() <<endl;
    return chang_startnum;
}

/**
 * @brief 四家抓牌
*/
void Game_class::drawcard()
{
    for(int player_id=0; player_id<4; player_id++)
    {
        player[player_id].restart();
        //player_handcards[player].clear();
    }
    player[0].set_wind("东"); player[1].set_wind("南"); player[2].set_wind("西"); player[3].set_wind("北"); 

    for(int point=1; point<=13; point++)
    {
        for(int player_id=0; player_id<4; player_id++)
        {
            player[player_id].cards_hand.append(card[cards_order[chang_nownum]]);
            //player_handcards[player].append(card[cards_order[chang_nownum]]);
            chang_nownum ++;
        }
    }
}

/**
 * @brief 四家理牌
*/
void Game_class::sort_playercards()
{
    for(int player_id=0; player_id<4; player_id++) //对每个player查看手牌
    {
        player[player_id].cards_hand.sorted();
    }
}

/**
 * @brief 显示全局牌谱
 * @param[in] lang “en”显示英文牌谱，“zh”显示中文牌谱
 * @param[in] index “on”“off” 是否显示索引/牌序号
*/
void Game_class::show_order(string lang="en",string index="off")
{
#ifdef _WIN32
    //system("cls");
#endif

    cout << endl <<"显示牌谱："<< endl;
    


    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
    //
    printf("\033[92m");


    for(int order=1; order<=136; order++)
    {
        uint16_t id = cards_order[order];
        
        if(order == chang_nownum)
            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            printf("\033[0m");
        if(index == "on")
            cout << order << ":\t" ;

        if(lang == "zh")
            cout << card[id].card_name() << "\t";
        else if (lang == "en")
            cout << card[id].card_str() << "\t";

        if(index == "on")
            cout << endl ;
    }
    cout << "现在是第" << chang_nownum << "张。" << endl ;
    cout << endl ;
}

/**
 * @brief 显示手牌
 * 
 * @param player_id 0~3显示某位玩家手牌，4显示所有玩家手牌。默认为4
 */
void Game_class::show_playercards(int player_id=4)
{
    if(player_id==4)
    {
        for(int id=0; id<4; id++) //对每个player查看手牌
        {
            player[id].show();
            //cout << "player" << player << " ";
            //player_handcards[player].show_list();
            
            // for(auto id_pointer=player_handcards[player].begin(); id_pointer!=player_handcards[player].end(); id_pointer++)
            //     cout << card[*id_pointer].card_name() << "\t"; //id_pointer是vector指针，遍历player所有手牌id
            // cout << endl;
        }
    }
    else if (player_id<4 && player_id>=0)
    {
        player[player_id].show();
        // cout << "player" << player_id << " ";
        // player_handcards[player_id].show_list();
        // for(auto id_pointer=player_handcards[player_id].begin(); id_pointer!=player_handcards[player_id].end(); id_pointer++)
        //     cout << card[*id_pointer].card_name() << "\t";
        // cout << endl;
    }
    
    
}







Game_class::Game_class(/* args */)
{
    card_init();
    
    for(uint16_t order=1; order<=136; order++)
    {
        cards_order[order] = order;
    }

    srand(time(NULL));
}

Game_class::~Game_class()
{
    cout << "Cards_class析构函数被调用" << endl;
}



