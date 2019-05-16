#pragma once
#include <iostream>
#include <string>

using namespace std;
class BanDoc;
class Sach;
class PhieuMuon;
class Date
{
	int nNgay;
	int nThang;
	int nNam;
public:
	friend BanDoc;
	friend Sach;
	friend PhieuMuon;
	Date(int nNgay = 0, int nThang = 0, int nNam = 0)
	{
		this->nNgay = nNgay;
		this->nThang = nThang;
		this->nNam = nNam;
	}
	void setNgay(int d);
	void setThang(int m);
	void setNam(int y);
	int getNgay();
	int getThang();
	int getNam();
	void xuat();
	~Date(void){};
};