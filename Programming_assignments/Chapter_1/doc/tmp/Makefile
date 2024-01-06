all: Report.pdf

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

clean:
	rm -f *.aux *.log *.pdf \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Report-blx.bib *.gz

.PHONY: all clean