#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


bool is_3N(vector<int> &cards_list) // 使用前备份cardlist,且升序排序
{
    int n = cards_list.size();
    if(n == 0) return true;
    else if(n % 3 != 0) {
        cout << "不是3的倍数." <<endl;
        return false;
    }

    vector<int> temp = cards_list;
    if(temp[0] == temp[1] && temp[0] == temp[2]) { // 找到刻子则删掉刻子
        temp.erase(temp.begin());
        temp.erase(temp.begin());
        temp.erase(temp.begin());
        return is_3N(temp);
    }
    else { // 找顺子
        auto it1 = find(temp.begin(), temp.end(), temp[0] + 1);
        auto it2 = find(temp.begin(), temp.end(), temp[0] + 2);
        if(it1 != temp.end() && it2 != temp.end() ) { // 找到顺子
            temp.erase(it2);
            temp.erase(it1);
            temp.erase(temp.begin());
            return is_3N(temp);
        }
        else {
            return false;
        }
    }
}

void show_vector(vector<int> &card3N)
{
    for(auto num:card3N) {
        cout << num << " "; 
    }
    cout <<endl;
}

bool is_3N_Feng(vector<int> &card3N)
{
    size_t n = card3N.size();
    if(n == 0) return true;
    else if(n % 3 != 0) {
        cout << "不是3的倍数." <<endl;
        return false;
    }

    size_t  index1, index2;
    if(card3N[0] <= 2) { // 找顺子
        index1 = find(card3N.begin(), card3N.end(), card3N[0] + 1) - card3N.begin();
        index2 = find(card3N.begin(), card3N.end(), card3N[0] + 2) - card3N.begin();
        if(index1 != card3N.size() && index2 != card3N.size() ) { // 找到顺子
            vector<int> temp = card3N;
            temp.erase(temp.begin() + index2);
            temp.erase(temp.begin() + index1);
            temp.erase(temp.begin());
            show_vector(temp);
            if (is_3N_Feng(temp)) return true;
        }
        // 找到顺子也可以继续尝试其他组合
        if(card3N[0] == 1) {
            int index3 = find(card3N.begin(), card3N.end(), card3N[0] + 3) - card3N.begin();
            if(index1 != card3N.size() && index3 != card3N.size()) { // 找到顺子
                vector<int> temp = card3N;
                temp.erase(temp.begin() + index3);
                temp.erase(temp.begin() + index1);
                temp.erase(temp.begin());
                show_vector(temp);
                if (is_3N_Feng(temp)) return true;
            }
            if(index2 != card3N.size() && index3 != card3N.size() ) { // 找到顺子
                vector<int> temp = card3N;
                temp.erase(temp.begin() + index3);
                temp.erase(temp.begin() + index2);
                temp.erase(temp.begin());
                show_vector(temp);
                if (is_3N_Feng(temp)) return true;
            }
        }
    }

    if(card3N[0] == card3N[1] && card3N[0] == card3N[2]) { // 找到刻子则删掉刻子
        vector<int> temp = card3N;
        temp.erase(temp.begin());
        temp.erase(temp.begin());
        temp.erase(temp.begin());
        show_vector(temp);
        if (is_3N_Feng(temp)) return true;
    }

    return false;

}



int main()
{

    std::vector<int> numbers;
    int n;
    
    std::cout << "请输入一串数（输入非整数结束）：" << std::endl;
    
    while (std::cin >> n) {
        numbers.push_back(n%10);
    }
    sort(numbers.begin(), numbers.end() );

    for(auto i:numbers) {
        cout << i <<" ";
    }
    cout << endl << "是3N吗?  " << is_3N_Feng(numbers) <<endl;
    return 0;
}

