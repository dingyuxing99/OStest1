#include"command.h"
#include"operate.h"

int  main()
{
	cout << "Dingyuxing Platform [�汾 1.0.0.1]" << endl;
	cout << "(c) 2019 Dingyuxing SingleWork����������Ȩ����" << endl;
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