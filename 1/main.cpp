#include <systemc-ams.h>
#include <systemc.h>

SC_MODULE(rc_example) {
  // ELN primitive instances
  sca_eln::sca_vsource i_vin;
  sca_eln::sca_r i_sca_r1;
  sca_eln::sca_c i_sca_c1;
  // ELN nodes
  sca_eln::sca_node vin;
  sca_eln::sca_node vout;
  sca_eln::sca_node_ref gnd;
  // RC lowpass with sine input
  SC_CTOR(rc_example)
      : i_vin("i_vin", 2.0, 2.0, 1.0, 1e6, 0, sc_core::SC_ZERO_TIME, 1.0), // 2V
        // DC, 1V / 1MHz sin and 1V AC 
        i_sca_r1("i_sca_r1", 1e3), // R of lowpass
        i_sca_c1("i_sca_c1", 160e-12),                         // C of lowpass
        vin("vin"), vout("vout"), gnd("gnd") {
    // input source, ELN time step definition
    i_vin.p(vin);
    i_vin.n(gnd);
    i_vin.set_timestep(1, sc_core::SC_NS);
    // RC lowpass
    i_sca_r1.p(vin);
    i_sca_r1.n(vout);
    i_sca_c1.p(vout);
    i_sca_c1.n(gnd);
  }
};
// ========================================================
int sc_main(int argc, char *argv[]) {
  sc_set_time_resolution(1.0, SC_NS);
  rc_example dut("dut");
  // transient domain simulation
  sca_util::sca_trace_file *trtf = sca_util::sca_create_tabular_trace_file("tr.tab");
  sca_util::sca_trace(trtf, dut.vin, "vin");
  sca_util::sca_trace(trtf, dut.vout, "vout");
  sc_start(2, SC_US);
  trtf->disable();
  SC_REPORT_INFO("sc_main", "transient domain simulation done");
  // frequency-domain simulation
  sca_util::sca_trace_file *actf =
      sca_util::sca_create_tabular_trace_file("ac.tab");
  sca_util::sca_trace(actf, dut.vin, "vin");
  sca_util::sca_trace(actf, dut.vout, "vout");
  sca_ac_start(1e3, 100e6, 100);
  SC_REPORT_INFO("sc_main", "frequency domain simulation done");
  return 0;
}
