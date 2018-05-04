#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <istream>
#include <ostream>
#include <stdio.h>
#include <conio.h>
void Insert(struct node *b, struct node *a);
unsigned int against(unsigned int j,  unsigned int N[]);
#define MAX 4000
unsigned int N[MAX] = { 0 };//0��  1�ǿ�  2������  3�Ǳ� 
int NUM = 0;//��¼��ϵ�˸���
int NUM2 = 0;//����������
int NUM3 = 0;//�Ǳ����
char password[] = "123456";//��½����
int chongtudizhi[60][50];
using namespace std;
//��ϣ��ַ���� ����ȡ�� �ַ���
//��ϣ���Һ���
//��ϣ���뺯��
//��ϣɾ������
//��ϣ�޸ĺ���
//��ͻ���� ���ŵ�ַ��
struct node
{
	char name[20];//�洢����
	long long int phone;//�洢�绰
	string adress;//�洢��ַ
	int chongfu = 0;//0��ʾ��ϵ��û�������������ʾ������  ����Ϊ1 2 3....
	struct node *next=NULL;//�ڵ�ָ�룬�����������ϵ�� �����½ڵ㣬ָ��ָ��������ϵ��
};
struct node1
{
	string name;
	long long number;
};

//��ϣ�㷨���ɵ�ַ ����ȡ�� ��ͻ����Ϊ���ŵ�ַ��
unsigned int BKDRHash(char *str)
{
	unsigned int seed = 131313;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash*seed + (*str++);
	}
	return hash % 3989;
}

//������ϣ��
void createhash(int n,struct node *a)
{
	node temp[100];//Ϊ���������鷳 ÿ��ֻ��������ʮ����������
	for (int i = 0; i < n; i++)
	{
		cout << "�������ӵ�" << i + 1 << "λ��ϵ��" << endl;
		cout << "����������:";
		cin >> temp[i].name;
		cout << endl;
		cout << "�������ֻ��ţ�";
		cin >> temp[i].phone;
		cout << endl;
		cout << "�������ַ��";
		cin >> temp[i].adress;
		//unsigned int j = BKDRHash(temp[i].name);
		//if (N[j] != 0)j = against(j,N);//��ͻ����
		//N[j] = 1;
		//NUM++;
		//cout << j << endl;
		//a[j] = temp[i];
		Insert(temp, a);
	}
	cout << "  " << n << "λ��ϵ�����ӳɹ�" << endl;
}

bool un(char a[], char b[])//�ж����������Ƿ����
{
	for (int i = 0; i < 20; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

//��ϣ����     �½���ϵ��//�ɹ�
void Insert(struct node *b,struct node *a)
{
	node temp[1];
	temp[0] = *b;
	unsigned int j = BKDRHash(temp[0].name);
	if (N[j] != 0 && !un(temp[0].name, a[j].name)) {
		
		cout << "��ͻ��ϢΪ��" << endl;
		cout << a[j].name << " " << a[j].phone << " " << a[j].adress << endl;
		cout << "Ҫ���ӵ���ϢΪ��" << endl;
		cout << temp[0].name << " " << temp[0].phone << " " << temp[0].adress << endl;
		j = against(j, N);//��ͻ����
	}
	if (N[j] == 1||N[j]==2||N[j]==3)
	{
		cout << "��ϵ�� " << temp[0].name << " �Ѵ���" << endl;
		cout << "�ظ���ϵ����ϢΪ��" << endl;
		if (a[j].chongfu == 0)
		{
			cout << " " << a[j].name;
			//cout << a[j].chongfu;
			cout << "    " << a[j].phone;
			cout << "    " << a[j].adress;
			cout << endl;
		}
		else if(a[j].chongfu>0)
		{
			node *xt = &a[j];
			while ((xt) != NULL)
			{
				cout << " " << (*xt).name;
				cout << (*xt).chongfu;
				cout << "    " << (*xt).phone;
				cout << "    " << (*xt).adress;
				cout << endl;
				xt = (*xt).next;
			}
		}
		
		cout << "�Ƿ񸲸���ϵ��  1.��������   2.�������½�  3.����ָ��������ϵ��" << endl;
		cout << "����������ѡ��";
		int t;
		cin >> t;
		if (t == 1)
		{
			goto next;
		}
		else if (t == 2)
		{
			node *tmp1;
			tmp1 = new node;
			strcpy(tmp1->name, temp[0].name);
			//tmp1->name=temp[0].name
			//tmp1->name = b->name;
			//(*tmp1).name = *(*b).name;//&temp[0].name;
			(*tmp1).phone = temp[0].phone;
			tmp1->adress.swap(temp[0].adress);//(*tmp1).adress = temp[0].adress;
			tmp1->next = NULL;
			if (a[j].chongfu == 0)
			{
				a[j].next = tmp1;
				a[j].chongfu = 1;
				(*tmp1).chongfu = 2;
				NUM++;
			}
			else if (a[j].chongfu > 0)
			{
				node *temp7 = &a[j];
				while ((*temp7).next != NULL)
				{
					temp7 = (*temp7).next;
				}
				(*temp7).next = tmp1;
				(*tmp1).chongfu = (*temp7).chongfu + 1;
				NUM++;
			}
		}
		else if (t == 3)
		{
			node *tmp1;
			tmp1 = new node;
			strcpy(tmp1->name, temp[0].name);
			(*tmp1).phone = temp[0].phone;
			tmp1->adress.swap(temp[0].adress);//(*tmp1).adress = temp[0].adress;
			tmp1->next = NULL;
			if (a[j].chongfu == 0)goto next;
			else if (a[j].chongfu > 0)
			{
				cout << "������Ҫ���ǵ���ϵ�����ֺ��������:";
				int qq = 0;
				cin >> qq;
				node *xt = &a[j];
				while ((xt) != NULL)
				{
					if (xt->chongfu == qq)
					{
						strcpy(xt->name, temp[0].name);
						xt->phone = temp[0].phone;
						xt->adress.swap(temp[0].adress);
					}
					xt = (*xt).next;
				}
			}
		}
	}
	else
	{
		next:
		N[j] = 1;
		NUM++;
		a[j] = temp[0];
	}
	
	cout << "���ӳɹ�" << endl;
}

//��ϣɾ��  ɾ��������ϵ��(�ɹ���
void Delete(unsigned int i,struct node *a)
{
	if (a[i].chongfu == 0)
	{
		*(a[i].name) = NULL;
		a[i].phone = 0;
		N[i] = 0;
	}
	else if (a[i].chongfu > 0)
	{
		cout << "�ҵ�������ϵ�ˣ�" << endl;
		node *xt = &a[i];
		node *xy = &a[i];
		while ((xt) != NULL)
		{
			cout << " " << (*xt).name;
			cout << (*xt).chongfu;
			cout << "    " << (*xt).phone;
			cout << "    " << (*xt).adress;
			cout << endl;
			xt = (*xt).next;
		}
		cout << "������Ҫ���ǵ���ϵ�����ֺ�������֣�";
		int qq = 0;
		cin >> qq;
		//node *xt1 = &a[i];
		//while ((xt1) != NULL)
		//{
		if (qq == 1)
		{
			xt = &a[i];
			strcpy(xt->name, xt->next->name);
			xt->phone = xt->next->phone;
			xt->adress.swap(xt->next->adress);
			node *xt0 = xt->next;
			xt->next = xt->next->next;
			node *xt01 = xt0->next;
			free(xt0);
			while (xt01 != NULL)
			{
				xt01->chongfu--;
				xt01 = xt01->next;
			}
		}
		if (qq > 1)
		{
			while (xy != NULL)
			{
				if (qq == xy->chongfu + 1)
				{
					node *xt03 = xy->next;
					xy->next = xt03->next;
					free(xt03);
					//break;
				}
				if (xy->chongfu > qq)
					xy->chongfu--;
				xy = xy->next;
			}
		}
	}
	cout << "ɾ���ɹ�" << endl;
	
	NUM--;
}
//��ϣ�޸� �޸���ϵ����Ϣ
void Update(unsigned int i, struct node *a)
{
	//char name1[20];
	long long int newphone;
	string newaddress;
	cout << "��ѡ��Ҫ�޸ĵ���Ϣ" << endl;
	cout << "1.����  2.�绰  3.��ַ  0.����" << endl;
	int flag2;
	cin >> flag2;
	switch (flag2)
	{
	case 1:
	{
		node a1;
		cout << "�������µ�������";
	cin >> a1.name;
	//strcpy_s(a1.name, name1);//���鿽��
	/**a1.name = *name1;*/
	a1.phone = a[i].phone;
	a1.adress = a[i].adress;
	Delete(i, a);
	Insert(&a1, a);
	}
		return;
	case 2:
		cout << "�������µĵ绰���룺";//�ɹ�
		cin >> newphone;
		a[i].phone = newphone;
		return;
	case 3:
		cout << "�������µĵ�ַ��";//�ɹ�
		cin >> newaddress;
		a[i].adress = newaddress;
		return;
	case 0:
		return;
	}
}

//��ϣ����  
/*������ϵ�� �粻���� ��ʾ�Ƿ����  
  �������ʾ�Ƿ�ɾ��
  �����޸���Ϣ*/
void Look(struct node *a)
{
	clock_t begin, end;
	node temp;
	system("cls");
	cout << "----------������ϵ��----------" << endl;
	cout << "������Ҫ���ҵ�������";
	cin >> temp.name;
	begin = clock();
	unsigned int j = BKDRHash(temp.name);
	if (!strcmp(a[j].name,temp.name) ){//un(a[j].name, temp.name)    strcmp()���� �Ƚ�����  ��ͬ����0
		cout << "��Ҫ���ҵ���ϵ����ϢΪ��" << endl;
		cout << "-------" << endl;
		if (a[j].chongfu == 0)
		{
			cout << " | ������" << a[j].name << endl;
			cout << " | �绰��" << a[j].phone << endl;
			cout << " | ��ַ��" << a[j].adress << endl;
		}
		else if (a[j].chongfu > 0)
		{
			node * xz = &a[j];
			while (xz != NULL)
			{
				cout << " | ������" << xz->name << xz->chongfu << endl;
				cout << " | �绰��" << xz->phone << endl;
				cout << " | ��ַ��" << xz->adress << endl;
				cout << endl;
				xz = xz->next;
			}
		}
		cout << "-------" << endl;
		end = clock();
		double cost = (double)(end - begin) / CLOCKS_PER_SEC;

		cout << "���ҳɹ�"<<"  ��ʱ��"<<cost<<endl;
		if (N[j] == 2)
			cout << "����ϵ���Ѽ��������" << endl;
		else if (N[j] == 3)
			cout << "��Ϊ�Ǳ���ϵ��" << endl;
		cout << "��ѡ����Ӧ�Ĳ���";
		cout << endl;
		cout << "1.�޸ĵ�ǰ��ϵ����Ϣ";
		cout << endl;
		cout << "2.ɾ����ǰ��ϵ��";//�ɹ�
		cout << endl;
		cout << "3.���������" << endl;
		cout << "4.�Ƴ�������" << endl;
		cout << "5.����Ϊ�Ǳ���ϵ��" << endl;
		cout << "6.ȡ���Ǳ���ϵ��" << endl;
		cout << "0.����";
		cout << endl;
		int flag1;
		cin >> flag1;
		switch (flag1)
		{
		case 3:
			N[j] = 2;
			NUM2++;
			cout << "����������ɹ�" << endl;
			break;
		case 4:
			N[j] = 1;
			NUM2--;
			cout << "�Ƴ��������ɹ�" << endl;
			break;
		case 5:
			N[j] = 3;
			NUM3++;
			cout << "�����Ǳ�ɹ�" << endl;
			break;
		case 6:
			N[j] = 1;
			NUM3--;
			cout << "ȡ���Ǳ�ɹ�" << endl;
			break;
		case 2:

			//ɾ��
			cout << "ɾ������ϵ��(���Գɹ���" << endl;//��һ��switch�ж���ɾ�������޸�
			Delete(j, a);
			return;
		case 1:
			cout << "�޸ĸ���ϵ����Ϣ" << endl;//
			Update(j, a);
			//��ϣ�޸ĺ���
			//�޸�
			return;
		case 0:
			return;
		}
	}
	else
	{
		int p = 1;
		{//��ͻ����
			unsigned int H = j;
			while (p <= 100)
			{
				while (N[H] == 0&&p<=100)
				{
					H = (H + p * 10) % MAX;
					//cout << "��ͻ " << p << " ��δ�ҵ�" << endl;
					p++;
				}
				if (!strcmp(a[H].name, temp.name))//(un(a[H].name, temp.name))
				{
					cout<< "��ͻ " << p << " ���ҵ�" << endl;
					cout << "����ϵ����Ϣλ:" << endl;
					cout << a[H].name << " " << a[H].phone << " " << a[H].adress;
					cout << endl;
					system("pause"); goto end;
				}
				else
				{
					//cout << "��ͻ " << p << " ��δ�ҵ�" << endl;
					H = (H + p * 10) % MAX;
					p++;
				}
			}
		}
		cout << "��ͻ " << p << " ��δ�ҵ�" << endl;
		cout << "�������ҵ���Ϣ������" << endl;
		cout << "�Ƿ�Ҫ������Ϊ����ϵ�ˣ������롮y' ���� 'n'" << endl;
		char flag;
		cin >> flag;
		switch (flag)
		{
		case 'y':
		{
			//strcpy_s(temp.name, b);
			//*(temp.name) = *b;
			cout << "������������Ϊ��" << temp.name << endl;
			cout << "����������ϵ���ֻ��ţ�";
			cin >> temp.phone;
			cout << endl;
			cout << "����������ϵ�˵�ַ��";
			cin >> temp.adress;
			cout << endl;
			Insert(&temp, a);
		}
		break;
		case 'n':
			return;
		}
	}
end:;
}
/*
int Serchaccount(int id,struct account *aa)//����ID��ѯ���û��Ƿ����
{
	int m = -1;
	for (int i = 0; i <100 ; i++)//���洢100���˺���Ϣ������Щ��Ϣ�в��ҵ�IDƥ�����Ϣ
	{
		if (aa[i].id == id)//��I���˺���Ϣƥ��
			return i;
	}
	return m;
}
*/
void savenumber(struct node *a)//���绰��Ϣ�������ļ�
{
	ofstream fout("books.txt");
	if (fout)
	{
		fout << NUM << endl;//data�ṹ���ݵĴ�С(���е绰�ĸ���)
		int haha = 0;
		for (int i = 0; i < NUM; i++)
		{
			for (int j = haha; j < MAX; j++)
			{
				if (N[j] == 1||N[j]==3||N[j]==2)
				{
					if (a[j].chongfu == 0)
					{
						fout << a[j].name << " " << a[j].phone << " " << a[j].adress << endl;
						haha = j + 1;
						break;
					}
					else if (a[j].chongfu > 0)
					{
						node *xt = &a[j];
						while ((xt) != NULL)
						{
							fout << xt->name << " " << xt->phone << " " << xt->adress << endl;
							xt = (*xt).next;
							haha = j + 1;
						}
						break;
					}
				}
			}
			
		}
		fout.close();
	}
	cout << "�����ɹ�" <<"    �ļ�·��Ϊ��\\�绰��\\�绰��\\books.txt "<< endl;
}

void getfile1(struct node *a)//���ļ���������ϵ����Ϣ
{
	/*������ȡ��ϵ����Ϣ  �����½���ϵ�˺������� ����info  ͬʱ��ϵ�˸���+1*/
	ifstream fin("books1.txt");
	int num = 0;
	if (fin)
	{
		fin >> num; //cout << num;
		node haha;
		for (int i = 0; i < num; i++)
		{
			fin >> haha.name >> haha.phone >> haha.adress;
			unsigned int j = BKDRHash(haha.name);
			cout << "�� " << i + 1 << " λ��ϵ��";
			Insert(&haha, a);
		}
	}
	fin.close();
	cout << "����ɹ�" << endl;
	cout << "��������" << num << "λ��ϵ����Ϣ" << endl;
}
void getfile2(struct node *a)//���ļ���������ϵ����Ϣ
{
	/*������ȡ��ϵ����Ϣ  �����½���ϵ�˺������� ����info  ͬʱ��ϵ�˸���+1*/
	ifstream fin("books2.txt");
	int num = 0;
	if (fin)
	{
		fin >> num; //cout << num;
		node haha;
		for (int i = 0; i < num; i++)
		{
			fin >> haha.name >> haha.phone >> haha.adress;
			unsigned int j = BKDRHash(haha.name);
			cout << "�� " << i + 1 << " λ��ϵ��";
			Insert(&haha, a);
		}
	}
	fin.close();
	cout << "����ɹ�" << endl;
	cout << "��������" << num << "λ��ϵ����Ϣ" << endl;
}

void findphone(struct node *a)//���������
{
	int success = 0;
	cout << "������Ҫ��ѯ�ĺ���:";
	long long int fphone = 0;
	cin >> fphone;
	for (int i = 0; i < MAX; i++)
	{
		if (N[i] == 1)
		{
			if (a[i].phone == fphone) {
				cout << "���ҳɹ�" << endl;
				success = 1;
			
				cout << "-------" << endl;
				cout << "  ������" << a[i].name << endl;
				cout << "  �绰��" << a[i].phone << endl;
				cout << "  ��ַ��" << a[i].adress << endl;
				if (N[i] == 2)
					cout << "�����Ѽ��������" << endl;
				else if (N[i] == 3)
					cout << "��Ϊ�Ǳ���ϵ��" << endl;
				cout << "��ѡ����Ӧ�Ĳ���";
				cout << endl;
				cout << "1.�޸ĵ�ǰ��ϵ����Ϣ";
				cout << endl;
				cout << "2.ɾ����ǰ��ϵ��";//�ɹ�
				cout << endl;
				cout << "3.���������" << endl;
				cout << "4.�Ƴ�������" << endl;
				cout << "5.����Ϊ�Ǳ���ϵ��" << endl;
				cout << "6.ȡ���Ǳ���ϵ��" << endl;
				cout << "0.����";
				cout << endl;
				int flag1;
				cin >> flag1;
				switch (flag1)
				{
				case 3:
					N[i] = 2;
					NUM2++;
					cout << "����������ɹ�" << endl;
					break;
				case 4:
					N[i] = 1;
					NUM2--;
					cout << "�Ƴ��������ɹ�" << endl;
					break;
				case 5:
					N[i] = 3;
					NUM3++;
					cout << "�����Ǳ�ɹ�" << endl;
					break;
				case 6:
					N[i] = 1;
					NUM3--;
					cout << "ȡ���Ǳ�ɹ�" << endl;
					break;
				case 2:

					//ɾ��
					cout << "ɾ������ϵ��(���Գɹ���" << endl;//��һ��switch�ж���ɾ�������޸�
					Delete(i, a);
					return;
				case 1:
					cout << "�޸ĸ���ϵ����Ϣ" << endl;//
					Update(i, a);
					//��ϣ�޸ĺ���
					//�޸�
					return;
				case 0:
					return;
				}
			}
		}
	}
	if (success == 0)
	{
		cout << "�޴˺���" << endl;
		cout << "�Ƿ�Ҫ������Ϊ����ϵ�ˣ������롮y' ���� 'n'" << endl;
		char flag;
		cin >> flag;
		
		if(flag=='y')
		{
			node temp;
			temp.phone = fphone;
			cout << "��Ҫ���ӵ���ϵ�˺���Ϊ��" << temp.phone << endl;
			cout << "����������ϵ��������" <<endl;
			cin >> temp.name;
			cout << "����������ϵ�˵�ַ��";
			cin >> temp.adress;
			cout << endl;
			Insert(&temp, a);
		}
		
		else
			return;
		
	}
}

void starphone(struct node *a)//�Ǳ���ϵ���б�
{
	cout << "�����Ǳ���ϵ��" << endl;
	for (int i = 0; i < MAX; i++)
	{
		if (N[i] == 3)
		{
			cout << " " << a[i].name << "  " << a[i].phone << "  " << a[i].adress << endl;
		}
	}
	cout << "����" << NUM3 << "λ�Ǳ���ϵ��" << endl;
}

int main()
{
	//��ʼ������   �ɺ���
	node1 nologin[7];
	nologin[0].name = "����"; nologin[0].number = 110;
	nologin[1].name = "����"; nologin[1].number = 120;
	nologin[2].name = "��"; nologin[2].number = 119;
	nologin[3].name = "�¹�"; nologin[3].number = 122;
	nologin[4].name = "����"; nologin[4].number = 12121;
	nologin[5].name = "��ʱ"; nologin[5].number = 12117;
	nologin[6].name = "��ѯ"; nologin[6].number = 114;
	//�����½  ���û���˺� ����
	while (10)
	{
		system("cls");
		cout << "��ӭʹ�õ绰����ϵͳ�����½��ʹ�ã�δ��½ֻ�ܽ���ÿ�ģʽ" << endl;
		cout << "1.���������½" << endl;
		cout << "2.�ÿ�ģʽ��½" << endl;
		cout << "0.�Ƴ�" << endl;
		cout << endl;
		cout << "���������Ĳ�����";
		int login = 0;
		cin >> login;
		if (login == 0)exit(0);
		else if (login == 2)
		{
			//����ÿ�ģʽ�����Բ�ѯ��������
			system("cls");
			cout << "�����ڷÿ�ģʽ�����Բ�ѯ��������" << endl;
			
			cout << "�ɲ��������Ϊ��" << endl;
			for (int i = 0; i < 6; i++)
			{
				cout << nologin[i].name << "  " << nologin[i].number << endl;
			}
			system("pause");
		}
		else if (login == 1)
		{
			cout << "���������루���飺�����ʼΪ123456" << endl;
			cout << "���룺";
			int kk = 1;//0��־�������  1��־�ɹ�
			char passwordlogin[7];//��strcmp()ƥ��
			for (int i = 0; i < 7; i++)
			{
				passwordlogin[i] = _getch();
				cout << "*";
			}
			for (int i = 0; i < 6; i++)
			{
				if (password[i] != passwordlogin[i])
				{
					kk = 0; break;
				}
			}
			cout << endl;
			if (kk==1)
			{
				//����Ϊ�ɹ������û�����
				node info[MAX];
				while (1)
				{
					system("cls");
					cout << "----------��ӭʹ��----------" << endl;
					cout << "1.�½��绰��" << endl;
					cout << "2.������������ϵ��" << endl;
					cout << "9.�����������ϵ��" << endl;
					cout << "3.�½���ϵ��" << endl;
					cout << "4.�޸���ϵ��" << endl;
					cout << "5.ɾ����ϵ��" << endl;
					cout << "6.��ʾ������ϵ��" << endl;
					cout << "7.�������ļ�" << endl;
					cout << "8.���ļ�������ϵ��(��һ�δ�����ļ����룺�������ŵ�ַ��ͻ���ݣ�" << endl;
					cout << "80.���ļ�������ϵ�ˣ��ڶ��δ�����ļ����룺��������ַ����ͻ���ݣ�" << endl;
					cout << "10.�������б�" << endl;
					cout << "101.����������" << endl;
					cout << "11.�Ǳ���ϵ���б�" << endl;
					cout << "111.�����Ǳ���ϵ��" << endl;
					cout << "0.�Ƴ�" << endl;
					cout << "----------------------------" << endl;
					cout << "��������Ĳ�����";
					int caozuo;
					cin >> caozuo;
					cout << endl;
					switch (caozuo)
					{
					case 1:cout << "������Ҫ���ӵ���ϵ����������ÿ�����Ӳ�����10������";
						int n;
						cin >> n;
						createhash(n, info);
						system("pause");
						break;
					case 2:Look(info); system("pause"); break;
					case 3: {node newlian;
						cout << "������ϵ����Ϣ:" << endl;
						cout << " ������"; cin >> newlian.name;
						cout << " �绰��"; cin >> newlian.phone;
						cout << " ��ַ��"; cin >> newlian.adress;
						Insert(&newlian, info); }system("pause"); break;
					case 4:cout << "������Ҫ�޸ĵ���ϵ��������";
					{char name3[20];
					cin >> name3;
					unsigned int x = BKDRHash(name3);
					Update(x, info); }
					system("pause");
					break;
					case 5:cout << "������Ҫɾ������ϵ��������";
					{char name3[20];
					cin >> name3;
					unsigned int x = BKDRHash(name3);
					Delete(x, info); }
					system("pause");
					break;
					case 6:cout << "---------������ϵ��---------" << endl;
						cout << "��ǰ����" << NUM << "λ��ϵ����Ϣ" << endl;
						cout << "\t|����\t\t\t\t\t|�绰\t\t\t\t\t|��ַ";
						cout << endl;
						cout << endl;
						{for (int i = 0; i < MAX; i++)
						{
							if (N[i] == 1 || N[i] == 3)
							{
								if (info[i].chongfu == 0) {
									cout << "\t|" << info[i].name;
									cout << "\t\t\t\t\t|" << info[i].phone;
									cout << "\t\t\t\t|" << info[i].adress;
									cout << endl;
								}
								else if (info[i].chongfu > 0)
								{
									node *xt = &info[i];
									while ((xt) != NULL)
									{
										cout << "\t|" << (*xt).name;
										cout << (*xt).chongfu;
										cout << "\t\t\t\t|" << (*xt).phone;
										cout << "\t\t\t\t|" << (*xt).adress;
										cout << endl;
										xt = (*xt).next;
									}
								}
							}
						}}
						cout << NUM3 << "λ�Ǳ���ϵ��" << "    " << NUM2 << "λ��������ϵ��" << endl;
						cout << endl; system("pause"); break;
					case 7:
					{
						savenumber(info);
					}
					system("pause");
					break;
					case 8:
					{
						//���ļ�������ϵ��
						getfile1(info);
					}
					system("pause");
					break;
					case 9:
					{
						//���������
						findphone(info);
					}
					system("pause");
					break;
					case 80:
						getfile2(info);
						system("pause");
						break;
					case 10:
					{
						//�������б�
						cout << "�������б�" << endl;
						for (int i = 0; i < MAX; i++)
						{
							if (N[i] == 2)
							{
								cout << info[i].name << "  " << info[i].phone << "  " << info[i].adress << endl;
							}
						}
						cout << "����������" << NUM2 << "λ��ϵ��" << endl;
					}
					system("pause");
					break;
					case 101:
					{
						//����������
						ofstream bfout("blackname.txt");
						if (bfout)
						{
							bfout << NUM2 << endl;//data�ṹ���ݵĴ�С(���е绰�ĸ���)
							int haha1 = 0;
							for (int i = 0; i < NUM2; i++)
							{
								for (int j = haha1; j < MAX; j++)
								{
									if (N[j] == 2)
									{
										bfout << info[j].name << " " << info[j].phone << " " << info[j].adress << endl;
										haha1 = j + 1;
										break;
									}
								}

							}
							bfout.close();
							cout << "�����������ɹ�" << "    �ļ�·��Ϊ��\\�绰��\\�绰��\\blackname.txt" << endl;
						}
					}
					system("pause");
					break;
					case 11:
					{
						//�Ǳ���ϵ���б�
						starphone(info);
					}
					system("pause");
					break;
					case 111:
					{
						//�����Ǳ�
						ofstream sfout("starname.txt");
						if (sfout)
						{
							sfout << NUM3 << endl;//data�ṹ���ݵĴ�С(���е绰�ĸ���)
							int haha3 = 0;
							for (int i = 0; i < NUM3; i++)
							{
								for (int j = haha3; j < MAX; j++)
								{
									if (N[j] == 3)
									{
										sfout << info[j].name << " " << info[j].phone << " " << info[j].adress << endl;
										haha3 = j + 1;
										break;
									}
								}

							}
							sfout.close();
							cout << "�����Ǳ�ɹ�" << "    �ļ�·��Ϊ��\\�绰��\\�绰��\\starname.txt" << endl;
						}
					}
					system("pause");
					break;
					case 0:exit(1);
					default:cout << "�������" << endl;
					}
				}
			}
			else
			{
				cout << "�������" << endl;
				system("pause");
			}
		}
		else
		{
			cout << "ָ���������" << endl;
			system("pause");
		}
	}
	return 0;
}

//��ͻ����  Ϊ��ͻ�����½��ռ�  ÿ�β�����  �ռ��� ����ҳ�ͻ�ռ�
//������ͻ  ����ַ��

//���ŵ�ַ��   ����ͬ����ϣ������ͻʱ����
unsigned int against(unsigned int j,unsigned int N[])
{
	int i = 1;
	unsigned int H=j;
	while (N[H] != 0&&(i)<=100)
		/*��Hλ����Ԫ��ʱ����ͻ �������� 
		  ��������ͻ��������100ʱ����������*/
	{
		cout << "��ͻ  ����  " << i << "��" << endl;
		H = (H + (i) * 10) % MAX;
		i++; 
	}
	return H;
}

/*����ͻ�ĵ�ַ����һ������*/