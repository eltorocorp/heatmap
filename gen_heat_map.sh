./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap.png
sudo cp heatmap.png /var/www/html/images/heatmap.png
cp data.txt data_files/starbucks_data.txt
cp data_files/louisville_thrift_store_data.txt data.txt
./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap2.png
sudo cp heatmap2.png /var/www/html/images/heatmap2.png
cp data.txt data_files/louisville_thrift_store_data.txt
cp data_files/starbucks_data.txt data.txt
