
// Change_Bmp_JpgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Change_Bmp_Jpg.h"
#include "Change_Bmp_JpgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CChange_Bmp_JpgDlg �Ի���




CChange_Bmp_JpgDlg::CChange_Bmp_JpgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChange_Bmp_JpgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChange_Bmp_JpgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILEPATH, m_editFilePath);
	DDX_Control(pDX, IDC_COMBO_CHANGEMODE, m_boxChangeMode);
	DDX_Control(pDX, IDC_EDIT_DESTPATH, m_editOutFilePath);
	DDX_Control(pDX, IDC_COMBO_VALUE, m_qualityValue);
}

BEGIN_MESSAGE_MAP(CChange_Bmp_JpgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE, &CChange_Bmp_JpgDlg::OnBnClickedButtonChoose)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChange_Bmp_JpgDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSEOUT, &CChange_Bmp_JpgDlg::OnBnClickedButtonChooseout)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANGEMODE, &CChange_Bmp_JpgDlg::OnCbnSelchangeComboChangemode)
END_MESSAGE_MAP()


// CChange_Bmp_JpgDlg ��Ϣ�������

BOOL CChange_Bmp_JpgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������




	m_boxChangeMode.AddString(_T("JPGת��ΪBMP"));
	m_boxChangeMode.AddString(_T("BMPת��ΪJPG"));
	m_boxChangeMode.SetCurSel(0);

	CString strText;

	for(int i = 0; i < 101; i++)
	{
		strText.Format(_T("%d"), i);
		m_qualityValue.AddString(strText);
	}
	m_qualityValue.SetCurSel(100);

	GetDlgItem(IDC_STATIC_TEXT)->ShowWindow(SW_HIDE);
	m_qualityValue.ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChange_Bmp_JpgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChange_Bmp_JpgDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChange_Bmp_JpgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChange_Bmp_JpgDlg::OnBnClickedButtonChoose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("bin"),NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T(" Files (*.jpg)|*.jpg|(*.bmp)|*.bmp|All Files (*.*)|*.*||"),this);
	if (dlg.DoModal() == IDOK)
	{
		m_strPath = dlg.GetPathName();  //��ȡ�ļ�������·��
		m_editFilePath.SetWindowText(m_strPath);
	}
	else
	{
		return;
	}
}

void CChange_Bmp_JpgDlg::OnBnClickedButtonChooseout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE, _T("bin"),NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T(" Files (*.jpg)|*.jpg|(*.bmp)|*.bmp|All Files (*.*)|*.*||"),this);
	if (dlg.DoModal() == IDOK)
	{
		m_strOutPath = dlg.GetPathName();  //��ȡ�ļ�������·��
		m_editOutFilePath.SetWindowText(m_strOutPath);
	}
	else
	{
		return;
	}
}

void CChange_Bmp_JpgDlg::OnBnClickedButtonChange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int iSelect = m_boxChangeMode.GetCurSel();

	CString strInPath; 
	m_editFilePath.GetWindowText(strInPath);
	CString strOutPath;
	m_editOutFilePath.GetWindowText(strOutPath);
	CString strCheck1 = strInPath.Right(3);
	CString strCheck2 = strOutPath.Right(3);
	strCheck1.MakeUpper();
	strCheck2.MakeUpper();

	int iRet = 0;
	if(strInPath == _T("") || strOutPath == _T(""))
	{
		AfxMessageBox(_T("�ļ�·������Ϊ��"));
		return;
	}
	if(0 == iSelect && strCheck1 == _T("JPG") && strCheck2 == _T("BMP")) //���ж��ļ���׺
	{
		//jpgתbmp
		iRet = m_jpgToBmp.LoadJpegFile(strInPath.GetBuffer(0), strOutPath.GetBuffer(0));
	}
	else if(1 == iSelect && strCheck1 == _T("BMP") && strCheck2 == _T("JPG")) //���ж��ļ���׺
	{
		//bmpתjpg
		int iValue = m_qualityValue.GetCurSel();
		iRet = m_bmpToJpg.BMPToJPG(strInPath.GetBuffer(0), strOutPath.GetBuffer(0), iValue);
	}
	else
	{
		AfxMessageBox(_T("����ת�������Ƿ���ȷ"));
		return;
	}


	strInPath.ReleaseBuffer();
	strOutPath.ReleaseBuffer();

	if(iRet == 1)
	{
		AfxMessageBox(_T("ת���ɹ���"));
	}
	else
	{
		AfxMessageBox(_T("ת��ʧ�ܣ�"));
	}
}



void CChange_Bmp_JpgDlg::OnCbnSelchangeComboChangemode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iSelect = m_boxChangeMode.GetCurSel();
	
	if(0 == iSelect)
	{
		GetDlgItem(IDC_STATIC_TEXT)->ShowWindow(SW_HIDE);
		m_qualityValue.ShowWindow(SW_HIDE);
	}
	else if(1 == iSelect)
	{
		GetDlgItem(IDC_STATIC_TEXT)->ShowWindow(SW_SHOW);
		m_qualityValue.ShowWindow(SW_SHOW);
	}

}
