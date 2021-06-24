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

#समावेश "timed_ctrl.h"

#अगर_अघोषित __INLINE_TIMED_CTRL__
#समावेश "timed_ctrl_private.h"
#पूर्ण_अगर /* __INLINE_TIMED_CTRL__ */

#समावेश "assert_support.h"

व्योम समयd_ctrl_snd_commnd(
    स्थिर समयd_ctrl_ID_t			ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    hrt_address				addr,
    hrt_data				value)
अणु
	OP___निश्चित(ID == TIMED_CTRL0_ID);
	OP___निश्चित(TIMED_CTRL_BASE[ID] != (hrt_address)-1);

	समयd_ctrl_reg_store(ID, _HRT_TIMED_CONTROLLER_CMD_REG_IDX, mask);
	समयd_ctrl_reg_store(ID, _HRT_TIMED_CONTROLLER_CMD_REG_IDX, condition);
	समयd_ctrl_reg_store(ID, _HRT_TIMED_CONTROLLER_CMD_REG_IDX, counter);
	समयd_ctrl_reg_store(ID, _HRT_TIMED_CONTROLLER_CMD_REG_IDX, (hrt_data)addr);
	समयd_ctrl_reg_store(ID, _HRT_TIMED_CONTROLLER_CMD_REG_IDX, value);
पूर्ण

/* pqiao TODO: make sure the following commands get
	correct BASE address both क्रम csim and android */

व्योम समयd_ctrl_snd_sp_commnd(
    स्थिर समयd_ctrl_ID_t			ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    स्थिर sp_ID_t				SP_ID,
    hrt_address				offset,
    hrt_data				value)
अणु
	OP___निश्चित(SP_ID < N_SP_ID);
	OP___निश्चित(SP_DMEM_BASE[SP_ID] != (hrt_address)-1);

	समयd_ctrl_snd_commnd(ID, mask, condition, counter,
			      SP_DMEM_BASE[SP_ID] + offset, value);
पूर्ण

व्योम समयd_ctrl_snd_gpio_commnd(
    स्थिर समयd_ctrl_ID_t			ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    स्थिर gpio_ID_t				GPIO_ID,
    hrt_address				offset,
    hrt_data				value)
अणु
	OP___निश्चित(GPIO_ID < N_GPIO_ID);
	OP___निश्चित(GPIO_BASE[GPIO_ID] != (hrt_address)-1);

	समयd_ctrl_snd_commnd(ID, mask, condition, counter,
			      GPIO_BASE[GPIO_ID] + offset, value);
पूर्ण
