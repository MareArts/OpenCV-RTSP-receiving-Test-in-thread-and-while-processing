#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;

int main(int, char)
{

	string streamUri = "rtsp://192.168.0.21:554/onvif/profile2/media.smp";
	VideoCapture stream(streamUri);
	if (!stream.isOpened()){
		cout << "error" << endl;
		return 0;
	}

	Mat image;
	while (1){
		stream >> image;
		imshow("test", image);
		if (waitKey(30) >= 0)
			break;

	}

	return 0;
}