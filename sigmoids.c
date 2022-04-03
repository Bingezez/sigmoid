float teylor_tanh(float x){
	float x2 = x * x;
	float x4 = x2 * x2;
	float x6 = x4 * x2;
	float x8 = x4 * x4;
	float x10 = x8 * x2;
	return x - (x2*x)/3 + (2*x4*x)/15 - (17*x6*x)/315 + (62*x8*x)/2835 - (1382*x10*x)/155925;
}

float tanh1_2(float x){
  float x2 = x * x;
  float a = x * 3;
  float b = 3 + x2;
  return a / b;
}

float tanh3_2(float x){
  float x2 = x * x;
  float a = x * (15 + x2);
  float b = (15 + 6 * x2);
  return a / b;
}

float tanh3_4(float x){
  float x2 = x * x;
  float a = x * (105 + 10 * x2);
  float b = (105 + 45 * x2 * (1 + x2));
  return a / b;
}

float tanh5_4(float x){
  float x2 = x * x;
  float a = x * (945 + 105 * x2 * (1 + x2));
  float b = (945 + x2 * (420 + 15 * x2));
  return a / b;
}

float tanh5_6(float x){
  float x2 = x * x;
  float a = x * (10395 + x2 * (1260 + 21 * x2));
  float b = (10395 + x2 * (4725 + x2 * ( 210 + x2)));
  return a / b;
}

float fast_tanh(float x){
  float x2 = x * x;
  float a = x * (135135.0f + x2 * (17325.0f + x2 * (378.0f + x2)));
  float b = 135135.0f + x2 * (62370.0f + x2 * (3150.0f + x2 * 28.0f));
  return a / b;
}

float tanh7_8(float x){
  float x2 = x * x;
  float a = x * (2027025 + x2 * (270270 + x2 * (6930 + 36 * x2)));
  float b = (2027025 + x2 * (945945 + x2 * (51975 + x2 * (630 + x2))));
  return a / b;
}


float fast_tanh3(float v){
  const float c1 = 0.03138777F;
  const float c2 = 0.276281267F;
	const float c_log2f = 1.442695022F;
  v = v * c_log2f;
  int intPart = (int)v;
  float x = (v - intPart);
  float xx = x * x;
  float v1 = c_log2f + c2 * xx;
  float v2 = x + xx * c1 * x;
  float v3 = (v2 + v1);
  *((int*)&v3) += intPart << 24;
  float v4 = v2 - v1;
	// printf("%f - %f\n", v3, v4);
  return (v3 + v4) / (v3 - v4);
}

// float tanh_c3(float v)
// {
//     const float c1 = 3.606761932F;
//     const float c2 = 0.1153258756F;
//     const float c3 = 5.20338583F;
//     const float c_log2f = 1.442695022F;
//     v *= c_log2f;
//     int intPart = (int)v;
//     float x = (v - intPart);
//     float xx = x * x;
//     float v1 = c3 + xx;
//     float v2 = x * (c1 + xx * c2);
//     float v3 = (v2 + v1);
//     reinterpret_cast<int &>(v3) += intPart << 23;24;
//     float v4 = v2 - v1;
//     float res = (v3 + v4) / (v3 - v4);
//     return res;
// }
// float fast_tanh3(float v){
// 	const float c1 = 3.606761932F;
// 	const float c2 = 0.1153258756F;
// 	const float c3 = 5.20338583F;
// 	const float c_log2f = 1.442695022F;
// 	v *= c_log2f;
// 	int intPart = (int)v;
// 	float x = (v - intPart);
// 	float xx = x * x;
// 	float v1 = c3 + xx;
// 	float v2 = x * (c1 + xx * c2);
// 	float v3 = (v2 + v1);
//   *((int*)&v3) += intPart << 24;
//   float v4 = v2 - v1;
// 	// printf("%f - %f\n", v3, v4);
//   return (v3 + v4) / (v3 - v4);
// }
// -----------------

float sign(float x){
	if (x > 0) {return 1;}
	if (x == 0){return 0;}
	if (x < 0) {return -1;}
}

float eexxpp(float x){
	float x2 = x * x;
	float x4 = x2 * x2;
	return (float) (1 + fabs(x) + 0.5658 * x2 + 0.143 * x4);
}

float ttanhh(float x) {
	return sign(x)*((eexxpp(x) - 1/(eexxpp(x))) / (eexxpp(x) + 1/(eexxpp(x))));
}


float orig_tanh(float x, float (*fun)(float)){
	return (float)(((*fun)(x) - (*fun)(-x)) / ((*fun)(x) + (*fun)(-x)));
}

float tanhfast(float x) {
x = x / 3.4f;
x = x * 0.5f;
x = abs(x+0.5f) - abs(x-0.5f);
x = (abs(x)-2)*x;
return (abs(x)-2)*x;
}
