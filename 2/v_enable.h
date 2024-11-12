#include <systemc-ams>

SCA_TDF_MODULE(v_enable_tdf) {
  sca_tdf::sca_out<bool> out;

  v_enable_tdf(sc_core::sc_module_name mn,
               sca_core::sca_time Tm_ =
                   sca_core::sca_time(0.125, sc_core::SC_MS))
      : out("out") {}

  void processing() {
    if (get_time() > sca_core::sca_time(6000, sc_core::SC_NS)) {
      out.write(1);
    } else {
      out.write(0);
    }
  }

  sca_core::sca_time Tm; // module time step
};
