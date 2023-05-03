
// MFC_10_18View.h: CMFC1018View 클래스의 인터페이스
//

#pragma once
class Ball {
public:
	int number;
	int x, y;
	double r;
	int dx, dy;
	int color;
	Ball() { number = -1;  x = -1; y = -1; r = 0.0; dx = 0; dy = 0; color = 0; }
	Ball(int inumber,int ix, int iy, double ir, int idx, int idy, int icolor)
	{
		number = inumber; x = ix; y = iy; r = ir; dx = idx; dy = idy; color = icolor;
	}
};


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;


class CMFC1018View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC1018View() noexcept;
	DECLARE_DYNCREATE(CMFC1018View)

// 특성입니다.
public:
	CMFC1018Doc* GetDocument() const;

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
	virtual ~CMFC1018View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	vector<Ball> ball;
	enum { RED,GREEN,BLUE};
	COLORREF bc[3] = { RGB(255,0,0) , RGB(0,255,0) , RGB(0,0,255) };
};

#ifndef _DEBUG  // MFC_10_18View.cpp의 디버그 버전
inline CMFC1018Doc* CMFC1018View::GetDocument() const
   { return reinterpret_cast<CMFC1018Doc*>(m_pDocument); }
#endif

