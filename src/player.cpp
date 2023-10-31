

#include "player.h"


bool Player_class::is_kezi(Card_list card3)
{
    if(card3.size() != 3)
    {
        return false;
    }
    if(card3.list[0].code() == card3.list[1].code() && card3.list[0].code() == card3.list[2].code())
    {
        return true;
    }
    else
        return false;
}
bool Player_class::is_shunzi(Card_list card3)
{
    if(card3.size() != 3)
    {
        return false;
    }
    card3.sorted();

    Color color = card3.list[0].color_id;
    uint16_t first_num = card3.list[0].num;
    for(auto ptr = card3.list.begin(); ptr != card3.list.end(); ptr++) //花色不一样则为假
    {
        if(color != Zi)
        {
            if((*ptr).color_id != color)
                return false;
        }
        else if(first_num <= 4)
        {
            if((*ptr).is_wind() == false)
                return false;
        }
        else if(first_num <= 7)
        {
            if((*ptr).is_zhong() == false)
                return false;
        }
    }

    if(color != Zi) //判断顺子形状
    {
        if(card3.list[0].num == (card3.list[1].num - 1) && card3.list[0].num == (card3.list[2].num - 2))
            return true;
        else
            return false;
    }
    else //是字的话，不同就是顺子
    {
        if(card3.list[0].num != card3.list[1].num && card3.list[0].num != card3.list[2].num && card3.list[2].num != card3.list[1].num)
            return true;
        else
            return false;
    }
    
}

bool Player_class::has_quetou() //有待修改
{
    cards_hand.sorted();
    for(auto card_iter = cards_hand.list.begin(); card_iter != cards_hand.list.end(); card_iter++)
    {
        if((*card_iter).code() == (*(card_iter + 1)).code())
        {
            return true;
        }
    }
    return false;
}
bool Player_class::has_shunzi(Card_list l_s)
{
    l_s.sorted();
    int length = l_s.size();
    if(length % 3 != 0)
    {
        return false;
    }
    if(length == 3)
    {
        if(is_kezi(l_s) || is_shunzi(l_s))
            return true;
        else
            return false;
    }
    

    return true;
}



void Player_class::set_wind(string wind)
{
    this->self_wind = wind;
}

void Player_class::show()
{
    cout << name << " -- " ;
    cards_hand.show_list(); 
}




void Player_class::restart()
{
    cards_public.clear();
    cards_hand.clear();
    cards_river.clear();
    self_wind = "无";
    ting = false;
}



bool Player_class::is_3N(Card_list &card3N)
{
    int n = card3N.size();
    if(n == 0) return true;
    else if(n % 3 != 0) {
        cout << "不是3的倍数." <<endl;
        return false;
    }

    Card_list temp = card3N;
    if(temp.list[0].code() == temp.list[1].code() && temp.list[0].code() == temp.list[2].code()) { // 找到刻子则删掉刻子
        temp.remove(temp.list[0].code());
        temp.remove(temp.list[0].code());
        temp.remove(temp.list[0].code());
        return is_3N(temp);
    }
    else { // 找顺子
        int index1 = temp.get_index(temp.list[0].code() + 1);
        int index2 = temp.get_index(temp.list[0].code() + 2);
        if(index1 != -1 && index2 != -1 ) { // 找到顺子
            temp.remove(temp.list[0].code());
            temp.remove(temp.list[0].code()+1);
            temp.remove(temp.list[0].code()+2);
            return is_3N(temp);
        }
        else {
            return false;
        }
    }
}

bool Player_class::is_3Nplus2(Card_list &card3N_2)
{
    card3N_2.sorted();
    for(int i = 0; i < card3N_2.size() - 1; i++) {
        Card_list hupaixing = card3N_2;
        if (hupaixing.list[i].code() == hupaixing.list[i + 1].code()) {
            hupaixing.remove(hupaixing.list[i].code());
            hupaixing.remove(hupaixing.list[i].code());
            if (is_3N(hupaixing)) {
                return true;
            }
        }
    }
    return false;

}


/*
player_class::player_class(string NAME="Player")
{
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

}
*/

//#include <cassert>
/**
bool Player_class::is_3N(Card_list card3N)
{
    int p = 0;
    int length = card3N.__len__();
    assert(length % 3 == 0);

    while (p < length) {
        string color = card3N.list[p].color();
        // AA
        if (card3N.list[p].card_str() == card3N.list[p + 1].card_str()) {
            // AAA
            if (card3N.list[p].card_str() == card3N.list[p + 2].card_str()) {
                p += 3;
                continue;
            }
            // AABBCC
            else {
                if (p + 5 >= length) return false;
                
                uint16_t num = card3N.list[p].num;
                if (color == card3N.list[p+2].color() && color == card3N.list[p+3].color() && color == card3N.list[p+4].color() && color == card3N.list[p+5].color() 
                    && num + 1 == card3N.list[p+2].num && num + 1 == card3N.list[p+3].num && num + 2 == card3N.list[p+4].num && num + 2 == card3N.list[p+5].num ) {
                        p += 6;
                        continue;
                }
                return false
            }
        }
        // ABC
        else {
            if (color == card3N.list[p+2].color() && color == card3N.list[p+3].color())
        }
        
    }
}*/

