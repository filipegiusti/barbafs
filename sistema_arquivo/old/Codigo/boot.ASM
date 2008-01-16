.model small
.stack
.code 
;
;
;
	mov dx, seg FileName    : 
	mov ds,dx
	mov dx,offset FileName	; put offset of filename in dx
	mov al,2		; especifica  modo de leitura e escrita no arquivo
	mov ah,3Dh		; especifica que o arquivo (disk) vai ser aberto para leitura
	int 21h			; chama o serviço, de acordo com o valor ah e al sabe que deve abrir o arquivo e ler. Apos isso, o AX vai ter o valor de onde começa o arquivo	
	mov Handle,ax		; move para handle (ponteiro para o arquivo disk) o valor onde esta o arquivo
;
	mov dx, seg FileName2
	mov ds,dx
	mov dx,offset FileName2 ; put offset of filename in dx 
	xor cx,cx		; limpa cx para que posteriormente seja criado um arquivo. ISSO EH CODIGO, TEM Q FAZER 
	mov ah,3Ch		; function 3Ch - FUNÇAO Q CRIA UM ARQUIVO "NESTE CASO O ARQUIVO SE CHAMARA TEMP.EXE" OLHA LA EMBAIXO, NO FINAL DO ARQUIVO :p
	int 21h 
;
	mov dx, seg FileName2
	mov ds,dx
	mov dx,offset FileName2 ; put offset of filename in dx
	mov al,2		; especifica  modo de leitura e escrita no arquivo
	mov ah,3Dh		; function 3Dh - ABRE O ARQUIVO, NESTE CASO O TEMP.EXE
	int 21h 		; call dos service
	mov Handle2,ax	
;
;
;ATÉ AKI NO CODIGO, FOI ABERTO UM ARQUIVO disk.VDM E FOI CRIADO UM OUTRO "TEMP.EXE" E DP ESTE FOI ABERTO
;OU SEJA, ATE AKI TU TENS DOIS ARQUIVOS ABERTOS

	mov ah,42h		; posiciona ponteiro no inicio do arquivo
	mov al,0		; ISSO TUDO EH CODIGO
	mov bx,Handle		; COLOCA EM BX O PONTEIRO PARA O ARQUIVO HANDLE, NESTE CASO O disk.VDM
	mov cx,0		; CODIGO
	mov dx,1024		; posiciona no Byte 1024 DO ARQUIVO disk.VDM. nO NOSSO CASO, ERA NESSA POSIÇAO EM QUE ESTAVA O SO NO disk.VDM
	int 21h			; chama a funçao int 21h q posiciona de fato no byte 1024
	mov sp,40972		; numero de bytes que serao lidos no arquivo, no nosso caso, o tamanho do HPSYS
;
;nos dois proximos blocos de codigo é onde eh feita copia de um arquivo para outro
;esse buffer eu nao lembro pra que tem que usar ms provavelmente tenha que usar para chamar alguma int 21h
;na linha mov cx,1 esta especifica que sera copia um byte do arquivo disk.vdm. VAI SER COPIADO BYTE A BYTE DO ARQUIVO
;AIH USA UM LOOP E ENQTO A O VALOR DE SP(QUE EH O TAMANHO DO HPSYS DENTRO DO disk) NAO TIVER ACABADO ELE CONTINUA COPIANDO BYTE A BYTE
;
volta:	mov dx,seg Buffer
	mov ds,dx
	mov dx,offset Buffer	; address of buffer in dx
	mov bx,Handle		; handle in bx
	mov cx,1		; 
	mov ah,3Fh		; function 3Fh - read from file
	int 21h
	mov Handle,bx 
	add sp,-1	
	jz fim
;
	mov dx,seg Buffer
	mov ds,dx
	mov dx,offset Buffer   ; copia para o buffer
	mov bx,Handle2	       ; salva a posiçao corrente do arquivo
	mov cx,1	       ; 
	mov ah, 40h	       ;chama funçao de escrita
	int 21h
	mov Handle2,bx 
	jmp volta
;
;
;DP SIMPLESMENTE FECHA OS ARQUIVOS E TAH PRONTO
;
fim:	mov bx,Handle		; put file handle in bx 
	mov ah,3Eh		; function 3Eh - close a file
	int 21h 
;
	mov bx,Handle2		; put file handle in bx 
	mov ah,3Eh		; function 3Eh - close a file
	int 21h 
;
	
.data 
;
	FileName DB 'disk.vdm',0 ; name of file to open 
	FileName2 DB 'temp.exe',0 ; name of file to open 
	Handle	 dw 0	; to store file handle
	Handle2   dw 0	; to store file handle  
	Buffer db 1 dup (0)
end