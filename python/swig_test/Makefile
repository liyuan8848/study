all:
	swig -python CswigToPY.i
	python setup.py build_ext --inplace

clean:
	rm -rf build
	rm CswigToPY.py*
	rm _*
