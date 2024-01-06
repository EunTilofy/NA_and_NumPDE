all: Ch2_Answers.pdf

Ch2_Answers.pdf: Answers.tex
	xelatex Answers.tex
	bibtex Answers
	xelatex Answers.tex
	xelatex Answers.tex
	rm -f *.aux *.log \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Answers-blx.bib *.gz
	mv Answers.pdf ../Ch3_Answers.pdf

clean:
	rm -f *.aux *.log *.pdf \
	*.toc *.snm *.nav *.out \
	*.thm *.bbl *.ps *.dvi *.blg \
	*.bcf *.xml Answers-blx.bib *.gz

.PHONY: all clean