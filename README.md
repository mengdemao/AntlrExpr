AntlrExpr笔记
====
[![CMake](https://github.com/mengdemao/AntlrExpr/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/mengdemao/AntlrExpr/actions/workflows/build.yml)
![Travis (.com)](https://img.shields.io/travis/com/mengdemao/AntlrExpr?style=plastic)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/mengdemao/AntlrExpr)
![GitHub all releases](https://img.shields.io/github/downloads/mengdemao/AntlrExpr/total)
![GitHub](https://img.shields.io/github/license/mengdemao/AntlrExpr)
![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/mengdemao/AntlrExpr)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/mengdemao/AntlrExpr)

## 编译原理
> 只涉及到了编译原理前端,可以学习ANTLR的基础知识即可

### 词法分析

#### RE2NFA

#### NFA2DFA

#### mDFA

### 语法分析

#### 自顶向下

#### 自底向上

## 语法文件

### 编译指令

antlr4脚本内容
```shell
# antlr4编译脚本
java org.antlr.v4.Tool %*

# grun运行程序
java org.antlr.v4.gui.TestRig %*

# 编译G4文件
antlr4 Test.g4

# 编译java
javac *.java

# 运行程序
grun Test prog -gui
```
### 语法详解

描述ANTLR语法和/或词法文件名形如`标题.g4`，内容由以下部分组成：

1. 头，形如以下之一：

   - `grammar 标题;`表示这文件同时描述词法和语法
   - `lexer grammar 标题;`表示这文件只描述词法
   - `parser grammar 标题;`表示这文件只描述语法

2. 选项（可选），形如

   ```plaintext
   options { 键1=值1; ... 键N=值N; }
   ```

   ，其中可指定的键有：

   - `superClass`：分词器或解析器的父类
   - `language`：生成用指定语言编写的代码
   - `tokenVocab`：使用指定文件（加后缀`.token`的属性文件）给出的词类代码
   - `TokenLabelType`：表示词类的类型，默认为`Token`
   - `contextSuperClass`：表示语法树的类型（应派生自`RuleContext`），默认为`ParserRuleContext`

3. 导入（可选），形如`import 导入文件的标题,...;`。导入的效果是依次把被导入文件中规则加到最后（从而规则同名时以当前文件中的为准），词类、通道和命名动作分别合并。纯词法只能导入纯词法，纯语法只能导入纯语法，混合语法可以导入纯语法或没有模式的纯词法。导入可以递归。

4. 词类声明（可选），形如`tokens { 词类名, ... }`，列出额外词类（没有词法规则的）以便动作代码使用。

5. 通道（可选，只适用于纯词法），形如`channels {通道名,...}`，列出自定义通道。

6. 命名动作（可选），形如

   ```plaintext
   @动作名 {代码}
   ```

   ，用于把代码注入到解析器中。其中动作名可以是：

   - `header`表示把代码注入到类声明前
   - `members`表示把代码注入到类内作为字段或方法

7. 一条或以上规则，简单的规则形如`规则名 : 分支1 | ... | 分支N ;`，其中词法规则名由大写字母开始而语法规则名由小写字母开始。更复杂的语法规则形如：

```
规则名[参数声明,...] returns [返回值声明,...] locals [局部总量声明,...] : 分支1 | ... | 分支N ;
```

各种名称可以由字母、数字、下划线组成（支持Unicode），但不能是关键词`import`、`fragment`、`lexer`、`parser`、`grammar`、`returns`、`locals`、`throws`、`catch`、`finally`、`mode`、`options`或`tokens`。另外文件中可以使用Java风格的注释`//行末注释`、`/* 注释 */`和`/** Javadocs */`。

#### 词法规则

| 分支             | 匹配                                                         |
| :--------------- | :----------------------------------------------------------- |
| `词类名`         | 词类中的词                                                   |
| `'字符序列'`     | 字面上的字符序列，除了转义序列`\n`（换行）、`\r`（回车）、`\t`（制表符）、`\b`（退格）、`\f`（换页）、`\uXXXX`（Unicode四位十六进制代码点）或`\u{XXXXXX}’`（Unicode十六进制代码点） |
| `[字符集]`       | 字符集中的一个字符，其中字符集由单字符（包括上述转义序列、`\\`、`\]`、`\-`）、形如`单字符-单字符`的字符区间、形如`\p{属性名}`或`\p{枚举属性=值}`的Unicode子集、以及它们形如`\P{属性名}`或`\P{枚举属性=值}`的补集组成 |
| `'字符'..'字符'` | 字符区间中的字符（包括这两个字符）                           |
| `.`              | 任何一个字符                                                 |
| `词法规则`       | 匹配指定词法规则（包括`fragment`规则）的字符串，可以递归但不能左递归（需要手动改成右递归） |
| `{动作代码}`     | 空，用于在读取到这位置时执行指定代码，当代码中花括号不配对时额外的花括号要用`\{`或`\}`转义 |
| `{谓词代码}?`    | 空，布尔表达式的值为假时放弃继续尝试当前规则                 |
| `~子规则`        | 一个不匹配指定子规则的字符                                   |
| `子规则 子规则`  | 由分别匹配子规则的字符串接起来的                             |
| `子规则*`        | 由零个或多个匹配子规则的字符串串接起来，匹配尽可能长         |
| `子规则+`        | 由一个或多个匹配子规则的字符串串接起来，匹配尽可能长         |
| `子规则?`        | 由零个或一个匹配子规则的字符串串接起来，匹配尽可能长         |
| `子规则*?`       | 由零个或多个匹配子规则的字符串串接起来，匹配尽可能短         |
| `子规则+?`       | 由一个或多个匹配子规则的字符串串接起来，匹配尽可能短         |
| `子规则??`       | 由零个或一个匹配子规则的字符串串接起来，匹配尽可能短         |

在动作代码或谓词代码中可以通过`$规则名`引用匹配子规则的词（当有多个同名子规则时可在规则前加上`名称=`来指定别名），进而可通过`.`引用其字段或方法，例如以下只读属性：

| 属性      | 方法                    | 类型     | 值                                                           |
| :-------- | :---------------------- | :------- | :----------------------------------------------------------- |
| `text`    | `getText`               | `String` | 匹配的文本                                                   |
| `type`    | `getType`               | `int`    | 词类代号                                                     |
| `line`    | `getLine`               | `int`    | 词开始的行号（从1开始）                                      |
| `pos`     | `getCharPositionInLine` | `int`    | 词在行的偏移（从0开始）                                      |
| `index`   | `getTokenIndex`         | `int`    | 当前词的序号（从0开始                                        |
| `channel` | `getChannel`            | `int`    | 通道代码，默认为0 (`Token.DEFAULT_CHANNEL`)，隐藏通道为`Token.HIDDEN_CHANNEL` |
| `int`     |                         | `int`    | 匹配文本表示的整数                                           |

在一个分支的最后可以加上`->命令,...`，其中可用的命令有：

- `skip`用于放弃当前词
- `mode(模式)`修改栈顶模式（栈可用于实现仅用正则表达式无法描述的模式，如某些语言容许的嵌套注释）
- `pushMode(模式)`推入栈顶模式
- `popMode`弹出栈顶模式
- `more`要求继续匹配以延长当前词
- `type(词类)`用于修改当前词所属的词类
- `channel(通道)`用于把当前词送到指定通道

如果一条词法规则纯粹为了共用代码或提高可读性，而不是要实际生成词，可在规则前加上`fragment `。

#### 语法规则

语法分支可以由以下元素组成：

| 构造                  | 描述                                                         |
| :-------------------- | :----------------------------------------------------------- |
| `词类名`              | 匹配词类中的词，特殊词`EOF`用于标记输入结束                  |
| `'字符串`’            | 匹配恰由指定字符串组成的词                                   |
| `语法规则`            | 匹配指定规则的一列词                                         |
| `语法规则 [参数,...]` | 匹配指定规则的一列词，参数的值将传递给该规则                 |
| `{动作代码}`          | 马上执行指定代码，其中可以通过`$x`或`$x.y`引用属性，并可通过`$x::y`引用非局部属性（动态作用域） |
| `{谓词代码}?`         | 若代码的值为`false`则放弃尝试当前分支                        |
| `.`                   | 匹配任何词（除了`EOF`）                                      |
| `(分支|...)`          | 匹配匹配其中一个子分支的词列                                 |
| `元素?`               | 匹配匹配零个或一个元素的词列，匹配尽可能长                   |
| `元素*`               | 匹配匹配零个或以上元素的词列，匹配尽可能长                   |
| `元素+`               | 匹配匹配一个或以上元素的词列，匹配尽可能长                   |
| `元素??`              | 匹配匹配零个或一个元素的词列，匹配尽可能短                   |
| `元素*?`              | 匹配匹配零个或以上元素的词列，匹配尽可能短                   |
| `元素+?`              | 匹配匹配一个或以上元素的词列，匹配尽可能短                   |

在动作代码或谓词代码中可以通过`$规则名`引用匹配子规则的文本（当有多个同名子规则时可在规则前加上`名称=`来指定别名），进而可通过`.`引用其字段或方法，例如以下只读属性：

| 属性    | 类型                | 值                                                           |
| :------ | :------------------ | :----------------------------------------------------------- |
| `text`  | `String`            | 已匹配的文本（包括隐藏通道中的）                             |
| `start` | `Token`             | 主通道中首个匹配的词                                         |
| `stop`  | `Token`             | 主通道中最后一个匹配的词（只适用于末尾的动作和`finally`动作） |
| `ctx`   | `ParserRuleContext` | 上下文对象                                                   |

如果希望通过侦听器监视什么时候开始和结束结束尝试分支，可以在分支后加上`#名称`（一个规则要么所有分支都有名称，要么都没有），多个分支可以有相同名称。

## 文件生成规则

```markdown
grammar Expr;

prog : stat+;

stat: expr NEWLINE          # printExpr
	| ID '=' expr NEWLINE   # assign
	| NEWLINE               # blank
	;

expr: expr op=('*'|'/') expr        # MulDiv
	| expr op=('+'|'-') expr        # AddSub
	| INT                           # int
	| ID                            # id
	| '('expr')'                  # parens
	;

MUL     : '*' ; // assigns token name to '*' used above in grammar
DIV     : '/' ;
ADD     : '+' ;
SUB     : '-' ;
ID      : [a-zA-Z]+ ;
INT     : [0-9]+ ;
NEWLINE :'\r'? '\n' ;
WS      : [ \t]+ -> skip;
```
生成如下的的文件

| 源文件                                | 头文件                            |
| ------------------------------------- | :-------------------------------- |
| ExprListener.cpp/ExprBaseListener.cpp | ExprListener.h/ExprBaseListener.h |
| ExprVisitor.cpp/ExprBaseVisitor.cpp   | ExprVisitor.h/ExprBaseVisitor.h   |
| ExprLexer.cpp                         | ExprLexer.h                       |
| ExprParser.cpp                        | ExprParser.h                      |

同时初步生成的中间文件`interp/tokens`作为临时文件

生成的符号文件

```
T__0=1
T__1=2
T__2=3
MUL=4
DIV=5
ADD=6
SUB=7
ID=8
INT=9
NEWLINE=10
WS=11
'='=1
'('=2
')'=3
'*'=4
'/'=5
'+'=6
'-'=7
```

重点分析`Lexer/Parser`，

首先需要明白Antlr4的ATN是什么?

`AugmentedTransitionNetworks`(增强过渡网络)这是什么意思?[ATN论文](doc/LL-star-PLDI11.pdf)

## antlr运行时

### 生成法分析树
> 写法相对固定,携程如下的固定即可

```c
// 输入字符串
ANTLRInputStream input(InputString);

// 词法解析
ExprLexer lexer(&input);

// 分割单词
CommonTokenStream tokens(&lexer);

// 解析语法单元
ExprParser parser(&tokens);

// 生成语法树
ParseTree *tree = parser.prog();
```

### 分析语法分析树

#### 监听器(Listener)

为了将遍历树时触发的时间转换为监听器的调用,antlr提供了ParseTree-Walker类,我们可以实现对应处理节点的接口,每条规则都有对应的`enter`和`exit`规则

测试语句

```
./AntlrExpr "1 + ( 2 - 3 ) * 4 / 5"
```

![计算流程](doc/Expr.png)

| 事件         | 数据  |
| ----------- | ---- |
| enterAddSub | +    |
| enterInt    | 1    |
| exitInt     | 1    |
| enterMulDiv | /    |
| enterMulDiv | *    |
| enterAddSub | -    |
| enterInt    | 2    |
| exitInt     | 2    |
| enterInt    | 3    |
| exitInt     | 3    |
| exitAddSub  | -    |
| enterInt    | 4    |
| exitInt     | 4    |
| exitMulDiv  | *    |
| enterInt    | 5    |
| exitInt     | 5    |
| exitMulDiv  | /    |
| exitAddSub  | +    |

#### 访问器(Visitor)

| 事件         | 数据  |
| ----------- | ---- |
| visitAddSub |	+    |
| visitInt    |	1    |
| visitMulDiv |	/    |
| visitMulDiv |	*    |
| visitAddSub |	-    |
| visitInt	  | 2    |
| visitInt	  | 3    |
| visitInt	  | 4    |
| visitInt	  | 5    |
