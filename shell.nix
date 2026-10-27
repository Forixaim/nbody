{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    glm
    glfw3
    yaml-cpp
    shader-slang
    vulkan-headers
    vulkan-loader
    vulkan-tools
    vulkan-validation-layers
  ];

  nativeBuildInputs = with pkgs; [
    bc
    cmake
    ninja
    pkg-config
  ];

  shellHook = ''
    export NIX_ENFORCE_NO_NATIVE="0"
    export VK_LAYER_PATH="${pkgs.vulkan-validation-layers}/lib"
    export LD_LIBRARY_PATH="${pkgs.vulkan-loader}/lib"
  '';
}
