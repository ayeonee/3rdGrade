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
                        y = 0;
                    }
                    else if (y >= img.rows) {
                        y = img.rows - 1;
                    }
                    if (x < 0) {
                        x = 0;
                    }
                    else if (x >= img.cols) {
                        x = img.cols - 1;
                    }
                    sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
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

    float vdata[] = { //수직방향 마스크
        1,0,-1,
        2,0,-2,
        1,0,-1
    };
    
    float hdata[] = { //수평방향 마스크
    -1,-2,-1,
    0,0,0,
    1,2,1
    };

    Mat vmask(3, 3, CV_32F, vdata); //각각 마스크 적용
    Mat hmask(3, 3, CV_32F, hdata);

    Mat vSobel, hSobel, dst;
    convolution(image, vSobel, vmask);
    convolution(image, hSobel, hmask);
    magnitude(vSobel, hSobel, dst);//두 가지 행렬이 들어가면 행렬에 대해서 벡터 계산 후 그 크기 반환
    threshold(dst, dst, 100, 255, THRESH_BINARY);//임계값 정해놓으면 좀 더 깔끔하게 외곽선 검출 가능
    dst.convertTo(dst, CV_8U);
    imshow("image", image);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}