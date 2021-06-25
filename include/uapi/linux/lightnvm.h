<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2015 CNEX Lअसल.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139,
 * USA.
 */

#अगर_अघोषित _UAPI_LINUX_LIGHTNVM_H
#घोषणा _UAPI_LINUX_LIGHTNVM_H

#अगर_घोषित __KERNEL__
#समावेश <linux/स्थिर.h>
#अन्यथा /* __KERNEL__ */
#समावेश <मानकपन.स>
#समावेश <sys/ioctl.h>
#घोषणा DISK_NAME_LEN 32
#पूर्ण_अगर /* __KERNEL__ */

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा NVM_TTYPE_NAME_MAX 48
#घोषणा NVM_TTYPE_MAX 63
#घोषणा NVM_MMTYPE_LEN 8

#घोषणा NVM_CTRL_खाता "/dev/lightnvm/control"

काष्ठा nvm_ioctl_info_tgt अणु
	__u32 version[3];
	__u32 reserved;
	अक्षर tgtname[NVM_TTYPE_NAME_MAX];
पूर्ण;

काष्ठा nvm_ioctl_info अणु
	__u32 version[3];	/* in/out - major, minor, patch */
	__u16 tgtsize;		/* number of tarमाला_लो */
	__u16 reserved16;	/* pad to 4K page */
	__u32 reserved[12];
	काष्ठा nvm_ioctl_info_tgt tgts[NVM_TTYPE_MAX];
पूर्ण;

क्रमागत अणु
	NVM_DEVICE_ACTIVE = 1 << 0,
पूर्ण;

काष्ठा nvm_ioctl_device_info अणु
	अक्षर devname[DISK_NAME_LEN];
	अक्षर bmname[NVM_TTYPE_NAME_MAX];
	__u32 bmversion[3];
	__u32 flags;
	__u32 reserved[8];
पूर्ण;

काष्ठा nvm_ioctl_get_devices अणु
	__u32 nr_devices;
	__u32 reserved[31];
	काष्ठा nvm_ioctl_device_info info[31];
पूर्ण;

काष्ठा nvm_ioctl_create_simple अणु
	__u32 lun_begin;
	__u32 lun_end;
पूर्ण;

काष्ठा nvm_ioctl_create_extended अणु
	__u16 lun_begin;
	__u16 lun_end;
	__u16 op;
	__u16 rsv;
पूर्ण;

क्रमागत अणु
	NVM_CONFIG_TYPE_SIMPLE = 0,
	NVM_CONFIG_TYPE_EXTENDED = 1,
पूर्ण;

काष्ठा nvm_ioctl_create_conf अणु
	__u32 type;
	जोड़ अणु
		काष्ठा nvm_ioctl_create_simple s;
		काष्ठा nvm_ioctl_create_extended e;
	पूर्ण;
पूर्ण;

क्रमागत अणु
	NVM_TARGET_FACTORY = 1 << 0,	/* Init target in factory mode */
पूर्ण;

काष्ठा nvm_ioctl_create अणु
	अक्षर dev[DISK_NAME_LEN];		/* खोलो-channel SSD device */
	अक्षर tgttype[NVM_TTYPE_NAME_MAX];	/* target type name */
	अक्षर tgtname[DISK_NAME_LEN];		/* dev to expose target as */

	__u32 flags;

	काष्ठा nvm_ioctl_create_conf conf;
पूर्ण;

काष्ठा nvm_ioctl_हटाओ अणु
	अक्षर tgtname[DISK_NAME_LEN];

	__u32 flags;
पूर्ण;

काष्ठा nvm_ioctl_dev_init अणु
	अक्षर dev[DISK_NAME_LEN];		/* खोलो-channel SSD device */
	अक्षर mmtype[NVM_MMTYPE_LEN];		/* रेजिस्टर to media manager */

	__u32 flags;
पूर्ण;

क्रमागत अणु
	NVM_FACTORY_ERASE_ONLY_USER	= 1 << 0, /* erase only blocks used as
						   * host blks or grown blks */
	NVM_FACTORY_RESET_HOST_BLKS	= 1 << 1, /* हटाओ host blk marks */
	NVM_FACTORY_RESET_GRWN_BBLKS	= 1 << 2, /* हटाओ grown blk marks */
	NVM_FACTORY_NR_BITS		= 1 << 3, /* stops here */
पूर्ण;

काष्ठा nvm_ioctl_dev_factory अणु
	अक्षर dev[DISK_NAME_LEN];

	__u32 flags;
पूर्ण;

काष्ठा nvm_user_vio अणु
	__u8 opcode;
	__u8 flags;
	__u16 control;
	__u16 nppas;
	__u16 rsvd;
	__u64 metadata;
	__u64 addr;
	__u64 ppa_list;
	__u32 metadata_len;
	__u32 data_len;
	__u64 status;
	__u32 result;
	__u32 rsvd3[3];
पूर्ण;

काष्ठा nvm_passthru_vio अणु
	__u8 opcode;
	__u8 flags;
	__u8 rsvd[2];
	__u32 nsid;
	__u32 cdw2;
	__u32 cdw3;
	__u64 metadata;
	__u64 addr;
	__u32 metadata_len;
	__u32 data_len;
	__u64 ppa_list;
	__u16 nppas;
	__u16 control;
	__u32 cdw13;
	__u32 cdw14;
	__u32 cdw15;
	__u64 status;
	__u32 result;
	__u32 समयout_ms;
पूर्ण;

/* The ioctl type, 'L', 0x20 - 0x2F करोcumented in ioctl-number.txt */
क्रमागत अणु
	/* top level cmds */
	NVM_INFO_CMD = 0x20,
	NVM_GET_DEVICES_CMD,

	/* device level cmds */
	NVM_DEV_CREATE_CMD,
	NVM_DEV_REMOVE_CMD,

	/* Init a device to support LightNVM media managers */
	NVM_DEV_INIT_CMD,

	/* Factory reset device */
	NVM_DEV_FACTORY_CMD,

	/* Vector user I/O */
	NVM_DEV_VIO_ADMIN_CMD = 0x41,
	NVM_DEV_VIO_CMD = 0x42,
	NVM_DEV_VIO_USER_CMD = 0x43,
पूर्ण;

#घोषणा NVM_IOCTL 'L' /* 0x4c */

#घोषणा NVM_INFO		_IOWR(NVM_IOCTL, NVM_INFO_CMD, \
						काष्ठा nvm_ioctl_info)
#घोषणा NVM_GET_DEVICES		_IOR(NVM_IOCTL, NVM_GET_DEVICES_CMD, \
						काष्ठा nvm_ioctl_get_devices)
#घोषणा NVM_DEV_CREATE		_IOW(NVM_IOCTL, NVM_DEV_CREATE_CMD, \
						काष्ठा nvm_ioctl_create)
#घोषणा NVM_DEV_REMOVE		_IOW(NVM_IOCTL, NVM_DEV_REMOVE_CMD, \
						काष्ठा nvm_ioctl_हटाओ)
#घोषणा NVM_DEV_INIT		_IOW(NVM_IOCTL, NVM_DEV_INIT_CMD, \
						काष्ठा nvm_ioctl_dev_init)
#घोषणा NVM_DEV_FACTORY		_IOW(NVM_IOCTL, NVM_DEV_FACTORY_CMD, \
						काष्ठा nvm_ioctl_dev_factory)

#घोषणा NVME_NVM_IOCTL_IO_VIO		_IOWR(NVM_IOCTL, NVM_DEV_VIO_USER_CMD, \
						काष्ठा nvm_passthru_vio)
#घोषणा NVME_NVM_IOCTL_ADMIN_VIO	_IOWR(NVM_IOCTL, NVM_DEV_VIO_ADMIN_CMD,\
						काष्ठा nvm_passthru_vio)
#घोषणा NVME_NVM_IOCTL_SUBMIT_VIO	_IOWR(NVM_IOCTL, NVM_DEV_VIO_CMD,\
						काष्ठा nvm_user_vio)

#घोषणा NVM_VERSION_MAJOR	1
#घोषणा NVM_VERSION_MINOR	0
#घोषणा NVM_VERSION_PATCHLEVEL	0

#पूर्ण_अगर
