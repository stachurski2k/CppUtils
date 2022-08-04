template<typename  T>// swap int data with T to be done
class BetterArray{
private:
    int size;
    int length;
    int *data;
public:
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
    int At(int i){
        if(i>=size){
            return 0;
        }
        return data[i];
    }
    void PushBack(int v){
        if(size==length){
            return;
        }
        data[length]=v;
        length++;      
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
};