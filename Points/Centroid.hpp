#pragma once

#include "Points.hpp"

class Centroid : public Points
{
public:
    Centroid(const std::vector<float> coordonne) 
        : Points{coordonne}
    {}

    Centroid(const Points pt) 
        : Points{pt}
    {}


    void reset() 
    { 
        numOfPoints = 0;  
        std::fill(coordonnees.begin(), coordonnees.end(), 0);
    };

    void prepareBarryCenter(const Points& point)
    {
        for(int x{0} ; x < point.getFeatures().size() ; ++x)
        {
            coordonnees.at(x)+= point.getFeatures().at(x);
        }
        ++numOfPoints;
    }

    void setNewCentroidCoordonnees()
    {
        std::for_each(coordonnees.begin(), coordonnees.end(), [this](auto& val){ val = val/numOfPoints; });
    }

private:
    uint32_t numOfPoints{0};

};