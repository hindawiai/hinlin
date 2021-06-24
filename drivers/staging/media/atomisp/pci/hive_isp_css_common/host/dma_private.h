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

#अगर_अघोषित __DMA_PRIVATE_H_INCLUDED__
#घोषणा __DMA_PRIVATE_H_INCLUDED__

#समावेश "dma_public.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

STORAGE_CLASS_DMA_C व्योम dma_reg_store(स्थिर dma_ID_t ID,
				       स्थिर अचिन्हित पूर्णांक reg,
				       स्थिर hrt_data value)
अणु
	निश्चित(ID < N_DMA_ID);
	निश्चित(DMA_BASE[ID] != (hrt_address) - 1);
	ia_css_device_store_uपूर्णांक32(DMA_BASE[ID] + reg * माप(hrt_data), value);
पूर्ण

STORAGE_CLASS_DMA_C hrt_data dma_reg_load(स्थिर dma_ID_t ID,
	स्थिर अचिन्हित पूर्णांक reg)
अणु
	निश्चित(ID < N_DMA_ID);
	निश्चित(DMA_BASE[ID] != (hrt_address) - 1);
	वापस ia_css_device_load_uपूर्णांक32(DMA_BASE[ID] + reg * माप(hrt_data));
पूर्ण

#पूर्ण_अगर /* __DMA_PRIVATE_H_INCLUDED__ */
