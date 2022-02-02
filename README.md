**AntlrExpr笔记**
====
![Github Action](https://github.com/mengdemao/AntlrExpr/actions/workflows/build.yml/badge.svg?branch=master)
![Travis](https://img.shields.io/travis/com/mengdemao/AntlrExpr?style=plastic)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/mengdemao/AntlrExpr)
![GitHub all releases](https://img.shields.io/github/downloads/mengdemao/AntlrExpr/total)
![GitHub](https://img.shields.io/github/license/mengdemao/AntlrExpr)
![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/mengdemao/AntlrExpr)
![GitHub commit activity](https://img.shields.io/github/commit-activity/y/mengdemao/AntlrExpr)

![说明文件](doc/AntlrExpr.png "AntlrExpr Logo")

## 程序结构
```shell
.
├── bin	
├── build.sh
├── CMakeLists.txt
├── doc
├── Doxyfile.in
├── Expr.g4
├── grammar
├── inc
├── LICENSE
├── main.cc
├── README.md
├── runtime
├── src
└── tool
```

### 编译指令

### 设置antlr编译器
1. 设置java运行环境 
2. 下载antlr执行文件
3. 设置环境变量

```shell
export CLASSPATH=".:${pwd}/bin/antlr-complete.jar:$CLASSPATH"
alias antlr4='java -jar ${pwd}/bin/antlr-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'
```

4. 测试G4文件

```shell

# 编译G4文件
antlr4 Expr.g4

# 编译java
javac *.java

# 运行程序
grun Expr prog -gui

```

测试语句`"1 + ( 2 - 3 ) * 4 / 5"`,按`Ctrl+Z`执行

生成结果如下
![表达式自动生成](doc/Expr.png)

## antlr运行时

### 生成法分析树
> 写法相对固定,写成如下的固定即可

```c
// 输入字符串
ANTLRInputStream input(InputString);

// 词法解析
ExprLexer lexer(&input);

// 分割单词
CommonTokenStream tokens(&lexer);

// 解析语法单元
ExprParser parser(&tokens);

// 生成语法分析树
ParseTree *tree = parser.prog();
```

### 分析语法分析树

测试语句

```sh
./AntlrExpr "1 + ( 2 - 3 ) * 4 / 5"
```

#### 监听器(Listener)

为了将遍历树时触发的时间转换为监听器的调用,antlr提供了ParseTree-Walker类,我们可以实现对应处理节点的接口,每条规则都有对应的`enter`和`exit`规则,na

#### 访问器(Visitor)

### 总体框架

监听器生成抽象语法树并且运算结果,
访问器校验抽象语法树使用LLVM校验结果
