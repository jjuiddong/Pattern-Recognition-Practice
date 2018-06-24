
#include "stdafx.h"
#include "ChartTest.h"
#include "ChartTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChartTestDlg dialog
CChartTestDlg::CChartTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHARTTEST_DIALOG, pParent)
	, m_chartWnd(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChartTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChartTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CChartTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChartTestDlg::OnBnClickedCancel)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CChartTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CChartWindow *chartWnd = new CChartWindow();
	if (chartWnd->Create(NULL, NULL, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER
		, CRect(0, 0, 500, 500), this, 10))
	{
		chartWnd->OnInitialUpdate();
		chartWnd->ShowWindow(SW_SHOW);

		sChartConfig config;
		config.xRangeMin = -10;
		config.xRangeMax = 100;
		config.yRangeMin = -10;
		config.yRangeMax = 100;
		config.xOrigin = 0;
		config.yOrigin = 0;
		chartWnd->SetConfig(config);

		vector<Vector2> data;
		data.push_back({ 10, 10 });
		data.push_back({ 20, 20 });
		data.push_back({ 40, 20 });
		data.push_back({ 40, 50 });
		chartWnd->DrawChart(data);
	}

	m_chartWnd = chartWnd;

	return TRUE;
}

void CChartTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CChartTestDlg::OnPaint()
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

HCURSOR CChartTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChartTestDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}


void CChartTestDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CChartTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_chartWnd)
		m_chartWnd->OnInitialUpdate();	
}
