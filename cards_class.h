#ifndef __CARDS_CLASS_H
#define __CARDS_CLASS_H

#include <iostream>
#include <string>
#include <vector>



using namespace std;


extern vector<uint16_t> player_handcards[4], player_fulu[4];


struct card_example
    {
        uint16_t    id;
        string      color;
        uint16_t    color_id;
        uint16_t    num;

        string      card_str;
        string      card_name;
    };
    

class Cards_class
{
    
private:
    void card_init();
    bool is_yaojiu(uint16_t);

public:
    Cards_class(/* args */);
    ~Cards_class();

    card_example card[137];
    vector <uint16_t> cards_order = vector<uint16_t>(137);

    uint16_t shuffle();
    void drawcard();
    void sort_playercards();
    
    uint16_t chang_startnum;
    uint16_t chang_nownum;

    void show_order(string, string);
    void show_playercards(int);

};


class Card_list
{
private:
    void Card_list_init(vector<card_example> );

public:
    vector<card_example> list; //牌列

    void show_list(); //牌列str显示
    bool is_contained(string); //是否包含某个牌
    int __len__(); //牌列长度

    int get_index(string); //获取牌列中str的最小索引/id
    void append(card_example); //向牌列中添加card
    void remove(string); //向牌列中删除该str的最小索引card
    int count(string);
    Card_list sorted(); //排列牌列（？
    void clear(); //清空牌列
    bool is_empty(); 

    
};

bool is_wind(card_example);
bool is_zhong(card_example);

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
