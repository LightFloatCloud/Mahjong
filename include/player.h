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
    bool is_shunzi(Card_list card3);

    Card_list extract_shunzi(Card_list &cards); // 搜索顺子并攫取
    bool is_3N(Card_list &card3N);
    bool is_3N_Feng(Card_list &card3N);


public:
    const string name;
    Card_list cards_public; //副露
    Card_list cards_hand; //手牌
    Card_list cards_river; // 牌河
    string self_wind = "";
    //string table_wind = "东";
    bool ting = false;
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




//    get_face(v);
    bool has_quetou();
    bool has_shunzi(Card_list l_s); //待修改
    bool is_hule(Card_list hand); //待增加

    //Card_list get_public(Card_list publiccard);
      

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
