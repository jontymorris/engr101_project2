#include "video_proc.hpp"

int main(){

    int nFrames = 20;
    for ( int iFrame = 0; iFrame < nFrames ; iFrame++){
		// produce file name of "X.ppm" type where X goes from 0 to number of images
		std::string fileName;
		std::ostringstream stringStream;
        stringStream <<iFrame<<".ppm";
        fileName = stringStream.str();
		std::cout<<" File::"<<fileName<<std::endl;
		// open image file
		OpenPPMFile(fileName);
			
        int totred = 0;
        int totint = 0;
        float redness = 0;
        for ( int row =0 ; row < image.height ; row++)  {	
		  for ( int column = 0; column < image.width ; column++) {
			  totred = totred + (int)get_pixel(row,column,0);
			  totint = totint + (int)get_pixel(row,column,3);
			  redness = (float)totred/(3.0*(float)totint);
		   }	  
	    }  
	   cout<<"Total red ="<<totred;
	   cout<<"Total int ="<< totint;
	   cout<<" Redness ="<<redness<<endl;
	}
	
	return 0; 
}
