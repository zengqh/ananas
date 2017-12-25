#include <thread>
#include <cstdio>
#include "net/EventLoop.h"
#include "net/EventLoopGroup.h"
#include "net/Application.h"

using namespace ananas;

int main()
{
    EventLoopGroup group(1);
    auto& app = Application::Instance();
    auto& loop = *group.SelectLoop();

    // exit after sleep 5 seconds
    loop.Sleep(std::chrono::seconds(5))
        .Then([&app]() {
            printf("After sleep for 5 seconds, exit!\n");
            app.Exit();
        });

    loop.ScheduleAfter<kForever>(std::chrono::seconds(1), []() {
        printf("waiting for exit...\n");
    });

    app.Run();

    return 0;
}
