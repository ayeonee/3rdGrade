#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Scalar blue(255, 0, 0), red(0, 0, 255), green(0, 255, 0);
    Scalar white(0);

    Mat image(400, 600, CV_8UC3, white);
    Point pt1(50, 130), pt2(200, 300), pt3(300, 150), pt4(400, 50);
    Rect rec(pt3, Size(200, 150));

    line(image, pt1, pt2, blue, 3);
    line(image, pt3, pt4, green, 1, LINE_AA);
    line(image, pt3, pt4, green, 2, LINE_8,1);

    rectangle(image, rec, red, 1);
    rectangle(image, rec, red, FILLED, LINE_4, 1);
    rectangle(image, pt1, pt2, red, 3);

    circle(image, pt4, 40, Scalar(255, 255, 255), 1);
    ellipse(image, pt3, Size(100,60), 30, 0, 90, red, 1);
   
    imshow("image", image);
    waitKey(0);
    return 0;
}