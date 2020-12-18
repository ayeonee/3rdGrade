#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat image1(300, 400, CV_8U, Scalar(255)); //흰색바탕
    Mat image2(300, 400, CV_8U, Scalar(100)); //회색바탕
    string title1 = "흰창 제어";
    string title2 = "회색창 제어";
    string title3 = "창크기 변경-auto";
    string title4 = "창크기 변경-normal";

    namedWindow(title1, WINDOW_AUTOSIZE); //autosize 대신 1 가능, 크기변경 불가
    namedWindow(title2, WINDOW_NORMAL); //normal대신 0 가능, 크기변경 가능
    namedWindow(title3, WINDOW_AUTOSIZE);
    namedWindow(title4, WINDOW_NORMAL);
    moveWindow(title1, 100, 200); //x,y값
    moveWindow(title2, 300, 200);
    resizeWindow(title3, 500, 200); //width, height
    resizeWindow(title4, 500, 200); 

    imshow(title1, image1);
    imshow(title2, image2);
    imshow(title3, image1);
    imshow(title4, image2);
    waitKey();
    destroyAllWindows();
    return 0;
}