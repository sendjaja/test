#!/bin/bash

helpFunction()
{
    echo "Usage: $0 -a parameterA -b parameterB" # -c parameterC"
    echo -e "\t-a Description of what is parameterA"
    echo -e "\t-b Description of what is parameterB"
    # echo -e "\t-c Description of what is parameterC"
    exit 1 # Exit script after printing help
}

while getopts "a:b:" opt
do
   case "$opt" in
      a ) parameterA="$OPTARG" ;;
      b ) parameterB="$OPTARG" ;;
    #   c ) parameterC="$OPTARG" ;;
      ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
   esac
done

#DEBUG
parameterA="develop"
parameterB="IPG-v86.0"

# Print helpFunction in case parameters are empty
if [ -z "$parameterA" ] || [ -z "$parameterB" ] # || [ -z "$parameterC" ]
then
   echo "Some or all of the parameters are empty";
   helpFunction
fi

# Begin script in case all parameters are correct
echo "$parameterA"
echo "$parameterB"
# echo "$parameterC"

# Get the list of merge between parameterA and parameterB
#git log --pretty=oneline --first-parent $parameterA...$parameterB > commit_list.txt

# Find the first occurence of NEUR- and the following 5 characters
awk 'match($0, /NEUR-/) {
    print substr($0, RSTART, RLENGTH+8)
}
' sample_data.txt > commit_list_1.txt
#' commit_list.txt > commit_list_1.txt


# Only allow 0-9
sed 's/[^0-9]*//g' commit_list_1.txt > commit_list_2.txt

# Check the length of each line
awk '{print length}' commit_list_2.txt | sort -n | uniq -c > commit_list_length.txt

# more commit_list.txt| awk -F'NEUR' '{print $2}'
#sed 's/^NEUR-/NEUR-/' commit_list.txt > commit_list_1.txt
# Remove the first column of the commit hash
#sed 's/^ *//' commit_list.txt | cut -d" " -f2- > commit_list_1.txt


# Remove all duplicates using unique
uniq commit_list_2.txt > commit_list_3.txt

# Sort if needed
sort commit_list_3.txt > commit_list_sorted.txt