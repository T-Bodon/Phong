
// PhongModelDlg.h : 头文件
//

#pragma once

// CPhongModelDlg 对话框
class CPhongModelDlg : public CDialogEx
{
// 构造
public:
	CPhongModelDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONGMODEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//光源坐标
	int source_x;
	int source_y;
	int source_z;
	//绘制中心的坐标
	int centerx;
	int centery;
	int centerz;
	int radius;
	// 反射指数
	int n;
	//镜面反射系数
	double ks;
	// 漫反射系数
	double kd;
	// 环境光反射系数
	double ka;

	afx_msg void OnClickedPaint();
};
