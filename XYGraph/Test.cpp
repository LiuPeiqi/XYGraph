#include <string>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "XYGraph.h"
using namespace std;
using namespace cv;

int main() 
{
	LPQ::XYGraph graph(320, 240);
	LPQ::XYGraph::X_AXIS_TYPE x{"10:01","10:02", "10:03", "10:04", "10:05" };
	LPQ::XYGraph::Y_AXIS_TYPE y{ 3,1,4,2,5 };
	graph.Plot(x, y);
	namedWindow("img", CV_WINDOW_AUTOSIZE);
	imshow("img", graph.GetGraph());
	waitKey(0);
	return 0;
}
