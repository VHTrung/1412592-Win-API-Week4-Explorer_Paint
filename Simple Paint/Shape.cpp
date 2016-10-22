#include "stdafx.h"
#include "Shape.h"



CShape::~CShape()
{
}

int CShape::SetData(const CPoint & _leftTop, const CPoint & _rightBottom, const int & _moreDataElemantNum, void * _moreData)
{
	m_leftTop = _leftTop;
	m_rightBottom = _rightBottom;
	if (_moreDataElemantNum != 0 || _moreData != nullptr)// parameters are ignored
		return 1;
	return 0;
}
