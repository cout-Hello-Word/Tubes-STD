#include "transport.h"

void createIntersection(string newIntersectionID, adrIntersection &I) {
    I = new intersection;
    I->intersectionID = newIntersectionID;
    I->nextIntersection = nullptr;
    I->firstRoad = nullptr;
    I->isBlocked = false;
}

void initNetwork(transportNetwork &N) {
    N.firstIntersection = nullptr;
}

void addIntersection(transportNetwork &N, string newIntersectionID) {
    adrIntersection I;
    createIntersection(newIntersectionID, I);
    if (N.firstIntersection == nullptr) {
        N.firstIntersection = I;
    } else {
        adrIntersection temp = N.firstIntersection;
        while (temp->nextIntersection != nullptr) {
            temp = temp->nextIntersection;
        }
        temp->nextIntersection = I;
    }
}

void addRoad(transportNetwork &N, string fromIntersectionID, string toIntersectionID, int length, int safetyScore) {
    adrIntersection from = N.firstIntersection;
    while (from != nullptr && from->intersectionID != fromIntersectionID) {
        from = from->nextIntersection;
    }

    if (from != nullptr) {
        adrRoad newRoad = new road;
        newRoad->destIntersectionID = toIntersectionID;
        newRoad->length = length;
        newRoad->safetyScore = safetyScore;
        newRoad->nextRoad = from->firstRoad;
        from->firstRoad = newRoad;
    }
}

void printNetwork(transportNetwork &N) {
    adrIntersection I = N.firstIntersection;
    while (I != nullptr) {
        cout << I->intersectionID << " -> ";
        adrRoad R = I->firstRoad;
        while (R != nullptr) {
            cout << "(" << R->destIntersectionID << ", " << R->length << " km, Safety: " << R->safetyScore << ") ";
            R = R->nextRoad;
        }
        cout << endl;
        I = I->nextIntersection;
    }
}

void updateIntersectionStatus(transportNetwork &N) {
    string blockedID;
    cout << "Masukkan Persimpangan yang Diblokir: ";
    getline(cin, blockedID);

    adrIntersection I = N.firstIntersection;
    while (I != nullptr) {
        if (I->intersectionID == blockedID) {
            I->isBlocked = true;
            cout << "Persimpangan " << blockedID << " telah diblokir." << endl;
            return;
        }
        I = I->nextIntersection;
    }
    cout << "Persimpangan tidak ditemukan." << endl;
}

void searchByShortestPath(transportNetwork &N, string startIntersectionID, string targetIntersectionID) {
    cout << "Mencari rute terpendek dari " << startIntersectionID << " ke " << targetIntersectionID << endl;
}

void searchBySafestPath(transportNetwork &N, string startIntersectionID, string targetIntersectionID) {
    cout << "Mencari rute teraman dari " << startIntersectionID << " ke " << targetIntersectionID << endl;
}

void findEmergencyRoute(transportNetwork &N, string startIntersectionID, string targetIntersectionID, string blockedIntersections) {
    cout << "Mencari rute darurat dari " << startIntersectionID << " ke " << targetIntersectionID
         << ", menghindari persimpangan " << blockedIntersections << endl;
}
