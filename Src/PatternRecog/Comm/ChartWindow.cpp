
#include "stdafx.h"
#include "ChartWindow.h"

// CChartWindow
CChartWindow::CChartWindow()
{

}

CChartWindow::~CChartWindow()
{
}


BEGIN_MESSAGE_MAP(CChartWindow, CScrollView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CChartWindow drawing

void CChartWindow::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 10;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// 그래프 출력.
void CChartWindow::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	const float xr = abs(m_config.xRangeMax - m_config.xRangeMin);
	const float yr = abs(m_config.yRangeMax - m_config.yRangeMin);
	const float xu = rect.Width() / xr;
	const float yu = rect.Height() / yr;

	// draw origin line
	{
		const float orig_x = (m_config.xOrigin - m_config.xRangeMin) * xu;
		const float orig_y = (m_config.yOrigin - m_config.yRangeMin) * xu;
		pDC->MoveTo({ (int)orig_x, (int)rect.Height() });
		pDC->LineTo({ (int)orig_x, 0 });
		pDC->MoveTo({ 0, rect.Height() - (int)orig_y });
		pDC->LineTo({ rect.Width(), rect.Height() - (int)orig_y });

		// draw origin coordinate
		wchar_t text[64];
		wsprintf(text, L"%d, %d", (int)m_config.xOrigin, (int)m_config.yOrigin);
		pDC->DrawText(text
			, CRect((int)orig_x + 3, rect.Height() - (int)orig_y + 3
				, (int)orig_x + 30
				, rect.Height() - (int)orig_y + 30), DT_LEFT);
	}

	// draw point
	for (auto &pos : m_data)
	{
		const float x = (pos.x - m_config.xRangeMin) * xu;
		const float y = (pos.y - m_config.yRangeMin) * xu;
		const int tx = (int)x;
		const int ty = rect.Height() - (int)y;

		pDC->Ellipse(CRect(tx-5, ty-5, tx+5, ty+5));

		wchar_t text[64];
		wsprintf(text, L"%d, %d", (int)pos.x, (int)pos.y);
		pDC->DrawText(text, CRect(tx + 3, ty + 3, tx + 100, ty + 30), DT_LEFT);
	}
}


// CChartWindow diagnostics

#ifdef _DEBUG
void CChartWindow::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CChartWindow::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


void CChartWindow::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
}


BOOL CChartWindow::OnEraseBkgnd(CDC* pDC)
{
	//return CScrollView::OnEraseBkgnd(pDC); 백그라운드 화면을 갱신하지 않는다.
	return TRUE;
}
