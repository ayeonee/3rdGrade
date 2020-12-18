#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Matx23f src1(1, 2, 3, 4, 5, 1);
    Matx23f src2(5, 4, 2, 3, 2, 1);
    Matx32f src3(5, 4, 2, 3, 2, 1);
    Mat dst1, dst2, dst3;
    double alpha = 1.0, beta = 1.0;

    gemm(src1, src2, alpha, Mat(), beta, dst1, GEMM_1_T); //src1을 전치
    gemm(src1, src2, alpha, noArray(), beta, dst2, GEMM_2_T); //src2을 전치
    gemm(src1, src3, alpha, noArray(), beta, dst3);

    cout << "[src1] = " << endl << src1 << endl;
    cout << "[src2] = " << endl << src2 << endl;
    cout << "[src3] = " << endl << src3 << endl<<endl;

    cout << "[dst1] = " << endl << dst1 << endl;
    cout << "[dst2] = " << endl << dst2 << endl << endl;
    cout << "[dst3] = " << endl << dst3 << endl;

    //4개좌표로 사각형 그리고 사각형 회전하기
    vector<Point> rect_pt1, rect_pt2;
    rect_pt1.push_back(Point(200, 50));
    rect_pt1.push_back(Point(400, 50));
    rect_pt1.push_back(Point(400, 250));
    rect_pt1.push_back(Point(200, 250));

    float theta = 20 * CV_PI / 180; //라디안각도계산
    Matx22f m(cos(theta), -sin(theta), sin(theta), cos(theta));
    transform(rect_pt1, rect_pt2, m);
    Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < 4; i++) {
        line(image, rect_pt1[i], rect_pt1[(i + 1) % 4], Scalar(0, 0, 0), 1);
        line(image, rect_pt2[i], rect_pt2[(i + 1) % 4], Scalar(255, 0, 0), 2);
        cout << "rect_pt1[" + to_string(i) + "]=" << rect_pt1[i] << "\t";
        cout << "rect_pt2[" + to_string(i) + "]=" << rect_pt2[i] << endl;
    }
    imshow("image", image);
    waitKey();
    return 0;
}