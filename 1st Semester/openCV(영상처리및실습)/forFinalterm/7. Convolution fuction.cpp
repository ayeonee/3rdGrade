#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//중첩된 부분만 계산하는 함수
//void convolution(Mat img, Mat& dst, Mat mask) //원본사진, 결과사진행렬, 마스크행렬
//{
//    dst = Mat(img.size(), CV_32F, Scalar(0));//결과값 초기화하는 함수, 원본사이즈와 같은 크기로 설정, 0으로 채워져있음
//    Point maskCenter = mask.size() / 2;//중심값 알아야함, 사이즈 함수가 너비, 높이 알기에 나누기 2하면 중심값 알수있음
//
//    for (int i = maskCenter.y; i<img.rows - maskCenter.y; i++) //중첩된 포문 4개, (원본이미지와 마스크이미지)
//    {
//        for (int j = maskCenter.x; j < img.cols - maskCenter.x; j++) {
//            float sum = 0;
//
//            for (int u = 0; u < mask.rows; u++) { //마스크에 대한 루프문
//                for (int v = 0; v < mask.cols; v++) {
//                    int y = i + u - maskCenter.y;
//                    int x = j + v - maskCenter.x;
//
//                    sum+=mask.at<float>(u, v) * img.at<uchar>(y, x);//원본에서는 픽셀값이기에 unsignedchar
//                }
//            }
//            dst.at<float>(i, j) = sum;
//        }
//    }
//}

//비어있는 영역에 상수를 삽입하는 함수
//void convolution(Mat img, Mat& dst, Mat mask, uchar borderPixel=0) //특정 픽셀값 받아서 비어있는 부분 동작시 그 수로 채움. 
//{
//    dst = Mat(img.size(), CV_32F, Scalar(0));
//    Point maskCenter = mask.size() / 2;
//
//    for (int i = 0; i < img.rows; i++) {//0부터 시작해서 끝까지, 이미지의 외곽도 계산.
//        for (int j = 0; j < img.cols; j++) {
//            float sum = 0;
//
//            for (int u = 0; u < mask.rows; u++) {
//                for (int v = 0; v < mask.cols; v++) {
//                    int y = i + u - maskCenter.y;
//                    int x = j + v - maskCenter.x;
//
//                    if (y<0 || y>img.rows - 1 || x<0 || x>img.cols - 1) //외곽인 부분(특정한 상수값을 넣어서 계산)
//                    {
//                        sum += mask.at<float>(u, v) * borderPixel;
//                    }
//                    else {
//                        sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
//                    }
//                }
//            }
//            dst.at<float>(i, j) = sum;
//        }
//    }
//   }

//외곽부분의 빈공간을 현재 외곽부분으로 채워넣는 함수
//void convolution(Mat img, Mat& dst, Mat mask) 
//{
//    dst = Mat(img.size(), CV_32F, Scalar(0));
//    Point maskCenter = mask.size() / 2;
//
//    for (int i =0; i < img.rows ; i++) 
//    {
//        for (int j = 0; j < img.cols; j++) {
//            float sum = 0;
//
//            for (int u = 0; u < mask.rows; u++) { 
//                for (int v = 0; v < mask.cols; v++) {
//                    int y = i + u - maskCenter.y;
//                    int x = j + v - maskCenter.x;
//
//                    if (y < 0) {
//                        y = 0;
//                    }
//                    else if (y >= img.rows) {
//                        y = img.rows - 1;
//                    }
//                    if (x < 0) {
//                        x = 0;
//                    }
//                    else if (x >= img.cols) {
//                        x = img.cols - 1;
//                    }
//                    sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
//                }
//            }
//            dst.at<float>(i, j) = sum;
//        }
//    }  
//}

//래핑하는 함수
void convolution(Mat img, Mat& dst, Mat mask)
{
    dst = Mat(img.size(), CV_32F, Scalar(0));
    Point maskCenter = mask.size() / 2;

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++) {
            float sum = 0;

            for (int u = 0; u < mask.rows; u++) {
                for (int v = 0; v < mask.cols; v++) {
                    int y = i + u - maskCenter.y;
                    int x = j + v - maskCenter.x;

                    if (y < 0) {
                        y =img.rows+y;
                    }
                    else if (y >= img.rows) {
                        y = y-img.rows;
                    }
                    if (x < 0) {
                        x = img.cols + x;
                    }
                    else if (x >= img.cols) {
                        x = x-img.cols;
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
  
    float data1[] = { //블러링하는 마스크 데이터
        1 / 9.f, 1 / 9.f, 1 / 9.f,
         1 / 9.f, 1 / 9.f, 1 / 9.f,
         1 / 9.f, 1 / 9.f, 1 / 9.f
    };

    float data[]{ //샤프닝하는 마스크 데이터
        0,-1,0,
        -1,5,-1, 
        0,-1,0
    };
    Mat mask(3, 3, CV_32F, data); //하나의 행렬만듦
    Mat blur; //결과값 불러올 블러
    convolution(image, blur, mask);
    blur.convertTo(blur, CV_8U); //unsignedchar로 바꾸어주는 작업 필요함

    imshow("image", image);
    imshow("blur", blur);
    waitKey(0);
    return 0;
}