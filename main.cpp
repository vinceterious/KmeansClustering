#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "Points/Centroid.hpp"
#include "Points/Points.hpp"

std::vector<std::string> split(std::string s, const char delim)
{
    std::vector<std::string> ret{};
    std::stringstream ss{s}; 
    std::string temp{};
    while (std::getline(ss, temp, delim))
    {
        ret.push_back(temp);
    }
    return ret;
}

std::vector<Points> loadData(std::ifstream& inFile)
{
    std::vector<Points> ret{};
    std::string line{};
    std::getline(inFile, line);
    std::string header = line;
    while(std::getline(inFile, line))
    {
        auto rawData = split(line, ',');
        std::vector<float> entry{std::stof(rawData.at(3)), std::stof(rawData.at(4)) };
        ret.emplace_back(Points(entry));
    }
    return ret;
}

void calculateDistanceToCentroid(std::vector<Points>& data, std::vector<Centroid>& centroids)
{
    for( auto& dt : data )
    {
        for( auto& centro : centroids )
        {
            dt.distance(centro);
        }
    }
}

void findNewCoordonateForCentroid(std::vector<Points>& data, std::vector<Centroid>& centroids)
{
    for( auto& centro : centroids )
    {
        centro.reset();
    }
    for( auto& dt : data )
    {
        auto clusterIdx = dt.getNearClusterIndex();
        centroids.at(clusterIdx).prepareBarryCenter(dt);
        dt.resetDistance();
    }
    for( auto& centro : centroids )
    {
        centro.setNewCentroidCoordonnees();
    }
}

void KmeansIteration(std::vector<Points>& data, std::vector<Centroid>& centroids)
{
    calculateDistanceToCentroid(data, centroids);
    findNewCoordonateForCentroid(data, centroids);
}

float KmeansAlgorithm(std::vector<Points>& data, std::vector<Centroid>& centroids)
{
    for( int i{0} ; i < 300 ; ++i )
    {
        KmeansIteration(data, centroids);
    }
    float inertia{0};
    for( auto& dt : data )
    {
        for( auto& centro : centroids )
        {
            dt.distance(centro);
        }
        auto clusterIdx = dt.getNearClusterIndex();
        inertia+=dt.distance(centroids.at(clusterIdx));
        dt.resetDistance();
    }
    return inertia;
}

Points pickRandomPoint(const std::vector<Points>& data)
{
    auto randomIndex = rand() % data.size();
    return data.at(randomIndex);
}

std::vector<Centroid> createCentroidRandomInit(int numOfCenter, const std::vector<Points>& data )
{
    std::vector<Centroid> ret{};
    ret.reserve(numOfCenter);
    for( int i{0} ; i < numOfCenter; ++i  )
    {
        ret.push_back(pickRandomPoint(data));
    }
    return ret;
}

void printDataWhithThereRespectiveCentroid(std::ofstream& outFile, std::vector<Points>& data, std::vector<Centroid>& centroids)
{
    for( auto& dt : data )
    {
        for( auto& centro : centroids )
        {
            dt.distance(centro);
        }
        uint8_t idx = dt.getNearClusterIndex();
        outFile << "x/y," << dt.getFeatures().at(0) << "," << dt.getFeatures().at(1) << "," << (int)idx <<"\n";
    }
}

void printCentroid(std::ofstream& outFile, std::vector<Centroid>& centroids)
{
    for( auto& centro : centroids )
    {
        outFile << "centro: x/y," << centro.getFeatures().at(0) << "," << centro.getFeatures().at(1) << "\n";
    }
}

int main()
{
    std::ifstream inFile{"Mall_Customers.csv"};
    std::ofstream outFilePoint{"point"};
    std::ofstream outFileCentroid{"centroid"};
    std::ofstream outFileElbow{"elbow"};
    std::vector<Points> data{ loadData(inFile) };

    //Elbow dtermination
    for( int i{1} ; i < 20 ; ++i )
    {
        std::vector<Centroid> centro{createCentroidRandomInit(i,data)};
        auto inertia = KmeansAlgorithm(data, centro);
        outFileElbow << i << "," << inertia << "\n";
    }

    //Example with 5 cluster
    std::vector<Centroid> centroids{data.at(3), data.at(64), data.at(101), data.at(104), data.at(149)};
    KmeansAlgorithm(data, centroids);

    //Print data and centroid result
    printDataWhithThereRespectiveCentroid(outFilePoint, data, centroids);
    printCentroid(outFileCentroid,centroids);

    outFileCentroid.flush();
    outFilePoint.flush();
    outFileElbow.flush();
    return 0;
}