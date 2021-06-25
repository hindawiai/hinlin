<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "common.h"

/**
 * zip_cmd_qbuf_alloc - Allocates a cmd buffer क्रम ZIP Inकाष्ठाion Queue
 * @zip: Poपूर्णांकer to zip device काष्ठाure
 * @q:   Queue number to allocate bufffer to
 * Return: 0 अगर successful, -ENOMEM otherwise
 */
पूर्णांक zip_cmd_qbuf_alloc(काष्ठा zip_device *zip, पूर्णांक q)
अणु
	zip->iq[q].sw_head = (u64 *)__get_मुक्त_pages((GFP_KERNEL | GFP_DMA),
						get_order(ZIP_CMD_QBUF_SIZE));

	अगर (!zip->iq[q].sw_head)
		वापस -ENOMEM;

	स_रखो(zip->iq[q].sw_head, 0, ZIP_CMD_QBUF_SIZE);

	zip_dbg("cmd_qbuf_alloc[%d] Success : %p\n", q, zip->iq[q].sw_head);
	वापस 0;
पूर्ण

/**
 * zip_cmd_qbuf_मुक्त - Frees the cmd Queue buffer
 * @zip: Poपूर्णांकer to zip device काष्ठाure
 * @q:   Queue number to मुक्त buffer of
 */
व्योम zip_cmd_qbuf_मुक्त(काष्ठा zip_device *zip, पूर्णांक q)
अणु
	zip_dbg("Freeing cmd_qbuf 0x%lx\n", zip->iq[q].sw_tail);

	मुक्त_pages((u64)zip->iq[q].sw_tail, get_order(ZIP_CMD_QBUF_SIZE));
पूर्ण

/**
 * zip_data_buf_alloc - Allocates memory क्रम a data bufffer
 * @size:   Size of the buffer to allocate
 * Returns: Poपूर्णांकer to the buffer allocated
 */
u8 *zip_data_buf_alloc(u64 size)
अणु
	u8 *ptr;

	ptr = (u8 *)__get_मुक्त_pages((GFP_KERNEL | GFP_DMA),
					get_order(size));

	अगर (!ptr)
		वापस शून्य;

	स_रखो(ptr, 0, size);

	zip_dbg("Data buffer allocation success\n");
	वापस ptr;
पूर्ण

/**
 * zip_data_buf_मुक्त - Frees the memory of a data buffer
 * @ptr:  Poपूर्णांकer to the buffer
 * @size: Buffer size
 */
व्योम zip_data_buf_मुक्त(u8 *ptr, u64 size)
अणु
	zip_dbg("Freeing data buffer 0x%lx\n", ptr);

	मुक्त_pages((u64)ptr, get_order(size));
पूर्ण
