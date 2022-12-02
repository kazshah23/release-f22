/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    
    MosaicCanvas *output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    std::map<Point<3>, TileImage*> mp;
    std::vector<Point<3>> points;
    // add points to vector 
    // use convert xyz somehow 
    // map?
    // gets average color 
    for (size_t i = 0; i < theTiles.size(); i++) {
      // set pixel to the tiles at i average color  
      // add point to vector 
      LUVAPixel pixel = theTiles[i].getAverageColor();
      Point<3> pt = convertToXYZ(pixel);
      mp[pt] = &theTiles[i];
      points.push_back(pt);
    }
    KDTree<3> tree(points);

    // 2d iterator through source rows and cols 
    // map to the canvas/output 
    for (int row = 0; row < theSource.getRows(); row++) {
      for (int column = 0; column < theSource.getColumns(); column++) {
        Point<3> pt1 = convertToXYZ(theSource.getRegionColor(row,column));
        Point<3> best = tree.findNearestNeighbor(pt1);
        output -> setTile(row, column, mp[best]);
      }
    }

    return output;
}

