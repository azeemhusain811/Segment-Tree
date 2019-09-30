#include<bits/stdc++.h>
using namespace std;

void buildTree(int *arr, int *tree, int start, int end, int node)
{
	if(start==end)
	{
		tree[node] = arr[start];
		return; 
	}
	int mid = start+(end-start)/2;
	
	buildTree(arr, tree, start, mid, 2*node+1);
	buildTree(arr, tree, mid+1, end, 2*node+2);
	
	tree[node] = tree[2*node+1] + tree[2*node+2];
	
}

void updateTree(int* tree, int start, int end, int node, int i, int value)
{
	if(start==end)
	{
		tree[node] = value;
		return;
	}
	int mid = (start+end)/2;
	if(i>mid)
	updateTree(tree, mid+1, end, 2*node+2, i, value);
	else
	updateTree(tree, start, mid, 2*node+1, i, value);
	
	tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

int sumRange(int* tree, int start, int end, int i, int j, int node)
{
	if(i>end || j<start)      // Segment is outside of the Range
	return 0;
	
	if(i<=start && j>=end)   // Segment is completely inside Range
	return tree[node];
	
	int mid = (start+end)/2;
	return sumRange(tree, start, mid, i, j, 2*node+1) + 
	sumRange(tree, mid+1, end, i, j, 2*node+2);       // If Segment intersects
}

main()
{
	int arr[] = {1,2,3,4,5,6};
	int height = (int)ceil(log2(6));
	int size = (int)pow(2, height+1) - 1;	
	int* tree = new int[size];
	buildTree(arr, tree, 0, 5, 0);
	updateTree(tree, 0, 5, 0, 2, 5);
	cout<<sumRange(tree, 0, 5, 1, 3, 0);
}
