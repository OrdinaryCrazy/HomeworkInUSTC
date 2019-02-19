        .MODEL  SMALL
        .DATA
NUMBER  db 20 dup(0)
TEN     db 10
LENGTH  dw 20
N       db 0
FLAG    db 0
        .CODE
        .STARTUP
        mov dl,0
GetN:
        mov ah,1
        int 21h
        sub al,48
        js  NGet
        mov bx,ax
        mov al,10
        mul dl
        mov dl,al
        mov ax,bx
        add dl,al
        jmp GetN
NGet:
        mov N,dl
        mov ah,2
        mov dl,13
        int 21h
        mov dl,10
        int 21h
;===============================================================================
        mov NUMBER[0],1
        mov cx,2
        mov bx,0
MultiOne:
        mov al,NUMBER[bx]
        mul cl
        mov NUMBER[bx],al
        add bx,1
        cmp bx,LENGTH
        jnz MultiOne
;======================================
        push cx
        mov cx,LENGTH
        lea bx,NUMBER
Adjust:
        mov al,[bx]
        mov ah,0
        div TEN
        mov [bx],ah
        mov ah,[bx + 1]
        add ah,al
        mov [bx + 1],ah
        inc bx
        dec cx
        jnz Adjust
;========================================
EndAdjust:
        pop cx
;========================================
Iteration:
        mov bx,0
        inc cx
        mov al,N
        inc al
        cmp cl,al
        js MultiOne
;===============================================================================
        mov cx,LENGTH
        lea bx,NUMBER
        add bx,LENGTH
        sub bx,1
        mov ah,2
Print:
        mov dl,[bx]
        cmp dl,0
        jz OutputOrNot
        mov FLAG,1
        add dl,48
        int 21H
        jmp PrintIter
OutputOrNot:
        mov al,FLAG
        add al,0        ;change sign flag
        jz PrintIter
        add dl,48
        int 21H
PrintIter:
        dec bx
        dec cx
        jnz Print

        .EXIT
        end