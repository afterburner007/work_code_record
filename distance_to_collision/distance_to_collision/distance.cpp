
#include "distance.h"
#include "iostream"
using namespace std;
float distance_point_to_point(point2d<float> point1, point2d<float> point2){
	float distance;
	distance = sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
	return distance;
}//计算两点之间的距离


float max_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4){
	float distance1 = distance_point_to_point(point, point1), distance2 = distance_point_to_point(point, point2), distance3 = distance_point_to_point(point, point3), distance4 = distance_point_to_point(point, point4);
	float MAX = distance1;
	if (distance2 >= MAX)
	{
		MAX = distance2;
	}
	if (distance3 >= MAX)
	{
		MAX = distance3;
	}
	if (distance4 >= MAX)
	{
		MAX = distance4;
	}
	return MAX;
}//获得最大距离


float min_distance(point2d<float> point, point2d<float> point1, point2d<float> point2, point2d<float> point3, point2d<float> point4){
	float distance1 = distance_point_to_point(point, point1), distance2 = distance_point_to_point(point, point2), distance3 = distance_point_to_point(point, point3), distance4 = distance_point_to_point(point, point4);
	float MIN = distance1;
	if (distance2 <= MIN)
	{
		MIN = distance2;
	}
	if (distance3 <= MIN)
	{
		MIN = distance3;
	}
	if (distance4 <= MIN)
	{
		MIN = distance4;
	}
	return MIN;
}//获得最小距离



bool collision_range(circle<float> circlemin, circle<float> circlemax, point2d<float> point){



	if (point_in_circle(point, circlemax) && !point_in_circle(point, circlemin))
	{
		return true;
	}
	else
	{
		return false;
	}

}

float *solving_equations(float a, float b, float c){
	float answer[2];
	answer[0] = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	answer[1] = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
	return answer;
}

point2d<float> *point_of_intersection(point2d<float> point1, point2d<float> point2, circle<float> circles){
	point2d<float> point[2]; float u1, u2;
	float a = (point2.x - point1.x)*(point2.x - point1.x) + (point2.y - point1.y)*(point2.y - point1.y);
	float b = 2 * ((point2.x - point1.x)*(point1.x - circles.x) + (point2.y - point1.y)*(point1.y - circles.y));
	float c = circles.x*circles.x + circles.y*circles.y + point1.x*point1.x + point1.y*point1.y - 2 * (circles.x*point1.x + circles.y*point1.y) - circles.radius*circles.radius;
	if ((b*b - 4 * a*c) >= 0)
	{
		u1 = solving_equations(a, b, c)[0];
		u2 = solving_equations(a, b, c)[1];
		point[0].x = point1.x + u1*(point2.x - point1.x);
		point[0].y = point1.y + u1*(point2.y - point1.y);
		point[1].x = point1.x + u2*(point2.x - point1.x);
		point[1].y = point1.y + u2*(point2.y - point1.y);
		/*cout << point[0].x << "," << point[0].y << "      " << point[1].x << "," << point[1].y << endl;*/
	}
	else
	{
		cout << "无交点" << endl;
	}
	return point;
}//计算直线与圆的交点


point2d<float> intersection_segment_to_circle(point2d<float> pointd, point2d<float> pointc, circle<float> circles){

	point2d<float> intersection;

	for (int i = 0; i < 2; i++){
		if (point_of_intersection(pointd, pointc, circles)[i].x >= pointd.x&&point_of_intersection(pointd, pointc, circles)[i].x <= pointc.x&&point_of_intersection(pointd, pointc, circles)[i].y >= pointd.y&&point_of_intersection(pointd, pointc, circles)[i].y <= pointc.y)
		{
			intersection.x = point_of_intersection(pointd, pointc, circles)[i].x;
			intersection.y = point_of_intersection(pointd, pointc, circles)[i].y;
		}
	}
	return intersection;

}


float angle(point2d<float> point, point2d<float> collision, point2d<float> intersection){

	return (point.x*(collision.y - intersection.y) + collision.x*(intersection.y - point.y) + intersection.x*(point.y - collision.y)) / (distance_point_to_point(point, collision)*distance_point_to_point(point, intersection));

}


//radius 半径
//shiftpos = 2 前进；其他值表示后退
//wheelangle >0 表示左转，<0表示右转
//Point2f* objpoints,int ObjNUM 障碍物点
float get_mindistance_code(float Radius, int shiftpos, float wheelangle, point2d<float>* objpoints, int ObjNUM)
{

	float rearwheel2head = 3.8f;
	float rearwheel2tail = 1.0f;
	float carwidth = 1.8f;

	point2d<float> pointa, pointb, pointc, pointd, circlepoint, collision;
	pointa.x = -0.9;
	pointa.y = -1.0;
	pointb.x = 0.9;
	pointb.y = -1.0;
	pointc.x = 0.9;
	pointc.y = 3.8;
	pointd.x = -0.9;
	pointd.y = 3.8;//四个点的坐标赋值

	if (wheelangle < 0){
		circlepoint.x = Radius;
		circlepoint.y = 0;
	}
	else
	{
		circlepoint.x = -Radius;
		circlepoint.y = 0;
	}//旋转圆心赋值


	point2d<float> minr(0.9, 0), minl(-0.9, 0);
	float maxradius = max_distance(circlepoint, pointa, pointb, pointc, pointd);
	float minradius = min_distance(circlepoint, minr, minl, pointc, pointd);

	circle<float> maxcircle;
	maxcircle.x = circlepoint.x;
	maxcircle.y = circlepoint.y;
	maxcircle.radius = maxradius;//碰撞最大范围
	circle<float> mincircle;
	mincircle.x = circlepoint.x;
	mincircle.y = circlepoint.y;
	mincircle.radius = minradius;//碰撞最小范围



	vector<float> L;


	for (int i = 0; i < ObjNUM; i++)
	{

		collision.x = objpoints[i].x;
		collision.y = objpoints[i].y;


		if (collision_range(mincircle, maxcircle, collision))
		{
			circle<float> circles;
			circles.radius = distance_point_to_point(circlepoint, collision);
			circles.x = circlepoint.x;
			circles.y = circlepoint.y;

			point2d<float> intersection;

			if (shiftpos == 2 & wheelangle<0)
			{
				circle<float> circlea;
				circlea.radius = distance_point_to_point(circlepoint, pointa);
				circlea.x = circlepoint.x;
				circlea.y = circlepoint.y;

				if (collision.y >3.8 || (collision.x > 0.9&&collision.y > 0)){
					if (circles.radius > distance_point_to_point(circlepoint, pointc))
					{
						intersection = intersection_segment_to_circle(pointd, pointc, circles);
						//cout << intersection.x << "," << intersection.y <<"交点"<< endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));

					}
					else
					{
						intersection = intersection_segment_to_circle(pointb, pointc, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
					}

				}
				else if (collision.x >= -0.9&&collision.x <= 0.9&&collision.y >= -1 && collision.y <= 3.8)
				{
					L.push_back(0);
				}
				else if (point_in_circle(collision, circlea) && collision.x < -0.9)
				{
					intersection = intersection_segment_to_circle(pointa, pointd, circles);
					L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
				}

				else
				{
					L.push_back(100000);
					cout << "范围错误" << endl;
				}

			}//向前，右转


			else if (shiftpos == 2 & wheelangle > 0)
			{
				circle<float> circleb;
				circleb.radius = distance_point_to_point(circlepoint, pointb);
				circleb.x = circlepoint.x;
				circleb.y = circlepoint.y;
				cout << circlepoint.x << endl;
				if (collision.y > 3.8 || (collision.x<-0.9&&collision.y>0)){
					if (circles.radius > distance_point_to_point(circlepoint, pointd))
					{
						intersection = intersection_segment_to_circle(pointd, pointc, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));

					}
					else
					{
						intersection = intersection_segment_to_circle(pointa, pointd, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
					}

				}
				else if (collision.x >= -0.9&&collision.x <= 0.9&&collision.y >= -1 && collision.y <= 3.8)
				{
					L.push_back(0);
				}
				else if (point_in_circle(collision, circleb) && collision.x > 0.9)
				{
					intersection = intersection_segment_to_circle(pointb, pointc, circles);
					L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
				}
				else
				{
					L.push_back(100000);
					cout << "范围错误" << endl;
				}

			}//向前，左转


			else if (shiftpos != 2 & wheelangle < 0)
			{
				if (collision.y < -1 || (collision.x<-0.9&&collision.y>-1 && collision.y<3.8)){
					if (circles.radius>distance_point_to_point(circlepoint, pointa))
					{
						intersection = intersection_segment_to_circle(pointa, pointd, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));

					}

					else
					{
						intersection = intersection_segment_to_circle(pointa, pointb, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
					}
				}
				else if (collision.x >= -0.9&&collision.x <= 0.9&&collision.y >= -1 && collision.y <= 3.8)
				{
					L.push_back(0);
				}
				else if (collision.x > 0.9&&collision.y > -1 && collision.y < 0)
				{
					intersection = intersection_segment_to_circle(pointb, pointc, circles);
					L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
				}
				else
				{
					L.push_back(100000);
					cout << "范围错误" << endl;
				}
			}//向后，右转


			else if (shiftpos != 2 & wheelangle > 0)
			{
				if (collision.y < -1 || (collision.x>0.9&&collision.y > -1 && collision.y<3.8)){
					if (circles.radius>distance_point_to_point(circlepoint, pointb))
					{
						intersection = intersection_segment_to_circle(pointb, pointc, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));

					}
					else
					{
						intersection = intersection_segment_to_circle(pointa, pointb, circles);
						//cout << intersection.x << "," << intersection.y << "交点" << endl;
						L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));
					}
				}
				else if (collision.x >= -0.9&&collision.x <= 0.9&&collision.y >= -1 && collision.y <= 3.8)
				{
					L.push_back(0);
				}
				else if (collision.x < -0.9&&collision.y<0 && collision.y>-1)
				{
					intersection = intersection_segment_to_circle(pointa, pointd, circles);
					L.push_back(fabs(asin(angle(circlepoint, collision, intersection)) / (2 * PI) * 2 * PI*circles.radius));

				}
				else
				{
					L.push_back(100000);
					cout << "范围错误" << endl;
				}



			}//向后，左转

		}

		else
		{
			cout << "(" << collision.x << "," << collision.y << ")" << "此点不在碰撞区" << endl;
			L.push_back(100000);
		}

	}
	float tempdistance = 0;
	tempdistance = L[0];

	for (int i = 1; i < ObjNUM; i++)
	{
		if (L[i] <= tempdistance)
		{
			tempdistance = L[i];
		}
	}

	return tempdistance;
}

//float get_mindistance(float Radius, int shiftpos, float wheelangle, Point2f* objpoints, int ObjNUM)
//{
//	point2d<float> *temp;
//	for (int i = 0; i < ObjNUM; i++)
//	{
//		temp[i].x = objpoints[i].x;
//		temp[i].y = objpoints[i].y;
//	}
//
//	return get_mindistance_code( Radius,  shiftpos,  wheelangle,  temp,  ObjNUM)
//
//}


