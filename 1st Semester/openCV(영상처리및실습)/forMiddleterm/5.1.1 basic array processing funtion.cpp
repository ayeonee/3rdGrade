#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat image(500, 500, CV_8U);
    image = imread("../olaf.jpg",IMREAD_COLOR);
    CV_Assert(image.data);

    Mat x_axis, y_axis, xy_axis, rep_img, trans_img;
    flip(image, x_axis, 0); //x축 뒤집기
    flip(image, y_axis, 1); //y축 뒤집기
    flip(image, xy_axis, -1); //xy 축 뒤집기

    repeat(image, 2, 2, rep_img); //2x2로 사진 증가
    transpose(image, trans_img); //전치행렬로 전환

    imshow("그냥 올라프", image);
    imshow("뒤집힌 올라프", x_axis);
    imshow("뒤집힌 올라프", y_axis);
    imshow("뒤집힌 올라프", xy_axis);
    imshow("두마리 올라프", rep_img);
    imshow("전치행렬된 올라프", trans_img);

    waitKey(0);
    return 0;
}
