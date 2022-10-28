
// 2020110223View.cpp: CMy2020110223View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2020110223.h"
#endif

#include "2020110223Doc.h"
#include "2020110223View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2020110223View

IMPLEMENT_DYNCREATE(CMy2020110223View, CView)

BEGIN_MESSAGE_MAP(CMy2020110223View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(rede, &CMy2020110223View::Onrede)
	ON_COMMAND(greene, &CMy2020110223View::Ongreene)
	ON_COMMAND(bluee, &CMy2020110223View::Onbluee)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(dele, &CMy2020110223View::Ondele)
END_MESSAGE_MAP()

// CMy2020110223View 생성/소멸

CMy2020110223View::CMy2020110223View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	currentcolor = 0;
	rx=ry=rs=re= 0;
	first = true;
	run = 0;
	guri = 500;
	vi = -1;
	vj = -1;
}

CMy2020110223View::~CMy2020110223View()
{
}

BOOL CMy2020110223View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy2020110223View 그리기

void CMy2020110223View::OnDraw(CDC* /*pDC*/)
{
	CMy2020110223Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	if (first) {
		rx = rc.right / 8;
		ry = rc.bottom / 4;
		rs = 0;
		re = 0;
		first = false;
	}
	CBrush bsb(RGB(0, 0, 0));
	dc.SelectObject(&bsb);
	dc.SetBkMode(TRANSPARENT);
	dc.Rectangle(rs, re, rx, ry);
	for (int i = 0; i < ball.size(); i++) {
		CBrush bs(bc[ball[i].color]);
		dc.SelectObject(&bs);
		dc.Ellipse(ball[i].x - ball[i].r, ball[i].y - ball[i].r, ball[i].x + ball[i].r, ball[i].y + ball[i].r);
	}
	CString str;
	str.Format(L"2020110223 송승우");
	dc.SetTextColor(RGB(128, 128, 128));
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(str, rc, (DT_CENTER | DT_VCENTER | DT_SINGLELINE));
}


// CMy2020110223View 인쇄

BOOL CMy2020110223View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy2020110223View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy2020110223View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy2020110223View 진단

#ifdef _DEBUG
void CMy2020110223View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2020110223View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2020110223Doc* CMy2020110223View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2020110223Doc)));
	return (CMy2020110223Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2020110223View 메시지 처리기


void CMy2020110223View::OnLButtonDown(UINT nFlags, CPoint point)
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
		if (sqrt(dx * dx + dy * dy) <= ball[i].r + 30)
		{
			overlap = 1;
			MessageBox(L"겹치는 원은 만들 수 없다", L"경고");
		}

	}
	if (overlap == 0) {
		ball.push_back(Ball(point.x, point.y, 30, currentcolor));
		Invalidate();
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2020110223View::Onrede()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 0;
}


void CMy2020110223View::Ongreene()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 1;
}


void CMy2020110223View::Onbluee()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 2;
}


void CMy2020110223View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	int count = 0;
	while (count < 1) {
		int px = rand() % rc.right;
		int py = rand() % rc.bottom;
		int coll = 0;
		for (int i = 0; i < ball.size(); i++)
		{
			int xx = ball[i].x - px;
			int yy = ball[i].y - py;
			for (int j = 0; j<ball.size(); j++)
			if (sqrt(xx * xx + yy * yy) <= ball[i].r + ball[j].r)
			{
				coll = 1; //충돌하면 생성 x
			}

		}
		if (coll == 1) { continue; }
		if (px + 50 <= rc.right && px - 50 >= rc.left && py + 50 <= rc.bottom && py - 50 >= rc.top)
		{
			ball.push_back(Ball(px, py, rand()%31 + 20 , currentcolor));
			count++;
		}
	}
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}


void CMy2020110223View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		run = !run;
		if (run == 1)
			SetTimer(0, 500, NULL); // 1초 = 1000  
		else
			KillTimer(0);
	}
	
	switch (nChar) {	
	case VK_UP: {re -= 10; ry -= 10; break; }
	case VK_RIGHT: {rx += 10; rs += 10; break; }
	case VK_DOWN: {ry += 10; re += 10; break; }
	case VK_LEFT: {rx -= 10; rs -= 10; }
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy2020110223View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i=0; i < ball.size(); i++) {
		ball[i].x += 10;
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CMy2020110223View::Ondele()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (run == 0) {
		for (int i = 0; i < ball.size()-1; i++) {
			for (int j = i+1 ; j < ball.size(); j++) {
				int dx = ball[i].x - ball[j].x;
				int dy = ball[i].y - ball[j].y;
				if (sqrt(dx * dx + dy * dy) <= guri) {
					guri = sqrt(dx * dx + dy * dy);
					vi = i;
					vj = j;
				}
			}
		}
		if (vi > vj)
		{
			ball.erase(ball.begin() + vi);
		}
		if (vi < vj)
		{
			ball.erase(ball.begin() + vj);
		}
		Invalidate();
	}
}
