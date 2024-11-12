#include "comparator.h"
#include "constant_voltage_tdf.h"
#include "sin_src.h"
#include "v_enable.h"
#include <systemc-ams>

int sc_main(int argc, char *argv[]) {
  uint32_t i;
  sca_tdf::sca_signal<double> vp;
  sca_tdf::sca_signal<double> vn;
  sca_tdf::sca_signal<bool> en;
  sc_core::sc_signal<bool> z;
  sc_core::sc_time time_step(10.0, sc_core::SC_NS);
  comparator comp0("comp0");
  comp0.vplus(vp);
  comp0.vminus(vn);
  comp0.comp(z);
  comp0.v_enable(en);
  sin_src sin0("sin0", 3.3, 10000, time_step);
  sin0.out(vp);
  constant_voltage_tdf ref("ref", 1.2);
  ref.out(vn);

  v_enable_tdf v_enable("v_enable");
  v_enable.out(en);

  sca_util::sca_trace_file *vcdfile =
      sca_util::sca_create_vcd_trace_file("comparator-tdf.vcd");
  sca_trace(vcdfile, vp, "vp");
  sca_trace(vcdfile, vn, "vn");
  sca_trace(vcdfile, z, "z");
  sca_trace(vcdfile, en, "en");
  sc_start(5, sc_core::SC_MS);
  sca_util::sca_close_vcd_trace_file(vcdfile);
  return 0;
}
