all:
	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o bubble \
	    src/bubble/bubble_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o insertion \
	    src/insertion/insertion_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o selection \
	    src/selection/selection_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer
	
	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o quick \
	    src/quick/quick_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o merge \
	    src/merge/merge_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o bogo \
	    src/bogo/bogo_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer

	g++ -I src_SDL/include \
	    -L src_SDL/lib \
	    -L /usr/lib/gcc/x86_64-w64-mingw32/11 \
	    -o Stalin \
	    src/Stalin/Stalin_sort.cpp \
	    -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer	