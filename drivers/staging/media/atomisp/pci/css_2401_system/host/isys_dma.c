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

#समावेश "system_local.h"
#समावेश "isys_dma_global.h"
#समावेश "assert_support.h"
#समावेश "isys_dma_private.h"

स्थिर isys2401_dma_channel N_ISYS2401_DMA_CHANNEL_PROCS[N_ISYS2401_DMA_ID] = अणु
	N_ISYS2401_DMA_CHANNEL
पूर्ण;

व्योम isys2401_dma_set_max_burst_size(
    स्थिर isys2401_dma_ID_t	dma_id,
    uपूर्णांक32_t		max_burst_size)
अणु
	निश्चित(dma_id < N_ISYS2401_DMA_ID);
	निश्चित((max_burst_size > 0x00) && (max_burst_size <= 0xFF));

	isys2401_dma_reg_store(dma_id,
			       DMA_DEV_INFO_REG_IDX(_DMA_V2_DEV_INTERF_MAX_BURST_IDX, HIVE_DMA_BUS_DDR_CONN),
			       (max_burst_size - 1));
पूर्ण
