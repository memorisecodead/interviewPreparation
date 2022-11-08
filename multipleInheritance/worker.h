#pragma once
#include <string>
#include <iostream>

class Worker
{
private:
	std::string mFullName;
	unsigned int mID;
protected:
	virtual void data() const;
	virtual void getWorkerData();
public:
	Worker() : mFullName("no one"),mID(0){}
	Worker(const std::string& s, unsigned int n)
		: mFullName(s), mID(n) {}
	virtual ~Worker() = default;
	virtual void setWorkerData() = 0;
	virtual void showInfo() const = 0;
};	

class Waiter : virtual public Worker
{
private:
	int mPanache;
protected:
	void data() const;
	void getWorkerData();
public:
	Waiter() : Worker(), mPanache(0) {}
	Waiter(const std::string& s, unsigned int n, int p = 0)
		:Worker(s, n), mPanache(p) {}
	Waiter(const Worker& wk, int p = 0)
		: Worker(wk), mPanache(p) {}
	void setWorkerData();
	void showInfo() const;
};

class Singer : virtual public Worker
{
protected:
	enum {other, alto, contalto, soprano,
		bass, baritone, tenor};
	enum {Vtypes = 7};
	void data() const;
	void getWorkerData();
private:
	std::string mVoiceType[Vtypes];
	int mVoice;
public:
	Singer() :Worker(), mVoice(other) {}
	Singer(const std::string& s, unsigned int n, int v = other)
		: Worker(s,n),mVoice(v) {}
	Singer(const Worker& wk, int v = other)
		:Worker(wk), mVoice(v) {}
	void setWorkerData();
	void showInfo() const;
};

class SingingWaiter : public Singer, public Waiter
{
protected:
	void data() const;
	void getWorkerData();
public:
	SingingWaiter(){}
	SingingWaiter(const std::string& s, unsigned int n,
		int p, int v = other)
		: Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
	SingingWaiter(const Worker& wk, int p = 0, int v = other)
		:Worker(wk), Waiter(wk,p), Singer(wk, v) {}
	SingingWaiter(const Waiter& wt, int v = other)
		:Worker(wt), Waiter(wt), Singer(wt,v) {}
	SingingWaiter(const Singer& wt, int p = 0)
		:Worker(wt), Waiter(wt, p), Singer(wt) {}
	void setWorkerData();
	void showInfo() const;
};
