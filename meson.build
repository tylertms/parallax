project(
    'parallax',
    ['c', 'cpp'],
    default_options: ['c_std=c11', 'warning_level=2'],
)

vkrt_sp = subproject('vkrt', default_options: ['build_examples=false'])
vkrt_dep = vkrt_sp.get_variable('vkrt_dep')

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

c_args = ['-D_GNU_SOURCE']

sources = [
    'src/main.c',
    'src/interface.c',
]

executable(
    'parallax',
    sources,
    c_args: c_args,
    dependencies: [vkrt_dep],
    link_language: 'cpp'
)
