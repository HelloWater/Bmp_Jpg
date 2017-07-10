#include "stdafx.h"
#include <afx.h>
#include <afxwin.h>         
#include <afxext.h>
#include "BmpToJpg.h"
//#include <Gdiplus.h> 
//#include <GdiPlusEnums.h> 
//#include ".\gdijpegutil.h"

using namespace Gdiplus; 


CBmpToJpg::CBmpToJpg(void)
{

}

CBmpToJpg::~CBmpToJpg(void)
{
}

WCHAR *CBmpToJpg::BStr2WStr(const char *pSource, int &iDstLen)
{
	iDstLen = MultiByteToWideChar(0, 0, pSource, (int)strlen(pSource), NULL, 0);
	WCHAR *pWDst = new WCHAR[iDstLen + 1];
	memset(pWDst, 0, sizeof(WCHAR) * (iDstLen + 1));
	MultiByteToWideChar(0, 0, pSource, (int)strlen(pSource), pWDst, iDstLen);
	return pWDst;
}

int GetCodecClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0;
	UINT size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
	{
		return -1;
	}

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
	{
		return -1;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);

	return -1;
}

// iQuality:ͼ������ 0~100
bool CBmpToJpg::BMPToJPG(const char *pBmpFile, const char *pJpgFile, long iQuality)
{
	bool bRet = false;
	try
	{
		CLSID codecClsid;
		EncoderParameters encoderParameters;
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		int iLen = 0;
		WCHAR *pWBmpFile = BStr2WStr(pBmpFile, iLen);
		WCHAR *pWJpegFile = BStr2WStr(pJpgFile, iLen);

		GetCodecClsid(L"image/jpeg", &codecClsid);

		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		encoderParameters.Parameter[0].Value = &iQuality;

		Image *pImage = new Image(pWBmpFile);
		Status bStatus = pImage->Save(pWJpegFile, &codecClsid, &encoderParameters);
		delete pImage;

		delete pWBmpFile;
		delete pWJpegFile;

		GdiplusShutdown(gdiplusToken); 
		if (bStatus == Ok)
		{
			bRet = true;
		}
	}
	catch (...)
	{
	}
	return bRet;
}

bool CBmpToJpg::JPGToBMP(const char *pJpgFile, const char *pBmpFile)
{
	bool bRet = false;
	try
	{
		CLSID codecClsid;
		EncoderParameters encoderParameters;
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		int iLen = 0;
		WCHAR *pWBmpFile = BStr2WStr(pBmpFile, iLen);
		WCHAR *pWJpegFile = BStr2WStr(pJpgFile, iLen);

		GetCodecClsid(L"image/bmp", &codecClsid);

		encoderParameters.Count = 0;

		Image *pImage = new Image(pWJpegFile);
		Status bStatus = pImage->Save(pWBmpFile, &codecClsid, &encoderParameters);
		delete pImage;

		delete pWBmpFile;
		delete pWJpegFile;

		GdiplusShutdown(gdiplusToken); 
		if (bStatus == Ok)
		{
			bRet = true;
		}
	}
	catch (...)
	{
	}
	return bRet;
}

bool CBmpToJpg::AddFont(const char *pSrcName, const char *pDstName, const char *pText, int iXPos, int iYPos)
{
	CLSID codecClsid;
	EncoderParameters encoderParameters;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	int iLen = 0;
	WCHAR *pWSrcFile = BStr2WStr(pSrcName, iLen);
	WCHAR *pWDstFile = BStr2WStr(pDstName, iLen);
	WCHAR *pWText = BStr2WStr(pText, iLen);

	Image *pImage = new Image(pWSrcFile);
	Graphics *pGraph = new Graphics(pImage);
	SolidBrush *pBrush = new SolidBrush(Color::Black);
	FontFamily fontFamily(L"����");
	Gdiplus::Font font(&fontFamily, 16, FontStyleRegular, UnitPoint);
	PointF fontPoint((REAL)iXPos, (REAL)iYPos);

	pGraph->DrawString(pWText, (INT)wcslen(pWText), &font, fontPoint, pBrush);

	GetCodecClsid(L"image/bmp", &codecClsid);
	encoderParameters.Count = 0;
	Status bStatus = pImage->Save(pWDstFile, &codecClsid, &encoderParameters);
	delete pWText;
	delete pWDstFile;
	delete pWSrcFile;
	delete pGraph;
	delete pImage;
	return true;
}