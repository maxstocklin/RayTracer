# RayTracer - A CGI Rendering Program

## Table of Contents
1. [Description](#description)
    * [Features](#features)
    * [What is Ray Tracing?](#what-is-ray-tracing)
    * [What is Photon Mapping?](#what-is-photon-mapping)
2. [Installation](#installation)
3. [Usage](#usage)
    * [Mandatory](#mandatory)
    * [Optional](#optional)
5. [Examples](#examples)
6. [Contributing](#contributing)
7. [License](#license)

## Description

RayTracer is a powerful CGI rendering program that utilizes advanced graphics techniques to create stunning visual simulations. Developed in C with the Minilibx library, it harnesses the same technology used in the world of cinema to deliver exceptional rendering capabilities.

### Features

With RayTracer, you can achieve lifelike reflections, refractions, and shading effects. The program employs ray tracing, simulating the behavior of light as it interacts with various materials. This enables the rendering of realistic metallic reflections, transparent surfaces with accurate refraction, and sophisticated shading effects using Phong's lighting model, encompassing ambient, diffuse, and specular lighting.

One of RayTracer's standout features is its implementation of photon mapping. This technique captures the intricate interplay of light and object interactions, resulting in visually stunning caustic lighting effects. By accurately simulating the paths of photons, RayTracer adds depth and realism to your scenes.

RayTracer supports a wide range of geometric primitives, including planes, spheres, cylinders, discs, and cones, giving you the flexibility to create diverse virtual environments. Additionally, the program offers support for checkerboard color disruption, enabling the generation of captivating visual patterns and textures. Furthermore, you can apply bump map textures to objects, adding intricate details and enhancing the overall realism of your rendered scenes.

With RayTracer's combination of CGI technology, ray tracing, and photon mapping, you have the power to bring your creative visions to life with unparalleled precision and visual fidelity.

### What is Ray Tracing?

Ray tracing is a technique used in computer graphics to create realistic images by simulating the behavior of light. Ray tracing operates in reverse compared to real-life light propagation. While in real life, light rays travel from the light source to our eyes, in ray tracing, virtual rays are traced backward from the viewer's or camera's perspective. While it may seem counterintuitive, ray tracing allows us to simulate light propagation in a controlled and efficient manner. By considering properties like reflection, refraction, and shading (including ambient, diffuse, and specular lights), ray tracing calculates the color and illumination of each pixel, resulting in visually accurate and detailed renderings.

### What is Photon Mapping?

Photon mapping is a technique used to capture the behavior of light more realistically in computer graphics. Unlike ray tracing, which traces rays backward from the viewer's perspective, photon mapping works more like real-life light propagation. It simulates the emission of photons from light sources, their interactions with objects in the scene, and their subsequent contributions to illumination effects. These photons bounce off surfaces, undergo reflections, refractions, and scattering, and are accumulated in a data structure called the photon map. During rendering, the photon map is used in conjunction with ray tracing to compute indirect illumination, global illumination, caustics, and other complex lighting phenomena. By simulating light more faithfully, photon mapping enhances the realism and visual quality of rendered scenes, capturing the intricate interactions of light just as they occur in the real world.

## Installation

Follow these steps to install and compile the RayTracer:

1. Clone the repository:
    ```bash
    git clone git@github.com:maxstocklin/RayTracer.git raytracer
    ```
2. Navigate into the cloned repository and compile it:
    ```bash
    cd raytracer && make
    ```
## Usage

To use RayTracer, execute the following command:
    ```bash
   ./raytracer ./files/fourspheres.rt
    ```

RayTracer takes as a first argument a scene description file with the ```.rt``` extension. There are some scenes in the ```files``` folder that showcase RayTracer. Otherwise, you can create your own ```.rt``` file.
Shapes and elements can be defined as follow:

### Mandatory:
Origin	Orientation	Scale	Radius	width	Height	Color

Ambient lightning:
markdown
| Column 1 ID | Column 2 LIGHTING RATIO | Column 3 RGB COLORS |
| :-------------- | :-------------: |
| A    | 0.2 | 255,255,255 | 

Camera:
markdown
| Column 1 ID | Column 2 ORIGIN | Column 3 ORIENTATION | Column 4 ANGLE |
| :-------------- | :-------------: |
| C    | -50,0,20 | 0,0,1 | 67 |

### Optional:

