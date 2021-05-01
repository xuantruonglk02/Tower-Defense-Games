#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream finp("config.in");
    ofstream fout("config.h");

    fout << "#pragma once" << endl << endl;

    fout << "#include <iostream>" << endl << endl;

    fout << "const int SCREEN_WIDTH = 950;" << endl;
    fout << "const int SCREEN_HEIGHT = 650;" << endl << endl;

    fout << "const int PLAY_ZONE_X = 150;" << endl;
    fout << "const int PLAY_ZONE_Y = 100;" << endl;
    fout << "const int PLAY_ZONE_W = 750;" << endl;
    fout << "const int PLAY_ZONE_H = 500;" << endl << endl;

    fout << "const std::string WINDOW_TITLE = \"GoodGame.com\";" << endl;
    fout << "const std::string MENU_PATH = \"images/menu.png\";" << endl;
    fout << "const std::string O_MENU_PATH = \"images/options_menu.png\";" << endl;
    fout << "const std::string PLAY_PATH = \"images/play.png\";" << endl;
    fout << "const std::string OPTIONS_PATH = \"images/options.png\";" << endl;
    fout << "const std::string QUIT_PATH = \"images/quit.png\";" << endl;
    fout << "const std::string MUTE_PATH = \"images/die.png\";" << endl << endl;

    fout << "const std::string CTB_PATH = \"images/control_board.png\";" << endl;
    fout << "const std::string PAUSE_PATH = \"images/pause.png\";" << endl;
    fout << "const std::string HPBAR_PATH = \"images/hp_bar.png\";" << endl;
    fout << "const std::string LOCK_PATH = \"images/lock.png\";" << endl;
    fout << "const std::string NEXT_BUTTON_PATH[2] = {\"images/next_button_down.png\", \"images/next_button_up.png\"};" << endl;
    fout << "const std::string TOWER_PATH[6] = {\"images/tower0.png\"," << endl;
    fout << "                                    \"images/tower1.png\"," << endl;
    fout << "                                    \"images/tower2.png\"," << endl;
    fout << "                                    \"images/tower3.png\"," << endl;
    fout << "                                    \"images/tower4.png\"," << endl;
    fout << "                                    \"images/tower5.png\"};" << endl;
    fout << "const std::string REVIEW_BOARD_PATH[6] = {\"images/info.png\"," << endl;
    fout << "                                            \"images/info.png\"," << endl;
    fout << "                                            \"images/info.png\"," << endl;
    fout << "                                            \"images/info.png\"," << endl;
    fout << "                                            \"images/info.png\"," << endl;
    fout << "                                            \"images/info.png\"};" << endl << endl;

    fout << "const std::string MAP_PATH = \"images/map.png\";" << endl;
    fout << "const std::string ROAD_PATH = \"images/road.png\";" << endl << endl;

    fout << "const std::string UPDATE_BOARD_PATH = \"images/update_board.png\";" << endl;
    fout << "const std::string INC_BUTTON_PATH = \"images/inc_button.png\";" << endl;
    fout << "const std::string SHOOTING_RANGE_CIRCLE_PATH = \"images/circle.png\";" << endl;
    fout << "const std::string LEVER_PATH = \"images/lever.png\";" << endl;
    fout << "const std::string BLOCK_PATH = \"images/block.png\";" << endl << endl;

    fout << "const std::string GUN_BASE_PATH = \"images/gun_base.png\";" << endl;
    fout << "const std::string GUN_PATH[4][2] = {{\"images/gun0_1.png\", \"images/gun0_2.png\"}," << endl;
    fout << "                                    {\"images/gun1_1.png\", \"images/gun1_2.png\"}," << endl;
    fout << "                                    {\"images/gun2_1.png\", \"images/gun2_2.png\"}," << endl;
    fout << "                                    {\"images/gun3_1.png\", \"images/gun3_1.png\"}};" << endl;
    fout << "const std::string ROCKET_FIRST = \"images/rocket_1.png\";" << endl << endl;

    fout << "const std::string SUP_BASE_PATH = \"images/supporter_base.png\";" << endl;
    fout << "const std::string SUP_DAME_PATH[9] = {\"images/1.png\"," << endl;
    fout << "                                        \"images/2.png\"," << endl;
    fout << "                                        \"images/3.png\"," << endl;
    fout << "                                        \"images/4.png\"," << endl;
    fout << "                                        \"images/5.png\"," << endl;
    fout << "                                        \"images/6.png\"," << endl;
    fout << "                                        \"images/7.png\"," << endl;
    fout << "                                        \"images/8.png\"," << endl;
    fout << "                                        \"images/9.png\"};" << endl;
    fout << "const std::string SUP_RANGE_PATH = \"images/rada.png\";" << endl << endl;

    fout << "const std::string ENEMY_PATH[3] = {\"images/enemy1.png\"," << endl;
    fout << "                                    \"images/enemy2.png\"," << endl;
    fout << "                                    \"images/enemy3.png\"};" << endl << endl;

    fout << "const std::string BULLET_PATH[4] = {\"images/bullet.png\"," << endl;
    fout << "                                    \"images/double_bullet.png\"," << endl;
    fout << "                                    \"images/laze.png\"," << endl;
    fout << "                                    \"images/rocket_2.png\"};" << endl << endl;

    fout << "const std::string BOOM_PATH[5] = {\"images/boom_1.png\"," << endl;
    fout << "                                    \"images/boom_2.png\"," << endl;
    fout << "                                    \"images/boom_3.png\"," << endl;
    fout << "                                    \"images/boom_4.png\"," << endl;
    fout << "                                    \"images/boom_5.png\"};" << endl << endl;

    fout << "const int BUTTON_W = 270;" << endl;
    fout << "const int BUTTON_H = 70;" << endl;
    fout << "const int BUTTON_DISTANCE = 20;" << endl;
    fout << "const int OPTIONS_MENU_W = 300, OPTIONS_MENU_H = 200;" << endl;
    fout << "const int MUSIC_X = 100, MUSIC_Y = 100, MUSIC_R = 30;" << endl;
    fout << "const int SOUND_X = 200, SOUND_Y = 100;" << endl << endl;

    fout << "const int REVIEW_BOARD_SIZE[6][2] = {{100, 100}, {200, 200}, {100, 200}, {200, 100}, {300, 300}, {150, 200}}; " << endl;
    fout << "const int NEXT_BUTTON_W = 130, NEXT_BUTTON_H = 60;" << endl;
    fout << "const int TOWER_BOARD_X = 3, TOWER_BOARD_Y = 206;" << endl;
    fout << "const int UPDATE_BOARD_W = 130, UPDATE_BOARD_H = 214;" << endl;
    fout << "const int DISTANCE = 10;" << endl;
    fout << "const int LOCK_W = 27, LOCK_H = 40;" << endl;
    fout << "const int WAITING_WAVE_TIME_DEFAULT = 16000;" << endl << endl;

    fout << "const int MAP_ROW = 10;" << endl;
    fout << "const int MAP_COL = 15;" << endl;
    fout << "const int MAP_SIZE = 150;" << endl << endl;

    fout << "const int UPDATE_BOARD_BORDER = 5;" << endl;
    fout << "const int INC_BUTTON_SIZE = 30;" << endl << endl;

    fout << "const int GUN_BASE_SIZE = 40;" << endl;
    fout << "const int ROCKET_FIRST_H = 52;" << endl;
    fout << "const int ROCKET_FIRST_W = 24;" << endl;
    fout << "const int GUN_W[4][2] = {{24, 24}, {24, 24}, {24, 24}, {30, 30}};" << endl;
    fout << "const int GUN_H[4][2] = {{52, 73}, {52, 81}, {52, 52}, {30, 30}};" << endl << endl;

    fout << "const int SUP_SIZE[2] = {40, 54};" << endl << endl;

    fout << "const int ENEMY_SIZE = 21;" << endl << endl;

    fout << "const int BULLET_SIZE = 8;" << endl << endl;
    fout << "const int DOUBLE_BULLET_W = 18;" << endl;
    fout << "const int DOUBLE_BULLET_H = 8;" << endl;
    fout << "const int ROCKET_W[2] = {24, 24};" << endl;
    fout << "const int ROCKET_H[2] = {52, 75};" << endl;
    fout << "const int BULLET_SPEED[4] = {20, 20, 0, 5};" << endl;
    fout << "const int BOOM_RANGE = 50;" << endl << endl;

    int a, b, c, d;
    string s;
///////////////////////////////////////////
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_PRICE[4] = {" << a << ", " << b << ", " << c << ", " << d << "};" << endl;

    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_DAMAGE[4] = {" << a << ", " << b << ", " << c << ", " << d << "};" << endl;

    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_RANGE[4] = {" << a << ", " << b << ", " << c << ", " << d << "};" << endl;

    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_SHOT_DELAY_TIME[4] = {" << a << ", " << b << ", " << c << ", " << d << "};" << endl << endl;
////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_INC_DAMAGE[4][4] = {{" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                {" << a << ", " << b << ", " << c << ", " << d << "}};" << endl;
///////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_INC_RANGE[4][4] = {{" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                               {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                               {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                               {" << a << ", " << b << ", " << c << ", " << d << "}};" << endl;
/////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_DEC_SHOT_DELAY_TIME[4][4] = {{" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                         {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                         {" << a << ", " << b << ", " << c << ", " << d << "}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                         {" << a << ", " << b << ", " << c << ", " << d << "}};" << endl;
////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c >> d;
    fout << "const int G_UPDATE_PRICE[4][3][4] = {{{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}}," << endl;

    finp >> a >> b >> c >> d;
    fout << "                                     {{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}}," << endl;
    
    finp >> a >> b >> c >> d;
    fout << "                                     {{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}}," << endl;
    
    finp >> a >> b >> c >> d;
    fout << "                                     {{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}, ";
    finp >> a >> b >> c >> d;
    fout << "{" << a << ", " << b << ", " << c << ", " << d << "}}};" << endl << endl;
///////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b;
    fout << "const int S_PRICE[2] = {" << a << ", " << b << "};" << endl;
//////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b;
    fout << "const int S_BUFF[2] = {" << a << ", " << b << "};" << endl;
//////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b;
    fout << "const int S_RANGE[2] = {" << a << ", " << b << "};" << endl << endl;
/////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c;
    fout << "const int E_HP[3] = {" << a << ", " << b << ", " << c << "};" << endl;
///////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c;
    fout << "const int E_DAMAGE[3] = {" << a << ", " << b << ", " << c << "};" << endl;
///////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c;
    fout << "const int E_PRIZE[3] = {" << a << ", " << b << ", " << c << "};" << endl;
///////////////////////////////////////////////////
    finp.ignore();
    getline(finp, s);
    finp >> a >> b >> c;
    fout << "const double E_SPEED[3] = {" << a << ", " << b << ", " << c << "};" << endl;
///////////////////////////////////////////////////

    finp.close();
    fout.close();
}
