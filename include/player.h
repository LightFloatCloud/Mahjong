#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>
#include "card_example.h"


/*
class Player:
    def __init__( NAME='Player'):
        if NAME == '':
            NAME = 'Player'
        __name = NAME
        public = PaiList()
        hand = PaiList()
        river = PaiList()
        side = []
        wind = None
        table_wind = None
        ting = False
        riichi_flag = False
        riichi_list = []
        ting_item = ''
        fangchong = False
        hula = False
        face_down = PaiList()

*/

class Player_class
{
private:
    bool is_kezi(Card_list card3);
    bool is_shunzi(Card_list card3); // 需要修改

    // Card_list extract_shunzi(Card_list &cards); // 搜索顺子并攫取
    bool is_3N(Card_list &card3N);
    bool is_3N_Feng(Card_list &card3N);


public:
    const string name;
    vector<Card_list> cards_public; //副露
    Card_list cards_hand; //手牌
    Card_list cards_river; // 牌河
    string self_wind = "";
    //string table_wind = "东";
    bool ting = false;


// 吃碰杠操作
    bool just_ganged = false;
    bool just_chipenged = false;
    bool hule = false;
// 机器人策略
    bool default_dicide_hu = true;
    bool default_dicide_gang = false;
    bool default_dicide_peng = false;
    uint8_t default_dicide_chi = 0x00; 
    //bool riichi_flag = false;
    //riichi_list = []
    //ting_item = ''
    //bool fangchong = false;
    //bool hula = false;
    //Card_list face_down;


    Player_class(string NAME = "Player") :name(NAME) { }
    //~player_class() {};

    void set_wind(string); 
    void show();

    bool is_3Nplus2(Card_list &card3N_2);
    bool is_7dui(Card_list &card7dui);

    vector<uint16_t> is_ting(); // 返回听的几张牌




//    get_face(v);
    int  has_quetou(Card_list l_s);  //  几个对子(包括刻子,4个算2对)
    bool has_shunzi(Card_list l_s); //待修改(无作用)
    //bool is_hule(Card_list hand); //待增加

    //Card_list get_public(Card_list publiccard);
    
    uint8_t can_chi(uint16_t card_code); // 1左吃，2中吃，4右吃
    bool can_peng(uint16_t card_code);
    bool can_gang(uint16_t card_code);
    bool can_hu(uint16_t card_code);

    void chi(card_example &card, uint8_t mode); // 以哪种模式吃
    void peng(card_example &card);
    void gang(card_example &card); 
    void hu(card_example &card);  //...

    void action(card_example &card);


    // card_example play();
    // bool hu(card_example newcard);
    // bool gang(card_example newcard);
    // bool jiagang();
    // bool peng(card_example newcard);
    // bool chi(card_example newcard);

    // void sort();
    // card_example river_last_pop();
    // bool check_hu();
    // bool check_ting();

    void restart();


    //action_play();
    //action_peng();


};




#endif
