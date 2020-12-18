#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat image = imread("../minMax.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);
    double minVal, maxVal;
    minMaxIdx(image, &minVal, &maxVal);

    double ratio = (maxVal - minVal) / 255.0; //비율조정
    Mat dst = (image - minVal) / ratio;

    cout << "최솟값 = " << minVal;
    cout << "최댓값 = " << maxVal;
    imshow("image", image);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}
