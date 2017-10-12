#ifndef PRINT_H
#define PRINT_H
class Printer {
    // YOU MAY ADD PRIVATE MEMBERS
        int *withdraw;
        int *card_pass;
        bool *flush;
        int numberp;
        int numbercard;
	public:
	~Printer();
	Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards );
	void prt( unsigned int id, int took, int RemainingPlayers );
};

#endif
