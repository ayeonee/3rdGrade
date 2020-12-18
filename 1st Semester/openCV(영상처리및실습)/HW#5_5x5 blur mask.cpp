#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void convolution(Mat img, Mat& dst, Mat mask) 
{
    dst = Mat(img.size(), CV_32F, Scalar(0));
    Point maskCenter = mask.size() / 2;

    for (int i =0; i < img.rows ; i++) 
    {
        for (int j = 0; j < img.cols; j++) {
            float sum = 0;
            for (int u = 0; u < mask.rows; u++) { 
                for (int v = 0; v < mask.cols; v++) {
                    int y = i + u - maskCenter.y;
                    int x = j + v - maskCenter.x;

                   if (y < 0) {
                        y =abs(y);
                    }
                    else if (y >= img.rows) {
                        y =((img.rows - 1)-y)*2+y;
                    }
                    if (x < 0) {
                        x = abs(x);
                    }
                    else if (x >= img.cols) {
                        x =((img.cols - 1)-x)*2+x;
                    }
                    sum+=mask.at<float>(u, v) * img.at<uchar>(y, x);
                }
            }
            dst.at<float>(i, j) = sum;
        }
    }  
}

int main(int argc, const char* arcv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    float data[] = { 
        1 / 25.f, 1 / 25.f, 1 /25.f, 1/25.f, 1/ 25.f,
        1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f,
         1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f,
          1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f,
           1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f, 1 / 25.f
    };

    Mat mask(5,5, CV_32F, data); 
    Mat blur; 
    convolution(image, blur, mask);
    blur.convertTo(blur, CV_8U);

    imshow("image", image);
    imshow("blur", blur);
    imwrite("lena_blur.jpg", blur);
    waitKey(0);
    return 0;
}