#include "interface.h"

#include "dcimgui.h"
#include "dcimgui_impl_glfw.h"
#include "dcimgui_impl_vulkan.h"
#include "dcimgui_internal.h"

void initGUI(VKRT* vkrt) {
    vkrt->imguiContext = ImGui_CreateContext(NULL);

    ImGuiIO* io = ImGui_GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    VKRT_setDarkTheme();

    ImGuiStyle* style = ImGui_GetStyle();
    style->WindowRounding = 2;
    style->GrabRounding = 2;
    style->FrameRounding = 2;
    style->FrameBorderSize = 0;
    style->WindowBorderSize = 0;
    style->DockingSeparatorSize = 1;
    style->WindowPadding = (ImVec2){8, 5};

    cImGui_ImplGlfw_InitForVulkan(vkrt->window, true);
    ImGui_ImplVulkan_InitInfo imGuiVulkanInitInfo = {0};
    imGuiVulkanInitInfo.Instance = vkrt->instance;
    imGuiVulkanInitInfo.PhysicalDevice = vkrt->physicalDevice;
    imGuiVulkanInitInfo.Device = vkrt->device;
    imGuiVulkanInitInfo.Queue = vkrt->graphicsQueue;
    imGuiVulkanInitInfo.QueueFamily = vkrt->indices.graphics;
    imGuiVulkanInitInfo.PipelineCache = VK_NULL_HANDLE;
    imGuiVulkanInitInfo.DescriptorPool = vkrt->descriptorPool;
    imGuiVulkanInitInfo.Allocator = VK_NULL_HANDLE;
    uint32_t imgCount = (uint32_t)vkrt->swapChainImageCount;
    uint32_t minImgCount = (imgCount > 1u) ? (imgCount - 1u) : imgCount;
    imGuiVulkanInitInfo.MinImageCount = minImgCount;
    imGuiVulkanInitInfo.ImageCount = imgCount;
    imGuiVulkanInitInfo.CheckVkResultFn = VK_NULL_HANDLE;
    imGuiVulkanInitInfo.RenderPass = vkrt->renderPass;

    cImGui_ImplVulkan_Init(&imGuiVulkanInitInfo);
    cImGui_ImplVulkan_CreateFontsTexture();
}

void deinitGUI(VKRT* vkrt) {
    cImGui_ImplVulkan_Shutdown();
    cImGui_ImplGlfw_Shutdown();

    ImGui_DestroyContext(vkrt->imguiContext);}

void drawGUI(VKRT* vkrt) {
    cImGui_ImplGlfw_NewFrame();
    cImGui_ImplVulkan_NewFrame();
    ImGui_NewFrame();

    VKRT_pollCameraMovement(vkrt);

    ImGui_PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
    ImGui_PushStyleVar(ImGuiStyleVar_GrabRounding, 10.0f);
    bool open = true;
    ImGui_Begin("Statistics", &open, ImGuiWindowFlags_NoTitleBar);

    ImGui_Text("Device: %s", vkrt->deviceName);
    ImGui_Text("Resolution: %dx%d", vkrt->camera.width, vkrt->camera.height);

    if (ImGui_Checkbox("V-Sync", (bool*)&vkrt->vsync)) {
        vkrt->framebufferResized = VK_TRUE;
    }

    ImGui_NewLine();
    ImGui_Text("FPS:                %6d", vkrt->framesPerSecond);
    ImGui_Text("Render time:        %6.3f ms", vkrt->renderTimeMs);
    ImGui_Text("Frame time:         %6.3f ms", vkrt->displayTimeMs);
    ImGui_Text("Average frame time: %6.3f ms", vkrt->averageFrametime);
    ImGui_Text("Samples per pixel:  %6d", vkrt->sceneData->samplesPerPixel);
    ImGui_Text("Total samples:      %6d", vkrt->sceneData->totalSamples);
    ImGui_NewLine();

    ImGui_PlotLinesEx("##", vkrt->frametimes, COUNT_OF(vkrt->frametimes), (int)vkrt->frametimeStartIndex, "", 0.0f, 2 * vkrt->averageFrametime, (ImVec2){160.0f, 40.0f}, sizeof(float));

    ImGui_End();

    ImGui_PopStyleVar();
    ImGui_PopStyleVar();

    ImGui_Render();
}
