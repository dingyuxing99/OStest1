//创建虚拟磁盘
void CreateDisk(const char *A)
{
	fstream myfile;
	myfile.open(A, ios::out | ios::binary);  //以二进制方式打开文件
	if (!myfile)
	{
		cout << "Can't open this file!" << endl;
		exit(0);
	}
	myfile << setw(Driver_Size) << " ";
	myfile.close();
}
//初始化虚拟磁盘
void Initial()
{
	int i, j;
	for (i = 0; i<FileNode_Num; i++)     //磁盘中无文件信息
	{
		FileList[i].FileType = 0;
		FileList[i].BlockNum = -1;
		FileList[i].ParentNodeNum = -1;
		FileList[i].BrotherNodeNum = -1;
		FileList[i].ChildNodeNum = -1;
		for (j = 0; j<12; j++)
			FileList[i].FileName[j] = '\0';
	}
	for (i = 0; i<Block_Num; i++)       //磁盘块内无内容
	{
		BlockList[i].IfUsing = false;
		BlockList[i].next = -1;
		for (j = 0; j<55; j++)
			BlockList[i].content[j] = '\0';
	}

	FileList[0].FileType = 1;     //第一个文件为目录结点，即磁盘A为第一个结点
	FileList[0].FileName[0] = 'A';
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "Can't open file!" << endl;
		exit(1);
	}
	for (i = 0; i<FileNode_Num; i++)
		dist.write((char*)&FileList[i], FileNode_Size);   //将创建的文件内容写到磁盘A上
	for (i = 0; i<Block_Num; i++)
		dist.write((char*)&BlockList[i], Block_Size);     //将每一块分区的内容写到磁盘A上
	dist.close();
}
//读写文件
void ReadAll()
{
	int i;
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		CreateDisk("A.dat");
	}
	dist.seekg(0, ios::end);   //对输入文件定位，偏移的基地址为输入流的结束
	long v_big = dist.tellg();   //返回下一个被读取的元素的位置
	if (v_big != Driver_Size)      //如果下一个被读取的位置未达到磁盘容量的最大值
	{
		dist.close();
		Initial();    //完成磁盘初始化工作
	}
	else
	{
		dist.seekg(0, ios::beg);      //从流的开始定位
		for (i = 0; i<FileNode_Num; i++)
			dist.read((char*)&FileList[i], FileNode_Size);   //从磁盘上读文件信息
		for (i = 0; i<Block_Num; i++)
			dist.read((char*)&BlockList[i], Block_Size);	    //从磁盘上读分区块信息
		dist.close();
	}
	RoadNode = 0;   //当前目录位置
	Road[0] = 0;     //文件记录
}
//显示当前路径
void PutOutRoad()
{
	for (int i = 0; i <= RoadNode; i++)
	{
		if (i == 0)
		{
			cout << "A:";
			if (RoadNode == 0)
				cout << char(92);   //输出"A:\"
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
//命令分段
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
			First[j] = Command[i];   //命令
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
			Second[j] = Command[i];    //命令的第一个参数
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
			Third[j] = Command[i];   //命令的第二个参数
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
			Other[j] = Command[i];     //命令的第三个参数
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
		cout << "‘" << First << "’不是内部命令，也不是可运行的程序或批处理文件" << endl;
	cout << endl;
}
//判断路径
int DistinguishRoad(char* a)
{
	int i, j;
	char c[30];
	if ((a[0] == 'a' || a[0] == 'A') && a[1] == ':'&&a[2] == 92)   //"A:\"
	{
		InputRoad[0] = 0;    //输入记录
		InputRoadNode = 0;   //当前位置
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
			j = FileList[InputRoad[InputRoadNode]].ChildNodeNum;  //j为A的孩子结点
			while (c[0] != '\0'&&j != -1)
			{
				if (strcmp(FileList[j].FileName, c) == 0)   //如果A孩子结点的文件名与输入的路径名相同
				{
					InputRoad[++InputRoadNode] = j;      //当前位置加1，文件记录变为孩子结点
					break;
				}
				j = FileList[j].BrotherNodeNum;   //否则j为A的同级文件
			}
			if (j == -1)
			{
				InputRoadNode = 0;   //回到A，说明路径名不对
				return -1;
			}
			if (c[0] == '\0')
				i++;
		}
		if (FileList[InputRoad[InputRoadNode]].FileType == 1)
			return 0;      //目录结点
		else
			return 1;      //不是目录结点
	}
	else
	{
		i = 0;
		while (a[i] != '\0')
		{
			if (a[i] == 92)
				return -1;    //路径不对
			i++;
		}
		return 2;
	}
}
//创建文件
int ApplyFileNode()
{
	for (int i = 1; i<FileNode_Num; i++)
		if (FileList[i].FileType == 0)
			return i;
	return -1;
}
//创建分区
int ApplyBlock()
{
	for (int i = 0; i<Block_Num; i++)
		if (!BlockList[i].IfUsing)
			return i;
	return -1;
}
//文件写入磁盘
void WriteFileNode(int n)
{
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "磁盘A不存在" << endl;
		exit(1);
	}
	dist.seekg(FileNode_Size*n);   //n为文件级数
	dist.write((char*)&FileList[n], FileNode_Size);
	dist.close();
}
//目录写入磁盘
void WriteFileNodes(int n)
{
	if (n == -1)    //路径不对
		return;	
	int to = FileList[InputRoad[InputRoadNode]].ChildNodeNum;
	DirectoryTo(n, to);
	WriteFileNodes(FileList[n].BrotherNodeNum);   //写入同级文件结点
	WriteFileNodes(FileList[n].ChildNodeNum);   //写入孩子文件结点
}
//分区写入磁盘
void WriteBlock(int n)
{
	fstream dist;
	dist.open("A.dat", ios::in | ios::out | ios::binary);
	if (!dist)
	{
		cout << "磁盘A不存在" << endl;
		exit(1);
	}
	dist.seekg(FileList_Size + Block_Size * n);
	dist.write((char*)&BlockList[n], Block_Size);
	dist.close();
}
//删除文件
void FreeFileNode(int n)
{
	FileList[n].FileType = 0;   //文件属性变为空
	WriteFileNode(n);    //将文件重新写入磁盘
}
//删除目录
void FreeFileNodes(int n)
{
	if (n == -1)    //路径不对
		return;
	FreeFileNodes(FileList[n].ChildNodeNum);   //删除孩子文件结点
	FreeFileNodes(FileList[n].BrotherNodeNum);   //删除同级文件结点
	if (FileList[n].FileType == 2)                   //如果文件为文本文件
		FreeBlocks(FileList[n].BlockNum);         //释放分区
	FreeFileNode(n);	                  //删除当前文件
}

//释放分区
void FreeBlock(int n)
{
	BlockList[n].IfUsing = false;   //将分区设为空
	WriteBlock(n);
}
//释放分区
void FreeBlocks(int n)
{
	if (n == -1)
		return;
	FreeBlocks(BlockList[n].next);  //释放下一个分区
	FreeBlock(n);                   //释放本分区
}