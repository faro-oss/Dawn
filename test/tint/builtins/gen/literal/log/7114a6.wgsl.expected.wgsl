fn log_7114a6() {
  var res : f32 = log(1.0f);
}

@vertex
fn vertex_main() -> @builtin(position) vec4<f32> {
  log_7114a6();
  return vec4<f32>();
}

@fragment
fn fragment_main() {
  log_7114a6();
}

@compute @workgroup_size(1)
fn compute_main() {
  log_7114a6();
}
