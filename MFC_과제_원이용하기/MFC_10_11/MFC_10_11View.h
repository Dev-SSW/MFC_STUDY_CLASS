
// MFC_10_11View.h: CMFC1011View 클래스의 인터페이스
//
#pragma once
#include <vector>;
#include <iostream>;
#include <algorithm>;
using namespace std;

class CMFC1011View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC1011View() noexcept;
	DECLARE_DYNCREATE(CMFC1011View)

// 특성입니다.
public:
	CMFC1011Doc* GetDocument() const;

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
	virtual ~CMFC1011View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
    vector<CPoint> Ball;
	vector<double> BallSize;
	vector<int> BallColor;
	vector<int> BHx;
	vector<int> BHy;
	int speed1;
	int speed2;
	int speed3;
	int SelectBH;

	int run;
	int count;
	int currentcolor;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRede();
	afx_msg void OnGreene();
	afx_msg void OnBluee();
};

#ifndef _DEBUG  // MFC_10_11View.cpp의 디버그 버전
inline CMFC1011Doc* CMFC1011View::GetDocument() const
   { return reinterpret_cast<CMFC1011Doc*>(m_pDocument); }
#endif

