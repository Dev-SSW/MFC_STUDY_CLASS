
// MFC_exam_ex22View.h: CMFCexamex22View 클래스의 인터페이스
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


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

class CMFCexamex22View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCexamex22View() noexcept;
	DECLARE_DYNCREATE(CMFCexamex22View)

// 특성입니다.
public:
	CMFCexamex22Doc* GetDocument() const;

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
	virtual ~CMFCexamex22View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRed();
	afx_msg void OnGreen();
	afx_msg void OnBlue();
	afx_msg void Onlined();
	afx_msg void Onrandd();
	afx_msg void Onmoveball();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	vector<Ball> ball;
	COLORREF bc[3] = { RGB(255,0,0) , RGB(0,255,0) , RGB(0,0,255) };

	vector<int> BHx;
	vector<int> BHy;

	int bh;
	int currentcolor;
	int run;

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void Onstop();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFC_exam_ex22View.cpp의 디버그 버전
inline CMFCexamex22Doc* CMFCexamex22View::GetDocument() const
   { return reinterpret_cast<CMFCexamex22Doc*>(m_pDocument); }
#endif

