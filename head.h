#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<ctime>

using namespace std;

#define Block_Size 64								//分区大小
#define Block_Num 15*40								//分区数量
#define FileNode_Size 32							//文件结点
#define FileNode_Num 2*30							//文件结点数量
#define BlockList_Size Block_Size*Block_Num			//分区的总空间
#define FileList_Size FileNode_Size*FileNode_Num	//所有文件的总空间
#define Driver_Size BlockList_Size+FileList_Size    //磁盘总空间

struct  FileNode									//文件控制块
{
	int FileType;									//文件类型，0为空，1为目录结点，2为文本文件结点
	int BlockNum;									//文本文件的文本内容所在分区的第一个分区号
	int ParentNodeNum;								//该文件结点所在的父母结点号
	int BrotherNodeNum;								//该文件结点的同级文件结点号
	int ChildNodeNum;								//如果是目录文件结点，表示该结点下的孩子文件结点号
	char FileName[12];								//文件名
};
struct BlockNode									//分区
{
	bool IfUsing;									//该分区是否被占用
	int next;										//同一文件内容的下一个分区号，如果没有为-1
	char content[200];								//文本文件的内容
};
struct CommandArray									// cmd命令字符串数组
{
	char First[30], Second[30], Third[30], Other[30];
};
struct CommandResult								// cmd返回值
{
	int state;										// 执行cmd后当前目录
	char output[256];								// 输出信息字符串
};

FileNode FileList[FileNode_Num];					//目录项
BlockNode BlockList[Block_Num];						//磁盘分区数组

int Road[20];										//文件记录
int RoadNode;										//当前目录位置
int InputRoad[20];									//输入记录
int InputRoadNode;									//当前输入位置
char Command[200];									//存储命令输入
char First[30];										//命令名称
char Second[100];									//命令的第一个参数
char Third[100];									//命令的第二个参数
char Other[100];									//命令的其余部分

void CreateDisk(char *A);							//创建固定大小的磁盘
void Commands(const CommandArray &, int);			//根据命令选择相关的命令处理函数
void PutOutRoad(int);								//输出路径
void Initial();										//格式化
void ReadAll();										//读取所有的信息，初始化相关变量
void WriteFileNode(int);							//将指定的文件结点写入磁盘
void WriteFileNodes(int);                           //将指定的文件结点写入磁盘，若该结点不是终端结点则写入该结点下的所有结点
void WriteBlock(int);								//将指定的分区写入磁盘
int ApplyFileNode();								//申请一个文件结点，返回结点号，如果没有空结点返回-1
int ApplyBlock();									//申请一个分区，返回分区号，如果没有空分区返回-1
void FreeFileNode(int);								//释放指定位置的文件结点
void FreeFileNodes(int);							//释放指定位置的文件结点，若该结点不是终端结点则释放该结点下的所有结点
void FreeBlock(int);								//释放指定位置的分区
void FreeBlocks(int);								//释放指定位置的分区，包括该盘块所在文本文件内容的所有分区
CommandArray Interpretation(const char*);			//将命令分段
int DistinguishRoad(int, const char*);				//解析路径
void DirectoryTo(int, int);                         //找到写入指定文件目录

CommandResult Attrib(int, const char*, const char*);         //显示一个文本文件的属性
void Cd();											 //进入指定文件    
void Copy();										 //复制文件 
void XCopy();                                        //复制文件或目录下的所有文件   
void Del();											 //删除文件
void Dir();											 //显示文件目录 
void Exit();										 //退出系统
void Format();										 //格式化磁盘
void Find();										 //查找字符串
void Help();										 //帮助
void Mk();											 //新建一个文本文件
void Mkdir();										 //新建一个文件目录
void More();										 //显示并修改文本文件内容 
void Move();										 //移动文本文件位置
void Rmdir();										 //删除一个文件目录
void Time();										 //显示系统时间
void Ver();											 //显示系统版本
void Import();										 //从磁盘外导入
void Export();										 //从磁盘外导出