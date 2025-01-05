#include <stdio.h>
#include <string.h>

int main(void){

    char arr_sp[102][102];
    int n = 0;
    while (fgets(arr_sp[n], 102, stdin) != NULL){
        if (strcmp(arr_sp[n], "\n") == 0) {
            break;
        }
        
        arr_sp[n][strlen(arr_sp[n])-1] = '\0';
        n++;
    }
    
    for (int i = 0; i < n; i++){
        if (i % 2 != 0){
           puts(arr_sp[i]); 
        }
    }

    for (int i = n - 1; i >= 0; i--){
        if (i % 2 == 0){
            puts(arr_sp[i]); 
        }
    }

    return 0;
}