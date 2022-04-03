
random_player:
	g++ -std=c++11 random_player.cpp -o random_player

clean:
	rm -f torneo *.o *~
	rm -f random_player *.o *~
	rm -f nextPlay *.o *~
	rm -f grid *.o *~
	rm -f genetic *.o *~
	rm -f geneticPlayer *.o *~
	rm -f gridPlayer *.o *~

nextPlay:
	g++ -o nextPlay nextPlay.cpp defines.cpp

grid:
	g++ -o grid grid_search.cpp defines.cpp neighbourhood.cpp our_referee.cpp

genetic:
	g++ -o genetic genetic_search.cpp defines.cpp our_referee.cpp generation.cpp

torneo:
	g++ -o torneo tournament_exp.cpp defines.cpp our_referee.cpp generation.cpp

gridPlayer:
	g++ -o gridSearchPlayer.cpp defines.cpp	

geneticPlayer:
	g++ -o geneticSearchPlayer.cpp defines.cpp	