./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap.png
sudo yes | cp -rf heatmap.png /var/www/html/images/heatmap.png
yes | cp -rf data_files/louisville_thrift_store_data.txt data.txt
./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap2.png
sudo yes | cp -rf heatmap2.png /var/www/html/images/heatmap2.png
yes | cp -rf data_files/starbucks_data.txt data.txt
