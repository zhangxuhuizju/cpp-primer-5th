# <center>C++ primer 阅读笔记</center>
## 前言 
&ensp;最近重新开始看c++ primer这本书，写点笔记，也为了以后复习和找工作吧...

## chapter1
&ensp;第一章没啥好写的，就讲了c++的一些基础，快速浏览了一下

## chapter2

### <center>c++ 类型表</center>

类型  |  含义  |  最小尺寸
-|-|-
bool | 布尔 | undefined
char | 字符 | 8位
w_char | 宽字符 | 16位
char16_t | unicode字符 | 16位
char32_t | unicode字符 | 32位
short | 短整形 | 16位
int | 整形 | 16位
long | 长整形 | 32位
long long | 长整形 | 64位
float | 单精度浮点数 | 6位有效数字
double | 双精度浮点数 | 10位有效数字
long double | 扩展精度浮点数 | 10位有效数字

&ensp;其中需要注意的是char类型，有char、signed char和unsigned char三种定义类型。但是字符的表现则只有两种（无符号和有符号的），具体是哪一种由编译器决定

### 类型转换     
```c++
bool b = 42; //b is true
int i = b; //i = 1
i = 3.14; //i=3
double pi = i; //pi=3
unsigned char c = -1; //c=255
signed char c2 = 256; //undefined
```
+ bool = (value == 0) ? false : true
+ value = (bool) ? 1 : 0
+ float to int, only save the interger part
+ 赋予无符号数的数值大于表示范围时，取mod操作
+ 赋予有符号数的数值大于表示范围时，结果是 **未定义**
+ 既有signed 又有unsigned时会转化成unsigned，此时容易造成错误，尽量不要混用两者

### 指定字面值的类型
```c++
L'a' //wchar_t
u8"hi!" //utf-8字符串字面值
42ULL //unsigned long long
1E-3F //float
3.14159L //long double
```
+ 规范使用L表示long以免和数字1混淆

||指定字面值的类型||
-|-|-
前缀|含义|类型
u | unicode16 | char16_t
U | unicode32 | char32_t
L | 宽字符 | wchar_t
||**整形字面值**||
后缀||最小匹配类型
u or U || unsigned
l or L || long
ll or LL || long long
||**浮点型字面值**||
f or F || float
l or L || long double


### 变量初始化
+ c++里的初始化比较复杂，赋值和初始化是不同的，注意区别，后续章节将反复出现各类初始化

初始化的几种类型：
```C++
int units_sold = 0;
int units_sold = {0};
int units_sold(0);
int units_sold{0};
```
C++ 11的新标准使得可以全面用{}来初始化，称为**列表初始化**。该类初始化有一个特点：如果初始值存在丢失信息的风险，编译器会报错

```C++
long double ld = 3.1415926536;
int a{ld}, b = {ld}; //error:转化未执行，存在信息丢失的风险
int c(ld), d = ld; //正确，转化执行，并且确实丢失了部分值
```
默认初始化：在函数外部则一般初始化为0，内部则**不被初始化**     

### 变量声明和定义
```C++
extern int i; //声明变量i
int j; //声明并定义变量j ！！！
extern double pi = 3.14; //定义，不允许写在函数体内部
```
+ 声明让名字为程序所指，定义负责创建和名字关联的实体
+ 声明规定变量的类型和名字，定义在此基础上申请存储空间并且还可能赋初始值
+ 加extern关键字并且不显示初始化变量表示一个申明
+ 函数内部不允许初始化extern标记的变量
+ 变量可以申明多次，但只能定义一次

### 标识符
C++不允许用户自定义标识符出现连续的两个下划线，也不允许下划线紧连大写字母开头。此外，函数体外的标识符不能以下划线开头！

变量命名规范
+ 标识符要能体现含义
+ 变量名一般用小写，如index
+ 类名用大写字母开头，如Sales_item
+ 标识符用多个单词组成，需要显示隔开，如student_loan或studentLoan

### 引用
一般说的引用指的是左值引用    
引用不是对象，是给已存在的对象起了另一个名字    
引用不能重新绑定到其他对象，在初始化的时候就需要绑定好。不能定义引用的引用
```C++
//some examples of reference
int ival = 1024;
int &refVal = ival; //refVal refer to the ival
int &refVal2; //error! reference must be initilized

//error! the initial value of the reference must be a object
int &refVal3 = 10; 
double dval = 3.14;
int &refVal4 = dval; //error! type must be the same!
```

### 指针
指针和引用区别：
+ 指针本身是一个对象，允许对指针赋值和拷贝，可以修改指针指向的对象
+ 指针无需在定义的时候赋值，如果不赋值，则其初始值和其他变量初始化的结果一样，为0（在快块作用域外）或未定义（块作用域内）

空指针：
```C++
int *p1 = nullptr;
int *p2 = 0;
int *p3 = NULL;
```
上面三种方法都定义了一个空指针，其中nullptr是C11的新引入方法    
但是，以下方式是错误的
```C++
int zero = 0;
int *pi = zero; //error! 不能把int变量赋值给指针，即便变量的值为0
```
void*指针    
void*是一种特殊的指针，可以存放任何对象的地址，可以与别的指针进行比较，作为函数的输入或输出，或者赋值给另一个void*指针。但无法对其指向的对象进行操作，因为不知道指向的具体类型是什么

指向指针的引用
```C++ 
int *&r;
```
对于r的表示，**从右到左**进行理解。&对r最有影响，表示r是一个引用。其余部分表示r引用的是什么。*表明r引用的是一个指针，int表明这个指针指向int类型

### const限定符
const修饰符修饰的变量值不能进行更改
```C++
const int bufSize = 512;
bufSize = 512; // error! the const value can not be modifed

const int i = get_size(); //运行时初始化
const int j = 42;  //编译时初始化
const int k; //error！ k没有被初始化！
```
默认状态下，const对象仅在文件内有效。多个文件中出现同名的const时，认为在不同文件中分别定义了独立的变量。如果需要在不同文件中都用同一个const，那么在所有的同名const变量前加上extern关键字，其中只需要定义一次，不需要每个const变量都初始化。

const的引用
```C++
const int ci = 1024;
const int &r1 = ci; //引用和对用的对象都是常量，正确
r1 = 42; //error
int &r2 = ci; //error！ 非常量的引用不能指向常量对象
```
如果上文中r2可以初始化，则可以通过r2来改变引用对象的值，这显然会出错！

常量引用绑定到另一个类型上发生了以下的操作：
```C++
double dval = 3.14;
const int &ri = dval;

//上述语句做了以下的事情
const int temp = dval;
const int &ri = temp;
```
ri绑定的是一个**临时量**对象，如果ri是常量，那么这样的绑定是没有问题的，因为不需要改变临时量对象的值。但是ri不是常量的时候，即ri要改变绑定的对象的值，否则绑定没有意义，那么去改变一个临时量对象也是没有意义的，因此不允许普通的引用绑定到临时量对象上。

const引用的本质是不能利用改引用来改变绑定的对象的值，因此const引用可以绑定到非const的对象上。例如：
```C++
int i = 10;
const int &i1 = i;
int &i2 = i;
//i1 = 0; error! 不允许const引用来改变绑定对象
i2 = 0;
cout << i1 << endl; //输出0
```
### 指针和const
**指向常量的指针**不能用于改变其所指向对象的值。如果要存放常量对象的地址，必须使用指向常量的指针
```C++
const double pi = 3.14;
double *ptr = &pi; //error! ptr is not a const point
const double *cptr = &pi;
*cptr = 42; //error!
```
指向常量的指针允许指向一个非常量的对象，但是不能通过指针改变对象的值

const指针
指针是对象，因此允许把指针本身定为常量。*放在const之前表示指针是一个常量，即不变的是指针本身的值，而不是指针指向的那个值
```C++
int errNum = 0;
int *const curErr = &errNum; //curErr一直指向errNum

const double pi = 3.14;
const double *const pip = &pi; //pip是指向常量对象的常量指针
```
与前面所学内容一样，用从右到左的分析方法分析具体含义即可

**顶层const**：指针本身是个常量    
**底层const**：指针指向的对象是个常量

顶层const的拷贝不受限制，但是底层const的拷贝必须要求有相同的底层const资格

**常量表达式**：值不会改变并且编译过程就可以得到计算结果的表达式
```C++
const int max_files = 20; //max_files is constexpr
const int limit = max_files + 1; //limit is constexpr
int staff_size = 27; //staff_size is not constexpr
const int sz = get_size(); //sz is not constexpr
```
上例中，get_size()的值要在运行时才能确定，因此sz不是常量表达式

C11规定，允许把变量申明为**constexpr**让编译器检查变量值是否为常量表达式
```C++
constexpr int mf = 20;
constexpr int limit = mf + 1;
//only correct when size() is a constexpr function
constexpr int sz = size();
```
constexpr类型的指针必须是nullptr或者是0，或者是某个固定地址中的对象

在constexpr声明中定义了指针，constexpr只对指针有效，与所指对象无关
```C++
const int *p = nullptr;  //p is a pointer point to a const integer
constexpr int *q = nullptr; //q is a const pointer point to a integer
```
### 类型别名
两种方法定义类型别名
+ typedef
+ C11规定的别名声明
```C++
typedef double wages; //wages is the synonym of double
typedef wages base, *p; //base is the synonym of double, *p of double*

using SI = Sales_item; //the same as typedef
```
**指针、常量和类型别名**
```C++
typedef char *ptr;
const ptr cstr = 0; //cstr is a const pointer point to char
//ps is a pointer, point to a const pointer, which point to char
const ptr *ps;

const char *cstr = 0; //cstr is a pointer point to const char
```
注意typedef后的区别，不能简单用替换前的部分改写声明来进行类型判断

**auto**：使用较为简单，其中需要注意的一点是auto一般会忽略顶层const，保留底层const
```C++
const int ci = i, &cr = ci;
auto b = ci; //b is a int, ignore the top-level const of ci
auto c = cr; //cr is a int
auto d = &i; //d is a int poniter
//e is a pointer point to const int, cannot ignore the buttom-level const 
auto e = &ci; 

//if we want to get a top-level const, we can write as:
const auto f = ci;

auto &g = ci;
auto &h = 42; //error! h is not a const reference!
const auto &j = 42;

auto &n = i, *p = &ci; //error! i is a int but ci is a const int.
```
**decltype**:与auto不同在于，会把顶层const也包含在内
```C++
const int ci = 0, &cj = ci;
decltype(ci) x = 0;  //x is a const int
decltype(ci) y = x; //y is a const int
decltype(ci) z; //error! z is a reference, must be initialized!
```
一般而言，引用都是作为其指向对象的同义词，但是decltype是个例外。如：
```C++
int i = 0, *p = &i;
decltype(*p) c; //error! c is a int &, must be initialized!

decltype((i)) d; //error! d is int &
decltype(i) e; //e is int
```
*p是解引用操作，得到指针指向的对象，则decltype判断该表达式是引用    
此外，在变量外加一层括号，编译器会将其作为表达式，此时decltype将其解析为引用！！！

## Chapter3
### 命名空间using声明
using声明格式：
```C++
using namespace::name;
```
需要注意的是，头文件不应该包含using声明，因为头文件内容会拷贝到所有引用他们的文件中，则这些文件都会using声明，可能会产生冲突

### 标准库string
||string对象初始化的方式|
-|-
string s1 | 默认初始化，s1为空
string s2(s1) | s2是s1的副本
string s2 = s1 | 等价于string s2(s1)
string s3("value") | s3是字面值为“value”的副本
string s3 = “value" | 等价于string s3("value")
string s4(n, 'c') | s4初始化为n个字符c组成的串

#### 直接初始化和拷贝初始    
使用 = 进行的是拷贝初始化，否则是直接初始化

cin读入的string会忽略空白格，从真正的字符开始读到下一个空白处为止

读取一行用getline(istrem, s),遇到换行符为界。如果一开始就是换行符则读取的是空串

#### 字面值和string对象相加    
字面值可以和string对象进行 + 操作，因为标准库允许把字符字面值和字符串字面值转化成string对象。但是进行 + 操作时，必须保证每个 + 号的两侧至少有一个string对象
```C++
string s1 = "hello", s2 = "world";
string s3 = s1 + ", " + s2 + '\n'; //s3 == "hello, world"

string s4 = s1 + ", "; //add a string object with a string value
string s5 = "hello" + ", "; //error! no string object!

string s6 = s1 + " ," + "world";
string s7 = "hello" + ", " + s2; //error! the first + add two string values!
```
**Attention**：C++中的字符串字面值不是string对象！！！

#### 处理string对象的字符
cctype头文件中定义了一系列标准库函数用于判别，具体查阅相关API

**tips**： C++兼顾了C中的标准库，并且将C中的头文件如name.h命名为cname。两者的内容是一样的，但是写C++的时候建议用C++的标准写法，即用cname，保证命名空间std里面可以找到库中的名字。

```C++
//an example to use range for to handle string
string s("Hello World!!!");
/*the type of s.size() is string::size_type, we cannot sure which type it is. But it must be an unsigned type. */
decltype(s.size()) punct_cnt = 0;
for (auto c : s) {
    if (ispunct(c))
        punct_cnt++;
}
cout << punct_cnt << " punctuation characters in "
     << s << endl;
```
如果需要改变字符串中的字符，可以用for(auto &c : s)来进行处理，这时的c是引用

### 标准库vector
vector是模板而非类型，vector生成的类型必须包含vector中元素的类型，如vector \<int\>

####定义和初始化vector对象
||vector对象初始化的方式|
-|-
vector<T> v1 | 默认初始化，v1为空
vector<T> v2(v1) | v2是v1的副本，v1和v2的元素类型必须相同！
vector<T> v2 = v1 | 等价于v2{v1}
vector<T> v3(n, val) | v3有n个值为val的函数
vector<T> v4(n) | v4有n个值为默认初始化值的对象
vector<T> v5{a,b,c...} | v5包含初始化元素的个数，每个元素被赋予相应值
vector<T> v6 = {a,b,c...} | 等价于v5{a,b,c...}

对于vevotr的初始化，()一般用来提供构造vector对象的值，{}一般用来存放想要初始化的vector列表。但有一个例外，当{}存放的值无法用来初始化vector中元素的时候，编译器会试图用{}存放的内容来构造vector对象。例如：

```C++
vector<string> v1("hi"); //error
vector<string> v2{"hi"};

vector<string> v3{10}; //v3 contains 10 empty string
vector<string> v4{10, "hi"}; //v3 contains 10 "hi"
```

vector中动态增加元素用push_back()函数。如果有动态增加，则不允许使用范围for循环

vecotr中的size_type必须指明vector是哪种类型定义的
```C++
vector<int>::size_type; //correct
vector::size_type; //error!
```

#### 迭代器介绍
一般容器都有begin和end的成员，begin指向第一个元素，end指向尾元素的下一个元素。当容器为空的时候，两者返回的都是尾后迭代器。

迭代器的用法和指针类似，有* / -> / ++ / -- / == / != 等操作。    
例子：将string的第一个字母变成大写
```C++
string s("some string");
if (s.begin() != s.end()) { //确保s非空
    auto it = s.begin();
    *it = toupper(*it);
}
```

**tips**：C++的for循环尽量用!=，因为C++的容器迭代器基本都定义了 == 和 != 而不一定有 > <等操作

**迭代器类型**
```C++
vector<int>::iterator it;
string::iterator it2; //it and it2 can read and write

vector<int>::const_iterator it3;
string::const_iterator it4;  //it3 and it4 are read only
```
如果容器是个常量对象，那么只能用const_iterator, 否则两者都可以使用

如果对容器的操作过程中只需要读不要写，那么尽量用const_iterator。C++11标准引入了cbegin()和cend()，用来返回const_iterator

凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素，以免迭代器失效。

指向同一个容器的两个迭代器可以进行 - 操作，其返回的结果类型为**difference_type**的带符号整形数

#### 数组
编译的时候必须知道数组的维度，即维度必须是一个常量表达式
```C++
unsigned cnt = 42;  //not a constexpr
constexpr unsigned sz = 42;  //constexpr
int arr[10]; //an array contains 10 integers
int *parr[sz]; //an array contains 42 pointers point to int
string bad[cnt]; //error! cnt is not a constexpr
string strs[get_size()]; //correct only get_size return a constexpr
```

**字符数组的特殊性**
可以用字符串的字面值对字符数组进行初始化，此时需要注意字符串字面值的结尾有一个空字符('\0')
```C++
char a1[] = {'C', '+', '+'};  //a1 has 3 chars
char a2[] = {'C', '+', '+', '\0'}; //a2 has 4 chars
char a3[] = "C++"; // the same as a2
const char a4[3] = "C++";  //error! a4 can only contain 3 chars
```
数组不允许拷贝和赋值，这一点与容器不同！引用类型不存在数组，因为数组的元素必须为对象。

**一些复杂的数组声明**
```C++
//ptrs is an array contains 10 pointers point to integer
int *ptrs[10]; 
int &refs[10] = /*?*/;  //error! reference array is not exist!
//Parray is a pointer point to an array contains 10 intergers
int (*Parray)[10] = &arr;
//arrRef is a reference refer to an array contains 10 integers 
int (&arrRef)[10] = arr;
//arry is a reference refer to an array contains 10 pointer point to int
int *(&arry)[10] = ptrs;
```
对于数组的声明，从其名字开始由内向外进行阅读即可。

#### 指针和数组
一般而言数组名就是指向数组第一个元素的指针，其中对数组名用auto和decltype的时候也有不同，具体如下：
```C++
int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto ia2(ia); //ia2 is a pointer point to the first element in ia
ia2 = 42; //error!!!

decltype(ia) ia3 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //ia3 is an array contains 10 integers
```
对于数组的首尾指针，C++11用了begin(array_name)和end(array_name)两个函数来定义

指针相减的结果返回**ptrdiff_t**类型

与容器不同，数组的下标允许是负数，如：
```C++
int ia[] = {0, 2, 4, 6, 8};
int *p = &ia[2];
int j = p[1]; //j == ia[3] == 6
int k = p[-2]; //k == ia[0] == 0
```

#### 与C风格字符串的接口
C++为了兼容C风格字符串，允许在任何出现字符串字面值的地方都可以用以空字符结束的字符数组来替代。但反之不成立：
```C++
string s = "hello";
char *str = s; //error!
const char *str = s.c_str(); //correct!
```
c_str函数返回一个C风格的字符串，即一个指针，指向以空字符结束的字符接口

**使用数组初始化vector对象**
不允许用一个数组为另一个内置类型的数组赋初值，也不允许用vector对象初始化数组，但是允许用数组初始化vector对象
```C++
int int_arr[] = {0, 1, 2, 3, 4, 5};
//vector有6个元素，分别是int_arr数组中对应元素的副本
vector<int> ivec(begin(int_arr), end(int_arr));
//vector中含有三个元素，分别是1 2 3
vector<int> ivec(int_arr + 1, int_arr + 4);
```

#### 多维数组
C++严格意义上没有多维数组，通常所说的多维数组其实是数组的数组
**多维数组的初始化**
```C++
//两个初始化效果一致
int ia[3][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9 ,10 , 11}
};
int ia[3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

//仅初始化每行的第一个元素
int ia[3][4] = {{0}, {4}, {8}};

//显式地初始化第一行，其余元素未初始化
int ia[3][4] = {0, 3, 6, 9};
```
对于多维数组，用范围for循环的时候，所有层都应该是引用类型，否则会出错。因为对于外层的auto类型判别其为指针，再对其进行auto不能得到想要的结果。

**类型别名简化多维数组的指针**
```C++
using int_array = int[4];
typedef int int_array[4];
```
上述两个语句都是给一个4个int的数组定义了一个int_array的别名
