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

#समावेश "ia_css_formats.host.h"
#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"

/*#समावेश "sh_css_frac.h"*/
#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
#समावेश "ia_css_debug.h"
#पूर्ण_अगर

स्थिर काष्ठा ia_css_क्रमmats_config शेष_क्रमmats_config = अणु
	1
पूर्ण;

व्योम
ia_css_क्रमmats_encode(
    काष्ठा sh_css_isp_क्रमmats_params *to,
    स्थिर काष्ठा ia_css_क्रमmats_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->video_full_range_flag = from->video_full_range_flag;
पूर्ण

#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
व्योम
ia_css_क्रमmats_dump(
    स्थिर काष्ठा sh_css_isp_क्रमmats_params *क्रमmats,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!क्रमmats) वापस;
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "video_full_range_flag", क्रमmats->video_full_range_flag);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित IA_CSS_NO_DEBUG
/* FIXME: See BZ 4427 */
व्योम
ia_css_क्रमmats_debug_dtrace(
    स्थिर काष्ठा ia_css_क्रमmats_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.video_full_range_flag=%d\n",
			    config->video_full_range_flag);
पूर्ण
#पूर्ण_अगर
