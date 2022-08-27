#include<iostream>
#include<iomanip>
#include<random>
#include<ctime>
#include "mysin.h"

double test_min=0;
double test_max=PI/2;
std::random_device seed;
std::ranlux48 engine(seed());
std::uniform_real_distribution<> distrib(test_min,test_max);
std::time_t begin,end;

struct testfunc_t{
    double (*fn)(double)=nullptr;
    std::string name="";
    testfunc_t(double (*fn_)(double),const char* name_){
        fn=fn_;
        name=name_;
    };
};

int main(){
    //init
    unsigned short test_times;
    double (*testFunc)(double)=nullptr;
    std::string testFuncName="";
    #define test_func_count 6
    testfunc_t testfns[test_func_count]={
        testfunc_t(sin,"std"),
        testfunc_t(mySin1,"half"),
        testfunc_t(mySin2,"lookup"),
        testfunc_t(mySin3,"fit"),
        testfunc_t(mySin4,"triple"),
        testfunc_t(mySin5,"taylor"),
    };
    //config
    std::cout<<"Please input which function to test;\n";
    std::cout<<"Names of functions are shown below, please input one;\n";
    for(unsigned char i=0;i<test_func_count;++i) std::cout<<' '<<testfns[i].name;
    std::cout<<'\n';
    std::cin>>testFuncName;
    for(unsigned char i=0;i<test_func_count;++i) if(testFuncName==testfns[i].name) testFunc=testfns[i].fn;
    if(!testFunc){
        std::cout<<testFuncName<<": Function not found!\n";
        goto finish;
    };
    std::cout<<"Please input the times to test a function;\n";
    std::cin>>test_times;
    if(!std::cin.good()){
        std::cout<<"Illegal test times!\n";
        goto finish;
    };
    //generate data for testing
    double* test_data= new double[test_times];
    for(unsigned short i=0;i<test_times;++i) test_data[i]=distrib(engine);
    std::cout<<"Initialization completed;\n";
    //start test
    begin=clock();
    for(unsigned short i=0;i<test_times;++i) testFunc(test_data[i]);
    //end test
    end=clock();
    //output results
    std::cout<<"Altogether "<<test_times<<" samples, total time used: "<<end-begin<<" ms;\n";
    std::cout<<std::setprecision(2)<<(float)(end-begin)/test_times<<" ms per sample on average;\n";
    finish:
    system("pause");
    return 0;
}

/* 
以下哪些行为是违法犯罪行为？
A.污染整个地区的DNS请求，返回无效IP
b.在主干网上进行劫持，对特定网站发起HTTPS MITM攻击
c.篡改HTTP响应并插入攻击脚本，对特定网站发起DDos攻击
d.使用多线程下载百度云
 */