
#!/bin/bash
swig -python CswigToPY.i
python setup.py build_ext --inplace
