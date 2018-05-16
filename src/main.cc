/*
 * =====================================================================================
 *
 *       Filename:  main.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/14/2018 12:09:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
  auto img = imread("test.jpg");
  namedWindow("window");
  imshow("window", img);
  waitKey();
  return EXIT_SUCCESS;
}  /* ----------  end of function main  ---------- */
