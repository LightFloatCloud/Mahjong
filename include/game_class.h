#ifndef __CARDS_CLASS_H
#define __CARDS_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include "player.h"


//extern Card_list player_handcards[4], player_fulu[4];

/**
 * @brief 整个牌局
 * 
 */
class Game_class
{
    
private:
    void card_init();        

public:
    Game_class(/* args */);
    ~Game_class();

    // 136张牌，[0] 无意义
    card_example card[137];

    // 136张牌的索引序列，表示牌序
    vector <uint16_t> cards_order = vector<uint16_t>(137);


    // 4位玩家
    Player_class player[4] = {Player_class("You"), Player_class("Bob"), Player_class("Cora"), Player_class("Dell")};
    int turn = 0; // 0~3 东南西北

    uint16_t shuffle(); // 返回开牌的序数
    void all_drawcard();

    uint16_t drawcard(); // 返回抓牌的牌编号
    void playcard(uint16_t code);

    void sort_playercards();
    
    // 开牌的序数
    uint16_t chang_startnum;
    // 当前的牌序数
    uint16_t chang_nownum;

    void show_order(string lang, string index); // 显示牌河
    void show_playercards(int);      // 显示手牌



    int enquire_hu(card_example &enquire_card); // 查看余下三家有没有胡的, 并执行，返回1<<winner.turn(可一炮双响)
    int enquire_peng(card_example &enquire_card); // 返回值是 penger.turn + 1, 0 表示无
    bool enquire_chi(card_example &enquire_card);

    bool is_over(bool &is_Hu, string &prompt); // 返回值为是否结束，是否胡，说明内容


};




/*
class PaiList:

    def __getitem__(self, item):
        return self.li[item]

    def __setitem__(self, key, value):
        self.li[key] = value

    def get_n(self):
        return [i.n for i in self.li]

    def extend(self, other):
        self.li.extend(other.li)

    def set(self):
        temp = PaiList()
        for i in self.li:
            if i not in temp:
                temp.append(i)
        temp.sorted()
        return temp

*/



#endif
