#include<iterator>
#include<vector>
#include<algorithm>
#include<iostream>
#include<map>
#include<unordered_map>

using namespace std;


struct Dog{
    Dog(int age,double weight):
        m_age(age),
        m_weight(weight)      
    {

    }

    // for sorting according to weight in ascending order
    bool operator<(const Dog&right){
        return this->m_weight < right.m_weight;
    }

    int m_age;
    double m_weight;
};

struct sortByAgeFunctor{
    bool operator()(const Dog&lhs, const Dog&rhs){
        return lhs.m_age<rhs.m_age;
    }
};


struct findDogByWeight{
    findDogByWeight(double weight)
        :m_weight(weight)
    {

    }

    bool operator()(const Dog & d1){
        return this->m_weight == d1.m_weight;
    }
    double m_weight;
};

int percentageLetter(string s, char letter) {
    int cnt = 0;
    int len = s.size();
    for_each(begin(s),end(s),[&cnt,letter](char ch){
        if(ch==letter)
            cnt++;
    });

    return cnt*100/len;
}

int main(){
    vector<Dog> v = {Dog(10,50) , Dog(2,10) , Dog(11,55) , Dog(8,45) , Dog(7,60) , Dog(12,64)};
    sort(begin(v),end(v));
    sort(begin(v),end(v),sortByAgeFunctor());
    
    
    Dog d1 = {5,34};
    Dog d2 = {4,45};
    bool isLess = d1 < d2;
    bool isLess2 = d1.operator<(d2);
    
    // isLess is syntatic sugar for isLess2
    // similarly lamda is syntactic de-sugar for functor

    vector<int> v2 = {12,34,-90,21,45,-100,0,56};
    sort(begin(v2),end(v2),[](const int& lhs, const int& rhs){
        return lhs<rhs; // ascending order => right side element should be greater
    });
    
    // In above lamda function,
    /*
        [] = capture list // similar to parameter of constructor in functor
             this is used if we need to use some variable from outside of lamda scope
             It can also be th memeber of functor. e.g find dog by weight 55  
        () = parameter list //parameter of functor. In above Dog example , it was Dog obj lhs and rhs 
        {} = body of lamda function
    */ 
    
    vector<Dog>::iterator itr = find_if(begin(v),end(v),findDogByWeight(55));
    if(itr==v.end()){
        cout<<"Not found\n";
    }else{
        cout<<"Found\n";
    }

    //same can be done with lamba
    int weight = 55;
    itr = find_if(begin(v),end(v),[weight](const Dog*d){
        return d->m_weight == weight;
    });

    //e.g => sort vector according to frequency 
    v2 = {1,1,1,1,3,2,2,4,1,5,6,3,1,2,9,9,5};
    unordered_map<int,int> freq;
    for(int num : v2){
        freq[num]++;
    }

    //Now we need this freq map for sorting v2.
    //we can pass this freq map in capture list of lamda function
    sort(begin(v2),end(v2),[&freq](const int lhs,const int rhs){
        if(freq[lhs] == freq[rhs])
            return lhs<rhs;
        else
            return freq[lhs]>freq[rhs];
    });

    /*
    Few capture list 
        [=] : everything by value
        [&] : everything by reference
        []  : nothing captured

    */


    //e.g return the list of number greater than num
    int num = 30;
    vector<int> res;
    v2 = {10,23,34,45,9,29,56,90,75,30,55,78,18,12,7,9,15,26};
    //capture num by value and res by reference 
    for_each(begin(v2),end(v2),[num,&res](const int v2_elem){
        if(v2_elem>num)
        {
            res.push_back(v2_elem);
        }
    });

    
    for(int n : res){
        cout<<n<<" ";
    }
    cout<<"\n";

    return 0;
}
