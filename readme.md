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