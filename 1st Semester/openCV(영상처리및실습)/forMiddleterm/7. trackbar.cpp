#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

string title = "밝기변경";
Mat image;
string bar_name = "밝기";

bool isMouseClick = false;

void onChange(int value, void* userdata)//초기값 설정, 사용자데이터 넣을 수 있게끔
{
    int add_value = value - 130;
    cout << "추가 화소값" << add_value << endl;

    Mat dst(size(image), CV_8U);
    image.convertTo(dst, CV_8U);
    Mat tmp = dst + add_value;
    imshow(title, tmp);
}

void onMouse(int event, int x, int y, int flags, void* parm) {
    if (event == EVENT_RBUTTONDOWN) {
        add(image, 10, image);
        setTrackbarPos(bar_name, title, image.at<uchar>(0));
        //image.setTo(130);
        imshow(title, image);

    }
    else if (event == EVENT_LBUTTONDOWN) {
        //subtract(image, 10, image);
        //setTrackbarPos(bar_name, title, image.at<uchar>(0));
        Range r1(y,y+4), r2(x,x+4);
        Mat m1 = image(r1, r2);
        m1.setTo(0);
        imshow(title, image);
        isMouseClick = true;
    }
    else if (event == EVENT_LBUTTONUP) {
        isMouseClick = false;
    }
    else if (event == EVENT_MOUSEMOVE) {
        if (isMouseClick) {
            Range r1(y, y + 4), r2(x, x + 4);
            Mat m1 = image(r1, r2);
            m1.setTo(0);
            imshow(title, image);
        }
    }
}

int main()
{
    int value = 130;
   // image = Mat(300, 400, CV_8U, Scalar(130));
    image= imread("../olaf.jpg", IMREAD_GRAYSCALE);
    CV_Assert(image.data);

    namedWindow(title, WINDOW_AUTOSIZE);
    createTrackbar(bar_name, title, &value, 255, onChange);
    //트랙바 이름, 트랙바가 생성될 윈도우창 이름, 트랙바가 어떤 위치에 있을지 초기값 설정, 트랙바의 전체 크기, 트랙바의 변화 알수 있는 콜백함수 설정(OnChange)

    setMouseCallback(title, onMouse);
    imshow(title, image);
    waitKey(0);
    return 0;
}