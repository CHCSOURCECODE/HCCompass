// HCCompassTestMFCWMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HCCompassTestMFCWM.h"
#include "HCCompassTestMFCWMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHCCompassTestMFCWMDlg �Ի���

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


// CHCCompassTestMFCWMDlg ��Ϣ�������

BOOL CHCCompassTestMFCWMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	/*                   �������                    */
	/*************************************************/
	HRESULT hr = S_OK;
	if (FAILED(m_HCCompass.CreateInstance(__uuidof(Compass)) 
		|| m_HCCompass == NULL))
	{
		MessageBox(_T("Error"), _T("�������ʧ��"), MB_ICONERROR);
		return FALSE;
	}

	SetTimer(1, 1000, NULL);
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_HCCompass->IsLaserOpen() == VARIANT_TRUE)
	{
		if (m_HCCompass->CloseLaser() == VARIANT_TRUE)
		{
			AfxMessageBox(_T("�رռ���ɹ�"));
			SetDlgItemText(IDC_BUTTON1, _T("�򿪼���"));
		}
		else
		{
			AfxMessageBox(_T("�رռ���ʧ��"));
		}
	}
	else
	{
		if (m_HCCompass->OpenLaser() == VARIANT_TRUE)
		{
			AfxMessageBox(_T("�򿪼���ɹ�"));
			SetDlgItemText(IDC_BUTTON1, _T("�رռ���"));
		}
		else
		{
			AfxMessageBox(_T("�򿪼���ʧ��"));
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
