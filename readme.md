# <center>C++ primer 阅读笔记</center>
## 前言 
&ensp;最近重新开始看c++ primer这本书，写点笔记，也为了以后复习和找工作吧...

## chapter1 开始
&ensp;第一章没啥好写的，就讲了c++的一些基础，快速浏览了一下

## chapter2 变量和基本类型

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

## Chapter3 字符串、向量和数组
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

## chapter4 表达式
### 基本概念
**重载运算符**

重载运算符的时候，运算对象的类型和返回值的类型都是由该运算符定义的，但是运算对象的个数、运算符的优先级和结合率无法改变

**左值和右值**

一个对象作为右值的时候，用的是对象的值/内容;作为左值的时候，用的是对象的身份(在内存中的位置)

decltype对于左值和右值也有所不同。如果表达式求值结果是左值，那么decltype用于该表达式得到引用类型。
```C++
int i = 1;
int *p = &i;  //p is a pointer
decltype(*p) c = i;  //*p是对指针解引用，产生一个左值，因此c是int&类型
decltype(&p) d = &p; //&p产生一个右值，因此d是int**类型
```
**求值顺序**

优先级规定运算对象的组合方式，但是运算对象的求值顺序却是不定的。如`int i = f1() * f2()`中，f1和f2哪个先计算是不确定的

对于未指定执行顺序的运算符，表达式指向并修改了同一个对象，将会引发错误并产生未定义的行为，如：
```C++
int i = 0;
cout << i << " " << ++i << endl; //undefined
```
明确规定了求值顺序的运算符有逻辑与(&&),逻辑或(||),条件运算(?:),逗号运算(,)

### 算数运算符
\+ - 号有一元和二元两种含义，当一元\+ -号作用于一个指针或者算数值的时候，返回运算对象值的一个提升的副本
```C++
int i = 1024;
int k = -i; //k = -1024
bool b = true;
bool b2 = -b; //b2 = true!
```
上式中，由于-true做了变量提升，提升为int型，则得到结果-1,-1返回true

%运算规定必须是整形参与，其结果由(m/n)*n+m%n == m定义，即如果m不等于0,则结果的符号和m相同

### 赋值运算符
需要区分初始化和赋值是不同的两类操作

C++11新标准允许花括号扩起来的初始值列表作为赋值语句的右值运算对象，但是这些运算对象的类型所占空间必须小于等于目标对象类型，例如
```C++
int k = 0;
k = {3.14}; //error! double -> int 
k = {true}; //correct! bool -> int
vector<int> v;
v = {1, 2, 3, 4, 5};
```
**复合求值运算符**：如+=等，与普通运算符的区别在于对于左侧运算对象求值次数用复合运算符只求一次

### 递增递减运算符
++&ensp;--运算符有前置和后置两个类型。一般而言优先选用前置版本，以免不必要的临时存储开销

**运算对象可按任意顺序求值**

举一个简单的例子：
```C++
while(beg != s.end() && !isspace(*beg))
    *beg = toupper(*beg++);  //error! undefined!
```
上述语句会发生错误，因为运算对象处理顺序是可以任意的，编译器可能按照以下任意一种方式处理表达式：
```C++
*beg = toupper(*beg);  //先求左值
*(beg+1) = toupper(*beg); //先求右值
```
### sizeof运算符
两类形式：sizeof (type)和sizeof expr 

举例如下：
```C++
Sales_data data, *p;
sizeof(Sales_data);  //存储sales_data类型的对象所占空间的大小
sizeof data;   //同上
sizeof p;    //指针本身所占空间的大小
sizeof *p;  //同sizeof(Sales_data);
sizeof data.revenue;  //revenue成员的大小
sizeof Sales_data::revenue;  //同上
```
sizeof运算符的一些性质：
+ 对char或者类型是char的表达式执行sizeof得到1
+ 对引用类型执行sizeof得到引用对象所占空间大小
+ 对指针执行sizeof获得指针本身所占空间大小
+ 对解引用指针执行sizeof获得指针指向的对象所占空间的大小，**指针不要求有效！！！** 因为sizeof运算符并不真正执行运算
+ 对数组进行sizeof获得整个数组所占空间的大小
+ 对string和vector对象执行sizeof返回该类型固定部分的大小，不计算对象中的元素占了多少空间

利用上述性质，计算数组长度代码可以写为：
```C++
constexpr size_t sz = sizeof(array) / sizeof(*array);
```
### 逗号运算符
逗号运算符按照从左往右的顺序依次求值，把左侧的值丢弃掉最后的结果是右侧的值。如果右侧运算结果是左值，那么最终的求值结果也是左值。

### 显式强制类型转换
有**static_case**，**const_cast** , **reinterpret_cast**, **dynamic_cast** 4类

不含有底层const时，可以用static_case，const_cast用来改变底层const属性，reinterpret_cast为运算对象的位模式提供较低层次上的解释。举例如下：
```C++
int i, j;
double slope = static_cast<double>(j) / i;

void *p = &d;
double *dp = static_cast<double>(p);

const char *pc;
char *p = const_cast(char*)(pc); //correct! 但是通过p写值是未定义的

const char *cp;
char *q = static_cast<char*>(cp); //error! static_cast无法去掉底层const属性
static_cast<string><cp>; //正确，字符串字面值转化成string类型
const_cast<string>(cp);  //错误，const_cast只能改变常量属性

int *ip;
char *pc = reinterpret_cast<char*>(ip);
```
运算符优先表，见书p.147

## chapter5 语句
本章内容很基础，几乎所有的高级程序设计语言都会涉及到。如for、while、if-else、switch等。因此就记几个比较容易忽视的点吧。

### switch
switch语句的case标签必须是整形表达式。

switch内部的变量定义：C++不允许switch语句跨过变量的**初始化语句**直接跳转到该变量作用域的另一个位置。如果要在case后定义分支并初始化变量，应该把变量定义在块内。例如：
```C++
case true:
    string file_name; //错误，控制流绕过一个隐式初始化变量
    int ival = 0;  //错误：控制流绕过一个显式初始化变量
    int jval; //正确，jval没有初始化
    break;
case false:
    jval = next_num(); //正确。给jval赋值
    if (file_name.empty())  //file_name在作用域内但没有初始化
        //...

//最好采用以下写法
case true:
    {
        string file_name = get_file_name();
    }
    break;
case false:
    if (file_name.empty()) //error! file_name不在作用域之内
```
### while
定义在while条件部分或者循环体内的变量每次迭代都经历从创建到销毁的过程

### 范围for循环
如果在循环过程中需要对序列中的元素执行写操作，那么循环变量必须声明成引用类型

### goto语句
goto语句和控制权转向的那条带标签的语句必须位于同一个函数之内

### try语句块和异常处理
C++中，异常处理包括：
+ throw表达式，用来引发(raise)异常
+ try语句块，后面跟一个或者多个catch，为异常处理代码
+ 一套异常类，用以在throw表达式和相关的catch子句之间传递异常的具体信息
#### throw表达式
```C++
if(item1.isbn() != item2.isben())
    throw runtime_error("Data must refer to same ISBN");
```
上面代码中，抛出异常后会终止当前的函数，并把控制权转移给能处理该异常的代码。初始化runtime_error的对象时，需要给它提供一个string对象或者是一个C风格的字符串，该字符串中有一些关于异常的辅助信息。

#### try语句块
try语句块后面跟多个catch语句块，当选中某个catch语句块后，执行对应的块。catch一旦完成，程序跳转到try语句块最后一个catch子句之后的那条语句继续执行！

**attention**：try语句块中声明的变量在块外部不能访问，即便是catch子句内也不行！
```C++
while(cin >> item1 >> item2) {
    try {
        //执行之前throw表达式部分的if语句
    } catch(runtime_error err) {
        cout << err.what()
             << "\nTry Again? Enter y or n" << endl;
        char c;
        cin >> c;
        if (!cin || c == 'n')
            break; //break the while loop
    }
}
/*输出如下：
Data must refer to same ISBN
Try Again? Enter y or n
*/
```
#### 标准异常
C++标准库定义了一组类，用来报告异常，分别在4个头文件
+ exception头文件，定义最通用的异常类exception。只报告异常的发生，不提供任何额外信息
+ stdexcept头文件定义几种常用的异常类
+ new头文件定义了bad_alloc异常类型
+ type_info头文件定义了bad_cast异常类型
+ 对于exception，bad_alloc和bad_cast对象，只能默认初始化，不允许提供初始值
+ 其他异常则应该用string或者C风格的字符串初始化对象，不允许使用默认的初始化方式、
+ 异常定义了一个what的成员函数，没有任何参数，反馈一个const char*，提供关于异常的一些文本信息

||\<stdexcept\>定义的异常类|
-|-
exception | 最常见的问题
runtime_error | 运行时才能检测的错误
range_error | 运行时错误：生成的结果超出了有意义的值范围
overflow_error | 运行时错误：计算上溢
underflow_error | 运行时错误：计算下溢
logic_error | 程序逻辑错误
domain_error | 逻辑错误：参数对应的结果值不存在
invalid_error | 逻辑错误：无效参数
length_error | 逻辑错误：试图创建一个超出该类型最大长度的对象
out_of_range | 逻辑错误：使用一个超出有效范围的值

## chapter6 函数
函数的写法和使用部分与大多数的高级语言相似，不再赘述。需要注意的是C++里函数的返回类型不能是数组或者函数类型，但可以是指向数组或函数的指针。

### 局部对象
+ 名字的作用域是程序文本的一部分，名字在其中可见
+ 对象的生命周期是程序执行过程中该对象存在的一段时间

**自动对象**：只存在于块执行期间的对象，例如形参

### 分离式编译
例如，定义了头文件header.h，该头文件中定义的函数是现在func.cpp，然后主函数文件main.cpp调用了这一系列函数。由于头文件只是起到声明的作用，因此只需编译两个*.cpp文件并链接就可以。命令如下
```shell
g++ -c func.cpp
g++ -c main.cpp
#上述两条语句编译完成后生成fuc.o和main.o文件，接着链接
g++ main.o func.o -o test
#最终生成test可执行文件
```
### 参数传递
形参是引用类型的时候，为引用传递，否则是值传递

#### 传值参数
该部分需要注意的是指针作为形参的时候，执行指针拷贝的时候，拷贝的是指针的值。例如：
```C++
void reset(int *p) {
    *ip = 0;
    ip = 0;
}
```
上述reset函数中，*ip=0语句会改变原本实参指向对象的值，但是ip=0并不会影响原本实参。这是因为p和原本的实参是两个不同的指针，只不过指向的是同一个对象。

一般来说，尽量使用引用，避免拷贝大量的对象。当不需要修改形参的值时，最好用常量引用。在参数前加个const

#### const形参和实参
实参初始化形参的过程中会忽略掉顶层const，尽管形式和用法上有差异。这一点需要注意，例如以下两个fcn函数编译器会认为是重复定义的：
```C++
void fcn(const int i) {/*fcn can read i, but cannot write to i */}
void fcn(int i) {} //error! 重复定义fcn
```
注意在给引用形参传值的过程中，const类型不可以传给非const类型。而且类型必须保持一致。如果形参是const引用，那么必须传递一个常量。例如：
```C++
//define three functions
void reset(int *ip);
void reset(int &i);
string::size_type find_char(const string &s, char c, string::size_type &occurs);

int i = 0;
const int ci = i;
string::size_type ctr = 0;
reset(&i); //call int* reset
reset(&ci); //error! 不能用指向const int的指针初始化int*
reset(i); //call &i reset
reset(ci); //error!
reset(42); //error! 普通引用无法绑定字面值
reset(ctr); //error！ ctr是无符号类型，类型不匹配
find_char("hello", 'o', ctr); //正确，find_char第一个形参是对常量的引用
```
对于函数的引用，尽量使用常量引用，减少错误的发生。因为const引用可以引用非const的对象，反之则不可

#### 数组形参
数组形参的三种写法：
```C++
void print(const int*);
void print(const int[]);
void print(const int[10]); //维度表示希望有多少个元素，实际不一定,不要这样写
```
上面三个函数传入的都是const int* 类型，调用print的时候，检查是否传入了const int*即可。

数组也可以传入引用形参，如：
```C++
void print(int (&arr)[10]);
void print(int &arr[10]); //错误，此时arr指的是引用的数组！！！
```
#### 可变形参的函数
**initializer_list形参**：对于实参的数量未知但是类型都相同的情况下可以用initializer_list类型的形参，具体操作如下表：

||initializer_list提供的操作|
-|-
initializer_list<T> lst; | 默认初始化，T类型元素的空列表
initializer_list<T> lst{a, b, c...}; | lst元素数量和初始化一样多，列表中的元素是**const**类型
lst2(lst)<br>lst2 = lst | 拷贝或赋值一个initializer_list对象不会拷贝列表中的元素，<br>原始列表和副本是共享元素的
lst.size() | 列表中元素数量
lst.begin() | lst首元素指针
lst.end() | lst尾元素下一个位置的指针

使用举例：
```C++
void error_msg(initializer_list<string> li) {
    for (auto i = li.begin(); i != li.end(); ++i)
        cout << *i << " ";
    cout << endl;
}

//向initializer_list里面传递的参数序列用{}扩起来
if (expected != actual)
    error_msg({"functionX", expected, actual});
else
    error_msg({"functionX", "okay"});
```
#### 函数的返回值
如果函数返回引用，那么该引用仅仅是它所引对象的一个别名。例如：
```C++
const string &shorterString(const string &s1, const string &s2) {
    return s1.size() < s2.size() ? s1 : s2;
}
```
上例中，形参和返回类型都是const string的引用，不管是调用还是返回都不拷贝string对象

**attention**：不要返回局部对象的引用或指针，因为局部对象在函数完成后存储空间也随之释放，返回其引用或指针会造成未定义的行为。

**列表初始化返回值**：C++11标准规定，函数可以返回花括号包围的值的列表，但如果返回的是内置类型，则{}里面只能含有一个值，而且所占的空间不应该大于目标类型的空间。例：
```C++
vector<string> porcess() {
    //expected 和 actual 是 string 对象
    if (expected.empty())
        return {}; //返回一个空的vevtor对象
    else if (expected == actual)
        return {"functionX", "okay"}; //返回列表初始化的vector对象
    else
        rerurn {"functionX", expected, actual};
}
```
#### 返回数组指针
简单的写法可以使用别名，如：
```C++
typedef int arrT[10];
using arrT = int[10];  //arrT是一个数组别名，含有十个整形

arrT* fuunc(int i); //func返回一个含有10个整数的数组的指针
```
如果不使用别名，则书写的时候格式需要注意，为*Type&nbsp;(\*function(parameter_list))&nbsp; [dimension]* ,理解的时候由内向外阅读即可

**使用尾置返回类型**：C++新标准规定可以用尾置返回类型简化声明，例子如下：
```C++
//func接受一个int类型的实参，返回一个指针，指向含有10个整数的数组
auto func(int i)->int(*)[10];
```

**使用decltype**：如果知道返回的指针指向哪里，那么用decltype关键字即可，例如：
```C++
int odd[] = {1, 3, 5, 7, 9};
int even[] = {2, 4, 6, 8, 10};

//返回一个指针，指向含有5个整数的数组
//decltype推测odd的时候认为是一个数组类型，所以如果要返回指针需要加上*号
decltype(odd) *arrPtr(int i) {
    return (i % 2) ? &odd : &even;
}
```
### 函数重载
重载的时候顶层const不影响传入函数的对象，如
```C++
Record lookup(Phone);
Record lookup(const Phone); //error! re-defined!

Record lookup(Phone *);
Record lookup(Phone * const); //error! re-defined!
```
底层的const是可以重载的，如：
```C++
//定义了4个独立的重载函数，对于接受引用或指针的函数，对象是常量还是非常量对应参数是不同的
Record lookup(Account&);
Record lookup(const Account&);

Record lookup(Phone *);
Record lookup(const *Phone);
```
const对象只能传递给const形参，但是非const对象调用函数的时候，会优先调用非常量版本的函数

#### const_cast和重载
const_cast用在函数重载中的例子如下：
```C++
const string &shorterString(const string &s1, const string &s2) {
    return s1.size() < s2.size() ? s1 : s2;
}

//该函数中，首先把实参转化成const的引用，然后调用const版本的函数，再将返回值转回非const引用
string &shorterString(string &s1, string &s2) {
    auto &r = shorterString(const_cast<const string&>(s1),
                            const_cast<const string&>(s2));
    return const_cast<string&>(r);
}
```
#### 重载与作用域
一般而言，不要将函数声明在局部作用域内，但是为了说明情况，举个例子：
```C++
string read();
void print(const string &);
void print(double); //overload print
void fooBar(int ival) {
    bool read = false;  //屏蔽了read函数
    string s = read(); //error！ read是bool值而非函数

    void print(int); //屏蔽了之前的print函数
    print("Value "); //error,之前的print(const string &)被屏蔽了
    print(3.14);
    print(ival); //这两句都可以正确执行
}
```
**attention**:C++语言中，名字查找发生在类型检查之前

### 特殊用途语言特性
#### 默认实参
在定义函数的时候给形参赋值即可，调用的时候省略相应的实参。注意，一旦函数的某个形参被赋予了初值，那么其后面的所有参数都需要有默认值。在调用的时候只能省略尾部的实参。例如
```C++
typedef string::size_type sz;
string screen(sz ht = 24, sz wid = 80, char background = ' ');

window = screen(, , '?'); //错误，只能省略尾部的实参
window = screen('?'); //调用screen('?', 80, ' '),即把'?'转化成sz类传递给第一个参数
```
对于函数的声明，一个形参只能被赋予一次默认实参，例如
```C++
string screen(sz, sz, char = ' ');  //宽和高没有默认值
string screen(sz, sz, char = '*');  //error！ 不可以重复声明
string screen(sz = 24, sz = 80, char);  //正确，添加默认声明
```
除了局部默认值外，只要表达式的类型可以转化成形参需要的类型，该表达式就可以作为默认实参。（可以灵活地改变表达式的值从而达到改变默认实参的目的）

#### 内联函数和constexpr函数
在定义函数的时候使用关键字inline，表示内联函数。用来优化规模较小、流程直接、频繁调用的函数。但是编译器可以忽略这个请求。

constexpr函数是用于常量表达式的函数，其返回类型和形参的类型都是字面值类型，而且函数体必须有且仅有一条return语句。不过constexpr并不一定返回常量表达式，可以理解成constexpr做了函数重载，一个是可以返回constexpr一个不可以，具体返回什么看传入的参数是不是constexpr类型

### 调式帮助
#### assert
assert为预处理宏，定义在cassert头文件中。用法
```C++
assert(word.size() > threshold);
```
#### NDEBUG
assert的行为依赖于NDEBUG的预处理变量状态。如果定义了NDEBUG，则assert什么也不做。默认状态没有定于NDEBUG，则assert进行运行时检查。关闭调试可以用命令行选项
```shell
$g++ -D NDEBUG main.c #相当于定于了NDBUG的宏
```
其他用法
```C++
void print(const int ia[]. size_t size) {
    #ifndef NDEBUG
    //__func__是编译器定义的一个局部静态变量，存放函数名
        cerr << __func__ << endl;
    #endif
}
```
其他的一些对于调试很有用的名字
+ __FILE__ 存放文件名的字符串字面值
+ __LINE__ 存放当前行号的整形字面值
+ __TIME__ 存放文件编译时间的字符串字面值
+ __DATE__ 存放文件编译日期的字符串字面值

### 函数匹配
```C++
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);

f(5.6); //call void f(double, double)
f(42, 5.6); //error! 有歧义
```
对于f(42, 5.6)的匹配，第一个参数看，最佳匹配是f(int, int)，第二个参数看则是f(double, double), 返回二义性。
### 实参类型转化
类型转化的排序：
+ 精确匹配，包括
    + 实参和形参完全相同
    + 数组类型或者函数类型转化为指针
    + 添加或者删除顶层const
+ const转换实现的匹配
+ 类型提升实现的匹配
+ 算数类型转化或者指针转化（void* or 0->nullptr)形成的匹配
+ 类类型转化形成的匹配

类型提升或者算数转化的时候，级别都是一样的，如char->int等，如果都是需要提升，那么会产生二义性，如
```C++
void ff(int);
void ff(short);
ff('a'); //char->int, call f(int)

void ff(long);
void ff(float);
ff(3.14); //error! double->float / double->long 有二义性
```
### 函数指针
函数指针和函数名无关，只与返回类型和形参的类型有关。如：
```C++
bool func(const string &, const string &);
//fp is a pointer can point to func
bool (*fp)(const string &, const string &);

fp = func;
fp = &func; //两者等价，将函数名赋给函数指针的时候会自动类型转化

//调用函数的时候，可以直接用指针无需解引用。以下三条语句等价
bool b1 = fp("hello", "world");
bool b2 = (*fp)("hello", "world");
bool b3 = func("hello", "world");
```
对于重载函数的指针，必须将返回类型和形参都一一对应。

#### 函数指针形参
形参可以写成函数类型，但实际上是当作函数指针使用。函数也可以作为实参，但是会自动转化成指针。

#### 返回指向函数的指针
和函数指针形参不同，当函数返回值是一个函数指针的时候，编译器不会自动将函数类型转化成对应的指针，此时尽量使用别名以免出错。例如
```C++
using F = int(int*, int);
using PF = int(*)(int*, int);

//定义f1返回指向函数的指针，以下几条语句等价
PF f1(int); 
F *f1(int);
int (*f1(int))(int*, int);
auto f1(int) -> int(*)(int*, int);

F f1(int); //error!!! F是函数类型，f1不能返回函数！
```

## chapter7 类
从构造一个类开始讨论类的一些细节。构造一个sales_data类，接口包含
+ isbn成员函数，返回ISBN编号
+ combine成员函数，将一个sales_data对象加到另一个对象上
+ add函数，执行两个sales_data对象的加法
+ read函数，将数据从istream读入到sales_data对象
+ print函数，输出到ostream

从而得到类的一个基本表示
```C++
struct Sales_data{
    //新成员，关于Sales_data对象的操作
    std::string isbn() const{ return bookNO; }
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    std::string bookNO;
    unsigned units_sold = 0;
    double revenue = 0.0;
}
//Sales_data的非成员函数接口
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, const Sales_data&);
```
**attention**:类的成员函数必须在类内声明，但是可以在外部定义。定义在类内部的函数是隐式的inline函数

### 引入this
成员函数通过一个this的额外隐式参数来访问调用它的那个对象。当调用一个成员函数时，用请求该函数的对象地址初始化this。

this是一个常量指针，不能改变this的地址。

### const成员函数
上文中的`std::string isbn() const{ return bookNO; }`语句，const是用来修饰this指针的。默认情况下，this指向类类型非常量的常量指针。即this指针类型为`Sales_data *const`。而在成员函数后面用const表示常量成员函数，无法对其对象的数据成员写入新值,this指针类型为`const Sales_data *const`。

常量对象，常量对象的引用或者指针只能调用常量成员函数。

### 类外部定义成员函数
对Sales_data的avg_price进行定义，如下：
```C++
double Sales_data::avg_price() const{
    if (units_sold)
        return revenue/ units_sold;
    else 
        return 0;
}
```
式中::表示该函数被定义在xx类中。

### 定义返回this对象的函数
对于Sales_data类的combine函数进行如下定义：
```C++
Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += ths.revenue;
    return *this;
}
```
上文中的`return *this;`返回调用该函数的对象

### 类相关的非成员函数
对伊一些辅助函数，不属于类本身，但是属于类的接口的组成部分，此时一般将其声明在类的同一个头文件内

例如上例中的read和print函数
```C++
istream &read(istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
```
istream和ostream都是IO类，不能拷贝，因此必须用引用来传递

对于add函数，用来将两个sales_data对象作为参数，返回一个新的对象
```C++
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
```
### 构造函数
构造函数不能声明成const,由于创建const对象的时候，直到构造函数完成初始化过程，对象才能真正取得其常量属性，因此**构造函数在const对象构造过程中可以向其写入值**。

只有类没有声明任何构造函数的时候，编译器才会自动生成默认构造函数。对于默认构造函数，C++11标准里可以直接用`classname() = default`即可。可以写在类内也可以写在类外，区别为是否内联。默认构造函数初始化数据成员规则如下：
+ 如果存在类内初始值，用它初始化成员
+ 不存在，则默认初始化成员

**tips:** 构造函数不应该轻易覆盖类内的初始值，除非要赋予一个与原值不同的值。如果没有类内初始值，则所有构造函数最好显示初始化每个内置类型的成员。

### 访问控制与封装
+ public成员在整个程序内可以被访问
+ private成员可以被类内的成员函数访问，但是不能被使用该类的代码访问

class和struct定义类的唯一区别就是默认访问权限。

### 友元
类可以允许其他类或者函数访问其非公有成员，方法是让其他类或者函数称为友元(friend)。友元声明在类的内部，尽量写在开始或者结束的位置，以friend关键字开头。

友元声明仅仅指定了访问权限，而非真正的函数声明。因此在类内声明友元后，在对应的头文件中还需要声明相应的函数。

### 定义类型成员
类可以自定义某种类型在类中的别名，该类姓名和其他成员一样存在访问权限。用来定义类型的成员必须先定义后使用，一般写在类的起始位置。如：
```C++
class Screen{
public:
    using pos = std::string::size_type;
    //或者可以用等价的语句
    //typedef std::string::size_type pos;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
}
```
### 可变数据成员
关键字mutable可以让某个数据成员可修改，即使是在const对象的成员依然可以修改。例如
```C++
class Screen{
public:
    void some_member() const;
private:
    mutable size_t access_ctr;
}

void Screen::some_member() const {
    ++access_ctr;
}
```