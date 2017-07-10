
// Change_Bmp_JpgDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "JpgToBmp.h"
#include "BmpToJpg.h"

// CChange_Bmp_JpgDlg �Ի���
class CChange_Bmp_JpgDlg : public CDialog
{
// ����
public:
	CChange_Bmp_JpgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHANGE_BMP_JPG_DIALOG };

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
	CEdit m_editFilePath;
	CEdit m_editOutFilePath;

	CComboBox m_boxChangeMode;


	afx_msg void OnBnClickedButtonChoose();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonChooseout();
	







private:
	CString	m_strPath;
	CString m_strOutPath;
	CJpgToBmp	m_jpgToBmp;
	CBmpToJpg	m_bmpToJpg;
	
public:
	CComboBox m_qualityValue;
	afx_msg void OnCbnSelchangeComboChangemode();
};
