<शैली गुरु>
/*
 * Copyright 2008 - 2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __FM_SP_H
#घोषणा __FM_SP_H

#समावेश "fman.h"
#समावेश <linux/types.h>

#घोषणा ILLEGAL_BASE    (~0)

/* शेषs */
#घोषणा DFLT_FM_SP_BUFFER_PREFIX_CONTEXT_DATA_ALIGN	64

/* Registers bit fields */
#घोषणा FMAN_SP_EXT_BUF_POOL_EN_COUNTER		0x40000000
#घोषणा FMAN_SP_EXT_BUF_POOL_VALID			0x80000000
#घोषणा FMAN_SP_EXT_BUF_POOL_BACKUP			0x20000000
#घोषणा FMAN_SP_DMA_ATTR_WRITE_OPTIMIZE		0x00100000
#घोषणा FMAN_SP_SG_DISABLE				0x80000000

/* shअगरts */
#घोषणा FMAN_SP_EXT_BUF_MARG_START_SHIFT		16
#घोषणा FMAN_SP_DMA_ATTR_SWP_SHIFT			30
#घोषणा FMAN_SP_IC_TO_EXT_SHIFT			16
#घोषणा FMAN_SP_IC_FROM_INT_SHIFT			8

/* काष्ठाure क्रम defining पूर्णांकernal context copying */
काष्ठा fman_sp_पूर्णांक_context_data_copy अणु
	/* < Offset in External buffer to which पूर्णांकernal
	 *  context is copied to (Rx) or taken from (Tx, Op).
	 */
	u16 ext_buf_offset;
	/* Offset within पूर्णांकernal context to copy from
	 * (Rx) or to copy to (Tx, Op).
	 */
	u8 पूर्णांक_context_offset;
	/* Internal offset size to be copied */
	u16 size;
पूर्ण;

/*  काष्ठा क्रम defining बाह्यal buffer margins */
काष्ठा fman_sp_buf_margins अणु
	/* Number of bytes to be left at the beginning
	 * of the बाह्यal buffer (must be भागisible by 16)
	 */
	u16 start_margins;
	/* number of bytes to be left at the end
	 * of the बाह्यal buffer(must be भागisible by 16)
	 */
	u16 end_margins;
पूर्ण;

काष्ठा fman_sp_buffer_offsets अणु
	u32 data_offset;
	u32 prs_result_offset;
	u32 समय_stamp_offset;
	u32 hash_result_offset;
पूर्ण;

पूर्णांक fman_sp_build_buffer_काष्ठा(काष्ठा fman_sp_पूर्णांक_context_data_copy
				*पूर्णांक_context_data_copy,
				काष्ठा fman_buffer_prefix_content
				*buffer_prefix_content,
				काष्ठा fman_sp_buf_margins *buf_margins,
				काष्ठा fman_sp_buffer_offsets
				*buffer_offsets,
				u8 *पूर्णांकernal_buf_offset);

व्योम fman_sp_set_buf_pools_in_asc_order_of_buf_sizes(काष्ठा fman_ext_pools
						     *fm_ext_pools,
						     u8 *ordered_array,
						     u16 *sizes_array);

#पूर्ण_अगर	/* __FM_SP_H */
