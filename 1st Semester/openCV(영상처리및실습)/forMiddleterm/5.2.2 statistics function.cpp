#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    Mat image = imread("../olaf.jpg", IMREAD_COLOR);
    CV_Assert(image.data);
    Mat mask(image.size(), CV_8U, Scalar(0)), mean1, stddev;
    mask(Rect(20, 40, 70, 70)).setTo(255);

    Scalar sum_value = sum(image);
    Scalar mean_value1 = mean(image);
    Scalar mean_value2 = mean(image, mask);
    cout << "[sum_value] = " << sum_value << endl;
    cout << "[mean_value1] = " << mean_value1 << endl;
    cout << "[mean_value2] = " << mean_value2 << endl << endl;

    meanStdDev(image, mean1, stddev);
    cout << "[mean]= " << mean << endl;
    cout << "[stddev]= " << stddev << endl << endl;

    meanStdDev(image, mean1, stddev, mask);
    cout << "[mean]= " << mean << endl;
    cout << "[stddev]= " << stddev << endl;

    imshow("image", image), imshow("mask", mask);

    //정렬
    Mat_<uchar> m1(3, 5);
    m1 << 11, 2, 3, 4, 10,
        6, 10, 15, 9, 7,
        7, 12, 8, 14, 1;
    Mat m_sort1, m_sort2, m_sort3, m_sort_idx1, m_sort_idx2;
    cv::sort(m1, m_sort1, SORT_EVERY_ROW);
    cv::sort(m1, m_sort2, SORT_EVERY_ROW + SORT_DESCENDING);
    cv::sort(m1, m_sort3, SORT_EVERY_COLUMN);

    cout << "m1 = " << endl << m1 << endl << endl;
    cout << "m_sort1 = " << endl << m_sort1  << endl;
    cout << "m_sort2 = " << endl << m_sort2  << endl;
    cout << "m_sort3 = " << endl << m_sort3 << endl;
    waitKey();
    return 0;
}