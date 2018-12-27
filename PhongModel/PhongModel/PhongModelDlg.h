
// PhongModelDlg.h : ͷ�ļ�
//

#pragma once

// CPhongModelDlg �Ի���
class CPhongModelDlg : public CDialogEx
{
// ����
public:
	CPhongModelDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONGMODEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//��Դ����
	int source_x;
	int source_y;
	int source_z;
	//�������ĵ�����
	int centerx;
	int centery;
	int centerz;
	int radius;
	// ����ָ��
	int n;
	//���淴��ϵ��
	double ks;
	// ������ϵ��
	double kd;
	// �����ⷴ��ϵ��
	double ka;

	afx_msg void OnClickedPaint();
};
