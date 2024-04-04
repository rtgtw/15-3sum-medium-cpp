/*
15. 3Sum

Given an array of unsorted numbers, find all unique triplets in it that add up to zero.

Example 1:

Input: [-3, 0, 1, 2, -1, 1, -2]
Output: [[-3, 1, 2], [-2, 0, 2], [-2, 1, 1], [-1, 0, 1]]
Explanation: There are four unique triplets whose sum is equal to zero. smallest sum.'



Solution:

We are going to use a two pointer approach 

1.We have an unsorted array so the first thing is to sort it
	we can do this though the algorithm header and std::sort

2. We are going to iterate through the array taking 1 element, i at a time
	when we take i, we then look for two elements, X and Z, whos sum equals 
	i's complement

3. We have to avoid duplicate numbers because we are looking for only unique pairs
after sorting the array, a duplicate would be next to itself, so if they are equal
to each other then we can simply just skip them



-----
1.The main function 'searchtriplets' is our main method that handles this process
	search triplets starts by sorting the array

2. Next it starts iterating over the sorted array, at each iteration 
	it calls the searchPair method in order to find a pair within the rest of the array
	(not including i itself) that adds up to i's complement 

3. The searchPair method is going to be using the two pointer technique to find two pairs
	It starts with one pair at the begining of the array (after i) and one at the end of the array
	It then calculates the sum of the pairs (elements at each pointer)
	It compares this to the target, which is i's complement
	If they are equal then add all three to the new vector to include all three values
		This includes i which is the element that is iterated over searchTriplets, and 
		X and Y that adds up to i's complement

4. If the sum of X and Y is less than the target(i's complement) then we need to increase 
	the sum by  incremeneting the left pointer
	If the sum of X and Y is greater than the target (i's complement) then we need to increase
	the sum by decrementing the right pointer 

5.To avoid duplicates, both searchTriplets and searchPairs both skip elements that are
	the same as the previous value that they were at 

*/




//Add algorithm to use std::sort to sort the unordered array
#include <algorithm>
#include <iostream>
#include <vector>



class Solution {
private:
	static void searchPairs(std::vector<std::vector<int>> &result, std::vector<int> &arr,int target, int i);


public:
	static std::vector<std::vector<int>> searchTriplets(std::vector<int>& arr);

};


void Solution::searchPairs(std::vector<std::vector<int>>& result, std::vector<int>& arr, int target, int i){\
	
	//searchPairs method is going to be employing the two pointers approach
	//The left pointer is going to be i + 1
	//The right pointer is going to be arr . size() - 1
	int left = i + 1;
	int right = arr.size() - 1;

	//We can now search for two elements within the array that equals the target
	//We can use a while loop to iterate through the array while left is less than right
	while (left < right) {
		
		//Create a variable to store the sum of left and right
		int sum = arr[left] + arr[right];

		//We now check if the sum of left and right is equal to the target
		//If the sum is less than the target then we need to move up so increment left
		if (sum < target) {
			left++;
		}
		else if (sum > target) {
			right--;
		}//now if the sum is equal to the target we want to store that inside of result
		//we also want to increment left and decrement right
		//We also want to check for duplicates 
		else {
			
			result.push_back({ arr[i],arr[left],arr[right] });
			left++;
			right--;
			//changed from if to while, to iterate through all duplicates and not just one
			//I also need to account for the bounds, left has to be smaller than right
			while (left < right && arr[left] == arr[left - 1]) {
				left++;
			}
			//This is where I had an error, I did right - 1 instead of right + 1 
			//To account for where right just came from
			//Right has to be more than left, to stay in bounds
			while (right > left && arr[right] == arr[right + 1]) {
				right--;
			}

		}

	}

}




 std::vector<std::vector<int>> Solution::searchTriplets(std::vector<int>& arr) {
	 //First thing we want to do within this method is sort the array that is passed in
	 std::sort(arr.begin(), arr.end());

	 //Next we want to create an empty array of arrays that will hold our results when we 
	 //Find a triplet
	 std::vector<std::vector<int>> results;

	 //We need to create a for loop that will iterate through each element within arr
	 for (int i = 0; i < arr.size(); i++) {

		 //Through each iteration we are using that element as the first element for potential triplets
		 //We then want to call a method searchPairs, within the same sorted array, and look for two
		 //elements who equals i's complement
		 
		 //target = i's complement. if i = 5, i's complement is = -5
		 int target = arr[i] * -1;
		
		 //We need to pass in the target and the sorted array to the check pairs method.
		 // We also need to pass in the result since checkPairs will insert a triplet if found
		 //To make sure we are not iterating through a duplicate we can create and if statement
		 //That says to only enter the if statement if it has not been seen previously
		 //This works since our array is sorted
		 //We also know that if i is greater than 0 then it would be impossible to find
		 //2 other values that we can get to 0, so we dont enter the loop as well
		 
		 if (i > 0 && arr[i] == arr[i - 1]  ) {

			 continue;

		 }

		 searchPairs(results, arr, target, i);



	 }





	 return results;
}


 int main() {

	 Solution solution;

	 std::vector<int> vector = { -3, 0, 1, 2, -1, 1, -2 };
	 std::vector<int> vector2 = { -5,2,-1,-2,3 };
	 std::vector<int> vector3 = { -2,0,0,2,2 };
	 std::vector<int> vector4 = { -2,0,1,1,2 };
	 std::vector<int> vector5 = { -2,0,3,-1,4,0,3,4,1,1,1,-3,-5,4,0 };

	 std::vector<std::vector<int>> result = solution.searchTriplets(vector5);

	 for (std::vector<int> arr : result) {

		 std::cout << " { " ;
		 for (int element : arr) {

			 std::cout << element << ' ';
		 }
		 std::cout  << " } ";
	 }


	 //Time compelxity = O(N^2)
	 //Space Complexity = O(n)
	 //Study time: 4H

	 return 0;
 }