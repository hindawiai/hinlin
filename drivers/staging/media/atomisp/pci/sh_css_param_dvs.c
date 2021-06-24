<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "sh_css_param_dvs.h"
#समावेश <निश्चित_support.h>
#समावेश <type_support.h>
#समावेश <ia_css_err.h>
#समावेश <ia_css_types.h>
#समावेश "ia_css_debug.h"

अटल काष्ठा ia_css_dvs_6axis_config *
alloc_dvs_6axis_table(स्थिर काष्ठा ia_css_resolution *frame_res,
		      काष्ठा ia_css_dvs_6axis_config  *dvs_config_src)
अणु
	अचिन्हित पूर्णांक width_y = 0;
	अचिन्हित पूर्णांक height_y = 0;
	अचिन्हित पूर्णांक width_uv = 0;
	अचिन्हित पूर्णांक height_uv = 0;
	पूर्णांक err = 0;
	काष्ठा ia_css_dvs_6axis_config  *dvs_config = शून्य;

	dvs_config = kvदो_स्मृति(माप(काष्ठा ia_css_dvs_6axis_config),
			      GFP_KERNEL);
	अगर (!dvs_config)	अणु
		IA_CSS_ERROR("out of memory");
		err = -ENOMEM;
	पूर्ण अन्यथा अणु
		/*Initialize new काष्ठा with latest config settings*/
		अगर (dvs_config_src) अणु
			dvs_config->width_y = width_y = dvs_config_src->width_y;
			dvs_config->height_y = height_y = dvs_config_src->height_y;
			dvs_config->width_uv = width_uv = dvs_config_src->width_uv;
			dvs_config->height_uv = height_uv = dvs_config_src->height_uv;
			IA_CSS_LOG("alloc_dvs_6axis_table Y: W %d H %d", width_y, height_y);
		पूर्ण अन्यथा अगर (frame_res) अणु
			dvs_config->width_y = width_y = DVS_TABLE_IN_BLOCKDIM_X_LUMA(frame_res->width);
			dvs_config->height_y = height_y = DVS_TABLE_IN_BLOCKDIM_Y_LUMA(
							      frame_res->height);
			dvs_config->width_uv = width_uv = DVS_TABLE_IN_BLOCKDIM_X_CHROMA(
							      frame_res->width /
							      2); /* UV = Y/2, depens on colour क्रमmat YUV 4.2.0*/
			dvs_config->height_uv = height_uv = DVS_TABLE_IN_BLOCKDIM_Y_CHROMA(
								frame_res->height /
								2);/* UV = Y/2, depens on colour क्रमmat YUV 4.2.0*/
			IA_CSS_LOG("alloc_dvs_6axis_table Y: W %d H %d", width_y, height_y);
		पूर्ण

		/* Generate Y buffers  */
		dvs_config->xcoords_y = kvदो_स्मृति(width_y * height_y * माप(uपूर्णांक32_t),
						 GFP_KERNEL);
		अगर (!dvs_config->xcoords_y) अणु
			IA_CSS_ERROR("out of memory");
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण

		dvs_config->ycoords_y = kvदो_स्मृति(width_y * height_y * माप(uपूर्णांक32_t),
						 GFP_KERNEL);
		अगर (!dvs_config->ycoords_y) अणु
			IA_CSS_ERROR("out of memory");
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण

		/* Generate UV buffers  */
		IA_CSS_LOG("UV W %d H %d", width_uv, height_uv);

		dvs_config->xcoords_uv = kvदो_स्मृति(width_uv * height_uv * माप(uपूर्णांक32_t),
						  GFP_KERNEL);
		अगर (!dvs_config->xcoords_uv) अणु
			IA_CSS_ERROR("out of memory");
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण

		dvs_config->ycoords_uv = kvदो_स्मृति(width_uv * height_uv * माप(uपूर्णांक32_t),
						  GFP_KERNEL);
		अगर (!dvs_config->ycoords_uv) अणु
			IA_CSS_ERROR("out of memory");
			err = -ENOMEM;
		पूर्ण
निकास:
		अगर (err) अणु
			मुक्त_dvs_6axis_table(
			    &dvs_config); /* we might have allocated some memory, release this */
			dvs_config = शून्य;
		पूर्ण
	पूर्ण

	IA_CSS_LEAVE("dvs_config=%p", dvs_config);
	वापस dvs_config;
पूर्ण

अटल व्योम
init_dvs_6axis_table_from_शेष(काष्ठा ia_css_dvs_6axis_config *dvs_config,
				  स्थिर काष्ठा ia_css_resolution *dvs_offset)
अणु
	अचिन्हित पूर्णांक x, y;
	अचिन्हित पूर्णांक width_y = dvs_config->width_y;
	अचिन्हित पूर्णांक height_y = dvs_config->height_y;
	अचिन्हित पूर्णांक width_uv = dvs_config->width_uv;
	अचिन्हित पूर्णांक height_uv = dvs_config->height_uv;

	IA_CSS_LOG("Env_X=%d, Env_Y=%d, width_y=%d, height_y=%d",
		   dvs_offset->width, dvs_offset->height, width_y, height_y);
	क्रम (y = 0; y < height_y; y++) अणु
		क्रम (x = 0; x < width_y; x++) अणु
			dvs_config->xcoords_y[y * width_y + x] =  (dvs_offset->width + x *
				DVS_BLOCKDIM_X) << DVS_COORD_FRAC_BITS;
		पूर्ण
	पूर्ण

	क्रम (y = 0; y < height_y; y++) अणु
		क्रम (x = 0; x < width_y; x++) अणु
			dvs_config->ycoords_y[y * width_y + x] =  (dvs_offset->height + y *
				DVS_BLOCKDIM_Y_LUMA) << DVS_COORD_FRAC_BITS;
		पूर्ण
	पूर्ण

	क्रम (y = 0; y < height_uv; y++) अणु
		क्रम (x = 0; x < width_uv;
		     x++) अणु /* Envelope dimensions set in Ypixels hence offset UV = offset Y/2 */
			dvs_config->xcoords_uv[y * width_uv + x] =  ((dvs_offset->width / 2) + x *
				DVS_BLOCKDIM_X) << DVS_COORD_FRAC_BITS;
		पूर्ण
	पूर्ण

	क्रम (y = 0; y < height_uv; y++) अणु
		क्रम (x = 0; x < width_uv;
		     x++) अणु /* Envelope dimensions set in Ypixels hence offset UV = offset Y/2 */
			dvs_config->ycoords_uv[y * width_uv + x] =  ((dvs_offset->height / 2) + y *
				DVS_BLOCKDIM_Y_CHROMA) <<
				DVS_COORD_FRAC_BITS;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
init_dvs_6axis_table_from_config(काष्ठा ia_css_dvs_6axis_config *dvs_config,
				 काष्ठा ia_css_dvs_6axis_config  *dvs_config_src)
अणु
	अचिन्हित पूर्णांक width_y = dvs_config->width_y;
	अचिन्हित पूर्णांक height_y = dvs_config->height_y;
	अचिन्हित पूर्णांक width_uv = dvs_config->width_uv;
	अचिन्हित पूर्णांक height_uv = dvs_config->height_uv;

	स_नकल(dvs_config->xcoords_y, dvs_config_src->xcoords_y,
	       (width_y * height_y * माप(uपूर्णांक32_t)));
	स_नकल(dvs_config->ycoords_y, dvs_config_src->ycoords_y,
	       (width_y * height_y * माप(uपूर्णांक32_t)));
	स_नकल(dvs_config->xcoords_uv, dvs_config_src->xcoords_uv,
	       (width_uv * height_uv * माप(uपूर्णांक32_t)));
	स_नकल(dvs_config->ycoords_uv, dvs_config_src->ycoords_uv,
	       (width_uv * height_uv * माप(uपूर्णांक32_t)));
पूर्ण

काष्ठा ia_css_dvs_6axis_config *
generate_dvs_6axis_table(स्थिर काष्ठा ia_css_resolution *frame_res,
			 स्थिर काष्ठा ia_css_resolution *dvs_offset)
अणु
	काष्ठा ia_css_dvs_6axis_config *dvs_6axis_table;

	निश्चित(frame_res);
	निश्चित(dvs_offset);

	dvs_6axis_table = alloc_dvs_6axis_table(frame_res, शून्य);
	अगर (dvs_6axis_table) अणु
		init_dvs_6axis_table_from_शेष(dvs_6axis_table, dvs_offset);
		वापस dvs_6axis_table;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा ia_css_dvs_6axis_config *
generate_dvs_6axis_table_from_config(काष्ठा ia_css_dvs_6axis_config
				     *dvs_config_src)
अणु
	काष्ठा ia_css_dvs_6axis_config *dvs_6axis_table;

	निश्चित(dvs_config_src);

	dvs_6axis_table = alloc_dvs_6axis_table(शून्य, dvs_config_src);
	अगर (dvs_6axis_table) अणु
		init_dvs_6axis_table_from_config(dvs_6axis_table, dvs_config_src);
		वापस dvs_6axis_table;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम
मुक्त_dvs_6axis_table(काष्ठा ia_css_dvs_6axis_config  **dvs_6axis_config)
अणु
	निश्चित(dvs_6axis_config);
	निश्चित(*dvs_6axis_config);

	अगर ((dvs_6axis_config) && (*dvs_6axis_config)) अणु
		IA_CSS_ENTER_PRIVATE("dvs_6axis_config %p", (*dvs_6axis_config));
		अगर ((*dvs_6axis_config)->xcoords_y) अणु
			kvमुक्त((*dvs_6axis_config)->xcoords_y);
			(*dvs_6axis_config)->xcoords_y = शून्य;
		पूर्ण

		अगर ((*dvs_6axis_config)->ycoords_y) अणु
			kvमुक्त((*dvs_6axis_config)->ycoords_y);
			(*dvs_6axis_config)->ycoords_y = शून्य;
		पूर्ण

		/* Free up UV buffers */
		अगर ((*dvs_6axis_config)->xcoords_uv) अणु
			kvमुक्त((*dvs_6axis_config)->xcoords_uv);
			(*dvs_6axis_config)->xcoords_uv = शून्य;
		पूर्ण

		अगर ((*dvs_6axis_config)->ycoords_uv) अणु
			kvमुक्त((*dvs_6axis_config)->ycoords_uv);
			(*dvs_6axis_config)->ycoords_uv = शून्य;
		पूर्ण

		IA_CSS_LEAVE_PRIVATE("dvs_6axis_config %p", (*dvs_6axis_config));
		kvमुक्त(*dvs_6axis_config);
		*dvs_6axis_config = शून्य;
	पूर्ण
पूर्ण

व्योम copy_dvs_6axis_table(काष्ठा ia_css_dvs_6axis_config *dvs_config_dst,
			  स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_config_src)
अणु
	अचिन्हित पूर्णांक width_y;
	अचिन्हित पूर्णांक height_y;
	अचिन्हित पूर्णांक width_uv;
	अचिन्हित पूर्णांक height_uv;

	निश्चित(dvs_config_src);
	निश्चित(dvs_config_dst);
	निश्चित(dvs_config_src->xcoords_y);
	निश्चित(dvs_config_src->xcoords_uv);
	निश्चित(dvs_config_src->ycoords_y);
	निश्चित(dvs_config_src->ycoords_uv);
	निश्चित(dvs_config_src->width_y == dvs_config_dst->width_y);
	निश्चित(dvs_config_src->width_uv == dvs_config_dst->width_uv);
	निश्चित(dvs_config_src->height_y == dvs_config_dst->height_y);
	निश्चित(dvs_config_src->height_uv == dvs_config_dst->height_uv);

	width_y = dvs_config_src->width_y;
	height_y = dvs_config_src->height_y;
	width_uv =
	    dvs_config_src->width_uv; /* = Y/2, depens on colour क्रमmat YUV 4.2.0*/
	height_uv = dvs_config_src->height_uv;

	स_नकल(dvs_config_dst->xcoords_y, dvs_config_src->xcoords_y,
	       (width_y * height_y * माप(uपूर्णांक32_t)));
	स_नकल(dvs_config_dst->ycoords_y, dvs_config_src->ycoords_y,
	       (width_y * height_y * माप(uपूर्णांक32_t)));

	स_नकल(dvs_config_dst->xcoords_uv, dvs_config_src->xcoords_uv,
	       (width_uv * height_uv * माप(uपूर्णांक32_t)));
	स_नकल(dvs_config_dst->ycoords_uv, dvs_config_src->ycoords_uv,
	       (width_uv * height_uv * माप(uपूर्णांक32_t)));
पूर्ण

व्योम
ia_css_dvs_statistics_get(क्रमागत dvs_statistics_type type,
			  जोड़ ia_css_dvs_statistics_host  *host_stats,
			  स्थिर जोड़ ia_css_dvs_statistics_isp *isp_stats)
अणु
	अगर (type == DVS_STATISTICS) अणु
		ia_css_get_dvs_statistics(host_stats->p_dvs_statistics_host,
					  isp_stats->p_dvs_statistics_isp);
	पूर्ण अन्यथा अगर (type == DVS2_STATISTICS) अणु
		ia_css_get_dvs2_statistics(host_stats->p_dvs2_statistics_host,
					   isp_stats->p_dvs_statistics_isp);
	पूर्ण
	वापस;
पूर्ण
