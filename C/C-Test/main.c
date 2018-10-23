#include <stdio.h>

unsigned int FloatToUint(float n);
float UintToFloat(unsigned int n);



int main()
{

   char buf[sizeof(unsigned int)*7] = {};

   printf("size of buf is %d \n", sizeof(buf));

   float  a = -37.77;
   
   printf("converted unsinged int is %d \n", FloatToUint(a));
   printf(" converted back float is %f \n",UintToFloat(FloatToUint(a)));

   return 0;

}
	

unsigned int FloatToUint(float n)
{
   return (unsigned int)(*(unsigned int*)&n);
}
 
float UintToFloat(unsigned int n)
{
   return (float)(*(float*)&n);
}
