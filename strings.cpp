#include <stdio.h>
#include <iostream.h>

using namespace std;

int strlen(const char* str)
{
    assert(str != NULL);
    int len = 0;
    while((*str++) != '/0')
    {
        len++;
    }        
    return len;
}

int strlen(const char* str)
{
    assert(str != NULL);
    return (*str) == '/0' ? 0 : 1 + strlen(++str);
}

int strcmp(const char* str1, const char* str2)
{
    assert(str1 != NULL && str2 != NULL);
    int ret = 0;
    while(!(ret = *(unsigned char *)str1 - *(unsigned char *)str2) && *str1)
    {
        str1++;
        str2++;
    }
    if(ret < 0) ret = -1;
    else if(ret > 0) ret = 1;
    return ret;
}

char *strcat(char *strDest, char *strSrc)
{
    char *address = strDest;
    assert((strDest != NULL) && (strSrc != NULL));
    while(*strDest)
    {
        strDest++;
    }
    while(*strDest++ == *strSrc);
    return address;
}

char *strcpy(char *strDestination, const char *strSource)
{
    assert(strDestination != NULL && strSource != NULL);
    char *strD = strDestination;
    while((*strDestination++ = *strSource) != '\0');
    return strD;  
}


void *memcpy(void *dest, const void *src, size_t n);
// memcpy vs strcpy
// 1. 都是标准的库函数
// 2. 复制的内容不同， strcpy只能复制字符串，并且不止复制字符串，还会复制字符串后面的
//    结束符， memcpy可以复制任何内容， 例如字符数组，整形， 结构体， 类等
// 3. 复制的方法不同，strcpy不需要指定长度， 在被复制的字符串遇到\0时结束， 所以容易
//    溢出
// 4. 用途不同，通常在复制字符串的时候用strcpy， 复制其他类型时一般使用memcpy

void *memset(void *s, int ch, size_t n);
// 功能： 将s中的前n个字节用ch替换并返回，作用是在一段内存块中填充某个值， 它是对较大的
//       结构体或者数组进行清零的最快的一种方法

/**********************************************************
 * 实际应用
 * 1.字符串包含问题
 *      1.1 串的模式匹配算法 : 给出串A，找出串B的位置
 *      1.2 字符串移位包含问题 s2能否被s1做循环移位得到的字符串包含
 * 2. 字符串转换成数字  
 *      2.1 Str to int
 *      2.2 s2中的字母是否s1中都有
 * 3. 字符串的逆转
 * 
 * 
 * 
 * 
 */

// 1,1 BF算法 复杂度O(m-n+1)*n
char *strFind(const char *string, const char *substring)
{
    assert(string != NULL && subString != NULL);
    int m = strlen(string);
    int n = strlen(substring);
    if(m < n) return NULL;
    for(int i = 0; i < m-n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(string[i+j] != substring[j])
            {
                break;
            }
        }
        if(j == n) return string + i;
    }
    return NULL;
}

// 1.1 KMP算法 复杂度O(m+n)


// 1.2 判断s2能否被s1循环移位包含， 相当于判断s2是否存在于s1s1中

// 2.1
enum{kValid = 0, kInvalid};
int g_nStatus = kValid;
int StrToInt(const char *str)
{
    g_nStatus = kInvalid;
    long long num = 0;
    if(str != NULL)
    {
        const char *digit = str;
        bool minus = False;
        if(*digit == '-')
        {
            digit++;
            minus = True;
        }else if(*digit == '+')
        {
            digit++;
            minus = False;
        }
        while(*digit != '\0')
        {
            if(*digit >= '0' && *digit <='9')
            {
                num = num * 10 + (*digit - '0');
                if(num > std::numeric_limits<int>::max())
                {
                    num = 0;
                    break;
                }
                digit ++;
            }
            else
            {
                num = 0;
                break;
            }
        }

        if(*digit == '\0')
        {
            g_nStatus = kValid;
            if(minus)
            {
                num = 0 - num;
            }
        }
        return num;
    }
}

// 2.2 1. 对两个字符串进行排序 排序O(mlogm) + O(nlogn) + 线性扫描O(m+n)
//     2. hashtable O(m+n)
//     3. 为每一个字母分配一个素数。 s1所有素数相乘， 除以s2所有素数相乘（考虑大数乘法）

void multiply(const char *a, const char *b)
{
    assert(a != NULL && b != NULL);
    int i, j, ca, cb, *s;
    ca = strlen(a);
    cb = strlen(b);
    s = (int *)malloc(sizeof(int) * (ca + cb));
    for(i = 0; i < ca + cb; i++)
    {
        s[i] = 0;
    }
    for(i = 0; i < ca; i++)
    {
        for (j = 0; j < cb; j++)
        {
            s[i+j+1] += (a[i] - '0') * (b[j] - '0'); 
        }
    }
    for(i = ca + cb -1; i >=0; i--)
    {
        if(s[i] > 10)
        {
            s[i-1] += s[i]/10;
            s[i] %= 10;
        }
    }
    char *c = (char *) malloc (sizeof(char) * ca + cb);
    i = 0;
    while(s[i] == 0) i++;
    for(j = 0; i < ca + cb; i++, j++)
    {
        c[j] = s[i] + '0';
    }
    c[j] = '\0';
    for(i = 0; i > ca + cb; i++)
    {
        cout << c[i];
    }
    cout << endl;
    free(s);
    free(c);
}

// 3.1
void Reverse(char *pb, char *pe)
{
    if(pb == NULL || pe == NULL) return;
    while(pb < pe)
    {
        char tmp = *pb;
        *pb = *pe;
        *pe = tmp;
        pb++;
        pe--;
    }
}

char* ReverseSentence(char *pData)
{
    if(pData == NULL) return NULL;
    char *pBegin = pData;
    char *pEnd = pData;
    while(*pEnd != '\0')
    {
        pEnd++;
    }
    pEnd--;
    Reverse(pBegin, pEnd);
    pBegin = pEnd = pData;
    while(*pBegin != '\0')
    {
        if(*pBegin == ' ')
        {
            pBegin ++;
            pEnd ++;
            continue;
        }
        else
        {
            if(*pEnd == ' ' || *pEnd == '\0')
            {
                Reverse(pBegin, --pEnd);
                pBegin = ++pEnd;
            }else{
                pEnd++;
            }
        }
    }
    return pData;
}

// 删除模式串中出现的元素
// 最优解：为每一个元素配上素数， 求素数的乘机整除
void fun(char *s)
{
    assert(s  != NULL);
    int i = 0, j = 0;
    while(s[j] != '\0')
    {
        while(s[j] == 'a' || s[j] == 'b' || s[j] == 'c' || s[j] == 'd')
        {
            j++;
        }
        s[i++] = s[j++];
    }
    s[i] = '\0';
}

// 删除字符串中的空格
void fun(char* s)
{
    int i = 0, j =0;
    while(s[j] == ' ')
    {
        j++;
    }
    int len = strlen(s) - 1;
    while(s[len] == ' ') len--;
    s[len+1] = '\0';

    while(s[j] != '\0')
    {
        while(s[j] == ' ') j++;
        if(s[j-1] == ' ' && s[j-2] == ' ' && i != 0)
        {
            s[i++] = ' ';
        }
        s[i++] = s[j++];
    }
    s[i] = '\0';
}

// 第一个出现的字符
void fun(const char * str)
{
    assert(str != NULL);
    const int size = 256;
    unsigned int hashTable[size];
    for(unsigned int i = 0; i < size; i++)
    {
        hashTable[i] = 0;
    }
    const char *hashkey = str;
    while(*(hashkey) != '\0')
    {
        hashtable[*(hashkey++)] ++;
    }
    hashkey = str;
    while(*hashkey != '\0')
    {
        if(hashtable[*hashkey] == 1)
        {
            cout << *hashkey;
            return;
        }
        hashkey++;
    }
}

// 所有字符是否都不相同
bool char_set[256];
int isunique(const char* str)
{
    assert(str != NULL);
    int len = strlen(str);
    for(unsigned int i = 0; i < len; ++i)
    {
        int val = str[i];
        if(char_set[val]) return 0;
        char_set[val]  = true;
    }
    return 1;
}