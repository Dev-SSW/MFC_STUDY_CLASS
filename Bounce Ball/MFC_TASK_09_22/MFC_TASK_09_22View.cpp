#include <stdlib.h>
#include <time.h>
// MFC_TASK_09_22View.cpp: CMFCTASK0922View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_TASK_09_22.h"
#endif

#include "MFC_TASK_09_22Doc.h"
#include "MFC_TASK_09_22View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTASK0922View

IMPLEMENT_DYNCREATE(CMFCTASK0922View, CView)

BEGIN_MESSAGE_MAP(CMFCTASK0922View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMFCTASK0922View 생성/소멸

CMFCTASK0922View::CMFCTASK0922View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	run = 0;
	count = 0;
}

CMFCTASK0922View::~CMFCTASK0922View()
{
}

BOOL CMFCTASK0922View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCTASK0922View 그리기

void CMFCTASK0922View::OnDraw(CDC* pDC)
{
	CMFCTASK0922Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);
	CBrush bs(RGB(rand()%255, rand() % 255, rand() % 255));
	dc.SelectObject(&bs);

	/********************************************************************/
	for (int i = 0; i < count; i++) {
		dc.Ellipse(ball[i].x - 50, ball[i].y - 50, ball[i].x + 50, ball[i].y + 50); //공 생성 시키기
	}

	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			int dx = ball[i].x - ball[j].x;
			int dy = ball[i].y - ball[j].y;
			if (sqrt(dx * dx + dy * dy) <= 100) {
				ball[i].SetPoint(-300, -300);
				ball[j].SetPoint(-300, -300);
				break;
			}
		}
	}

}


// CMFCTASK0922View 인쇄

BOOL CMFCTASK0922View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCTASK0922View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCTASK0922View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCTASK0922View 진단

#ifdef _DEBUG
void CMFCTASK0922View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCTASK0922View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCTASK0922Doc* CMFCTASK0922View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCTASK0922Doc)));
	return (CMFCTASK0922Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCTASK0922View 메시지 처리기


void CMFCTASK0922View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int overlap = 0;
	for (int i = 0; i < count; i++) 
	{
		int dx = ball[i].x - point.x;
		int dy = ball[i].y - point.y;
		if (sqrt(dx * dx + dy * dy) <= 100)
		{
			overlap = 1;
			break;
		}
	}
	if (overlap == 0) {
		ball[count] = point;
		count++;
		Invalidate();
	}

	//맨처음에 밑으로 내려가게 하는 함수
	for (int i = 0; i < count; i++)
	{
		run1[count-1] = 1;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCTASK0922View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		run = !run;
		if (run == 1) {
			SetTimer(0, 100, NULL);
			
		}
		else {
			KillTimer(0);
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCTASK0922View::OnTimer(UINT_PTR nIDEvent)
{	
	srand((unsigned)time(NULL));
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	

	//시작하자마자 내려가기
	
	//아래쪽 벽
	for (int i = 0; i < count; i++) {
		if (ball[i].y + 50 >= rc.bottom) {
			
			run0[i] = rand()%3 +1;
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

	CView::OnTimer(nIDEvent);
}
