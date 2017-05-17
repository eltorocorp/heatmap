./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap.png
sudo mv heatmap.png /var/www/html/images/heatmap.png
