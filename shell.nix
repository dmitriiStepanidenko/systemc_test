{ pkgs ? import <nixpkgs> {} }:

let 
  callPackage =
    path: overrides:
    let
      f = import path;
    in
    f ((builtins.intersectAttrs (builtins.functionArgs f) pkgs) // overrides);

systemc-ams = callPackage ./systemc-ams.nix {  };
in 
pkgs.mkShell {
  buildInputs = [
    systemc-ams
    pkgs.systemc
  ];
  nativeBuildInputs =  [
    pkgs.clang-tools
    pkgs.automake
    pkgs.autoconf
    pkgs.cmake
  ];
}
