float piece_exp(float x){
  int a;
  x = x / log(2);
  a = *(int *)&x;
  a = (int)((x + 127) * (1 << 23));
  x = *(float *)&a;
  return x;
}

float expf_fast(float a){
  union { float f; int x; } u;
  u.x = (int) (12102203 * a + 1065353217);
  return u.f;
}

float better_expf_fast(float a){
  union { float f; int x; } u, v;
  u.x = (long long)(6051102 * a + 1065353216);
  v.x = (long long)(1065353216 - 6051102 * a);
  return u.f / v.f;
}

float fasterpow2 (float p){
  union { uint32_t i; float f; }
  v = { (1 << 23) * (p + 126.94269504088896f) }; // 127 - (-2 + log(8))/log(4)
  return v.f;
}

float fasterexp (float p){
  return fasterpow2 (1.4426950408889634f * p); // log2(e)
}

float fast_exp (float x){
  volatile union {
    float f;
    unsigned int i;
  } cvt;
  /* exp(x) = 2^i * 2^f; i = floor (log2(e) * x), 0 <= f <= 1 */
  float t = x * 1.442695041f;
  float fi = floorf (t);
  float f = t - fi;
  int i = (int)fi;
  cvt.f = (0.3371894346f * f + 0.657636276f) * f + 1.00172476f; /* compute 2^f */
  cvt.i += (i << 23);                                          /* scale by 2^i */
  return cvt.f;
}

float pade33 (float x){
  return (120 + x * (60 + x * (12 + x)))/(120 - x * (60 - x * (12 - x)));
}

float pade34 (float x){
  return (840 + x * (480 + x * (120 + x * (16 + x))))/(840 - x * (360 - x * (60 - 4*x)));
}

float spline5 (float x) {
  const int mantissa = (1 << 23);
  const int bias = 127;
  const int ishift = mantissa * bias;
  float yf, y;
  int i;
  const float s[5] = {-1.90188191959304e-3,-9.01146535969578e-3,-5.57129652016652e-2,
                      -2.40226506959101e-1, 3.06852819440055e-1};
  y = x / log(2);
  yf  = y - floorf(y);
  y = y - ((((s[0] * yf + s[1]) * yf + s[2]) * yf + s[3]) * yf + s[4]) * yf;
  i = mantissa * y + ishift;
  y = *(float *)&i;
  return y;
}

float spline3 (float x) {
  const int mantissa = (1 << 23);
  const int bias = 127;
  const int ishift = mantissa * bias;
  float yf, y;
  int i;
  const float s[3] = {-7.6167541742324804e-2,-0.23141283591588344,0.30758037765820823};
  y = x / log(2);
  yf  = y - floorf(y);
  y = y - ((s[0] * yf + s[1]) * yf + s[2]) * yf;
  i = mantissa * y + ishift;
  y = *(float *)&i;
  return y;
}

float fastExp4(float x){  // quartic spline approximation
  union { float f; int32_t i; } reinterpreter;
  reinterpreter.i = (int32_t)(12102203.0f*x) + 127*(1 << 23);
  // printf("%f\n", reinterpreter.f);
  int32_t m = (reinterpreter.i >> 7) & 0xFFFF;  // copy mantissa 0xFFFF;
  printf("%d\n",m);
  // empirical values for small maximum relative error (1.21e-5):
  reinterpreter.i += (((((((((((3537*m) >> 16) + 13668)*m) >> 18) + 15817)*m) >> 14) - 80470)*m) >> 11);
  printf("%d\n",reinterpreter.i);

  return reinterpreter.f;
}

float fastExp3(float x){  // cubic spline approximation
  union { float f; int32_t i; } reinterpreter;
  reinterpreter.i = (int32_t)(12102203.0f*x) + 127*(1 << 23); //(1 << 23) / log(2) = 12102203.0f КОНСТАНТА тА ЗМІЩЕННЯ НА 23 БІТА ПО МАНТИСІ
  int32_t m = (reinterpreter.i >> 7) & 0xFFFF;  // copy mantissa 0xFFFF;
  // empirical values for small maximum relative error (8.34e-5):
  reinterpreter.i += ((((((((1277*m) >> 14) + 14825)*m) >> 14) - 79749)*m) >> 11) - 626;
  return reinterpreter.f;
}


// -------------------------- taylor_series hibrid ---------------------------
float texp(float x){
  float last=1.0;
  float sum=1.0;
  if(x<0) return 1 / texp(-x);
  for(int i = 1; i < 7; i++) { last *= x / i; sum += last; }
  return sum;
}

float taylor_series(float x){
  float sum = 1.0, last = 1.0;
  for(int i = 1; i < 7; i++) {
    last *= x / i;    //multiply the last term in the series from the previous term by x/n
    sum += last; //add this new last term to the sum
  }
  return sum;
}

float hybrid(float x){
  float temp;
  if (-0.5 <= x && x <= 0.5) {
    return taylor_series(x);
  } else {
    temp = hybrid(x / 2);
    return (temp * temp);
  }
}

const float coeff_4 = 0.006935931 , coeff_3 = 0.019890581;
const float coeff_2 = 0.143440676 , coeff_1 = 4.831794110;
const float coeff_0 = 1. , onebylog2 = 1.442695041;
const int offset_127 = 127 , shift_23 = 23;
const float min_x = -88.;

float exp_appr ( float x ){
  if ( x > min_x ){
    x *= onebylog2 ;
     union {int i ; float f ;}
     f1 = {( int) x };
     x -= f1 . i ;
     float f2 = x , x_tmp = x ;
     f1.i += offset_127 ;
     f1.i <<= shift_23 ;
     f2 *= coeff_4;
     x_tmp += coeff_1;
     f2 += coeff_3;
     x_tmp *= x ;
     f2 *= x ;
     f2 += coeff_2 ;
     f2 *= x_tmp ;
     f2 += coeff_0 ;

     return f1.f * f2 ;
   }
 return 0.;
 }
