
// Mission_MFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Mission_MFC.h"
#include "Mission_MFCDlg.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CMissionMFCDlg dialog



CMissionMFCDlg::CMissionMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMissionMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMissionMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMissionMFCDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMissionMFCDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMissionMFCDlg::OnBnClickedBtnOpen)
	ON_EN_CHANGE(IDC_EDIT_COUNT, &CMissionMFCDlg::OnEnChangeEditCount)
	ON_STN_CLICKED(IDC_STATIC_IMAGE, &CMissionMFCDlg::OnStnClickedStaticImage)
	ON_EN_CHANGE(IDC_EDIT_XY, &CMissionMFCDlg::OnEnChangeEditXy)
END_MESSAGE_MAP()


// CMissionMFCDlg message handlers

BOOL CMissionMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMissionMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMissionMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMissionMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//
void CMissionMFCDlg::OnBnClickedBtnDraw()
{
	//이미지 크기 설정
	int nWidth = 640;
	int nHeight = 480;
	int nBPP = 8;

	m_image.Destroy(); // 기존 이미지 해제
	m_image.Create(nWidth, -nHeight, nBPP); // 이미지 생성
	if (nBPP == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}
	
	// 이미지의 첫 번쨰 포인트를 가져온다.
	int nPitch = m_image.GetPitch();
	
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

		int nRadius = rand() % 50 + 10; // 10~60 크기 랜덤
		int nX = rand() % (nWidth - nRadius * 2);
		int nY = rand() % (nHeight - nRadius * 2);
		int nGray = rand() % 128; // 회색 음영 랜덤(어두운 계열)
		
		drawCircle(fm, nX, nY, nRadius, nGray);

	UpdateDisplay();
}

// Draw한 이미지 저장하기
void CMissionMFCDlg::OnBnClickedBtnAction()

{
	// CEdit 컨트롤에서 입력된 값을 가져옴
	CString strCount;
	CEdit* pEditCount = (CEdit*)GetDlgItem(IDC_EDIT_COUNT); // CEdit 컨트롤 ID가 IDC_EDIT_COUNT일 경우
	pEditCount->GetWindowText(strCount); // 텍스트 가져오기

	// 개수 입력 칸 공백 시 메시지 출력
	if (strCount.IsEmpty()) {
		AfxMessageBox(_T("아래 빈칸에 숫자를 입력해주세요."));
		return; 
	}

	// 입력값 숫자로 변환
	int m_nCircleCount = _ttoi(strCount); // CString을 int로 변환

	// 원의 개수만큼 반복
	for (int i = 0; i < m_nCircleCount; i++) {
		// 랜덤 값으로 원의 위치, 크기, 회색 음영 생성
		int nRadius = rand() % 50 + 10; // 10~60 크기 랜덤
		int nX = rand() % (m_image.GetWidth() - nRadius * 2);
		int nY = rand() % (m_image.GetHeight() - nRadius * 2);
		int nGray = rand() % 128; // 회색 음영 랜덤(어두운계열)

		// 원 위치 업데이트 및 화면에 출력
		UpdateCirclePosition(nX, nY, nRadius, nGray);

		// 파일 이름 생성(현재 시간)
		CString strFileName;
		SYSTEMTIME st;
		GetLocalTime(&st);
		strFileName.Format(_T("c:\\image\\save_%04d%02d%02d%02d%02d%02d.bmp"),
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		// 이미지 저장
		m_image.Save(strFileName);

		// 원 그리기 후 잠시 대기 (애니메이션 효과)
		Sleep(1000);
	}
}

// 저장된 이미지 불러오기
void CMissionMFCDlg::OnBnClickedBtnOpen()
{
	// 파일 다이얼로그에서 이미지 파일을 로드하고 OpenCV로 변환
	cv::Mat matImage;

	// 이미지 파일 로드 및 openCV로 변환
	LoadImageFile(matImage);
		
	// 원 찾기 및 원중심, 좌표 찾기
	FindCircleXY(matImage);

	// 처리된 이미지를 Picture Control에 업데이트
	UpdateImageDlg(matImage);
}

// 화면에 이미지 그리기(함수 생성)
void CMissionMFCDlg::UpdateDisplay()
{
	
	// PICTURE CONTROL에 이미지를 표시하는 로직
	CStatic* pStaticCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE); // PICTURE CONTROL 가져오기
	pStaticCtrl->ModifyStyle(0xF, SS_BITMAP);  // PICTURE CONTROL을 비트맵 스타일로 설정

	// 비트맵을 설정하여 PICTURE CONTROL에 이미지 표시
	HBITMAP hBitmap = m_image;  // CImage 객체에서 HBITMAP을 직접 가져옴
	pStaticCtrl->SetBitmap(hBitmap); // PICTURE CONTROL에 비트맵 설정
	Invalidate(); // 다이얼로그를 다시 그리도록 요청
	
}

// 원 위치 업데이트 및 화면에 출력
void CMissionMFCDlg::UpdateCirclePosition(int nX, int nY, int nRadius, int nGray)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 이미지의 배경을 흰색으로 설정(원 지우기)
	memset(fm, 0xff, nWidth * nHeight); // 배경을 흰색으로 설정

	// 새로운 원을 그리기
	drawCircle(fm, nX, nY, nRadius, nGray);

	UpdateDisplay();

}

// 이미지 내에 좌표 존재 여부
BOOL CMissionMFCDlg::valiImagPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));	
}

// 원 그리기
void CMissionMFCDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
}

// 원 안에 픽셀 값 여부 확인
bool CMissionMFCDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;
	
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDit = dX * dX + dY * dY;

	if (dDit < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
}

// Edit Control : 생성할 원 개수 입력
void CMissionMFCDlg::OnEnChangeEditCount()
{
	CString strCount;
	GetDlgItemText(IDC_EDIT_COUNT, strCount);
	m_nCircleCount = _ttoi(strCount); // 문자열을 정수로 변환
}

// Picture Control : image 표시
void CMissionMFCDlg::OnStnClickedStaticImage()
{
	
}

// Edit Control : Center(x,y), Radius 표시
void CMissionMFCDlg::OnEnChangeEditXy()
{

}

// 이미지 파일 로드 및 openCV로 변환
bool CMissionMFCDlg::LoadImageFile(cv::Mat& matImage)
{
	// 파일 다이얼로그 객체 생성(열기 모드)
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK) {
		CString strFilePath = dlg.GetPathName();
		m_image.Destroy(); // 기존 이미지 해제

		// 이미지 불러오기
		if (m_image.Load(strFilePath) == S_OK) {
			// 이미지 파일을 OpenCV 형식으로 변환
			HBITMAP hBitmap = (HBITMAP)m_image.Detach();
			CImage tempImage;
			tempImage.Attach(hBitmap);

			// 이미지를 OpenCV의 Mat 객체로 변환
			int width = tempImage.GetWidth();
			int height = tempImage.GetHeight();
			matImage = cv::Mat(height, width, CV_8UC3);
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					COLORREF color = tempImage.GetPixel(x, y);
					matImage.at<cv::Vec3b>(y, x)[0] = GetBValue(color);
					matImage.at<cv::Vec3b>(y, x)[1] = GetGValue(color);
					matImage.at<cv::Vec3b>(y, x)[2] = GetRValue(color);
				}
			}

			return true;
		}
		else {
			AfxMessageBox(_T("이미지 파일을 불러올 수 없습니다."));
			return false;
		}
	}
	return false;
}

// 원 찾기 및 원중심, 좌표 찾기
void CMissionMFCDlg::FindCircleXY(cv::Mat& matImage)
{
	// 그레이스케일로 변환
	cv::Mat gray;
	cv::cvtColor(matImage, gray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);

	// HoughCircles로 원 찾기
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 50, 20, 0, 0);

	// 원 발견 시 중심 좌표와 반지름 출력
	if (circles.size() > 0) {
		for (size_t i = 0; i < circles.size(); i++) {
			cv::Vec3f c = circles[i];
			int x = cvRound(c[0]);
			int y = cvRound(c[1]);
			int radius = cvRound(c[2]);

			// 원을 원래 이미지에 그리기
			cv::circle(matImage, cv::Point(x, y), radius, cv::Scalar(0, 255, 0), 2); // 초록색 원

			// X 모양의 크기를 반지름에 비례하여 설정
			int lineLength = radius / 5; // 반지름의 1/5 크기로 X 모양 길이 설정

			// 원의 중심에 X 모양 그리기
			cv::line(matImage, cv::Point(x - lineLength, y - lineLength), cv::Point(x + lineLength, y + lineLength), cv::Scalar(0, 0, 255), 2); // 대각선1
			cv::line(matImage, cv::Point(x - lineLength, y + lineLength), cv::Point(x + lineLength, y - lineLength), cv::Scalar(0, 0, 255), 2); // 대각선2

			// 좌표값 텍스트 표시
			std::string text = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
			int baseline = 0;
			cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseline);
			cv::Point textOrigin(x - textSize.width / 2, y - textSize.height - 5);
			cv::putText(matImage, text, textOrigin, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);

			// 원의 중심과 반지름을 edit control에 표시
			CString strMessage;
			strMessage.Format(_T("(%d, %d), %d"), x, y, radius);
			SetDlgItemText(IDC_EDIT_XY, strMessage); // ID가 IDC_EDIT_XY인 Edit Control에 텍스트 표시
		}
	}
	else {
		SetDlgItemText(IDC_EDIT_XY, _T("원 미발견"));
	}
}

// 처리된 이미지를 Picture Control에 업데이트
void CMissionMFCDlg::UpdateImageDlg(cv::Mat& matImage)
{
	// OpenCV로 처리한 이미지를 다시 CImage 객체로 변환
	cv::Mat matImageRGB;
	cv::cvtColor(matImage, matImageRGB, cv::COLOR_BGR2RGB); // OpenCV에서 BGR -> RGB로 변환

	// 이미지 크기와 포맷을 CImage에 맞게 설정
	CImage tempImage;
	int width = matImage.cols;
	int height = matImage.rows;
	tempImage.Destroy();
	tempImage.Create(width, height, 24); // 24비트 컬러 이미지로 생성

	// 이미지를 CImage로 복사
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			cv::Vec3b color = matImageRGB.at<cv::Vec3b>(y, x);
			tempImage.SetPixel(x, y, RGB(color[2], color[1], color[0])); // RGB로 색상 설정
		}
	}

	// PICTURE CONTROL 객체 가져오기
	CStatic* pStaticCtrl = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
	pStaticCtrl->ModifyStyle(0xF, SS_BITMAP);  // PICTURE CONTROL의 비트맵 스타일로 설정 및 준비

	// tempImage에서 비트맵 핸들 분리 및 반환
	HBITMAP hNewBitmap = (HBITMAP)tempImage.Detach();
	pStaticCtrl->SetBitmap(hNewBitmap); // 분리된 비트맵 핸들을 PICTURE CONTROL에 설정 후 표시

	Invalidate();  // 업데이트된 새로운 이미지 표시

}

