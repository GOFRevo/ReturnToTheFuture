#pragma once

class FRTFUtility
{
public:
	static float ReduceFloatError(const float Num, const float Err);
	static float CalcuSin(const float Near, const float Far);
	static float Interp(const float Min, const float Max, const float Cur);
};
