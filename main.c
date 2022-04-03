#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include "sigmoids.c"
#include "exponential.c"
#include "sigmoid_first_real.c"
#include "benchmark_v2.c"
#include "timer.c"


// float fass (float p){
//   const int c1 = 60801;
//   const float fc1;
//   p = *(float*)&c1;
//   printf("%f\n", p);
// }


void main(int argc, char const *argv[]) {
  printf("%f - %f\n", fast_tanh3(2), tanhf(2));
  // fass(2);
  // printf("%f - %f\n",fast_tanh3(-3), tanhf(-3));
  // benchmark_function(6, 0.000001, tanhf, tanhfast);


  // benchmark_function(point, step, (*lib)(float), (*fun)(float));
  // benchmark_function_tanh(point, step, (*lib)(float), (*fun)(float,(*fun_exp)(float)), (*fun_exp)(float));


  // benchmark_function(1, 0.0000001, expf, piece_exp); //
  // benchmark_function(1, 0.0000001, expf, expf_fast); //----
  // benchmark_function(1, 0.0000001, expf, better_expf_fast); //
  // benchmark_function(1, 0.0000001, expf, fasterexp); //
  // benchmark_function(1, 0.0000001, expf, pade33); // ?
  // benchmark_function(1, 0.0000001, expf, pade34); //
  // benchmark_function(1, 0.0000001, expf, spline5); //
  // benchmark_function(1, 0.0000001, expf, spline3); //
  // benchmark_function(1, 0.0000001, expf, fastExp4); // +
  // benchmark_function(1, 0.0000001, expf, fastExp3); // +
  // benchmark_function(1, 0.0000001, expf, texp); // +

  // benchmark_function(6, 0.000001, tanhf, tanh5_6);
  // benchmark_function(6, 0.000001, tanhf, fast_tanh);
  // benchmark_function(6, 0.000001, tanhf, tanh7_8);
  // benchmark_function(10, 0.000001, tanhf, fast_tanh3);
  // benchmark_function(10, 0.000001, tanhf, ttanhh);10

  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, piece_exp); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, expf_fast); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, better_expf_fast); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, fasterexp); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, pade33); // ?
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, pade34); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, spline5); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, spline3); //
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, fastExp4); // +
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, fastExp3); // +
  // benchmark_function_tanh(6, 0.000001, tanhf, orig_tanh, texp); // +

  // write graphic
  // benchmark_function_write_tanh
  // benchmark_function_write


  // benchmark_function_write(3,0.00001,"1.txt",piece_exp); //#1
  // benchmark_function_write(3,0.00001,"1.txt",expf_fast); //#2 ---
  // benchmark_function_write(3,0.00001,"1.txt", better_expf_fast); //#3
  // benchmark_function_write(3,0.00001,"1.txt",fasterexp); //#5
  // benchmark_function_write(3,0.00001,"1.txt",pade33); //#6
  // benchmark_function_write(3,0.00001,"1.txt",pade34); //#7
  // benchmark_function_write(3,0.00001,"1.txt",spline5); //#8
  // benchmark_function_write(3,0.00001,"1.txt",spline3); //# 8-9
  // benchmark_function_write(3,0.00001,"1.txt",fastExp4); //#10
  // benchmark_function_write(3,0.00001,"1.txt",fastExp3); //#11
  // benchmark_function_write(3,0.00001,"1.txt",texp); //#12

  // benchmark_function_write(10,0.00001,"1.txt",tanh5_6); //#1 -
  // benchmark_function_write(10,0.00001,"1.txt",fast_tanh); //#2
  // benchmark_function_write(10,0.00001,"1.txt",tanh7_8); //#3
  // benchmark_function_write(10,0.00001,"1.txt",fast_tanh3); //#4
  // benchmark_function_write(10,0.00001,"1.txt",ttanhh); //#5

  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, piece_exp); //#1
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, expf_fast); //#2 ---
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, better_expf_fast); //#3
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, fasterexp); //#5
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, pade33); //#6 ???
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, pade34); //#7 ???
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, spline3); //#9 -
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, spline5); //#8
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, fastExp3); //#11
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, fastExp4); //#10
  // benchmark_function_write_tanh(10,0.00001,"1.txt",orig_tanh, texp); //#12

  //time graphic
  // graphic_function("time1.txt", 1000,10, expf);
  // // graphic_function("time2.txt", 100,1000, fastExp3);
  // // graphic_function("time3.txt", 100,1000, fastExp4);
  // graphic_sse("time2.txt", 1000,10, ssespline3);
  // graphic_sse("time3.txt", 1000,10, ssespline5);
  // graphic_avx("time4.txt", 1000,10, avxspline3);
  // graphic_avx("time5.txt", 1000,10, avxspline5);


  // graphic_function("time1.txt", 300,100000, expf);
  // graphic_function("time2.txt", 300,100000, piece_exp);
  // graphic_function("time3.txt", 300,100000, better_expf_fast);
  // graphic_function("time4.txt", 300,100000, fasterexp);
  // graphic_function("time5.txt", 300,100000, fast_exp);
  // graphic_function("time6.txt", 300,100000, pade33);
  // graphic_function("time7.txt", 300,100000, pade34);
  // graphic_function("time8.txt", 300,100000, spline5);
  // graphic_function("time9.txt", 300,100000, spline3);
  // graphic_function("time10.txt", 300,100000, fastExp4);
  // graphic_function("time11.txt", 300,100000, texp);

  // graphic_function("time1.txt", 300,100000, tanhf);
  // graphic_function("time2.txt", 300,100000, tanh5_6);
  // graphic_function("time3.txt", 300,100000, fast_tanh);
  // graphic_function("time4.txt", 300,100000, tanh7_8);
  // graphic_function("time5.txt", 300,100000, fast_tanh3);
  // graphic_function("time6.txt", 300,100000, ttanhh);

  // graphic_function("time1.txt", 300,100000, tanhf);
  // graphic_function_tanh("time2.txt", 300,100000,orig_tanh, piece_exp);
  // graphic_function_tanh("time3.txt", 300,100000,orig_tanh, better_expf_fast);
  // graphic_function_tanh("time4.txt", 300,100000,orig_tanh, fasterexp);
  // graphic_function_tanh("time5.txt", 300,100000,orig_tanh, fast_exp);
  // graphic_function_tanh("time6.txt", 300,100000,orig_tanh, pade33);
  // graphic_function_tanh("time7.txt", 300,100000,orig_tanh, pade34);
  // graphic_function_tanh("time8.txt", 300,100000,orig_tanh, spline5);
  // graphic_function_tanh("time9.txt", 300,100000,orig_tanh, spline3);
  // graphic_function_tanh("time10.txt", 300,100000,orig_tanh, fastExp4);
  // graphic_function_tanh("time11.txt", 300,100000,orig_tanh, texp);


  // graphic_function("time1.txt", 300,100000, tanhf);
  // graphic_sse_tanh("time2.txt", 300,100000,tanhsse_exp, piece_exp);
  // graphic_sse_tanh("time3.txt", 300,100000,tanhsse_exp, better_expf_fast);
  // graphic_sse_tanh("time4.txt", 300,100000,tanhsse_exp, fasterexp);
  // graphic_sse_tanh("time5.txt", 300,100000,tanhsse_exp, fast_exp);
  // graphic_sse_tanh("time6.txt", 300,100000,tanhsse_exp, pade33);
  // graphic_sse_tanh("time7.txt", 300,100000,tanhsse_exp, pade34);
  // graphic_sse_tanh("time8.txt", 300,100000,tanhsse_exp, spline5);
  // graphic_sse_tanh("time9.txt", 300,100000,tanhsse_exp, spline3);
  // graphic_sse_tanh("time10.txt",300,100000,tanhsse_exp, fastExp4);
  // graphic_sse_tanh("time11.txt",300,100000,tanhsse_exp, texp);

  // graphic_function("time1.txt", 400,10000, tanhf);
  // graphic_avx_tanh("time2.txt", 400,10000,tanhavx_exp, piece_exp);
  // graphic_avx_tanh("time3.txt", 400,10000,tanhavx_exp, better_expf_fast);
  // graphic_avx_tanh("time4.txt", 400,10000,tanhavx_exp, fasterexp);
  // graphic_avx_tanh("time5.txt", 400,10000,tanhavx_exp, fast_exp);
  // graphic_avx_tanh("time6.txt", 400,10000,tanhavx_exp, pade33);
  // graphic_avx_tanh("time7.txt", 400,10000,tanhavx_exp, pade34);
  // graphic_avx_tanh("time8.txt", 400,10000,tanhavx_exp, spline5);
  // graphic_avx_tanh("time9.txt", 400,10000,tanhavx_exp, spline3);
  // graphic_avx_tanh("time10.txt",400,10000,tanhavx_exp, fastExp4);
  // graphic_avx_tanh("time11.txt",400,10000,tanhavx_exp, texp);

  // graphic_function("time1.txt", 400,10000, expf);
  graphic_sse("time2.txt", 400,10000, FastExpSsee);
  // graphic_sse("time3.txt", 400,10000, ssespline3);
  // graphic_sse("time4.txt", 400,10000, ssespline5);
  // graphic_sse("time5.txt", 400,10000, ssepade34);
  // graphic_avx("time6.txt", 400,10000, FastExpAvx);
  // graphic_avx("time7.txt", 400,10000, avxspline3);
  // graphic_avx("time8.txt", 400,10000, avxspline5);
  // graphic_avx("time9.txt", 400,10000, avxpade34);

  // graphic_function("time1.txt", 400,100000, tanhf);
  // graphic_sse("time2.txt", 400,100000, tanhsse2);
  // graphic_sse("time3.txt", 400,100000, tanhsse);
  // graphic_avx("time4.txt", 400,100000, tanhavx2);
  // graphic_avx("time5.txt", 400,100000, tanhavx);



  // vector_bench(3, 0.00001,fast_exp_sse);
  // benchmark_function_write_sse(10,0.000001,"1.txt",tanhsse2);
}
