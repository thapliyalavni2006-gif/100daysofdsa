/*Read a string and check if it is a palindrome using two-pointer comparison.

Input:
- Single line: string s

Output:
- Print YES if palindrome, otherwise NO*/

#include <stdio.h>
#include <string.h>

int main(){
    char s[1000];
    scanf("%s", s);
    
    int left = 0;
    int right = strlen(s) - 1;
    int isPalindrome = 1;
    
    while(left < right){
        if(s[left] != s[right]){
            isPalindrome = 0;
            break;
        }
        left++;
        right--;
    }
    
    if(isPalindrome){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    return 0;
}