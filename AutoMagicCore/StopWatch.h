#pragma once

/************************************************************
************************************************************/

/**************************************************
-	前回アクセスから指定時間 経過しているかどうかを知るためのclass
-	初回アクセスはtrue
-	Reset機能あり
-	同じ時間に連続でアクセスした場合は、前回の結果(経過したかどうか)をそのまま返す
**************************************************/
class STOP_WATCH{
private:
	bool b_1stAccess;
	
	int t_Last_Access_ms;
	int TIMEOUT_ms;
	
	FILE *fp;
	
	bool b_IsTimePassed;
	
public:
	STOP_WATCH(int _TIMEOUT_ms);
	~STOP_WATCH();
	
	bool IsTimePassed(int now_ms);
	void Reset();
	void start(int now_ms, int _TIMEOUT_ms = -1);
};



