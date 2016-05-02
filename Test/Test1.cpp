#include<stdio.h>
#include<string.h>
#include <stdlib.h>

char prog[80],token[9];//The number array token maximal leath with is 9
char ch;
int syn,p,m,n,sum;
char * rwtab[6] = {"function","if","then","while","do","endfunc"};
char number[20];

void scaner();
int main(){
	int chose = 0;
	int i;
	printf("please choose the way to analyse\n 1.Use the Terminal 2.Use the file\n");
	scanf("%d", &chose);
	if (chose == 1) {
		printf("\n please input string:\n");
		do {
			scanf("%c", &ch);
			prog[p++] = ch;
		}

		while (ch != '#');
	}
	else {

		FILE *fp = NULL;
		
		fp = fopen("C:\\Users\\Shu\\Desktop\\testData.txt", "r");
		{
			for (i = 0; fscanf(fp, "%c", prog + i) != EOF; i++);
		}
		fclose(fp);
	}
	p = 0;
	do{
		scaner();
	switch(syn){
	case 11:printf("\n (%d,%s)",syn,number);
		break;
	case -1: printf("\n error");
		break;
	default:
		printf("\n (%d,%s)",syn,token);

	}
	}
		while(syn != 0);
	return 0;
}

void scaner(){

	int i = 0;
	int k = 0;
	for(n=0;n<9;n++)
		token[n] = NULL;//将token置空
		ch  = prog[p++];
		m = 0;
		while ((ch == ' ') || (ch == '\n'))
			ch = prog[p++];//处理空格和换行符
		
			if ((ch >= 'a' &&ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				while ((ch >= 'a' &&ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' &&ch <= '9'))
				{
					token[m++] = ch;
					ch = prog[p++];
				}
// 				token[m] = '\0';
// 				ch = prog[--p];
				p--;
				syn = 10;
				for (n = 0; n < 6; n++) {
					if (strcmp(token, rwtab[n]) == 0)
					{
						syn = n + 1;
						break;
					}
				}
			}
			else
				if ((ch >= '0' && ch <= '9')||ch=='.')
				{
					sum = 0;
					number[i++] = ch;
					while ((ch >= '0'&& ch <= '9')||ch == '.' || ch == 'e' || ch == 'E')
					{
						
						//sum = sum * 10 + ch - '0';
						ch = prog[p++];
						if ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')
							
						{
							number[i++] = ch;
						}
						
					}
					/*ch = prog[--p];*/
					p--;
					syn = 11;

				}
				else {
					switch (ch) {
					case '<':m = 0;
						token[m++] = ch;
						ch = prog[++p];
						if (ch == '=') {
							syn = 22;
							token[m++] = ch;
						}
						else
						{
							syn = 20;
							//ch = prog[--p];
							p--;
						}
						break;

					case '>':
						m = 0;
						token[m++] = ch;
						ch = prog[p++];
						if (ch == '=') {
							syn = 24;
							token[m++] = ch;
						}
						else {
							syn = 23;
							//ch = prog[--p];
							p--;
						}
						break;

					case'=':
						m = 0;
						token[m++] = ch;
						ch = prog[p++];
						if (ch == '=') {
							syn = 25;
							token[m++] = ch;
						}
						else {
							syn = 18;
							//ch = prog[--p];
							p--;
						}
						break;

					case '!':
						m = 0;
						token[m++] = ch;
						ch = prog[++p];
						if (ch == '=') {
							syn = 22;
							token[m++] = ch;
						}
						else
							syn = -1;
						break;

// 					case'.':
// 						token[m++] = ch;
// 						ch = prog[p++];
// 						if (ch>='0' && ch<='9')
// 						{
// 							number[i++] = ch;
// 							while ((ch >= '0' && ch <= '9')||ch == 'e' || ch=='E')
// 							{
// 								ch = prog[p++];
// 								if ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')
// 
// 								{
// 									number[i++] = ch;
// 								}
// 							}
// 						}

					case'+':syn = 13; token[m++] = ch;
						break;
					case'-': i = p - 2;
						
						number[k++] = '-';
						do
						{
							
							if ((prog[i] >= '!' &&prog[i] <= '/') || (prog[i] >= ':' && prog[i] <= '@') || (prog[i] >= '{' &&prog[i] <= '~'))//若之前为逻辑符号，则为负号
							{
								ch = prog[p++];
								number[k++] = ch;
								while ((ch >= '0' && ch <= '9') || ch == 'e' || ch == 'E')
								{
									ch = prog[p++];
									if ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')

									{
										number[k++] = ch;
									}
									ch = prog[p++];
									p--;
									syn = 11;
									
								}
							}
							else
								if (prog[i]!=' ' && prog[i]!='\n') {
									syn = 14;
									token[m++] = ch;
									break;
									i--;
								}
						} while (prog[i] == ' ' && prog[i] == '\n');
						break;
					case'*':syn = 15; token[m++] = ch;
						break;
					case'/':syn = 16; token[m++] = ch;
						break;
					case';':syn = 26; token[m++] = ch;
						break;
					case'(':syn = 27; token[m++] = ch;
						break;
					case')':syn = 28; token[m++] = ch;
						break;
					case '#': syn = 0; token[m++] = ch;
						break;

					default: syn = -1;
						break;
					}
				}
					token[m++] = '\0';
}
