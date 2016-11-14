all: writing

writing:
	latex main.tex
	bibtex main
	latex main.tex
	latex main.tex
	dvips -R -Poutline -t letter main.dvi -o main.ps
	ps2pdf main.ps
	
clean:
	rm -f main *.pdf *.ps *.dvi *.out *.aux *.bbl *.log *blg
	
.PHONY: all show clean ps pdf showps