            .MODEL SMALL
            .STACK 100H
            .DATA
BUFFER      db 0
FILE        db "./lab2data.txt",0
OUTPUT      db "./lab2output.txt",0
HANDLE      dw 0
OUTPUTHAN   dw 0
ARRAY       dw 1024 dup(0)
LENGTH      dw 0
TEN         dw 10
HUNDRED     dw 100
THUSAND     dw 1000
TENTHUSAND  dw 10000
HEADZERO    db 0
strOpenFailed 	DB "the file open failed$",0
            .CODE
            .STARTUP
open_file_and_get_handle:
            mov ah,3dH      ;code to open file
            mov al,2        ;read-write mode
            lea dx,FILE
            int 21H
            jc  OpenFaildLT    ;file read error
            mov HANDLE,ax   ;save handle to file

            mov ah,3dH      ;code to open file
            mov al,2        ;read-write mode
            lea dx,OUTPUT
            int 21H
            jc  OpenFaildLT    ;file read error
            mov OUTPUTHAN,ax   ;save handle to file

            mov cx,0        ;count for number
            lea bx,ARRAY    ;set bx as pointer to array
    
add_new_number_into_array:
            mov dx,0
read_a_char:
            push bx
            push cx
            push dx

            mov bx,HANDLE
            mov cx,1
            lea dx,BUFFER
            mov ah,3fH
            int 21H

            pop dx
            pop cx
            pop bx
        
            test ax,ax      ;test EOF = 0, ax is the number of char get
            jz  data_get
trans_char_to_the_number:
            push bx
            mov bx,dx
            mov dl,BUFFER
            sub dl,48
            js  get_number_iteration
            push dx
            mov ax,10
            mul bx
            pop dx
            mov dh,0
            add ax,dx
            mov dx,ax
            pop bx
            jmp read_a_char
get_number_iteration:
            mov dx,bx
            pop bx
            push bx         ;get an CR and come here, read the following LF
            push cx
            push dx

            mov bx,HANDLE
            mov cx,1
            lea dx,BUFFER
            mov ah,3fH
            int 21H

            pop dx
            pop cx
            pop bx

            inc cx
            mov [bx],dx
            add bx,2
            jmp add_new_number_into_array
data_get:
            inc cx
            mov [bx],dx     ;there should be no CRLF after the last number
            mov LENGTH,cx

            add cx,cx
bubble_sort:
            mov bx,0                    ;set bx as array index pointer
            sub cx,2
            jz loop_to_store_the_result
sort_loop:
            cmp bx,cx
            jz  bubble_sort
            mov ax,ARRAY[bx]
            mov dx,ARRAY[bx + 2]
            cmp ax,dx
            jbe sort_loop_iter
            mov ARRAY[bx + 2],ax
            mov ARRAY[bx],dx
sort_loop_iter:
            add bx,2
            jmp sort_loop
;==================================================================================
            mov bx,0
loop_to_store_the_result:
            mov cx,LENGTH
            add cx,cx
            cmp bx,cx
            jz  finished

            mov ax,ARRAY[bx]
            push bx
            mov dx,0
            div TENTHUSAND
            push dx

            lea dx,BUFFER
            mov cx,1
            mov bx,OUTPUTHAN

            cmp al,0
            jz  write_thousand
            add al,48
            mov BUFFER,al
            mov ah,40H
            int 21H
            mov HEADZERO,1
write_thousand:
            pop ax
            mov dx,0
            div THUSAND
            push dx
            mov dl,HEADZERO
            add dl,0
            jnz thou_out
            cmp al,0
            jz  write_hundred
thou_out:   
            lea dx,BUFFER
            add al,48
            mov BUFFER,al
            mov ah,40H
            int 21H
            mov HEADZERO,1
write_hundred:
            pop ax
            mov dx,0
            div HUNDRED
            push dx
            mov dl,HEADZERO
            add dl,0
            jnz hund_out
            cmp al,0
            jz  write_ten
hund_out:   
            lea dx,BUFFER
            add al,48
            mov BUFFER,al
            mov ah,40H
            int 21H
            mov HEADZERO,1
write_ten:
            pop ax
            mov dx,0
            div TEN
            push dx
            mov dl,HEADZERO
            add dl,0
            jnz ten_out
            cmp al,0
            jz  write_one
ten_out:   
            lea dx,BUFFER
            add al,48
            mov BUFFER,al
            mov ah,40H
            int 21H
            mov HEADZERO,1
write_one:
            pop ax
            mov dx,0
            add al,48
            mov BUFFER,al
            mov ah,40H
            int 21H

            mov BUFFER,13
            mov ah,40H
            int 21H

            mov BUFFER,10
            mov ah,40H
            int 21H

            pop bx
            add bx,2
            mov HEADZERO,0
            jmp loop_to_store_the_result

OpenFaildLT:
		MOV AH, 9H
		MOV BX, 1
		MOV DX, OFFSET strOpenFailed
		INT 21H
		JMP finished

finished:
            .EXIT
            end