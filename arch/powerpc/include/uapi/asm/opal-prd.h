<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * OPAL Runसमय Diagnostics पूर्णांकerface driver
 * Supported on POWERNV platक्रमm
 *
 * (C) Copyright IBM 2015
 *
 * Author: Vaidyanathan Srinivasan <svaidy at linux.vnet.ibm.com>
 * Author: Jeremy Kerr <jk@ozद_असल.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _UAPI_ASM_POWERPC_OPAL_PRD_H_
#घोषणा _UAPI_ASM_POWERPC_OPAL_PRD_H_

#समावेश <linux/types.h>

/**
 * The version of the kernel पूर्णांकerface of the PRD प्रणाली. This describes the
 * पूर्णांकerface available क्रम the /dev/opal-prd device. The actual PRD message
 * layout and content is निजी to the firmware <--> userspace पूर्णांकerface, so
 * is not covered by this versioning.
 *
 * Future पूर्णांकerface versions are backwards-compatible; अगर a later kernel
 * version is encountered, functionality provided in earlier versions
 * will work.
 */
#घोषणा OPAL_PRD_KERNEL_VERSION		1

#घोषणा OPAL_PRD_GET_INFO		_IOR('o', 0x01, काष्ठा opal_prd_info)
#घोषणा OPAL_PRD_SCOM_READ		_IOR('o', 0x02, काष्ठा opal_prd_scom)
#घोषणा OPAL_PRD_SCOM_WRITE		_IOW('o', 0x03, काष्ठा opal_prd_scom)

#अगर_अघोषित __ASSEMBLY__

काष्ठा opal_prd_info अणु
	__u64	version;
	__u64	reserved[3];
पूर्ण;

काष्ठा opal_prd_scom अणु
	__u64	chip;
	__u64	addr;
	__u64	data;
	__s64	rc;
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _UAPI_ASM_POWERPC_OPAL_PRD_H */
