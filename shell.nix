{
  pkgs ? import <nixpkgs> { },
}:

let
  libs = with pkgs; [
    glm
    glfw3
    yaml-cpp
    shader-slang
    vulkan-headers
    vulkan-loader
    vulkan-tools
    vulkan-validation-layers
  ];
in
pkgs.mkShell {
  buildInputs = libs;

  nativeBuildInputs = with pkgs; [
    bc
    cmake
    ninja
    pkg-config
  ];

  shellHook = ''
    export NIX_ENFORCE_NO_NATIVE="0"
    export VK_LAYER_PATH="${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d"
    export LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib''${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
    export CPLUS_INCLUDE_PATH="${pkgs.lib.makeSearchPathOutput "dev" "include" libs}:${pkgs.stdenv.cc.cc}/lib/gcc/${pkgs.stdenv.hostPlatform.config}/${pkgs.stdenv.cc.cc.version}/include"
  '';
}
