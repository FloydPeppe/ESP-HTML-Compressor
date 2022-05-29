
files=($(find data -regex ".*\..*"))

outfile="./include/assetsPath.h"

rm $outfile

echo "
/*
 * 
 * Definition of assets path strings 
 *
 */
 " > $outfile

for i in ${files[*]}; do 
    path=$(echo $i | sed 's/data//g' )
    namefile="$(echo $path | sed 's/\/assets\///g' | sed 's/\///g' | sed 's/\./_/g')"_path
    #echo "const char* $namefile= \"$path\";" >> $outfile
    echo "#define ${namefile^^} (const char*) \"$path\"" >> $outfile 
done

exit


