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

#अगर_अघोषित __GPIO_PUBLIC_H_INCLUDED__
#घोषणा __GPIO_PUBLIC_H_INCLUDED__

#समावेश "system_local.h"

/*! Write to a control रेजिस्टर of GPIO[ID]

 \param	ID[in]				GPIO identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn none, GPIO[ID].ctrl[reg] = value
 */
STORAGE_CLASS_GPIO_H व्योम gpio_reg_store(
    स्थिर gpio_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक		reg_addr,
    स्थिर hrt_data			value);

/*! Read from a control रेजिस्टर of GPIO[ID]

 \param	ID[in]				GPIO identअगरier
 \param	reg_addr[in]		रेजिस्टर byte address
 \param value[in]			The data to be written

 \लeturn GPIO[ID].ctrl[reg]
 */
STORAGE_CLASS_GPIO_H hrt_data gpio_reg_load(
    स्थिर gpio_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक		reg_addr);

#पूर्ण_अगर /* __GPIO_PUBLIC_H_INCLUDED__ */
