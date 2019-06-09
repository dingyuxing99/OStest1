#include "head.h"
#include<cstring>
//��ʾ�ı��ļ�������
CommandResult Attrib(int state, const char *Second, const char *Third)
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int nowvacation = DistinguishRoad(state, Second);
	if (nowvacation == -1)
	{
		cout << "�������·�����ļ�������ȷ" << endl;
		return;
	}
	if (nowvacation == 0)
	{
		cout << "�������·���ն˲����ı��ļ�" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (nowvacation == 1)   //���ı��ļ�
		filenodenum = InputRoad[InputRoadNode];
	if (nowvacation == 2)   //�����·��
	{
		filenodenum = FileList[state].ChildNodeNum;
		while (filenodenum != -1)
		{
			if (strcmp(FileList[filenodenum].FileName, Second) == 0 && FileList[filenodenum].FileType == 2)
				break;
			filenodenum = FileList[filenodenum].BrotherNodeNum;
		}
		if (filenodenum == -1)
		{
			cout << "��Ŀ¼��û����Ϊ��" << Second << "�����ı��ļ�\n";
			return;
		}
	}
	blocknum = FileList[filenodenum].BlockNum;
	int len = strlen(BlockList[blocknum].content);
	CommandResult result;
	result.state = state;
	sprintf(result.output, "�ļ�����:%s\n�ַ�������:%d\n�ļ�����: �ı��ļ�", FileList[filenodenum].FileName, len);
	return result;
}
//���ļ�
CommandResult Cd(int state, const char *Second, const char* Third)
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	if (strcmp(Second, "..") == 0)  //���������ǽ���ĳ���ļ������� cd .. �򷵻ص���һ��
	{
		if (RoadNode > 0)
			RoadNode--;
	}
	int distination = DistinguishRoad(state, Second);
	if (distination == -1)
		cout << "ϵͳ�Ҳ���ָ��·��" << endl;
	else if (distination == 0)     //��Ŀ¼�ļ������뵽Ŀ¼�ļ���
	{
		for (RoadNode = 0; RoadNode <= InputRoadNode; RoadNode++)
			Road[RoadNode] = InputRoad[RoadNode];
		RoadNode--;
	}
	else if (DistinguishRoad(Second) == 1)     //����Ŀ¼�ļ������ɽ���
	{
		cout << "�������·���ն˲����ļ���" << endl;
		return;
	}
	else
	{
		
		else
		{
			int i = FileList[Road[RoadNode]].ChildNodeNum;   //iΪ��ǰĿ¼����Ŀ¼
			while (i != -1)
			{
				if (FileList[i].FileType == 1 && strcmp(FileList[i].FileName, Second) == 0)
				{
					Road[++RoadNode] = i;    //��Ŀ¼�ļ�������������ȷ���ļ���¼��1
					return;
				}
				i = FileList[i].BrotherNodeNum;  //�����ļ���¼Ϊͬ���ļ�
			}
			cout << "ϵͳ�Ҳ���ָ��·��" << Second << endl;
		}
	}
}
//�����ļ�
void Copy()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int from, to;
	if (DistinguishRoad(Second) == 1)
		from = InputRoad[InputRoadNode];   //��¼��ǰ�ļ�
	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //��¼���ļ����
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "�������Դ�ļ�·������ȷ" << endl;
			return;
		}
	}
	DistinguishRoad(Third);
	to = InputRoad[InputRoadNode];
	if (FileList[from].ParentNodeNum == to)   //�ļ��Ѿ�������Ŀ��·����
	{
		cout << "���ܽ��ļ����Ƶ�������Ŀ¼\n";
		return;
	}
	int newnode = ApplyFileNode();    //�½�һ�����ļ����ֵ
	if (newnode == -1)
	{
		cout << "�������������ܸ���\n";
		return;
	}
	int i;
	for (i = 0; i<12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//��Դ�ļ����Ƶ��½����ļ���
	FileList[newnode].FileType = FileList[from].FileType;					//���ļ�������ԭ����ͬ
	FileList[newnode].ParentNodeNum = to;									//���ļ��ĸ�ĸ�ļ����ΪĿ���ļ�
	FileList[newnode].ChildNodeNum = -1;									//���ļ��ĺ����ļ���㲻����
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//���ļ���ͬ���ļ����ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[to].ChildNodeNum = newnode;									//���ļ�ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[newnode].BlockNum = ApplyBlock();								//Ϊ���ļ�����һ������
	WriteFileNode(to);														//Ŀ���ļ�����д�����
	WriteFileNode(newnode);													 //���½����ļ�д�����
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "�����������ļ������޷�����\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//����û����
	{
		i = 0;
		while (i<55 && BlockList[blocknum1].content[i] != '\0')    //�����ļ�����
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i<55)
		{
			cout << "�ļ��������\n";
			WriteBlock(blocknum2);   //д�����
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//���·������Ϊռ��
		BlockList[blocknum2].next = ApplyBlock();				//������һ������
		if (BlockList[blocknum2].next == -1)					//������벻��
		{
			cout << "���̿ռ䲻�㣬���������Ը���\n";
			return;
		}
		WriteBlock(blocknum2);									//���뵽�ˣ����·���д�����
		blocknum1 = BlockList[blocknum1].next;					//��ǰ����λ�ú���
		blocknum2 = BlockList[blocknum2].next;
	}
}
//�����ļ���Ŀ¼
void XCopy() 
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 0 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int from, to;
	if (DistinguishRoad(Second) == 0)
	{
		from = InputRoad[InputRoadNode];
		DistinguishRoad(Third);
		to = InputRoad[InputRoadNode];
		DirectoryTo(from, to);
		WriteFileNodes(FileList[from].ChildNodeNum);
	}
	if (DistinguishRoad(Second) == 1) 
	{
		from = InputRoad[InputRoadNode];   //��¼��ǰ�ļ�
		DistinguishRoad(Third);
		to = InputRoad[InputRoadNode];
		DirectoryTo(from, to);
	}
		

	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //��¼���ļ����

		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "�������Դ�ļ�·������ȷ" << endl;
			return;
		}
		DistinguishRoad(Third);
		to = InputRoad[InputRoadNode];
		DirectoryTo(from, to);
	}
	
}
//XCopy��Ŀ���ļ�����
void DirectoryTo(int from, int to)
{
	if (FileList[from].ParentNodeNum == to)   //�ļ��Ѿ�������Ŀ��·����
	{
		cout << "���ܽ��ļ����Ƶ�������Ŀ¼\n";
		return;
	}
	int newnode = ApplyFileNode();    //�½�һ�����ļ����ֵ
	if (newnode == -1)
	{
		cout << "�������������ܸ���\n";
		return;
	}
	int i;
	for (i = 0; i < 12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//��Դ�ļ����Ƶ��½����ļ���
	FileList[newnode].FileType = FileList[from].FileType;					//���ļ�������ԭ����ͬ
	FileList[newnode].ParentNodeNum = to;									//���ļ��ĸ�ĸ�ļ����ΪĿ���ļ�
	FileList[newnode].ChildNodeNum = -1;									//���ļ��ĺ����ļ���㲻����
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//���ļ���ͬ���ļ����ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[to].ChildNodeNum = newnode;									//���ļ�ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[newnode].BlockNum = ApplyBlock();								//Ϊ���ļ�����һ������
	WriteFileNode(to);														//Ŀ���ļ�����д�����
	WriteFileNode(newnode);													 //���½����ļ�д�����
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "�����������ļ������޷�����\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//����û����
	{
		i = 0;
		while (i < 55 && BlockList[blocknum1].content[i] != '\0')    //�����ļ�����
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i < 55)
		{
			cout << "�ļ��������\n";
			WriteBlock(blocknum2);   //д�����
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//���·������Ϊռ��
		BlockList[blocknum2].next = ApplyBlock();				//������һ������
		if (BlockList[blocknum2].next == -1)					//������벻��
		{
			cout << "���̿ռ䲻�㣬���������Ը���\n";
			return;
		}
		WriteBlock(blocknum2);									//���뵽�ˣ����·���д�����
		blocknum1 = BlockList[blocknum1].next;					//��ǰ����λ�ú���
		blocknum2 = BlockList[blocknum2].next;
	}
}
//ɾ���ļ�
void Del()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int i = DistinguishRoad(Second);
	int filenode;
	if (i == -1)
	{
		cout << "��������ļ�·������ȷ" << endl;
		return;
	}
	/*if (i == 0)   //Ŀ¼�ļ�
	{
		filenode = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[filenode].ChildNodeNum);    //�����ӽ���ļ�ɾ��
	}*/
	if (i == 1)   //�ı��ļ�
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //�ͷŷ���
	}
	if (i == 2)   //�����ս��ļ���������·��
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //�������ļ�
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //ɾ�����ӽ���ļ�
				else
					FreeBlocks(FileList[filenode].BlockNum);   //������ı��ļ����ͷŷ���
				break;
			}
			n = FileList[n].BrotherNodeNum;   //ͬ���ļ�
		}
		if (n == -1)
		{
			cout << "��������ļ�·������ȷ" << endl;
			return;
		}
	}
	for (int j = 1; j <= RoadNode; j++)
		if (Road[j] == filenode)
		{
			RoadNode = j - 1;
			break;
		}
	i = FileList[FileList[filenode].ParentNodeNum].ChildNodeNum;
	if (i == filenode)
	{
		FileList[FileList[i].ParentNodeNum].ChildNodeNum = FileList[i].BrotherNodeNum;
		WriteFileNode(FileList[i].ParentNodeNum);  //����ĸ�ļ�����д�����
		FreeFileNode(i);                            //���ļ�����ɾ��
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}
	if (i != filenode)
	{
		while (filenode != FileList[i].BrotherNodeNum)
		{
			i = FileList[i].BrotherNodeNum;
			FileList[i].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		}
		FileList[i].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		WriteFileNode(i);
		FreeFileNode(filenode);
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}
}
//��ʾ�ļ���Ϣ
void Dir()
{
	int i;
	if (strcmp(Second, "") == 0)
	{
		cout << endl;
		cout << FileList[Road[RoadNode]].FileName << "��Ŀ¼\n" << endl;
		i = FileList[Road[RoadNode]].ChildNodeNum;
		while (i != -1)
		{
			if (FileList[i].FileType == 1)              //��ʾ����Ŀ¼�ļ�
				cout << "\t<DIR>\t" << FileList[i].FileName << endl;
			i = FileList[i].BrotherNodeNum;
		}
		i = FileList[Road[RoadNode]].ChildNodeNum;
		while (i != -1)
		{
			if (FileList[i].FileType == 2)             //��ʾ�����ı��ļ�
				cout << "\t  \t" << FileList[i].FileName << endl;
			i = FileList[i].BrotherNodeNum;
		}
	}
	else
	{
		if (strcmp(Third, "") != 0)
		{
			cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
			return;
		}
		else
		{
			if (DistinguishRoad(Second) != 0)     //����Ŀ¼�ļ�
			{
				cout << "�������Ŀ¼·������ȷ���������ʹ��help����鿴" << endl;
				return;
			}
			cout << FileList[InputRoad[InputRoadNode]].FileName << "��Ŀ¼\n" << endl;
			i = FileList[InputRoad[InputRoadNode]].ChildNodeNum;
			while (i != -1)
			{
				if (FileList[i].FileType == 1)
					cout << "\t<DIR>\t" << FileList[i].FileName << endl;
				i = FileList[i].BrotherNodeNum;
			}
			i = FileList[InputRoad[InputRoadNode]].ChildNodeNum;
			while (i != -1)
			{
				if (FileList[i].FileType == 2)
					cout << "\t  \t" << FileList[i].FileName << endl;
				i = FileList[i].BrotherNodeNum;
			}
		}
	}
}
//�˳�ϵͳ
void Exit()
{
	exit(1);
}
//��ʽ������
void Format()
{
	if (strcmp(Second, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	cout << "���̸�ʽ�����������ݶ��ᶪʧ��ȷ��Ҫ��ʽ����(Y/N)\n";
	char a[5];
	cin.getline(a, 5);
	if (a[0] != 'y'&&a[0] != 'Y')   //����ʽ��
		return;
	Initial();   //�����̳�ʼ��
	ReadAll();   //��д�ļ�
}
//�����ַ���
void Find()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int thirdfile = DistinguishRoad(Third);
	if (thirdfile == -1)
	{
		cout << "�������·�����ļ�������ȷ" << endl;
		return;
	}
	if (thirdfile == 0)
	{
		cout << "�������·���ն˲����ı��ļ�" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (thirdfile == 1)   //���ı��ļ�
		filenodenum = InputRoad[InputRoadNode];
	if (thirdfile == 2)   //��·��
	{
		filenodenum = FileList[Road[RoadNode]].ChildNodeNum;
		while (filenodenum != -1)
		{
			if (strcmp(FileList[filenodenum].FileName, Third) == 0 && FileList[filenodenum].FileType == 2)
				break;
			filenodenum = FileList[filenodenum].BrotherNodeNum;
		}
		if (filenodenum == -1)
		{
			cout << "��Ŀ¼��û����Ϊ��" << Third << "�����ı��ļ�\n";
			return;
		}
	}
	cout << "----------" << FileList[filenodenum].FileName << endl;
	blocknum = FileList[filenodenum].BlockNum;
	
	if (strstr(BlockList[blocknum].content,Second ) == NULL)
		cout << "û���ҵ��ַ���\n";
	//cout << BlockList[blocknum].content;
	//cout << Second;
	else
		cout << BlockList[blocknum].content;
		
}
//��ʾ����
void Help()
{
	if (strcmp(Second, "") == 0)
	{
		cout << "attrib    ��ʾһ���ı��ļ�������\n";
		cout << "cd        ����ָ��Ŀ¼�ļ�\n";
		cout << "copy      ��һ���ı��ļ����Ƶ�ָ����Ŀ¼��\n";
		cout << "xcopy	  ��һ���ı��ļ���Ŀ¼�ļ��µ������ļ����Ƶ�ָ����Ŀ¼��\n";
		cout << "del       ɾ��һ���ı��ļ�\n";
		cout << "dir       ��ʾĿ¼�µ������ļ���Ϣ\n";
		cout << "exit      �˳�ϵͳ\n";
		cout << "format    ��ʽ������\n";
		cout << "find      �����ַ���\n";
		cout << "mk        �ڵ�ǰĿ¼���½�һ���ı��ļ�\n";
		cout << "mkdir     �ڵ�Ŀ¼���½�һ��Ŀ¼�ļ�\n";
		cout << "more      ��ʾ���޸��ı��ļ�������\n";
		//cout << "move	   �ƶ��ı��ļ�\n";
		cout << "rmdir	  ɾ��Ŀ¼�ļ�����Ŀ¼�µ������ļ�\n";
		cout << "time	  ��ʾϵͳ��ʱ��\n";
		cout << "import    ����������ļ�����\n";
		cout << "export    ����������ļ�����\n";
		cout << "�������������ʹ�����help ��������\n";
	}
	else
	{
		if (strcmp(Third, "") != 0)
		{
			cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
			return;
		}
		else if (strcmp(Second, "attrib") == 0)
			cout << "\nattrib ���� ��ʾһ���ı��ļ�������\n������ֻ��һ���������ò��������ǵ�ǰĿ¼�µ��ļ�����Ҳ�������ļ��ľ���·��\n";
		else if (strcmp(Second, "cd") == 0)
			cout << "\ncd ���� ����ָ��Ŀ¼�ļ�\n������ֻ��һ���������ò��������ǡ�..������ʾ������һ��Ŀ¼��Ҳ�����ǵ�ǰĿ¼�µ�һ��Ŀ¼�ļ�������ʾ�����Ŀ¼��Ҳ������ĳ��Ŀ¼�ľ���·��\n";
		else if (strcmp(Second, "copy") == 0)
			cout << "\ncopy ���� ��һ���ı��ļ����Ƶ�ָ����Ŀ¼��\n��������������������һ��������ʾҪ���Ƶ�Դ�ļ��������ǵ�ǰĿ¼�µ��ļ�����Ҳ�������ļ��ľ���·�����ڶ���������ʾ���Ƶ���Ŀ¼���ò���������Ŀ¼�ľ���·��\n";
		else if (strcmp(Second, "xcopy") == 0)
			cout << "\nxcopy ���� ��һ���ı��ļ���Ŀ¼�ڵ������ļ����Ƶ�ָ����Ŀ¼��\n��������������������һ��������ʾҪ���Ƶ��ļ���Ŀ¼�µ������ļ��������ǵ�ǰĿ¼�µ��ļ�����Ŀ¼����Ҳ�������ļ���Ŀ¼�ľ���·�����ڶ���������ʾ���Ƶ���Ŀ¼���ò���������Ŀ¼�ľ���·��\n";
		else if (strcmp(Second, "del") == 0)
			cout << "\ndel ���� ɾ��һ���ı��ļ�\n������ֻ��һ���������ò���ΪҪɾ�����ļ����ļ����������ǵ�ǰĿ¼�µ��ļ�����Ҳ�������ļ��ľ���·��\n";
		else if (strcmp(Second, "dir") == 0)
			cout << "\ndir ���� ��ʾĿ¼�µ������ļ���Ϣ\n���������û�в�����ʾ��ʾ��ǰĿ¼�µ������ļ���Ϣ��Ҳ������һ��������ΪĳһĿ¼�ļ��ľ���·������ʾ��Ŀ¼�µ������ļ���Ϣ\n";
		else if (strcmp(Second, "exit") == 0)
			cout << "\nexit ���� �˳�ϵͳ\n������û�в�������ʾ�˳�ϵͳ\n";
		else if (strcmp(Second, "format") == 0)
			cout << "\nformat ���� ��ʽ������\n������û�в�����ʹ�ú�ʹ���̳�ʼ��\n";
		else if (strcmp(Second, "find") == 0)
			cout << "\nfind ���� �����ַ���\n��������������������һ��������ʾҪ���ҵ��ַ������ڶ��������ǲ��ҵľ���·�����ı��ļ���";
		else if (strcmp(Second, "mk") == 0)
			cout << "\nmk ���� �ڵ�ǰĿ¼���½�һ���ı��ļ�\n������ֻ��һ���������ò���Ϊ�½��ı��ļ����ļ������Ҳ��ܺ͵�ǰĿ¼�������ļ����ļ�����ͬ\n";
		else if (strcmp(Second, "mkdir") == 0)
			cout << "\nmkdir ���� �ڵ�Ŀ¼���½�һ��Ŀ¼�ļ�\n������ֻ��һ���������ò���Ϊ�½�Ŀ¼�ļ����ļ������Ҳ��ܺ͵�ǰĿ¼�������ļ����ļ�����ͬ\n";
		else if (strcmp(Second, "more") == 0)
			cout << "\nmore ���� ��ʾ���޸��ı��ļ�������\n������ֻ��һ���������ò���Ϊָ���ı��ļ����ļ��������·������ʾ���ı��ļ���ǰ�����ݣ�Ȼ�����ʾѡ���Ƿ��޸����ݣ�����޸��������µ����ݲ����浽������\n";
		else if (strcmp(Second, "move") == 0)
			cout << "\nmove ���� �ƶ��ı��ļ�\n��������������������һ������Ϊ���ƶ���Դ�ļ�·�����ڶ�������ΪҪ�ƶ�����Ŀ��Ŀ¼\n";
		else if (strcmp(Second, "rmdir") == 0)
			cout << "\nrmdir ���� ɾ��Ŀ¼�ļ�����Ŀ¼�µ������ļ�\n������ֻ��һ���������ò���Ҫɾ�����ļ����ļ����������ǵ�ǰĿ¼�µ��ļ�����Ҳ�������ļ��ľ���·��\n";
		else if (strcmp(Second, "time") == 0)
			cout << "\ntime ���� ��ʾϵͳʱ��\n������û�в�������ʾϵͳ��ǰʱ��\n";
		else if (strcmp(Second, "help") == 0)
			cout << "\n�������������ʹ�����help ��������\n���������û�в�����ʾ��ʾShellϵͳ֧�ֵ�����������ͣ�Ҳ������һ��������Ϊ�����������ƣ���ʾ������ʹ�����\n";
		else if (strcmp(Second, "import") == 0)
			cout << "\nimport ���� ��������·���µ��ļ����뵽��ǰ·����\n������������������һ������Ϊ�����·�����ڶ�������ΪҪ�����ڴ����ڵ�·��\n";
		else if (strcmp(Second, "export") == 0)
			cout << "\nexport ���� ��������·���µ��ļ�������������·����\n��������������������һ������ΪҪ�����Ĵ��������ݵ�·�����ڶ�������ΪҪ�����ڴ������·����\n";
		else
			cout << "\n����������" << Second << "��������\n";
	}
}
//�����ļ�
void Mk()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int nodenum = ApplyFileNode();   //�������ļ����
	int contentnum = ApplyBlock();    //�����·���
	if (nodenum == -1 || contentnum == -1)
	{
		cout << "���������������½�Ŀ¼\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //���ļ�Ϊ��ǰ�ļ������ļ�
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Second) == 0)    //�ж��Ƿ����
		{
			cout << "�ļ�" << Second << "�Ѿ�����\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Second[i] != '\0')
	{
		if (Second[i] == 92)
		{
			cout << "�ļ����в����С�" << char(92) << "���ַ�" << endl;  //�ļ����в�����'\'
			return;
		}
		FileList[nodenum].FileName[i] = Second[i];  //��������ļ�����ֵ���½����ļ����
		i++;
	}
	FileList[nodenum].FileType = 2;      //���ļ�����Ϊ�ı��ļ�
	FileList[nodenum].ParentNodeNum = Road[RoadNode];   //��ǰ�ļ�Ϊ���ļ��ĸ�ĸ���
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;  //��ǰ�ļ��ĺ��ӽ��Ϊ���ļ���ͬ�����
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;  //��ǰ�ļ��ĺ��ӽ��Ϊ���ļ�
	FileList[nodenum].ChildNodeNum = -1;    //���ļ�û�к��ӽ��
	FileList[nodenum].BlockNum = contentnum;   //���ļ�д���·���
	BlockList[contentnum].IfUsing = true;   //�·������Ϊռ��
	BlockList[contentnum].next = -1;       //�·�������һ������û��
	BlockList[contentnum].content[0] = '\0';   //���ļ�����Ϊ��
	WriteFileNode(nodenum);        //�����ļ�д�����
	WriteFileNode(FileList[nodenum].ParentNodeNum);   //�����ļ��ĸ�ĸ���д�����
	WriteBlock(contentnum);   //���·���д�����
}
//����Ŀ¼
void Mkdir()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int nodenum = ApplyFileNode();  //�����µ��ļ����
	if (nodenum == -1)
	{
		cout << "���������������½�Ŀ¼\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //�µ��ļ����Ϊ��ǰ���ĺ��ӽ��
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Second) == 0)
		{
			cout << "Ŀ¼" << Second << "�Ѿ�����\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Second[i] != '\0')
	{
		if (Second[i] == 92)
		{
			cout << "�ļ����в����С�" << char(92) << "���ַ�" << endl;
			return;
		}
		FileList[nodenum].FileName[i] = Second[i];
		i++;
	}
	FileList[nodenum].FileName[i] = '\0';   //���ļ���
	FileList[nodenum].FileType = 1;     //���ļ�����
	FileList[nodenum].ParentNodeNum = Road[RoadNode];  //��ĸ���
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;   //��ĸ���ĺ��ӽ��Ϊ���ļ���ͬ�����
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;
	FileList[nodenum].ChildNodeNum = -1;
	WriteFileNode(nodenum);    //���ļ�д�����
	WriteFileNode(FileList[nodenum].ParentNodeNum);  //��ĸ���д�����
}
//�޸��ļ�����
void More()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int nowvacation = DistinguishRoad(Second);
	if (nowvacation == -1)
	{
		cout << "�������·�����ļ�������ȷ" << endl;
		return;
	}
	if (nowvacation == 0)
	{
		cout << "�������·���ն˲����ı��ļ�" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (nowvacation == 1)   //���ı��ļ�
		filenodenum = InputRoad[InputRoadNode];
	if (nowvacation == 2)   //��·��
	{
		filenodenum = FileList[Road[RoadNode]].ChildNodeNum;
		while (filenodenum != -1)
		{
			if (strcmp(FileList[filenodenum].FileName, Second) == 0 && FileList[filenodenum].FileType == 2)
				break;
			filenodenum = FileList[filenodenum].BrotherNodeNum;
		}
		if (filenodenum == -1)
		{
			cout << "��Ŀ¼��û����Ϊ��" << Second << "�����ı��ļ�\n";
			return;
		}
	}
	blocknum = FileList[filenodenum].BlockNum;
	int i, j;
	char a[5];
	char newcontent[500];
	while (blocknum != -1)
	{
		i = 0;
		while (i < 55 && BlockList[blocknum].content[i] != '\0')
		{
			cout << BlockList[blocknum].content[i];   //����ļ�����
			i++;
		}
		blocknum = BlockList[blocknum].next;
	}
	cout << "\n���ı��ļ��������Ѿ���ʾ��ϣ��Ƿ�����޸ģ���Y/N��";
	cin.getline(a, 5);
	if (a[0] != 'Y' && a[0] != 'y' || a[1] != '\0')
		return;
	cout << "�������ı��ļ�������\n";
	cin.getline(newcontent, 500);
	i = 0;
	blocknum = FileList[filenodenum].BlockNum;
	while (newcontent[i] != '\0')
	{
		j = 0;
		while (j < 55 && newcontent[i] != '\0')
		{
			BlockList[blocknum].content[j] = newcontent[i];
			j++;
			i++;
		}
		if (j < 55)
		{
			BlockList[blocknum].content[j] = '\0';
			FreeBlocks(BlockList[blocknum].next);
			BlockList[blocknum].next = -1;
			WriteBlock(blocknum);
			cout << "�޸ĺ��������д�����\n";
			return;
		}
		WriteBlock(blocknum);
		j = BlockList[blocknum].next;
		if (j == -1)
		{
			j = ApplyBlock();
			if (j == -1)
			{
				cout << "����������ֻ�в�������д�뵽������\n";
				return;
			}
			BlockList[j].IfUsing = true;
			BlockList[j].next = -1;
			BlockList[j].content[0] = '\0';
			BlockList[blocknum].next = j;
		}
		blocknum = j;
	}
}
//�ƶ��ı��ļ�
void Move() 
{
	//copy
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int from, to;
	if (secondfile == 0)   //Ŀ¼�ļ�
	{
		from = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[from].ChildNodeNum);    //�����ӽ���ļ�ɾ��
	}
	if (secondfile == 1) 
	{
		from = InputRoad[InputRoadNode];   //��¼��ǰ�ļ�
		FreeBlocks(FileList[from].BlockNum);   //�ͷŷ���
	}
	if (secondfile == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //��¼���ļ����
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "�������Դ�ļ�·������ȷ" << endl;
			return;
		}
	}
	DistinguishRoad(Third);
	to = InputRoad[InputRoadNode];
	if (FileList[from].ParentNodeNum == to)   //�ļ��Ѿ�������Ŀ��·����
	{
		cout << "���ܽ��ļ����Ƶ�������Ŀ¼\n";
		return;
	}
	int newnode = ApplyFileNode();    //�½�һ�����ļ����ֵ
	if (newnode == -1)
	{
		cout << "�������������ܸ���\n";
		return;
	}
	int i;
	for (i = 0; i < 12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//��Դ�ļ����Ƶ��½����ļ���
	FileList[newnode].FileType = FileList[from].FileType;					//���ļ�������ԭ����ͬ
	FileList[newnode].ParentNodeNum = to;									//���ļ��ĸ�ĸ�ļ����ΪĿ���ļ�
	FileList[newnode].ChildNodeNum = -1;									//���ļ��ĺ����ļ���㲻����
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//���ļ���ͬ���ļ����ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[to].ChildNodeNum = newnode;									//���ļ�ΪĿ���ļ��ĺ��ӽ���ļ�
	FileList[newnode].BlockNum = ApplyBlock();								//Ϊ���ļ�����һ������
	WriteFileNode(to);														//Ŀ���ļ�����д�����
	WriteFileNode(newnode);													 //���½����ļ�д�����
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "�����������ļ������޷�����\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//����û����
	{
		i = 0;
		while (i < 55 && BlockList[blocknum1].content[i] != '\0')    //�����ļ�����
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i < 55)
		{
			cout << "�ļ��������\n";
			WriteBlock(blocknum2);   //д�����
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//���·������Ϊռ��
		BlockList[blocknum2].next = ApplyBlock();				//������һ������
		if (BlockList[blocknum2].next == -1)					//������벻��
		{
			cout << "���̿ռ䲻�㣬���������Ը���\n";
			return;
		}
		WriteBlock(blocknum2);									//���뵽�ˣ����·���д�����
		blocknum1 = BlockList[blocknum1].next;					//��ǰ����λ�ú���
		blocknum2 = BlockList[blocknum2].next;
	}
	//del
	/*int filenode;
	if (secondfile == 1)   //�ı��ļ�
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //�ͷŷ���
	}
	if (secondfile == 2)   //�����ս��ļ���������·��
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //�������ļ�
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //ɾ�����ӽ���ļ�
				else
					FreeBlocks(FileList[filenode].BlockNum);   //������ı��ļ����ͷŷ���
				break;
			}
			n = FileList[n].BrotherNodeNum;   //ͬ���ļ�
		}
		if (n == -1)
		{
			cout << "��������ļ�·������ȷ" << endl;
			return;
		}
	}
	for (int j = 1; j <= RoadNode; j++)
		if (Road[j] == filenode)
		{
			RoadNode = j - 1;
			break;
		}
	secondfile  = FileList[FileList[filenode].ParentNodeNum].ChildNodeNum;
	if (secondfile == filenode)
	{
		FileList[FileList[secondfile].ParentNodeNum].ChildNodeNum = FileList[secondfile].BrotherNodeNum;
		WriteFileNode(FileList[secondfile].ParentNodeNum);  //����ĸ�ļ�����д�����
		FreeFileNode(secondfile);                            //���ļ�����ɾ��
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}
	if (secondfile != filenode)
	{
		while (filenode != FileList[secondfile].BrotherNodeNum)
		{
			secondfile = FileList[secondfile].BrotherNodeNum;
			FileList[secondfile].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		}
		FileList[secondfile].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		WriteFileNode(secondfile);
		FreeFileNode(filenode);
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}*/
}
//ɾ��һ���ļ�Ŀ¼
void Rmdir()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int i = DistinguishRoad(Second);
	int filenode;
	if (i == -1)
	{
		cout << "��������ļ�·������ȷ" << endl;
		return;
	}
	if (i == 0)   //Ŀ¼�ļ�
	{
		filenode = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[filenode].ChildNodeNum);    //�����ӽ���ļ�ɾ��
	}
	if (i == 1)   //�ı��ļ�
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //�ͷŷ���
	}
	if (i == 2)   //�����ս��ļ���������·��
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //�������ļ�
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //ɾ�����ӽ���ļ�
				else
					FreeBlocks(FileList[filenode].BlockNum);   //������ı��ļ����ͷŷ���
				break;
			}
			n = FileList[n].BrotherNodeNum;   //ͬ���ļ�
		}
		if (n == -1)
		{
			cout << "��������ļ�·������ȷ" << endl;
			return;
		}
	}
	for (int j = 1; j <= RoadNode; j++)
		if (Road[j] == filenode)
		{
			RoadNode = j - 1;
			break;
		}
	i = FileList[FileList[filenode].ParentNodeNum].ChildNodeNum;
	if (i == filenode)
	{
		FileList[FileList[i].ParentNodeNum].ChildNodeNum = FileList[i].BrotherNodeNum;
		WriteFileNode(FileList[i].ParentNodeNum);  //����ĸ�ļ�����д�����
		FreeFileNode(i);                            //���ļ�����ɾ��
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}
	if (i != filenode)
	{
		while (filenode != FileList[i].BrotherNodeNum)
		{
			i = FileList[i].BrotherNodeNum;
			FileList[i].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		}
		FileList[i].BrotherNodeNum = FileList[filenode].BrotherNodeNum;
		WriteFileNode(i);
		FreeFileNode(filenode);
		cout << "�ļ���" << FileList[filenode].FileName << "����ɾ��";
	}
}
//��ʾϵͳʱ��
void Time()
{
	struct tm t;			//tm�ṹָ�� 
	time_t now;				//����time_t���ͱ���
	time(&now);				//��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);	//��ȡ�������ں�ʱ��
	
	printf("%d�� %d�� %d��\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
	printf("%dʱ %d�� %d��\n", t.tm_hour, t.tm_min, t.tm_sec);
}
//��ʾϵͳ�汾
void Ver()
{
	cout << endl;
	cout << "Dingyuxing Platform [�汾 1.0.0.1]" << endl;
}
//����
void Export()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2)))
	{
		cout << "������������ʽ����ȷ���������ʹ��help����鿴" << endl;
		return;
	}
	int from, to;
	if (DistinguishRoad(Second) == 1)
		from = InputRoad[InputRoadNode];   //��¼��ǰ�ļ�
	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //��¼���ļ����
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "�������Դ�ļ�·������ȷ" << endl;
			return;
		}
	}
	ofstream out;
	out.open(Third, std::ios::out | std::ios::app);
	if (!out.is_open())
		cout << "���ļ�����." << endl;
	
	out << BlockList[FileList[from].BlockNum].content << endl;
	out.close();
	
}
//����
void Import()
{
	int nodenum = ApplyFileNode();   //�������ļ����
	int contentnum = ApplyBlock();    //�����·���
	if (nodenum == -1 || contentnum == -1)
	{
		cout << "���������������½�Ŀ¼\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //���ļ�Ϊ��ǰ�ļ������ļ�
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Third) == 0)    //�ж��Ƿ����
		{
			cout << "�ļ�" << Third << "�Ѿ�����\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Third[i] != '\0')
	{
		if (Third[i] == 92)
		{
			cout << "�ļ����в����С�" << char(92) << "���ַ�" << endl;  //�ļ����в�����'\'
			return;
		}
		FileList[nodenum].FileName[i] = Third[i];  //��������ļ�����ֵ���½����ļ����
		i++;
	}
	FileList[nodenum].FileType = 2;      //���ļ�����Ϊ�ı��ļ�
	FileList[nodenum].ParentNodeNum = Road[RoadNode];   //��ǰ�ļ�Ϊ���ļ��ĸ�ĸ���
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;  //��ǰ�ļ��ĺ��ӽ��Ϊ���ļ���ͬ�����
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;  //��ǰ�ļ��ĺ��ӽ��Ϊ���ļ�
	FileList[nodenum].ChildNodeNum = -1;    //���ļ�û�к��ӽ��
	FileList[nodenum].BlockNum = contentnum;   //���ļ�д���·���
	BlockList[contentnum].IfUsing = true;   //�·������Ϊռ��
	BlockList[contentnum].next = -1;       //�·�������һ������û��	

	ifstream infile;
	infile.open(Second, ios::in);   //���ļ����������ļ��������� 
	if (!infile)
	{
		cerr << "ERROR!" << endl;
	}
	int sn = 0;
	char c;
	while (!infile.eof())
	{
		infile >> c;
		BlockList[contentnum].content[sn++] = c;
	}
	infile.close();             //�ر��ļ�������

	WriteFileNode(nodenum);        //�����ļ�д�����
	WriteFileNode(FileList[nodenum].ParentNodeNum);   //�����ļ��ĸ�ĸ���д�����
	WriteBlock(contentnum);   //���·���д�����
}