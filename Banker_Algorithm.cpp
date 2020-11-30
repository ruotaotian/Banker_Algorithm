#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define rN  50
#define pN  50
int processNum, resourceNum;

int available[rN] = {};										  //可利用资源向量available: 3,3,2
int maxRequest[pN][rN] = {};								  //最大需求矩阵: 7,5,3,3,2,2,9,0,2,2,2,2,4,3,3
int allocation[pN][rN] = {};								  //分配矩阵: 0,1,0,2,0,0,3,0,2,2,1,1,0,0,2
int need[pN][rN] = {};										  //需求矩阵: 7,4,3,1,2,2,6,0,0,0,1,1,4,3,1
int requests[rN];											  //请求的资源
bool Finish[pN];
int safeSeries[pN] = {};									  //安全序列

void show_resource()										//显示系统资源
{

	printf("available[resourceNum] = ");
	for (int i = 0; i < resourceNum; i++)
	{
		printf("  %d  ", available[i]);
	}
	printf("\n\n\n");
	printf("allocation[processNum][resourceNum]: ");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			if (j % 3 == 0)
			{
				printf("\n");
			}
			printf("   %d   ", allocation[i][j]);
		}
	}
	printf("\n\n\n");
	printf("need[processNum][resourceNum]: ");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			if (j % 3 == 0)
			{
				printf("\n");
			}
			printf("   %d   ", need[i][j]);
		}
	}
	printf("\n\n\n");
	printf("max[processNum][resourceNum]: ");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			if (j % 3 == 0)
			{
				printf("\n");
			}
			printf("   %d   ", maxRequest[i][j]);
		}
	}
	printf("\n\n\n");
}

int safe_Algorithm()										//安全性算法
{
	int work[rN],i;
	int order = 0, r_flag = 0, p_flag = 0;
	for (int i = 0; i < resourceNum; i++)
	{
		work[i] = available[i];
	}
	printf("\n");
	for (int i = 0; i < processNum; i++)
	{
		Finish[i] = false;
	}
	for(int n = 0; n < processNum; n++)
	{
		for (int i = 0; i < processNum; i++)
		{
			for (int j = 0; j < resourceNum; j++)
			{
				if (Finish[i] == false && need[i][j] <= work[j])
				{
					r_flag++;
				}
			}
			if (r_flag == resourceNum)
			{
				r_flag = 0;
				printf("P%d ", i);
				Finish[i] = true;
				for (int j = 0; j < resourceNum; j++)
				{
					work[j] = work[j] + allocation[i][j];
				}
				for (int i = 0; i < resourceNum; i++)
				{
					printf(" %d", work[i]);
				}
				printf("\n");
				safeSeries[order] = i;
				order++;
				p_flag++;
			}
			else
			{
				r_flag = 0;
			}
		}
	}
	if (p_flag == processNum)
	{
		printf("系统处于安全状态\n\n");
		printf("安全序列为: ");
		for (int i = 0; i < processNum; i++)
		{
			printf("P%d ", safeSeries[i]);
		}
		printf("\n\n\n");
		return 1;
	}
	else
	{
		printf("系统处于不安全状态\n\n");
		return 0;

	}

}

void Banker_Algorithm(int process)                            //银行家算法
{
	int flag = 0;
	bool result;
	for (int i = 0; i < resourceNum; i++)
	{
		if (requests[i] <= need[process][i])
		{
			flag++;
		}
	}

	if (flag == resourceNum)
	{
		printf("所需资源没超过资源的最大值\n\n");
		flag = 0;
		for (int i = 0; i < resourceNum; i++)
		{
			if (requests[i] <= available[i])
			{
				flag++;
			}
		}
		if (flag == resourceNum)
		{
			printf("有足够的可利用资源,系统试探着将资源分配给P%d\n\n", process);
			for (int i = 0; i < resourceNum; i++)
			{
				need[process][i] = need[process][i] - requests[i];
				allocation[process][i] = allocation[process][i] + requests[i];
				available[i] = available[i] - requests[i];
			}
			result = safe_Algorithm();
			if (result == 1)
			{
				printf("系统安全, 正式将资源分配给P%d\n\n", process);
				show_resource();
			}
			else
			{
				for (int i = 0; i < resourceNum; i++)
				{
					need[process][i] = need[process][i] + requests[i];
					allocation[process][i] = allocation[process][i] - requests[i];
					available[i] = available[i] + requests[i];
				}
				printf("系统不安全，此次分配作废\n\n");
				show_resource();
			}
		}
		else
		{
			printf("尚无足够资源,P%d进程需等待\n\n", process);
		}
	}
	else
	{
		printf("所需资源数已经超过了他所宣布的最大值\n\n");
	}

}


void input_resource()										//输入资源
{
	printf("请输入进程数: ");
	scanf_s("%d", &processNum);
	printf("请输入资源数: ");
	scanf_s("%d", &resourceNum);
	printf("\n输入可利用资源向量Available: \n");
	for (int i = 0; i < resourceNum; i++)
	{
		scanf_s("%d", &available[i]);
	}
	printf("\n输入最大需求矩阵Max: \n");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			scanf_s("%d", &maxRequest[i][j]);
		}
	}
	printf("\n输入分配矩阵Allocation: \n");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			scanf_s("%d", &allocation[i][j]);
		}
	}
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			need[i][j] = maxRequest[i][j] - allocation[i][j];
		}
	}
	printf("\n\n");
}

int main()
{
	int choose;
	int process;
	while (true)
	{
		system("cls");
		printf("******************************************************************************************\n\n");
		printf("***********************************欢迎使用银行家算法*************************************\n\n");
		printf("\n1.输入资源\n2.银行家算法\n3.安全性算法\n4.显示系统资源\n0.退出\n\n");
		printf("******************************************************************************************\n\n");
		printf("请输入操作选项: ");
		scanf_s("%d", &choose);
		if (choose == 2)
		{
			if(resourceNum != 0 && processNum != 0)
			{ 
				printf("输入请求的进程: ");
				scanf_s("%d", &process);
				for (int i = 0; i < resourceNum; i++)
				{
					printf("输入requests请求%d类资源: ", i);
					scanf_s("%d", &requests[i]);
				}
				Banker_Algorithm(process);
			}
			else
			{
				printf("当前系统无资源请分配资源后再运行算法\n\n");
			}
		}

		if (choose == 3)
		{
			if (resourceNum != 0 && processNum != 0)
			{
				safe_Algorithm();
			}
			else
			{
				printf("当前系统无资源请分配资源后再运行算法\n\n");
			}
		}

		if (choose == 4)
		{
			show_resource();
		}

		if (choose == 1)
		{
			input_resource();
		}

		_getch();

		if (choose == 0)
		{
			break;
		}
	}
}
