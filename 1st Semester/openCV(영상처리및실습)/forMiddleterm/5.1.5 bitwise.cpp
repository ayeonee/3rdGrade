#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat image1 (300, 300, CV_8U, Scalar(0));
    Mat image2 (300, 300, CV_8U, Scalar(0));
    Mat image3, image4, image5, image6;

    Point center = image1.size() / 2;
    circle(image1, center, 100, Scalar(255), -1); //-1은 원 내부 채움.
    rectangle(image2, Point(0, 0), Point(150, 300), Scalar(255), -1);

    bitwise_or(image1, image2, image3);
    bitwise_and(image1, image2, image4);
    bitwise_xor(image1, image2, image5);
    bitwise_not(image1, image6); //행렬 반전

    //imshow("image1", image1);
    //imshow("image2", image2);
    //imshow("image3", image3);
    //imshow("image4", image4);
    //imshow("image5", image5);
    //imshow("image6", image6);

     //로고합성
    Mat image = imread("../olaf.jpg", IMREAD_COLOR);
    Mat logo = imread("../logo.jpg", IMREAD_COLOR);
    Mat logo_th, masks[5], background, foreground, dst;
    CV_Assert(image.data && logo.data);

    threshold(logo, logo_th, 70, 255, THRESH_BINARY); //로고영상 이진화
    split(logo_th, masks);

    bitwise_or(masks[0], masks[1], masks[3]);
    bitwise_or(masks[2], masks[3], masks[3]);
    bitwise_not(masks[3], masks[4]);

    Point center1 = image.size() / 2;
    Point center2 = logo.size() / 2;
    Point start = center1 - center2;
    Rect roi(start, logo.size());

    bitwise_and(logo, logo, foreground, masks[3]);
    bitwise_and(image(roi), image(roi), background, masks[4]);
   
    add(background, foreground, dst);
    dst.copyTo(image(roi));
   
    imshow("background", background);
    imshow("foreground", foreground);
    imshow("dst", dst);
    imshow("image", image);
    waitKey(0);
    return 0;
 }