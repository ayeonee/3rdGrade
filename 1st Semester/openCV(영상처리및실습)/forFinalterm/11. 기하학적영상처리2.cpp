#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//이미지 축소(다운샘플링)
void downSampling(Mat img, Mat& dst, int scaleFactor) //scale factor = 줄이는 크기값
{
    dst = Mat(Size(img.cols / scaleFactor, img.rows / scaleFactor), CV_8UC1); //결과영상 행렬

    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            dst.at<uchar>(i, j) = img.at<uchar>(i * scaleFactor, j * scaleFactor); //원본의 위치 값 갖고와서 목적에 넣어줌
        }
    }
}

//이미지 회전 구현하기
uchar bilinear_value(Mat img, double x, double y) //양선형 보간법
{
    if (x >= img.cols - 1)
        x--; 
    if (y >= img.rows - 1)
        y--;
    Point pt((int)x, (int)y);
    int A = img.at<uchar>(pt);
    int B = img.at<uchar>(pt+Point(0,1));
    int C = img.at<uchar>(pt+Point(1,0));
    int D = img.at<uchar>(pt+Point(1,1));

    double alpha = y - pt.y;
    double beta = x - pt.x;
    int M1 = A + (int)cvRound(alpha * (B - A));
    int M2 = C + (int)cvRound(alpha * (D - C));
    int P = M1 + (int)cvRound(beta * (M2 - M1));

    return saturate_cast<uchar>(P);
}

//회전
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


    dst = Mat(Size(imageH*cos_90+imageW*cos_value,imageH*cos_value+imageW*cos_90), img.type(), Scalar(0));
    imageH = img.size().height - 1;
    Point center = img.size() / 2;
    //사진 중앙으로 옮겨주기
    int adding_width = ((dst.size().width - img.size().width) / 2);
    int adding_height = ((dst.size().height - img.size().height) / 2);
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            ////좌표0,0에서 회전 구현
            //double x = i * sin_value + j * cos_value;
            //double y = i * cos_value - j * sin_value;
         // 이미지 중심에서 회전 구현
           //double x=(i-center.y)*sin_value+(j-center.x)*cos_value+center.x;
            //double y=(i-center.y)*cos_value-(j-center.x)*sin_value+center.y;

            int new_i = i - adding_height;
            int new_j = j - adding_width;

         // 수학좌표계로 변경후
            double x=(imageH-new_i-center.y)*sin_value+(new_j-center.x)*cos_value+center.x;
            double y=imageH-((imageH-new_i-center.y)*cos_value-(new_j-center.x)*sin_value+center.y);

            if (rect.contains(Point2d(x, y))) //목적영상에 원본영상의 좌표가 있지 않으면 아무것도 안하게 함, 해당값이 들어가있는가 들어가있지않는가
            {
                dst.at<uchar>(i, j) = bilinear_value(img, x, y); //양선형보간법으로 만들어진 새로운 픽셀값을 결과영상에 붙여넣음
            }
        }
    }
}

//대칭
void Symmetry(Mat img, Mat& dst, int type)
{
    dst = Mat(Size(img.cols, img.rows), CV_8UC1);

    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            if (type == 0)
            {
                //상하대칭
                dst.at<uchar>(dst.rows - 1 - i, j) = img.at<uchar>(i, j);
            }
            else if (type == 1)
            {
                //좌우대칭
                dst.at<uchar>(i, dst.cols - 1 -  j) = img.at<uchar>(i, j);
            }
            else if (type == 2)
            {
                //상하좌우대칭
                dst.at<uchar>(dst.rows - 1 - i, dst.cols-1-j) = img.at<uchar>(i, j);
            }
        }

    }
}

//평행이동
void translation(Mat img, Mat& dst, Point pt)
{
    Rect rect(Point(0, 0), img.size());
    dst = Mat(img.size(), CV_8UC1, Scalar(0));

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
int main(int argc, const char* argv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat dst1, gaussian, sym, trans;
    Point p(30,30);
    //imshow("image", image);
    //GaussianBlur(image, gaussian, Size(3, 3), 1.2); //마스크 크기 3x3, 블러종류
    //downSampling(image, dst1, 2); //2/1로 줄임
    //imshow("dst1", dst1);

    imshow("image", image);
    rotation(image, dst1, 30);
    Symmetry(image, sym, 0);
    translation(image, trans, p);

    imshow("dst1", dst1);
    imshow("sym", sym);
    imshow("trans", trans);
    waitKey(0);
    return 0;
}