default: 
	gcc dash.c -o dash

doc: 
	pandoc README.md -s -o final.pdf

