#include "opencv2/opencv.hpp"
#include <string>
#include <list>
#include <thread>

using namespace std;
using namespace cv;



// RTSP receive buffer list
list< Mat> frames;
cv::VideoCapture stream2;
bool isRun;

// thread function for video getting and show
void StreamThread(bool &isRun)
{
	cv::Mat image;
	while (isRun){
		stream2 >> image;
		frames.push_back(image.clone());
		printf("%d mat stacked \n", frames.size());
	}
}


int main(int, char)
{
	//rtsp address	
	string streamUri = "rtsp://192.168.0.21:554/onvif/profile2/media.smp";
	stream2.open(streamUri);

	//open check
	if (!stream2.isOpened()){
		cerr << "Stream open failed : " << streamUri << endl;
		return EXIT_FAILURE;
	}

	isRun = true;
	// thread run
	thread(StreamThread, isRun).detach();


	//Mat draw only in the main function.
	while (isRun){

		if (frames.size()>1){

			Mat image = frames.front();
			imshow("test", image);
			frames.pop_front();

			if (waitKey(30) >= 0)
				break;
		}
	}

	isRun = false;

	return 0;
}