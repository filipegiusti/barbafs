hformat_fp = open("../../bin/hformat.bin", "rb")
hformat = hformat_fp.read()
hformat_fp.close()

boot = open("../../bin/boot.bin", "rb").read()
marca_ini = hformat.find("gambi_ini") + len("gambi_ini") 
marca_fim = hformat.find("gambi_fim")

conteudo = hformat[marca_ini:marca_fim]
head = hformat.split("gambi_ini")
tail = head[1].split("gambi_fim")
novo_hformat = head[0] + boot + tail[1]
hformat_fp = open("../../bin/hformat.bin", "wb")
hformat_fp.write(novo_hformat)
