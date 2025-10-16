{
  description = "Urrly: basically self toture by writing a url shortener in c with only docs";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: {

    packages = nixpkgs.lib.genAttrs [ "x86_64-linux" ] (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in rec {
      default = pkgs.stdenv.mkDerivation {
        pname = "urrly";
        version = "1.0";

        src = ./.;

        nativeBuildInputs = with pkgs; [ libgcc ];

        buildInputs = with pkgs; [ zlib ];

        buildPhase = ''
          runHook preBuild
          
          gcc -c baseutils.c
          gcc -c url.c
          gcc -c backe.c
          gcc -o urrly main.c baseutils.o url.o backe.o -lm

          runHook postBuild
        '';

        installPhase = ''
          runHook preInstall

          mkdir -p $out/bin
          cp urrly $out/bin

          runHook postInstall
        '';
      };
    });

  };
}
