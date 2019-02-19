                .MODEL SMALL 

                .DATA
TABLE           DB  36 DUP(0)
BASE            DB  10
DIMEN           DB  6

                .CODE
                .STARTUP

                LEA BX TABLE
                MOV CX 36
                MOV AL 1

FILL:           MOV [BX],AL
                INC BX
                INC AL
                DEC CX
                JNZ FILL

                LEA BX TABLE
                MOV CH 0        ;set CH as row index
                MOV CL 0        ;set CL as column index

PROCESS_LOOP:   MOV AL,CH
                SUB AL,CL
                JGE PRINT_NUMBER

IF_PRINT_NUM:   MOV AL,CL
                SUB AL,5
                JZ  PRINT_CRLF

LOOP_CHANG:     MOV AL,CL
                MOV AH,0
                INC AL
                DIV DIMEN       ;quotient in AL while remainder in AH
                MOV CL,AH
                ADD CH,AL
                INC BX

                CMP CH,6
                JL PROCESS_LOOP
                .EXIT
                
PRINT_NUMBER:   MOV AL,[BX]
                MOV AH,0
                DIV BASE
                ADD AL,48       ;quotient in AL while remainder in AH
                ADD AH,48
                MOV DX,AX
                MOV AH,2
                INT 21H
                MOV DL,DH
                INT 21H
                MOV DL,32
                INT 21H
                JMP IF_PRINT_NUM

PRINT_CRLF:     MOV AH,2
                MOV DL,13
                INT 21H
                MOV DL,10
                INT 21H
                JMP LOOP_CHANG

                END