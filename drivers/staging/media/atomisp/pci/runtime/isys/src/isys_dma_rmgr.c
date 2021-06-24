<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#समावेश "system_global.h"

#अगर_घोषित ISP2401

#समावेश "assert_support.h"
#समावेश "platform_support.h"
#समावेश "ia_css_isys.h"
#समावेश "bitop_support.h"
#समावेश "isys_dma_rmgr.h"

अटल isys_dma_rsrc_t isys_dma_rsrc[N_ISYS2401_DMA_ID];

व्योम ia_css_isys_dma_channel_rmgr_init(व्योम)
अणु
	स_रखो(&isys_dma_rsrc, 0, माप(isys_dma_rsrc_t));
पूर्ण

व्योम ia_css_isys_dma_channel_rmgr_uninit(व्योम)
अणु
	स_रखो(&isys_dma_rsrc, 0, माप(isys_dma_rsrc_t));
पूर्ण

bool ia_css_isys_dma_channel_rmgr_acquire(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel)
अणु
	bool retval = false;
	isys2401_dma_channel	i;
	isys2401_dma_channel	max_dma_channel;
	isys_dma_rsrc_t		*cur_rsrc = शून्य;

	निश्चित(dma_id < N_ISYS2401_DMA_ID);
	निश्चित(channel);

	max_dma_channel = N_ISYS2401_DMA_CHANNEL_PROCS[dma_id];
	cur_rsrc = &isys_dma_rsrc[dma_id];

	अगर (cur_rsrc->num_active < max_dma_channel) अणु
		क्रम (i = ISYS2401_DMA_CHANNEL_0; i < N_ISYS2401_DMA_CHANNEL; i++) अणु
			अगर (bitop_getbit(cur_rsrc->active_table, i) == 0) अणु
				bitop_setbit(cur_rsrc->active_table, i);
				*channel = i;
				cur_rsrc->num_active++;
				retval = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

व्योम ia_css_isys_dma_channel_rmgr_release(
    isys2401_dma_ID_t	dma_id,
    isys2401_dma_channel	*channel)
अणु
	isys2401_dma_channel	max_dma_channel;
	isys_dma_rsrc_t		*cur_rsrc = शून्य;

	निश्चित(dma_id < N_ISYS2401_DMA_ID);
	निश्चित(channel);

	max_dma_channel = N_ISYS2401_DMA_CHANNEL_PROCS[dma_id];
	cur_rsrc = &isys_dma_rsrc[dma_id];

	अगर ((*channel < max_dma_channel) && (cur_rsrc->num_active > 0)) अणु
		अगर (bitop_getbit(cur_rsrc->active_table, *channel) == 1) अणु
			bitop_clearbit(cur_rsrc->active_table, *channel);
			cur_rsrc->num_active--;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर
