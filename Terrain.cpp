/*
 *  Terrain.cpp
 *  fluricube
 *
 *  Created by Christopher Weber on 22.12.10.
 *  Copyright 2010 Bfh. All rights reserved.
 *
 */

using namespace std;
#include "Terrain.h"

Terrain::Terrain(int x,int z) {
	hs = new float *[z];
	for (int i=0; i<z; i++)
		hs[i] = new float[x];
}

float Terrain::getHeight(int x,int z) {
	return hs[z][x];
}

