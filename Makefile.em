OUTPUT=prototracker
SRC=src/*.cpp

$(OUTPUT).html: $(SRC) src/*.h
	emcc -Wformat -std=c++11 --preload-file assets -O3 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS='["_main","_emFilesSyncedStartup","_emFilesSyncedShutdown","_emOnFileImported","_emExportFile","_emNewSong","_emPlaySong","_emRequestSong"]' -s SDL2_IMAGE_FORMATS='["png"]' \
		-DOVERSAMPLE=3 -DSAMPLERATE=22050 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 $(wildcard *.cpp) -o $@