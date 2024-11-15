#include "diode.h"
#include "diode_controll.h"
#include <systemc-ams>
#include <systemc>
int sc_main(int argc, char *argv[]) {
  sca_eln::sca_node sigInput;
  sca_eln::sca_node sigOutput;
  sca_eln::sca_node_ref gnd;
  sca_tdf::sca_signal<double> vdiode;
  sc_core::sc_signal<bool> diodectrl;

  sca_eln::sca_vsource src("src", 0.0, 0.0, 3.3, 1e5);
  src.set_timestep(10, sc_core::SC_NS);
  src.p(sigInput);
  src.n(gnd);

  diode_and_r d0("d0");
  diode_ctrl_tdf dctrl0("dctrl0");

  d0.vin(sigInput);
  d0.p(sigOutput);
  d0.n(gnd);
  d0.vdiode(vdiode);
  d0.diodectrl(diodectrl);

  dctrl0.vdiode(vdiode);
  dctrl0.diodectrl(diodectrl);

  sca_util::sca_trace_file *eln =
      sca_util::sca_create_vcd_trace_file("diode.vcd");

  sca_trace(eln, sigInput, "sigInput");
  sca_trace(eln, sigOutput, "sigOuput");
  sca_trace(eln, vdiode, "vdiode");
  sca_trace(eln, diodectrl, "diodectrl");

  sc_start(20, sc_core::SC_US);
  sca_util::sca_close_vcd_trace_file(eln);

  return 0;
}
