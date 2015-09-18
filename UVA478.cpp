#include<iostream>
#include<cmath>
using namespace std;
struct point {
	double x;
	double y;
};
struct Rectangle{
	point lu;//左上leftup
	point rd;//右下rightdown
};
struct Circle {
	point cc;//圓心circle center
	double r;//半徑radius
};
struct Triangle {
	point tr_point[3];//三點
};
struct figure {
	char type;
	union {
		Rectangle rec;
		Circle cir;
		Triangle tri;
	};
};
int dis(point p, Circle c) {
	if (sqrt((p.x - c.cc.x)*(p.x - c.cc.x) + (p.y - c.cc.y)*(p.y - c.cc.y)) < c.r)
		return 1;
	else
		return 0;
}
double area(point a, point b,point c)
{
	return fabs((a.x*b.y + b.x*c.y + c.x*a.y) - (b.x*a.y + c.x*b.y + a.x*c.y));
}
int areacheck(point p, Triangle t) {
	double area1, area2, area3, area_total;
	area1 = area(p, t.tr_point[0], t.tr_point[1]);
	area2 = area(p, t.tr_point[1], t.tr_point[2]);
	area3 = area(p, t.tr_point[0], t.tr_point[2]);
	area_total = area(t.tr_point[0], t.tr_point[1], t.tr_point[2]);
	if (fabs(area_total - (area1 + area2 + area3))<0.00001)
		return 1;
	else
		return 0;
}
int main()
{
	char c;
	figure fig[10];
	int num_fig = 0;
	while (cin >> c)
	{
		if (c == '*')break;
		else {
			fig[num_fig].type = c;
			if (fig[num_fig].type == 'r') {

				cin >> fig[num_fig].rec.lu.x
					>> fig[num_fig].rec.lu.y
					>> fig[num_fig].rec.rd.x
					>> fig[num_fig].rec.rd.y;
			}
			else if (fig[num_fig].type == 'c') {
				cin >> fig[num_fig].cir.cc.x
					>> fig[num_fig].cir.cc.y
					>>fig[num_fig].cir.r;
			}
			else if (fig[num_fig].type == 't')
			{
				cin >> fig[num_fig].tri.tr_point[0].x >> fig[num_fig].tri.tr_point[0].y
					>> fig[num_fig].tri.tr_point[1].x >> fig[num_fig].tri.tr_point[1].y
					>> fig[num_fig].tri.tr_point[2].x >> fig[num_fig].tri.tr_point[2].y;
			}
			num_fig++;
		}
	}
	point in_p;
	int num_p=1;
	bool containp = 0;//是否包含fig
	while (cin >> in_p.x >> in_p.y)
	{
		containp = 0;
		if (in_p.x == 9999.9 && in_p.y == 9999.9)break;
		else
		{
			for (int i = 0; i < num_fig; i++) {
				if (fig[i].type == 'r')
				{
					if (in_p.x > fig[i].rec.lu.x
						&&in_p.x < fig[i].rec.rd.x
						&&in_p.y < fig[i].rec.lu.y
						&&in_p.y > fig[i].rec.rd.y)
					{
						cout << "Point " << num_p << " is contained in figure " << i + 1 << endl;
						containp = 1;
					}
				}
				else if (fig[i].type == 'c') {
					if (dis(in_p, fig[i].cir)==1)
					{
						cout << "Point " << num_p << " is contained in figure " << i + 1 << endl;
						containp = 1;
					}
				}
				else if (fig[i].type == 't') {
					if (areacheck(in_p, fig[i].tri) == 1)
					{
						cout << "Point " << num_p << " is contained in figure " << i + 1 << endl;
						containp = 1;
					}
				}
			}
			if (!containp)
			{
				cout << "Point " << num_p << " is not contained in any figure" << endl;
			}
			num_p++;
		}
	}
	return 0;
}
