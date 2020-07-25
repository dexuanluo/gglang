# Supported Grammar
_Author: Dexuan Luo_

## Arithmetic Operation
The Arithmetic behavior is based on `c++`. `INT` in `gg lang` is `long int` in `c++`, `FLOAT` is `double` in `c++`.
#### Addition and Subtraction: <br/>
        gg >> 1 + 2       // Integer Addition
        3
        
        gg >> 1 - 2       // Integer Subtraction 
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

#### expr: <br/>
        KEYWORD:var IDENTIFIER EQUAL expr
        term((PLUS|MINUS)term)*

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
        
