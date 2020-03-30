#pragma once

#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

static const size_t npos=-1;
static const char* _PSTRING_VISION="1.0.0";
static const int _PSTRING_MAX_LEN=65535;


class mystring {
	friend ostream& operator<<(ostream& ou ,mystring& obj){
		ou<<obj._str;
		return ou;
	}
    char * _str ;
    size_t _str_len = 0;

    //data allocation and dellocation
    void _alloc_cstr( size_t sz );                      //alloc memory for _str
    void _reset();                                        //for resetting data
    void _swap(mystring & s );                             //mem function swap.
    void _copy_str( const char * s );             //alloc and copy.


    //private utility functions
    bool _have_value() const;
    size_t _char_find( const char & match , size_t pos = 0) const;
    void _char_replace( const char & match_char,
                                 const char & replace_char );


  public:

    mystring();                                             //default constructor
    mystring( const char * c );                             //cstr constructor
    mystring( const mystring & s );                           //copy constructor
    mystring( mystring && s ) noexcept;                       //move constructor
    ~mystring();                                            //destructor


    const char * c_str() const;                           //getter
    //operators
    mystring & operator = ( mystring s );                     //copy and swap assignmment for move and copy assignment.
    mystring & operator += ( const mystring & s );            //concatenation for mystring
    mystring & operator += ( const char * s );              //concatenation for literals
    char& operator [] ( const size_t index ) const;  //subscript operator

    //comparison operator
    bool operator == ( const mystring & s ) const;
    bool operator != ( const mystring & s ) const;
    bool operator >= ( const mystring & s ) const;
    bool operator >  ( const mystring & s ) const;
    bool operator <= ( const mystring & s ) const;
    bool operator <  ( const mystring & s ) const;

    // conversion operators
    operator const char * () const;             // c-mystring type

    //utility methods
    size_t length() const { return _str_len; }
    size_t size() const { return _str_len; }
    mystring lower() const;
    mystring upper() const;
    const char & back() const;
    const char & front() const;
    mystring substr(size_t pos = 0, size_t len = npos) const;
    static const char * version() { return _PSTRING_VISION; }


    //find and replace utility functions
    size_t find( const mystring & str, size_t pos = 0) const;
    size_t find( const char * s, size_t pos = 0 ) const;
    size_t find( char c, size_t pos = 0) const;
    mystring replace( size_t pos, size_t len, const char * str );
    mystring replace( size_t pos, size_t len, const mystring & str );

    //compare
    int compare (const mystring& str) const noexcept;
    int compare (const char * str) const;
};

  mystring operator + ( const mystring & lhs, const mystring & rhs );
  mystring operator + ( const mystring & lhs, const char * rhs );








