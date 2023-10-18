#include <gtest/gtest.h>
#include <numeric>

#include "../Centroid.hpp"
#include "../Points.cpp"

namespace testing{

TEST(TestPoints, TestConstructor) 
{
    Points pt{};
    ASSERT_EQ(255, pt.getClusterIndex());
}

TEST(TestPoints, TestFeatures) 
{
    Points pt{};
    std::vector<float> f{{0.9864,0.65,0.6234, 0.72}};
    
    Centroid fCentro{f};
    pt.setCoordonnees(f);

    float distance{ pt.distance(fCentro) };
    float res = std::accumulate(f.cbegin(), f.cend(),0, [](auto ac, const auto current){ return ac+=current*current; });
    ASSERT_EQ(res, distance);
}

TEST(TestPoints, TestClosestCentroid) 
{
    Points pt1{};
    std::vector<float> f{{1, 4, 5, 2}};
    pt1.setCoordonnees(f);

    std::vector<float> fistCentroid{{10, 15, 12, 20}};
    Centroid fCentro{fistCentroid};
    
    std::vector<float> secondCentroid{{15, 20, 10, 25}};
    Centroid sCentro{secondCentroid};

    pt1.distance(fCentro);
    pt1.distance(sCentro);

    auto index = pt1.getNearClusterIndex();
    ASSERT_EQ(0, index);

    std::vector<float> closestCentroid{{4, 5, 6, 5}};
    Centroid closetCentro{closestCentroid};

    pt1.distance(closestCentroid);
    index = pt1.getNearClusterIndex();
    ASSERT_EQ(2, index);

}

TEST(TestPoints, TestCentroid) 
{
    Points pt1{};
    std::vector<float> f1{{1, 4, 5, 2}};
    pt1.setCoordonnees(f1);

    std::vector<float> f2{{10, 15, 12, 20}};
    Points pt2{f2};
    
    std::vector<float> c{{15, 20, 10, 25}};
    Centroid centroid{c};

    centroid.reset();
    for(auto val : centroid.getFeatures())
    {
        ASSERT_EQ(0, val);
    }

    centroid.prepareBarryCenter(pt1);
    centroid.prepareBarryCenter(pt2);

    centroid.setNewCentroidCoordonnees();

    for(int i{0} ; i < centroid.getFeatures().size() ; ++i)
    {
        ASSERT_EQ( (f1.at(i) + f2.at(i))/2 , centroid.getFeatures().at(i) );
    }
}

}