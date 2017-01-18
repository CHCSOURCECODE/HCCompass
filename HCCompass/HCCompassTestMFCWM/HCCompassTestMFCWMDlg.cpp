// HCCompassTestMFCWMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HCCompassTestMFCWM.h"
#include "HCCompassTestMFCWMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHCCompassTestMFCWMDlg 对话框

CHCCompassTestMFCWMDlg::CHCCompassTestMFCWMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHCCompassTestMFCWMDlg::IDD, pParent)
	, m_angleX(0)
	, m_angleY(0)
	, m_direction(0)
	, m_speedX(0)
	, m_speedY(0)
	, m_speedZ(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHCCompassTestMFCWMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_angleX);
	DDX_Text(pDX, IDC_EDIT2, m_angleY);
	DDX_Text(pDX, IDC_EDIT3, m_direction);
	DDX_Text(pDX, IDC_EDIT4, m_speedX);
	DDX_Text(pDX, IDC_EDIT5, m_speedY);
	DDX_Text(pDX, IDC_EDIT6, m_speedZ);
}

BEGIN_MESSAGE_MAP(CHCCompassTestMFCWMDlg, CDialog)
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	ON_WM_SIZE()
#endif
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CHCCompassTestMFCWMDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CHCCompassTestMFCWMDlg 消息处理程序

BOOL CHCCompassTestMFCWMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	EnableAutomation();
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	TCHAR szPath[MAX_PATH] = {0};
	if (::GetModuleFileName(NULL, szPath, MAX_PATH) == 0)
		return FALSE;

	CString strDllPathName;
	strDllPathName = szPath;
	strDllPathName = strDllPathName.Left(strDllPathName.ReverseFind(_T('\\')) + 1);
	strDllPathName += _T("HCCompass.dll");
	
	HINSTANCE hHandle = NULL;
	hHandle = ::LoadLibrary(strDllPathName);
	if (hHandle == NULL)
		return FALSE;

	FARPROC proc = ::GetProcAddress(hHandle, _T("DllRegisterServer"));
	if (proc != NULL)
	{
		proc();
	}
	::FreeLibrary(hHandle);
	hHandle = NULL;

	/*************************************************/
	/*                   创建组件                    */
	/*************************************************/
	HRESULT hr = S_OK;
	if (FAILED(m_HCCompass.CreateInstance(__uuidof(Compass)) 
		|| m_HCCompass == NULL))
	{
		MessageBox(_T("Error"), _T("组件创建失败"), MB_ICONERROR);
		return FALSE;
	}

	SetTimer(1, 1000, NULL);
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
void CHCCompassTestMFCWMDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? 
			MAKEINTRESOURCE(IDD_HCCOMPASSTESTMFCWM_DIALOG_WIDE) : 
			MAKEINTRESOURCE(IDD_HCCOMPASSTESTMFCWM_DIALOG));
	}
}
#endif


void CHCCompassTestMFCWMDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_HCCompass->IsLaserOpen() == VARIANT_TRUE)
	{
		if (m_HCCompass->CloseLaser() == VARIANT_TRUE)
		{
			AfxMessageBox(_T("关闭激光成功"));
			SetDlgItemText(IDC_BUTTON1, _T("打开激光"));
		}
		else
		{
			AfxMessageBox(_T("关闭激光失败"));
		}
	}
	else
	{
		if (m_HCCompass->OpenLaser() == VARIANT_TRUE)
		{
			AfxMessageBox(_T("打开激光成功"));
			SetDlgItemText(IDC_BUTTON1, _T("关闭激光"));
		}
		else
		{
			AfxMessageBox(_T("打开激光失败"));
		}
	}
	
}

void CHCCompassTestMFCWMDlg::OnTimer( UINT_PTR nIDEvent )
{
	m_HCCompass->GetLaserDip(&m_angleX, &m_angleY);
	m_HCCompass->GetDirection(&m_direction);
	m_HCCompass->GetAngularSpeed(&m_speedX, &m_speedY, &m_speedZ);

	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

CHCCompassTestMFCWMDlg::~CHCCompassTestMFCWMDlg()
{
	if (m_HCCompass->IsLaserOpen() == VARIANT_TRUE)
	{
		m_HCCompass->CloseLaser();
	}

}
