#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void print(vector<int> &in); // print whole vector. Using for testing
int selection(vector<int> &in, int p, int r, int k);
int partition(vector<int> &in, int p, int r, int pivot);
void insert_sort(vector<int> &in, int p, int r);

int k_in;

int main(int argc, char const *argv[])
{
    // init variable------------------------------------------------------------------------------
    ifstream fin;
    ofstream fout;
    int size, buffer, ans;
    vector<int> data;

    // get k which is the kth small element
    if(argc != 2){
        cout << "Usage: ./selection k\n";
        return 1;
    }
    k_in = atoi(argv[1]);
    cout << "k: " << k_in << "\n";

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
    ans = selection( data, 0, data.size()-1, k_in);

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

    //if input is not enough 5, then do insert-sort and return median directly
    if( r-p+1 <= 5){
        insert_sort(in, p, r);

        // when using selection() to find median may cause an error of p+k-1 is too large
        // this is cause by different meaning of k when different using
        // but using selection() to find median actually don't need return value so we just let it return 0
        if(p+k-1 >= k_in){
            return 0;
        }
        return in[p+k-1];
    }

    int tmp;
    int target = p - 1; // index where to put median

    for(int i = p; i+5 < r; i += 5){
        insert_sort(in, i, i+4);

        //swap median to the front
        tmp = in[++target];
        in[target] = in[i+2];
        in[i+2] = tmp;
    }

    // using selection() to find median recursively
    // median here will all at the head of data list
    // Be aware of that selection 4'th parameter "k" pass by "mid" will be the actually position where median place
    int mid = p + (target-p) / 2;
    tmp = selection(in, p, target, mid);

    // using median as pivot to do partition
    int q = partition(in, p, r, mid);

    // using selection() to reduce (3/10)*n data recursively
    // Be aware of that selection 4'th parameter "k" pass by "mid" will be the target k to find for answer
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
    for(int i = p+1; i <= r; i++) {
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