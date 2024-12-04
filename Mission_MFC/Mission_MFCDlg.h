
// Mission_MFCDlg.h : header file
//

#pragma once
#include <opencv2/opencv.hpp>

// CMissionMFCDlg dialog
class CMissionMFCDlg : public CDialogEx
{
// 이미지 생성 변수 선언
private:
	CImage m_image;
	BOOL valiImagPos(int x, int y);
	int m_nCircleCount; 
	int centerX;  
	int centerY;
	CEdit m_editCoord; 
	CStatic m_picture_control;
// Construction
public:
	CMissionMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	void UpdateDisplay();
	void UpdateCirclePosition(int nX, int nY, int nRadius, int nGray);
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	afx_msg void OnEnChangeEditCount();
	afx_msg void OnStnClickedStaticImage();
	afx_msg void OnEnChangeEditXy();
	bool LoadImageFile(cv::Mat& matImage);
	void FindCircleXY(cv::Mat& matImage);
	void UpdateImageDlg(cv::Mat& matImage);
};
