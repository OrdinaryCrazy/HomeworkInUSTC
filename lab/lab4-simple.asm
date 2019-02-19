                .MODEL  SMALL
;========================================================================================
                .STACK  300H
                .DATA
Line            dw 2048 dup(0)
Label           db "0123456789+-()$",0
ProcessingNum   db 0
UnfinishedNum   dw 0
TEN             dw 10
HUNDRED         dw 100
THUSAND         dw 1000
TENTHUSAND      dw 10000
HEADZERO        db 0
;========================================================================================
                .CODE
                .STARTUP
                lea si,Line
                mov [si],6
                add si,2
                mov [si],'$'
                add si,2
GetChar:
                mov ah,1
                int 21H
                lea bx,Label
FindLabel:      
                mov cl,[bx]
                cmp cl,0
                jz  FinalEnd
                cmp al,cl
                jz  GetLabel
                inc bx
                jmp FindLabel
;=====================================================================================
GetLabel:
                cmp al,48
                js  OpeLabel
NumLabel:
                sub al,48
                mov ProcessingNum,1
                mov cl,al
                mov ch,0
                mov ax,10
                mul UnfinishedNum
                add ax,cx
                mov UnfinishedNum,ax
                jmp GetChar
OpeLabel:
                mov bl,ProcessingNum
                cmp bl,0
                jz  NotAsNumEnd
                mov bx,UnfinishedNum
                mov [si],1
                add si,2
                mov [si],bx
                add si,2
                jmp NotNeedToChange
NotAsNumEnd:
                cmp al,'+'
                jz  NeedToChange
                cmp al,'-'
                jz  NeedToChange
                jmp NotNeedToChange
NeedToChange:
                mov ah,[si-4]
                cmp ah,4
                jz  Change
                cmp ah,6
                jz  Change
                cmp ah,5
                jz  NotNeedToChange
                jmp FinalEnd  
Change:
                mov [si],1
                add si,2
                mov [si],0
                add si,2
NotNeedToChange:
                mov ah,0
                mov dx,ax

                cmp al,'+'
                jz Plus
                cmp al,'-'
                jz Minus
                cmp al,'('
                jz LeftParen
                cmp al,')'
                jz RightParen
                cmp al,'$'
                jz LineEnd
Plus:
                mov al,2
                jmp KeepRemainLine
Minus:
                mov al,3
                jmp KeepRemainLine
LeftParen:
                mov al,4
                jmp KeepRemainLine
RightParen:
                mov al,5
                jmp KeepRemainLine
LineEnd:
                mov al,6
                mov [si],ax
                add si,2
                mov [si],dx
                jmp EndOfInput
                
KeepRemainLine:
                mov [si],ax
                add si,2
                mov [si],dx
                add si,2
                mov ProcessingNum,0
                mov UnfinishedNum,0
                jmp GetChar
EndOfInput:
                push [si]
                sub si,2
                push [si]
                sub si,2
PushLineIntoStack:
                mov ax,[si-2]
                cmp ax,6
                jz LineEndCompute
                cmp ax,4
                jz LeftParenCompute

                push [si]
                sub si,2
                push [si]
                sub si,2
                jmp PushLineIntoStack
LineEndCompute:
                pop ax
                pop ax
                pop bx
                cmp bx,2
                jz  AddForLineEnd
                cmp bx,3
                jz  SubForLineEnd 
                jmp PrintResult
AddForLineEnd:
                pop bx
                pop bx
                pop bx
                add ax,bx
                push ax
                push 1
                jmp LineEndCompute
SubForLineEnd:
                pop bx
                pop bx
                pop bx
                sub ax,bx
                push ax
                push 1
                jmp LineEndCompute
;======================================================================================
LeftParenCompute:
                pop ax
                pop ax
                pop bx
                cmp bx,2
                jz AddForLeftParen
                cmp bx,3
                jz SubForLeftParen
                jmp RightParenForLeftParen
AddForLeftParen:
                pop bx
                pop bx
                pop bx
                add ax,bx
                push ax
                push 1
                jmp LeftParenCompute
SubForLeftParen:
                pop bx
                pop bx
                pop bx
                sub ax,bx
                push ax
                push 1
                jmp LeftParenCompute
RightParenForLeftParen:
                pop bx   
                push ax
                push 1
                sub si,4
                jmp PushLineIntoStack
;===================================COMPUTE FINISHED==========================================
PrintResult:
                push ax
                mov ah,2
                mov dl,13
                int 21H
                mov dl,10
                int 21H
                pop ax
                cmp ax,0
                jge NoSignOut
                push ax
                mov ah,2
                mov dl,2DH
                int 21H
                pop ax
                not ax
                inc ax
NoSignOut:
                mov dx,0
                div TENTHUSAND
                push dx
                mov dl,HEADZERO
                cmp dl,0
                jnz TenThousandOut
                cmp al,0
                jz  PrintThousand
TenThousandOut:
                mov ah,2
                mov dl,al
                add dl,48
                int 21H
                mov HEADZERO,1
PrintThousand:
                pop ax
                mov dx,0
                div THUSAND
                push dx
                mov dl,HEADZERO
                cmp dl,0
                jnz ThousandOut
                cmp al,0
                jz  PrintHundred
ThousandOut:
                mov ah,2
                mov dl,al
                add dl,48
                int 21H
                mov HEADZERO,1
PrintHundred:
                pop ax
                mov dx,0
                div HUNDRED
                push dx
                mov dl,HEADZERO
                cmp dl,0
                jnz HundredOut
                cmp al,0
                jz  PrintTen
HundredOut:
                mov ah,2
                mov dl,al
                add dl,48
                int 21H
                mov HEADZERO,1
PrintTen:
                pop ax
                mov dx,0
                div TEN
                push dx
                mov dl,HEADZERO
                cmp dl,0
                jnz TenOut
                cmp al,0
                jz  PrintOne
TenOut:
                mov ah,2
                mov dl,al
                add dl,48
                int 21H
                mov HEADZERO,1
PrintOne:
                pop dx
                mov ah,2
                add dl,48
                int 21H

                mov dl,13
                int 21H
                mov dl,10
                int 21H
FinalEnd:
        .EXIT
        end