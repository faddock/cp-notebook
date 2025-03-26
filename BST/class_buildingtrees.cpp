#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    vector<int> hasLeft(n, 0);
    vector<int> hasRight(n, 0);
    
    auto cmp = [&a](int i, int j) {
        return a[i] < a[j];
    };
    set<int, decltype(cmp)> bst(cmp);
    
    bst.insert(0);
    
    for (int i = 1; i < n; i++){
        auto it = bst.lower_bound(i);
        int rightParent = *it; 
        int leftParent = *prev(it);
        cout << i << " index, RightParent: " << rightParent << " Left parent: " << leftParent << "\n";
        if(it == bst.end()){
            hasRight[leftParent] = 1;
            cout << a[leftParent] << " (case 1) ";
        } else if(it == bst.begin()){
            hasLeft[rightParent] = 1;
            cout << a[rightParent] << " (case 2) ";
        } else {
            if(hasRight[leftParent] == 0){
                hasRight[leftParent] = 1;
                cout << a[leftParent] << " (case 3) ";
            } else {
                hasLeft[rightParent] = 1;
                cout << a[rightParent] << " (case 4) ";
            }
        }
        std::copy(hasLeft.begin(), hasLeft.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "hasLeft " << std::endl;
        std::copy(hasRight.begin(), hasRight.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "hasRight " << std::endl;
        bst.insert(i);
    }
    
    cout << "\n";
    return 0;
}
