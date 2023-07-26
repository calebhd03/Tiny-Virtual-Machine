/*
 * tinyarch.c
 *
 *  Created on: Jul 17, 2023
 *      Author: calebdeters
 */

#include <stdio.h>
#define IMSIZE 129
#define DMSIZE 10

//Instuction Register
struct IR
{
	int OP;
	int ADDR;
};

FILE *fpW; //file to write to
struct IR IR; //instuction Register
int IM[IMSIZE]; //instruction memory
int DM[DMSIZE];	//data memory
int PC = 0;	//program counter
int AC = 0; //accumulator

//puts next instruction in IR
void Fetch()
{
	int MAR1 = PC;
	PC += 2;
	IR.OP = IM[MAR1];
	IR.ADDR = IM[MAR1+1];
}
// AC = DM[ADDR]
void Load()
{
	fprintf(fpW, "Load <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC = MDR;
}
// AC += DM[ADDR]
void Add()
{
	fprintf(fpW, "Add <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC += MDR;
}
//store AC in DM[ADDR]
void Store()
{
	fprintf(fpW, "Store <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = AC;
	DM[MAR] = MDR;
}
// AC -= DM[ADDR]
void Sub()
{
	fprintf(fpW, "Subt <%d>\n", IR.ADDR);
	int MAR = IR.ADDR;
	int MDR = DM[MAR];
	AC -= MDR;
}
//keyboard input to AC
void In()
{
	fprintf(fpW, "In <%d>\n", IR.ADDR);
	printf("Input keyboard: ");
	scanf("%d", &AC);
	fprintf(fpW, "Input keyboard: %d\n", AC);
}
//output AC to screen
void Out()
{
	fprintf(fpW, "Out <%d>\n", IR.ADDR);
	fprintf(fpW, "result is %d\n", AC);
	printf("result is %d\n", AC);
}
//ends the program
int Halt()
{
	return 0;
}
//jump to PC <ADDR>
void JMP()
{
	PC = IR.ADDR * 2;
}
//if AC == 0 skip next line
void SkipZ()
{
	if(AC == 0)
	{
		PC += 2;
	}
}
//if AC > 0 skip next line
void SkipG()
{
	if(AC>0)
	{
		PC += 2;
	}
}
//if AC < 0 skip next line
void SkipL()
{
	if(AC<0)
	{
		PC += 2;
	}
}
//prints the current machines values
void PrintValues()
{
	fprintf(fpW, "\nPC = %d | A = %d | DM = [%d", PC, AC, DM[0]);
	//prints DM
	for(int i=1; i < DMSIZE; i++)
	{
		fprintf(fpW, ", %d", DM[i]);
	}
	fprintf(fpW, "]\n");
}
//converts the elf to instructions
void InputIM()
{
	printf("Input file name: ");
	char fileName[128];
	scanf("%s", fileName);


	FILE *fp;
	fp = fopen(fileName, "r");

	fprintf(fpW, "Starting compile: %s\n", fileName);
	char buff[255];
	int IMCounter = 0;
	int op = 0;
	int addr = 0;
	fscanf(fp, "%d", &op);
	fscanf(fp, "%d", &addr);
	fgets(buff, 255, fp);

	//fgets(buff, 255, (FILE*)fp);

	while(feof(fp) ==0)
	{

		IM[IMCounter] = op;
		IM[IMCounter + 1] = addr;

		IMCounter += 2;
		fscanf(fp, "%d", &op);
		fscanf(fp, "%d", &addr);
		fgets(buff, 255, (FILE*)fp);

	}
	IM[IMCounter] = op;
	IM[IMCounter + 1] = addr;

	fclose(fp);



	fprintf(fpW, "Done Compiling \n");
}
//prints the instruction memory
void PrintIM()
{

	fprintf(fpW, "IM = [%d", IM[0]);
	//prints DM
	for(int i=1; i < IMSIZE; i++)
	{
		fprintf(fpW, ", %d", IM[i]);
	}
	fprintf(fpW, "]\n");
}

int main()
{
	char outputFileName[128] = "CalebDetersOutputFIle.txt";
	fpW= fopen(outputFileName, "w");

	printf("Outputting to: %s\n", outputFileName);

	InputIM();
	PrintIM();

	//run program
	int loop = 1;
	while(loop)
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
			loop = Halt(); //ends the program here
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
			fprintf(fpW, "!!!! WRONG INPUT !!!!");
			break;
		}
	}

	fprintf(fpW, "\nEnd of program\n");
	fclose(fpW);
	return 0;
}
