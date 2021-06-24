<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित KFD_EVENTS_H_INCLUDED
#घोषणा KFD_EVENTS_H_INCLUDED

#समावेश <linux/kernel.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश "kfd_priv.h"
#समावेश <uapi/linux/kfd_ioctl.h>

/*
 * IDR supports non-negative पूर्णांकeger IDs. Small IDs are used क्रम
 * संकेत events to match their संकेत slot. Use the upper half of the
 * ID space क्रम non-संकेत events.
 */
#घोषणा KFD_FIRST_NONSIGNAL_EVENT_ID ((पूर्णांक_उच्च >> 1) + 1)
#घोषणा KFD_LAST_NONSIGNAL_EVENT_ID पूर्णांक_उच्च

/*
 * Written पूर्णांकo kfd_संकेत_slot_t to indicate that the event is not संकेतed.
 * Since the event protocol may need to ग_लिखो the event ID पूर्णांकo memory, this
 * must not be a valid event ID.
 * For the sake of easy स_रखो-ing, this must be a byte pattern.
 */
#घोषणा UNSIGNALED_EVENT_SLOT ((uपूर्णांक64_t)-1)

काष्ठा kfd_event_रुकोer;
काष्ठा संकेत_page;

काष्ठा kfd_event अणु
	u32 event_id;

	bool संकेतed;
	bool स्वतः_reset;

	पूर्णांक type;

	रुको_queue_head_t wq; /* List of event रुकोers. */

	/* Only क्रम संकेत events. */
	uपूर्णांक64_t __user *user_संकेत_address;

	/* type specअगरic data */
	जोड़ अणु
		काष्ठा kfd_hsa_memory_exception_data memory_exception_data;
		काष्ठा kfd_hsa_hw_exception_data hw_exception_data;
	पूर्ण;
पूर्ण;

#घोषणा KFD_EVENT_TIMEOUT_IMMEDIATE 0
#घोषणा KFD_EVENT_TIMEOUT_INFINITE 0xFFFFFFFFu

/* Matching HSA_EVENTTYPE */
#घोषणा KFD_EVENT_TYPE_SIGNAL 0
#घोषणा KFD_EVENT_TYPE_HW_EXCEPTION 3
#घोषणा KFD_EVENT_TYPE_DEBUG 5
#घोषणा KFD_EVENT_TYPE_MEMORY 8

बाह्य व्योम kfd_संकेत_event_पूर्णांकerrupt(u32 pasid, uपूर्णांक32_t partial_id,
				       uपूर्णांक32_t valid_id_bits);

#पूर्ण_अगर
