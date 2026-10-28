#pragma once
#include <cstddef>
#include <cstdint>
#include <yaml-cpp/yaml.h>

struct Galaxy {
    public:
        enum class Type {
            None, Spiral, Cluster, Uniform, Voronoi
        };

        Galaxy() noexcept  : type(Type::None), points(0) {}
        Galaxy(const YAML::Node conf) : type(Type::None), points(0) {
            this->Load(conf);
        }

        /// @brief Creates a new galaxy based on the previously loaded config, this is a factory function and each call is independent of the last, (internal rng state updates between calls)
        void New() const;

        void Load(const YAML::Node conf);

        uint64_t Seed() const noexcept;
        size_t Points() const noexcept;

        Type GalaxyType() const noexcept;
        std::string GalaxyString() const noexcept;

    private:
        Type type;
        size_t points;
        uint64_t seed;

        float xPos;
        float yPos;

        float xVel;
        float yVel;
};
