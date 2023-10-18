#pragma once

#include <vector>
#include <limits>
#include <cstdint>

class Centroid;

class Points
{
public:
    static const uint8_t invalidClusterIndex = std::numeric_limits<uint8_t>::max();

    Points();
    Points(const std::vector<float> coordonne);
    const uint8_t getClusterIndex() const { return clusterIndex; };
    const std::vector<float> getFeatures() const { return coordonnees; };
    float distance(const Centroid& p);
    void resetDistance(){ clusterDistances.clear();};
    uint8_t getNearClusterIndex();

    void setCoordonnees(const std::vector<float>& feats)
    {
        std::copy(feats.begin(), feats.end(), std::back_inserter(coordonnees));
    }

protected:
    std::vector<float> coordonnees;
private:
    std::vector<float> clusterDistances;
    uint8_t clusterIndex;
};