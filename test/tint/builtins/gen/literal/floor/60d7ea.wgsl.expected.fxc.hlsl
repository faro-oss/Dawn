void floor_60d7ea() {
  float3 res = floor((1.0f).xxx);
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  floor_60d7ea();
  return (0.0f).xxxx;
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  floor_60d7ea();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  floor_60d7ea();
  return;
}
