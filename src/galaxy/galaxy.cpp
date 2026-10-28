#include "galaxy.hpp"
#include <algorithm>
#include <stdexcept>
#include <random>
#include <yaml-cpp/node/node.h>

#define TYPE "type"
#define POINTS "points"
#define SEED "seed"
#define XPOS "xpos"
#define YPOS "ypos"
#define XVEL "xvel"
#define YVEL "yvel"

void Galaxy::New() const {}

void Galaxy::Load(const YAML::Node conf) {
    std::string typeName = conf[TYPE].as<std::string>();
    std::transform(typeName.begin(), typeName.end(), typeName.begin(), ::tolower);

    if (typeName == "spiral") {
        type = Type::Spiral;
    } else if (typeName == "cluster") {
        type = Type::Cluster;
    } else if (typeName == "uniform") {
        type = Type::Uniform;
    } else if (typeName == "voronoi") {
        type = Type::Voronoi;
    } else {
        throw std::invalid_argument(typeName + " not recognized as an init method");
    }

    this->points = conf[POINTS].as<size_t>();

    std::default_random_engine urng(std::random_device{}());
    std::uniform_int_distribution<size_t> gen(0, std::numeric_limits<size_t>::max());
    this->seed = conf[SEED].as<uint64_t>(gen(urng));

    this->xPos = conf[XPOS].as<float>(0.0f);
    this->yPos = conf[YPOS].as<float>(0.0f);

    this->xVel = conf[XVEL].as<float>(0.0f);
    this->yVel = conf[YVEL].as<float>(0.0f);


}

uint64_t Galaxy::Seed() const noexcept {
    return this->seed;
}

size_t Galaxy::Points() const noexcept {
    return this->points;
}

Galaxy::Type Galaxy::GalaxyType() const noexcept {
    return this->type;
}

std::string Galaxy::GalaxyString() const noexcept {
    switch (this->type) {
        case Type::None:
            return "None";
        case Type::Spiral:
            return "Spiral";
        case Type::Cluster:
            return "Cluster";
        case Type::Uniform:
            return "Uniform";
        case Type::Voronoi:
            return "Voronoi";
        default:
            return "Unknown";
    }
}

#undef TYPE
#undef POINTS
#undef SEED
#undef XPOS
#undef YPOS
#undef XVEL
#undef YVEL
