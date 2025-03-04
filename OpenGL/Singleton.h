#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T _instance;
		return _instance;
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
};

#endif //SINGLETON_H