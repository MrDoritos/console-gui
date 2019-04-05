#include "eventHandler.h"

/*
template<class _b>
void eventHandler<_b>::assign(int flg, void (*f)(_b*)) {
	if (flg > FLG_NUM || flg < 1) {
		return;				
	}
	if (f == nullptr) {
		return;
	}
	funcEvent[flg - 1] = f;
	avEv.a |= flg;
}
*/

/*
template<class _b>
void eventHandler<_b>::handle(int flg) {
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
*/

/*
template<class _b>
void eventHandler<_b>::setReferer(_b* obj) {
	_referer = obj;
}
*/