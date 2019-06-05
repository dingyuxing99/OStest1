//�����������
void CreateDisk(const char *A)
{
	fstream myfile;
	myfile.open(A, ios::out | ios::binary);  //�Զ����Ʒ�ʽ���ļ�
	if (!myfile)
	{
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	myfile << setw(Driver_Size) << " ";
	myfile.close();
}
//��ʼ���������
void Initial()
{
	int i, j;
	for (i = 0; i<FileNode_Num; i++)     //���������ļ���Ϣ
	{
		FileList[i].FileType = 0;
		FileList[i].BlockNum = -1;
		FileList[i].ParentNodeNum = -1;
		FileList[i].BrotherNodeNum = -1;
		FileList[i].ChildNodeNum = -1;
		for (j = 0; j<12; j++)
			FileList[i].FileName[j] = '\0';
	}
	for (i = 0; i<Block_Num; i++)       //���̿���������
	{
		BlockList[i].IfUsing = false;
		BlockList[i].next = -1;
		for (j = 0; j<55; j++)
			BlockList[i].content[j] = '\0';
	}

	FileList[0].FileType = 1;     //��һ���ļ�ΪĿ¼��㣬������AΪ��һ�����
	FileList[0].FileName[0] = 'A';
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "Can't open file!" << endl;
		exit(1);
	}
	for (i = 0; i<FileNode_Num; i++)
		dist.write((char*)&FileList[i], FileNode_Size);   //���������ļ�����д������A��
	for (i = 0; i<Block_Num; i++)
		dist.write((char*)&BlockList[i], Block_Size);     //��ÿһ�����������д������A��
	dist.close();
}
//��д�ļ�
void ReadAll()
{
	int i;
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		CreateDisk("A.dat");
	}
	dist.seekg(0, ios::end);   //�������ļ���λ��ƫ�ƵĻ���ַΪ�������Ľ���
	long v_big = dist.tellg();   //������һ������ȡ��Ԫ�ص�λ��
	if (v_big != Driver_Size)      //�����һ������ȡ��λ��δ�ﵽ�������������ֵ
	{
		dist.close();
		Initial();    //��ɴ��̳�ʼ������
	}
	else
	{
		dist.seekg(0, ios::beg);      //�����Ŀ�ʼ��λ
		for (i = 0; i<FileNode_Num; i++)
			dist.read((char*)&FileList[i], FileNode_Size);   //�Ӵ����϶��ļ���Ϣ
		for (i = 0; i<Block_Num; i++)
			dist.read((char*)&BlockList[i], Block_Size);	    //�Ӵ����϶���������Ϣ
		dist.close();
	}
	RoadNode = 0;   //��ǰĿ¼λ��
	Road[0] = 0;     //�ļ���¼
}
//��ʾ��ǰ·��
void PutOutRoad()
{
	for (int i = 0; i <= RoadNode; i++)
	{
		if (i == 0)
		{
			cout << "A:";
			if (RoadNode == 0)
				cout << char(92);   //���"A:\"
			continue;
		}
		cout << char(92);
		int j = 0;
		while (FileList[Road[i]].FileName[j] != '\0')
		{
			cout << FileList[Road[i]].FileName[j];
			j++;
		}
	}
	cout << '>';
}
//����ֶ�
void Interpretation()
{
	int i = 0, j = 0;
	bool flag = true;
	j = 0;
	while (true)
	{
		if (Command[i] == ' ' && !flag || Command[i] == '\0')
			break;
		else if (Command[i] != ' ')
		{
			First[j] = Command[i];   //����
			j++;
			flag = false;
		}
		i++;
	}
	First[j] = '\0';
	flag = true;
	j = 0;
	while (true)
	{
		if (Command[i] == ' ' && !flag || Command[i] == '\0')
			break;
		else if (Command[i] != ' ')
		{
			Second[j] = Command[i];    //����ĵ�һ������
			j++;
			flag = false;
		}
		i++;
	}
	Second[j] = '\0';
	flag = true;
	j = 0;
	while (true)
	{
		if (Command[i] == ' ' && !flag || Command[i] == '\0')
			break;
		else if (Command[i] != ' ')
		{
			Third[j] = Command[i];   //����ĵڶ�������
			j++;
			flag = false;
		}
		i++;
	}
	Third[j] = '\0';
	j = 0;
	while (true)
	{
		if (Command[i] == '\0')
			break;
		else
		{
			Other[j] = Command[i];     //����ĵ���������
			j++;
		}
		i++;
	}
	Other[j] = '\0';
}

void Commands()
{
	if (strcmp(First, "") == 0)return;
	else if (strcmp(First, "attrib") == 0)Attrib();
	else if (strcmp(First, "cd") == 0)Cd();
	else if (strcmp(First, "copy") == 0)Copy();
	else if (strcmp(First, "xcopy") == 0)XCopy();
	else if (strcmp(First, "del") == 0)Del();
	else if (strcmp(First, "dir") == 0)Dir();
	else if (strcmp(First, "exit") == 0)Exit();
	else if (strcmp(First, "format") == 0)Format();
	else if (strcmp(First, "find") == 0)Find();
	else if (strcmp(First, "help") == 0)Help();
	else if (strcmp(First, "mk") == 0)Mk();
	else if (strcmp(First, "mkdir") == 0)Mkdir();
	else if (strcmp(First, "more") == 0)More();
	else if (strcmp(First, "move") == 0)Move();
	else if (strcmp(First, "rmdir") == 0)Rmdir();
	else if (strcmp(First, "time") == 0) Time();
	else if (strcmp(First, "ver") == 0)Ver();
	else if (strcmp(First, "import") == 0)Import();
	else if (strcmp(First, "export") == 0)Export();
	else
		cout << "��" << First << "�������ڲ����Ҳ���ǿ����еĳ�����������ļ�" << endl;
	cout << endl;
}
//�ж�·��
int DistinguishRoad(char* a)
{
	int i, j;
	char c[30];
	if ((a[0] == 'a' || a[0] == 'A') && a[1] == ':'&&a[2] == 92)   //"A:\"
	{
		InputRoad[0] = 0;    //�����¼
		InputRoadNode = 0;   //��ǰλ��
		i = 3;
		while (a[i] != '\0')
		{
			j = 0;
			while (a[i] != 92 && a[i] != '\0')
			{
				c[j] = a[i];
				i++;
				j++;
			}
			c[j] = '\0';
			j = FileList[InputRoad[InputRoadNode]].ChildNodeNum;  //jΪA�ĺ��ӽ��
			while (c[0] != '\0'&&j != -1)
			{
				if (strcmp(FileList[j].FileName, c) == 0)   //���A���ӽ����ļ����������·������ͬ
				{
					InputRoad[++InputRoadNode] = j;      //��ǰλ�ü�1���ļ���¼��Ϊ���ӽ��
					break;
				}
				j = FileList[j].BrotherNodeNum;   //����jΪA��ͬ���ļ�
			}
			if (j == -1)
			{
				InputRoadNode = 0;   //�ص�A��˵��·��������
				return -1;
			}
			if (c[0] == '\0')
				i++;
		}
		if (FileList[InputRoad[InputRoadNode]].FileType == 1)
			return 0;      //Ŀ¼���
		else
			return 1;      //����Ŀ¼���
	}
	else
	{
		i = 0;
		while (a[i] != '\0')
		{
			if (a[i] == 92)
				return -1;    //·������
			i++;
		}
		return 2;
	}
}
//�����ļ�
int ApplyFileNode()
{
	for (int i = 1; i<FileNode_Num; i++)
		if (FileList[i].FileType == 0)
			return i;
	return -1;
}
//��������
int ApplyBlock()
{
	for (int i = 0; i<Block_Num; i++)
		if (!BlockList[i].IfUsing)
			return i;
	return -1;
}
//�ļ�д�����
void WriteFileNode(int n)
{
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "����A������" << endl;
		exit(1);
	}
	dist.seekg(FileNode_Size*n);   //nΪ�ļ�����
	dist.write((char*)&FileList[n], FileNode_Size);
	dist.close();
}
//Ŀ¼д�����
void WriteFileNodes(int n)
{
	if (n == -1)    //·������
		return;	
	int to = FileList[InputRoad[InputRoadNode]].ChildNodeNum;
	DirectoryTo(n, to);
	WriteFileNodes(FileList[n].BrotherNodeNum);   //д��ͬ���ļ����
	WriteFileNodes(FileList[n].ChildNodeNum);   //д�뺢���ļ����
}
//����д�����
void WriteBlock(int n)
{
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "����A������" << endl;
		exit(1);
	}
	dist.seekg(FileList_Size + Block_Size * n);
	dist.write((char*)&BlockList[n], Block_Size);
	dist.close();
}
//ɾ���ļ�
void FreeFileNode(int n)
{
	FileList[n].FileType = 0;   //�ļ����Ա�Ϊ��
	WriteFileNode(n);    //���ļ�����д�����
}
//ɾ��Ŀ¼
void FreeFileNodes(int n)
{
	if (n == -1)    //·������
		return;
	FreeFileNodes(FileList[n].ChildNodeNum);   //ɾ�������ļ����
	FreeFileNodes(FileList[n].BrotherNodeNum);   //ɾ��ͬ���ļ����
	if (FileList[n].FileType == 2)                   //����ļ�Ϊ�ı��ļ�
		FreeBlocks(FileList[n].BlockNum);         //�ͷŷ���
	FreeFileNode(n);	                  //ɾ����ǰ�ļ�
}

//�ͷŷ���
void FreeBlock(int n)
{
	BlockList[n].IfUsing = false;   //��������Ϊ��
	WriteBlock(n);
}
//�ͷŷ���
void FreeBlocks(int n)
{
	if (n == -1)
		return;
	FreeBlocks(BlockList[n].next);  //�ͷ���һ������
	FreeBlock(n);                   //�ͷű�����
}