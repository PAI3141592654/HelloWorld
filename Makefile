mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))

mkfile_dir := $(dir $(mkfile_path))

all:install  report

install:
	make Mandelbrot_Linux
	make Mandelbrot_Windows

Mandelbrot_Linux:
	ln -s $(mkfile_dir)  ~/Mandelbrot_Set
	gcc -o ~/Mandelbrot_Set/bin/Mandelbrot_Linux ~/Mandelbrot_Set/src/Mandelbrot_Linux.c
	rm ~/Mandelbrot_Set

Mandelbrot_Windows:
	ln -s $(mkfile_dir)  ~/Mandelbrot_Set
	gcc -o ~/Mandelbrot_Set/bin/Mandelbrot_Windows ~/Mandelbrot_Set/src/Mandelbrot_Windows.c
	rm ~/Mandelbrot_Set

report:
	ln -s $(mkfile_dir)  ~/Mandelbrot_Set
	cp ~/Mandelbrot_Set/examples/* ~/Mandelbrot_Set
	cp ~/Mandelbrot_Set/doc/* ~/Mandelbrot_Set
	xelatex ~/Mandelbrot_Set/man.tex
	bibtex man.aux
	xelatex ~/Mandelbrot_Set/man.tex
	xelatex ~/Mandelbrot_Set/man.tex
	rm ~/Mandelbrot_Set/man.aux
	rm ~/Mandelbrot_Set/man.log
	rm ~/Mandelbrot_Set/1.png
	rm ~/Mandelbrot_Set/2.png
	rm ~/Mandelbrot_Set/3.jpg
	rm ~/Mandelbrot_Set/4.jpg
	rm ~/Mandelbrot_Set/5.png
	rm ~/Mandelbrot_Set/6.png
	rm ~/Mandelbrot_Set/man.tex
	rm ~/Mandelbrot_Set/ref.bib
	rm ~/Mandelbrot_Set/man.blg
	rm ~/Mandelbrot_Set/man.bbl
	mv ~/Mandelbrot_Set/man.pdf ~/Mandelbrot_Set/report.pdf
	mv ~/Mandelbrot_Set/report.pdf ~/Mandelbrot_Set/doc/report.pdf
	rm ~/Mandelbrot_Set

clean:
	ln -s $(mkfile_dir) ~/Mandelbrot_Set
	rm ~/Mandelbrot_Set/bin/Mandelbrot_Linux
	rm ~/Mandelbrot_Set/bin/Mandelbrot_Windows
	rm ~/Mandelbrot_Set/doc/report.pdf
	rm ~/Mandelbrot_Set
