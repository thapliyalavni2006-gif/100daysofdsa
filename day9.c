/*A secret system stores code names in forward order. To display them in mirror format, you must transform the given code name so that its characters appear in the opposite order.

Input:
- Single line: a lowercase string containing only alphabetic characters (no spaces)

Output:
- Print the transformed code name after applying the mirror operation
*/
#include <stdio.h>
#include <string.h>

int main(){
    char str[1000];
    scanf("%s", str);
    
    int len = strlen(str);
    
    for(int i = len - 1; i >= 0; i--){
        printf("%c", str[i]);
    }
    
    printf("\n");
    
    return 0;
}