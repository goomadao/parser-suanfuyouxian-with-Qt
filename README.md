## 功能
***
输入某一特定的文法，求出该文法的firstVT集合和lastVT集合，并且构造出算符优先矩阵，再输入某一串代码，根据求出的算符优先矩阵输出该代码向上规约的过程，并且对过程中可能出现的错误进行捕获和通知。
##说明
***
1.  文法的输入：输入某一段文法，首先检验文法格式的正确性，再根据”|”符号对文法进行划分，去除重复的文法，并且在解析文法的过程中对出现的终结符和非终结符进行存储备用。
2.	构建firstVT集合：首先得出所有非终结符能一步推导出的firstVT，再递归求出其余的需要多步推导得出的firstVT。
    1.  若U::=b…或者U::=Vb…，则b是U的firstVT(一步推导)
    2.  若U::=V…，则V中的所有firstVT也属于U的firstVT(多步推导)
3.	构建lastVT集合：首先得出所有非终结符能一步推导出的lastVT，再递归求出其余的需要多个推导得出的lastVT。
    1.  若U::=…b或者U::=…Vb，则b是U的lastVT(一步推导)
    2.	若U::=…V，则V中的所有lastVT也属于U的lastVT(多步推导)

4.	构造单符号向上规约集合findMap：对每一个形似E->F|i的推导出单个终结符或者非终结符的文法，将(‘F’,set<char&gt;{‘E’})或者(‘i’,<char&gt;{‘E’})加入到findMap中(某个符号的多个直接上层放在同一个set中)，以便在规约某个子串又没有完全匹配的文法可以规约时，可以先将子串的某一个或者多个符号先向上规约，再寻找匹配的规约文法。
5.	构造出算符优先矩阵：对某个产生式P->X1X2...Xn，根据以下规则构造算符优先矩阵 For i=1 to n-1
    1.	Xi、Xi+1都是终结符，优先级Xi = Xi+1
    2.	i≤n-2，Xi、Xi+2都是终结符，Xi+1是非终结符，优先级Xi = Xi+2
    3.	Xi是终结符，Xi+1是非终结符，for firstVT(中的每个a)，优先级Xi<a
    4.	Xi是非终结符，Xi+1是终结符，for lastVT(中的每个a)，优先级a> Xi+1
6.	待规约代码的输入：输入一段代码，首先去除代码中的空白无意义字符(如空格、换行)，再与vt和vn集合进行比对，如果出现了未定义的文法符号，则报错，如果没有出现错误，把代码交给语法分析器进行规约。
7.	根据算符优先矩阵和文法规约代码：对代码进行移进和规约直到规约栈里只有一个非终结符号且没有剩余代码。当栈内离栈顶最近的终结符的优先级小于或者等于代码最前的终结符的优先级时，以进，当大于时，进行规约，当算符优先矩阵中没有这两个终结符之间的关系时，报错。在规约时，首先扫描一遍所有的文法看是否有完全匹配的文法可以规约，如果有，就按照这个文法进行规约；如果没有，说明待规约的字串中的一部分需要多次向上规约，思路为：
    1.	循环每一个右边部分长度与待规约子串相同的文法
    2.	循环每个相应位置上的字符是否相等，如果相等，则继续分析下一个位置，如果不相等，再判断待规约子串中该位置能否在findMap中递归的向上转换成该文法对应位置上的符号，如果可以，继续分析下一个位置，如果不能转换，则结束对该条文法的匹配，尝试匹配另一条文法
    3.	若某条文法匹配成功，则推出规约过程并且返回该条文法的左部符号，如果所有右边部分长度与待规约子串相同的文法都不匹配，则规约失败，并报错。
