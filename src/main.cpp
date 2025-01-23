#ifdef _WIN32
#include <windows.h>
#endif

#include "game_class.h"

#include <unistd.h>
#include <limits>
#include <cassert>


using namespace std;



int cosplay(Game_class &game, uint16_t &play_code);


int main()
{
#ifdef _WIN32
    system("cls");
    system("chcp 65001");
#endif
    Game_class game;

    // 游戏主循环
    while(game.getState() != GameState::GAME_OVER) {
        switch(game.getState()) {
            case GameState::PLAYER_TURN: {
                if(game.turn == 1)
                    system("cls");

                // 听牌显示
                vector<uint16_t> ting_codes = game.player[game.turn].is_ting();
                if(!ting_codes.empty()) {
                    cout << "\033[1;33m听牌：\033[0m" ;
                    for(auto code:ting_codes) {
                        cout << card_example::code2str(code) << " ";
                    }
                }

                // 摸牌
                uint16_t newcard_code = game.drawcard();
                uint16_t play_code = newcard_code; // AI 默认出牌

                game.show_playercards(4);
                
                // 判胡
                bool is_over = false;
                bool is_Hu = false; 
                string prompt;
                is_over = game.is_over(is_Hu, prompt);
                if(is_Hu) {
                    cout << prompt <<endl;
                    game.setState(GameState::GAME_OVER);
                    break;
                }

                // 玩家决定出牌
                int user_answer;
                do { 
                    user_answer = cosplay(game, play_code);
                } while (user_answer == -2);
                
                if(user_answer == -1) { // 退出
                    game.setState(GameState::GAME_OVER);
                    break;
                }

                // 打牌
                int index = game.player[game.turn].cards_hand.get_index(play_code);
                assert(index >= 0);
                card_example card_play = game.player[game.turn].cards_hand.list[index];
                game.player[game.turn].cards_hand.list.erase(game.player[game.turn].cards_hand.list.begin() + index);
                
                game.player[game.turn].cards_river.append(card_play);
                game.player[game.turn].cards_hand.sorted();

                // 流局
                if(game.chang_nownum == 137) {
                    cout << "牌局结束" << endl;
                    game.setState(GameState::GAME_OVER);
                    break;
                }

                // 下一轮
                game.turn++;
                if(game.turn == 4) game.turn = 0;

                // 检查是否需要进入询问动作状态
                game.setState(GameState::ENQUIRE_ACTION);
                break;
            }
            case GameState::ENQUIRE_ACTION:
                // 这里可以添加吃碰杠的判断逻辑
                game.setState(GameState::PLAYER_TURN);
                break;
            default:
                break;
        }
    }
// game.player[0].cards_hand.append(card_example::code2card(card_example::str2code("4m")));


    cin.get();
    return 0;
}


int cosplay(Game_class &game, uint16_t &play_code)
{
    string input;
    if(game.turn == 0) {
        std::cout << "还有" << 137 - game.chang_nownum << "张牌, ";
        std::cout << "请输入要打出的牌（例如 '4m'）或 'q/Q' 退出: ";
        std::cin >> input;  
        // 清空输入缓冲区，直到遇到换行符
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(input == "q" || input == "Q") {
            cout << "退出！" << endl;
            return -1;
        }
        // system("cls");
        play_code = card_example::str2code(input);

        // 检查输入的牌是否存在
        int count = game.player[game.turn].cards_hand.count(play_code);
        if(count == 0) {
            cout << "要打的牌不存在，请重新输入" <<endl;
            return -2;
        }
    } else {
        // AI 默认出牌
        play_code = game.player[game.turn].cards_hand.list.front().code();
    }
    return 0;
}

// 经过代码分析，当前麻将程序的结构有以下优化建议：

// 1. 重构游戏状态管理：

// - 引入状态机模式，将游戏流程分解为明确的状态（如准备、发牌、出牌、结算等）
// - 每个状态封装对应的逻辑，提高代码可维护性

// 2. 完善核心游戏机制：

// - 实现吃、碰、杠等操作的完整逻辑
// - 增加对特殊牌型（如十三幺、全不靠）的支持
// - 实现番种计算功能

// 3. 优化AI系统：

// - 将AI决策逻辑从主循环中分离
// - 实现更智能的AI策略（如防守、进攻模式）
// - 增加AI学习能力

// 4. 改进代码结构：

// - 分离游戏逻辑和UI显示
// - 使用更高效的数据结构管理牌列
// - 增加单元测试覆盖率

// 5. 扩展功能：

// - 支持更多麻将规则
// - 实现回放和统计功能
