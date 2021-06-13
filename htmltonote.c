#include<stdio.h>
#include<string.h>
void parser(char* arr)
{
	int n=0,index=0;
	for(int i=0;i<strlen(arr);i++){
		if(arr[i]=='<'){
			n=1;
			continue;
		}
		else if(arr[i]=='>'){
			n=0;
			continue;
		}
		if(n==0){
			arr[index]=arr[i];
			index++;
		}
	}
	arr[index]='\0';
	while(arr[0]==' '){
		for(int i=0;i<strlen(arr);i++){
			arr[i]=arr[i+1];
		}
	}
	while(arr[strlen(arr)-1]==' '){
		arr[strlen(arr)-1]='\0';
	}
}

int main()
{
	char arr[20];
	char arr1[20];
	printf("Enter 1st line of html code: ");
	gets(arr);
	parser(arr);
	puts(arr);
}
