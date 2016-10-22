#pragma once
#include "Shape.h"
#include "Paint.h"
int PaintLine(HDC * _hdc, const CPoint &, const CPoint &, const int &, void *);
class CLine :
	public CShape
{
private:

public:
	CLine();
	CLine(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum = 0, void* _moreData = nullptr);
	virtual ~CLine();

	virtual CPoint GetLeftTop() const;
	virtual CPoint GetRightBottom() const;
	virtual int GetMoreDataElementNum() const;
	virtual void* GetMoreData() const;
	virtual CShape* Create() const;
	virtual CShape* Create(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum = 0, void* _moreData = nullptr) const;
	virtual CShape* Clone() const;
	virtual int Paint() const;

	virtual int SetData(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum = 0, void* _moreData = nullptr);

};

