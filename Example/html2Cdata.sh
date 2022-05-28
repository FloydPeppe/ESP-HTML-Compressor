
DIR=$(dirname "$(realpath "$0")")

echo Compressing and generating C syntax array from $DIR/HTML
echo

$DIR/Convert.py && cp output_dir $DIR/Webserver/include/StaticPageData.h

echo
echo $DIR/Webserver/include/StaticPageData.h created!

