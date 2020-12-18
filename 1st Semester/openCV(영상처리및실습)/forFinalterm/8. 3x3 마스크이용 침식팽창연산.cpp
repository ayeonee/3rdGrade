#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//매칭하는 함수
bool check_match(Mat img, Point start, Mat mask, int mode = 0)
{
    for (int u = 0; u < mask.rows; u++)
    {
        for (int v = 0; v < mask.cols; v++) {
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

//침식 (물체크기 축소, 검은색더 많게)
void erosion(Mat img, Mat & dst, Mat mask){
 
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

//팽창 (물체크기 확장, 흰색더많게)
void dilation(Mat img, Mat& dst, Mat mask) 
    {
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
            bool check = check_match(img, start, mask, 1);
            dst.at<uchar>(i, j) = (check) ? 0 : 255;
        }
    }
}

int main(int argc, const char* argv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat th_img, dst1, dst2;
    threshold(image, th_img, 160, 255, THRESH_BINARY); //0과1로된 흑백으로 나타냄

    uchar data[] = {
      0,1,0,
      1,1,1,
      0,1,0
    };

    Mat mask(3, 3, CV_8UC1, data);

    erosion(th_img, dst1, mask);
    dilation(th_img, dst2, mask);

    //열림연산(침식->팽창)
   //닫힘연산(팽창->침식)
    //이런식으로 번갈아가면서 작성
    //erosion(dst1, dst1, (Mat)mask);
    //erosion(dst1, dst1, (Mat)mask);
    //dilation(dst1, dst1, (Mat)mask);
    //dilation(dst1, dst1, (Mat)mask);

    imshow("image", image);
    imshow("th_img", th_img);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey(0);
    return 0;

}