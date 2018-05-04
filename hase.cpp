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
unsigned int N[MAX] = { 0 };//0空  1非空  2黑名单  3星标 
int NUM = 0;//记录联系人个数
int NUM2 = 0;//黑名单个数
int NUM3 = 0;//星标个数
char password[] = "123456";//登陆密码
int chongtudizhi[60][50];
using namespace std;
//哈希地址函数 除留取余 字符串
//哈希查找函数
//哈希插入函数
//哈希删除函数
//哈希修改函数
//冲突处理 开放地址法
struct node
{
	char name[20];//存储姓名
	long long int phone;//存储电话
	string adress;//存储地址
	int chongfu = 0;//0表示联系人没有重名，非零表示有重名  依次为1 2 3....
	struct node *next=NULL;//节点指针，如果有重名联系人 增加新节点，指针指向重名联系人
};
struct node1
{
	string name;
	long long number;
};

//哈希算法生成地址 除留取余 冲突处理为开放地址法
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

//构建哈希表
void createhash(int n,struct node *a)
{
	node temp[100];//为避免输入麻烦 每次只允许输入十个以内数据
	for (int i = 0; i < n; i++)
	{
		cout << "正在添加第" << i + 1 << "位联系人" << endl;
		cout << "请输入姓名:";
		cin >> temp[i].name;
		cout << endl;
		cout << "请输入手机号：";
		cin >> temp[i].phone;
		cout << endl;
		cout << "请输入地址：";
		cin >> temp[i].adress;
		//unsigned int j = BKDRHash(temp[i].name);
		//if (N[j] != 0)j = against(j,N);//冲突处理
		//N[j] = 1;
		//NUM++;
		//cout << j << endl;
		//a[j] = temp[i];
		Insert(temp, a);
	}
	cout << "  " << n << "位联系人添加成功" << endl;
}

bool un(char a[], char b[])//判断两个数组是否相等
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

//哈希插入     新建联系人//成功
void Insert(struct node *b,struct node *a)
{
	node temp[1];
	temp[0] = *b;
	unsigned int j = BKDRHash(temp[0].name);
	if (N[j] != 0 && !un(temp[0].name, a[j].name)) {
		
		cout << "冲突信息为：" << endl;
		cout << a[j].name << " " << a[j].phone << " " << a[j].adress << endl;
		cout << "要添加的信息为：" << endl;
		cout << temp[0].name << " " << temp[0].phone << " " << temp[0].adress << endl;
		j = against(j, N);//冲突处理
	}
	if (N[j] == 1||N[j]==2||N[j]==3)
	{
		cout << "联系人 " << temp[0].name << " 已存在" << endl;
		cout << "重复联系人信息为：" << endl;
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
		
		cout << "是否覆盖联系人  1.覆盖所有   2.不覆盖新建  3.覆盖指定重名联系人" << endl;
		cout << "请输入您的选择：";
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
				cout << "请输入要覆盖的联系人名字后面的数字:";
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
	
	cout << "添加成功" << endl;
}

//哈希删除  删除已有联系人(成功）
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
		cout << "找到以下联系人：" << endl;
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
		cout << "请输入要覆盖的联系人名字后面的数字：";
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
	cout << "删除成功" << endl;
	
	NUM--;
}
//哈希修改 修改联系人信息
void Update(unsigned int i, struct node *a)
{
	//char name1[20];
	long long int newphone;
	string newaddress;
	cout << "请选择要修改的信息" << endl;
	cout << "1.姓名  2.电话  3.地址  0.返回" << endl;
	int flag2;
	cin >> flag2;
	switch (flag2)
	{
	case 1:
	{
		node a1;
		cout << "请输入新的姓名：";
	cin >> a1.name;
	//strcpy_s(a1.name, name1);//数组拷贝
	/**a1.name = *name1;*/
	a1.phone = a[i].phone;
	a1.adress = a[i].adress;
	Delete(i, a);
	Insert(&a1, a);
	}
		return;
	case 2:
		cout << "请输入新的电话号码：";//成功
		cin >> newphone;
		a[i].phone = newphone;
		return;
	case 3:
		cout << "请输入新的地址：";//成功
		cin >> newaddress;
		a[i].adress = newaddress;
		return;
	case 0:
		return;
	}
}

//哈希查找  
/*查找联系人 如不存在 提示是否插入  
  如存在提示是否删除
  或者修改信息*/
void Look(struct node *a)
{
	clock_t begin, end;
	node temp;
	system("cls");
	cout << "----------查找联系人----------" << endl;
	cout << "请输入要查找的人名：";
	cin >> temp.name;
	begin = clock();
	unsigned int j = BKDRHash(temp.name);
	if (!strcmp(a[j].name,temp.name) ){//un(a[j].name, temp.name)    strcmp()函数 比较数组  相同返回0
		cout << "您要查找的联系人信息为：" << endl;
		cout << "-------" << endl;
		if (a[j].chongfu == 0)
		{
			cout << " | 姓名：" << a[j].name << endl;
			cout << " | 电话：" << a[j].phone << endl;
			cout << " | 地址：" << a[j].adress << endl;
		}
		else if (a[j].chongfu > 0)
		{
			node * xz = &a[j];
			while (xz != NULL)
			{
				cout << " | 姓名：" << xz->name << xz->chongfu << endl;
				cout << " | 电话：" << xz->phone << endl;
				cout << " | 地址：" << xz->adress << endl;
				cout << endl;
				xz = xz->next;
			}
		}
		cout << "-------" << endl;
		end = clock();
		double cost = (double)(end - begin) / CLOCKS_PER_SEC;

		cout << "查找成功"<<"  用时："<<cost<<endl;
		if (N[j] == 2)
			cout << "此联系人已加入黑名单" << endl;
		else if (N[j] == 3)
			cout << "此为星标联系人" << endl;
		cout << "请选择相应的操作";
		cout << endl;
		cout << "1.修改当前联系人信息";
		cout << endl;
		cout << "2.删除当前联系人";//成功
		cout << endl;
		cout << "3.加入黑名单" << endl;
		cout << "4.移除黑名单" << endl;
		cout << "5.添加为星标联系人" << endl;
		cout << "6.取消星标联系人" << endl;
		cout << "0.返回";
		cout << endl;
		int flag1;
		cin >> flag1;
		switch (flag1)
		{
		case 3:
			N[j] = 2;
			NUM2++;
			cout << "加入黑名单成功" << endl;
			break;
		case 4:
			N[j] = 1;
			NUM2--;
			cout << "移除黑名单成功" << endl;
			break;
		case 5:
			N[j] = 3;
			NUM3++;
			cout << "添加星标成功" << endl;
			break;
		case 6:
			N[j] = 1;
			NUM3--;
			cout << "取消星标成功" << endl;
			break;
		case 2:

			//删除
			cout << "删除该联系人(调试成功）" << endl;//用一个switch判断是删除还是修改
			Delete(j, a);
			return;
		case 1:
			cout << "修改该联系人信息" << endl;//
			Update(j, a);
			//哈希修改函数
			//修改
			return;
		case 0:
			return;
		}
	}
	else
	{
		int p = 1;
		{//冲突处理
			unsigned int H = j;
			while (p <= 100)
			{
				while (N[H] == 0&&p<=100)
				{
					H = (H + p * 10) % MAX;
					//cout << "冲突 " << p << " 次未找到" << endl;
					p++;
				}
				if (!strcmp(a[H].name, temp.name))//(un(a[H].name, temp.name))
				{
					cout<< "冲突 " << p << " 次找到" << endl;
					cout << "该联系人信息位:" << endl;
					cout << a[H].name << " " << a[H].phone << " " << a[H].adress;
					cout << endl;
					system("pause"); goto end;
				}
				else
				{
					//cout << "冲突 " << p << " 次未找到" << endl;
					H = (H + p * 10) % MAX;
					p++;
				}
			}
		}
		cout << "冲突 " << p << " 次未找到" << endl;
		cout << "您所查找的信息不存在" << endl;
		cout << "是否要添加作为新联系人？请输入‘y' 或者 'n'" << endl;
		char flag;
		cin >> flag;
		switch (flag)
		{
		case 'y':
		{
			//strcpy_s(temp.name, b);
			//*(temp.name) = *b;
			cout << "新添加人名字为：" << temp.name << endl;
			cout << "请输入新联系人手机号：";
			cin >> temp.phone;
			cout << endl;
			cout << "请输入新联系人地址：";
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
int Serchaccount(int id,struct account *aa)//根据ID查询该用户是否存在
{
	int m = -1;
	for (int i = 0; i <100 ; i++)//最多存储100个账号信息，从这些信息中查找到ID匹配的信息
	{
		if (aa[i].id == id)//第I个账号信息匹配
			return i;
	}
	return m;
}
*/
void savenumber(struct node *a)//将电话信息导出到文件
{
	ofstream fout("books.txt");
	if (fout)
	{
		fout << NUM << endl;//data结构数据的大小(所有电话的个数)
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
	cout << "导出成功" <<"    文件路径为：\\电话簿\\电话簿\\books.txt "<< endl;
}

void getfile1(struct node *a)//从文件中添加联系人信息
{
	/*逐条读取联系人信息  调用新建联系人函数处理 存入info  同时联系人个数+1*/
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
			cout << "第 " << i + 1 << " 位联系人";
			Insert(&haha, a);
		}
	}
	fin.close();
	cout << "导入成功" << endl;
	cout << "新添加了" << num << "位联系人信息" << endl;
}
void getfile2(struct node *a)//从文件中添加联系人信息
{
	/*逐条读取联系人信息  调用新建联系人函数处理 存入info  同时联系人个数+1*/
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
			cout << "第 " << i + 1 << " 位联系人";
			Insert(&haha, a);
		}
	}
	fin.close();
	cout << "导入成功" << endl;
	cout << "新添加了" << num << "位联系人信息" << endl;
}

void findphone(struct node *a)//按号码查找
{
	int success = 0;
	cout << "请输入要查询的号码:";
	long long int fphone = 0;
	cin >> fphone;
	for (int i = 0; i < MAX; i++)
	{
		if (N[i] == 1)
		{
			if (a[i].phone == fphone) {
				cout << "查找成功" << endl;
				success = 1;
			
				cout << "-------" << endl;
				cout << "  姓名：" << a[i].name << endl;
				cout << "  电话：" << a[i].phone << endl;
				cout << "  地址：" << a[i].adress << endl;
				if (N[i] == 2)
					cout << "此人已加入黑名单" << endl;
				else if (N[i] == 3)
					cout << "此为星标联系人" << endl;
				cout << "请选择相应的操作";
				cout << endl;
				cout << "1.修改当前联系人信息";
				cout << endl;
				cout << "2.删除当前联系人";//成功
				cout << endl;
				cout << "3.加入黑名单" << endl;
				cout << "4.移除黑名单" << endl;
				cout << "5.添加为星标联系人" << endl;
				cout << "6.取消星标联系人" << endl;
				cout << "0.返回";
				cout << endl;
				int flag1;
				cin >> flag1;
				switch (flag1)
				{
				case 3:
					N[i] = 2;
					NUM2++;
					cout << "加入黑名单成功" << endl;
					break;
				case 4:
					N[i] = 1;
					NUM2--;
					cout << "移除黑名单成功" << endl;
					break;
				case 5:
					N[i] = 3;
					NUM3++;
					cout << "添加星标成功" << endl;
					break;
				case 6:
					N[i] = 1;
					NUM3--;
					cout << "取消星标成功" << endl;
					break;
				case 2:

					//删除
					cout << "删除该联系人(调试成功）" << endl;//用一个switch判断是删除还是修改
					Delete(i, a);
					return;
				case 1:
					cout << "修改该联系人信息" << endl;//
					Update(i, a);
					//哈希修改函数
					//修改
					return;
				case 0:
					return;
				}
			}
		}
	}
	if (success == 0)
	{
		cout << "无此号码" << endl;
		cout << "是否要添加作为新联系人？请输入‘y' 或者 'n'" << endl;
		char flag;
		cin >> flag;
		
		if(flag=='y')
		{
			node temp;
			temp.phone = fphone;
			cout << "您要添加的联系人号码为：" << temp.phone << endl;
			cout << "请输入新联系人姓名：" <<endl;
			cin >> temp.name;
			cout << "请输入新联系人地址：";
			cin >> temp.adress;
			cout << endl;
			Insert(&temp, a);
		}
		
		else
			return;
		
	}
}

void starphone(struct node *a)//星标联系人列表
{
	cout << "所有星标联系人" << endl;
	for (int i = 0; i < MAX; i++)
	{
		if (N[i] == 3)
		{
			cout << " " << a[i].name << "  " << a[i].phone << "  " << a[i].adress << endl;
		}
	}
	cout << "共有" << NUM3 << "位星标联系人" << endl;
}

int main()
{
	//初始化部分   可忽略
	node1 nologin[7];
	nologin[0].name = "报警"; nologin[0].number = 110;
	nologin[1].name = "急救"; nologin[1].number = 120;
	nologin[2].name = "火警"; nologin[2].number = 119;
	nologin[3].name = "事故"; nologin[3].number = 122;
	nologin[4].name = "天气"; nologin[4].number = 12121;
	nologin[5].name = "报时"; nologin[5].number = 12117;
	nologin[6].name = "查询"; nologin[6].number = 114;
	//密码登陆  如果没有账号 创建
	while (10)
	{
		system("cls");
		cout << "欢迎使用电话管理系统，请登陆后使用，未登陆只能进入访客模式" << endl;
		cout << "1.输入密码登陆" << endl;
		cout << "2.访客模式登陆" << endl;
		cout << "0.推出" << endl;
		cout << endl;
		cout << "请输入您的操作：";
		int login = 0;
		cin >> login;
		if (login == 0)exit(0);
		else if (login == 2)
		{
			//进入访客模式，可以查询紧急号码
			system("cls");
			cout << "您正在访客模式，可以查询紧急号码" << endl;
			
			cout << "可查紧急号码为：" << endl;
			for (int i = 0; i < 6; i++)
			{
				cout << nologin[i].name << "  " << nologin[i].number << endl;
			}
			system("pause");
		}
		else if (login == 1)
		{
			cout << "请输入密码（检验：密码初始为123456" << endl;
			cout << "密码：";
			int kk = 1;//0标志密码错误  1标志成功
			char passwordlogin[7];//用strcmp()匹配
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
				//以下为成功进入用户界面
				node info[MAX];
				while (1)
				{
					system("cls");
					cout << "----------欢迎使用----------" << endl;
					cout << "1.新建电话本" << endl;
					cout << "2.按姓名查找联系人" << endl;
					cout << "9.按号码查找联系人" << endl;
					cout << "3.新建联系人" << endl;
					cout << "4.修改联系人" << endl;
					cout << "5.删除联系人" << endl;
					cout << "6.显示所有联系人" << endl;
					cout << "7.导出到文件" << endl;
					cout << "8.从文件导入联系人(第一次从这个文件导入：包含开放地址冲突数据）" << endl;
					cout << "80.从文件导入联系人（第二次从这个文件导入：包含链地址法冲突数据）" << endl;
					cout << "10.黑名单列表" << endl;
					cout << "101.导出黑名单" << endl;
					cout << "11.星标联系人列表" << endl;
					cout << "111.导出星标联系人" << endl;
					cout << "0.推出" << endl;
					cout << "----------------------------" << endl;
					cout << "请输入你的操作：";
					int caozuo;
					cin >> caozuo;
					cout << endl;
					switch (caozuo)
					{
					case 1:cout << "请输入要添加的联系人数（建议每次添加不超过10个）：";
						int n;
						cin >> n;
						createhash(n, info);
						system("pause");
						break;
					case 2:Look(info); system("pause"); break;
					case 3: {node newlian;
						cout << "输入联系人信息:" << endl;
						cout << " 姓名："; cin >> newlian.name;
						cout << " 电话："; cin >> newlian.phone;
						cout << " 地址："; cin >> newlian.adress;
						Insert(&newlian, info); }system("pause"); break;
					case 4:cout << "请输入要修改的联系人姓名：";
					{char name3[20];
					cin >> name3;
					unsigned int x = BKDRHash(name3);
					Update(x, info); }
					system("pause");
					break;
					case 5:cout << "请输入要删除的联系人姓名：";
					{char name3[20];
					cin >> name3;
					unsigned int x = BKDRHash(name3);
					Delete(x, info); }
					system("pause");
					break;
					case 6:cout << "---------所有联系人---------" << endl;
						cout << "当前共有" << NUM << "位联系人信息" << endl;
						cout << "\t|姓名\t\t\t\t\t|电话\t\t\t\t\t|地址";
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
						cout << NUM3 << "位星标联系人" << "    " << NUM2 << "位黑名单联系人" << endl;
						cout << endl; system("pause"); break;
					case 7:
					{
						savenumber(info);
					}
					system("pause");
					break;
					case 8:
					{
						//从文件导入联系人
						getfile1(info);
					}
					system("pause");
					break;
					case 9:
					{
						//按号码查找
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
						//黑名单列表
						cout << "黑名单列表" << endl;
						for (int i = 0; i < MAX; i++)
						{
							if (N[i] == 2)
							{
								cout << info[i].name << "  " << info[i].phone << "  " << info[i].adress << endl;
							}
						}
						cout << "黑名单共有" << NUM2 << "位联系人" << endl;
					}
					system("pause");
					break;
					case 101:
					{
						//导出黑名单
						ofstream bfout("blackname.txt");
						if (bfout)
						{
							bfout << NUM2 << endl;//data结构数据的大小(所有电话的个数)
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
							cout << "黑名单导出成功" << "    文件路径为：\\电话簿\\电话簿\\blackname.txt" << endl;
						}
					}
					system("pause");
					break;
					case 11:
					{
						//星标联系人列表
						starphone(info);
					}
					system("pause");
					break;
					case 111:
					{
						//导出星标
						ofstream sfout("starname.txt");
						if (sfout)
						{
							sfout << NUM3 << endl;//data结构数据的大小(所有电话的个数)
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
							cout << "导出星标成功" << "    文件路径为：\\电话簿\\电话簿\\starname.txt" << endl;
						}
					}
					system("pause");
					break;
					case 0:exit(1);
					default:cout << "输入错误" << endl;
					}
				}
			}
			else
			{
				cout << "密码错误" << endl;
				system("pause");
			}
		}
		else
		{
			cout << "指令输入错误" << endl;
			system("pause");
		}
	}
	return 0;
}

//冲突处理  为冲突数据新建空间  每次查找若  空间无 则查找冲突空间
//重名冲突  链地址法

//开放地址法   当不同名哈希产生冲突时调用
unsigned int against(unsigned int j,unsigned int N[])
{
	int i = 1;
	unsigned int H=j;
	while (N[H] != 0&&(i)<=100)
		/*当H位置有元素时，冲突 继续处理 
		  当处理冲突次数超过100时，放弃处理*/
	{
		cout << "冲突  处理  " << i << "次" << endl;
		H = (H + (i) * 10) % MAX;
		i++; 
	}
	return H;
}

/*将冲突的地址存入一个数组*/