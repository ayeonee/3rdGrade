#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//전방향 사상
void scaling(Mat img, Mat& dst, Size size) 
{
    dst = Mat(size, img.type(), Scalar(0)); //목적이미지 선언
    double ratioY = (double)size.height / img.rows; //비율(원본과 목적영상간)
    double ratioX = (double)size.width / img.cols;

    for (int i = 0; i < img.rows; i++) //원본이미지 크기만큼 loop돔
    {
        for (int j = 0; j < img.cols; j++) 
        {
            int x = (int)(j * ratioX); //결과영상에 해당 화소 넣음, 특정 위치를 계산. int로 계산되면서 특정 위치가확정
            int y = (int)(i * ratioY);
            dst.at<uchar>(y, x) = img.at<uchar>(i,j);
        }
    }
}

//최근접 이웃 보간법(역방향)
void scaling_nearest(Mat img, Mat& dst, Size size)
{
    dst = Mat(size, img.type(), Scalar(0));
    double ratioY = (double)size.height / img.rows;
    double ratioX = (double)size.width / img.cols;

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            int x = (int)(j / ratioX);
            int y = (int)(i / ratioY);
            dst.at<uchar>(i,j) = img.at<uchar>(y,x);
        }
    }
}

//양선형 보간법
uchar bilinear_value(Mat img, double x, double y)
{
    //xy값이 잘못들어와서 이미지 사이즈보다 커지면 발생하는 오류를 막음
    if (x >= img.cols - 1)
        x--;
    if (y >= img.rows - 1)
        y--;
    Point pt((int)x, (int)y); //point객체로 좌표변환
    int A = img.at<uchar>(pt); //좌표와 가장 가까운 좌표의 화소값
    int B = img.at<uchar>(pt + Point(0, 1));
    int C = img.at<uchar>(pt + Point(1,0));
    int D = img.at<uchar>(pt + Point(1, 1));

    double alpha = y - pt.y;
    double beta = x - pt.x;
    int M1 = A + (int)cvRound(alpha * (B - A)); //화소값이기에 int형, 반올림함(Round함수써서)
    int M2 = C + (int)cvRound(alpha * (D - C));
    int P = M1 + (int)cvRound(beta * (M2 - M1)); //최종 값

    return saturate_cast<uchar>(P); //계산된 결과값이 0~255넘어가는 것 방지
}

void scaling_bilinear(Mat img, Mat& dst, Size size)
{
    dst = Mat(size, img.type(), Scalar(0));
    double ratioY = (double)size.height / img.rows;
    double ratioX = (double)size.width / img.cols;

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            double x = j / ratioX;
            double y = i / ratioY;
            dst.at<uchar>(i, j) = bilinear_value(img,x,y);
        }
    }
}

int main(int argc, const char * argv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    //Mat dst1, dst2;
    //scaling(image, dst1, Size(256, 256));
    //scaling(image, dst2, Size(1024, 1024));

    //imshow("image", image);
    //imshow("dst_1축소", dst1);
    //imshow("dst_2확대", dst2);

    Mat dst1;
    scaling_bilinear(image, dst1, Size(1024, 1024));

    //3차회선보간법 
    //resize(image, dst1, Size(1024, 1024), INTER_CUBIC);

    //Lanzos4 보간법
    //resize(image, dst1, Size(1024,1024), INTER_LANCZOS4);

    imshow("image", image);
    imshow("dst_1확대", dst1);


    waitKey(0);
    return 0;
}