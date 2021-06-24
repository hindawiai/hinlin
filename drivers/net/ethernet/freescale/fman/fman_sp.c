<शैली गुरु>
/*
 * Copyright 2008 - 2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
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

#समावेश "fman_sp.h"
#समावेश "fman.h"

व्योम fman_sp_set_buf_pools_in_asc_order_of_buf_sizes(काष्ठा fman_ext_pools
						     *fm_ext_pools,
						     u8 *ordered_array,
						     u16 *sizes_array)
अणु
	u16 buf_size = 0;
	पूर्णांक i = 0, j = 0, k = 0;

	/* First we copy the बाह्यal buffers pools inक्रमmation
	 * to an ordered local array
	 */
	क्रम (i = 0; i < fm_ext_pools->num_of_pools_used; i++) अणु
		/* get pool size */
		buf_size = fm_ext_pools->ext_buf_pool[i].size;

		/* keep sizes in an array according to poolId
		 * क्रम direct access
		 */
		sizes_array[fm_ext_pools->ext_buf_pool[i].id] = buf_size;

		/* save poolId in an ordered array according to size */
		क्रम (j = 0; j <= i; j++) अणु
			/* this is the next मुक्त place in the array */
			अगर (j == i)
				ordered_array[i] =
				    fm_ext_pools->ext_buf_pool[i].id;
			अन्यथा अणु
				/* find the right place क्रम this poolId */
				अगर (buf_size < sizes_array[ordered_array[j]]) अणु
					/* move the pool_ids one place ahead
					 * to make room क्रम this poolId
					 */
					क्रम (k = i; k > j; k--)
						ordered_array[k] =
						    ordered_array[k - 1];

					/* now k==j, this is the place क्रम
					 * the new size
					 */
					ordered_array[k] =
					    fm_ext_pools->ext_buf_pool[i].id;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fman_sp_set_buf_pools_in_asc_order_of_buf_sizes);

पूर्णांक fman_sp_build_buffer_काष्ठा(काष्ठा fman_sp_पूर्णांक_context_data_copy *
				पूर्णांक_context_data_copy,
				काष्ठा fman_buffer_prefix_content *
				buffer_prefix_content,
				काष्ठा fman_sp_buf_margins *buf_margins,
				काष्ठा fman_sp_buffer_offsets *buffer_offsets,
				u8 *पूर्णांकernal_buf_offset)
अणु
	u32 पंचांगp;

	/* Align start of पूर्णांकernal context data to 16 byte */
	पूर्णांक_context_data_copy->ext_buf_offset = (u16)
		((buffer_prefix_content->priv_data_size & (OFFSET_UNITS - 1)) ?
		((buffer_prefix_content->priv_data_size + OFFSET_UNITS) &
			~(u16)(OFFSET_UNITS - 1)) :
		buffer_prefix_content->priv_data_size);

	/* Translate margin and पूर्णांक_context params to FM parameters */
	/* Initialize with illegal value. Later we'll set legal values. */
	buffer_offsets->prs_result_offset = (u32)ILLEGAL_BASE;
	buffer_offsets->समय_stamp_offset = (u32)ILLEGAL_BASE;
	buffer_offsets->hash_result_offset = (u32)ILLEGAL_BASE;

	/* Internally the driver supports 4 options
	 * 1. prsResult/बारtamp/hashResult selection (in fact 8 options,
	 * but क्रम simplicity we'll
	 * relate to it as 1).
	 * 2. All IC context (from AD) not including debug.
	 */

	/* This हाल covers the options under 1 */
	/* Copy size must be in 16-byte granularity. */
	पूर्णांक_context_data_copy->size =
	    (u16)((buffer_prefix_content->pass_prs_result ? 32 : 0) +
		  ((buffer_prefix_content->pass_समय_stamp ||
		  buffer_prefix_content->pass_hash_result) ? 16 : 0));

	/* Align start of पूर्णांकernal context data to 16 byte */
	पूर्णांक_context_data_copy->पूर्णांक_context_offset =
	    (u8)(buffer_prefix_content->pass_prs_result ? 32 :
		 ((buffer_prefix_content->pass_समय_stamp ||
		 buffer_prefix_content->pass_hash_result) ? 64 : 0));

	अगर (buffer_prefix_content->pass_prs_result)
		buffer_offsets->prs_result_offset =
		    पूर्णांक_context_data_copy->ext_buf_offset;
	अगर (buffer_prefix_content->pass_समय_stamp)
		buffer_offsets->समय_stamp_offset =
		    buffer_prefix_content->pass_prs_result ?
		    (पूर्णांक_context_data_copy->ext_buf_offset +
			माप(काष्ठा fman_prs_result)) :
		    पूर्णांक_context_data_copy->ext_buf_offset;
	अगर (buffer_prefix_content->pass_hash_result)
		/* If PR is not requested, whether TS is
		 * requested or not, IC will be copied from TS
			 */
		buffer_offsets->hash_result_offset =
		buffer_prefix_content->pass_prs_result ?
			(पूर्णांक_context_data_copy->ext_buf_offset +
				माप(काष्ठा fman_prs_result) + 8) :
			पूर्णांक_context_data_copy->ext_buf_offset + 8;

	अगर (पूर्णांक_context_data_copy->size)
		buf_margins->start_margins =
		    (u16)(पूर्णांक_context_data_copy->ext_buf_offset +
			  पूर्णांक_context_data_copy->size);
	अन्यथा
		/* No Internal Context passing, STartMargin is
		 * immediately after निजी_info
		 */
		buf_margins->start_margins =
		    buffer_prefix_content->priv_data_size;

	/* align data start */
	पंचांगp = (u32)(buf_margins->start_margins %
		    buffer_prefix_content->data_align);
	अगर (पंचांगp)
		buf_margins->start_margins +=
		    (buffer_prefix_content->data_align - पंचांगp);
	buffer_offsets->data_offset = buf_margins->start_margins;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fman_sp_build_buffer_काष्ठा);

