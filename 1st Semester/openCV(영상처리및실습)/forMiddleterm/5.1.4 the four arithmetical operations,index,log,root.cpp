#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat m1(3, 6, CV_8UC1, Scalar(10)); //단일채널
	Mat m2(3, 6, CV_8UC1, Scalar(50));
	Mat add1, add2, div1, div2;
	Mat mask(m1.size(), CV_8UC1,Scalar(0));

	Rect rect(Point(3, 0), Size(3, 3)); //관심영역 지정
	mask(rect).setTo(1); //모든 원소 1지정

	add(m1, m2, add1);
	add(m1, m2, add2, mask);
	divide(m1, m2, div1);
	m1.convertTo(m1, CV_32F);
	m2.convertTo(m2, CV_32F);
	divide(m1, m2, div2);

	cout << "m1= " << endl<< m1 << endl;
	cout << "m2= " << endl << m2 << endl;
	cout << "mask= " << endl << mask << endl << endl;
	cout << "add1= " << endl << add1 << endl;
	cout << "add2= " << endl << add2 << endl;
	cout << "div1= " << endl <<div1 << endl;
	cout << "div2= " << endl << div2 << endl;


//지수로그루트
	vector<float> v1, v_exp, v_log;
	Matx<float, 1, 5> m3(1, 2, 3, 5, 10);
	Mat m_exp, m_sqrt,m_pow;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	exp(v1, v_exp); //벡터에 대한 지수계산
	exp(m3,m_exp); //행렬에 대한 지수계산
	log(m3, v_log); //로그 계산 벡터로 입력, 출력은 벡터
	sqrt(m3, m_sqrt); //제곱근 계산
	pow(m3, 3, m_pow); //3 거듭제곱 계산

	cout << "[m1]= " << m3 << endl << endl;
	cout << "[v_exp]= " <<((Mat) v_exp).reshape(1,1) << endl;
	cout << "[m_exp]= " << m_exp << endl;
	cout << "[v_log]= " << ((Mat)v_log).reshape(1, 1) << endl;

	cout << "[m_sqrt]= " << m_sqrt << endl;
	cout << "[m_pow]= " << m_pow << endl;

	return 0;
}