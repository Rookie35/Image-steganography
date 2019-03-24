#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include<bitset>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat rgb;
	rgb = imread("watermark.bmp");
	if (rgb.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	Mat mv[3];
	split(rgb, mv);
	Mat oi1 = mv[0];//B
	Mat oi2 = mv[1];//G
	Mat oi3 = mv[2];//R
	int orows = rgb.rows;
	int ocols = rgb.cols;
	int pixelcount = orows*ocols;
	Mat water(orows, ocols, CV_8UC1, Scalar(0));
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//ͼ���һҳ��R��
	cout << "R��" << endl;
	//cout << "rows:" << orows << endl;
	//cout << "cols:" << ocols << endl;
	//cout << "pixelcount:" << pixelcount << endl;

	for (int n = 0; n < pixelcount/64; n++){
		Mat b1(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				b1.at<uchar>(i, j) = oi1.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols);
			}
		}
		//cout << b1<<endl;//����
		int h1 = b1.rows;
		int w1 = b1.cols;

		//�����븴ԭ�Ĺ�ͬ����
		int u = 10, a = 3, c = 5, N;
		N = h1;
		//����
		Mat imgn1(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < u; i++){
			for (int y = 0; y < h1; y++){
				for (int x = 0; x < w1; x++){
					int xx = ((x + c*y) % N);
					int yy = ((a*x + (a*c + 1)*y) % N);
					imgn1.at<uchar>(yy, xx) = b1.at<uchar>(y, x);
				}
			}
		}
		//cout << imgn1 << endl;//����
		imgn1.copyTo(b1);
		//cout << b1 << endl;
		//��b���������ص�ĸ���λ�浽l
		Mat l1(8, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				for (int k = 0; k < 7; k++){
					bitset<8> a(b1.at<uchar>(i, j));
					l1.at<uchar>(i, 7 * j + k) = a[k + 1];
				}
			}
		}
		//cout << l1 << endl;//����
		//ˮӡ����
		Mat sum1(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 56; j++){
				sum1.at<uchar>(0, j) ^= l1.at<uchar>(i, j);
			}
		}
		//cout << "sum1"<<endl<<sum1<<endl;//����

		Mat watermark(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 7; i++){
			for (int j = 0; j < 8; j++){
				bitset<8> a(oi1.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols));
				watermark.at<uchar>(0, i * 8 + j) = a[0];
			}
		}
	
	//cout <<" watermark"<<endl<<watermark<<endl;//����

		
		for (int k = 0; k < 56; k++){
			if (sum1.at<uchar>(0, k) != watermark.at<uchar>(0, k)){
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						water.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols) = 255;
					}
				}
			}
			
		
		}
	}
	
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//ͼ��ڶ�ҳ��G��
	cout << "G��" << endl;
	//cout << "rows:" << orows << endl;
	//cout << "cols:" << ocols << endl;
	//cout << "pixelcount:" << pixelcount << endl;

	for (int n = 0; n < pixelcount / 64; n++){
		Mat b2(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				b2.at<uchar>(i, j) = oi2.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols);
			}
		}

		int h2 = b2.rows;
		int w2 = b2.cols;

		//�����븴ԭ�Ĺ�ͬ����
		int u = 10, a = 3, c = 5, N;
		N = h2;
		//����
		Mat imgn2(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < u; i++){
			for (int y = 0; y < h2; y++){
				for (int x = 0; x < w2; x++){
					int xx = ((x + c*y) % N);
					int yy = ((a*x + (a*c + 1)*y) % N);
					imgn2.at<uchar>(yy, xx) = b2.at<uchar>(y, x);
				}
			}
		}
		imgn2.copyTo(b2);
		//��b���������ص�ĸ���λ�浽l
		Mat l2(8, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				for (int k = 0; k < 7; k++){
					bitset<8> a(b2.at<uchar>(i, j));
					l2.at<uchar>(i, 7 * j + k) = a[k + 1];
				}
			}
		}
		//ˮӡ����
		Mat sum2(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 56; j++){
				sum2.at<uchar>(0, j) ^= l2.at<uchar>(i, j);
			}
		}

		Mat watermark(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 7; i++){
			for (int j = 0; j < 8; j++){
				bitset<8> a(oi2.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols));
				watermark.at<uchar>(0, i * 8 + j) = a[0];
			}
		}


		for (int k = 0; k < 56; k++){
			if (sum2.at<uchar>(0, k) != watermark.at<uchar>(0, k)){
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						water.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols) = 255;
					}
				}
			}
		}
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//ͼ�����ҳ��B��
	cout << "B��" << endl;
	//cout << "rows:" << orows << endl;
	//cout << "cols:" << ocols << endl;
	//cout << "pixelcount:" << pixelcount << endl;

	for (int n = 0; n < pixelcount / 64; n++){
		Mat b3(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				b3.at<uchar>(i, j) = oi3.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols);
			}
		}

		int h3 = b3.rows;
		int w3 = b3.cols;

		//�����븴ԭ�Ĺ�ͬ����
		int u = 10, a = 3, c = 5, N;
		N = h3;
		//����
		Mat imgn3(8, 8, CV_8UC1, Scalar(0));
		for (int i = 0; i < u; i++){
			for (int y = 0; y < h3; y++){
				for (int x = 0; x < w3; x++){
					int xx = ((x + c*y) % N);
					int yy = ((a*x + (a*c + 1)*y) % N);
					imgn3.at<uchar>(yy, xx) = b3.at<uchar>(y, x);
				}
			}
		}
		imgn3.copyTo(b3);
		//��b���������ص�ĸ���λ�浽l
		Mat l3(8, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				for (int k = 0; k < 7; k++){
					bitset<8> a(b3.at<uchar>(i, j));
					l3.at<uchar>(i, 7 * j + k) = a[k + 1];
				}
			}
		}
		//ˮӡ����
		Mat sum3(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 56; j++){
				sum3.at<uchar>(0, j) ^= l3.at<uchar>(i, j);
			}
		}

		Mat watermark(1, 56, CV_8UC1, Scalar(0));
		for (int i = 0; i < 7; i++){
			for (int j = 0; j < 8; j++){
				bitset<8> a(oi3.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols));
				watermark.at<uchar>(0, i * 8 + j) = a[0];
			}
		}


		for (int k = 0; k < 56; k++){
			if (sum3.at<uchar>(0, k) != watermark.at<uchar>(0, k)){
				for (int i = 0; i < 8; i++){
					for (int j = 0; j < 8; j++){
						water.at<uchar>(floor((8 * n + j) / ocols) * 8 + i, (8 * n + j) % ocols) = 255;
					}
				}
			}
	
		}
	}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	imwrite("dingwei.bmp", water);
	imshow("Ƕ��ˮӡ�Ĵ۸�ͼ��", rgb);
	imshow("�۸Ķ�λ",water);

	waitKey(0);
	return 0;
}