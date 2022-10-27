
// MFC_exam_ex22View.cpp: CMFCexamex22View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_exam_ex22.h"
#endif

#include "MFC_exam_ex22Doc.h"
#include "MFC_exam_ex22View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCexamex22View

IMPLEMENT_DYNCREATE(CMFCexamex22View, CView)

BEGIN_MESSAGE_MAP(CMFCexamex22View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(Red, &CMFCexamex22View::OnRed)
	ON_COMMAND(Green, &CMFCexamex22View::OnGreen)
	ON_COMMAND(Blue, &CMFCexamex22View::OnBlue)
	ON_COMMAND(lineD, &CMFCexamex22View::Onlined)
	ON_COMMAND(randD, &CMFCexamex22View::Onrandd)
	ON_COMMAND(moveball, &CMFCexamex22View::Onmoveball)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_COMMAND(stop, &CMFCexamex22View::Onstop)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCexamex22View 생성/소멸

CMFCexamex22View::CMFCexamex22View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	currentcolor = 0;
	run = 0;
	bh = rand() % 8;
}

CMFCexamex22View::~CMFCexamex22View()
{
}

BOOL CMFCexamex22View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCexamex22View 그리기

void CMFCexamex22View::OnDraw(CDC* /*pDC*/)
{
	CMFCexamex22Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	for (int i = 0; i < ball.size(); i++) {
		CBrush bs(bc[ball[i].color]);
		dc.SelectObject(&bs);
		dc.Ellipse(ball[i].x - ball[i].r, ball[i].y - ball[i].r, ball[i].x + ball[i].r, ball[i].y + ball[i].r);
	}
}


// CMFCexamex22View 인쇄

BOOL CMFCexamex22View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCexamex22View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCexamex22View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCexamex22View 진단

#ifdef _DEBUG
void CMFCexamex22View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCexamex22View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCexamex22Doc* CMFCexamex22View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCexamex22Doc)));
	return (CMFCexamex22Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCexamex22View 메시지 처리기


void CMFCexamex22View::OnRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 0;
}


void CMFCexamex22View::OnGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 1;
}


void CMFCexamex22View::OnBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 2;
}


void CMFCexamex22View::Onlined()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int vi = 0;
	int vj = 0;
	double guri = 0;
	for (int i = 0; i < ball.size(); i++) {
		for (int j = 0; j < ball.size(); j++) {
			int dx = ball[i].x - ball[j].x;
			int dy = ball[i].y - ball[j].y;
			if (sqrt(dx * dx + dy * dy) >= guri && ball[i].color == ball[j].color) {
				guri = sqrt(dx * dx + dy * dy);
				vi = i;
				vj = j;
			}
		}
	}
	CClientDC dc(this);
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, bc[ball[vi].color]);
	CPen* oldPen = dc.SelectObject(&pen);
	dc.MoveTo(ball[vi].x, ball[vi].y);
	dc.LineTo(ball[vj].x, ball[vj].y);
	/*
	CBrush bs(bc[ball[vi].color]);
	dc.SelectObject(&bs);
	dc.Ellipse(ball[vi].x - ball[vi].r, ball[vi].y - ball[vi].r, ball[vi].x + ball[vi].r, ball[vi].y + ball[vi].r);
	dc.Ellipse(ball[vj].x - ball[vj].r, ball[vj].y - ball[vj].r, ball[vj].x + ball[vj].r, ball[vj].y + ball[vj].r);
	*/
	CString str;
	str.Format(L"%d", (int)guri);
	CRect trc(ball[vi].x , ball[vi].y, ball[vj].x , ball[vj].y);
	//dc.SetBkMode(TRANSPARENT); //글자가 어울림이 될 것인지 아닌지
	dc.DrawText(str, trc, (DT_CENTER | DT_VCENTER | DT_SINGLELINE));
	
}


void CMFCexamex22View::Onrandd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CRect rc;
	GetClientRect(&rc);
	/*
		int count = 0;
		while (count < 10) {
			srand((unsigned)time(NULL));
			int px = rand() % rc.right;
			int py = rand() % rc.bottom;
			int coll = 0;
			for (int i = 0; i < ball.size(); i++)
			{
				int xx = ball[i].x - px;
				int yy = ball[i].y - py;
				for (int j = 0; j < ball.size(); j++) {
					if (sqrt(xx * xx + yy * yy) <= ball[i].r + 15)
					{
						coll = 1; //충돌하면 생성 x
					}
				}
			}
			if (coll == 1) { continue; }
			if (px + 15 <= rc.right && px - 15 >= rc.left && py + 15 <= rc.bottom && py - 15 >= rc.top)
			{
				ball.push_back(Ball(px, py, 15, rand() % 3));
				count++;
			}
		}
	}
	*/
}

void CMFCexamex22View::Onmoveball()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (run == 0) {
		SetTimer(0, 100, NULL);
		run = 1;
	}
	
}
void CMFCexamex22View::Onstop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (run == 1) {
		KillTimer(0);
		bh = rand() % 8;
		run = 0;
	}
}



void CMFCexamex22View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int overlap = 0;
	CClientDC dc(this);
	for (int i = 0; i < ball.size(); i++) {
		int dx = ball[i].x - point.x;
		int dy = ball[i].y - point.y;
		if (point.x >= ball[i].x - ball[i].r && point.x <= ball[i].x + ball[i].r && point.y <= ball[i].y + ball[i].r &&
			point.y >= ball[i].y - ball[i].r)
		{
			overlap = 1;
			if (ball[i].color == 2) {
				ball[i].color = -1;
			}
			ball[i].color += 1;
			Invalidate();
			break;
		}
		if (sqrt(dx * dx + dy * dy) <= ball[i].r + 15)
		{
			overlap = 1;
			MessageBox(L"겹치는 원은 만들 수 없다", L"경고");
		}

	}
	if (overlap == 0) {
		ball.push_back(Ball(point.x, point.y, 15, currentcolor));
		BHx.push_back(0);
		BHy.push_back(0);
		Invalidate();
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCexamex22View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	if (run == 1)
	{
		for (int i = 0; i < ball.size(); i++) {
			ball[i].x += BHx[i];
			ball[i].y += BHy[i];
			if (bh == 0) { BHy[i] = -20; }
			if (bh == 1) { BHy[i] = -20; BHx[i] = 20; }
			if (bh == 2) { BHx[i] = 20; }
			if (bh == 3) { BHy[i] = 20; BHx[i] = 20; }
			if (bh == 4) { BHy[i] = 20; }
			if (bh == 5) { BHy[i] = 20; BHx[i] = -20; }
			if (bh == 6) { BHx[i] = -20; }
			if (bh == 7) { BHy[i] = -20; BHx[i] = -20; }
			
		}
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CMFCexamex22View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		if (run == 0) {
			SetTimer(0, 100, NULL);
			run = 1;
		}
		else {
			KillTimer(0);
			run = 0;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}




void CMFCexamex22View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	int count = 0;
	while (count < 10) {
		int px = rand() % rc.right;
		int py = rand() % rc.bottom;
		int coll = 0;
		for (int i = 0; i < ball.size(); i++)
		{
			int xx = ball[i].x - px;
			int yy = ball[i].y - py;
			if (sqrt(xx * xx + yy * yy) <= ball[i].r + 15)
			{
				coll = 1; //충돌하면 생성 x
			}
			
		}
		if (coll == 1) { continue; }
		if (px + 15 <= rc.right && px - 15 >= rc.left && py + 15 <= rc.bottom && py - 15 >= rc.top)
		{
			ball.push_back(Ball(px, py, 15, rand() % 3));
			count++;
		}
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}
