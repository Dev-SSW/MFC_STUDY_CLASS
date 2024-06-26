
// MFC_TASK_09_22View.h: CMFCTASK0922View 클래스의 인터페이스
//

#pragma once


class CMFCTASK0922View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCTASK0922View() noexcept;
	DECLARE_DYNCREATE(CMFCTASK0922View)

// 특성입니다.
public:
	CMFCTASK0922Doc* GetDocument() const;

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
	virtual ~CMFCTASK0922View();
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
	CPoint ball[200];
	int count;
	int run;
	int run0[200]; //밑
	int run1[200]; //위
	int run2[200]; //오른쪽
	int run3[200]; //왼쪽
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // MFC_TASK_09_22View.cpp의 디버그 버전
inline CMFCTASK0922Doc* CMFCTASK0922View::GetDocument() const
   { return reinterpret_cast<CMFCTASK0922Doc*>(m_pDocument); }
#endif

