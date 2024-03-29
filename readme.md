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
### 返回*this的成员函数
例：
```C++
class Screen{
public:
    //其余代码见chapter7 screen.h
    Screen &move(pos r, pos c); //可以在定义的时候加上inline变为内联
    Screen &set(char);
    Screen &set(pos, pos, char);
};

inline Screen &Screen::move(pos r, pos c){
    pos row = r * width;  //计算行的位置
    cursor = row + c;     //在行内将光标移动到指定的列
    return *this;         //以左值的形式返回对象
}

inline Screen& Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch) {
    contents[r *width + col] = ch;
    return *this;
}
```
返回类型为Screen&，如果没有&那么返回的是原对象的一个副本而不是原本对象本身。利用这样的写法，可以用以下语句：
```C++
myScreen.move(4, 0).set('#');

//如果返回Screen而非Screen&，等价于
Screen temp = myScreen.move(4, 0);
temp.set('#');
```
如果从const成员函数中返回this*，那么返回的是常量引用，无法对其的值进行修改。

### 基于const的重载
根据成员函数是否为const，可以进行重载。即函数可以根据是否有底层const进行重载。例如：
```C++
class Screen {
public:
    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }

    const Screen &display(std::ostream &os) const{
        do_display(os);
        return *this;
    }

private:
    void do_display(std::ostream &os) const {
        os << contents;
    }
}
```
### 类的声明
类可以暂时声明而不定义，但是在创建对象之前必须定义它，不然编译器不知道需要分配多少空间。因此，一个类的成员里面不能有类本身。但是类被声明之后，成员就可以有指向类本身的指针。

### 类之间的友元
写法如下：
```C++
class Screen {
    //Window_mgr 成员可以访问 Screen 类的私有部分
    friend class Window_mgr;
}
```
友元关系没有传递型，即Window_mgr可以访问Screen中的成员，但是Window_mgr的友元是不能访问的。如果指向让Window_mgr的某个成员函数访问Screen中的成员，可以有下述写法：
```C++
class Screen {
    friend void Window_mgr::clear(ScreenIndex);
}
```
上例中的程序设计流程如下：
+ 先定义Window_mgr类，声明clear函数，但不定义。因为clear使用Screen成员之前必须先声明Screen
+ 定义Screen，包括对clear的友元声明
+ 最后定义clear，此时它才能使用Screen的成员

对于重载的函数，每个函数都是不同的函数，因此声明友元的时候需要每一个分别声明才行。

对于友元的声明，仅仅是影响访问权限，本身并不是普通的声明，例子如下：
```C++
struct X{
    friend void f() {}
    X() { f(); } //error! f is undefined!
    void g();
    void h();
}
void X::g() {
    return f();   //error! f is undefined!
}
void f();
void X::h() {
    return f();  //correct!
}
```
### 名字查找和类的作用域
类的定义分两步处理：
+ 首先编译成员的声明
+ 全部的类可见之后再编译函数体

因此，定义在类内部的函数顺序不太要紧，因为成员函数体直到整个类可见后才会被处理。但这两条规则仅适用于成员函数中使用的名字，声明中使用的名字和返回类型中的名字都必须在定义前可见。例：
```C++
typedef double Money;
string bal;
class Account {
public:
    Money balance() {return bal;}  //bal为函数体内的bal，Money在函数体外查找到
private:
    Money bal;
}
```
在类中，成员如果使用了外层作用域中的某个名字，而该名字代表某类，则不能重新定义该名字
```C++
typedef double Money;
string bal;
class Account {
public:
    Money balance() {return bal;} 
private:
    typedef double Money;   //error！不能重新定义money
    Money bal;
}
```
类的成员函数中使用的名字解析过程：
+ 首先在函数内查找，此时只查找函数使用之前出现的声明才会查找
+ 其次在类内继续查找
+ 类内也找不到则在成员函数定义之前的作用域内继续查找

例如：
```C++
int height;
class Screen {
public:
    typedef std::string::size_type pos;
    void dummy_fun(pos height) {
        cursor = width * height;  //height为最先定义的参数
    }
private;
    pos cursor = 0;
    pos height = 0, width = 0;
}

//如果要让height为成员变量，则有以下几种写法：
void dummy_fun(pos height) {
    cursor = width * this->height;
    cursor = width * Screen::height;
}

//以下函数中，height在函数作用域内找不到，则在类内继续查找，找到类内的成员变量
void dummy_fun(pos ht) {
    cursor = width * height;   
}
```
如果需要用全局的height，可以用`::height`作用域控制符。

### 构造函数初始化再谈
对于Sales_data的构造函数初始化方式有两种看上去等价的：
```C++
Sales_data(const string &s, unsigned u, double p):
               bookNo(s), units_sold(u), revenue(u*p){}

Sales_data::Sales_data(const string &s, unsigned u, double p) {
    bookNo = s;
    units_sold = u;
    revenue = u * p;
}
```
两者的区别在于，第一种写法是直接赋初值，第二种是默认初始化后再进行赋值，效率较低。构造函数一开始执行，则初始化就完成了。因此对于一些const变量或者没有构造函数的类变量必须使用构造函数赋初值，如：
```C++
class ConstRef {
public:
    ConstRef(int ii);
private:
    int i;
    const int ci;
    int &ri;
}

ConstRef::ConstRef(int ii) {
    i = ii;   //正确
    ci = ii;  //error,不能给const赋值
    ri = i;  //error,ri没有初始化
}

//正确写法应该是：
ConstRef::ConstRef(int ii):i(ii), ci(ii), ri(i) {}
```
### 成员初始化顺序
构造函数中的初始化列表顺序不影响成员的初始化顺序，成员的初始化顺序只和其定义的顺序有关。例如：
```C++
class X {
    int i;
    int j;
public:
    //undefined, i在j之前被初始化！！！
    X(int val) : j(val), i(j){};
}
```
对于默认构造函数，可以在其参数列表中加入默认实参值，这样就可以将其与只接受一个相应实参的构造函数卸载一起。

### 委托构造函数
写法举例：
```C++
class Sales_data {
public: 
    //非委托构造函数
    Sales_data(const string &s, unsigned u, double p):
               bookNo(s), units_sold(u), revenue(u*p){}
    //委托构造函数
    Sales_data(): Sales_data("", 0, 0){}
    Sales_data(std::string s): Sales_data(s, 0, 0){}
    Sales_data(std::istream &is): Sales_data() {
        read(is, *this);
    }
}
```
对于委托构造函数，受委托的函数会依次执行初始化列表和函数体，然后再返回委托函数的函数体。

### 隐式的类类型转换
类的类型之间可以有隐式的转化，但是只能转化一步，不能多步，例如：
```C++
string null_book = "9-999-99999-9";
//会创造一个临时的Sales_data对象，利用null_book进行构造
item.combine(null_book);
//以下写法与上面等价
item.combine(string("9-999-99999-9"));
item.combine(Sales_data("9-999-99999-9"));

//以下写法错误,因为要先把其转成string再转化
item.combine("9-999-99999-9");
```
类的类型转换不是总有效的，可以在构造函数前加`explicit`关键字加以阻止。其仅对与有一个实参的构造函数有效，对于有多个实参的构造函数本身就无法进行隐式转换。此外，`explicit`关键字只能在类内声明的时候用，类外部定义时不能重复。`explicit`构造函数只能用于直接初始化，不能用于拷贝形式的初始化过程(=赋值)，如：
```C++
//假设构造函数是explicit的
Sales_data item1(null_book);
Sales_data item2 = null_book; //error, explicit的构造函数不能用于拷贝初始化
```
要使用`explicit`的构造函数，可以用`static_cast`进行转化，如
```C++
item.combine(static_cast<Sales_data>(cin));
```
### 聚合类
聚合类需要满足以下要求：
+ 所有成员都是public的
+ 没有定义任何构造函数
+ 没有类内初始值
+ 没有基类，也没有虚函数

聚合类可以用{}括起来的成员初始值列表来初始化。

### 字面值常量类
数据成员都是字面值类型的聚合类是字面值常量类。如果不是聚合类，但符合以下要求，则其也是一个字面值常量类：
+ 数据成员都是字面值类型
+ 类至少有一个constexpr构造函数
+ 如果一个数据成员有类内初始值，则初始值必须是一条常量表达式。如果成员是某个类类型，则初始值必须使用成员自己的constexpr构造函数
+ 必须使用默认的析构函数

constexpr构造函数的函数体一般是空的。

### 类的静态成员
类的静态成员函数不包含this指针，因此不能声明成const，也不能在static函数体内使用this指针。静态成员函数可以在类的外部定义，此时不能重复static关键字。

静态成员的初始化一般是在类的外部定义并且初始化的，但是有一个例外，如
```C++
class Amount{
    static constexpr int period = 30;
    double daily_tbl[period];
};
```
period在类的内部就被初始化了，那么在类的外部不能再指定初始值。但是为了规范，一般在类外也定义一下该成员，用`constexpr int Amount::period;`语句.否则无法在类外部被使用。

静态成员和普通成员的两个区别
+ 静态数据成员可以是不完全类型（已经声明但还没有完整定义，不完全类型只能用于指针、引用和返回该类型的函数），如
```C++
class Bar {
public:
    //...
private:
    static Bar mem1;    //静态成员可以是不完全类型
    Bar *mem2;          //指针成员可以是不完全类型
    Bar* mem3;          //error！数据成员必须是完全类型！！！
}
```
+ 静态成员可以用于默认实参。非静态数据成员不能用于默认实参，如
```C++
class Screen {
public:
    Screen& clear(char = bkground);
private:
    static const char bkground;
}
```
## chapter8 IO类
||IO库类型和头文件|
-|-
**头文件** | **类型**
iostrem | istream, wistream 从流中读数据
&nbsp; | ostream, wostream 向流中写数据
&nbsp; | iostream, wiostream 读写流
fstream | ifstream, wifstream 从文件中读数据
&nbsp; | ofstream, wofstream 向文件中写数据
&nbsp; | fstream, wfstream 读写文件
sstream | istringstream, wistringstream 从string中读数据
&nbsp; | ostringstream, wostringstream 向string中写数据
&nbsp; | stringstream, wstringstream 读写string

上表中，w表示宽字符版本类型。对于IO对象，无拷贝和赋值，例如：
```C++
ofstream out1, out2;
out1 = out2; //错误，流对象不能赋值
ofstream print(ofstream); //错误，不能初始化ofstream参数
out2 = print(out2);  //错误，不能拷贝流对象
```
||IO库条件状态|
-|-
**头文件** | **类型**
strm::iostate | strm是一种IO类型，iostate为一种机器类型，提供表达条件状态的完整功能
strm::badbit | 致命的输入/输出错误,无法挽回
strm::failbit | 非致命的输入/输出错误，可挽回
strm::eofbit | 已到达文件尾
strm::goodbit | 此值保证为0,指出流未处于错误状态
s.eof() | 返回s的eofbit是否置位
s.fail() | 返回s的failbit或badbit是否置位
s.bad() | 返回s的badbit是否置位
s.good() | 返回流s是否处于有效状态
s.clear() | 将流s的所有条件状态复位，状态设为有效，返回void
s.clear(flags) | 根据flags将流s对应的条件状态位复位，flags类型位stm::iostate
s.setstate(flags) | 效果同上
s.rdstate() | 返回流s的当前状态，返回类型为stm::iostate

例子如下：
```C++
auto old_state = cin.rdstate();   //记住cin的当前状态
cin.clear();                      //使cin有效
process_input(cin);               //使用cin
cin.setstate(old_state);          //把cin设回原有状态
```
### 输出缓冲区管理
输出缓冲区刷新的原因：
+ 程序正常结束
+ 缓冲区满需要刷新
+ endl等操纵符显示刷新
+ 可以使用unitbuf设置流的内部状态。默认状态下cerr是设置unitbuf的，因此cerr内容是立即刷新的
+ 一个输出流关联到另一个流，例如cin和cerr都关联到cout，因此读cin或者写cerr都会导致cout缓冲区被刷新

**刷新输出缓冲区**
```C++
cout << "hi!" << endl;  //输出hi和一个换行，然后刷新缓冲区
cout << "hi!" << flush; //输出hi，然后刷新缓冲区
cout << "hi!" << ends;  //输出hi和一个空字符，然后刷新缓冲区
```
**unitbuf操作符**：如果每次输出操作都想刷新缓冲区，可以用unitbuf操纵符，例如：
```C++
cout << unitbuf;       //所有输出操作后都会立即刷新缓冲区
cout << nounitbuf;     //回到正常的缓冲方式
```
程序如果崩溃，是不会刷新输出缓冲区。因此程序崩溃后，需要手动刷新输出缓冲区。

输入输出流的关联用tie函数，用法如下：
```C++
cin.tie(&cout);  //cin和cout关联在一起
//old_tie指向当前关联到cin的流，如果有的话
ostream *old_tie = cin.tie(nullptr);  //cin不再与其他流关联
cin.tie(&cerr);  //cin与cerr关联，即读cin会刷新cerr
cin.tie(old_tie); //重建cin和cout之间的正常关联
```
一个流同时最多关联到一个流，但是多个流可以同时关联到同一个ostream。

### 文件输入输出
||fstream特有的操作|
-|-
fstream fstrm| 创建一个未绑定的文件流。fstream是头文件fstream中定义的某类型
fstream fstrm(s) | 创建一个fstrm并打开名为s的文件
fstream fstrm(s, mode) | 按照mode打开文件
fstrm.open(s) | 打开文件s并与fstrm绑定，返回void
fstrm.close() | 关闭与fstrm绑定的文件，返回void
fstrm.is_open() | 返回一个bool，指出与fstrm关联的文件是否成功打开且尚未关闭

当fstream对象被销毁的时候，close会自动调用。

### 文件模式
|| 文件模式|
-|-
in | 读方式打开
out | 写方式打开
app | 每次写操作定位到文件末尾
ate | 打开文件后立即定为到文件末尾
trunc | 截断文件
binary | 二进制方式进行IO

使用举例：
```C++
//file1在以下语句中都被截断，三者效果一样
ofstream out("file1");
ofstream out2("file1, ofstream::out); 
ofstream out3("file1", ofstream::out | ofstream::trunc);
//为了保留文件，显示指定app模式
ofstream app("file2", ofstream::app);  //隐含为输出模式
ofstream app2("file2", ofstream::out | ofstream::app);
```
### string流
|| stringstream流|
-|-
sstream strm; | strm是未绑定的stringstream对象
sstream strm(s); | 绑定s的一个拷贝
strm.str(); | 返回strm保存的string的拷贝
strm.str(s); | 将string s拷贝到strm中，返回void

## chapter9 顺序容器
|| 顺序容器类型|
-|-
vector | 可变大小数组，支持快速随机访问
deque | 双端队列
list | 双向链表
forward_list | 单项链表，没有size操作
array | 固定大小数组
string | 与vector类似，专门保存字符

### 容器定义和初始化
容器初始化为另一个容器的拷贝，可以直接拷贝整个容器，或者拷贝由一个迭代器对指定的元素范围。为了创建拷贝，要求容器的类型和元素的类型都匹配。但使用迭代器参数拷贝则不要求容器类型相同，而且元素类型只要能转化即可。例：
```C++
list<string> authors = {"Milton", "shakespeare", "Austen"};
vector<const char*> articles = {"a", "an", "the"};

list<string> list2(authors); //correct
deque<string> authList<authors); //error! 容器类型不匹配
//正确，const char*可以转化成string
forward_list<string> words(articles.begin(), articles.end());
```
### 标准库array
array标准库的大小也是容器的一部分，用法举例如下：
```C++
array<int, 42> //类型为保存42个int的数组
array<string, 10> //类型为保存10个string的数组

array<int, 10>::size_type i;  //数组类型要包括元素类型和大小
array<iint>::size_type j;     //error!!! array<int>不是一个类型，必须包含大小

array<int, 10> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
array<int, 10> copy = digits; //对于标准库array只要类型相同赋值操作即合法
```
### 赋值和swap
|| 容器赋值运算|
-|-
c1=c2 | 将c1中的元素替换成c2中元素的拷贝
c={a,b,c...} | c中元素替换成初始化列表的拷贝，array不适用
swap(c1, c2) <br> c1.swap(c2) | 交换c1和c2中的元素，两者必须有相同的类型。<br>swap通常比拷贝快很多
assign操作不适用于关联容器和array |
seq.assign(b, e) | seq中的元素替换成迭代器b，e范围中的元素
seq.assign(il) | seq中的元素替换成初始化列表il中的元素
seq.assign(n,t) | seq中的元素替换成n个值为t的元素

赋值相关操作会导致左边容器的迭代器、引用和指针失效。而swap不会，但是指向的容器变了（string和array除外）。

使用举例：
```C++
list<string> names;
vector<const char*> oldstyle;
names = oldstyle;  //error！容器类型不匹配
//可以将const char*转化成string
names.assign(oldstyle.cbegin(), oldstyle.cend());
```
需要注意的是，swap交换array的时候会真正交换他们之间的元素，因此交换两个array所需时间与array中元素数目成正比。因此对array，swap交换后的指针、引用和迭代器绑定的元素保持不变，但是元素值已经变了。

swap函数建议使用非成员版本的swap(a,b)

### 向顺序容器添加元素
|| 顺序容器添加元素操作|
-|-
此类操作会改变容器大小，array不支持|
forward_list有自己的inset和emplace |
forward_list不支持push_back和emplace_back |
c.push_back<t><br>c.emplace_back(*args*) | 在c1的尾部创建一个值为t或者由args创建的元素，返回void
c.push_front<t><br>c.emplace_front(*args*) | 在c1的头部创建一个值为t或者由args创建的元素，返回void
c.insert(p, t)<br>c.implace(p, *args*) | 在迭代器p指向的元素之前创建一个值为t或者由args创建的元素，返回被添加元素的迭代器
c.insert(p, n, t)<br>c.insert(p, b, e)<br>c.insert(p, il) | 在c中迭代器p指向的元素之前插入由括号中的参数指明的一系列元素，返回新添加的第一个元素的迭代器。如果没有元素新添加，则返回p

向一个vector、string或deque插入元素会使得所有指向容器的迭代器、引用和指针失效！！！

添加到容器中的元素是拷贝添加，不会影响到原本的元素，需要注意。此点与Java不同。

emplace函数直接在容器中构造元素，不需要创建一个临时变量再压入容器。传递给emplace函数的参数必须与元素类型的构造函数相匹配。

### 访问元素
|| 顺序容器中访问元素操作|
-|-
at和下标只适用于string、vector、deque和array|
back不适用与forward_list |
c.back() | 返回c中尾元素的引用。如果c为空，函数未定义
c.front() | 返回c中首元素的引用。如果c为空，函数未定义
c[n] | 返回c中下标为n的元素的引用，下标溢出则未定义
c. at[n] | 返回c中下标为n的元素的引用，下标溢出则抛出异常

### 删除元素
|| 顺序容器中访问元素操作|
-|-
这些操作会改变容器大小，不适用于array|
forward_list有特殊的erase操作 |
forward_list不支持pop_back |
vector和string不支持pop_front |
c.pop_back() | 删除c中尾元素，返回void。如果c为空，函数未定义
c.pop_back() | 删除c中首元素，返回void。如果c为空，函数未定义
c.erase(p) | 删除p所指向的元素，返回被删除元素之后元素的迭代器
c.erase(b, e) | 删除b和e指定范围内的元素，返回最后一个被删除的元素之后元素的迭代器

注意，删除deque除了首尾位置之外的任何元素都会使所有迭代器、引用和指针失效。指向vector或string中删除点之后的迭代器、引用和指针都会失效。

### 特殊的forward_list操作
由于单项链表没法获取其前驱，因此很多操作是通过改变迭代器指向元素的后续来实现的，基本操作类型如下：
|| forward_list中插入或删除元素的操作|
-|-
lst.before_begin()<br>list.cbefore_begin| 返回指向链表首元素之前不存在元素的迭代器，不能解引用。
lst.insert_afert(p,t)<br> lst.insert_afert(p,n,t)<br>lst.insert_afert(p,b,e)<br>lst.insert_afert(p,il)| 在迭代器p之后的位置插入元素，如果p是尾后迭代器，则行为未定义。返回一个指向最后一个插入元素的迭代器。
emplace_after(p, *args*) | 使用args在p指定的位置后创建一个元素，返回新元素。p不能使尾迭代器
lst.erase_after(p)<br>lst.erase_after(b, e) | 删除p之后的元素或者删除从b到e之间的元素，然后返回指向被删除元素素之后元素的迭代器。如果不存在这样的元素，返回尾迭代器。p不能使尾元素或者尾迭代器

### 容器操作改变迭代器
```C++
//删除偶数元素，复制每个奇数元素举例
vector<int> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
auto iter = vi.begin();
while (iter != vi.end()) {
    if (*iter % 2) {
        iter = vi.insert(iter, *iter);  //复制当前元素
        iter += 2;
    } else {
        iter = vi.erase(iter);          //删除偶数元素
    }
}
```

### 管理容器的成员函数
|| 容器大小管理操作|
-|-
capacity和reserve只适用于vector和string| 
shrink_to_fit只适用于vector、string和deque| 
c.shrink_to_fit() | 将capacity()减少为和size()相同大小
c.capacity() | 不重新分配，c可以保存多少元素
c.reserve()| 分配至少能容纳n个元素的内存空间

reserve影响的是内存空间，而不是元素数量。resize影响的是元素数量，而不是内存空间。

shrink_to_fit操作并不能保证一定退回空间。vector只有在容量不够的情况下才会扩容。

### 构造string的其他方法
| | |
-|- 
string s(cp, n) | s是cp指向数组的前n个字符的拷贝，此数组至少包含n个字符
string s(s2, pos2) | s从s2的pos2开始拷贝，pos2不能大于s2.size()
string s(s2, pos2, len2)| 拷贝最多len2个字符或者拷贝到s2结尾

用法举例：
```C++
const char *cp = "Hello world!!!";   //end with '\0'
char noNull[] = {'H', 'i'};         //end without '\0'
string s1(cp); //s1 == "Hello world!!!"
string s2(noNull, 2);  //s2 == "Hi"
string s3(noNull);     //undefined! noNull is not end with '\0'
string s4(cp+6, 5);    //s4 == "world"
string s5(s1, 6, 5);   //s5 == s4
string s6(s1, 6);      //s6 == "world!!!"
string s7(s1, 6, 20);  //s7 == s6
string s8(s1, 16);     //throw an out_of_range error
```
string和数字之间的转化，有sto(i/l/ul/ll/ull)代表string to int/long......其中函数可以传三个参数，(s, p, b),p保存第一个非数值字符下标，b表示进制。数字转成string用to_string函数。

## chapter10 范型算法
本章主要讲各种标准库算法的应用，学习这类算法最好的方式就是看源码了，而且对着代码学也相对easy。
```C++
//find
template<class InputIterator, class T>
  InputIterator find (InputIterator first, InputIterator last, const T& val)
{
  while (first!=last) {
    if (*first==val) return first;
    ++first;
  }
  return last;
}

//accumulate
template <class InputIterator, class T>
   T accumulate (InputIterator first, InputIterator last, T init)
{
  while (first!=last) {
    init = init + *first;
    ++first;
  }
  return init;
}

//equal, the lenght of frist2 is at least last1-first1
template <class InputIterator1, class InputIterator2>
  bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
  while (first1!=last1) {
    if (!(*first1 == *first2)) 
      return false;
    ++first1; ++first2;
  }
  return true;
}

//fill
template <class ForwardIterator, class T>
  void fill (ForwardIterator first, ForwardIterator last, const T& val)
{
  while (first != last) {
    *first = val;
    ++first;
  }
}

//copy
template<class InputIterator, class OutputIterator>
  OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
{
  while (first!=last) {
    *result = *first;
    ++result; ++first;
  }
  return result;
}

//replace
template <class ForwardIterator, class T>
  void replace (ForwardIterator first, ForwardIterator last,
                const T& old_value, const T& new_value)
{
  while (first!=last) {
    if (*first == old_value) *first=new_value;
    ++first;
  }
}

//replace_copy
template <class InputIterator, class OutputIterator, class T>
  OutputIterator replace_copy (InputIterator first, InputIterator last,
                               OutputIterator result, const T& old_value, const T& new_value)
{
  while (first!=last) {
    *result = (*first==old_value)? new_value: *first;
    ++first; ++result;
  }
  return result;
}

//unique,保证已排序好的容器中所有元素都唯一
template <class ForwardIterator>
  ForwardIterator unique (ForwardIterator first, ForwardIterator last)
{
  if (first==last) return last;

  ForwardIterator result = first;
  while (++first != last)
  {
    if (!(*result == *first))  
      *(++result)=*first;
  }
  return ++result;
}

//transform
template <class InputIterator, class OutputIterator, class UnaryOperator>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperator op)
{
  while (first1 != last1) {
    *result = op(*first1); 
    ++result; ++first1;
  }
  return result;
}

//fill_n
template <class OutputIterator, class Size, class T>
  OutputIterator fill_n (OutputIterator first, Size n, const T& val)
{
  while (n>0) {
    *first = val;
    ++first; --n;
  }
  return first;     // since C++11
}
```
介绍了fill_n之后，可以看到它每次都是给first赋值。此处引入一个`back_inserter`，接受一个指向容器的引用，返回一个与该容器绑定的插入迭代器。通过该迭代器赋值时，赋值运算会调用`push_back`操作。例：
```C++
vector<int> vec;   //空向量
fill_n(back_inserter(vec), 10, 0);   //根据之前fill_n的实现，该操作可以添加10个0到vec
```
**attention:** 标准库算法对迭代器而不是容器进行操作，因此算法不能直接添加或删除元素。

`stable_sort(a.begin(), a.end(), cmp)`,在通过cmp比较排序之后，对于cmp比较过程中相等的元素按照原有的默认方法进行排序。

### lambda表达式
基本形式`[cpature list](parameter list) -> return type{function body}`;

其中，lambda必须使用尾置返回类型，可以忽略参数列表和返回类型，但必须永远包含捕获列表和函数体，如：`auto f = []{return 42}`，定义了一个f，不接受参数，返回42.返回类型不指定则根据return的代码来推断。

利用lambda表达式的例子：
```C++
//按长度排序，长度相同的按字典序排序
stable_sort(words.begin(), words.end(),
    [](const string &a, const string &b)
        {return a.size() < b.size();});

void biggies(vector<string> &words, vector<string>::size_type sz) {
    elimDups(words);  //将words按字典排序，删除重复单词
    stable_sort(words.begin(), words.end(), isShorter);
    //此处的lambda表达式用捕获列表捕获了所在函数的局部变量sz，不捕获则无法使用sz
    auto wc = find_if(words.begin(), words.end(),
                      [sz](const string &a){return a.size() >= sz;});
}

//for_each
template<class InputIterator, class Function>
  Function for_each(InputIterator first, InputIterator last, Function fn)
{
  while (first!=last) {
    fn (*first);
    ++first;
  }
  return fn;
}

//利用for_each和lambda，可以写出很简单的表达式。如打印所有单词
for_each(words.begin(), words.end(),
        [](const string& s){cout << s << ' ';});
```
**attention**:捕获列表只用于局部非static变量，lambda可以直接使用局部static变量和在它所在函数之外声明的名字

lambda的捕获有值捕获和引用捕获两种，lambda在创建的时候就把被捕获的变量拷贝，例：
```C++
void fun1() {
    size_t v1 = 42;
    auto f = [v1]{return v1;};
    v1 = 0;
    auto j = f();  // j == 42;
}

void fun2() {
    size_t v1 = 42;
    auto f = [&v1]{return v1;};
    v1 = 0;
    auto j = f();  // j == 0;
}
```
lambda捕获指针或引用的时候，很可能到他执行的时候，对象的值已经完全不同了。因此尽量减少捕获的数据量，并且尽量避免捕获指针或引用。

### lambda隐式捕获
可以让编译器自行推断捕获列表，&表示捕获引用方式，=表示值捕获方式。例：
```C++
//sz让编译器自动推断是隐式的值捕获
auto wc = find_if(words.begin(), words.end(),
                      [=](const string &a){return a.size() >= sz;});

```
如果需要对一部分用引用捕获，一部分用值捕获，则可以用显示和隐式捕获相结合的方式，但是捕获列表的第一个元素必须是 = 或者 &，指定默认捕获方式。当使用混合方式的时候，显示和隐式的捕获方式必须是不一样的！！！

#### 可变lambda
利用关键字mutable可以改变lambda表达式对于捕获变量的值。例如：
```C++
void fun3() {
    size_t v1 = 42;
    auto f = [v1]()mutable{return ++v1;};
    v1 = 0;
    auto j = f();  // j == 43;
}

void fun4() {
    size_t v1 = 42;
    auto f = [&v1]()mutable{return ++v1;};
    v1 = 0;
    auto j = f();  // j == 1;
}
```
#### 指定lambda的返回类型
一般情况下，如果一个lambda包含return之外的任何语句，则编译器认为其返回void。此时需要显示的指明返回类型。如：
```C++
transform(vi.begin(), vi.end(), vi.begin(),
          [](int i){return i < 0 ? -i : i;});

//error！！！lambda的函数体包含了两条语句，因此返回类型会推断为void
transform(vi.begin(), vi.end(), vi.begin(),
          [](int i){if(i<0) return -i; else return i;});

//需要显式指明返回类型
transform(vi.begin(), vi.end(), vi.begin(),
          [](int i)->int{if(i<0) return -i; else return i;});
```
### 参数绑定
对于只接受一个一元谓词的函数，如果不用lambda表达式，而调用的函数有需要引用其他参量的时候，需要参数绑定。

#### 标准库bind函数
bind定义在functional头文件中，调用的一般形式为`auto newCallable = bind(callable, arg_list);` 其中arg_list中的参数可能包含_n的名字，n是一个整数，表示占位符。比如_1表示newCallable的第一个参数，_2表示第二个，以此类推。例如：
```C++
bool check_size(const string &s, string::size_type sz) {
    return s.size() >= sz;
}
auto check6 = bind(check_size, _1, 6);  
bool b1 = check6(s);    //check6(s)会调用check_size(s, 6)

//绑定之后可以使用find_if
auto wc = find_if(words.begin(), words.end(), 
            bind(check_size, _1, sz));
```
其中名字_n都定义在一个名为`placeholders`的命名空间中，利用`using namespace std::placeholders;`即可直接用这些占位符。

对于bind的参数，根据占位符的写法分配，例如：
```C++
auto g = bind(f, a, b, _2, c, _1);
g(x, y);  //is equal to f(a, b, y, c, x);
```
一般情况下，bind的那些不是占位符的参数被拷贝到bind返回的可调用对象中。如果想要对这些参数进行修改，必须使用ref函数/cref函数，例如
```C++
for_each(words.begin(), words.end(), 
        [&os, c](const string &s) {os << s << c;});

//下述语句等价于上述语句
for_each(words.begin(), words.end(),
        bind(print, ref(os), _1, ' '));
//os必须用ref来修饰，不然bind会创造其一个拷贝，但IO对象不允许拷贝
```
### 插入迭代器
||插入迭代器操作|
-|-
*it = t | 在it指定大的当前位置插入t。根据it绑定的容器选择调用push_back或者push_front
*it,++it,it++ | 操作均存在，但不会改变it，每个操作都返回it

插入器的三种类型：
+ back_inserter,创建一个使用push_back的迭代器
+ front_inserter， 创建一个使用push_front的迭代器
+ inserter,chuangjiianyige使用onsert的迭代器，该函数接受第二个参数，该参数必须是指向给定容器的迭代器。元素将被插入到给定迭代器所表示的元素之前

例如：
```C++
auto it = inserter(c, iter);
*it = val;
//等价于
it = c.insert(it, val);  //it指向新加入的元素
++it;   //递增it让它指向原来的元素

list<int> lst = {1,2,3,4};
list<int> lst2, lst3;
copy(lst.cbegin(), lst.cend(), front_inserter(lst2));  //lst2包含4,3,2,1
copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin())); //lst3包含1,2,3,4
```
### iostream迭代器
标准库定义了istream_iterator和ostream_iterator一组迭代器对iostream流进行操作

#### istream_iterator操作
||istream_iterator操作|
- | -
istream_iterator<T> in(is); | in从输入流is读取类型为T的值
istream_iterator<T> end; | 读取类型为T的istream_itreator迭代器，表示尾后位置
in1 == in2<br>in1 != in2 | in1和in2必须读取相同类型。如果它们都是尾后迭代器或者绑定到相同输入，则相等
*in | 返回从流中读取的数据
in->mem | 等同于(*in).mem
++in, in++ | 使用元素类型定义的>>运算符从输入流中读取下一个值

使用举例：
```C++
istream_iterator<int> in_inter(cin);    //read int from cin
istream_iterator<int> eof;              //istream尾后迭代器
while (in_iter != eof)
    vec.push_back(*in_inter++);
//or
vector<int> vec(in_inter, eof);         //construct vector using iterator
```

#### ostream_iterator操作
||ostream_iterator操作|
- | -
ostream_iterator<T> out(os); | out将类型为T的值os写到输出流os中
ostream_iterator<T> out(os,d); | 写完os后都输出一个d，d要求是C语言类型的字符串
out = val | 使用元素类型定义的<<运算符向输出流写入下一个值
*out, ++out, out++ | 不做任何事情，返回out本身

```C++
ostream_iterator<int> out_iter(cout, " ");
for (auto e : vec)
    *out_iter++ = e;
cout << endl;
/*  *out_iter++ = e 
can be write as
    out = e;
but recommon the first style
*/

copy(vec.cbegin(), vec.cend(), out_iter);
cout << endl;
```

### 反向迭代器
rbegin, rend, crbegin, crend为反向迭代器，利用反响迭代器可以实现sort的逆序排序

反响迭代器使用.base()操作后可以变回普通迭代器，位置会对应往前移一格。

### 链表特有的操作
||list和forward_list成员函数版本的算法|
- | -
此类操作都返回void |
lst.merge(lst2)<br>lst.merge(lst2, comp) | merge操作，第二个版本利用comp进行比较
lst.remove()<br>lst.remove_if(pred) | 等价于erase操作
lst.reverse() | 反转lst中元素的顺序
lst.sort()<br>lst.sort(cmp) | 对list进行排序
lst.unique()<br>lst.unique(pred) | 对list去重

对lsit的insert操作定义了`lst.splice()和flst.splice_after()`操作

链表的特有操作会改变容器

### 5种类型的迭代器
1.Input Iterator用于读取序列中的元素，支持以下操作
+ 比较两个迭代器的相等和不相等运算符(==和!=)
+ 用于推进迭代器的后置和前置递增运算(++)
+ 用于读取元素的接应用运算符(*)，解引用只会出现在赋值运算符右侧（即不可修改，只可读)
+ 箭头运算符(->)
+ 只能单次扫描

2.Output Iterator只写不读的，支持以下操作
+ ++
+ 解引用(*)，只会出现在赋值运算符的左侧，向其赋值则为写入元素值
+ 只能单次扫描

3.forward iterator
+ 可读写
+ 多遍扫描
+ 只能递增

4.bidirectional iterator
+ 可读写
+ 多遍扫描
+ 可递增，可递减

5.random-access iterator
+ 可读写
+ 多遍扫描
+ 支持全部迭代器运算

## chapter11 关联容器
关联容器主要有map和set两种，从而引申有multimap，multiset，unordered_map,unordered_set,unordered_multiset和unordered_multimap

### 关键字类型的自定义比较
某个类型如果定义了严格弱序的\<运算符,那么它可以用作关键字类型。对于set，还可以使用以下方式：
```C++
bool compareIsbn(const Sales_data &lhs, const Sales_date &rhs) {
    return lhs.isbn() < rhs.isbn();
}

/**
 * 为了使用自定义的操作，定义multiset的时候必须提供两个类型：关键字类型和比较操作函数指针
 * 定义此类型的对象时，提供对象名后()跟着对应的函数地址
**/
multiset<Sales_data, decltype(compareIsbn)*>
        bookstore(compareIsbn);
```
### pair类型
pair的数据成员是public的，有first和second两个成员分别来访问。
||pair上的操作|
- | -
pair<T1, T2> p; | p是一个pair，T1和T2成员进行值初始化
pair<T1, T2> p(v1, v2); | p用(v1, v2)来初始化
pair<T1, T2>p = {v1, v2}; | 等价为p(v1, v2)
make_pair(v1, v2) | 返回v1和v2初始化的pair，类型由v1和v2推断
p.first/p.second | 返回p的名为first/second的公有数据成员
p1 *relop* p2 | 根据关系运算符字典定义。先判断first大小，如果相同再根据second大小进行比较
p1 == p2<br>p1 != p2 | 当first和second分别相等的时候，pair相等。利用 == 来判断相等性

使用举例：
```C++
pair<string, int>
process(vector<string> &v) {
    if(!v.empty())
        return {v.back(), v.back().size()}; //列表初始化
    else
        return pair<string, int>();     //隐式构造返回值
}
```
### 关联容器操作
||关联容器额外的类型别名|
- | -
key_type | 此容器类型的关键字类型
mapped_type | 每个关键字关联的类型，只适用于map
value_type | 对于set，和key_type相同，对于map为pair<const key_type, mapped_type>

用法举例：
```C++
set<string>::value_type v1;     //v1 is a string
set<string>::key_type v2;       //v2 is a string
map<string, int>::value_type v3;//v3 is a pair<const string, int>
map<string, int>::key_type v4;  //v4 is a string
map<string, int>::mapped_type v5; //v5 is a int
```
### 关联容器迭代器
解引用一个关联容器迭代器的时候，类型为value_type，对map是pair类型，其first成员保存的关键字是const类型的。

对于set，其迭代器是const的。即set中的关键字是只读的，不能更改

### 添加元素
set用insert添加元素，有两种写法，如下：
```C++
vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
set<int> set2;
set2.insert(ivec.begin(), ivec.end());
set2.insert({1, 3, 5, 7, 1, 3, 5, 7});
```
对map进行insert的时候，有以下四种方法：
```C++
word_count.insert({word, 1});
word_count.insert(make_pair{word, 1});
word_count.insert(pair<string, int>(word, 1));
word_count.insert(map<string, int>::value_type(word, 1));
```
关联容器的insert可以是一个对象，一个迭代器范围，一组{}的内容，也可以用emplace。

对于insert的返回值，如果是不含重复关键字的容器，返回一组pair，first是一个迭代器，指向关键字元素(value_type)，second指向bool，false表示容器中已有该元素，true表示插入成功。但对于multiset和multimap会返回一个指向新元素的迭代器。例如：
```C++
//统计每个单词在输入中出现次数的一种繁琐的方法
map<string, size_t> word_count;
string word;
while (cin >> word) {
    auto ret = word.insert({word, 1});
    if (!auto->second)
        ++ret.first->second;
}
```
### 删除元素
||关联容器删除元素操作|
- | -
c.erase(k) | 从c中删除关键字为k的元素，返回删除的元素数量
c.erase(p) | 从c中删除迭代器指向的元素，返回p指向元素之后元素的迭代器。p不能使end()
c,erase(b, e) | 删除b，e区间范围的元素，返回e

### map的下标操作
此类操作一般比较熟悉，需要注意的一点是，map下标操作返回的类型是mapped_type,而迭代器解引用返回的是value_type

### 关联容器查找元素
||在关联容器中查找元素的操作|
- | -
| |lower_bound和upper_bound不适用于无序容器
| |下标和at只能用于非const的map和unordered_map
c.find(k) | 返回一个迭代器，指向第一个关键字为k的元素。k不存在则返回尾后迭代器
c.count(k) | 返回关键字k的元素数量
c.lower_bound(k) | 返回一个迭代器，指向第一个关键字不小于k的元素
c.upper_bound(k) | 返回一个迭代器，指向第一个关键字大于k的元素
c.equal_bound(k) | 返回一个pair，表示关键字等于k的元素范围。如果k不存在，pair两个成员为end

lower_bound和upper_bound的一种用法：
```C++
//authors is a multimap
for (auto beg = authors.lower_bound(search_item),
          end = authors.upper_bound(search_item);
    beg != end; ++beg)
    cout << beg->second << endl;

//上面循环的一种等价写法
for (auto pos = authors.equal_range(search_item);
     pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl;
```
如果关键字不在容器中，lower_bound会返回关键字的第一个安全插入点。

### 无序容器
无序容器是用hash实现的，由一组桶来映射元素，hash_value相同的元素保存在相同的桶中。
||无序容器管理操作|
- | -
**桶接口** |
c.bucket_count() | 正在使用的桶数目
c.max_bucket_count() | 容器可以容纳的最多的桶数目
c.bucket_size(n) | 第n个桶中有多少个元素
c.bucket(k) | 关键字k在哪个桶中
**桶迭代** |
local_iterator | 用来访问桶中元素的迭代器类型
const_local_iterator | const版本迭代器
c.begin(n), c.end(n) | 桶n的首尾迭代器
c.cbegin(n), c.cend(n) | 桶n的首尾迭代器，类型为const_local_iterator
**哈希策略** |
c.load_factor() | 每个桶的平均元素数量，float
c.max_load_factor() | c试图维护的平均桶大小，float
c.rehash(n) | 重组存储，bucket_count >= n且满足load_factor要求
c.reserve(n) | 重组存储，使得c可以保存n个元素且不必rehash

利用无序容器装填自定义类型的时候，必须提供自己的hash版本。详细内容见16章。

## chapter12 动态内存
静态内存保存局部static、类static数据成员，以及定义在函数之外的变量。栈用来保存函数内非static对象。动态分配的对象在堆区。

一般的分配中，new需要delete。但是用智能指针，可以自动释放对象。C++中有三种智能指针，shared_ptr允许多个指针指向同个对象，unique_ptr独占所指向的对象和weak_ptr指向shared_ptr所管理的对象。

### shared_ptr
||shard_ptr和unique_ptr公有操作|
-|-
shared_ptr<T> sp<br>unique_ptr<T> up | 空智能指针，指向类型为T的对象
p / *p / p->mem |和普通指针用法一样
p.get() | 返回p中保存的指针。如果智能指针释放了对象则指向的对象消失
swap(p, q)<br>p.swap(q) | 交换p和q中的指针

||shared_ptr独有的操作|
-|-
make_shared<T>(*args*) | 返回一个shard_ptr，指向动态分配的类型为T的对象，用args初始化对象
shared_ptr<T> p(q)<br>p = q | p是q的拷贝，q中的指针必须能转化为T*
p.unique() | return p.use_count == 1;
p.use_count() | 返回与p共享对象的智能指针数量

使用举例：
```C++
//p1指向值为42的int
shared_ptr<int> p1 = make_shared<int>(42);
//p2指向“9999999999”的string
shared_ptr<string> p2 = make_shared<string>(10, '9');
//p3指向值为0的int
shared_ptr<int> p3 = make_shared<int>();
//简便写法
auto p4 = make_shared<vector<string>>();
```
对于shared_ptr，如果放到容器中之后，指向的对象不需要再使用，最好用erase删除之，从而释放不必要的内存。

使用动态内存的原因之一是允许多个对象共享相同的状态，而不需要对其进行一一拷贝。例子见chapter12文件夹下的StrBlob.cc文件。

### 直接内存管理
C++可以用new和delete来分配和释放动态内存。但是相比于智能指针，直接内存管理的类不能依赖类对象拷贝、赋值和销毁操作的任何默认定义。

默认情况下，动态分配的对象是默认初始化的。但也可以用直接初始化的方式来构建（使用圆括号或者花括号）。当提供括号包围的初始化器，可以用auto，例如：
```C++
auto p1 = new auto(obj);    //p指向一个与obj类型相同的对象，该对象用obj初始化
auto p2 = new auto{a, b, c};//错误，括号中只能有一个初始化器，否则无法推断类型
```
利用const可以动态分配const对象，此时new返回的指针是一个指向const的指针。

当内存不足，无法满足new的需求时，会抛出bad_alloc异常，但是可以改变new的方式来阻止异常，如：
```C++
int *p1 = new int;              //if allocate failed, throw std::bad_alloc
int *p2 = new (nothrow) int;    //if failed, return a nullptr
```
对于new的空间，使用完之后记得delete。但是不能释放非new的空间，或者将相同指针值释放多次。编译器只能判断delete的对象是否为指针，不能检测出上述错误。例如：
```C++
int i, *pi1 = &i, *pi2 = nullptr;
double *pd = new double(33), *pd2 = pd;
delete i;   //error, i is not a pointer
delete pi1; //undefined! pi1 point to a local variable
delete pd;  //correct
delete pd2; //undefined! the memory pd2 point to has been freed
delete pi2; //delete a nullptr is always right
```
### shared_ptr和new结合使用
可以用new返回的指针来初始化智能指针。但是智能指针的构造早函数explicit的，因此不能将内置指针隐式转化成智能指针，必须直接初始化。例如：
```C++
shared_ptr<double> p1;              //p1 point to a double
shared_ptr<int> p2(new int(42));    //p2 point to a int values 42
shared_ptr<int> p = new int(1024);  //error! explicit必须直接初始化不能拷贝构造
shared_ptr<int> clone(int p) {
    return new int(p);              //error! 不能隐式转化成智能指针
}
shared_ptr<int> clone(int p) {
    return shared_ptr<int>(new int(p));   //correct!    
}
```
智能指针和普通指针之间不要混合使用，否则会发生错误。一旦把一个智能指针绑定到普通指针后，内存管理的任务就是智能指针来负责，不要再用内置指针访问智能指针指向的内存。一个典型的错误：
```C++
void procee(shared_ptr<int> ptr) {
    //using ptr
} //ptr is deleted

int *x(new int(1024));
process(x);  //error!
process(shared_ptr<int>(x));  //correct
int j = *x;         //undefined! x is a dangling pointer
```
由于x交给智能指针托管，传入函数后，ptr在离开函数的时候就被销毁，智能指针指向的空间计数成了0,则空间被释放，导致原先的x成了悬空指针

智能指针有get函数，返回一个内置指针，指向智能指针管理的对象。get返回指针的代码不能delete该指针，并且不能让get初始化另一个智能指针。例如：
```C++
shared_ptr<int> p(new int(42));
int *q = p.get();

{
    shared_ptr<int>(q);
}//q has been deleted
int foo = *p;  //error!
```
和前面一样，让智能指针托管q之后，离开作用域，则q指向的空间被销毁，q指向的空间也是p指向的空间，会发生严重的错误！get函数返回的是内置指针，各自的引用计数都是1 ！！！

智能指针也可以用来管理非动态内存，但此时要注意构造的时候传递一个删除器来代替delete操作。

正确使用智能指针的一些规范：
+ 不使用相同的内置指针初始化或reset多个只能指针
+ 不delete get()返回的指针
+ 不使用get()初始化或reset另一个智能指针
+ 使用的智能指针管理的资源不是new分配的，需要传递一个删除器

总而言之，尽量不要浑用普通指针和动态指针。因为用普通指针创建智能指针的时候初始引用计数是1,即便已经创建过一次了。

### unique_ptr
||unique_ptr特有操作|
- | -
unique_ptr<T> u1<br>unique_ptr<T, D> u2 | 空的unique_ptr，指向类型为T的对象。<br>u1会用delete释放指针，u2用类型为D的可调用对象释放指针
unique_ptr<T, D> u(d) | 空ptr，用类型为D的对象d代替delete
u = nullptr | 释放u指向的对象，将u置空
u.release() | u放弃对指针的控制权，返回指针并置空u，但u指向的空间没有释放！
u.reset()<br>u.reset(q)<br>u.reset(nullptr) | 释放u指向的对象<br>如果提供了内置指针q，令u指向这个对象<br>否则u置空

使用举例：
```C++
unique_ptr<string> p1(new string("stegosaurus"));
unique_ptr<string> p2(p1);  //unique_ptr不支持拷贝
unique_ptr<string> p3;
p3 = p2;                    //unique_ptr不支持赋值

unique_ptr<string> p2(p1.release());    //p1置空
unique_ptr<string> p3(new string("Trex"));
p2.reset(p3.release());                 //reset释放p2原来指向的内存
```
对于unique_ptr，当我们拷贝或者赋值一个即将被销毁的unique_ptr时，是允许的。最常见的是从一个函数返回unique_ptr。

unique_ptr初始化的时候需要绑定到一个new构建的对象上，否则报错！！！

### weak_ptr
weak_ptr不控制指向对象的生存周期，指向一个shared_ptr管理的对象。与shared_ptr绑定之后，不会改变shared_ptr的引用计数。

||weak_ptr操作|
- | -
weak_ptr<T> w<br>weak_ptr<T> w(sp) | 初始化一个weak_ptr
w = p | p是一个shared或者weak_ptr，赋值后两者共享对象
w.reset() | 将w置空
w.use_count() | 与w共享的shared_ptr的数量
w.expired() | return w.use_count == 0;
w.lock() | 如果expired为true,返回空的shared_ptr,否则返回一个指向w的对象的shared_ptr

由于对象可能不存在，因此不能用weak_ptr直接访问对象，而必须调用lock。例如：
```C++
if(shared_ptr<int> np = wp.lock()) {

}
```
上述循环中，当wp指向的对象存在才会进入，循环结束后np的生命周期结束。否则不进入循环，保证安全。

### new和数组
利用new动态分配数组之后，分配的只是一个数组元素类型的指针，该内存并不是数组类型，无法对动态数组调用begin和end等操作。对于数组的delete，需要在delete后跟[]，销毁顺序为数组元素的逆序

### 智能指针和动态数组
unique_ptr可以用来管理动态数组，管理动态数组的时候，一旦release则调用delete[\]销毁管理的数组。当其管理动态数组的时候，不能用->运算符，可以用[]取下标。例如：
```C++
unique_ptr<int[]> up(new int[10]);
up.release();               //auto call delete[]
for (size_t i = 0; i != 10; ++i)
    up[i] = i;
```
如果要用shared_ptr管理动态数组，必须提供自己的删除器，不然调用的是delete不是delete[]会出错。而且访问元素的时候没有下标访问方式，不建议使用。例子如下：
```C++
shared_ptr<int> sp(new int[10], [](int *p){delete[] p;});
sp.reset();         //利用lambda表达式调用delete[]
for(size_t i = 0; i != 10; ++i)
    *(sp.get() + i) = i;
```

### allocator类
||allocator类及算法|
- | -
allocator<T> a | a为allocator类对象，可以为T类型的对象分配内存
a.allocate(n) | 分配原始、未构造的内存，可以保存n个类型为T的对象
a.deallocate(p, n) | 释放T*指针p中地址开始的内存。释放之前必须对每个元素都调用destory
a.construct(p, *args*) | 利用args在p指向的内存中构造一个对象
a.destory(p) | 对p的对象执行析构函数

使用举例：
```C++
allocator<string> alloc;
auto const p = alloc.allocate(n);       //可以分配n个未初始化的string
auto q = p;                             
alloc.construct(q++);                   //*q为空字符串
alloc.construct(q++, 10, 'c');          //*q为cccccccccc
alloc.construct(q++, "hi");             //*q为hi

while(q != p)
    alloc.destory(--q);                 //释放构造的string

alloc.deallocate(p, n);                 //释放内存
```
针对allocator，有四种常用的算法，分别是：
+ `uninitialized_copy(b, e, b2)`,将b->e区间的内容拷贝到b2开始的区间
+ `uninitialized_copy_n(b, n, b2`，将n个b拷贝到b2开始的区间
+ `uninitialized_fill(b, e, t)`，在b到e区间创建对象，对象值均为t
+ `uninitialized_fill(b, n, t)`，在b开始的区间创建n个值为t的对象
+ 四种算法的返回值都是最后一个构造的元素之后的位置

## chapter13 拷贝控制
对于C++而言，必须定义对象拷贝、移动、赋值或者销毁的时候做哪些事情，编译器可能会帮我们默认定义，但是可能做的事情并不是我们所想的，因此需要程序员显示完成。

### 拷贝构造函数
一个构造函数，第一个参数是自身类类型的引用，且任何额外的参数都有默认值，则此构造函数是拷贝构造函数。例如：
```C++
class Foo {
public:
    Foo();              //默认构造函数
    Foo(const Foo&);    //拷贝构造函数
};
```
对于一个类，即便已经定义了拷贝构造函数，编译器也会为我们定义一个合成拷贝构造函数，将参数成员逐个拷贝到正在创建的对象中。如果元素是类类型，那么调用其拷贝构造函数来进行拷贝。

会发生拷贝初始化的情况：
+ 用 = 定义变量的时候
+ 将一个对象作为实参传递给一个非引用类型的形参
+ 从一个返回类型为非引用类型的函数返回一个对象
+ 用花括号列表初始化一个数组中的元素或者聚合类的成员

注意对于标准库容器的对象，insert是拷贝，emplace是直接初始化的！对于explicit的构造函数，拷贝初始化有限制，例如：
```C++
vector<int> v1(10);         //直接初始化
vector<int> v2 = 10;        //error! 接受大小参数的构造函数是explicit的
void f(vector<int>);        //f参数进行拷贝初始化
f(10);                      //error! 不能用explicit构造函数拷贝一个实参
f(vector<int>(10));         //从一个int直接构造一个临时vector
```
拷贝构造函数一般是初始化的使用，利用拷贝初始化进行。而对于后期，两个相同的类型进行赋值操作的时候，会用到拷贝赋值运算符，自己写的类里面需要重载之。同样，编译器也会默认构建一个。

通常对于拷贝赋值运算符，如果运算符是个成员函数，其左侧运算对象就绑定到隐式的this参数。赋值运算符通常返回一个指向其左侧运算对象的引用，例如：
```C++
Sales_data&
Sales_data::operator=(const Sales_data &rhs) {
    bookNo = rhs.bookNo;
    units_sold = rhs.unit_sold;
    revenue = rhs.revenue;
    return *this;
}
```
### 析构函数
析构函数由~加上类名构成，没有返回值，也不接受任何参数。不能被重载，一个类只会有唯一一个析构函数。对于构造函数，成员初始化是构造函数函数体之间完成的。对于析构函数，首先执行函数体，然后销毁成员。成员按照初始化（即定义的）顺序逆序销毁。

注意，隐式销毁一个内置指针类型的成员不会delete其指向的对象。当一个对象的引用或指针离开作用域的时候，析构函数不会执行。

析构举例：
```C++
{//新作用域
    //p和p2指向动态分配的对象
    Sales_data *p = new Sales_data;
    auto p2 = make_shared<Sales_data>();
    Sales_data item(*p);
    vector<Sales_data> vec;
    vec.push_bak(*p2);
    delete p;           //对p指向的对象执行析构函数
}//推出局部作用域，对item、p2和vec调用析构函数
 //销毁p2会递减引用计数，如果变为0,对象被释放
 //销毁vector会销毁其元素
```
注意析构函数体本身并不直接销毁成员，成员是在析构函数体之后隐含的析构阶段被销毁的。

两大设计原则：
+ 一个类需要自定义析构函数，几乎肯定他也需要自定义拷贝赋值运算符和拷贝构造函数
+ 一个类需要自定义拷贝构造函数 or 拷贝赋值运算符，那么也需要另一半。而对于析构函数，不一定需要自定义

拷贝控制成员和析构函数也可以用 = default要求编译器合成默认版本。在类内写则是inline的。

### 阻止拷贝
对于一些特殊的类，比如IO类，需要编写拷贝构造函数来阻止拷贝。

#### 定义删除的函数
在函数参数列表上写 = delete表示希望将其定义为删除的，例如：
```C++
struct NoCopy{
    NoCopy() = default;
    NoCopy(const NoCopy &) = delete;    //阻止拷贝
    NoCopy& operator=(const NoCopy&) = delete;  //阻止赋值
    ~NoCopy() = default;  
};
```
=default和=delete的不同之处：
+ =delete必须出现在函数第一次声明的时候
+ 可以对任何函数使用=delete

如果析构函数被删除，那么不能定义这种类型的变量或成员，但可以动态分配这种类型的对象。但是无法释放，如：
```C++
struct NoDtor{
    NoDtor() = default;
    ~NoDtor() = delete;
};
NoDtor nd;                  //error!
NoDtor *p = new NoDtor();
delete p;                   //error!
```
如果一个类有数据成员不能默认构造、拷贝、赋值或销毁，那么对应的成员函数将被定义为删除的。

新标准前，将拷贝和赋值函数定义为私有的来阻止拷贝和赋值，但是无法对友元和类内函数的拷贝和赋值进行阻止。因此，尽量使用=delete的新标准。

### 交换操作
重排元素顺序的算法会调用swap，一个类最好能定义自己的swap操作。一个典型的swap实现如下：
```C++
class HasPtr{
    friend void swap(HasPtr&, HasPtr&);
};

inline
void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);  //交换的是指针，不是string数据
    swap(lhs.i, rhs.i);
}
```
对于以上定义好的swap，当调用的时候，必须调用HasPtr的swap而不是std::swap。例如现在有个Foo的类，它有个类型为HasPtr的成员h，则编写Foo的swap：
```C++
void swap(Foo &lhs, Foo &rhs) {
    //error! 用了std的swap而不是HasPtr的swap
    std::swap(lhs.h, rhs.h);
}

void swap(Foo &lhs, Foo &rhs) {
    using std::swap;
    swap(lhs.h, rhs.h); //使用HasPtr版本的swap
}
```
利用swap的一个例子：
```C++
HasPtr& HasPtr::opreator=(HasPtr rhs){
    swap(*this, rhs);   //rhs现在指向本对象层使用的内存
    return *this;       //rhs被销毁，从而delete了rhs中的指针
}
```
该版本中，右侧运算对象以传值的方式传递给赋值运算符，则rhs是右侧运算对象的一个副本。参数传递的时候会拷贝该对象的string副本。因为是有副本拷贝，因此天然是异常安全的，能够保证自赋值的正确性。

### 移动构造函数和std::move
对于string在内的标准库都提供了移动构造函数。它通常是将资源从给定对象“移动”而不是拷贝到正在创建的对象。标准库utility下的std::move可以调用对应的移动构造函数。

IO类和unique_ptr类可以移动但不能拷贝，标准库容器、string和shared_ptr类既支持移动也支持拷贝。

### 右值引用
右值引用只能绑定到一个将要销毁的对象上，通过&&来获取右值引用。它可以绑定右值，但不能绑定左值。例如：
```C++
int i = 42;
int &r = i;             //r是个左值引用，引用i
int &&rr = i;           //错误，rr是个右值引用，i是个左值
int &r2 = i * 42;       //错误，r2是个左值引用，i×42是右值
const int &r3 = i * 42; //正确，可以将const引用绑定在右值上
int &&rr2 = i * 42;     //正确，rr2绑定到乘法结果上
```
右值只能绑定到临时变量（普通变量是左值），因此：
+ 右值引用的对象即将被销毁
+ 该对象没有其他的用户
+ 使用右值引用的代码可以自由地接管所引用的对象的资源
+ 返回引用的函数是左值，否则是右值

对于标准库的move函数，可以显示地将一个左值转化为对应的右值引用类型。例如：
```C++
int &&rr3 = std::mobe(rr1);     //OK!
```
使用move意味着对rr1赋值或者销毁它以外，不能再对他进行任何操作。

### 移动构造函数和移动赋值运算符
为了让自己的类也可以进行移动和拷贝，需要定义移动构造函数和移动赋值运算符。这些函数的第一个参数是该类类型的一个右值引用。此外外，还必须保证移后源对象处于销毁无害的状态。例如：
```C++
StrVec::StrVec(StrVec &&rhs) noexcept:
        elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap) {
    rhs.elements = rhs.cap = rhs.first_free = nullptr;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept {
    if (&rhs != this) {     //自赋值检测
        free();
        elements = rhs.elements;
        cap = rhs.cap;
        first_free = rhs.first_free;
        rhs.elements = rhs.cap = rhs.first_free = nullptr;
    }
} 
```
对于移动操作，通常需要用noexcept指明不抛出异常。noexcept在定义和声明的时候都必须写上。需要写noexcept原因在于：
+ 移动操作虽然通常不抛出异常，但是抛出异常也是允许的
+ 标准库容器能对异常发生时的自身行为提供保障，例如vector保证push_back时发生异常，自身不会改变。但是移动操作的时候，一旦发生异常，自身已经被改变了，因此需要显示告诉编译器不要抛出异常。

移动后，源对象必须是有效的、可以析构的状态，但使用胡不能对其值进行任何的假设。

只有当一个类没有定义任何自己版本的拷贝控制成员，且类的每个非static数据成员都可以移动时，编译器才为他合成移动构造函数或移动赋值运算符。例如：
```C++
//编译器会为X和hasX合成移动操作
struct X {
    int i;          //内置类型可以移动
    std::string s;  //string定义了自己的移动操作
};
struct hasX {
    X mem;          //X有合成的移动操作
};
X x, x2 = std::move(x);         //使用和成的移动构造函数
hasX hx, hx2 = std::move(hx);   //使用和成的移动构造函数
```
移动操作和拷贝构造函数的关系：
+ 当定义了一个移动构造函数或者移动赋值运算符的时候，必须定义自己的拷贝函数，否则会默认认为是删除的。
+ 当一个类的成员定义了自己的拷贝构造函数但没有定义移动构造哦函数，或者编译器不能为他合成移动构造函数，移动构造函数就被认为是删除的。
+ 移动构造函数或者移动赋值运算符两者有一个被定义为删除的，则另一个也是删除的
+ 析构函数如果是删除的，那么移动构造和移动赋值运算符都是删除的
+ 有类成员是const或者引哟哦嗯，那么移动赋值运算符被定义为删除的
```C++
//假设Y是一个类，定义了自己的拷贝构造函数但没有定义自己的移动构造函数
struct hasY {
    hasY() = default;
    hasY(hasY&&) = default;
    Y mem;  //hasY将有一个删除的移动构造函数，即使声明了default也不行，除非显示定义
};
hasY hy, hy2 = std::move(hy);   //error! 移动构造函数是删除的！
```
如果没有移动构造函数（移动构造函数是删除的除外），则右值运算的时候实际上是调用了拷贝构造函数，即把&&转化为一个const的&。例如：
```C++
class Foo{
public:
    Foo() = default;
    Foo(const Foo&);    //拷贝构造函数
    //Foo未定义移动构造函数
};
Foo x;                 
Foo y(x);               //拷贝构造函数,x是一个左值
Foo z(std::move(x));    //拷贝构造函数，因为没有定义移动构造函数
```
#### 拷贝并交换赋值运算和移动操作
```C++
class HasPtr {
public:
    //添加的移动构造函数
    HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) {p.ps = 0;}
    //赋值运算既是移动赋值运算符，也是拷贝赋值运算符
    HasPtr& operator=(HasPtr rhs) {
        swap(*this, rhs);
        return *this;
    }
    //其他成员的定义
};
```
上述示例代码中，添加了一个移动构造函数，则单一的赋值运算符就实现了拷贝赋值运算符和移动赋值运算符两个操作。因为该运算符的参数是非引用的，意味着该参数要进行拷贝初始化。依赖参数的类型，左值拷贝初始化用拷贝构造函数，右值用移动构造。

#### 右值和左值引用成员函数
对于右值也可以进行赋值操作，但是不会改变原有的内容。例如：
```C++
string s1("a"), s2("b");
s1 + s2 = "main";
```
上述代码中，`s1+s2`是一个右值，对右值进行赋值，并不会改变s1和s2的内容。如果自己的类中，需要指定函数的运算对象只能是左值或者只能是右值，那么需要在参数列表后放置一个引用限定符，如：
```C++
class Foo {
public:
    Foo &operator=(const Foo&) &;       //函数参数列表外的&表示只能向可修改的左值赋值
};
Foo &Foo:operator=(const Foo&) & {      //该符号在定义和声明的时候都要写
    //...
    return *this;
}
```
如果一个函数同时用了const和引用限定，那么限定符必须跟在const后面，即const &或者const &&形式。

如果一个成员函数有引用限定符，则具有相同参数列表的所有版本都必须有引用限定符！！！而对于const，可以一个版本有一个无。例如：
```C++
class Foo {
public:
    Foo sorted() &&;
    Foo sorted() const;         //error! 必须有引用限定符
    using comp = bool(const int&, const int&);
    Foo sorted(comp*);
    Foo sorted(comp*) const;    //正确，两个版本都没有引用限定符
};
```
对于右值进行的函数，可以任意在原对象上改修，对于左值则必须拷贝一份，不能在原对象上任意修改。

## 重载运算与类型转换
### 基本概念
+ 重载运算符是成员函数时，this绑定到左侧运算对象
+ 对于运算符函数，至少有一个类类型的参数
+ 只能重载已有的运算符
+ 对于既可以是一元运算符又可以是二元运算符的符号，可以从参数的数量上推断
+ 无论符号是否重载，优先级和结合率都不会改变

使用重载的运算符，本质上是一次函数调用。因此这些关于运算对象求值顺序的规则无法应用到重载的运算符上。基于此，`&&  ，  &  ||`不建议重载。

使用重载运算符应该与内置类型一致：
+ 类如果执行IO，则定义移位预算符使其与内置类型的IO一致
+ 类的某个操作是检查相等性，那么定义operator==。此外最好也定义operator！=
+ 如果有单序比较操作，定义operator<,以及其他关系操作
+ 逻辑运算和关系运算返回bool，算数运算返回类类型的值，赋值和复合赋值运算符返回左侧运算对象的一个引用

重载运算符作为成员还是非成员函数：
+ 赋值（=）、下标（[]）、调用（()）和成员访问（->）运算符必须是成员
+ 复合赋值运算符一般来说是成员，但也不一定
+ 改变对相撞太或者与给定类型密切相关的运算符，如递增、递减、解引用等通常是成员
+ 对称性的运算符可能转化任意一端的运算对象，通常是普通的非成员函数

### 输入和输出运算符
### 重载输入输出运算符
通常情况下，输出运算符的第一个形参是非常量的ostream对象的引用，第二个是常量的引用。输出运算符尽量减少格式化操作，该部分留给用户自行控制。例：
```C++
ostream& operator<<(ostream &os, const Sales_data &item) {
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}
```
输入输出运算符必须是非成员函数，否则其左侧运算对象将变为类的一个对象，如：
```C++
data << cout;   //data将输出运算符写作成员函数的用法
```
对于输入运算符，与输出运算符不同的是，必须能够处理输入失败的情况，例：
```C++
istream& operator>>(istream &is, Sales_data &item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)
        item.revenue = item.units_sold * price;
    else 
        item = Sales_data();        //判断输入是否失败
    return is;
}
```
输入错误一般有：
+ 流错误类型的数据时，读取操作会失败
+ 遇到eof或者与到输入流的其他错误

对于这些错误，一次性验证即可，像上述代码示例。

### 算术和关系运算符
算数运算符使用举例：
```C++
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += lhs;
    return sum;
}
```
对于算数运算符的重载，一般会把对应的复合赋值运算符也重载。在算数运算符里面调用重载的复合赋值运算符来实现是一般的做法。

#### 相等运算符
一般 == 和 != 运算符两者要一起出现，而且 != 中可以简单调用 == 运算取反的结果即可。

#### 关系运算符
对于 < 运算符，如果存在唯一一种可靠的 < 定义，则可以重载。当类内也同时包含 == 时，当且仅当 < 的定义和 == 产生的结果一致才可以定义 < 运算符。

例如对于Sales_data类，如果定义 < 运算符，利用isbn的大小來排序，那么会出现，当两个对象不相等的时候(!= 重载的时候需要所有成员一样才返回false)两者谁都不比谁小，会出现不必要的歧义。

### 赋值运算符
赋值运算符一般需要作为成员函数，可以有多种不同类型的重载，代表不同形式的赋值操作。例如：
```C++
class StrVec {
public:
    StrVec &operator=(std::initializer_list<std::string>);
    //...
};
StrVec &StrVec operator=(std::initializer_list<std::string> il) {
    auto data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
```
### 下标运算符
表示容器的类通常可以通过元素在容器中的位置访问元素，这些类一般会定义operator[]，且必须是成员函数。

下标运算符通常以所访问元素的引用作为返回值，这样下标就可以出现在赋值运算的任何一端。并且最好定义常量和非常量的版本。例：
```C++
class StrVec {
public:
    std::string& operator[](std::size_t n)
        {return elements[n];}
    const std::string& operator[](std::size_t n) const
        {return elements[n];}
private:
    std::string *elements;          //指向数组首元素的指针
};
```
### 递增和递减运算符
递增递减运算符因为会改变所操作对象状态，建议设为成员函数。定义递增和递减运算符的类应该同时定义前置和后置的版本。重载的一个例子：
```C++
class StrBlobPtr {
public:
    //前置版本
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    //后置版本
    StrBlobPtr operator++(int);
    StrBlobPtr operator++(int);
    //......
};

StrBlobPtr& StrBlobPtr::operator++() {
    //check(...)
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
    --curr;
    //check(...)
    return *this;
}

StrBlobPtr StrBlobPtr::operator++() {
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator--() {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

StrBlobPtr p(a1);
p.operator++(0);            //后置版本
p.operator++();             //前置版本
```
前置版本中函数不需要参数，后置版本设置了一个额外的不适用的int形参，从而来进行区分是前置还是后置版本。前置版本返回的是引用，后置版本则不是。调用的时候也可以显示的调用。

### 成员访问运算符
先举一个使用的例子：
```C++
class StrBlobPtr {
public:
    std::string& operator*() const {
        auto p = check();
        return (*p)[curr];          //*p是对象所指的vector
    }

    std::string* operator->() const {
        return & this->operator*();
    }
};
```
对于*运算符的重载比较好理解，返回当前对象的某个内容即可。关键是要理解 -> 运算符。例如对于point->mem举例，根据point的不同，可以有两种等价方式
+ `(*point).mem   //point是一个内置的指针类型`
+ `point.operator()->mem    //point是一个类的对象`

其执行过程为：
+ 如果point是指针，则应用内置的箭头运算符，先解引用该对象再获取对应的成员
+ 如果point是定义了operator->的类的一个对象，则使用point.operator->()的结果来获取mem。根据结果的不同，重复执行上一步或该步。

### 函数调用运算符
还是以例子来说明：
```C++
class PrintString {
public:
    PrintString(ostream &o = cout, char c = ' '):
        os(o), sep(c){}
    void operator()(const string &s) const {os << s << sep;}
private:
    ostream &os;
    char sep;
};

PrintString printer;
printer(s);             //在cout中打印s后面加个空格
PrintString errors(cerr, '\n');
errors(s);              //在cerr中打印s，后面跟一个换行符

//第三个实参是类型PrintString的一个临时对象，调用for_each时会把所有元素依次打印
for_each(v.begin(), v.end(), PrintString(cerr, '\n'));
```
对于函数调用运算符可以有很多不同的版本，相互之间在参数数量或类型上有区别即可。

### 标准库定义的函数对象
标准库定义了一套模板对象，来表示算数运算符、关系运算符和逻辑运算符的类,头文件为functional。
||标准库函数对象||
-|-|-
算术|关系|逻辑
plus\<Type\> | equal_to\<Type\> | logical_and\<Type\>
minus\<Type\> | not_equal_to\<Type\> | logical_or\<Type\>
multiplies\<Type\> | greater\<Type\> | logical_not\<Type\>
divides\<Type\> | greater_equal\<Type\> | 
modulus\<Type\> | less\<Type\>
negate\<Type\> | less_equal\<Type\>

用法举例：
```C++
plus<int> intAdd;
negate<int> intNegate;
int sum = intAdd(10, 20);       //sum = 30
sum = intNegate(intAdd(10,20)); //sum = -30

sort(sevc.begin(), sevc.end(), greater<string>());

//标准库的函数对于指针也可以按照对应的地址大小排序，如
vector<string *> nameTable;
//error! 指针之间无法比较大小
sort(nameTable.begin(), nameTable.end(),
    [](string *a, string *b){return a<b;});
//正确
sort(nameTable.begin(), nameTable.end(), less<string*>());
```
### 可调用对象与function
C++中，函数、函数指针、lambda表达式、bind创建的对象和重载了函数调用运算符的类都是可调用对象。对于所有可调用对象，根据返回类型和传递给调用的实参类型可以决定一个类别。

标准库定义了function类型，可以绑定所有同类别的可调用对象。例子如下：
```C++
int add(int i, int j) {return i + j;}
auto mod = [](int i, int j) {return i % j;}
struct divide {
    int operator()(int i, int j) {
        return i / j;
    }
};

function<int(int, int)> f1 = add;
function<int(int, int)> f2 = divide;
function<int(int, int)> f3 = mod;

f1(4,2);    //6
f2(4,2);    //2
f3(4,2);    //0

map<string, function<int(int, int)>> binops = {
    {"+", add},
    {"-", std::minus<int>()},
    {"/", divide()},
    {"*", [](int i, int j){return i*j;}},
    {"%", mod}
};
//接下来可以用如下操作
binops["+"](10,5);  //调用add(10,5)
```
对于重载的函数，利用函数指针指明是哪个函数再加入到map中，否则编译器无法通过单独的函数名来判断。

### 重载、类型转换与运算符
#### 类型转换运算符
类型转换运算符是类的特殊成员函数，负责将类类型转换成其他类型，形式如`operator type() const`所示。类型转换运算符可以面向除了void外任何类型进行定义。

类型转换运算符没有显式的返回类型，也没有形参，而且必须定义成类的成员函数，一般是const的。举例：
```C++
class smallInt {
public:
    smallInt(int i = 0) val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SamllInt value");
    }
    operator int() const{
        return val;
    }
private:
    std::size_t val;
};

smallInt si;
si = 4;     //将4隐式转化为samllInt然后调用smallInt::operator=
si + 3;     //首先将si隐式转化为int，然后执行整数的加法
```
用户定义的类的类型转换一次只能执行一个，但可以将隐式的用户定义类型转化置于一个内置类型转换之前或之后。

#### 显式的类型转换运算符
为了防止隐式类型转换造成的不必要的困扰，可以用explicit指定显式的转换，如：
```C++
class smallInt(int i = 0) val(i) {
public:
    if (i < 0 || i > 255)
        throw std::out_of_range("Bad SamllInt value");
    }
    explicit operator int() const{
        return val;
    }
private:
    std::size_t val;
};

smallInt si = 3;    //正确，构造函数不是显式的
si + 3;             //错误，类的运算符是显式的
static_cast<int>(si) + 3;   //正确，显式请求类型转换
```
遇到以下情况，则显式的类型转换会被隐式的执行：
+ if、while和do语句的条件部分
+ for语句的条件部分
+ 逻辑非、逻辑或和逻辑与的运算对象
+ 条件运算符的条件表达式

### 避免二义性的类型转换
举个例子：
```C++
struct B;
struct A {
    A() = default;
    A(const &B);        //把一个B转换成A
    //......
};
struct B {
    operator A() const; //把一个B转换成A
    //......
};

A f(const &A);
B b;
A a = f(b); //二义性错误，是f(B::operator A())
            //还是f(A::A(const &B))
A a1 = f(b.operator A());   //正确，显式调用B的类型转换
A a2 = f(A(b));             //正确，显式调用A的构造函数
```
### 函数匹配和重载运算符
例子：
```C++
class smallInt {
    friend
    smmallInt operator+(const smallInt&, const smallInt&);
public:
    smallInt(int i = 0) val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SamllInt value");
    }
    operator int() const{
        return val;
    }
private:
    std::size_t val;
};

smallInt s1, s2;
samllInt s3 = s1 + s2;      //使用重载的operator+
int i = s3 + 0;             //二义性错误，可以把0转换成smallInt也可以把s3转化为int
```
二义性的一些需要注意的点：
+ 一般不要为类定义相同的类型转换，也不要在类内定义两个及以上的转换源或目标是算数类型的转换
+ 使用两个用户定义的类型转换时，如果转换函数之前或者之后存在标准类型转换，则标准类型转换决定哪个是最佳匹配。
+ 调用重载函数的时候，如果需要额外的标准类型转换，则转换的级别只有当所有可行函数都请求同一个用户定义的类型转换时才有用。

## chapter15 面向对象程序设计
示例代码详见chapter15文件夹下的Quote.h和Quote.cc文件。

C++中oop和基类的基本知识:
+ 面向对象程序设计的三个基本概念：数据抽象、继承和动态绑定(核心概念)
    + 数据抽象：将类的接口与实现分离
    + 继承：我们可以定义与其他类相似但完全不相同的新类
    + 动态绑定：在使用这些彼此相似的类时，在一定程度上忽略他们的区别，统一使用它们的对象

+ 类的继承构成一种层次关系，在层次根部的为基类，其他类则直接或者间接的从基类中继承而来，称为派生类。基类负责定义在层次关系中所有类共有的数据成员，而派生类定义各自特有的成员

+ 对于某些函数，基类希望它的派生类各自定义适合其自身的版本，基类会将该函数声明为虚函数！而派生类必须在其内部对所有重新定义的虚函数进行声明，若不加virtual关键字，可以在其后加上override显式声明改写基类的虚函数

+ 动态绑定，函数的运行版本由实参决定也被称为运行时绑定：在使用基类的引用调用一个虚函数时将会发生动态绑定。当我们使用指针或者引用调用虚函数时，将调用动态绑定

+ 基类通常应该定义一个虚析构函数，即使该函数不执行任何操作也是如此！

+ 关键词virtual只能出现在类内的声明函数语句之前，而不能用于类外部的函数定义，在派生类中相应的函数将隐式的是虚函数（不加virtual的情况）

+ 非虚函数，其解析过程将发生在编译时而非运行时

+ protected受保护的成员，基类希望它的派生类有权访问该成员，同时禁止其他用户访问，而private即使是其派生类也不能访问

+ 派生类拥有的成员包括自己定义的成员和继承自基类的相关成员，但是这两部分并不一定是连续存储的

+ 可以把派生类的对象当成基类的对象来使用，也可以将基类的指针或引用绑定到派生类对象中的基类部分上

+ 若基类中定义了静态成员static，则在整个继承体系中只存在该成员的唯一定义，并且只有一份实例，例如：
```C++
class Base {
public:
    static void statmem();
};
class Derived : public Base {
    void f(const Derived&);
};

void Derived::f(const Derived &derived_obj) {
    //以下几种访问方式均正确
    Base::statmem();
    Derived::statmem();
    derived_obj.statmem();
    statmem();  //this访问
}
```
+ 派生类的声明只能包含类名，不能包含它的派生列表：一条声明语句的目的是令程序知晓某个名字的存在以及该名字表示一个怎样的实体，派生列表以及其定义的相关细节必须与类的主体一起出现。例如：
```C++
class Bulk_quote : public Quote;    //error!
class Bulk_quote;                   //正确
```
+ 若要将一个类当作基类来使用，那么这个类就必须是已经定义过的，仅仅声明是不可以的，因为派生类需要知道其基类到底是什么，所以类不能派生其本身，最终的派生类将包含所有间接类的相关成员，例如：
```C++
class Quote;        //声明但未定义
//错误！Quote必须被定义
class Bulk_quote : public Quote {...};
```
+ C++11新标准，防止类被继承可以在其类名后加final，表示其不能作为基类,写法为`class Base final{...};` 或者 `class Derived final : public Base {...};`

+ 表达式的静态类型是在编译时已知的，是变量声明时的类型或者表达式生成的类型，其动态类型是变量或者表达式表示内存的对象的类型，知道运行时才可知，即如item对象，静态类型为Quote&，动态类型则依赖于item所绑定的实参，直到函数运行时才可知

+ 如果表达式既不是指针也不是引用，则其动态类型和静态类型会一直绑定在一起

+ 派生类到基类的类型转换只针对与引用或者指针的类型，其本类型是不支持的，即对象之间不存在类型转换

+ 用一个派生类的对象给一个基类对象初始化或者赋值时，只���其基类的部分被拷贝、移动或者赋值，它的派生类部分将会被忽略掉

### 虚函数
+ 当使用引用或者指针调用一个虚成员函数时才会执行动态绑定，因为在程序运行时才知道到底调用了哪个版本的虚函数，所以所有虚函数都必须有定义。如果不是指针和引用，是不会有动态绑定的，编译期就确定了对应的版本

+ 引用和指针的静态类型与动态类型不同的这一事实是C++语言支持多态性的根本所在(必须是虚函数)

+ 一个派生类的函数成员如果覆盖了基类的继承而来的虚函数，则它的形参类型必须与被它覆盖的基类函数完全一致，返回类型也必须相匹配，但当类的虚函数的返回类型是类本身的指针或者引用时，返回类型可以不同

+ 派生类如果定义了一个与基类虚函数同名函数，但参数列表不相同的话，仍然是合法行为，编译器会认为该函数与基类虚函数是相互独立的，但这往往是把形参列表弄错了的错误，编译器发现不了，所以C++11用关键词override表示其要对基类的函数进行覆盖，若未覆盖，编译器报错。例如：
```C++
struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};
struct D : B {
    void f1(int) const override;    //正确
    void f2(int) override;          //错误，f2没有int
    void f3() override;             //错误，f3不是虚函数
    void f4() override;             //错误，B没有f4的函数
};
```
+ 可以把某个函数指定成final，则该函数不允许任何形式的覆盖,即后序继承该类的派生类不允许覆盖该函数

+ 虚函数可以有默认实参，若函数调用了默认实参，则实参值由静态类型决定，所以基类和派生类中定义的默认实参最好一致

+ 某些情况下，我们不希望进行动态绑定，我们可使用作用域运算符强行指定其执行哪个版本，进行回避虚函数，一般情况下是成员函数中的代码才需要以防止自己调用自身造成无限循环

+ 在一个类的某个虚函数定义后写 =0,则函数成了纯虚函数。有纯虚函数的类是抽象类，不可以定义实体。

+ 派生类调用基类的构造函数，只能调用直接基类的。

### 访问控制和继承
protected成员：
+ protected成员对于类的用户是不可访问的
+ protected成员对于派生类的成员和友元是可访问的
+ 派生类的成员或友元只能通过派生类对象来访问基类的protected成员。派生类对一个基类对象的protected成员没有访问权限。例如：
```C++
class Base {
protected:
    int prot_mem;
};
class Sneaky : public Base {
    friend void clobber(Sneaky&);
    friend void clobber(Base&);
    int j;
};
//正确，clobber可以访问Sneaky对象的private和protcted成员
void clobber(Sneaky &s) {s.j = s.prot_mem = 0;}
//错误，clobber不能访问Base的protected成员。因为这个b的prot_mem并不一定是属于Sneaky类的
void clobber(Base &b) {b.prot_mem = 0;}
```
#### 公有、私有和受保护继承
派生类的访问说明符对派生类的成员和友元无影响。对于基类成员的访问权限只和基类的访问说明符有关系。派生访问说明符是用来控制派生类用户和派生类的派生类对于基类的访问权限的。例如：
```C++
class Base {
public:
    void pub_mem();
protected:
    int prot_mem;
private:
    char priv_mem;
};

struct Pub_Derv: public Base {
    //正确，protected成员可以访问
    int f() {return prot_mem;}
    //错误，private成员不能访问
    char g() {return priv_mem;}
};

struct Priv_Derv : private Base {
    //privvate不影响派生类的访问权限
    int f1() const {return prot_mem;}
};

Pub_Derv d1;
Priv_Derv d2;
d1.pub_mem();       //正确，public继承的
d2.pub_mem();       //错误，private继承的
```
假设D继承自B：
+ 只有D公有继承B，用户代码才能使用派生类向基类的转换，否则不行
+ 无论D以什么形式继承B，D的成员函数和友元都能使用派生类向基类的转化
+ 如果D是公有或受保护继承B，那么D的派生类成员和友元可以使用D向B的转化，否则不行

#### 友元与继承
友元关系不存在继承性。但是友元在访问派生类的基类部分时，对于该部分能否访问是由基类决定的，与派生类无关。

#### 改变个别成员的可访问性
通过在类的内部使用using声明改变派生类继承的某个名字的访问权限，using语句中名字的访问权限由该using出现之前的访问说明符决定。例如：
```C++
class Base {
public:
    std::size_t size() const {return n;}
protected:
    std::size_t n;
};

class Derived : private Base {
public:
    //size变为public的了
    using Base::size;
protected:
    using Base::n;
};
```
对于class，默认的继承是private，对于struct，默认的继承是public

### 继承中的类作用域
即便静态类型和动态类型可能不一样，能使用哪些成员还是由静态类型决定的。例如一个基类的指针指向子类对象，利用该指针无法访问子类对象中独有的public成员，即便确实含有。

函数重载只会重载相同定义域内的重名函数。因此，派生类里如果定义了一个与基类同名的函数，则会隐藏基类的对应成员。例如：
```C++
struct Base {
    int memfcn();
};
struct Derived : Base {
    int memfcn(int);        //隐藏了基类的memfcn
};

Derived d;
Base b;
b.memfcn();
d.memfcn(10);
d.memfin();         //错误
d.Base::memfcn();
```
原则是，先进行静态的名字查找，如果找到，则再看是否为virtual，如果是，那么结果等到运行时确定，如果不是，则常规调用即可。

当基类有多个重载的虚函数时，派生类如果只想覆盖其中的个别，但是需要能访问到所有的函数，那么使用`using Base_class_name::function_name;`即可。

### 虚析构函数
+ 虚析构函数：可以动态分配继承体系中的对象，如果我们需要删除一个指向派生类对象的基类指针，就需要虚析构函数，这样可以确保delete基类指针时将运行正确的虚构函数版本(动态绑定虚析构函数)

+ 基类需要一个虚析构函数产生的影响：一个类定义了析构函数，即使它通过=default的形式生成合成的版本，编译器也不会为这个类合成移动操作

+ 基类的默认构造函数、拷贝构造函数、拷贝赋值运算符或析构函数被删除或者不可见，则派生类相应的成员将是被删除的。

+ 基类有不可访问或删除的析构函数，则派生类中合成的默认和拷贝构造函数将是被删除的，因为编译器无法销毁派生类对象的基类部分。

### 派生类的拷贝控制成员
构造函数和赋值运算符需要为派生类及其基类部分构造和赋值，但析构函数只负责销毁派生类自己分配的资源。

默认情况下，基类默认构造函数初始化派生类对象的基类部分。如果要移动或拷贝基类部分，则必须在派生类的构造函数初始值列表中显式的使用基类的对应函数。

### 继承的构造函数
派生类继承基类的构造函数的方式是利用using声明。例如：
```C++
class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;   //继承构造函数
    //......
};
```
该语句等价于生成`derived(parms) : base(args){}`。当派生类含有自己的数据成员时，这些成员会被默认初始化。

构造函数的using声明不会改变函数的访问级别。无论using声明在哪，基类的私有构造函数在派生类中还是私有构造函数，其余也是这个规则。此外，using声明不能指定explicit或者constexpr，只能默认继承基类的这些属性。

基类的构造函数有默认实参时，实参不会被继承，而是让派生类获取多个继承的构造函数，其中每个构造函数分别省略一个有默认实参的形参。

## chapter16 模板与泛型编程
### 函数模板
函数模板的写法如下：
```C++
template <typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2)
        return -1;
    if (v2 < v2)
        return 1;
    return 0;
}
```
在模板定义中，模板参数列表不能为空。对于该函数，调用的时候编译器会利用函数实参的类型推断出模板实参。

模板类型参数的规范和用法(对于模板参数，class和typename用法等价)：
```C++
//表示返回类型和参数类型相同
template <typename T> T foo(T* p){
    T tem = *p;
    //...
    return tem;
}

//错误：U之前必须有class或者typename
template <typename T, U> T calc(const T&, cosnt U&);
```
#### 非类型模板参数
可以在模板中定义非类型模板参数，表示一个值而非类型。需要用特定的类型名来指定非类型参数。例如：
```C++
template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
}
```
调用`compare("hi", "mom")`实际编译器会实例化`int compare(const char (&p1)[3], const char (&p2)[4])`.

非类型模板参数的模板实参必须是常量表达式。
#### inline和constexpr的函数模板
模板也可以声明为inline和constexpr的，将说明符放在模板参数列表之后，返回类型之前即可。例：
```C++
//正确
template<typename T> inline T min(const T&, const T&);
//错误，inline说明符的位置不正确
inline template <typename T> T min(const T&, const T&);
```
#### 编写类型无关的代码
模板程序应该尽量减少对实参类型的要求，例如之前的compare函数，考虑其类型无关和可移植性，可以改进为以下形式：
```C++
template <typename T> int compare(const T &v1, const T &v2) {
    if (less<T>()(v1, v2)) return -1;
    if (lsee<T>()(v2, v1)) return 1;
    return 0;
}
```
这样解决了原始版本传递两个无关指针会遇到的问题。

#### 模板编译
为了生成模板的实例化版本，编译器需要掌握函数模板或类模板成员函数的定义。因此，模板的的头文件既包括声明又包括定义。

调用template时，编译器会使用实参的类型来确定绑定到模版参数T上的类型，之后编译器利用推断出的模版参数来实例化一个特定版本的函数，这个过程被称之为实例化。

类模版的成员函数实例化：只有在程序使用它时才会被实例化，即使其类模版已经被实例化。

### 类模板
举一个Blob的模板例子，如下：
```C++
template <typename T> class Blob {
public:
    using size_type = std::vector<T>::size_type;
    //构造函数
    Blob();
    Blob(std::initializer_list<T> il);
    //blob中元素数目
    size_type size() const{return data->size();}
    bool empty() const{return data->empty();}
    void push_back(const T& t) {data->push_back(t);}
    void push_back(T&& t){data->push_back(std::move(t));}
    void pop_back();
    //元素访问
    T& back();
    T& operator[](size_type i);
private:
    std::shared_ptr<std::vector<T>> data;
};
```
使用类模板的时候，需要显式地给定模板实参列表，类模板的每个实例都形成一个独立的类。对于模板类中的成员，在模板类外进行定义的写法为：
```C++
template<typename T>
return-type ClassName<T>::member-name(parm-list)
```
默认情况下，对于一个实例化的类模板，类成员只有在使用的时候才会实例化。

在一个类模板的作用域内，可以直接使用模板名而不必指定模板实参，例如：
```C++
template<typename T>
BlobPtr<T> BlobPtr<T>::operator(int) {
    //此处不需要写成BlobPtr<T>，因为已经在类的作用域内了
    BlobPtr ret = *this;
    ++*this;
    return ret;
}
```

#### 类模板和友元
类和友元各自是否是模板相互无关。

#### 一对一的友元关系
```C++
//为了引用模板的特定实例，需要先声明模板自身
template<typename> class BlobPtr;
template<typename> class Blob;
template<typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);

template<typename T> class Blob {
    friend class BlobPtr<T>;
    friend bool operator==<T>
            (const Blob<T>&, const Blob<T>&);
};
```
上例中，友元的声明用Blob的模板形参作为他们自己的模板实参，则友好关系被限定在同类型的Blob和BlobPtr相等运算符之间。

#### 通用和特性的模板友好关系
```C++
//前置声明，将模板的一个特定实例声明为友元时要用
template <typename T> class Pal;

class C {//C是普通的非模板类
    friend class Pal<C>;    //用C实例化的Pal是C的一个友元
    //Pal2的所有实例都是C的友元;该情况不需要前置声明
    template <typename T> friend class Pal2;
};

template <typename T> class C2 {
    friend class Pal<T>;    //C2的每个实例都将相同实例化的Pal声明为友元
    friend class Pal3;      //Pal3是个非模板类
    //Pal2的所有实例都是C2的每个实例的友元，不需要前置声明
    template <typename X> friend class Pal2; 
};
```
#### 模板自己的类型参数成为友元
例如：
```C++
template <typename Type> class Bar {
    friend Bar;
    //...
};
```
此处将实例化Bar的类型声明为了友元。例如`Sales_data`为`Bar<Sales_data>`的友元。

#### 模板类型别名
```C++
template <typename T> using twin = pair<T, T>;
twin<string> authors;   //authors is a pair<string, string>
twin<double> area;      //area is a pair<double, double>

template <typename T> using partNo = pair<T, unsigned>;
partNo<string> books;   //books is a pair<string, unsigned>
partNo<Student> kids;   //kids is a pair<Student, unsigned>
```
#### 类模板的static成员
类模板可以声明static成员，但是每个模板的不同实例都有自己的static成员实例。由于每个实例都有一个独特的static对象，因此static数据成员也需要定义成模板。访问static实例的时候，需要引用一个特定的实例。例如：
```C++
template <typename T> class Foo {
public:
    static std::size_t count() {return ctr;}
private:
    static std::size_t ctr;
};

template <typename T> size_t Foo<T>::ctr = 0;

Foo<int> fi;                    //实例化Foo<int>类和static数据成员
auto ct = Foo<int>::count();    //实例化Foo<int>::count
ct = fi.count();                //使用Foo<int>::count
ct = Foo::count();              //错误！！！不知道使用哪个模板实例的count！！！
```
### 模板参数
#### 模板参数与作用域
模板参数名的可用范围是其声明之后，到模板声明或定义结束之前，其中会隐藏外层作用域声明的相同名字，例如：
```C++
typedef double A;
template <typename A, typename B> void f(A a, B b) {
    A tmp = a;      //tmp是模板参数A的类型
    double B;       //错误！不能重声明B！
}
```
#### 使用类的类型成员
一般作用域运算符(::)可以来访问static成员和类型成员(定义在类内的某种参数类型)。默认情况下，
C++假定通过作用域运算符访问的名字是static成员。如果要访问类型成员，则需要typename关键字。例如：
```C++
template <typename T>
typename T::value_type top(const T& c) {
    if (!c.empty())
        return c.back();
    else 
        return typename T::value_type();
}
```
当通知编译器一个名字表示类型时，关键字必须用typename，不能用class

#### 默认模板实参
用法举例：
```C++
//compare有一个默认模板实参less<T>和一个默认函数实参F()
template <typename T, typename F = less<T>>
int compare(const T &v1, const T &v2, F f = F()) {
    if (f(v1, v2))
        return -1;
    if(f(v2, v1))
        return 1;
    return 0;
}
bool i = compare(0, 42);    //使用less，i为-1
bool j = compare(item1, item2, compareIsbn);    //使用compareIsbn
```
### 成员模板
一个类无论是类模版还是普通类，都可以将其成员函数定义为模版，称之为成员模版，但是成员模版不能是虚函数。
#### 类莫本的成员模板
举例如下：
```C++
template <typename T> class Blob {
    template <typename It> Blob(It b, It e);
    //...
};

template <typename T>
template <typename It> 
Blob::Blob(It b, It e):
    data(std::make_shared<std::vector<T>>(b, e)){};
```
例子中，定义了一个类模板的成员，其有一个模板类型参数，名为T。而成员自身是一个函数模板，有一个名为It的类型参数

### 控制实例化
对于模版使用时才会被实例化，会产生一个问题：相同的实例可能会出现在多个对象文件中，这时候每个文件都会有一份实例化的副本，这无疑造成了很大的额外开销，所以在C++11新标准下，我们可以使用显示实例化以避免这样的开销，所有的模版参数会被替换为模版实参。
例如：
```C++
//in Application.cc
extern template class Blob<string>;
extern template int compare(const int&, const int&);
Blob<string> sa;    //实例化出现在其他位置
//Blob<int>需要在本文件实例化
Blob<int> a1 = {0,1,2,3};
Blob<int> a2(a1);   //拷贝构造函数在本文件实例化
int i = compare(a1[0], a2[0]);  //实例化出现在其他位置
```
假设templateBuild.o中含有Blob<string>和int compare的实例化，那么在编译时，需要将两个.o文件链接到一起。

一个类模版的实例化定义会实例化该模版的所有成员，包括内联函数成员，因为我们也不知道程序会使用那些成员函数，所以我们必须将其全部实例化，这就要求在实例化定义中，所用类型必须能作用于模版的所有成员函数。

模板实例化的总结：
+ 在我们使用类模板时，只有当代码中使用了类模板的一个实例的名字，而且上下文环境要求必须存在类的定义时，这个类模板才被实例化。

+ 声明一个类模板的指针和引用，不会引起类模板的实例化，因为没有必要知道该类的定义。

+ 定义一个类类型的对象时需要该类的定义，因此类模板会被实例化。

+ 在使用sizeof()时，它是计算对象的大小，编译器必须根据类型将其实例化出来，所以类模板被实例化.

+ new表达式要求类模板被实例化。

+ 引用类模板的成员会导致类模板被编译器实例化。

+ 需要注意的是，类模板的成员函数本身也是一个模板。标准C++要求这样的成员函数只有在被调用或者取地址的时候，才被实例化。用来实例化成员函数的类型，就是其成员函数要调用的那个类对象的类型。但是类模板的实例化定义会实例化该模板的所有成员。

#### 类型转换与模板类型参数
类型转化中，能在调用中应用于函数模板的包括：
+ 忽略顶层const

+ const转换，将一个非const对象的引用或指针传递给一个非const对象

+ 数组或者函数指针的转换

此外，算数转换、派生类向基类转换以及用户定义的转换都不能用于函数模板。

### 函数模板显式实参
例如，定义一个以下的模板，编译器无法推断T1的类型，必须显式给定：
```C++
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);
//显式指定T1,T2和T3从类型推断而来，最后类型为long long sum(int, int)
auto val = sum<long long>(1, 10);
```
显示模板实参按照从左到右的顺序与对应的模板实参匹配。只有最尾参数的显式模板实参可以被忽略，忽略的前提是他们可以从函数参数推断出。

### 尾置返回类型与类型转换
挡不指定返回结果的确切类型，但可以从参数列表中的参数中推断出的时候，可以用尾置返回类型。例如：
```C++
template <typename It>
auto &fcn(It beg, It end) -> decltype(*beg){
    //...
    return *beg;
}
```
上述例子中，\*beg解引用返回的是一个左值，因此decltype推断出的类型为\*beg类型的一个引用。当需要返回类型，而非引用时，可以使用类型转换模板，定义在头文件type_traits中。

||标准类型转换模板||
-|-|-
对Mod\<T\>,其中Mod为 | 若T为 | 则Mod\<T\>::type为
remove_reference | X&& or X&&<br>otherwise | X <br> T
add_const | X&、const X or function <br> otherwise | T <br> const T
add_lvalue_reference | X& <br> X&& <br> otherwise | T <br> X& <br> T&
add_rvalue_reference | X& or X&& <br> otherwise | T <br> T&&
remove_pointer | X*<br> otherwise | X <br> T
add_pointer | X& or X&& <br> otherwise | X* <br> T*
make_signed | unsigned X <br> otherwise | X <br> T
make_unsigned | signed type<br>otherwise | unsigned X <br> T
remove_extent | X[n] <br> otherwise | X <br> T
remove_all_extents | X[n1][n2]...<br>otherwise | X <br> T

使用举例：
```C++
//此时的返回类型是*beg的类型而不是*beg类型对象的一个引用
template <typename It>
auto fcn(It beg, It end) ->
    typename remove_reference<decltype(*beg)>::type {
    //...
    return *beg;
}
```
### 函数指针和实参推断
使用举例：
```C++
template <typename T> int compare(const T&, const T&);
//pf指向int compare(const int&, const int&)
int (*pf)(const int&, const int&) = compare;

void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));
func(compare);  //错误！编译器无法得知使用哪个compare实例
func(compare<int>); //正确，显式指出编译器应该传递的compare版本
```
当参数是一个函数模板实例的地址时，程序上下文必须满足：对每个模板参数，能唯一确定其值或类型。

### 模板实参推断和引用
```C++
template <typename T> void f1(T&);          //实参必须是一个左值
//对f1的调用使用实参所引用的类型作为模板参数类型
f1(i);      //i是一个int，模板参数类型T是int
f1(ci);     //ci是一个const int，模板参数类型是const int
f1(5);      //错误，必须传递给f1一个左值

template <typename T> void f2(const T&);    //实参可以接受右值
//f2中的参数是const &,实参中的const是无关的
//下面三种情况，T都是int
f2(i);
f2(ci);
f2(5);      //一个const &参数可以绑定到一个右值

template <typename T> void f3(T&&);
f3(42);     //实参是一个int类型的右值，模板参数T是右值
```
影响右值引用参数推断的两条准则：
+ 当我们将一个左值传递给右值引用时，编译器会推断模版参数类型为实参的左值引用类型，即将T推断为T&，以使用左值引用（一般情况下我们不能定义一个引用的引用，但是通过类型别名或者模版参数类型间接定义是可以的）
+ 只有四个以上的引用符号会转化为X&& &&折叠为X&&，其他都会折叠为普通的左值引用X&

引用折叠只能应用于间接创建的引用的引用，如类型别名或模板参数。根据以上原则，有：
```C++
f3(i);      //T为int&
f3(ci);     //T为const int&
```
但是，右值引用类型有时会造成困扰，如：
```C++
template <typename T> void f3(T&& val) {
    T t = val;      //拷贝还是绑定一个引用？
    t = fcn(t);     //值改变t还是t和val都改变
    if (val == t) {...}
}
```
上述f3中，传入一个右值和传入一个左值得到的结果类型完全不同。比如传入42,那么T为int。传入i，T为int&。为了避免这种困扰，一般定义两个模板：
```C++
template <typename T> void f(T&&);
template <typename T> void f(const T&);
```
### std::move
利用move，可以获得一个绑定到左值上的右值引用。标准库的move定义如下：
```C++
template <typename T>
typename remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```
利用remove_reference去除引用，再在返回类型里面指定是右值。如此一来，无论传递的是左值还是右值引用，最终返回的结果都是右值类型。

### 转发
当使用下面函数的时候，无法保持const属性以及实参的左值/右值属性。
```C++
//接受一个可调用对象和另外两个参数
//flip1会丢失顶层const和引用
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}

void f(int v1, int &v2) {
    cout << v1 << " " << ++v2 << endl;
}

f(42, i);           //f会改变i
flip1(f, j, 42);    //通过flip1调用f不会改变j
```
上面的示例代码中，通过flip1调用f，传入的j和42分别拷贝给了t1和t2,后续函数调用改变t1和t2不会影响j的值。为了能保持左值的信息以及const属性，可以将模板改进为：
```C++
template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2 &&t2) {
    f(t2, t1);
}
```
改成右值模板参数，则如果传递右值，则保持右值的属性。如果传递左值，则会保持引用。即如果一个函数参数是指向模板类型参数的右值引用，则它对应的实参的const属性和左值/右值属性都会得到保持。

但是依旧存在问题，如果调用的函数改为：
```C++
void g(int &&i, int &j) {
    //...
}
```
则给i传递一个左值，是无法用左值来实例化int&&的。即，int&& t2,t2是一个右值引用，但它本身是一个左值，所以不能将t2绑定到i上。为了解决该问题，可以调用标准库utility里中的forward函数，forward\<T\>返回类型为T&&，如下：
```C++
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}
```
### 重载与模板
模板重载的一个例子：
```C++
template <typename T> string debug_rep(const T &t) {
    ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> string debug_rep(T* p) {
    ostringstream ret;
    ret << "pointer: " << p;
    if (p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

string s("hi");
debug_rep(s);
debug_rep(&s);
```
debug_rep(s)中，只能匹配到第一个版本，因为第二个版本需要传递地址，因此匹配到第一个。

debug_rep(&s)中，两个函数都生成可行的实例。第一版本生成debug_rep(const string* &),第二个版本生成debug_rep(string*)。由于第二个版本是精准匹配，选用第二个版本。

在有多个可行模板的时候，选用最特例化的版本。当非模板和模板都产生一样好的匹配时，选用非模板，其更具有特例性。

上述两个debug_rep函数，加上`debug_rep(const string &s)`函数，在使用`debug_rep("hi world!")`时，三个版本都可行：

+ debug_rep(const char[10]&)

+ debug_rep(const char*)

+ debug_rep(const string&),要求const char*到string的类型转化。

由于第一个和第二个都是精准匹配（数组名和指针的转化算精准匹配），第三个需要一次类型转化。第一个和第二个匹配中，T*版本更具有特例化，因此编译器选择该版本。

### 可变参数模板
写法如下：
```C++
//Args是一个模板参数包，rest是一个函数参数包
//Args表示0或多个模板类型参数
//rest表示0或多个函数参数
template <typename T, typename... Args>
void foo(const T&t, const Args&...rest);
```
如果需要知道包中有多少元素，可以使用`sizeof...`运算符，例子如下：
```C++
template<typename... Args> void g(Args...args) {
    cout << sizeof...(Args) << endl;
    cout << sizeof...(args) << endl;
}
```
利用可变参数模板编程的一个例子：
```C++
template<typename T>
ostream &print(ostream &os, const T &t) {
    os << t;    //最后一个元素之后不打分割符
}
//包中除了最后一个元素之外的其他元素都会调用以下版本的print
template<typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&...rest) {
    os << t << ", ";
    return print(os, rest...);
}
```
#### 转发参数包
举个例子，在StrVec类中添加emplace_bback成员，代码如下：
```C++
template<typename... Args>
void StrVec::emplace_back(Args&&... args) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}
```
上述例子中，既扩展了Args也扩展了args。转发的时候为了保证类型的一直，用到了std::forward\<T\>

### 模板特例化
以下两个compare的函数：
```C++
//版本一，可以比较任意两个类型
template <typename T> int compare(const T&, const T&);
//版本二，可以处理字符串字面常量
template<size_t N, size_t M>
int compare(const char(&) [N], const char (&)[M]);
```
如果需要特例化模板，例如处理字符数组的指针，则可以写成：
```C++
template<>
int compare(const char* const &p1, const char* const &p2) {
    //...
}
```
特例化的本质是实例化一个模板，而不是重载它。因此特例化不会影响函数匹配。

## chapter17 标准库特殊设施
本章内容不是很重要，大概有个印象即可，介绍了一些标准库不常用的内容。

1：tuple类型，tuple意为元组，类似于pair，但参数可以有很多个，可以用于函数返回多个值的情况（话说使用结构体也可以），需要tuple头文件

2：bitset类型，bit+set，类似于array，可以存储二进制位，大小不可变

3：正则表达式：描述字符序列的方法，regex

4：C语言中可以使用rand产生随机数，但是C++提供了更多产生随机数的引擎和方法

5：IO库的格式控制、未格式化IO和随机访问

## chapter18 用于大型程序的工具
### 异常处理
异常抛出一个指针，则要求指针所指的对象在任何处理的地方都要存在。抛出一条表达式时，表达式的静态编译时类型决定了异常对象的类型。

catch子句中的异常声明看起来像是函数的形参列表，但是这个类型必须是完全类型，不能是右值引用。若其参数类型是非引用，则会传入一份异常对象的副本，若是引用，则是该对象的别名。

若catch的参数是基类类型，我们可以使用派生类类型的异常声明对其进行初始化，如若不是引用方式，则会将派生类的部分切除。

搜索匹配的catch语句过程中，找到的未必是最佳匹配，是第一个可以匹配的catch语句，所以越是专门、越是特例化的catch语句应该放在前面，因为catch语句是按照其出现顺序逐一匹配的。

catch语句参数类型允许的类型转换：非const到const、派生类到基类、数组元素到指针、函数名到指针这四种类型转换被允许。

当一个单独的catch语句不能完整地处理异常，则当前catch可以重新抛出异常，用`throw;`这样不含表达式的语句即可。该语句只能出现在catch语句或catch语句直接调用的函数内。

catch语句会改变其参数的内容，如果改变参数的内容后catch语句重新抛出异常，则只有是引用类型时，对参数的改变才会保留并继续传播，例如：
```C++
catch(my_error &eObj) {
    eObj.status = errCodes::severeErr;  //修改异常对象
    throw;                              //异常对象的status成员是severeErr
} catch(other_error eObj) {
    eObj.status = errCodes::baderr;     //只修改了异常对象的局部副本
    throw;                              //异常对象的status成员并没有改变
}
```
如果想要代码能够捕获所有的异常，可以用`catch(...)`语句。例如：
```C++
void manip(){
    try {
        //raise an error
    } catch(...) {
        //handle some error
        throw;
    }
}
```
#### 函数try语句块与构造函数
由于构造函数在其进入函数体之前进行初始化（执行初始化列表），所以此时的try语句块还未生效，所以构造函数体内的catch语句无法处理构造函数初始值列表抛出的异常，这是就需要构造函数try语句块的形式，即将初始值列表置于try语句块中。示例如下：
```cpp
template <Typename T>
Blob<T>::Blob(std::initializer_list<T> il) try:
    data(std::make_shared<std::vector<T>>(il)) {

    }catch(const std::bad_alloc &e) { handle_out_of_memory(e); }
```
#### noexcept异常说明
使用noexcept关键字，指定某个函数不会抛出异常，它不属于函数类型的一部分。noexcept的一些注意事项：
+ noexcept需要出现在函数的所有声明和定义语句中，并且在尾置返回类型之前
+ noexcept说明符需要在const和引用限定符号之后，在final、override或者=0之前

编译器不会在编译时检查noexcept说明，如果noexcept后跟了throw，也可以顺利通过，但是不会进行处理，直接调用terminate。因此noexcept也可以用在不知道如何处理异常的情况中。

两条等价的声明（老版本的写法）：
```cpp
void recoup(int) noexcept;
void recoup(int) throw();   //表示recoup不会抛出异常
```
noexcept也可以接受参数，该参数必须能转化为bool类型，如下：
```cpp
void recoup(int) noexcept(true);        //recoup不会抛出异常
void alloc(int) noexcept(false);        //alloc可能抛出异常
```
noexcept还可以作为运算符来使用，当其不跟在函数参数列表之后时，返回值是一个bool的常量表达式，为true时，表明传入参数会抛出异常。

#### 异常说明与指针、虚函数和拷贝控制
函数指针如果做了noexcept声明，则只能指向同样声明了noexcept的函数。反之，如果函数指针没有做此声明，则可以指向任意函数，例如：
```cpp
void (*pf1)(int) noexcept = recoup;
void (*pf2)(int) = recoup;

pf1 = alloc;        //错误，alloc可能抛出异常，但pf1说明它不会抛出异常
pf2 = alloc;        //正确，pf2和alloc都可能抛出异常
```
如果虚函数承诺不会抛出异常，则后续派生的虚函数也必须有一致承诺。反之，如果基类虚函数允许抛出异常，则派生类对应函数可以抛出也可以不抛出异常，例如：
```cpp
class Base {
public:
    virtual double f1(double) noexcept;
    virtual int f2() noexcept(false);
    virtual void f3();
};
class Derived : public Base {
public:
    double f1(double);      //error! Base::f1承诺不会抛出异常
    int f2() noexcept(false);
    void f3() noexcept;
};
```
若对所有成员和基类的操作都是noexcept的，则编译器合成版本的成员也是noexcept的

自己也可以构建异常类，例如：
```cpp
class out_of_stock: public std::runtime_error {
public:
    explicit out_of_stock(const std::string &s):
                            std::runtime_error(s){}
};

class isbn_mismatch: public std::logic_error {
public:
    explicit isbn_mismatch(const std::string &s):
                            std::logic_error(s) {}
    isbn_mismatch(const std::string &s,
        const std::string &lhs, const std::string &rhs):
        std::logic_error(s), left(lhs), right(rhs) {}
    const std::string left, right;
};
```
### 命名空间
namespace后加命名空间的名字，加上一对花括号就是一个完整的命名空间（注意花括号后无需加分号），只要能出现于全局作用域中的声明就能置于命名空间内，主要包括：类、变量（初始化操作）、函数声明和定义、模版、其他命名空间。例如：
```cpp
namespace cplusplus_primer {
    class Sales_data {//...};
    Sales_data operator+(const Sales_data&, const Sales_data&);
    class Query{//...};
    class Query_base{//...};
}//此处无需分号
```
命名空间不能定义在函数和类的内部。命名空间本身是可以不连续的。

命名空间的成员可以定义在命名空间外部，但是这样的定义必须出现在所属命名空间的外层空间中。

命名空间的模板特例化使用举例：
```cpp
namespace std {
    template <> struct hash<Sales_data>;
}

template <> struct std:hash<Sales_data> {
    size_t opeartor()(const Sales_data& s) const {
        return hash<string>()(s.bookNo)^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
};
```
定义在全局作用域中的名字，用`::member_name`来表示。

#### 内联命名空间
C++11有一套新的嵌套命名空间标准，为**内联命名空间**。内联命名空间的名字可以直接被外层命名空间使用，例如：
```cpp
inline namespace FifthEd {
    //表示第五版代码的命名空间
}
namespace FifthEd {     //隐式内联,inline只要第一次的时候有即可，后面可省略
    class Query_base{//...}
    //...
}

namespace FourthEd {
    class Item_base {//...}
    class Query_base {//...}
}

//命名空间cplusplus_primer将同时用到之前使用的两个命名空间
namespace cplusplus_primer {
    #include "FifthEd.h"
    #include "FourthEd.h"
}
```
上例中，如果要访问FifthEd的代码，用`cpluplus_primer::`即可。否则，需要`cplusplus_primer::FourthEd::`这样的形式

#### 未命名的命名空间
namespace之后不加名字，为未命名的命名空间，其中的变量拥有静态的生命周期，程序结束时才被销毁，但是不可以跨文件进行定义，其中的成员可以直接使用。当然，未命名的命名空间也可以嵌套在其他命名空间中，此时可以通过外层的命名空间名加以访问。

根据C++11标准，static定义静态变量的做法已取消，现在是定义一个全局的未命名的名字空间。

### 使用命名空间成员
`namespace_name::member_name`这样使用命名空间成员显得很繁琐，可以有以下几种方式来简化。

#### 命名空间别名
如，`namespace primer = cplusplus_primer`,后面就可以用`primer::`来表示原本`cplusplus_primer::`的空间。

一个命名空间可以有好几个同义词或者别名。

#### using声明
一次只能引入命名空间的一个成员，其有效范围从using声明开始，到using声明所在的作用域结束为止。例如`using namespace_name::member_name`,之后可以直接用`member_name`

#### using指示
using指示：与using声明类似，也可以使用其简写模式，using namespace XX，将XX命名空间的所有成员变成可见，作用域和using声明一致。using指示一般被看作是出现在最近的外层作用域中，若有同名冲突成员，应加限定符予以区分。

### 类、命名空间与作用域
用例子来说明相应的关系：
```cpp
namespace A {
    int i;
    namespace B {
        int i;          //B中隐藏了A::i
        int j;
        int f1() {
            int j;      //j是f1的局部变量，隐藏了A::B::j
            return i;   //return B::i
        }
    }//命名空间B结束，之后B定义的名字不可见
    int f2() {
        return j;       //错误，j未定义
    }
    int j = i;          //用A::i进行初始化
}
```
对于命名空间中的类，常规的查找规则仍然适用：成员函数用某个名字时，先在成员中查找，然后在类中查找，然后在外层作用域中查找，例如：
```cpp
namespace A {
    int i;
    int k;
    class C1 {
    public:
        C1():i(0), j(0){}       //正确，初始化C1::i,C1::j
        int f1() {return k;}    //return A::k
        int f2() {return h;}    //error! h is undefined
        int f3();
    private:
        int i;                  //C1中隐藏了A::i
        int j;
    };
    int h = i;                  //用A::i初始化
}
int A::C1::f3() {return h;}     //正确，返回A::h
```
给函数传递一个类类型的对象时，除了在常规的作用域中查找，还查找实参所属类型的命名空间，这对于传递类的引用和指针同样有效（非常重要）

#### 友元声明和实参相关的查找
类声明友元时，友元声明并没有使得友元本身可见。然而，一个另外的未声明的类或函数如果第一次出现在友元声明中，则认为它是最近的外层命名空间成员。例如：
```cpp
namespace A {
    class C {
        //两个友元，友元声明外无其他声明
        //这些函数隐式地成为命名空间A的成员
        friend void f2();
        friend void f(const C&);   
    }
}

int main() {
    A::C cobj;
    f(cobj);        //会查找cobj所属的命名空间，从而找到A::f
    f2();           //error! f2 is undefined!
}
```
### 重载与命名空间
#### 与实参相关的查找与重载
对于接受类类型实参的函数，其名字查找将在实参类所属命名空间进行，这对我们如何确定候选函数集造成了影响。例如：
```cpp
namespace NS {
    class Quote {//...};
    void display(const Quote&) {//...}
}
//Bulk_item的基类声明在命名空间NS中
class Bulk_item : public NS::Quote {//...};
int main() {
    Bulk_item book;
    display(book);          //为NS::display
    return 0;
}
```
#### 重载与using声明
using声明语句声明的是一个名字，而非一个特定的函数，所以 `using NS::print(int)`将是错误的，需要写成`using NS::print`。该语句会将print函数的所有版本引入到该空间，若本空间已有同名函数，则using声明会引发错误。

#### 重载与using指示
using指示将命名空间的成员提升到外层作用域中，若两空间有同名函数，则会被添加到重载集合中，且引入一个与已有函数形参列表完全相同的函数不会造成错误，只要我们指明使用哪个版本的函数即可。

一个using声明引入的函数将重载该声明语句所属作用域中已有的同名函数，如果using声明出现在局部作用域中，则引入的名字会隐藏外层作用域中的相关声明

例子如下：
```cpp
namespace libs_R_us {
    extern void print(int);
    extern void print(double);
}
//普通声明
void print(const std::string &);
//这个using指示把名字添加到print调用的候选函数集
using namespace libs_R_us;
//print调用的候选函数包括：
//libs_R_us的print(int), print(double)
//显式声明的print(const std::string &)
void fooBar(int ival) {
    print("Value: ");           //全局的print
    print(ival);                //libs_R_us的print(int)
}
```
### 多继承与虚继承
#### 多继承
多继承的写法为`class A: public class B, public  class C {//...};`。每个基类都有一个可选的访问说明符。如果省略，按照class为private继承，struct为public继承。

构造一个派生类的对象将同时构造并初始化其所有基类子对象。基类的构造顺序与其派生列表的出现顺序一致，例如：
```cpp
//显式初始化所有基类
Panda::Panda(std::string name, bool onExhibit)
      :Bear(name, onExhibit, "Panda"),
       Endangered(Endangered::critical) {}
//隐式地使用Bear的默认构造函数初始化Bear子对象
Panda::Panda()
      :Endangered(Endangered::critical) {}
```
C++11新标准，派生类可以从其基类中继承构造函数，但是若从所个基类中继承了相同的构造函数（形参列表完全相同的情况），就会发生错误，此时该派生类应该为它自己定义一个形参列表相同的构造函数。例如：
```cpp
struct Base1 {
    Base1() = default;
    Base1(const std::string&);
    Base1(std::shared_ptr<int>);
};
struct Base2 {
    Base2() = default;
    Base2(const std::string&);
    Base2(int);
};
//错误！D1试图从两个基类中都继承D1::D1(const string&)
struct D1: public Base1, public Base2 {
    using Base1::Base1;     //从Base1继承构造函数
    using Base2::Base2;     //从Base2继承构造函数
};

//正确写法
struct D2: public Base1, public Base2 {
    using Base1::Base1;     //从Base1继承构造函数
    using Base2::Base2;     //从Base2继承构造函数
    //D2必须自定义一个接受string的构造函数
    D2(const string &s): Base1(s), Base2(s) {}
    D2() = default;         //一旦D2定义了自己的构造函数，则必须有默认构造函数
};
```
析构函数执行的顺序与构造函数相反，派生类的析构函数只负责清除派生类本身分配的资源，派生类的成员及基类都是自动销毁的。

若派生类使用合成的拷贝、移动和赋值操作，则会自动的对基类的部分进行这些操作，此时基类会自动调用自己的相应成员。

### 类型转换与多个基类
编译器不会在派生类向基类的转化中进行比较和选择，认为都一样好。因此在转化的时候，如果有多个可以转化的函数，需要指明。

在多继承下，使用一个成员或者函数时，在多个作用域中都发现了相同的成员或者函数，编译器直接报错。此时，需要注明引用的是哪个作用域，或者在类内重定义一个同名的成员或函数。

### 虚继承
派生列表中同一个基类只能出现一次，但派生类可以多次继承同一个类。比如A继承B和C，B和C同时继承了D，则A继承了D两次。默认情况下，如果某个类在派生过程中出现了多次，则派生类中将包含该类的多个子对象。

虚继承的目的是令某个类做出声明，承诺愿意共享它的基类，共享的基类子对象称为及虚基类，在此情况下，无论虚基类在集成体系中出现多少次，派生类中都只包含唯一一个共享的虚基类对象。具体做法是在继承说明中加上virtual，可以与继承说明符互换。例如以下继承体系和代码：
```cpp
            ZooAnimal
    (虚继承) /     \ (虚继承)
           /       \
         Bear  Raccoon  Endangered
           \      |     /
            \     |    /
             \    |   /
                Panda

class Reccoon : public virtual ZooAnimal {//...};
class Bear : virtual public ZooAnimal {//...};
class Panda : public Bear,
              public Raccoon, public Endangered {//...};
```
无论基类是不是虚基类，派生类对象都能被可访问基类的指针或引用操作。

#### 虚基类成员的可见性
假设B定义了x的成员，D1和D2虚继承自B，D继承自D1和D2.当利用D访问x(D中未定义x)的时候，有以下可能：
+ 如果D1和D2都没有x，则x直接解析为B的成员，此时不存在二义性
+ 如果D1和D2有一个类中有x，那么也没二义性，因为派生类的x比共享基类B的x优先级更高。
+ 如果D1和D2都有x的定义，则有二义性

### 构造函数与虚继承
在虚派生中，虚基类由最底层的派生类初始化，否则将会在多条继承路径上被重复初始化

只要能创建虚基类的派生类对象，该派生类的构造函数就必须初始化它的虚基类

首先用最底层派生类的构造函数的初始值初始化该对象的虚基类子部分，虚基类优先构造，析构函数执行顺序与构造函数相反

利用上面的继承结构说明，创建一个Panda对象时，
+ 先用Panda的构造函数初始值列表提供的初始值构造虚基类ZooAnimal部分
+ 构造Bear部分
+ 构造Raccoon部分
+ 构造Endangered部分
+ 最后构造Panda部分

## Chapter19 特殊工具与技术
### 控制内存分配
new和delete运算符的实现细节：
+ new的操作过程：第一步、new表达式调用operator new(或者 operator new[])的标准库函数，该函数分配一块足够大的、原始的、未命名的内存空间以便存储特定类型的对象（或数组）。第二步、编译器运行相应的构造函数以构造这些对象，并为其传入初始值。第三步、对象分配了空间并构造完成，返回一个指向该对象的指针

+ delete的操作过程：第一步：对指针所指对象的数组指针所指数组执行相应的析构函数。第二步：编译器调用operator delete（或者operator delete[]）的标准库函数释放内存空间

C++从C语言中继承了malloc和free函数，头文件为cstdlib，malloc接受一个表示待分配字节数的size_t，返回指向该内存空间的指针或者返回0表示分配失败。free()函数接受一个void *，它是malloc返回指针的副本，free将相关内存返回给系统，free(0)无意义。所以operator new可以用malloc来实现，例如：
```cpp
#include <iostream>  
#include <cstdlib>  
  
void *operator new(std::size_t n){  
    std::cout << "new(size_t)"<<endl;  
    if (void *mem = malloc(n))  
        return mem;  
    else  
        throw std::bad_alloc();  
}  
void operator delete(void *mem) noexcept{  
    std::cout << "delete(void*)<<endl";  
    free(mem);  
}  
```
operator new和operator delete和alloctor类的allocate和deallocate很像，都是负责分配和释放内存的函数，但是对于operator new分配的内存空间我们无法使用construct函数构造对象，我们应该使用new的定位new形式构造对象

当只传入一个指针类型的实参时，定位new表达式构造对象但是不分配内存，这个指针没有要求，甚至可能是一个不是一个指向动态内存的指针

调用析构函数会销毁对象，但是不会释放内存

### 运行时类型识别
运行时类型识别（RTTI），typeid：用于返回表达式的类型，dynamic_cast：用于将基类的指针或引用转换成派生类的指针或引用，当我们将这两个运算符用于某种类型的引用或指针时，并且该类型含有虚函数，运算符将会使用指针或引用所绑定对象的动态类型。

对于`dynamic_cast`运算符，使用形式有以下三种：
+ `dynamic_cast<type*> (e)`，此时e必须是个有效指针，若失败，返回0
+ `dynamic_cast<type&> (e)`，此时e必须是一个左值，若失败，抛出bad_cast异常
+ `dynamic_cast<type&&> (e)`，此时e不能是一个左值

例如：
```cpp
if (Derived *dp = dynamic_cast<Derived*>(bp)) {
    //使用dp指向的Derived对象
} else {
    //使用bp指向的Base对象
}

try {
    const Derived &d = dynamic_cast<const Derived&>(b);
    //使用b引用的Derived对象
} catch(bad_cast) {
    //处理类型转换失败的情况
}
```
typeid(e)，其中e可以是任何类型或表达式的名字，若为表达式，返回的是引用所引对象的类型，若作用域为数组名，返回的是数组类型，若作用于指针，返回的是该指针的静态编译的类型。使用举例：
```cpp
Dervied *dp = new Derived;
Base *bp = dp;                  //两个指针都指向Dervied对象

if (typeid(*bp) == typeid(*dp)) {
    //...
}
if (typeid(*bp) == typeid(Derived)) {
    //...
}

//比较Base*和Derived，由于指针本身不是一个类类型对象，所以永远不会进入if条件
if (typeid(bp) == typeid(Derived)) {
    //never come here!
}
```
当typeid作用于指针时(而非指针所指的对象)，返回的结果是该指针的静态编译时类型。注意typeid只有在所指对象有虚函数的时候，会对表达式求值，否则返回静态类型。如果没有写虚函数，一种策略是把析构函数写成虚函数！！！

一个使用RTTI的例子如下：
```cpp
class Base {
    friend bool operator==(const Base&, const Base&);
public:
    //Base的接口成员
protected:
    virtual bool equal(const Base&) const;
    //Base的数据成员和其他用于实现的成员
};

class Derived: public Base {
public:
    //Derived的其他接口成员
protected:
    bool equal(const Base&) const;
    //Derived的数据成员和其他用于实现的成员
};

bool operator==(const Base &lhs, const Base &rhs) {
    //如果typeid不同，返回false;否则虚调用equal
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

bool Derived::equal(const Base &rhs) const {
    auto r = dynamic_cast<const Derived&>(rhs);
    //执行比较两个Derived对象的操作并返回结果
}

bool Base::equal(const Base &rhs) const {
    //执行比较Base对象的操作
}
```
### 枚举类型
C++的枚举包含限定作用域和不限定作用域的枚举类型。使用举例：
```cpp
enum color {red, yellow, green};       //不限定作用域的枚举类型
//未命名的，不限定作用域的枚举类型
enum {floatPrec = 6, doublePrec = 10, double_doublePrec = 10};
//限定作用域的枚举类型
enum class open_modes {input, output, append};
```
在限定作用域的枚举类型中，遵循常规的作用域准则，在枚举类型作用域外不可访问，不限定作用域的枚举类型，枚举成员的作用域和枚举类型本身的作用域相同（一般来说两个不限定作用域的枚举类型的成员不可以相同，因为其作用域是相同的，会重复定义）。

默认情况下，枚举成员的枚举值从0开始，依次加1，但我们也可以为枚举成员指定初值。

枚举成员是const的，所以赋值时必须使用常量表达式。

使用举例：
```cpp
enum color {red, yellow, green};            //不限定作用域的枚举类型
enum stoplight {red, yellow, green};        //错误：重复定义了枚举成员
enum class peppers {red, yellow. green};    //正确：枚举成员被隐藏了
color eyes = green;                         //正确
peppers p = green;        //错误：peppers的枚举成员不在有效的作用域中
                          //color::green在有效的作用域中，但是类型错误
color hair = color::red;                    //正确：允许显式的访问枚举成员
peppers p2 = peppers::red;                  //正确：使用peppers的red

int i = color::red;     //正确：不限定作用域的枚举类型的枚举成员隐式地转化成int
int j = peppers::red;   //错误：限定作用域的枚举类型不会进行隐式转化
```
要想初始化一个enum对象或者为enum赋值，必须使用该类型的一个枚举成员或者该类型的另一个对象，不限定作用域的枚举类型的对象或其枚举成员会自动转换为整形。

C++11新标准，可以在enum之后加上冒号再加上我们想在enum中使用的类型：`enum：unsigned int{}`，默认情况下为int。

枚举类型可以先声明不定义。其中不限定作用域的enum未指定成员的默认大小，因此每个声明必须指定成员的大小。对于限定作用域的enum来说，可以不指定成员大小，这个值被隐式地定义成int。如：
```cpp
enum intValues : unsigned long long;    //不限定作用域的，必须指定成员类型
enum class open_modes;                  //限定作用域的枚举类型可以使用默认成员类型int
```
### 类成员指针
成员指针是指可以指向类的非静态成员的指针，由于类的静态成员不属于任何对象，所以无需特殊的指向该成员的指针，成员指针的类型需要包括类的类型和成员的类型。

利用Screen类来举例说明：
```cpp
class Screen {
public:
    typedef std::string::size_type pos;
    char get_cursor() const { return contents[cursor]; }
    char get() const;
    char get(pos ht, pos wd);
private:
    std::string contents;
    pos cursor;
    pos height, width;
}

//pdata可以指向一个常量(非常量)Screen对象的string成员
//该初始化过程中，指针并没有指向任何数据。
//成员指针指定了成员而非改成员所属的对象
const std::string Screen::*pdata;
pdata = &Screen::contents;

//使用数据成员指针
Screen myScreen, *pScreen = &myScreen;
auto s = myScreen.*pdata;
s = pScreen->*pdata;

//由于pdata指向的contents是私有的，因此其使用必须位于Screen类成员或友元内部
//此时一般在类内写一个函数返回相应指针，如
class Screen {
public:
    //data是一个静态成员，返回一个成员指针
    static const std::string Screen::* data() {
        return &Screen::contents;
    }
}

//调用data函数的操作
const string Screen::*pdata = Screen::data();
auto s = myScreen.*pdata;

//pmf是一个指针，指向Screen的某个常量成员函数
auto pmf = &Screen::get_cursor;

char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
pmf2 = &Screen::get;
pmf2 = Screen::get;     //错误，成员函数和指针之间不存在自动转换规则

//使用成员函数指针
char c1 = (pScreen->*pmf)();
char c2 = (myScreen.*pmf2)(0,0);
```
### 将成员函数用作可调用对象
因为成员指针不是可调用对象，所以我们不能直接将一个指向成员函数的指针传递给算法。想要通过成员指针调用函数，必须使用->\*或者.\*运算符。

有三种方式为成员函数生成可调用对象：
#### 用function
```cpp
function <bool (const string&)> fcn = &string::empty;//empty()是一个接受string参数并返回bool值的函数
find_if(vec.begin()，vec.end()，fcn);//正确
```
#### 用men_fn
```cpp
find_if(vec.begin()，vec.end()，mem_fn(&string::empty));//mem_fn会生成一个可调用对象
```
#### 用bind
```cpp
find_if(vec.begin()，vec.end()，bind(&string::empty,_1));//bind会生成一个可调用对象,第一个实参既可以是指针也可以是引用
```
其中，使用function的话，传入的参数必须是string的指针，而mem_fn和bind可以传入string的指针或引用。

### 嵌套类
嵌套类是一个独立的类，与外层类没什么关系，并且外层类对象与内层类对象是相互独立的，嵌套类对象中不包含任何外层类的成员。

嵌套类的名字在外层类的作用域中是可见的，两者都没有对对方有特殊的访问权限。

嵌套类在其外层类完成真正的定义之前，它都是一个不完全类型。

### union
union是一种特殊的类，可以包含多个数据成员，但是在任意时刻只能有一个数据成员可以有值，其他成员属于未定义的状态，分配给union的内存只要能存储它的最大数据成员即可

union中不能含有引用类型的成员，由于union不可继承，因此不能含有虚函数。

匿名的union，没有名字，其中的成员可以直接访问，匿名union不能包含受保护成员和私有成员，也不能包含成员函数

通常将含有类类型成员的union内嵌在另一个类之中，将其定义为匿名union，将自身类类型成员的控制权转移给该类