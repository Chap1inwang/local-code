#progma once

class noncopyable{
protect:
	noncopyable(){}
	~noncopyable(){}
private:
	noncopyable(const noncopyable&);
	const noncopyable& operator=(const noncopyable&);
};
