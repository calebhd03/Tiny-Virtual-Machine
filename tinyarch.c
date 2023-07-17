/*
 * tinyarch.c
 *
 *  Created on: Jul 17, 2023
 *      Author: calebdeters
 */

#include <stdio.h>

struct IR
{
	int OP;
	int ADDR;
};

struct IR IR;
int IM[10] = {5,5,};
int DM[10];
int PC = 0;
int AC = 0;

void Fetch()
{
	int MAR1 = PC;
	PC += 2;
	IR.OP = IM[MAR1];
	IR.ADDR = IM[MAR1+1];
}

void Load()
{
	AC = DM[IR.ADDR];
}

void Add()
{
	AC += DM[IR.ADDR];
}

void Store()
{
	DM[IR.ADDR] = AC;
}

void Sub()
{
	AC -= DM[IR.ADDR];
}

void In()
{
	scanf("%d", &AC);
}

void Out()
{
	printf("%d\n", AC);
}

int END()
{
	return 0;
}

void JMP()
{
	PC += 2;
}

void SkipZ()
{
	if(AC == 0)
	{
		PC += 2;
	}
}


int main()
{
	IR.OP = 2;
	printf("hello");

	//run program
	while(1)
	{
		Fetch();

		switch(IR.OP)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		}
	}

	return 0;
}
