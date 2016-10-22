#pragma once
#include "Point.h"

class CShape
{
protected:
	CPoint m_leftTop;
	CPoint m_rightBottom;

public:
	virtual ~CShape();

	virtual CPoint GetLeftTop() const = 0;
	virtual CPoint GetRightBottom() const = 0;
	virtual int GetMoreDataElementNum() const = 0;
	virtual void* GetMoreData() const = 0;
	virtual CShape* Create() const = 0;
	virtual CShape* Create(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum = 0, void* _moreData = nullptr) const = 0;
	virtual CShape* Clone() const = 0;
	virtual int Paint()const = 0;

	virtual int SetData(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum = 0, void* _moreData = nullptr);
};

