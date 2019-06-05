#include"command.h"
#include"operate.h"

int  main()
{
	cout << "Dingyuxing Platform [版本 1.0.0.1]" << endl;
	cout << "(c) 2019 Dingyuxing SingleWork。保留所有权利。" << endl;
	cout << endl;

	ReadAll();

	while(true)
	{
		PutOutRoad();
		cin.getline(Command,200);
		Interpretation();     
		Commands();
	}

	return 0;
}