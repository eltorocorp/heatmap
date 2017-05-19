#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

///////////////////////////////////////////////////////////////////////////////////
// Converts a list of space delimited lat-long pairs to pixel point coordinates  //
//							                         //
//     *Created to create an output file usable by the heatmap_gen program*      //
//										 //
// Saves output to points.txt							 //
//										 //
// The first two arguments should be the height and width of the expected output //
///////////////////////////////////////////////////////////////////////////////////


using namespace std;



/*BEGIN OSM COVERSION CODE

//
// Mercator transformation
// accounts for the fact that the earth is not a sphere, but a spheroid
//
#define D_R (M_PI / 180.0)
#define R_D (180.0 / M_PI)
#define R_MAJOR 6378137.0
#define R_MINOR 6356752.3142
#define RATIO (R_MINOR/R_MAJOR)
#define ECCENT (sqrt(1.0 - (RATIO * RATIO)))
#define COM (0.5 * ECCENT)

static double deg_rad (double ang) {
        return ang * D_R;
}

double merc_x (double lon) {
        return R_MAJOR * deg_rad (lon);
}

double merc_y (double lat) {
        lat = fmin (89.5, fmax (lat, -89.5));
        double phi = deg_rad(lat);
        double sinphi = sin(phi);
        double con = ECCENT * sinphi;
        con = pow((1.0 - con) / (1.0 + con), COM);
        double ts = tan(0.5 * (M_PI * 0.5 - phi)) / con;
        return 0 - R_MAJOR * log(ts);
}

static double rad_deg (double ang) {
        return ang * R_D;
}

double merc_lon (double x) {
        return rad_deg(x) / R_MAJOR;
}

double merc_lat (double y) {
        double ts = exp ( -y / R_MAJOR);
        double phi = M_PI_2 - 2 * atan(ts);
        double dphi = 1.0;
        int i;
        for (i = 0; fabs(dphi) > 0.000000001 && i < 15; i++) {
                double con = ECCENT * sin (phi);
                dphi = M_PI_2 - 2 * atan (ts * pow((1.0 - con) / (1.0 + con), COM)) - phi;
                phi += dphi;
        }
        return rad_deg (phi);
}

//END OSM CONVERSION CODE*/

int main(int argc, char** argv) //If not given a list, will look for data.txt in the same directory
{
   vector<double> latList;
   vector<double> longList;
   int height = 0, width = 0;
   float latLowBound = 0.0, latHighBound = 0.0, longLowBound = 0.0, longHighBound = 0.0;


   if(argc > 2)
   {
      if(!(width = stoi(argv[1])) || !(height = stoi(argv[2])))
      {
         cerr << "Error reading arguments. The first two arguments must be the width and height" << endl;
      }
      if(!(latLowBound = stof(argv[3])) || !(latHighBound = stof(argv[4])))
      {

      }
      if(!(longLowBound = stof(argv[5])) || !(longHighBound = stof(argv[6])))
      {

      }
      for(int i = 7 ; i < argc ;)
      {
         latList.push_back(stof(argv[i++]));

         longList.push_back(stof(argv[i++]));
      }
   }

   ifstream dataFile; 
   
   dataFile.open("data.txt", ios::in);
   if(!dataFile.is_open())
   {
      cerr << "Error opening data.txt" << endl;
   }
   else
   {
      string line;

      while (getline(dataFile,line))
      {
         size_t delim = line.find(" ");
	 if(width == 0 && height == 0)
	 {
	    width = stoi(line.substr(0,delim));
	    height = stoi(line.substr(delim + 1));
	 }
         else if (latLowBound == 0.0 && latHighBound == 0.0)
         {
	    latLowBound = stof(line.substr(0,delim));
            latHighBound = stof(line.substr(delim + 1));
         }
         else if (longLowBound == 0.0 && longHighBound == 0.0)
         {
	    longLowBound = stof(line.substr(0,delim));
            longHighBound = stof(line.substr(delim + 1));
         }
	 else
	 {
	    latList.push_back(stof(line.substr(0,delim)));
            longList.push_back(stof(line.substr(delim + 1)));
	 } 
      }
   dataFile.close();
   }


   float minLat = latList[0], minLong = longList[0], maxLat = latList[0], maxLong = longList[0]; 
   int size = latList.size();
   for(int i = 1 ; i < size ; i++)
   {
      if(latList[i] < minLat)
      {
         minLat = latList[i];
      }
      else if(latList[i] > maxLat)
      {
         maxLat = latList[i];
      }

      if(longList[i] < minLong)
      {
         minLong = longList[i];
      }
      else if(longList[i] > maxLong)
      {
         maxLong = longList[i];
      }
   }
   
   float deltaLat = latHighBound - latLowBound;
   float deltaLong = longHighBound - longLowBound;
   vector<int> xList;
   vector<int> yList;
   
   //double xLowBound = merc_x(longLowBound);
   //double xHighBound = merc_x(longHighBound);
   //double yLowBound = merc_y(latLowBound);
   //double yHighBound = merc_y(latHighBound);

   for(int i = 0 ; i < size ; i++)
   {
      

      //convert lat long to x y and translate it to the origin
      //xList.push_back((merc_x(longList[i]) - xLowBound));
      //yList.push_back((merc_y(latList[i]) - yHighBound) * -1);

      //Scale to size of output image
      //xList[i] = xList[i] * width / (xHighBound - xLowBound);
      //yList[i] = yList[i] * height / (yHighBound - yLowBound);
      

      xList.push_back(round(((((longList[i] - longLowBound)/(deltaLong)))*width)));
      yList.push_back(round((1 -((latList[i] - latLowBound)/(deltaLat)))*height));
      
	
   }

   ofstream outputFile;
   outputFile.open("points.txt", ios::out);
   if(!outputFile.is_open())
   {
      cerr << "Error opening points.txt" << endl;
   }
   else
   {
      for(int i = 0 ; i < size ; i++)
      { 
	 outputFile << xList[i] << " " << yList[i] << endl;
      }
   }
   outputFile.close();

   return 0;
}



