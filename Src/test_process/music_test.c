#include "test_process.h"

void music_doudizhu()
{
	buzzer_set_timebase(200);
	
	while(1)
	{
		wait_on_evts(EVT_BTN1_DN);
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_play(E, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 4, 3);
		buzzer_rest(1);
		
		buzzer_play(E, 4, 1);
		buzzer_rest(1);
		buzzer_play(E, 4, 1);
		buzzer_play(D, 4, 1);
		buzzer_play(E, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_play(E, 5, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 5, 1);
		buzzer_play(A, 4, 3);
		buzzer_rest(1);
		
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(E, 5, 1);
		buzzer_rest(1);
		buzzer_play(E, 5, 1);
		buzzer_play(G, 5, 1);
		buzzer_play(E, 5, 1);
		buzzer_rest(1);
		
		buzzer_play(D, 5, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_rest(1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 4, 1);
		buzzer_rest(1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(A, 4, 1);
		buzzer_play(B, 4, 1);
		buzzer_play(G, 4, 3);
		buzzer_rest(1);

	}
}

void music_monsterhunter()
{
	buzzer_set_timebase(80);
	while(1)
	{
		wait_on_evts(EVT_BTN1_DN);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_rest(2);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 6);
		buzzer_rest(2);
		buzzer_play(F, 5, 1);
		buzzer_rest(1);
		buzzer_play(Ds, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_play(As, 4, 4);
		buzzer_rest(2);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(Ds, 5, 2);
		buzzer_rest(2);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_play(As, 4, 4);
		buzzer_rest(2);
		buzzer_play(G, 4, 12);
		buzzer_rest(12);
		
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 4);
		buzzer_rest(2);
		buzzer_rest(2);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(D, 5, 1);
		buzzer_rest(1);
		buzzer_play(C, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 4, 1);
		buzzer_rest(1);
		
		buzzer_play(C, 6, 6);
		buzzer_rest(2);
		buzzer_play(As, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 6);
		buzzer_rest(6);
		
		buzzer_play(F, 5, 1);
		buzzer_rest(1);
		buzzer_play(G, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 2);
		buzzer_rest(2);
		buzzer_play(G, 5, 1);
		buzzer_rest(1);
		buzzer_play(Gs, 5, 1);
		buzzer_rest(1);
		buzzer_play(As, 5, 4);
		buzzer_rest(2);
		buzzer_play(D, 6, 4);
		buzzer_rest(2);
		buzzer_play(C, 6, 18);
		buzzer_rest(2);

	}
}
