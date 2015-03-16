//
//  ABHashTableAlgorithm.cpp
//  workplace
//
//  Created by Andrii Bugaiov on 2015-03-16.
//  Copyright (c) 2015 Andrii Bugaiov. All rights reserved.
//

#include "ABHashTableAlgorithm.h"

#include "ABHashTable.h"

#include "ABNodeKeyValue.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

#pragma mark -

#define T_MIN (-10000)
#define T_MAX (10000)

// TODO:
int ABTwoSumComputingAlgorithm(const char *aFileName)
{
    ifstream filestream(aFileName);
    if(!filestream)
    {
        throw runtime_error("Failed to open file.");
    }
    
    int twoSums[T_MAX - T_MIN + 1] = {0};
    long long m = T_MAX - T_MIN + 1;
    
    ABHashTable<ABNodeKeyValue<long long>> ht(546527);
    long long value;
    while (filestream >> value)
    {
        int key = int(value / m);
        ABNodeKeyValue<long long> node(value, key);
        ht.insert(node);
    }
    filestream.close();
    //	ht.display();
    
    int j = 0;
    for (; j < ht.getTableSize(); ++j)
    {
        const ABList<ABNodeKeyValue<long long>> &list = ht[j];
        ABList<ABNodeKeyValue<long long>>::ABConstIterator listIterator = list.begin();
        for (; listIterator != list.end(); ++listIterator)
        {
            long long T = T_MIN - (*listIterator).getData();
            int keys[2];
            keys[0] = int(T / m);
            keys[1] = int(T / m) + 1;
            
            int i = 0;
            for (; i < sizeof(keys) / sizeof(keys[0]); ++i)
            {
                ABNodeKeyValue<long long> blank(0, keys[i]);
                int position = ht.hashPosition(blank);
                
                const ABList<ABNodeKeyValue<long long>> &otherList = ht[position];
                ABList<ABNodeKeyValue<long long>>::ABConstIterator otherListIterator = otherList.begin();
                for (; otherListIterator != otherList.end(); ++otherListIterator)
                {
                    long long twoSum = (*listIterator).getData() + (*otherListIterator).getData();
                    if (twoSum >= T_MIN && twoSum <= T_MAX)
                    {
                        twoSums[twoSum - T_MIN] = 1;
                    }
                }
            }
        }
    }
    
    int counter = 0;
    for (j = 0; j < T_MAX - T_MIN + 1; ++j)
    {
        counter += twoSums[j];
    }
    return counter;
}
