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

#अगर_अघोषित __SP_PRIVATE_H_INCLUDED__
#घोषणा __SP_PRIVATE_H_INCLUDED__

#समावेश "sp_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

STORAGE_CLASS_SP_C व्योम sp_ctrl_store(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर hrt_data		value)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_CTRL_BASE[ID] != (hrt_address)-1);
	ia_css_device_store_uपूर्णांक32(SP_CTRL_BASE[ID] + reg * माप(hrt_data), value);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C hrt_data sp_ctrl_load(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_CTRL_BASE[ID] != (hrt_address)-1);
	वापस ia_css_device_load_uपूर्णांक32(SP_CTRL_BASE[ID] + reg * माप(hrt_data));
पूर्ण

STORAGE_CLASS_SP_C bool sp_ctrl_getbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data val = sp_ctrl_load(ID, reg);

	वापस (val & (1UL << bit)) != 0;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_ctrl_setbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data	data = sp_ctrl_load(ID, reg);

	sp_ctrl_store(ID, reg, (data | (1UL << bit)));
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_ctrl_clearbit(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data	data = sp_ctrl_load(ID, reg);

	sp_ctrl_store(ID, reg, (data & ~(1UL << bit)));
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_dmem_store(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर व्योम			*data,
    स्थिर माप_प्रकार		size)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	ia_css_device_store(SP_DMEM_BASE[ID] + addr, data, size);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_dmem_load(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr,
    व्योम				*data,
    स्थिर माप_प्रकार		size)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	ia_css_device_load(SP_DMEM_BASE[ID] + addr, data, size);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_dmem_store_uपूर्णांक8(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक8_t		data)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	ia_css_device_store_uपूर्णांक8(SP_DMEM_BASE[SP0_ID] + addr, data);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_dmem_store_uपूर्णांक16(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक16_t		data)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	ia_css_device_store_uपूर्णांक16(SP_DMEM_BASE[SP0_ID] + addr, data);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C व्योम sp_dmem_store_uपूर्णांक32(
    स्थिर sp_ID_t		ID,
    hrt_address		addr,
    स्थिर uपूर्णांक32_t		data)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	ia_css_device_store_uपूर्णांक32(SP_DMEM_BASE[SP0_ID] + addr, data);
	वापस;
पूर्ण

STORAGE_CLASS_SP_C uपूर्णांक8_t sp_dmem_load_uपूर्णांक8(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	वापस ia_css_device_load_uपूर्णांक8(SP_DMEM_BASE[SP0_ID] + addr);
पूर्ण

STORAGE_CLASS_SP_C uपूर्णांक16_t sp_dmem_load_uपूर्णांक16(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	वापस ia_css_device_load_uपूर्णांक16(SP_DMEM_BASE[SP0_ID] + addr);
पूर्ण

STORAGE_CLASS_SP_C uपूर्णांक32_t sp_dmem_load_uपूर्णांक32(
    स्थिर sp_ID_t		ID,
    स्थिर hrt_address	addr)
अणु
	निश्चित(ID < N_SP_ID);
	निश्चित(SP_DMEM_BASE[ID] != (hrt_address)-1);
	(व्योम)ID;
	वापस ia_css_device_load_uपूर्णांक32(SP_DMEM_BASE[SP0_ID] + addr);
पूर्ण

#पूर्ण_अगर /* __SP_PRIVATE_H_INCLUDED__ */
