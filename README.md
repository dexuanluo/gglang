# Supported Grammar

##### Author: Dexuan Luo

#### expr: <br/>
        term((PLUS|MINUS) term)*

#### term: <br/>
        factor((MUL | DIV)factor)*

#### factor: <br/>
        (PLUS|MINUS) power
        power
        
#### atom: <br/>
        INT | FLOAT
        LPAREN expr RPAREN
        
#### power: <br/>
        atom (POW factor)*