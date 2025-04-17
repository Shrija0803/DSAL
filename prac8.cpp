#include <iostream>
using namespace std;
#define SIZE 20
class optimal {
public:
int p[SIZE];
int q[SIZE];
int a[SIZE];
int w[SIZE][SIZE];
int c[SIZE][SIZE];
int r[SIZE][SIZE];
int n;
int front, rear, queue[2 * SIZE];
optimal() {
front = rear = -1;
}
void getdata();
int minvalue(int, int);
void OBST();
void buildtree();
};
void optimal::getdata() {
cout << "\nOptimal binary search tree";
cout << "\nEnter the number of nodes: ";
cin >> n;
cout << "\nEnter the data:\n";
for (int i = 1; i <= n; i++) {
cout << "\na[" << i << "]: ";
cin >> a[i];
}
cout << "\nEnter the probabilities for successful search\n";
for (int i = 1; i <= n; i++) {
cout << "p[" << i << "]: ";
cin >> p[i];
}cout << "\nEnter probabilities for unsuccessful search\n";
for (int i = 1; i <= n; i++) {
cout << "q[" << i << "]: ";
cin >> q[i];
}
}
int optimal::minvalue(int i, int j) {
int min = 32000, k, m;
for (m = r[i][j - 1]; m <= r[i + 1][j]; m++) {
if ((c[i][m - 1] + c[m][j]) < min) {
min = c[i][m - 1] + c[m][j];
k = m;
}
}
return k;
}
void optimal::OBST() {
int i, j, k, m;
for (i = 0; i < n; i++) {
w[i][i] = q[i];
c[i][i] = 0;
r[i][i] = 0;
w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
r[i][i + 1] = i + 1;
c[i][i + 1] = w[i][i + 1];
}
w[n][n] = q[n];
c[n][n] = 0;
r[n][n] = 0;
for (m = 2; m <= n; m++) {
for (i = 0; i <= n - m; i++) {
j = i + m;
w[i][j] = w[i][j - 1] + p[j] + q[j];
k = minvalue(i, j);
c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
r[i][j] = k;
}
}
}
void optimal::buildtree() {
int i, j, k;
cout << "\nThe optimal binary search tree for given nodes is:\n";
cout << "\nThe root of this OBST is: " << r[0][n];
cout << "\nThe cost of this OBST is: " << c[0][n];
cout << "\n\nNode \t Left child \t Right child";cout <<
"\n___________________________________________________________________________"
<< endl;
queue[++rear] = 0;
queue[++rear] = n;
while (front != rear) {
i = queue[++front];
j = queue[++front];
k = r[i][j];
cout << "\n\t" << k;
if (r[i][k - 1] != 0) {
cout << " " << r[i][k - 1];
queue[++rear] = i;
queue[++rear] = k - 1;
} else {
cout << " ";
}
if (r[k][j] != 0) {
cout << " " << r[k][j];
queue[++rear] = k;
queue[++rear] = j;
} else {
cout << " ";
}
}
cout << endl;
}
int main() {
optimal obj;
obj.getdata();
obj.OBST();
obj.buildtree();
return 0;
}
