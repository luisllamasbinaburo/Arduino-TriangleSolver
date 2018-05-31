/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#include "TriangleSolverLib.h"

bool TriangleSolver::Solve(bool preferObtuse = false)
{
	const byte sideCounter = CountSides();

	if(sideCounter == 0) return false;

	if (sideCounter == 1)
	{
		Solve1Side();
	}
	else if (sideCounter == 2)
	{
		Solve2Sides(preferObtuse);
	}
	else
	{
		Solve3Sides();
	}

	return true;
}

void TriangleSolver::Solve3Sides() const
{
	Alpha = SolveInverseCosine(B, C, A);
	Beta = SolveInverseCosine(C, A, B);
	Gamma = PI - Alpha - Beta;
}

void TriangleSolver::Solve2Sides(bool preferObtuse)
{
	const byte angleId = findFirstNonEmpty(angles);

	if (sides[angleId] != 0.0) Solve2SidesOposite(angleId, preferObtuse);
	else Solve2SidesAdjacent(angleId);
}

void TriangleSolver::Solve2SidesOposite(byte angleId, bool preferObtuse)
{
	Serial.println("2SidesOposites");
	const byte prevSideId = prevIndex(angleId);
	const byte nextSideId = nextIndex(angleId);

	const byte missingId = sides[prevSideId] == 0.0 ? prevSideId : nextSideId;
	const byte adjacentSideId = sides[prevSideId] != 0.0 ? prevSideId : nextSideId;

	angles[adjacentSideId] = SolveInverseSin(sides[angleId], angles[angleId], sides[adjacentSideId]);
	if (preferObtuse) angles[adjacentSideId] = PI - angles[adjacentSideId];

	angles[missingId] = PI - angles[angleId] - angles[adjacentSideId];


	sides[missingId] = SolveSin(sides[angleId], angles[angleId], angles[missingId]);
}

void TriangleSolver::Solve2SidesAdjacent(byte sideId)
{
	const byte prevSideId = prevIndex(sideId);
	const byte nextSideId = nextIndex(sideId);

	sides[sideId] = SolveCosine(sides[prevSideId], sides[nextSideId], angles[sideId]);

	Solve3Sides();
}

void TriangleSolver::Solve1Side()
{
	SolveAngles();

	const byte sideId = findFirstNonEmpty(sides);
	const byte prevSideId = prevIndex(sideId);
	const byte nextSideId = nextIndex(sideId);

	sides[prevSideId] = SolveSin(sides[sideId], angles[sideId], angles[prevSideId]);
	sides[nextSideId] = SolveSin(sides[sideId], angles[sideId], angles[nextSideId]);
}

void TriangleSolver::SolveAngles()
{
	const byte missingAngle = findFirstEmpty(angles);
	angles[missingAngle] = PI - angles[prevIndex(missingAngle)] - angles[nextIndex(missingAngle)];
}

byte TriangleSolver::CountSides()
{
	byte rst = 0;
	for (byte i = 0; i < 3; i++)
	{
		if (sides[i] != 0.0) rst++;
	}
	return rst;
}

float TriangleSolver::SolveCosine(float L1, float L2, float angle3)
{
	const float L3 = sqrt(L1 * L1 + L2 * L2 - 2 * L1 * L2 * cos(angle3));
	return L3;
}

float TriangleSolver::SolveInverseCosine(float L1, float L2, float L3)
{
	const float angle3 = acos((L1 * L1 + L2 * L2 - L3 * L3) /  (2 * L1 * L2));
	return angle3;
}

float TriangleSolver::SolveSin(float L1, float angle1, float angle2)
{
	const float L2 = L1 * sin(angle2) / sin(angle1);
	return L2;
}

float TriangleSolver::SolveInverseSin(float L1, float angle1, float L2)
{
	const float angle2 = asin(L2 / L1 * sin(angle1));
	return angle2;
}

byte TriangleSolver::findFirstEmpty(float* values)
{
	for (byte i = 0; i < 3; i++)
	{
		if (values[i] == 0.0) return i;
	}
	return 0;
}

byte TriangleSolver::findFirstNonEmpty(float* values)
{
	for (byte i = 0; i < 3; i++)
	{
		if (values[i] != 0.0) return i;
	}
	return 0;
}
