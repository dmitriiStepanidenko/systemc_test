# flake.nix

{
  description = "test";

  #inputs =
  #  {
  #    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  #    old-python-nixpkgs.url = "github:nixos/nixpkgs/2030abed5863fc11eccac0735f27a0828376c84e";
  #  };
  inputs = {
    nixpkgs-stable.url = "github:nixos/nixpkgs?ref=nixos-24.11";
    nixpkgs-unstable.url = "github:nixos/nixpkgs?ref=nixpkgs-unstable";
  };

  outputs = { self, nixpkgs, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.x86_64-linux.default =
        pkgs.mkShell
          {
            name = "sss";
            nativeBuildInputs = with inputs.nixpkgs-unstable; [
              #clang-tools
              inputs.nixpkgs-stable.legacyPackages.${system}.clang-tools
              inputs.nixpkgs-stable.legacyPackages.${system}.systemc
              inputs.nixpkgs-stable.legacyPackages.${system}.automake
              inputs.nixpkgs-stable.legacyPackages.${system}.autoconf
            ];
          };
    };
}

