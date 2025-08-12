project(
    'parallax',
    ['c', 'cpp'],
    default_options: ['c_std=c11', 'warning_level=2'],
)

vkrt_dep = dependency('vkrt')
glslc = find_program('glslc')

shader_inputs = [
    'src/shaders/raytracing/main.rchit',
    'src/shaders/raytracing/main.rgen',
    'src/shaders/raytracing/main.rmiss',
]

shader_targets = []
foreach shader_in : shader_inputs
    basename = shader_in.split('/')[-1]
    shader_target = custom_target(
        'compile_' + basename,
        input: shader_in,
        output: basename + '.spv',
        command: [glslc, '@INPUT@', '--target-env=vulkan1.4', '-O', '-o', '@OUTPUT@'],
        build_by_default: true,
    )
    shader_targets += shader_target
endforeach

sources = [
    'src/main.c',
    'src/interface.c',
]

executable(
    'parallax',
    sources,
    dependencies: [vkrt_dep],
    link_language: 'cpp'
)
