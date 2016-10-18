#ifndef XY_GRAPH_H
#define XY_GRAPH_H
#include <string>
#include <vector>

#include <opencv2/core.hpp>
namespace LPQ {
	class XYGraph {
	public:
		XYGraph(int w, int h) :width(w), height(h) {}
		XYGraph(const XYGraph&) = delete;
		XYGraph operator = (const XYGraph&) = delete;
		using X_AXIS_TYPE = std::vector<std::string>;
		using Y_AXIS_TYPE = std::vector<double>;
		void Plot(const X_AXIS_TYPE& x, const Y_AXIS_TYPE& y);
		const cv::Mat& GetGraph()const;
	private:
		int width, height;
		X_AXIS_TYPE xs;
		Y_AXIS_TYPE ys;
		cv::Size y_mark_max_size;
		cv::Size x_mark_max_size;
		cv::Point left_top, right_bottom;
		cv::Mat graph;
	};
}
#endif // !XY_GRAPH_H
