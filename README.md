# Supported Grammar

##### Author: Dexuan Luo

#### expr: <br/>
        term((PLUS|MINUS) term)*

#### term: <br/>
        factor((MUL | DIV)factor)*

#### factor: <br/>
        INT | FLOAT
        LPAREN expr RPAREN
        PLUS|MINUS INT