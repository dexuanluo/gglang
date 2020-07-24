
#Supported Grammar

#####Author: Dexuan Luo

####expr: <br/>
        term((PLUS|MINUS) term)*<br/>

####term: <br/>
        factor((MUL | DIV)factor)*<br/>

####factor: <br/>
        INT | FLOAT<br/>
        LPAREN expr RPAREN<br/>
        PLUS|MINUS INT<br/>