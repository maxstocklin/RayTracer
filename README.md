# RayTracer - A CGI Rendering Program

RayTracer is a powerful CGI rendering program that utilizes advanced graphics techniques to create stunning visual simulations. Developed in C with the Minilibx library, it harnesses the same technology used in the world of cinema to deliver exceptional rendering capabilities.

![Example Image](./images/chessroom.png)


## Table of Contents
1. [Description](#description)
    * [Features](#features)
    * [What is Ray Tracing?](#what-is-ray-tracing)
    * [What is Photon Mapping?](#what-is-photon-mapping)
2. [Installation](#installation)
3. [Usage](#usage)
    * [Mandatory](#mandatory)
    * [Optional](#optional)
    * [Special Cases](#special-elements)
5. [Examples](#examples)

## Description
<details>
<summary>Click to expand</summary>

### Features
<details>
<summary>Click to expand</summary>

With RayTracer, you can achieve lifelike reflections, refractions, and shading effects. The program employs ray tracing, simulating the behavior of light as it interacts with various materials. This enables the rendering of realistic metallic reflections, transparent surfaces with accurate refraction, and sophisticated shading effects using Phong's lighting model, encompassing ambient, diffuse, and specular lighting.

One of RayTracer's standout features is its implementation of photon mapping. This technique captures the intricate interplay of light and object interactions, resulting in visually stunning caustic lighting effects. By accurately simulating the paths of photons, RayTracer adds depth and realism to your scenes.

RayTracer supports a wide range of geometric primitives, including planes, spheres, cylinders, discs, and cones, giving you the flexibility to create diverse virtual environments. Additionally, the program offers support for checkerboard color disruption, enabling the generation of captivating visual patterns and textures. Furthermore, you can apply bump map textures to objects, adding intricate details and enhancing the overall realism of your rendered scenes.

With RayTracer's combination of CGI technology, ray tracing, and photon mapping, you have the power to bring your creative visions to life with great precision and visual fidelity.
 
</details>

### What is Ray Tracing?
<details>
<summary>Click to expand</summary>

   
Ray tracing is a technique used in computer graphics to create realistic images by simulating the behavior of light. Ray tracing operates in reverse compared to real-life light propagation. While in real life, light rays travel from the light source to our eyes, in ray tracing, virtual rays are traced backward from the viewer's or camera's perspective. While it may seem counterintuitive, ray tracing allows us to simulate light propagation in a controlled and efficient manner. By considering properties like reflection, refraction, and shading (including ambient, diffuse, and specular lights), ray tracing calculates the color and illumination of each pixel, resulting in visually accurate and detailed renderings.
</details>

### What is Photon Mapping?
<details>
<summary>Click to expand</summary>

   
Photon mapping is a technique used to capture the behavior of light more realistically in computer graphics. Unlike ray tracing, which traces rays backward from the viewer's perspective, photon mapping works more like real-life light propagation. It simulates the emission of photons from light sources, their interactions with objects in the scene, and their subsequent contributions to illumination effects. These photons bounce off surfaces, undergo reflections, refractions, and scattering, and are accumulated in a data structure called the photon map. During rendering, the photon map is used in conjunction with ray tracing to compute indirect illumination, global illumination, caustics, and other complex lighting phenomena. By simulating light more faithfully, photon mapping enhances the realism and visual quality of rendered scenes, capturing the intricate interactions of light just as they occur in the real world.

</details>
</details>

## Installation
<details>
<summary>Click to expand</summary>

   
Follow these steps to install and compile the RayTracer:

1. Clone the repository:
    ```bash
    git clone git@github.com:maxstocklin/RayTracer.git raytracer
    ```
2. Navigate into the cloned repository and compile it:
    ```bash
    cd raytracer && make
    ```
   
</details>

## Usage
<details>
<summary>Click to expand</summary>

   
To use RayTracer, execute the following command:
    ```bash
   ./raytracer ./files/fourspheres.rt
    ```

RayTracer takes as a first argument a scene description file with the ```.rt``` extension. There are some scenes in the ```files``` folder that showcase RayTracer. Otherwise, you can create your own ```.rt``` file.
Shapes and elements can be defined as follow:

### Mandatory:
<details>
<summary>Click to expand</summary>

   
AMBIENT LIGHTNING:

| ID | LIGHTING RATIO | RGB COLORS |
| :-------------- | :-------------: | :-------------: |
| A | 0.2 | 255,255,255 | 

CAMERA:

| ID | ORIGIN | ORIENTATION | ANGLE |
| :-------------- | :-------------: | :-------------: | :-------------: |
| C | -50,0,20 | 0,0,1 | 67 |
</details>

### Optional:
<details>
<summary>Click to expand</summary>

LIGHTS:
| ID | ORIGIN | BRIGHTNESS RATIO | RGB COLORS |
| :-------------- | :-------------: | :-------------: | :-------------: |
| L | -50,0,20 | 0.6 | 255,255,255 |

PLANES:
| ID |  ORIGIN | ORIENTATION | RGB COLORS | REFLECTION RATIO |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: |
| pl | -5,22,20 | 0,0,1 | 255,255,255 | 0.2 |

SPHERES:
| ID | ORIGIN | DIAMETER | RGB COLORS | REFLECTION RATIO |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: |
| sp | -10,0,80 | 20.7 | 255,255,255 | 0.9 |

CYLINDERS:
|  ID | ORIGIN | ORIENTATION | DIAMETER | HEIGHT | RGB COLORS | REFLECTION RATIO |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| cy | 0,10,-130 | 0.2,0,-1 | 15 | 27.2 | 255,255,255 | 0 |

CONES:
|  ID | ORIGIN | ORIENTATION | ANGLE | RGB COLORS | REFLECTION RATIO |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| cn | -50,0,20 | -0.8,0.3,-0.2 | 35 | 0,122,255 | 0.6 |
</details>

### Special Elements:
<details>
<summary>Click to expand</summary>

SPOTLIGHTS (PHOTON MAP):
| ID | ORIGIN | BRIGHTNESS RATIO | RGB COLORS |  ORIENTATION | ANGLE |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| LS | -50,0,20 | 0.6 | 255,255,255 | -1,-0.95,0 | 45 |

CHECKERBOARD PLANES:
| ID |  ORIGIN | ORIENTATION | RGB COLORS | REFLECTION RATIO | MATERIAL (optional) |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| pl | -5,22,20 | 0,0,1 | 255,255,255 | 0.2 | checkerboard |

CHECKERBOARD SPHERES:
| ID | ORIGIN | DIAMETER | RGB COLORS | REFLECTION RATIO | MATERIAL (optional) |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| sp | -10,0,80 | 20.7 | 255,255,255 | 0.9 | checkerboard |

BUMP MAP TEXTURED SPHERES:
| ID | ORIGIN | DIAMETER | RGB COLORS | REFLECTION RATIO | MATERIAL (optional) |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| sp | -10,0,80 | 20.7 | 255,255,255 | 0.9 | bumpmap |

TRANSPARENT SPHERES:
| ID | ORIGIN | DIAMETER | RGB COLORS | REFLECTION RATIO | MATERIAL (optional) |
| :-------------- | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| sp | -10,0,80 | 20.7 | 255,255,255 | 0.9 | transparent |
</details>

</details>

## Examples

### Example of All Objects (Sphere, Plane, Cylinder, Cone)

![Example Caustic](./images/room.png)

### Example of Bump Map Texture Applied to a Sphere

![Example Caustic](./images/moon.png)


### Example of Mirror, Bump Map Texture, Checkerboard Color Disruption, and Transparency Applied to Spheres

![Example Caustic](./images/fourspheres.png)

### Basic Example of Caustic Light Using a Photon Map

![Example Caustic](./images/caustic.png)

### Advanced Example of Caustic Light Using a Photon Map

![Example Caustic](./images/caustic2.png)


### 100 Spheres

![Example Caustic](./images/100spheres.png)


## Contributors

- [@stuartrapop](https://github.com/stuartrapop)
- [@maxstocklin](https://github.com/maxstocklin)


