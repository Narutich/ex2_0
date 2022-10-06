#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int check_points(int* points, int size){
	int flag = 0;
	int count = 0;
	for(int i = 0; i < size; i++){
		if(points[i] == -1)
			count++;
	}
	
	if(count == (size-1))
		flag = 1;
		
	return flag;
}


int min_point(int* points, int size){
	if(check_points(points, size) == 1)
		return -1;

	int min_num = -1;
	int min_index;
	for(int i = 0;i < size;i++){
		if(points[i] != -1){
			min_num = points[i];
			min_index = i;
			break;
		}
	}
	
			
	for(int i = 0;i < size; i++){
		if(min_num > points[i] && points[i] != -1){
			min_num = points[i];
			min_index = i;
		}
	}
	return min_index;
}


int min_distance(int* points, int size){
	int rightDistance = 0, leftDistance = 0;
	int min_num = min_point(points, size);
	int rightIndex = -1;
	int leftIndex = -1;
	
	for(int i = min_num + 1; i < size; i++, rightDistance++){
		if(points[i] != -1){
			rightIndex = i;
			break;
		}
	}

	for(int i = min_num - 1; i >= 0; i--, leftDistance++){
		if(points[i] != -1){
			leftIndex = i;
			break;
		}	
	}

	
	if(rightIndex == -1 && leftIndex == -1)
		return -1;
	else if(rightIndex == -1)
		return leftIndex;
	else if(leftIndex == -1)
		return rightIndex;
	return rightDistance > leftDistance ? leftIndex : rightIndex;
}

void sum_points(int* points, int size){
	int min_index = min_point(points, size);
	int side = min_distance(points, size);
	
	points[side] += points[min_index];
	points[min_index] = -1;
}

void print_arr(int* arr, int size){
	for(int i = 0;i < size; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}

void fill_arr(int* arr, int size){
	srand(time(NULL));
	for(int i = 0;i < size; i++)
		arr[i] = rand() % 100;
}


int main(){
	int n;
	printf("Enter amount of points: ");
	scanf("%d", &n);
	if(n <= 0){
		printf("size less than 0");
		return 0;
	}
	int* points = (int*)malloc(n * sizeof(int));
	
	fill_arr(points, n);
	printf("--------------original_arr--------------\n");
	print_arr(points, n);
	printf("----------------------------------------\n");
	while(check_points(points, n) != 1){
		sum_points(points, n);
		print_arr(points, n);
		printf("---------------------------------------\n");
	}
	
	free(points);
	return 0;
}