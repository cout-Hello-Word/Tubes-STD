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
#include <cstring>
#include <climits>

using namespace std;

typedef struct intersection *adrIntersection;
typedef struct road *adrRoad;

struct intersection {
    char intersectionID[50]; // Mengganti std::string dengan char[]
    adrIntersection nextIntersection;
    adrRoad firstRoad;
    bool isBlocked;
};

struct road {
    char destIntersectionID[50]; // Mengganti std::string dengan char[]
    int length;
    int safetyScore;
    adrRoad nextRoad;
};

struct transportNetwork {
    adrIntersection firstIntersection;
};

void createIntersection(const char *newIntersectionID, adrIntersection &I);
void initNetwork(transportNetwork &N);
void addIntersection(transportNetwork &N, const char *newIntersectionID);
void addRoad(transportNetwork &N, const char *fromIntersectionID, const char *toIntersectionID, int length, int safetyScore);
void printNetwork(transportNetwork &N);
void updateIntersectionStatus(transportNetwork &N);
void searchByShortestPath(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID);
void searchBySafestPath(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID);
void findEmergencyRoute(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID, const char *blockedIntersections);

#endif // TRANSPORT_H_INCLUDED
