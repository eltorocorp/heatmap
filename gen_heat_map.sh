./latlong2point
cat points.txt | examples/heatmap_gen 500 500 > heatmap.png
sudo mv heatmap.png /var/www/html/images/heatmap.png
