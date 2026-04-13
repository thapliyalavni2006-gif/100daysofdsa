/*Given a string s consisting of lowercase letters, find the first repeated character in the string. A character is considered repeated if it appears more than once, and among all such characters, the one whose second occurrence has the smallest index should be returned.

Input Format
A single string s.

Output Format
Print the first repeated character. If no character is repeated, print -1.

Sample Input
geeksforgeeks

Sample Output
e*/

#include <stdio.h>
#include <string.h>

int main() {
    char s[100001];
    scanf("%s", s);
    
    int seen[26] = {0};
    int n = strlen(s);
    
    for (int i = 0; i < n; i++) {
        int idx = s[i] - 'a';
        if (seen[idx]) {
            printf("%c\n", s[i]);
            return 0;
        }
        seen[idx] = 1;
    }
    
    printf("-1\n");
    return 0;
}