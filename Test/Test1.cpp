#include<stdio.h>
#include<string.h>
#include <stdlib.h>

char prog[1000],token[9];//The number array token maximal leath with is 9
char ch;
int syn,p,m,n,sum;
char * rwtab[6] = {"function","if","then","while","do","endfunc"};
char number[50];

void scaner();
int main() {
	int chose = 0;
	int i;

	printf("please choose the way to analyse\n 1.Use the Terminal 2.Use the file\n");
	scanf("%d", &chose);
	if (chose == 1) {
		printf("\n please input string:\n");
		getchar();//将之前选择模式时候输入的换行符吃掉。否则后面会处理这个换行符
		do {

			scanf("%c", &ch);
			prog[p++] = ch;
		}

		while (ch != '#');
	}
	else {

		FILE *fp = NULL;//输入文件
		FILE *fp2 = NULL;//输出文件
		fp = fopen("C:\\Users\\Shu\\Desktop\\testData.txt", "r");
		{
			for (i = 0; fscanf(fp, "%c", prog + i) != EOF; i++);
		}
		fp2 = fopen("C:\\Users\\Shu\\Desktop\\output.txt", "w+");//以创建模式打开，可以清空之前的内容
		fclose(fp);
		fclose(fp2);
	}
	p = 0;
	do {
		scaner();
		if (chose == 1)
		{
			switch (syn) {
			case 11:printf("\n (%d,%s)", syn, number);
				for (i = 0; i < 50; i++)//将number数字置空，否则会输出多余的数据
					number[i] = NULL;
				
				
				break;
			case -1: 
				printf("\n error");
				break;
			default:
				printf("\n (%d,%s)", syn, token);

			}
		}
		else
		{
			freopen("C:\\Users\\Shu\\Desktop\\output.txt", "a+", stdout);
			switch (syn) {
			case 11:printf("\n (%d,%s)", syn, number);
				for (i = 0; i < 20; i++)//将number数字置空，否则会输出多余的数据
					number[i] = NULL;

				break;
			case -1: printf("\n error");
				break;
			default:
				printf("\n (%d,%s)", syn, token);
			
			}
			
		}
	}
		while (syn != 0);
		return 0;
}


void scaner(){

	int i = 0;
	int k = 0;
	int j = 0;
	char temp[9];
	for (n = 0; n < 9; n++)
	{
		token[n] = NULL;//将token置空
		temp[n] = NULL;
	}
		ch  = prog[p++];

		m = 0;
		while ((ch == ' ') || (ch == '\n')|| (ch == '\t'))
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
					number[i++] = ch;//将第一个数字或小数点放入数组
					while ((ch >= '0'&& ch <= '9')||ch == '.' || ch == 'e' || ch == 'E')//循环到没有数字、“.”、“E”既识别完这一个实数
					{
						
						//sum = sum * 10 + ch - '0';
						ch = prog[p++];//将下一个字符放入ch
// 						if ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')//判断是否为符合要求的字符，若不判断，之后的任何字符都会放入number中并输出
// 							number[i++] = ch;
						if (ch == 'e' || ch == 'E')//识别科学计数法的之后的幂次数
						{
							temp[j++] = ch;//将e和e之后的所有字符存入temp数组
							ch = prog[p++];
							while ((ch >= '0'&& ch <= '9') || ch == '.' || ch == '-')
							{
								temp[j++] = ch;
								ch = prog[p++];
								
							}
							strcat(number, temp);//将两个数组连接并输出
							break;
						}
					}
					/*ch = prog[--p];*/
					p--;
					syn = 11;

				}
				else {
					switch (ch) {//主要处理各种逻辑符号
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
					case'-': 
						
						i = p - 2;
						
						number[k++] = '-';//先将读到的“-”放入number
						do
						{
						
							if ((prog[i] >= '!' &&prog[i] <= '/') || (prog[i] >= ':' && prog[i] <= '@') || (prog[i] >= '{' &&prog[i] <= '~'))//若之前为逻辑符号，则为负号
							//判断之前一个字符是不是逻辑符号，若为逻辑符号，则为负号
							{
								ch = prog[p++];
								number[k++] = ch;
								while ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')//循环到没有数字、“.”、“E”既识别完这一个实数
								{
									
									//sum = sum * 10 + ch - '0';
									
												   // 						if ((ch >= '0'&& ch <= '9') || ch == '.' || ch == 'e' || ch == 'E')//判断是否为符合要求的字符，若不判断，之后的任何字符都会放入number中并输出
												   // 							number[i++] = ch;
									if (ch == 'e' || ch == 'E')//识别科学计数法的之后的幂次数
									{
										temp[j++] = ch;
										ch = prog[p++];
										while ((ch >= '0'&& ch <= '9') || ch == '.' || ch == '-')
										{
											temp[j++] = ch;
											ch = prog[p++];

										}
										strcat(number, temp);
										break;
									}
									else
									{
										number[i++] = ch;
									}
									ch = prog[p++];//将下一个字符放入ch
								}
								p--;
								syn = 11;
								break;
							}
							else
								if (prog[i]!=' ' && prog[i]!='\n') {//之前若为其他符号，则为减号，单独进行处理
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
