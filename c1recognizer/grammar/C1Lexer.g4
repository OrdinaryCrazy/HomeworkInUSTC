lexer grammar C1Lexer;

tokens {
    Comma,
    SemiColon,
    Assign,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    
    If,
    Else,
    While,
    Const,
    
    Equal,
    NonEqual,
    Less,
    Greater,
    LessEqual,
    GreaterEqual,
    
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,

    Int,
    Float,
    Void,

    Identifier,
    IntConst,
    FloatConst
}

// rules
/****************************/
Comma:',';
SemiColon:';';
Assign:'=';
LeftBracket:'[';
RightBracket:']';
LeftBrace:'{';
RightBrace:'}';
/****************************/

LeftParen: '(';
RightParen: ')';

/***************************************/
If:'if';
Else:'else';
While:'while';
Const:'const';
Equal:'==';
NonEqual:'!='|'<>';
Less:'<';
Greater:'>';
LessEqual:'<=';
GreaterEqual:'>=';
/***************************************/

Plus: '+' ;
Minus: '-' ;
Multiply: '*' ;
Divide: '/' ;
Modulo: '%' ;

/*******************************************/
Int: 'int' ;
Float: 'float' ;
Void: 'void' ;

Identifier  : ([A-Z]|[a-z]|'_')+([0-9]|[A-Z]|[a-z]|'_')* ;

FloatConst  : ([0-9]+'.')([0-9]*)?(('E'|'e')('+'|'-')?[0-9]+)?
            | ([0-9]+)?('.'[0-9]+)(('E'|'e')('+'|'-')?[0-9]+)?
            | [0-9]+(('E'|'e')('+'|'-')?[0-9]+)
            | ('0x'|'0X')([0-9]|[A-F]|[a-f])+(('P'|'p')('+'|'-')?[0-9]+)
            | ('0x'|'0X')(([0-9]|[A-F]|[a-f])+'.')(([0-9]|[A-F]|[a-f])*)?(('P'|'p')('+'|'-')?[0-9]+)
            | ('0x'|'0X')(([0-9]|[A-F]|[a-f])+)?('.'([0-9]|[A-F]|[a-f])+)(('P'|'p')('+'|'-')?[0-9]+) ;

IntConst: [1-9][0-9]*
        | '0'[0-7]+
        | ('0x'|'0X')([0-9]|[A-F]|[a-f])+ 
        | '0';
/*******************************************/

WhiteSpace: [ \t\r\n]+ -> skip; 
Comment :('//'(Nochangline)*((' \\''\n')Nochangline*)*('\n')?
        | '/*'('*'*OTHERS+'/'*)*'*/' 
        | '/'(Nochangline)*'\\''\n''/'Nochangline*('\n')? ) -> skip;
fragment OTHERS : ~ ('*'|'/') ;
fragment Nochangline : ~ ('\\'|'\n') ;


/*
fragment ID : ([A-Z]|[a-z]|'_')+([0-9]|[A-Z]|[a-z])*;
fragment Integer_suffix : (Unsigned_suffix)(Long_suffix)?
                        | (Unsigned_suffix)(Long_long_suffix)
                        | (Long_suffix)(Unsigned_suffix)?
                        | (Long_long_suffix)(Unsigned_suffix)?
                        ;
fragment Unsigned_suffix: 'u'|'U';
fragment Long_suffix: 'l'|'L' ;
fragment Long_long_suffix: 'll'|'LL' ;
fragment Floating_suffix: 'f'|'F'|'l'|'L' ;
*/