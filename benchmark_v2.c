static uint64_t get_time_delta(struct timespec *spec_1, struct timespec *spec_2){
  int res = (spec_2->tv_sec - spec_1->tv_sec) * 1000000000 + (spec_2->tv_nsec - spec_1->tv_nsec);
  return res;
}

static void errors_result_functions(float p, float h, float (*lib)(float), float (*fun)(float)) {
  uint32_t iter = 0;
  uint32_t save_1 = 0, save_2 = 0;
  float invp = -p;
  float alf1, alf2;
  float medabsolute = 0, maxabsolute = 0, medratio = 0, maxratio = 0;
  float *packetabs   = (float*)malloc(sizeof(float));
  float *packetratio = (float*)malloc(sizeof(float));
  float *packetpoint = (float*)malloc(sizeof(float));
  for (float i = invp; i < p; i += h, iter++){
    packetpoint[iter] = i;
    alf1 = (*lib)(i);  alf2 = (*fun)(i);
    packetabs[iter]   = (alf1 - alf2);
    packetratio[iter] = (fabs(alf1 - alf2) / alf1) * 100;
    packetabs   = (float*)realloc(packetabs, (iter + 2) * sizeof(float));
    packetratio = (float*)realloc(packetratio, (iter + 2) * sizeof(float));
    packetpoint = (float*)realloc(packetpoint, (iter + 2) * sizeof(float));
  }
  uint32_t i = 0;
  for (i = 0; i < iter; ++i){
    medabsolute += fabs(packetabs[i]);
  }
  medabsolute /= iter;
  maxabsolute = packetabs[0];
  for (i = 0; i < iter; ++i){
    if (maxabsolute < fabs(packetabs[i])){ maxabsolute = fabs(packetabs[i]); save_1 = i;}
  }
  for (i = 0; i < iter; ++i){
    medratio += fabs(packetratio[i]);
  }
  medratio /= iter;
  maxratio = packetratio[0];
  for (i = 0; i < iter; ++i){
    if (maxratio < fabs(packetratio[i])){ maxratio = fabs(packetratio[i]); save_2 = i;}
  }
  printf("medabsolute = %.20f\n", medabsolute);
  printf("maxabsolute = %.20f\n", maxabsolute);
  printf("point on maxabsolute = %.20f\n", packetpoint[save_1]);
  printf("medratio = %.20f\n", medratio);
  printf("maxratio = %.20f\n", maxratio);
  printf("point on maxratio = %.20f\n", packetpoint[save_2]);
  free(packetabs);
  free(packetpoint);
  free(packetratio);
}

static void errors_result_functions_nextafter(float p, float (*lib)(float), float (*fun)(float)) {
  uint32_t iter = 0;
  float save_1 = 0, save_2 = 0;
  float invp = -p, temp, delt;
  float alf1, alf2;
  float medabsolute = 0, maxabsolute = 0, medratio = 0, maxratio = 0;
  while(invp < p){
    alf1 = (*lib)(invp);  alf2 = (*fun)(invp);
    temp = (alf1 - alf2);
    medabsolute += fabs(temp);
    if (maxabsolute < fabs(temp)){ maxabsolute = fabs(temp); save_1 = invp;}
    delt = (fabs(alf1 - alf2) / alf1) * 100;
    medratio += fabs(delt);
    if (maxratio < fabs(delt)){ maxratio = fabs(delt); save_2 = invp;}
    invp = nextafterf(invp, p);
    iter++;
  }
  medabsolute /= iter;
  medratio /= iter;
  printf("iteration nextafter = %d\n", iter);
  printf("medabsolute = %.20f\n", medabsolute);
  printf("maxabsolute = %.20f\n", maxabsolute);
  printf("point on maxabsolute = %.20f\n", save_1);
  printf("medratio = %.20f\n", medratio);
  printf("maxratio = %.20f\n", maxratio);
  printf("point on maxratio = %.20f\n", save_2);
}

extern void errors_result_functions_tanh(float p, float h, float(*lib)(float), float(*fun)(float, float(*fun_exp)(float)), float(*fun_exp)(float)) {
  uint32_t iter = 0;
  uint32_t save_1 = 0, save_2 = 0, save_3 = 0;
  float invp = -p;
  float alf1, alf2;
  float medabsolute = 0, maxabsolute = 0, medratio = 0, maxratio = 0;
  float realratio = 0;
  float *packetabs   = (float*)malloc(sizeof(float));
  float *packetratio = (float*)malloc(sizeof(float));
  float *packetpoint = (float*)malloc(sizeof(float));
  for(float i = invp; i < p; i += h, iter++){
    packetpoint[iter] = i;
    alf1 = (*lib)(i);  alf2 = (*fun)(i, (*fun_exp));
    packetabs[iter]   = (alf1 - alf2);
    packetratio[iter] = (fabs(alf1 - alf2) / alf1) * 100;
    packetabs   = (float*)realloc(packetabs, (iter + 2) * sizeof(float));
    packetratio = (float*)realloc(packetratio, (iter + 2) * sizeof(float));
    packetpoint = (float*)realloc(packetpoint, (iter + 2) * sizeof(float));
  }
  uint32_t i = 0;
  for (i = 0; i < iter; ++i){
    medabsolute += fabs(packetabs[i]);
  }
  medabsolute /= iter;
  maxabsolute = packetabs[0];
  for (i = 0; i < iter; ++i){
    if (maxabsolute < fabs(packetabs[i])){ maxabsolute = fabs(packetabs[i]); save_1 = i;}
  }
  for (i = 0; i < iter; ++i){
    medratio += fabs(packetratio[i]);
  }
  medratio /= iter;
  maxratio = packetratio[0];
  realratio = packetratio[0];
  for (i = 0; i < iter; ++i){
    if (maxratio < fabs(packetratio[i]) && fabs(packetratio[i]) < 1 && fabs(packetratio[i]) > -1 ){ maxratio = fabs(packetratio[i]); save_2 = i;}
    if (realratio < fabs(packetratio[i])){ realratio = fabs(packetratio[i]); save_3 = i;}
  }
  printf("medabsolute = %.20f\n", medabsolute);
  printf("maxabsolute = %.20f\n", maxabsolute);
  printf("point on maxabsolute = %.20f\n", packetpoint[save_1]);
  printf("medratio = %.20f\n", medratio);
  printf("maxratio = %.20f\n", maxratio);
  printf("point on maxratio = %.20f\n", packetpoint[save_2]);
  printf("realratio = %.20f\n", realratio);
  printf("point on realratio = %.20f\n", packetpoint[save_3]);
  free(packetabs);
  free(packetratio);
  free(packetpoint);
}

extern void errors_result_functions_tanh_nextafter(float p, float(*lib)(float), float(*fun)(float, float(*fun_exp)(float)), float(*fun_exp)(float)) {
  uint32_t iter = 0;
  float save_1 = 0, save_2 = 0;
  float invp = -p, temp, delt;
  float alf1, alf2;
  float medabsolute = 0, maxabsolute = 0, medratio = 0, maxratio = 0;
  while(invp < p){
    alf1 = (*lib)(invp);  alf2 = (*fun)(invp, (*fun_exp));
    temp = (alf1 - alf2);
    medabsolute += fabs(temp);
    if (maxabsolute < fabs(temp)){ maxabsolute = fabs(temp); save_1 = invp;}
    delt = (fabs(alf1 - alf2) / alf1) * 100;
    medratio += fabs(delt);
    if (maxratio < fabs(delt)){ maxratio = fabs(delt); save_2 = invp;}
    invp = nextafterf(invp, p);
    iter++;
  }
  medabsolute /= iter;
  medratio /= iter;
  printf("iteration nextafter = %d\n", iter);
  printf("medabsolute = %.20f\n", medabsolute);
  printf("maxabsolute = %.20f\n", maxabsolute);
  printf("point on maxabsolute = %.20f\n", save_1);
  printf("medratio = %.20f\n", medratio);
  printf("maxratio = %.20f\n", maxratio);
  printf("point on maxratio = %.20f\n", save_2);
}

extern void benchmark_function(float p, float h, float (*lib)(float), float (*fun)(float)){
  float invp = -p;
  int iteration = 0;
  while (invp < p){invp+=h; iteration++;}
  printf("Iteration = %d\n", iteration);
  errors_result_functions(p, h, (*lib), (*fun));
  printf("\n\nNextafter\n");
  errors_result_functions_nextafter(p, (*lib), (*fun));
}

extern void benchmark_function_tanh(float p, float h, float (*lib)(float),float (*fun)(float, float(*fun_exp)(float)), float (*fun_exp)(float)){
  float invp = -p;
  int iteration = 0;
  while (invp < p){invp+=h; iteration++;}
  printf("Iteration = %d\n", iteration);
  errors_result_functions_tanh(p, h, (*lib), (*fun), (*fun_exp));
  printf("\n\nNextafter\n");
  errors_result_functions_tanh_nextafter(p, (*lib), (*fun), (*fun_exp));
}

// ----------------------------- write graphic ---------------------------------
extern void benchmark_function_write_tanh(float s, float h, char* name, float (*fun)(float, float(*fun_exp)(float)), float (*fun_exp)(float)){
  FILE *write_file;
  write_file = fopen(name, "w");
  float invs = -s, alf1;
  for (float i = invs; i < s; i += h){
    alf1 = (*fun)(i, (*fun_exp));
    fprintf(write_file,"%.10f %.15f\n", i, alf1);
  }
  printf("\t\t---Finish---\n");
  fclose(write_file);
}

extern void benchmark_function_write(float s, float h, char* name, float (*fun)(float)){
	FILE *write_file;
	write_file = fopen(name, "w");
	float invs = -s, alf1;
	for (float i = invs; i < s; i += h){
		alf1 = (*fun)(i);
		fprintf(write_file, "%.10f %.15f\n", i, alf1);
	}
	printf("\t\t---Finish---\n");
	fclose(write_file);
}

extern void benchmark_function_write_sse(float n, float i, char* name, __m128 (*fun)(__m128)){
	FILE *write_file;
	write_file = fopen(name, "w");
  float invn = -n;
  int nn = 0;
  while (invn < n){ invn+=i; nn++; }
  float *x = (float *)_mm_malloc((nn+1) * sizeof(float), 16);
  float *res = (float *)_mm_malloc((nn+1) *sizeof(float), 16);
  invn = -n;
  for (uint64_t ii = 0; ii < nn; ii++, invn+=i){
    x[ii] = invn;
  }
  for (uint64_t i = 0; i < nn-1; i+=4){
    res[i]   = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[3];
    res[i+1] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[2];
    res[i+2] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[1];
    res[i+3] = (*fun)(_mm_set_ps(x[i], x[i+1], x[i+2], x[i+3]))[0];
  }
  	for (uint64_t i = 0; i < nn-1; i+=4){
		fprintf(write_file, "%.10f %.15f\n", x[i], res[i]);
	}
	printf("\t\t---Finish---\n");
	fclose(write_file);
}
