#include <bits/stdc++.h>
#include <benchmark/benchmark.h>

#define ll long long

using namespace std;

static void INT_Addition(benchmark::State& state) {
    srand(time(0));
    int a = rand();
    srand(time(0));
    int b = rand();
    for (auto _ : state) {
        a + b;
    }
}

BENCHMARK(INT_Addition);

void merge (vector <int> &a, ll l, ll m, ll r) {
    ll i, j, k;
    ll n1 = m-l+1;
    ll n2 = r-m;

    int v1[n1], v2[n2];
    for (i = 0; i < n1; i++) v1[i] = a[l+i];
    for (i = 0; i < n2; i++) v2[i] = a[m+1+i];

    i = 0; j = 0; k = 0;
    while (i < n1 && j < n2) {
        if (v1[i] <= v2[j]) {
            a[k] = v1[i];
            i++;
        }
        else {
            a[k] = v2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = v1[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        a[k] = v2[j];
        j++;
        k++;
    }
}

void mergeSort(vector <int> &arr, int n) 
{ 
   int curr_size;  
   int left_start; 
  
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) 
   { 
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) 
       { 
           int mid = min(left_start + curr_size - 1, n-1); 
  
           int right_end = min(left_start + 2*curr_size - 1, n-1); 
  
           merge(arr, left_start, mid, right_end); 
       } 
   } 
} 

static void MergeSort(benchmark::State& state) {
    vector <int> arr;
    ll sz = 101001;
    ll s = 0, e = sz-1;
    for (ll i = 0; i < sz; i++) {
        arr.push_back(rand());
    }
    for (auto _ : state) {
        mergeSort(arr, sz);
    }
}

BENCHMARK(MergeSort);

void swap (int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

ll partition (vector <int> &a, ll low, ll high) {
    int pivot = a[high];
    ll i = low-1;
    for (ll j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap (&a[i+1], &a[high]);
    return (i+1);
}

void quickSort(vector <int> &a, ll l, ll h) {
    int stack[h - l + 1];
    int sz = h-l+1; 
  
    int top = -1; 
     
    stack[++top] = l; 
    stack[++top] = h; 
  
    while (top >= 0) { 
         
        h = stack[top--]; 
        l = stack[top--];
         
        int p = partition(a, l, h); 
 
        if (p - 1 > l) { 
            stack[++top] = l; 
            stack[++top] = p - 1; 
        } 
   
        if (p + 1 < h) { 
            stack[++top] = p + 1; 
            stack[++top] = h; 
        } 
    }
}

static void QuickSort(benchmark::State& state) {
    vector <int> arr;
    ll sz = 10100;
    ll s = 0, e = sz-1;
    for (ll i = 0; i < sz; i++) {
        arr.push_back(rand());
    }
    for (auto _ : state) {
        quickSort(arr, s, e);
    }
}

BENCHMARK(QuickSort);

static void StdSort(benchmark::State& state) {
    vector <int> arr;
    ll sz = 101001;
    ll s = 0, e = sz-1;
    for (ll i = 0; i < sz; i++) {
        arr.push_back(rand());
    }
    for (auto _ : state) {
        sort(arr.begin(), arr.end());
    }
}

BENCHMARK(StdSort);

BENCHMARK_MAIN();