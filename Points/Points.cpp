#include "Points.hpp"
#include "Centroid.hpp"

Points::Points()
    : coordonnees{}
    , clusterDistances{}
    , clusterIndex{invalidClusterIndex}
{
}

Points::Points(const std::vector<float> coordonne)
    : coordonnees{coordonne}
    , clusterDistances{}
    , clusterIndex{invalidClusterIndex}
{
}

float Points::distance(const Centroid& c)
{
    float dist{0};
    for( int i{0} ; i < c.getFeatures().size() or i < coordonnees.size() ; ++i )
    {
        dist+= (coordonnees.at(i) - c.getFeatures().at(i))*(coordonnees.at(i) - c.getFeatures().at(i));
    }
    clusterDistances.push_back(dist);
    return dist;
}

uint8_t Points::getNearClusterIndex()
{
    clusterIndex = std::distance(std::begin(clusterDistances), std::min_element(std::begin(clusterDistances), std::end(clusterDistances)));
    return clusterIndex;
}