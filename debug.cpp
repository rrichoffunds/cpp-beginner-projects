#include <iostream>
using namespace std;
int main()
{
    int i = 0;
    for (; i < 3; i++)
    {
        int times = i + 1;
        cout << "Display \"Hello World\" for the " << times << " times" << endl;
    }
    cout << i << endl;
    return 0;
}
