#ifndef DensityProfile2D_H
#define DensityProfile2D_H


#include "DensityProfile.h"

//  --------------------------------------------------------------------------------------------------------------------
//! lkjskljaslkdjaskl
//  --------------------------------------------------------------------------------------------------------------------
class DensityProfile2D : public DensityProfile
{
    
public:
    DensityProfile2D(){};
    ~DensityProfile2D() {};
    double operator() (PicParams*, unsigned int, std::vector<double>);
    
    
private:
    
    
};//END class

#endif
