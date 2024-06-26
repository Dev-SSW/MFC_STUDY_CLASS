
// MFC_Task_2View.h: CMFCTask2View 클래스의 인터페이스
//

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CMFCTask2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCTask2View() noexcept;
	DECLARE_DYNCREATE(CMFCTask2View)

// 특성입니다.
public:
	CMFCTask2Doc* GetDocument() const;

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
	virtual ~CMFCTask2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Blue();
	afx_msg void Green();
	afx_msg void Red();

	vector<CPoint> ball;
	vector<double> ballsize;
	vector<int> ballcolor;
	
	vector<CPoint> rect;
	vector<double> rectsize;
	vector<int> rectcolor;
	
	int DrawERun;
	int DrawRRun;

	int currentballcolor;
	int currentrectcolor;
	
	int count;
	int count2;
	
	int run;
	
	int run0[200]; //밑
	int run1[200]; //위
	int run2[200]; //오른쪽
	int run3[200]; //왼쪽

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnFast();

	afx_msg void OnR();
	afx_msg void OnG();
	afx_msg void OnB();
};

#ifndef _DEBUG  // MFC_Task_2View.cpp의 디버그 버전
inline CMFCTask2Doc* CMFCTask2View::GetDocument() const
   { return reinterpret_cast<CMFCTask2Doc*>(m_pDocument); }
#endif

