<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* The industrial I/O - event passing to userspace
 *
 * Copyright (c) 2008-2011 Jonathan Cameron
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित _UAPI_IIO_EVENTS_H_
#घोषणा _UAPI_IIO_EVENTS_H_

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/**
 * काष्ठा iio_event_data - The actual event being pushed to userspace
 * @id:		event identअगरier
 * @बारtamp:	best estimate of समय of event occurrence (often from
 *		the पूर्णांकerrupt handler)
 */
काष्ठा iio_event_data अणु
	__u64	id;
	__s64	बारtamp;
पूर्ण;

#घोषणा IIO_GET_EVENT_FD_IOCTL _IOR('i', 0x90, पूर्णांक)

#घोषणा IIO_EVENT_CODE_EXTRACT_TYPE(mask) ((mask >> 56) & 0xFF)

#घोषणा IIO_EVENT_CODE_EXTRACT_सूची(mask) ((mask >> 48) & 0x7F)

#घोषणा IIO_EVENT_CODE_EXTRACT_CHAN_TYPE(mask) ((mask >> 32) & 0xFF)

/* Event code number extraction depends on which type of event we have.
 * Perhaps review this function in the future*/
#घोषणा IIO_EVENT_CODE_EXTRACT_CHAN(mask) ((__s16)(mask & 0xFFFF))
#घोषणा IIO_EVENT_CODE_EXTRACT_CHAN2(mask) ((__s16)(((mask) >> 16) & 0xFFFF))

#घोषणा IIO_EVENT_CODE_EXTRACT_MODIFIER(mask) ((mask >> 40) & 0xFF)
#घोषणा IIO_EVENT_CODE_EXTRACT_DIFF(mask) (((mask) >> 55) & 0x1)

#पूर्ण_अगर /* _UAPI_IIO_EVENTS_H_ */
