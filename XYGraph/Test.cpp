#include <string>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "XYGraph.h"
using namespace std;
using namespace cv;

int main() 
{
	LPQ::XYGraph graph(640, 400);
	LPQ::XYGraph::X_AXIS_TYPE x{"10:01","10:02", "10:03", "10:04", "10:05" };
	LPQ::XYGraph::Y_AXIS_TYPE y{ 0.65,0.66,0.6123456,0.62,0.7456789 };
	//LPQ::XYGraph::Y_AXIS_TYPE y{ 1.1,-2,4,-5.5,3.3 };
	graph.Plot(x, y);
	namedWindow("img", CV_WINDOW_AUTOSIZE);
	imshow("img", graph.GetGraph());
	waitKey(0);
	return 0;
}
