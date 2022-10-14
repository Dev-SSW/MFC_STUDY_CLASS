#include <stdlib.h>;
#include <time.h>;
// MFC_10_11View.cpp: CMFC1011View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_10_11.h"
#endif

#include "MFC_10_11Doc.h"
#include "MFC_10_11View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1011View

IMPLEMENT_DYNCREATE(CMFC1011View, CView)

BEGIN_MESSAGE_MAP(CMFC1011View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(RedE, &CMFC1011View::OnRede)
	ON_COMMAND(GreenE, &CMFC1011View::OnGreene)
	ON_COMMAND(BlueE, &CMFC1011View::OnBluee)
END_MESSAGE_MAP()

// CMFC1011View 생성/소멸

CMFC1011View::CMFC1011View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	count = 0;
	run = 0;
	currentcolor = 0;
	speed1 = 10;
	speed2 = 20;
	speed3 = 30;
	SelectBH = 0;
}

CMFC1011View::~CMFC1011View()
{
}

BOOL CMFC1011View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1011View 그리기

void CMFC1011View::OnDraw(CDC* /*pDC*/)
{
	CMFC1011Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	COLORREF color[3] = { RGB(255,0,0) , RGB(0,255,0) , RGB(0,0,255) };
	for (int i = 0; i < count; i++) {
		CBrush bs(color[BallColor[i]]);
		dc.SelectObject(&bs);
		dc.Ellipse(Ball[i].x - BallSize[i], Ball[i].y - BallSize[i], Ball[i].x + BallSize[i], Ball[i].y + BallSize[i]);
		
	}
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {
			int dx = Ball[i].x - Ball[j].x;
			int dy = Ball[i].y - Ball[j].y;
			if (BallSize[i] < 5) {
				Ball[i].SetPoint(-300, -300);
				BallSize[i] = 0;
				BHx[i] = 0;
				BHy[i] = 0;
			}
			if (BallSize[j] < 5) {
				Ball[j].SetPoint(-300, -300);
				BallSize[j] = 0;
				BHx[j] = 0;
				BHy[j] = 0;
			}
			if (sqrt(dx * dx + dy * dy) <= (BallSize[i] + BallSize[j])) {
				if (BallColor[i] == BallColor[j]) {
					if (BallSize[i] > BallSize[j]) {
						BallSize[i] += BallSize[j];
						Ball[j].SetPoint(-300, -300);
						BallSize[j] = 0;
						BHx[j] = 0;
						BHy[j] = 0;
						if (BallSize[i] > 100) {
							Ball[i].SetPoint(-300, -300);
							BallSize[i] = 0;
							BHx[i] = 0;
							BHy[i] = 0;
						}
					}
					if (BallSize[i] < BallSize[j]) {
						BallSize[j] += BallSize[i];
						Ball[i].SetPoint(-300, -300);
						BallSize[i] = 0;
						BHx[i] = 0;
						BHy[i] = 0;
						if (BallSize[j] > 100) {
							Ball[j].SetPoint(-300, -300);
							BallSize[j] = 0;
							BHx[j] = 0;
							BHy[j] = 0;
						}
					}
					if (BallSize[i] == BallSize[j]) {
						BallSize[i] = 75;
						Ball[j].SetPoint(-300, -300);
						BallSize[j] = 0;
						BHx[j] = 0;
						BHy[j] = 0;
					}
				}
				if (BallColor[i] != BallColor[j]) {
					BallSize[i] = BallSize[i] - (0.02 * BallSize[i]);
					BallSize[j] = BallSize[j] - (0.02 * BallSize[j]);
					BHx[i] = -BHx[i];
					BHx[j] = -BHx[j];
					BHy[i] = -BHy[i];
					BHy[j] = -BHy[j];
				}
			}
		}
	}
}


// CMFC1011View 인쇄  

BOOL CMFC1011View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1011View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1011View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1011View 진단

#ifdef _DEBUG
void CMFC1011View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1011View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1011Doc* CMFC1011View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1011Doc)));
	return (CMFC1011Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1011View 메시지 처리기


void CMFC1011View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (run == 0) //공이 안 움직이고 있을 때
	{
		Ball.push_back(point);
		BallSize.push_back(40);
		BallColor.push_back(currentcolor);
		BHx.push_back(25);
		BHy.push_back(25);
		count++;
		Invalidate();
	}
	
	/*
	if (이미 있는 공)
		return;
	*/
	CView::OnLButtonDown(nFlags, point);
}


void CMFC1011View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		run = !run; //현재 상태 반전
		if (run == 1)
			SetTimer(0, 50, NULL);
		else
			KillTimer(0);
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFC1011View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);
	for (int i = 0; i < count; i++) {
		if (Ball[i].y - BallSize[i] <= rc.top - 100) {
			BHy[i] = 0;
		}
		if (Ball[i].x - BallSize[i] <= rc.left - 100) {
			BHx[i] = 0;
		}
	}
	for (int i = 0; i < count; i++) 
	{
		Ball[i].x += BHx[i];
		Ball[i].y += BHy[i];
		if (Ball[i].y + BallSize[i] >= rc.bottom) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHy[i] = -speed1; }
			if (SelectBH == 2) { BHy[i] = -speed2; }
			if (SelectBH == 3) { BHy[i] = -speed3; }
		}

		if (Ball[i].y - BallSize[i] <= rc.top) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHy[i] = speed1; }
			if (SelectBH == 2) { BHy[i] = speed2; }
			if (SelectBH == 3) { BHy[i] = speed3; }
		}
		if (Ball[i].x + BallSize[i] >= rc.right) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHx[i] = -speed1; }
			if (SelectBH == 2) { BHx[i] = -speed2; }
			if (SelectBH == 3) { BHx[i] = -speed3; }
		}
		if (Ball[i].x - BallSize[i] <= rc.left) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHx[i] = speed1; }
			if (SelectBH == 2) { BHx[i] = speed2; }
			if (SelectBH == 3) { BHx[i] = speed3; }
		}
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CMFC1011View::OnRede()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 0;
}


void CMFC1011View::OnGreene()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 1;
}


void CMFC1011View::OnBluee()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 2;
}
