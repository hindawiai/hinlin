<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2017 Chelsio Communications.  All rights reserved.
 */

#समावेश "cxgb4.h"
#समावेश "cudbg_if.h"
#समावेश "cudbg_lib_common.h"

पूर्णांक cudbg_get_buff(काष्ठा cudbg_init *pdbg_init,
		   काष्ठा cudbg_buffer *pdbg_buff, u32 size,
		   काष्ठा cudbg_buffer *pin_buff)
अणु
	u32 offset;

	offset = pdbg_buff->offset;
	अगर (offset + size > pdbg_buff->size)
		वापस CUDBG_STATUS_NO_MEM;

	अगर (pdbg_init->compress_type != CUDBG_COMPRESSION_NONE) अणु
		अगर (size > pdbg_init->compress_buff_size)
			वापस CUDBG_STATUS_NO_MEM;

		pin_buff->data = (अक्षर *)pdbg_init->compress_buff;
		pin_buff->offset = 0;
		pin_buff->size = size;
		वापस 0;
	पूर्ण

	pin_buff->data = (अक्षर *)pdbg_buff->data + offset;
	pin_buff->offset = offset;
	pin_buff->size = size;
	वापस 0;
पूर्ण

व्योम cudbg_put_buff(काष्ठा cudbg_init *pdbg_init,
		    काष्ठा cudbg_buffer *pin_buff)
अणु
	/* Clear compression buffer क्रम re-use */
	अगर (pdbg_init->compress_type != CUDBG_COMPRESSION_NONE)
		स_रखो(pdbg_init->compress_buff, 0,
		       pdbg_init->compress_buff_size);

	pin_buff->data = शून्य;
	pin_buff->offset = 0;
	pin_buff->size = 0;
पूर्ण

व्योम cudbg_update_buff(काष्ठा cudbg_buffer *pin_buff,
		       काष्ठा cudbg_buffer *pout_buff)
अणु
	/* We alपढ़ोy ग_लिखो to buffer provided by ethool, so just
	 * increment offset to next मुक्त space.
	 */
	pout_buff->offset += pin_buff->size;
पूर्ण
