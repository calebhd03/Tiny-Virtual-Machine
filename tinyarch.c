/*
 * tinyarch.c
 *
 *  Created on: Jul 17, 2023
 *      Author: calebdeters
 */

#include <stdio.h>
#define IMSIZE 129
#define DMSIZE 10

struct IR
{
	int OP;
	int ADDR;
};

struct IR IR;
int IM[IMSIZE];
int DM[DMSIZE];
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
	printf("Load <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC = MDR;
}

void Add()
{
	printf("Add <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC += MDR;
}

void Store()
{
	printf("Store <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = AC;
	DM[MAR] = MDR;
}

void Sub()
{
	printf("Subt <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC -= MDR;
}

void In()
{
	printf("In <%d>\n", IR.ADDR);
	scanf("%d", &AC);
}

void Out()
{
	printf("Out <%d>\n", IR.ADDR);
	printf("%d\n", AC);
}

int Halt()
{
	printf("\nend of program\n");
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

void SkipG()
{
	if(AC>0)
	{
		PC += 2;
	}
}

void SkipL()
{
	if(AC<0)
	{
		PC += 2;
	}
}

void PrintValues()
{
	printf("\nPC = %d | A = %d | DM = [%d", PC, AC, DM[0]);
	//prints DM
	for(int i=1; i < DMSIZE; i++)
	{
		printf(", %d", DM[i]);
	}
	printf("]\n");
}

void InputIM()
{
	FILE *fp;
	fp = fopen("elf.txt", "r");

	char buff[255];
	int IMCounter = 0;


	fgets(buff, 255, (FILE*)fp);

	while(feof(fp) ==0)
	{
		printf("%s", buff);
		IM[IMCounter] = buff[0] - '0';
		IM[IMCounter + 1] = buff[2] - '0';

		IMCounter += 2;
		fgets(buff, 255, (FILE*)fp);

	}
	printf("%s\n", buff);
	IM[IMCounter] = buff[0] - '0';
	IM[IMCounter + 1] = buff[2] - '0';

	IMCounter += 2;
	fgets(buff, 255, (FILE*)fp);


	fclose(fp);
}

void PrintIM()
{

	printf("IM = [%d", IM[0]);
	//prints DM
	for(int i=1; i < IMSIZE; i++)
	{
		printf(", %d", IM[i]);
	}
	printf("]\n");
}

int main()
{
	printf("hello\n");

	InputIM();
	printf("Done Inputing \n");

	PrintIM();

	//run program
	while(1)
	{
		PrintValues();
		Fetch();

		switch(IR.OP)
		{
		case 1:
			Load();
			break;
		case 2:
			Add();
			break;
		case 3:
			Store();
			break;
		case 4:
			Sub();
			break;
		case 5:
			In();
			break;
		case 6:
			Out();
			break;
		case 7:
			return Halt(); //ends the program here
			break;
		case 8:
			JMP();
			break;
		case 9:
			SkipZ();
			break;
		case 10:
			SkipG();
			break;
		case 11:
			SkipL();
			break;
		default:
			printf("!!!! WRONG INPUT !!!!");
			break;
		}
	}

	return 0;
}
