#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//최대값, 최소값 필터 구현
uchar min_max_fliter(Mat img, Point start, Mat mask, int mode=0) //원본이미지, 필터마스크가 시작할 시작점, 필터마스크(모든 숫자에 대해서 돌기때문에 크기정보정도만 쓴다고 생각), 모드가 0이면 최솟값 반환, 아니면 최댓값 반환
{
    bool isFirst = true; //처음 시작할 때 min_max값이 0이면 최솟값을 구할때 항상 0으로 표현하기에 처음값을 저장하게 함, 처음 시작하는거냐 아니냐
    uchar min_max = 0; //최댓값,최솟값을 저장할 변수
    for (int u = 0; u < mask.rows; u++) {
        for (int v = 0; v < mask.cols; v++) {   
            Point pt(v, u); //마스크의 위치에 대한 포인트
            int p = img.at<uchar>(start + pt); //마스크에서 지정하고 있는 위치값에 대한 실제 이미지의 픽셀값을 가져옴. 특정 위치에 대해서 마스크 전체를 돌면서 값을 가져옴. 
            if (isFirst) { //1번 들어오고 값을 넣어줌
                isFirst = false;
                min_max = p;
            }
            else {
                if (mode == 0 && min_max > p) { //최솟값 구할 경우
                    min_max = p;
                }
                else if (mode != 0 && min_max < p) { //최댓값 구할 경우
                    min_max = p;
                }
            }
        }
    }
    return min_max;
}

//침식연산구현
void erosion(Mat img, Mat& dst, Mat mask) //원본이미지, 반환한 행렬, 마스크
{
    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(1));
    }
    Point center = mask.size() / 2; //마스크 크기에서 가운뎃값 찾기
    for (int i = center.y; i < img.rows - center.y; i++) //마스크와 중첩되는 부분만 처리
    {
        for (int j = center.x; j < img.cols - center.x; j++) {
            Point start = Point(j, i) - center; //시작값(center에서 시작하는게 아닌 마스크 제일 첫번째에서 시작할 수 있도록 함
            uchar min_max = min_max_fliter(img, start, mask, 0); //가장 작은 값 갖고옴
            dst.at<uchar>(i, j) = min_max;
        }
    }
}

//팽창연산구현    
void dilation(Mat img, Mat& dst, Mat mask) {
    dst = Mat(img.size(), CV_8U, Scalar(0));
    if (mask.empty()) {
        mask = Mat(3, 3, CV_8UC1, Scalar(0));
    }
    Point center = mask.size() / 2;
    for (int i = center.y; i < img.rows - center.y; i++) {
        for (int j = center.x; j < img.cols - center.x; j++) {
            Point start = Point(j, i) - center;
            uchar min_max = min_max_fliter(img, start, mask, 1); //최댓값 갖고옴
            dst.at<uchar>(i, j) = min_max;
        }
    }
}

int main(int argc, const char* argv[])
{
    Mat image = imread("../lena.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    Mat th_img, dst1, dst2;
    threshold(image, th_img, 160, 255, THRESH_BINARY); //0과1로된 흑백으로 나타냄(160이상이면 255로 표현), 이진화된 영상.

    uchar data[] = {
           1,1,1,
           1,1,1,
           1,1,1
    };

    Mat mask(3, 3, CV_8UC1, data);

    erosion(th_img, dst1, mask);
    dilation(th_img, dst2, mask);

    imshow("image", image);
    imshow("th_img", th_img);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey(0);
    return 0;

}
