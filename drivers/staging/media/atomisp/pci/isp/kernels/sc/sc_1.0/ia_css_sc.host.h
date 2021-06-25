<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_SC_HOST_H
#घोषणा __IA_CSS_SC_HOST_H

#समावेश "sh_css_params.h"

#समावेश "ia_css_sc_types.h"
#समावेश "ia_css_sc_param.h"

व्योम
ia_css_sc_encode(
    काष्ठा sh_css_isp_sc_params *to,
    काष्ठा ia_css_shading_table **from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_sc_dump(
    स्थिर काष्ठा sh_css_isp_sc_params *sc,
    अचिन्हित पूर्णांक level);

/* @brief Configure the shading correction.
 * @param[out]	to	Parameters used in the shading correction kernel in the isp.
 * @param[in]	from	Parameters passed from the host.
 * @param[in]	size	Size of the sh_css_isp_sc_isp_config काष्ठाure.
 *
 * This function passes the parameters क्रम the shading correction from the host to the isp.
 */
/* ISP2401 */
व्योम
ia_css_sc_config(
    काष्ठा sh_css_isp_sc_isp_config *to,
    स्थिर काष्ठा ia_css_sc_configuration *from,
    अचिन्हित पूर्णांक size);

/* @brief Configure the shading correction.
 * @param[in]	binary	The binary, which has the shading correction.
 * @param[in]	पूर्णांकernal_frame_origin_x_bqs_on_sctbl
 *			X coordinate (in bqs) of the origin of the पूर्णांकernal frame on the shading table.
 * @param[in]	पूर्णांकernal_frame_origin_y_bqs_on_sctbl
 *			Y coordinate (in bqs) of the origin of the पूर्णांकernal frame on the shading table.
 *
 * This function calls the ia_css_configure_sc() function.
 * (The ia_css_configure_sc() function is स्वतःmatically generated in ia_css_isp.configs.c.)
 * The ia_css_configure_sc() function calls the ia_css_sc_config() function
 * to pass the parameters क्रम the shading correction from the host to the isp.
 */
/* ISP2401 */
व्योम
ia_css_sc_configure(
    स्थिर काष्ठा ia_css_binary *binary,
    u32 पूर्णांकernal_frame_origin_x_bqs_on_sctbl,
    uपूर्णांक32_t पूर्णांकernal_frame_origin_y_bqs_on_sctbl);

/* ------ deprecated(bz675) : from ------ */
व्योम
sh_css_get_shading_settings(स्थिर काष्ठा ia_css_isp_parameters *params,
			    काष्ठा ia_css_shading_settings *settings);

व्योम
sh_css_set_shading_settings(काष्ठा ia_css_isp_parameters *params,
			    स्थिर काष्ठा ia_css_shading_settings *settings);
/* ------ deprecated(bz675) : to ------ */

#पूर्ण_अगर /* __IA_CSS_SC_HOST_H */
