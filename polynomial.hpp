#include<iostream>
#include<cmath>
using namespace std;
class Polynomial{
    struct Term
    {
        int coefficinet;
        int power;
    };
    int size;
    int termCount;
    Term* terms;
public:
    Polynomial(){}
    Polynomial(int s){
        size=s;
        terms=new Term[size];
        termCount=0;
    }
    ~Polynomial(){
        delete [] terms;
    }
    int GetPowerIndex(int p){
        int low=0,high=termCount-1;
        while (low<=high)
        {
            int mid=(low+high)/2;
            if(terms[mid].power==p){
                return mid;
            }else if(terms[mid].power>p){
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return -1;
    }
    void AddTerm(int c,int p){
        int i=GetPowerIndex(p);
        if(i!=-1){
            terms[i].coefficinet+=c;
            return;
        }
        int j=termCount;
        while (terms[j-1].power<p&&j>=1)
        {
            terms[j]=terms[j-1];
            j--;
        }
        terms[j].power=p;
        terms[j].coefficinet=c;
        termCount++;
    }
    long long int calculateForX(int x){
        long long int sum=0;
        for (int i = 0; i < termCount; i++)
        {
            sum+=terms[i].coefficinet*(pow(x,terms[i].power));
        }
        return sum;
    }
    void Display(){
        for (int i = 0; i < termCount; i++)
        {
            if(terms[i].power!=0&&terms[i].coefficinet!=0){
                cout<<terms[i].coefficinet<<"x"<<terms[i].power;
                cout<<"+";
            }
        }
        cout<<endl;
    }
    Polynomial operator+(Polynomial& b){
        Polynomial c(this->size+b.size);
        int i=0,j=0,k=0;
        while (i<this->termCount&&j<b.termCount)
        {
            if(this->terms[i].power>b.terms[j].power){
                c.terms[k]=this->terms[i];
                k++;i++;
            }else if(this->terms[i].power<b.terms[j].power){
                c.terms[k]=b.terms[j];
                k++;j++;
            }else{
                c.terms[k]=this->terms[i];
                c.terms[k].coefficinet+=b.terms[j].coefficinet;
                k++;i++;j++;
            }
        }
        for (; i < this->termCount; i++)
        {
            c.terms[k]=this->terms[i];
            k++;
        }
        for (; j <b.termCount; j++)
        {
            c.terms[k]=b.terms[j];
            k++;
        }
        c.termCount=k;
        return c;
    }
};