fn asinh_157447() {
  var arg_0 = 1.0f;
  var res : f32 = asinh(arg_0);
}

@vertex
fn vertex_main() -> @builtin(position) vec4<f32> {
  asinh_157447();
  return vec4<f32>();
}

@fragment
fn fragment_main() {
  asinh_157447();
}

@compute @workgroup_size(1)
fn compute_main() {
  asinh_157447();
}
