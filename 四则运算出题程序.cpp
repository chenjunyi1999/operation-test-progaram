#include <iostream>
#include <ctime>
#include<string>
#include <fstream>
#include <cstring>	
#include <cmath>		
#include <iomanip>
#include <windows.h>
#include <process.h>
#include<conio.h>
#define SECOND 5              //�����ȡÿһ���޶�ʱ�䣬�������޸�ÿһ��ʱ��
using namespace std;

int flag = true,flag2 =true;
int second = 0;
float rightnumber = 0.0f; //��ȷ�ĸ���
int numoftest = 0;   //��Ŀ���
int judgerandom[10];
int numofuser = 2;
int wrongnumber = 0;
string usernamearr[10] = { "boy","girl" };
string passwordarr[10] = { "123","123" };
string wquestion[15];
string wqanswer[15];

DWORD WINAPI timecontrol(LPVOID lpParamter)
{
	flag = true;
	while (second > 0)
	{
		Sleep(1000);
		second--;
	}
	flag = false;
	if (flag2)
	{
		cout << endl << "�Բ���,��û����ɲ���,������һ����Զ��˳�" ;
	}
	return 0;
}
string signup()
{
	cout << endl << "*************������½������������� �û���.txt ��***********" << endl;
	string username;
	string password;
	int flag = -1;
	while (true)
	{
		cout << "            �������û�����";
		cin >> username;
		for (int temp = 0; temp < numofuser; temp++)
		{
			if (username.compare(usernamearr[temp]) == 0)
			{
				flag = temp;
				break;
			}
		}
		if (flag == -1)
		{
			cout << "   ----------------------�û���������----------------------" << endl;
			continue;
		}
		/*if (username != "boy" && username != "girl")
		{
			cout << "�û��������ڣ�" << endl;
			continue;
		}*/
		cout << "            �������¼���룺";
		cin >> password;
		if (password.compare(passwordarr[flag]) != 0)
		{
			cout << "   -----------------------�������-----------------------" << endl;
			flag = -1;
			continue;
		}

		break;
	}
	cout << endl << "*********************��½�ɹ�������ѡ������*******************" << endl;
	return username;
}
string registeruser()
{

	string username;
	string password;
	cout << "          ����������û���:";
	cin >> username;
	cout << "          �������������:";
	cin >> password;
	usernamearr[numofuser] = username;
	passwordarr[numofuser] = password;
	numofuser++;
	cout << endl << "*********************��½�ɹ�������ѡ������*******************" << endl;
	return username;
}
std::string getCurrentTime()                   //�õ���ǰ��ʱ�䣬���ұ�׼����ʾ
{
	time_t nowtime = time(&nowtime);
	struct tm* ptm = localtime(&nowtime);
	char date[60] = { 0 };
	sprintf(date, "%4d-%02d-%02d %02d:%02d:%02d",
		(int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
		(int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
	return std::string(date);
}
void resultjudge(string& fileName, string& username,int numoftest,string questionstr,string yourstr ,string answerstr)
{
	if (yourstr.compare(answerstr) == 0)
	{
		cout << "correct!!!" << endl;
		rightnumber++;
		ofstream out;
		out.open(("user/" + username + ".txt").c_str(), ios::app);
		out << numoftest << "question is:" << questionstr << "    your answer is:" << yourstr << "    the right answer is:" << answerstr << endl;
		out.close();
	}
	else
	{
		wquestion[wrongnumber] = questionstr;
		wqanswer[wrongnumber] = answerstr;
		wrongnumber++;
		cout << "Sorry��you are wrong..." << endl;
		ofstream out;
		out.open(("user/" + username + ".txt").c_str(), ios::app);
		out << numoftest << "question is:" << questionstr << "    your answer is:" << yourstr << "    the right answer is:" << answerstr << endl;
		out.close();
	}
}
void createquestion(string& fileName, string& username)   //�����жϳ�������������ѡ���txt����һ���⣬�����ж�
{                                                         //��createitemq��createchooseq��createjudgeq����
	numoftest++;
	ifstream inf(fileName.c_str());
	//����α�����ʱ�����ӷ�������������
	string onelineData;
	int i = 0;
	string tmpLine;
	string questiontempstrp[10];
	while (getline(inf, tmpLine))
	{
		questiontempstrp[i] = tmpLine;
		i++;
	}
	while (1)
	{
		int randomint = (rand() % (9 - 0)) + 0;
		for (int l = 0; l < i; l++)
		{
			if (judgerandom[randomint] == 0)
			{
				onelineData = questiontempstrp[randomint];
				judgerandom[randomint] = 1;
				goto part1;
			}
			else
			{
				continue;
			}
		}

	}
part1:int  point = 0; //Ҫ�ָ�ĵ��λ��
	for (int index = 0; index < onelineData.length(); index++)
	{
		if (onelineData[index] != '?')
		{
			continue;
		}
		else
		{
			point = index;
			break;
		}
	}
	string questionstr = onelineData;//�����ַ����ֱ�����Ŀ�ʹ��ַ���
	string answerstr = onelineData;
	string yourstr;   //������Լ��Ĵ�
	questionstr.erase(point, answerstr.length() + 1);
	answerstr.erase(0, point + 1);
	answerstr = answerstr.substr(0, answerstr.length() - 1);
	cout << "this is question " << numoftest << " : " << questionstr << endl << "��������Ĵ�(���»س��ύ������һ��)";
	cin >> yourstr;
	/*clock_t sum, s = clock();                             //�����ע�ͣ��������ÿһ��λSECOND��������
	int second = SECOND * CLOCKS_PER_SEC;
	while ((sum = (clock() - s)) < second && !_kbhit())
		;
	if (sum >= second)
	{
		cout << "��ʱ��������һ�⣡" << endl;
		return;
	}
	else
	{
		cin >> yourstr;
	}*/
	
	resultjudge(fileName, username, numoftest, questionstr, yourstr, answerstr);
	inf.close();

}
void review()   
{
	string yourstr;
	cout << "************************�����Ǵ��⼯����********************" << endl;
	if (wrongnumber == 0)
	{
		cout << "you have solved all the question correctly!!" << endl;
	}
	for (int i = 0; i < wrongnumber; i++)
	{
		cout << "this is the" << i + 1 << "st question: " << wquestion[i] << endl << "��˼���������µĴ𰸣�";
		cin >> yourstr;
		if (yourstr.compare(wqanswer[i]) == 0)
		{
			cout << "this time your are right������" << endl;
		}
		else
		{
			cout << "sorry,you are wrong, the right answer is " << wqanswer[i] << "!!!" << endl;
		}

	}
}
class Test
{
private:
	int level;
	bool  negative;  //���޸���
	bool decimal;    //����С��
	bool brackets;     //��������
	int numofoperand;  //����������
	int numofc;      //ѡ������
	int numofj;      //�ж�����
	int numofi;      //�������
	string readpath; //��ȡ��Ŀ��·��
public:
	void testinformation()
	{
		int test;
		this->readpath = "";
		cout << "��������Ŀ���Ѷ� 1:10���� 2:100���� 3:1000����" << endl;
		cin >> test;
		while (true)
		{
			if (test == 1 || test == 2 || test == 3)
			{
				this->level = test;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else
			{
				cout << "����������";
				cin >> test;
			}
		}
		cout << "�Ƿ��ܹ�����С�� 1:�и��� 2:û�и���" << endl;
		cin >> test;
		while (true)
		{
			if (test == 1)
			{
				this->negative = true;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else if (test == 2)
			{
				this->negative = false;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else
			{
				cout << "����������";
				cin >> test;
			}
		}
		cout << "�Ƿ��ܹ�����С�� 1:��С�� 2:û��С��" << endl;
		cin >> test;
		while (true)
		{
			if (test == 1)
			{
				this->decimal = true;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else if (test == 2)
			{
				this->decimal = false;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else
			{
				cout << "����������";
				cin >> test;
			}
		}
		cout << "�Ƿ��ܹ�����С�� 1:������ 2:û������" << endl;
		cin >> test;
		while (true)
		{
			if (test == 1)
			{
				this->brackets = true;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else if (test == 2)
			{
				this->brackets = false;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else
			{
				cout << "����������" << endl;
				cin >> test;
			}
		}
		cout << "���������������(2��/3��) 1: 2�� 2: 3��������" << endl;
		cin >> test;
		while (true)
		{
			if (test == 1)
			{
				this->numofoperand = test + 1;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else if (test == 2)
			{
				this->numofoperand = test + 1;
				std::string s = std::to_string(test);
				this->readpath += s;
				break;
			}
			else
			{
				cout << "����������";
				cin >> test;
			}
		}

		int a, b, c;
		cout << "��������գ�ѡ���жϸ���(ÿ�����Ͳ�����5����Ŀ���ܹ�������15��)" << endl;
		cin >> a >> b >> c;
		while (true)
		{
			if (a < 0 || b < 0 || c < 0 || a>5 || b>5 || c > 5 || (a + b + c) == 0)
			{
				cout << "����������" << endl;
				cin >> a >> b >> c;
			}
			else
			{
				numofi = a;
				numofc = b;
				numofj = c;
				break;
			}
		}
	}
	int getnumofc()
	{
		return numofc;
	}
	int getnumofj()
	{
		return numofj;
	}
	int getnumofi()
	{
		return numofi;
	}
	string getpath()
	{
		return this->readpath;
	}
	void createitemq(string& username)
	{
		string finalpath = "test/" + this->readpath + "1.txt";
		createquestion(finalpath, username);

	}
	void createchooseq(string& username)
	{
		string finalpath = "test/" + this->readpath + "3.txt";
		createquestion(finalpath, username);
	}
	void createjudgeq(string& username)
	{
		string finalpath = "test/" + this->readpath + "2.txt";
		createquestion(finalpath, username);
	}

};
int main()
{
	system("mode con cols=75 lines=50");
part2:cout << "**********************��ӭ���������������ϵͳ****************" << endl;
	string username;
	int option1;
	cout << "**********1��ϵͳĬ���û�/���û���½  2�����û�ע��***********" << endl;
	while (true)
	{
		cin >> option1;
		if (option1 == 1)
		{
			username = signup();//��½����
			break;
		}
		else if (option1 == 2)
		{
			username = registeruser();
			break;
		}
		else
		{
			cout << "����������";
			continue;
		}

	}
	Test test;
	test.testinformation();
	second = (test.getnumofc() + test.getnumofi() + test.getnumofj()) * SECOND;
	srand((unsigned int)time(NULL));
	rightnumber = 0;              //��ʼ��;
	numoftest = 0;
	wrongnumber = 0;
	cout << endl << "**************************���濪ʼ����************************" << endl;
	ofstream out;
	out.open(("user/" + username + ".txt").c_str(), ios::app);
	out << "\n\t" << getCurrentTime() << endl;
	out.close();
	
	flag = true;
	flag2 = true;
	HANDLE h = CreateThread(NULL, 0, timecontrol, NULL, 0, NULL);
	CloseHandle(h);
	


	for (int l = 0; l < 10; l++)
	{
		judgerandom[l] = 0;
	}
	if (test.getnumofi() > 0 && flag)
	{
		cout << "   ---------����������ⲿ�֣���ֱ��������ȷ�Ĵ�------------" << endl;
		for (int i = 0; i < test.getnumofi(); i++)
		{
			if (flag)
			{
				test.createitemq(username);
			}
		}
	}
	for (int l = 0; l < 10; l++)
	{
		judgerandom[l] = 0;
	}
	if (test.getnumofc() > 0&&flag)
	{
		cout << "   ---------������ѡ���ⲿ�֣���������ȷ��ѡ�� A��B��C--------" << endl;
		for (int i = 0; i < test.getnumofc(); i++)
		{
			if (flag)
			{
				test.createchooseq(username);
			}
		}
	}
	for (int l = 0; l < 10; l++)
	{
		judgerandom[l] = 0;
	}
	if (test.getnumofj() > 0 && flag)
	{
		cout << "   -----------�������ж��ⲿ�֣���������ȷ��ѡ��T��F----------" << endl;
		for (int i = 0; i < test.getnumofj(); i++)
		{
			if (flag)
			{
				test.createjudgeq(username);
			}
		}
	}
	flag2 = false;
	cout << "���������￼�Խ�����������յĵ÷�Ϊ" << rightnumber / (test.getnumofc() + test.getnumofi() + test.getnumofj()) * 100 << "�֡������" << endl;
	out.open(("user/" + username + ".txt").c_str(), ios::app);
	out << "���յ÷�Ϊ��" << rightnumber / (test.getnumofc() + test.getnumofi() + test.getnumofj()) * 100 << "��" << endl;
	cout << "��ϸ�����������" << username << ".txt����" << endl;
	out.close();
	cout << endl << " *************************����/��������*********************" << endl;
part4:ofstream out2;
	int option;
	string errorpath = "error/error.txt";
	cout << "1�����⼯ 2����Ŀ��/��ʽ���� 3�������� 4�������" << endl;
	cin >> option;
	out2.open(errorpath.c_str(), ios::app);
	string errorstr;
	switch (option)
	{
	case 1:
		review();
		goto part4;
		break;
	case 2:
		out2 << test.getpath() << "---->��Ŀ��/��ʽ�д���" << endl;
		cout << "лл���������ǻἰʱ�޸�" << endl;
		cout << "*********************��ӭ�´μ���ʹ�ã�************************" << endl;
		goto part4;
		break;
	case 3:
		cout << "����������(����Ľ�����): ";
		cin >> errorstr;
		out2 << "���������û������ַ���---->" << errorstr << endl;
		cout << "лл���������ǻἰʱ�Ľ�" << endl;
		cout << "*********************��ӭ�´μ���ʹ�ã�************************" << endl;
		goto part4;
		break;
	case 4:
		cout << "*********************��ӭ�´μ���ʹ�ã�************************" << endl;
		break;
	default:
		break;
	}
	cout << endl<<"*****************1:�ٴ�ʹ��  ���������:�˳�*******************" << endl;
	while (true)
	{
		cin >> option1;
		if (option1 == 1)
		{
			goto part2;
			break;
		}
		else
		{
			return 0;
			break;
		}

	}

}


//����Ϊ�ö�ջ������������Ĵ���
//#include<iostream>
//#include<string>
//#include<cmath>
//#include<stdlib.h>
//#include<stdbool.h>
//using namespace std;
//
//#define MAXSIZE 100
//#define FIGUREMAXSIZE 20
//bool flag = true;
//int level(char op);
//double calcValue(double od1, double od2, char tempop);
//bool isOp(char ch);
//
//void transfer(char str[], char exp[])
//{
//	struct
//	{
//		char data[MAXSIZE];//������Ų�����
//		int top;//�����±�
//	} op; //�ýṹ�崴��������ջ
//	op.top = -1; //��������ջ��ʼ�������±�Ϊ-1
//
//	char ch = 'a';
//	int i = 0, j = 0, tempi = 0;
//	while (ch != '\0')
//	{
//		ch = str[i]; //ȡstr����ĵ�i��Ԫ�ظ�ֵ��ch
//		if ((ch >= '0' && ch <= '9') || ch == '.') //����ֵ����
//		{
//			tempi = i; //��chΪ���ֻ�С���㣬�����±�ֵ������ʱ�±�tempi
//					   //�������ɨ��str���飬��һֱΪ���֣�����whileѭ��
//			while ((ch >= '0' && ch <= '9') || ch == '.')
//			{
//				tempi++;
//				exp[j] = ch; //�����ִ���exp������
//				j++;
//				ch = str[tempi]; //ȡstr�������±�Ϊtempi��Ԫ�ظ���ch
//			}
//			exp[j] = '#';
//			j++;//��#���ָ���������ֵ�ָ���
//			i = tempi; //����ѭ��������ʱ��tempi����i,�������ɨ��
//		}
//		//�Բ���������
//		else if (isOp(ch))
//		{
//			if (ch == '(') //���Ϊ(��ֱ�ӽ�ջ
//			{
//				op.top++;
//				op.data[op.top] = ch; //��ջ����
//			}
//			else if (ch == ')')
//			{
//				//���Ϊ),һֱ��ջֱ������(
//				while (level(op.data[op.top]) != -1) //��ջ��Ԫ�ز�Ϊ(,����whileѭ��
//				{
//					exp[j] = op.data[op.top]; //��������ջ������exp������
//					op.top--;
//					j++;
//					if (op.top == -1)break; //���ջΪ�գ�����ѭ��
//				}
//				op.top--;//������pop����
//			}
//			else if (op.top == -1) //���ջΪ�գ�ֱ�ӽ�ջ
//			{
//				op.top++;
//				op.data[op.top] = ch; //��ջ����
//			}
//			//�����ɨ��Ĳ��������ȵȼ���ջ��Ԫ�ظߣ�ֱ�ӽ�ջ
//			else if (level(ch) > level(op.data[op.top]))
//			{
//				op.top++;
//				op.data[op.top] = ch; //��ջ����
//			}
//			else
//			{
//				//�����ɨ��Ĳ��������ȵȼ�û��ջ��Ԫ�ظߣ�
//				//һֱ��ջֱ����ջ��Ԫ�����ȼ���
//				while (level(ch) <= level(op.data[op.top]))
//				{
//					exp[j] = op.data[op.top]; //��ջ����exp������
//					op.top--;
//					j++;
//					if (op.top == -1)break; //���ջΪ�գ�����ѭ��
//				}
//				op.top++;
//				op.data[op.top] = ch; //��ջ��Ԫ�����ȼ��ߣ���ջ
//			}
//			i++;//str�±��1�����ɨ��
//		}
//		else//��������
//		{
//			printf("����ı��ʽ����\n");
//
//			return;
//		}
//	}
//	while (op.top != -1) //ɨ����������������ջ��Ϊ�գ���ջֱ��Ϊ��
//	{
//		exp[j] = op.data[op.top]; //��ջ����exp������
//		op.top--;
//		j++;
//	}
//	exp[j] = '\0'; //��\0����exp�ַ�����
//}
//
//double calcTransfer(char exp[])
//{
//	struct
//	{
//		double data[MAXSIZE];
//		int top;
//	} od;
//	double d;                          //����d�����洢��ֵ
//	double od1, od2;                   //�洢ֵջ����pop�����Ĳ�����
//	char ch;
//	char tempch[20];                    //������ʱ����洢�Ӵ�
//	int j = 0, t;
//	int length = strlen(exp); //����exp����ĳ���
//	od.top = -1;              //��ʼ��ֵջ�����±�Ϊ-1
//	while (j < length)
//	{
//		ch = exp[j];          //��ȡexp�е�j��Ԫ��
//		if (!isOp(ch))
//		{
//			d = 0;
//			t = 0;
//			while ((ch >= '0' && ch <= '9') || ch == '.')
//			{
//				tempch[t] = ch;
//				t++;
//				j++;
//				ch = exp[j];
//			}
//			tempch[t] = '\0';       //����tempch����
//			d = atof(tempch);       //���Ӵ�ת����double���͵���
//			od.top++;
//			od.data[od.top] = d; //��ֵջ
//		}
//		else                   //��Ϊ����������ֵջ��pop������������
//		{
//			od2 = od.data[od.top];
//			od.top--;//�ȳ�ջ�ĸ���od2
//			od1 = od.data[od.top];       //���ջ�ĸ���od1
//			od.data[od.top] = calcValue(od1, od2, ch); //��������������ջ
//		}
//		j++;
//	}
//	return od.data[od.top];//��������ֵջ�е���pop��������Ϊ������
//}
//
//bool isOp(char ch)
//{
//	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')' || ch == '^')
//		return true;
//	return false;
//}
//
//int level(char op)//�жϲ��������ȵȼ�
//{
//	if (op == '+' || op == '-')//��Ϊ+��-���ȼ�Ϊ1
//		return 1;
//	else if (op == '*' || op == '/' || op == '%')
//		return 2;         //��Ϊ*��/��%,�ȼ�Ϊ2
//	else if (op == '^')
//		return 3;         //��Ϊ^,�ȼ�Ϊ3
//	else if (op == '(')
//		return -1;      //��Ϊ(,�ȼ�Ϊ-1
//	else
//		return -3;       //�����ȼ�Ϊ-3��
//}
//
//double calcValue(double od1, double od2, char tempop) //����
//{
//	switch (tempop) {
//	case '+':
//		return od1 + od2;//����ӷ�
//	case '-':
//		return od1 - od2;//�������
//	case '*':
//		return od1 * od2;//����˷�
//	case '/':
//		return od1 / od2;//�������
//	case '%':
//		return fmod(od1, od2); //����
//	case '^':
//		return pow(od1, od2);//ָ��
//	}
//	return 0;
//}
//
//int main()
//{
//	char str[MAXSIZE], exp[MAXSIZE];//����str��������ѧ���ʽ
//part3: cout << "�����������ʽ��\n";
//	gets_s(str);       //�ӿ���̨�����������ʽ
//	transfer(str, exp);
//	if (flag)
//	{
//
//		cout << "����" << calcTransfer(exp) << endl;
//		goto part3;
//	}
//	system("pause");
//	return  0;
//}
