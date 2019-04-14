#include <limits.h>
#include <stdlib.h>
#include <stdio.h>




int main()
{
   int a = INT_MAX; int b = INT_MAX;

    printf("INT_MAX is %d \n", INT_MAX);
   
   int ans = (a/2+b/2 + (a%2+b%2)/2);

   printf("half of a is %d \n", a/2);



  
   printf("average is %d \n", ans);

    return 0;


} 



