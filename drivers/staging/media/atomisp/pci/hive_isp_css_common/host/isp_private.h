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

#अगर_अघोषित __ISP_PRIVATE_H_INCLUDED__
#घोषणा __ISP_PRIVATE_H_INCLUDED__

#अगर_घोषित HRT_MEMORY_ACCESS
#समावेश <hrt/api.h>
#पूर्ण_अगर

#समावेश "isp_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"
#समावेश "type_support.h"

STORAGE_CLASS_ISP_C व्योम isp_ctrl_store(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_CTRL_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_store_uपूर्णांक32(ISP_CTRL_BASE[ID] + reg * माप(hrt_data), value);
#अन्यथा
	hrt_master_port_store_32(ISP_CTRL_BASE[ID] + reg * माप(hrt_data), value);
#पूर्ण_अगर
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C hrt_data isp_ctrl_load(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_CTRL_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	वापस ia_css_device_load_uपूर्णांक32(ISP_CTRL_BASE[ID] + reg * माप(hrt_data));
#अन्यथा
	वापस hrt_master_port_uload_32(ISP_CTRL_BASE[ID] + reg * माप(hrt_data));
#पूर्ण_अगर
पूर्ण

STORAGE_CLASS_ISP_C bool isp_ctrl_getbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data val = isp_ctrl_load(ID, reg);

	वापस (val & (1UL << bit)) != 0;
पूर्ण

STORAGE_CLASS_ISP_C व्योम isp_ctrl_setbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data	data = isp_ctrl_load(ID, reg);

	isp_ctrl_store(ID, reg, (data | (1UL << bit)));
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C व्योम isp_ctrl_clearbit(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर अचिन्हित पूर्णांक	bit)
अणु
	hrt_data	data = isp_ctrl_load(ID, reg);

	isp_ctrl_store(ID, reg, (data & ~(1UL << bit)));
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C व्योम isp_dmem_store(
    स्थिर isp_ID_t		ID,
    अचिन्हित पूर्णांक		addr,
    स्थिर व्योम		*data,
    स्थिर माप_प्रकार		size)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_DMEM_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_store(ISP_DMEM_BASE[ID] + addr, data, size);
#अन्यथा
	hrt_master_port_store(ISP_DMEM_BASE[ID] + addr, data, size);
#पूर्ण_अगर
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C व्योम isp_dmem_load(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	addr,
    व्योम			*data,
    स्थिर माप_प्रकार		size)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_DMEM_BASE[ID] != (hrt_address) - 1);
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_load(ISP_DMEM_BASE[ID] + addr, data, size);
#अन्यथा
	hrt_master_port_load(ISP_DMEM_BASE[ID] + addr, data, size);
#पूर्ण_अगर
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C व्योम isp_dmem_store_uपूर्णांक32(
    स्थिर isp_ID_t		ID,
    अचिन्हित पूर्णांक		addr,
    स्थिर uपूर्णांक32_t		data)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_DMEM_BASE[ID] != (hrt_address) - 1);
	(व्योम)ID;
#अगर !defined(HRT_MEMORY_ACCESS)
	ia_css_device_store_uपूर्णांक32(ISP_DMEM_BASE[ID] + addr, data);
#अन्यथा
	hrt_master_port_store_32(ISP_DMEM_BASE[ID] + addr, data);
#पूर्ण_अगर
	वापस;
पूर्ण

STORAGE_CLASS_ISP_C uपूर्णांक32_t isp_dmem_load_uपूर्णांक32(
    स्थिर isp_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	addr)
अणु
	निश्चित(ID < N_ISP_ID);
	निश्चित(ISP_DMEM_BASE[ID] != (hrt_address) - 1);
	(व्योम)ID;
#अगर !defined(HRT_MEMORY_ACCESS)
	वापस ia_css_device_load_uपूर्णांक32(ISP_DMEM_BASE[ID] + addr);
#अन्यथा
	वापस hrt_master_port_uload_32(ISP_DMEM_BASE[ID] + addr);
#पूर्ण_अगर
पूर्ण

STORAGE_CLASS_ISP_C uपूर्णांक32_t isp_2w_cat_1w(
    स्थिर u16		x0,
    स्थिर uपूर्णांक16_t		x1)
अणु
	u32 out = ((uपूर्णांक32_t)(x1 & HIVE_ISP_VMEM_MASK) << ISP_VMEM_ELEMBITS)
		  | (x0 & HIVE_ISP_VMEM_MASK);
	वापस out;
पूर्ण

#पूर्ण_अगर /* __ISP_PRIVATE_H_INCLUDED__ */
