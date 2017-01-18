// HCCompassTestMFCWMDlg.h : ͷ�ļ�
//

#pragma once

// CHCCompassTestMFCWMDlg �Ի���
class CHCCompassTestMFCWMDlg : public CDialog
{
// ����
public:
	CHCCompassTestMFCWMDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CHCCompassTestMFCWMDlg();

// �Ի�������
	enum { IDD = IDD_HCCOMPASSTESTMFCWM_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	virtual afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	/******************************/
	/*     ���ջ��������         */
	/******************************/
	ICompassPtr   m_HCCompass;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
#if defined(_DEVICE_RESOLUTION_AWARE) && !defined(WIN32_PLATFORM_WFSP)
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	double m_angleX;
	double m_angleY;
	double m_direction;
private:
	long m_speedX;
	long m_speedY;
	long m_speedZ;
};
