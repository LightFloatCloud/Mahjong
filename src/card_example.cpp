

#include <algorithm> 
#include <cassert>
#include "card_example.h"


uint16_t card_example::code()
{
    return (color_id) * 10 + num; // x1~x9
    // 41~44
    // 55~57
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
        break;
    case 5:
        if(num >= 5 && num <= 7) color = "箭";
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
    case 5:
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
        default:
            card_name = "未定义";
            break;
        }
        break;
    case 5:
        switch(num)
        {
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
            card_name = "未定义";
            break;
        }
        break;
    default:
        card_name = "空";
        break;
    }
    return card_name;
}

bool card_example::is_YaoJiu()
{
    if(num==1 || num==9)
        return true;
    else
        return false;
}
bool card_example::is_Zi()
{
    if(color_id == 4 || color_id == 5)
        return true;
    else
        return false;
}
bool card_example::is_Feng()
{
    if(color_id == 4 && num <= 4)
        return true;
    else
        return false;
}
bool card_example::is_Zhong()
{
    if(color_id == 5 && num >= 5 && num <= 7)
        return true;
    else
        return false;
}

string card_example::code2str(uint16_t code)
{
    string card_str;
    int color_id = code / 10;
    int num = code % 10;
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
    case 5:
        card_str = to_string(num) + "z";
        break;
    default:
        card_str = "00";
        break;
    }
    return card_str;
}


uint16_t card_example::str2code(string str)
{
    if(str.size() != 2) {
        cout << "字符i长度错误！" << endl;
        return 0;
    }

    int num = str[0] - '0';
    int color = 0;
    
    switch (str[1])
    {
    case 'm':
        color = 1;
        break;
    case 's':
        color = 2;
        break;
    case 'p':
        color = 3;
        break;
    case 'z':
        if(num <= 4) color = 4;
        else if(num <= 7) color = 5;
        break;
    default:
        cout << "花色错误！" << endl;
        break;
    }

    return color * 10 + num;

}

card_example card_example::code2card(uint16_t code)
{
    card_example card;
    card.color_id = static_cast<Color>(code / 10);
    card.num = code % 10;
    if(card.color_id == Jian) card.id = (card.color_id - 2)*36 + (card.num-1)*4 + 1;
    else card.id = (card.color_id - 1)*36 + (card.num-1)*4 + 1;
    return card;
}






/**
 * @brief 显示当前牌列（中文）显示颜色
*/
void Card_list::show_list()
{
    cout << "Show list:" << endl;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).color_id == Wan) {
            cout << "\033[31m" ;  // 红色
        }
        else if((*card_pointer).color_id == Tiao) {
            cout << "\033[32m" ;  // 绿色
        }
        else if((*card_pointer).color_id == Tong) {
            cout << "\033[34m" ;  // 蓝色
        }
        else if((*card_pointer).color_id == Feng) {
            //cout << "\033[34m" ;  // 白色
        }
        else if((*card_pointer).color_id == Jian) {
            cout << "\033[33m" ;  // 黄色
        }
        cout << (*card_pointer).card_name() << "\t";
        cout << "\033[0m" ;
    }
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

int Card_list::size()
{
    return list.size();
}

int Card_list::get_index(uint16_t cardcode)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).code() == cardcode)
            return card_pointer - list.begin();
    }
    //cout << "Cardlist中无" << cardcode <<endl;
    return -1;
}
int Card_list::get_index(Color color_id, uint16_t num)
{
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).color_id == color_id && (*card_pointer).num == num)
            return card_pointer - list.begin();
    }
    //cout << "Cardlist中无该牌" << endl;
    return -1;
}

void Card_list::append(card_example newcard)
{
    list.push_back(newcard);
}
card_example Card_list::remove(uint16_t cardcode)
{
    int index = get_index(cardcode);
    assert(index >= 0);
    card_example card = *(list.begin() + index);
    list.erase(list.begin() + index);
    return card;
}
void Card_list::remove(Color color_id, uint16_t num)
{
    int index = get_index(color_id, num);
    assert(index >= 0);
    list.erase(list.begin() + index);
}

int Card_list::count(uint16_t cardcode)
{
    int Count = 0;
    for(auto card_pointer = list.begin(); card_pointer != list.end(); card_pointer++)
    {
        if((*card_pointer).code() == cardcode)
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







