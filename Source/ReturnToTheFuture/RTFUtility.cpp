#include "RTFUtility.h"

float FRTFUtility::ReduceFloatError(const float Num, const float Err)
{
	if(FMath::Abs(Num) < Err) return 0.0f;
	return Num;
}

