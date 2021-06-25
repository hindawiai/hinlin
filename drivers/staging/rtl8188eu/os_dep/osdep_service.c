<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _OSDEP_SERVICE_C_

#समावेश <osdep_service.h>
#समावेश <osdep_पूर्णांकf.h>
#समावेश <drv_types.h>
#समावेश <recv_osdep.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rtw_ioctl_set.h>

u8 *_rtw_दो_स्मृति(u32 sz)
अणु
	वापस kदो_स्मृति(sz, in_पूर्णांकerrupt() ? GFP_ATOMIC : GFP_KERNEL);
पूर्ण

व्योम _rtw_init_queue(काष्ठा __queue *pqueue)
अणु
	INIT_LIST_HEAD(&pqueue->queue);
	spin_lock_init(&pqueue->lock);
पूर्ण

व्योम rtw_buf_मुक्त(u8 **buf, u32 *buf_len)
अणु
	*buf_len = 0;
	kमुक्त(*buf);
	*buf = शून्य;
पूर्ण

व्योम rtw_buf_update(u8 **buf, u32 *buf_len, u8 *src, u32 src_len)
अणु
	u32 dup_len = 0;
	u8 *ori = शून्य;
	u8 *dup = शून्य;

	अगर (!buf || !buf_len)
		वापस;

	अगर (!src || !src_len)
		जाओ keep_ori;

	/* duplicate src */
	dup = rtw_दो_स्मृति(src_len);
	अगर (dup) अणु
		dup_len = src_len;
		स_नकल(dup, src, dup_len);
	पूर्ण

keep_ori:
	ori = *buf;

	/* replace buf with dup */
	*buf_len = 0;
	*buf = dup;
	*buf_len = dup_len;

	/* मुक्त ori */
	kमुक्त(ori);
पूर्ण
