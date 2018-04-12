#include "auto_test.h"

void main(){
	//char *dat1, *dat2;  string pointsa[100][20], pointsb[100][20];
	//string headera[100], headerb[100];
	//quadix<float,2> quadixa,quadixb;
	//char stringa[100][20], stringb[100][20];
	//char patha[100][100]={},pathb[100][100]={};

	//for (int i = 0; i < 3; i++)
	//{    char strtemp1[5],strtemp2[5];
	//   
	//    strcat(patha[i],"C:\\Users\\Administrator\\Desktop\\work_note\\a");
	//	strcat(patha[i],itoa(i+1,strtemp1,10));
	//	strcat(patha[i],".txt");
	//	strcat(pathb[i],"C:\\Users\\Administrator\\Desktop\\work_note\\b");
	//	strcat(pathb[i],itoa(i+1,strtemp1,10));
	//	strcat(pathb[i],".txt");

	//}//获取地址路径
	//
	//
	//

	//
	//for (int m = 0; m < 3; m++)
	//{
	//	headera[m] = splitEx(read_data(patha[m]), ",")[0];
	//	
	//	for (int i = 0; i <8; i++)
	//	{
	//		pointsa[m][i] = splitEx(read_data(patha[m]), ",")[i+1];
	//		
	//	}
	//}//获取坐标，与头标号，a为GT值，b为检测值
	//
	//for (int m = 0; m < 3; m++)
	//{
	//	headerb[m] = splitEx(read_data(pathb[m]), ",")[0];
	//	for (int i = 0; i <8; i++)
	//	{
	//		pointsb[m][i] = splitEx(read_data(pathb[m]), ",")[i + 1];
	//	}
	//}//获取坐标，与头标号，a为GT值，b为检测值


	//
	//
	//int miss_inspect=0, incorrect_inspect=0;
	//for (int q = 0; q < 3; q++)
	//{
	//	if (!judge_exist(headera[q],headerb))
	//	{
	//		cout << headera[q] << "不存在" << endl;
	//		miss_inspect++;
	//	}
	//	else
	//	{
	//		quadixa = assignment_quadix(pointsa[q]);
	//		quadixb = assignment_quadix(pointsb[q]);
	//		cout << "重合率为:" << proportion(quadixa, quadixb) << endl;
	//		if (proportion(quadixa, quadixb)<0.7){
	//			cout << "误检号为：" <<q<< endl;
	//			incorrect_inspect++;
	//		}
	//	}
	//}//获取漏检，误检号

	//cout << "miss_insect=" << miss_inspect << endl;
	//cout << "incorrect_inspect=" << incorrect_inspect << endl;
	
	quadix<float,2>  quadix1, quadix2;
	quadix1[0].x = 0;
	quadix1[0].y = 0;
	quadix1[1].x = 1;
	quadix1[1].y = 0;
	quadix1[2].x = 1;
	quadix1[2].y = 1;
	quadix1[3].x = 0;
	quadix1[3].y = 1;

	quadix2[0].x = 0;
	quadix2[0].y = 0;
	quadix2[1].x = 1;
	quadix2[1].y = 0;
	quadix2[2].x = 1.5;
	quadix2[2].y = 1.5;
	quadix2[3].x = 0.8;
	quadix2[3].y = 1.5;

	float p1=proportion(quadix1,quadix2,0.1);
	float p2 = proportion(quadix1, quadix2, 0.05);
	float p3 = proportion(quadix1, quadix2, 0.01);
	cout << "精度为0.1时，重合所占比为："<<p1<< endl;
	cout << "精度为0.05时，重合所占比为：" << p2 << endl;
	cout << "精度为0.01时，重合所占比为：" << p3<< endl;
	
	}
	

	
	