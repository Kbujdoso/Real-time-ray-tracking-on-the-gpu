#include <iostream>
#include <utility>
#include <vector>
#include <optional>
#include "Geometry.h"
#include "Ray.h"
#include "Resolution.h"
#include "Camera.h"
#include "Light.h"
#include "Objects.h"

Scene::Scene(std::vector<Objects> Objects, std::vector<Light> Lights) {
    objects = Objects;
    lights = Lights;
}

Scene::Scene(){
    objects = {};
    lights = {};
}

std::optional<std::pair<Objects, point3D>> sphere_intersection_test(Ray ray, Objects::Sphere sphere){
    segment_vector OC_vector = segment_vector(ray.O, )
    float discriminant = dot_product(ray.D, )
}