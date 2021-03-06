/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qfremeau <qfremeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:46:22 by qfremeau          #+#    #+#             */
/*   Updated: 2016/12/03 17:18:52 by qfremeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		*v3_add_vec(t_vec3 const v1, t_vec3 const v2)
{
	t_vec3		*vec;

	vec = v3_new_vec(v1.x + v2.x,
					v1.y + v2.y,
					v1.z + v2.z);
	return (vec);
}

t_vec3		*v3_sub_vec(t_vec3 const v1, t_vec3 const v2)
{
	t_vec3		*vec;

	vec = v3_new_vec(v1.x - v2.x,
					v1.y - v2.y,
					v1.z - v2.z);
	return (vec);
}

t_vec3		*v3_cross_vec(t_vec3 const v1, t_vec3 const v2)
{
	t_vec3		*vec;

	vec = v3_new_vec(v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x);
	return (vec);
}

t_vec3		*v3_multiply_vec(t_vec3 const v1, t_vec3 const v2)
{
	t_vec3		*vec;

	vec = v3_new_vec(v1.x * v2.x,
					v1.y * v2.y,
					v1.z * v2.z);
	return (vec);
}

t_vec3		*v3_scale_vec(t_vec3 const v, double const c)
{
	t_vec3		*vec;

	vec = v3_new_vec(v.x * c,
					v.y * c,
					v.z * c);
	return (vec);
}

t_vec3		*v3_div_vec(t_vec3 const v, double const c)
{
	t_vec3		*vec;

	vec = v3_new_vec(v.x / c,
					v.y / c,
					v.z / c);
	return (vec);
}
