#include "head.h"
#include<cstring>
//显示文本文件的属性
CommandResult Attrib(int state, const char *Second, const char *Third)
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int nowvacation = DistinguishRoad(state, Second);
	if (nowvacation == -1)
	{
		cout << "您输入的路径或文件名不正确" << endl;
		return;
	}
	if (nowvacation == 0)
	{
		cout << "您输入的路径终端不是文本文件" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (nowvacation == 1)   //是文本文件
		filenodenum = InputRoad[InputRoadNode];
	if (nowvacation == 2)   //是相对路径
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
			cout << "该目录下没有名为‘" << Second << "’的文本文件\n";
			return;
		}
	}
	blocknum = FileList[filenodenum].BlockNum;
	int len = strlen(BlockList[blocknum].content);
	CommandResult result;
	result.state = state;
	sprintf(result.output, "文件名称:%s\n字符串长度:%d\n文件类型: 文本文件", FileList[filenodenum].FileName, len);
	return result;
}
//打开文件
CommandResult Cd(int state, const char *Second, const char* Third)
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	if (strcmp(Second, "..") == 0)  //如果输入的是进入某个文件后输入 cd .. 则返回到上一层
	{
		if (RoadNode > 0)
			RoadNode--;
	}
	int distination = DistinguishRoad(state, Second);
	if (distination == -1)
		cout << "系统找不到指定路径" << endl;
	else if (distination == 0)     //是目录文件，进入到目录文件中
	{
		for (RoadNode = 0; RoadNode <= InputRoadNode; RoadNode++)
			Road[RoadNode] = InputRoad[RoadNode];
		RoadNode--;
	}
	else if (DistinguishRoad(Second) == 1)     //不是目录文件，不可进入
	{
		cout << "您输入的路径终端不是文件夹" << endl;
		return;
	}
	else
	{
		
		else
		{
			int i = FileList[Road[RoadNode]].ChildNodeNum;   //i为当前目录的子目录
			while (i != -1)
			{
				if (FileList[i].FileType == 1 && strcmp(FileList[i].FileName, Second) == 0)
				{
					Road[++RoadNode] = i;    //是目录文件且名字输入正确，文件记录加1
					return;
				}
				i = FileList[i].BrotherNodeNum;  //否则文件记录为同级文件
			}
			cout << "系统找不到指定路径" << Second << endl;
		}
	}
}
//复制文件
void Copy()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int from, to;
	if (DistinguishRoad(Second) == 1)
		from = InputRoad[InputRoadNode];   //记录当前文件
	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //记录子文件结点
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "您输入的源文件路径不正确" << endl;
			return;
		}
	}
	DistinguishRoad(Third);
	to = InputRoad[InputRoadNode];
	if (FileList[from].ParentNodeNum == to)   //文件已经存在于目标路径中
	{
		cout << "不能将文件复制到其所在目录\n";
		return;
	}
	int newnode = ApplyFileNode();    //新建一个空文件结点值
	if (newnode == -1)
	{
		cout << "磁盘已满，不能复制\n";
		return;
	}
	int i;
	for (i = 0; i<12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//将源文件复制到新建的文件中
	FileList[newnode].FileType = FileList[from].FileType;					//新文件类型与原来相同
	FileList[newnode].ParentNodeNum = to;									//新文件的父母文件结点为目标文件
	FileList[newnode].ChildNodeNum = -1;									//新文件的孩子文件结点不存在
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//新文件的同级文件结点为目标文件的孩子结点文件
	FileList[to].ChildNodeNum = newnode;									//新文件为目标文件的孩子结点文件
	FileList[newnode].BlockNum = ApplyBlock();								//为新文件分配一个分区
	WriteFileNode(to);														//目标文件重新写入磁盘
	WriteFileNode(newnode);													 //将新建的文件写入磁盘
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "磁盘已满，文件内容无法复制\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//磁盘没有满
	{
		i = 0;
		while (i<55 && BlockList[blocknum1].content[i] != '\0')    //复制文件内容
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i<55)
		{
			cout << "文件复制完成\n";
			WriteBlock(blocknum2);   //写入磁盘
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//将新分区标记为占用
		BlockList[blocknum2].next = ApplyBlock();				//申请下一个分区
		if (BlockList[blocknum2].next == -1)					//如果申请不到
		{
			cout << "磁盘空间不足，部分内容以复制\n";
			return;
		}
		WriteBlock(blocknum2);									//申请到了，将新分区写入磁盘
		blocknum1 = BlockList[blocknum1].next;					//当前分区位置后移
		blocknum2 = BlockList[blocknum2].next;
	}
}
//复制文件及目录
void XCopy() 
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 0 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
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
		from = InputRoad[InputRoadNode];   //记录当前文件
		DistinguishRoad(Third);
		to = InputRoad[InputRoadNode];
		DirectoryTo(from, to);
	}
		

	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //记录子文件结点

		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "您输入的源文件路径不正确" << endl;
			return;
		}
		DistinguishRoad(Third);
		to = InputRoad[InputRoadNode];
		DirectoryTo(from, to);
	}
	
}
//XCopy的目的文件部分
void DirectoryTo(int from, int to)
{
	if (FileList[from].ParentNodeNum == to)   //文件已经存在于目标路径中
	{
		cout << "不能将文件复制到其所在目录\n";
		return;
	}
	int newnode = ApplyFileNode();    //新建一个空文件结点值
	if (newnode == -1)
	{
		cout << "磁盘已满，不能复制\n";
		return;
	}
	int i;
	for (i = 0; i < 12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//将源文件复制到新建的文件中
	FileList[newnode].FileType = FileList[from].FileType;					//新文件类型与原来相同
	FileList[newnode].ParentNodeNum = to;									//新文件的父母文件结点为目标文件
	FileList[newnode].ChildNodeNum = -1;									//新文件的孩子文件结点不存在
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//新文件的同级文件结点为目标文件的孩子结点文件
	FileList[to].ChildNodeNum = newnode;									//新文件为目标文件的孩子结点文件
	FileList[newnode].BlockNum = ApplyBlock();								//为新文件分配一个分区
	WriteFileNode(to);														//目标文件重新写入磁盘
	WriteFileNode(newnode);													 //将新建的文件写入磁盘
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "磁盘已满，文件内容无法复制\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//磁盘没有满
	{
		i = 0;
		while (i < 55 && BlockList[blocknum1].content[i] != '\0')    //复制文件内容
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i < 55)
		{
			cout << "文件复制完成\n";
			WriteBlock(blocknum2);   //写入磁盘
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//将新分区标记为占用
		BlockList[blocknum2].next = ApplyBlock();				//申请下一个分区
		if (BlockList[blocknum2].next == -1)					//如果申请不到
		{
			cout << "磁盘空间不足，部分内容以复制\n";
			return;
		}
		WriteBlock(blocknum2);									//申请到了，将新分区写入磁盘
		blocknum1 = BlockList[blocknum1].next;					//当前分区位置后移
		blocknum2 = BlockList[blocknum2].next;
	}
}
//删除文件
void Del()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int i = DistinguishRoad(Second);
	int filenode;
	if (i == -1)
	{
		cout << "您输入的文件路径不正确" << endl;
		return;
	}
	/*if (i == 0)   //目录文件
	{
		filenode = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[filenode].ChildNodeNum);    //将孩子结点文件删除
	}*/
	if (i == 1)   //文本文件
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //释放分区
	}
	if (i == 2)   //不是终结文件，即仍是路径
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //进入子文件
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //删除孩子结点文件
				else
					FreeBlocks(FileList[filenode].BlockNum);   //如果是文本文件，释放分区
				break;
			}
			n = FileList[n].BrotherNodeNum;   //同级文件
		}
		if (n == -1)
		{
			cout << "您输入的文件路径不正确" << endl;
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
		WriteFileNode(FileList[i].ParentNodeNum);  //将父母文件重新写入磁盘
		FreeFileNode(i);                            //将文件本身删除
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
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
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
	}
}
//显示文件信息
void Dir()
{
	int i;
	if (strcmp(Second, "") == 0)
	{
		cout << endl;
		cout << FileList[Road[RoadNode]].FileName << "的目录\n" << endl;
		i = FileList[Road[RoadNode]].ChildNodeNum;
		while (i != -1)
		{
			if (FileList[i].FileType == 1)              //显示所有目录文件
				cout << "\t<DIR>\t" << FileList[i].FileName << endl;
			i = FileList[i].BrotherNodeNum;
		}
		i = FileList[Road[RoadNode]].ChildNodeNum;
		while (i != -1)
		{
			if (FileList[i].FileType == 2)             //显示所有文本文件
				cout << "\t  \t" << FileList[i].FileName << endl;
			i = FileList[i].BrotherNodeNum;
		}
	}
	else
	{
		if (strcmp(Third, "") != 0)
		{
			cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
			return;
		}
		else
		{
			if (DistinguishRoad(Second) != 0)     //不是目录文件
			{
				cout << "您输入的目录路径不正确，具体可以使用help命令查看" << endl;
				return;
			}
			cout << FileList[InputRoad[InputRoadNode]].FileName << "的目录\n" << endl;
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
//退出系统
void Exit()
{
	exit(1);
}
//格式化磁盘
void Format()
{
	if (strcmp(Second, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	cout << "磁盘格式化后，所有数据都会丢失，确认要格式化吗？(Y/N)\n";
	char a[5];
	cin.getline(a, 5);
	if (a[0] != 'y'&&a[0] != 'Y')   //不格式化
		return;
	Initial();   //将磁盘初始化
	ReadAll();   //读写文件
}
//查找字符串
void Find()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int thirdfile = DistinguishRoad(Third);
	if (thirdfile == -1)
	{
		cout << "您输入的路径或文件名不正确" << endl;
		return;
	}
	if (thirdfile == 0)
	{
		cout << "您输入的路径终端不是文本文件" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (thirdfile == 1)   //是文本文件
		filenodenum = InputRoad[InputRoadNode];
	if (thirdfile == 2)   //是路径
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
			cout << "该目录下没有名为‘" << Third << "’的文本文件\n";
			return;
		}
	}
	cout << "----------" << FileList[filenodenum].FileName << endl;
	blocknum = FileList[filenodenum].BlockNum;
	
	if (strstr(BlockList[blocknum].content,Second ) == NULL)
		cout << "没有找到字符串\n";
	//cout << BlockList[blocknum].content;
	//cout << Second;
	else
		cout << BlockList[blocknum].content;
		
}
//显示帮助
void Help()
{
	if (strcmp(Second, "") == 0)
	{
		cout << "attrib    显示一个文本文件的属性\n";
		cout << "cd        进入指定目录文件\n";
		cout << "copy      将一个文本文件复制到指定的目录下\n";
		cout << "xcopy	  将一个文本文件或目录文件下的所有文件复制到指定的目录下\n";
		cout << "del       删除一个文本文件\n";
		cout << "dir       显示目录下的所以文件信息\n";
		cout << "exit      退出系统\n";
		cout << "format    格式化磁盘\n";
		cout << "find      查找字符串\n";
		cout << "mk        在当前目录下新建一个文本文件\n";
		cout << "mkdir     在当目录下新建一个目录文件\n";
		cout << "more      显示和修改文本文件的内容\n";
		//cout << "move	   移动文本文件\n";
		cout << "rmdir	  删除目录文件包括目录下的所有文件\n";
		cout << "time	  显示系统的时间\n";
		cout << "import    将磁盘外的文件导入\n";
		cout << "export    将磁盘外的文件导出\n";
		cout << "具体命令解释请使用命令‘help 命令名’\n";
	}
	else
	{
		if (strcmp(Third, "") != 0)
		{
			cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
			return;
		}
		else if (strcmp(Second, "attrib") == 0)
			cout << "\nattrib 命令 显示一个文本文件的属性\n该命令只有一个参数，该参数可以是当前目录下的文件名，也可以是文件的绝对路径\n";
		else if (strcmp(Second, "cd") == 0)
			cout << "\ncd 命令 进入指定目录文件\n该命令只有一个参数，该参数可以是‘..’，表示返回上一级目录，也可以是当前目录下的一个目录文件名，表示进入该目录，也可以是某个目录的决定路径\n";
		else if (strcmp(Second, "copy") == 0)
			cout << "\ncopy 命令 将一个文本文件复制到指定的目录下\n该命令有两个参数，第一个参数表示要复制的源文件，可以是当前目录下的文件名，也可以是文件的绝对路径；第二个参数表示复制到的目录，该参数必须是目录的绝对路径\n";
		else if (strcmp(Second, "xcopy") == 0)
			cout << "\nxcopy 命令 将一个文本文件或目录内的所有文件复制到指定的目录下\n该命令有两个参数，第一个参数表示要复制的文件或目录下的所有文件，可以是当前目录下的文件名或目录名，也可以是文件或目录的绝对路径；第二个参数表示复制到的目录，该参数必须是目录的绝对路径\n";
		else if (strcmp(Second, "del") == 0)
			cout << "\ndel 命令 删除一个文本文件\n该命令只有一个参数，该参数为要删除的文件的文件名，可以是当前目录下的文件名，也可以是文件的绝对路径\n";
		else if (strcmp(Second, "dir") == 0)
			cout << "\ndir 命令 显示目录下的所以文件信息\n该命令可以没有参数表示显示当前目录下的所以文件信息，也可以有一个参数，为某一目录文件的绝对路径，显示该目录下的所以文件信息\n";
		else if (strcmp(Second, "exit") == 0)
			cout << "\nexit 命令 退出系统\n该命令没有参数，表示退出系统\n";
		else if (strcmp(Second, "format") == 0)
			cout << "\nformat 命令 格式化磁盘\n该命令没有参数，使用后将使磁盘初始化\n";
		else if (strcmp(Second, "find") == 0)
			cout << "\nfind 命令 查找字符串\n该命令有两个参数，第一个参数表示要查找的字符串，第二个参数是查找的绝对路径（文本文件）";
		else if (strcmp(Second, "mk") == 0)
			cout << "\nmk 命令 在当前目录下新建一个文本文件\n该命令只有一个参数，该参数为新建文本文件的文件名，且不能和当前目录下其他文件的文件名相同\n";
		else if (strcmp(Second, "mkdir") == 0)
			cout << "\nmkdir 命令 在当目录下新建一个目录文件\n该命令只有一个参数，该参数为新建目录文件的文件名，且不能和当前目录下其他文件的文件名相同\n";
		else if (strcmp(Second, "more") == 0)
			cout << "\nmore 命令 显示和修改文本文件的内容\n该命令只有一个参数，该参数为指定文本文件的文件名或绝对路径，显示该文本文件当前的内容，然后会提示选择是否修改内容，如果修改则输入新的内容并保存到磁盘中\n";
		else if (strcmp(Second, "move") == 0)
			cout << "\nmove 命令 移动文本文件\n该命令有两个参数，第一个参数为被移动的源文件路径，第二个参数为要移动到的目的目录\n";
		else if (strcmp(Second, "rmdir") == 0)
			cout << "\nrmdir 命令 删除目录文件包括目录下的所有文件\n该命令只有一个参数，该参数要删除的文件的文件名，可以是当前目录下的文件名，也可以是文件的决定路径\n";
		else if (strcmp(Second, "time") == 0)
			cout << "\ntime 命令 显示系统时间\n该命令没有参数，显示系统当前时间\n";
		else if (strcmp(Second, "help") == 0)
			cout << "\n具体命令解释请使用命令‘help 命令名’\n该命令可以没有参数表示显示Shell系统支持的所以命令解释，也可以有一个参数，为其他命令名称，表示具体解释此命令\n";
		else if (strcmp(Second, "import") == 0)
			cout << "\nimport 命令 将磁盘外路径下的文件导入到当前路径下\n该命令有两个参数，一个参数为导入的路径，第二个参数为要保存在磁盘内的路径\n";
		else if (strcmp(Second, "export") == 0)
			cout << "\nexport 命令 将磁盘内路径下的文件导出到磁盘外路径下\n该命令有两个参数，第一个参数为要导出的磁盘内数据的路径，第二个参数为要保存在磁盘外的路径。\n";
		else
			cout << "\n您输入的命令‘" << Second << "’不存在\n";
	}
}
//创建文件
void Mk()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int nodenum = ApplyFileNode();   //申请新文件结点
	int contentnum = ApplyBlock();    //申请新分区
	if (nodenum == -1 || contentnum == -1)
	{
		cout << "磁盘已满，不能新建目录\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //新文件为当前文件的子文件
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Second) == 0)    //判断是否存在
		{
			cout << "文件" << Second << "已经存在\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Second[i] != '\0')
	{
		if (Second[i] == 92)
		{
			cout << "文件名中不能有‘" << char(92) << "’字符" << endl;  //文件名中不能有'\'
			return;
		}
		FileList[nodenum].FileName[i] = Second[i];  //将输入的文件名赋值给新建的文件结点
		i++;
	}
	FileList[nodenum].FileType = 2;      //新文件类型为文本文件
	FileList[nodenum].ParentNodeNum = Road[RoadNode];   //当前文件为新文件的父母结点
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;  //当前文件的孩子结点为新文件的同级结点
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;  //当前文件的孩子结点为新文件
	FileList[nodenum].ChildNodeNum = -1;    //新文件没有孩子结点
	FileList[nodenum].BlockNum = contentnum;   //新文件写入新分区
	BlockList[contentnum].IfUsing = true;   //新分区标记为占用
	BlockList[contentnum].next = -1;       //新分区的下一个分区没有
	BlockList[contentnum].content[0] = '\0';   //新文件内容为空
	WriteFileNode(nodenum);        //将新文件写入磁盘
	WriteFileNode(FileList[nodenum].ParentNodeNum);   //将新文件的父母结点写入磁盘
	WriteBlock(contentnum);   //将新分区写入磁盘
}
//创建目录
void Mkdir()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int nodenum = ApplyFileNode();  //申请新的文件结点
	if (nodenum == -1)
	{
		cout << "磁盘已满，不能新建目录\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //新的文件结点为当前结点的孩子结点
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Second) == 0)
		{
			cout << "目录" << Second << "已经存在\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Second[i] != '\0')
	{
		if (Second[i] == 92)
		{
			cout << "文件名中不能有‘" << char(92) << "’字符" << endl;
			return;
		}
		FileList[nodenum].FileName[i] = Second[i];
		i++;
	}
	FileList[nodenum].FileName[i] = '\0';   //新文件名
	FileList[nodenum].FileType = 1;     //新文件属性
	FileList[nodenum].ParentNodeNum = Road[RoadNode];  //父母结点
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;   //父母结点的孩子结点为新文件的同级结点
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;
	FileList[nodenum].ChildNodeNum = -1;
	WriteFileNode(nodenum);    //新文件写入磁盘
	WriteFileNode(FileList[nodenum].ParentNodeNum);  //父母结点写入磁盘
}
//修改文件内容
void More()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int nowvacation = DistinguishRoad(Second);
	if (nowvacation == -1)
	{
		cout << "您输入的路径或文件名不正确" << endl;
		return;
	}
	if (nowvacation == 0)
	{
		cout << "您输入的路径终端不是文本文件" << endl;
		return;
	}
	int filenodenum, blocknum;
	if (nowvacation == 1)   //是文本文件
		filenodenum = InputRoad[InputRoadNode];
	if (nowvacation == 2)   //是路径
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
			cout << "该目录下没有名为‘" << Second << "’的文本文件\n";
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
			cout << BlockList[blocknum].content[i];   //输出文件内容
			i++;
		}
		blocknum = BlockList[blocknum].next;
	}
	cout << "\n该文本文件的内容已经显示完毕，是否对其修改？（Y/N）";
	cin.getline(a, 5);
	if (a[0] != 'Y' && a[0] != 'y' || a[1] != '\0')
		return;
	cout << "请输入文本文件的内容\n";
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
			cout << "修改后的内容以写入磁盘\n";
			return;
		}
		WriteBlock(blocknum);
		j = BlockList[blocknum].next;
		if (j == -1)
		{
			j = ApplyBlock();
			if (j == -1)
			{
				cout << "磁盘已满，只有部分内容写入到磁盘中\n";
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
//移动文本文件
void Move() 
{
	//copy
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2) && DistinguishRoad(Third) == 0))
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int from, to;
	if (secondfile == 0)   //目录文件
	{
		from = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[from].ChildNodeNum);    //将孩子结点文件删除
	}
	if (secondfile == 1) 
	{
		from = InputRoad[InputRoadNode];   //记录当前文件
		FreeBlocks(FileList[from].BlockNum);   //释放分区
	}
	if (secondfile == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //记录子文件结点
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "您输入的源文件路径不正确" << endl;
			return;
		}
	}
	DistinguishRoad(Third);
	to = InputRoad[InputRoadNode];
	if (FileList[from].ParentNodeNum == to)   //文件已经存在于目标路径中
	{
		cout << "不能将文件复制到其所在目录\n";
		return;
	}
	int newnode = ApplyFileNode();    //新建一个空文件结点值
	if (newnode == -1)
	{
		cout << "磁盘已满，不能复制\n";
		return;
	}
	int i;
	for (i = 0; i < 12; i++)
		FileList[newnode].FileName[i] = FileList[from].FileName[i];			//将源文件复制到新建的文件中
	FileList[newnode].FileType = FileList[from].FileType;					//新文件类型与原来相同
	FileList[newnode].ParentNodeNum = to;									//新文件的父母文件结点为目标文件
	FileList[newnode].ChildNodeNum = -1;									//新文件的孩子文件结点不存在
	FileList[newnode].BrotherNodeNum = FileList[to].ChildNodeNum;			//新文件的同级文件结点为目标文件的孩子结点文件
	FileList[to].ChildNodeNum = newnode;									//新文件为目标文件的孩子结点文件
	FileList[newnode].BlockNum = ApplyBlock();								//为新文件分配一个分区
	WriteFileNode(to);														//目标文件重新写入磁盘
	WriteFileNode(newnode);													 //将新建的文件写入磁盘
	if (FileList[newnode].BlockNum == -1)
	{
		cout << "磁盘已满，文件内容无法复制\n";
		return;
	}
	int blocknum1 = FileList[from].BlockNum;
	int blocknum2 = FileList[newnode].BlockNum;
	while (blocknum1 != -1)		//磁盘没有满
	{
		i = 0;
		while (i < 55 && BlockList[blocknum1].content[i] != '\0')    //复制文件内容
		{
			BlockList[blocknum2].content[i] = BlockList[blocknum1].content[i];
			i++;
		}
		if (i < 55)
		{
			cout << "文件复制完成\n";
			WriteBlock(blocknum2);   //写入磁盘
			return;
		}
		BlockList[blocknum2].IfUsing = true;					//将新分区标记为占用
		BlockList[blocknum2].next = ApplyBlock();				//申请下一个分区
		if (BlockList[blocknum2].next == -1)					//如果申请不到
		{
			cout << "磁盘空间不足，部分内容以复制\n";
			return;
		}
		WriteBlock(blocknum2);									//申请到了，将新分区写入磁盘
		blocknum1 = BlockList[blocknum1].next;					//当前分区位置后移
		blocknum2 = BlockList[blocknum2].next;
	}
	//del
	/*int filenode;
	if (secondfile == 1)   //文本文件
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //释放分区
	}
	if (secondfile == 2)   //不是终结文件，即仍是路径
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //进入子文件
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //删除孩子结点文件
				else
					FreeBlocks(FileList[filenode].BlockNum);   //如果是文本文件，释放分区
				break;
			}
			n = FileList[n].BrotherNodeNum;   //同级文件
		}
		if (n == -1)
		{
			cout << "您输入的文件路径不正确" << endl;
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
		WriteFileNode(FileList[secondfile].ParentNodeNum);  //将父母文件重新写入磁盘
		FreeFileNode(secondfile);                            //将文件本身删除
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
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
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
	}*/
}
//删除一个文件目录
void Rmdir()
{
	if (strcmp(Second, "") == 0 || strcmp(Second, "") != 0 && strcmp(Third, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int i = DistinguishRoad(Second);
	int filenode;
	if (i == -1)
	{
		cout << "您输入的文件路径不正确" << endl;
		return;
	}
	if (i == 0)   //目录文件
	{
		filenode = InputRoad[InputRoadNode];
		FreeFileNodes(FileList[filenode].ChildNodeNum);    //将孩子结点文件删除
	}
	if (i == 1)   //文本文件
	{
		filenode = InputRoad[InputRoadNode];
		FreeBlocks(FileList[filenode].BlockNum);   //释放分区
	}
	if (i == 2)   //不是终结文件，即仍是路径
	{
		int n = FileList[Road[RoadNode]].ChildNodeNum;  //进入子文件
		while (n != -1)
		{
			if (strcmp(FileList[n].FileName, Second) == 0)
			{
				filenode = n;
				if (FileList[n].FileType == 1)
					FreeFileNodes(FileList[filenode].ChildNodeNum);  //删除孩子结点文件
				else
					FreeBlocks(FileList[filenode].BlockNum);   //如果是文本文件，释放分区
				break;
			}
			n = FileList[n].BrotherNodeNum;   //同级文件
		}
		if (n == -1)
		{
			cout << "您输入的文件路径不正确" << endl;
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
		WriteFileNode(FileList[i].ParentNodeNum);  //将父母文件重新写入磁盘
		FreeFileNode(i);                            //将文件本身删除
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
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
		cout << "文件‘" << FileList[filenode].FileName << "’已删除";
	}
}
//显示系统时间
void Time()
{
	struct tm t;			//tm结构指针 
	time_t now;				//声明time_t类型变量
	time(&now);				//获取系统日期和时间
	localtime_s(&t, &now);	//获取当地日期和时间
	
	printf("%d年 %d月 %d日\n", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
	printf("%d时 %d分 %d秒\n", t.tm_hour, t.tm_min, t.tm_sec);
}
//显示系统版本
void Ver()
{
	cout << endl;
	cout << "Dingyuxing Platform [版本 1.0.0.1]" << endl;
}
//导出
void Export()
{
	if (!(strcmp(Second, "") != 0 && strcmp(Third, "") != 0) || strcmp(Other, "") != 0)
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int secondfile = DistinguishRoad(Second);
	if (!((secondfile == 1 || secondfile == 2)))
	{
		cout << "您输入的命令格式不正确，具体可以使用help命令查看" << endl;
		return;
	}
	int from, to;
	if (DistinguishRoad(Second) == 1)
		from = InputRoad[InputRoadNode];   //记录当前文件
	if (DistinguishRoad(Second) == 2)
	{
		from = FileList[Road[RoadNode]].ChildNodeNum;   //记录子文件结点
		while (from != -1)
		{
			if (FileList[from].FileType == 2 && strcmp(FileList[from].FileName, Second) == 0)
				break;
			from = FileList[from].BrotherNodeNum;
		}
		if (from == -1)
		{
			cout << "您输入的源文件路径不正确" << endl;
			return;
		}
	}
	ofstream out;
	out.open(Third, std::ios::out | std::ios::app);
	if (!out.is_open())
		cout << "打开文件错误." << endl;
	
	out << BlockList[FileList[from].BlockNum].content << endl;
	out.close();
	
}
//导入
void Import()
{
	int nodenum = ApplyFileNode();   //申请新文件结点
	int contentnum = ApplyBlock();    //申请新分区
	if (nodenum == -1 || contentnum == -1)
	{
		cout << "磁盘已满，不能新建目录\n";
		return;
	}
	int i = FileList[Road[RoadNode]].ChildNodeNum;   //新文件为当前文件的子文件
	while (i != -1)
	{
		if (strcmp(FileList[i].FileName, Third) == 0)    //判断是否存在
		{
			cout << "文件" << Third << "已经存在\n";
			return;
		}
		i = FileList[i].BrotherNodeNum;
	}
	i = 0;
	while (Third[i] != '\0')
	{
		if (Third[i] == 92)
		{
			cout << "文件名中不能有‘" << char(92) << "’字符" << endl;  //文件名中不能有'\'
			return;
		}
		FileList[nodenum].FileName[i] = Third[i];  //将输入的文件名赋值给新建的文件结点
		i++;
	}
	FileList[nodenum].FileType = 2;      //新文件类型为文本文件
	FileList[nodenum].ParentNodeNum = Road[RoadNode];   //当前文件为新文件的父母结点
	FileList[nodenum].BrotherNodeNum = FileList[Road[RoadNode]].ChildNodeNum;  //当前文件的孩子结点为新文件的同级结点
	FileList[Road[RoadNode]].ChildNodeNum = nodenum;  //当前文件的孩子结点为新文件
	FileList[nodenum].ChildNodeNum = -1;    //新文件没有孩子结点
	FileList[nodenum].BlockNum = contentnum;   //新文件写入新分区
	BlockList[contentnum].IfUsing = true;   //新分区标记为占用
	BlockList[contentnum].next = -1;       //新分区的下一个分区没有	

	ifstream infile;
	infile.open(Second, ios::in);   //将文件流对象与文件连接起来 
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
	infile.close();             //关闭文件输入流

	WriteFileNode(nodenum);        //将新文件写入磁盘
	WriteFileNode(FileList[nodenum].ParentNodeNum);   //将新文件的父母结点写入磁盘
	WriteBlock(contentnum);   //将新分区写入磁盘
}