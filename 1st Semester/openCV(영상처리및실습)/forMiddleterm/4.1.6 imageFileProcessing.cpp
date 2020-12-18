#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
        Mat image = imread("../olaf.jpg", IMREAD_COLOR);
        CV_Assert(image.data);

        vector<int> params_jpg, params_png;
        params_jpg.push_back(IMWRITE_JPEG_QUALITY);
        params_jpg.push_back(50);
        params_png.push_back(IMWRITE_PNG_COMPRESSION);
        params_png.push_back(9);

        imwrite("../image/write_test1.jpg", image);
        imwrite("../image/write_test2.jpg", image);
        imwrite("../image/write_test3.png", image);
        imwrite("../image/write_test4.bmp", image);
        return 0;
}