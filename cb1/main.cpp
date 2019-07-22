#include <iostream>
#include<stdio.h>

using namespace std;
int main()
{
    int a[10],b[1000],c[3],z=0;
    for(int i=1,j=0;i<10;i++,j++)
    {
        a[j]=i;
    }
    for(int i=0;i<9;i++)
    {
        for(int j=i+1;j<9;j++)
        {
            for(int k=j+1;k<9;k++)
            {
                b[z]=a[i]*100+a[j]*10+a[k];
                //cout<<b[z]<<" ";
                b[z+1]=a[j]*100+a[k]*10+a[i];
                //cout<<b[z+1]<<" ";
                b[z+2]=a[k]*100+a[i]*10+a[j];
                //cout<<b[z+2]<<" ";
                z=z+3;
            }
        }
    }
    int count=0;
    for(int i=0;i<1000;i++)
    {
        //if(b[i]>100&&b[i]<=987)
            cout<<b[i]<<" ";
    }
    return 0;
}
