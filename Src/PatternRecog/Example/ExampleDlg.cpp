
#include "stdafx.h"
#include "Example.h"
#include "ExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CExampleDlg::CExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CExampleDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CExampleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


Vector2 Avr(const vector<Vector2> &ar)
{
	Vector2 ret = { 0, 0 };
	for (auto &v : ar)
	{
		ret.x += v.x;
		ret.y += v.y;
	}

	ret.x /= ar.size();
	ret.y /= ar.size();
	return ret;
}


Mat2x2 Covariance(const vector<Vector2> &ar, const Vector2 &avr)
{
	Mat2x2 ret = { 0,0,0,0 };
	if (ar.size()<2)
		return ret;

	for (auto &v : ar)
	{
		Vector2 v1 = { v.x - avr.x, v.y - avr.y };
		ret.m11 += v1.x * v1.x;
		ret.m22 += v1.y * v1.y;
		ret.m12 += v1.x * v1.y;
		ret.m21 += v1.y * v1.x;
	}

	ret.m11 /= (ar.size() - 1);
	ret.m12 /= (ar.size() - 1);
	ret.m21 /= (ar.size() - 1);
	ret.m22 /= (ar.size() - 1);
	return ret;
}


BOOL CExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetWindowTextA(m_hWnd, "Example");

	CChartWindow *chartWnd = new CChartWindow();
	if (chartWnd->Create(NULL, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER
		, CRect(0, 0, 500, 500), this, 10))
	{
		chartWnd->OnInitialUpdate();
		chartWnd->ShowWindow(SW_SHOW);

		sChartConfig config;
		config.xRangeMin = -10;
		config.xRangeMax = 20;
		config.yRangeMin = -10;
		config.yRangeMax = 20;
		config.xOrigin = 0;
		config.yOrigin = 0;
		chartWnd->SetConfig(config);

		vector<Vector2> data1;
		data1.push_back({ 1, 2 });
		data1.push_back({ 3, 1 });
		data1.push_back({ 5, 2 });
		data1.push_back({ 3, 3 });

		vector<Vector2> data2;
		data2.push_back({ 6, 6 });
		data2.push_back({ 8, 5 });
		data2.push_back({ 10, 6 });
		data2.push_back({ 8, 7 });

		Vector2 m1 = Avr(data1);
		Vector2 m2 = Avr(data2);
		Mat2x2 cv1 = Covariance(data1, m1);
		Mat2x2 cv2 = Covariance(data2, m2);

		vector<Vector2> data;
		for (auto &v : data1)
			data.push_back(v);
		for (auto &v : data2)
			data.push_back(v);

		chartWnd->DrawChart(data);
	}

	m_chartWnd = chartWnd;

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExampleDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CExampleDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
