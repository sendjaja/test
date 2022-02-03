#!/bin/bash

# program needed
# git, awk, sed, uniq, jq

Server="https://jira.atlassian.com/rest/api/2/issue/"

# NEED TO EDIT THIS FILE FOR LOCAL GIT REPO LOCATION
# otherwise clone everytime? not very efficient, but ensure
# that the local copy is fresh
GIT_REPO_LOCATION=git_repo_list.txt

# Need this, but cannot get it yet
JIRA_TOKEN=
# Can't get token yet, so use cookie

COOKIE="JSESSIONID="

JIRA_TYPE=""

TICKET_LIST=commit_list_4.txt

getMergedTickets()
{

   # echo "$parameterC"

   for i in $(cat < $GIT_REPO_LOCATION); do
      # Get the list of merge between parameterA and parameterB
      echo "Repo : $i"
      echo "From : $1"
      echo "To   : $2"

      # Why does --first-parent not work?
      git -C $i log --pretty=oneline  $1..$2 > commit_list.txt

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

      # Sort if needed
      # sort commit_list_2.txt > commit_list_sorted.txt

      # Remove all duplicates using unique
      # uniq commit_list_sorted.txt > commit_list_3.txt

      awk '!x[$0]++' commit_list_2.txt > commit_list_3.txt

      awk -v ref=$JIRA_TYPE '{print ref $0}' commit_list_3.txt > $TICKET_LIST
      rm commit_list_sorted.txt commit_list_1.txt commit_list_2.txt commit_list.txt commit_list_3.txt
   done
}

getJIRASummary()
{
   rm -f $1

   IFS=$'\n'       # make newlines the only separator
   set -f          # disable globbing
   for i in $(cat < $TICKET_LIST); do
      # Now need to call JIRA API to get ticket summary based on those keys in TICKET_LIST
      #SUMMARY=$(curl -s "$Server$i?fields=summary" | jq ".fields.summary")
      SUMMARY=$(curl -s "$Server$i?fields=summary" -b "$COOKIE"| jq ".fields.summary")

      # Summary returned will have "" as the first and last character
      # Remove first character from summary
      # SUMMARY=${SUMMARY#?}
      # Remove last character from summary
      # Somehow not working
      # SUMMARY=${SUMMARY%?}

      # Substitute all occurences of \" to nothing
      SUMMARY=${SUMMARY//\"/}

      echo $i $SUMMARY >> $1
   done

   cat $1
}

helpFunction()
{
    echo "Usage: $0 -f commit_from -t commit_to -o output_file"
    echo -e "\t-f tag/hash/branch of commits to diff from"
    echo -e "\t-t tag/hash/branch of commits to diff to"
    echo -e "\t-o Output file"
    exit 1 # Exit script after printing help
}

while getopts "f:t:o:" opt
do
   case "$opt" in
      f ) parameterA="$OPTARG" ;;
      t ) parameterB="$OPTARG" ;;
      o ) parameterC="$OPTARG" ;;
      ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Print helpFunction in case parameters are empty
if [ -z "$parameterA" ] || [ -z "$parameterB" ] || [ -z "$parameterC" ]
then
   echo "Some or all of the parameters are empty";
   helpFunction
fi

# Begin script in case all parameters are correct

# Get all unique JIRA ticket that got merged from
# commit $parameterA to commit $parameterB
getMergedTickets $parameterA $parameterB

parameterC="output.txt"
# Use JIRA Rest API to get JIRA ticket summary
getJIRASummary $parameterC

rm $TICKET_LIST
