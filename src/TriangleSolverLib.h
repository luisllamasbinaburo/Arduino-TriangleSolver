/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
#ifndef _TRIANGLESOLVERLIB_h
#define _TRIANGLESOLVERLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class TriangleSolver
{
public:
	bool Solve(bool preferObtuse = false);

	float& A = sides[0];
	float& B = sides[1];
	float& C = sides[2];
	float& Alpha = angles[0];
	float& Beta = angles[1];
	float& Gamma = angles[2];

	void UpdateA(float a) const { A = a; Alpha = 0.0; Beta = 0.0; Gamma = 0.0; }
	void UpdateB(float b) const { B = b; Alpha = 0.0; Beta = 0.0; Gamma = 0.0; }
	void UpdateC(float c) const { C = c; Alpha = 0.0; Beta = 0.0; Gamma = 0.0; }

	void UpdateAlpha(float alpha) const { Alpha = alpha; A = 0.0; Beta = 0.0; Gamma = 0.0; }
	void UpdateBeta(float beta) const { Beta = beta; Alpha = 0.0; B = 0.0; Gamma = 0.0; }
	void UpdateGamma(float gamma) const { Gamma = gamma; Alpha = 0.0; Beta = 0.0; C = 0.0; }

private:
	float sides[3];
	float angles[3];

	void Solve3Sides() const;
	void Solve2Sides(bool preferObtuse);
	void Solve2SidesOposite(byte angleId, bool preferObtuse);
	void Solve2SidesAdjacent(byte sideId);
	void Solve1Side();
	void SolveAngles();

	byte CountSides();

	static float SolveCosine(float L1, float L2, float angle3);
	
	static float SolveInverseCosine(float L1, float L2, float L3);

	static float SolveSin(float L1, float angle1, float angle2);
	static float SolveInverseSin(float L1, float angle1, float L2);

	static byte findFirstEmpty(float *values);

	static byte findFirstNonEmpty(float *values);

	static byte nextIndex(byte index) { return (index + 1 ) % 3; }

	static byte prevIndex(byte index) { return (index - 1 + 3) % 3; }

	static byte fixIndex(byte index) { return index % 3; }
};
#endif

