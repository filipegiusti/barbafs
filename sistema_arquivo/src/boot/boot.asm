section .data
	arq_exec_tmp:	db 'temp.exe'	; Arquivo com o código do kernel pra ser executado
	DA_tempexe:	dw 1		; Descritor do arquivo temp.exe
	DA_disco:	dw 1		; Descritor do arquivo onde está o disco

section .bss
	buffer:		resb 1000	; Buffer para a transferencia de memoria dos arquivos


section .text
	global _start

_start:	mov	ebx,1		; Descritor da saida padrão
	pop	ecx		; Recebe o argc
	pop	ecx		; Recebe o argv[0] que é o nome do programa
	pop	ecx		; Recebe o argv[1]
	mov	eax, ecx	; Coloca a string no eax
	call	tamstr
	mov	edx, eax
	mov	eax,4		; sys_write
	int	80h


	mov	eax, 5		; sys_open
	mov	ebx, ecx	; argv[1]
	mov	ecx, 0
	int	80h
;	mov	DA_disco, ax

	mov	eax, 8		; sys_creat
	mov	ebx, arq_exec_tmp
	mov	ecx, 0		; mode
	int	80h
;	mov	DA_tempexe, ax

	mov	eax, 19		; sys_lseek
	mov	ebx, DA_disco	; descritor do arquivo
	mov	ecx, 1024	; offset do arquivo
	mov	edx, 0		; metodo de posicionamento
	int	80h

	mov	edi, 1000	; Tamanho do hpsys

	mov	eax, 3		; sys_read
	mov	ebx, DA_tempexe	; descritor do arquivo
	mov	ecx, buffer	; Buffer para transferencia
	mov	edx, 1000	; Quantidade de bytes pra ler
	int	80h

	mov	eax, 4		; sys_write
	mov	ebx, DA_disco	; descritor do arquivo
	mov	ecx, buffer	; Buffer para transferencia
	mov	edx, 1000	; Quantidade de bytes pra ler
	int	80h

	mov	eax,1		; sys_exit
	mov	ebx,0		; Código de retorno 0
	int	80h

; Conta o número de caracteres de uma string com terminador NULL
;
; Label de entrada:	tamstr
; Argumentos:		eax - Apontando para uma string terminada em NULL
; Retorno:		eax - Tamanho da string
; Modificações:	

tamstr:	push	ebx		; Salva ebx e edx
	push	edx
	xor	ebx, ebx	; Zera ebx que será usado como contador
tamstr1:mov	dl, [eax]
	cmp	dl, 0
	je	tamstr2		; Testa se encontrou o NULL
	inc	ebx		; Incrementa o contador
	inc	eax		; Vai avançando na string
	jmp	tamstr1		; Retorna pro looping
tamstr2:mov	eax, ebx	; Põe o resultado em eax
	pop	edx
	pop	ebx		; Restaura ebx
	ret
