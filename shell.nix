{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = [
    pkgs.libpng
    pkgs.feh
  ]
  ++ pkgs.lib.optionals pkgs.stdenv.isDarwin [
  ]
  ++ pkgs.lib.optionals pkgs.stdenv.isLinux [
  ];

  shellHook =
  ''
  '';
}
