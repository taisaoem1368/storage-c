/*
Đồ Án Số 02
 Nhóm 4
 1. Hồ Văn Quyến
 2. Nguyễn Lê Thành Công
 3. Ngô Hữu Thế
 4. Nguyễn Viết Hiếu
*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;
// ===== KHAI BÁO CẤU TRÚC KHÁCH HÀNG =====
struct KhachHang
{
	string sUser;
	string sPass;
	string sSTK;	
	string sHoTen;
	double fSoDu;
	string sLoaiTien;
	string sChiNhanh;
};
// ===== KHAI BÁO 1 CÁI NODE CHO KHÁCH HÀNG =====
struct Node
{
	KhachHang nData; //Dữ liệu của Node
	Node * pNext;	//Con trỏ dùng liên kết các cái Node
};
Node * getNode(KhachHang X)
{
	Node * p = new Node;
	p->nData = X; //đưa dữ liệu biến x khách hàng vào data
	p->pNext = NULL; //khởi tạo node p, hiện tại node p chưa có liên kết
	return p;
}
// ===== KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN =====//
struct List
{
	Node * pHead;
	Node * pTail;
};
//========THÔNG TIN TRỤ ATM=========//
string sMaATM = "998091"; //Mã trụ ATM
void input_1_Data(ifstream &Filein, KhachHang &kh);
void input_All_Data(ifstream &Filein, List &L);
void textcolor(WORD color);
//Ghi dữ liệu
void output_Data(List &L);
void initial(List &L);
void inputTail(List &L, Node *p);
void output(List L);
void outputToScreen(List L);
void xuat(KhachHang kh);
int maGiaodich();
// đăng nhập 
string passwordInput(unsigned maxLength);
void login(List L);
// rút tiền
void withdrawal(List L, Node * q);
void vien_thong_bao(string sVien);
void transfers(List L, Node * q);
void changePassword(List L, Node * q);
void thongTinTK(List L, Node * q);
void transaction_history(List L, Node * q, string type_perform, int nTienTru, Node * g, int PhiGD);
void outscreen_transaction_history(Node * q);
void inHoaDon(List L, Node * q, int nTienRut, int PhiGD,  Node * g, string sForm);
int nPhiGiaoDich(int nTienNhap, string sForm);
string kiemTraTime(string s, Node * q);
void recharge(List L, Node * q);
void luaChon();
int nDemSoLuongKhachHang();
//Code chỉnh kích thước màn hình visua khi chạy chương trình
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void main()
{
	
	List L;
	initial(L); // Tạo 1 List mới
	ifstream File; //Mở File Input đưa dữ liệu vào
	File.open("input.txt", ios::in);
	input_All_Data(File, L); // hàm nhập dữ liệu từ file
	File.close();
	Node * q = new Node;
	Node * g = new Node;
	login(L);
	system("pause");
}
//Đăng nhập
void login(List L)
{
	int nChon = 0;
	int i = 0;
	int nLan = 2;
	string sUsername = " ";
	string sPassword = " ";
	int flag = 0;
	int nDem = 0;
	vien_thong_bao("LOGIN");
	cout << "\t\t\tLuu y: Nhap ";
	textcolor(4);
	cout << "ESC";
	textcolor(7);
	cout << " de thoat khoi chuong trinh\n" << endl;
	while(i < 3)
	{
		textcolor(2);
		cout << "\t\t\tNhap tai khoan: ";
		textcolor(7);
		fflush(stdin);
		getline(cin, sUsername);
		if (sUsername == "ESC" || sUsername == "esc")
		{
			textcolor(10);
			cout << "\n\t\t\tCam On Quy Khach Da Su Dung Dich Vu Hen Gap Lai " << endl;
			i = i + 4;
			textcolor(7);
		}
		else
		{
			textcolor(2);
			cout << "\t\t\tNhap pass word: ";
			textcolor(7);
			sPassword = passwordInput(6);
			for(Node * p = L.pHead; p != NULL; p = p->pNext)
			{
			 if(sUsername == p->nData.sUser && p->nData.sPass == "locked")
			 {
				 textcolor(4);
				 cout << "\t\tTai khoan nay da bi khoa. Vui Long Lien He: 0923.778.128 !!!\a\n\n";
				 textcolor(7);
				 i +=4;
				 break;
			 }
			 else if(sUsername == p->nData.sUser && sPassword == p->nData.sPass)
				{
					nDem += 5;
					Node * q = p;
					i += 4;
					flag = 0;
					do {	
						system("cls");
						cc:
						textcolor(10);
						cout << "\t\t\tLogin Thanh Cong - Welcom To BIDV \n" << endl;
						textcolor(7);
						vien_thong_bao("MENU");
						textcolor(10);
						cout << "\t\t\tNhap so de thuc hien: ";
						textcolor(7);
						cin >> nChon;					
					} while(nChon < 1 || nChon > 7);
					string sLuaChon = "";
					switch(nChon)
					{		
					case 1:
						system("cls");
						//Rút tiền
						withdrawal(L, q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						fflush(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 2:
						system("cls");
						//Chuyển Tiền
						transfers(L,q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						fflush(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 3: 
						system("cls");
						//Thông tin tài khoản
						thongTinTK(L, q);					
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						fflush(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 4:
						system("cls");
						//Lich su giao dich
						outscreen_transaction_history(q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						fflush(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 5:
						system("cls");
						//Doi Mat Khau
						changePassword(L, q);
						break;
					case 6:
						system("cls");
						recharge(L, q);
						textcolor(9);
						cout << "\n\n\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de quay lai Menu. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
						fflush(stdin); getline(cin, sLuaChon);
						if(sLuaChon == "yes" || sLuaChon == "YES")
						{
							system("cls");
							goto cc;
						}
						else 
						{
							textcolor(10);
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							textcolor(7);
							break;
						}
					case 7:
						//Thoat khoi giao dich
						textcolor(10);
						cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
						textcolor(7);
						break;
					}
				}
			}
			nDem++;
			if (nDem == 3)
			{
				system("cls");
				vien_thong_bao("LOGIN");
				textcolor(4);
				cout << "\t\t\tTai khoan ban da bi khoa !!! Vui Long Lien He: 0923.778.128 !!!\a\n\n";
				textcolor(7);
				i += 3;
				for(Node * f = L.pHead; f != NULL; f = f->pNext)
				{
					if(sUsername == f->nData.sUser)
					{
						f->nData.sPass = "locked";
						output_Data(L);
						Node * e = L.pHead;
						transaction_history(L, f, "LOCKED", 0, e, 0);
						break;
					}
				}
			}
			else if (i < 3)
			{

				system("cls");
				vien_thong_bao("LOGIN");
				textcolor(4);
				cout << "\t\t\tTai khoan hoac mat khau khong dung.\a Con " << nLan-- << " lan dang nhap \n\n";
				textcolor(7);
				i++;
			}
		}
	}
}
// Rút tiền
void withdrawal(List L, Node * q)
{
	int nNhapTienRut = 0;
	int nN = 0;
	system("cls");
	do {
		vien_thong_bao("RUTTIEN");
		vien_thong_bao("MENURUTTIEN"); textcolor(10);
		cout << "\n\t\t\t\t\tNhap so can chon: ";textcolor(10);
		cin >> nN;
	} while(nN < 1 || nN > 6);
	switch(nN)
	{
		case 1:
			nNhapTienRut = 50000;
			break;
		case 2:
			nNhapTienRut = 100000;
			break;
		case 3:
			nNhapTienRut = 200000;
			break;
		case 4:
			nNhapTienRut = 500000;
			break;
		case 5:
			nNhapTienRut = 1000000;
			break;
		case 6:
			do {
				dd:
				system("cls");
				vien_thong_bao("RUTTIEN");
				textcolor(4);
				cout << "\tSo tien nhap vao phai la boi cua 10.000vnd. Gioi han giao dich tu 50.000vnd den 50.000.000vnd\n";
				textcolor(10);
				cout << "\t\t\tNhap so tien can rut: ";
				textcolor(7);
				cin >> nNhapTienRut;
			}while(nNhapTienRut < 50000 || nNhapTienRut > 50000000);
			break;
	}
	if (nNhapTienRut % 10000 == 0)
	{
		double fSoDuKhaDung = 0;
		fSoDuKhaDung = q->nData.fSoDu - 50000;
		if (nNhapTienRut > fSoDuKhaDung)
		{
			textcolor(4);
			cout << "\t\tSo du trong tai khoan khong du de thuc hien giao dich.\n";
			textcolor(7);
		}
		else
		{
			system("cls");
			vien_thong_bao("RUTTIEN");
			string sKiemTra = "";
			textcolor(10);
			cout << "\t\t\t\tXac Nhan Rut Tien\n";
			textcolor(3);
			cout << "\t\t\tRut Tien Tu STK: " << q->nData.sSTK << endl;
			cout << "\t\t\tTen Chu The: " << q->nData.sHoTen << endl;
			cout << "\t\t\tSo Tien Rut: " << nNhapTienRut << " " << q->nData.sLoaiTien << endl;
			cout << "\t\t\tPhi Giao Dich: " << nPhiGiaoDich(nNhapTienRut, "RUTTIEN") - nPhiGiaoDich(nNhapTienRut, "RUTTIEN")/11 << " " << q->nData.sLoaiTien << "   -   VAT: " << nPhiGiaoDich(nNhapTienRut, "RUTTIEN")/11 << " " << q->nData.sLoaiTien << endl;
			cout << "\t\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
			cout << "\t\t\tSo Du Con Lai: " << q->nData.fSoDu - (float)nNhapTienRut - (float)nPhiGiaoDich(nNhapTienRut, "RUTTIEN") << " " << q->nData.sLoaiTien << endl;
			cout << "\tNhap "; textcolor(10);
			cout << "Mat Khau";textcolor(3);
			cout << " De Xac Nhan Lenh Rut Tien. Nhap "; textcolor(4);
			cout << "NO";textcolor(3);
			cout << " De Huy Lenh Chuyen Tien: ";textcolor(7);
			sKiemTra = passwordInput(6);
			if (sKiemTra == q->nData.sPass)
			{
				q->nData.fSoDu = q->nData.fSoDu - nNhapTienRut - nPhiGiaoDich(nNhapTienRut, "RUTTIEN");
				textcolor(10);
				cout << "\n\t\t\tBan da rut thanh cong: " << nNhapTienRut << " " << q->nData.sLoaiTien << endl;
				cout << "\t\t\tSo du con lai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
				textcolor(7);
				//Ghi dữ liệu lên file sau khi rút tiền
				Node * g = L.pHead;				
				//In hoa don rut tien?
				string ktra = "";
				textcolor(9);
				cout << "\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de in hoa don. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
				fflush(stdin);
				getline(cin, ktra);
				if ( ktra == "YES" || ktra == "yes")
				{
					int nPGD = nPhiGiaoDich(nNhapTienRut, "RUTTIEN");
					nPGD += 550;
					inHoaDon(L, q, nNhapTienRut, nPhiGiaoDich(nNhapTienRut, "RUTTIEN"), g, "RUTTIEN");
					output_Data(L);
					transaction_history(L, q, "RUTTIEN", nNhapTienRut, g, nPGD);
				}
				else
				{
					textcolor(10);
					cout << "\t\t\t\tBan da chon khong in hoa don !";
					textcolor(7);
					output_Data(L);
					transaction_history(L, q, "RUTTIEN", nNhapTienRut, g, nPhiGiaoDich(nNhapTienRut, "RUTTIEN"));
				}
			}
			else
			{
				textcolor(4);
				cout << "\t\t\tNhap sai ! Lenh Rut Tien Da Tam Dung\a\n";
				textcolor(7);
			}

		}
	}
	else
	{
		cout <<"\a";
		goto dd;
	}
}
//Cau 3: Chuyển Tiền
void transfers(List L, Node * q)
{
	int flag = 0;
	int i = 0;
	string sNhapSTKChuyen = " ";
	system("cls");
	vien_thong_bao("CHUYENTIEN");
	cout << "\t\t\tLuu y: Nhap ";
	textcolor(4);
	cout << "ESC";
	textcolor(7);
	cout << " de thoat khoi chuong trinh\n" << endl;
	while (flag == 0)
	{
		textcolor(10);
		cout << "\t\t\tNhap so tai khoan can chuyen tien: ";textcolor(7);
		fflush(stdin);
		getline(cin, sNhapSTKChuyen);
		if (sNhapSTKChuyen == q->nData.sSTK)
		{
			textcolor(4);
			cout << "\t\t\tKhong the chuyen tien cho chinh minh !!!\n";
			textcolor(7);
		}
		else if (sNhapSTKChuyen == "ESC" || sNhapSTKChuyen == "esc")
		{
			flag = 5;
			textcolor(10);
			cout << "\t\t\tCam on quy khach da su dung dinh vu\n";
			textcolor(7);
		}
		else
		{
			for(Node * t = L.pHead; t != NULL; t = t->pNext)
			{
				if(sNhapSTKChuyen == t->nData.sSTK)
				{
					flag = 5;
					int nNhapTienChuyen = 0;
					do {
						gg:
						system("cls");
						vien_thong_bao("CHUYENTIEN");
						textcolor(4);
						cout << "\tSo tien nhap vao phai la boi cua 50.000vnd. Gioi han giao dich tu 200.000vnd den 50.000.000vnd\n";
						textcolor(10);
						cout << "\t\t\tNhap so tien can chuyen: ";
						textcolor(7);
						cin >> nNhapTienChuyen;
						system("cls");
						if (nNhapTienChuyen % 50000 != 0)
						{
							goto gg;
						}

					} while(nNhapTienChuyen < 200000 || nNhapTienChuyen > 50000000);
					double fSoDuKhaDung = 0.0;
					fSoDuKhaDung = q->nData.fSoDu - 50000;
					if (nNhapTienChuyen >= 200000)
					{
						if (nNhapTienChuyen <= fSoDuKhaDung)
						{
							system("cls");
							vien_thong_bao("CHUYENTIEN");
							textcolor(10);
							cout << "\t\t\t\tXac Nhan Chuyen Tien\n";
							textcolor(3);
							cout << "\t\t\tChuyen Tien Den STK: " << t->nData.sSTK << endl;
							cout << "\t\t\tTen Nguoi Nhan: " << t->nData.sHoTen << endl;
							cout << "\t\t\tSo Tien Chuyen: " << nNhapTienChuyen << " " << t->nData.sLoaiTien << endl;
							cout << "\t\t\tPhi Giao Dich: " << nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN") - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN")/11 << " " << q->nData.sLoaiTien << "   -   VAT: " << nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN")/11 << " " << q->nData.sLoaiTien << endl;
							cout << "\t\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << t->nData.sLoaiTien << endl;
							cout << "\t\t\tSo Du Con Lai: " << q->nData.fSoDu - (float)nNhapTienChuyen - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN") << " " << t->nData.sLoaiTien << endl;
							string sLC = " ";
							cout << "\tNhap "; textcolor(10);
							cout << "Mat Khau";textcolor(3);
							cout << " De Xac Nhan Lenh Chuyen Tien. Nhap "; textcolor(4);
							cout << "NO";textcolor(3);
							cout << " De Huy Lenh Chuyen Tien: ";textcolor(7);
							sLC = passwordInput(6);
							if(sLC == q->nData.sPass)
							{
								q->nData.fSoDu = q->nData.fSoDu - (float)nNhapTienChuyen - nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN");
								t->nData.fSoDu = t->nData.fSoDu + nNhapTienChuyen;
								textcolor(10);
								cout << "\t\t\tChuyen Tien Thanh Cong !!!\n";
								cout << "\t\t\tSo Du Con Lai: "; 
								cout << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;textcolor(7);
								/*output_Data(L);
								transaction_history(L, q, "CHUYENTIEN", nNhapTienChuyen, t);*/
								
								//In hoa don:
								string ktra = "";
								textcolor(9);
								cout << "\t\tNhap \"";textcolor(10); cout << "YES"; textcolor(9); cout << "\" de in hoa don. Nhap \""; textcolor(4); cout << "NO"; textcolor(9); cout << "\" de thoat: "; textcolor(7);
								fflush(stdin);
								getline(cin, ktra);
								if ( ktra == "YES" || ktra == "yes")
								{
									int nPGD = nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN");
									nPGD = nPGD + 550;
									inHoaDon(L, q, nNhapTienChuyen, nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN"), t, "CHUYENTIEN");
									output_Data(L);
									transaction_history(L, q, "CHUYENTIEN", nNhapTienChuyen, t, nPGD);
									transaction_history(L, t, "NHANTIEN", nNhapTienChuyen, q, 0);
								}
								else
								{
									textcolor(10);
									cout << "\t\t\t\tBan da chon khong in hoa don !";
									textcolor(7);
									output_Data(L);
									transaction_history(L, q, "CHUYENTIEN", nNhapTienChuyen, t, nPhiGiaoDich(nNhapTienChuyen, "CHUYENTIEN"));
									transaction_history(L, t, "NHANTIEN", nNhapTienChuyen, q, 0);
								}
							}
							else
							{
								textcolor(4);
								cout << "\t\t\tNhap sai ! Lenh Chuyen Tien Da Tam Dung\a\n";
								textcolor(7);
							}
							break;
						}
						else if (nNhapTienChuyen > fSoDuKhaDung)
						{
							system("cls");
							vien_thong_bao("CHUYENTIEN");
							textcolor(4);
							cout << "\n\t\tSo du trong tai khoan khong du de thuc hien giao dich. Giao dich ket thuc !!!\n";
							textcolor(7);
							break;
						}
					}
				}
				else 
				{
					flag = 0;
				}
			}
			if(flag == 0)
			{
				system("cls");
				vien_thong_bao("CHUYENTIEN");
				cout << "\t\t\tLuu y: Nhap ";
				textcolor(4);
				cout << "ESE";
				textcolor(7);
				cout << " de thoat khoi chuong trinh\n" << endl;
				textcolor(4);
				cout << "\t\t\tSo tai khoan khong chinh xac. Vui long nhap lai!\n";
				textcolor(7);	
			}
		}
	}
}
//Đổi mật khẩu:
void changePassword(List L, Node * q)
{
	int nDem = 0;
	system("cls");
	vien_thong_bao("DOIMK");
	string sPassHienTai = "";
	dd:
	textcolor(10);
	cout << "\t\t\tNhap Mat Khau Hien Tai: ";
	textcolor(7);
	sPassHienTai = passwordInput(6);
	nDem++;
	if(sPassHienTai == q->nData.sPass)
	{
		string sPassMoi = "";
		string sNhapLai = "";
		textcolor(4);
		cout << "\t\t\tLuu y: mat khau gom 6 chu so\n";
		textcolor(7);
		textcolor(10);
		cout << "\t\t\tNhap mat khau moi: ";
		textcolor(7);
		sPassMoi = passwordInput(6);
		textcolor(10);
		cout << "\t\t\tNhap lai mat khau moi: ";
		textcolor(7);
		sNhapLai = passwordInput(6);
		if(sPassMoi == sNhapLai)
		{
			if(sPassMoi.length() == 6)
			{
				q->nData.sPass = sPassMoi;
				output_Data(L);
				textcolor(10);
				cout << "\t\t\tBan da thay doi mat khau thanh cong !!!\n";
				cout << "\t\t\tVui long dang nhap lai !!!\n";
				textcolor(7);
			}
			else 
			{
				system("cls");
				vien_thong_bao("DOIMK");
				textcolor(4);
				cout << "\t\t\tLuu y: mat khau moi bao gom 6 chu so. Vui long nhap lai\n";
				textcolor(7);
				goto dd;
			}
		}
		else if(sPassMoi == "ESC" || sPassMoi == "esc" || sNhapLai == "ESC" || sNhapLai == "esc")
		{
			textcolor(10);
			cout << "\t\tBan da chon thoat khoi chuong trinh\n";
			textcolor(7);
		}
		else
		{
			system("cls");
			vien_thong_bao("DOIMK");
			textcolor(4);
			cout << "\t\tMat khau khong trung khop vui long nhap lai: \n";
			textcolor(7);
			goto dd;
		}
	}
	else if (sPassHienTai == "esc" || sPassHienTai == "ESC")
	{
		textcolor(10);
		cout << "Ban da chon thoat khoi chuong trinh\n";
		textcolor(7);
	}
	else if(nDem == 3)
	{
		system("cls");
		vien_thong_bao("DOIMK");
		textcolor(4);
		cout << "\t\tBan nhap sai qua 3 lan, tai khoan nay da bi khoa !!! Vui Long Lien He: 0923.778.128 !!!\a\n\n";
		textcolor(7);
		q->nData.sPass = "locked";
		output_Data(L);
		Node * e = L.pHead;
		transaction_history(L, q, "LOCKED", 0, e, 0);
	}
	else
	{
		system("cls");
		vien_thong_bao("DOIMK");
		textcolor(4);
		cout << "\t\tMat khau nhap vao sai, Vui long nhap lai.\n";
		cout << "\t\tNhap ESC de thoat khoi chuong trinh !\n";
		textcolor(7);
		goto dd;
	}
}
//Ghi lại dữ liệu lên file
void output_Data(List &L)
{
	int nSoLuongKhachHang = nDemSoLuongKhachHang();
	ofstream File;
	File.open("input.txt");
	int nDem = 0;
	for (Node * k = L.pHead; k != NULL; k = k->pNext)
	{
		nDem++;
		File << k->nData.sUser << "," << k->nData.sPass << "," << k->nData.sSTK << "," << k->nData.sHoTen << "," << k->nData.fSoDu << "," << k->nData.sLoaiTien << "," << k->nData.sChiNhanh;
		if(nDem < nSoLuongKhachHang) //
		{
			
			File << endl;
		}
	}
	File.close();
}
//Đọc từ file input 1 khách hàng
void input_1_Data(ifstream &Filein, KhachHang &kh) //Đọc từ file input 1 khách hàng
{
	/*username, password,STK, Họ Tên, Số Dư, loại tiền, chi nhánh  */	
	getline(Filein, kh.sUser, ',');
	getline(Filein, kh.sPass, ',');
	getline(Filein, kh.sSTK, ',');
	getline(Filein, kh.sHoTen, ',');
	Filein >> kh.fSoDu;
	Filein.ignore(1,',');
	getline(Filein, kh.sLoaiTien, ',');
	getline(Filein, kh.sChiNhanh);
	Filein.ignore(0,'\n');
}
//Đọc từ file input toàn bộ khách hàng
void input_All_Data(ifstream &Filein, List &L) 
{
	while(!Filein.eof() == true) // Nếu hàm Filein.eof() trả về true thì con trỏ chỉ thị con trỏ đang ở cuối file và ngược lại
	{
		//Bước 1: Đọc thông tin từng Khách hàng
		KhachHang KH;
		input_1_Data(Filein, KH); //bắt đầu đọc từ filein và thông tin KH;
		//Bước 2: Khởi tạo 1 cái Node KH;
		Node * p = getNode(KH); //Tạo 1 cái Node để đưa dữ liệu vào LinkedList
		//Bước 3: Thêm 'Khách Hàng = Node p' Vào Danh Sách LK Đơn
		inputTail(L, p); // Thêm vào cuối danh sách
	}
}
//Xuất kiểm tra- toàn bộ khách hàng có trong danh sách
void xuat(KhachHang kh)
{
	cout << "\nUser: " << kh.sUser;
	cout << "\nPass: " << kh.sPass;
	cout << "\nSTK: " << kh.sSTK;
	cout << "\nTen: " << kh.sHoTen;
	cout << "\nTien: " << kh.fSoDu << " " << kh.sLoaiTien;
	cout << "\nChi Nhanh: " << kh.sChiNhanh << endl;
}
void outputToScreen(List L)
{
	int dem = 1;
	for (Node * k = L.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\t\t\tKhach Hang Thu " << dem++;
		xuat(k->nData);
	}
}
//Tạo List mới
void initial(List &L)
{
	L.pHead = L.pTail = NULL;
}
//Thêm vào cuối DS
void inputTail(List &L, Node *p) 
{
	if (L.pHead == NULL) //Danh sách rỗng
	{
		L.pHead = L.pTail = p;
		return;
	}
	else
	{
		L.pTail->pNext = p; //Cho con trỏ của pTail trỏ đến Node p
		L.pTail = p; //Cập nhật lại pTail chính là Node p

	}

	
}
void output(List L)
{
	if(L.pHead == NULL)
	{
		cout << "\n\t\t\tDanh Sach Rong !!!\n";
		return;
	}
	else
	{
		cout << "\n\t\t\tXuat Du Lieu List\n";
		Node *p = L.pHead;
		while(p != NULL)
		{
			
			p = p->pNext;
		}
	}
}
//Viền thông báo
void vien_thong_bao(string sVien)
{
	if (sVien == "LOGIN")
	{
		textcolor(6);
		cout << "\t\t\t\t************************" << endl;
		cout << "\t\t\t\t*  ";
		textcolor(10);
		cout << "DANG NHAP HE THONG"; textcolor(6);  
		cout <<"  *" << endl;
		cout << "\t\t\t\t************************" << endl;
		textcolor(7);
	}
	else
	{
		if (sVien == "MENU")
		{
			textcolor(6);
			cout << "\t\t*************************************************************************" << endl;
			cout << "\t\t*  ";
			textcolor(10);
			cout << "\t\t    CHON PHUONG AN DE THUC HIEN"; textcolor(6);  
			cout <<"\t\t\t\t*" << endl;
			textcolor(6);
			cout << "\t\t*  ";
			textcolor(10);
			cout << "   1. Rut Tien\t\t\t2. Chuyen Tien"; textcolor(6);
			cout <<"   \t\t*" << endl;
			textcolor(6);
			cout << "\t\t*  ";
			textcolor(10);
			cout << "   3. Thong Tin Tai Khoan\t\t4. Lich su giao dich"; textcolor(6);
			cout <<"   \t\t*" << endl;
			textcolor(6);
			cout << "\t\t*  ";
			textcolor(10);
			cout << "   5. Doi Mat Khau \t\t\t6. Nap Tien            \t"; textcolor(6);
			cout <<"   \t*" << endl;
			cout << "\t\t*  ";
			textcolor(10);
			cout << "   7. Thoat giao dich\t\t\t\t"; textcolor(6);
			cout <<"   \t\t*" << endl;
			cout << "\t\t*************************************************************************" << endl;
			textcolor(7);	
		}
		else if (sVien == "RUTTIEN")
		{
			textcolor(6);
			cout << "\t\t\t\t*************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(10);
			cout << "\tRUT TIEN\t"; textcolor(6);  
			cout <<"*" << endl;
			cout << "\t\t\t\t*************************" << endl;
			textcolor(7);
		}
		else if (sVien == "DOIMK")
		{
			textcolor(6);
			cout << "\t\t\t\t*************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(10);
			cout << "\tDOI MAT KHAU\t"; textcolor(6);  
			cout <<"*" << endl;
			cout << "\t\t\t\t*************************" << endl;
			textcolor(7);
		}
		else if (sVien == "CHUYENTIEN") {
			textcolor(6);
			cout << "\t\t\t\t*************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(10);
			cout << "\tCHUYEN TIEN\t"; textcolor(6);  
			cout <<"*" << endl;
			cout << "\t\t\t\t*************************" << endl;
			textcolor(7);
		}
		else if (sVien == "MENURUTTIEN")
		{ //"; cout << "
			textcolor(10);
			cout << "\t\t\t\t\tVUI LONG CHON SO TIEN CAN RUT\n";
			textcolor(9);
			cout << "\t\t|\\----------------------------\\ \t\t /----------------------------/|" << endl;
			cout << "\t\t|";textcolor(4); cout << "1";textcolor(9); cout << "\\       50.000 VND           \\ \t\t/          100.000 VND       /";textcolor(4); cout << "2";textcolor(9); cout << "|" << endl;textcolor(10);
			cout << "\t\t| /                            / \t\t\\\                            \\ |" << endl;
			cout << "\t\t|/----------------------------/ \t\t \\----------------------------\\|" << endl;
			cout << endl;textcolor(9);
			cout << "\t\t|\\----------------------------\\ \t\t /----------------------------/|" << endl;
			cout << "\t\t|";textcolor(4); cout << "3";textcolor(9); cout << "\\      200.000 VND           \\ \t\t/          500.000 VND       /";textcolor(4); cout << "4";textcolor(9); cout << "|" << endl;textcolor(10);
			cout << "\t\t| /                            / \t\t\\\                            \\ |" << endl;
			cout << "\t\t|/----------------------------/ \t\t \\----------------------------\\|" << endl;
			cout << endl;textcolor(9);
			cout << "\t\t|\\----------------------------\\ \t\t /----------------------------/|" << endl;
			cout << "\t\t|"; textcolor(4);cout << "5";textcolor(9); cout << "\\     1.000.000 VND          \\ \t\t/         Nhap So Khac       /";textcolor(4); cout << "6"; textcolor(9);cout << "|" << endl;textcolor(10);
			cout << "\t\t| /                            / \t\t\\\                            \\ |" << endl;
			cout << "\t\t|/----------------------------/ \t\t \\----------------------------\\|" << endl; textcolor(7);
		}
		else if (sVien == "NAPTIEN")
		{
			textcolor(6);
			cout << "\t\t\t\t*************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(10);
			cout << "\tNAP TIEN\t"; textcolor(6);  
			cout <<"*" << endl;
			cout << "\t\t\t\t*************************" << endl;
			textcolor(7);
		}
	}
}
//Đổi pass nhập vào thành d
string passwordInput(unsigned maxLength)
{
	string pw = "";
	for (char c; (c = getch()); )
	{
		if (c == '\n' || c == '\r') { // \n là phím phím enter + \r là Nhảy về đầu hàng, không xuống hàng
			cout << "\n";
			break;
		} else if (c == '\b') { //phím backspace
			cout << "\b \b";
			if (!pw.empty()) pw.erase(pw.size()-1);
		} else if (c == -32) { //phím mũi tên
			_getch(); //bỏ qua kí tự tiếp theo (hướng mũi tên)
		} else if (isprint(c) && pw.size() < maxLength) { //isprint tức là chỉ nhận những ký tự in ra được (có tính khoảng trắng)
			cout << '*';
			pw += c;
		}
	}
	return pw;
}
//Thông tin tài khoản
void thongTinTK(List L, Node * q) 
{
	textcolor(6);
			cout << "\t\t\t\t*************************" << endl;
			cout << "\t\t\t\t*  ";
			textcolor(10);
			cout << "THONG TIN KHACH HANG "; textcolor(6);  
			cout <<"*" << endl;
			cout << "\t\t\t\t*************************" << endl;
	textcolor(7);
	textcolor(3);
	cout << "\n";
	cout << "\t\t\tHo va Ten: " << q->nData.sHoTen << endl;
	cout << "\t\t\tSo Tai Khoan: " << q->nData.sSTK << endl;
	cout << "\t\t\tSo Du Hien Tai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << endl;
	cout << "\t\t\tChi Nhanh: " << q->nData.sChiNhanh << endl;
	textcolor(7);
}
//Ghi lại lịch sử giao dịch
void transaction_history(List L, Node * q, string type_perform, int nTienTru, Node * g, int PhiGD)
{
	time_t now = time('\0');
	tm *t = localtime(&now);
	ofstream File;
	File.open("\LichSuGiaoDich\\" + q->nData.sSTK + ".txt", ios::app);
	if(type_perform == "CHUYENTIEN")
	{	
		File << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << "   " << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << " " << nTienTru << q->nData.sLoaiTien << kiemTraTime("100", q) << "  " << q->nData.fSoDu << q->nData.sLoaiTien << "   " << PhiGD << "     " << "send" << "    " << g->nData.sSTK << "  " << g->nData.sHoTen << "   " << maGiaodich();
	}
	else if (type_perform == "RUTTIEN")
	{
		File << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << "   " << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << " " << nTienTru << q->nData.sLoaiTien << kiemTraTime("100", q) << "  " << q->nData.fSoDu << q->nData.sLoaiTien << "   " << PhiGD <<"      " << "with" << "    " << "Not Applicable" << "  " << "N/A" << "              " << maGiaodich();
	}
	else if (type_perform == "NHANTIEN")
	{
		File << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << "   " << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << " " << nTienTru << g->nData.sLoaiTien << kiemTraTime("100", q) << "  " << q->nData.fSoDu << q->nData.sLoaiTien << "   " << "0" << "         " << "plus" << "    " << g->nData.sSTK << "  " << g->nData.sHoTen << "   " << maGiaodich();
	}
	else if (type_perform == "LOCKED")
	{
		File << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << "   " << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << " " << "0" << q->nData.sLoaiTien << "       " << q->nData.fSoDu << q->nData.sLoaiTien << "   " << 0 <<   "         " << "lock" << "    " << "Not Applicable" << "  " << "N/A" << "              " << maGiaodich();
	}
	else if (type_perform == "NAPTIEN")
	{
		File << "\n" << kiemTraTime("hh", q) << t->tm_hour << ":" << kiemTraTime("m", q) << t->tm_min << ":" << kiemTraTime("ss", q) << t->tm_sec << "   " << kiemTraTime("dd", q) << t->tm_mday << "/" << kiemTraTime("mm", q) << 1+t->tm_mon << "/" << 1900+t->tm_year  << " " << nTienTru << q->nData.sLoaiTien << "  " << q->nData.fSoDu << q->nData.sLoaiTien << "   " << 0 <<   "         " << "add" << "     " << "Not Applicable" << "  " << "N/A" << "              " << maGiaodich();
	}
	File.close();
	
}
//Xuất lịch sử giao dịch ra màn hình
void outscreen_transaction_history(Node * q)
{
	string a = "";
	ifstream File; //Mở File Input đưa dữ liệu vào
	File.open("\LichSuGiaoDich\\" + q->nData.sSTK + ".txt");
	cout << "		          =================>>>LICH SU GIAO DICH<<<=================\n\n";

cout << "hh/mm/ss    Dd/mm/yy  Convert    Wallet     Tran-Fee   Type    Account number  F-L name      Trading code\n";
	while(!File.eof())
	{
		getline(File, a, '\n');
		cout << a << endl;
		Sleep(30);
	}
	File.close();
	cout << "\t\t___________________________________________________________________________\n";
}
//In hóa đơn
void inHoaDon(List L, Node * q, int nTienRut, int PhiGD, Node * g, string sForm)
{
	time_t now = time('\0');
	tm *t = localtime(&now);
	if (sForm == "RUTTIEN")
	{
		textcolor(9);
		cout << "\t\t\t\t/-----------------------------------------------------\\\n";
		cout << "\t\t\t\t| BIDV - Ngan Hang TMCP Dau Tu Va Phat Trien Viet Nam |\n";
		cout << "\t\t\t\t|-----------------------------------------------------|\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|\t\t    RUT TIEN MAT\t\t      |\n";
		cout << "\t\t\t\t|Ngay\t\t\tGio\t\t       May ATM|\n";
		cout << "\t\t\t\t|"<< t->tm_mday << "/" << 1+t->tm_mon << "/" << 1900+t->tm_year << "\t\t" << t->tm_hour << ":" << t->tm_min << "\t\t\t" << sMaATM << "|\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|So tai khoan:  "<< q->nData.sSTK  <<"\t\t\t      |\n";
		cout << "\t\t\t\t|So tien rut:   "<< nTienRut << " " << q->nData.sLoaiTien << "\t\t\t      |\n";
		q->nData.fSoDu = q->nData.fSoDu - 550;
		cout << "\t\t\t\t|So du tai khoan: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << "\t\t\t      |\n";
		cout << "\t\t\t\t|So giao dich: " << maGiaodich() << "\t\t\t\t      |\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|Phi: " << PhiGD - (PhiGD/11) <<" VND\t\t\tVAT: " << PhiGD/11 << " VND\t      |\n";
		cout << "\t\t\t\t|Phi in hoa don: 500 VND\t\t\t      |\n";
		cout << "\t\t\t\t|VAT in hoa don: 50 VND \t\t\t      |\n";
		cout << "\t\t\t\t|-----------------------------------------------------|\n";
		cout << "\t\t\t\t| \tDien thoai ho tro 24/24: 0923.778.128 \t      |\n";
		cout << "\t\t\t\t\\-----------------------------------------------------/\n";
		textcolor(7);
	}
	else if (sForm == "CHUYENTIEN")
	{
		textcolor(9);
		cout << "\t\t\t\t/-----------------------------------------------------\\\n";
		cout << "\t\t\t\t| BIDV - Ngan Hang TMCP Dau Tu Va Phat Trien Viet Nam |\n";
		cout << "\t\t\t\t|-----------------------------------------------------|\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|\t\t  CHUYEN TIEN TRONG NUOC\t      |\n";
		cout << "\t\t\t\t|Ngay\t\t\tGio\t\t       May ATM|\n";
		cout << "\t\t\t\t|"<< t->tm_mday << "/" << 1+t->tm_mon << "/" << 1900+t->tm_year << "\t\t" << t->tm_hour << ":" << t->tm_min << "\t\t\t" << sMaATM << "|\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|So tai khoan:  "<< q->nData.sSTK  <<"\t\t\t      |\n";
		cout << "\t\t\t\t|So tien chuyen:   "<< nTienRut << " " << q->nData.sLoaiTien << "\t\t\t      |\n";
		q->nData.fSoDu = q->nData.fSoDu - 550;
		cout << "\t\t\t\t|So du tai khoan: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << "\t\t\t      |\n";
		cout << "\t\t\t\t|So giao dich: " << maGiaodich() << "\t\t\t\t      |\n";
		cout << "\t\t\t\t|Chuyen den so tai khoan: " << g->nData.sSTK << "\t      |\n";
		cout << "\t\t\t\t|\t\t\t\t\t\t      |\n";
		cout << "\t\t\t\t|Phi: " << PhiGD - (PhiGD/11) <<" VND\t\t\tVAT: " << PhiGD/11 << " VND\t      |\n";
		cout << "\t\t\t\t|Phi in hoa don: 500 VND\t\t\t      |\n";
		cout << "\t\t\t\t|VAT in hoa don: 50 VND \t\t\t      |\n";
		cout << "\t\t\t\t|-----------------------------------------------------|\n";
		cout << "\t\t\t\t| \tDien thoai ho tro 24/24: 0923.778.128 \t      |\n";
		cout << "\t\t\t\t\\-----------------------------------------------------/\n";
		textcolor(7);
	}
		
	
}
//ma giao dich
int maGiaodich()
{
	int nMaGiaoDich = 0;
	ifstream File1;
	File1.open("\IDgiaodich\\IDgiaodich.txt");
	File1 >> nMaGiaoDich;
	File1.close();
	ofstream File2;
	File2.open("\IDgiaodich\\IDgiaodich.txt");
	nMaGiaoDich = nMaGiaoDich + 1;
	File2 << nMaGiaoDich;
	File2.close();
	return nMaGiaoDich;
}
//Phí giao dịch
int nPhiGiaoDich(int nTienNhap, string sForm)
{
	if (sForm == "RUTTIEN")
	{
		if (nTienNhap <= 500000)
		{
			return 1100;
		}
		else if (nTienNhap <= 1000000)
		{
			return 3300;
		}
		else if (nTienNhap <= 10000000)
		{
			return 11000;
		}
		return 22000;
	}
	else if (sForm == "CHUYENTIEN")
	{
		if (nTienNhap <= 1000000)
		{
			return 11000;
		}
		else if (nTienNhap <= 5000000)
		{
			return 22000;
		}
		else if (nTienNhap <= 10000000)
		{
			return 33000;
		}
		return 44000;
	}
	return 0;
}
//Kiểm tra thời gian
string kiemTraTime(string sX, Node * q)
{
	// làm dữ liệu lịch sử giao dịch \\thẳng hàng\\, thật đẹp để xuất ra màn hình
	time_t now = time('\0');
	tm *t = localtime(&now);
	if (sX == "ss")
	{
		if(t->tm_sec < 10)
		{
			return "0";
		}
	}
	if (sX == "m")
	{
		if((t->tm_min) < 10)
		{
			return "0";
		}
	}
	if(sX == "hh")
	{
		if(t->tm_hour < 10)
		{
			return "0";
		}
	}
	if (sX == "dd")
	{
		if (t->tm_mday < 10)
		{
			return "0";
		}
	}
	if (sX == "mm")
	{
		if (t->tm_mon + 1 < 10)
		{
			return "0";
		}
	}
	if (sX == "100")
	{
		if (q->nData.fSoDu < 100000)
		{
			return " ";
		}
	}
	return "";
}
//Nạp tiền vào tài khoản
void recharge(List L, Node * q)
{	
dd:
	system("cls");
	vien_thong_bao("NAPTIEN");
	int nNhapTienNap = 0;
	textcolor(4);
	cout << "\t\t\tLuu y so tien nap phai lon hon 100.000 VND va la boi cua 50.000 VND\n";
	textcolor(10);
	cout << "\t\t\tNhap so tien nap: ";
	textcolor(7);
	cin >> nNhapTienNap;
	if (nNhapTienNap < 100000 || nNhapTienNap % 50000 != 0)
	{
		goto dd;
	}
	q->nData.fSoDu += nNhapTienNap;
	textcolor(10);
	cout << "\t\t\tBan da nap thanh cong " << nNhapTienNap << " " << q->nData.sLoaiTien << " vao tai khoan.\n";
	cout << "\t\t\tSo du hien tai: " << q->nData.fSoDu << " " << q->nData.sLoaiTien << "\n";
	textcolor(7);
	output_Data(L);
	Node * g = new Node;
	transaction_history(L, q, "NAPTIEN", nNhapTienNap, g, 0);
}
void textcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
 
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
int nDemSoLuongKhachHang()
{

	int nDem = 0;
	string s = "";
	ifstream File;
	File.open("input.txt");
	while(!File.eof())
	{
		
		nDem++;
		getline(File, s, '\n');
	}
	File.close();
	return nDem;
}