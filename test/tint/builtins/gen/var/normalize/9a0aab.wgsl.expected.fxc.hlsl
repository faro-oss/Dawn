void normalize_9a0aab() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = normalize(arg_0);
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  normalize_9a0aab();
  return (0.0f).xxxx;
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  normalize_9a0aab();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  normalize_9a0aab();
  return;
}
