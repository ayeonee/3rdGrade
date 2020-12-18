#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//키보드 이벤트 제어
//int main()
//{
//    Mat image(200, 300, CV_8U, Scalar(255));
//    namedWindow("키보드 이벤트", 1);
//    imshow("키보드 이벤트", image);
//    while (1) {
//        int key = waitKey(100);
//        if (key == 27) break; //esc키
//
//        switch (key) {
//        case 'a':cout << "a키 입력" << endl; break;
//        case 'b':cout << "b키 입력" << endl; break;
//        case 0x41:cout << "A키 입력" << endl; break;
//        case 66:cout << "B키 입력" << endl; break;
//        }
//    }
//}

//마우스 이벤트제어
void onMouse(int, int, int, int, void*); //마우스 콜백함수 선언
int main() {
    Mat image(200, 300, CV_8U);
    image.setTo(255); //행렬초기화
    imshow("마우스 이벤트1", image);
    imshow("마우스 이벤트2", image);

    setMouseCallback("마우스 이벤트1", onMouse, 0);
    waitKey(0);
    return 0;
}

void onMouse(int event, int x, int y, int flags, void* param) //event와 마우스 좌표(x,y), 마우스가 어떤 키와 눌렸는가에 대한 정보(flag), userdata 받아올 수 있는 매개변수
{
    switch (event) {
    case EVENT_LBUTTONDOWN:
        cout << "마우스 왼쪽 버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONDOWN:
        cout << "마우스 오른쪽 버튼 누르기" << endl;
        break;
    case EVENT_RBUTTONUP:
        cout << "마우스 오른쪽 버튼 떼기" << endl;
        break;
    case EVENT_LBUTTONDBLCLK:
        cout << "마우스 왼쪽 버튼 더블클릭" << endl;
        break;
    }
};