#pragma once
// PhongModelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PhongModel.h"
#include "PhongModelDlg.h"
#include "afxdialogex.h"
#include"renderer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhongModelDlg �Ի���



CPhongModelDlg::CPhongModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHONGMODEL_DIALOG, pParent)
	, source_x(0)
	, source_y(0)
	, source_z(0)
	, centerx(0)
	,centery(0)
	,centerz(0)
	,radius(200)
	, n(0)
	, kd(0)
	, ka(0)
	,ks(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhongModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, source_x);
	DDX_Text(pDX, IDC_EDIT2, source_y);
	DDX_Text(pDX, IDC_EDIT3, source_z);
	DDX_Text(pDX, IDC_EDIT5, n);
	DDX_Text(pDX, IDC_EDIT4, kd);
	DDX_Text(pDX, IDC_EDIT6, ka);
}

BEGIN_MESSAGE_MAP(CPhongModelDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDOK, &CPhongModelDlg::OnBeginDraw)
	ON_BN_CLICKED(IDC_PAINT, &CPhongModelDlg::OnClickedPaint)
END_MESSAGE_MAP()


// CPhongModelDlg ��Ϣ�������

BOOL CPhongModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPhongModelDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPhongModelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPhongModelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CPhongModelDlg::OnClickedPaint()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int IPR = 192, IPG = 0, IPB = 0;//��Դ��ǿ
	int IAR = 64, IAG =0, IAB = 0;//������ǿ
	Vector V = Vector(0, 0,1);
	
	CRect rect;
	GetDlgItem(IDC_PIC)->GetWindowRect(rect);
	CPoint pt = rect.CenterPoint();
	//(centerx,centery,centerz)��������
	centerx = pt.x;
	centery = pt.y;
	ks = 1 - kd;
	Vector L0 = Vector(-source_x, -source_y, -source_z);
	Vector L = numbermulptiply(1 / mole(L0), L0);//�ѹ���������һ��

	double moleh = mole(vectorplus(L, V));
	Vector lv = vectorplus(L, V);
	Vector H = numbermulptiply(1 / moleh, lv);

	for (int x = centerx - radius; x < centerx + radius; x++) {
		int ymax = int( sqrt(radius*radius - (centerx - x)*(centerx - x)));
		for (int y = centery - ymax; y < centery + ymax; y++) {
			int z2 = radius*radius - (centerx - x)*(centerx - x) - (centery - y)*(centery - y);
			double z = sqrt(double(z2));
			Vector N0(x-centerx, y-centery, z);
			Vector N= numbermulptiply(1 / mole(N0), N0);
			int IR, IG, IB;    //���ص����ɫ
			double cosi = cos(L, N);      //���ߺͷ������н�����
			if (cosi>0.0)  //������ֱ�ӵ���õ�
			{
				double HN = vectormultiply(H, N);
				double HN_n = pow(HN, n);
				IR = IAR*ka + IPR*kd*cosi + IPR*ks*HN_n;
				IG = IAG*ka + IPG*kd*cosi+ IPG*ks*HN_n;
				IB = IAB*ka + IPB*kd*cosi + IPB*ks*HN_n;
			}
			else           //���߲��ܵ���õ�
			{
				IR = IAR*ka ;
				IG = IAG*ka ;
				IB = IAB*ka ;
			}
			HDC hDC = ::GetDC(NULL);
			SetPixel(hDC, x, y, RGB(IR, IG, IB));
			::ReleaseDC(NULL, hDC);
		}
	}
}
