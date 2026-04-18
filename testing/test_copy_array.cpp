#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int or_arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(or_arr) / sizeof(or_arr[0]);
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(or_arr[i], cp_arr[i]) << "i:" << i;
    }
    free(cp_arr);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int or_arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(or_arr) / sizeof(or_arr[0]);
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int i = 0; i < length; i++) {
        EXPECT_EQ(or_arr[i], (i+1));
    }
    free(cp_arr);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int or_arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(or_arr) / sizeof(or_arr[0]);
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int i = 0; i < length; i++) {
        or_arr[i] = 10 + i;
    }

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(cp_arr[j], (j + 1));
    }
    EXPECT_NE(or_arr, cp_arr);
    free(cp_arr);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int length = values.size();
    int* or_arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        or_arr[i] = values[i];
    }
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(or_arr[j], cp_arr[j]) << "j:" << j;
    }
    free(or_arr);
    free(cp_arr);
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int length = values.size();
    int* or_arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        or_arr[i] = values[i];
    }
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(or_arr[j], values[j]) << "j:" << j;
    }
    free(or_arr);
    free(cp_arr);
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */

    int length = values.size();
    int* or_arr = (int*) malloc (length * sizeof(int));

    for (int i = 0; i < length; i++) {
        or_arr[i] = values[i];
    }
    int* cp_arr;

    cp_arr = copy_array(or_arr, length);

    for (int i = 0; i < length; i++) {
        or_arr[i] = 10 + i;
    }

    for (int j = 0; j < length; j++) {
        EXPECT_EQ(cp_arr[j], values[j]) << "j:" << j;
    }

    EXPECT_NE(or_arr, cp_arr);
    free(or_arr);
    free(cp_arr);
}



