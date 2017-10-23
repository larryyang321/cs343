#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>
//#include "test.cc"
#include "q1binsertsort.h"


template<typename T>
 _Coroutine Binsertsort {
    const T Sentinel;           // value denoting end of set
    T value;                    // communication: value being passed down/up the tree
    Binsertsort *less;
    Binsertsort *great;
	T pivot;		//compare with value
	//_Event Break{};
	//_Event init{};
    void main(){
	
	if(value == Sentinel){
		suspend();
		value = Sentinel;
		return;
	}
	pivot = value;
	suspend();
	
        Binsertsort<T> l(Sentinel);
        Binsertsort<T> g(Sentinel);
        less = &l;
        great = &g;	
		while(true){
			if(value == Sentinel){
				
				break;
			}
			if(value < pivot){
				less->sort(value);
			}else 	{
				great->sort(value);
			}
        		suspend();
		}
	
		//here for retrieve	
		less->sort(Sentinel);
		great->sort(Sentinel);
		suspend();
		while(true){
			T va;
			if(pivot == Sentinel){
				va = great->retrieve();
				value = va;
				if(value == Sentinel)return;	
			}else{
				va = less->retrieve();
				if(va == Sentinel){
					value = pivot;
					pivot = Sentinel;
				}else{
					value = va;
				}
			}
			suspend();
			
			

		}
		
	
		
	
    }             
  public:
    Binsertsort( T Sentinel ) : Sentinel( Sentinel ) {}
    void sort( T value ) {      // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {              // retrieve sorted value
        resume();
        return value;
    }
};
//copied from example code

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    string temp;
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	! ( ss >> temp );				// characters after conversion all blank ?
} // convert

enum { sizeDeflt = 20, codeDeflt = 5 };			// global defaults

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ size (>= 0 : " << sizeDeflt
	 << ") [ code (>= 0 : " << codeDeflt
	 << ") [ input-file [ output-file ] ] ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

void uMain::main() {
//    int size = sizeDeflt, code = codeDeflt;		// default value
    istream *infile = &cin;				// default value
    ostream *outfile = &cout;				// default value
//	void size;
//	void code;
    switch ( argc ) {
      case 3:
	try {
	    outfile = new ofstream( argv[2] );
	} catch( uFile::Failure ) {			// open failed ?
	    cerr << "Error! Could not open output file \"" << argv[2] << "\"" << endl;
	    exit(-1);
	} // try
        // FALL THROUGH
      case 2:
//	cout<<"here"<<endl;
	try {
	    infile = new ifstream( argv[1] );
	} catch( uFile::Failure ) {
	    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
	    exit(-1);
	} // try
	break;
        // FALL THROUGH
      /*case 3:
        if ( ! convert( code, argv[2] ) || code < 0 ) {	// invalid integer ?
	    usage( argv );
	} // if
        // FALL THROUGH
      case 2:
        if ( ! convert( size, argv[1] ) || size < 0 ) {	// invalid integer ?
	    usage( argv );
	} // if
        // FALL THROUGH
      case 1:						// all defaults
        break;*/
      default:	
	cerr << "Usage: "<<argv[0]<<" unsorted-file [ sorted-file ]" << endl;					// wrong number of options
	exit(-1);
	//usage( argv );
    } // switch

    //*infile >> noskipws;				// turn off white space skipping during input

   
	int number;
	while(true){
	*infile >> number;	
	if (!*infile) {
            break;
        }
	if(number == 0){
//		*outfile << "blank line from list of length 0 (not actually printed)";

//		*outfile<<endl;
	}

	TYPE value;
	int i = 0;
	Binsertsort<TYPE> start(SENTINEL);
	while(i < number){
		
		
		*infile >> value;
		if (!*infile) {
            		cerr<<"not enough input"<<endl;
        	}
		*outfile << value;
		if(i<(number - 1))*outfile << " ";
		start.sort(value);
		i++;
	}
	*outfile<<endl;
	start.sort(SENTINEL);
	i = 0;
	 if(number == 0){

//		*outfile <<endl;
//                *outfile << "blank line from list of length 0 (not actually printed)";
        }
	while(i < number){
		TYPE v = start.retrieve();
		*outfile << v;
		if(i<(number - 1))*outfile << " ";
		i++;
	}
	*outfile<<endl;
	*outfile<<endl;
	
	}
    if ( infile != &cin ) delete infile;		// close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		// close file, do not delete cout!
} // main

