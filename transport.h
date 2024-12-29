#ifndef TRANSPORT_H_INCLUDED
#define TRANSPORT_H_INCLUDED
#define firstIntersection(G) ((G).firstIntersection)
#define nextIntersection(I) ((I)->nextIntersection)
#define firstRoad(I) ((I)->firstRoad)
#define intersectionID(I) ((I)->intersectionID)
#define destIntersectionID(R) ((R)->destIntersectionID)
#define roadLength(R) ((R)->length)
#define roadSafetyScore(R) ((R)->safetyScore)
#define nextRoad(R) ((R)->nextRoad)
#include <iostream>
#include <string>

using namespace std;

typedef struct intersection *adrIntersection;
typedef struct road *adrRoad;

struct intersection {
    string intersectionID;
    adrIntersection nextIntersection;
    adrRoad firstRoad;
    bool isBlocked;
};

struct road {
    string destIntersectionID;
    int length;
    int safetyScore;
    adrRoad nextRoad;
};

struct transportNetwork {
    adrIntersection firstIntersection;
};

void createIntersection(string newIntersectionID, adrIntersection &I);
void initNetwork(transportNetwork &N);
void addIntersection(transportNetwork &N, string newIntersectionID);
void addRoad(transportNetwork &N, string fromIntersectionID, string toIntersectionID, int length, int safetyScore);
void printNetwork(transportNetwork &N);
void updateIntersectionStatus(transportNetwork &N);
void searchByShortestPath(transportNetwork &N, string startIntersectionID, string targetIntersectionID);
void searchBySafestPath(transportNetwork &N, string startIntersectionID, string targetIntersectionID);
void findEmergencyRoute(transportNetwork &N, string startIntersectionID, string targetIntersectionID, string blockedIntersections);

#endif // TRANSPORT_H_INCLUDED
