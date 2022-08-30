#include<iostream>

using namespace std;
class Matrix{
    public:
    virtual void Init(int n){}
    virtual void Set(int v, int x,int y){}
    virtual void Display(){}
    virtual int Get(int x,int y){return 0;}
};
class DiagonalMatrix:Matrix{
private:
    int size;
    int *data;
public:
    virtual void Init(int n){
        size=n;
        data=new int[size];
    }
    virtual void Set(int v, int x,int y){
        if(x==y){
            data[x]=v;
        }
    }
    virtual void Display(){}
    virtual int Get(int x,int y){
        if(x==y){
            return data[x];
        }
        return 0;
    }
};
class YTriangularMatrix:Matrix{     // 1 0 0
                                    // 3 1 0
                                    // 2 3 3
private:
    int size;
    int *data;
    int dataLen;
public:
    virtual void Init(int n){
        size=n;
        dataLen=((n)*(n+1))/2;
        data=new int[dataLen];
    }
    virtual void Set(int v, int x,int y){
        if(y>=x){
            data[(y*(y+1)+x)]=v;
        }
    }
    virtual void Display(){}
    virtual int Get(int x,int y){
        if(y>=x){
            return data[(y*(y+1)+x)];
        }else {
            return 0;
        }
    }
};
class XTriangularMatrix:Matrix{     // 1 3 2
                                    // 0 1 2
                                    // 0 0 3
private:
    int size;
    int *data;
    int dataLen;
public:
    virtual void Init(int n){
        size=n;
        dataLen=((n)*(n+1))/2;
        data=new int[dataLen];
    }
    virtual void Set(int v, int x,int y){
        if(y<=x){
            data[(x*(x+1)/2+y)]=v;
        }
    }
    virtual void Display(){}
    virtual int Get(int x,int y){
        if(y<=x){
            return data[(x*(x+1)/2+y)];
        }else {
            return 0;
        }
    }
};
class TriDiagonalMatrix:Matrix{
private:
int size;
int dataLen;
int* data;
public:
    virtual void Init(int n){
        dataLen=3*n-2;
        size=n;
        data=new int[dataLen];
    }
    virtual void Set(int v, int x,int y){
        if(x-y==-1){
            data[x]=v;
        }else if(x-y==0){
            data[size-1+x]=v;
        }else if(x-y==1){
            data[2*size-1+y]=v;
        }
    }
    virtual void Display(){}
    virtual int Get(int x,int y){
        if(x-y==-1){
           return data[x];
        }else if(x-y==0){
           return data[size-1+x];
        }else if(x-y==1){
           return data[2*size-1+y];
        }
        else{
            return 0;
        }
    }

};
class ToeplitzMatrix:Matrix{
private:
int size;
int dataLen;
int *data;
public:
    virtual void Init(int n){
        dataLen=2*n-1;
        size=n;
        data=new int[dataLen];
    }
    virtual void Set(int v, int x,int y){
        if(x>=y){
            data[x-y]=v;
        }else{
            data[size+y-x]=v;
        }
    }
    virtual void Display(){}
    virtual int Get(int x,int y){
        if(x>=y){
            return data[x-y];
        }else{
            return data[size+y-x];
        }
    }
};
class SparseMatrix:Matrix{// 0 0 0
                          // 0 1 2
                          // 0 0 3
    
    struct Element{
        int x,y,v;
    };
    int size;
    int elementCount;
    Element* data=nullptr;
public:
    SparseMatrix(){

    }
    ~SparseMatrix(){
        if(data!=nullptr)
            delete [] data;
    }
    SparseMatrix operator+(SparseMatrix &b){
        SparseMatrix c=SparseMatrix();
        c.Init(this->size);
        int i=0,j=0,k=0;
        while (i<this->elementCount&&j<b.elementCount)
        {
            if(this->data[i].x<b.data[j].x){
                c.data[k]=this->data[i];
                i++;k++;
            }else if(this->data[i].x>b.data[j].x){
                c.data[k]=b.data[j];
                j++;k++;
            }else{
                if(this->data[i].y<b.data[j].y){
                    c.data[k]=this->data[i];
                    i++;k++;
                }else if(this->data[i].y>b.data[j].y){
                    c.data[k]=b.data[j];
                    j++;k++;
                }else{
                    c.data[k]=this->data[i];
                    c.data[k].v+=b.data[j].v;
                    k++;i++;j++;
                }
            }
        }
        for (; i<this->elementCount; i++)
        {
            c.data[k]=this->data[i];
            k++;
        }
        for (; j<b.elementCount; j++)
        {
            c.data[k]=b.data[j];
            k++;
        }
        c.elementCount=k;
        return c;
    }
    int IndexOfCord(int x,int y){
        int low=0,high=elementCount-1;
        while (low<=high)
        {
            int mid=(low+high)/2;
            if(data[mid].x==x&&data[mid].y==y){
                return mid;
            }
            else if(data[mid].x==x){
                if(data[mid].y>y){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }else{
                if(data[mid].x>x){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }
        }
        return -1;
    }
    virtual void Init(int n){
        size=n;
        data=new Element[size*size];
        elementCount=0;
    }
    virtual void Set(int v, int x,int y){
        int i=IndexOfCord(x,y);
        if(i!=-1){
            data[i].v=v;
            return;
        }
        int j=elementCount;
        while (data[j].x>x||(data[j].y>y&&data[j].x==x))
        {
            data[j]=data[j-1];
            j--;
        }
        data[j].x=x;
        data[j].y=y;
        data[j].v=v;
        
        elementCount++;
    }
    virtual void Display(){
        int k=0;
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if(k<elementCount&&data[k].x==x&&data[k].y==y){
                    cout<<data[k].v<<" ";
                    k++;
                }else {
                    cout<<"0 ";
                }
            }
            cout<<endl;
        }
    }
    virtual int Get(int x,int y){
        int i=IndexOfCord(x,y);
        if(i!=-1){
            return data[i].v;
        }
        return 0;
    }
};