default: 
	gcc dash.c -o dash -lpthread

doc: 
	pandoc README.md -s -o final.pdf

