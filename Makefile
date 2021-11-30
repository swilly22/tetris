default:
	( cd build; cmake $(CMAKE_OPTIONS) .. ; $(MAKE) )

clean: distclean

# remove all files not in the distribution
distclean:
	rm -rf build/*

