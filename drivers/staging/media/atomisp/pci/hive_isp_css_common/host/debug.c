<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2016, Intel Corporation.
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

#समावेश "debug.h"

#समावेश "hmm.h"

#अगर_अघोषित __INLINE_DEBUG__
#समावेश "debug_private.h"
#पूर्ण_अगर /* __INLINE_DEBUG__ */

#घोषणा __INLINE_SP__
#समावेश "sp.h"

#समावेश "assert_support.h"

/* The address of the remote copy */
hrt_address	debug_buffer_address = (hrt_address) - 1;
ia_css_ptr	debug_buffer_ddr_address = (ia_css_ptr)-1;
/* The local copy */
अटल debug_data_t		debug_data;
debug_data_t		*debug_data_ptr = &debug_data;

व्योम debug_buffer_init(स्थिर hrt_address addr)
अणु
	debug_buffer_address = addr;

	debug_data.head = 0;
	debug_data.tail = 0;
पूर्ण

व्योम debug_buffer_ddr_init(स्थिर ia_css_ptr addr)
अणु
	debug_buf_mode_t mode = DEBUG_BUFFER_MODE_LINEAR;
	u32 enable = 1;
	u32 head = 0;
	u32 tail = 0;
	/* set the ddr queue */
	debug_buffer_ddr_address = addr;
	hmm_store(addr + DEBUG_DATA_BUF_MODE_DDR_ADDR,
		   &mode, माप(debug_buf_mode_t));
	hmm_store(addr + DEBUG_DATA_HEAD_DDR_ADDR,
		   &head, माप(uपूर्णांक32_t));
	hmm_store(addr + DEBUG_DATA_TAIL_DDR_ADDR,
		   &tail, माप(uपूर्णांक32_t));
	hmm_store(addr + DEBUG_DATA_ENABLE_DDR_ADDR,
		   &enable, माप(uपूर्णांक32_t));

	/* set the local copy */
	debug_data.head = 0;
	debug_data.tail = 0;
पूर्ण

व्योम debug_buffer_seपंचांगode(स्थिर debug_buf_mode_t mode)
अणु
	निश्चित(debug_buffer_address != ((hrt_address)-1));

	sp_dmem_store_uपूर्णांक32(SP0_ID,
			     debug_buffer_address + DEBUG_DATA_BUF_MODE_ADDR, mode);
पूर्ण
