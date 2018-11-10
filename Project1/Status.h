
#ifndef STATUS_H
#define STATUS_H

#include <iostream>

#define STATUS_RESUME_PVP 1
#define STATUS_RESUME_PVC 2
#define STATUS_PVP 3
#define STATUS_PVC 4
#define STATUS_SETTING 5
#define STATUS_SAVE 6
#define STATUS_LOAD 7
#define STATUS_STAT 8
#define STATUS_EXIT 9

#define STATUS_NONE -1

class Status
{
private:
	int rightSideScreen;
	bool isPlay;
	int status;
public:
	int getRightSideScreen() {
		return rightSideScreen;
	}
	void setRightSideScreen(int k) {
		rightSideScreen = k;
	}
	bool getIsPlay() {
		return isPlay;
	}
	void setIsPlay(bool c) {
		isPlay = c;
	}
	int getStatus() {
		return status;
	}
	void setStatus(int a) {
		status = a;
	}
	Status() {
		rightSideScreen = 0;
		status = -1;
	}
};

#endif // !STATUS_H

