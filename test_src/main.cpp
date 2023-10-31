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





int main()
{

    std::vector<int> numbers;
    int n;
    
    std::cout << "请输入一串数（输入非整数结束）：" << std::endl;
    
    while (std::cin >> n) {
        numbers.push_back(n);
    }
    sort(numbers.begin(), numbers.end() );

    for(auto i:numbers) {
        cout << i <<" ";
    }
    cout << endl << "是3N吗?  " << is_3N(numbers) <<endl;
    return 0;
}

