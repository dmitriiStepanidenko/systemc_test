#include <systemc-ams>

SC_MODULE(lsf_module) {

  sca_tdf::sca_in<double> in;
  sca_tdf::sca_out<double> out;

  sca_lsf::sca_tdf::sca_source tdf2lsf;
  sca_lsf::sca_tdf::sca_sink lsf2tdf;

  sca_lsf::sca_ltf_zp sca_ltf_zp_lsf;

  SC_CTOR(lsf_module, sca_util::sca_vector<sca_util::sca_complex> zeros,
          sca_util::sca_vector<sca_util::sca_complex> poles, double k)
      : in("in"), out("out"), tdf2lsf("tdf2lsf"), lsf2tdf("lsf2tdf"),
        sca_ltf_zp_lsf("src", zeros, poles,
                       sca_core::sca_time(0.1, sc_core::SC_MS), k) {
    tdf2lsf.inp(in);
    tdf2lsf.y(sig1);
    sca_ltf_zp_lsf.x(sig1);
    sca_ltf_zp_lsf.y(sig2);
    lsf2tdf.x(sig2);
    lsf2tdf.outp(out);
  }

private:
  sca_lsf::sca_signal sig1, sig2;
};
