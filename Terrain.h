/*
 *  Terrain.h
 *  fluricube
 *
 *  Created by Christopher Weber on 22.12.10.
 *  Copyright 2010 Bfh. All rights reserved.
 *
 */

class Terrain {
	private:
		float **hs;
	
	public:
		Terrain(int width,int heigt);
		float getHeight(int x,int y);
};

