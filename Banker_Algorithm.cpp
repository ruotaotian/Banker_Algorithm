#include<stdio.h>
#define rN  50
#define pN  50
int processNum, resourceNum;

int available[rN] = {};										  //��������Դ����available: 3,3,2
int maxRequest[pN][rN] = {};								  //����������: 7,5,3,3,2,2,9,0,2,2,2,2,4,3,3
int allocation[pN][rN] = {};								  //�������: 0,1,0,2,0,0,3,0,2,2,1,1,0,0,2
int need[pN][rN] = {};										  //�������: 7,4,3,1,2,2,6,0,0,0,1,1,4,3,1
int requests[rN];											  //�������Դ
bool Finish[pN];
int safeSeries[pN] = {};									  //��ȫ����

int safe_Algorithm()										//��ȫ���㷨
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
	while(p_flag < processNum)
	{
		for (int i = 0; i < processNum; i++)
		{
			for (int j = 0; j < resourceNum; j++)
			{
				if (Finish[i] == false && need[i][j] <= work[j])
				{
					r_flag++;
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
			}
		}
	}
	if (p_flag == processNum)
	{
		printf("ϵͳ���ڰ�ȫ״̬\n\n");
		printf("��ȫ����Ϊ: ");
		for (int i = 0; i < processNum; i++)
		{
			printf("P%d ", safeSeries[i]);
		}
		printf("\n\n\n");
		return 1;
	}
	else
	{
		printf("ϵͳ���ڲ���ȫ״̬\n\n");
		return 0;

	}

}

void Banker_Algorithm(int process)                            //���м��㷨
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
		printf("������Դû������Դ�����ֵ\n\n");
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
			printf("���㹻�Ŀ�������Դ,ϵͳ��̽�Ž���Դ�����P%d\n\n", process);
			for (int i = 0; i < resourceNum; i++)
			{
				need[process][i] = need[process][i] - requests[i];
				allocation[process][i] = allocation[process][i] + requests[i];
				available[i] = available[i] - requests[i];
			}
			result = safe_Algorithm();
			if (result == 1)
			{
				printf("ϵͳ��ȫ, ��ʽ����Դ�����P%d\n\n", process);
			}
			else
			{
				for (int i = 0; i < resourceNum; i++)
				{
					need[process][i] = need[process][i] + requests[i];
					allocation[process][i] = allocation[process][i] - requests[i];
					available[i] = available[i] + requests[i];
				}
				printf("ϵͳ����ȫ���˴η�������\n\n");
			}
		}
		else
		{
			printf("�����㹻��Դ,P%d������ȴ�\n\n", process);
		}
	}
	else
	{
		printf("������Դ���Ѿ��������������������ֵ\n\n");
	}

}

void show_resource()										//��ʾϵͳ��Դ
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
}

void input_resource()										//������Դ
{
	printf("�����������: ");
	scanf_s("%d", &processNum);
	printf("��������Դ��: ");
	scanf_s("%d", &resourceNum);
	printf("\n�����������Դ����Available: \n");
	for (int i = 0; i < resourceNum; i++)
	{
		scanf_s("%d", &available[i]);
	}
	printf("\n��������������Max: \n");
	for (int i = 0; i < processNum; i++)
	{
		for (int j = 0; j < resourceNum; j++)
		{
			scanf_s("%d", &maxRequest[i][j]);
		}
	}
	printf("\n����������Allocation: \n");
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
		printf("******************************************************************************************\n\n");
		printf("***********************************��ӭʹ�����м��㷨*************************************\n\n");
		printf("\n1.������Դ\n2.���м��㷨\n3.��ȫ���㷨\n4.��ʾϵͳ��Դ\n0.�˳�\n\n");
		printf("******************************************************************************************\n\n");
		printf("���������ѡ��: ");
		scanf_s("%d", &choose);
		if (choose == 2)
		{
			if(resourceNum != 0 && processNum != 0)
			{ 
				printf("��������Ľ���: ");
				scanf_s("%d", &process);
				for (int i = 0; i < resourceNum; i++)
				{
					printf("����requests����%d����Դ: ", i);
					scanf_s("%d", &requests[i]);
				}
				Banker_Algorithm(process);
			}
			else
			{
				printf("��ǰϵͳ����Դ�������Դ���������㷨\n\n");
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
				printf("��ǰϵͳ����Դ�������Դ���������㷨\n\n");
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

		if (choose == 0)
		{
			break;
		}
	}
}