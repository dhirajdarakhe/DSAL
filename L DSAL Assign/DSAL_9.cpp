#include <iostream>
using namespace std;

void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}

void heapify(int arr[],int n,int i){
	int largest=i;
	int left = (2*i)+1;
	int right = (2*i)+2;

	if(left<n && arr[left]>arr[largest]){
		largest = left;
	}
	if(right<n && arr[right]>arr[largest]){
		largest = right;
	}
	if(largest!=i){
		swap(arr[i],arr[largest]);
		heapify(arr,n,largest);
	}
}

void heap_sort(int arr[],int n){

	for(int i= (n/2)-1;i>=0;i--){
		heapify(arr,n,i);
	}

	for(int i=n-1;i>=0;i--){
		swap(arr[0],arr[i]);
		heapify(arr,i,0);
	}
}

int main() {

	int arr1[7] = {20,50,40,60,10,30,70};
	cout<<"Before Sorting:\n";
	for(int i=0;i<7;i++){
		cout<<arr1[i]<<" ";
	}
	cout<<endl;
	heap_sort(arr1,7);
	cout<<"After Sorting:\n";
	for(int i=0;i<7;i++){
		cout<<arr1[i]<<" ";
	}
	cout<<endl;

	return 0;
}
