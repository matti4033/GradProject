#pragma once
#include "CoreMinimal.h"

struct FSpiderFABRIK
{
	static void Solve(TArray<FVector>& Chain,
		const FVector& Target,
		int32 Iterations = 10,
		float Tolerance = 0.1f)
	{
		if (Chain.Num() < 2) return;

		//Bone Lengths saving!
		TArray<float> Lengths;
		for (int32 i = 0; i < Chain.Num() - 1; i++)
		{
			Lengths.Add(FVector::Dist(Chain[i], Chain[i + 1]));
		}

		FVector Root = Chain[0];

		for(int32 Iter = 0; Iter < Iterations; Iter++)
		{
			if (FVector::Dist(Chain.Last(), Target) < Tolerance) break;

			//FOrward pass
			Chain.Last() = Target;
			for (int32 i = Chain.Num() - 2; i >= 0; i--)
			{
				FVector Dir = (Chain[i] - Chain[i + 1]).GetSafeNormal();
				Chain[i] = Chain[i + 1] + Dir * Lengths[i];
			}

			//Backward paass
			Chain[0] = Root;
			for (int32 i = 0; i < Chain.Num() - 1; i++)
			{
				FVector Dir = (Chain[i + 1] - Chain[i]).GetSafeNormal();
				Chain[i + 1] = Chain[i] + Dir * Lengths[i];
			}
		}

	}
};