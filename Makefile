.PHONY: eddy clean tags

tags:
	etags ./lib/raylib/build/**/*.h *.c ./src/*.h

eddy:
	gcc main.c -o eddy -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I./lib/raylib/build/include -L./lib/raylib/build/lib -lraylib

clean:
	$(RM) eddy *.o

raylib:
#	buiding for 14.3 aka Sonoma doesn't seem to work correctly yet
	MACOSX_DEPLOYMENT_TARGET=14.0 $(MAKE) -C ./lib/raylib/src
	DESTDIR=../build $(MAKE) -C ./lib/raylib/src install-macos

# ADD THE FOLLOWING TARGET TO raylib/src/Makefile for the install step to work on macos
# install-macos :
# 	mkdir -p $(RAYLIB_INSTALL_PATH) $(RAYLIB_H_INSTALL_PATH)
# 	cp -v ./lib$(RAYLIB_LIB_NAME).a $(RAYLIB_INSTALL_PATH)/lib$(RAYLIB_LIB_NAME).a
# 	cp raylib.h $(RAYLIB_H_INSTALL_PATH)/raylib.h
# 	cp raymath.h $(RAYLIB_H_INSTALL_PATH)/raymath.h
# 	cp rlgl.h $(RAYLIB_H_INSTALL_PATH)/rlgl.h
# 	@echo "raylib development files installed/updated!"
