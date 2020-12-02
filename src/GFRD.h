#ifndef GFRD_H
#define GFRD_H

class GFRD
{
 public:
  GFRD(std::string fname);
  ~GFRD();
  void ReadInitialStructure(std::string fname);
  
 private:

  // variables related to GFRD features 
  int species;
  int *BeadsPerSpecies;
  double *Diffusivity;
  double *MinDomainSize;
  double *Cutoff;
  
  // variables related to simulation system
  int natoms; 
  int *tag;
  double **x;
  int *type;
  int *molecule;
  double *q;
  double xlo, ylo, zlo, xhi, yhi, zhi;
};

#endif
