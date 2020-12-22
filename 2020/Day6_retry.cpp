#include <stdio.h>

int main(){
	FILE *fp = fopen("input_day6.txt", "r");
	char line[11];
	int max = 0;
	while(fread(line, 1, 11, fp)){
		printf("%s\n", line);
		// val > max && (max = val);
	}
	printf("%d\n", max);
		


	fclose(fp);

	return 0;
}