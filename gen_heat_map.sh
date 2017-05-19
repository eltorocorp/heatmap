./latlong2point
cat points.txt | examples/heatmap_gen 1920 1080 > heatmap.png
sudo mv heatmap.png /var/www/html/images/heatmap.png
mv data.txt data_files/starbucks_data.txt
mv data_files/louisville_thrift_store_data.txt data.txt
./latlong2point
cat points.txt | example/heatmap_gen 1920 1080 > heatmap2.png
sudo mv heatmap2.png /var/www/html/images/heatmap2.png
