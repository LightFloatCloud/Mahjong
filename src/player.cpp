

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
bool Player_class::is_shunzi(Card_list card3) // 需要修改
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
        if(!card3.list[0].is_Zi())
        {
            if((*ptr).color_id != color)
                return false;
        }
        else if(first_num <= 4)
        {
            if((*ptr).is_Feng() == false)
                return false;
        }
        else if(first_num <= 7)
        {
            if((*ptr).is_Zhong() == false)
                return false;
        }
    }

    if(!card3.list[0].is_Zi()) //判断顺子形状
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

int Player_class::has_quetou(Card_list l_s)
{
    l_s.sorted();
    int res = 0;

    auto card_iter = l_s.list.begin();
    while(card_iter + 1 < l_s.list.end()) {
        uint16_t code = (*card_iter).code();
        if(code == (*(card_iter + 1)).code())
        {
            res ++;
            card_iter += 2;
        }
        else
        {
            card_iter ++;
        }
        
    }
    return res;
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
        //cout << "不是3的倍数." <<endl;
        return false;
    }

    Card_list temp = card3N;
    if(temp.list[0].code() == temp.list[1].code() && temp.list[0].code() == temp.list[2].code()) { // 找到刻子则删掉刻子
    //cout << "Kezi:remove " << card_example::code2str(temp.list[0].code()) <<endl;
        uint16_t code = temp.list[0].code();
        temp.remove(code);
        temp.remove(code);
        temp.remove(code);
        return is_3N(temp);
    }
    else { // 找顺子
        int index1, index2;
        index1 = temp.get_index(temp.list[0].code() + 1);
        index2 = temp.get_index(temp.list[0].code() + 2);
        
        if(index1 != -1 && index2 != -1 ) { // 找到顺子
            uint16_t code = temp.list[0].code();
        //cout << "Shunzi:remove " << card_example::code2str(code) <<endl;
            temp.remove(code);
            temp.remove(code+1);
            temp.remove(code+2);
            
            return is_3N(temp);
        }
        else {
            return false;
        }
    }
}

bool Player_class::is_3N_Feng(Card_list &card3N)
{
    int n = card3N.size();
    if(n == 0) return true;
    else if(n % 3 != 0) {
        // cout << "不是3的倍数." <<endl;
        return false;
    }

    int index1, index2;
    if(card3N.list[0].num <= 2) { // 找顺子
        index1 = card3N.get_index(card3N.list[0].code() + 1);
        index2 = card3N.get_index(card3N.list[0].code() + 2);
        if(index1 != -1 && index2 != -1 ) { // 找到顺子
            Card_list temp = card3N;
            uint16_t code = temp.list[0].code();
            temp.remove(code);
            temp.remove(code+1);
            temp.remove(code+2);
            if (is_3N_Feng(temp)) return true;
        }
        // 找到顺子也可以继续尝试其他组合
        if(card3N.list[0].num == 1) {
            int index3 = card3N.get_index(card3N.list[0].code() + 3);
            if(index1 != -1 && index3 != -1 ) { // 找到顺子
                Card_list temp = card3N;
                uint16_t code = temp.list[0].code();
                temp.remove(code);
                temp.remove(code+1);
                temp.remove(code+3);
                if (is_3N_Feng(temp)) return true;
            }
            if(index2 != -1 && index3 != -1 ) { // 找到顺子
                Card_list temp = card3N;
                uint16_t code = temp.list[0].code();
                temp.remove(code);
                temp.remove(code+2);
                temp.remove(code+3);
                if (is_3N_Feng(temp)) return true;
            }
        }
    }

    if(card3N.list[0].code() == card3N.list[1].code() && card3N.list[0].code() == card3N.list[2].code()) { // 找到刻子则删掉刻子
        Card_list temp = card3N;
        uint16_t code = temp.list[0].code();
        temp.remove(code);
        temp.remove(code);
        temp.remove(code);
        if (is_3N_Feng(temp)) return true;
    }

    return false;

}

bool Player_class::is_3Nplus2(Card_list &card3N_2)
{
    card3N_2.sorted();



    for(int i = 0; i < card3N_2.size() - 1; i++) {
        Card_list hupaixing = card3N_2;


        if (hupaixing.list[i].code() == hupaixing.list[i + 1].code()) {
            hupaixing.remove(hupaixing.list[i].code());
            hupaixing.remove(hupaixing.list[i].code());
            Card_list m_list, s_list, p_list, Feng_list, Zhong_list;


            for(auto pai:hupaixing.list) {
                switch (pai.color_id)
                {
                case Wan:
                    m_list.append(pai);
                    break;
                case Tiao:
                    s_list.append(pai);
                    break;
                case Tong:
                    p_list.append(pai);
                    break;
                case Feng:
                    Feng_list.append(pai);
                    break;
                case Jian:
                    Zhong_list.append(pai);
                    break;
                default:
                    break;
                }
            }

            if (is_3N(m_list) && is_3N(s_list) && is_3N(p_list) && is_3N_Feng(Feng_list) && is_3N(Zhong_list) ) {
                return true;
            }
        }
        
    }
    return false;

}

bool Player_class::is_7dui(Card_list &card7dui)
{
    int numofdui = has_quetou(card7dui);
    if(numofdui == 7) {
        return true;
    }
    else {
        return false;
    }
    return false;
}


vector<uint16_t> Player_class::is_ting()
{
    vector<uint16_t> ting_codes;


    for(uint16_t code = 11; code <= 57; code++) {
        if(code % 10 == 0) {
            continue;
        }else if (code >=45 && code <= 54)
        {
            code = 55;
        }
//cout << "now " << card_example::code2str(code) <<endl;
        Card_list try_list = cards_hand;
        try_list.append(card_example::code2card(code));
        if(is_3Nplus2(try_list)  || is_7dui(try_list)) {
            ting_codes.push_back(code);
        }
        
    }

    return ting_codes;



}


uint8_t Player_class::can_chi(uint16_t card_code)
{
    int count_fore_1 = 0;
    int count_fore_2 = 0;
    int count_post_1 = 0;
    int count_post_2 = 0;
    for(auto card_pointer = cards_hand.list.begin(); card_pointer != cards_hand.list.end(); card_pointer++)
    {
        if(card_code == (*card_pointer).code() - 2) count_fore_2 ++;
        else if(card_code == (*card_pointer).code() - 1) count_fore_1 ++;
        else if(card_code == (*card_pointer).code() + 1) count_post_1 ++;
        else if(card_code == (*card_pointer).code() + 2) count_post_2 ++;
    }

    uint8_t res = 0x00;
    if(count_fore_1 > 0 && count_post_1 > 0) res |= 0x02;
    if(count_fore_1 > 0 && count_fore_2 > 0) res |= 0x01;
    if(count_post_1 > 0 && count_post_2 > 0) res |= 0x04;

    return res;
}

bool Player_class::can_peng(uint16_t card_code)
{
    if (cards_hand.count(card_code) >= 2) {
        return true;
    }
    return false;
}

bool Player_class::can_gang(uint16_t card_code)
{
    if (cards_hand.count(card_code) >= 3) {
        return true;
    }
    return false;
}

bool Player_class::can_hu(uint16_t card_code)
{
    Card_list temp = cards_hand;
    temp.append(card_example::code2card(card_code));
    if(is_3Nplus2(temp)  || is_7dui(temp)) {
        return true;
    }
    return false;
}


void Player_class::chi(card_example card, uint8_t mode)
{
    uint16_t card_code = card.code();
    
    card_example card1, card2;

    if(mode == 0x00) return;
    else if(mode == 0x01) {
        card1 = cards_hand.remove(card_code - 2);
        card2 = cards_hand.remove(card_code - 1);
    }
    else if(mode == 0x02) {
        card1 = cards_hand.remove(card_code - 1);
        card2 = cards_hand.remove(card_code + 1);
    }
    else if(mode == 0x04) {
        card1 = cards_hand.remove(card_code + 1);
        card2 = cards_hand.remove(card_code + 2);
    }
    else {
        cerr << "Err in Player_class::chi()\n";
    }
    
    Card_list cards3;
    cards3.append(card);
    cards3.append(card1);
    cards3.append(card2);

    cards_public.push_back(cards3);
}

void Player_class::peng(card_example card)
{
    uint16_t card_code = card.code();
    card_example card1, card2;
    card1 = cards_hand.remove(card_code);
    card2 = cards_hand.remove(card_code);

    Card_list cards3;
    cards3.append(card);
    cards3.append(card1);
    cards3.append(card2);

    cards_public.push_back(cards3);
}



void Player_class::action()
{
    
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

