
#pragma once

#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <iomanip>

class Profiler {
public:
    using Clock = std::chrono::steady_clock;

    enum class Stage : std::size_t {
        ClearFramebuffer,
        ClearZBuffer,
        Collisions,
        UpdatePipeline,
        RenderPipeline,
        CameraController,
        SDLUpload,
        SDLPresent,
        FrameTotal,
        Count
    };

private:
    struct Stat {
        double totalUs = 0.0;
        double minUs = 1e30;
        double maxUs = 0.0;
        std::uint64_t samples = 0;

        void add(double us) {
            totalUs += us;

            if (us < minUs)
                minUs = us;

            if (us > maxUs)
                maxUs = us;

            ++samples;
        }

        void reset() {
            *this = Stat{};
        }

        double average() const {
            return samples ? totalUs / samples : 0.0;
        }
    };

    static constexpr std::size_t stageCount =
        static_cast<std::size_t>(Stage::Count);

    std::array<Stat, stageCount> stats{};

    Clock::time_point reportStart = Clock::now();
    std::uint64_t frameCount = 0;

    static constexpr const char* names[] = {
        "Clear framebuffer",
        "Clear Z-buffer",
        "Collisions",
        "Update pipeline",
        "Render pipeline",
        "Camera controller",
        "SDL texture upload",
        "SDL draw/present",
        "Frame total"
    };

    static constexpr std::size_t index(Stage stage) {
        return static_cast<std::size_t>(stage);
    }

public:
    template<typename Function>
    void measure(Stage stage, Function&& function) {
        const auto start = Clock::now();

        function();

        const auto end = Clock::now();

        const double us =
            std::chrono::duration<double, std::micro>(
                end - start
            ).count();

        stats[index(stage)].add(us);
    }

    void endFrame() {
        ++frameCount;

        const auto now = Clock::now();

        const double elapsed =
            std::chrono::duration<double>(
                now - reportStart
            ).count();

        if (elapsed < 1.0)
            return;

        std::cout << "\n========== ENGINE PROFILER ==========\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "FPS promedio: "
                  << frameCount / elapsed << '\n';

        std::cout << std::left
                  << std::setw(24) << "Etapa"
                  << std::right
                  << std::setw(12) << "Avg (us)"
                  << std::setw(12) << "Min (us)"
                  << std::setw(12) << "Max (us)"
                  << '\n';

        for (std::size_t i = 0; i < stageCount; ++i) {
            const Stat& s = stats[i];

            if (s.samples == 0)
                continue;

            std::cout << std::left
                      << std::setw(24) << names[i]
                      << std::right
                      << std::setw(12) << s.average()
                      << std::setw(12) << s.minUs
                      << std::setw(12) << s.maxUs
                      << '\n';
        }

        for (auto& stat : stats)
            stat.reset();

        frameCount = 0;
        reportStart = now;
    }
};
