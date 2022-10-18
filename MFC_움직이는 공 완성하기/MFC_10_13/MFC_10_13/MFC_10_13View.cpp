#include <math.h>
#include <time.h>

// MFC_10_13View.cpp: CMFC1013View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_10_13.h"
#endif

#include "MFC_10_13Doc.h"
#include "MFC_10_13View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1013View

IMPLEMENT_DYNCREATE(CMFC1013View, CView)

BEGIN_MESSAGE_MAP(CMFC1013View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(Red, &CMFC1013View::OnRed)
	ON_COMMAND(Green, &CMFC1013View::OnGreen)
	ON_COMMAND(Blue, &CMFC1013View::OnBlue)
END_MESSAGE_MAP()

// CMFC1013View 생성/소멸

CMFC1013View::CMFC1013View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	run = 0;
	speed1 = 10;
	speed2 = 20;
	speed3 = 30;
	SelectBH = 0;
	currentcolor = 0;
}

CMFC1013View::~CMFC1013View()
{
}

BOOL CMFC1013View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1013View 그리기

void CMFC1013View::OnDraw(CDC* /*pDC*/)
{
	CMFC1013Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	for (int i = 0; i < v.size(); i++) {
		CBrush bs(color[BallColor[i]]);
		dc.SelectObject(&bs);
		dc.Ellipse(v[i].x - v[i].r, v[i].y - v[i].r, v[i].x + v[i].r, v[i].y + v[i].r);
	}
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size() - 1; j++) {
			int dx = v[i].x - v[j].x;
			int dy = v[i].y - v[j].y;
			if ((v[i].r < 5) || (v[i].r > 100)) {
				v.erase(v.begin() + i);
			}
			if ((v[j].r < 5) || (v[j].r > 100)) {
				v.erase(v.begin() + j);
			}
			if (sqrt(dx * dx + dy * dy) <= (v[i].r + v[j].r)) {
				if (BallColor[i] == BallColor[j]) {
					if (v[i].r > v[j].r) {
						v[i].r += v[j].r;
						v.erase(v.begin() + j);
					}
					if (v[i].r < v[j].r) {
						v[j].r += v[i].r;
						v.erase(v.begin() + i);
					}
					if (v[i].r == v[j].r) {
						v[i].r += v[j].r;
						v.erase(v.begin() + j);
					}
				}
				if (BallColor[i] != BallColor[j]) {
					v[i].r = v[i].r - (0.02 * v[i].r);
					v[j].r = v[j].r - (0.02 * v[j].r);
					BHx[i] = -BHx[i];
					BHx[j] = -BHx[j];
					BHy[i] = -BHy[i];
					BHy[j] = -BHy[j];
				}
			}
			
		}
	}
	
	
}


// CMFC1013View 인쇄

BOOL CMFC1013View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1013View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1013View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1013View 진단

#ifdef _DEBUG
void CMFC1013View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1013View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1013Doc* CMFC1013View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1013Doc)));
	return (CMFC1013Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1013View 메시지 처리기


void CMFC1013View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	for (int i = 0; i < v.size(); i++) {
		int dx = v[i].x - point.x;
		int dy = v[i].y - point.y;
		if (sqrt((double)dx * dx + dy * dy) <= v[i].r + v[i].r) {
			return;
		}
	}
	//v.erase(v.begin() + i); //원 삭제
	if (run == 0) {
		BallColor.push_back(currentcolor);
		v.push_back(ballinfo(point.x, point.y, 20.0));
		BHx.push_back(25);
		BHy.push_back(25);
		Invalidate();
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFC1013View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_SPACE) {
		run = !run; //현재 상태 반전
		if (run == 1)
			SetTimer(0, 100, NULL);
		else
			KillTimer(0);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFC1013View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rc;
	GetClientRect(&rc);

	for (int i = 0; i < v.size(); i++)
	{
		v[i].x += BHx[i];
		v[i].y += BHy[i];
		if (v[i].y + v[i].r >= rc.bottom) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHy[i] = -speed1; }
			if (SelectBH == 2) { BHy[i] = -speed2; }
			if (SelectBH == 3) { BHy[i] = -speed3; }
		}

		if (v[i].y - v[i].r <= rc.top) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHy[i] = speed1; }
			if (SelectBH == 2) { BHy[i] = speed2; }
			if (SelectBH == 3) { BHy[i] = speed3; }
		}
		if (v[i].x + v[i].r >= rc.right) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHx[i] = -speed1; }
			if (SelectBH == 2) { BHx[i] = -speed2; }
			if (SelectBH == 3) { BHx[i] = -speed3; }
		}
		if (v[i].x - v[i].r <= rc.left) {
			SelectBH = rand() % 3 + 1;
			if (SelectBH == 1) { BHx[i] = speed1; }
			if (SelectBH == 2) { BHx[i] = speed2; }
			if (SelectBH == 3) { BHx[i] = speed3; }
		}
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CMFC1013View::OnRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 0;
}


void CMFC1013View::OnGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 1;
}


void CMFC1013View::OnBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	currentcolor = 2;
}
