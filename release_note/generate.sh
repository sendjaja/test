#!/bin/bash

# program needed
# git, awk, sed, uniq, jq

Server="https://jira.atlassian.com/rest/api/2/issue/"

# NEED TO EDIT THIS FILE FOR LOCAL GIT REPO LOCATION
GIT_REPO_LOCATION=git_repo_list.txt

# Need this, but not MINE
JIRA_TOKEN=

# In case if tickets are moved under NRF-
JIRA_TYPE="NEUR-"

#DEBUG
# parameterA="develop"
# parameterB="IPG-v86.0"
parameterA="develop"
parameterB="IPG-v86.0"

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

for i in $(cat < $GIT_REPO_LOCATION); do
   # Get the list of merge between parameterA and parameterB
   echo $i
   git -C $i log --no-merges --pretty=oneline --first-parent $parameterA...$parameterB > commit_list.txt

   # Find the first occurence of NEUR- and the following 5 characters
   awk -v ref=$JIRA_TYPE 'match($0, ref) {
      print substr($0, RSTART, RLENGTH+8)
   }
   ' commit_list.txt > commit_list_1.txt

   # Only allow 0-9
   sed 's/[^0-9]*//g' commit_list_1.txt > commit_list_2.txt

   # Check the length of each line
   #awk '{print length}' commit_list_2.txt | sort -n | uniq -c > commit_list_length.txt

   # more commit_list.txt| awk -F'NEUR' '{print $2}'
   #sed 's/^NEUR-/NEUR-/' commit_list.txt > commit_list_1.txt
   # Remove the first column of the commit hash
   #sed 's/^ *//' commit_list.txt | cut -d" " -f2- > commit_list_1.txt

   # Remove all duplicates using unique
   uniq commit_list_2.txt > commit_list_3.txt

   awk -v ref=$JIRA_TYPE '{print ref $0}' commit_list_3.txt > commit_list_4.txt

   # Sort if needed
   #sort commit_list_3.txt > commit_list_sorted.txt

   rm commit_list_1.txt commit_list_2.txt commit_list.txt commit_list_3.txt

   cat commit_list_4.txt
   #rm commit_list_4.txt
done

TICKET_LIST=commit_list_sample.txt

OUTPUT=result.txt

rm -f $OUTPUT

IFS=$'\n'       # make newlines the only separator
set -f          # disable globbing
for i in $(cat < $TICKET_LIST); do
   # Now need to call JIRA API to get ticket summary based on those keys in TICKET_LIST
   SUMMARY=$(curl -s "$Server$i?fields=summary" | jq ".fields.summary")
   # Summary returned will have "" as the first and last character
   # Remove first character from summary
   SUMMARY=${SUMMARY#?}
   # Remove last character from summary
   SUMMARY=${SUMMARY%?}
   echo $i $SUMMARY >> $OUTPUT
done