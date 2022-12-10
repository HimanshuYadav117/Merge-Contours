struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);

		if (hash1 != hash2) {
			return hash1 ^ hash2;
		}

		return hash1;
	}
};
void findPixelsNearby(unordered_map<pair<int, int>,bool,hash_pair>&res, Point px,int pxlVal) {
	for (int itr1 = (px.x) - pxlVal; itr1 <= (px.x) + pxlVal; itr1++) {
		for (int itr2 = (px.y - pxlVal); itr2 <= (px.y) + pxlVal; itr2++) {
			res[{itr1, itr2}] = true;
		}
	}
}
unordered_map<pair<int, int>, bool, hash_pair> createSets(vector<Point2f>Contour, int rect) {
	unordered_map<pair<int,int>,bool,hash_pair>res;
	for (auto tra : Contour) {
		Point px = (Point)tra;
		findPixelsNearby(res,px,rect);
	
	}

	return res;
}

//void drawContour(Mat& img, vector<Point2f>s1,int px,int py,int pz) {
//	for (auto x : s1) {
//		line(img, x, x, Scalar(px, py, pz), 4, 0);
//
//	}
//	resShow("temp",img,1);
	
//}

bool hasCommon(unordered_map<pair<int,int>,bool,hash_pair>s1, unordered_map<pair<int, int>, bool, hash_pair>s2){
	for (auto x : s1) {
		if (s2.find(x.first) != s2.end()) {
			return true;
		}
	}
	return false;

}
															
void MergeContours(Mat image, vector<Contour>&usableContours,int distance_considered, vector<Contour>& finalContours) {
	

	int numberContours = usableContours.size();
	vector<vector<int>>ids_for_contour_merge(numberContours);
	vector<unordered_map<pair<int, int>, bool, hash_pair>>ContourSets;	
	vector<bool>boolVals(numberContours,false); 

	for (int i = 0; i < numberContours; i++) {
		ContourSets.push_back(createSets(usableContours[i].points, distance_considered/2));
	}

	for (int i = 0; i < numberContours; i++) {
		
		if (boolVals[i] == false) {
			boolVals[i] = true;
			for (int j = i+1; j < numberContours; j++) {
				if (boolVals[j] == false) {
					
					if(hasCommon(ContourSets[i], ContourSets[j])==true){
						ContourSets[i].insert(ContourSets[j].begin(), ContourSets[j].end());
						boolVals[j] = true;
						ids_for_contour_merge[i].push_back(j);
						j = i;

					}
				}
			}
		}
	}
	vector<bool>Visited(ids_for_contour_merge.size(), false);
	
	for (int mr = 0; mr < ids_for_contour_merge.size(); mr++) {
		if (Visited[mr] == false) {
			vector<Point2f>temp=usableContours[mr].points;
			if (ids_for_contour_merge[mr].size() > 0) {
				for (int mc = 0; mc < ids_for_contour_merge[mr].size(); mc++) {

					int valPtr = ids_for_contour_merge[mr][mc];
					
                    copy(usableContours[valPtr].points.begin(), usableContours[valPtr].points.end(), std::back_inserter(temp));
					Visited[valPtr] = true;
					

				}
			}
			else {
				Visited[mr] = true;
			}
			Contour newCtr;
			newCtr.points = temp;
			finalContours.push_back(newCtr);
		}
		
	}

	///////////////////////////////////////////////////////////////DRAWING CONTOURS
		/*for (auto x : finalContours) {
			cout <<"CONTOURS FINAL SIZE IS : " <<x.points.size()<<endl;
			int px = 0;
			int py = 0;
			int pz = 0;
			drawContour(image, x.points, ((px+rand())%255), ((py + rand()) % 255), ((pz + rand()) % 255));
		
		}*/
	//////////////////////////////////////////////////////////////////////////////


}
