#include <systemc-ams>

SCA_TDF_MODULE(lsf_module) {
  sca_tdf::sca_in<double> in;

  sca_tdf::sca_out<double> out;

  lsf_module(sc_core::sc_module_name nm, double fc_, double h0_ = 1.0,
             sca_core::sca_time Tm_ = sca_core::sca_time(0.125, sc_core::SC_MS))
      : out("out"), Tm(Tm_), fc(fc_), h0(h0_) {}

  void initialize() {
    // filter requires no zeros to be defined
    poles(0) = sca_util::sca_complex(-2.0 * M_PI * fc, 0.0);
    k = h0 * 2.0 * M_PI * fc;
  }
  void processing() { out.write(ltf_zp(zeros, poles, in.read(), k)); }

private:
  double k; // filter gain
  sca_core::sca_time Tm;
  sca_tdf::sca_ltf_zp ltf_zp;
  sca_util::sca_vector<sca_util::sca_complex> poles, zeros;
  double fc; // 3dB cut-off frequency in Hz
  double h0; // DC gain
};
