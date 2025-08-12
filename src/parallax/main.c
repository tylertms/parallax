#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gui.h"
#include "vkrt.h"

int main(void) {
    VKRT parallax = {0};

    VKRT_registerGUI(&parallax, initGUI, deinitGUI, drawGUI);

    if (VKRT_init(&parallax) != VK_SUCCESS) {
        fprintf(stderr, "ERROR: Failed to initialize VKRT object\n");
        VKRT_deinit(&parallax);
        return EXIT_FAILURE;
    }

    VKRT_addMesh(&parallax, "assets/models/sphere.glb");
    VKRT_addMesh(&parallax, "assets/models/dragon.glb");

    Material light = {
        .color = {0.f, 0.f, 0.f},
        .roughness = 1.f,
        .emissiveColor = {1.f, 1.f, 1.f},
        .emissiveIntensity = 6.f
    };
    VKRT_addMaterial(&parallax, &light);

    Material white = {
        .color = {1.f, 1.f, 1.f},
        .roughness = 1.f,
        .emissiveColor = {0.f, 0.f, 0.f},
        .emissiveIntensity = 0.f
    };
    VKRT_addMaterial(&parallax, &white);

    parallax.meshes[0].info.materialIndex = 0;
    parallax.meshes[1].info.materialIndex = 1;

    vec3 sphereScale = {0.5f, 0.5f, 0.5f};
    memcpy(&parallax.meshes[0].info.scale, &sphereScale, sizeof(vec3));

    vec3 spherePosition = {-1.0f, 0.5f, -1.0f};
    memcpy(&parallax.meshes[0].info.position, &spherePosition, sizeof(vec3));

    vec3 dragonPosition = {0.0f, 0.0f, 0.0f};
    vec3 dragonRotation = {0.0f, 0.0f, 0.0f};
    vec3 dragonScale = {2.0f, 2.0f, 2.0f};

    memcpy(&parallax.meshes[1].info.scale, &dragonScale, sizeof(vec3));
    memcpy(&parallax.meshes[1].info.position, &dragonPosition, sizeof(vec3));
    memcpy(&parallax.meshes[1].info.rotation, &dragonRotation, sizeof(vec3));

    VKRT_updateTLAS(&parallax);

    while (!VKRT_shouldDeinit(&parallax)) {
        VKRT_poll(&parallax);
        VKRT_draw(&parallax);
    }

    VKRT_deinit(&parallax);

    return EXIT_SUCCESS;
}
