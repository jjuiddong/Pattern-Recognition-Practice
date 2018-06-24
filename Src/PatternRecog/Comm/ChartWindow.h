#pragma once


struct sChartConfig
{
	float xRangeMin;
	float xRangeMax;
	float yRangeMin;
	float yRangeMax;
	float xOrigin;
	float yOrigin;
};

struct Vector2 {
	float x, y;
};

struct Mat2x2 {
	float m11, m12, m21, m22;
};


// CChartWindow view
class CChartWindow : public CScrollView
{
public:
	CChartWindow();
	virtual ~CChartWindow();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void OnInitialUpdate();     // first time after construct
	void SetConfig(const sChartConfig &config);
	void DrawChart(const vector<Vector2> &data);


protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view


public:
	sChartConfig m_config;
	vector<Vector2> m_data;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};



inline void CChartWindow::SetConfig(const sChartConfig &config)
{
	m_config = config;
}


inline void CChartWindow::DrawChart(const vector<Vector2> &data)
{
	m_data = data;
}
