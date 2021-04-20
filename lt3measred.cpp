/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <iostream>
#include "E101.h"

using namespace std;

int main()
{
  int err = init(0);
  cout<<" Hello. err="<<err<<endl;
  int totred = 0; // combined value of all red values of all pixels
  int totint = 0; // ditto for grey
  float redness = 0; // ratio of redness to greyness
  open_screen_stream();
  
  
  // make 1000 runs  
  for(int countrun =0; countrun <1000; countrun=countrun+1)
  {
	take_picture();
	update_screen();	
    totred = 0;
    totint = 0;
    redness = 0; 
    // for all pixels in latest image
    for ( int row = 0 ; row <240 ; row=row+1)
	{	
		for (int col=0; col<320; col=col+1)
		{
			totred = totred + (int)get_pixel(row,col,0);
			totint = totint + (int)get_pixel(row,col,3);
		}	  
	}  
	redness = (float)totred/(3.0*(float)totint);
	cout<<" countrun="<<countrun;
	cout<<" Total red "<< totred;
	cout<<" Total int "<< totint;
	cout<<" Redness "<< redness<<endl;
	sleep1(100); // slow down a bit to make display easier
  }  
  close_screen_stream();
  return 0;
}
