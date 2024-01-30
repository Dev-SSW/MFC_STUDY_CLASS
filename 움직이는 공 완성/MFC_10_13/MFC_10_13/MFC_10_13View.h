
// MFC_10_13View.h: CMFC1013View 클래스의 인터페이스
//
class ballinfo {
public:
	int x, y;
	double r;
	ballinfo() { x = y = -1; r = -1; }
	ballinfo(int a, int b, double c) { x = a; y = b; r = c; }
};
#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class CMFC1013View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC1013View() noexcept;
	DECLARE_DYNCREATE(CMFC1013View)

// 특성입니다.
public:
	CMFC1013Doc* GetDocument() const;

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
	virtual ~CMFC1013View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	vector<ballinfo> v;
	int currentcolor;
	vector<int> BallColor;
	COLORREF color[3] = { RGB(255,0,0) , RGB(0,255,0) , RGB(0,0,255) };
	int run;
	vector<int> BHx;
	vector<int> BHy;
	int speed1;
	int speed2;
	int speed3;
	int SelectBH;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRed();
	afx_msg void OnGreen();
	afx_msg void OnBlue();
};

#ifndef _DEBUG  // MFC_10_13View.cpp의 디버그 버전
inline CMFC1013Doc* CMFC1013View::GetDocument() const
   { return reinterpret_cast<CMFC1013Doc*>(m_pDocument); }
#endif

