/*Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

Input Format
First line contains an integer n representing number of votes.
Second line contains n space-separated strings representing candidate names.

Output Format
Print the name of the winning candidate followed by the number of votes received.

Sample Input
13
john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

Sample Output
john 4*/

#include <stdio.h>
#include <string.h>

#define MAX_VOTES 1000
#define MAX_LEN 50

int main() {
    int n;
    scanf("%d", &n);

    char votes[MAX_VOTES][MAX_LEN];
    for (int i = 0; i < n; i++)
        scanf("%s", votes[i]);

    char candidates[MAX_VOTES][MAX_LEN];
    int count[MAX_VOTES] = {0};
    int unique = 0;

    // Count votes
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique; j++) {
            if (strcmp(votes[i], candidates[j]) == 0) {
                count[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(candidates[unique], votes[i]);
            count[unique] = 1;
            unique++;
        }
    }

    // Find max votes
    int max_votes = 0;
    for (int i = 0; i < unique; i++)
        if (count[i] > max_votes)
            max_votes = count[i];

    // Find lexicographically smallest among winners
    char winner[MAX_LEN] = "";
    for (int i = 0; i < unique; i++) {
        if (count[i] == max_votes) {
            if (strlen(winner) == 0 || strcmp(candidates[i], winner) < 0)
                strcpy(winner, candidates[i]);
        }
    }

    printf("%s %d\n", winner, max_votes);
    return 0;
}