// HCCompassTestMFCWMDlg.h : 头文件
//

#pragma once

// CHCCompassTestMFCWMDlg 对话框
class CHCCompassTestMFCWMDlg : public CDialog
{
// 构造
public:
	CHCCompassTestMFCWMDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CHCCompassTestMFCWMDlg();

// 对话框数据
	enum { IDD = IDD_HCCOMPASSTESTMFCWM_DIALOG };


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	virtual afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	/******************************/
	/*     接收机控制组件         */
	/******************************/
	ICompassPtr   m_HCCompass;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
