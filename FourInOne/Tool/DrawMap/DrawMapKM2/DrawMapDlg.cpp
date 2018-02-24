// DrawMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawMap.h"
#include "DrawMapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawMapDlg dialog

CDrawMapDlg::CDrawMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawMapDlg)
	m_GpsFilePath = _T("");
	m_ebs = 38.0;
	m_edh = 0.0;
	m_edw = 0.0;
	m_emaxx = 0.0;
	m_emaxy = 0.0;
	m_eminx = 90000000.0;
	m_eminy = 90000000.0;
	m_CB = 63;
	m_CG = 159;
	m_CR = 220;	
	m_CSIZE = 8;
	m_ER2 = 254;
	m_EG2 = 195;
	m_EB2 = 101;
	m_ESIZE2 = 6;
	m_TText = _T("XXX驾校科目二电子地图");
	m_Ejwdbs = 1;
	m_Check = FALSE;
	m_Check2 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawMapDlg)
	DDX_Text(pDX, IDC_EDIT8, m_GpsFilePath);
	DDX_Text(pDX, IDC_EBS, m_ebs);
	DDX_Text(pDX, IDC_EDH, m_edh);
	DDX_Text(pDX, IDC_EDW, m_edw);
	DDX_Text(pDX, IDC_EMAXX, m_emaxx);
	DDX_Text(pDX, IDC_EMAXY, m_emaxy);
	DDX_Text(pDX, IDC_EMINX, m_eminx);
	DDX_Text(pDX, IDC_EMINY, m_eminy);
	DDX_Text(pDX, IDC_EB, m_CB);
	DDX_Text(pDX, IDC_EG, m_CG);
	DDX_Text(pDX, IDC_ER, m_CR);
	DDX_Text(pDX, IDC_ESIZE, m_CSIZE);
	DDX_Text(pDX, IDC_ER2, m_ER2);
	DDX_Text(pDX, IDC_EG2, m_EG2);
	DDX_Text(pDX, IDC_EB2, m_EB2);
	DDX_Text(pDX, IDC_ESIZE2, m_ESIZE2);
	DDX_Text(pDX, IDC_EDIT1, m_TText);
	DDX_Text(pDX, IDC_EJWDBS, m_Ejwdbs);
	DDX_Check(pDX, IDC_CHECK1, m_Check);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawMapDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawMapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnLoadFile)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_BTN_CARM, OnBtnCarm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawMapDlg message handlers

BOOL CDrawMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	COleDateTime pngfiletime(time_t(1636708777));
	COleDateTime curTime =COleDateTime::GetCurrentTime();	
	if (pngfiletime < curTime)
	{
		m_BSb=2;
	}
	else
	{
		m_BSb=1;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrawMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDrawMapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawMapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDrawMapDlg::OnLoadFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
//	CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"传感器 (*.cfg)|*.cfg |All Files (*.*)|*.* ||");
	CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"轨迹数据文件(*.txt)|*.txt |All Files (*.*)|*.*||");
	if(dlg.DoModal()==IDOK)
	{
		m_GpsFilePath=dlg.GetPathName();
		CStdioFile file;
		CString readText;
		int posi;
		double tempx,tempy;
		CString xx,yy,temp;
		if (file.Open(m_GpsFilePath, CFile::modeRead))
		{
			while (file.ReadString(readText))
			{
				TRACE(readText+"\n");
				posi=readText.Replace(",",",");
				if (posi!=2)
				{
					continue;
				}
				posi =readText.Find(",");				
				temp =readText.Mid(posi+1);
				posi =temp.Find(",");
				xx=temp.Left(posi);
				readText =temp.Mid(posi+1);
				yy=readText.Left(posi);
				tempx=atof(xx)*m_Ejwdbs;
				tempy=atof(yy)*m_Ejwdbs;
				//////////////////////////////////////////////////////////////////////////
				if (tempx >m_emaxx)
				{
					m_emaxx=tempx;
				}
				if (tempx <m_eminx)
				{
					m_eminx=tempx;
				}
				if (tempy>m_emaxy)
				{
					m_emaxy =tempy;
				}
				if (tempy <m_eminy)
				{
					m_eminy=tempy;
				}
				//////////////////////////////////////////////////////////////////////////
			}
			UpdateData(FALSE);
		}//if file open
	}
}
//修正数据
void CDrawMapDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString temp;
	temp.Format("%.0f",m_emaxx);
	m_emaxx =atof(temp)+30;
	temp.Format("%.0f",m_emaxy);
	m_emaxy =atof(temp)+30;
	temp.Format("%.0f",m_eminx);
	m_eminx =atof(temp)-30;
	temp.Format("%.0f",m_eminy);
	m_eminy =atof(temp)-30;
	m_edw =(m_emaxx-m_eminx)*m_ebs*m_BSb;
	m_edh =(m_emaxy-m_eminy)*m_ebs*m_BSb;
	
	CString strax,stray,strix,striy,strzoom;
	strax.Format("%lf",m_emaxx);
	stray.Format("%lf",m_emaxy);
	strix.Format("%lf",m_eminx);
	striy.Format("%lf",m_eminy);
	strzoom.Format("%lf",m_ebs);
	::WritePrivateProfileString("MAPCONFIG","MAXX",strax,".\\MAP.cfg");
	::WritePrivateProfileString("MAPCONFIG","MAXY",stray,".\\MAP.cfg");
	::WritePrivateProfileString("MAPCONFIG","MINX",strix,".\\MAP.cfg");
	::WritePrivateProfileString("MAPCONFIG","MINY",striy,".\\MAP.cfg");
	::WritePrivateProfileString("MAPCONFIG","ZoomIn",strzoom,".\\MAP.cfg");	
	UpdateData(FALSE);

}

void CDrawMapDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strax,stray,strzoom,strix,striy;
	GetPrivateProfileString("MAPCONFIG","MAXX","",strax.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
	GetPrivateProfileString("MAPCONFIG","MAXY","",stray.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
	GetPrivateProfileString("MAPCONFIG","MINX","",strix.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
	GetPrivateProfileString("MAPCONFIG","MINY","",striy.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
	GetPrivateProfileString("MAPCONFIG","ZoomIn","",strzoom.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
	strax.ReleaseBuffer();
	stray.ReleaseBuffer();
	strzoom.ReleaseBuffer();
	strix.ReleaseBuffer();
	striy.ReleaseBuffer();
	m_emaxx =atof(strax);
	m_emaxy =atof(stray);
	m_ebs =atof(strzoom);
	m_eminx=atof(strix);
	m_eminy=atof(striy);
	UpdateData(FALSE);
	if (m_Check)
	{
		::WritePrivateProfileString("MAPCONFIG","XC","1",".\\MAP.cfg");
	}
	else
	{
		::WritePrivateProfileString("MAPCONFIG","XC","0",".\\MAP.cfg");
	}
	if (m_Check2)
	{
		::WritePrivateProfileString("MAPCONFIG","YC","1",".\\MAP.cfg");
	}
	else
	{
		::WritePrivateProfileString("MAPCONFIG","YC","0",".\\MAP.cfg");
	}
	if (m_GpsFilePath.IsEmpty())
	{
		CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"轨迹数据文件(*.txt)|*.txt||");
		if(dlg.DoModal()==IDOK)
		{
			m_GpsFilePath = dlg.GetPathName();
		}
		else
		{
			return ;
		}
	}
	Image  image(L"MAPN.png");
	Graphics imageGraphics(&image);
	Pen blackPen(Color(250,m_CR,m_CG,m_CB),1);
	CStdioFile file;
	CString readText;
	CString xx,yy,temp;
	PointF pPoints[20000];
	PointF temppoint;
	PointF firstPoint;
	int pointi=0;
	if (file.Open(m_GpsFilePath, CFile::modeRead))
	{
		while (file.ReadString(readText))
		{
			TRACE(readText+"\n");
			int pos=readText.Replace(",",",");
			if (pos==2)
			{
				pos =readText.Find(",");				
				temp =readText.Mid(pos+1);
				pos =temp.Find(",");
				xx=temp.Left(pos);
				readText =temp.Mid(pos+1);
				yy=readText.Left(pos);
				if (m_Check)
				{
					temppoint.X=(float)((atof(xx)*m_Ejwdbs-m_eminx)*m_ebs);	
				}
				else
				{
					temppoint.X=(float)((m_emaxx-atof(xx)*m_Ejwdbs)*m_ebs);
				}
				if(m_Check2)
				{
					temppoint.Y=(float)((atof(yy)*m_Ejwdbs-m_eminy)*m_ebs);
				}
				else
				{
					temppoint.Y=(float)((m_emaxy-atof(yy)*m_Ejwdbs)*m_ebs);
				}
				pPoints[pointi]=temppoint;	
				if (pointi==0)
				{
					firstPoint=temppoint;
				}
				pointi+=1;	
			}
			else
			{
				if ( pointi > 0)
				{
					pPoints[pointi]=firstPoint;
					pointi+=1;
					imageGraphics.DrawLines(&blackPen, pPoints, pointi);		
					pointi=0;
				}
			}
		}		
	}
	m_GpsFilePath=_T("");
	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	image.Save(L"MAPN.skin.png", &pngClsid, NULL);
	AfxMessageBox("地图生成完成!文件名为:MAPN.skin.png");
}

int CDrawMapDlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num= 0;
	UINT size= 0;
	
	ImageCodecInfo* pImageCodecInfo= NULL;
	
	GetImageEncodersSize(&num, &size);
	if(size== 0)
	{
		return -1;
	}
	pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo== NULL)
	{
		return -1;
	}
	
	GetImageEncoders(num, size, pImageCodecInfo);
	
	for(UINT j=0; j< num; ++j)
	{
		if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
		{
			*pClsid= pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	
	free(pImageCodecInfo);
	return -1;
}

void CDrawMapDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);	
	CDC *pDC = this->GetDC();
	int idw,idh;
	idh=(int)m_edh;
	idw=(int)m_edw;
	if (idh <=0 || idw<=0)
	{
		return ;
	}
	CBitmap m_bmpMap;
 	CDC	 m_dcMem;
	m_bmpMap.CreateCompatibleBitmap(pDC,idw,idh);
	if (m_bmpMap.m_hObject==NULL)
	{
		AfxMessageBox("生成背景图失败!");
		return ;
	}
	m_dcMem.CreateCompatibleDC(pDC);
	m_dcMem.SelectObject(m_bmpMap);
	COLORREF m_BackColor;
	m_BackColor=RGB(240,240,240);
	m_dcMem.SetBkColor(m_BackColor);
	CBrush br;
	br.CreateSolidBrush(m_BackColor);
	CRect rect;
	rect.SetRect(0,0,idw,idh);
	m_dcMem.FillRect(&rect,&br);
	br.DeleteObject();
	
	rect.SetRect(0,0,352,288);
	CFont fontz,fontzerror;//
	fontz.CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_STROKE_PRECIS, CLIP_STROKE_PRECIS,
		DRAFT_QUALITY, VARIABLE_PITCH | FF_SWISS, "宋体");
	m_dcMem.SelectObject(&fontz);
	m_dcMem.DrawText(m_TText,&rect,DT_CENTER | DT_SINGLELINE | DT_VCENTER );
	rect.SetRect(0,idh-35,idw,idh);

	m_dcMem.DrawText("福州北科大舟宇电子有限公司",&rect,DT_CENTER | DT_SINGLELINE | DT_VCENTER );
	fontz.DeleteObject();
	Bitmap mbitmap(HBITMAP(m_bmpMap),NULL);//从CBitmap中得到HBitmap		
	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	unsigned short tcharArr[100];
	CString temp;
	temp.Format(".\\MAPN.png");
	memset(tcharArr,0x0,sizeof(tcharArr));
	swprintf((wchar_t *)tcharArr,L"%s",temp.AllocSysString());
	mbitmap.Save(tcharArr,&pngClsid);//保存
	//////////////////////////////////////////////////////////////////////////
	m_bmpMap.DeleteObject();
	m_dcMem.DeleteDC();
	this->ReleaseDC(pDC);
	AfxMessageBox("生成背景完成 MAPN.png");
}

void CDrawMapDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"轨迹数据文件(*.txt)|*.txt||");
	if(dlg.DoModal()==IDOK)
	{
		m_GpsFilePath = dlg.GetPathName();
		CFileFind FindaviFile;
		if (FindaviFile.FindFile("MAPN.skin.png"))
		{
			if (FindaviFile.FindFile("MAPN.png"))
			{
				CFile::Remove("MAPN.png");
			}
			CFile::Rename("MAPN.skin.png","MAPN.png");
		}
		FindaviFile.Close();
		UpdateData(FALSE);
		OnButton3();
	}
}

void CDrawMapDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"轨迹数据文件(*.txt)|*.txt||");
	if(dlg.DoModal()==IDOK)
	{
		CFileFind FindaviFile;
		if (FindaviFile.FindFile("MAPN.skin.png"))
		{
			if (FindaviFile.FindFile("MAPN.png"))
			{
				CFile::Remove("MAPN.png");
			}
			CFile::Rename("MAPN.skin.png","MAPN.png");
		}
		FindaviFile.Close();
		CString strax,stray,strzoom,strix,striy;
		GetPrivateProfileString("MAPCONFIG","MAXX","",strax.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
		GetPrivateProfileString("MAPCONFIG","MAXY","",stray.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
		GetPrivateProfileString("MAPCONFIG","MINX","",strix.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
		GetPrivateProfileString("MAPCONFIG","MINY","",striy.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
		GetPrivateProfileString("MAPCONFIG","ZoomIn","",strzoom.GetBuffer(MAX_PATH),MAX_PATH,".\\MAP.cfg");
		strax.ReleaseBuffer();
		stray.ReleaseBuffer();
		strzoom.ReleaseBuffer();
		strix.ReleaseBuffer();
		striy.ReleaseBuffer();
		m_emaxx =atof(strax);
		m_emaxy =atof(stray);
		m_ebs =atof(strzoom);
		m_eminx=atof(strix);
		m_eminy=atof(striy);
		UpdateData(FALSE);
		
		Image  image(L"MAPN.png");
		Graphics imageGraphics(&image);
		
		SolidBrush blackBrush(Color(255, 0, 0, 0));
		
		float x,y;
		x=0.0f;
		y=0.0f;
		CStdioFile file;
		CString readText;
		CString xx,yy,temp,temp2;
		unsigned short tcharArr[10];
		Font myFont(L"Arial",14);
		StringFormat format;
		format.SetAlignment(StringAlignmentNear);//默认都不影响垂直 
		format.SetLineAlignment(StringAlignmentNear);// 和SetAlignment对应，为竖直的设置
		
		
		m_GpsFilePath = dlg.GetPathName();
		int pos=0;
		if (file.Open(m_GpsFilePath, CFile::modeRead))
		{
			while (file.ReadString(readText))
			{
				TRACE(readText+"\n");
				pos=readText.Replace(",",",");
				if (pos!=2)
				{
					continue;
				}
				pos=readText.Find(",");
				if (pos >0)
				{
					xx=readText.Left(pos);
					temp =readText.Mid(pos+1);
					pos =temp.Find(",");
					if (pos >0)
					{					
						yy=temp.Left(pos);						
						if (m_Check)
						{
							x=(float)((atof(xx)*m_Ejwdbs-m_eminx)*m_ebs)+176;	
						}
						else
						{
							x=(float)((m_emaxx-atof(xx)*m_Ejwdbs)*m_ebs)+176;
						}
						if (m_Check2)
						{
							y=(float)((atof(yy)*m_Ejwdbs-m_eminy)*m_ebs)+144;
						}
						else
						{
							y=(float)((m_emaxy-atof(yy)*m_Ejwdbs)*m_ebs)+144;
						}
						temp2=temp.Mid(pos+1);
						TRACE(temp2+"\n");
						memset(tcharArr,0x0,sizeof(tcharArr));
						swprintf((wchar_t *)tcharArr,L"%s",temp2.AllocSysString());
						
						//temppoint.X=(float)(m_dw-((m_maxx-atof(xx))*m_bs));

						Rect ellipseRect((int)x-3,(int)y-3, 6, 6);
						RectF strrect((float)x,(float)y,200.0f,20.0f);
						imageGraphics.FillEllipse(&blackBrush, ellipseRect);
						//ellipseRect.X+=6;
						imageGraphics.DrawString(
							tcharArr,
							wcslen(tcharArr),
							&myFont,
							strrect,
							&format,
							&blackBrush);
					}
				}
			}
		}	
		CLSID pngClsid;
		GetEncoderClsid(L"image/png", &pngClsid);
		image.Save(L"MAPN.skin.png", &pngClsid, NULL);
		AfxMessageBox("地图生成完成!文件名为:MAPN.skin.png");
	}	
}

void CDrawMapDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	m_CR=200;
	m_CG=200;
	m_CB=200;
	m_CSIZE=18;
	m_ER2=249;
	m_EG2=249;
	m_EB2=249;
	m_ESIZE2=16;
	UpdateData(FALSE);
}

void CDrawMapDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_CB = 63;
	m_CG = 159;
	m_CR = 220;	
	m_CSIZE = 20;
	m_ER2 = 254;
	m_EG2 = 195;
	m_EB2 = 101;
	m_ESIZE2 =18;
	UpdateData(FALSE);
}

void CDrawMapDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_Check=m_Check?FALSE:TRUE;
	if (m_Check)
	{
		TRACE("C\n");
	}
	else
	{
		TRACE("NC\n");
	}
}

void CDrawMapDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CDrawMapDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	m_Check2=m_Check2?FALSE:TRUE;
	if (m_Check2)
	{
		TRACE("C\n");
	}
	else
	{
		TRACE("NC\n");
	}
}

void CDrawMapDlg::OnBtnCarm() 
{
	// TODO: Add your control notification handler code here
	CString m_GpsFilePath;
	CFileDialog dlg(TRUE,"txt",NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,"轨迹数据文件(*.txt)|*.txt |All Files (*.*)|*.*||");
	if(dlg.DoModal()==IDOK)
	{
		m_GpsFilePath = dlg.GetPathName();
	}
	else
	{
		return ;
	}
	Image  image(L"carImg.png");
	Graphics imageGraphics(&image);
	Pen blackPen(Color(250,255,0,255),1);
	//	Pen blackPen(Color(255,230,230,230),10);
	//	Pen blackPen(Color(255,0,255,0),1);
	CStdioFile file;
	CString readText;
	CString xx,yy,temp;
	PointF pPoints[20000];
	PointF temppoint;
	PointF firstpoint;
	int pointi=0;
	int imgx,imgy;
	imgx=image.GetWidth()/2;
	imgy=image.GetHeight()/2;
	if (file.Open(m_GpsFilePath, CFile::modeRead))
	{
		while (file.ReadString(readText))
		{
			TRACE(readText+"\n");
			int pos =readText.Find(",");
			if (pos >0)
			{
				temp =readText.Mid(pos+1);
				pos =temp.Find(",");
				if (pos >0)
				{
					xx=temp.Left(pos);
					yy=temp.Mid(pos +1);
					temppoint.X=(float)(imgx+atof(xx)*m_ebs);
					temppoint.Y=(float)(imgy+atof(yy)*m_ebs);
					pPoints[pointi]=temppoint;	
					if (pointi==0)
					{
						firstpoint=temppoint;
					}
					pointi+=1;
					
				}
			}		
		}
		pPoints[pointi]=firstpoint;
		pointi+=1;
		if ( pointi > 0)
		{
			TRACE("aaa\n");
			imageGraphics.DrawLines(&blackPen, pPoints, pointi);	
			pointi=0;
		}
		
	}
	m_GpsFilePath=_T("");
	CLSID pngClsid;
	GetEncoderClsid(L"image/png", &pngClsid);
	image.Save(L"Car.skin.png", &pngClsid, NULL);
	AfxMessageBox("地图生成完成!文件名为:Car.skin.png");
}
