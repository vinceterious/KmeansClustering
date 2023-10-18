# KmeansClustering
A quick program to machine learning KMeans clustering algorithm

This c++ implementation is very "naive" and non optimized solution.

For compilation:
- mkdir build
- cmake <project_directory>
- make

Three files are create with this dataset:

1) File "elbow" which contains the inertia value considering the number of cluster evaluate:

Visualization with gnuplot:

  set datafile sep ','
  
  plot 'elbow' u 1:2 w l
  
Elbow is quite "bumpy" due to very naive initialization of the centroid (totally random point is choose for initialize each centroid) 
![image](https://github.com/vinceterious/KmeansClustering/assets/37022308/33f8f0a2-1c2f-4ff1-81cc-4cee0890a540)
  
2) File "point" from dataset with associated centroid index cluster:
  
Visualization with gnuplot:

  set datafile sep ','
  
  plot 'point' u 2:3:4 palette ps 5 pt 7
  

![image](https://github.com/vinceterious/KmeansClustering/assets/37022308/29ad4979-0d00-48ff-b13d-18b0d667e32a)

3) File "centroid" which contents coordinates of the centroid:
  
Visualization with gnuplot for both data and centroid:

  set datafile sep ','
  
  plot 'point' u 2:3:4 palette ps 5 pt 7, 'centroid' u 2:3 ps 5 pt 9

![image](https://github.com/vinceterious/KmeansClustering/assets/37022308/22c72865-20b2-4573-9623-ca11b2f5124d)


More information on dataset use in this example and dataset process via sklearn here:

https://www.kaggle.com/code/heeraldedhia/kmeans-clustering-for-customer-data?scriptVersionId=45166976&cellId=26
