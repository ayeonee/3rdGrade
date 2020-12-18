#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//1번
/*uchar bilinear_value(Mat img, double x, double y) //양선형 보간법
{
    if (x >= img.cols - 1)
        x--;
    if (y >= img.rows - 1)
        y--;
    Point pt((int)x, (int)y);
    int A = img.at<uchar>(pt);
    int B = img.at<uchar>(pt + Point(0, 1));
    int C = img.at<uchar>(pt + Point(1, 0));
    int D = img.at<uchar>(pt + Point(1, 1));

    double alpha = y - pt.y;
    double beta = x - pt.x;
    int M1 = A + (int)cvRound(alpha * (B - A));
    int M2 = C + (int)cvRound(alpha * (D - C));
    int P = M1 + (int)cvRound(beta * (M2 - M1));

    return saturate_cast<uchar>(P);
}

//회전함수
void rotation(Mat img, Mat& dst, double degree) //몇도 회전시킬것인가
{
    double radian = degree / 180 * CV_PI; //라디안값으로  바꾸기  
    double sin_value = sin(radian);
    double cos_value = cos(radian);

    Rect rect(Point(0, 0), img.size());
    //출력영상 크기 조정
    int imageW = img.size().width;
    int imageH = img.size().height;
    double new_radian = (90 - degree) / 180 * CV_PI;
    double cos_90 = cos(new_radian);
     dst = Mat(Size(imageH * cos_90 + imageW * cos_value, imageH * cos_value + imageW * cos_90), img.type(), Scalar(0));
    imageH = img.size().height - 1;
    Point center = img.size() / 2;
    //사진 중앙으로 옮겨주기
    int adding_width = ((dst.size().width - img.size().width) / 2);
    int adding_height = ((dst.size().height - img.size().height) / 2);
    //회전수행
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            int new_i = i - adding_height;
            int new_j = j - adding_width;
            double x = (imageH - new_i - center.y) * sin_value + (new_j - center.x) * cos_value + center.x;
            double y = imageH - ((imageH - new_i - center.y) * cos_value - (new_j - center.x) * sin_value + center.y);

            if (rect.contains(Point2d(x, y))) //목적영상에 원본영상의 좌표가 있지 않으면 아무것도 안하게 함
            {
                dst.at<uchar>(i, j) = bilinear_value(img, x, y); //양선형보간법으로 만들어진 새로운 픽셀값을 결과영상에 붙여넣음
            }
        }
    }
}

//평행이동
void translation(Mat img, Mat& dst, Point pt)
{
    Rect rect(Point(0, 0), img.size());
    int imageW = img.size().width;
    int imageH = img.size().height;
    //출력영상 크기 조절
    dst = Mat(Size(imageW+pt.x, imageH+pt.y),CV_8UC1, Scalar(0));

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            Point dst_pt(j, i);
            Point img_pt = dst_pt - pt;
            if (rect.contains(img_pt)) {
                dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);
            }
        }
    }
}

int main(int argc, const char* arcv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);
    Mat dst;
    Point p(100, 100);

    imshow("image", image);
    rotation(image, dst, 30); //30도만큼 회전
    translation(dst, dst, p); //이동
    imshow("dst", dst);
    waitKey(0);
    return 0;
}*/

//2번
/////////////////
//문제2 알고리즘
//1. 이미지를 Grayscale로 불러온다.
//2. threshold를 이용해 0과 1로된 흑백으로 나타낸다. 이때 threshold 값을 높여주어 나사 안 공간을 최대한 매꾼다.
//3.  닫힘연산을 이용해 이미지의 빈공간을 매꾸어준다.
//4. convolution함수, sobel 마스크를 이용해 경계선을 검출한다.
/////////////////


//침식연산을 위해 마스크와 픽셀값을 매칭.
bool check_match(Mat img, Point start, Mat mask, int mode = 0)
{
    for (int u = 0; u < mask.rows; u++)
    {
        for (int v = 0; v < mask.cols; v++)
        {
            Point pt(v, u); //마스크에 해당하는 위치값
            int m = mask.at<uchar>(pt); //1일경우에만 계산하기 때문에 해당마스크의 값도 가져옴
            int p = img.at<uchar>(start + pt); //마스크와 대응되는 실제 이미지의 픽셀값

            bool ch = (p == 255);
            if (m == 1 && ch == mode) //침식연산일 경우 하나라도 false면 false
            {
                return false;
            }
        }
    }  return true;
}

//침식연산함수
void erosion(Mat img, Mat& dst, Mat mask) {

    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(1));
    }
    Point center = mask.size() / 2;
    for (int i = center.y; i < img.rows - center.y; i++)
    {
        for (int j = center.x; j < img.cols - center.x; j++)
        {
            Point start = Point(j, i) - center;
            bool check = check_match(img, start, mask, 0);
            dst.at<uchar>(i, j) = (check) ? 255 : 0;
        }
    }
}

//팽창연산함수
void dilation(Mat img, Mat& dst, Mat mask)
{
    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(0));
    }
    Point center = mask.size() / 2;
    for (int i = center.y; i < img.rows - center.y; i++)
    {
        for (int j = center.x; j < img.cols - center.x; j++)
        {
            Point start = Point(j, i) - center;
            bool check = check_match(img, start, mask, 1);
            dst.at<uchar>(i, j) = (check) ? 0 : 255;
        }
    }
}

//외곽부분의 빈공간을 현재 외곽부분으로 채우며 마스크 적용.
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
    Mat image = imread("../nasa.jpg", IMREAD_GRAYSCALE); //이미지 그레이 스케일로 받아옴.
    CV_Assert(image.data);
    imshow("image", image);

    Mat dst, vSobel, hSobel;
    threshold(image, dst, 230, 255, THRESH_BINARY); //임계값을 높여주었다.

    uchar data[] = {
     0,1,0,
     1,1,1,
     0,1,0
    };

    Mat mask(3, 3, CV_8UC1, data);
    
    //닫힘연산 수행
    erosion(dst, dst, (Mat)mask);
    erosion(dst, dst, (Mat)mask);
    erosion(dst, dst, (Mat)mask);
    erosion(dst, dst, (Mat)mask);
    erosion(dst, dst, (Mat)mask);
    erosion(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);
    dilation(dst, dst, (Mat)mask);


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

    Mat vmask(3, 3, CV_32F, vdata); //수직방향 마스크 적용
    Mat hmask(3, 3, CV_32F, hdata); //수평방향 마스크 적용
    convolution(dst, vSobel, vmask); //sobel 마스크 적용
    convolution(dst, hSobel, hmask);
    magnitude(vSobel, hSobel, dst); //두 가지 행렬을 받아서 벡터 계산 후 크기를 반환, 
    imshow("dst", dst);
    waitKey(0);
    return 0;
}