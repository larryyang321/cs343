#include <cmath>
#include <iostream>
#include "PRNG.h"//download from online cs246
#include "q2.h"
using namespace std;
PRNG *prng;

unsigned int numberofplayer;
_Event Stop{};
_Event Dr{};
_Coroutine Player {
	int id;
    	Player *left=NULL;
	Player *right=NULL;
	int card_remain;
	Printer *pt;
	bool out = false;
	
	bool startdrink = false;
	void main(){
		try{
		_Enable{
		while(true){
			
			if((numberofplayer == 1)){
                                pt->prt(id,0,numberofplayer);
                                break;
                        }
			
			int withdraw = 0;
			
				withdraw = (*prng)(1,8);
			
			int remain = max(0,card_remain-withdraw);
			
			if(remain == 0){
				withdraw = card_remain;
				pt->prt(id,withdraw,numberofplayer);
				pt->prt(id,withdraw,numberofplayer);
				break;
			}
			pt->prt(id,withdraw,numberofplayer);

			if((card_remain%DEATH_DECK_DIVISOR == 0)){
                          
				
				      out = true;
				card_remain = card_remain - withdraw;
                                numberofplayer = numberofplayer -1;
				break;
                        }
			
                                if((*prng)(0,9)==0){
                                        startdrink = true;
                                        pt->prt(id,-1,numberofplayer);
                                        _Resume Dr() _At *right;
                                        right->drink();
                                }

                        	
			if(remain%2 == 0){
				right->play(remain);
			}else{
				left->play(remain);
			}
		}
		//winner here
		if(out){
			while(true){
				if(card_remain%2 == 0){
                                	right->play(card_remain);
                        	}else{
                                	left->play(card_remain);
                        	}
			}

		}
		_Resume Stop() _At *left;
		left->play(0);
		
		}
		}_CatchResume(Dr){
			if(startdrink){
				startdrink = false;
			}else{
			if(!out){
				pt->prt(id,-1,numberofplayer);
			}
			_Resume Dr() _At *right;
                        right->drink();}

		}catch(Stop){

			
                        _Resume Stop() _At *left;
                        left->play(0);

                }
	}
	// YOU MAY ADD PRIVATE MEMBERS, INCLUDING STATICS
  public:
    enum { DEATH_DECK_DIVISOR = 7 };
    static void players( unsigned int num ){
		numberofplayer = num;
	}
    Player( Printer &printer, unsigned int id ):id(id){
		pt = &printer;
	}
    void start( Player &lp, Player &rp ){
		left = &lp;
		right =&rp;
	}
    void play( unsigned int deck ){
		
		card_remain = deck;
		resume();
	}
		
    void drink(){
		resume();
		

	}
};


Printer::Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards ){
		numberp = NoOfPlayers;
		numbercard = NoOfCards;
		cout<<"Players: "<<NoOfPlayers<<"    "<<"Cards: "<<NoOfCards<<endl;
		int i =0;
		
		withdraw = new int[NoOfPlayers];
		card_pass = new int[NoOfPlayers];
		flush = new bool[NoOfPlayers];
		while(i < ((int)NoOfPlayers-1)){
			cout<<"P"<<i<<'\t';
			flush[i]=false;
			i++;

		}
		cout<<"P"<<i;
		flush[i]=false;
		cout<<endl;
	}
    void Printer::prt( unsigned int id, int took, int RemainingPlayers ){
		if(flush[id]){
			int i =0;
			int numneedprint =0;
			while(i<numberp){
				if(flush[i])numneedprint++;
				i++;
			}
			
			i=0;
			
			while(i < numberp){
				if(flush[i]){
					numneedprint--;	
					bool out = false;
					bool winner = false;
					winner = (card_pass[i] == 0);			
					out = ((withdraw[i]+card_pass[i])%Player::DEATH_DECK_DIVISOR == 0);
					
						

				if(withdraw[i]==-1){
					cout<<"D";
					flush[i] = false;
				}else{			

					cout<<withdraw[i]<<":"<<card_pass[i]<<(winner ? "#":"");
					if(winner){
					
						cout<<(out ? "X" : "");
					}else{
						cout<<((card_pass[i]%2 == 0) ? ">" : "<")<<(out ? "X" : "");
					}
					flush[i]=false;
				}
				if(numneedprint!=0)cout<<'\t';
				
				}else{
					if(numneedprint==0){}
					else if(i<(numberp-1)){
						cout<<'\t';
					}else{}
				}
					

				i++;
			}
			cout<<endl;
		}
		flush[id] =true;
		
		withdraw[id] = took;
		if(took == -1){}else{
		card_pass[id] = numbercard - took;
		numbercard = numbercard-took;}
		if(RemainingPlayers == 1){
			int i =0;
			int np = 0;
			while(i < numberp){
				if(flush[i])np++;
				i++;
			}
			i=0;
			while(i < numberp){
				if(flush[i]){
					np--;
                                        bool out = false;

                                        out = ((withdraw[i]+card_pass[i])%Player::DEATH_DECK_DIVISOR == 0);
                                        
					if(i ==(int) id){
						cout<<"#"<<numbercard<<"#"<<(out ? "X" : "");

					}else{
						cout<<withdraw[i]<<":"<<card_pass[i]<<((card_pass[i]%2 == 0) ? ">" : "<")<<(out ? "X" : "");
                                        }
					flush[i]=false;

				if(np!=0)cout<<'\t';
                                }else{
					if(np == 0){}
                                        else if(i <(numberp -1)){
						cout<<'\t';
					}else{}
                                }

                                i++;

			}
			cout<<endl;
		}
		
	}
Printer::~Printer() {
    delete []flush;
	delete[] withdraw;
	delete[] card_pass;
}





void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
         << " [ games (>= 0) | \"x\" [ players (>= 2) | \"x\" [ cards (> 0) | \"x\" [ random-seed (> 0) | \"x\" ] ] ] ]" << endl;
    exit( EXIT_FAILURE );                               // TERMINATE
}
void uMain::main(){
	int game = 5; //default
	int seed = getpid();
	unsigned int cards =0;//if no card value is assigned, random between 10 200
	unsigned int players =0;//no player value is assigned, random between 2 10
	switch(argc){
		
		case 5:
			seed = stoi(argv[4]);
			if(seed <= 0)usage(argv);
		case 4:
			try{
			cards = stoi(argv[3]);}
			catch(invalid_argument& e){
				cards = 0;
			}
                        //if(card <= 0)usage(argv);
		case 3:
			try{
			players = stoi(argv[2]);}
			catch(invalid_argument& e){
				players = 0;
			}
			//if(player < 2)usage(argv);
		case 2:
			game = stoi(argv[1]);
			if(game<0)usage(argv);
		default:
			break;		



	}
	prng = new PRNG(seed);
	//init
	int gamenumber = 0;
	while(gamenumber < game){
	unsigned int player = players;
	unsigned int card = cards;
//	if(cards == 0)card = (*prng)(10,200);
	
	if(player == 0)player = (*prng)(2,10);
if(cards == 0)card = (*prng)(10,200);
	Player::players(player);
	int first = (*prng)(0,player-1);
	
	int i =0;
	Printer p(player,card);
	Player* people[player];
	while(i <(int) player){
		people[i] = new Player(p,i);
		i++;
	}
	i = 0;
	while(i <(int)player){
		people[i]->start(*people[(i-1+player)%player],*people[(i+1)%player]);
		i++;
	}
	
	people[first]->play(card);
	i = 0;
	while(i < (int)player){
		delete people[i];
		i++;
	}
	if(gamenumber != (game -1)){
	cout<<endl;
	cout<<endl;	
	}
	gamenumber++;
	}
	
	delete prng;


}
