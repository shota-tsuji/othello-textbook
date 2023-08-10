tag_name=othello
container_name=othello
docker build -t ${tag_name} .
docker run -it --rm --name ${container_name} --entrypoint /bin/bash ${tag_name}:latest