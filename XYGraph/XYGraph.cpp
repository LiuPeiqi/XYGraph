#include <algorithm>
#include <cassert>
#include "XYGraph.h"
using namespace LPQ;
using namespace std;
using namespace cv;

void XYGraph::Plot(const X_AXIS_TYPE & x, const Y_AXIS_TYPE & y)
{
	assert(size(x) == size(y));
	int font_face = FONT_HERSHEY_COMPLEX;
	double font_scale = 0.4;
	int thickness = 1;
	int base_line = 0;
	int offset = 4;
	int mark_line_length = 10;
	y_mark_max_size = Size(0, 0);
	for (const auto& y_item : y) {
		auto current_size = getTextSize(to_string(y_item), font_face, font_scale, thickness, &base_line);
		if (y_mark_max_size.height < current_size.height) {
			y_mark_max_size.height = current_size.height;
		}
		if (y_mark_max_size.width < current_size.width) {
			y_mark_max_size.width = current_size.width;
		}
	}
	for (const auto& x_item : x) {
		auto current_size = getTextSize(x_item, font_face, font_scale, thickness, &base_line);
		if (x_mark_max_size.height < current_size.height) {
			x_mark_max_size.height = current_size.height;
		}
		if (x_mark_max_size.width < current_size.width) {
			x_mark_max_size.width = current_size.width;
		}
	}
	auto x_axis = y_mark_max_size.width + offset;
	auto y_axix = x_mark_max_size.height + offset;
	left_top = Point(x_axis, offset);
	right_bottom = Point(width - offset, height - y_axix);
	auto zero = Point(left_top.x, right_bottom.y);
	graph = Mat(height, width, CV_8UC3, Scalar::all(255));
	rectangle(graph, left_top, right_bottom, Scalar::all(0));
	auto y_step = (zero.y - left_top.y) / (size(y)-1);
	Y_AXIS_TYPE y_copy(y);
	sort(begin(y_copy), end(y_copy));
	for (size_t i = 0; i < y_copy.size(); ++i) {
		auto text = to_string(y_copy[i]);
		auto yi_size = getTextSize(text, font_face, font_scale, thickness, &base_line);
		Point pos(zero.x - yi_size.width, zero.y - i*y_step);
		Point text_pos(pos.x, pos.y+yi_size.height/2);
		putText(graph, text, text_pos, font_face, font_scale, Scalar::all(0), thickness);
		line(graph, Point(zero.x, pos.y), Point(zero.x + mark_line_length, pos.y), Scalar::all(0), thickness);
	}
	auto x_step = (right_bottom.x - zero.x) / (size(x));
	for (size_t i = 0; i < x.size(); ++i) {
		auto text = x[i];
		auto xi_size = getTextSize(text, font_face, font_scale, thickness, &base_line);
		Point pos(zero.x + i*x_step, zero.y + xi_size.height);
		putText(graph, text, pos, font_face, font_scale, Scalar::all(0), thickness);
		line(graph, Point(pos.x, zero.y), Point(pos.x, zero.y - mark_line_length), Scalar::all(0), thickness);
	}
	double y_min, y_max;
	minMaxLoc(y, &y_min, &y_max);
	auto y_normal_factor = 1/(y_max - y_min);
	auto y_length = zero.y - left_top.y;
	auto x_length = right_bottom.x - zero.x;
	Point pre(zero);
	for (size_t i = 0; i < y.size(); ++i) {
		Point cur(zero.x + static_cast<int>(i*1.0/y.size() * x_length) ,
			zero.y-static_cast<int>((y[i] - y_min)*y_normal_factor * y_length));
		if (i > 0) {
			line(graph, pre, cur, Scalar(255, 0, 0), thickness + 2);
		}
		pre = cur;
	}
	if (y.size() <= 1) {
		line(graph, pre, pre, Scalar(255, 0, 0), thickness + 2);
	}
}

const cv::Mat & LPQ::XYGraph::GetGraph() const
{
	return graph;
}
