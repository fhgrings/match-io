sudo docker build -t mqtt-parser . &&
sudo docker run -d --name mqtt-parser -p 1080:1080 mqtt-parser
