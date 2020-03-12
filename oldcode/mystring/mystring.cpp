#include"mystring.h"
using namespace std;


mystring::mystring(){
	_reset();
}


void mystring::_reset(){
	if(_str==NULL){
		delete[] _str;
	}
	_str=nullptr;
	_str_len=0;
}

void mystring::_alloc_cstr(size_t sz){
	if(_str){
		_reset();
	}
	_str_len=(sz>_PSTRING_MAX_LEN)?_PSTRING_MAX_LEN:sz;
	_str=new char[_str_len+1];
}

void mystring::_swap(mystring& other){
	std::swap(_str,other._str);
	std::swap(_str_len,other._str_len);
}

void mystring::_copy_str(const char *s){
	if(s){
		size_t sz=strnlen(s,_PSTRING_MAX_LEN);
		_alloc_cstr(sz);
		strncpy(_str,s,sz);
	}
}


bool mystring::_have_value() const{
	return this->_str!=NULL&&this->_str_len!=0?true:false;
}


size_t mystring::_char_find( const char & match , size_t pos ) const{
	if(pos>=this->_str_len){
		return npos;
	}
	for(int i=0;i+pos<_str_len;++i){
		if(this->_str[i+pos]==match){
			return i;
		}
	}
	return npos;
}



void mystring::_char_replace( const char & match_char,const char & replace_char ){
	for(size_t i=0;i<_str_len;++i){
		if(_str[i]==match_char){
			_str[i]=replace_char;
			return;
		}
	}
	return;
}


mystring::mystring(const char* s){
	_copy_str(s);
}

mystring::mystring( const mystring & s ){
	_copy_str(s._str);
}           
mystring::mystring( mystring && s ) noexcept{
	_str=s._str;
	_str_len=s._str_len;
	s._reset();
}
mystring::~mystring(){
	_reset();
}


const char* mystring:: c_str() const{
	return _str;
}

mystring& mystring::operator = ( mystring s ){
	_reset();
	_alloc_cstr(s._str_len);
	for(size_t i=0;i<_str_len+1;++i){
		_str[i]=s._str[i];
	}
	return *this;
}

mystring& mystring::operator += ( const char* s ){
	size_t sz=_str_len+strlen(s);
	char* buf=new char[sz+1];
	if(_str&&_str_len){
		memcpy(buf,_str,_str_len);
	}
	memcpy(buf+_str_len,s,strlen(s));
	_reset();
	_str=buf;
	_str_len=sz;
	return *this;
}

mystring& mystring::operator += ( const mystring&  s ){
	this->operator+=(s._str);
	return *this;
}

//不是应该返回 char&吗？
char& mystring::operator [] ( const size_t index ) const{
	if(index>=_str_len){
		return *(_str+_str_len); 
	}
	return *(_str+index);
}


bool mystring::operator == ( const mystring & s ) const{
	if(_str_len!=s._str_len){
		return false;
	}
	for(size_t i=0;i<_str_len+1;++i){
		if(*(_str+i)!=s[i]){
			return false;
		}
	}
	return true;
}

bool mystring::operator != ( const mystring & s ) const{
	return !operator==(s);
}

bool mystring::operator >= ( const mystring & s ) const{
	if(std::strncmp(_str,s._str,_PSTRING_MAX_LEN)>=0){
		return true;
	}
	return false;
}

bool mystring::operator >  ( const mystring & s ) const{
	if(std::strncmp(_str,s._str,_PSTRING_MAX_LEN)>0){
		return true;
	}
	return false;
}

bool mystring::operator <= ( const mystring & s ) const{
	if(std::strncmp(_str,s._str,_PSTRING_MAX_LEN)<=0){
		return true;
	}
	return false;
}

bool mystring::operator <  ( const mystring & s ) const{
	if(std::strncmp(_str,s._str,_PSTRING_MAX_LEN)<0){
		return true;
	}
	return false;
}
    
mystring::operator const char * () const{
	return _str;
}


mystring mystring::lower() const{
	mystring res=*this;
	for(size_t i=0;i<_str_len;++i){
		res[i]=tolower(res[i]);
	}
	return res;
}

mystring mystring::upper() const{
	mystring res=*this;
	for(size_t i=0;i<_str_len;++i){
		res[i]=toupper(res[i]);
	}
	return res;
}

const char& mystring::back() const{
	return (*this)[_str_len-1];
}

const char & mystring::front() const{
	return (*this)[0];
}

mystring mystring::substr(size_t pos , size_t len ) const{
	mystring res;
	char* buf;
	if(len+1>_PSTRING_MAX_LEN||pos+len>_PSTRING_MAX_LEN){
		return res;
	}
	if(pos+len>=_str_len){
		return res;
	}
	if(_str==NULL){
		return res;
	}
	buf=new char[len+1];
	memcpy(buf,_str+pos,len);
	buf[len]='\n';
	res=buf;
	delete[] buf;
	return res;
}


size_t mystring::find( const mystring & str, size_t pos) const{
	return find(str._str,pos);
}

size_t mystring::find( const char * s, size_t pos) const{
	size_t index=npos;
	if(pos>_str_len){
		return index;
	}
	char* sub=strstr(_str+pos,s);
	if(sub!=NULL){
		return sub-_str;
	}
	return npos;	
}

size_t mystring::find( char c, size_t pos) const{
	return _char_find(c,pos);
}


mystring mystring::replace( size_t pos, size_t len, const mystring & str ){
	return replace(pos,len,str.c_str());
}


int mystring::compare (const mystring& str) const noexcept{
	return strncmp(this->c_str(),str.c_str(),_PSTRING_MAX_LEN);
}

int mystring::compare (const char * str) const{
	strncmp(this->c_str(),str,_PSTRING_MAX_LEN);
}

mystring operator + ( const mystring & lhs, const mystring & rhs ){
	mystring ans=lhs;
	ans+=rhs;
	return ans;
}

mystring operator + ( const mystring & lhs, const char * rhs ){
	mystring ans=lhs;
	ans+=rhs;
	return ans;
}




mystring mystring::replace( size_t pos, size_t len, const char * str ){
	mystring res;
	if((pos>=_str_len)||(pos+len>=_str_len)){
		return res;
	}
	mystring s1=pos>0?substr(0,pos):"";
	mystring s2=str;
	mystring s3=substr(pos+len,_str_len-(pos+len));
	mystring s4=s1+s2+s3;
	return s4;
}






