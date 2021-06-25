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

#अगर_अघोषित __ISYS_DMA_PRIVATE_H_INCLUDED__
#घोषणा __ISYS_DMA_PRIVATE_H_INCLUDED__

#समावेश "isys_dma_public.h"
#समावेश "device_access.h"
#समावेश "assert_support.h"
#समावेश "dma.h"
#समावेश "dma_v2_defs.h"
#समावेश "print_support.h"

व्योम isys2401_dma_reg_store(स्थिर isys2401_dma_ID_t	dma_id,
			    स्थिर अचिन्हित पूर्णांक		reg,
			    स्थिर hrt_data		value)
अणु
	अचिन्हित पूर्णांक reg_loc;

	निश्चित(dma_id < N_ISYS2401_DMA_ID);
	निश्चित(ISYS2401_DMA_BASE[dma_id] != (hrt_address) - 1);

	reg_loc = ISYS2401_DMA_BASE[dma_id] + (reg * माप(hrt_data));

	ia_css_prपूर्णांक("isys dma store at addr(0x%x) val(%u)\n", reg_loc,
		     (अचिन्हित पूर्णांक)value);
	ia_css_device_store_uपूर्णांक32(reg_loc, value);
पूर्ण

hrt_data isys2401_dma_reg_load(स्थिर isys2401_dma_ID_t	dma_id,
			       स्थिर अचिन्हित पूर्णांक	reg)
अणु
	अचिन्हित पूर्णांक reg_loc;
	hrt_data value;

	निश्चित(dma_id < N_ISYS2401_DMA_ID);
	निश्चित(ISYS2401_DMA_BASE[dma_id] != (hrt_address) - 1);

	reg_loc = ISYS2401_DMA_BASE[dma_id] + (reg * माप(hrt_data));

	value = ia_css_device_load_uपूर्णांक32(reg_loc);
	ia_css_prपूर्णांक("isys dma load from addr(0x%x) val(%u)\n", reg_loc,
		     (अचिन्हित पूर्णांक)value);

	वापस value;
पूर्ण

#पूर्ण_अगर /* __ISYS_DMA_PRIVATE_H_INCLUDED__ */
