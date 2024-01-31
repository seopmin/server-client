# install graphviz to use "dot" command
dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png

prepare:
	rm -rf build
	mkdir build
	cmake -S ./ -B ./build
	make -C ./build
	