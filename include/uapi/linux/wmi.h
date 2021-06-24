<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only WITH Linux-syscall-note */
/*
 *  User API methods क्रम ACPI-WMI mapping driver
 *
 *  Copyright (C) 2017 Dell, Inc.
 */
#अगर_अघोषित _UAPI_LINUX_WMI_H
#घोषणा _UAPI_LINUX_WMI_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/* WMI bus will filter all WMI venकरोr driver requests through this IOC */
#घोषणा WMI_IOC 'W'

/* All ioctl requests through WMI should declare their size followed by
 * relevant data objects
 */
काष्ठा wmi_ioctl_buffer अणु
	__u64	length;
	__u8	data[];
पूर्ण;

/* This काष्ठाure may be modअगरied by the firmware when we enter
 * प्रणाली management mode through SMM, hence the अस्थिरs
 */
काष्ठा calling_पूर्णांकerface_buffer अणु
	__u16 cmd_class;
	__u16 cmd_select;
	अस्थिर __u32 input[4];
	अस्थिर __u32 output[4];
पूर्ण __packed;

काष्ठा dell_wmi_extensions अणु
	__u32 argattrib;
	__u32 blength;
	__u8 data[];
पूर्ण __packed;

काष्ठा dell_wmi_smbios_buffer अणु
	__u64 length;
	काष्ठा calling_पूर्णांकerface_buffer std;
	काष्ठा dell_wmi_extensions	ext;
पूर्ण __packed;

/* Whitelisted smbios class/select commands */
#घोषणा CLASS_TOKEN_READ	0
#घोषणा CLASS_TOKEN_WRITE	1
#घोषणा SELECT_TOKEN_STD	0
#घोषणा SELECT_TOKEN_BAT	1
#घोषणा SELECT_TOKEN_AC		2
#घोषणा CLASS_FLASH_INTERFACE	7
#घोषणा SELECT_FLASH_INTERFACE	3
#घोषणा CLASS_ADMIN_PROP	10
#घोषणा SELECT_ADMIN_PROP	3
#घोषणा CLASS_INFO		17
#घोषणा SELECT_RFKILL		11
#घोषणा SELECT_APP_REGISTRATION	3
#घोषणा SELECT_DOCK		22

/* whitelisted tokens */
#घोषणा CAPSULE_EN_TOKEN	0x0461
#घोषणा CAPSULE_DIS_TOKEN	0x0462
#घोषणा WSMT_EN_TOKEN		0x04EC
#घोषणा WSMT_DIS_TOKEN		0x04ED

/* Dell SMBIOS calling IOCTL command used by dell-smbios-wmi */
#घोषणा DELL_WMI_SMBIOS_CMD	_IOWR(WMI_IOC, 0, काष्ठा dell_wmi_smbios_buffer)

#पूर्ण_अगर
