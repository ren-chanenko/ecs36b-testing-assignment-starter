# Google Test And Debugging Writeup

## Things I Thought To Test
1. `swap`: 
   - test whether the two values will be changed at the two pointers given
2. `copy_array`:
   - test whether the copied array is identical to the original, have the
     same length and the same value of the elements 
   - check the case with an empty array
   - check whether the function actually returns a copy, change a value in a 
     copy and see if the original would be affected or not
3. `min_index_of_array`:
    - test whether the value at the index is actually the smallest value
    - in the case of the two values being the same, check if the returned
      value is actually from the lower index
4. `make_sorted`:
    - check whether the array is sorted in the correct way
    - check that all the initial values are still present in the sorted array,
      and there are no extra values
5. `get_sorted`
    - check whether the array has been sorted correctly
    - check if the returned array is the copy, not the original
    - check either all the values of the original array are
      present in the sorted one, and no extra values are present
6. `parse_args`:
  - check that the arguments in the argv are correctly converted into integers
  - check if all of the arguments that can be converted into integers were
    written into the ar_out, and those that cant be converted(a string like "hello")
    is set to 0?
  - check that there is no extra arguments in the ar_out(len_out is 1 less than
    argc)
  - check if there is no command line arguments, then ar_out is NULL
    

## Bugs

### Bug 1

### Location

sorting.cpp, line 66-68, swap function

```c++
    int* temp = a;
    a = b;
    b = temp;
```

### How the bug was located

I ran the first test(SwapTests, SimpleSwapTwoValues) to see if the two value would be
swaped. It failed, so I used the debugger to see what is going on in the swap function.

### Description

The function is supposed to swap the two values represented by the pointers. Instead,
it was swapping what those two pointers are pointing at, without swaping the values themselves.

### Fix 

I changed it so it dereference pointers and swap the actual values.

```c++
    int temp = *a;
    *a = *b;
    *b = temp;
```

### Bug 2

### Location

sorting.ccp, line 36-37, copy_array function

```c++
    int* copy = ar;
    return copy;
```

### How the bug was located

I ran the test(CopyArrayTests, SimpleValuesAreSame) and it failed. I went to
look at the function body, and it was obvious that the function is not properly
written.

### Description

The program doesn't copy the array, instead it creates a new pointer that points
at the original array.

### Fix

I created a new array by using malloc and put all of the values from the original
array one by one, then I pointed a pointed to the beginning of the copy array 
and returned that pointed

```c++
  int* copy_arr = (int*) malloc (len * sizeof (int));

  for (int i = 0; i < len; ++i) {
    copy_arr[i] = ar[i];
  }
  int * p_copy = &copy_arr[0];

  return p_copy;
```

### Bug 3

### Location

sorting.cpp, line 23-26, make_sorted function

```c++
  for (int i = 0; i < len; ++i) {
    int min_index = min_index_of_array(ar + i, len);
    swap(ar + i, ar + min_index);
  }
```

### How the bug was located

Ran the test(MakeSortedTests, SimpleSortSortedArray) and it failed. Then I ran it with the debugger
and discovered the bugs.

### Description

When calling out min_index_of_array function, we are passing the pointer that not always points at the beginning
of the array. Which means that the parameter length has to be different. Ex.: if we are passing a pointer
that points to a second element, then the length will be smaller by one, in comparison to the pointer
that is pointing to the first element. In addition, if we pass an array pointing not to the first element, 
the function sees it as a first element, and will treat it, as if it's index is 0. So when making the conversion 
back, it needs to be adjusted too.

### Fix

I adjusted the length parameter by subtracting the number of elements the loop already went over(i). And I added i
to the result of min_index_of_array function, in order to account the change in convertion

```c++
  for (int i = 0; i < len; ++i) {
    int min_index = min_index_of_array((ar + i), (len - i)) + i;
    swap(ar + i, ar + min_index);
  }
}
```