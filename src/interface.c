#include "interface.h"

void initGUI(VKRT* vkrt) {
    vkrt->imguiContext = ImGui_CreateContext(NULL);

    ImGuiIO* io = ImGui_GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    VKRT_setDefaultStyle();

    cImGui_ImplGlfw_InitForVulkan(vkrt->window, true);

    ImGui_ImplVulkan_InitInfo imGuiVulkanInitInfo = {0};
    VKRT_getImGuiVulkanInitInfo(vkrt, &imGuiVulkanInitInfo);
    cImGui_ImplVulkan_Init(&imGuiVulkanInitInfo);

    cImGui_ImplVulkan_CreateFontsTexture();
}

void deinitGUI(VKRT* vkrt) {
    cImGui_ImplVulkan_Shutdown();
    cImGui_ImplGlfw_Shutdown();
    ImGui_DestroyContext(vkrt->imguiContext);
}

void drawGUI(VKRT* vkrt) {
    cImGui_ImplGlfw_NewFrame();
    cImGui_ImplVulkan_NewFrame();
    ImGui_NewFrame();

    VKRT_pollCameraMovement(vkrt);

    {
        ImGui_PushStyleVar(ImGuiStyleVar_WindowRounding, 8.0f);
        ImGui_PushStyleVar(ImGuiStyleVar_GrabRounding, 8.0f);
        ImGui_PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

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
    
        ImGui_PopStyleVarEx(3);
    }

    ImGui_End();
    ImGui_Render();
}
