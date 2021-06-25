<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __GP_DEVICE_PRIVATE_H_INCLUDED__
#घोषणा __GP_DEVICE_PRIVATE_H_INCLUDED__

#समावेश "gp_device_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

STORAGE_CLASS_GP_DEVICE_C व्योम gp_device_reg_store(
    स्थिर gp_device_ID_t	ID,
    स्थिर अचिन्हित पूर्णांक		reg_addr,
    स्थिर hrt_data			value)
अणु
	निश्चित(ID < N_GP_DEVICE_ID);
	निश्चित(GP_DEVICE_BASE[ID] != (hrt_address) - 1);
	निश्चित((reg_addr % माप(hrt_data)) == 0);
	ia_css_device_store_uपूर्णांक32(GP_DEVICE_BASE[ID] + reg_addr, value);
	वापस;
पूर्ण

STORAGE_CLASS_GP_DEVICE_C hrt_data gp_device_reg_load(
    स्थिर gp_device_ID_t	ID,
    स्थिर hrt_address	reg_addr)
अणु
	निश्चित(ID < N_GP_DEVICE_ID);
	निश्चित(GP_DEVICE_BASE[ID] != (hrt_address)-1);
	निश्चित((reg_addr % माप(hrt_data)) == 0);
	वापस ia_css_device_load_uपूर्णांक32(GP_DEVICE_BASE[ID] + reg_addr);
पूर्ण

#पूर्ण_अगर /* __GP_DEVICE_PRIVATE_H_INCLUDED__ */
