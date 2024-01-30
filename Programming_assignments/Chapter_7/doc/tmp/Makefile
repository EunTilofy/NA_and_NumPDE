all: Report.pdf Design.pdf

Report.pdf: Report.tex
	xelatex Report.tex
	bibtex Report
	xelatex Report.tex
	xelatex Report.tex
	rm -f *.aux *.log \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Report-blx.bib *.gz
	mv Report.pdf ../
	xelatex Design.tex
	bibtex Design
	xelatex Design.tex
	xelatex Design.tex
	rm -f *.aux *.log \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Design-blx.bib *.gz
	mv Design.pdf ../

clean:
	rm -f *.aux *.log *.pdf \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Report-blx.bib *.gz Design-blx.bib

.PHONY: all clean