#include "opencv2/opencv.hpp"
#include <string>
#include <list>
#include <thread>

using namespace std;
using namespace cv;



// RTSP receive buffer list
list< Mat> frames;
bool isRun;

// thread function for video show
void drawFrame(bool &isRun)
{
	while (isRun){
		if (frames.size()>1){
			Mat image = frames.front();
			imshow("test", image);
			waitKey(1);
			frames.pop_front();
		}
	}
}


int main(int, char)
{
	//rtsp address	
	string streamUri = "rtsp://192.168.0.21:554/onvif/profile2/media.smp";
	VideoCapture stream(streamUri);

	//open check
	if (!stream.isOpened()){
		cerr << "Stream open failed : " << streamUri << endl;
		return EXIT_FAILURE;
	}

	isRun = true;
	// thread run
	thread(drawFrame, isRun).detach();

	cv::Mat image;
	//Mat get only in the main function.
	while (isRun){

		stream >> image;
		frames.push_back(image.clone());
		printf("%d mat stacked \n", frames.size());
	}

	isRun = false;

	return 0;
}