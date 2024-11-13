#ifndef _DIODE_H_
#define _DIODE_H_
#include <systemc-ams>
SC_MODULE(diode_and_r) {
  sca_eln::sca_terminal vin, n;
  sca_eln::sca_terminal p;
  sc_core::sc_in<bool> diodectrl;
  sca_tdf::sca_out<double> vdiode;
  sca_eln::sca_r resistor;
  sca_eln::sca_de_rswitch
      sw; // Switch controlled by a discrete-event input signal
  sca_eln::sca_tdf::sca_vsink
      vsink; // Converts voltage to a discrete-event output signal
  SC_CTOR(diode_and_r)
      : p("p"), n("n"), sw("sw", 0.1, 10e12), vsink("vsink"),
        resistor("resistor", 1e3) {

    resistor.p(vin);
    resistor.n(p);

    sw.p(p);
    sw.n(n);
    sw.ctrl(diodectrl);

    vsink.p(p);
    vsink.n(n);
    vsink.outp(vdiode);
  }
};
#endif /* _DIODE_H_ */
