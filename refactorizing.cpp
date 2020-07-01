//g++ refactorizing.cpp -o refactorizing `pkg-config --cflags --libs opencv`

#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

// System Headers
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <chrono>


#include <ctime>
#include <iostream>
#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#include <vector>
#include <string>
#include <glob.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// #include "contour.h"
//namespace
using namespace cv;
using namespace std;
using namespace chrono;



#define Mpixel(image,x,y) ((uchar *)((image).data +(y)*((image).step)))[(x)*((image).channels())]//gray color space
#define pixelB(image,x,y) image.data[image.step[0]*y+image.step[1]*x]	//Blue color space
#define pixelG(image,x,y) image.data[image.step[0]*y+image.step[1]*x+1]	//Green color space
#define pixelR(image,x,y) image.data[image.step[0]*y+image.step[1]*x+2]	//Red color space

int detemine_frame_size(Mat input, Point obj_center, int frame_size, int append_size ){
	bool is_tri=false;
	bool is_exceptional_case=false;
	// cout<<"input.size(): "<<input.size()<<endl;
	// cout<<"obj_center.x: "<<obj_center.x<<endl;
	// cout<<"obj_center.y: "<<obj_center.y<<endl;

 	if( (obj_center.x-frame_size < 0) || (obj_center.y-frame_size < 0 ) ){//the case1 of out of frame boundary
 		// cout<<"return case1"<<endl;
 		return -1;
	}

	if( (obj_center.x+frame_size > input.cols) || (obj_center.y+frame_size > input.rows) ){//the case2 of out of frame boundary
		// cout<<"return case2"<<endl;
 		return -2;
	}

	while(true){
		if( (obj_center.x-frame_size<=0)||(obj_center.y-frame_size<=0) ){//The frame size bigger than the left and top side margin so finish expanding more frame size
			// cout<<"return case3"<<endl;
			return frame_size*2;
		}

		if( (obj_center.x+frame_size >= input.cols)||(obj_center.y+frame_size >= input.rows) ){//The frame size bigger than the left and top side margin so finish expanding more frame size
			// cout<<"return case4"<<endl;
			return frame_size*2;
		}

		for(int k=obj_center.x-frame_size;k<obj_center.x+frame_size;k++){			
			for(int l=obj_center.y-frame_size;l<obj_center.y+frame_size;l++){

				// cout<<"k: "<<k<<endl;
				// cout<<"l: "<<l<<endl;
				// cout<<"obj_center.x: "<<obj_center.x<<endl;
				// cout<<"obj_center.y: "<<obj_center.y<<endl;
				if( (k==obj_center.x-frame_size)||(k==obj_center.x+frame_size-1)||(l==obj_center.y-frame_size)||(l==obj_center.y+frame_size-1) ){
					Point t_pp;
					t_pp.x=k;
					t_pp.y=l;
					// circle(temp_output,t_pp,3,Scalar(255,255,255));
					if((int)Mpixel(input,k,l)!=0 ){
						is_tri=true;
					}
				}


			}	
		}

		
		
		frame_size=frame_size+append_size;

		// cout<<"frame_size: "<<frame_size<<endl;
		if(is_tri==false){
			// cout<<"normal case: "<<endl;
			// cout<<"frame_size: "<<frame_size*2<<endl;
			break;
		}
		is_tri=false;

		if(frame_size>=250){//maximum size
			return frame_size*2;
			cout<<"error for size"<<endl;
		}
	}
	return frame_size*2;
}

int main(){
	Mat test_window=Mat::zeros(cv::Size(1440, 720),CV_8UC3);//default size initializing
	Point test_p;
	for(int i=0;i<test_window.cols;i++){
		for(int j=0;j<test_window.rows;j++){
			test_p.x=i;
			test_p.y=j;
			int final_size=detemine_frame_size(test_window,test_p,20,20);
		}
	}
	
	


}
