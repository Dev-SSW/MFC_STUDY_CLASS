
// MFC_10_18View.cpp: CMFC1018View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_10_18.h"
#endif

#include "MFC_10_18Doc.h"
#include "MFC_10_18View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1018View

IMPLEMENT_DYNCREATE(CMFC1018View, CView)

BEGIN_MESSAGE_MAP(CMFC1018View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFC1018View 생성/소멸

CMFC1018View::CMFC1018View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));

}

CMFC1018View::~CMFC1018View()
{
}

BOOL CMFC1018View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1018View 그리기

void CMFC1018View::OnDraw(CDC* /*pDC*/)
{
	CMFC1018Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/*
	dc.Rectangle(rc.left, rc.bottom, rc.right * 0.1, rc.top);
	dc.Rectangle(rc.right * 0.9, rc.bottom, rc.right, rc.top);
	dc.Rectangle(rc.left, rc.bottom*0.1, rc.right, rc.top);
	dc.Rectangle(rc.left, rc.bottom*0.9, rc.right, rc.bottom);
	*/
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);

	CBrush bsb(RGB(0, 0, 0)) , bsw(RGB(255, 255, 255));
	dc.SelectObject(&bsb);
	dc.Rectangle(0, 0, rc.right, rc.bottom);

	int sw = rc.right / 10, sh = rc.bottom / 10;
	dc.SelectObject(&bsw);
	dc.Rectangle(sw, sh, rc.right - sw, rc.bottom - sh);

	
	for (int i = 0; i < ball.size(); i++) {
		CBrush bs(bc[ball[i].color]);
		dc.SelectObject(&bs);
		dc.Ellipse(ball[i].x - ball[i].r, ball[i].y - ball[i].r, ball[i].x + ball[i].r, ball[i].y + ball[i].r);
		CString str;
		str.Format(L"%d", ball[i].number);
		CRect trc(ball[i].x - ball[i].r, ball[i].y - ball[i].r, ball[i].x + ball[i].r, ball[i].y + ball[i].r);
		dc.SetBkMode(TRANSPARENT); //글자가 어울림이 될 것인지 아닌지
		dc.DrawText(str,trc, (DT_CENTER | DT_VCENTER | DT_SINGLELINE ));
	}
}


// CMFC1018View 인쇄

BOOL CMFC1018View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1018View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1018View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1018View 진단

#ifdef _DEBUG
void CMFC1018View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1018View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1018Doc* CMFC1018View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1018Doc)));
	return (CMFC1018Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1018View 메시지 처리기


void CMFC1018View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int count = 0;
	int number = 0;
	if (ball.size()>=0) {
		number = ball.size() + 1; // if ball size가 하나 이상일때
	}
	while (count < 10) {
		int px = rand() % 500 +20;
		int py = rand() % 400 +20;
		int coll = 0;
		for (int i = 0; i < ball.size(); i++)
		{
			int xx = ball[i].x - px;
			int yy = ball[i].y - py;
			if (sqrt(xx * xx + yy * yy) <= ball[i].r + 20)
			{
				coll = 1; //충돌하면 생성 x
			}
		}
		if (coll == 1) { continue; }
		int tx, ty;
		tx = rand() % 3 + 1;
		ty = rand() % 3 + 1;
		ball.push_back(Ball(number + count , px, py, 20, tx, ty, rand() % 3));
		count++;
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
