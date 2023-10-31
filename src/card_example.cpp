

#include <algorithm> 

#include "card_example.h"


uint16_t card_example::code()
{
    return (color_id-1) * 10 + num;
}


string card_example::color()
{
    string color;
    switch (color_id)
    {
    case 1:
        color = "万";
        break;
    case 2:
        color = "条";
        break;
    case 3:
        color = "筒";
        break;
    case 4:
        if(num >= 1 && num <= 4) color = "风";
        else if(num >= 5 && num <= 7) color = "箭";
        break;
    default:
        color = "空";
        break;
    }
    return color;
}

string card_example::card_str()
{
    string card_str;
    switch (color_id)
    {
    case 1:
        card_str = to_string(num) + "m";
        break;
    case 2:
        card_str = to_string(num) + "s";
        break;
    case 3:
        card_str = to_string(num) + "p";
        break;
    case 4:
        card_str = to_string(num) + "z";
        break;
    default:
        card_str = "00";
        break;
    }
    return card_str;
}

string card_example::card_name()
{
    string card_name;
    switch (color_id)
    {
    case 1:
        card_name = to_string(num) + "万";
        break;
    case 2:
        card_name = to_string(num) + "条";
        break;
    case 3:
        card_name = to_string(num) + "筒";
        break;
    case 4:
        switch(num)
        {
        case 1:
            card_name = "东";
            break;
        case 2:
            card_name = "南";
            break;
        case 3:
            card_name = "西";
            break;
        case 4:
            card_name = "北";
            break;

        case 5:
            card_name = "中";
            break;
        case 6:
            card_name = "发";
            break;
        case 7:
            card_name = "白";
            break;
        default:
            card_name = "花";
            break;
        }
        break;
    default:
        card_name = "空";
        break;
    }
    return card_name;
}

bool card_example::is_yaojiu()
{
    if(num==1 || num==9)
        return true;
    else
        return false;
}
bool card_example::is_zi()
{
    if(color_id==4)
        return true;
    else
        return false;
}
bool card_example::is_wind()
{
    if(color_id == 4 && num <= 4)
        return true;
    else
        return false;
}
bool card_example::is_zhong()
{
    if(color_id == 4 && num >= 5 && num <= 7)
        return true;
    else
        return false;
}











/**
 * @brief 显示当前牌列（中文）
*/
void Card_list::show_list()
{
    cout << "Show list:" << endl;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
        cout << (*card_pointer).card_name() << "\t";
    cout << endl;
}

bool Card_list::is_contained(string cardstr)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).card_str() == cardstr)
            return true;
    }
    return false;
}
bool Card_list::is_contained(Color color_id, uint16_t num) //是否包含某个牌
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).color_id == color_id && (*card_pointer).num == num)
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
        if((*card_pointer).card_str() == cardstr)
            return card_pointer - list.begin();
    }
    cout << "Cardlist中无" << cardstr <<endl;
    return -1;
}
int Card_list::get_index(Color color_id, uint16_t num)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).color_id == color_id && (*card_pointer).num == num)
            return card_pointer - list.begin();
    }
    cout << "Cardlist中无该牌" << endl;
    return -1;
}

void Card_list::append(card_example newcard)
{
    list.push_back(newcard);
}
void Card_list::remove(string cardstr)
{
    list.erase(list.begin() + get_index(cardstr));
}
void Card_list::remove(Color color_id, uint16_t num)
{
    list.erase(list.begin() + get_index(color_id, num));
}

int Card_list::count(string cardstr)
{
    int Count = 0;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).card_str() == cardstr)
            Count++;
    }
    return Count;
}


Card_list Card_list::sorted()
{
    auto card_cmp = [](card_example cardA, card_example cardB) -> bool {
        return cardA.id < cardB.id;
    };
    sort(list.begin(), list.end(), card_cmp);
    return *this; 
}

void Card_list::clear()
{
    list.clear();
}
bool Card_list::is_empty()
{
    return list.empty();
}







