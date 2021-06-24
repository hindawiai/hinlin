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

#अगर_अघोषित __TIMED_CTRL_PUBLIC_H_INCLUDED__
#घोषणा __TIMED_CTRL_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"

/*! Write to a control रेजिस्टर of TIMED_CTRL[ID]

 \param	ID[in]				TIMED_CTRL identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn none, TIMED_CTRL[ID].ctrl[reg] = value
 */
STORAGE_CLASS_TIMED_CTRL_H व्योम समयd_ctrl_reg_store(
    स्थिर समयd_ctrl_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक		reg_addr,
    स्थिर hrt_data			value);

व्योम समयd_ctrl_snd_commnd(
    स्थिर समयd_ctrl_ID_t				ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    hrt_address				addr,
    hrt_data				value);

व्योम समयd_ctrl_snd_sp_commnd(
    स्थिर समयd_ctrl_ID_t				ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    स्थिर sp_ID_t			SP_ID,
    hrt_address				offset,
    hrt_data				value);

व्योम समयd_ctrl_snd_gpio_commnd(
    स्थिर समयd_ctrl_ID_t				ID,
    hrt_data				mask,
    hrt_data				condition,
    hrt_data				counter,
    स्थिर gpio_ID_t			GPIO_ID,
    hrt_address				offset,
    hrt_data				value);

#पूर्ण_अगर /* __TIMED_CTRL_PUBLIC_H_INCLUDED__ */
