
// 2020110223View.h: CMy2020110223View 클래스의 인터페이스
//

#pragma once
class Ball {
public:
	int x, y;
	double r;
	int color;
	Ball() { x = -1; y = -1; r = 0.0; color = 0; }
	Ball(int ix, int iy, double ir, int icolor)
	{
		x = ix; y = iy; r = ir; color = icolor;
	}
};
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class CMy2020110223View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy2020110223View() noexcept;
	DECLARE_DYNCREATE(CMy2020110223View)

// 특성입니다.
public:
	CMy2020110223Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy2020110223View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void Onrede();
	afx_msg void Ongreene();
	afx_msg void Onbluee();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	vector<Ball> ball;
	vector<int> rect;
	COLORREF bc[3] = { RGB(255,0,0) , RGB(0,255,0) , RGB(0,0,255) };
	int currentcolor;
	
	int run;
	
	int guri;
	int vi;
	int vj;


	bool first;
	int rx, ry ,rs ,re;
	afx_msg void Ondele();
};

#ifndef _DEBUG  // 2020110223View.cpp의 디버그 버전
inline CMy2020110223Doc* CMy2020110223View::GetDocument() const
   { return reinterpret_cast<CMy2020110223Doc*>(m_pDocument); }
#endif

