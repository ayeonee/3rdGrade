#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string title = "중간고사";
Mat image;
string bar_name = "밝기";
string bar_name2 = "대비";

void onChange(int value, void* userdata) //밝기 값을 변경하는 트랙바 콜백함수
{
    int add_value = value - 130;
    cout << "추가 화소값" << add_value << endl;

    Mat dst(size(image), CV_8UC1);
    image.convertTo(dst, CV_8UC1);
    Mat tmp = dst + add_value;
    imshow(title, tmp);
}

void onChange2(int value, void* userdata) //대비값을 변경하는 트랙바 콜백함수
{
    int add_value = value/10;
    cout << "변경 대비값" << add_value << endl;

    Mat dst(size(image), CV_8UC1);
    image.convertTo(dst, CV_8UC1);
    Mat tmp = dst + add_value;
    imshow(title, tmp);
}

void onMouse(int event, int x, int y, int flags, void* parm) {
    if (event == EVENT_RBUTTONDOWN) {
        setTrackbarPos(bar_name, title, 130); //트랙바 연결
        setTrackbarPos(bar_name2, title, 10);
        image = imread("../lena.jpg", IMREAD_COLOR); //사진 초기화
        imshow(title, image);

    }
    else if (event == EVENT_LBUTTONDOWN) {
      
        Mat dst; 
        //히스토그램을 어떻게 불러오는지 모르겠습니다 ㅠㅠ
        //시간이 많을 때 다시 생각해보겠습니다... ㅠㅠ
        /*equalizeHist(hist, dst);      //히스토그램 평활화
        draw_histo(hist, hist_img);
    */
    }
   
}

void calc_histo(const Mat& image, Mat& hist, int bins, int range_max = 256)//히스토그램 계산
{
    int histSize[] = { bins };
    float range[] = { 0,(float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };

    Mat gray;
    image.convertTo(gray, IMREAD_GRAYSCALE);

    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges); 

}

void draw_histo(Mat hist, Mat& hist_img, Size size = Size(256, 200)) //히스토그램 출력
{
    hist_img = Mat(size, CV_8U, Scalar(255)); 
    float bin = (float)hist_img.cols / hist.rows;
    normalize(hist, hist, 0, hist_img.rows, NORM_MINMAX); 

    for (int i = 0; i < hist.rows; i++) {
        float start_x = i * bin;
        float end_x = (i + 1) * bin;
        Point2f pt1(start_x, 0); 
        Point2f pt2(end_x, hist.at<float>(i)); 

        if (pt2.y > 0) {
            rectangle(hist_img, pt1, pt2, Scalar(0), -1);
        }
    }
    flip(hist_img, hist_img, 0); 
}
int main()
{
    int value = 130;
    int value2 = 10;
    image = imread("../lena.jpg", IMREAD_COLOR); //lena 컬러 이미지로 불러오기
    CV_Assert(image.data);

    Mat hist, hist_img;
    calc_histo(image, hist, 64); //히스토그램 사이즈 64로 설정
    draw_histo(hist, hist_img);


    namedWindow(title, WINDOW_AUTOSIZE);
    createTrackbar(bar_name, title, &value, 255, onChange);
    createTrackbar(bar_name2, title, &value2, 100, onChange2);

    setMouseCallback(title, onMouse);
    imshow(title, image);
    imshow("히스토그램", hist_img);
    waitKey(0);
    return 0;
}