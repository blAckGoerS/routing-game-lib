# The routing game library 

OVERVIEW
--------

* The routing game library (RGL) is an open source library to compute equilibrium routing solutions in strategic routing settings, i.e., situations where two independent entities (for example, routers, devices) send traffic to each other using multiple paths or interfaces.

* By calling the built-in functions provided by the RGL, one can build a 2-player routing game from an input route cost array, and then compute the routing decision (for example, paths, egress interfaces) determined by the corresponding non-cooperative game equilibrium profiles. The equilibrium computation methods available are those presented in [1].

* The main functions of the routing game library are :
	+ Encode/decode cost arrays/components into/from a 32-bit value, obtained by function call or a configuration file
	+ Compute different routing game parameters related to the routing computation method (for instance, the equilibrium threshold, the load balancing rule, etc) 
	+ Find game equilibrium profiles and load-balancing weights accordingly
	+ Return and save the results

You can download the latest version of the library from https://github.com/routing-games/routing-game-lib .


HOW TO USE
----------

1> Import the library by copying these two following files into your project, and including the header file "rgl.h" in your source code
	rgl.c 
	rgl.h 

2> RGL provides two built-in functions: routing_game_main() and routing_game_output_file()

* routing_game_main(int N, int P, float T, int U,path_cost PATHCOST[],strategy_profile ROUTINGGAME[n][n],routing_path SELECTEDPATH[]) 

	This is the core function of the library. It combines multiple tasks (reading input cost array, loading configuration parameters, building routing game, computing payoff, calculating potential value, finding equilibrium strategy profiles and weighting selected profiles) into one function call. 
	The input parameters of this function include: 
		N : an integer number indicating the number of strategy available for each player (note that the number of strategy is the same for both players).
		P : an integer number ranging from 0 to 3 and representing the coordination policy used in the routing game.
		T : a real number, the potential threshold applied to elect routing game equilibria.
		I : an integer numner that only accept 0 or 1 as its value, in which 0 means to use the standard even load-balancing, while 1 indicates turning on explicit load-balancing 

		PATHCOST: an array of path_cost type - path_cost is a data type that keeps all the routing costs associated with a path in one structure. 

		struct path_cost
		{
			unsigned int path_id;
      unsigned int egresscost;           // ingress routing cost at local node  
			unsigned int Pingresscost;         // ingress routing cost at external node 
			unsigned int Pegresscost;          // egress routing cost at local node  
			unsigned int ingresscost;          // ingress routing cost at external node
		}

		ROUTINGGAME: an empty 2D array of strategy_profile type - strategy_profile is a data type to store the payoff and potential value associated with each strategy profile. ROUTINGGAME[i][j] is a representation of strategy profile (i,j). Routing_game_main() maintains and updates this array with payoff and potential value for every strategy profiles.

		struct strategy_profile
		{
			unsigned int 	localcost; 		// IGP routing cost
			unsigned int 	peercost; 		// IGP routing cost at peer site
			int		      pvalue; 	      // potential value
			short       eq;  			      // equilibria or not ? 1 YES 0 NO
			short       pe;  			      // pareto optimum or not ? 1 YES 0 NO
			short       status;         // selected or not? 1 YES 0 NO. Determined regarding the routing policy

		}

		SELECTEDPATH: is an empty array of routing_path type - routing_path is a data type to store paths selected as solutions by the routing game.
		
		struct routing_path
    {
			int     id;
			int     ingresscost;
			int     egresscost;
			int     freq;                     	// frequency of occurrence in the array
			int     pvalue;				              // potential value
			int     status;                  	  // 1 selected, 0 not selected
			float   tload;              		    // computed traffic load on this path
		}

	The output of routing_game_main() is therefore recorded in ROUTINGGAME and SELECTED arrays. 
	
* routing_game_output_file(char FILENAME[],int n, strategy_profile ROUTINGGAME[][], int npath,routing_path SELECTEDPATH[])
	The logging function that records the routing decision process (starts from building routing game until the decision is made) into an output text file. 
	It processes the ROUTINGGAME and SELECTEDPATH arrays.  


KNOWN APPLICATIONS
---------------

* RGL is used in a patched version of Quagga to support the functions of a PEMP enable router [1]. More information about this project could be found on https://github.com/routing-games/quagga. 
* Further envisioned applications are to MPTCP and LISP load-balancing, see [2,3].




REFERENCES
----------

[1] Stefano SECCI, Jean-Louis ROUGIER, Achille PATTAVINA, Fioravante PATRONE, Guido MAIER, "Peering Equilibrium MultiPath Routing: a game theory framework for Internet peering settlements", IEEE/ACM Transactions on Networking, Vol. 19, No. 2, pp: 419-432, April 2011. http://www-phare.lip6.fr/~secci/papers/SeRoPaPaMa-ToN-11.pdf

[2] Stefano SECCI, Kunpeng LIU, Bijan JABBARI, "Efficient Inter-Domain Traffic Engineering with Transit-Edge Hierarchical Routing", Computer Networks, Vol. 57, No. 4, pp: 976-989, March 2013. https://www-phare.lip6.fr/~secci/papers/SeLiJa-COMNET13.pdf

[3] Stefano SECCI, Guy PUJOLLE, Thi-Mai-Trang NGUYEN, Sinh-Chung NGUYEN, "Performance-Cost Trade-off Strategic Evaluation of Multipath TCP Communications", IEEE Transactions on Network and Service Management. Vol. 11, No. 2, pp: 250-263, June 2014. https://www-phare.lip6.fr/~secci/papers/SePuNgNg-TNSM14.pdf

