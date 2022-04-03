static inline __m128 _mm_abs_ps_2(__m128 x) {
  __m128 signMask = _mm_set1_ps(-0.0f);
  return _mm_andnot_ps(signMask, x);
}

static inline __m256 absavx(__m256 x) {
  __m256 _o0 = _mm256_set1_ps(-0.0f);
  return _mm256_andnot_ps(_o0, x);
}

// ---------------------------------- SSE --------------------------------------
__m128 tanhsse2(__m128 x){
  __m128 _o34 = _mm_set1_ps(3.4);
  __m128 _o05 = _mm_set1_ps(0.5);
  __m128 _o20 = _mm_set1_ps(2);
  __m128 d;
  d = _mm_div_ps(x, _o34);        //         x / 3.4f;
  d = _mm_mul_ps(d,_o05);         //         x * 0.5f;
  d = _mm_sub_ps(_mm_abs_ps_2(_mm_add_ps(d, _o05)), _mm_abs_ps_2(_mm_sub_ps(d, _o05))); // fabs(x + 0.5f) - fabs(x - 0.5f);
  d = _mm_mul_ps(_mm_sub_ps(_mm_abs_ps_2(d), _o20), d);
  __m128 res = _mm_mul_ps(_mm_sub_ps(_mm_abs_ps_2(d), _o20), d);
  return _mm_castsi128_ps((__m128i)res);
}

__m128 tanhsse(__m128 x){
  __m128 _o135135 = _mm_set1_ps(135135.0);
  __m128 _o17325  = _mm_set1_ps(17325.0);
  __m128 _o378    = _mm_set1_ps(378.0);
  __m128 _o62370  = _mm_set1_ps(62370.0);
  __m128 _o3150   = _mm_set1_ps(3150.0);
  __m128 _o28     = _mm_set1_ps(28.0);
  __m128 x2 = _mm_mul_ps(x, x);
  __m128 a = _mm_mul_ps(x,_mm_add_ps(_o135135, _mm_mul_ps(x2, _mm_add_ps(_o17325, _mm_mul_ps(x2,_mm_add_ps(_o378, x2))))));
  // a = x * (135135.0f + x2 * (17325.0f + x2 * (378.0f + x2)));
  __m128 b = _mm_add_ps(_o135135, _mm_mul_ps(x2, _mm_add_ps(_o62370, _mm_mul_ps(x2, _mm_add_ps(_o3150, _mm_mul_ps(x2,_o28))))));
  // b = 135135.0f + x2 * (62370.0f + x2 * (3150.0f + x2 * 28.0f));
  __m128 res =  _mm_div_ps(a, b);
  return _mm_castsi128_ps((__m128i)res);
}

__m128 tanhsse_exp(__m128 x){
  __m128 _o1 = _mm_set1_ps(1.0);
  __m128 r = _mm_div_ps(_mm_sub_ps(x,_mm_div_ps(_o1,x)),_mm_add_ps(x,_mm_div_ps(_o1,x)));
  return _mm_castsi128_ps((__m128i)r);
}

__m128 FastExpSsee(__m128 x){
    __m128 a = _mm_set1_ps (12102203.0f); /* (1 << 23) / log(2) */
    __m128i b = _mm_set1_epi32 (127 * (1 << 23) - 298765);
    __m128i t = _mm_add_epi32 (_mm_cvtps_epi32 (_mm_mul_ps (a, x)), b);
    return _mm_castsi128_ps (t);
}

__m128 ssespline3(__m128 x){
  __m128 _omantis = _mm_set1_ps(1<<23);
  __m128 _obias = _mm_set1_ps(127);
  __m128i _oshift = _mm_set1_epi32(1065353216);
  __m128 _olog2 = _mm_set1_ps(0.6931471805599453f);
  const __m128 _oconst1 = _mm_set1_ps(-7.6167541742324804e-2f);
  const __m128 _oconst2 = _mm_set1_ps(-0.23141283591588344f);
  const __m128 _oconst3 = _mm_set1_ps(0.30758037765820823f);
  __m128 y = _mm_div_ps(x,_olog2);
  __m128 yf = _mm_sub_ps(y,_mm_floor_ps(y));
  __m128 yy = _mm_sub_ps(y, _mm_mul_ps(yf,_mm_add_ps(_oconst3,_mm_mul_ps(yf,_mm_add_ps(_oconst2,_mm_mul_ps(yf,_oconst1))))));
  __m128i res = _mm_add_epi32(_oshift,_mm_cvtps_epi32(_mm_mul_ps(_omantis,yy)));
  return _mm_castsi128_ps (res);
}

__m128 ssespline5(__m128 x){
  __m128 _omantis = _mm_set1_ps(1<<23);
  __m128 _obias = _mm_set1_ps(127);
  __m128i _oshift = _mm_set1_epi32(1065353216);
  __m128 _olog2 = _mm_set1_ps(0.6931471805599453f);
  const __m128 _oconst1 = _mm_set1_ps(-1.90188191959304e-3f);
  const __m128 _oconst2 = _mm_set1_ps(-9.01146535969578e-3f);
  const __m128 _oconst3 = _mm_set1_ps(-5.57129652016652e-2f);
  const __m128 _oconst4 = _mm_set1_ps(-2.40226506959101e-1f);
  const __m128 _oconst5 = _mm_set1_ps(3.06852819440055e-1f);
  __m128 y = _mm_div_ps(x,_olog2);
  __m128 yf = _mm_sub_ps(y,_mm_floor_ps(y));
  __m128 yy = _mm_sub_ps(y, _mm_mul_ps(yf,_mm_add_ps(_oconst5,_mm_mul_ps(yf,_mm_add_ps(_oconst4,_mm_mul_ps(yf,_mm_add_ps(_oconst3,_mm_mul_ps(yf,_mm_add_ps(_oconst2,_mm_mul_ps(yf,_oconst1))))))))));
  __m128i res = _mm_add_epi32(_oshift,_mm_cvtps_epi32(_mm_mul_ps(_omantis,yy)));
  return _mm_castsi128_ps (res);
}

__m128 ssepade34(__m128 x){
  __m128 _o840 = _mm_set1_ps(840);
  __m128 _o480 = _mm_set1_ps(480);
  __m128 _o120 = _mm_set1_ps(120);
  __m128 _o16 = _mm_set1_ps(16);
  __m128 _o360 = _mm_set1_ps(360);
  __m128 _o60 = _mm_set1_ps(60);
  __m128 _o4 = _mm_set1_ps(4);
  __m128 a = _mm_add_ps(_o840, _mm_mul_ps(x,_mm_add_ps(_o480,_mm_mul_ps(x,_mm_add_ps(_o120,_mm_mul_ps(x,_mm_add_ps(_o16,x)))))));
  __m128 b = _mm_sub_ps(_o840, _mm_mul_ps(x,_mm_sub_ps(_o360,_mm_mul_ps(x,_mm_sub_ps(_o60,_mm_mul_ps(x,_o4))))));
  __m128 res = _mm_div_ps(a,b);
  return _mm_castsi128_ps ((__m128i)res);
}


//https://overcoder.net/q/2538751/%D0%BA%D0%B0%D0%BA-%D0%B2%D1%8B-%D0%BE%D0%B1%D1%80%D0%B0%D0%B1%D0%B0%D1%82%D1%8B%D0%B2%D0%B0%D0%B5%D1%82%D0%B5-exp-%D1%81-sse2

// ------------------------------------- AVX -----------------------------------
__m256 tanhavx2(__m256 x){
  __m256 _m34 = _mm256_set1_ps(3.4f);
  __m256 _o05 = _mm256_set1_ps(0.5f);
  __m256 _o20 = _mm256_set1_ps(2.0f);
  __m256 d;
  d = _mm256_setzero_ps();
  d = _mm256_div_ps(x, _m34);        //         x / 3.4f;
  d = _mm256_mul_ps(d,_o05);             //         x * 0.5f;
  d = _mm256_sub_ps(absavx(_mm256_add_ps(d, _o05)), absavx(_mm256_sub_ps(d, _o05))); // fabs(x + 0.5f) - fabs(x - 0.5f);
  d = _mm256_mul_ps(_mm256_sub_ps(absavx(d), _o20), d);
  __m256 res = _mm256_mul_ps(_mm256_sub_ps(absavx(d), _o20), d);
  return _mm256_castsi256_ps((__m256i)res);
}

__m256 tanhavx(__m256 x){
  __m256 _o135135 = _mm256_set1_ps(135135.0f);
  __m256 _o17325  = _mm256_set1_ps(17325.0f);
  __m256 _o378    = _mm256_set1_ps(378.0f);
  __m256 _o62370  = _mm256_set1_ps(62370.0f);
  __m256 _o3150   = _mm256_set1_ps(3150.0f);
  __m256 _o28     = _mm256_set1_ps(28.0f);
  __m256 a, b, x2;
  x2 = _mm256_mul_ps(x, x);
  a = _mm256_mul_ps(x,_mm256_add_ps(_o135135, _mm256_mul_ps(x2, _mm256_add_ps(_o17325, _mm256_mul_ps(x2,_mm256_add_ps(_o378, x2))))));
  // a = x * (135135.0f + x2 * (17325.0f + x2 * (378.0f + x2)));
  b = _mm256_add_ps(_o135135, _mm256_mul_ps(x2, _mm256_add_ps(_o62370, _mm256_mul_ps(x2, _mm256_add_ps(_o3150, _mm256_mul_ps(x2,_o28))))));
  // b = 135135.0f + x2 * (62370.0f + x2 * (3150.0f + x2 * 28.0f));
  __m256 res =  _mm256_div_ps(a, b);
  return _mm256_castsi256_ps((__m256i)res);
}

__m256 tanhavx_exp(__m256 x){
  __m256 _o1 = _mm256_set1_ps(1.0f);
  __m256 r = _mm256_div_ps(_mm256_sub_ps(x,_mm256_div_ps(_o1,x)),_mm256_add_ps(x,_mm256_div_ps(_o1,x)));
  return _mm256_castsi256_ps((__m256i)r);
}

__m256 avxpade34(__m256 x){
  __m256 _o840 = _mm256_set1_ps(840.0f);
  __m256 _o480 = _mm256_set1_ps(480.0f);
  __m256 _o120 = _mm256_set1_ps(120.0f);
  __m256 _o16 = _mm256_set1_ps(16.0f);
  __m256 _o360 = _mm256_set1_ps(360.0f);
  __m256 _o60 = _mm256_set1_ps(60.0f);
  __m256 _o4 = _mm256_set1_ps(4.0f);
  __m256 a = _mm256_add_ps(_o840, _mm256_mul_ps(x,_mm256_add_ps(_o480,_mm256_mul_ps(x,_mm256_add_ps(_o120,_mm256_mul_ps(x,_mm256_add_ps(_o16,x)))))));
  __m256 b = _mm256_sub_ps(_o840, _mm256_mul_ps(x,_mm256_sub_ps(_o360,_mm256_mul_ps(x,_mm256_sub_ps(_o60,_mm256_mul_ps(x,_o4))))));
  __m256i res = _mm256_cvtps_epi32(_mm256_div_ps(a,b));
  return _mm256_castsi256_ps(res);
}

__m256 FastExpAvx(__m256 x){
    __m256 a = _mm256_set1_ps(12102203.0f);
    __m256i b = _mm256_set1_epi32(127 * (1 << 23) - 298765);
    __m256i t = _mm256_add_epi32(_mm256_cvtps_epi32(_mm256_mul_ps(a, x)), b);
    return _mm256_castsi256_ps(t);
}

__m256 avxspline3(__m256 x){
  __m256 _omantis = _mm256_set1_ps(1<<23);
  __m256 _obias = _mm256_set1_ps(127);
  __m256i _oshift = _mm256_set1_epi32(1065353216);
  __m256 _olog2 = _mm256_set1_ps(0.6931471805599453f);
  const __m256 _oconst1 = _mm256_set1_ps(-7.6167541742324804e-2f);
  const __m256 _oconst2 = _mm256_set1_ps(-0.23141283591588344f);
  const __m256 _oconst3 = _mm256_set1_ps(0.30758037765820823f);
  __m256 y = _mm256_div_ps(x,_olog2);
  __m256 yf = _mm256_sub_ps(y,_mm256_floor_ps(y));
  __m256 yy = _mm256_sub_ps(y, _mm256_mul_ps(yf,_mm256_add_ps(_oconst3,_mm256_mul_ps(yf,_mm256_add_ps(_oconst2,_mm256_mul_ps(yf,_oconst1))))));
  __m256i res = _mm256_add_epi32(_oshift,_mm256_cvtps_epi32(_mm256_mul_ps(_omantis,yy)));
  return _mm256_castsi256_ps (res);
}

__m256 avxspline5(__m256 x){
  __m256 _omantis = _mm256_set1_ps(1<<23);
  __m256 _obias = _mm256_set1_ps(127);
  __m256i _oshift = _mm256_set1_epi32(1065353216);
  __m256 _olog2 = _mm256_set1_ps(0.6931471805599453f);
  const __m256 _oconst1 = _mm256_set1_ps(-1.90188191959304e-3f);
  const __m256 _oconst2 = _mm256_set1_ps(-9.01146535969578e-3f);
  const __m256 _oconst3 = _mm256_set1_ps(-5.57129652016652e-2f);
  const __m256 _oconst4 = _mm256_set1_ps(-2.40226506959101e-1f);
  const __m256 _oconst5 = _mm256_set1_ps(3.06852819440055e-1f);
  __m256 y = _mm256_div_ps(x,_olog2);
  __m256 yf = _mm256_sub_ps(y,_mm256_floor_ps(y));
  __m256 yy = _mm256_sub_ps(y, _mm256_mul_ps(yf,_mm256_add_ps(_oconst5,_mm256_mul_ps(yf,_mm256_add_ps(_oconst4,_mm256_mul_ps(yf,_mm256_add_ps(_oconst3,_mm256_mul_ps(yf,_mm256_add_ps(_oconst2,_mm256_mul_ps(yf,_oconst1))))))))));
  __m256i res = _mm256_add_epi32(_oshift,_mm256_cvtps_epi32(_mm256_mul_ps(_omantis,yy)));
  return _mm256_castsi256_ps (res);
}
// --------------------------------------CREATE Vector`s -----------------------

void vector(float n, float i, __m128 (*fun)(__m128)){
  float invn = -n;
  int nn = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x = (float *)_mm_malloc((nn+1) * sizeof(float), 16);
  float *res = (float *)_mm_malloc((nn+1) *sizeof(float), 16);
  invn = -n;
  for (uint64_t ii = 0; ii < nn; ii++, invn+=i){
    x[ii] = invn;
  }
  for (uint64_t i = 0; i < nn; i+=4){
    res[i]   = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[3];
    res[i+1] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[2];
    res[i+2] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[1];
    res[i+3] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[0];
  }
  printf("%f\n", res[0]);
  _mm_free(x);
  _mm_free(res);
}

void vector_bench(float n, float i, __m128 (*fun)(__m128)){
  float invn = -n;
  int nn = 0;
  float delt, maxdelt = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x = (float *)_mm_malloc((nn+1) * sizeof(float), 16);
  float *res = (float *)_mm_malloc((nn+1) *sizeof(float), 16);
  invn = -n;
  for (uint64_t ii = 0; ii < nn; ii++, invn+=i){
    x[ii] = invn;
  }
  for (uint64_t i = 0; i < nn; i+=4){
    res[i]   = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[3];
    res[i+1] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[2];
    res[i+2] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[1];
    res[i+3] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[0];
    printf("%.7f - %.7f - %.7f - %.7f\n", (res[i] - expf(x[i]))/expf(x[i]), (res[i+1] - expf(x[i+1]))/expf(x[i+1]) , (res[i+2] - expf(x[i+2]))/expf(x[i+2]), (res[i+3] - expf(x[i+3]))/expf(x[i+3]));
  }
  for (uint64_t i = 0; i < nn; i++){
    delt = fabs((res[i] - expf(x[i]))/expf(x[i]));
    if(maxdelt < delt){
        maxdelt = delt;
    }
  }
  printf("Maxratio %.10f\n", maxdelt);
  _mm_free(x);
  _mm_free(res);
}

void vector_avx(float n, float i, __m256 (*fun)(__m256)){
  float invn = -n;
  int nn = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x   = (float *)aligned_alloc(32, nn * sizeof(float));
  float *res = (float *)aligned_alloc(32, nn * sizeof(float));
  invn = -n;
  for (uint64_t ii = 0; ii < nn; ii++, invn+=i){
    x[ii] = invn;
  }
  // printf("\n");
  for (uint64_t i = 0; i < nn; i+=8){
    res[i]   = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[7];
    res[i+1] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[6];
    res[i+2] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[5];
    res[i+3] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[4];
    res[i+4] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[3];
    res[i+5] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[2];
    res[i+6] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[1];
    res[i+7] = (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]))[0];
  }
  printf("%f\n", res[0]);
  free(x);
  free(res);
}

void vector_exp(float n, float i, __m128(*fun)(__m128), float(*fun_exp)(float)){
  float invn = -n;
  int nn = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x = (float *)_mm_malloc((nn<<1) * sizeof(float), 16);
  float *res   = (float *)_mm_malloc((nn<<1) * sizeof(float), 16);
  invn = -n;
  for (uint64_t ii = 0; ii < nn+1; ii++,invn+=i){
    x[ii] = invn;
  }
  for (uint64_t i = 0; i < nn; i+=4){
    res[i]   = (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])))[3];
    res[i+1] = (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])))[2];
    res[i+2] = (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])))[1];
    res[i+3] = (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])))[0];
  }
  printf("%f\n", res[0]);
  _mm_free(x);
  _mm_free(res);
}

void vector_exp_avx(float n, float i, __m256(*fun)(__m256), float(*fun_exp)(float)){
  float invn = -n;
  int nn = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x = (float *)aligned_alloc(32, (nn<<1) * sizeof(float));
  float *res   = (float *)aligned_alloc(32, (nn<<1) * sizeof(float));
  invn = -n;
  for (uint64_t ii = 0; ii < nn; ii++,invn+=i){
    x[ii] = invn;
  }
  for (uint64_t i = 0; i < nn; i+=8){
    res[i]   = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[7];
    res[i+1] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[6];
    res[i+2] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[5];
    res[i+3] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[4];
    res[i+4] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[3];
    res[i+5] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[2];
    res[i+6] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[1];
    res[i+7] = (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])))[0];
  }
  // for (uint64_t i = 0; i < nn; i+=8){
  //   printf("%f - %f - %f - %f - %f - %f - %f - %f\n",res[i],res[i+1],res[i+2],res[i + 3],res[i+4],res[i+5],res[i+6],res[i + 7]);
  // }
  free(x);
  free(res);
}

void vectors(float p, float h, __m128 (*ssefunc)(__m128)){
  float invp = -p;
  int iter = 0;
  while (invp < p){ invp+=h; iter++; }
  float *x   = (float *)_mm_malloc(iter * sizeof(float), 16);
  float *res = (float *)_mm_malloc(iter * sizeof(float), 16);
  invp = -p;
  for (uint64_t i = 0; i < iter; ++i){
    x[i] = invp; res[i] = 0;
    invp+=h;
  }
  for (uint64_t i = 0; i < iter; i+=4){
    res[i]   = (*ssefunc)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[3];
    res[i+1] = (*ssefunc)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[2];
    res[i+2] = (*ssefunc)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[1];
    res[i+3] = (*ssefunc)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[0];
  }
  // for (uint64_t i = 0; i < iter; i+=4){
  //   printf("%f - %f - %f -%f\n",res[i],res[i+1],res[i+2],res[i + 3] );
  // }
  _mm_free(res);
  _mm_free(x);
}

__m128 fast_exp_sse(__m128 x){
    __m128 t, f, p, r;
    __m128i i, j;

    const __m128 l2e = _mm_set1_ps (1.442695041f); /* log2(e) */
    const __m128 cvt = _mm_set1_ps (12582912.0f);  /* 1.5 * (1 << 23) */
    const __m128 c0 =  _mm_set1_ps (0.238428936f);
    const __m128 c1 =  _mm_set1_ps (0.703448006f);
    const __m128 c2 =  _mm_set1_ps (1.000443142f);

    /* exp(x) = 2^i * 2^f; i = rint (log2(e) * x), -0.5 <= f <= 0.5 */
    t = _mm_mul_ps (x, l2e);             /* t = log2(e) * x */
    r = _mm_sub_ps (_mm_add_ps (t, cvt), cvt); /* r = rint (t) */
    f = _mm_sub_ps (t, r);               /* f = t - rint (t) */
    i = _mm_cvtps_epi32 (t);             /* i = (int)t */
    p = c0;                              /* c0 */
    p = _mm_mul_ps (p, f);               /* c0 * f */
    p = _mm_add_ps (p, c1);              /* c0 * f + c1 */
    p = _mm_mul_ps (p, f);               /* (c0 * f + c1) * f */
    p = _mm_add_ps (p, c2);              /* p = (c0 * f + c1) * f + c2 ~= exp2(f) */
    j = _mm_slli_epi32 (i, 23);          /* i << 23 */
    r = _mm_castsi128_ps (_mm_add_epi32 (j, _mm_castps_si128 (p))); /* r = p * 2^i*/
    return r;
}
