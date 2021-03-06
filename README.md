

# GG LANG
_Author: Dexuan Luo_

`gg lang` is a **Turing Complete** scripted language powered by `C++`.

# Supported Grammar 
## Variable Assignment<br/>
        gg >> var a = 10;
        gg >> a
        10
        
## Logical Operator<br/> 
Logical operation return `int` `1` as `true` and `int` `0` as `false`

        gg >> true
        1
        gg >> false
        0
        gg >> var a = true; var b = false;
        
        gg >> a == b;
        0
        
        gg >> a != b + 3;
        1
        
        gg >> a >= b;
        1
        
        gg >> a <= b;
        0
        
        gg >> a > b;
        1
        
        gg >> a < b;
        0
        
        gg >> a and b;
        0
        
        gg >> a or b;
        1
        
## Arithmetic Operation
The Arithmetic behavior is based on `C++`. `INT` in `gg lang` is `long int` in `C++`, `FLOAT` is `double` in `c++`.
#### Addition and Subtraction: <br/>
        gg >> var a = 1; var b = 2
        
        gg >> a + b       // Integer Addition
        3
        
        gg >> a - b       // Integer Subtraction 
        -1
        
        gg >> 1.5 + 4.2   // Floating Point Addition
        5.7
        
        gg >> 1.5 - 4.2   // Floating Point Subtraction
        -2.7
      
#### Multiplication and Division: <br/>
        gg >> 1 * 2       // Integer Multiplication
        2
   
        gg >> 1 / 2       // Integer Division
        0
        
        gg >> 6 * 7.8     // Integer Multiplied by Floating Point
        46.8
        
        gg >> 6 / 7.8     // Integer Divided by Floating Point
        0.769231
        
        gg >> 7 / 0       // Division by 0
        inf
        
        gg >> 7 / 0 * -1  // Negative Infinity
        -inf
        
        gg >> 0 / 0       // 0 divided by 0
        nan
        
#### Power: <br/>
        gg >> 2^0         // Power to Integer
        1
        
        gg >> 2^(-5)      // Power to Negative Integer
        0.03125
        
        gg >> 4^0.5       // Power to Floating Point
        2
        
        gg >> 4^(-0.5)    // Power to Negative Floating Point
        0.5
        
        gg >> 2^(1/0)     // Power to Infinity
        inf
        
        gg >> 2^(-1/0)    // Power to Negative Infinity
        0
        
        gg >> 2^(0/0)     // Power to nan
        nan
        
        
        
## Element Priority From Low to High


#### scope: <br/>
        expr | expr SEMICOL scope*

#### expr: <br/>
        KEYWORD:var IDENTIFIER EQUAL expr    //variable assignment
        comp_expr ((KEYWORD: and|or) expr)*

#### comp_expr: <br/>
        KEYWORD:not|EXCLAMATION  com_expr
        arith_expr ((EE|NE|GE|LE|GREATER|LESS) arith_expr)*
        
#### arith_expr: <br/>
        term((PLUS|MINUS) arith_expr)*
        
#### term: <br/>
        factor((MUL|DIV)factor)*

#### factor: <br/>
        (PLUS|MINUS) power
        power

#### power: <br/>
        atom(POW factor)*
           
#### atom: <br/>
        INT|FLOAT|IDENTIFIER
        LPAREN expr RPAREN
        
