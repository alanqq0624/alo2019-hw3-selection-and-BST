#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void print(vector<int> &in); // print whole vector. Using for testing
int selection(vector<int> &in, int p, int r, int k);
int partition(vector<int> &in, int p, int r, int pivot);
void insert_sort(vector<int> &in, int p, int r);

int k;

int main(int argc, char const *argv[])
{
    // init variable------------------------------------------------------------------------------
    ifstream fin;
    ofstream fout;
    int size, buffer, ans;
    vector<int> data;

    // get k which is the kth small element
    int k;
    if(argc != 2){
        cout << "Usage: ./mix_quick_insert_sort\n";
        return 1;
    }
    k = atoi(argv[1]);
    cout << "k: " << k << "\n";

    // open files ---------------------------------------------------------------------------------
    fin.open("input");
    if (!fin) {
        cout << "file in failed" << endl;
        return 0;
    }
    fout.open("output");
    if (!fout) {
        cout << "file in failed" << endl;
        return 0;
    }

    // get data from input file --------------------------------------------------------------------
    fin >> size;
    cout << "Size: " << size << endl;
    for(int i = 0; i < size; i++) {
        fin >> buffer;
        if (buffer == EOF) {
            cout << "file size error: " << buffer ;
            return 1;
        }
        data.push_back(buffer);
    }

    // pirnt raw data --------------------------------------------------------------------------------
    // cout << "raw:  ";
    // print(data);

    // sorting -------------------------------------------------------------------------------
    cout << k << "\n";
    ans = selection( data, 0, data.size()-1, k);

    // print sorted data --------------------------------------------------------------------------
    // cout << "sort: ";
    // print(data);

    // print out answer
    cout << "Answer: " << ans << "\n";

    // write sorted data to output file -----------------------------------------------------------
    fout << data.size() << endl;
    for(int i = 0; i < (int)data.size(); i++) {
        fout << data[i] << endl;
    }

    // end program stuff----------------------------------------------------------------------------
    fin.close();
    fout.close();
    return 0;
}

void print(vector<int> &in)
{
    for(int i = 0; i < (int)in.size(); i++) {
        cout << in[i] << " ";
    }
    cout << endl;
}

int selection(vector<int> &in, int p, int r, int k){
    cout << p << " " << r << " " << k << "\n";

    if( r-p+1 <= 5){
        insert_sort(in, p, r);
        return in[p+k-1];
    }

    int tmp;
    int target = p - 1;

    for(int i = p; i+5 < r; i += 5){
        insert_sort(in, i, i+4);

        //swap 
        tmp = in[++target];
        in[target] = in[i+2];
        in[i+2] = tmp;
    }

    int mid = p + (target-p) / 2;

    tmp = selection(in, p, target, mid);
    int q = partition(in, p, r, mid);

    int curr = q - p + 1;
    if (curr == k)
        return in[q];
    else if(curr > k)
        return selection(in, p, q-1, k);
    else if(curr < k)
        return selection(in, q+1, r, k-curr);
    else{
        cout << "selection() error\n";
        exit(EXIT_FAILURE);
    }
    
}


int partition(vector<int> &in, int p, int r, int pivot)
{

    //swap last(r) and pivot, let pivot to be the last one
    int tmp = in[pivot];
    in[pivot] = in[r];
    in[r] = tmp;

    int x = in[r];
    int i = p - 1;

    for(int j = p; j < r; j++) {
        if( in[j] <= x) {
            i++;

            // swap in[i] in[j]
            tmp = in[i];
            in[i] = in[j];
            in[j] = tmp;
        }
    }
    tmp = in[i+1];
    in[i+1] = in[r];
    in[r] = tmp;

    return i+1;
}

void insert_sort(vector<int> &in, int p, int r)
{
    for(int i = p; i < r; i++) {
        int key = in[i];

        // insert target into queue
        int j = i - 1;
        while(i >= 0 && in[j] > key) {
            in[j+1] = in[j];
            j--;
        }

        in[j+1] = key;

    }

}