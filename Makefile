COMPILE=g++
all:
	$(COMPILE) -o bin/bts-new src/bts-new.cpp
	$(COMPILE) -o bin/bts-init src/bts-init.cpp
	$(COMPILE) -o bin/bts-help src/bts-help.cpp
	$(COMPILE) -o bin/bts-find src/bts-find.cpp
	$(COMPILE) -o bin/bts-change-fix src/bts-change-fix.cpp

install:
	sudo cp bin/* /usr/local/bin
