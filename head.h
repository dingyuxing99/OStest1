#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<ctime>

using namespace std;

#define Block_Size 64								//������С
#define Block_Num 15*40								//��������
#define FileNode_Size 32							//�ļ����
#define FileNode_Num 2*30							//�ļ��������
#define BlockList_Size Block_Size*Block_Num			//�������ܿռ�
#define FileList_Size FileNode_Size*FileNode_Num	//�����ļ����ܿռ�
#define Driver_Size BlockList_Size+FileList_Size    //�����ܿռ�

struct  FileNode									//�ļ����ƿ�
{
	int FileType;									//�ļ����ͣ�0Ϊ�գ�1ΪĿ¼��㣬2Ϊ�ı��ļ����
	int BlockNum;									//�ı��ļ����ı��������ڷ����ĵ�һ��������
	int ParentNodeNum;								//���ļ�������ڵĸ�ĸ����
	int BrotherNodeNum;								//���ļ�����ͬ���ļ�����
	int ChildNodeNum;								//�����Ŀ¼�ļ���㣬��ʾ�ý���µĺ����ļ�����
	char FileName[12];								//�ļ���
};
struct BlockNode									//����
{
	bool IfUsing;									//�÷����Ƿ�ռ��
	int next;										//ͬһ�ļ����ݵ���һ�������ţ����û��Ϊ-1
	char content[200];								//�ı��ļ�������
};
struct CommandArray									// cmd�����ַ�������
{
	char First[30], Second[30], Third[30], Other[30];
};
struct CommandResult								// cmd����ֵ
{
	int state;										// ִ��cmd��ǰĿ¼
	char output[256];								// �����Ϣ�ַ���
};

FileNode FileList[FileNode_Num];					//Ŀ¼��
BlockNode BlockList[Block_Num];						//���̷�������

int Road[20];										//�ļ���¼
int RoadNode;										//��ǰĿ¼λ��
int InputRoad[20];									//�����¼
int InputRoadNode;									//��ǰ����λ��
char Command[200];									//�洢��������
char First[30];										//��������
char Second[100];									//����ĵ�һ������
char Third[100];									//����ĵڶ�������
char Other[100];									//��������ಿ��

void CreateDisk(char *A);							//�����̶���С�Ĵ���
void Commands(const CommandArray &, int);			//��������ѡ����ص��������
void PutOutRoad(int);								//���·��
void Initial();										//��ʽ��
void ReadAll();										//��ȡ���е���Ϣ����ʼ����ر���
void WriteFileNode(int);							//��ָ�����ļ����д�����
void WriteFileNodes(int);                           //��ָ�����ļ����д����̣����ý�㲻���ն˽����д��ý���µ����н��
void WriteBlock(int);								//��ָ���ķ���д�����
int ApplyFileNode();								//����һ���ļ���㣬���ؽ��ţ����û�пս�㷵��-1
int ApplyBlock();									//����һ�����������ط����ţ����û�пշ�������-1
void FreeFileNode(int);								//�ͷ�ָ��λ�õ��ļ����
void FreeFileNodes(int);							//�ͷ�ָ��λ�õ��ļ���㣬���ý�㲻���ն˽�����ͷŸý���µ����н��
void FreeBlock(int);								//�ͷ�ָ��λ�õķ���
void FreeBlocks(int);								//�ͷ�ָ��λ�õķ������������̿������ı��ļ����ݵ����з���
CommandArray Interpretation(const char*);			//������ֶ�
int DistinguishRoad(int, const char*);				//����·��
void DirectoryTo(int, int);                         //�ҵ�д��ָ���ļ�Ŀ¼

CommandResult Attrib(int, const char*, const char*);         //��ʾһ���ı��ļ�������
void Cd();											 //����ָ���ļ�    
void Copy();										 //�����ļ� 
void XCopy();                                        //�����ļ���Ŀ¼�µ������ļ�   
void Del();											 //ɾ���ļ�
void Dir();											 //��ʾ�ļ�Ŀ¼ 
void Exit();										 //�˳�ϵͳ
void Format();										 //��ʽ������
void Find();										 //�����ַ���
void Help();										 //����
void Mk();											 //�½�һ���ı��ļ�
void Mkdir();										 //�½�һ���ļ�Ŀ¼
void More();										 //��ʾ���޸��ı��ļ����� 
void Move();										 //�ƶ��ı��ļ�λ��
void Rmdir();										 //ɾ��һ���ļ�Ŀ¼
void Time();										 //��ʾϵͳʱ��
void Ver();											 //��ʾϵͳ�汾
void Import();										 //�Ӵ����⵼��
void Export();										 //�Ӵ����⵼��