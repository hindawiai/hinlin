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

#अगर_अघोषित __ISYS_DMA_PUBLIC_H_INCLUDED__
#घोषणा __ISYS_DMA_PUBLIC_H_INCLUDED__

#अगर_घोषित ISP2401

#समावेश "system_local.h"
#समावेश "type_support.h"

बाह्य व्योम isys2401_dma_reg_store(
    स्थिर isys2401_dma_ID_t dma_id,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value);

बाह्य hrt_data isys2401_dma_reg_load(
    स्थिर isys2401_dma_ID_t dma_id,
    स्थिर अचिन्हित पूर्णांक	reg);

व्योम isys2401_dma_set_max_burst_size(
    स्थिर isys2401_dma_ID_t dma_id,
    uपूर्णांक32_t		max_burst_size);

#पूर्ण_अगर /* ISP2401 */

#पूर्ण_अगर /* __ISYS_DMA_PUBLIC_H_INCLUDED__ */
