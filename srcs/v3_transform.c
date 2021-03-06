/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 22:57:30 by qfremeau          #+#    #+#             */
/*   Updated: 2016/11/28 16:00:17 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		v3_negative(t_vec3 *v)
{
	v->x *= -1;
	v->y *= -1;
	v->z *= -1;
}

void		v3_normalize(t_vec3 *v)
{
	double	m;

	m = v3_magnitude_double(*v);
	v->x *= m;
	v->y *= m;
	v->z *= m;
}

double		v3_dot_double(t_vec3 const v1, t_vec3 const v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		v3_magnitude_double(t_vec3 const v)
{
	return (1 / sqrt(v3_dot_double(v, v)));
}

double		v3_lenght_double(t_vec3 const v)
{
	return (sqrt(v3_dot_double(v, v)));
}
