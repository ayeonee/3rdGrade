#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
   
//1차원 DFT, 역변환 시에는 정변환과 같은 구조지만 전체 갯수로 나눠주는 부분만 추가 됨.
Mat DFT_1D(Mat one_row, int dir) //원본이미지의 한 행을 받음, 그 행에 대한 1차원 푸리에변환 진행,  dir=어떤 방향으로 할 것인가. -1일 경우 역변환 , 다른경우는 정변환
{
    int N = one_row.cols; //전체 크기 저장할 변수
    Mat dst(one_row.size(), CV_32FC2); //실수와 허수를 같이 담고 있는, 결과 영상 행렬 필요. 

    //푸리에변환 진행.
    for (int k = 0; k < N; k++)
    {
        Vec2f complex(0, 0); //계산된 결과 누적해주는 변수(=해당 위치가 주파수영역으로 바뀐 값
        for (int n = 0; n < N; n++)
        {
            float theta = dir * -2 * CV_PI * k * n / N; //dir=역변환, 정변환 구분. dir이 -면 부호바뀜.
            Vec2f value = one_row.at<Vec2f>(n); //원본영상 받아서 그 영상의 실수값, 허수값 이용해서 계산.

            complex[0] += value[0] * cos(theta) - value[1] * sin(theta); 
            complex[1] += value[1] * cos(theta) + value[0] * sin(theta);
            //value[0]=실제영상의 실수부, value[1]=허수부
        }
        dst.at<Vec2f>(k) = complex; //실수와 허수로 누적된 값들이 각각 들어감.
    }

    if (dir == -1)
    {
        dst /= N;
    }

    return dst; //결과행렬 반환
}

//2차원DFT 실제 계산할 이미지(역변환 시에는 주파수 영역의 데이터가 되고 정변환 하면 2채널로 된 원본 이미지가 됨)
void DFT_2D(Mat complex_img, Mat& dst, int dir) //원본주파수영역 넣는 변수, 변환된 결과값 넣는 변수, 역변환할것인가 정변환할것인가에 대한 인자값
{
    complex_img.convertTo(complex_img, CV_32F); //실제계산할때는 float 형태로 받아야해서 변환.
    Mat tmp(complex_img.size(), CV_32FC2, Vec2f(0, 0)); //실제 계산이 이루어질 임시 행렬. 푸리에변환은 가로방향으로 한번, 전치해서 세로방향으로  한번 하기 때문에 해당 값을 가지고 있을 임시 변수 필요함.
    tmp.copyTo(dst); //결과 행렬에 대한 것도 초기화.

    for (int i = 0; i < complex_img.rows; i++) //가로방향으로 푸리에변환
    {
        Mat dft_row = DFT_1D(complex_img.row(i), dir); //한 줄에 대한 1차원 푸리에변환 진행.
        dft_row.copyTo(tmp.row(i));
    }

    transpose(tmp, tmp); //행렬전치

    for (int i = 0; i < tmp.rows; i++)
    {
        Mat dft_row = DFT_1D(tmp.row(i), dir);
        dft_row.copyTo(dst.row(i)); //계산 결과를 실제 영상에 넣음.
    }
    transpose(dst, dst); //다시 전치
}

//log 함수 적용 후 정규화(0~255)
void log_mag(Mat complex_mat, Mat& dst)
{
    Mat planes[2];
    split(complex_mat, planes); //2채널 행렬 분리(실수와 허수의 크기를 가지고 벡터의크기를 구해야해서)
    //주파수 영역으로 바뀐 데이터를 벡터의 크기로 바꿔서 그것을 화면에 보여줌.
    magnitude(planes[0], planes[1], dst); //벡터 크기 구해서 더함.

    log(dst + 1, dst);  //log 함수할때 값이 0이면 무한대로 가니까 +1해줌.
    normalize(dst, dst, 0, 255, CV_MINMAX); //이미지 픽셀로 나타나야해서 0~255, 타입은 MINMAX (가장 큰것에서 작은것까지)

    dst.convertTo(dst, CV_8U); //dst가 float형태로 되어있기에 화면에 띄울려면 usigned float 형태로 바꿔줌.
}

//shuffling
void shuffling(Mat mag_img, Mat& dst)
{
    //들어오는이미지의 center값 (1,2,3,4사분면 나누는 기준)
    int cx = mag_img.cols / 2; 
    int cy = mag_img.rows / 2;

    Rect q1(cx, 0, cx, cy);
    Rect q2(0, 0, cx, cy);
    Rect q3(0, cy, cx, cy);
    Rect q4(cx, cy, cx, cy);

    dst = Mat(mag_img.size(), mag_img.type());
    mag_img(q1).copyTo(dst(q3));
    mag_img(q3).copyTo(dst(q1));
    mag_img(q2).copyTo(dst(q4));
    mag_img(q4).copyTo(dst(q2));
}

int main()
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat complex_img, dft_coef, dft_img, idft_coef, shuffling_img, idft_img[2];
    Mat tmp[] = { image, Mat::zeros(image.size(),CV_8U) }; //실수와 허수를 가질 수 있는 type으로 이미지 변환. 두개의값을 갖는 행렬로 만들고 이를 merge시켜 2채널의 행렬로 만듦. 1채널에는 원본이미지, 2채널에는 허수부 계산을 위한 0으로 된 행렬추가.

    merge(tmp, 2, complex_img); 

    DFT_2D(complex_img, dft_coef, 1); //1=정변환
    log_mag(dft_coef, dft_img);
    shuffling(dft_img, shuffling_img);

    DFT_2D(dft_coef, idft_coef, -1);
    split(idft_coef, idft_img); //2채널 함수 분리
    idft_img[0].convertTo(idft_img[0], CV_8U);

    imshow("image", image);
    imshow("dft_img", dft_img);
    imshow("shuffling_img", shuffling_img);
    imshow("idft_img[0]", idft_img[0]);

    waitKey(0);
    return 0;
}