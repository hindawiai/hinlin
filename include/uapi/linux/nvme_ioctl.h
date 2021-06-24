<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम the NVM Express ioctl पूर्णांकerface
 * Copyright (c) 2011-2014, Intel Corporation.
 */

#अगर_अघोषित _UAPI_LINUX_NVME_IOCTL_H
#घोषणा _UAPI_LINUX_NVME_IOCTL_H

#समावेश <linux/types.h>

काष्ठा nvme_user_io अणु
	__u8	opcode;
	__u8	flags;
	__u16	control;
	__u16	nblocks;
	__u16	rsvd;
	__u64	metadata;
	__u64	addr;
	__u64	slba;
	__u32	dsmgmt;
	__u32	reftag;
	__u16	apptag;
	__u16	appmask;
पूर्ण;

काष्ठा nvme_passthru_cmd अणु
	__u8	opcode;
	__u8	flags;
	__u16	rsvd1;
	__u32	nsid;
	__u32	cdw2;
	__u32	cdw3;
	__u64	metadata;
	__u64	addr;
	__u32	metadata_len;
	__u32	data_len;
	__u32	cdw10;
	__u32	cdw11;
	__u32	cdw12;
	__u32	cdw13;
	__u32	cdw14;
	__u32	cdw15;
	__u32	समयout_ms;
	__u32	result;
पूर्ण;

काष्ठा nvme_passthru_cmd64 अणु
	__u8	opcode;
	__u8	flags;
	__u16	rsvd1;
	__u32	nsid;
	__u32	cdw2;
	__u32	cdw3;
	__u64	metadata;
	__u64	addr;
	__u32	metadata_len;
	__u32	data_len;
	__u32	cdw10;
	__u32	cdw11;
	__u32	cdw12;
	__u32	cdw13;
	__u32	cdw14;
	__u32	cdw15;
	__u32	समयout_ms;
	__u32   rsvd2;
	__u64	result;
पूर्ण;

#घोषणा nvme_admin_cmd nvme_passthru_cmd

#घोषणा NVME_IOCTL_ID		_IO('N', 0x40)
#घोषणा NVME_IOCTL_ADMIN_CMD	_IOWR('N', 0x41, काष्ठा nvme_admin_cmd)
#घोषणा NVME_IOCTL_SUBMIT_IO	_IOW('N', 0x42, काष्ठा nvme_user_io)
#घोषणा NVME_IOCTL_IO_CMD	_IOWR('N', 0x43, काष्ठा nvme_passthru_cmd)
#घोषणा NVME_IOCTL_RESET	_IO('N', 0x44)
#घोषणा NVME_IOCTL_SUBSYS_RESET	_IO('N', 0x45)
#घोषणा NVME_IOCTL_RESCAN	_IO('N', 0x46)
#घोषणा NVME_IOCTL_ADMIN64_CMD	_IOWR('N', 0x47, काष्ठा nvme_passthru_cmd64)
#घोषणा NVME_IOCTL_IO64_CMD	_IOWR('N', 0x48, काष्ठा nvme_passthru_cmd64)

#पूर्ण_अगर /* _UAPI_LINUX_NVME_IOCTL_H */
