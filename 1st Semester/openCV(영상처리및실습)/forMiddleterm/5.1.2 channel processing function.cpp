#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat ch0(3, 4, CV_8U, Scalar(10));
    Mat ch1(3, 4, CV_8U, Scalar(20));
    Mat ch2(3, 4, CV_8U, Scalar(30));

    Mat bgr_arr[] = { ch0, ch1, ch2 };
    Mat bgr1;
    merge(bgr_arr, 3, bgr1); //합침
    vector<Mat> bgr_vec;
    split(bgr1, bgr_vec); //분리

    //
    Mat image = imread("../olaf.jpg", IMREAD_COLOR);
    CV_Assert(image.data);

    Mat bgr[3];
    split(image, bgr);
    imshow("파란 올라프", bgr[0]);
    imshow("초록 올라프", bgr[0]);
    imshow("빨간 올라프", bgr[0]);
    waitKey(0);
    return 0;
}