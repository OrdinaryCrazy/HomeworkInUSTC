                .MODEL  SMALL
;========================================================================================
                .STACK  300H
                .DATA
;数据说明：一个数据，一个对应的类型，以便栈操作处理
;类型说明：
;       1:操作数;(Num)
;       2:加号;(Plus)
;       3:减号;(Minus)
;       4:左括号;(LeftParen)
;       5:右括号;(RightParen)
;       6:终结符;(用来在栈操作时使计算终止)(EndLabel)
Line            dw 2048 dup(0)
Label           db "0123456789+-()$",0  ;最后这个0是哨兵，用来判断非法字符
;假设计算结果在字的表示范围内
;Result          dw 0
;这个想了一下不需要，最后栈底直接是
ProcessingNum   db 0
UnfinishedNum   dw 0
;用于最后打印答案的一些参数
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
;======================================================================================
                ;这一段只是用来提高健壮性的
                lea bx,Label
FindLabel:      
                mov cl,[bx]
                cmp cl,0
                jz  FinalEnd    ;非法字符引起程序终止
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
        ;这里有个关键性的问题：
        ;'+'和'-'是重载的，这对栈操作非常不友好，那么可以做如下转化消除重载：
        ; +5 --> 0+5
        ;而且这种情况当且仅当前面是'('或'$'，避免连续操作
        ;这是一个假设要求
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
                jmp FinalEnd    ;出错直接退出 
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
                ;要求输入串以'$'结尾
KeepRemainLine:
                mov [si],ax
                add si,2
                mov [si],dx
                add si,2
                mov ProcessingNum,0
                mov UnfinishedNum,0
                jmp GetChar
EndOfInput:
;==================================INPUT FINISHED===========================================
;基本策略：
;栈操作计算
;左结合性，从左到右依次入栈，遇到右括号开始计算到第一个左括号，遇到终结符开始计算到栈底终结符
;如果是上面这样想的，会把自己坑死
;最先计算的是最右边的，也是栈顶的，也就是说对应的栈底应该最左端，即应该从左向右压栈
;最左端的终结符是栈底，最右端的劝你停止压栈
;相应的应该从左括号计算到右括号
                ;lea si,Line
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
                jz  SubForLineEnd       ;这个点位栈里面应该是不会有左右括号的
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
                pop bx          ;左括号出栈
                push ax
                push 1
                sub si,4        ;右括号
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