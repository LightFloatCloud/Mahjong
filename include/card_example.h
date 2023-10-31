#ifndef __CARD_EXAMPLE_H
#define __CARD_EXAMPLE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint> //uint16







using namespace std;




enum Color {
    Wan = 1,
    Tiao = 2,
    Tong = 3,
    Zi = 4,
    Other = 0
};


struct card_example
{
    uint16_t    id;
    Color    color_id;
    uint16_t    num;

    uint16_t    code();  // 编码标识 1~9 万 11~19 条 21~29 筒 31~34 风 35~37 箭

    string      color();
    string      card_str(); // 英文牌名
    string      card_name(); // 中文牌名


    bool is_yaojiu();
    bool is_zi();
    bool is_wind();
    bool is_zhong();


};
    

/**
 * @brief 牌元素构成的牌列
 * 
 */
class Card_list
{
private:
    //void Card_list_init(vector<card_example> __list);

public:
    
    Card_list(vector<card_example> _list = vector<card_example>(0)) : list(_list) {};

    vector<card_example> list; //牌列

    void show_list(); //牌列str显示
    bool is_contained(string); //是否包含某个牌
    bool is_contained(Color color_id, uint16_t num); 
    int __len__(); //牌列长度

    int get_index(uint16_t cardcode); //获取牌列中str的最小索引/id
    int get_index(Color color_id, uint16_t num);



    void append(card_example); //向牌列中添加card
    void remove(uint16_t cardcode); //向牌列中删除该str的最小索引card
    void remove(Color color_id, uint16_t num);
    int count(string);
    Card_list sorted(); //排列牌列（？
    void clear(); //清空牌列
    bool is_empty(); 


    
};










#endif

