<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम the VTPM proxy driver
 * Copyright (c) 2015, 2016, IBM Corporation
 * Copyright (C) 2016 Intel Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _UAPI_LINUX_VTPM_PROXY_H
#घोषणा _UAPI_LINUX_VTPM_PROXY_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/**
 * क्रमागत vtpm_proxy_flags - flags क्रम the proxy TPM
 * @VTPM_PROXY_FLAG_TPM2:	the proxy TPM uses TPM 2.0 protocol
 */
क्रमागत vtpm_proxy_flags अणु
	VTPM_PROXY_FLAG_TPM2	= 1,
पूर्ण;

/**
 * काष्ठा vtpm_proxy_new_dev - parameter काष्ठाure क्रम the
 *                             %VTPM_PROXY_IOC_NEW_DEV ioctl
 * @flags:	flags क्रम the proxy TPM
 * @tpm_num:	index of the TPM device
 * @fd:		the file descriptor used by the proxy TPM
 * @major:	the major number of the TPM device
 * @minor:	the minor number of the TPM device
 */
काष्ठा vtpm_proxy_new_dev अणु
	__u32 flags;         /* input */
	__u32 tpm_num;       /* output */
	__u32 fd;            /* output */
	__u32 major;         /* output */
	__u32 minor;         /* output */
पूर्ण;

#घोषणा VTPM_PROXY_IOC_NEW_DEV	_IOWR(0xa1, 0x00, काष्ठा vtpm_proxy_new_dev)

/* venकरोr specअगरic commands to set locality */
#घोषणा TPM2_CC_SET_LOCALITY	0x20001000
#घोषणा TPM_ORD_SET_LOCALITY	0x20001000

#पूर्ण_अगर /* _UAPI_LINUX_VTPM_PROXY_H */
