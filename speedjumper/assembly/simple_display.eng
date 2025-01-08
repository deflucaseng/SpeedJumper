
section .data
	true_msg db 'true', 0xA
	true_len equ $ - true_msg
	false_msg db 'false', 0xA
	false_len equ $ - false_msg
	newline db 10

section .text
	global _start

_start:
                mov eax, 1
                mov dword [num_to_print], eax
                jmp start_num_print
            
                mov eax, 2
                mov dword [num_to_print], eax
                jmp start_num_print
            
                mov eax, 3
                mov dword [num_to_print], eax
                jmp start_num_print
            
mov eax, 1
mov dword [test1], eax

mov eax, 0
mov dword [test2], eax

                mov eax, [test1]
                cmp eax, 1
                jne print_false
                jmp print_true
            
                mov eax, [test2]
                cmp eax, 1
                jne print_false
                jmp print_true
            
print_true:
	mov ecx, true_msg
	mov edx, true_len
	jmp do_print
print_false:
	mov ecx, false_msg
	mov edx, false_len
do_print:
	mov eax, 4
	mov ebx, 1
	int 0x80
	jmp print_newline
start_num_print:
	mov ecx, buffer
	add ecx, 11
	mov byte [ecx], 0
	dec ecx
	mov ebx, 10
convert_loop:
	xor edx, edx
	div ebx
	add dl, \'0\'
	mov [ecx], dl
	dec ecx
	test eax, eax
	jnz convert_loop
	mov eax, [num_to_print]
	test eax, eax
	jns print_number
	mov byte [ecx], \'-\'
	dec ecx
print_number:
	mov edx, buffer
	add edx, 11
	sub edx, ecx
	inc ecx
	mov eax, 4
	mov ebx, 1
	int 0x80
	jmp print_newline
print_newline:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 0x80
	jmp [lastknownpos]

section .bss
	num_to_print resd 1
	lastknownpos resd 1
	buffer resb 12
	test2 resd 1
	test1 resd 1
