<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Greybus Component Authentication User Header
 *
 * Copyright(c) 2016 Google Inc. All rights reserved.
 * Copyright(c) 2016 Linaro Ltd. All rights reserved.
 */

#अगर_अघोषित __GREYBUS_AUTHENTICATION_USER_H
#घोषणा __GREYBUS_AUTHENTICATION_USER_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा CAP_CERTIFICATE_MAX_SIZE	1600
#घोषणा CAP_SIGNATURE_MAX_SIZE		320

/* Certअगरicate class types */
#घोषणा CAP_CERT_IMS_EAPC		0x00000001
#घोषणा CAP_CERT_IMS_EASC		0x00000002
#घोषणा CAP_CERT_IMS_EARC		0x00000003
#घोषणा CAP_CERT_IMS_IAPC		0x00000004
#घोषणा CAP_CERT_IMS_IASC		0x00000005
#घोषणा CAP_CERT_IMS_IARC		0x00000006

/* IMS Certअगरicate response result codes */
#घोषणा CAP_IMS_RESULT_CERT_FOUND	0x00
#घोषणा CAP_IMS_RESULT_CERT_CLASS_INVAL	0x01
#घोषणा CAP_IMS_RESULT_CERT_CORRUPT	0x02
#घोषणा CAP_IMS_RESULT_CERT_NOT_FOUND	0x03

/* Authentication types */
#घोषणा CAP_AUTH_IMS_PRI		0x00000001
#घोषणा CAP_AUTH_IMS_SEC		0x00000002
#घोषणा CAP_AUTH_IMS_RSA		0x00000003

/* Authenticate response result codes */
#घोषणा CAP_AUTH_RESULT_CR_SUCCESS	0x00
#घोषणा CAP_AUTH_RESULT_CR_BAD_TYPE	0x01
#घोषणा CAP_AUTH_RESULT_CR_WRONG_EP	0x02
#घोषणा CAP_AUTH_RESULT_CR_NO_KEY	0x03
#घोषणा CAP_AUTH_RESULT_CR_SIG_FAIL	0x04


/* IOCTL support */
काष्ठा cap_ioc_get_endpoपूर्णांक_uid अणु
	__u8			uid[8];
पूर्ण __attribute__ ((__packed__));

काष्ठा cap_ioc_get_ims_certअगरicate अणु
	__u32			certअगरicate_class;
	__u32			certअगरicate_id;

	__u8			result_code;
	__u32			cert_size;
	__u8			certअगरicate[CAP_CERTIFICATE_MAX_SIZE];
पूर्ण __attribute__ ((__packed__));

काष्ठा cap_ioc_authenticate अणु
	__u32			auth_type;
	__u8			uid[8];
	__u8			challenge[32];

	__u8			result_code;
	__u8			response[64];
	__u32			signature_size;
	__u8			signature[CAP_SIGNATURE_MAX_SIZE];
पूर्ण __attribute__ ((__packed__));

#घोषणा CAP_IOCTL_BASE			'C'
#घोषणा CAP_IOC_GET_ENDPOINT_UID	_IOR(CAP_IOCTL_BASE, 0, काष्ठा cap_ioc_get_endpoपूर्णांक_uid)
#घोषणा CAP_IOC_GET_IMS_CERTIFICATE	_IOWR(CAP_IOCTL_BASE, 1, काष्ठा cap_ioc_get_ims_certअगरicate)
#घोषणा CAP_IOC_AUTHENTICATE		_IOWR(CAP_IOCTL_BASE, 2, काष्ठा cap_ioc_authenticate)

#पूर्ण_अगर /* __GREYBUS_AUTHENTICATION_USER_H */
