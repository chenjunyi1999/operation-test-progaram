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
#define SECOND 5              //如果采取每一题限定时间，在这里修改每一题时间
using namespace std;

int flag = true,flag2 =true;
int second = 0;
float rightnumber = 0.0f; //正确的个数
int numoftest = 0;   //题目标号
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
		cout << endl << "对不起,你没能完成测试,做完这一题后将自动退出" ;
	}
	return 0;
}
string signup()
{
	cout << endl << "*************请您登陆，做题结果会存入 用户名.txt 中***********" << endl;
	string username;
	string password;
	int flag = -1;
	while (true)
	{
		cout << "            请输入用户名：";
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
			cout << "   ----------------------用户名不存在----------------------" << endl;
			continue;
		}
		/*if (username != "boy" && username != "girl")
		{
			cout << "用户名不存在！" << endl;
			continue;
		}*/
		cout << "            请输入登录密码：";
		cin >> password;
		if (password.compare(passwordarr[flag]) != 0)
		{
			cout << "   -----------------------密码错误-----------------------" << endl;
			flag = -1;
			continue;
		}

		break;
	}
	cout << endl << "*********************登陆成功！设置选项如下*******************" << endl;
	return username;
}
string registeruser()
{

	string username;
	string password;
	cout << "          请输入你的用户名:";
	cin >> username;
	cout << "          请输入你的密码:";
	cin >> password;
	usernamearr[numofuser] = username;
	passwordarr[numofuser] = password;
	numofuser++;
	cout << endl << "*********************登陆成功！设置选项如下*******************" << endl;
	return username;
}
std::string getCurrentTime()                   //得到当前的时间，并且标准化显示
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
		cout << "Sorry，you are wrong..." << endl;
		ofstream out;
		out.open(("user/" + username + ".txt").c_str(), ios::app);
		out << numoftest << "question is:" << questionstr << "    your answer is:" << yourstr << "    the right answer is:" << answerstr << endl;
		out.close();
	}
}
void createquestion(string& fileName, string& username)   //根据判断出来的提米类型选择的txt题库出一道题，并且判断
{                                                         //被createitemq，createchooseq，createjudgeq调用
	numoftest++;
	ifstream inf(fileName.c_str());
	//避免伪随机，时间种子放在主函数当中
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
part1:int  point = 0; //要分割的点的位置
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
	string questionstr = onelineData;//两个字符串分别存放题目和答案字符串
	string answerstr = onelineData;
	string yourstr;   //存放你自己的答案
	questionstr.erase(point, answerstr.length() + 1);
	answerstr.erase(0, point + 1);
	answerstr = answerstr.substr(0, answerstr.length() - 1);
	cout << "this is question " << numoftest << " : " << questionstr << endl << "请输入你的答案(按下回车提交进入下一题)";
	cin >> yourstr;
	/*clock_t sum, s = clock();                             //如果不注释，则程序编程每一题位SECOND单独结算
	int second = SECOND * CLOCKS_PER_SEC;
	while ((sum = (clock() - s)) < second && !_kbhit())
		;
	if (sum >= second)
	{
		cout << "超时，进入下一题！" << endl;
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
	cout << "************************下面是错题集环节********************" << endl;
	if (wrongnumber == 0)
	{
		cout << "you have solved all the question correctly!!" << endl;
	}
	for (int i = 0; i < wrongnumber; i++)
	{
		cout << "this is the" << i + 1 << "st question: " << wquestion[i] << endl << "请思考后输入新的答案：";
		cin >> yourstr;
		if (yourstr.compare(wqanswer[i]) == 0)
		{
			cout << "this time your are right！！！" << endl;
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
	bool  negative;  //有无负数
	bool decimal;    //有无小数
	bool brackets;     //有无括号
	int numofoperand;  //操作数个数
	int numofc;      //选择数量
	int numofj;      //判断数量
	int numofi;      //填空数量
	string readpath; //读取题目的路径
public:
	void testinformation()
	{
		int test;
		this->readpath = "";
		cout << "请输入题目的难度 1:10以内 2:100以内 3:1000以内" << endl;
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
				cout << "请重新输入";
				cin >> test;
			}
		}
		cout << "是否能够加入小数 1:有负数 2:没有负数" << endl;
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
				cout << "请重新输入";
				cin >> test;
			}
		}
		cout << "是否能够加入小数 1:有小数 2:没有小数" << endl;
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
				cout << "请重新输入";
				cin >> test;
			}
		}
		cout << "是否能够加入小数 1:有括号 2:没有括号" << endl;
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
				cout << "请重新输入" << endl;
				cin >> test;
			}
		}
		cout << "请输入操作数个数(2个/3个) 1: 2个 2: 3个及以上" << endl;
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
				cout << "请重新输入";
				cin >> test;
			}
		}

		int a, b, c;
		cout << "请输入填空，选择，判断个数(每种题型不超过5道题目，总共不超过15道)" << endl;
		cin >> a >> b >> c;
		while (true)
		{
			if (a < 0 || b < 0 || c < 0 || a>5 || b>5 || c > 5 || (a + b + c) == 0)
			{
				cout << "请重新输入" << endl;
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
part2:cout << "**********************欢迎来到四则运算测试系统****************" << endl;
	string username;
	int option1;
	cout << "**********1、系统默认用户/老用户登陆  2、新用户注册***********" << endl;
	while (true)
	{
		cin >> option1;
		if (option1 == 1)
		{
			username = signup();//登陆功能
			break;
		}
		else if (option1 == 2)
		{
			username = registeruser();
			break;
		}
		else
		{
			cout << "请重新输入";
			continue;
		}

	}
	Test test;
	test.testinformation();
	second = (test.getnumofc() + test.getnumofi() + test.getnumofj()) * SECOND;
	srand((unsigned int)time(NULL));
	rightnumber = 0;              //初始化;
	numoftest = 0;
	wrongnumber = 0;
	cout << endl << "**************************下面开始测试************************" << endl;
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
		cout << "   ---------下面是填空题部分，请直接输入正确的答案------------" << endl;
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
		cout << "   ---------下面是选择题部分，请输入正确的选项 A、B、C--------" << endl;
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
		cout << "   -----------下面是判断题部分，请输入正确的选项T、F----------" << endl;
		for (int i = 0; i < test.getnumofj(); i++)
		{
			if (flag)
			{
				test.createjudgeq(username);
			}
		}
	}
	flag2 = false;
	cout << "★★★★★★★★★考试结束，你的最终的得分为" << rightnumber / (test.getnumofc() + test.getnumofi() + test.getnumofj()) * 100 << "分★★★★★★" << endl;
	out.open(("user/" + username + ".txt").c_str(), ios::app);
	out << "最终得分为：" << rightnumber / (test.getnumofc() + test.getnumofi() + test.getnumofj()) * 100 << "分" << endl;
	cout << "详细结果保存在了" << username << ".txt当中" << endl;
	out.close();
	cout << endl << " *************************错误/反馈窗口*********************" << endl;
part4:ofstream out2;
	int option;
	string errorpath = "error/error.txt";
	cout << "1：错题集 2：题目答案/格式错误 3：提出意见 4：无意见" << endl;
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
		out2 << test.getpath() << "---->题目答案/格式有错误" << endl;
		cout << "谢谢反馈，我们会及时修改" << endl;
		cout << "*********************欢迎下次继续使用！************************" << endl;
		goto part4;
		break;
	case 3:
		cout << "请您提出意见(输入改进需求): ";
		cin >> errorstr;
		out2 << "这是来自用户的文字反馈---->" << errorstr << endl;
		cout << "谢谢反馈，我们会及时改进" << endl;
		cout << "*********************欢迎下次继续使用！************************" << endl;
		goto part4;
		break;
	case 4:
		cout << "*********************欢迎下次继续使用！************************" << endl;
		break;
	default:
		break;
	}
	cout << endl<<"*****************1:再次使用  其他任意键:退出*******************" << endl;
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


//以下为用堆栈计算四则运算的代码
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
//		char data[MAXSIZE];//用来存放操作符
//		int top;//数组下标
//	} op; //用结构体创建操作符栈
//	op.top = -1; //给操作符栈初始化，令下标为-1
//
//	char ch = 'a';
//	int i = 0, j = 0, tempi = 0;
//	while (ch != '\0')
//	{
//		ch = str[i]; //取str数组的第i个元素赋值给ch
//		if ((ch >= '0' && ch <= '9') || ch == '.') //对数值操作
//		{
//			tempi = i; //若ch为数字或小数点，将其下标值赋给临时下标tempi
//					   //依次向后扫描str数组，若一直为数字，跳入while循环
//			while ((ch >= '0' && ch <= '9') || ch == '.')
//			{
//				tempi++;
//				exp[j] = ch; //将数字存入exp数组中
//				j++;
//				ch = str[tempi]; //取str数组中下标为tempi的元素赋给ch
//			}
//			exp[j] = '#';
//			j++;//用#做分隔符，将数值分隔开
//			i = tempi; //跳出循环，将此时的tempi赋给i,继续向后扫描
//		}
//		//对操作符操作
//		else if (isOp(ch))
//		{
//			if (ch == '(') //如果为(，直接进栈
//			{
//				op.top++;
//				op.data[op.top] = ch; //进栈操作
//			}
//			else if (ch == ')')
//			{
//				//如果为),一直出栈直到遇到(
//				while (level(op.data[op.top]) != -1) //若栈顶元素不为(,进入while循环
//				{
//					exp[j] = op.data[op.top]; //操作符出栈，存入exp数组中
//					op.top--;
//					j++;
//					if (op.top == -1)break; //如果栈为空，跳出循环
//				}
//				op.top--;//左括号pop出来
//			}
//			else if (op.top == -1) //如果栈为空，直接进栈
//			{
//				op.top++;
//				op.data[op.top] = ch; //进栈操作
//			}
//			//如果所扫描的操作符优先等级比栈顶元素高，直接进栈
//			else if (level(ch) > level(op.data[op.top]))
//			{
//				op.top++;
//				op.data[op.top] = ch; //进栈操作
//			}
//			else
//			{
//				//如果所扫描的操作符优先等级没有栈顶元素高，
//				//一直出栈直到比栈顶元素优先级高
//				while (level(ch) <= level(op.data[op.top]))
//				{
//					exp[j] = op.data[op.top]; //出栈存入exp数组中
//					op.top--;
//					j++;
//					if (op.top == -1)break; //如果栈为空，跳出循环
//				}
//				op.top++;
//				op.data[op.top] = ch; //比栈顶元素优先级高，入栈
//			}
//			i++;//str下标加1，向后扫描
//		}
//		else//输入有误
//		{
//			printf("输入的表达式有误\n");
//
//			return;
//		}
//	}
//	while (op.top != -1) //扫描结束后如果操作符栈不为空，出栈直至为空
//	{
//		exp[j] = op.data[op.top]; //出栈存入exp数组中
//		op.top--;
//		j++;
//	}
//	exp[j] = '\0'; //赋\0结束exp字符数组
//}
//
//double calcTransfer(char exp[])
//{
//	struct
//	{
//		double data[MAXSIZE];
//		int top;
//	} od;
//	double d;                          //声明d变量存储数值
//	double od1, od2;                   //存储值栈依次pop出来的操作数
//	char ch;
//	char tempch[20];                    //声明临时数组存储子串
//	int j = 0, t;
//	int length = strlen(exp); //计算exp数组的长度
//	od.top = -1;              //初始化值栈，令下标为-1
//	while (j < length)
//	{
//		ch = exp[j];          //提取exp中第j个元素
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
//			tempch[t] = '\0';       //结束tempch数组
//			d = atof(tempch);       //将子串转化成double类型的数
//			od.top++;
//			od.data[od.top] = d; //入值栈
//		}
//		else                   //若为操作符，从值栈中pop出两个数计算
//		{
//			od2 = od.data[od.top];
//			od.top--;//先出栈的赋给od2
//			od1 = od.data[od.top];       //后出栈的赋给od1
//			od.data[od.top] = calcValue(od1, od2, ch); //计算出结果后再入栈
//		}
//		j++;
//	}
//	return od.data[od.top];//将结束后值栈中的数pop出来，即为计算结果
//}
//
//bool isOp(char ch)
//{
//	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '(' || ch == ')' || ch == '^')
//		return true;
//	return false;
//}
//
//int level(char op)//判断操作符优先等级
//{
//	if (op == '+' || op == '-')//若为+、-，等级为1
//		return 1;
//	else if (op == '*' || op == '/' || op == '%')
//		return 2;         //若为*、/、%,等级为2
//	else if (op == '^')
//		return 3;         //若为^,等级为3
//	else if (op == '(')
//		return -1;      //若为(,等级为-1
//	else
//		return -3;       //其他等级为-3；
//}
//
//double calcValue(double od1, double od2, char tempop) //计算
//{
//	switch (tempop) {
//	case '+':
//		return od1 + od2;//计算加法
//	case '-':
//		return od1 - od2;//计算减法
//	case '*':
//		return od1 * od2;//计算乘法
//	case '/':
//		return od1 / od2;//计算除法
//	case '%':
//		return fmod(od1, od2); //求余
//	case '^':
//		return pow(od1, od2);//指数
//	}
//	return 0;
//}
//
//int main()
//{
//	char str[MAXSIZE], exp[MAXSIZE];//定义str数组存放数学表达式
//part3: cout << "输入算术表达式：\n";
//	gets_s(str);       //从控制台输入算数表达式
//	transfer(str, exp);
//	if (flag)
//	{
//
//		cout << "答案是" << calcTransfer(exp) << endl;
//		goto part3;
//	}
//	system("pause");
//	return  0;
//}
