#include <stdbool.h>

typedef struct 对弈信息 Game;
struct 对弈信息
{
	char *chessBoard;
	short *全场棋子的索引数组;
	short 全场棋子数量;
	short *黑棋索引数组;
	short 黑棋数量;
	short *红棋索引数组;
	short 红棋数量;
	
	char *当前操作方名称;
	short *当前操作方的棋子的索引数组;
	short 当前操作方的棋子数量;
	
	short *当前应对方的棋子的索引数组;
	short 当前应对方的棋子数量;
};

typedef struct 棋步信息 TheStep;
struct 棋步信息
{
	short from_x, from_y;
	short from_coord[2];
	short from_index;
	
	short to_index_of_flip;
	short to_index_of_move;
};

// 开局
void 先填满默认空(char *);
void show_棋盘(char *);
bool 是否有效索引(short index);
short 坐标转索引(short pos_x, short pos_y);
bool 索引转坐标(short index, short *单个坐标数组);
void 摆棋(char *chessBoard, short (*)[2], short , const char *);
void Game_更新全场棋子的索引数组(Game *self);

// 暂时不用。只需要单向视图，不需要双向视图。双向视图无意义。												  
void 倒转(char *chessBoard, short 棋子数量, short *棋子索引数组, short *倒转后的棋子索引数组);

// 举棋之可落点的计算
// 车
short 车_计算最理想可移动步数(short *单个坐标数组, char *移动方向);
short 判断该棋位内容情况(char pos_content);
short 车_可移动步数缩小(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向);
short 车_获取可选落点索引之单点(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向, short 本次移动步数);
short 车的可活动范围缩小及准备移动到的随机落点(char *chessBoard, short *选到的棋子的坐标数组);

// 马
short 马_近端_计算最理想可移动步数(short *单个坐标数组, char *移动方向);
short 马_近端_可移动步数缩小(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向, short 最理想可移动步数);
short 马_远端_获取可选落点索引之单点(char *chessBoard, short *选到的棋子的坐标数组, char *移动方向, short 哪边);
short 马的可活动范围缩小及准备移动到的随机落点(char *chessBoard, short *选到的棋子的坐标数组);

// 将每种棋子的唯一需要调用的计算函数统一起来
void TheStep_update_toIndexOfMove(Game *game, TheStep *着法);

// 炮
bool 该直线移动方向是索引减小的吗(const char *移动方向);
bool 该直线移动方向是纵坐标变化的吗(const char *移动方向);
void assign_by_direction(short *var, short increment, const char *移动方向);
short 炮_近端_计算最理想可移动步数(short *单个坐标数组, const char *移动方向);
bool 判断棋位与边界距离是否在某个范围内(short pos_x, short pos_y, const char *移动方向, short farthest);
short 炮_近端_可移动步数缩小(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 最理想可移动步数);
short 炮_近端_获取可选落点索引之单点(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 本次移动步数);
short 炮_远端_获取可选落点索引(char *chessBoard, short *选到的棋子的坐标数组, const char *移动方向, short 近端可移动步数);
short 炮的可活动范围缩小及准备移动到的随机落点(char *chessBoard, short *选到的棋子的坐标数组);



// 举棋之选棋

// 落棋后的变化
/*
落点只有两种：空或敌

基础变化：
一枚棋子的索引必定变化：单方可起棋索引必定变化
全场两个点的内容必定变化

额外变化（如踩敌而发生吃子）：
全场棋子数量可能变化，这时全场棋子的索引从两个重复索引中减少
单方棋子数量可能变化，这时单方棋子的索引减少一个
*/

// 一枚棋子的索引变化：单方可起棋索引变化
// 全场两个点的内容变化
void replace_num(short *container, short old_item, short new_item);

// 一枚棋子的索引变化：单方可起棋索引变化
// 全场一个点的内容变化
// 全场棋子数量变化，单方棋子数量变化
short remove_num(short *container, short item, short *size);