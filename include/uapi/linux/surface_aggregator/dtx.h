<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Surface DTX (clipboard detachment प्रणाली driver) user-space पूर्णांकerface.
 *
 * Definitions, काष्ठाs, and IOCTLs क्रम the /dev/surface/dtx misc device. This
 * device allows user-space to control the clipboard detachment process on
 * Surface Book series devices.
 *
 * Copyright (C) 2020-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _UAPI_LINUX_SURFACE_AGGREGATOR_DTX_H
#घोषणा _UAPI_LINUX_SURFACE_AGGREGATOR_DTX_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* Status/error categories */
#घोषणा SDTX_CATEGORY_STATUS		0x0000
#घोषणा SDTX_CATEGORY_RUNTIME_ERROR	0x1000
#घोषणा SDTX_CATEGORY_HARDWARE_ERROR	0x2000
#घोषणा SDTX_CATEGORY_UNKNOWN		0xf000

#घोषणा SDTX_CATEGORY_MASK		0xf000
#घोषणा SDTX_CATEGORY(value)		((value) & SDTX_CATEGORY_MASK)

#घोषणा SDTX_STATUS(code)		((code) | SDTX_CATEGORY_STATUS)
#घोषणा SDTX_ERR_RT(code)		((code) | SDTX_CATEGORY_RUNTIME_ERROR)
#घोषणा SDTX_ERR_HW(code)		((code) | SDTX_CATEGORY_HARDWARE_ERROR)
#घोषणा SDTX_UNKNOWN(code)		((code) | SDTX_CATEGORY_UNKNOWN)

#घोषणा SDTX_SUCCESS(value)		(SDTX_CATEGORY(value) == SDTX_CATEGORY_STATUS)

/* Latch status values */
#घोषणा SDTX_LATCH_CLOSED		SDTX_STATUS(0x00)
#घोषणा SDTX_LATCH_OPENED		SDTX_STATUS(0x01)

/* Base state values */
#घोषणा SDTX_BASE_DETACHED		SDTX_STATUS(0x00)
#घोषणा SDTX_BASE_ATTACHED		SDTX_STATUS(0x01)

/* Runसमय errors (non-critical) */
#घोषणा SDTX_DETACH_NOT_FEASIBLE	SDTX_ERR_RT(0x01)
#घोषणा SDTX_DETACH_TIMEDOUT		SDTX_ERR_RT(0x02)

/* Hardware errors (critical) */
#घोषणा SDTX_ERR_FAILED_TO_OPEN		SDTX_ERR_HW(0x01)
#घोषणा SDTX_ERR_FAILED_TO_REMAIN_OPEN	SDTX_ERR_HW(0x02)
#घोषणा SDTX_ERR_FAILED_TO_CLOSE	SDTX_ERR_HW(0x03)

/* Base types */
#घोषणा SDTX_DEVICE_TYPE_HID		0x0100
#घोषणा SDTX_DEVICE_TYPE_SSH		0x0200

#घोषणा SDTX_DEVICE_TYPE_MASK		0x0f00
#घोषणा SDTX_DEVICE_TYPE(value)		((value) & SDTX_DEVICE_TYPE_MASK)

#घोषणा SDTX_BASE_TYPE_HID(id)		((id) | SDTX_DEVICE_TYPE_HID)
#घोषणा SDTX_BASE_TYPE_SSH(id)		((id) | SDTX_DEVICE_TYPE_SSH)

/**
 * क्रमागत sdtx_device_mode - Mode describing how (and अगर) the clipboard is
 * attached to the base of the device.
 * @SDTX_DEVICE_MODE_TABLET: The clipboard is detached from the base and the
 *                           device operates as tablet.
 * @SDTX_DEVICE_MODE_LAPTOP: The clipboard is attached normally to the base
 *                           and the device operates as laptop.
 * @SDTX_DEVICE_MODE_STUDIO: The clipboard is attached to the base in reverse.
 *                           The device operates as tablet with keyboard and
 *                           touchpad deactivated, however, the base battery
 *                           and, अगर present in the specअगरic device model, dGPU
 *                           are available to the प्रणाली.
 */
क्रमागत sdtx_device_mode अणु
	SDTX_DEVICE_MODE_TABLET		= 0x00,
	SDTX_DEVICE_MODE_LAPTOP		= 0x01,
	SDTX_DEVICE_MODE_STUDIO		= 0x02,
पूर्ण;

/**
 * काष्ठा sdtx_event - Event provided by पढ़ोing from the DTX device file.
 * @length: Length of the event payload, in bytes.
 * @code:   Event code, detailing what type of event this is.
 * @data:   Payload of the event, containing @length bytes.
 *
 * See &क्रमागत sdtx_event_code क्रम currently valid event codes.
 */
काष्ठा sdtx_event अणु
	__u16 length;
	__u16 code;
	__u8 data[];
पूर्ण __attribute__((__packed__));

/**
 * क्रमागत sdtx_event_code - Code describing the type of an event.
 * @SDTX_EVENT_REQUEST:         Detachment request event type.
 * @SDTX_EVENT_CANCEL:          Cancel detachment process event type.
 * @SDTX_EVENT_BASE_CONNECTION: Base/clipboard connection change event type.
 * @SDTX_EVENT_LATCH_STATUS:    Latch status change event type.
 * @SDTX_EVENT_DEVICE_MODE:     Device mode change event type.
 *
 * Used in &काष्ठा sdtx_event to describe the type of the event. Further event
 * codes are reserved क्रम future use. Any event parser should be able to
 * gracefully handle unknown events, i.e. by simply skipping them.
 *
 * Consult the DTX user-space पूर्णांकerface करोcumentation क्रम details regarding
 * the inभागidual event types.
 */
क्रमागत sdtx_event_code अणु
	SDTX_EVENT_REQUEST		= 1,
	SDTX_EVENT_CANCEL		= 2,
	SDTX_EVENT_BASE_CONNECTION	= 3,
	SDTX_EVENT_LATCH_STATUS		= 4,
	SDTX_EVENT_DEVICE_MODE		= 5,
पूर्ण;

/**
 * काष्ठा sdtx_base_info - Describes अगर and what type of base is connected.
 * @state:   The state of the connection. Valid values are %SDTX_BASE_DETACHED,
 *           %SDTX_BASE_ATTACHED, and %SDTX_DETACH_NOT_FEASIBLE (in हाल a base
 *           is attached but low clipboard battery prevents detachment). Other
 *           values are currently reserved.
 * @base_id: The type of base connected. Zero अगर no base is connected.
 */
काष्ठा sdtx_base_info अणु
	__u16 state;
	__u16 base_id;
पूर्ण __attribute__((__packed__));

/* IOCTLs */
#घोषणा SDTX_IOCTL_EVENTS_ENABLE	_IO(0xa5, 0x21)
#घोषणा SDTX_IOCTL_EVENTS_DISABLE	_IO(0xa5, 0x22)

#घोषणा SDTX_IOCTL_LATCH_LOCK		_IO(0xa5, 0x23)
#घोषणा SDTX_IOCTL_LATCH_UNLOCK		_IO(0xa5, 0x24)

#घोषणा SDTX_IOCTL_LATCH_REQUEST	_IO(0xa5, 0x25)
#घोषणा SDTX_IOCTL_LATCH_CONFIRM	_IO(0xa5, 0x26)
#घोषणा SDTX_IOCTL_LATCH_HEARTBEAT	_IO(0xa5, 0x27)
#घोषणा SDTX_IOCTL_LATCH_CANCEL		_IO(0xa5, 0x28)

#घोषणा SDTX_IOCTL_GET_BASE_INFO	_IOR(0xa5, 0x29, काष्ठा sdtx_base_info)
#घोषणा SDTX_IOCTL_GET_DEVICE_MODE	_IOR(0xa5, 0x2a, __u16)
#घोषणा SDTX_IOCTL_GET_LATCH_STATUS	_IOR(0xa5, 0x2b, __u16)

#पूर्ण_अगर /* _UAPI_LINUX_SURFACE_AGGREGATOR_DTX_H */
