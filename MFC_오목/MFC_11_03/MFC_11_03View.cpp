
// MFC_11_03View.cpp: CMFC1103View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_11_03.h"
#endif

#include "MFC_11_03Doc.h"
#include "MFC_11_03View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC1103View

IMPLEMENT_DYNCREATE(CMFC1103View, CView)

BEGIN_MESSAGE_MAP(CMFC1103View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFC1103View 생성/소멸

CMFC1103View::CMFC1103View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	sc = BLACK;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			arr[i][j] = -1;
		}
	}
	running = START;
	rangeover = 1;
}

CMFC1103View::~CMFC1103View()
{
}

BOOL CMFC1103View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC1103View 그리기

void CMFC1103View::OnDraw(CDC* /*pDC*/)
{
	CMFC1103Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);


	gap = rc.bottom / 19;

	//바둑판 그리기
	for (int y = 0; y < 19; y++) {
		for (int x = 0; x < 19; x++) {
			CBrush board(RGB(255, 204, 051));
			dc.SelectObject(&board);
			dc.Rectangle(x * gap, y * gap, (x + 1) * gap, (y + 1) * gap);
		}
	}
	
	CBrush col[] = { RGB(0,0,0) , RGB(255,255,255) };
	for (int i = 0; i < v.size(); i++) {
		dc.SelectObject(&col[v[i].bw]);
		dc.Ellipse(v[i].x - gap/2-3, v[i].y - gap/2-3, v[i].x + gap/2-3, v[i].y + gap/2-3);
	}

	

	for (int y = 0; y < 20; y++) {
		CString str;
		CString temp;
		for (int x = 0; x < 20; x++) {
			temp.Format(L"%2d", arr[x][y]);
			str = str + temp;
		}
		dc.TextOut(1000, y * 15, str);
	}

}


// CMFC1103View 인쇄

BOOL CMFC1103View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC1103View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC1103View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC1103View 진단

#ifdef _DEBUG
void CMFC1103View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC1103View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC1103Doc* CMFC1103View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC1103Doc)));
	return (CMFC1103Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC1103View 메시지 처리기


void CMFC1103View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//테스트용도입니다.
	CClientDC dc(this);
	
	if (running == START) {
		int x = point.x / gap + (point.x % gap >= gap/2);
		int y = point.y / gap + (point.y % gap >= gap/2);
		
		if (arr[x][y] == -1) {
			arr[x][y] = sc;
		}
		else
			return;
		if (x > 20 || y > 20) {
			rangeover = 0;
		}
		else {
			rangeover = 1;
		}
		x = x * gap;
		y = y * gap;

		if (rangeover == 1) {
			v.push_back(info(x, y, sc));
			sc = !sc;   // 돌 색상 변경
			Invalidate();
		}


		for (x = 0; x < 16; x++) {
			for (y = 0; y < 20; y++) {

				if (arr[x][y] == 0 && arr[x + 1][y] == 0 && arr[x + 2][y] == 0 && arr[x + 3][y] == 0 && arr[x + 4][y] == 0) {
					MessageBox(L"흑이 이겼습니다.");
					running = STOP;
					break;
				}
				if (arr[x][y] == 1 && arr[x + 1][y] == 1 && arr[x + 2][y] == 1 && arr[x + 3][y] == 1 && arr[x + 4][y] == 1) {
					MessageBox(L"백이 이겼습니다.");
					running = STOP;
					break;
				}
			}
		}

		for (x = 0; x < 20; x++) {
			for (y = 0; y < 16; y++) {

				if (arr[x][y] == 0 && arr[x][y + 1] == 0 && arr[x][y + 2] == 0 && arr[x][y + 3] == 0 && arr[x][y + 4] == 0) {
					MessageBox(L"흑이 이겼습니다.");
					running = STOP;
					break;
				}
				if (arr[x][y] == 1 && arr[x][y + 1] == 1 && arr[x][y + 2] == 1 && arr[x][y + 3] == 1 && arr[x][y + 4] == 1) {
					MessageBox(L"백이 이겼습니다.");
					running = STOP;
					break;
				}
			}
		}

		for (x = 0; x < 20; x++) {
			for (y = 0; y < 20; y++) {

				if ((arr[x][y] == 0) && (arr[x + 1][y + 1] == 0) && (arr[x + 2][y + 2] == 0) && (arr[x + 3][y + 3] == 0) && (arr[x + 4][y + 4] == 0)) {
					MessageBox(L"흑이 이겼습니다.");
					running = STOP;
					break;
				}

				if ((arr[x][y] == 1) && (arr[x + 1][y + 1] == 1) && (arr[x + 2][y + 2] == 1) && (arr[x + 3][y + 3] == 1) && (arr[x + 4][y + 4] == 1)) {
					MessageBox(L"백이 이겼습니다.");
					running = STOP;
					break;
				}
			}
		}
		for (x = 0; x < 20; x++) {
			for (y = 0; y < 20; y++) {

				if ((arr[x][y] == 0) && (arr[x + 1][y - 1] == 0) && (arr[x + 2][y - 2] == 0) && (arr[x + 3][y - 3] == 0) && (arr[x + 4][y - 4] == 0)) {
					MessageBox(L"흑이 이겼습니다.");
					running = STOP;
					break;
				}

				if ((arr[x][y] == 1) && (arr[x + 1][y - 1] == 1) && (arr[x + 2][y - 2] == 1) && (arr[x + 3][y - 3] == 1) && (arr[x + 4][y - 4] == 1)) {
					MessageBox(L"백이 이겼습니다.");
					running = STOP;
					break;
				}
			}
		}
	}

	if (running == STOP)
	{
		MessageBox(L"게임이 끝났습니다");
	}
	/*
	//돌이 있는지 검사
	for (int i = 0; i < v.size(); i++) {
		int dx = v[i].x - x;
		int dy = v[i].y - y;
		double dist = sqrt((double)dx * dx + dy * dy);
		if (dist <= 25) {
			MessageBox(L"이미 돌이 있습니다.");
			return;
		}
	}
	*/
	/*
	int n = CheckArray();
	CString str;
	str.Format(L"%d", n);
	MessageBox(str);
	*/
	CView::OnLButtonDown(nFlags, point);
}

/*
int CMFC1103View::CheckArray()
{
	CString str;
	int count = 0;
	for (int x = 0; x < 19; x++)
		for (int y = 0; y < 19; y++)
			if (arr[x][y] != -1)
				count++;
	// TODO: 여기에 구현 코드 추가.
	return count;
}
*/