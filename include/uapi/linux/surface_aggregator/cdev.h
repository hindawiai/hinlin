<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Surface System Aggregator Module (SSAM) user-space EC पूर्णांकerface.
 *
 * Definitions, काष्ठाs, and IOCTLs क्रम the /dev/surface/aggregator misc
 * device. This device provides direct user-space access to the SSAM EC.
 * Intended क्रम debugging and development.
 *
 * Copyright (C) 2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H
#घोषणा _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/**
 * क्रमागत ssam_cdev_request_flags - Request flags क्रम SSAM cdev request IOCTL.
 *
 * @SSAM_CDEV_REQUEST_HAS_RESPONSE:
 *	Specअगरies that the request expects a response. If not set, the request
 *	will be directly completed after its underlying packet has been
 *	transmitted. If set, the request transport प्रणाली रुकोs क्रम a response
 *	of the request.
 *
 * @SSAM_CDEV_REQUEST_UNSEQUENCED:
 *	Specअगरies that the request should be transmitted via an unsequenced
 *	packet. If set, the request must not have a response, meaning that this
 *	flag and the %SSAM_CDEV_REQUEST_HAS_RESPONSE flag are mutually
 *	exclusive.
 */
क्रमागत ssam_cdev_request_flags अणु
	SSAM_CDEV_REQUEST_HAS_RESPONSE = 0x01,
	SSAM_CDEV_REQUEST_UNSEQUENCED  = 0x02,
पूर्ण;

/**
 * काष्ठा ssam_cdev_request - Controller request IOCTL argument.
 * @target_category: Target category of the SAM request.
 * @target_id:       Target ID of the SAM request.
 * @command_id:      Command ID of the SAM request.
 * @instance_id:     Instance ID of the SAM request.
 * @flags:           Request flags (see &क्रमागत ssam_cdev_request_flags).
 * @status:          Request status (output).
 * @payload:         Request payload (input data).
 * @payload.data:    Poपूर्णांकer to request payload data.
 * @payload.length:  Length of request payload data (in bytes).
 * @response:        Request response (output data).
 * @response.data:   Poपूर्णांकer to response buffer.
 * @response.length: On input: Capacity of response buffer (in bytes).
 *                   On output: Length of request response (number of bytes
 *                   in the buffer that are actually used).
 */
काष्ठा ssam_cdev_request अणु
	__u8 target_category;
	__u8 target_id;
	__u8 command_id;
	__u8 instance_id;
	__u16 flags;
	__s16 status;

	काष्ठा अणु
		__u64 data;
		__u16 length;
		__u8 __pad[6];
	पूर्ण payload;

	काष्ठा अणु
		__u64 data;
		__u16 length;
		__u8 __pad[6];
	पूर्ण response;
पूर्ण __attribute__((__packed__));

#घोषणा SSAM_CDEV_REQUEST	_IOWR(0xA5, 1, काष्ठा ssam_cdev_request)

#पूर्ण_अगर /* _UAPI_LINUX_SURFACE_AGGREGATOR_CDEV_H */
