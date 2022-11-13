
// MFC_11_03View.h: CMFC1103View 클래스의 인터페이스
//

#pragma once
class info {
public:
	int x;
	int y;
	int bw; //볼 색깔

	info() { x = -1; y = -1; bw = -1; }

	info(int dx, int dy, int dbw) {
		x = dx; y = dy; bw = dbw;
	}
};

#include <vector>
#include <iostream>
using namespace std;

class CMFC1103View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC1103View() noexcept;
	DECLARE_DYNCREATE(CMFC1103View)

// 특성입니다.
public:
	CMFC1103Doc* GetDocument() const;

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
	virtual ~CMFC1103View();
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
	vector<info> v;
	enum color { BLACK, WHITE };
	enum run { STOP,START };
	int running;
	int arr[30][30];
	int gap;
	int sc;
	int rangeover;
	int CheckArray();
};

#ifndef _DEBUG  // MFC_11_03View.cpp의 디버그 버전
inline CMFC1103Doc* CMFC1103View::GetDocument() const
   { return reinterpret_cast<CMFC1103Doc*>(m_pDocument); }
#endif

