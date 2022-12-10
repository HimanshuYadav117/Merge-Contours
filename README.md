# Merge-Contours
Optimized Merging Contours logic on basis of distance of nearby contours in C++ &amp; OpenCV 

########## THE LOGIC IS ALSO COMPATIBLE WITH EDGE SUB PIXEL header file which finds contour in sub pixel range ##########

To use merge contours function in your own c++ code you just need the basic OPENCV liberary headers included in your main file.

#PARAMETERS PASSED AND THEIR MEANING
  
void MergeContours
(
Mat image,    //IMAGE IN MAT format 

vector<Contour>&usableContours, //USABLE Contours is an array of all contours found in the image (CAN BE SUB PIXEL CONTOURS)

int distance_considered,   ##ALWAYS EVEN     //the distance considered in pixel i.e. if distance considered if 4 then assume
//a 4 pixel box(2px up and 2px down) arround every point of contour and then if another contour is in that range it will be merged into that contour

vector<Contour>& finalContours  //storing final contours
) 

INSTRUCTIONS FOR USE:
  COPY ALL THE CONTENT OF "mergecontours.cpp" file into your main file and its ready to use 
  
