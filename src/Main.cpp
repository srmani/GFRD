#include<fstream>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<limits>
#include<math.h>
#include<streambuf>
#include <vector>
#include<limits>
#include<time.h>
#include<sstream>
#include "GFRD.h"


int main(int argc, char **argv)
{
  
  /*if(argc==1)
    throw error_fn("Tag for input parameter file not provided");
  */

  int iarg=1;
  std::string ConfigFile;
  while(iarg<argc)
    {
      if(strcmp(argv[iarg],"-in")==0 || strcmp(argv[iarg],"-input")==0){
	    /*if(argc-iarg!=2)
	      throw error_fn("Name of the input parameter file not provided");*/
	  iarg=iarg+1;
	  ConfigFile=argv[iarg];
	  std::cout<<ConfigFile<<std::endl;
	  iarg=iarg+1;
	}
    }

  GFRD gfrd(ConfigFile);

  return 1;
}
