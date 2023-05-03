#include <stdlib.h>
#include <time.h>
// MFC_Task_2View.cpp: CMFCTask2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_Task_2.h"
#endif

#include "MFC_Task_2Doc.h"
#include "MFC_Task_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTask2View

IMPLEMENT_DYNCREATE(CMFCTask2View, CView)

BEGIN_MESSAGE_MAP(CMFCTask2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(Blue_E, &CMFCTask2View::Blue)
	ON_COMMAND(Green_E, &CMFCTask2View::Green)
	ON_COMMAND(Red_E, &CMFCTask2View::Red)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
//	ON_WM_KEYDOWN()
ON_COMMAND(Start, &CMFCTask2View::OnStart)
ON_COMMAND(Pause, &CMFCTask2View::OnPause)
ON_COMMAND(Fast, &CMFCTask2View::OnFast)

ON_COMMAND(Red_R, &CMFCTask2View::OnR)
ON_COMMAND(Green_R, &CMFCTask2View::OnG)
ON_COMMAND(Blue_R, &CMFCTask2View::OnB)
END_MESSAGE_MAP()

// CMFCTask2View 생성/소멸

CMFCTask2View::CMFCTask2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	currentballcolor = 0;
	currentrectcolor = 0;

	run = 0;

	count = 0;
	count2 = 0;

	DrawERun = 1;
	DrawRRun = 0;
}

CMFCTask2View::~CMFCTask2View()
{
}

BOOL CMFCTask2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCTask2View 그리기

void CMFCTask2View::OnDraw(CDC* /*pDC*/)
{
	CMFCTask2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);	
	if (DrawERun == 1) {
		COLORREF color1[3] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255) };
		for (int i = 0; i < count; i++) {
			CBrush bs(color1[ballcolor[i]]);
			dc.SelectObject(&bs);
			dc.Ellipse(ball[i].x - ballsize[i], ball[i].y - ballsize[i], ball[i].x
				+ ballsize[i], ball[i].y + ballsize[i]);
			}
		}
	CClientDC tc(this);
	if (DrawRRun == 1) {
		COLORREF color2[3] = { RGB(255,0,0),RGB(0,255,0),RGB(0,0,255) };
		for (int i = 0; i < count2; i++) {
			CBrush ds(color2[rectcolor[i]]);
			tc.SelectObject(&ds);
			tc.Rectangle(rect[i].x - 50, rect[i].y - 50, rect[i].x
				+ 50, rect[i].y + 50);
			}
			
		}
	
	
}


// CMFCTask2View 인쇄

BOOL CMFCTask2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCTask2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCTask2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCTask2View 진단

#ifdef _DEBUG
void CMFCTask2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTask2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTask2Doc* CMFCTask2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTask2Doc)));
	return (CMFCTask2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTask2View 메시지 처리기


void CMFCTask2View::Blue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 0;
	DrawERun = 1;
	
	currentballcolor = 2;
	
}


void CMFCTask2View::Green()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 0;
	DrawERun = 1;
	
	currentballcolor = 1;
}


void CMFCTask2View::Red()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 0;
	DrawERun = 1;
	
	currentballcolor = 0;

}


void CMFCTask2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
		
		if (DrawERun == 1) {
			ball.push_back(point);
			ballcolor.push_back(currentballcolor);
			ballsize.push_back(30);
			count++;
			Invalidate();
		}
		if (DrawRRun == 1) {
			rect.push_back(point);
			rectcolor.push_back(currentrectcolor);
			rectsize.push_back(30);
			count2++;
			Invalidate();
		}
	

	for (int i = 0; i < count; i++)
	{
		run1[count - 1] = 1;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCTask2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	srand((unsigned)time(NULL));
	CRect rc;
	GetClientRect(&rc);
	if (run == 1) {
		for (int i = 0; i < count; i++) {
			if (ball[i].y + 50 >= rc.bottom) {

				run0[i] = rand() % 3 + 1;
				run1[i] = 0;
				run2[i] = 0;
				run3[i] = 0;
				// run0[i] = 1 은 바로 위 2 는 왼쪽 위 3은 오른쪽 위
			}
			if (run0[i] == 1) {
				ball[i].y -= 25;
			}
			if (run0[i] == 2) {
				ball[i].y -= 25;
				ball[i].x -= 25;
			}
			if (run0[i] == 3) {
				ball[i].y -= 25;
				ball[i].x += 25;
			}
		}

		//위쪽 벽
		for (int i = 0; i < count; i++) {
			if (ball[i].y - 50 <= rc.top) {
				run0[i] = 0;
				run1[i] = rand() % 3 + 1;
				run2[i] = 0;
				run3[i] = 0;
				// run1[i] = 1 은 바로 밑 2 는 왼쪽 밑 3은 오른쪽 밑
			}
			if (run1[i] == 1) {
				ball[i].y += 25;
			}
			if (run1[i] == 2) {
				ball[i].y += 25;
				ball[i].x -= 25;
			}
			if (run1[i] == 3) {
				ball[i].y += 25;
				ball[i].x += 25;
			}
		}

		//오른쪽 벽
		for (int i = 0; i < count; i++) {
			if (ball[i].x + 50 >= rc.right) {
				run0[i] = 0;
				run1[i] = 0;
				run2[i] = rand() % 3 + 1;
				run3[i] = 0;
				// 1 왼쪽 2 왼쪽 위 3왼쪽 밑
			}
			if (run2[i] == 1) {
				ball[i].x -= 25;
			}
			if (run2[i] == 2) {
				ball[i].y -= 25;
				ball[i].x -= 25;
			}
			if (run2[i] == 3) {
				ball[i].y += 25;
				ball[i].x -= 25;
			}
		}

		// 왼쪽 벽
		for (int i = 0; i < count; i++) {
			if (ball[i].x - 50 <= rc.left) {
				run0[i] = 0;
				run1[i] = 0;
				run2[i] = 0;
				run3[i] = rand() % 3 + 1;
				// 1 오른쪽 2오른쪽 위 3오른쪽 밑
			}
			if (run3[i] == 1) {
				ball[i].x += 25;
			}
			if (run3[i] == 2) {
				ball[i].y -= 25;
				ball[i].x += 25;
			}
			if (run3[i] == 3) {
				ball[i].y += 25;
				ball[i].x += 25;
			}
		}
		Invalidate();
	}
	
	CView::OnTimer(nIDEvent);
}



void CMFCTask2View::OnStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(0, 100, NULL);
	run = 1;
}


void CMFCTask2View::OnPause()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(0);
	run = 0;
}

void CMFCTask2View::OnFast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(0, 50, NULL);
	run = 1;
}




void CMFCTask2View::OnR()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 1;
	DrawERun = 0;

	currentrectcolor = 0;
}


void CMFCTask2View::OnG()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 1;
	DrawERun = 0;

	currentrectcolor = 1;
}


void CMFCTask2View::OnB()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DrawRRun = 1;
	DrawERun = 0;

	currentrectcolor = 2;
}
