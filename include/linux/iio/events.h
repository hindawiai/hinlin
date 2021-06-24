<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O - event passing to userspace
 *
 * Copyright (c) 2008-2011 Jonathan Cameron
 */
#अगर_अघोषित _IIO_EVENTS_H_
#घोषणा _IIO_EVENTS_H_

#समावेश <linux/iio/types.h>
#समावेश <uapi/linux/iio/events.h>

/**
 * IIO_EVENT_CODE() - create event identअगरier
 * @chan_type:	Type of the channel. Should be one of क्रमागत iio_chan_type.
 * @dअगरf:	Whether the event is क्रम an dअगरferential channel or not.
 * @modअगरier:	Modअगरier क्रम the channel. Should be one of क्रमागत iio_modअगरier.
 * @direction:	Direction of the event. One of क्रमागत iio_event_direction.
 * @type:	Type of the event. Should be one of क्रमागत iio_event_type.
 * @chan:	Channel number क्रम non-dअगरferential channels.
 * @chan1:	First channel number क्रम dअगरferential channels.
 * @chan2:	Second channel number क्रम dअगरferential channels.
 */

#घोषणा IIO_EVENT_CODE(chan_type, dअगरf, modअगरier, direction,		\
		       type, chan, chan1, chan2)			\
	(((u64)type << 56) | ((u64)dअगरf << 55) |			\
	 ((u64)direction << 48) | ((u64)modअगरier << 40) |		\
	 ((u64)chan_type << 32) | (((u16)chan2) << 16) | ((u16)chan1) | \
	 ((u16)chan))


/**
 * IIO_MOD_EVENT_CODE() - create event identअगरier क्रम modअगरied channels
 * @chan_type:	Type of the channel. Should be one of क्रमागत iio_chan_type.
 * @number:	Channel number.
 * @modअगरier:	Modअगरier क्रम the channel. Should be one of क्रमागत iio_modअगरier.
 * @type:	Type of the event. Should be one of क्रमागत iio_event_type.
 * @direction:	Direction of the event. One of क्रमागत iio_event_direction.
 */

#घोषणा IIO_MOD_EVENT_CODE(chan_type, number, modअगरier,		\
			   type, direction)				\
	IIO_EVENT_CODE(chan_type, 0, modअगरier, direction, type, number, 0, 0)

/**
 * IIO_UNMOD_EVENT_CODE() - create event identअगरier क्रम unmodअगरied channels
 * @chan_type:	Type of the channel. Should be one of क्रमागत iio_chan_type.
 * @number:	Channel number.
 * @type:	Type of the event. Should be one of क्रमागत iio_event_type.
 * @direction:	Direction of the event. One of क्रमागत iio_event_direction.
 */

#घोषणा IIO_UNMOD_EVENT_CODE(chan_type, number, type, direction)	\
	IIO_EVENT_CODE(chan_type, 0, 0, direction, type, number, 0, 0)

#पूर्ण_अगर
