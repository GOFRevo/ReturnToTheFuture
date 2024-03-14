#include "RTFUtility.h"

float FRTFUtility::ReduceFloatError(const float Num, const float Err)
{
	if(FMath::Abs(Num) < Err) return 0.0f;
	return Num;
}

float FRTFUtility::CalcuSin(const float Near, const float Far)
{
	return Far / FMath::Sqrt(Near * Near + Far * Far);
}

float FRTFUtility::Interp(const float Min, const float Max, const float Cur)
{
	return (Cur - Min) / (Max - Min);
}

bool FRTFUtility::Prob(const float Prob)
{
	return FMath::RandRange(0.0f, 1.0f) < Prob;
}

bool FRTFUtility::IsSameMark(const float Lhs, const float Rhs)
{
	return Lhs * Rhs > 0.0f;
}

float FRTFUtility::GetDirection(const float Num)
{
	return Num > 0.0f? 1.0f: -1.0f;
}






