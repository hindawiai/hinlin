<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

#समावेश <linux/videodev2.h>

#समावेश "atomisp_internal.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_ioctl.h"
#समावेश "atomisp_compat_ioctl32.h"

/* Macros borrowed from v4l2-compat-ioctl32.c */

#घोषणा get_user_cast(__x, __ptr)					\
(अणु									\
	get_user(__x, (typeof(*__ptr) __user *)(__ptr));		\
पूर्ण)

#घोषणा put_user_क्रमce(__x, __ptr)					\
(अणु									\
	put_user((typeof(*__x) __क्रमce *)(__x), __ptr);			\
पूर्ण)

/* Use the same argument order as copy_in_user */
#घोषणा assign_in_user(to, from)					\
(अणु									\
	typeof(*from) __assign_पंचांगp;					\
									\
	get_user_cast(__assign_पंचांगp, from) || put_user(__assign_पंचांगp, to);\
पूर्ण)

अटल पूर्णांक get_atomisp_histogram32(काष्ठा atomisp_histogram __user *kp,
				   काष्ठा atomisp_histogram32 __user *up)
अणु
	compat_uptr_t पंचांगp;

	अगर (!access_ok(up, माप(काष्ठा atomisp_histogram32)) ||
	    assign_in_user(&kp->num_elements, &up->num_elements) ||
	    get_user(पंचांगp, &up->data) ||
	    put_user(compat_ptr(पंचांगp), &kp->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_histogram32(काष्ठा atomisp_histogram __user *kp,
				   काष्ठा atomisp_histogram32 __user *up)
अणु
	व्योम __user *पंचांगp;

	अगर (!access_ok(up, माप(काष्ठा atomisp_histogram32)) ||
	    assign_in_user(&up->num_elements, &kp->num_elements) ||
	    get_user(पंचांगp, &kp->data) ||
	    put_user(ptr_to_compat(पंचांगp), &up->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_v4l2_framebuffer32(काष्ठा v4l2_framebuffer __user *kp,
				  काष्ठा v4l2_framebuffer32 __user *up)
अणु
	compat_uptr_t पंचांगp;

	अगर (!access_ok(up, माप(काष्ठा v4l2_framebuffer32)) ||
	    get_user(पंचांगp, &up->base) ||
	    put_user_क्रमce(compat_ptr(पंचांगp), &kp->base) ||
	    assign_in_user(&kp->capability, &up->capability) ||
	    assign_in_user(&kp->flags, &up->flags) ||
	    copy_in_user(&kp->fmt, &up->fmt, माप(kp->fmt)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_dis_statistics32(काष्ठा atomisp_dis_statistics __user *kp,
					काष्ठा atomisp_dis_statistics32 __user *up)
अणु
	compat_uptr_t hor_prod_odd_real;
	compat_uptr_t hor_prod_odd_imag;
	compat_uptr_t hor_prod_even_real;
	compat_uptr_t hor_prod_even_imag;
	compat_uptr_t ver_prod_odd_real;
	compat_uptr_t ver_prod_odd_imag;
	compat_uptr_t ver_prod_even_real;
	compat_uptr_t ver_prod_even_imag;

	अगर (!access_ok(up, माप(काष्ठा atomisp_dis_statistics32)) ||
	    copy_in_user(kp, up, माप(काष्ठा atomisp_dvs_grid_info)) ||
	    get_user(hor_prod_odd_real,
		     &up->dvs2_स्थिति.सor_prod.odd_real) ||
	    get_user(hor_prod_odd_imag,
		     &up->dvs2_स्थिति.सor_prod.odd_imag) ||
	    get_user(hor_prod_even_real,
		     &up->dvs2_स्थिति.सor_prod.even_real) ||
	    get_user(hor_prod_even_imag,
		     &up->dvs2_स्थिति.सor_prod.even_imag) ||
	    get_user(ver_prod_odd_real,
		     &up->dvs2_stat.ver_prod.odd_real) ||
	    get_user(ver_prod_odd_imag,
		     &up->dvs2_stat.ver_prod.odd_imag) ||
	    get_user(ver_prod_even_real,
		     &up->dvs2_stat.ver_prod.even_real) ||
	    get_user(ver_prod_even_imag,
		     &up->dvs2_stat.ver_prod.even_imag) ||
	    assign_in_user(&kp->exp_id, &up->exp_id) ||
	    put_user(compat_ptr(hor_prod_odd_real),
		     &kp->dvs2_स्थिति.सor_prod.odd_real) ||
	    put_user(compat_ptr(hor_prod_odd_imag),
		     &kp->dvs2_स्थिति.सor_prod.odd_imag) ||
	    put_user(compat_ptr(hor_prod_even_real),
		     &kp->dvs2_स्थिति.सor_prod.even_real) ||
	    put_user(compat_ptr(hor_prod_even_imag),
		     &kp->dvs2_स्थिति.सor_prod.even_imag) ||
	    put_user(compat_ptr(ver_prod_odd_real),
		     &kp->dvs2_stat.ver_prod.odd_real) ||
	    put_user(compat_ptr(ver_prod_odd_imag),
		     &kp->dvs2_stat.ver_prod.odd_imag) ||
	    put_user(compat_ptr(ver_prod_even_real),
		     &kp->dvs2_stat.ver_prod.even_real) ||
	    put_user(compat_ptr(ver_prod_even_imag),
		     &kp->dvs2_stat.ver_prod.even_imag))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_dis_statistics32(काष्ठा atomisp_dis_statistics __user *kp,
					काष्ठा atomisp_dis_statistics32 __user *up)
अणु
	व्योम __user *hor_prod_odd_real;
	व्योम __user *hor_prod_odd_imag;
	व्योम __user *hor_prod_even_real;
	व्योम __user *hor_prod_even_imag;
	व्योम __user *ver_prod_odd_real;
	व्योम __user *ver_prod_odd_imag;
	व्योम __user *ver_prod_even_real;
	व्योम __user *ver_prod_even_imag;

	अगर (!!access_ok(up, माप(काष्ठा atomisp_dis_statistics32)) ||
	    copy_in_user(up, kp, माप(काष्ठा atomisp_dvs_grid_info)) ||
	    get_user(hor_prod_odd_real,
		     &kp->dvs2_स्थिति.सor_prod.odd_real) ||
	    get_user(hor_prod_odd_imag,
		     &kp->dvs2_स्थिति.सor_prod.odd_imag) ||
	    get_user(hor_prod_even_real,
		     &kp->dvs2_स्थिति.सor_prod.even_real) ||
	    get_user(hor_prod_even_imag,
		     &kp->dvs2_स्थिति.सor_prod.even_imag) ||
	    get_user(ver_prod_odd_real,
		     &kp->dvs2_stat.ver_prod.odd_real) ||
	    get_user(ver_prod_odd_imag,
		     &kp->dvs2_stat.ver_prod.odd_imag) ||
	    get_user(ver_prod_even_real,
		     &kp->dvs2_stat.ver_prod.even_real) ||
	    get_user(ver_prod_even_imag,
		     &kp->dvs2_stat.ver_prod.even_imag) ||
	    put_user(ptr_to_compat(hor_prod_odd_real),
		     &up->dvs2_स्थिति.सor_prod.odd_real) ||
	    put_user(ptr_to_compat(hor_prod_odd_imag),
		     &up->dvs2_स्थिति.सor_prod.odd_imag) ||
	    put_user(ptr_to_compat(hor_prod_even_real),
		     &up->dvs2_स्थिति.सor_prod.even_real) ||
	    put_user(ptr_to_compat(hor_prod_even_imag),
		     &up->dvs2_स्थिति.सor_prod.even_imag) ||
	    put_user(ptr_to_compat(ver_prod_odd_real),
		     &up->dvs2_stat.ver_prod.odd_real) ||
	    put_user(ptr_to_compat(ver_prod_odd_imag),
		     &up->dvs2_stat.ver_prod.odd_imag) ||
	    put_user(ptr_to_compat(ver_prod_even_real),
		     &up->dvs2_stat.ver_prod.even_real) ||
	    put_user(ptr_to_compat(ver_prod_even_imag),
		     &up->dvs2_stat.ver_prod.even_imag) ||
	    assign_in_user(&up->exp_id, &kp->exp_id))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_dis_coefficients32(काष्ठा atomisp_dis_coefficients __user *kp,
					  काष्ठा atomisp_dis_coefficients32 __user *up)
अणु
	compat_uptr_t hor_coefs_odd_real;
	compat_uptr_t hor_coefs_odd_imag;
	compat_uptr_t hor_coefs_even_real;
	compat_uptr_t hor_coefs_even_imag;
	compat_uptr_t ver_coefs_odd_real;
	compat_uptr_t ver_coefs_odd_imag;
	compat_uptr_t ver_coefs_even_real;
	compat_uptr_t ver_coefs_even_imag;

	अगर (!access_ok(up, माप(काष्ठा atomisp_dis_coefficients32)) ||
	    copy_in_user(kp, up, माप(काष्ठा atomisp_dvs_grid_info)) ||
	    get_user(hor_coefs_odd_real, &up->hor_coefs.odd_real) ||
	    get_user(hor_coefs_odd_imag, &up->hor_coefs.odd_imag) ||
	    get_user(hor_coefs_even_real, &up->hor_coefs.even_real) ||
	    get_user(hor_coefs_even_imag, &up->hor_coefs.even_imag) ||
	    get_user(ver_coefs_odd_real, &up->ver_coefs.odd_real) ||
	    get_user(ver_coefs_odd_imag, &up->ver_coefs.odd_imag) ||
	    get_user(ver_coefs_even_real, &up->ver_coefs.even_real) ||
	    get_user(ver_coefs_even_imag, &up->ver_coefs.even_imag) ||
	    put_user(compat_ptr(hor_coefs_odd_real),
		     &kp->hor_coefs.odd_real) ||
	    put_user(compat_ptr(hor_coefs_odd_imag),
		     &kp->hor_coefs.odd_imag) ||
	    put_user(compat_ptr(hor_coefs_even_real),
		     &kp->hor_coefs.even_real) ||
	    put_user(compat_ptr(hor_coefs_even_imag),
		     &kp->hor_coefs.even_imag) ||
	    put_user(compat_ptr(ver_coefs_odd_real),
		     &kp->ver_coefs.odd_real) ||
	    put_user(compat_ptr(ver_coefs_odd_imag),
		     &kp->ver_coefs.odd_imag) ||
	    put_user(compat_ptr(ver_coefs_even_real),
		     &kp->ver_coefs.even_real) ||
	    put_user(compat_ptr(ver_coefs_even_imag),
		     &kp->ver_coefs.even_imag))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_dvs_6axis_config32(काष्ठा atomisp_dvs_6axis_config __user *kp,
					  काष्ठा atomisp_dvs_6axis_config32 __user *up)
अणु
	compat_uptr_t xcoords_y;
	compat_uptr_t ycoords_y;
	compat_uptr_t xcoords_uv;
	compat_uptr_t ycoords_uv;

	अगर (!access_ok(up, माप(काष्ठा atomisp_dvs_6axis_config32)) ||
	    assign_in_user(&kp->exp_id, &up->exp_id) ||
	    assign_in_user(&kp->width_y, &up->width_y) ||
	    assign_in_user(&kp->height_y, &up->height_y) ||
	    assign_in_user(&kp->width_uv, &up->width_uv) ||
	    assign_in_user(&kp->height_uv, &up->height_uv) ||
	    get_user(xcoords_y, &up->xcoords_y) ||
	    get_user(ycoords_y, &up->ycoords_y) ||
	    get_user(xcoords_uv, &up->xcoords_uv) ||
	    get_user(ycoords_uv, &up->ycoords_uv) ||
	    put_user_क्रमce(compat_ptr(xcoords_y), &kp->xcoords_y) ||
	    put_user_क्रमce(compat_ptr(ycoords_y), &kp->ycoords_y) ||
	    put_user_क्रमce(compat_ptr(xcoords_uv), &kp->xcoords_uv) ||
	    put_user_क्रमce(compat_ptr(ycoords_uv), &kp->ycoords_uv))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_3a_statistics32(काष्ठा atomisp_3a_statistics __user *kp,
				       काष्ठा atomisp_3a_statistics32 __user *up)
अणु
	compat_uptr_t data;
	compat_uptr_t rgby_data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_3a_statistics32)) ||
	    copy_in_user(kp, up, माप(काष्ठा atomisp_grid_info)) ||
	    get_user(rgby_data, &up->rgby_data) ||
	    put_user(compat_ptr(rgby_data), &kp->rgby_data) ||
	    get_user(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data) ||
	    assign_in_user(&kp->exp_id, &up->exp_id) ||
	    assign_in_user(&kp->isp_config_id, &up->isp_config_id))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_3a_statistics32(काष्ठा atomisp_3a_statistics __user *kp,
				       काष्ठा atomisp_3a_statistics32 __user *up)
अणु
	व्योम __user *data;
	व्योम __user *rgby_data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_3a_statistics32)) ||
	    copy_in_user(up, kp, माप(काष्ठा atomisp_grid_info)) ||
	    get_user(rgby_data, &kp->rgby_data) ||
	    put_user(ptr_to_compat(rgby_data), &up->rgby_data) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data) ||
	    assign_in_user(&up->exp_id, &kp->exp_id) ||
	    assign_in_user(&up->isp_config_id, &kp->isp_config_id))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_metadata_stat32(काष्ठा atomisp_metadata __user *kp,
				       काष्ठा atomisp_metadata32 __user *up)
अणु
	compat_uptr_t data;
	compat_uptr_t effective_width;

	अगर (!access_ok(up, माप(काष्ठा atomisp_metadata32)) ||
	    get_user(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data) ||
	    assign_in_user(&kp->width, &up->width) ||
	    assign_in_user(&kp->height, &up->height) ||
	    assign_in_user(&kp->stride, &up->stride) ||
	    assign_in_user(&kp->exp_id, &up->exp_id) ||
	    get_user(effective_width, &up->effective_width) ||
	    put_user_क्रमce(compat_ptr(effective_width), &kp->effective_width))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_metadata_stat32(काष्ठा atomisp_metadata __user *kp,
				काष्ठा atomisp_metadata32 __user *up)
अणु
	व्योम __user *data;
	व्योम *effective_width;

	अगर (!access_ok(up, माप(काष्ठा atomisp_metadata32)) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data) ||
	    assign_in_user(&up->width, &kp->width) ||
	    assign_in_user(&up->height, &kp->height) ||
	    assign_in_user(&up->stride, &kp->stride) ||
	    assign_in_user(&up->exp_id, &kp->exp_id) ||
	    get_user(effective_width, &kp->effective_width) ||
	    put_user(ptr_to_compat((व्योम __user *)effective_width),
				   &up->effective_width))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
put_atomisp_metadata_by_type_stat32(काष्ठा atomisp_metadata_with_type __user *kp,
				    काष्ठा atomisp_metadata_with_type32 __user *up)
अणु
	व्योम __user *data;
	u32 *effective_width;

	अगर (!access_ok(up, माप(काष्ठा atomisp_metadata_with_type32)) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data) ||
	    assign_in_user(&up->width, &kp->width) ||
	    assign_in_user(&up->height, &kp->height) ||
	    assign_in_user(&up->stride, &kp->stride) ||
	    assign_in_user(&up->exp_id, &kp->exp_id) ||
	    get_user(effective_width, &kp->effective_width) ||
	    put_user(ptr_to_compat((व्योम __user *)effective_width),
		     &up->effective_width) ||
	    assign_in_user(&up->type, &kp->type))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_metadata_by_type_stat32(काष्ठा atomisp_metadata_with_type __user *kp,
				    काष्ठा atomisp_metadata_with_type32 __user *up)
अणु
	compat_uptr_t data;
	compat_uptr_t effective_width;

	अगर (!access_ok(up, माप(काष्ठा atomisp_metadata_with_type32)) ||
	    get_user(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data) ||
	    assign_in_user(&kp->width, &up->width) ||
	    assign_in_user(&kp->height, &up->height) ||
	    assign_in_user(&kp->stride, &up->stride) ||
	    assign_in_user(&kp->exp_id, &up->exp_id) ||
	    get_user(effective_width, &up->effective_width) ||
	    put_user_क्रमce(compat_ptr(effective_width), &kp->effective_width) ||
	    assign_in_user(&kp->type, &up->type))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_morph_table32(काष्ठा atomisp_morph_table __user *kp,
			  काष्ठा atomisp_morph_table32 __user *up)
अणु
	अचिन्हित पूर्णांक n = ATOMISP_MORPH_TABLE_NUM_PLANES;

	अगर (!access_ok(up, माप(काष्ठा atomisp_morph_table32)) ||
		assign_in_user(&kp->enabled, &up->enabled) ||
		assign_in_user(&kp->width, &up->width) ||
		assign_in_user(&kp->height, &up->height))
			वापस -EFAULT;

	जबतक (n-- > 0) अणु
		compat_uptr_t coord_kp;

		अगर (get_user(coord_kp, &up->coordinates_x[n]) ||
		    put_user(compat_ptr(coord_kp), &kp->coordinates_x[n]) ||
		    get_user(coord_kp, &up->coordinates_y[n]) ||
		    put_user(compat_ptr(coord_kp), &kp->coordinates_y[n]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_morph_table32(काष्ठा atomisp_morph_table __user *kp,
				     काष्ठा atomisp_morph_table32 __user *up)
अणु
	अचिन्हित पूर्णांक n = ATOMISP_MORPH_TABLE_NUM_PLANES;

	अगर (!access_ok(up, माप(काष्ठा atomisp_morph_table32)) ||
		assign_in_user(&up->enabled, &kp->enabled) ||
		assign_in_user(&up->width, &kp->width) ||
		assign_in_user(&up->height, &kp->height))
			वापस -EFAULT;

	जबतक (n-- > 0) अणु
		व्योम __user *coord_kp;

		अगर (get_user(coord_kp, &kp->coordinates_x[n]) ||
		    put_user(ptr_to_compat(coord_kp), &up->coordinates_x[n]) ||
		    get_user(coord_kp, &kp->coordinates_y[n]) ||
		    put_user(ptr_to_compat(coord_kp), &up->coordinates_y[n]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_overlay32(काष्ठा atomisp_overlay __user *kp,
				 काष्ठा atomisp_overlay32 __user *up)
अणु
	compat_uptr_t frame;

	अगर (!access_ok(up, माप(काष्ठा atomisp_overlay32)) ||
	    get_user(frame, &up->frame) ||
	    put_user_क्रमce(compat_ptr(frame), &kp->frame) ||
	    assign_in_user(&kp->bg_y, &up->bg_y) ||
	    assign_in_user(&kp->bg_u, &up->bg_u) ||
	    assign_in_user(&kp->bg_v, &up->bg_v) ||
	    assign_in_user(&kp->blend_input_perc_y,
			   &up->blend_input_perc_y) ||
	    assign_in_user(&kp->blend_input_perc_u,
			   &up->blend_input_perc_u) ||
	    assign_in_user(&kp->blend_input_perc_v,
			   &up->blend_input_perc_v) ||
	    assign_in_user(&kp->blend_overlay_perc_y,
			   &up->blend_overlay_perc_y) ||
	    assign_in_user(&kp->blend_overlay_perc_u,
			   &up->blend_overlay_perc_u) ||
	    assign_in_user(&kp->blend_overlay_perc_v,
			   &up->blend_overlay_perc_v) ||
	    assign_in_user(&kp->overlay_start_x, &up->overlay_start_x) ||
	    assign_in_user(&kp->overlay_start_y, &up->overlay_start_y))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_overlay32(काष्ठा atomisp_overlay __user *kp,
				 काष्ठा atomisp_overlay32 __user *up)
अणु
	व्योम *frame;

	अगर (!access_ok(up, माप(काष्ठा atomisp_overlay32)) ||
	    get_user(frame, &kp->frame) ||
	    put_user(ptr_to_compat((व्योम __user *)frame), &up->frame) ||
	    assign_in_user(&up->bg_y, &kp->bg_y) ||
	    assign_in_user(&up->bg_u, &kp->bg_u) ||
	    assign_in_user(&up->bg_v, &kp->bg_v) ||
	    assign_in_user(&up->blend_input_perc_y,
			   &kp->blend_input_perc_y) ||
	    assign_in_user(&up->blend_input_perc_u,
			   &kp->blend_input_perc_u) ||
	    assign_in_user(&up->blend_input_perc_v,
			   &kp->blend_input_perc_v) ||
	    assign_in_user(&up->blend_overlay_perc_y,
			   &kp->blend_overlay_perc_y) ||
	    assign_in_user(&up->blend_overlay_perc_u,
			   &kp->blend_overlay_perc_u) ||
	    assign_in_user(&up->blend_overlay_perc_v,
			   &kp->blend_overlay_perc_v) ||
	    assign_in_user(&up->overlay_start_x, &kp->overlay_start_x) ||
	    assign_in_user(&up->overlay_start_y, &kp->overlay_start_y))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_calibration_group32(काष्ठा atomisp_calibration_group __user *kp,
				काष्ठा atomisp_calibration_group32 __user *up)
अणु
	compat_uptr_t calb_grp_values;

	अगर (!access_ok(up, माप(काष्ठा atomisp_calibration_group32)) ||
	    assign_in_user(&kp->size, &up->size) ||
	    assign_in_user(&kp->type, &up->type) ||
	    get_user(calb_grp_values, &up->calb_grp_values) ||
	    put_user_क्रमce(compat_ptr(calb_grp_values), &kp->calb_grp_values))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
put_atomisp_calibration_group32(काष्ठा atomisp_calibration_group __user *kp,
				काष्ठा atomisp_calibration_group32 __user *up)
अणु
	व्योम *calb_grp_values;

	अगर (!access_ok(up, माप(काष्ठा atomisp_calibration_group32)) ||
	    assign_in_user(&up->size, &kp->size) ||
	    assign_in_user(&up->type, &kp->type) ||
	    get_user(calb_grp_values, &kp->calb_grp_values) ||
	    put_user(ptr_to_compat((व्योम __user *)calb_grp_values),
		     &up->calb_grp_values))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_acc_fw_load32(काष्ठा atomisp_acc_fw_load __user *kp,
				     काष्ठा atomisp_acc_fw_load32 __user *up)
अणु
	compat_uptr_t data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_load32)) ||
	    assign_in_user(&kp->size, &up->size) ||
	    assign_in_user(&kp->fw_handle, &up->fw_handle) ||
	    get_user_cast(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_acc_fw_load32(काष्ठा atomisp_acc_fw_load __user *kp,
				     काष्ठा atomisp_acc_fw_load32 __user *up)
अणु
	व्योम __user *data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_load32)) ||
	    assign_in_user(&up->size, &kp->size) ||
	    assign_in_user(&up->fw_handle, &kp->fw_handle) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_acc_fw_arg32(काष्ठा atomisp_acc_fw_arg __user *kp,
				    काष्ठा atomisp_acc_fw_arg32 __user *up)
अणु
	compat_uptr_t value;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_arg32)) ||
	    assign_in_user(&kp->fw_handle, &up->fw_handle) ||
	    assign_in_user(&kp->index, &up->index) ||
	    get_user(value, &up->value) ||
	    put_user(compat_ptr(value), &kp->value) ||
	    assign_in_user(&kp->size, &up->size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_acc_fw_arg32(काष्ठा atomisp_acc_fw_arg __user *kp,
				    काष्ठा atomisp_acc_fw_arg32 __user *up)
अणु
	व्योम __user *value;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_arg32)) ||
	    assign_in_user(&up->fw_handle, &kp->fw_handle) ||
	    assign_in_user(&up->index, &kp->index) ||
	    get_user(value, &kp->value) ||
	    put_user(ptr_to_compat(value), &up->value) ||
	    assign_in_user(&up->size, &kp->size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_v4l2_निजी_पूर्णांक_data32(काष्ठा v4l2_निजी_पूर्णांक_data __user *kp,
				       काष्ठा v4l2_निजी_पूर्णांक_data32 __user *up)
अणु
	compat_uptr_t data;

	अगर (!access_ok(up, माप(काष्ठा v4l2_निजी_पूर्णांक_data32)) ||
	    assign_in_user(&kp->size, &up->size) ||
	    get_user(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data) ||
	    assign_in_user(&kp->reserved[0], &up->reserved[0]) ||
	    assign_in_user(&kp->reserved[1], &up->reserved[1]))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_v4l2_निजी_पूर्णांक_data32(काष्ठा v4l2_निजी_पूर्णांक_data __user *kp,
				       काष्ठा v4l2_निजी_पूर्णांक_data32 __user *up)
अणु
	व्योम __user *data;

	अगर (!access_ok(up, माप(काष्ठा v4l2_निजी_पूर्णांक_data32)) ||
	    assign_in_user(&up->size, &kp->size) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data) ||
	    assign_in_user(&up->reserved[0], &kp->reserved[0]) ||
	    assign_in_user(&up->reserved[1], &kp->reserved[1]))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_shading_table32(काष्ठा atomisp_shading_table __user *kp,
				       काष्ठा atomisp_shading_table32 __user *up)
अणु
	अचिन्हित पूर्णांक n = ATOMISP_NUM_SC_COLORS;

	अगर (!access_ok(up, माप(काष्ठा atomisp_shading_table32)) ||
	    assign_in_user(&kp->enable, &up->enable) ||
	    assign_in_user(&kp->sensor_width, &up->sensor_width) ||
	    assign_in_user(&kp->sensor_height, &up->sensor_height) ||
	    assign_in_user(&kp->width, &up->width) ||
	    assign_in_user(&kp->height, &up->height) ||
	    assign_in_user(&kp->fraction_bits, &up->fraction_bits))
		वापस -EFAULT;

	जबतक (n-- > 0) अणु
		compat_uptr_t पंचांगp;

		अगर (get_user(पंचांगp, &up->data[n]) ||
		    put_user_क्रमce(compat_ptr(पंचांगp), &kp->data[n]))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_acc_map32(काष्ठा atomisp_acc_map __user *kp,
				 काष्ठा atomisp_acc_map32 __user *up)
अणु
	compat_uptr_t user_ptr;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_map32)) ||
	    assign_in_user(&kp->flags, &up->flags) ||
	    assign_in_user(&kp->length, &up->length) ||
	    get_user(user_ptr, &up->user_ptr) ||
	    put_user(compat_ptr(user_ptr), &kp->user_ptr) ||
	    assign_in_user(&kp->css_ptr, &up->css_ptr) ||
	    assign_in_user(&kp->reserved[0], &up->reserved[0]) ||
	    assign_in_user(&kp->reserved[1], &up->reserved[1]) ||
	    assign_in_user(&kp->reserved[2], &up->reserved[2]) ||
	    assign_in_user(&kp->reserved[3], &up->reserved[3]))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक put_atomisp_acc_map32(काष्ठा atomisp_acc_map __user *kp,
				 काष्ठा atomisp_acc_map32 __user *up)
अणु
	व्योम __user *user_ptr;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_map32)) ||
	    assign_in_user(&up->flags, &kp->flags) ||
	    assign_in_user(&up->length, &kp->length) ||
	    get_user(user_ptr, &kp->user_ptr) ||
	    put_user(ptr_to_compat(user_ptr), &up->user_ptr) ||
	    assign_in_user(&up->css_ptr, &kp->css_ptr) ||
	    assign_in_user(&up->reserved[0], &kp->reserved[0]) ||
	    assign_in_user(&up->reserved[1], &kp->reserved[1]) ||
	    assign_in_user(&up->reserved[2], &kp->reserved[2]) ||
	    assign_in_user(&up->reserved[3], &kp->reserved[3]))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_acc_s_mapped_arg32(काष्ठा atomisp_acc_s_mapped_arg __user *kp,
			       काष्ठा atomisp_acc_s_mapped_arg32 __user *up)
अणु
	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_s_mapped_arg32)) ||
	    assign_in_user(&kp->fw_handle, &up->fw_handle) ||
	    assign_in_user(&kp->memory, &up->memory) ||
	    assign_in_user(&kp->length, &up->length) ||
	    assign_in_user(&kp->css_ptr, &up->css_ptr))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
put_atomisp_acc_s_mapped_arg32(काष्ठा atomisp_acc_s_mapped_arg __user *kp,
			       काष्ठा atomisp_acc_s_mapped_arg32 __user *up)
अणु
	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_s_mapped_arg32)) ||
	    assign_in_user(&up->fw_handle, &kp->fw_handle) ||
	    assign_in_user(&up->memory, &kp->memory) ||
	    assign_in_user(&up->length, &kp->length) ||
	    assign_in_user(&up->css_ptr, &kp->css_ptr))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक get_atomisp_parameters32(काष्ठा atomisp_parameters __user *kp,
				    काष्ठा atomisp_parameters32 __user *up)
अणु
	पूर्णांक n = दुरत्व(काष्ठा atomisp_parameters32, output_frame) /
		माप(compat_uptr_t);
	compat_uptr_t stp, mtp, dcp, dscp;
	काष्ठा अणु
		काष्ठा atomisp_shading_table shading_table;
		काष्ठा atomisp_morph_table morph_table;
		काष्ठा atomisp_dis_coefficients dvs2_coefs;
		काष्ठा atomisp_dvs_6axis_config dvs_6axis_config;
	पूर्ण __user *karg = (व्योम __user *)(kp + 1);

	अगर (!access_ok(up, माप(काष्ठा atomisp_parameters32)))
		वापस -EFAULT;

	जबतक (n >= 0) अणु
		compat_uptr_t __user *src = (compat_uptr_t __user *)up + n;
		व्योम * __user *dst = (व्योम * __user *)kp + n;
		compat_uptr_t पंचांगp;

		अगर (get_user_cast(पंचांगp, src) || put_user_क्रमce(compat_ptr(पंचांगp), dst))
			वापस -EFAULT;
		n--;
	पूर्ण

	अगर (assign_in_user(&kp->isp_config_id, &up->isp_config_id) ||
	    assign_in_user(&kp->per_frame_setting, &up->per_frame_setting) ||
	    get_user(stp, &up->shading_table) ||
	    get_user(mtp, &up->morph_table) ||
	    get_user(dcp, &up->dvs2_coefs) ||
	    get_user(dscp, &up->dvs_6axis_config))
		वापस -EFAULT;

	/* handle shading table */
	अगर (stp && (get_atomisp_shading_table32(&karg->shading_table,
						compat_ptr(stp)) ||
		    put_user_क्रमce(&karg->shading_table, &kp->shading_table)))
		वापस -EFAULT;

	/* handle morph table */
	अगर (mtp && (get_atomisp_morph_table32(&karg->morph_table,
					      compat_ptr(mtp)) ||
		    put_user_क्रमce(&karg->morph_table, &kp->morph_table)))
		वापस -EFAULT;

	/* handle dvs2 coefficients */
	अगर (dcp && (get_atomisp_dis_coefficients32(&karg->dvs2_coefs,
						   compat_ptr(dcp)) ||
		    put_user_क्रमce(&karg->dvs2_coefs, &kp->dvs2_coefs)))
		वापस -EFAULT;

	/* handle dvs 6axis configuration */
	अगर (dscp &&
	    (get_atomisp_dvs_6axis_config32(&karg->dvs_6axis_config,
					    compat_ptr(dscp)) ||
	     put_user_क्रमce(&karg->dvs_6axis_config, &kp->dvs_6axis_config)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_acc_fw_load_to_pipe32(काष्ठा atomisp_acc_fw_load_to_pipe __user *kp,
				  काष्ठा atomisp_acc_fw_load_to_pipe32 __user *up)
अणु
	compat_uptr_t data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_load_to_pipe32)) ||
	    assign_in_user(&kp->flags, &up->flags) ||
	    assign_in_user(&kp->fw_handle, &up->fw_handle) ||
	    assign_in_user(&kp->size, &up->size) ||
	    assign_in_user(&kp->type, &up->type) ||
	    assign_in_user(&kp->reserved[0], &up->reserved[0]) ||
	    assign_in_user(&kp->reserved[1], &up->reserved[1]) ||
	    assign_in_user(&kp->reserved[2], &up->reserved[2]) ||
	    get_user(data, &up->data) ||
	    put_user(compat_ptr(data), &kp->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
put_atomisp_acc_fw_load_to_pipe32(काष्ठा atomisp_acc_fw_load_to_pipe __user *kp,
				  काष्ठा atomisp_acc_fw_load_to_pipe32 __user *up)
अणु
	व्योम __user *data;

	अगर (!access_ok(up, माप(काष्ठा atomisp_acc_fw_load_to_pipe32)) ||
	    assign_in_user(&up->flags, &kp->flags) ||
	    assign_in_user(&up->fw_handle, &kp->fw_handle) ||
	    assign_in_user(&up->size, &kp->size) ||
	    assign_in_user(&up->type, &kp->type) ||
	    assign_in_user(&up->reserved[0], &kp->reserved[0]) ||
	    assign_in_user(&up->reserved[1], &kp->reserved[1]) ||
	    assign_in_user(&up->reserved[2], &kp->reserved[2]) ||
	    get_user(data, &kp->data) ||
	    put_user(ptr_to_compat(data), &up->data))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक
get_atomisp_sensor_ae_bracketing_lut(काष्ठा atomisp_sensor_ae_bracketing_lut __user *kp,
				     काष्ठा atomisp_sensor_ae_bracketing_lut32 __user *up)
अणु
	compat_uptr_t lut;

	अगर (!access_ok(up, माप(काष्ठा atomisp_sensor_ae_bracketing_lut32)) ||
	    assign_in_user(&kp->lut_size, &up->lut_size) ||
	    get_user(lut, &up->lut) ||
	    put_user_क्रमce(compat_ptr(lut), &kp->lut))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ native_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret = -ENOIOCTLCMD;

	अगर (file->f_op->unlocked_ioctl)
		ret = file->f_op->unlocked_ioctl(file, cmd, arg);

	वापस ret;
पूर्ण

अटल दीर्घ atomisp_करो_compat_ioctl(काष्ठा file *file,
				    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	जोड़ अणु
		काष्ठा atomisp_histogram his;
		काष्ठा atomisp_dis_statistics dis_s;
		काष्ठा atomisp_dis_coefficients dis_c;
		काष्ठा atomisp_dvs_6axis_config dvs_c;
		काष्ठा atomisp_3a_statistics s3a_s;
		काष्ठा atomisp_morph_table mor_t;
		काष्ठा v4l2_framebuffer v4l2_buf;
		काष्ठा atomisp_overlay overlay;
		काष्ठा atomisp_calibration_group cal_grp;
		काष्ठा atomisp_acc_fw_load acc_fw_load;
		काष्ठा atomisp_acc_fw_arg acc_fw_arg;
		काष्ठा v4l2_निजी_पूर्णांक_data v4l2_pri_data;
		काष्ठा atomisp_shading_table shd_tbl;
		काष्ठा atomisp_acc_map acc_map;
		काष्ठा atomisp_acc_s_mapped_arg acc_map_arg;
		काष्ठा atomisp_parameters param;
		काष्ठा atomisp_acc_fw_load_to_pipe acc_fw_to_pipe;
		काष्ठा atomisp_metadata md;
		काष्ठा atomisp_metadata_with_type md_with_type;
		काष्ठा atomisp_sensor_ae_bracketing_lut lut;
	पूर्ण __user *karg;
	व्योम __user *up = compat_ptr(arg);
	दीर्घ err = -ENOIOCTLCMD;

	karg = compat_alloc_user_space(
		माप(*karg) + (cmd == ATOMISP_IOC_S_PARAMETERS32 ?
				 माप(काष्ठा atomisp_shading_table) +
				 माप(काष्ठा atomisp_morph_table) +
				 माप(काष्ठा atomisp_dis_coefficients) +
				 माप(काष्ठा atomisp_dvs_6axis_config) : 0));
	अगर (!karg)
		वापस -ENOMEM;

	/* First, convert the command. */
	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_HISTOGRAM32:
		cmd = ATOMISP_IOC_G_HISTOGRAM;
		अवरोध;
	हाल ATOMISP_IOC_S_HISTOGRAM32:
		cmd = ATOMISP_IOC_S_HISTOGRAM;
		अवरोध;
	हाल ATOMISP_IOC_G_DIS_STAT32:
		cmd = ATOMISP_IOC_G_DIS_STAT;
		अवरोध;
	हाल ATOMISP_IOC_S_DIS_COEFS32:
		cmd = ATOMISP_IOC_S_DIS_COEFS;
		अवरोध;
	हाल ATOMISP_IOC_S_DIS_VECTOR32:
		cmd = ATOMISP_IOC_S_DIS_VECTOR;
		अवरोध;
	हाल ATOMISP_IOC_G_3A_STAT32:
		cmd = ATOMISP_IOC_G_3A_STAT;
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_GDC_TAB32:
		cmd = ATOMISP_IOC_G_ISP_GDC_TAB;
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_GDC_TAB32:
		cmd = ATOMISP_IOC_S_ISP_GDC_TAB;
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_FPN_TABLE32:
		cmd = ATOMISP_IOC_S_ISP_FPN_TABLE;
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_OVERLAY32:
		cmd = ATOMISP_IOC_G_ISP_OVERLAY;
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_OVERLAY32:
		cmd = ATOMISP_IOC_S_ISP_OVERLAY;
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP32:
		cmd = ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP;
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD32:
		cmd = ATOMISP_IOC_ACC_LOAD;
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_ARG32:
		cmd = ATOMISP_IOC_ACC_S_ARG;
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA32:
		cmd = ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA;
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_SHD_TAB32:
		cmd = ATOMISP_IOC_S_ISP_SHD_TAB;
		अवरोध;
	हाल ATOMISP_IOC_ACC_DESTAB32:
		cmd = ATOMISP_IOC_ACC_DESTAB;
		अवरोध;
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA32:
		cmd = ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA;
		अवरोध;
	हाल ATOMISP_IOC_ACC_MAP32:
		cmd = ATOMISP_IOC_ACC_MAP;
		अवरोध;
	हाल ATOMISP_IOC_ACC_UNMAP32:
		cmd = ATOMISP_IOC_ACC_UNMAP;
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_MAPPED_ARG32:
		cmd = ATOMISP_IOC_ACC_S_MAPPED_ARG;
		अवरोध;
	हाल ATOMISP_IOC_S_PARAMETERS32:
		cmd = ATOMISP_IOC_S_PARAMETERS;
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD_TO_PIPE32:
		cmd = ATOMISP_IOC_ACC_LOAD_TO_PIPE;
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA32:
		cmd = ATOMISP_IOC_G_METADATA;
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA_BY_TYPE32:
		cmd = ATOMISP_IOC_G_METADATA_BY_TYPE;
		अवरोध;
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT32:
		cmd = ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT;
		अवरोध;
	पूर्ण

	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_HISTOGRAM:
	हाल ATOMISP_IOC_S_HISTOGRAM:
		err = get_atomisp_histogram32(&karg->his, up);
		अवरोध;
	हाल ATOMISP_IOC_G_DIS_STAT:
		err = get_atomisp_dis_statistics32(&karg->dis_s, up);
		अवरोध;
	हाल ATOMISP_IOC_S_DIS_COEFS:
		err = get_atomisp_dis_coefficients32(&karg->dis_c, up);
		अवरोध;
	हाल ATOMISP_IOC_S_DIS_VECTOR:
		err = get_atomisp_dvs_6axis_config32(&karg->dvs_c, up);
		अवरोध;
	हाल ATOMISP_IOC_G_3A_STAT:
		err = get_atomisp_3a_statistics32(&karg->s3a_s, up);
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_GDC_TAB:
	हाल ATOMISP_IOC_S_ISP_GDC_TAB:
		err = get_atomisp_morph_table32(&karg->mor_t, up);
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_FPN_TABLE:
		err = get_v4l2_framebuffer32(&karg->v4l2_buf, up);
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_OVERLAY:
	हाल ATOMISP_IOC_S_ISP_OVERLAY:
		err = get_atomisp_overlay32(&karg->overlay, up);
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP:
		err = get_atomisp_calibration_group32(&karg->cal_grp, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD:
		err = get_atomisp_acc_fw_load32(&karg->acc_fw_load, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_ARG:
	हाल ATOMISP_IOC_ACC_DESTAB:
		err = get_atomisp_acc_fw_arg32(&karg->acc_fw_arg, up);
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA:
		err = get_v4l2_निजी_पूर्णांक_data32(&karg->v4l2_pri_data, up);
		अवरोध;
	हाल ATOMISP_IOC_S_ISP_SHD_TAB:
		err = get_atomisp_shading_table32(&karg->shd_tbl, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_MAP:
	हाल ATOMISP_IOC_ACC_UNMAP:
		err = get_atomisp_acc_map32(&karg->acc_map, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_MAPPED_ARG:
		err = get_atomisp_acc_s_mapped_arg32(&karg->acc_map_arg, up);
		अवरोध;
	हाल ATOMISP_IOC_S_PARAMETERS:
		err = get_atomisp_parameters32(&karg->param, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD_TO_PIPE:
		err = get_atomisp_acc_fw_load_to_pipe32(&karg->acc_fw_to_pipe,
							up);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA:
		err = get_atomisp_metadata_stat32(&karg->md, up);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA_BY_TYPE:
		err = get_atomisp_metadata_by_type_stat32(&karg->md_with_type,
							  up);
		अवरोध;
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT:
		err = get_atomisp_sensor_ae_bracketing_lut(&karg->lut, up);
		अवरोध;
	पूर्ण
	अगर (err)
		वापस err;

	err = native_ioctl(file, cmd, (अचिन्हित दीर्घ)karg);
	अगर (err)
		वापस err;

	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_HISTOGRAM:
		err = put_atomisp_histogram32(&karg->his, up);
		अवरोध;
	हाल ATOMISP_IOC_G_DIS_STAT:
		err = put_atomisp_dis_statistics32(&karg->dis_s, up);
		अवरोध;
	हाल ATOMISP_IOC_G_3A_STAT:
		err = put_atomisp_3a_statistics32(&karg->s3a_s, up);
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_GDC_TAB:
		err = put_atomisp_morph_table32(&karg->mor_t, up);
		अवरोध;
	हाल ATOMISP_IOC_G_ISP_OVERLAY:
		err = put_atomisp_overlay32(&karg->overlay, up);
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP:
		err = put_atomisp_calibration_group32(&karg->cal_grp, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD:
		err = put_atomisp_acc_fw_load32(&karg->acc_fw_load, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_ARG:
	हाल ATOMISP_IOC_ACC_DESTAB:
		err = put_atomisp_acc_fw_arg32(&karg->acc_fw_arg, up);
		अवरोध;
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA:
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA:
		err = put_v4l2_निजी_पूर्णांक_data32(&karg->v4l2_pri_data, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_MAP:
	हाल ATOMISP_IOC_ACC_UNMAP:
		err = put_atomisp_acc_map32(&karg->acc_map, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_S_MAPPED_ARG:
		err = put_atomisp_acc_s_mapped_arg32(&karg->acc_map_arg, up);
		अवरोध;
	हाल ATOMISP_IOC_ACC_LOAD_TO_PIPE:
		err = put_atomisp_acc_fw_load_to_pipe32(&karg->acc_fw_to_pipe,
							up);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA:
		err = put_atomisp_metadata_stat32(&karg->md, up);
		अवरोध;
	हाल ATOMISP_IOC_G_METADATA_BY_TYPE:
		err = put_atomisp_metadata_by_type_stat32(&karg->md_with_type,
							  up);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

दीर्घ atomisp_compat_ioctl32(काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा atomisp_device *isp = video_get_drvdata(vdev);
	दीर्घ ret = -ENOIOCTLCMD;

	अगर (!file->f_op->unlocked_ioctl)
		वापस ret;

	चयन (cmd) अणु
	हाल ATOMISP_IOC_G_XNR:
	हाल ATOMISP_IOC_S_XNR:
	हाल ATOMISP_IOC_G_NR:
	हाल ATOMISP_IOC_S_NR:
	हाल ATOMISP_IOC_G_TNR:
	हाल ATOMISP_IOC_S_TNR:
	हाल ATOMISP_IOC_G_BLACK_LEVEL_COMP:
	हाल ATOMISP_IOC_S_BLACK_LEVEL_COMP:
	हाल ATOMISP_IOC_G_EE:
	हाल ATOMISP_IOC_S_EE:
	हाल ATOMISP_IOC_S_DIS_VECTOR:
	हाल ATOMISP_IOC_G_ISP_PARM:
	हाल ATOMISP_IOC_S_ISP_PARM:
	हाल ATOMISP_IOC_G_ISP_GAMMA:
	हाल ATOMISP_IOC_S_ISP_GAMMA:
	हाल ATOMISP_IOC_ISP_MAKERNOTE:
	हाल ATOMISP_IOC_G_ISP_MACC:
	हाल ATOMISP_IOC_S_ISP_MACC:
	हाल ATOMISP_IOC_G_ISP_BAD_PIXEL_DETECTION:
	हाल ATOMISP_IOC_S_ISP_BAD_PIXEL_DETECTION:
	हाल ATOMISP_IOC_G_ISP_FALSE_COLOR_CORRECTION:
	हाल ATOMISP_IOC_S_ISP_FALSE_COLOR_CORRECTION:
	हाल ATOMISP_IOC_G_ISP_CTC:
	हाल ATOMISP_IOC_S_ISP_CTC:
	हाल ATOMISP_IOC_G_ISP_WHITE_BALANCE:
	हाल ATOMISP_IOC_S_ISP_WHITE_BALANCE:
	हाल ATOMISP_IOC_CAMERA_BRIDGE:
	हाल ATOMISP_IOC_G_SENSOR_MODE_DATA:
	हाल ATOMISP_IOC_S_EXPOSURE:
	हाल ATOMISP_IOC_G_3A_CONFIG:
	हाल ATOMISP_IOC_S_3A_CONFIG:
	हाल ATOMISP_IOC_ACC_UNLOAD:
	हाल ATOMISP_IOC_ACC_START:
	हाल ATOMISP_IOC_ACC_WAIT:
	हाल ATOMISP_IOC_ACC_ABORT:
	हाल ATOMISP_IOC_G_ISP_GAMMA_CORRECTION:
	हाल ATOMISP_IOC_S_ISP_GAMMA_CORRECTION:
	हाल ATOMISP_IOC_S_CONT_CAPTURE_CONFIG:
	हाल ATOMISP_IOC_G_DVS2_BQ_RESOLUTIONS:
	हाल ATOMISP_IOC_EXT_ISP_CTRL:
	हाल ATOMISP_IOC_EXP_ID_UNLOCK:
	हाल ATOMISP_IOC_EXP_ID_CAPTURE:
	हाल ATOMISP_IOC_S_ENABLE_DZ_CAPT_PIPE:
	हाल ATOMISP_IOC_G_FORMATS_CONFIG:
	हाल ATOMISP_IOC_S_FORMATS_CONFIG:
	हाल ATOMISP_IOC_S_EXPOSURE_WINDOW:
	हाल ATOMISP_IOC_S_ACC_STATE:
	हाल ATOMISP_IOC_G_ACC_STATE:
	हाल ATOMISP_IOC_INJECT_A_FAKE_EVENT:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_INFO:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_G_SENSOR_AE_BRACKETING_MODE:
	हाल ATOMISP_IOC_G_INVALID_FRAME_NUM:
	हाल ATOMISP_IOC_S_ARRAY_RESOLUTION:
	हाल ATOMISP_IOC_S_SENSOR_RUNMODE:
	हाल ATOMISP_IOC_G_UPDATE_EXPOSURE:
		ret = native_ioctl(file, cmd, arg);
		अवरोध;

	हाल ATOMISP_IOC_G_HISTOGRAM32:
	हाल ATOMISP_IOC_S_HISTOGRAM32:
	हाल ATOMISP_IOC_G_DIS_STAT32:
	हाल ATOMISP_IOC_S_DIS_COEFS32:
	हाल ATOMISP_IOC_S_DIS_VECTOR32:
	हाल ATOMISP_IOC_G_3A_STAT32:
	हाल ATOMISP_IOC_G_ISP_GDC_TAB32:
	हाल ATOMISP_IOC_S_ISP_GDC_TAB32:
	हाल ATOMISP_IOC_S_ISP_FPN_TABLE32:
	हाल ATOMISP_IOC_G_ISP_OVERLAY32:
	हाल ATOMISP_IOC_S_ISP_OVERLAY32:
	हाल ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP32:
	हाल ATOMISP_IOC_ACC_LOAD32:
	हाल ATOMISP_IOC_ACC_S_ARG32:
	हाल ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA32:
	हाल ATOMISP_IOC_S_ISP_SHD_TAB32:
	हाल ATOMISP_IOC_ACC_DESTAB32:
	हाल ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA32:
	हाल ATOMISP_IOC_ACC_MAP32:
	हाल ATOMISP_IOC_ACC_UNMAP32:
	हाल ATOMISP_IOC_ACC_S_MAPPED_ARG32:
	हाल ATOMISP_IOC_S_PARAMETERS32:
	हाल ATOMISP_IOC_ACC_LOAD_TO_PIPE32:
	हाल ATOMISP_IOC_G_METADATA32:
	हाल ATOMISP_IOC_G_METADATA_BY_TYPE32:
	हाल ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT32:
		ret = atomisp_करो_compat_ioctl(file, cmd, arg);
		अवरोध;

	शेष:
		dev_warn(isp->dev,
			 "%s: unknown ioctl '%c', dir=%d, #%d (0x%08x)\n",
			 __func__, _IOC_TYPE(cmd), _IOC_सूची(cmd), _IOC_NR(cmd),
			 cmd);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */
