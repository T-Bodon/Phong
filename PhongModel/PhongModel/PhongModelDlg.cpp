#pragma once
// PhongModelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PhongModel.h"
#include "PhongModelDlg.h"
#include "afxdialogex.h"
#include"renderer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPhongModelDlg 对话框



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


// CPhongModelDlg 消息处理程序

BOOL CPhongModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPhongModelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPhongModelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CPhongModelDlg::OnClickedPaint()
{
	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int IPR = 192, IPG = 0, IPB = 0;//光源光强
	int IAR = 64, IAG =0, IAB = 0;//环境光强
	Vector V = Vector(0, 0,1);
	
	CRect rect;
	GetDlgItem(IDC_PIC)->GetWindowRect(rect);
	CPoint pt = rect.CenterPoint();
	//(centerx,centery,centerz)球心坐标
	centerx = pt.x;
	centery = pt.y;
	ks = 1 - kd;
	Vector L0 = Vector(-source_x, -source_y, -source_z);
	Vector L = numbermulptiply(1 / mole(L0), L0);//把光线向量归一化

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
			int IR, IG, IB;    //像素点的颜色
			double cosi = cos(L, N);      //光线和法向量夹角余弦
			if (cosi>0.0)  //光线能直接到达该点
			{
				double HN = vectormultiply(H, N);
				double HN_n = pow(HN, n);
				IR = IAR*ka + IPR*kd*cosi + IPR*ks*HN_n;
				IG = IAG*ka + IPG*kd*cosi+ IPG*ks*HN_n;
				IB = IAB*ka + IPB*kd*cosi + IPB*ks*HN_n;
			}
			else           //光线不能到达该点
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
