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

#अगर_अघोषित __GP_DEVICE_PUBLIC_H_INCLUDED__
#घोषणा __GP_DEVICE_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"

प्रकार काष्ठा gp_device_state_s		gp_device_state_t;

/*! Read the state of GP_DEVICE[ID]

 \param	ID[in]				GP_DEVICE identअगरier
 \param	state[out]			gp device state काष्ठाure

 \लeturn none, state = GP_DEVICE[ID].state
 */
व्योम gp_device_get_state(
    स्थिर gp_device_ID_t		ID,
    gp_device_state_t			*state);

/*! Write to a control रेजिस्टर of GP_DEVICE[ID]

 \param	ID[in]				GP_DEVICE identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn none, GP_DEVICE[ID].ctrl[reg] = value
 */
STORAGE_CLASS_GP_DEVICE_H व्योम gp_device_reg_store(
    स्थिर gp_device_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक		reg_addr,
    स्थिर hrt_data			value);

/*! Read from a control रेजिस्टर of GP_DEVICE[ID]

 \param	ID[in]				GP_DEVICE identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn GP_DEVICE[ID].ctrl[reg]
 */
STORAGE_CLASS_GP_DEVICE_H hrt_data gp_device_reg_load(
    स्थिर gp_device_ID_t	ID,
    स्थिर hrt_address	reg_addr);

#पूर्ण_अगर /* __GP_DEVICE_PUBLIC_H_INCLUDED__ */
