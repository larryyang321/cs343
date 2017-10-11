#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>
#include "test.cc"



template<typename T>
 _Coroutine Binsertsort {
    const T Sentinel;           // value denoting end of set
    T value;                    // communication: value being passed down/up the tree
    Binsertsort *less;
    Binsertsort *great;
	T pivot;
	_Event Break{};
	_Event init{};
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
    int size = sizeDeflt, code = codeDeflt;		// default value
    istream *infile = &cin;				// default value
    ostream *outfile = &cout;				// default value

    switch ( argc ) {
      case 5:
	try {
	    outfile = new ofstream( argv[4] );
	} catch( uFile::Failure ) {			// open failed ?
	    cerr << "Error! Could not open output file \"" << argv[4] << "\"" << endl;
	    usage( argv );
	} // try
        // FALL THROUGH
      case 4:
	try {
	    infile = new ifstream( argv[3] );
	} catch( uFile::Failure ) {
	    cerr << "Error! Could not open input file \"" << argv[3] << "\"" << endl;
	    usage( argv );
	} // try
        // FALL THROUGH
      case 3:
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
        break;
      default:						// wrong number of options
	usage( argv );
    } // switch

    //*infile >> noskipws;				// turn off white space skipping during input

   
	int number;
	*infile >> number;	
	TYPE value;
	int i = 0;
	Binsertsort<TYPE> start(SENTINEL);
	while(i < number){
		
		
		*infile >> value;
		start.sort(value);
		i++;
	}
	start.sort(SENTINEL);
	i = 0;
	while(i < number){
		TYPE v = start.retrieve();
		*outfile << v <<endl;
		i++;
	}

    if ( infile != &cin ) delete infile;		// close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		// close file, do not delete cout!
} // main

