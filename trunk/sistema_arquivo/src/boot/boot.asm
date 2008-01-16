section .data
	arq_exec_tmp:	db 'temp.exe'	; Arquivo com o código do kernel pra ser executado

section .bss
	

section .text
	global _start

_start:	mov eax,4		; The system call for write (sys_write)
	mov ebx,1		; File descriptor 1 - standard output
	mov ecx,arq_exec_tmp	; Put the offset of hello in ecx
	mov edx,8		; helloLen is a constant, so we don't need to say
				;  mov edx,[helloLen] to get it's actual value
	int 80h

	mov eax,1		; The system call for exit (sys_exit)
	mov ebx,0		; Exit with return code of 0 (no error)
	int 80h
