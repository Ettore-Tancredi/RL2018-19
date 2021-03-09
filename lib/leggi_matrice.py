def leggiDaFile(H, W, path)
	f = open(path, 'r')
	contenuto = f.read()
	matrice = [ [ 0 for i in range(W) ] for j in range(H) ]
	c = 0
	for i in contenuto: 
		if i != ' ':
			numero_str += str(i)
		else:
			numero = int(numero_str)
			matrice[int(c / W)][c % W] = numero
			numero_str = ""
			c = c + 1
			
	return matrice
