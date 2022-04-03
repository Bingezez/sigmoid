// void graphic_function(char* name, uint64_t size, uint64_t cycles, float (*fun) (float)){
//   FILE *write_file;
//   write_file = fopen(name, "w");
//   time_t t;
//   srand((unsigned int)time(&t));
//   struct timespec spec_1;
//   struct timespec spec_2;
//   uint64_t med, save_i;
//   float *packet_x   = (float *)malloc(size * sizeof(float));
//   float *packet     = (float *)malloc(size * sizeof(float));
//   float *packet_res = (float *)malloc(cycles * sizeof(float));
//   for (uint64_t i = 0; i < size; ++i) {
//     packet_x[i]   = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
//     packet[i]     = 0;
//     packet_res[i] = 0;
//   }
//   for (uint64_t j = 0; j < cycles; ++j){
//     med = 0;
//     for (uint64_t i = 0; i < size; ++i){
//       clock_gettime(CLOCK_REALTIME, &spec_1);
//       (*fun)(packet_x[i]);
//       clock_gettime(CLOCK_REALTIME, &spec_2);
//       packet[i] = get_time_delta(&spec_1, &spec_2);
//       packet_x[i] = 0;
//     }
//     for (uint64_t i = 0; i < size; ++i) {
//       packet_x[i]   = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
//       med += packet[i];
//     }
//     packet_res[j] = 0;
//     packet_res[j] = med/(size);
//   }
//   for (uint64_t i = 0; i < size; i++){
//     fprintf(write_file, "%ld %f\n", i, packet_res[i]);
//   }
//   printf("\t\t---Finish---\n");
//   free(packet_res);
//   free(packet_x);
//   fclose(write_file);
// }

void graphic_function(char* name, uint64_t size, uint64_t cycles, float (*fun) (float)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *packet_x   = (float *)malloc(size * sizeof(float));
  float *packet     = (float *)malloc(size * sizeof(float));
  for (uint64_t i = 0; i < size; ++i) {
    packet_x[i]   = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
    packet[i]     = 0;
  }
  for (uint64_t j = 0; j < cycles; ++j){
    for (uint64_t i = 0; i < size; ++i){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(packet_x[i]);
      clock_gettime(CLOCK_REALTIME, &spec_2);
      packet[i] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, packet[i]);
  }
  printf("\t\t---Finish---\n");
  free(packet_x);
  fclose(write_file);
}

// void graphic_function_tanh(char* name, uint64_t size, uint64_t cycles, float (*fun) (float, float(*fun_exp)(float)), float(*fun_exp)(float)){
//   FILE *write_file;
//   write_file = fopen(name, "w");
//   time_t t;
//   srand((unsigned int)time(&t));
//   struct timespec spec_1;
//   struct timespec spec_2;
//   uint64_t med, save_i;
//   float *packet_x   = (float *)malloc(size * sizeof(float));
//   float *packet     = (float *)malloc(size * sizeof(float));
//   float *packet_res = (float *)malloc(cycles * sizeof(float));
//   for (uint64_t i = 0; i < size; ++i) {
//     packet_x[i]   = ((float)rand()/(float)(RAND_MAX)) * 10.0f;
//     packet[i] = 0;
//     packet_res[i] = 0;
//   }
//   for (uint64_t i = 0; i < cycles; ++i){
//     med = 0;
//     for (uint64_t j = 0; j < size; ++j){
//       clock_gettime(CLOCK_REALTIME, &spec_1);
//       (*fun)(packet_x[j], (*fun_exp));
//       clock_gettime(CLOCK_REALTIME, &spec_2);
//       packet[j] = get_time_delta(&spec_1, &spec_2);
//       packet_x[j] = 0;
//     }
//     for (uint64_t j = 0; j < size; ++j) {
//       packet_x[j]   = ((float)rand()/(float)(RAND_MAX)) * 10.0f;
//       med += packet_x[j];
//     }
//     packet_res[i] = med;
//   }
//   for (uint64_t i = 0; i < size; i++){
//     fprintf(write_file, "%ld %f\n", i, packet_res[i]);
//   }
//   printf("\t\t---Finish---\n");
//   fclose(write_file);
//   free(packet_x);
//   free(packet_res);
// }

void graphic_function_tanh(char* name, uint64_t size, uint64_t cycles, float (*fun) (float, float(*fun_exp)(float)), float(*fun_exp)(float)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *packet_x   = (float *)malloc(size * sizeof(float));
  float *packet     = (float *)malloc(size * sizeof(float));
  for (uint64_t i = 0; i < size; ++i) {
    packet_x[i]   = ((float)rand()/(float)(RAND_MAX)) * 10.0f;
    packet[i] = 0;
  }
  for (uint64_t i = 0; i < cycles; ++i){
    for (uint64_t j = 0; j < size; ++j){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(packet_x[j], (*fun_exp));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      packet[j] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, packet[i]);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
  free(packet_x);
}

void graphic_sse(char* name, uint64_t size, uint64_t cycles, __m128(*fun)(__m128)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *timer = (float *)malloc(size * sizeof(float));
  float *x   = (float *)_mm_malloc(size * sizeof(float), 16);
  for (uint32_t i = 0; i < size; ++i) {
    x[i] = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
  }
  for (uint64_t j = 0; j < cycles; ++j){
    for (uint64_t i = 0; i < size; i+=4){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+1] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+2] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+3] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, timer[i]/4);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
  _mm_free(x);
  free(timer);
}

void graphic_sse_tanh(char* name, uint64_t size, uint64_t cycles, __m128 (*fun)(__m128), float(*fun_exp)(float)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *x      = (float *)_mm_malloc(size * sizeof(float), 16);
  float *timer  = (float *)malloc(size * sizeof(float));
  for (uint32_t i = 0; i < size; ++i) {
    x[i] = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
  }
  for (uint64_t j = 0; j < cycles; ++j){
    for (uint64_t i = 0; i < size; i+=4){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+1] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+2] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+3] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, timer[i]/4);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
  _mm_free(x);
  free(timer);
}

void graphic_avx(char* name, uint64_t size, uint64_t cycles, __m256 (*fun)(__m256)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *x   = (float *)aligned_alloc(32, size * sizeof(float));
  float *timer = (float *)malloc(size * sizeof(float));
  for (uint32_t i = 0; i < size; ++i) {
    x[i]   = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
  }
  for (uint64_t j = 0; j < cycles; ++j){
    for (uint64_t i = 0; i < size; i+=8){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+1] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+2] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+3] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+4] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+5] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+6] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps(x[i], x[i+1], x[i+2], x[i+3],x[i+4], x[i+5], x[i+6], x[i+7]));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+7] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, timer[i]/8);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
  free(x);
  free(timer);
}

void graphic_avx_tanh(char* name, uint64_t size, uint64_t cycles, __m256(*fun)(__m256), float(*fun_exp)(float)){
  FILE *write_file;
  write_file = fopen(name, "w");
  srand((unsigned int)time(NULL));
  struct timespec spec_1;
  struct timespec spec_2;
  float *timer = (float *)malloc(size * sizeof(float));
  float *x     = (float *)aligned_alloc(32, size * sizeof(float));
  for (uint32_t i = 0; i < size; ++i) {
    x[i] = ((float)rand()/(float)(RAND_MAX)) * 5.0f;
  }
  for (uint64_t i = 0; i < cycles; ++i){
    for (uint64_t i = 0; i < size; i+=8){
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+1] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+2] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+3] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+4] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+5] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+6] = get_time_delta(&spec_1, &spec_2);
      clock_gettime(CLOCK_REALTIME, &spec_1);
      (*fun)(_mm256_set_ps((*fun_exp)(x[i]), (*fun_exp)(x[i+1]), (*fun_exp)(x[i+2]), (*fun_exp)(x[i+3]),(*fun_exp)(x[i+4]), (*fun_exp)(x[i+5]), (*fun_exp)(x[i+6]), (*fun_exp)(x[i+7])));
      clock_gettime(CLOCK_REALTIME, &spec_2);
      timer[i+7] = get_time_delta(&spec_1, &spec_2);
    }
  }
  for (uint64_t i = 0; i < size; i++){
    fprintf(write_file, "%ld %f\n", i, timer[i]/8);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
  free(x);
  free(timer);
}
