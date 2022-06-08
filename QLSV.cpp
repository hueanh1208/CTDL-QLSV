#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <mylib.h>
#include <string>
#include <iostream>
#include <fstream>

#define MAXLOPTINCHI 100000
#define MAX 100

using namespace std;

//=============================== DS MON HOC CAY NHI PHAN TIM KIEM =====================

struct MonHoc{
	char MAMH[10];
	char TENMH[35];
	int STCLT;
	int STCTH; 
};

struct nodeMH{
	MonHoc mh;
	nodeMH *left;
	nodeMH *right;
};

typedef nodeMH *PTRMH;

//Danh sach mon hoc mang dong
struct DanhSachMonHoc{
		int soluong = 0;
		MonHoc* node;
};

//=============================== SINH VIEN DS LIEN KET DON ============================

struct SinhVien{
	char MASV[15];
	char HO[30];
	char TEN[10];
	char SDT[12];
	char PHAI[4];
	char MALOP[15];
};

struct nodeSV {
	SinhVien sv;
	nodeSV* next;
};

typedef nodeSV* PTRSV;

struct DanhSachSV{
	int soluong;
	SinhVien* node =new SinhVien[MAX];
};

//============================ DANH SACH DANG KY DS LIEN KET DON =======================

struct DangKy {
	char MASV[15];
	float DIEM;
	boolean HUYDANGKY = false;	
};

struct nodeDangKy {
	DangKy dangky;
	nodeDangKy* next;
};

typedef nodeDangKy* PTRDK;

//=========================LOP TIN CHI DS TUYEN TINH MANG CON TRO==========================

struct LopTinChi{
	int MALOPTC;
	char MAMH[10];
	char NIENKHOA[10];
	int HOCKY;
	int NHOM;
	int SOSVMIN;
	int SOSVMAX;
	
	boolean HUYLOP = false;
	PTRDK FirstDK = NULL;
};

struct LIST_LTC {
	int soluong = 0;
	LopTinChi *nodesltc[MAXLOPTINCHI];
};

//=========================== END KHAI BAO ========================

void MH_Clear_List (PTRMH &root){
	MH_Clear_List(root->left);
	MH_Clear_List(root->right);
	delete root;
}

int XacNhan (char *S){
	cout<<S;
	char kt;
	do{
		kt=toupper(getch());
	}while(kt!='Y'&&kt!='N');
	cout<<kt;
	return kt=='Y';
}
int DK_Reccount(PTRDK &FirstDK);
void DK_Insert_last(PTRDK &FirstDK, DangKy dk);
void DK_clearlist(PTRDK &FirstDK);
//=============================== MON HOC ========================

// tim kiem MH theo ma so khong de qui
PTRMH MH_SearchMS (PTRMH &root,char *x){
	PTRMH p;
	p=root;
	while(p!=NULL&&stricmp(p->mh.MAMH,x)!=0){
		if(stricmp(p->mh.MAMH,x)>0)
			p=p->left;
		else p=p->right;
	}
	return p;	
}

// dem tong so nut cua cay mon hoc
void MH_DemSoNut(PTRMH &root, int &sl){
   	if (root != NULL) {
		sl++;
      	MH_DemSoNut(root->left,sl);
      	MH_DemSoNut(root->right,sl);
   	}
}

//them node mon hoc vao cay nhi phan tim kiem
void MH_Insert(PTRMH &p, MonHoc mh){ 
   	if(p == NULL){   // nut p hien tai se la nut la
    	p = new nodeMH;
    	p->mh = mh;
    	p->left = NULL;     
		p->right = NULL;  
   	}
   	else
    	if(stricmp(mh.MAMH,p->mh.MAMH)<0)
    		MH_Insert(p->left, mh);
    	else if(stricmp(mh.MAMH,p->mh.MAMH)>0)
			MH_Insert(p->right, mh);
}

// Tao cay mon hoc 
void MH_Create(PTRMH &root){
	MonHoc mh;
	PTRMH temp;
	cout<<"\n NHAP 0 DE DUNG LAI";
  	while(1){
  		cout<<"\nNhap ma mon hoc: "; fflush(stdin);
  		gets(mh.MAMH);
	  	if(strcmp(mh.MAMH,"0")==0) break;
	  	temp=MH_SearchMS(root,mh.MAMH);
	  	if(temp!=NULL) {
	  		cout<<"Ma bi trung\n";
	  		continue;
		}
	  	cout<<"Nhap ten mon hoc: "; fflush(stdin);
	  	gets(mh.TENMH);
	MH_LT:
	  	cout<<"Nhap so tin chi ly thuyet: ";
	    cin >> mh.STCLT;
	    if(mh.STCLT<=0){
	    	cout<<"\nSo tin chi ly thuyet phai lon hon 0";
	    	goto MH_LT;
		}
	MH_TH:
	    cout<<"Nhap so tin chi thuc hanh: ";
	    cin >> mh.STCTH;  
	    if(mh.STCTH<=0){
	    	cout<<"\nSo tin chi thuc hanh phai lon hon 0";
	    	goto MH_TH;
		}
	    MH_Insert(root,mh);
    }
}

//Show NLR
void MH_Show(PTRMH root){ 
   if (root != NULL){
      printf("\n      %-5s    %-25s %-8d %-8d"   , root->mh.MAMH, root->mh.TENMH,root->mh.STCLT,root->mh.STCTH);
      MH_Show(root->left);
      MH_Show(root->right);
   }
}

PTRMH rp;
//remove truong hop 3
void  MH_remove_case_3(PTRMH  &r){
  	if (r->left != NULL)
    	MH_remove_case_3 (r->left);
    //den day r la nut cuc trai cua cay con ben phai co nut goc la rp
    else {
   		//Chep noi dung cua r sang rp
   		rp->mh = r->mh;	//  de lat nua free(rp)
   		rp = r;           	
   		r = rp->right;
	}
}

void  MH_remove (char *x ,  PTRMH &p ){
	if(p == NULL)  printf ("Khong tim thay");
	else
	  	if(stricmp(x,p->mh.MAMH)<0)   MH_remove (x, p->left);
	  	else if(stricmp(x,p->mh.MAMH)>0)
			MH_remove (x, p->right);
	    else{  	// p->key = x
			rp = p;
            if (rp->right == NULL)  p = rp->left;   
			// p là nút lá hoac la nut chi co cay con ben trai
		 	else if (rp->left == NULL) p = rp->right;  // p là nut co cay con ben phai
			else MH_remove_case_3(rp->right);
		delete rp;
	    }
}

//Xoa theo ma
void MH_Delete(PTRMH &root){
	printf("\n           DANH SACH MON HOC: ");
	printf("\n     MA MON       TEN MON              STCLT    STCTH");
	MH_Show(root);
	char mamh[10];
	cout<<"\nNhap ma mon hoc muon xoa: "; fflush(stdin);
	gets(mamh);
	MH_remove(mamh, root);
}

//Sua theo ma
void MH_Sua(PTRMH &root){
	PTRMH p;
	printf("\n           DANH SACH MON HOC: ");
	printf("\n     MA MON       TEN MON              STCLT    STCTH");	
	MH_Show(root);
	char mamh[10], tenmon[35];
	char stc[5];
	do{
		cout<<"\nNhap ma mon hoc muon sua: "; fflush(stdin);
		gets(mamh);
	
		p=MH_SearchMS(root,mamh);
		if(p==NULL){
			cout<<"\nMa mon hoc khong ton tai.";
			continue;
		}
		else break;
	}while(1);	
	
	cout<<"\tNHAN ENTER DE KHONG SUA";
	
	cout<<"\nNhap ten mon hoc: "; fflush(stdin);
	gets(tenmon);
	if(stricmp(tenmon,"")!=0) strcpy(p->mh.TENMH,tenmon);
MH_Sua_LT:
	cout<<"\nNhap so tin chi ly thuyen: ";
	gets(stc);
	if(stricmp(stc,"")!=0){
		p->mh.STCLT = atoi(stc);
		if(p->mh.STCLT<=0){
			cout<<"\nSo tin chi ly thuyet phai lon hon 0";
			goto MH_Sua_LT;
		}		
	}
MH_Sua_TH:
	cout<<"\nNhap so tin chi thuc hanh: "; fflush(stdin);
	gets(stc);
	if(stricmp(stc,"")!=0){
		p->mh.STCTH = atoi(stc);
		if(p->mh.STCTH<=0){
			cout<<"\nSo tin chi thuc hanh phai lon hon 0";
			goto MH_Sua_TH;
		}
	}	
	
}

void MH_Insert_dstt(DanhSachMonHoc &listMH, MonHoc mh){
	listMH.node[listMH.soluong]=mh;
	listMH.soluong +=1;
}

void MH_ThemMHVaoDSTT(PTRMH &root, DanhSachMonHoc &listMH){
   if (root != NULL) {
      MH_Insert_dstt(listMH,root->mh);
      MH_ThemMHVaoDSTT(root->left,listMH);
      MH_ThemMHVaoDSTT(root->right,listMH);
   }
}

void MH_Selection_Sort(DanhSachMonHoc &listMH){
   	int vitrimin;
  	int i,j;
  	MonHoc min;
  	for (i=0; i< listMH.soluong-1; i++){
    	min = listMH.node[i];
		vitrimin=i;
    	for (j=i+1; j<listMH.soluong; j++)
      		if (stricmp(listMH.node[j].TENMH,min.TENMH)<0){
	  			min = listMH.node[j];
				vitrimin=j;
      		}
    // Doi cho 2 phan tu A[i] va A[vitrimin]
    	min = listMH.node[vitrimin] ;
		listMH.node[vitrimin] = listMH.node[i];
		listMH.node[i] = min;
  	}
}

void MH_ShowDSTT(DanhSachMonHoc &listMH){
	int i;
	if(listMH.soluong == 0){
		printf("\n     Danh sach khong co phan tu");
		return;
	}
	printf("\n           DANH SACH MON HOC: ");
	printf("\n     MA MON       TEN MON              STCLT    STCTH");
	for(i = 0 ; i < listMH.soluong ; i++)	
		printf("\n      %-5s    %-25s %-8d %-8d"   , listMH.node[i].MAMH, listMH.node[i].TENMH,listMH.node[i].STCLT,listMH.node[i].STCTH);	
	getch();
	delete [] listMH.node;
}

void MH_SapXep(PTRMH &root){ 
	DanhSachMonHoc listMH;
	int slmh;
	MH_DemSoNut(root,slmh);
	listMH.node = new MonHoc[slmh];
	MH_ThemMHVaoDSTT(root,listMH);
	MH_Selection_Sort(listMH);
	MH_ShowDSTT(listMH);
}

//duyet cay ghi vao file NLR
void MH_traverseWriteToFile(PTRMH &root,ofstream &fileout){
	MonHoc mh;
	if(root != NULL){
		fileout<<root->mh.MAMH<<endl;
		fileout<<root->mh.TENMH<<endl;
		fileout<<root->mh.STCLT<<endl;
		fileout<<root->mh.STCTH<<endl;
		MH_traverseWriteToFile(root->left, fileout);
		MH_traverseWriteToFile(root->right, fileout);
	}
}

// ghi file mon hoc
void MH_ghiFileMonHoc(PTRMH &root){
	ofstream fileout;
	fileout.open("MonHoc.txt");
	int slmh =0;
	MH_DemSoNut(root,slmh);
	fileout<<slmh<<endl;
	MH_traverseWriteToFile(root,fileout);
	fileout.close();
}

// doc file mon hoc 
void MH_docFileMonHoc(PTRMH &root){
	MonHoc mh;
	ifstream filein;
	root = NULL;
	filein.open("MonHoc.txt",ios::in);
	int slmh;
	filein>>slmh;
	filein.ignore();
	for(int i =0; i<slmh; i++){
		filein.getline(mh.MAMH , 10);
		filein.getline(mh.TENMH,35);
		filein>>mh.STCLT;
		filein.ignore();
		filein>>mh.STCTH;
		filein.ignore();
		MH_Insert(root, mh);	
	}
	cout<<"\nDoc file MH thanh cong";
	filein.close();
}

// =============================== SINH VIEN ======================================
// Clear Danh Sach Sinh Vien
void SV_clearlist(PTRSV &FirstSV){
    PTRSV p;   
    p = FirstSV;
    while(FirstSV != NULL){
      p = FirstSV;
      FirstSV = FirstSV->next;
      delete p;
   }
}

//TIM SV THEO ....
PTRSV SV_search_MS(PTRSV FirstSV, char *x){
	PTRSV p;
	for(p=FirstSV; p!= NULL; p=p->next){
		if(stricmp(p->sv.MASV,x)==0)
		return p;
	}
	return NULL;
}

PTRSV SV_search_ML(PTRSV FirstSV, char *x){
	PTRSV p;
	for(p=FirstSV; p!= NULL; p=p->next){
		if(stricmp(p->sv.MALOP,x)==0)
		return p;
	}
	return NULL;
}

//THEM SV VAO CUOI
void SV_Insert_last(PTRSV &FirstSV, SinhVien x){
	PTRSV tmp = new nodeSV;
	tmp->sv = x;
	
	if(FirstSV==NULL){
		tmp->next = FirstSV;
		FirstSV = tmp;
	} 
		
	else{
	  	PTRSV p = FirstSV;
	  	while(p->next!=NULL)
			p = p->next;
	   	p->next = tmp;
	   	tmp->next=NULL;
	}    
}

//KHOI TAO DANH SACH SINH VIEN
void SV_Create_DSSV(PTRSV &FirstSV){ 
	PTRSV temp;
    SinhVien sv;
    char maso[15],c;    
    cout<<"\nNHAP 0 DE DUNG LAI";
  	do{
  		printf("\nMa so sinh vien: "); fflush(stdin);
		gets(sv.MASV);
		if(stricmp(sv.MASV,"0")==0) return;
		temp=SV_search_MS(FirstSV,sv.MASV);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: "); fflush(stdin);
		gets(sv.HO);
		printf("Ten sinh vien: "); fflush(stdin);
		gets(sv.TEN);
		cout<<"Ma lop: "; fflush(stdin);
		gets(sv.MALOP);
		cout<<"Phai: "; fflush(stdin);
		gets(sv.PHAI);
		cout<<"So dien thoai: "; fflush(stdin);
		gets(sv.SDT);		
		SV_Insert_last(FirstSV,sv);
	}while(1);
}

// In danh sach sinh vien
void SV_traverse(PTRSV FirstSV){
   	PTRSV p;
   	int stt = 0;
   	p = FirstSV; 
   	if(FirstSV == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return;
   	}
      
   	printf("\n                                     DANH SACH SINH VIEN: \n");
   	printf("\n   STT       MSSV             HO               TEN        MA LOP        PHAI         SDT");
   	while(p != NULL){
      	printf("\n    %-5d %-10s     %-20s %-10s %-15s %-7s %-15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.MALOP, p->sv.PHAI, p->sv.SDT);
      	p = p->next;
   	}
   	getche();
}

void SV_KT_MaLop(PTRSV &FirstSV, char *malop){
	PTRSV p;
	do{
		cout<<"\nNhap ma lop: ";fflush(stdin);
		gets(malop);
		p=SV_search_ML(FirstSV,malop);
		if(p==NULL){
			cout<<"\nMa lop khong ton tai";
			continue;
		}
		else
			return;
	}while(1);
}


//THEM SV VAO DS SINH VIEN LK DON BANG MA LOP
void SV_Them_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p,temp;
	SinhVien sv;
	cout<<"\nNhap ma lop: ";
	gets(sv.MALOP);
	do{
  		printf("\nMa so sinh vien: "); fflush(stdin);
		gets(sv.MASV);
		if(stricmp(sv.MASV,"0")==0) return;
		temp=SV_search_MS(FirstSV,sv.MASV);
		if(temp!=NULL)	{
			cout<<"\nMa so bi trung.\n";
			continue;	
		}
		printf("Ho sinh vien: ");fflush(stdin);
		gets(sv.HO);
		printf("Ten sinh vien: ");fflush(stdin);
		gets(sv.TEN);
		cout<<"Phai: ";fflush(stdin);
		gets(sv.PHAI);
		cout<<"So dien thoai: ";fflush(stdin);
		gets(sv.SDT);
		SV_Insert_last(FirstSV,sv);
	}while(1);
}

void SV_Delete_after(PTRSV p){
	PTRSV q;
	// neu p la NULL hoac p chi nut cuoi
	if((p == NULL) || (p->next == NULL))
      printf("Khong xoa sinh vien nay duoc");
    else{
    	q=p->next;
    	p->next=q->next;
    	delete q;
	}
}

void SV_Delete_first(PTRSV &FirstSV){
	PTRSV p;
	p=FirstSV;
	FirstSV=p->next;
	delete p;
}

PTRSV SV_search_malopmasv(PTRSV FirstSV, char *malop, char *masv){
	PTRSV p;
	for(p=FirstSV; p!= NULL; p=p->next){
		if(stricmp(p->sv.MASV,masv)==0 && stricmp(p->sv.MALOP,malop)==0)
		return p;
	}
	return NULL;
}

//XOA SINH VIEN
void SV_Xoa_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p;
	char malop[15], masv[15];
	SV_KT_MaLop(FirstSV,malop);
	
	printf("\n                   DANH SACH SINH VIEN LOP %s: ", malop);
   	printf("\n   STT       MSSV             HO               TEN       PHAI         SDT");
   	p=FirstSV;
   	int stt =0;
   	while(p != NULL){
   		if(stricmp(p->sv.MALOP,malop)==0)
      		printf("\n    %-5d %-10s     %-20s %-10s %-7s %-15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.PHAI, p->sv.SDT);
      	p = p->next;
    }
    cout<<"\nNHAP 0 DE DUNG LAI";
	while (1){
	   	cout<<"\nNhap ma sinh vien muon xoa: ";fflush(stdin);
	   	gets(masv);
	   	if(stricmp(masv,"0")==0)	return;
		p= SV_search_malopmasv(FirstSV,malop,masv);
		if(p==NULL){
		    cout<<"\nKhong ton tai";
		    continue;
		}
		else{
			cout<<"\n\tHo\tTen";
		 	cout<<"\n\t"<<p->sv.HO<<"\t"<<p->sv.TEN;
		 	int yn = XacNhan("\nBan co muon xoa khong? (Y/N): ");
			if(yn==1){
				if(p==FirstSV){
					SV_Delete_first(FirstSV);
				}
				else{
					PTRSV temp = FirstSV;
					while(temp->next != p){
						temp=temp->next;
					}
					SV_Delete_after(temp);
				}
				cout<<"\nXoa thanh cong";
				getch();
			}
		}
	}
}

// SUA SINH VIEN THEO MA LOP
void SV_Sua_SV_theo_malop(PTRSV &FirstSV){
	PTRSV p;
	char malop[15], masv[15];
	SV_KT_MaLop(FirstSV,malop);
	
	printf("\n                   DANH SACH SINH VIEN LOP %s: ", malop);
   	printf("\n   STT       MSSV             HO               TEN       PHAI         SDT");
   	p=FirstSV;
   	int stt =0;
   	while(p != NULL){
   		if(stricmp(p->sv.MALOP,malop)==0)
      		printf("\n    %-5d %-10s     %-20s %-10s %-7s %-15s"   , ++stt, p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.PHAI, p->sv.SDT);
      	p = p->next;
    }

	while (1){
	    cout<<"\nNhap ma sinh vien muon sua: ";fflush(stdin);
	   	gets(masv);
	   	if(stricmp(masv,"0")==0)	return;
	   	p= SV_search_malopmasv(FirstSV,malop,masv);
	   	if(p==NULL){
		   	cout<<"\n Khong ton tai.";
		   	continue;
	   	}
	   	SinhVien sv;
	   	cout<<"\nNHAP ENTER DE BO QUA (KHONG SUA)\n";
	   	cout<<"\nNhap ho: "; fflush(stdin);
	   	gets(sv.HO);
	   	if(stricmp(sv.HO,"")!=0)	strcpy(p->sv.HO,sv.HO);
	   	cout<<"\nNhap ten: "; fflush(stdin);
	   	gets(sv.TEN);
	   	if(stricmp(sv.TEN,"")!=0)	strcpy(p->sv.TEN,sv.TEN);
	   	cout<<"\nNhap phai: "; fflush(stdin);
	   	gets(sv.PHAI);
	   	if(stricmp(sv.PHAI,"")!=0)	strcpy(p->sv.PHAI,sv.PHAI);
	   	cout<<"\nNhap sdt: "; fflush(stdin);
	   	gets(sv.SDT);
	   	if(stricmp(sv.SDT,"")!=0)	strcpy(p->sv.SDT,sv.SDT);
	}
}

// Them 1 SV vao DSTT
void SV_Insert_dstt(DanhSachSV &listSV, SinhVien sv){
	listSV.node[listSV.soluong]=sv;
	listSV.soluong +=1;
}

// Duyet DSSV - Them SV Thuoc ma lop vao DSTT
void SV_ThemSV_VaoDSTT(PTRSV &FirstSV, char* malop, DanhSachSV &listSV){
	PTRSV p=FirstSV;
	while(p!=NULL){
		if(stricmp(p->sv.MALOP,malop)==0)
			SV_Insert_dstt(listSV,p->sv);
		p=p->next;
	}
}

// Sap sep DSTT SV theo ten ho - Selection sort
void SV_SapXepTenHo(DanhSachSV &listSV){
	int vitrimin;
	SinhVien min;
  	int i,j;
  	for (i=0; i< listSV.soluong-1; i++){
    	min = listSV.node[i];    vitrimin=i;
    	for (j=i+1; j<listSV.soluong; j++)
      		if (stricmp(listSV.node[j].TEN,min.TEN)<0){
	  			min = listSV.node[j];	vitrimin=j;
			}
	  		else if(stricmp(listSV.node[j].TEN,min.TEN)==0){
	  			if(stricmp(listSV.node[j].HO,min.HO)<0){
	  				min = listSV.node[j];	vitrimin=j;
				}		
      		}
    	min = listSV.node[vitrimin] ;    listSV.node[vitrimin] = listSV.node[i];    listSV.node[i] = min;
	}
}

// Show DSTT 
void SV_Show_DSTT(PTRSV &FirstSV){
	char malop[15];
	SV_KT_MaLop(FirstSV,malop);
	DanhSachSV listSV;
	SV_ThemSV_VaoDSTT(FirstSV,malop,listSV);
	SV_SapXepTenHo(listSV);
	
	printf("\n                    DANH SACH SINH VIEN LOP %s: ", malop);
   	printf("\n   STT       MSSV             HO               TEN       PHAI         SDT");
   	for(int i=0; i<listSV.soluong;i++){
   		printf("\n    %-5d %-10s     %-20s %-10s %-7s %-15s"   , i+1,listSV.node[i].MASV, listSV.node[i].HO,listSV.node[i].TEN, listSV.node[i].PHAI, listSV.node[i].SDT);
	}
	delete [] listSV.node;	
}


//ghi file nhi phan SV
int SV_GhiFile (PTRSV &FirstSV) {
	FILE *f = fopen ("SinhVien.txt", "wb");
	if (f==NULL) return 0;
	for (PTRSV p=FirstSV ; p!=NULL ; p=p->next)
	  	fwrite (&p->sv, sizeof (SinhVien), 1, f);
	fclose (f);
	cout<<"Da luu file";
	getche();
	return 1;  
}

//doc file nhi phan SV 
int SV_DocFile (PTRSV &FirstSV) {
	PTRSV p;  SinhVien sv ;
	FILE *f = fopen ("SinhVien.txt", "rb");
	if (f==NULL) 
	  	return 0; // mo file khong duoc
	SV_clearlist(FirstSV);
	while  (fread (&sv, sizeof (SinhVien), 1, f)== 1 ){
		SV_Insert_last (FirstSV , sv);
	} 
	fclose (f);
	cout<<"\nDoc file SV thanh cong";
	return 1;  
}

//==========================LOP TIN CHI========================

void LTC_clearlist(LIST_LTC &list_ltc){
	while(list_ltc.soluong>0){
		DK_clearlist(list_ltc.nodesltc[list_ltc.soluong-1]->FirstDK);
		delete list_ltc.nodesltc[list_ltc.soluong-1];
		list_ltc.soluong--;
	}
}

// ma LTC tu dong tang 
int maTuDongTang(LIST_LTC &list_ltc){
	if(list_ltc.soluong==0) return 1; 
	return list_ltc.nodesltc[list_ltc.soluong-1]->MALOPTC + 1;
}

// search ltc theo ma
int LTC_Search_theoma(LIST_LTC &list_ltc, int x){
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	     if (list_ltc.nodesltc[i]->MALOPTC == x) return i;
	return -1;
}

// tao lop tin chi
int LTC_Create(LIST_LTC &list_ltc, LopTinChi &ltc, PTRMH &root){
	PTRMH p;	
	ltc.MALOPTC=maTuDongTang(list_ltc);
	do{
		cout<<"\nNhap Ma mon hoc: ";fflush(stdin);
		gets(ltc.MAMH);
		if(stricmp(ltc.MAMH,"0")==0) return 0;
		p=MH_SearchMS(root,ltc.MAMH);
		if(p==NULL) {
			cout<<"\n Ma mon khong ton tai.";
			continue;
		}
		cout<<"Nhap Nien khoa: "; fflush(stdin);
		gets(ltc.NIENKHOA);
		cout<<"Nhap Hoc ki: ";
		cin>>ltc.HOCKY;
		cout<<"Nhap Nhom: ";
		cin>>ltc.NHOM;
	SV_Min:
		cout<<"Nhap so sinh vien min: ";
		cin>>ltc.SOSVMIN;
		if(ltc.SOSVMIN<=0){
			cout<<"\nSo sinh vien min phai lon hon 0.";
			goto SV_Min;
		}
	SV_Max:
		cout<<"Nhap so sinh vien max: ";
		cin>>ltc.SOSVMAX;
		if(ltc.SOSVMAX<=ltc.SOSVMIN||ltc.SOSVMAX<=0){
			cout<<"\nSo sinh vien max phai lon hon so sinh vien min va lon hon 0.";
			goto SV_Max;
		}
		ltc.HUYLOP = false;
		ltc.FirstDK=NULL;
		return 1;
	}while(true);
}

// Them LTC vao danh sach khi doc file
void LTC_Insert(LIST_LTC &list_ltc, LopTinChi ltc){
	list_ltc.nodesltc[list_ltc.soluong]=new LopTinChi;
	//gan gia tri lop tin chi them vao vao con tro lop tin chi cuoi mang
	*list_ltc.nodesltc[list_ltc.soluong]=ltc;
	list_ltc.soluong +=1;
}

// tao danh sach lop tin chi
// them lop tin chi
void LTC_Create_List(LIST_LTC &list_ltc,PTRMH &root){
	LopTinChi ltc;
	cout<<"Nhap thong tin lop tin chi\n";
	cout<<"\nNHAP 0 DE DUNG LAI";
	while(list_ltc.soluong<MAXLOPTINCHI){
		if (LTC_Create(list_ltc, ltc,root)==0)    
		   	return;
		LTC_Insert(list_ltc, ltc);
	}
	if(list_ltc.soluong==MAXLOPTINCHI)
		cout<<"\nDanh Sach Day.";
}

// duyet danh sach lop tin chi 
void LTC_traverse(LIST_LTC &list_ltc){
	char huylop[10];
	printf ("                                  DANH SACH LOP TIN CHI \n\n");
 	printf ("  STT   MA LOP   MA MON   NHOM   NIEN KHOA     HOC KY    SO SV MAX     SO SV MIN     HUY LOP\n");
	for (int i =0 ; i < list_ltc.soluong ; i++){
		if(list_ltc.nodesltc[i]->HUYLOP==false)	strcpy(huylop,"");
		else strcpy(huylop,"da huy");
		printf ("   %-6d %-7d %-7s  %-5d %-15s %-10d  %-10d   %-10d %-10s \n", 
		  i+1,
		  list_ltc.nodesltc[i]->MALOPTC,
		  list_ltc.nodesltc[i]->MAMH,
		  list_ltc.nodesltc[i]->NHOM,
		  list_ltc.nodesltc[i]->NIENKHOA,
		  list_ltc.nodesltc[i]->HOCKY,
		  list_ltc.nodesltc[i]->SOSVMAX,
		  list_ltc.nodesltc[i]->SOSVMIN,
		  huylop);
	}  		
}

int LTC_Empty(LIST_LTC &list_ltc){
    return(list_ltc.soluong == 0 ? 1 : 0);
}

// xoa LTC theo ma
void LTC_Delete_theoma(LIST_LTC &list_ltc){
	int maltc,j,vitri;
	char huylop[10];
	cout<<"\nNHAP 0 DE DUNG LAI";
LTC_XoaTiep:
	cout<<"\nNhap ma lop tin chi muon xoa: ";
	cin>>maltc;
	if(maltc==0) return;
	vitri=LTC_Search_theoma(list_ltc,maltc);
	if(vitri == -1){
		printf("\nMa lop khong ton tai.");
		goto LTC_XoaTiep;
	}
	else if(list_ltc.nodesltc[vitri]->FirstDK!=NULL){
		cout<<"\nKhong the xoa lop tin chi.";   // LTC co SV dang ky -> ko the xoa
		goto LTC_XoaTiep;
	}
	else{
		printf ("   MA LOP   MA MON   NHOM   NIEN KHOA     HOC KY    SO SV MAX     SO SV MIN     HUY LOP\n");
		if(list_ltc.nodesltc[vitri]->HUYLOP==false)	strcpy(huylop,"");
		else strcpy(huylop,"da huy");
  		printf ("     %-7d %-7s  %-5d %-15s %-10d  %-10d   %-10d %-10s \n", 
	  		list_ltc.nodesltc[vitri]->MALOPTC,
	  		list_ltc.nodesltc[vitri]->MAMH,
	  		list_ltc.nodesltc[vitri]->NHOM,
	  		list_ltc.nodesltc[vitri]->NIENKHOA,
	  		list_ltc.nodesltc[vitri]->HOCKY,
	  		list_ltc.nodesltc[vitri]->SOSVMAX,
	  		list_ltc.nodesltc[vitri]->SOSVMIN,
			huylop );
		int yn = XacNhan("\nBan co muon xoa khong? (Y/N): ");
		if(yn==1){
			delete list_ltc.nodesltc[vitri];
			for(j = vitri+1;  j< list_ltc.soluong ; j++)
				list_ltc.nodesltc[j-1] = list_ltc.nodesltc[j];
			list_ltc.soluong--;
			cout<<"\nXoa Thanh Cong!";
		}
		goto LTC_XoaTiep;
	}
}

//Sua info LTC theo ma  
void LTC_Sua_theoma(LIST_LTC &list_ltc, PTRMH &root){
	char x[10],huylop[10];
	int maltc;
	cout<<"\nNHAP 0 DE DUNG LAI";
LTC_SuaTiep:
	cout<<"\nNhap ma lop tin chi muon sua: ";
	cin>>maltc;
	if(maltc==0) return;
	int vitri=LTC_Search_theoma(list_ltc,maltc);
	if(vitri==-1){
		cout<<"Khong tim thay.";
		goto LTC_SuaTiep;
	}
	else{
		printf ("   MA LOP   MA MON   NHOM   NIEN KHOA     HOC KY    SO SV MAX     SO SV MIN     HUY LOP\n");
		if(list_ltc.nodesltc[vitri]->HUYLOP==false)	strcpy(huylop,"");
		else strcpy(huylop,"da huy");
  		printf ("     %-7d %-7s  %-5d %-15s %-10d  %-10d   %-10d %-10s \n", 
	  		list_ltc.nodesltc[vitri]->MALOPTC,
	  		list_ltc.nodesltc[vitri]->MAMH,
	  		list_ltc.nodesltc[vitri]->NHOM,
	  		list_ltc.nodesltc[vitri]->NIENKHOA,
	  		list_ltc.nodesltc[vitri]->HOCKY,
	  		list_ltc.nodesltc[vitri]->SOSVMAX,
	  		list_ltc.nodesltc[vitri]->SOSVMIN,
			huylop );
	  	cout<<"\nNHAN ENTER DE BO QUA (KHONG SUA)\n";
	LTC_NhapLaiMonHoc:
	  	cout<<"\nNhap Ma mon hoc: ";	fflush(stdin);
		gets(x);
		PTRMH p = MH_SearchMS(root,x);
		if(stricmp(x,"")!=0){
			if(p==NULL){
				cout<<"\nMa mon hoc khong ton tai";
				goto LTC_NhapLaiMonHoc;
			}
			else	strcpy(list_ltc.nodesltc[vitri]->MAMH,x);
		}  
	  	cout<<"Nhap Nien khoa: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"")!=0)	strcpy(list_ltc.nodesltc[vitri]->NIENKHOA,x);
		cout<<"Nhap Hoc ki: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"")!=0)	list_ltc.nodesltc[vitri]->HOCKY=atoi(x);
		cout<<"Nhap Nhom: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"")!=0)	list_ltc.nodesltc[vitri]->NHOM=atoi(x);
	LTC_Sua_svmin:
		cout<<"Nhap so sinh vien min: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"")!=0){
			list_ltc.nodesltc[vitri]->SOSVMIN=atoi(x);
			if(list_ltc.nodesltc[vitri]->SOSVMIN<=0){
				cout<<"\nSo sinh vien min phai lon hon 0";
				goto LTC_Sua_svmin;
			}
		}
	LTC_Sua_svmax:
		cout<<"Nhap so sinh vien max: "; fflush(stdin);
		gets(x);
		if(stricmp(x,"")!=0){
			list_ltc.nodesltc[vitri]->SOSVMAX=atoi(x);
			if(list_ltc.nodesltc[vitri]->SOSVMAX<=0||list_ltc.nodesltc[vitri]->SOSVMAX<=list_ltc.nodesltc[vitri]->SOSVMIN){
				cout<<"\nSo sinh vien max phai lon hon so sinh vien min va lon hon 0";
				goto LTC_Sua_svmax;
			}			
		}
		goto LTC_SuaTiep;
	}
}

int LTC_KTDiem(PTRDK &FirstDK){
	PTRDK p=FirstDK;
	while(p!=NULL){
		if(p->dangky.DIEM!=0)
			return 1;
	}
	return 0;
}

void LTC_Show_HuyLop(LIST_LTC &list_ltc, char *nienkhoa, int hocky){
	int sosvdk, stt=1;
	printf ("             DANH SACH LOP TIN CHI CO SO SV DANG KY NHO HON SO SV MIN \n");
 	printf ("  Stt   MA LOP   MA MON   NHOM   NIEN KHOA     HOC KY    SO SV MAX     SO SV MIN   SO SV DA DK");
	for(int i=0;i<list_ltc.soluong;i++){		
		if(stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[i]->HOCKY==hocky){
			sosvdk=DK_Reccount(list_ltc.nodesltc[i]->FirstDK);
			if(sosvdk < list_ltc.nodesltc[i]->SOSVMIN){
				printf ("\n   %-6d %-7d %-7s  %-5d %-15s %-10d  %-10d   %-10d %10d\n", 
				  stt++,
				  list_ltc.nodesltc[i]->MALOPTC,
				  list_ltc.nodesltc[i]->MAMH,
				  list_ltc.nodesltc[i]->NHOM,
				  list_ltc.nodesltc[i]->NIENKHOA,
				  list_ltc.nodesltc[i]->HOCKY,
				  list_ltc.nodesltc[i]->SOSVMAX,
				  
				  list_ltc.nodesltc[i]->SOSVMIN,
				  sosvdk);
				int yn = XacNhan("\nBan co muon huy lop nay khong? (Y/N): ");
				if(yn==1){
					if(LTC_KTDiem(list_ltc.nodesltc[i]->FirstDK)==0){
						list_ltc.nodesltc[i]->HUYLOP=true;
						cout<<"\nHuy lop thanh cong.";
						getch();
					}
					else
						cout<<"\nKhong the huy lop. Sinh vien dang ky lop da co diem.\n";
						getch();
				}
			}		
		}	
	}
}

void LTC_HuyLop(LIST_LTC &list_ltc){
	char nienkhoa[10];
	int hocky;
	cout<<"\nNhap nien khoa: "; fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap hoc ky: ";
	cin>>hocky;
	LTC_Show_HuyLop(list_ltc,nienkhoa,hocky);	
}

// ghi file lop tin chi
void LTC_ghiFile(LIST_LTC &list_ltc){
	PTRDK p;
	ofstream outfile;
	outfile.open("LopTinChi.txt");
	outfile<<list_ltc.soluong<<endl;	//ghi so luong lop
	for(int i=0; i<list_ltc.soluong;i++){
		outfile<<list_ltc.nodesltc[i]->MALOPTC<<endl;
		outfile<<list_ltc.nodesltc[i]->MAMH<<endl;
		outfile<<list_ltc.nodesltc[i]->NHOM<<endl;
		outfile<<list_ltc.nodesltc[i]->HOCKY<<endl;
		outfile<<list_ltc.nodesltc[i]->NIENKHOA<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMIN<<endl;
		outfile<<list_ltc.nodesltc[i]->SOSVMAX<<endl;
		if(list_ltc.nodesltc[i]->HUYLOP==true)
		outfile<<1<<endl;
		else outfile<<0<<endl;
		int slsv=DK_Reccount(list_ltc.nodesltc[i]->FirstDK);	//ghi so luong sinh vien cua lop
		outfile<<slsv<<endl;
		p=list_ltc.nodesltc[i]->FirstDK;
		while(p!=NULL){
			outfile<<p->dangky.MASV<<endl;
			outfile<<p->dangky.DIEM<<endl;
			if(p->dangky.HUYDANGKY==true)
			outfile<<1<<endl;
			else outfile<<0<<endl;	
			p=p->next;	
		}
	}
	outfile.close();
}

//doc file lop tin chi
void LTC_docFile(LIST_LTC &list_ltc){
	LopTinChi ltc;
	DangKy dk;
	ifstream filein;
	int slsv,slltc;
	list_ltc.soluong=0;
	filein.open("LopTinChi.txt",ios::in);
	filein>>slltc;
	filein.ignore();
	for(int i =0; i<slltc; i++){
		filein>>ltc.MALOPTC;
		filein.ignore();
		filein.getline(ltc.MAMH, 10);
		filein>>ltc.NHOM;
		filein.ignore();
		filein>>ltc.HOCKY;
		filein.ignore();
		filein.getline(ltc.NIENKHOA,10);
		filein>>ltc.SOSVMIN;
		filein.ignore();
		filein>>ltc.SOSVMAX;
		filein.ignore();
		int kt;
		filein>>kt;
		filein.ignore();
		if(kt==1)	ltc.HUYLOP=true;
		else	ltc.HUYLOP=false;
		filein>>slsv;
		filein.ignore();
		
		ltc.FirstDK=NULL;
		
		for(int j=0; j<slsv;j++){
			filein.getline(dk.MASV,15);
			filein>>dk.DIEM;
			filein.ignore();
			filein>>kt;
			filein.ignore();
			if(kt==1)	dk.HUYDANGKY=true;
			else	dk.HUYDANGKY=false;
			DK_Insert_last(ltc.FirstDK,dk);
		}
		LTC_Insert(list_ltc, ltc);		
	}
	cout<<"\nDoc file LTC thanh cong";
	filein.close();
}

//===============DS DANG KY================//

void DK_clearlist(PTRDK &FirstDK){
    PTRDK p;   
    p = FirstDK;
    while(FirstDK != NULL){
      p = FirstDK;
      FirstDK = FirstDK->next;
      delete p;
   }
}

int DK_Reccount(PTRDK &FirstDK){
	PTRDK p;
	int tong = 0;
	for(p=FirstDK; p!=NULL; p=p->next){
		++tong;
	}
	return tong;
}

void DK_Insert_last(PTRDK &FirstDK,DangKy dk){
	PTRDK tmp = new nodeDangKy;
	tmp->dangky= dk;
	if(FirstDK==NULL){
		tmp->next = FirstDK;
		FirstDK = tmp;
	} 	
	else {
	  	PTRDK p = FirstDK;
	  	while(p->next!=NULL)
			p = p->next;
	   	p->next = tmp;
	   	tmp->next=NULL;
	}    
}

PTRDK DK_search_masv(PTRDK &First, char *x){
	PTRDK p;
	for(p=First; p!= NULL; p=p->next){
		if(stricmp(p->dangky.MASV,x)==0)
		return p;
	}
	return NULL;
}

// TIM LOP DUA VAO NIEN KHOA, HOOC KY, MA MON, NHOM
int DK_Search_Info(LIST_LTC list_ltc, char *nienkhoa, char *mamon, int hocki, int nhom){
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	     if (stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0
		   &&stricmp(list_ltc.nodesltc[i]->MAMH,mamon)==0
		   &&list_ltc.nodesltc[i]->HOCKY==hocki
		   &&list_ltc.nodesltc[i]->NHOM==nhom)
		   return i;
	return -1;
}

int DK_traverse(LIST_LTC &list_ltc, PTRSV &FirstSV){
	char huydk[10];
	int malop;
DK_Xem:
  	cout<<"Nhap ma lop muon xem: ";
  	cin>>malop;
  	int vitri = LTC_Search_theoma(list_ltc,malop);
  	if(vitri==-1){
  		cout<<"\nMa lop khong ton tai.";
  		goto DK_Xem;
	}
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->FirstDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return -1;
   	}      
   	printf("\n             DANH SACH SINH VIEN LOP TIN CHI: ");
   	printf("\n     STT       MSSV       HO           TEN            DIEM        HUY DANG KY");
   	while(p != NULL){
   		if(p->dangky.HUYDANGKY==false) strcpy(huydk,"");
   		else strcpy(huydk, "Da huy");
   		PTRSV tempsv = SV_search_MS(FirstSV,p->dangky.MASV);
      	printf("\n   %5d %10s  %-15s %-10s %15d %10s"    , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,p->dangky.DIEM, huydk);
      	p = p->next;
   	}
   getche();
   return vitri;
}

// nien khoa, hoc ki, ma mon , nhom
void DK_Show_theo_info(LIST_LTC &list_ltc, PTRSV &FirstSV){
	char nienkhoa[10], mamon[10], huydk[10];
	int nhom, hocki;
DK_Xem_Info:
	cout<<"\nNhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap ma mon: ";fflush(stdin);
	gets(mamon);
	cout<<"\nNhap hoc ki: ";
	cin>>hocki;
	cout<<"\nNhap nhom: ";
	cin>>nhom;
	
  	int vitri = DK_Search_Info(list_ltc,nienkhoa,mamon,hocki,nhom);
  	if(vitri==-1){
  		cout<<"\nLop khong ton tai.";
		  goto DK_Xem_Info;	
	}
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->FirstDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return;
    }
   	printf("\n                              DANH SACH SINH VIEN DANG KY LOP TIN CHI: ");
   	printf("\n   STT       MSSV             HO               TEN        MA LOP        PHAI         SDT        HUY DANG KY");
   	while(p != NULL){
   		if(p->dangky.HUYDANGKY==false) strcpy(huydk,"");
   		else strcpy(huydk, "Da huy");
   		PTRSV tempsv = SV_search_MS(FirstSV,p->dangky.MASV); 		
      	printf("\n    %-5d %-10s     %-20s %-10s %-15s %-7s %-17s %-10s"   , ++stt, p->dangky.MASV, tempsv->sv.HO, tempsv->sv.TEN,tempsv->sv.MALOP,tempsv->sv.PHAI,tempsv->sv.SDT, huydk);
      	p = p->next;
   	}
   getche();
   return;
}

// Show Khi dang ky LTC - nhap nien khoa, hoc ky
int DK_Show_Lop_theo_hk_nk(PTRMH &root, LIST_LTC list_ltc, char *nienkhoa,  int hocki){
	int so_sv_dk, stt=0;
	int so_slot_con_trong;
	PTRMH p;
	printf ("                     DANH SACH LOP TIN CHI HOC KY %d, NIEN KHOA %s\n\n",hocki, nienkhoa);
	printf ("  STT   MA LOP   MA MON       TEN MON           NHOM     SO SV DA DANG KY     SO SLOT CON TRONG      \n");
	for ( int i =0 ; i <list_ltc.soluong ; i++)
  	    if (stricmp(list_ltc.nodesltc[i]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[i]->HOCKY==hocki ){
  	     	p=MH_SearchMS(root, list_ltc.nodesltc[i]->MAMH);
  	     	so_sv_dk = DK_Reccount(list_ltc.nodesltc[i]->FirstDK);
  	     	so_slot_con_trong = list_ltc.nodesltc[i]->SOSVMAX - so_sv_dk;
		  	printf ("   %-6d %-7d %-7s %-22s %-13d %-20d %-5d    \n",
			  	  stt++, 
				  list_ltc.nodesltc[i]->MALOPTC,
				  list_ltc.nodesltc[i]->MAMH,
				  p->mh.TENMH,
				  list_ltc.nodesltc[i]->NHOM,
				  so_sv_dk,
				  so_slot_con_trong);  
	}
	if(stt==0){
		cout<<"\nKhong co lop tin chi o hoc ky nay.";
		getch();
		return -1;
	}
	else return 0;
}

// SV dang ky LTC
void DK_SVDangKyLTC(LIST_LTC &list_ltc, char *masv, int malop){
	PTRDK Last,p, tempdk;
  	DangKy dk; 
  	int vitri = LTC_Search_theoma(list_ltc,malop);
  	tempdk=DK_search_masv(list_ltc.nodesltc[vitri]->FirstDK,masv);
  	if(tempdk!=NULL){
  		if(tempdk->dangky.HUYDANGKY==false){
  			cout<<"\nSinh vien da dang ky.";
  			return;
		}
		else{
			tempdk->dangky.HUYDANGKY=false;
			cout<<"\nDang ky thanh cong.";
		}	
	}
  	else{
  		int so_sv_dk = DK_Reccount(list_ltc.nodesltc[vitri]->FirstDK);
  		if(so_sv_dk==list_ltc.nodesltc[vitri]->SOSVMAX){
  			cout<<"\nKhong the dang ky. Lop da day.";
  			return;
		}
		else{
			dk.DIEM = 0;
	  		strcpy(dk.MASV,masv);
	  		dk.HUYDANGKY=false;
	  		p= new nodeDangKy;
	  		p->dangky=dk;
	  		DK_Insert_last(list_ltc.nodesltc[vitri]->FirstDK,dk);
		} 
		cout<<"\nDang ky thanh cong!";		
	}
}

void DK_HuyDK(LIST_LTC &list_ltc, char *masv, int malop){
	PTRDK tempdk,p;
	int vitri=LTC_Search_theoma(list_ltc,malop);
	tempdk=DK_search_masv(list_ltc.nodesltc[vitri]->FirstDK,masv);
	if(tempdk==NULL){
		cout<<"Sinh vien khong co trong lop tin chi.";
		return;
	}
	else{
		tempdk->dangky.HUYDANGKY=true;
		cout<<"\nHuy dang ky thanh cong!";
	}
}

// DANG KY/HUY DANG KY LOP TIN CHI - NHAP MA SV
void DK_DangKyLopTinChi(PTRMH &root, PTRSV &FirstSV, LIST_LTC &list_ltc){
	char masv[15], nienkhoa[10];
	int hocki, malop, chon;
	PTRSV p;
	cout<<"\nNHAP 0 DE DUNG LAI";
DK_DangKy:
	cout<<"\nNhap ma sinh vien: ";fflush(stdin);
	gets(masv);
	if(stricmp(masv,"0")==0) return;
	p=SV_search_MS(FirstSV,masv);
	if(p==NULL){
		cout<<"\nSinh vien khong ton tai.";
		goto DK_DangKy;
	}
	printf("\n        MSSV             HO               TEN          MA LOP       PHAI        SDT");
	printf("\n      %-14s %-20s %-10s %-15s %-7s %-17s"   , p->sv.MASV, p->sv.HO,p->sv.TEN, p->sv.MALOP, p->sv.PHAI, p->sv.SDT);
	cout<<"\nNhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap hoc ky: ";
	cin>>hocki;
	if(DK_Show_Lop_theo_hk_nk(root,list_ltc, nienkhoa, hocki)==-1) return;
	
	do{
		cout<<"\n\t\t    1. Dang ky\n";
		cout<<"\t\t    2. Huy dang ky\n";
		cout<<"\t\t    3. Thoat\n";
		cout<<"Chon: ";
		cin>>chon;
		switch(chon){
			case 1: {
				cout<<"\n NHAP MA LOP 0 DE DUNG DANG KY";
				do{
					cout<<"\nNhap ma lop muon dang ky: ";
					cin>>malop;
					if(malop==0) break;
					if(stricmp(list_ltc.nodesltc[malop-1]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[malop-1]->HOCKY==hocki){
						DK_SVDangKyLTC(list_ltc,masv,malop);
					}else cout<<"\nLop khong co trong nien khoa "<<nienkhoa<< " hoc ky "<<hocki;
				}while(true);
				break;
			}
			case 2: {
				cout<<"\n NHAP MA LOP 0 DE DUNG LAI";
				do{
					cout<<"\nNhap ma lop muon huy dang ky: ";
					cin>>malop;
					if(malop==0) break;
					if(stricmp(list_ltc.nodesltc[malop-1]->NIENKHOA,nienkhoa)==0 && list_ltc.nodesltc[malop-1]->HOCKY==hocki){
						DK_HuyDK(list_ltc,masv,malop);
					}else cout<<"\nLop khong co trong nien khoa "<<nienkhoa<< " hoc ky "<<hocki;
				}while(true);
				break;
			}
			case 3:{
				return;
			}
		}
	}while(1);	
}

void DK_Nhap_Diem(LIST_LTC &list_ltc, PTRSV &FirstSV){
	char nienkhoa[10], mamon[10], huydk[10];
	int nhom, hocki;
	
	cout<<"\nNhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap ma mon: ";fflush(stdin);
	gets(mamon);
	cout<<"\nNhap hoc ki: ";
	cin>>hocki;
	cout<<"\nNhap nhom: ";
	cin>>nhom;
	
  	int vitri = DK_Search_Info(list_ltc,nienkhoa,mamon,hocki,nhom);
  	if(vitri==-1) {
  		cout<<"\nLop khong ton tai.";
  		return;
	  }
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->FirstDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return;
    }   	
   	while(p != NULL){
   		if(p->dangky.HUYDANGKY==false){
   			PTRSV tempsv = SV_search_MS(FirstSV,p->dangky.MASV);
   			float diem;
   			cout<<endl<<"\nNhap diem cho sinh vien: ";
   			printf("\n          MSSV              HO                  TEN           DIEM       ");
			printf("\n       %-15s %-24s %-10s ",tempsv->sv.MASV,tempsv->sv.HO,tempsv->sv.TEN);
			cout<<"\nDiem: ";
			cin>>diem;
			p->dangky.DIEM = diem;     	
		}
   		p = p->next;
   	}
   	return;
}

void DK_InBangDiem(LIST_LTC &list_ltc, PTRSV &FirstSV, PTRMH &root){
	char nienkhoa[10], mamon[10], huydk[10];
	int nhom, hocki;
	
	cout<<"Nhap nien khoa: ";fflush(stdin);
	gets(nienkhoa);
	cout<<"\nNhap ma mon: ";fflush(stdin);
	gets(mamon);
	cout<<"\nNhap hoc ki: ";
	cin>>hocki;
	cout<<"\nNhap nhom: ";
	cin>>nhom;
	
  	int vitri = DK_Search_Info(list_ltc,nienkhoa,mamon,hocki,nhom);
  	if(vitri==-1) {
  		cout<<"\nLop khong ton tai.";
  		return;
	  }
  	PTRMH tempmh=MH_SearchMS(root,mamon);
   	PTRDK p;
   	int stt = 0;
   	p = list_ltc.nodesltc[vitri]->FirstDK; 
   	if(p == NULL){
   		printf("\n   (Khong co sinh vien trong danh sach)");
   		getche();
   		return;
    }
    
   	cout<<endl<<"       BANG DIEM MON HOC "<<tempmh->mh.TENMH;
   	cout<<endl<<"Nien khoa: "<<nienkhoa<<"  Hoc ky: "<<hocki<<"  Nhom: "<<nhom;
   	printf("\n\n   STT      MSSV              HO                  TEN           DIEM       ");
   	while(p != NULL)
   	{
   		if(p->dangky.HUYDANGKY==false){
   			PTRSV tempsv = SV_search_MS(FirstSV,p->dangky.MASV);
      		cout<<endl<<"     "<<++stt<<"     " <<p->dangky.MASV<<"        "<< tempsv->sv.HO<<"                "<<tempsv->sv.TEN<<"        "<<p->dangky.DIEM;    	
			//printf("\n      %5d %-15s %-24s %-10s %-10d",stt++,tempsv->sv.MASV,tempsv->sv.HO,tempsv->sv.TEN,p->dangky.DIEM);
		}
   		p = p->next;
   	}
    getche();
    return;
}

//============================== MAIN =================================

int mainMenu(){
	int chucnang;
	do {
		system("cls");
		printf("\n\n\t\tQUAN LY SINH VIEN THEO HE TIN CHI");
		printf("\n\Cac chuc nang cua chuong trinh\n");
		printf("   1. Quan ly mon hoc\n");
		printf("   2: Quan ly sinh vien\n");
		printf("   3: Quan ly lop tin chi\n");
		printf("   4: Ghi file \n");
      	printf("   5: Doc file \n");
		printf("   0: Thoat\n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
		
	}while(chucnang< 0 || chucnang>5) ;
    return chucnang;
}

int menuQLMH(){
	int chucnang;
	do{
		system("cls");
		printf("\n\n\t\tQUAN LY MON HOC\n");
		printf("   1: Nhap mon hoc\n");
		printf("   2: Xem danh sach mon hoc\n");
		printf("   3: Xoa Mon hoc \n");
		printf("   4: Sua Mon hoc \n");
		printf("   5: Sap xep mon hoc theo ten \n");
		printf("   0: Thoat \n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
		
	}while(chucnang< 0 || chucnang>5) ;
    return chucnang;
}

int menuQLSV(){
	int chucnang;
	do{
		system("cls");
		printf("\n\n\t\tQUAN LY SINH VIEN\n");
		printf("   1: Them sinh vien\n");
		printf("   2: Xem danh sach sinh vien\n");
		printf("   3: Them sinh vien theo ma lop\n");
		printf("   4: Xoa sinh vien theo ma lop \n");
		printf("   5: Sua sinh vien theo ma lop \n");
		printf("   6: In danh sach sinh vien theo ma lop sap xep theo ten ho \n");
		printf("   0: Thoat \n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
		
	}while(chucnang< 0 || chucnang>6) ;
    return chucnang;
}

int menuQLLTC(){
	int chucnang;
	do{
		system("cls");
		printf("\n\n\t\tQUAN LY LOP TIN CHI\n");
		printf("   1: Them lop tin chi\n");
		printf("   2: Xem lop tin chi\n");
		printf("   3: Xoa lop tin chi\n");
		printf("   4: Sua lop tin chi\n");
		printf("   5: Huy lop tin chi\n");
		printf("   6: Nhap nien khoa, hoc ki, nhom, mon hoc in DSSV LTC\n");
		printf("   7: Dang ky/huy dang ky LTC\n");
		printf("   8: Nhap diem\n");
		printf("   9: In bang diem LTC\n");
		printf("   0: Thoat \n");
		printf("Chuc nang ban chon: ");
		cin>>chucnang;
	}while(chucnang< 0 || chucnang>9) ;
    return chucnang;
}

//==============================MAIN=====================
int main(){
	PTRMH treeMH = NULL;
	LIST_LTC list_ltc;
	list_ltc.soluong =0;
	PTRSV FirstSV = NULL;
	boolean bien=true;
	do {
		system("cls");
      	int chucnang = mainMenu();
      	system("cls");
      	fflush(stdin);
      	switch(chucnang){
      		case 1:{
      			while(bien){
      				int cn = menuQLMH();
	      			system("cls");
	      			fflush(stdin);
	      			switch(cn){
	      				case 1:{
	      					MH_Create(treeMH);	
							break;
						}
						case 2:{
							printf("\n           DANH SACH MON HOC: ");
							printf("\n     MA MON       TEN MON              STCLT    STCTH");
							MH_Show(treeMH);	
							getch();
							break;						
						}
						case 3: {
							MH_Delete(treeMH);
							break;
						}
						case 4: {
							MH_Sua(treeMH);
							break;
						}
						case 5: {
							MH_SapXep(treeMH);
							break;
						}
						case 0: {
							bien = false;	
							break;
						}
					}
				}
				bien=true;
      			break;
			}
			case 2:{
				while(bien){
					int cn = menuQLSV();
	      			system("cls");
	      			fflush(stdin);
	      			switch(cn){
	      				case 1:{
	      					SV_Create_DSSV(FirstSV);
							break;
						}
						case 2:{
							SV_traverse(FirstSV);
							break;	
						}
						case 3:{
							SV_Them_SV_theo_malop(FirstSV);
							break;	
						}
						case 4: {
							SV_Xoa_SV_theo_malop(FirstSV);
							break;
						}
						case 5: {
							SV_Sua_SV_theo_malop(FirstSV);
							break;
						}
						case 6: {
							SV_Show_DSTT(FirstSV);
							getch();
							break;
						}
						case 0: {
							bien=false;
							break;
						}
					}
				}	
				bien=true;			
				break;
			}
			case 3:{
				while(bien){
					int cn = menuQLLTC();
	      			system("cls");
	      			fflush(stdin);
	      			switch(cn){
	      				case 1:{
	      					LTC_Create_List(list_ltc,treeMH);	      						
							break;
						}
						case 2:{
							LTC_traverse(list_ltc);
							getch();
							break;							
						}
						case 3: {
							LTC_Delete_theoma(list_ltc);
							break;
						}
						case 4: {
							LTC_Sua_theoma(list_ltc,treeMH);
							break;
						}
						case 5: {
							LTC_HuyLop(list_ltc);
							break;
						}
						case 6: {
							DK_Show_theo_info(list_ltc, FirstSV);
							break;
						}
						case 7: {
							DK_DangKyLopTinChi(treeMH,FirstSV,list_ltc);
							break;
						}
						case 8: {
							DK_Nhap_Diem(list_ltc, FirstSV);
							break;
						}
						case 9: {
							DK_InBangDiem(list_ltc,FirstSV,treeMH);
							break;
						}
						case 0: {
							bien = false;
							break;
						}
					}
				}
				bien = true;
				break;
			}
			case 4:{
				//MH_ghiFileMonHoc(treeMH);
				//SV_GhiFile(FirstSV);
				LTC_ghiFile(list_ltc);
				getch();
				break;
			}
			case 5: {
				MH_docFileMonHoc(treeMH);
				SV_DocFile(FirstSV);
				LTC_docFile(list_ltc);
				getch();
				break;
			}
			case 0:{
				system("cls");
				cout<<"Ket Thuc";
				MH_Clear_List(treeMH);
				SV_clearlist(FirstSV);
				LTC_clearlist(list_ltc);
				return 0;
			}
		}
	}
	while(1);
	
}

