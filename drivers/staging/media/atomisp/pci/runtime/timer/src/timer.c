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

#समावेश <type_support.h>		/* क्रम uपूर्णांक32_t */
#समावेश "ia_css_timer.h" /*काष्ठा ia_css_घड़ी_प्रकारick */
#समावेश "sh_css_legacy.h" /* IA_CSS_PIPE_ID_NUM*/
#समावेश "gp_timer.h" /*gp_समयr_पढ़ो()*/
#समावेश "assert_support.h"

पूर्णांक ia_css_समयr_get_current_tick(काष्ठा ia_css_घड़ी_प्रकारick *curr_ts)
अणु
	निश्चित(curr_ts);
	अगर (!curr_ts)
		वापस -EINVAL;
	curr_ts->ticks = (घड़ी_value_t)gp_समयr_पढ़ो(GP_TIMER_SEL);
	वापस 0;
पूर्ण
