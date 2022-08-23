#ifndef __PLAYER_H
#define __PLAYER_H

#include <string>
#include "cards_class.h"


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

public:
    const string name;
    Card_list cards_public;
    Card_list cards_hand;
    Card_list cards_river;
    //side = []
    string self_wind = "东";
    string table_wind = "东";
    bool ting = false;
    bool riichi_flag = false;
    //riichi_list = []
    //ting_item = ''
    bool fangchong = false;
    bool hula = false;
    Card_list face_down;


    Player_class(string NAME = "Player") :name(NAME) { }
    //~player_class() {};

    

//    get_face(v);
    bool has_quetou(Card_list l_q);
    bool has_shunzi(Card_list l_s);
    bool is_hule(Card_list hand);

    Card_list get_public(Card_list publiccard);
    void set_wind();   //需要后级补充

    card_example play();
    bool hu(card_example newcard);
//  bool riichi();
    bool gang(card_example newcard);
    bool jiagang();
    bool peng(card_example newcard);
    bool chi(card_example newcard);

    void sort();
    card_example river_last_pop();
    bool check_hu();
    bool check_ting();

    restart();


    //action_play();
    //action_peng();


};




#endif
