<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

#समावेश <type_support.h> /*uपूर्णांक32_t */
#समावेश "gp_timer.h"   /*प्रणाली_local.h,
			  gp_समयr_खुला.h*/

#अगर_अघोषित __INLINE_GP_TIMER__
#समावेश "gp_timer_private.h"  /*device_access.h*/
#पूर्ण_अगर /* __INLINE_GP_TIMER__ */
#समावेश "system_local.h"

/* FIXME: not sure अगर reg_load(), reg_store() should be API.
 */
अटल uपूर्णांक32_t
gp_समयr_reg_load(uपूर्णांक32_t reg);

अटल व्योम
gp_समयr_reg_store(u32 reg, uपूर्णांक32_t value);

अटल uपूर्णांक32_t
gp_समयr_reg_load(uपूर्णांक32_t reg)
अणु
	वापस ia_css_device_load_uपूर्णांक32(
		   GP_TIMER_BASE +
		   (reg * माप(uपूर्णांक32_t)));
पूर्ण

अटल व्योम
gp_समयr_reg_store(u32 reg, uपूर्णांक32_t value)
अणु
	ia_css_device_store_uपूर्णांक32((GP_TIMER_BASE +
				    (reg * माप(uपूर्णांक32_t))),
				   value);
पूर्ण

व्योम gp_समयr_init(gp_समयr_ID_t ID)
अणु
	/* set_overall_enable*/
	gp_समयr_reg_store(_REG_GP_TIMER_OVERALL_ENABLE, 1);

	/*set enable*/
	gp_समयr_reg_store(_REG_GP_TIMER_ENABLE_ID(ID), 1);

	/* set संकेत select */
	gp_समयr_reg_store(_REG_GP_TIMER_SIGNAL_SELECT_ID(ID), GP_TIMER_SIGNAL_SELECT);

	/*set count type */
	gp_समयr_reg_store(_REG_GP_TIMER_COUNT_TYPE_ID(ID), GP_TIMER_COUNT_TYPE_LOW);

	/*reset gp समयr */
	gp_समयr_reg_store(_REG_GP_TIMER_RESET_REG, 0xFF);
पूर्ण

uपूर्णांक32_t
gp_समयr_पढ़ो(gp_समयr_ID_t ID)
अणु
	वापस	gp_समयr_reg_load(_REG_GP_TIMER_VALUE_ID(ID));
पूर्ण
