/*
 * main.c
 *
 *  Created on: Oct 8, 2014
 *      Author: sirius
 */

#include "routegame.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nLink 3
#define nPair 1
#define nStrategy (int) pow(nLink,nPair)
//nStrategy = number of strategy = number of multipath

int main(int argc, char *argv[])
{

	if (argc != 5 )
	{
		printf("unexpected number of arguments");
		return -1;
	}

	// PEMP coordination policies: 0 ~ NEMP 1 ~ Pareto frontier 2 ~ Unselfish Jump 3 ~ Pareto Jump
	int Policy;
	// Threshold
	float T;
	// use load balancing (1) or not (0)
	int uLB;

	sscanf(argv[2],"%d",&Policy);
	sscanf(argv[3],"%f",&T);
	sscanf(argv[4],"%d",&uLB);

	char input_filename[]="routingcost";
	path_cost	pathcost[nStrategy];
	loadFile(input_filename,pathcost);

	strategy_profile routinggame[nStrategy][nStrategy];
	routing_path selectedpath[nStrategy];
	char output_filename[]="routegame";
	/*
	int nP = routing_game_main(nStrategy,Policy,T,uLB,pathcost,routinggame,selectedpath);

	int i;
	for (i =0; i <nP; i++)
		printf("Link %d traffic loaded %f \n",selectedpath[i].id,selectedpath[i].tload);

	routing_game_output_file(output_filename,nStrategy, routinggame,nP,selectedpath);
	 */
	routing_path peer_selectedpath[nStrategy];
	routing_game_result_all(nStrategy,Policy,T,uLB,pathcost,routinggame,selectedpath,peer_selectedpath);
	routing_game_output_file_all(output_filename,nStrategy, routinggame,selectedpath,peer_selectedpath);


	return 1;

}
