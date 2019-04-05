#pragma once

#define FLG_UPDATE 1
#define FLG_KEYPRESS 2
#define FLG_KEYHELD 3
#define FLG_KEYRELEASE 4
#define FLG_NUM 5
#define func(cs, xs) ((void(*)(cs*))&xs)


template<class _b>
struct eventHandler {
	public:
	eventHandler() {
		avEv.a = 0u;
	}
	void assign(int flg, void (*f)(_b*)) {
		if (flg > FLG_NUM || flg < 1) {
			return;				
		}
		if (f == nullptr) {
			return;
		}
		funcEvent[flg - 1] = f;
		avEv.a |= flg;
	}
	void handle(int flg) {
		if (flg > FLG_NUM || flg < 1) {
			return;
		}
		if (!(flg & avEv.a)) {
			return;
		}
		if (_referer == nullptr) {
			#if defined DEBUG || defined _DEBUG
				std::cout << "NO REFFERER" << std::endl;
				exit(1);
			#else
				return;
			#endif			
		}
	
		(*funcEvent[flg - 1])(_referer);
	}
	void setReferer(_b* obj) {
		_referer = obj;
	}
	//All events
	void (*funcEvent[FLG_NUM])(_b*);
	_b* _referer;
	
	union __av {
	char avEvents[4];
	int a;
	} avEv;
};