/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

TriangleSolver triang;

void debug()
{
	Serial.println(triang.A, 4);
	Serial.println(triang.B, 4);
	Serial.println(triang.C, 4);
	Serial.println(degrees(triang.Alpha), 4);
	Serial.println(degrees(triang.Beta)), 4;
	Serial.println(degrees(triang.Gamma), 4);
}

void setup() {
	Serial.begin(115200);
	
	triang.A = 50; 
	triang.C = 25.39;
	triang.Gamma = radians(30);
	triang.Solve(true);
	debug();

}

void loop() 
{
	// do nothing
	delay(1000);
}
