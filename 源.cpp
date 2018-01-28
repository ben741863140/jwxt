#define _CRT_SECURE_NO_WARNINGS       /*16长度一个汉字*/
#include<afx.h>
#include<graphics.h> //XOR_PUT
#include<cstdio>
#include<conio.h>//getch 键盘 kbhit 鼠标
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<time.h>
#include<tchar.h>
#include<wchar.h>
#include <string>
#pragma comment(lib,"Imm32.lib")
#define rep(i,a,n) for(i=a; i<n; i++)
#define rep1(i,a,n) for(i=n-1; i>=a; i--)
#define s(a) scanf("%d",&a)
#define ll long long
using namespace std;
struct  {
	char user[100];
	char mail[100];
	char password[100];
	int num;
}LOGIN[200010];//判断账号
struct 
{
	int num; //编号
	char name[100];//名字
	int sex;//0男 1女
	int age;// 年龄
	int ss;// 宿舍号码
	char phone[100];//电话号码
	int xf;//已修学分
	int kc[100];//挂科课程
	int sl;//挂科数目
}xscx[200010];//学生详细信息
struct {
	char name[100];
	int num;
}km[500];//科目对应编号
struct JS{
	int num;
	int kc[100];
	int sl;
}jscx[10000];//教师详细信息
struct {
	int num;
	int xs[200010];
	int sl;
}kmxs[500];//科目所含学生
struct {
	int ps[500];
	int ks[500];
}xscj[200010];//学生成绩
struct {
	char user[100];
	char mail[100];
	char password[100];
	int num;
}number[200010];//学号
struct {
	string name;
	int xf;
	int num;
	char cname[100];
}sqlist[1000];//申请开课列表
struct 
{
	int num;
	char phone[20];
	char name[20];
	char address[20];
}jsphone[100000];//教师名字和联系方式
struct {
	
		int num; //编号
		char name[100];//名字
		int sex;//0男 1女
		int age;// 年龄
		int ss;// 宿舍号码
		char phone[100];//电话号码
		char user[100];//学号
}insert[1005];//插入的学生信息
struct {
	int ps;
	int ks;
	int xf;
	int y;
	int xq;
	int jd;
}kmxx[500];//科目详细信息
struct {
	int num;
	char xh[100];
	int sl;
	int bh[15];
	int knum[15];
}xsxk[1010];//学生选课录入
struct
{
	char xh[50];
	int xsnum;
	int sl;
	int ps[500];
	int ks[500];
	int num[500];
	int bh[500];
}cjlr[1010];//学生成绩录入
struct {
	int num;
	int xs[110];
	int sl;
}xscls[10000];//班级内的学生
struct CLASS
{
	int num;
	char bj[20];
}cls[10000];//班级
struct
{
	char user[100];
	char mail[100];
	char password[100];
	int num;
}bm[10];
int xskm[200010];//学生含有科目的数量
char user[100] = "";
char password[100] = "";
char write[100] = "";
int num;
int open;//权限组
int ui;//用户名最尾
int mi;//密码最尾
bool fkcmd;
bool fcxxskm;
bool fcxxscj;
bool fcxxs;
bool fxsuser;
bool shflag;
FILE *fp;
bool iflogin;
void ecfile(LPCTSTR fpath)//文件加密
{
	char *data;
	CFile *file;
	DWORD flen;
	int m_password = 54254 ^ 98763;
	file = new CFile;
	file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite);
	flen = file->GetLength();
	data = new char[(int)flen];
	file->SeekToBegin();
	file->Read(data, flen);
	int i;
	rep(i, 0, (int)flen)
	{
		data[i] ^= m_password;
		data[i] ^= flen;
	}
	file->SeekToBegin();
	file->Write(data, flen);
	delete[] data;
	char cpass[5] = "Leon";
	rep(i, 0, 5)
	{
		cpass[i] ^= m_password;
	}
	file->SeekToEnd();
	file->Write(&cpass, 5);
	file->Close();
	delete file;
}
void dcfile(LPCTSTR fpath)//文件解密
{
	char *data;
	CFile *file;
	DWORD flen;
	char leon[5];
	file = new CFile;
	file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite);
	flen = file->GetLength();
	data = new char[(int)flen];
	file->Seek(-5, CFile::end);
	file->Read(&leon, 5);
	int m_password = 54254 ^ 98763;
	int i;
	rep(i, 0, 5)
	{
		leon[i] ^= m_password;
	}
	if (strcmp(leon, "Leon") != 0) return;
	file->SeekToBegin();
	file->Read(data, flen);
	rep(i, 0, (int)flen)
	{
		data[i] ^= m_password;
		data[i] ^= (flen - 5);
	}
	file->SeekToBegin();
	file->Write(data, flen);
	file->SetLength(flen - 5);
	file->Close();
	delete[] data;
	delete file;
}
int cmpcls(CLASS a, CLASS b)//比较班级编号
{
	return strcmp(a.bj, b.bj) < 0;
}
int cmpjs(JS a,JS b)//编号小的教师在前面
{
	return a.num < b.num;
}
void putback()//打印返回按钮
{
	settextstyle(15, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(750, 120, "返回");
}
void GetIMEString(HWND hWnd, string& str)//输入中文
{
	HIMC hIMC = ImmGetContext(hWnd);//获取HIMC	
	if (hIMC)
	{
		//这里先说明一下，以输入“中国”为例	
		//切换到中文输入法后，输入“zhongguo”，这个字符串称作IME组成字符串	
		//而在输入法列表中选择的字符串“中国”则称作IME结果字符串	
		static bool flagz = false;//输入完成标记：在输入中时，IME组成字符串不为空，置true；输入完成后，IME组成字符串为空，置false	
		DWORD dwSize = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0);	//获取IME组成输入的字符串的长度	
		if (dwSize>0)//如果IME组成字符串不为空，且没有错误（此时dwSize为负值），则置输入完成标记为true	
		{
			if (flagz == false)
			{
				flagz = true;
			}
		}
		else if (dwSize == 0 && flagz)	//如果IME组成字符串为空，并且标记为true，则获取IME结果字符串	
		{
			int iSize;	//IME结果字符串的大小	
			LPSTR pszMultiByte = NULL;//IME结果字符串指针	
			int ChineseSimpleAcp = 936;//宽字节转换时中文的编码	
			WCHAR *lpWideStr = NULL;//宽字节字符数组	
			dwSize = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);//获取IME结果字符串的大小	
			if (dwSize>0)	//如果IME结果字符串不为空，且没有错误	
			{
				dwSize += sizeof(WCHAR);//大小要加上NULL结束符	
										//为获取IME结果字符串分配空间	
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				lpWideStr = new WCHAR[dwSize];
				memset(lpWideStr, 0, dwSize);	//清空结果空间	
				ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpWideStr, dwSize);//获取IME结果字符串，这里获取的是宽字节	
				iSize = WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, NULL, 0, NULL, NULL);//计算将IME结果字符串转换为ASCII标准字节后的大小	
																									 //为转换分配空间	
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
				pszMultiByte = new char[iSize + 1];
				WideCharToMultiByte(ChineseSimpleAcp, 0, lpWideStr, -1, pszMultiByte, iSize, NULL, NULL);//宽字节转换	
				pszMultiByte[iSize] = '\0';
				str += pszMultiByte;//添加到string中	
									//释放空间	
				if (lpWideStr)
				{
					delete[]lpWideStr;
					lpWideStr = NULL;
				}
				if (pszMultiByte)
				{
					delete[] pszMultiByte;
					pszMultiByte = NULL;
				}
			}
			flagz = false;
		}
		ImmReleaseContext(hWnd, hIMC);//释放HIMC	
	}
}
int toint(char *x)//字符数组转成int
{
	int j,i,n = strlen(x),ans=0;
	i = n;
	rep(j, 0, n)
	{
		int z, temp;
		temp = (x[j] - '0');
		rep(z, 1, i)
			temp *= 10;
		ans += temp;
		i--;
	}
	return ans;
}
void change(int x)//数字改成字符
{
	if (x == 0) { write[0] = '0'; write[1] = '\0'; return; }
	int temp = x,j=0;
	memset(write, 0, sizeof(write));
	while (temp) {
		j++;
		temp /= 10;
	}
	rep1(temp, 0, j)
	{
		write[temp] = (x % 10)+'0';
		x /= 10;
	}
	write[j] = '\0';
}
void tz(int i, int v)//通知申请结果
{
	fclose(stdin);
	fp = fopen("sqjg.in", "a");
	fprintf(fp, "%d\n", sqlist[i].num);
	fprintf(fp, "%d\n", v);
	fclose(fp);
}
void cxxs(int &t)//将学生详细信息打入数组中
{
	fclose(stdin);
	freopen("xsxx.in", "r", stdin);
	scanf("%d", &t);
	int i;
	rep(i, 0, t)
	{
		scanf("%d", &xscx[i].num);
		getchar();
		gets_s(xscx[i].name);
		scanf("%d", &xscx[i].sex);
		scanf("%d", &xscx[i].age);
		scanf("%d", &xscx[i].ss);
		getchar();
		gets_s(xscx[i].phone);
		scanf("%d", &xscx[i].xf);
		int j = 0;
		scanf("%d", &xscx[i].kc[j]);
		while (xscx[i].kc[j] != 0)
		{
			j++;
			scanf("%d", &xscx[i].kc[j]);
		}
		xscx[i].sl = j;
	}
	fclose(stdin);
}
void cxjs(int &t)//教师信息打入数组
{
	int i;
	fclose(stdin);
	freopen("jsxx.in", "r", stdin);
	s(t);
	rep(i, 0, t)
	{
		s(jscx[i].num);
		s(jscx[i].kc[0]);
		int j = 0;
		while (jscx[i].kc[j] != 0)
		{
			j++;
			s(jscx[i].kc[j]);
		}
		jscx[i].sl = j;
	}
	fclose(stdin);
	freopen("jsphone.in", "r", stdin);
	s(t);
	rep(i, 0, t)
	{
		s(jsphone[i].num);
		getchar();
		gets_s(jsphone[i].name);
		gets_s(jsphone[i].phone);
		gets_s(jsphone[i].address);

	}
	fclose(stdin);
}
void cxkmxx(int &t)//将科目详细信息打入数组
{
	fclose(stdin);
	freopen("kmxx.in", "r", stdin);
	s(t);
	int i;
	for (i = 1; i <= t; i++)
	{
		s(kmxx[i].ps);
		s(kmxx[i].ks);
		s(kmxx[i].xf);
		s(kmxx[i].y);
		if (kmxx[i].y)
		{
			s(kmxx[i].xq);
			s(kmxx[i].jd);
		}
	}
	fclose(stdin);
}
void kmcx()//读取课程名字入数组
{
	fclose(stdin);
	freopen("km.in", "r", stdin);
	int t;
	s(t);
	int i;
	rep(i, 1, t+1)
	{
		getchar();
		gets_s(km[i].name);
		s(km[i].num);
	}
	fclose(stdin);
}
void cxxscj()//查询学生成绩
{
	int t,z,i,j,q;
	fclose(stdin);
	freopen("xscj.in", "r", stdin);
	s(t);//科目数量
	s(z);//学生数量
	rep(i, 1, t + 1)
	{
		rep(j, 0, z)
			s(xscj[j].ps[i]);
		rep(j, 0, z)
			s(xscj[j].ks[i]);
	}
	fclose(stdin);
}
void cxxskm()//查询课程所含的学生
{
	fclose(stdin);
	freopen("xskm.in", "r", stdin);
	int i,t;
	s(t);
	rep(i, 1, t+1)
	{
		s(kmxs[i].num);
		kmxs[i].sl = 0;
		s(kmxs[i].xs[kmxs[i].sl]);
		while (kmxs[i].xs[kmxs[i].sl] != -1)
		{
			kmxs[i].sl++;
			s(kmxs[i].xs[kmxs[i].sl]);
		}
	}
	fclose(stdin);
}
void cxxskm2()//查询学生所含的课程
{
	memset(xskm, 0, sizeof(xskm));
	fclose(stdin);
	freopen("xskm.in", "r", stdin);
	int i, t;
	s(t);
	rep(i, 1, t + 1)
	{
		s(kmxs[i].num);
		int j;
		s(j);
		while (j != -1)
		{
			kmxs[xskm[j]].xs[j] = i;
			xskm[j]++;
			s(j);
		}
	}
	fclose(stdin);
}
void bjg(int n,int m,int t)//整理学生学科成绩，重新找到不及格
{
	int i, j;
	rep(i, 0, t)
	{
		xscx[cjlr[i].xsnum].xf = 0;
		xscx[cjlr[i].xsnum].sl = 0;
		xscx[cjlr[i].xsnum].kc[xscx[cjlr[i].xsnum].sl] = 0;
		rep(j, 1, m + 1)
		{
			if (xscj[cjlr[i].xsnum].ps[j] != -1)
			{
				double temp = xscj[cjlr[i].xsnum].ps[j] * 0.4 + xscj[cjlr[i].xsnum].ks[j] * 0.6;
				if (temp >= 60)
				{
					xscx[cjlr[i].xsnum].xf += kmxx[j].xf;
				}
				else
				{
						xscx[cjlr[i].xsnum].kc[xscx[cjlr[i].xsnum].sl++] = j;
						xscx[cjlr[i].xsnum].kc[xscx[cjlr[i].xsnum].sl] = 0;
				}
			}
		}
	}
}
void xsxs(int i)//显示某个学生
{
	int j;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 200, "姓名:");
	settextcolor(BLACK);//字体颜色
	outtextxy(278,200,xscx[i].name);
	settextcolor(BLUE);//字体颜色
	outtextxy(400, 200, "性别:");
	settextcolor(BLACK);//字体颜色
	if (!xscx[i].sex) outtextxy(478, 200, "男");
	else outtextxy(478, 200, "女");
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 230, "年龄:");
	change(xscx[i].age);
	settextcolor(BLACK);//字体颜色
	outtextxy(278, 230, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(400, 230, "宿舍:");
	change(xscx[i].ss);
	settextcolor(BLACK);//字体颜色
	outtextxy(478, 230, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 260, "电话:");
	settextcolor(BLACK);//字体颜色
	outtextxy(278, 260, xscx[i].phone);
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 290, "学分:");
	change(xscx[i].xf);
	settextcolor(BLACK);//字体颜色
	outtextxy(278, 290, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 320, "有");
	change(xscx[i].sl);
	settextcolor(BLACK);//字体颜色
	outtextxy(275, 320, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(293, 320, "门科目不及格:");
	settextcolor(BLACK);//字体颜色
	kmcx();
	int temp = 0, temp1 = 5;
	rep(j, 0, xscx[i].sl)
	{
		if ((j-temp*temp1) > 4) temp++;
		outtextxy(200 + 155 * (j-temp*temp1), 350+30*temp, km[xscx[i].kc[j]].name);
	}
	cxxskm2();
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 500, "已选科目:");
	settextcolor(BLACK);//字体颜色
	temp = 0, temp1 = 5;
	rep(j, 0, xskm[i])
	{
		if ((j - temp*temp1) > 4) temp++;
		outtextxy(200 + 155 * (j - temp*temp1), 520 + 30 * temp, km[kmxs[j].xs[i]].name);
	}
}
void init()//白色背景
{
	IMAGE img;
	loadimage(&img, "白色背景.jpg", 1280, 960);
	putimage(0, 0, &img);
	return;
}
void putxsuser()//寻找学号
{
	freopen("xs.in", "r", stdin);
	int t, i, j;
	scanf("%d", &t);
	rep(i, 0, t)
		{
			getchar();
			gets_s(number[i].user);
			gets_s(number[i].mail);
			gets_s(number[i].password);
			scanf("%d", &number[i].num);
		}
	fclose(stdin);
}
void findclass(int &n) {
	fclose(stdin);
	freopen("class.in", "r", stdin);
	s(n);
	int i;
	rep(i, 0, n)
	{
		getchar();
		gets_s(cls[i].bj);
		s(cls[i].num);
	}
	fclose(stdin);
	freopen("xsclass.in", "r", stdin);
	s(n);
	rep(i, 0, n)
	{
		s(xscls[i].num);
		s(xscls[i].sl);
		int j;
		rep(j, 0, xscls[i].sl)
			s(xscls[i].xs[j]);
	}
	fclose(stdin);
}
void putlogin()//登录界面
{
	setbkmode(TRANSPARENT);//字体背景透明
	settextstyle(70, 0, "华文琥珀");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(260, 0, "教务信息管理系统");
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(300, 320, "账户");
	IMAGE img;
	loadimage(&img,"用户密码.jpg", 363, 114);
	putimage(370, 300, &img);
	outtextxy(300, 370, "密码");
	settextstyle(15, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(900, 120, "退出");
}
inline bool finduser()//判断账号
{
	int t,i,j;
	bool flag = false;
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(LOGIN[i].user);
		gets_s(LOGIN[i].mail);
		gets_s(LOGIN[i].password);
		scanf("%d", &LOGIN[i].num);
		if (strcmp(LOGIN[i].user, user) == 0)
		{
			if (strcmp(LOGIN[i].password, password) == 0)
			{
				num = LOGIN[i].num;
				flag = true;
				break;
			}
			else {
				flag = false;
				break;
			}
		}
		else if (strcmp(LOGIN[i].mail, user)==0)
		{
			if (strcmp(LOGIN[i].password, password) == 0)
			{
				num = LOGIN[i].num;
				flag = true;
				break;
			}
			else 
			{
				flag = false;
				break;
			}
		}
	}
	if (flag) return true;
	return false;
}
bool login()//登录系统
{
	int i,temp=0,tmp=0;
	char x;
	bool flag = false;
	IMAGE img,img1,img2,img3,img4,img5,img6,img7,img8,img9;
	loadimage(&img, "白色背景.jpg",320 , 25);
	loadimage(&img1, "部门.jpg", 45, 24);
	loadimage(&img2, "部门2.jpg", 45, 24);
	loadimage(&img3, "教师.jpg", 46, 23);
	loadimage(&img4, "教师2.jpg", 46, 23);
	loadimage(&img5, "学生.jpg", 45, 23);
	loadimage(&img6, "学生2.jpg", 45, 23);
	loadimage(&img7, "登录.jpg", 110, 39);
	MOUSEMSG msg,msg1;
	msg = GetMouseMsg();
	putimage(395, 425, &img1);
	putimage(455, 428, &img3);
	putimage(515, 427, &img5);
	putimage(455, 485, &img7);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	while(1)
	{
		if(msg.uMsg!=WM_LBUTTONDOWN||!flag)
		msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 405 && msg.x <= 702 && msg.y >= 302 && msg.y <= 332)//账号框
			{
				i = ui; flag = true;
				int start = clock(), finish = clock();
				if(ui==0) putimage(405, 315, &img);
				while (1)
				{
					finish = clock();
					if (finish - start>500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 315, "▏");
					}
					if (finish - start >1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 315, "▏");
							user[i] = '\0'; ui = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x == 9)
						{
							user[i] = '\0'; ui = i;  goto pas;
						}
						else if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								user[i] = x;
								outtextxy(420 + 8 * i, 315, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(420 + 8 * i, 315, user[i]);
								user[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 405 && msg.x <= 702 && msg.y >= 355 && msg.y <= 395)//密码框
			{
				flag = true;
				pas: i = mi; temp = i-1;
				if(mi==0) putimage(405, 375, &img);
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start>500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 375, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						start = clock();
					}
					//freopen("in.txt", "r", stdin);
					while (_kbhit()) 
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								if (i > 0)
								{
									setcolor(WHITE);
									outtextxy(420 + 8 * (i - 1), 375, password[i - 1]);
								}
								temp = i;
								tmp = i;
								setcolor(BLACK);
								password[i] = x;
								if (i > 0) outtextxy(420 + 8 * (i - 1), 375, "*");
								outtextxy(420 + 8 * i, 375, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								if(temp==i&&i>=tmp) { outtextxy(420 + 8 * i, 375, password[i]); }
								else outtextxy(420 + 8 * i, 375, "*");
								password[i] = '\0';
							}
						}
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 375, "▏");
							password[i] = '\0'; mi = i;    break;
						}
					}
				}
			}
			if (msg.x >= 395 && msg.x <= 440 && msg.y >= 425 && msg.y <= 449)//部门按钮
			{
				flag = true;
				putimage(455, 428, &img3);
				putimage(515, 427, &img5);
				putimage(395, 425, &img2);
				open = 1;
				msg = GetMouseMsg();
			}
			if (msg.x >= 455 && msg.x <= 501 && msg.y >= 428 && msg.y <= 451)//教师按钮
			{
				flag = true;
				putimage(395, 425, &img1);
				putimage(515, 427, &img5);
				putimage(455, 428, &img4);
				msg = GetMouseMsg();
				open = 2;
			}
			if (msg.x >= 515 && msg.x <= 560 && msg.y >= 427 && msg.y <= 450)//学生按钮
			{
				flag = true;
				putimage(455, 428, &img3);
				putimage(395, 425, &img1);
				putimage(515, 427, &img6);
				msg = GetMouseMsg();
				open = 3;
			}
			if (msg.x >= 455 && msg.x <= 565 && msg.y >= 485 && msg.y <= 526)//登录按钮
			{
				bool f = true;
				switch (open)
				{
				case 0: 
				{
					//putimage(395, 302, &img8, SRCINVERT );//XOR 登录类型失败
					f = false;
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "登录类型未选", "错误", MB_TASKMODAL);
					break;
				}
				case 1: 
				{
					freopen("bm.in", "r", stdin);
					f = finduser();
					break; 
				}
				case 2: 
				{
					freopen("js.in", "r", stdin);
					f = finduser();
					break;
				}
				case 3:
				{
					freopen("xs.in", "r", stdin);
					f = finduser();
					break;
				}
				
				}
				if (f) {
					//iflogin = true;
					return true;
				}
				else if(open!=0)
				{
					fclose(stdin); 
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "登录账号或密码错误", "错误", MB_TASKMODAL);
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				iflogin = true;
				return false;
			}
		}
	}
}
void exited()//退出界面
{
	iflogin = false;
	cleardevice();
	init();
	putlogin();
	open = 0;
	ui = 0; mi = 0; num = 0;
	fclose(stdin);
}
void putxgmm()//修改密码界面
{
	cleardevice();
	init();
	settextstyle(15, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(900, 120, "退出");
	IMAGE img,img1,img2;
	loadimage(&img, "页眉.jpg", 1030, 100);
	putimage(0, 0, &img);
	loadimage(&img1, "改密码.jpg", 450, 114);
	putimage(300, 300, &img1);
	loadimage(&img2,"确定.jpg", 356, 46);
	putimage(400, 450, &img2);
}
void xgmm()//修改密码
{
	int t;
	putxgmm();
	MOUSEMSG msg;
	bool flag = false,flag1=false;
	char x;
	int i,temp=0,tmp=0,temp1=0,tmp1=0;
	msg = GetMouseMsg();
	ui = 0; mi = 0;
	IMAGE img, img1, img2;
	loadimage(&img, "改密码失败.jpg", 434, 208);
	loadimage(&img1, "改密码提示.jpg", 249, 94);
	loadimage(&img2, "白色背景.jpg", 249, 94);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(200, 250, "不能使用全部重复的密码以及全是连续数字的密码");
	fclose(stdin);
	while (1)
	{
		msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return;
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 300 && msg.y <= 350)//新密码
			{
				i = ui; flag = true; temp1 = i - 1;
				putimage(755, 295, &img1);
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 315, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 315, "▏");
							putimage(755, 295, &img2);
							user[i] = '\0'; ui = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						x = _getch();
						if (x == 9)
						{
							putimage(755, 295, &img2);
							user[i] = '\0'; ui = i;
							goto pas;
						}
						else if (x != '\10')//退格键
						{
							if (i < 38)
							{
								if (i > 0)
								{
									setcolor(WHITE);
									outtextxy(420 + 8 * (i - 1), 315, user[i - 1]);
								}
								temp1 = i;
								tmp1 = i;
								setcolor(BLACK);
								user[i] = x;
								if (i > 0) outtextxy(420 + 8 * (i - 1), 315, "*");
								outtextxy(420 + 8 * i, 315, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								if (temp1 == i&&i >= tmp1) { outtextxy(420 + 8 * i, 315, user[i]); }
								else outtextxy(420 + 8 * i, 315, "*");
								user[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 360 && msg.y <= 414)//确认新密码
			{
				flag = true;
			pas: i = mi; temp = i - 1;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 375, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						start = clock();
					}
					//freopen("in.txt", "r", stdin);
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								if (i > 0)
								{
									setcolor(WHITE);
									outtextxy(420 + 8 * (i - 1), 375, password[i - 1]);
								}
								temp = i;
								tmp = i;
								setcolor(BLACK);
								password[i] = x;
								if (i > 0) outtextxy(420 + 8 * (i - 1), 375, "*");
								outtextxy(420 + 8 * i, 375, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								if (temp == i&&i >= tmp) { outtextxy(420 + 8 * i, 375, password[i]); }
								else outtextxy(420 + 8 * i, 375,"*");
								password[i] = '\0';
							}
						}
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 375, "▏");
							password[i] = '\0'; mi = i;    break;
						}
					}
				}
			}
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				flag1 = false;
				if (strcmp(user, password) == 0)
				{
					if (strlen(user) <= 14 && strlen(user) >= 6)
					{
						flag1 = true;
						rep(i, 0, strlen(user))
							if (user[i] == ' ')
							{
								flag1 = false;
								break;
							}
					}
					char a[12] = "01234567890";
					int next[20] = { 0 };
					i = 1;
					int j = 0;
					next[0] = 0;
					next[1] = 0;
					while (i<strlen(user))
					{
						if (j==0||user[i] == user[j])
						{
							i++;
							j++;
							next[i] = j;
						}
						else j = next[j];
					}
					rep(i, 0, strlen(user))
						if (next[i] >= strlen(user)-2) flag1 = false;
					i = 0, j = 0;
					while (i < strlen(a) && j < strlen(user))
					{
						if (a[i] == user[j]) { i++; j++; continue; }
						else {
							if (j != 0) j = next[j];
							else { i++; j = 1; }
						}
					}
					if (j >= strlen(user)) flag1 = false;
				}
				if (flag1) break;
				else {
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "设置密码不符合要求！", "错误", MB_TASKMODAL);
					cleardevice();
					putxgmm();
					settextstyle(20, 0, "宋体");//字体
					settextcolor(BLACK);//字体颜色
					outtextxy(200, 250, "不能使用全部重复的密码以及全是连续数字的密码");
					temp = 0; tmp = 0; temp1 = 0; tmp1 = 0;
					ui = 0; mi = 0;
				}
			}
		}
	}
	cleardevice();
	init();
	settextstyle(90, 0, "楷体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	if (open == 1)
		freopen("bm.in", "r", stdin);
	if (open == 2)
		freopen("js.in", "r", stdin);
	if (open==3)
		freopen("xs.in", "r", stdin);
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(LOGIN[i].user);
		gets_s(LOGIN[i].mail);
		gets_s(LOGIN[i].password);
		scanf("%d", &LOGIN[i].num);
	}
	fclose(stdin);
	if(open==1)
	 fp=fopen("bm.in", "w" );
	if (open == 2)
		fp = fopen("js.in", "w");
	if (open == 3)
		fp = fopen("xs.in", "w");
	fprintf(fp,"%d\n", t);
	rep(i, 0, t)
	{
		fputs(LOGIN[i].user,fp);
		fprintf(fp, "\n");
		fputs(LOGIN[i].mail,fp);
		fprintf(fp, "\n");
		if (i != num)
			fputs(LOGIN[i].password,fp);
		else
			fputs(user,fp);
		fprintf(fp, "\n");
		fprintf(fp,"%d\n", LOGIN[i].num);
	}
	fclose(fp);
	exited();
	return;
}
void putcaozuo()//操作界面
{
	IMAGE img;
	int i,n;
	loadimage(&img, "页眉.jpg", 1030, 100);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);//字体背景透明
	settextstyle(15, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(900, 120, "退出");
	outtextxy(800, 120, "修改密码");
	settextcolor(BLACK);//字体颜色
	outtextxy(650, 120, "欢迎您,");
	n = strlen(user);
	rep(i,0,n)
	outtextxy(698+8*i, 120, user[i]);
}
void putcaozuo2(int i)//教师操作界面
{
	IMAGE img, img1;
	loadimage(&img, "申请开课.jpg", 356, 46);
	putimage(322, 300, &img);
	loadimage(&img1, "本课学生.jpg", 356, 46);
	putimage(322, 500, &img1);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(RED);//字体颜色
	outtextxy(200, 150, "教师姓名：");
	settextcolor(BLUE);//字体颜色
	outtextxy(300, 150, jsphone[i].name);
	settextcolor(RED);//字体颜色
	outtextxy(370, 150, "电话：");
	settextcolor(BLUE);//字体颜色
	outtextxy(430, 150, jsphone[i].phone);
	settextcolor(RED);//字体颜色
	outtextxy(530, 150, "宿舍：");
	settextcolor(BLUE);//字体颜色
	outtextxy(590, 150, jsphone[i].address);
}
void putcaozuo1()//生成操作1按钮
{
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 150, "给学生发布通知");
	IMAGE img, img1;
	if (num == 1)
	{
		loadimage(&img, "录入学生.jpg", 356, 46);
		putimage(322, 300, &img);
	}
	else if (num == 2)
	{
		loadimage(&img, "录入课程.jpg", 356, 46);
		putimage(322, 300, &img);
	}
	else if (num == 3)
	{
		loadimage(&img, "录入选课.jpg", 356, 46);
		putimage(322, 300, &img);
	}
	else if (num == 4)
	{
		loadimage(&img, "录入学生成绩.jpg", 356, 46);
		putimage(322, 300, &img);
	}
	else if (num == 5)
	{
		IMAGE img2;
		loadimage(&img2, "增加教师账号.jpg", 356, 46);
		putimage(322, 400, &img2);
		loadimage(&img, "查看密码.jpg", 356, 46);
		putimage(322, 300, &img);
	}
	if (num != 5)
	{
		loadimage(&img1, "统计成绩.jpg", 356, 46);
		putimage(322, 500, &img1);
	}
	else
	{
		loadimage(&img1, "注销用户.jpg", 356, 46);
		putimage(322, 500, &img1);
	}
}
void putxstz(int &t)//学生通知读入数组
{
	t = 0;
	fclose(stdin);
	freopen("tz.in", "r", stdin);
	while (s(sqlist[t].num) != EOF)
	{
		getchar();
		cin >> sqlist[t++].name;
	}
	fclose(stdin);
}
void printfxstz(int t)//学生通知输入文件中
{
	int i;
	fp = fopen("tz.in", "w");
	rep(i, 0, t)
	{
		fprintf(fp, "%d\n",sqlist[i].num);
		fputs(sqlist[i].name.c_str(), fp);
		fprintf(fp, "\n");
	}
	fclose(fp);
}
void xsjskc(int &t)//显示教师课程
{
	if (jscx[num].sl == 0)
	{
		settextstyle(20, 0, "宋体");//字体
		settextcolor(BLUE);//字体颜色
		outtextxy(200, 200, "您还没有课程！");
	}
	else
	{
		int j;
		settextstyle(20, 0, "宋体");//字体
		settextcolor(GREEN);//字体颜色
		outtextxy(350, 320, "请点击课程名称选择您要查询的课程");
		settextcolor(BLUE);//字体颜色
		outtextxy(200, 320, "您的课程如下");
		settextcolor(BLACK);//字体颜色
		kmcx();
		int temp = 0, temp1 = 5;
		rep(j, 0, jscx[num].sl)
		{
			if ((j - temp * temp1) > 4) temp++;
			outtextxy(200 + 155 * (j - temp*temp1), 350 + 30 * temp, km[jscx[num].kc[j]].name);
		}
	}
}
void displaykcmd(int &temp,int i,int ps, int ks)//显示课程名单
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(50, 150, "平时成绩平均分:");
	settextcolor(RED);//字体颜色
	change(ps);
	outtextxy(210, 150, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(250, 150, "考试成绩平均分:");
	settextcolor(RED);//字体颜色
	change(ks);
	outtextxy(410, 150, write);
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 200, "课程中学生及学生该课的成绩如下");
	outtextxy(220, 250, "学号");
	outtextxy(375, 250, "考试成绩");
	outtextxy(530, 250, "平时成绩");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >=10) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	outtextxy(50, 200, km[i].name);
	j = (kmxs[i].sl / 10);
	if (kmxs[i].sl % 10) j++;
	change(j);
	outtextxy(530, 700, write);
	rep(j, temp, kmxs[i].sl)
	{
		int tmp = temp / 10 + 1;
		change(tmp);
		outtextxy(410, 700, write);
		outtextxy(200, 350 + 30 * (j-temp), number[kmxs[i].xs[j]].user);
		if (xscj[kmxs[i].xs[j]].ks[i] != -1)
		{
			change(xscj[kmxs[i].xs[j]].ks[i]);
			outtextxy(420, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(420, 350 + 30 * (j - temp), "未录入");
		}
		if (xscj[kmxs[i].xs[j]].ps[i] != -1)
		{
			change(xscj[kmxs[i].xs[j]].ps[i]);
			outtextxy(560, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(560, 350 + 30 * (j - temp), "未录入");
		}
		if (!((1+j) % 10)) break;
	}
	temp += 10;
	settextcolor(BLUE);//字体颜色
	if (temp < kmxs[i].sl) outtextxy(700, 700, "下一页");
}
bool kcmd(int i)//课程学生名单
{
	int temp = 0,j,z=0,ps=0,ks=0;
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	settextstyle(90, 0, "楷体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	if (!fcxxskm)
	{
		cxxskm();
		fcxxskm = true;
	}
	if (!fcxxscj)
	{
		cxxscj();
		fcxxscj = true;
	}
	putxsuser();
	rep(j, 0, kmxs[i].sl)
	{
		if (xscj[kmxs[i].xs[j]].ks[i] != -1)
		{
			ks += xscj[kmxs[i].xs[j]].ks[i];
			z++;
		}
		if (xscj[kmxs[i].xs[j]].ps[i] != -1)
			ps += xscj[kmxs[i].xs[j]].ps[i];
	}
	if (z != 0)
	{
		ks /= z;
		ps /= z;
	}
	settextstyle(90, 0, "楷体");//字体
	settextcolor(WHITE);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	if (kmxs[i].sl == 0)
	{
		settextstyle(20, 0, "宋体");//字体
		settextcolor(BLUE);//字体颜色
		outtextxy(200, 200, "该课程没有学生！");
	}
	else
	{
		displaykcmd(temp,i,ps,ks);
	}
	bool flag = false;
	int t;
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x>=700 && msg.x<=748 && msg.y>=700 && msg.y<=720 && temp<kmxs[i].sl)//下一页
			{
				displaykcmd(temp, i,ps,ks);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp>=20)//上一页
			{
				temp -= 20;
				displaykcmd(temp, i,ps,ks);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void cxkc()//查询课程按钮
{
	int t=0,i;
	int temp = 0, temp1 = 5;
	cleardevice();
    init();
	putcaozuo();
	MOUSEMSG msg;
	bool flag = false;
	fkcmd = false;
	msg = GetMouseMsg();
	xsjskc(t);
	while (1)
	{
			msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			rep(i, 0, jscx[num].sl)
			{
				if ((i - temp*temp1) > 4) temp++;
				int tmp = 10*strlen(km[jscx[num].kc[i]].name);
				if (msg.x >= 200 + 155 * (i - temp*temp1) && msg.x <= 200 + 155 * (i - temp*temp1) + tmp && msg.y >= 350 + 30 * temp && msg.y <= 370 + 30 * temp)
				{
					   if (kcmd(jscx[num].kc[i]))
						   fkcmd=true;
					   return;
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return;
			}
		}
	}
}
void putjssq(int x)
{
	IMAGE img1, img2;
	loadimage(&img1, "开课.jpg", 450, 114);
	putimage(300, 300, &img1);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(800, 315, "当前还剩   个申请名额");
	outtextxy(800, 345, "每人只能同时申请一次");
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	change(1000-x);
	outtextxy(882, 315, write);
	loadimage(&img2, "确定.jpg", 356, 46);
	putimage(400, 450, &img2);
}
void readjssq(int &t)//读取申请列表
{
	fclose(stdin);
	freopen("sqlist.in", "r", stdin);
	s(t);
	int i;
	rep(i, 0, t)
	{
		cin >> sqlist[i].name;
		s(sqlist[i].xf);
		s(sqlist[i].num);
	}
	fclose(stdin);
}
void printfjssq(int t)
{
	fp = fopen("sqlist.in", "w");
	fprintf(fp, "%d\n", t);
	int i;
	rep(i, 0, t)
	{
		fputs(sqlist[i].name.c_str(),fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", sqlist[i].xf);
		fprintf(fp, "%d\n", sqlist[i].num);
	}
	fclose(fp);
}
bool jssq()//教师申请
{
	int t, i, temp, temp1, tmp1, fi = 0;
	readjssq(t);
	cleardevice();
	init();
	putcaozuo();
	putback();
	putjssq(t);
	MOUSEMSG msg;
	bool flag = false;
	char x,jyxf[100]="";
	string str="";
	msg = GetMouseMsg();
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	HWND hWnd = GetHWnd();
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN||(!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 300 && msg.y <= 350)//课程名称
			{
				flag = true;
				while (1)
				{
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							//str += '\0';
							  break;
						}
					}
					if (_kbhit())	//如果是ASCII输入	
					{
						char c = _getch();
						if (c == '\b')
						{
							if (str.length()>0)
							{
								setcolor(WHITE);
								outtextxy(420, 315, str.c_str());
								if (str.at(str.length() - 1) & 0x8000)
									str.erase(str.end() - 1);
								str.erase(str.end() - 1);
							}
						}
						else {
							str += c;
						}
					}
					else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中	
					{
						GetIMEString(hWnd, str);
					}
					setcolor(BLACK);
					outtextxy(420, 315, str.c_str());
				 }
			  }
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 360 && msg.y <= 414)//建议学分
			{
				 flag = true;
				 i = fi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 375, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 375, "▏");
							jyxf[i] = '\0'; fi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 375, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								jyxf[i] = x;
								outtextxy(420 + 8 * i, 375, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(420 + 8 * i, 375, jyxf[i]);
								jyxf[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				if (t == 1000)//申请列表已满
				{
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "没有申请名额", "错误", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putjssq(t);
					settextstyle(20, 0, "宋体");//字体
					settextcolor(BLACK);//字体颜色
					outtextxy(420, 315, str.c_str());
					outtextxy(420, 375, jyxf);
				}
				else
				{
					bool cf = false;
					int u=toint(LOGIN[num].user);
					rep(i, 0, t)
					{
						if (u == sqlist[i].num)
						{
							cf = true;
							break;
						}
					}
					if (cf)
					{
						HWND hWnd1 = GetHWnd();
						MessageBox(hWnd1, "您已申请过了", "错误", MB_TASKMODAL);
						cleardevice();
						init();
						putcaozuo();
						putback();
						putjssq(t);
						settextstyle(20, 0, "宋体");//字体
						settextcolor(BLACK);//字体颜色
						outtextxy(420, 315, str.c_str());
						outtextxy(420, 375, jyxf);
					}
					else
					{
						sqlist[t].name = str;
						temp = toint(jyxf);
						sqlist[t].xf = temp;
						sqlist[t].num = u;
						t++;
						printfjssq(t);
						HWND hWnd1 = GetHWnd();
						MessageBox(hWnd1, "申请成功", "成功", MB_TASKMODAL);
						cleardevice();
						init();
						putcaozuo();
						putcaozuo2(num);
						return true;
					}
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo2(num);
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void putfunction1()//录入学生界面
{
	IMAGE img;
	loadimage(&img, "确定.jpg", 356, 46);
	putimage(400, 450, &img);
	settextstyle(25, 0, "宋体");//字体
	settextcolor(RED);//字体颜色
	outtextxy(100, 150, "请按以下格式输入到文件temp.txt中");
	outtextxy(100, 180, "，并将文件与此程序放置同一文件夹中，然后按确定");
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(100, 205, "将输入学生数量(一次不能超过1000)");
	outtextxy(100, 230, "学号(不能有重复)");
	outtextxy(100, 255, "姓名");
	outtextxy(100, 280, "性别");
	outtextxy(100, 305, "年龄");
	outtextxy(100, 330, "宿舍号码");
	outtextxy(100, 355, "电话号码");
}
bool panfunction1()
{
	int t,i,j,n,k,m;
	char temp[100], boy[10]="男", girl[10]="女";
	fclose(stdin);
	if (freopen("temp.txt", "r", stdin) == NULL) return true;
	if(s(t)==EOF) return true;
	getchar();
	if (t <= 1000)
	{
		rep(i, 0, t)
		{
			insert[i].num = i;
			gets_s(insert[i].user);
			rep(j, 0, strlen(insert[i].user))
				if (insert[i].user[j]<'0' || insert[i].user[j] > '9')
					return true;
			//getchar();
			gets_s(insert[i].name);
			//getchar();
			gets_s(temp);
			if (strcmp(temp, boy) == 0)
				insert[i].sex = 0;
			else if (strcmp(temp, girl) == 0)
				insert[i].sex = 1;
			else return true;
			//getchar();
			gets_s(temp);
			rep(j, 0, strlen(temp))
				if (temp[j]<'0' || temp[j] > '9')
					return true;
			insert[i].age = toint(temp);
			//getchar();
			gets_s(temp);
			rep(j, 0, strlen(temp))
				if (temp[j]<'0' || temp[j] > '9')
					return true;
			insert[i].ss = toint(temp);
			//getchar();
			gets_s(insert[i].phone);
			rep(j, 0, strlen(insert[i].phone))
				if (insert[i].phone[j]<'0' || insert[i].phone[j] > '9')
					return true;
		}
	}
	else
		return true;
	fclose(stdin);
	freopen("xs.in", "r", stdin);
	scanf("%d", &n);
	rep(i, 0, n)
	{
		getchar();
		gets_s(LOGIN[i].user);
		rep(j, 0, t)
			if (strcmp(LOGIN[i].user, insert[j].user) == 0) return true;
		gets_s(LOGIN[i].mail);
		gets_s(LOGIN[i].password);
		scanf("%d", &LOGIN[i].num);
	}
	cleardevice();
	init();
	putcaozuo();
	putback();
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[                  ]读取中..0%");
	fclose(stdin);
	fp = fopen("xs.in", "w");
	fprintf(fp, "%d\n", t+n);
	rep(i, 0, n)
	{
		fputs(LOGIN[i].user, fp);
		fprintf(fp, "\n");
		fputs(LOGIN[i].mail, fp);
		fprintf(fp, "\n");
		fputs(LOGIN[i].password, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", LOGIN[i].num);
	}
	rep(i, 0, t)
	{
		rep(j, 0, 3)
		{
			fputs(insert[i].user, fp);
			if (j == 1) fprintf(fp, "@163.com");
			fprintf(fp, "\n");
		}
		fprintf(fp, "%d\n", insert[i].num+n);
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[                  ]读取中..0%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉                ]读取中..10%");
	cxxs(n);
	findclass(m);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉                ]读取中..10%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	fp = fopen("xsxx.in", "w");
	fprintf(fp, "%d\n", n + t);
	rep(i, 0, n)
	{
		fprintf(fp,"%d\n", xscx[i].num);
		fputs(xscx[i].name,fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", xscx[i].sex);
		fprintf(fp, "%d\n", xscx[i].age);
		fprintf(fp, "%d\n", xscx[i].ss);
		fputs(xscx[i].phone,fp);
		fprintf(fp,"\n");
		fprintf(fp, "%d\n", xscx[i].xf);
		int j = 0;
		rep (j,0,xscx[i].sl)
		{
			fprintf(fp,"%d ", xscx[i].kc[j]);
		}
		fprintf(fp, "0\n");
	}
	rep(i, 0, t)
	{
		fprintf(fp, "%d\n", insert[i].num+n);
		fputs(insert[i].name, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", insert[i].sex);
		fprintf(fp, "%d\n", insert[i].age);
		fprintf(fp, "%d\n", insert[i].ss);
		fputs(insert[i].phone, fp);
		fprintf(fp, "\n");
		fprintf(fp, "0\n");
		fprintf(fp, "0\n");
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	cxxscj();
	rep(i, 0, t)
	{
		//二分
		char insertbj[20];
		strcpy(insertbj, insert[i].user);
		insertbj[10] = 0;
		int l = 0, r = m - 1;
		while (1)
		{
			if (l >= r) break;
			int mid = l + (r - l) / 2;
			if (strcmp(insertbj, cls[mid].bj) <= 0) r = mid;
			else l = mid + 1;
		}
		if (strcmp(insertbj, cls[l].bj) == 0)
			xscls[cls[l].num].xs[xscls[cls[l].num].sl++] = n + insert[i].num;
		else
		{
			strcpy(cls[m].bj, insertbj);
			cls[m].num = m;
			xscls[m].num = m;
			xscls[m].sl = 1;
			xscls[m].xs[0] = n + insert[i].num;
			if (strcmp(cls[m].bj, cls[m - 1].bj) < 0)
			{
				m++;
				sort(cls, cls + m,cmpcls);
			}
			else
				m++;
		}
	}
	fp = fopen("class.in", "w");
	fprintf(fp, "%d\n", m);
	rep(i, 0, m)
	{
		fputs(cls[i].bj, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", cls[i].num);
	}
	fclose(fp);
	fp = fopen("xsclass.in", "w");
	fprintf(fp, "%d\n", m);
	rep(i, 0, m)
	{
		fprintf(fp, "%d\n", xscls[i].num);
		fprintf(fp, "%d\n", xscls[i].sl);
		int j;
		rep(j, 0, xscls[i].sl)
			fprintf(fp, "%d ", xscls[i].xs[j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	freopen("xscj.in", "r", stdin);
	s(k);//科目数量
	fclose(stdin);
	fp = fopen("xscj.in", "w");
	fprintf(fp, "%d\n", k);
	fprintf(fp, "%d\n", n + t);
	rep(i, 1, k+1)
	{
		rep(j, 0, n)
			fprintf(fp, "%d\n", xscj[j].ps[i]);
		rep(j, 0, t)
			fprintf(fp, "-1\n");
		rep(j, 0, n)
			fprintf(fp,"%d\n",xscj[j].ks[i]);
		rep(j, 0, t)
			fprintf(fp, "-1\n");
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
	return false;
}
void putfunction3()
{
	IMAGE img;
	loadimage(&img, "确定.jpg", 356, 46);
	putimage(400, 450, &img);
	settextstyle(25, 0, "宋体");//字体
	settextcolor(RED);//字体颜色
	outtextxy(100, 150, "请按以下格式输入到文件temp.txt中");
	outtextxy(100, 180, "，并将文件与此程序放置同一文件夹中，然后按确定");
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(100, 205, "将输入学生数量(一次不能超过1000)");
	outtextxy(100, 230, "学号");
	outtextxy(100, 255, "选课数量(一次不能超过10门)");
	outtextxy(100, 280, "课程编号(用空格隔开)");
}
bool panfunction3()
{
	int n,t,i,m;
	putfunction3();
	fclose(stdin);
	freopen("xskm.in", "r",stdin);
	if(s(m)==EOF) return true;
	fclose(stdin);
	freopen("xs.in", "r", stdin);
	if(s(n)==EOF) return true;
	fclose(stdin);
	if (freopen("temp.txt", "r", stdin) == NULL) return true;
	if(s(t)==EOF) return true;
	if (t > 1000) return true;
	rep(i, 0, t)
	{
		getchar();
		gets_s(xsxk[i].xh);
		int j;
		rep(j, 0, strlen(xsxk[i].xh))
			if (xsxk[i].xh[j]<'0' || xsxk[i].xh[j]>'9') return true;
		if(s(xsxk[i].sl)==EOF) return true;
		if (xsxk[i].sl > 10) return true;
		rep(j, 1, xsxk[i].sl+1)
			if(s(xsxk[i].bh[j])==EOF) return true;
	}
	fclose(stdin);
	cleardevice();
	init();
	putcaozuo();
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉                ]读取中..10%");
	putxsuser();
	cxxskm();
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉                ]读取中..10%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	rep(i, 0, t)
	{
		bool flag1 = false;
		int j;
		rep(j, 0, n)
		{
			if (!strcmp(xsxk[i].xh, number[j].user))
			{
				flag1 = true;
				break;
			}
		}
		if (!flag1) return true;
		xsxk[i].num = number[j].num;
		rep(j, 1, xsxk[i].sl+1)
		{
			flag1 = false;
			int z;
			rep(z, 1, m + 1)
				if (xsxk[i].bh[j] == kmxs[z].num)
				{
					flag1 = true;
					xsxk[i].knum[j] = z;
					break;
				}
			if (!flag1) return true;
		}
	}
	rep(i, 0, t)
	{
		int j;
		rep(j, 1, xsxk[i].sl+1)
		{
			int z;
			bool flag1 = false;
			rep(z, 0, kmxs[xsxk[i].knum[j]].sl)
			{
				if (kmxs[xsxk[i].knum[j]].xs[z] == xsxk[i].num)
					flag1 = true;
			}
			if (!flag1)
			{
				kmxs[xsxk[i].knum[j]].xs[kmxs[xsxk[i].knum[j]].sl++] = xsxk[i].num;
				kmxs[xsxk[i].knum[j]].xs[kmxs[xsxk[i].knum[j]].sl] = -1;
			}
		}
	}
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	fp = fopen("xskm.in", "w");
	fprintf(fp, "%d\n", m);
	rep(i, 1, m + 1)
	{
		fprintf(fp,"%d\n",kmxs[i].num);
		int j;
		rep(j, 0, kmxs[i].sl)
			fprintf(fp, "%d ", kmxs[i].xs[j]);
		fprintf(fp, "-1\n");
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
	return false;
}
void putfunction4() 
{
	IMAGE img;
	loadimage(&img, "确定.jpg", 356, 46);
	putimage(400, 450, &img);
	settextstyle(25, 0, "宋体");//字体
	settextcolor(RED);//字体颜色
	outtextxy(100, 150, "请按以下格式输入到文件temp.txt中");
	outtextxy(100, 180, "，并将文件与此程序放置同一文件夹中，然后按确定");
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(100, 205, "将输入学生数量(一次不能超过1000)");
	outtextxy(100, 230, "学号");
	outtextxy(100, 255, "登记课程数量(500以内)");
	outtextxy(100, 280, "课程编号(不能有重复)");
	outtextxy(100, 305, "平时成绩和期末成绩(用空格隔开)");
}
bool panfunction4()
{
	int i,t,j,n,m;
	fclose(stdin);
	freopen("temp.txt", "r", stdin);
	if(s(t)==EOF) return true;
	if (t > 1000) return true;
	rep(i, 0, t)
	{
		getchar();
		gets_s(cjlr[i].xh);
		rep(j, 0, strlen(cjlr[i].xh))
		{
			if (cjlr[i].xh[j]<'0' || cjlr[i].xh[j]>'9') return true;
		}
		if(s(cjlr[i].sl)==EOF) return true;
		rep(j, 0, cjlr[i].sl)
		{
			if (s(cjlr[i].bh[j]) == EOF) return true;
			int z;
			rep(z, 0, j)
			{
				if (cjlr[i].bh[j] == cjlr[i].bh[z]) return true;
			}
		}
		rep(j, 0, cjlr[i].sl)
		{
			if (s(cjlr[i].ps[j]) == EOF) return true;
			if (cjlr[i].ps[j]<0) return true;
			if (s(cjlr[i].ks[j]) == EOF) return true;
			if (cjlr[i].ks[j] < 0) return true;
		}
	}
	fclose(stdin);
	freopen("xs.in", "r", stdin);
	s(n);
	fclose(stdin);
	freopen("km.in", "r", stdin);
	s(m);
	fclose(stdin);
	putxsuser();
	kmcx();
	cleardevice();
	init();
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[                  ]读取中..0%");
	setcolor(BLACK);
	rep(i, 0, t)
	{
		bool flag1 = true;
		rep(j,0,n)
		{
			if(strcmp(cjlr[i].xh,number[j].user)==0)
			{
				cjlr[i].xsnum = number[j].num;
				flag1 = false;
				break;
			}
		}
		if (flag1) return true;
		setcolor(WHITE);
		settextstyle(25, 0, "宋体");//字体
		outtextxy(300, 400, "[                  ]读取中..0%");
		setcolor(BLACK);
		settextstyle(25, 0, "宋体");//字体
		outtextxy(300, 400, "[▉                ]读取中..10%");
		rep(j, 0, cjlr[i].sl)
		{
			int z;
			flag1 = true;
			rep(z, 1, m+1)
			{
				if (cjlr[i].bh[j] == km[z].num)
				{
					cjlr[i].num[j] = z;
					flag1 = false;
					break;
				}
			}
			if (flag1) return true;
		}
	}
	cxxscj();
	cxxs(n);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉                ]读取中..10%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	cxkmxx(m);
	rep(i, 0, t)
	{
		rep(j, 0, cjlr[i].sl)
		{
			if(kmxx[cjlr[i].num[j]].y == 1&&kmxx[cjlr[i].num[j]].xq>=2 && xscj[cjlr[i].xsnum].ks[cjlr[i].num[j]]!=-1)
			{
				if (xscj[cjlr[i].xsnum].ks[cjlr[i].num[j]] < 60) xscj[cjlr[i].xsnum].ks[cjlr[i].num[j]] = max(cjlr[i].ks[j] - kmxx[cjlr[i].num[j]].jd,0);
				if (xscj[cjlr[i].xsnum].ps[cjlr[i].num[j]] < 60) xscj[cjlr[i].xsnum].ps[cjlr[i].num[j]] = max(cjlr[i].ps[j] - kmxx[cjlr[i].num[j]].jd, 0);
			}
			else
			{
				xscj[cjlr[i].xsnum].ks[cjlr[i].num[j]] = cjlr[i].ks[j];
				xscj[cjlr[i].xsnum].ps[cjlr[i].num[j]] = cjlr[i].ps[j];
			}
		}
	}
	bjg(n,m,t);//修改了学生成绩，学生详细信息
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	fp = fopen("xsxx.in", "w");
	fprintf(fp, "%d\n", n);
	rep(i, 0, n)
	{
		fprintf(fp, "%d\n", xscx[i].num);
		fputs(xscx[i].name, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", xscx[i].sex);
		fprintf(fp, "%d\n", xscx[i].age);
		fprintf(fp, "%d\n", xscx[i].ss);
		fputs(xscx[i].phone, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", xscx[i].xf);
		int j = 0;
		while (xscx[i].kc[j] != 0)
		{
			fprintf(fp, "%d ", xscx[i].kc[j]);
			j++;
		}
		fprintf(fp, "0\n");
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	fp = fopen("xscj.in", "w");
	fprintf(fp, "%d\n", m);
	fprintf(fp, "%d\n", n);
	rep(i, 1, m + 1)
	{
		rep(j, 0, n)
			fprintf(fp, "%d\n", xscj[j].ps[i]);
		rep(j, 0, n)
			fprintf(fp, "%d\n", xscj[j].ks[i]);
	}
	fclose(fp);
	setcolor(WHITE);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	setcolor(BLACK);
	settextstyle(25, 0, "宋体");//字体
	outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
	return false;
}
void putfunction5()
{
	IMAGE img, img1;
	loadimage(&img, "管理员.jpg", 356, 46);
	loadimage(&img1, "教师学生.jpg", 356, 46);
	putimage(322, 300, &img);
	putimage(322, 500, &img1);
}
bool bmmm()//部门密码
{
	int t, i, j;
	cleardevice();
	init();
	putcaozuo();
	fclose(stdin);
	freopen("bm.in", "r", stdin);
	putback();
	s(t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(bm[i].user);
		gets_s(bm[i].mail);
		gets_s(bm[i].password);
		scanf("%d", &bm[i].num);
	}
	fclose(stdin);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(220, 250, "账号");
	outtextxy(375, 250, "密码");
	settextcolor(BLACK);//字体颜色
	rep(j, 1, t + 1)
	{
		outtextxy(200, 350 + 30 * (j), bm[j].user);
		outtextxy(420, 350 + 30 * (j), bm[j].password);
	}
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putfunction5();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void putjsxsmm()//教师学生密码选择界面
{
	IMAGE img, img1;
	loadimage(&img, "教师账号.jpg", 356, 46);
	putimage(322, 300, &img);
	loadimage(&img1, "学生账号.jpg", 356, 46);
	putimage(322, 500, &img1);
}
void displaymm(int &temp,int t)//显示课程名单
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(220, 250, "帐号");
	outtextxy(440, 250, "密码");
	outtextxy(350, 700, "当前第    页，共      页");
	if (temp >= 10) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = (t / 10) + 1;
	change(j);
	outtextxy(515, 700, write);
	rep(j, temp, t)
	{
		int tmp = temp / 10 + 1;
		change(tmp);
		outtextxy(410, 700, write);
		outtextxy(200, 350 + 30 * (j - temp), number[j].user);
		outtextxy(420, 350 + 30 * (j - temp), number[j].password);
		if (!((1 + j) % 10)) break;
	}
	temp += 10;
	settextcolor(BLUE);//字体颜色
	if (temp < t) outtextxy(700, 700, "下一页");
}
bool jsmm()//显示教师密码
{
	int t, i,temp=0;
	fclose(stdin);
	freopen("js.in", "r", stdin);
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(number[i].user);
		gets_s(number[i].mail);
		gets_s(number[i].password);
		scanf("%d", &number[i].num);
	}
	fclose(stdin);
	displaymm(temp, t);
	MOUSEMSG msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<t)//下一页
			{
				displaymm(temp,t);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 20)//上一页
			{
				temp -= 20;
				displaymm(temp,t);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putjsxsmm();
				return true;
			}
			if (msg.x >= 900  && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool xsmm()//学生密码
{
	int t, i, temp = 0;
	fclose(stdin);
	freopen("xs.in", "r", stdin);
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(number[i].user);
		gets_s(number[i].mail);
		gets_s(number[i].password);
		scanf("%d", &number[i].num);
	}
	fclose(stdin);
	displaymm(temp, t);
	MOUSEMSG msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<t)//下一页
			{
				displaymm(temp, t);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 20)//上一页
			{
				temp -= 20;
				displaymm(temp, t);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putjsxsmm();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool jsxsmm()//选择教师或者学生显示密码
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putjsxsmm();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putfunction5();
				return true;
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//教师密码
			{
				if (!jsmm())
				{
					exited();
					return false;
				}
				msg = GetMouseMsg();
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//学生密码
			{
				if (!xsmm())
				{
					exited();
					return false;
				}
				msg = GetMouseMsg();
			}
		}
		if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
		{
			exited();
			return false;
		}
		if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
		{
			xgmm();
			return false;
		}
	}
}
void putnum2()//管理员页面显示还有多少个开课申请
{
	int t;
	fclose(stdin);
	freopen("sqlist.in","r",stdin);
	scanf("%d", &t);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(750, 150, "您还有    个开课申请未处理");
	settextcolor(GREEN);//字体颜色
	change(t);
	outtextxy(810, 150, write);
	fclose(stdin);
}
void pputnum2()//管理员页面显示还有多少个开课申请(辅助)
{
	int t;
	fclose(stdin);
	freopen("sqlist.in", "r", stdin);
	scanf("%d", &t);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(RED);//字体颜色
	outtextxy(750, 150, "您还有    个开课申请未处理");
	settextcolor(BLUE);//字体颜色
	change(t);
	outtextxy(810, 150, write);
	fclose(stdin);
}
bool function1()//录入学生信息
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putfunction1();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	bool flag = false;
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				if (panfunction1())//不符合输入格式
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "格式错误！", "失败", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putfunction1();
				}
				else
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "成功！", "结果", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putcaozuo1();
					return true;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool function3()//录入选课信息
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putfunction3();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	bool flag = false;
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				if (panfunction3())//不符合输入格式
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "格式错误！", "失败", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putfunction3();
				}
				else
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "成功！", "结果", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putcaozuo1();
					return true;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool function4()//录入学生成绩
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putfunction4();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	bool flag = false;
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				if (panfunction4())//不符合输入格式
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "格式错误！", "失败", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putfunction4();
				}
				else
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "成功！", "结果", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putcaozuo1();
					return true;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool function5()//查看密码
{
	
	cleardevice();
	init();
	putcaozuo();
	putback();
	putfunction5();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//管理员
			{
				if (!bmmm())
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//教师学生
			{
				if (!jsxsmm())
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void jszxcz(int x)//教师账号注销操作
{
	int t,i,v,j;
	bool flag = false;
	readjssq(t);
	int temp = toint(number[x].user);
	rep(i, 0, t)
	{
		if (sqlist[i].num == temp)
		{
			flag = true;
			break;
		}
	}
	fp = fopen("sqlist.in", "w");
	if (flag) fprintf(fp, "%d\n", t-1);
	else fprintf(fp, "%d\n", t);
	rep(i, 0, t)
	{
		if (sqlist[i].num != temp)
		{
			fputs(sqlist[i].name.c_str(), fp);
			fprintf(fp, "\n");
			fprintf(fp, "%d\n", sqlist[i].xf);
			fprintf(fp, "%d\n", sqlist[i].num);
		}
	}
	fclose(fp);
	bool flag1 = false;
	if (freopen("sqjg.in", "r", stdin) != NULL)
	{
		while (s(temp) != EOF)
		{
			s(v);
			if (temp == toint(number[x].user))
			{
				flag1 = true;
				break;
			}
		}
	}
	fclose(stdin);
	if (flag1)
	{
		freopen("sqjg.in", "r", stdin);
		int i = 0, j;
		while (s(sqlist[i].num) != EOF)
		{
			s(sqlist[i++].xf);
		}
		fclose(stdin);
		fp = fopen("sqjg.in", "w");
		rep(j, 0, i)
		{
			if (sqlist[j].num == temp) continue;
			fprintf(fp, "%d\n", sqlist[j].num);
			fprintf(fp, "%d\n", sqlist[j].xf);
		}
		fclose(fp);
	}
	cxjs(t);
	fp = fopen("jsxx.in", "w");
	fprintf(fp, "%d\n", t-1);
	rep(i, 0, t)
	{
		if (i == x) continue;
		if(i<x)
		    fprintf(fp, "%d\n", jscx[i].num);
		else
			fprintf(fp, "%d\n", jscx[i].num-1);
		rep(j, 0, jscx[i].sl)
		{
			fprintf(fp, "%d ", jscx[i].kc[j]);
		}
		fprintf(fp, "0\n");
	}
	fclose(fp);
	fp = fopen("jsphone.in", "w");
	fprintf(fp, "%d\n", t - 1);
	rep(i, 0, t)
	{
		if (i == x) continue;
		if (i < x)
			fprintf(fp, "%d\n", jsphone[i].num);
		else
			fprintf(fp, "%d\n", jsphone[i].num - 1);
		fputs(jsphone[i].name, fp);
		fprintf(fp, "\n");
		fputs(jsphone[i].phone, fp);
		fprintf(fp, "\n");
		fputs(jsphone[i].address, fp);
		fprintf(fp, "\n");
	}
	fclose(fp);
	fp = fopen("js.in", "w");
	fprintf(fp, "%d\n", t-1);
	rep(i, 0, t)
	{
		if (i == x) continue;
		fputs(number[i].user, fp);
		fprintf(fp, "\n");
		fputs(number[i].mail, fp);
		fprintf(fp, "\n");
		fputs(number[i].password, fp);
		fprintf(fp, "\n");
		if (i < x)
			fprintf(fp, "%d\n", number[i].num);
		else
			fprintf(fp, "%d\n", number[i].num - 1);
	}
	fclose(fp);
	return;
}
void xszxcz(int x)//学生账号注销操作
{
	int i, n, j, t;
	fclose(stdin);
	freopen("xskm.in", "r", stdin);
	s(n);
	fclose(stdin);
	cxxskm();
	fp = fopen("xskm.in", "w");
	fprintf(fp, "%d\n", n);
	rep(i, 1, n + 1)
	{
		fprintf(fp, "%d\n", kmxs[i].num);
		rep(j, 0, kmxs[i].sl)
		{
			if (kmxs[i].xs[j] == x) continue;
			if(kmxs[i].xs[j]<x)
			fprintf(fp, "%d ", kmxs[i].xs[j]);
			else
				fprintf(fp, "%d ", kmxs[i].xs[j]-1);
		}
		fprintf(fp, "-1\n");
	}
	fclose(fp);
	cxxscj();
	fclose(stdin);
	freopen("xscj.in", "r", stdin);
	s(n);//科目数量
	s(t);//学生数量
	fclose(stdin);
	fp = fopen("xscj.in", "w");
	fprintf(fp, "%d\n", n);
	fprintf(fp, "%d\n", t-1);
	rep(i, 1, n + 1)
	{
		rep(j, 0, t)
			if (j == x) continue;
			else    
				fprintf(fp, "%d\n", xscj[j].ps[i]);
		rep(j, 0, t)
			if (j == x) continue;
			else
				fprintf(fp, "%d\n", xscj[j].ks[i]);
	}
	fclose(fp);
	cxxs(t);
	fp = fopen("xsxx.in", "w");
	fprintf(fp, "%d\n", t-1);
	rep(i, 0, t)
	{
		if (i == x) continue;
		if(i<x)
		fprintf(fp, "%d\n", xscx[i].num);
		else
			fprintf(fp, "%d\n", xscx[i].num-1);
		fputs(xscx[i].name, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", xscx[i].sex);
		fprintf(fp, "%d\n", xscx[i].age);
		fprintf(fp, "%d\n", xscx[i].ss);
		fputs(xscx[i].phone, fp);
		fprintf(fp, "\n");
		fprintf(fp, "%d\n", xscx[i].xf);
		int j = 0;
		rep(j, 0, xscx[i].sl)
		{
			fprintf(fp, "%d ", xscx[i].kc[j]);
		}
		fprintf(fp, "0\n");
	}
	fclose(fp);
	fp = fopen("xs.in", "w");
	fprintf(fp, "%d\n", t - 1);
	rep(i, 0, t)
	{
		if (i == x) continue;
		fputs(number[i].user, fp);
		fprintf(fp, "\n");
		fputs(number[i].mail, fp);
		fprintf(fp, "\n");
		fputs(number[i].password, fp);
		fprintf(fp, "\n");
		if(i<x)
		    fprintf(fp, "%d\n", number[i].num);
		else
			fprintf(fp, "%d\n", number[i].num-1);
	}
	fclose(fp);
	findclass(n);
	bool flag = false;
	int temp;
	rep(i, 0, n)
	{
		rep(j, 0, xscls[i].sl)
		{
			if (xscls[i].xs[j] > x)
			{
				xscls[i].xs[j]--;
			}
			else if (xscls[i].xs[j] == x)
			{
				temp = xscls[i].num;
				if (xscls[i].sl-1 == 0)
					flag = true;
				xscls[i].xs[j] = -1;
			}
		}
	}
	fp = fopen("class.in", "w");
	if(flag) 
	    fprintf(fp, "%d\n", n-1);
	else
		fprintf(fp, "%d\n", n);
	rep(i, 0, n)
	{
		if (flag&&(cls[i].num == temp)) continue;
		fputs(cls[i].bj, fp);
		fprintf(fp, "\n");
		if (flag)
		{
			if (cls[i].num < temp)
				fprintf(fp, "%d\n", cls[i].num);
			else
				fprintf(fp, "%d\n", cls[i].num - 1);
		}
		else
			fprintf(fp, "%d\n", cls[i].num);
	}
	fclose(fp);
	fp = fopen("xsclass.in", "w");
	if (flag)
		fprintf(fp, "%d\n", n - 1);
	else
		fprintf(fp, "%d\n", n);
	rep(i, 0, n)
	{
		if (flag&&(i == temp)) continue;
		if (flag)
		{
			if(i<temp)
				fprintf(fp, "%d\n", xscls[i].num);
			else
				fprintf(fp, "%d\n", xscls[i].num-1);
		}
		else
			fprintf(fp, "%d\n", xscls[i].num);
		if(i!=temp)
		    fprintf(fp, "%d\n", xscls[i].sl);
		else
			fprintf(fp, "%d\n", xscls[i].sl-1);
		int j;
		rep(j, 0, xscls[i].sl)
			if (xscls[i].xs[j] != -1)
			{
					fprintf(fp, "%d ", xscls[i].xs[j]);
			}
		fprintf(fp, "\n");
	}
	fclose(fp);
	putxstz(n);
	fp = fopen("tz.in", "w");
	rep(i, 0, n)
	{
		if (sqlist[i].num == x) continue;
		if(sqlist[i].num<x)
		fprintf(fp, "%d\n", sqlist[i].num);
		else
			fprintf(fp, "%d\n", sqlist[i].num-1);
		fputs(sqlist[i].name.c_str(), fp);
		fprintf(fp, "\n");
	}
	fclose(fp);
}
void xszxjm(int &temp,int t,int v)//显示注销界面
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j, temp1 = 3;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	if(!v)
	    outtextxy(200, 300, "请选择您要选择的教师");
	else
		outtextxy(200, 300, "请选择您要选择的学生");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 30) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = (t / 30) + 1;
	change(j);
	if (!v)
		outtextxy(510, 700, write);
	else
		outtextxy(510, 700, write);
	int tmp = temp / 30 + 1;
	change(tmp);
	outtextxy(410, 700, write);
	tmp = 0;
	rep(j, temp, t)
	{
		if ((j - tmp*temp1 - temp) > 2) tmp++;
		outtextxy(200 + 210 * (j - temp1*tmp - temp), 350 + 30 * tmp, number[j].user);
		if (!((1 + j) % 30)) break;
	}
	temp += 30;
	settextcolor(BLUE);//字体颜色
	if (temp < t) outtextxy(700, 700, "下一页");
}
bool jszx()//教师注销
{
	int i,j,t;
	fclose(stdin);
	freopen("js.in", "r", stdin);
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(number[i].user);
		gets_s(number[i].mail);
		gets_s(number[i].password);
		scanf("%d", &number[i].num);
	}
	fclose(stdin);
	int temp = 0, temp1 = 3;
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xszxjm(temp,t,0);
	while (1)
	{
		msg = GetMouseMsg();
		int j, tmp = 0;
		rep(j, temp - 30, t)
		{
			if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
			if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 240 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
			{
				setcolor(GREEN);

				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[j].user);
			}
			else
			{
				setcolor(BLACK);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[j].user);
			}
			if (!((1 + j) % 30)) break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<t)//下一页
			{
				xszxjm(temp,t,0);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 60)//上一页
			{
				temp -= 60;
				xszxjm(temp,t,0);
			}
			tmp = 0;
			rep(j, temp - 30, t)
			{
				if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
				if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 240 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
				{
					int result=MessageBox(NULL, "确定删除吗？", "提醒", MB_OKCANCEL);
					if (result==IDOK)
					{
						cleardevice();
						init();
						putcaozuo();
						putback();
						settextstyle(90, 0, "楷体");//字体
						settextcolor(BLACK);//字体颜色
						outtextxy(350, 284, "请稍侯...");
						jszxcz(j);
						MessageBox(NULL, "删除成功！", "提醒", MB_OK);
						exited();
						return false;
					}
				}
				if (!((1 + j) % 30)) break;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putjsxsmm();
				return true;
			}
		}
	}
}
void xsbjtj(int &temp, int n)//显示班级
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j, temp1 = 3;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 300, "请选择您要查询的班级");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 30) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = floor(((n-1) / 30))+1;
	change(j);
	outtextxy(530, 700, write);
	int tmp = temp / 30 + 1;
	change(tmp);
	outtextxy(410, 700, write);
	tmp = 0;
	rep(j, temp, n)
	{
		if ((j - tmp*temp1 - temp) > 2) tmp++;
		outtextxy(200 + 210 * (j - temp1*tmp - temp), 350 + 30 * tmp, cls[j].bj);
		if (!((1 + j) % 30)) break;
	}
	temp += 30;
	settextcolor(BLUE);//字体颜色
	if (temp < n) outtextxy(700, 700, "下一页");
}
void xsxszxjm(int &temp, int b)//显示班级内的学生
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j, temp1 = 3;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 300, "请选择您要删除的学生");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 30) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = (xscls[cls[b].num].sl / 30) + 1;
	change(j);
	outtextxy(530, 700, write);
	int tmp = temp / 30 + 1;
	change(tmp);
	outtextxy(410, 700, write);
	tmp = 0;
	rep(j, temp, xscls[cls[b].num].sl)
	{
		if ((j - tmp*temp1 - temp) > 2) tmp++;
		outtextxy(200 + 210 * (j - temp1*tmp - temp), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
		if (!((1 + j) % 30)) break;
	}
	temp += 30;
	settextcolor(BLUE);//字体颜色
	if (temp < xscls[cls[b].num].sl) outtextxy(700, 700, "下一页");
}
bool xszx(int b)//学生注销
{
	int i, j, t;
	fclose(stdin);
	freopen("xs.in", "r", stdin);
	scanf("%d", &t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(number[i].user);
		gets_s(number[i].mail);
		gets_s(number[i].password);
		scanf("%d", &number[i].num);
	}
	fclose(stdin);
	int temp = 0, temp1 = 3;
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xsxszxjm(temp,b);
	while (1)
	{
		msg = GetMouseMsg();
		int j, tmp = 0;
		rep(j, temp - 30, xscls[cls[b].num].sl)
		{
			if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
			if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 320 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
			{
				setcolor(GREEN);

				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
			}
			else
			{
				setcolor(BLACK);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
			}
			if (!((1 + j) % 30)) break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<xscls[cls[b].num].sl)//下一页
			{
				xsxszxjm(temp,b);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 60)//上一页
			{
				temp -= 60;
				xsxszxjm(temp,b);
			}
			tmp = 0;
			rep(j, temp - 30, xscls[cls[b].num].sl)
			{
				if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
				if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 320 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
				{
					int result = MessageBox(NULL, "确定删除吗？", "提醒", MB_OKCANCEL);
					if (result == IDOK)
					{
						cleardevice();
						init();
						putcaozuo();
						putback();
						settextstyle(90, 0, "楷体");//字体
						settextcolor(BLACK);//字体颜色
						outtextxy(350, 284, "请稍侯...");
						xszxcz(xscls[cls[b].num].xs[j]);
						MessageBox(NULL, "删除成功！", "提醒", MB_OK);
						exited();
						return false;
					}
				}
				if (!((1 + j) % 30)) break;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				return true;
			}
		}
	}
}
bool bjtjzx()//按班级统计注销用户
{
	int n, m, i;
	int temp = 0, temp1 = 3;
	cleardevice();
	init();
	putcaozuo();
	putback();
	settextstyle(25, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(300, 400, "[                  ]读取中..0%");
	findclass(n);
	setcolor(WHITE);
	outtextxy(300, 400, "[                  ]读取中..0%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉                ]读取中..10%");
	if (!fcxxscj)
	{
		cxxscj();
		fcxxscj = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉                ]读取中..10%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	if (!fcxxs)
	{
		kmcx();
		cxxs(m);
		fcxxs = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	if (!fcxxskm)
	{
		cxxskm2();
		fcxxskm = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	if (!fxsuser)
	{
		putxsuser();
		fxsuser = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xsbjtj(temp, n);
	while (1)
	{
		msg = GetMouseMsg();
		int j, tmp = 0;
		rep(j, temp - 30, n)
		{
			if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
			if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 300 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
			{
				setcolor(GREEN);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, cls[j].bj);
			}
			else
			{
				setcolor(BLACK);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, cls[j].bj);
			}
			if (!((1 + j) % 30)) break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<n)//下一页
			{
				xsbjtj(temp, n);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 60)//上一页
			{
				temp -= 60;
				xsbjtj(temp, n);
			}
			tmp = 0;
			rep(j, temp - 30, n)
			{
				if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
				if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 300 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
				{
					if (!xszx(j))
					{
						exited();
						return false;
					}
					else
					{
						temp -= 30;
						xsbjtj(temp, n);
						break;
					}
				}
				if (!((1 + j) % 30)) break;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putjsxsmm();
				return true;
			}
		}
	}
}
bool zxyh()//注销用户
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putjsxsmm();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//教师密码
			{
				if (!jszx())
				{
					exited();
					return false;
				}
				msg = GetMouseMsg();
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//学生密码
			{
				if (!bjtjzx())
				{
					exited();
					return false;
				}
				msg = GetMouseMsg();
			}

			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
	return true;
}
void putaddkc()//显示增加课程界面
{
	IMAGE img, img1,img2,img3,img4;
	loadimage(&img, "课程基本信息.jpg", 459, 360);
	loadimage(&img3, "是.jpg", 45, 24);
	loadimage(&img4, "否.jpg", 45, 24);
	//loadimage(&img1, "重修.jpg", 450, 114);
	loadimage(&img2, "确定.jpg", 356, 46);
	putimage(280, 150, &img);
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(280, 520, "重修");
	putimage(350, 520, &img3);
	putimage(400, 520, &img4);
	//putimage(280, 550, &img1);
	putimage(350, 700, &img2);
}
bool addkc(string str,int dqz,int ls)//增加课程界面
{
	int i, ki=0,bi=0,psi=0,teacheri=0,xfi,y=-1,xqi=0,jdi=0,n,j,temp,m;
	char ks[100] = "",x,bh[100]="",ps[100]="",teacher[100]="",xf[100],xq[100]="",jd[100]="";
	cleardevice();
	init();
	putcaozuo();
	putback();
	putaddkc();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	IMAGE img, img1,img2,img3, img4, img5,img6,img7;
	loadimage(&img2, "是2.jpg", 45, 24);
	loadimage(&img3, "否2.jpg", 45, 24);
	loadimage(&img4, "是.jpg", 45, 24);
	loadimage(&img5, "否.jpg", 45, 24);
	loadimage(&img6, "重修.jpg", 450, 114);
	loadimage(&img7, "白色背景.jpg", 450, 114);
	bool flag = false;
	HWND hWnd = GetHWnd();
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	if (dqz != -1)
	{
		sprintf(xf, "%d", dqz);
		xfi = strlen(xf);
	}
	else
	{
		memset(xf, 0, sizeof(xf));
		xfi = 0;
	}
	if (ls != -1)
	{
		sprintf(teacher, "%d", ls);
		teacheri = strlen(teacher);
	}
	
	outtextxy(378, 225, str.c_str());
	for(i=0; i<xfi; i++)
	outtextxy(378+8*i, 465, xf[i]);
	for (i = 0; i < teacheri; i++)
		outtextxy(378 + 8 * i, 400, teacher[i]);
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 160 && msg.y <= 190)//课程编号
			{
				flag = true;
				i = bi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 165, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 165, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 165, "▏");
							bh[i] = '\0'; bi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 165, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 9)
							{
								setcolor(BLACK);
								bh[i] = x;
								outtextxy(375 + 8 * i, 165, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 165, bh[i]);
								bh[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 200 && msg.y <= 250)//课程名称
			{
				flag = true;
				while (1)
				{
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							//str += '\0';
							break;
						}
					}
					if (_kbhit())	//如果是ASCII输入	
					{
						char c = _getch();
						if (c == '\b')
						{
							if (str.length()>0)
							{
								setcolor(WHITE);
								outtextxy(378, 225, str.c_str());
								if (str.at(str.length() - 1) & 0x8000)
									str.erase(str.end() - 1);
								str.erase(str.end() - 1);
							}
						}
						else {
							str += c;
						}
					}
					else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中	
					{
						GetIMEString(hWnd, str);
					}
					setcolor(BLACK);
					outtextxy(378, 225, str.c_str());
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 270 && msg.y <= 310)//考试成绩
			{
				flag = true;
				i = ki;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 285, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 285, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 285, "▏");
							ks[i] = '\0'; ki = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 285, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								ks[i] = x;
								outtextxy(375 + 8 * i, 285, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 285, ks[i]);
								ks[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 330 && msg.y <= 370)//平时成绩
			{
				flag = true;
				i = psi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 345, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 345, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 345, "▏");
							ps[i] = '\0'; psi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 345, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								ps[i] = x;
								outtextxy(375 + 8 * i, 345, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 345, ps[i]);
								ps[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 390 && msg.y <= 420)//授课教师
			{
				flag = true;
				i = teacheri;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(378 + 8 * i, 400, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(378 + 8 * i, 400, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(378 + 8 * i, 400, "▏");
							teacher[i] = '\0'; teacheri = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(378 + 8 * i, 400, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								teacher[i] = x;
								outtextxy(378 + 8 * i, 400, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(378 + 8 * i, 400, teacher[i]);
								teacher[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 460 && msg.y <= 490)//学分
			{
				flag = true;
				i = xfi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(378 + 8 * i, 465, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(378 + 8 * i, 465, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(378 + 8 * i, 465, "▏");
							xf[i] = '\0'; xfi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(378 + 8 * i, 465, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								xf[i] = x;
								outtextxy(378 + 8 * i, 465, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(378 + 8 * i, 465, xf[i]);
								xf[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 395 && msg.y >= 520 && msg.y <= 544)//重修
			{
				y = 1;
				putimage(350, 520, &img2);
				putimage(400, 520, &img5);
				putimage(280, 550, &img6);
			}
			if (msg.x >= 400 && msg.x <= 445 && msg.y >= 520 && msg.y <= 544)//不重修
			{
				y = 0;
				putimage(350, 520, &img4);
				putimage(400, 520, &img3);
				putimage(280, 550, &img7);
				xqi = 0, jdi = 0;
			}
			if (y == 1 && msg.x >= 350 && msg.x <= 750 && msg.y >= 560 && msg.y <= 590)//重修学期
			{
				flag = true;
				i = xqi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 565, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 565, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 565, "▏");
							xq[i] = '\0'; xqi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 565, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								xq[i] = x;
								outtextxy(375 + 8 * i, 565, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 565, xq[i]);
								xq[i] = '\0';
							}
						}
					}
				}
			}
			if (y == 1 && msg.x >= 350 && msg.x <= 750 && msg.y >= 610 && msg.y <= 640)//重修降低分数
			{
				flag = true;
				i = jdi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 625, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 625, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 625, "▏");
							jd[i] = '\0'; jdi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 625, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								jd[i] = x;
								outtextxy(375 + 8 * i, 625, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 625, jd[i]);
								jd[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 706 && msg.y >= 700 && msg.y <= 746)//确定
			{
			    bool flag1=true;
				for(i=0; i<bi; i++)
					if (bh[i]<'0' || bh[i]>'9')
					{
						flag1 = false;
						break;
					}
				if(flag1)
				for (i = 0; i < ki; i++)
					if (ks[i]<'0' || ks[i]>'9')
					{
						flag1 = false;
						break;
					}
				if (flag1)
					for (i = 0; i < psi; i++)
						if (ps[i]<'0' || ps[i]>'9')
						{
							flag1 = false;
							break;
						}
				if (flag1)
					for (i = 0; i < teacheri; i++)
						if (teacher[i]<'0' || teacher[i]>'9')
						{
							flag1 = false;
							break;
						}
				if (flag1)
					for (i = 0; i < xfi; i++)
						if (xf[i]<'0' || xf[i]>'9')
						{
							flag1 = false;
							break;
						}
				if (flag1 && (y == -1)) flag1 = false;
				if (y == 1)
				{
					if (flag1)
						for (i = 0; i < xqi; i++)
							if (xq[i]<'0' || xq[i]>'9')
							{
								flag1 = false;
								break;
							}
					if (flag1)
						for (i = 0; i < jdi; i++)
							if (jd[i]<'0' || jd[i]>'9')
							{
								flag1 = false;
								break;
							}
				}
				if (flag1) {
					temp = toint(teacher)-1000;
					cxjs(m);
					int l = 0, r = m - 1;
					while (1)
					{
						int mid = l + (r - l) / 2;
						if (l >= r) break;
						if (jscx[mid].num >= temp) r = mid;
						else l = mid + 1;
					}
					if (jscx[l].num != temp) flag1 = false;
					else
					{
						cxkmxx(n);
						jscx[l].kc[jscx[l].sl] = n + 1;
						jscx[l].sl++;
					}
						
				}
				if (flag1) {
					kmcx();
					temp = toint(bh);
					rep(i,1,n+1)
						if(temp==km[i].num||strcmp(str.c_str(),km[i].name)==0)
						{
							flag1 = false;
							break;
						}
				}
				if (flag1)
				{
					cleardevice();
					init();
					putcaozuo();
					putback();
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[                  ]读取中..0%");
					cxxskm();
					fclose(stdin);
					fp = fopen("km.in", "w");
					fprintf(fp, "%d\n", n + 1);
					for (i = 1; i <= n; i++)
					{
						fputs(km[i].name, fp);
						fprintf(fp, "\n");
						fprintf(fp, "%d\n", km[i].num);
					}
					fputs(str.c_str(), fp);
					fprintf(fp, "\n");
					fputs(bh, fp);
					fprintf(fp, "\n");
					fclose(fp);
					fp = fopen("xskm.in", "w");
					fprintf(fp, "%d\n", n + 1);
					rep(i, 1, n + 1)
					{
						fprintf(fp, "%d\n", kmxs[i].num);
						rep(j, 0, kmxs[i].sl)
						{
							fprintf(fp, "%d ", kmxs[i].xs[j]);
						}
						fprintf(fp, "-1\n");
					}
					fputs(bh,fp);
					fprintf(fp, "\n");
					fprintf(fp, "-1\n");
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[                  ]读取中..0%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉                ]读取中..10%");
					fp = fopen("kmxx.in", "w");
					fprintf(fp, "%d\n", n+1);
					for (i = 1; i <= n; i++)
					{
						fprintf(fp, "%d\n", kmxx[i].ps);
						fprintf(fp, "%d\n", kmxx[i].ks);
						fprintf(fp, "%d\n", kmxx[i].xf);
						fprintf(fp, "%d\n", kmxx[i].y);
						if (kmxx[i].y)
						{
							fprintf(fp, "%d\n", kmxx[i].xq);
							fprintf(fp, "%d\n", kmxx[i].jd);
						}
					}
					fputs(ps, fp);
					fprintf(fp, "\n");
					fputs(ks, fp);
					fprintf(fp, "\n");
					fputs(xf, fp);
					fprintf(fp, "\n");
					fprintf(fp, "%d\n",y);
					if (y)
					{
						fputs(xq, fp);
						fprintf(fp, "\n");
						fputs(jd, fp);
						fprintf(fp, "\n");
					}
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉                ]读取中..10%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉              ]读取中..20%");
					cxxscj();
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉              ]读取中..20%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
					freopen("xscj.in", "r", stdin);
					int z;
					s(z);//科目数量
					s(z);//学生数量
					fclose(stdin);
					fp = fopen("xscj.in", "w");
					fprintf(fp, "%d\n", n + 1);
					fprintf(fp, "%d\n", z);
					rep(i, 1, n + 1)
					{
						rep(j,0,z)
							fprintf(fp, "%d\n", xscj[j].ps[i]);
						rep(j, 0, z)
							fprintf(fp, "%d\n", xscj[j].ks[i]);
					}
					rep(i, 0, 2)
						rep(j, 0, z)
						fprintf(fp, "-1\n");
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
					fp = fopen("jsxx.in", "w");
					fprintf(fp, "%d\n", m);
					rep(i, 0, m)
					{
						fprintf(fp, "%d\n", jscx[i].num);
						rep(j, 0, jscx[i].sl)
						{
							fprintf(fp, "%d ", jscx[i].kc[j]);
						}
						fprintf(fp, "0\n");
					}
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
				}
				if (!flag1)//不符合输入格式
				{
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "输入格式错误", "错误", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putaddkc();
					ki = 0, bi = 0, psi = 0, teacheri = 0, xfi=0, y = -1, xqi = 0, jdi = 0;
					str = "";
				}
				else
				{
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "开课成功！", "成功", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					shflag = true;
					return true;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool function2()//录入课程信息
{
	if (!addkc("", -1, -1))
		return false;
	else
	{
		putcaozuo1();
		if (num == 2)
			putnum2();
		return true;
	}
}
void putsh(int &t)//申请数组打进去
{
	int i;
	fclose(stdin);
	freopen("sqlist.in", "r", stdin);
	s(t);
	rep(i, 0, t)
	{
		getchar();
		gets_s(sqlist[i].cname);
		s(sqlist[i].xf);
		s(sqlist[i].num);
	}
	fclose(stdin);
}
void xssh(int &temp,int t)//显示审核列表
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	if (t == 0)
	{
		settextstyle(20, 0, "宋体");//字体
		settextcolor(BLUE);//字体颜色
		outtextxy(200, 200, "还没有申请！");
	}
	else
	{
		IMAGE img, img1;
		loadimage(&img1, "拒绝.jpg", 256, 36);
		loadimage(&img, "同意.jpg", 256, 36);
		int j;
		settextstyle(20, 0, "宋体");//字体
		settextcolor(BLUE);//字体颜色
		outtextxy(350, 700, "当前第    页，共    页");
		if (temp >= 10) outtextxy(250, 700, "上一页");
		outtextxy(210, 300, "课程名称");
		outtextxy(300, 300, "推荐学分");
		outtextxy(400, 300, "申请人");
		settextcolor(BLACK);//字体颜色
		j = ((t-1) / 10) + 1;
		change(j);
		outtextxy(530, 700, write);
		rep(j, temp, t)
		{
			int tmp = temp / 10 + 1;
			change(tmp);
			outtextxy(410, 700, write);
			outtextxy(200, 350 + 30 * (j - temp), sqlist[j].cname);
			change(sqlist[j].xf);
			outtextxy(350, 350 + 30 * (j - temp), write);
			change(sqlist[j].num);
			outtextxy(400, 350 + 30 * (j - temp), write);
			putimage(500, 340 + 30 * (j - temp), &img);
			putimage(750, 340 + 30 * (j - temp), &img1);
			if (!((1 + j) % 10)) break;
		}
		temp += 10;
		settextcolor(BLUE);//字体颜色
		if (temp < t) outtextxy(700, 700, "下一页");
	}
}
bool sh()//审核
{
	int i,t,temp=0;
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	IMAGE img, img1;
	loadimage(&img1, "成功.jpg", 434, 208);
	loadimage(&img, "错误.jpg", 434, 208);
	bool flag = false;
	putsh(t);
	xssh(temp,t);
	while (1)
	{
		//if (msg.uMsg != WM_LBUTTONDOWN || !flag)
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<t)//下一页
			{
				xssh(temp, t);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 20)//上一页
			{
				temp -= 20;
				xssh(temp, t);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			int j,tmp=temp-10;
			if (temp < 10) tmp = 0;
			rep(j, tmp, t)
			{
				if (msg.x >= 500 && msg.x <= 756 && msg.y >= 340 + 30 * (j - tmp) && msg.y <= 376 + 30 * (j - tmp)) //同意
				{
					shflag = false;
					if(!addkc(sqlist[j].cname,sqlist[j].xf,sqlist[j].num))
					return false;
					else
					{
						msg = GetMouseMsg();
						cleardevice();
						init();
						putcaozuo();
						putback();
						if (shflag)
						{
							tz(j, 1);
							rep(i, j + 1, t)
								sqlist[i - 1] = sqlist[i];
							t--;
							printfjssq(t);
							temp = 0;
						}
						else
							temp -= 10;
						xssh(temp, t);
					}
				}
				if (msg.x >= 750 && msg.x <= 1006 && msg.y >= 340 + 30 * (j - tmp) && msg.y <= 376 + 30 * (j - tmp)) //拒绝
				{
					tz(j, 0);
					flag = true;
					rep(i, j + 1, t)
						sqlist[i - 1] = sqlist[i];
					t--;
					printfjssq(t);
					temp = 0;
					xssh(temp, t);
				}
				if (!((1 + j) % 10)) break;
			}
		}
	}
}
void xskctj(int m)
{
	int j;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(GREEN);//字体颜色
	outtextxy(350, 320, "请点击课程名称选择您要查询的课程");
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 320, "课程如下");
	settextcolor(BLACK);//字体颜色
	int temp = 0, temp1 = 5;
	rep(j, 1, m+1)
	{
		if ((j - temp * temp1) > 4) temp++;
		outtextxy(200 + 155 * (j - temp*temp1), 350 + 30 * temp, km[j].name);
	}
}
void puttjcj()
{
	IMAGE img, img1;
	loadimage(&img, "课程统计.jpg", 356, 46);
	loadimage(&img1, "班级统计.jpg", 356, 46);
	putimage(322, 300, &img);
	putimage(322, 500, &img1);
}
bool kctj()//按课程统计成绩
{
	int n, m,i;
	int temp = 0, temp1 = 5;
	cleardevice();
	init();
	putcaozuo();
	putback();
	settextstyle(90, 0, "楷体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	kmcx();
	fcxxskm=false;
	fclose(stdin);
	freopen("km.in", "r", stdin);
	s(m);
	fclose(stdin);
	fcxxscj = false;
	putxsuser();
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xskctj(m);
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			temp = 0, temp1 = 5;
			rep(i, 1, m+1)
			{
				if ((i - temp*temp1) > 4) temp++;
				int tmp = 10 * strlen(km[i].name);
				if (msg.x >= 200 + 155 * (i - temp*temp1) && msg.x <= 200 + 155 * (i - temp*temp1) + tmp && msg.y >= 350 + 30 * temp && msg.y <= 370 + 30 * temp)
				{
					if (!kcmd(i))
					{
						exited();
						return false;
					}
					else
					{
						xskctj(m);
						putback();
					}
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				puttjcj();
				return true;
			}
		}
	}
}
void xsbjxs(int &temp, int b)//显示班级内的学生
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j, temp1 = 3;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 300, "请选择您要查询的学生");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 30) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = (xscls[cls[b].num].sl / 30) + 1;
	change(j);
	outtextxy(530, 700, write);
	int tmp = temp / 30 + 1;
	change(tmp);
	outtextxy(410, 700, write);
	tmp = 0;
	rep(j, temp, xscls[cls[b].num].sl)
	{
		if ((j - tmp*temp1 - temp) > 2) tmp++;
		outtextxy(200 + 210 * (j - temp1*tmp - temp), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
		if (!((1 + j) % 30)) break;
	}
	temp += 30;
	settextcolor(BLUE);//字体颜色
	if (temp < xscls[cls[b].num].sl) outtextxy(700, 700, "下一页");
}
void putxsxz()
{
	IMAGE img, img1;
	loadimage(&img, "学生详细信息.jpg", 356, 46);
	loadimage(&img1, "选课成绩.jpg", 356, 46);
	putimage(322, 300, &img);
	putimage(322, 500, &img1);
}
void putxsxkcj(int &temp, int i)
{
	int j;
	cleardevice();
	init();
	putcaozuo();
	putback();
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	if (xskm[i] == 0)
	{
		outtextxy(220, 250, "该生没有课程");
		return;
	}
	outtextxy(220, 250, "课程名字");
	outtextxy(375, 250, "考试成绩");
	outtextxy(530, 250, "平时成绩");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 10) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	j = (xskm[i] / 10) + 1;
	change(j);
	outtextxy(530, 700, write);
	rep(j, temp, xskm[i])
	{
		int tmp = temp / 10 + 1;
		change(tmp);
		outtextxy(410, 700, write);
		outtextxy(200, 350 + 30 * (j - temp), km[kmxs[j].xs[i]].name);
		if (xscj[i].ks[kmxs[j].xs[i]] != -1)
		{
			change(xscj[i].ks[kmxs[j].xs[i]]);
			outtextxy(420, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(420, 350 + 30 * (j - temp), "未录入");
		}
		if (xscj[i].ps[kmxs[j].xs[i]] != -1)
		{
			change(xscj[i].ps[kmxs[j].xs[i]]);
			outtextxy(560, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(560, 350 + 30 * (j - temp), "未录入");
		}
		if (!((1 + j) % 10)) break;
	}
	temp += 10;
	settextcolor(BLUE);//字体颜色
	if (temp < xskm[i]) outtextxy(700, 700, "下一页");
}
void putbjfl()
{
	IMAGE img, img1;
	loadimage(&img, "查询学生.jpg", 356, 46);
	loadimage(&img1, "查询课程.jpg", 356, 46);
	putimage(322, 300, &img);
	putimage(322, 500, &img1);
}
bool xsxkcj(int i)
{
	int j,temp=0;
	cleardevice();
	init();
	putcaozuo();
	putback();
	putxsxkcj(temp, i);
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{

		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<xskm[i])//下一页
			{
				putxsxkcj(temp, i);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 20)//上一页
			{
				temp -= 20;
				putxsxkcj(temp, i);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
					cleardevice();
					init();
					putcaozuo();
					putback();
					putxsxz();
					return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool xsxz(int i)
{
	bool flag=false;
	cleardevice();
	init();
	putcaozuo();
	putback();
	putxsxz();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	while (1)
	{
		
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (!flag)
			{
				if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//详细信息
				{
					cleardevice();
					init();
					putcaozuo();
					putback();
					xsxs(i);
					flag = true;
				}
				if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//选课成绩
				{
					if (!xsxkcj(i))
					{
						exited();
						return false;
					}
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				if (flag)
				{
					cleardevice();
					init();
					putcaozuo();
					putback();
					putxsxz();
					flag = false;
				}
				else
				{
					cleardevice();
					init();
					putcaozuo();
					putback();
					return true;
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool bjxs(int b)//某班显示学生
{
	int i, j;
	int temp = 0, temp1 = 3;
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xsbjxs(temp, b);
	while (1)
	{
		msg = GetMouseMsg();
		int j, tmp = 0;
		rep(j, temp - 30, xscls[cls[b].num].sl)
		{
			if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
			if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 320 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
			{
				setcolor(GREEN);
				
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
			}
			else
			{
				setcolor(BLACK);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, number[xscls[cls[b].num].xs[j]].user);
			}
			if (!((1 + j) % 30)) break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<xscls[cls[b].num].sl)//下一页
			{
				xsbjxs(temp, b);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 60)//上一页
			{
				temp -= 60;
				xsbjxs(temp,b);
			}
			tmp = 0;
			rep(j, temp - 30, xscls[cls[b].num].sl)
			{
				if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
				if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 320 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
				{
					if (!xsxz(xscls[cls[b].num].xs[j]))
					{
						exited();
						return false;
					}
					else
					{
						temp -= 30;
						xsbjxs(temp, b);
						break;
					}
				}
				if (!((1 + j) % 30)) break;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putbjfl();
				return true;
			}
		}
	}
}
void displaykccj(int &temp, int m, int ps[], int ks[],int b)
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	int j;
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLUE);//字体颜色
	outtextxy(200, 200, "该班中各科目的成绩");
	outtextxy(220, 250, "科目名字");
	outtextxy(375, 250, "考试成绩平均分");
	outtextxy(530, 250, "平时成绩平均分");
	outtextxy(350, 700, "当前第    页，共    页");
	if (temp >= 10) outtextxy(250, 700, "上一页");
	settextcolor(BLACK);//字体颜色
	outtextxy(50, 200, cls[b].bj);
	j = ((m) / 10);
	if (m % 10) j++;
	change(j);
	outtextxy(530, 700, write);
	int tmp = (temp) / 10 + 1;
	change(tmp);
	outtextxy(410, 700, write);
	rep(j, temp, m+1)
	{
		outtextxy(200, 350 + 30 * (j - temp), km[j].name);
		if (ks[j] !=0)
		{
			change(ks[j]);
			outtextxy(420, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(420, 350 + 30 * (j - temp), "未录入");
		}
		if (ps[j]!=0)
		{
			change(ps[j]);
			outtextxy(560, 350 + 30 * (j - temp), write);
		}
		else
		{
			outtextxy(560, 350 + 30 * (j - temp), "未录入");
		}
		if (!((j) % 10)) break;
	}
	temp += 10;
	settextcolor(BLUE);//字体颜色
	if (temp <= m) outtextxy(700, 700, "下一页");
}
bool kccj(int b)
{
	int i, m, temp = 1, j, z[500] = { 0 }, ps[500] = { 0 }, ks[500] = { 0 };
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	fclose(stdin);
	freopen("km.in", "r", stdin);
	s(m);
	fclose(stdin);
	kmcx();
		rep(i, 0, xscls[cls[b].num].sl)
		{
			rep(j,0,xskm[xscls[cls[b].num].xs[i]])
			if (xscj[xscls[cls[b].num].xs[i]].ks[kmxs[j].xs[xscls[cls[b].num].xs[i]]] != -1)
			{
				ks[kmxs[j].xs[xscls[cls[b].num].xs[i]]] += xscj[xscls[cls[b].num].xs[i]].ks[kmxs[j].xs[xscls[cls[b].num].xs[i]]];
				z[kmxs[j].xs[xscls[cls[b].num].xs[i]]]++;
			}
			rep(j, 0, xskm[xscls[cls[b].num].xs[i]])
			if (xscj[xscls[cls[b].num].xs[i]].ps[kmxs[j].xs[xscls[cls[b].num].xs[i]]] != -1)
				ps[kmxs[j].xs[xscls[cls[b].num].xs[i]]] += xscj[xscls[cls[b].num].xs[i]].ps[kmxs[j].xs[xscls[cls[b].num].xs[i]]];
		}
	rep(j, 1, m+1)
	{
		if (z[j] != 0)
		{
			ks[j] /= z[j];
			ps[j] /= z[j];
		}
	}
	displaykccj(temp, m, ps, ks,b);
	msg = GetMouseMsg();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<=m)//下一页
			{
				displaykccj(temp, m, ps, ks,b);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 20)//上一页
			{
				temp -= 20;
				displaykccj(temp, m, ps, ks,b);
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				putbjfl();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool bjfl(int b)//班级的功能
{
	MOUSEMSG msg;
	cleardevice();
	init();
	putcaozuo();
	putback();
	putbjfl();
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//具体学生
			{
				if (!bjxs(b))
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//课程统计成绩
			{
				if (!kccj(b))
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
bool bjtj()//按班级统计
{
	int n, m, i;
	int temp = 0, temp1 = 3;
	cleardevice();
	init();
	putcaozuo();
	putback();
	settextstyle(25, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(300, 400, "[                  ]读取中..0%");
	findclass(n);
	setcolor(WHITE);
	outtextxy(300, 400, "[                  ]读取中..0%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉                ]读取中..10%");
	if (!fcxxscj)
	{
		cxxscj();
		fcxxscj = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉                ]读取中..10%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	if (!fcxxs)
	{
		kmcx();
		cxxs(m);
		fcxxs = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉              ]读取中..20%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	if (!fcxxskm)
	{
		cxxskm2();
		fcxxskm = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	if (!fxsuser)
	{
		putxsuser();
		fxsuser = true;
	}
	setcolor(WHITE);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
	setcolor(BLACK);
	outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
	cleardevice();
	init();
	putcaozuo();
	putback();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	xsbjtj(temp,n);
	while (1)
	{
		msg = GetMouseMsg();
		int j, tmp = 0;
		rep(j, temp - 30, n)
		{
			if ((j - tmp*temp1 - temp + 30) > 2) tmp++;
			if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 300 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
			{
				setcolor(GREEN);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, cls[j].bj);
			}
			else
			{
				setcolor(BLACK);
				outtextxy(200 + 210 * (j - temp1*tmp - temp + 30), 350 + 30 * tmp, cls[j].bj);
			}
			if (!((1 + j) % 30)) break;
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 700 && msg.x <= 748 && msg.y >= 700 && msg.y <= 720 && temp<n)//下一页
			{
				xsbjtj(temp, n);
			}
			if (msg.x >= 250 && msg.x <= 298 && msg.y >= 700 && msg.y <= 720 && temp >= 60)//上一页
			{
				temp -= 60;
				xsbjtj(temp, n);
			}
			tmp=0;
			rep(j, temp-30, n)
			{
				if ((j - tmp*temp1 - temp+30) > 2) tmp++;
				if (200 + 210 * (j - temp1*tmp - temp + 30) <= msg.x && msg.x <= 300 + 210 * (j - temp1*tmp - temp + 30) && 350 + 30 * tmp <= msg.y && msg.y <= 370 + 30 * tmp)
				{
					if (!bjfl(j))
					{
						exited();
						return false;
					}
					else
					{
						temp -= 30;
						xsbjtj(temp, n);
						break;
					}
				}
				if (!((1 + j) % 30)) break;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putback();
				puttjcj();
				return true;
			}
		}
	}
}
bool tjcj()//统计成绩
{
	MOUSEMSG msg;
	cleardevice();
	init();
	putcaozuo();
	putback();
	puttjcj();
	fcxxscj = false;
	fcxxs = false;
	fcxxskm = false;
	fxsuser = false;
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//课程统计
			{
				if (!kctj())
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//班级统计成绩
			{
				if (!bjtj())
				{
					exited();
					return false;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void putzjjszh()//增加教师账号界面
{
	IMAGE img,img1;
	loadimage(&img, "教师基本信息.jpg", 459, 360);
	loadimage(&img1, "确定.jpg", 356, 46);
	putimage(280, 150, &img);
	putimage(350, 350, &img1);
}
bool zjjszh()//增加教师账号
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putzjjszh();
	MOUSEMSG msg;
	msg = GetMouseMsg();
	bool flag = false;
	HWND hWnd = GetHWnd();
	string str;
	int i, si = 0,pi=0,newzh,t;
	char x, ss[100] = "",phone[100]="";
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
			msg = GetMouseMsg();
		flag = false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 160 && msg.y <= 190)//教师姓名
			{
				flag = true;
				while (1)
				{
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							//str += '\0';
							break;
						}
					}
					if (_kbhit())	//如果是ASCII输入	
					{
						char c = _getch();
						if (c == '\b')
						{
							if (str.length()>0)
							{
								setcolor(WHITE);
								outtextxy(378, 165, str.c_str());
								if (str.at(str.length() - 1) & 0x8000)
									str.erase(str.end() - 1);
								str.erase(str.end() - 1);
							}
						}
						else {
							str += c;
						}
					}
					else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中	
					{
						GetIMEString(hWnd, str);
					}
					setcolor(BLACK);
					outtextxy(378, 165, str.c_str());
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 200 && msg.y <= 250)//宿舍号
			{
				flag = true;
				i = si;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 225, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 225, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 225, "▏");
							ss[i] = '\0'; si = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 225, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 9)
							{
								setcolor(BLACK);
								ss[i] = x;
								outtextxy(375 + 8 * i, 225, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 225, ss[i]);
								ss[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 270 && msg.y <= 310)//考试成绩
			{
				flag = true;
				i = pi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(375 + 8 * i, 285, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 285, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(375 + 8 * i, 285, "▏");
							phone[i] = '\0'; pi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(375 + 8 * i, 285, "▏");
						//freopen("in.txt", "r", stdin);
						x = _getch();
						if (x != '\10')//退格键
						{
							if (i < 38)
							{
								setcolor(BLACK);
								phone[i] = x;
								outtextxy(375 + 8 * i, 285, x);
								i++;
							}
						}
						else
						{
							if (i > 0)
							{
								setcolor(WHITE);
								i--;
								outtextxy(375 + 8 * i, 285, phone[i]);
								phone[i] = '\0';
							}
						}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 706 && msg.y >= 350 && msg.y <= 396)//确定
			{
				bool flag1 = true;
				for (i = 0; i < si; i++)
					if (ss[i]<'0' || ss[i]>'9')
					{
						flag1 = false;
						break;
					}
				if (flag1)
					for (i = 0; i < pi; i++)
						if (phone[i]<'0' || phone[i]>'9')
						{
							flag1 = false;
							break;
						}
				if (flag1)
				{
					cleardevice();
					init();
					putcaozuo();
					putback();
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[                  ]读取中..0%");
					int temp = 0,t,j;
					fclose(stdin);
					freopen("js.in", "r", stdin);
					s(t);
					rep(i, 0, t)
					{
						getchar();
						gets_s(number[i].user);
						temp = max(temp, toint(number[i].user));
						gets_s(number[i].mail);
						gets_s(number[i].password);
						scanf("%d", &number[i].num);
					}
					fclose(stdin);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[                  ]读取中..0%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉                ]读取中..10%");
					rep(i, 1000, temp+1)
					{
						bool flag1 = false;
						rep(j, 0, t)
						{
							if (toint(number[j].user) == i)
							{
								flag1 = true;
								break;
							}
						}
						if (flag1) continue;
						break;
					}
					newzh = i;
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉                ]读取中..10%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉              ]读取中..20%");
					fp = fopen("js.in", "w");
					fprintf(fp, "%d\n", t + 1);
					rep(i, 0, t)
					{
						fputs(number[i].user, fp);
						fprintf(fp, "\n");
						fputs(number[i].mail, fp);
						fprintf(fp, "\n");
						fputs(number[i].password, fp);
						fprintf(fp, "\n");
						fprintf(fp, "%d\n", number[i].num);
					}
					fprintf(fp, "%d\n", newzh);
					fprintf(fp, "%d", newzh);
					fputs("@163.com", fp);
					fprintf(fp, "\n");
					fprintf(fp, "%d\n", newzh);
					fprintf(fp, "%d\n", t);
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉              ]读取中..20%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
					cxjs(t);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉          ]读取中..40%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
					fp = fopen("jsxx.in", "w");
					fprintf(fp, "%d\n", t + 1);
					rep(i, 0, t)
					{
						fprintf(fp, "%d\n", jscx[i].num);
						rep(j, 0, jscx[i].sl)
						{
							fprintf(fp, "%d ", jscx[i].kc[j]);
						}
						fprintf(fp, "0\n");
					}
					fprintf(fp, "%d\n", t);
					fprintf(fp, "0\n");
					fclose(fp);
					fp = fopen("jsphone.in", "w");
					fprintf(fp, "%d\n", t + 1);
					rep(i, 0, t)
					{
						fprintf(fp, "%d\n", jsphone[i].num);
						fputs(jsphone[i].name, fp);
						fprintf(fp, "\n");
						fputs(jsphone[i].phone, fp);
						fprintf(fp, "\n");
						fputs(jsphone[i].address, fp);
						fprintf(fp, "\n");
					}
					fprintf(fp, "%d\n", t);
					fputs(str.c_str(), fp);
					fprintf(fp, "\n");
					fputs(phone, fp);
					fprintf(fp, "\n");
					fputs(ss, fp);
					fprintf(fp, "\n");
					fclose(fp);
					setcolor(WHITE);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉    ]读取中..70%");
					setcolor(BLACK);
					settextstyle(25, 0, "宋体");//字体
					outtextxy(300, 400, "[▉▉▉▉▉▉▉▉▉]读取中..100%");
				}
				if (!flag1)//不符合输入格式
				{
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "输入格式错误", "错误", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putback();
					putzjjszh();
					si = 0, pi = 0;
					str = "";
				}
				else
				{
					HWND hWnd1 = GetHWnd();
					char buf[100] = "";
					sprintf(buf, "新的账号密码为:%d", newzh);
					MessageBox(hWnd1, buf, "成功", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putcaozuo1();
					return true;
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void putfbxstz()
{
	IMAGE img, img1;
	loadimage(&img, "发布通知.jpg", 450, 114);
	putimage(300, 300, &img);
	loadimage(&img1, "确定.jpg", 356, 46);
	putimage(400, 450, &img1);
}
bool fbxstz()//发布学生通知
{
	cleardevice();
	init();
	putcaozuo();
	putback();
	putfbxstz();
	MOUSEMSG msg;
	HWND hWnd = GetHWnd();
	char x;
	int i,xi=0,t;
	char xh[100]="";
	bool flag = false;
	string str;
	msg = GetMouseMsg();
	settextstyle(20, 0, "宋体");//字体
	settextcolor(BLACK);//字体颜色
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || (!flag))
		msg = GetMouseMsg();
		flag=false;
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 300 && msg.y <= 350)//学号
			{
				flag = true;
				i = xi;
				int start = clock(), finish = clock();
				while (1)
				{
					finish = clock();
					if (finish - start > 500)
					{
						setcolor(BLACK);
						outtextxy(420 + 8 * i, 315, "▏");
					}
					if (finish - start > 1000)
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						start = clock();
					}
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							setcolor(WHITE);
							outtextxy(420 + 8 * i, 315, "▏");
							xh[i] = '\0'; xi = i;  break;
						}
					}
					while (_kbhit())
					{
						setcolor(WHITE);
						outtextxy(420 + 8 * i, 315, "▏");
						x = _getch();
						if (x == 9)
						{
							xh[i] = '\0'; xi = i;
							goto pas;
						}
						else if (x != '\10')//退格键
							{
								if (i < 38)
								{
									setcolor(BLACK);
									xh[i] = x;
									outtextxy(420 + 8 * i, 315, x);
									i++;
								}
							}
							else
							{
								if (i > 0)
								{
									setcolor(WHITE);
									i--;
									outtextxy(420 + 8 * i, 315, xh[i]);
									xh[i] = '\0';
								}
							}
					}
				}
			}
			if (msg.x >= 350 && msg.x <= 750 && msg.y >= 360 && msg.y <= 414)//通知内容
			{
				flag = true;
			pas:
				while (1)
				{
					if (MouseHit())
					{
						msg = GetMouseMsg();
						if (msg.uMsg == WM_LBUTTONDOWN)
						{
							//str += '\0';
							break;
						}
					}
					if (_kbhit())	//如果是ASCII输入	
					{
						char c = _getch();
						if (c == '\b')
						{
							if (str.length()>0)
							{
								setcolor(WHITE);
								outtextxy(420, 375, str.c_str());
								if (str.at(str.length() - 1) & 0x8000)
									str.erase(str.end() - 1);
								str.erase(str.end() - 1);
							}
						}
						else {
							str += c;
						}
					}
					else	//除此之外，检测是否有IME输入，如果有，则将输入结果添加到string中	
					{
						GetIMEString(hWnd, str);
					}
					setcolor(BLACK);
					outtextxy(420, 375, str.c_str());
				}
			}
			if (msg.x >= 400 && msg.x <= 756 && msg.y >= 450 && msg.y <= 496)//确定
			{
				flag = true;
				putxsuser();
				fclose(stdin);
				freopen("xs.in", "r", stdin);
				s(t);
				fclose(stdin);
				bool flag1 = false;
				rep(i, 0, t)
				{
					if(strcmp(number[i].user,xh)==0)
					{
						flag1 = true;
						break;
					}
				}
				if (flag1)
				{
					int n;
					putxstz(n);
					sqlist[n].num = number[i].num;
					sqlist[n++].name = str;
					printfxstz(n);
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "通知成功！", "成功", MB_TASKMODAL);
					cleardevice();
					init();
					putcaozuo();
					putcaozuo1();
					return true;
				}
				else
				{
					xi = 0;
					str = "";
					memset(xh, 0, sizeof(0));
					HWND hWnd1 = GetHWnd();
					MessageBox(hWnd1, "查无此人！", "错误", MB_TASKMODAL);
					flag = false;
					cleardevice();
					init();
					putcaozuo();
					putback();
					putfbxstz();
					settextstyle(20, 0, "宋体");//字体
					settextcolor(BLACK);//字体颜色
				}
			}
			if (msg.x >= 750 && msg.x <= 782 && msg.y >= 120 && msg.y <= 128)//返回
			{
				cleardevice();
				init();
				putcaozuo();
				putcaozuo1();
				return true;
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return false;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return false;
			}
		}
	}
}
void caozuo3()//学生操作界面
{
	MOUSEMSG msg;
	bool flag = false;
	int t,i=0;
	putcaozuo();
	msg=GetMouseMsg();
	fclose(stdin);
	settextstyle(90, 0, "楷体");//字体
	settextcolor(BLACK);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	cxxs(t);
	settextstyle(90, 0, "楷体");//字体
	settextcolor(WHITE);//字体颜色
	outtextxy(350, 284, "请稍侯...");
	xsxs(num);
	fclose(stdin);
	freopen("tz.in", "r", stdin);
	while (s(sqlist[i].num) != EOF)
	{
		getchar();
		cin >> sqlist[i].name;
		if (sqlist[i].num == num)
		{
			HWND hWnd1 = GetHWnd();
			MessageBox(hWnd1, sqlist[i].name.c_str(), "通知", MB_TASKMODAL);
		}
		i++;
	}
	fclose(stdin);
	int n = i;
	fp = fopen("tz.in", "w");
	rep(i, 0, n)
	{
		if (sqlist[i].num == num) continue;
		fprintf(fp, "%d\n", sqlist[i].num);
		fputs(sqlist[i].name.c_str(), fp);
		fprintf(fp, "\n");
	}
	fclose(fp);
	while (1)
	{
		if (msg.uMsg != WM_LBUTTONDOWN || !flag)
			msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return;
			}
		}
	}
}
void caozuo2()//教师操作界面
{
	MOUSEMSG msg;
	bool flag = false;
	int t;
	putcaozuo();
	cxjs(t);
	putcaozuo2(num);
	msg = GetMouseMsg();
	fclose(stdin);
	fcxxskm = false;
	fcxxscj = false;
	int temp, v;
	bool flag1 = false;
	if (freopen("sqjg.in", "r", stdin) != NULL)
	{	
		while (s(temp) != EOF)
		{
			s(v);
			if (temp == toint(LOGIN[num].user))
			{
				flag1 = true;
				if (v)
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "成功！", "申请结果", MB_TASKMODAL);
					break;
				}
				else
				{
					HWND hWnd = GetHWnd();
					MessageBox(hWnd, "被拒绝！", "申请结果", MB_TASKMODAL);
					break;
				}
			}
		}
	}
	fclose(stdin);
	if (flag1)
	{
		freopen("sqjg.in", "r", stdin);
		int i = 0,j;
		while (s(sqlist[i].num) != EOF)
		{
			s(sqlist[i++].xf);
		}
		fclose(stdin);
		fp = fopen("sqjg.in", "w");
		rep(j, 0, i)
		{
			if (sqlist[j].num == temp) continue;
			fprintf(fp, "%d\n", sqlist[j].num);
			fprintf(fp, "%d\n", sqlist[j].xf);
		}
		fclose(fp);
	}
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//申请选课 
			{
				if(!jssq())
				{
					exited();
					return; 
				}
				
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//查询本课学生  
			{
				cxkc();
				if (!fkcmd)
				{
					exited();
					return;
				}
				else
				{
					putcaozuo2(num);
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return;
			}
		}
	}
}
void caozuo1()//部门操作界面
{
	MOUSEMSG msg;
	putcaozuo();
	putcaozuo1();
	if (num == 2)
		putnum2();
	fclose(stdin);
	while (1)
	{
		msg = GetMouseMsg();
		if (num == 2 && msg.x >= 750 && msg.x <= 1030 && msg.y >= 150 && msg.y <= 170)//课程时移到审核会变色
		{
			pputnum2();
		}
		else if(num==2)
		{
			putnum2();
		}
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			if (num == 2 && msg.x >= 750 && msg.x <= 1030 && msg.y >= 150 && msg.y <= 170)//审核申请选课
			{
				if (!sh())
				{
					exited();
					return;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 300 && msg.y <= 346)//账号特殊功能
			{
				if (num == 1)
				{
					if(!function1())
					{
						exited();
						return;
					}
				}
				else if (num == 2)
				{
					if (!function2())
					{
						exited();
						return;
					}
				}
				else if (num == 3)
				{
					if (!function3())
					{
						exited();
						return;
					}
				}
				else if (num == 4)
				{
					if (!function4())
					{
						exited();
						return;
					}
				}
				else if (num == 5)
				{
					if (!function5())
					{
						exited();
						return;
					}
				}

			}
			if (msg.x >= 200 && msg.x <= 340 && msg.y >= 150 && msg.y <= 170)//增加教师账号
			{
				if (!fbxstz())
				{
					exited();
					return;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 400 && msg.y <= 446 && num == 5)//增加教师账号
			{
				if (!zjjszh())
				{
					exited();
					return;
				}
			}
			if (msg.x >= 322 && msg.x <= 678 && msg.y >= 500 && msg.y <= 546)//统计成绩或者注销用户
			{
				if (num != 5)
				{
					if (!tjcj())
					{
						exited();
						return;
					}
				}
				else
				{
					if (!zxyh())
					{
						exited();
						return;
					}
				}
			}
			if (msg.x >= 900 && msg.x <= 932 && msg.y >= 120 && msg.y <= 128)//退出
			{
				exited();
				return;
			}
			if (msg.x >= 800 && msg.x <= 832 && msg.y >= 120 && msg.y <= 128)//修改密码
			{
				xgmm();
				return;
			}
		}
	}
}
int main()
{
	dcfile("xs.in");
	dcfile("bm.in");
	dcfile("js.in");
	initgraph(1024, 768);
	init();
	putlogin();
	ui = 0; mi = 0; open = 0;
	iflogin = false;
	while(!iflogin)
	if (login())
	{
		cleardevice(); //清屏
		init();
		if (open == 3)//学生
		{
			caozuo3();
		}
		if (open == 2)
		{
			caozuo2();
		}
		if (open == 1)
		{
			caozuo1();
		}
	}
	ecfile("xs.in");
	ecfile("bm.in");
	ecfile("js.in");
	closegraph();
	return 0;
}
/*
if ( MouseHit() )
{
MOUSEMSG m = GetMouseMsg();
if ( m.uMsg == WM_LBUTTONDOWN ) // 分离出鼠标单击信息
{

}
}


WM_MOUSEMOVE 鼠标移动消息。
WM_MOUSEWHEEL 鼠标滚轮拨动消息。
WM_LBUTTONDOWN 左键按下消息。
WM_LBUTTONUP 左键弹起消息。
WM_LBUTTONDBLCLK 左键双击消息。
WM_MBUTTONDOWN 中键按下消息。
WM_MBUTTONUP 中键弹起消息。
WM_MBUTTONDBLCLK 中键双击消息。
WM_RBUTTONDOWN 右键按下消息。
WM_RBUTTONUP 右键弹起消息。
WM_RBUTTONDBLCLK 右键双击消息。

*/