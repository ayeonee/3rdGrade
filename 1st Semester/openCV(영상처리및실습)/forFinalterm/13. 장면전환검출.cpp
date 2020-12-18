#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256) //히스토그램 계산
{
    int histSize[] = { bins };
    float range[] = { 0, (float)range_max };
    int channels[] = { 0 };
    const float* ranges[] = { range };
    calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
}

int main()
{
    string video_reference = "../test_news.mp4";
    VideoCapture vc; //비디오 출력
    vc.open(video_reference);
    CV_Assert(vc.isOpened()); 

    double frame_rate = vc.get(CV_CAP_PROP_FPS);  //프레임 출력 속도 설정, delay 시켜주는 작업 필요
    int delay = 1000 / frame_rate; 

    //히스토그램을 위해 크기계산과 threshold 값 만들어줌.
    int width = vc.get(CAP_PROP_FRAME_WIDTH);
    int height = vc.get(CAP_PROP_FRAME_HEIGHT);
    int threshold = height * width; //이 값 이상 넘어가면 화면 넘어갔다고 인식.
    int counter = 0; //frame 카운트.
    Mat last_hist = Mat(256, 1, CV_32F, Scalar(0)); //이전 프레임에 대한 히스토그램 값 저장

    Mat frame;//프레임별로 받아와서 출력.
    while (vc.read(frame)) //프레임 계속 받아옴. 
    {
        if (waitKey(delay) >= 0) break;

        Mat gray_frame; 
        cvtColor(frame, gray_frame, COLOR_BGR2GRAY); //grayscale 로 변환
        if (counter == 0) //0번째 프레임은 그 전 프레임이 없기 때문에 비교 안해도 됨.
        {
            calc_Histo(gray_frame, last_hist, 256); //256=히스토그램의 x축크기
            counter++; 
            continue; //다음 코드 실행이 아닌 처음으로 돌아가서 루프문 진행.
        }

        //두개의 히스토그램의 차분값을 구하고 그것을 더해주고 그것이 threshold 벗어나는가 판단->영상이 변화된지 판단
        int sum_histo_differ = 0; //히스토그램 차분값 저장하는 변수
        Mat hist; //현재프레임에 대한 히스토그램
        calc_Histo(gray_frame, hist, 256); //히스토그램 계산.

        for (int i = 0; i < 256; i++)
        {
            sum_histo_differ += abs(hist.at<float>(i) - last_hist.at<float>(i)); //차분값에 대한 절댓값
        }

        if (sum_histo_differ > threshold)
        {
            cout << "Detected scene change at frame " << counter << endl;
            last_hist = hist;
            imshow("Detected Cut : frame " + to_string(counter), frame); //변화되는 위치에 대해 출력
        }
        counter++;
    }
    cout << "Read " << counter << "frame from video" << endl;

    vc.release(); //계산끝나면 메모리상에서 영상 날려줌.
    waitKey(0);
    return 0;
}