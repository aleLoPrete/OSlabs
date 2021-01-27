echo insert directory path

read dir

cd $dir;

find . -regex ".*" -exec mv \{} echo \{} | tr 'A-Z' 'a-z'\;