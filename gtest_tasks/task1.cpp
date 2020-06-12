#include <bits/stdc++.h>
#include "gtest/gtest.h"

#define ll long long
#define pb push_back

using namespace std;

TEST (Casting, IntToLong) {
    // Testing for 10,000 cases
    for (int i = 0; i < 10000; i++) {
        int num = rand() % 999999 + 1;
        EXPECT_EQ(num, (long)num);
    }
}

TEST (Float, CheckPrecision) {
    // Generating a random float number between 0 and 1000
    float a = 1000.0; // Fails if the upper limit to the float is 10000
    for (int i = 0; i < 1000000; i++) {
        float temp = (float(rand())/float((RAND_MAX)) * a);
        double d = (double) temp;
        EXPECT_NEAR(d*d, temp*temp, 0.1);
    }
}

TEST (Vectors, NullVectorEquality) {
    vector <int> v1, v2;
    EXPECT_EQ(v1, v2);
}

TEST (Vectors, FilledVectorEquality) {
    vector <ll> v1, v2, v3;
    // Filling the vectors with 10000 random values
    for (int i = 0; i < 10000; i++) {
        ll temp = rand();
        v1.pb(temp);
        v2.pb(temp);
    }
    v3 = v1;
    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v2, v3);
    EXPECT_EQ(v3, v1);
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS();
}