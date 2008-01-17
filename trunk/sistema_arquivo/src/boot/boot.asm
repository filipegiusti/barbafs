section .data
	arq_exec_tmp:	db 'temp.exe'	; Arquivo temporário que irá conter o código do kernel pra ser executado
	tam_hpsys:	equ 1000	; Tamanho do sistema operacional

section .bss
	buffer:		resb tam_hpsys	; Buffer para a transferencia de entre os arquivos
	DA_tempexe:	resd 1		; Descritor do arquivo temp.exe
	DA_disco:	resd 1		; Descritor do arquivo onde está o disco
;	tam_hpsys:	resd 1		; Tamanho do kernel

section .text
	global _start

_start:	mov	eax, 5		; sys_open
	pop	ebx		; Recebe o argc
	pop	ebx		; Recebe o argv[0] que é o nome do programa
	pop	ebx		; Recebe o argv[1]
;	pop	edx		; Recebe o argv[2]
;	mov	[tam_hpsys], edx; Salva o argv[2]
	mov	ecx, 0		; modo de abertura read_only
	int	80h
	mov	[DA_disco], eax	; Salva o descritor do arquivo

	mov	eax, 8		; sys_creat
	mov	ebx, arq_exec_tmp
	mov	ecx, 1		; mode
	int	80h
	mov	[DA_tempexe], eax	; Salva o descritor do arquivo

	mov	eax, 19		; sys_lseek
	mov	ebx, [DA_disco]	; descritor do arquivo
	mov	ecx, 1024	; offset do arquivo
	mov	edx, 0		; metodo de posicionamento
	int	80h

	mov	eax, 3		; sys_read
	mov	ebx, [DA_disco]	; descritor do arquivo
	mov	ecx, buffer	; Buffer para transferencia
	mov	edx, tam_hpsys	; Quantidade de bytes pra ler
	int	80h

	mov	eax, 4		; sys_write
	mov	ebx, [DA_tempexe]	; descritor do arquivo
	mov	ecx, buffer	; Buffer para transferencia
	mov	edx, tam_hpsys	; Quantidade de bytes pra escrever
	int	80h

	mov	eax,1		; sys_exit
	mov	ebx,0		; Código de retorno 0
	int	80h
