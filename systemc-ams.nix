{ lib
, stdenv
, fetchFromGitHub
, cmake
, systemc
}:

stdenv.mkDerivation rec {
  pname = "systemc-ams";
  version = "2.3.4";

  src = fetchFromGitHub {
    owner = "mhaeuser";
    repo = pname;
    rev = "7d05affaddd480673c9fa90e58cce424e8d31180";
    sha256 = "sha256-mmYykf3eZ0ELu3RVrRmIVYKJGM0jO0j4UGdt06Lsktk=";
  };

  nativeBuildInputs = [ cmake ];

  buildInputs = [ systemc ];

  meta = with lib; {
    description = "CHANGE";
    homepage = "https://github.com/mhaeuser/systemc-ams";
    license = licenses.asl20;
    maintainers = with maintainers; [  ];
  };
}
