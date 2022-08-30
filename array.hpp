#include<bits/stdc++.h>
#include<iostream>
class BetterArray{
private:
    int size;
    int length;
    int *data;
    void swap(int& x,int& y){
        static int v;
        v=x;
        x=y;
        y=v;
    }
///SORTING ALGORITHMS IMPLEMENTATIONS
    void BubleSortAscending(){
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length-i-1; j++)
            {
                if(data[j]>data[j+1]){
                    swap(data[j],data[j+1]);
                }
            }
        }
    }
    void BubleSortDescending(){
        for (int i = 0; i < length; i++)
        {
            for (int j = length-1; j >=i; j--)
            {
                if(data[j]<data[j+1]){
                    swap(data[j],data[j+1]);
                }
            }
        }
    }
    void QuickSortAscending(int left,int right){
        int mid=data[(left+right)/2];
        int i=left,j=right;
        do
        {
            while (data[i]<mid){i++;}
            while (data[j]>mid){j--;}
            if(i<=j){
                swap(data[i],data[j]);
                i++;j--;
            }
        }while(i<=j);
        if(i<right){
            QuickSortAscending(i,right);
        }
        if(j>left){
            QuickSortAscending(left,j);
        }
    }
    void QuickSortDescending(int left, int right){
        int mid=data[(left+right)/2];
        int i=left,j=right;
        while (i<j)
        {
            while (data[i]>mid){i++;}
            while (data[j]<mid){j--;}
            if(i<=j){
                swap(data[i],data[j]);
                i++;j--;
            }
        }
        if(i<right){
            QuickSortDescending(i,right);
        }
        if(j>left){
            QuickSortDescending(left,j);
        }
    }
    void MergeTwoSubArraysSorted(int s,int m,int e){
        int a1[m-s+1],a2[e-m];
        for (int i = 0; i < m-s+1; i++)
        {
            a1[i]=data[s+i];
        }
        for (int i = 0; i < e-m; i++)
        {
            a2[i]=data[m+i+1];
        }
        int i=0,j=0;
        int k=s;
        while (i<m-s+1&&j<e-m)
        {
            if(a1[i]>a2[j]){
                data[k]=a2[j];
                k++;j++;
            }else{
                data[k]=a1[i];
                k++;i++;
            }
        }
        for (; i < m-s+1; i++)
        {
            data[k]=a1[i];k++;
        }
        for (; j < e-m; j++)
        {
            data[k]=a2[j];k++;
        }
    }
    void MergeSortAscending(int start,int end){
        if(start>=end){
            return;
        }
        int mid=(start+end)/2;
        MergeSortAscending(start,mid);
        MergeSortAscending(mid+1,end);
        MergeTwoSubArraysSorted(start,mid,end);
    }

///END
public:
 ///SORTING ALGORITHMS DEFINITIONS
    void BubleSort(bool ascending=true){
        if(ascending)
            BubleSortAscending();
        else
            BubleSortDescending();
    }
    void QuickSort(bool ascending=true){
        if(ascending)
            QuickSortAscending(0,length-1);
        else
            QuickSortDescending(0,length-1);

    }
    void MergeSort(bool ascending=true){
        MergeSortAscending(0,length-1);
        if(!ascending){
            Reverse();
        }
    }
///END
    BetterArray(){}
    BetterArray(int s,bool heap=true){
        size=s;
        length=0;
        if(heap){
            data=new int[s];
        }else{
            int a[s];
            data=a;
        }
    } 
    BetterArray(const BetterArray &a){
        size=a.size;
        length=a.length;
        data=new int[size];
        for (size_t i = 0; i < length; i++)
        {
            data[i]=a.data[i];
        }
    }
    ~BetterArray(){
        delete [] data;
    }
    static BetterArray Concat(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        for (int i = 0; i < a1.length; i++)
        {
            a.PushBack(a1.Get(i));
        }
        for (int i = 0; i < a2.length; i++)
        {
            a.PushBack(a2.Get(i));
        }
        return a;
    }
    static BetterArray MergeSorted(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0,i=0,j=0;
        while (i<a1.length&&j<a2.length)
        {
            if(a1.data[i]<a2.data[j]){
                a.data[k]=a1.data[i];
                i++;k++;
            }else{
                a.data[k]=a2.data[j];
                j++;k++;
            }
        }
        for (; i < a1.length; i++)
        {
            a.data[k]=a1.data[i];
            k++;
        }
        for (; j < a2.length; j++)
        {
            a.data[k]=a2.data[j];
            k++;
        }
        a.length=a1.length+a2.length;
        return a;
    }
    static BetterArray Union(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0;
        for (int i = 0; i < a1.length; i++)
        {
            a.data[k]=a1.data[i];
            k++;
        }
        for (int i = 0; i < a2.length; i++)
        {
            bool isIn=false;
            for (int j = 0; j < a1.length; j++)
            {
                if(a1.data[j]==a2.data[i]){
                    isIn=true;
                    break;
                }
            }
            if(!isIn){
                a.data[k]=a2.data[i];
                k++;
            }
        }
        a.length=k;
        return a;
    }
    static BetterArray UnionSorted(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);

        int i=0,j=0,k=0;
        while (i<a1.length,j<a2.length)
        {
            if(a1.data[i]==a2.data[j]){
                a.data[k]=a1.data[i];
                k++;i++;j++;
            }else if(a1.data[i]>a2.data[j]){
                a.data[k]=a2.data[j];
                k++;j++;
            }else{
                a.data[k]=a1.data[i];
                k++;i++;
            }
        }
        for (; i < a1.length; i++)
        {
            a.data[k]=a1.data[i];
            k++;
        }
        for (; j < a2.length; j++)
        {
            a.data[k]=a2.data[j];
            k++;
        }
        a.length=k;
        return a;
    }
    static BetterArray Intersection(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0;
        for (int i = 0; i < a1.length; i++)
        {
            for (int j = 0; j < a2.length; j++)
            {
                if(a1.data[i]==a2.data[j]){
                    a.data[k]=a1.data[i];
                    k++;
                    break;
                }
            }
        }
        a.length=k;
        return a;
    }
    static BetterArray IntersectionSorted(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0,i=0,j=0;
        while (i<a1.length&&j<a2.length)
        {
            if(a1.data[i]==a2.data[j]){
                a.data[k]=a.data[i];
                k++;i++;j++;
            }else if(a1.data[i]<a2.data[j]){
                i++;
            }else{
                j++;
            }
        }
        a.length=k;
        return a;        
    }
    static BetterArray Difference(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0;
        for (int i = 0; i < a1.length; i++)
        {
            bool isIn=false;
            for (int j = 0; j < a2.length; j++)
            {
                if(a1.data[i]==a2.data[j]){
                    isIn=true;
                    break;
                }
            }
            if(!isIn){
                a.data[k]=a1.data[i];
                k++;
            }
        }
        a.length=k;
        return a;        
    }
    static BetterArray DifferenceSorted(BetterArray a1,BetterArray a2){
        BetterArray a=BetterArray(a1.size+a2.size);
        int k=0,i=0,j=0;
        while(i<a1.length&&j<a2.length){
            if(a1.data[i]==a2.data[j]){
                i++;j++;
            }else if(a1.data[i]<a2.data[j]){
                a.data[k]=a1.data[i];
                i++;k++;
            }else{
                j++;
            }
        }
        for (; i < a1.length; i++)
        {
            a.data[k]=a1.data[i];
            k++;
        }
        a.length=k;
        return a;
    }
    void Display(){
        for (int i = 0; i < length; i++)
        {
            std::cout<<data[i]<<" ,";
        }
        std::cout<<std::endl;
    }
    void FindMissing(){
        int start=0,end=0;
        for (size_t i = 0; i < length; i++)
        {
            if(data[i]>end){
                end=data[i];
            }
            if(data[i]<start){
                start=data[i];
            }
        }
        int hash[end-start];
        for (size_t i = 0; i < length; i++)
        {
            hash[data[i]-start]++;
        }
        for (size_t i = 0; i < end-start; i++)
        {
            if(hash[i]==0){
                std::cout<<i+start<<" ,";
            }
        }
        std::cout<<std::endl;
    }
    void FindDuplicates(){
        int start=0,end=0;
        for (size_t i = 0; i < length; i++)
        {
            if(data[i]>end){
                end=data[i];
            }
            if(data[i]<start){
                start=data[i];
            }
        }
        int hash[end-start];
        for (int i = 0; i < length; i++)
        {
            hash[data[i]-start]++;
        }
        for (int i = 0; i < end-start; i++)
        {
            if(hash[i]!=0){
                std::cout<<i+start<<" ocurres "<<hash[i]<<" times"<<std::endl;
            }
        }
    }
    int Length(){
        return length; 
    }
    int MaxSize(){
        return size;
    }
    void ChangeSize(int s){
        if(s<0||s==size){
            return;
        }
        int index=s;
        if(size<s){
            index=size;
        }
        int* handle=new int[s];
        for (int i = 0; i < index; i++)
        {
            handle[i]=data[i];
        }
        size=s;
        if(length>size){
            length=size;
        }
        delete [] data;
        data=handle;
    }
    int Get(int i){
        if(i>=0&&i>=size){
            return 0;
        }
        return data[i];
    }
    void Set(int i,int v){
        if(i>=0&&i>=size){
            return;
        }
    }
    int Max(){
        int m=INT_MIN;
        for (int i = 0; i < length; i++)
        {
            if(data[i]>m){
                m=data[i];
            }
        }
        return m;
    }
    int Min(){
        int m=INT_MAX;
        for (int i = 0; i < length; i++)
        {
            if(data[i]<m){
                m=data[m];
            }
        }
        return m;
        
    }
    int Sum(){
        int t=0;
        for (int i = 0; i < length; i++)
        {
            t+=data[i];
        }
        return t;
    }
    double Average(){
        return (double)Sum()/length;
    }
    void Insert(int index,int v){
        if(length>=size||index>length){
            return;
        }
        for (int i = length; i > index; i--)
        {
            data[i]=data[i-1];
        }
        length++;
        data[index]=v;
    }
    void PushBack(int v){
        if(length<size){
            data[length]=v;
            length++;
        }
    }
    void Delete(int index){
        if(index<0||index>=length){
            return;
        }
        for (int i = index; i < length-1; i++)
        {
            data[index]=data[index+1];
        }
        data[length]=0;
        length--;        
    }
    int IndexOf(int v){
        for (size_t i = 0; i < length; i++)
        {
            if(data[i]==v){
                return i;
            }
        }
        return -1;
    }
    int IndexOfSorted(int v){
        int low=0,high=length-1;
        while (low<high)
        {
            int mid=(low+high)/2;
            if(data[mid]==v){
                return mid;
            }
            else if(data[mid]>v){
                high=mid-1;
            }else{
                low=mid+1;
            }

        }
        return -1;
    }
    void Reverse(){
        int temp=0;
        for (int i = 0,j=length-1; i < j; i++,j--)
        {
            temp=data[i];
            data[i]=data[j];
            data[j]=temp;
        }
        
    }
    void Rotate(int amt){
        amt=amt%length;

        int* d2=new int[size];
        int index=0;
        for (int i = 0; i < length; i++)
        {
            index=i+amt;
            if(index>=length){
                index-=length;
            }else if(index<0){
                index+=length;
            }
            d2[index]=data[i];
        }
        delete [] data;
        data=d2;
    }
    void InsertSorted(int v){
        if(length+1==size){
            return;
        }
        int i=length-1;
        while (v<data[i]&&i>=0)
        {
            data[i+1]=data[i];
            i--;
        }
        data[i+1]=v;
        length++;
    }
    bool IsSorted(){
        for (int i = 1; i < length; i++)
        {
            if(data[i]<data[i-1]){
                return false;
            }
        }
        return true;
    }
    void PositivesToRight(){
        int i=0;
        int j=length-1;
        while (i<j)
        {
            while(data[i]<0){i++;}
            while(data[j]>=0){j--;}
            int t=data[i];
            data[i]=data[j];
            data[j]=t;
        }
    }
   
};
void testSorting(){
//     int elements=50000;
//     BetterArray a(elements);
//     srand((unsigned)time(NULL));
//     for (int i = 0; i < elements; i++)
//     {
//         a.PushBack(rand()%1000);
//     }
//     BetterArray a2=a;
//     BetterArray a3=a;
//    // std::cout<<a.IsSorted()<<std::endl;
//    // a.Display();

//     start=clock();
//     a.BubleSort();
//     stop=clock();
//     totalTime=(double)(stop-start)/CLOCKS_PER_SEC;
//     cout<<"Buble Sort: "<<totalTime<<endl;
//     cout<<a.IsSorted()<<endl;

//     start=clock();
//     a2.QuickSort();
//     stop=clock();
//     totalTime=(double)(stop-start)/CLOCKS_PER_SEC;
//     cout<<"Quick Sort: "<<totalTime<<endl;
//     cout<<a2.IsSorted()<<endl;


//     start=clock();
//     a3.MergeSort();
//     stop=clock();
//     totalTime=(double)(stop-start)/CLOCKS_PER_SEC;
//     cout<<"Merge Sort: "<<totalTime<<endl;
//     cout<<a3.IsSorted()<<endl;
}