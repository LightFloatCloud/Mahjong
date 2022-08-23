

#include "player.h"


bool Player_class::is_kezi(Card_list card3)
{
    if(card3.__len__() != 3)
    {
        return false;
    }
    if(card3.list[0].card_str == card3.list[1].card_str && card3.list[0].card_str == card3.list[2].card_str)
    {
        return true;
    }
    else
        return false;
}
bool Player_class::is_shunzi(Card_list card3)
{
    if(card3.__len__() != 3)
    {
        return false;
    }
    card3.sorted();

    uint16_t color = card3.list[0].color_id;
    uint16_t first_num = card3.list[0].num;
    for(auto ptr = card3.list.begin(); ptr != card3.list.end(); ptr++) //花色不一样则为假
    {
        if(color != 4)
        {
            if((*ptr).color_id != color)
                return false;
        }
        else if(first_num <= 4)
        {
            if(is_wind((*ptr)) == false)
                return false;
        }
        else if(first_num <= 7)
        {
            if(is_zhong((*ptr)) == false)
                return false;
        }
    }

    if(color !=4) //判断顺子形状
    {
        if(card3.list[0].num == (card3.list[1].num - 1) && card3.list[0].num == (card3.list[2].num - 2))
            return true;
        else
            return false;
    }
    else
    {
        if(card3.list[0].num != card3.list[1].num && card3.list[0].num != card3.list[2].num && card3.list[2].num != card3.list[1].num)
            return true;
        else
            return false;
    }
    
}

bool Player_class::has_quetou(Card_list l_q) //有待修改
{
    l_q.sorted();
    for(auto card_iter = l_q.list.begin(); card_iter != l_q.list.end(); card_iter++)
    {
        if((*card_iter).card_str == (*(card_iter + 1)).card_str)
        {
            l_q.remove((*card_iter).card_str);
            l_q.remove((*card_iter).card_str);
            //////////////////
            return true;
        }
    }
    return false;
}
bool Player_class::has_shunzi(Card_list l_s)
{
    l_s.sorted();
    int length = l_s.__len__();
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


