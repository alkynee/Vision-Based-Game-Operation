/*
 * MIT License
 * Copyright (c) 2020 Pablo Peñarroja
 */

/*
 * the following constants should be
 * altered in order to fit the user's
 * needs.
 * they're set to standard values
 * by default, and changing them may
 * dramatically alter the library's
 * behaviour
 */

 //                                   //
 //-------- c o n s t a n t s --------//
 //                                   //

/*
 * this indicates whether to render
 * the processed image to a matrix
 * 'frame'.
 * this matrix can be retrieved using
 * the 'getFrame()' method declared
 * bellow
 */
const bool RENDER_TO_FRAME = true;

/*
 * this indicates whether to create a
 * separate window and render the
 * current frame to that window.
 * it requires the 'RENDER_TO_FRAME'
 * constant to be true
 */
const bool RENDER_TO_WINDOW = true;

/*
 * this indicates whether to render
 * a small text explaining to the user
 * what to do
 */
const bool RENDER_SAMPLE_TEXT = true;

/*
 * width and height of the skin color
 * sampling rectangle
 */
const int SAMPLE_AREA_WIDTH = 30;
const int SAMPLE_AREA_HEIGHT = 30;

/*
 * this is the tolerance applied to
 * the lower and higher bounds of the
 * HSV skin tone color sampled from
 * the user.
 * low values limit the range, thus
 *
 */
const int MASK_LOW_TOLERANCE = 50;
const int MASK_HIGH_TOLERANCE = 25;

/*
 * width and height of the reticle:
 * the area centered at the middle of
 * the screen where the program will
 * look for the user's skin.
 * in case of finding it, the object
 * union find algorithm will start.
 */
const int RETICLE_SIZE = 40;

/*
 * if an object is detected, but the
 * aim point is located within this
 * area, the aim point will be instantly
 * set to zero.
 * the reason for this being that it's
 * very hard to distinguish the accurate
 * location of the aim point when the
 * user is pointing straight at the
 * camera
 */
const int NO_AIM_AREA_SIZE = 80;

/*
 * the bfs sample size represents the
 * square root of the area to scan for
 * each node of the bfs algorithm.
 * the lower this value, the more
 * accurate but the more noise, and the
 * more cpu usage required as well
 */
const int BFS_SAMPLE_SIZE = 2;

/*
 * smoothness is used to get rid of some
 * of the noise in the calculations.
 * the higher this number, the more
 * smoothness, less noise, but less
 * responsiveness as well
 */
const int AIM_SMOOTHNESS = 4;

/*
 * this is the minumum distance that
 * the aim point should travel upwards
 * in order to be considered a trigger
 * action.
 * it's represented as a percentage
 * of the screen real estate
 */
const double TRIGGER_MINIMUM_DISTANCE = 3.0;

/*
 * this is the maximum distance that
 * the aim point is allowed to  travel 
 * upwards in order to be considered a
 * trigger action.
 * it's represented as a percentage
 * of the screen real estate
 */
const double TRIGGER_MAXIMUM_DISTANCE = 15.0;

/*
 * consider y1 as the origin y value
 * for a trigger action, and y2 as the
 * final y value, then:
 * this value represents the absolute
 * maximum allowed deviation from y1
 * to y2 in order for the action to
 * be valid.
 * it's represented as a percentage of
 * the screen real estate
 */
const double TRIGGER_ALLOWED_Y_DEVIATION = 3.0;

/*
 * same as 'TRIGGER_ALLOWED_Y_DEVIATION'
 * but for the x-axis
 */
const double TRIGGER_ALLOWED_X_DEVIATION = 2.0;

//                                 //
//--------  v  a  a  a  c  --------//
//                                 //

#pragma once

#include <vector>
#include <utility>
#include <queue>
#include <deque>

#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

class vaaac {

	private:

		// is everything working
		int ok;

		// player detected
		bool detected;

		// resolution (square)
		int width;
		int height;
		int res;
		int halfRes;

		// computer vision vars
		cv::VideoCapture videoCapture;
		cv::Rect frameBounds;
		cv::Rect reticleBounds;
		cv::Rect noAimAreaBounds;
		cv::Mat frame;
		cv::Mat mask;

		// skin tone hsv color bounds
		int hLow;
		int hHigh;
		int sLow;
		int sHigh;
		int vLow;
		int vHigh;

		// breadth first search system
		std::vector<std::pair<int, int>> bfsOffsets;

		// aimed at point location
		double xAngle;
		double yAngle;

		// stepped point location
		double xAngleSmooth;
		double yAngleSmooth;

		// trigger system
		bool triggered;
		bool increment;
		int yxDeltaSize;
		int TRIGGER_MINIMUM_DISTANCE_PIXELS;
		int TRIGGER_MAXIMUM_DISTANCE_PIXELS;
		int TRIGGER_ALLOWED_Y_DEVIATION_PIXELS;
		int TRIGGER_ALLOWED_X_DEVIATION_PIXELS;
		std::vector<std::pair<int, int>> yxDelta;

	public:

		inline bool isOk() {
			return ok == 2;
		}

		inline bool isDetected() {
			return detected;
		}

		inline bool isTriggered() {
			return triggered;
		}

		inline double getXAngle() {
			return xAngleSmooth;
		}

		inline double getYAngle() {
			return yAngleSmooth;
		}

		inline cv::Mat getFrame() {
			return frame;
		}

		vaaac() {
			// webcam initialization
			videoCapture = cv::VideoCapture(0);
			videoCapture.set(cv::CAP_PROP_SETTINGS, 1);
			// check if it's alright
			ok = videoCapture.isOpened();
			if (!ok) {
				ok = false;
				return;
			}
			// resolution (1:1 aspect ratio)
			width = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
			height = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
			res = std::min(width, height);
			halfRes = res / 2;
			// make the viewport a centered square
			int addX = 0, addY = 0;
			if (width > height) {
				addX = (width - height) / 2;
			}
			else if (height > width) {
				addY = (height - width) / 2;
			}
			// limit camera resolution ratio to 1:1
			frameBounds = cv::Rect(addX, addY, res, res);
			// determine reticle view area
			int reticlePos = halfRes - RETICLE_SIZE / 2;
			reticleBounds = cv::Rect(reticlePos, reticlePos, RETICLE_SIZE, RETICLE_SIZE);
			// determine no aim zone
			int noAimAreaPos = halfRes - NO_AIM_AREA_SIZE / 2;
			noAimAreaBounds = cv::Rect(noAimAreaPos, noAimAreaPos, NO_AIM_AREA_SIZE, NO_AIM_AREA_SIZE);
			// fill up bfs offsets array
			bfsOffsets.clear();
			for (int i = -1; i < 2; ++i) {
				for (int j = -1; j < 2; ++j) {
					bfsOffsets.push_back(std::make_pair<int, int>(i * BFS_SAMPLE_SIZE, j * BFS_SAMPLE_SIZE));
				}
			}
			// precompute trigger system constants
			TRIGGER_MINIMUM_DISTANCE_PIXELS = TRIGGER_MINIMUM_DISTANCE * res / 100.0;
			TRIGGER_MAXIMUM_DISTANCE_PIXELS = TRIGGER_MAXIMUM_DISTANCE * res / 100.0;
			TRIGGER_ALLOWED_Y_DEVIATION_PIXELS = TRIGGER_ALLOWED_Y_DEVIATION * res / 100.0;
			TRIGGER_ALLOWED_X_DEVIATION_PIXELS = TRIGGER_ALLOWED_X_DEVIATION * res / 100.0;
			// clear y variance deque
			increment = true;
			yxDeltaSize = 0;
			yxDelta.clear();
		}

		~vaaac() {}

		void calibrateSkinTone() {
			if (ok & 1) {
				int xCoord = res / 2 - SAMPLE_AREA_WIDTH / 2;
				int yCoord = res / 2 - SAMPLE_AREA_HEIGHT / 2;
				int rectSizeX = std::min(SAMPLE_AREA_WIDTH, halfRes);
				int rectSizeY = std::min(SAMPLE_AREA_HEIGHT, halfRes);
				cv::Rect area(xCoord, yCoord, rectSizeX, rectSizeY);
				for (;;) {
					videoCapture >> frame;
					frame = frame(frameBounds);
					if (RENDER_SAMPLE_TEXT) {
						cv::putText(
								frame,
								"fill the area with your skin.",
								cv::Point(10, area.y - 60),
								cv::FONT_HERSHEY_DUPLEX,
								1.0,
								cv::Scalar(255, 255, 255),
								1);
						cv::putText(
								frame,
								"then press any key.",
								cv::Point(10, area.y - 20),
								cv::FONT_HERSHEY_DUPLEX,
								1.0,
								cv::Scalar(255, 255, 255),
								1);
					}
					/*
					 * check if user is done before
					 * drawing rectangle because,
					 * otherwise, the rectangle gets
					 * computed as the skin tone mean
					 */
					int key = cv::waitKey(1);
					if (key != -1) {
						break;
					}
					// now draw rectangle and draw
					if (RENDER_TO_WINDOW) {
						cv::rectangle(frame, area, cv::Scalar(255, 255, 255), 2);
						cv::imshow("calibrateSkinTone", frame);
					}
				}
				if (RENDER_TO_WINDOW) {
					cv::destroyWindow("calibrateSkinTone");
				}
				cv::Mat hsv;
				cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
				cv::Mat sample(hsv, area);
				cv::Scalar mean = cv::mean(sample);
				hLow = mean[0] - MASK_LOW_TOLERANCE;
				hHigh = mean[0] + MASK_HIGH_TOLERANCE;
				sLow = mean[1] - MASK_LOW_TOLERANCE;
				sHigh = mean[1] + MASK_HIGH_TOLERANCE;
				vLow = 0;
				vHigh = 255;
				ok = 2;
			}
		}

		void update() {

			//                                    //
			//-- i m a g e  p r o c e s s i n g --//
			//                                    //

			// always false before processing
			detected = false;
			triggered = false;
			// get current frame
			videoCapture >> frame;
			// reshape
			frame = frame(frameBounds);
			// to hsv
			cv::cvtColor(frame, mask, cv::COLOR_BGR2HSV);
			// binarization
			cv::inRange(mask, cv::Scalar(hLow, sLow, vLow), cv::Scalar(