project('parallax', ['c', 'cpp'],
  version: '1.0',
  default_options: [
    'c_std=c11',
    'cpp_std=c++17',
    'warning_level=2',
  ],
)

cc = meson.get_compiler('c')
c_args = ['-D_GNU_SOURCE']

glslc = find_program('glslc', required: true)

# ----- Includes -----
includes = include_directories(
  'include',
  'external/glfw3/include',
  'external/imgui/include',
  'external/cglm/include',
  'external/cgltf/include'
)

# ----- Dependencies -----
dependencies = [
  dependency('vulkan'),
  dependency('glfw3', static: true),
  dependency('rt', required: false),
]

# ----- Dear ImGui bridge (static) -----
dcimgui = static_library('dcimgui',
  include_directories: includes,
  dependencies: dependencies,
  sources: files(
    'external/imgui/src/dcimgui.cpp',
    'external/imgui/src/dcimgui_impl_glfw.cpp',
    'external/imgui/src/dcimgui_impl_vulkan.cpp',
    'external/imgui/src/dcimgui_internal.cpp',
    'external/imgui/src/imgui.cpp',
    'external/imgui/src/imgui_demo.cpp',
    'external/imgui/src/imgui_draw.cpp',
    'external/imgui/src/imgui_impl_glfw.cpp',
    'external/imgui/src/imgui_impl_vulkan.cpp',
    'external/imgui/src/imgui_tables.cpp',
    'external/imgui/src/imgui_widgets.cpp',
  ),
  cpp_args: ['-w']
)

# ----- VKRT sources -----
vkrt_sources = files(
  'src/vkrt/buffer.c',
  'src/vkrt/command.c',
  'src/vkrt/descriptor.c',
  'src/vkrt/device.c',
  'src/vkrt/instance.c',
  'src/vkrt/object.c',
  'src/vkrt/pipeline.c',
  'src/vkrt/scene.c',
  'src/vkrt/structure.c',
  'src/vkrt/surface.c',
  'src/vkrt/swapchain.c',
  'src/vkrt/validation.c',
  'src/vkrt/vkrt.c',
)

# ----- Parallax sources -----
parallax_sources = files(
  'src/parallax/gui.c',
  'src/parallax/main.c'
)

# ----- Shader sources -----
shader_sources = [
  'shaders/raytracing/main.rchit',
  'shaders/raytracing/main.rgen',
  'shaders/raytracing/main.rmiss'
]

# ----- Shader targets -----
shader_targets = []
foreach shader_file : shader_sources
    basename = shader_file.split('.')[-1]
    shader_target = custom_target(
        'compile_' + basename,
        input: shader_file,
        output: basename + '.spv',
        command: [glslc, '@INPUT@', '--target-env=vulkan1.4', '-O', '-o', '@OUTPUT@'],
        build_by_default: true,
    )
    shader_targets += shader_target
endforeach

# ----- VKRT executable -----
executable('parallax',
  c_args: c_args,
  sources: vkrt_sources + parallax_sources,
  dependencies: dependencies,
  include_directories: includes,
  link_with: [dcimgui],
  link_language: 'cpp'
)