#pragma once

class FRTFUtility
{
public:
	static float ReduceFloatError(const float Num, const float Err);
	static float CalcuSin(const float Near, const float Far);
	static float Interp(const float Min, const float Max, const float Cur);
	static bool Prob(const float Prob);
	static bool IsSameMark(const float Lhs, const float Rhs);
	static float GetDirection(const float Num);
};
