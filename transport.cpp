#include "transport.h"

void createIntersection(const char *newIntersectionID, adrIntersection &I) {
    I = new intersection;
    strcpy(I->intersectionID, newIntersectionID); 
    I->nextIntersection = nullptr;
    I->firstRoad = nullptr;
    I->isBlocked = false;
}

void initNetwork(transportNetwork &N) {
    N.firstIntersection = nullptr;
}

void addIntersection(transportNetwork &N, const char *newIntersectionID) {
    adrIntersection I;
    createIntersection(newIntersectionID, I);
    if (firstIntersection(N) == nullptr) {
        firstIntersection(N) = I;
    } else {
        adrIntersection temp = firstIntersection(N);
        while (nextIntersection(temp) != nullptr) {
            temp = nextIntersection(temp);
        }
        nextIntersection(temp) = I;
    }
}

void addRoad(transportNetwork &N, const char *fromIntersectionID, const char *toIntersectionID, int length, int safetyScore) {
    adrIntersection from = firstIntersection(N);
    while (from != nullptr && strcmp(intersectionID(from), fromIntersectionID) != 0) {
        from = nextIntersection(from);
    }

    if (from != nullptr) {
        adrRoad newRoad = new road;
        strcpy(newRoad->destIntersectionID, toIntersectionID); 
        newRoad->length = length;
        newRoad->safetyScore = safetyScore;
        newRoad->nextRoad = firstRoad(from);
        firstRoad(from) = newRoad;
    }
}

void printNetwork(transportNetwork &N) {
    adrIntersection I = firstIntersection(N);
    while (I != nullptr) {
        cout << intersectionID(I) << " -> ";
        adrRoad R = firstRoad(I);
        if (R == nullptr) {
            cout << "Tidak ada jalan keluar" << endl;
        } else {
            while (R != nullptr) {
                cout << "(" << destIntersectionID(R) << ", "
                     << roadLength(R) << " km, Safety: " << roadSafetyScore(R) << ") ";
                R = nextRoad(R);
            }
        }
        cout << endl;
        I = nextIntersection(I);
    }
}

void updateIntersectionStatus(transportNetwork &N) {
    char blockedID[50];
    cout << "Masukkan Persimpangan yang Diblokir: ";
    cin.getline(blockedID, 50);

    adrIntersection I = firstIntersection(N);
    while (I != nullptr) {
        if (strcmp(intersectionID(I), blockedID) == 0) {
            I->isBlocked = true;
            cout << "Persimpangan " << blockedID << " telah diblokir." << endl;
            return;
        }
        I = nextIntersection(I);
    }
    cout << "Persimpangan tidak ditemukan." << endl;
}

void searchByShortestPath(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID) {
    adrIntersection start = firstIntersection(N);
    adrIntersection target = firstIntersection(N);

    // Cari simpang asal
    while (start != nullptr && strcmp(intersectionID(start), startIntersectionID) != 0) {
        start = nextIntersection(start);
    }

    // Cari simpang tujuan
    while (target != nullptr && strcmp(intersectionID(target), targetIntersectionID) != 0) {
        target = nextIntersection(target);
    }

    
    if (!start || !target) {
        cout << "Simpang asal atau tujuan tidak ditemukan!" << endl;
        return;
    }

    cout << "Mencari rute terpendek dari " << startIntersectionID << " ke " << targetIntersectionID << "..." << endl;

    
    char route[500] = "";
    int totalDistance = 0;

    
    adrIntersection current = start;
    while (current != nullptr && strcmp(intersectionID(current), targetIntersectionID) != 0) {
        adrRoad shortestRoad = nullptr;
        int minLength = INT_MAX;

        adrRoad R = firstRoad(current);
        while (R != nullptr) {
            if (roadLength(R) < minLength) {
                minLength = roadLength(R);
                shortestRoad = R;
            }
            R = nextRoad(R);
        }

        if (shortestRoad == nullptr) {
            cout << "Rute tidak ditemukan." << endl;
            return;
        }

        
        strcat(route, intersectionID(current));
        strcat(route, " -> ");
        totalDistance += minLength;

        
        current = firstIntersection(N);
        while (current != nullptr && strcmp(intersectionID(current), destIntersectionID(shortestRoad)) != 0) {
            current = nextIntersection(current);
        }
    }

   
    strcat(route, targetIntersectionID);

    
    cout << "Rute Terpendek:" << endl;
    cout << route << endl;
    cout << "Total Panjang: " << totalDistance << " km" << endl;
}

void searchBySafestPath(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID) {
    adrIntersection start = firstIntersection(N);
    adrIntersection target = firstIntersection(N);

    
    while (start != nullptr && strcmp(intersectionID(start), startIntersectionID) != 0) {
        start = nextIntersection(start);
    }

    
    while (target != nullptr && strcmp(intersectionID(target), targetIntersectionID) != 0) {
        target = nextIntersection(target);
    }

    
    if (!start || !target) {
        cout << "Simpang asal atau tujuan tidak ditemukan!" << endl;
        return;
    }

    cout << "Mencari rute teraman dari " << startIntersectionID << " ke " << targetIntersectionID << "..." << endl;

    
    char route[500] = "";
    int totalSafetyScore = 0;

    
    adrIntersection current = start;
    while (current != nullptr && strcmp(intersectionID(current), targetIntersectionID) != 0) {
        adrRoad safestRoad = nullptr;
        int maxSafetyScore = -1;

        adrRoad R = firstRoad(current);
        while (R != nullptr) {
            if (roadSafetyScore(R) > maxSafetyScore) {
                maxSafetyScore = roadSafetyScore(R);
                safestRoad = R;
            }
            R = nextRoad(R);
        }

        if (safestRoad == nullptr) {
            cout << "Rute tidak ditemukan." << endl;
            return;
        }

        strcat(route, intersectionID(current));
        strcat(route, " -> ");
        totalSafetyScore += maxSafetyScore;

        current = firstIntersection(N);
        while (current != nullptr && strcmp(intersectionID(current), destIntersectionID(safestRoad)) != 0) {
            current = nextIntersection(current);
        }
    }

    strcat(route, targetIntersectionID);

    cout << "Rute Teraman:" << endl;
    cout << route << endl;
    cout << "Total Skor Keamanan: " << totalSafetyScore << endl;
}

void searchByEmergencyRoute(transportNetwork &N, const char *startIntersectionID, const char *targetIntersectionID, const char *avoidIntersectionID) {
    adrIntersection start = firstIntersection(N);
    adrIntersection target = firstIntersection(N);
    adrIntersection avoid = firstIntersection(N);

    while (start != nullptr && strcmp(intersectionID(start), startIntersectionID) != 0) {
        start = nextIntersection(start);
    }

    while (target != nullptr && strcmp(intersectionID(target), targetIntersectionID) != 0) {
        target = nextIntersection(target);
    }

    while (avoid != nullptr && strcmp(intersectionID(avoid), avoidIntersectionID) != 0) {
        avoid = nextIntersection(avoid);
    }

    if (!start || !target) {
        cout << "Simpang asal atau tujuan tidak ditemukan!" << endl;
        return;
    }
    if (!avoid) {
        cout << "Simpang yang harus dihindari tidak ditemukan!" << endl;
        return;
    }

    cout << "Mencari rute darurat dari " << startIntersectionID << " ke " << targetIntersectionID << "..." << endl;

    char route[500] = "";
    int totalDistance = 0;

    adrIntersection current = start;
    while (current != nullptr && strcmp(intersectionID(current), targetIntersectionID) != 0) {
        adrRoad shortestRoad = nullptr;
        int minDistance = INT_MAX;

        adrRoad R = firstRoad(current);
        while (R != nullptr) {
            if (strcmp(destIntersectionID(R), intersectionID(avoid)) != 0 && roadLength(R) < minDistance) {
                minDistance = roadLength(R);
                shortestRoad = R;
            }
            R = nextRoad(R);
        }

        if (shortestRoad == nullptr) {
            cout << "Rute tidak ditemukan." << endl;
            return;
        }

        strcat(route, intersectionID(current));
        strcat(route, " -> ");
        totalDistance += minDistance;

        current = firstIntersection(N);
        while (current != nullptr && strcmp(intersectionID(current), destIntersectionID(shortestRoad)) != 0) {
            current = nextIntersection(current);
        }
    }

    strcat(route, targetIntersectionID);

    cout << "Rute Darurat:" << endl;
    cout << route << endl;
    cout << "Total Panjang: " << totalDistance << " km" << endl;
}

