#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void print_locateROI(String str, Mat m) {
    Size size;
    Point pt;
    m.locateROI(size, pt); //부분행렬에서 부모의 행렬크기와 위치 반환
    cout << "부모크기" << size << ",";
    cout << "[" << str << "]=";
    cout << m.size() << "from" << pt << endl;
}
int main()
{
    Range r1(0, 3), r2(3, 7);
    int data[] = {
           10,11,12,13,14,15,16,
           20,21,22,23,24,25,26,
           30,31,32,33,34,35,36,
           40,41,42,43,44,45,46,
    };

    Mat m1, m2,m3;
    m1 = Mat(4, 7, CV_32S, data);
    m2 = m1(r1, r2);
    m3 = m1(r1, r1);

    print_locateROI("m2", m2);
    print_locateROI("m3", m3);

    m2.adjustROI(-1, 1, 2, -1); //관심영역 이동, 순서대로 위 아래 왼 오
    m3.adjustROI(0, -1, -2, 2);

    cout << endl << "관심영역 변경 후" << endl;
    print_locateROI("m2", m2);
    print_locateROI("m3", m3);
    cout << endl;
    cout << "변경 m2= " << endl << m2 << endl;
    cout << "변경 m3= " << endl << m3 << endl;
    return 0;
}