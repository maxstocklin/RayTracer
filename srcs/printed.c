#include "minirt.h"

void    ft_print_ray(t_minirt ray)
{
	if (ray.ambiant)

	{
		printf("AMBIANT:\n");
		printf("intensity: %f\n", ray.ambiant->intensity);
		printf("R = %d G = %d B = %d\n", ray.ambiant->rgb.red, ray.ambiant->rgb.green, ray.ambiant->rgb.blue);
	}
	if (ray.camera)
	{
		printf("\nCAMERA:\n");
		printf("coordinates x = %f y = %f z %f\n", ray.camera->origin.x, ray.camera->origin.y, ray.camera->origin.z);
		printf("orientation x = %f y = %f z %f\n", ray.camera->direction.x, ray.camera->direction.y,
			   ray.camera->direction.z);
		printf("Angle: %f\n", ray.camera->angle);
	}
	if (ray.lights)
	{
		printf("\nSPOTLIGHT:\n");
		printf("coordinates x = %f y = %f z %f\n", ray.lights->origin.x, ray.lights->origin.y, ray.lights->origin.z);
		printf("intensity: %f\n", ray.lights->intensity);
		printf("R = %d G = %d B = %d\n", ray.lights->rgb.red, ray.lights->rgb.green, ray.lights->rgb.blue);
	}
	if (ray.spheres)
	{
		printf("\nSPHERE:\n");
		printf("coordinates x = %f y = %f z %f\n", ray.spheres->origin.x, ray.spheres->origin.y, ray.spheres->origin.z);
		printf("index = %d\n", ray.spheres->index);
		printf("diameter: %f\n", ray.spheres->diameter);
		printf("R = %d G = %d B = %d\n", ray.spheres->rgb.red, ray.spheres->rgb.green, ray.spheres->rgb.blue);
	}
	if (ray.planes)
	{
		printf("\nPLANE:\n");
		printf("coordinates x = %f y = %f z %f\n", ray.planes->point.x, ray.planes->point.y, ray.planes->point.z);
		printf("normal x = %f y = %f z %f\n", ray.planes->normal.x, ray.planes->normal.y, ray.planes->normal.z);
		printf("R = %d G = %d B = %d\n", ray.planes->rgb.red, ray.planes->rgb.green, ray.planes->rgb.blue);
	}
	if (ray.cylinders)
	{
		printf("\nCYLINDER:\n");
		printf("coordinates x = %f y = %f z %f\n", ray.cylinders->origin.x, ray.cylinders->origin.y, ray.cylinders->origin.z);
		printf("diameter: %f\n", ray.cylinders->diameter);
		printf("height: %f\n", ray.cylinders->height);
		printf("R = %d G = %d B = %d\n", ray.cylinders->rgb.red, ray.cylinders->rgb.green, ray.cylinders->rgb.blue);
	}}
