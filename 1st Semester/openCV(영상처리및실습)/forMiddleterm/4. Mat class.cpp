#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//int main() {
//	Mat m1 = Mat::ones(3, 5, CV_8UC1); //전부다 1로
//	Mat m2 = Mat::zeros(3, 5, CV_8UC1); //전부다 0으로
//	Mat m3 = Mat::eye(3, 3, CV_8UC1); //단위행렬
//
//	cout << "[m1]= " << endl << m1 << endl;
//	cout << "[m2]= " << endl << m2 << endl;
//	cout << "[m3]= " << endl << m3 << endl;
//	return 0;
//}
int main()
{
    double data[] = {
        1.1, 2.2, 3.3, 4.4,
        5.5, 6.6, 7.7, 8.8,
        9.9, 10, 11, 12,
        13,14,15,16
    };

    Mat m1(4, 4, CV_64F, data);
    Mat m2 = m1.clone(); //행렬의 데이터 값 복사해서 새로운 행렬 반환
    Mat m3, m4;

    Mat mask = Mat::eye(4, 4, CV_8U);
    m1.copyTo(m3, mask);  //복사할때 0으로 된 데이터는 제외하고 복사
    m1.convertTo(m4, CV_64F, 1, 1); //alpha는곱하고 beta는 더함

    cout << "m1 = \n" << m1 << endl;
    cout << "m2 = \n" << m2 << endl;
    cout << "m3 = \n" << m3 << endl;
    cout << "m4 = \n" << m4 << endl;

    return 0;
}