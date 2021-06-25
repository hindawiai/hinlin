<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Greybus Firmware Management User Header
 *
 * Copyright(c) 2016 Google Inc. All rights reserved.
 * Copyright(c) 2016 Linaro Ltd. All rights reserved.
 */

#अगर_अघोषित __GREYBUS_FIRMWARE_USER_H
#घोषणा __GREYBUS_FIRMWARE_USER_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा GB_FIRMWARE_U_TAG_MAX_SIZE		10

#घोषणा GB_FW_U_LOAD_METHOD_UNIPRO		0x01
#घोषणा GB_FW_U_LOAD_METHOD_INTERNAL		0x02

#घोषणा GB_FW_U_LOAD_STATUS_FAILED		0x00
#घोषणा GB_FW_U_LOAD_STATUS_UNVALIDATED		0x01
#घोषणा GB_FW_U_LOAD_STATUS_VALIDATED		0x02
#घोषणा GB_FW_U_LOAD_STATUS_VALIDATION_FAILED	0x03

#घोषणा GB_FW_U_BACKEND_FW_STATUS_SUCCESS	0x01
#घोषणा GB_FW_U_BACKEND_FW_STATUS_FAIL_FIND	0x02
#घोषणा GB_FW_U_BACKEND_FW_STATUS_FAIL_FETCH	0x03
#घोषणा GB_FW_U_BACKEND_FW_STATUS_FAIL_WRITE	0x04
#घोषणा GB_FW_U_BACKEND_FW_STATUS_INT		0x05
#घोषणा GB_FW_U_BACKEND_FW_STATUS_RETRY		0x06
#घोषणा GB_FW_U_BACKEND_FW_STATUS_NOT_SUPPORTED	0x07

#घोषणा GB_FW_U_BACKEND_VERSION_STATUS_SUCCESS		0x01
#घोषणा GB_FW_U_BACKEND_VERSION_STATUS_NOT_AVAILABLE	0x02
#घोषणा GB_FW_U_BACKEND_VERSION_STATUS_NOT_SUPPORTED	0x03
#घोषणा GB_FW_U_BACKEND_VERSION_STATUS_RETRY		0x04
#घोषणा GB_FW_U_BACKEND_VERSION_STATUS_FAIL_INT		0x05

/* IOCTL support */
काष्ठा fw_mgmt_ioc_get_पूर्णांकf_version अणु
	__u8 firmware_tag[GB_FIRMWARE_U_TAG_MAX_SIZE];
	__u16 major;
	__u16 minor;
पूर्ण __attribute__ ((__packed__));

काष्ठा fw_mgmt_ioc_get_backend_version अणु
	__u8 firmware_tag[GB_FIRMWARE_U_TAG_MAX_SIZE];
	__u16 major;
	__u16 minor;
	__u8 status;
पूर्ण __attribute__ ((__packed__));

काष्ठा fw_mgmt_ioc_पूर्णांकf_load_and_validate अणु
	__u8 firmware_tag[GB_FIRMWARE_U_TAG_MAX_SIZE];
	__u8 load_method;
	__u8 status;
	__u16 major;
	__u16 minor;
पूर्ण __attribute__ ((__packed__));

काष्ठा fw_mgmt_ioc_backend_fw_update अणु
	__u8 firmware_tag[GB_FIRMWARE_U_TAG_MAX_SIZE];
	__u8 status;
पूर्ण __attribute__ ((__packed__));

#घोषणा FW_MGMT_IOCTL_BASE			'F'
#घोषणा FW_MGMT_IOC_GET_INTF_FW			_IOR(FW_MGMT_IOCTL_BASE, 0, काष्ठा fw_mgmt_ioc_get_पूर्णांकf_version)
#घोषणा FW_MGMT_IOC_GET_BACKEND_FW		_IOWR(FW_MGMT_IOCTL_BASE, 1, काष्ठा fw_mgmt_ioc_get_backend_version)
#घोषणा FW_MGMT_IOC_INTF_LOAD_AND_VALIDATE	_IOWR(FW_MGMT_IOCTL_BASE, 2, काष्ठा fw_mgmt_ioc_पूर्णांकf_load_and_validate)
#घोषणा FW_MGMT_IOC_INTF_BACKEND_FW_UPDATE	_IOWR(FW_MGMT_IOCTL_BASE, 3, काष्ठा fw_mgmt_ioc_backend_fw_update)
#घोषणा FW_MGMT_IOC_SET_TIMEOUT_MS		_IOW(FW_MGMT_IOCTL_BASE, 4, अचिन्हित पूर्णांक)
#घोषणा FW_MGMT_IOC_MODE_SWITCH			_IO(FW_MGMT_IOCTL_BASE, 5)

#पूर्ण_अगर /* __GREYBUS_FIRMWARE_USER_H */

