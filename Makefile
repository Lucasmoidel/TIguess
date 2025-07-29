NAME = TIguess
include $(CEDEV)/meta/makefile.mk

upload:
	tilp --calc=ti84+ --cable=DirectLink --port=1 --timeout=5 --no-gui bin/$(NAME).8xp