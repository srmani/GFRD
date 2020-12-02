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


GFRD::GFRD(std::string fname)
{

  std::string Temp;
  int block=1;

  std::ifstream configfile(fname.c_str());
  std::ofstream outputfile("echo.input");

  /*if(!configfile)
    throw error_fn("Input file missing in the location");*/
  
  while(block)   //!configfile.eof()- can replace with this
    {
      block=0;
      configfile>>Temp;
      if(Temp.compare("Species")==0)
	{
	  block=1;
	  configfile>>species;
	  BeadsPerSpecies=new int[species];
	  Diffusivity=new double[species];
	  MinDomainSize=new double[species];
	  Cutoff=new double [species];
	  outputfile<<"Species "<<species<<std::endl;
	}
      
      if(Temp.compare("BeadsPerSpecies")==0)
	{
	  block=1;
	  outputfile<<"BeadsPerSpecies ";
	  for (int i=0;i<species;i++){
	    configfile>>BeadsPerSpecies[i];
	    outputfile<<BeadsPerSpecies[i]<<' ';
	  }
	  outputfile<<std::endl;
	}
      
      if(Temp.compare("Diffusivity")==0)
	{
	  block=1;
	  outputfile<<"Diffusivity ";
	  for (int i=0;i<species;i++){
            configfile>>Diffusivity[i];
	    outputfile<<Diffusivity[i]<<' ';
	  }
	  outputfile<<std::endl;
	}

      if(Temp.compare("MinDomainSize")==0)
        {
          block=1;
	  outputfile<<"MinDomainSize ";
          for (int i=0;i<species;i++){
            configfile>>MinDomainSize[i];
	    outputfile<<MinDomainSize[i]<<' ';
	  }
	  outputfile<<std::endl;
	}

      if(Temp.compare("Cutoff")==0)
        {
          block=1;
	  outputfile<<"Cutoff ";
          for (int i=0;i<species;i++){
            configfile>>Cutoff[i];
	    outputfile<<Cutoff[i]<<' ';
	  }
	  outputfile<<std::endl;
        }

      if (Temp.compare("System")==0)
	{
	  block=1;
	  outputfile<<"System ";
	  std::string InitialSystem;
	  configfile>>InitialSystem;
	  ReadInitialStructure(InitialSystem);
	  outputfile<<InitialSystem<<' ';
	}

    }
  configfile.close();
  outputfile.close();
}


GFRD::~GFRD()
{
  delete BeadsPerSpecies;
  delete Diffusivity;
  delete MinDomainSize;
  delete Cutoff;
  delete tag;
  for (int i=0;i<natoms;i++)
    delete x[i];
  delete x;
  delete type;
  delete molecule;
  delete q;
}

void GFRD::ReadInitialStructure(std::string fname)
{
  std::string Temp;
  std::ifstream Initfile(fname.c_str());
  std::ofstream outputfile("echo.system");
  /*if(!Initfile)
    throw error_fn("Initial structure file missing in the location");*/

  Initfile>>natoms>>Temp;
  outputfile<<natoms<<' '<<Temp<<std::endl;

  tag=new int[natoms]{};
  x=new double *[natoms];
  for (int i=0;i<natoms;i++)
    x[i]=new double[3]{};
  type=new int[natoms]{};
  molecule=new int[natoms]{};
  q=new double[natoms]{};

  // assumed sequence of info (full style in lammps)
  // atomID, molID, typeID, charge, x, y, z

  for(int i=0;i<natoms;i++){
      Initfile>>tag[i]>>molecule[i]>>type[i]>>q[i]>>x[i][0]>>x[i][1]>>x[i][2];
      outputfile<<tag[i]<<' '<<molecule[i]<<' '<<type[i]<<' '<<q[i]<<' '<<x[i][0]<<' '<<x[i][1]<<' '<<x[i][2]<<std::endl;
  }
  Initfile.close();
  outputfile.close();
}
