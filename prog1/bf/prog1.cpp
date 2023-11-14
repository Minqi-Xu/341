#include <iostream>

using namespace std;

void my_mergesort(int l, int r, int* d[], int* h[], int* idex[]) {
    // base case: return if length of array is 1
    if(l == r)  return;

    int mid = (l + r) / 2;

    my_mergesort(l, mid, d, h, idex);
    my_mergesort(mid + 1, r, d, h, idex);
    int temp1[100001], temp2[100001], temp3[100001];   // temp arrays store the merged array
    int ll = l, rr = mid + 1, counter = l;
    while(counter <= r) {
        if(ll > mid) {
            temp1[counter] = (*d)[rr];
            temp2[counter] = (*h)[rr];
            temp3[counter] = (*idex)[rr];
            counter++;
            rr++;
        }
        else if(rr > r) {
            temp1[counter] = (*d)[ll];
            temp2[counter] = (*h)[ll];
            temp3[counter] = (*idex)[ll];
            counter++;
            ll++;
        }
        else if((*h)[ll] < (*h)[rr]) {
            temp1[counter] = (*d)[rr];
            temp2[counter] = (*h)[rr];
            temp3[counter] = (*idex)[rr];
            counter++;
            rr++;
        }
        else if((*h)[ll] > (*h)[rr]) {
            temp1[counter] = (*d)[ll];
            temp2[counter] = (*h)[ll];
            temp3[counter] = (*idex)[ll];
            counter++;
            ll++;
        }
        else {  // (*h)[ll] = (*h)[rr], this time need sort them with (*d)[] in non-decrease order
            if((*d)[ll] < (*d)[rr]) {
                temp1[counter] = (*d)[ll];
                temp2[counter] = (*h)[ll];
                temp3[counter] = (*idex)[ll];
                ll++;
            } else {
                temp1[counter] = (*d)[rr];
                temp2[counter] = (*h)[rr];
                temp3[counter] = (*idex)[rr];
                rr++;
            }
            counter++;
        }
    }

    // copy the temp array into h[] and d[]
    for (int i = l; i <= r; ++i) {
        (*d)[i] = temp1[i];
        (*h)[i] = temp2[i];
        (*idex)[i] = temp3[i];
    }

}

int main() {

    // initialize variables
    int n;  // number of trials
    scanf("%d", &n); // input n from stdin

    int d[100001];  // d[] in the problem stated
    int h[100001];  // h[] in the problem stated
    int* dd = d;    // dd stores the address of d[]
    int* hh = h;    // hh stores the address of h[]
    int idex[100001];  // idex[] store the initial index of trials
    int* iid = idex;    // iid stores the address of idex[]
    long long tot_h = 0;    // total happiness
    bool isOccupy[100001];  // isOccupy[i] store the state of day i, day i is scheduled => isOccupy[i] = true
    int schedule[100001];   // schedule[i] stores the scheduled trial on day i

    // initialize isOccupy
    for(int i = 0; i < 100001; ++i) {
        isOccupy[i] = 0;    // initialize the isOccupty[]
        idex[i] = i;    // initialize the idex[]
        schedule[i] = -1;   // initialize the schedule[]
    }

    // input d[] from stdin
    for(int i = 1; i <= n; ++i)
        scanf("%d", &d[i]);
    // input h[] from stdin
    for(int i = 1; i <= n; ++i)
        scanf("%d", &h[i]);
    // sort trials based on happiness of each trial in the non-increase order
    // if reach two identical happiness, sort by the corresponding d[] in the non-decrease order
    my_mergesort(1, n, &dd, &hh, &iid);
    // traverse the trials, and do the greedy algorithm
    for(int i = 1; i <= n; ++i) {
        if(!isOccupy[d[i]]) {   // if day d[i] is available, then choose to go current trial on day d[i]
            isOccupy[d[i]] = 1;
            schedule[d[i]] = idex[i];
            tot_h += h[i];
        } else {                // otherwise, find another day that is as late as possible to schedule the current trial
            for(int j = d[i] - 1; j > 0; j--) {
                if(!isOccupy[j]) {  // if the day is found, then schedule the day with current trial
                    isOccupy[j] = 1;
                    schedule[j] = idex[i];
                    tot_h += h[i];
                    break;
                }
            }
        }
    }

    // do the output
    cout << tot_h << endl;
    for(int i = 1; i < n; ++i)
        printf("%d ", schedule[i]);
    cout << schedule[n] << endl;

    return 0;
}
