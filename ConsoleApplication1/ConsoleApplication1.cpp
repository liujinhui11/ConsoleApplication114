#include <bits/stdc++.h>

using namespace std;

bool ck(string a) {
    if (a.size() == 1) return 1;
    //if (a.size() == 2) return 1;
    //if (a[0] != a[a.size() - 1]) return 0;
    string b = a;
    reverse(b.begin(), b.end());
    return b == a;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int now = 0;
        string t;
        cin >> t;
        //reverse(t.begin(), t.end());
        
        int lt = 0;
        while (lt <= t.size() - 1) {
            for (int j = t.size()-1; j >= lt; j--) {
                //cout << t.substr(lt, (j-lt+1)) << endl;
                if (ck(t.substr(lt, (j-lt+1)))) {
                    //cout << t.substr(lt, (j - lt+1)) << " y\n";
                    lt = j+1;
                    now++;
                    break;
                }
            }
        }

        int now1 = now;
        now = 0;

        reverse(t.begin(), t.end());

        lt = 0;
        while (lt <= t.size() - 1) {
            for (int j = t.size() - 1; j >= lt; j--) {
                //cout << t.substr(lt, (j-lt+1)) << endl;
                if (ck(t.substr(lt, (j - lt + 1)))) {
                    //cout << t.substr(lt, (j - lt + 1)) << " y\n";
                    lt = j + 1;
                    now++;
                    break;
                }
            }
        }

        cout << min(now,now1) << endl;
     }
    return 0;
}