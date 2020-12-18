#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Size2d sz(100.5, 60.6);
    Point2f pt1(20.f, 30.f), pt2(100.f, 200.f);

    Rect_<int> rect1(10, 10, 30, 50); //x, y, 너비,높이
    Rect_<float>rect2(pt1, pt2); //시작좌표, 종료좌표
    Rect_<double> rect3(Point2d(20.5, 10), sz); //시작좌표, size_객체

    Rect rect4 = rect1 + (Point)pt1; //시작좌표변경 -> 평행이동
    Rect2f rect5 = rect2 + (Size2f)sz; //사각형덧셈 -> 크기 변경
    Rect2d rect6 = rect1 & (Rect)rect2; //두사각형 교차영역

    cout << "rect3 = " << rect3.x << ", " << rect3.y << ", ";
    cout << rect3.width << "x" << rect3.height << endl;
    cout << "rect4= " << rect4.tl() << " " << rect4.br() << endl; //tl = top left, br = botton right 좌표
    cout << "rect5 크기= " << rect5.size() << endl;
    cout << "[rect6] = " << rect6 << endl;

    return 0;
}