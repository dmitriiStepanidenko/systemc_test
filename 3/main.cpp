#include "lsf_module.h"
#include "sin_src.h"
#include <scams/predefined_moc/lsf/sca_lsf_signal.h>
#include <systemc-ams>

int sc_main(int argc, char *argv[]) {
  sca_tdf::sca_signal<double> input, output;

  sc_core::sc_time time_step(10.0, sc_core::SC_NS);

  const double FC = 1.0;
  const double H0 = 2.0;

  double k;
  sca_util::sca_vector<sca_util::sca_complex> poles, zeros;
  poles(0) = sca_util::sca_complex(-2.0 * M_PI * FC, 0.0);
  k = H0 * 2.0 * M_PI * FC;

  lsf_module lsf("lsf_ltf_zp", zeros, poles, k);

  lsf.in(input);
  lsf.out(output);

  sin_src sin0("sin0", 3.3, 10000, time_step);
  sin0.out(input);

  sca_util::sca_trace_file *vcdfile =
      sca_util::sca_create_vcd_trace_file("lsf_ltf_zp.vcd");
  sca_trace(vcdfile, input, "input");
  sca_trace(vcdfile, output, "otput");
  sc_start(5, sc_core::SC_MS);
  sca_util::sca_close_vcd_trace_file(vcdfile);
  return 0;
}
