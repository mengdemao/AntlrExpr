AntlrExpr笔记
====
[![CMake](https://github.com/mengdemao/AntlrExpr/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/mengdemao/AntlrExpr/actions/workflows/build.yml)

[代码阅读](https://mengdemao.github.io/AntlrExpr/)

> 提交模板
```markdown
<type> (<scope>): <subject>

<body>

<footer>
```

### type

+ feat：新功能（feature）
+ fix：修补bug
+ docs：文档（documentation）
+ style： 格式（不影响代码运行的变动）
+ refactor：重构（即不是新增功能，也不是修改bug的代码变动）
+ test：增加测试
+ chore：构建过程或辅助工具的变动

### scope
> 本次的修改影响的范围

### body
> 详细描述

+ 改动1
  + 详细1
  + 详细2 
+ 改动2
  + 详细1
  + 详细2

### Footer
> 脚注

1. BREAKING CHANGE
2. 关闭 ISSUE
3. REVERT

## g4代码学习
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

## antlr运行时

### 语法分析树分析

#### 监听器(Listener)
为了将遍历树时触发的时间转换为监听器的调用,antlr提供了ParseTree-Walker类,我们可以实现对应处理节点的接口,每条规则都有对应的`enter`和`exit`规则

测试语句

```
./AntlrExpr "1 + ( 2 - 3 ) * 4 / 5"
```

![计算流程](doc/Expr.png) 

| 事件        | 数据 |
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
