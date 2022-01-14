CXXFLAGS = -lcurl
CXX = g++

all:
	$(CXX) get_song_list_PURE_C.cpp -o get_song_list_PURE_C $(CXXFLAGS)
	$(CXX) get_song_list.cpp -o get_song_list $(CXXFLAGS)
	$(CXX) get_file.cpp -o get_file $(CXXFLAGS)
