#include "utility.h"
#include <string.h>




void string_to_int (unsigned char *num,uint32_t*data,int number)
{
	int i= 0 ;
	int x ;
	int y ;

	for (x = 0 ; x<number ;x++)
	{
       y=i ;
		for ( ; i<15+y ;i++)
		if((num[i]> 0x29) && (num[i] <= 0x39))
				break ;
		for(;(num[i]>= 0x30) && (num[i] <= 0x39); i++)
			data[x] = (data[x])* 10 + ( num[i] - '0' );
	}
}

int Integer_To_String (char*arr,long integer)
{
	int size = 0 ;
	int temp = integer ;
	int count = 0  ;
	while (temp != 0)
	{
		temp = temp / 10;
		count ++ ;
	}

	size = count-- ;
	do {
		arr[count] =(integer % 10)+48;
		integer /= 10;
		count--;
	} while (integer != 0);


	return size ;
}


int Sprint_int(char *arr ,char *temp,int integer,... )
{

	char temp_arr[150];
	int i ;
	for(i = 0 ; temp[i] !='\0'; i++)
		temp_arr[i] = temp[i];
	temp_arr[i] = temp[i];

	int big_counter ;
	int counter = 0 ;
	int index = 0 ;
	int remain_array ;
	for (big_counter= 0 ; big_counter < 1 ; big_counter++)
	{
		char arr_integer[20];
		int size = Integer_To_String(arr_integer , *((&integer)+big_counter));
		counter = 0 ;
		while(temp_arr[counter] != '\0')
		{

			if((temp_arr[counter] == '%') && (temp_arr[counter+1] == 'd') )
			{

				break;
			}
			counter++ ;
		}

		if(temp_arr[counter] == '\0')
		{

			break;
		}

		remain_array = counter+2 ;
		for (index = 0 ; index < counter ; index++)
		{
			arr[index] = temp_arr[index] ;
		}
		for (counter = 0 ; counter < size ; counter++)
		{
			arr[index++] = arr_integer[counter] ;
		}
		for(counter = remain_array ; temp_arr[counter] != '\0' ; counter++ )
		{
			arr[index++] = temp_arr[counter] ;
		}
		arr[index] = '\0';



		for(i = 0 ; arr[i] != '\0'; i++)
		{
			temp_arr[i] = arr[i];
		}
		temp_arr[i] = arr[i];

	}
	return index ;
}

int Sprint_str(char *arr ,char *temp,char* str,... )
{
	int string_num = 0 ;


	volatile   char *string_array[10];


	int index = 0 ;


	int remain_array ;

	  char temp_arr[100];
	memset(temp_arr, 0, sizeof(temp_arr));
	int i ;
	int counter = 0;
	int num ;
	for(i = 0 ; temp[i] !='\0'; i++)
	{
		if (temp[i] == '%' && temp[i+1]== 's')
			string_num++;
		temp_arr[i] = temp[i];
	}

	temp_arr[i] = temp[i];
	for(i = 0 ; i < string_num ; i++)
		string_array[i] = *((&str)+i);

	for (i = 0 ; i <1 ; i++ )
	{
		counter = 0 ;
		while(temp_arr[counter] != '\0')
		{

			if((temp_arr[counter] == '%') && (temp_arr[counter+1] == 's') )
			{


				break;
			}
			counter++ ;

		}

		if(temp_arr[counter] == '\0')
		{

			break;
		}
		remain_array = counter+2 ;
		for (index = 0 ; index < counter ; index++)
		{
			arr[index] = temp_arr[index] ;

		}
		for (counter = 0 ; counter < strlen(string_array[i]) ; counter++)
		{
			arr[index++] = (string_array[i])[counter] ;

		}

		for(counter = remain_array ; temp_arr[counter] != '\0' ; counter++ )
		{
			arr[index++] = temp_arr[counter] ;

		}
		arr[index] = '\0';


		for(num= 0 ; arr[num] != '\0'; num++)
		{
			temp_arr[num] = arr[num];


		}
		temp_arr[num] = arr[num];



	}
	return index ;
}

int sprint(char*arr,char*temp,char* str,...)
{
	int counter = 0 ;
	int i ;
	int size ;
	memcpy(arr,temp,strlen(temp)+1);

	for (i = 0 ; i < strlen(temp) ; i++)
	{
		if (temp[i]=='%' && temp[i+1] == 's')
		{
			size = Sprint_str(arr , arr, *((&str)+counter) );
			counter++;
		}
		else  if (temp[i]=='%' && temp[i+1] == 'd')
		{

			size = Sprint_int(arr , arr, *((&str)+counter));
			counter++;

		}
	}
	return size;

}
