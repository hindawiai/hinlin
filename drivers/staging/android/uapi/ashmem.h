<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Apache-2.0 */
/*
 * Copyright 2008 Google Inc.
 * Author: Robert Love
 */

#अगर_अघोषित _UAPI_LINUX_ASHMEM_H
#घोषणा _UAPI_LINUX_ASHMEM_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा ASHMEM_NAME_LEN		256

#घोषणा ASHMEM_NAME_DEF		"dev/ashmem"

/* Return values from ASHMEM_PIN: Was the mapping purged जबतक unpinned? */
#घोषणा ASHMEM_NOT_PURGED	0
#घोषणा ASHMEM_WAS_PURGED	1

/* Return values from ASHMEM_GET_PIN_STATUS: Is the mapping pinned? */
#घोषणा ASHMEM_IS_UNPINNED	0
#घोषणा ASHMEM_IS_PINNED	1

काष्ठा ashmem_pin अणु
	__u32 offset;	/* offset पूर्णांकo region, in bytes, page-aligned */
	__u32 len;	/* length क्रमward from offset, in bytes, page-aligned */
पूर्ण;

#घोषणा __ASHMEMIOC		0x77

#घोषणा ASHMEM_SET_NAME		_IOW(__ASHMEMIOC, 1, अक्षर[ASHMEM_NAME_LEN])
#घोषणा ASHMEM_GET_NAME		_IOR(__ASHMEMIOC, 2, अक्षर[ASHMEM_NAME_LEN])
#घोषणा ASHMEM_SET_SIZE		_IOW(__ASHMEMIOC, 3, माप_प्रकार)
#घोषणा ASHMEM_GET_SIZE		_IO(__ASHMEMIOC, 4)
#घोषणा ASHMEM_SET_PROT_MASK	_IOW(__ASHMEMIOC, 5, अचिन्हित दीर्घ)
#घोषणा ASHMEM_GET_PROT_MASK	_IO(__ASHMEMIOC, 6)
#घोषणा ASHMEM_PIN		_IOW(__ASHMEMIOC, 7, काष्ठा ashmem_pin)
#घोषणा ASHMEM_UNPIN		_IOW(__ASHMEMIOC, 8, काष्ठा ashmem_pin)
#घोषणा ASHMEM_GET_PIN_STATUS	_IO(__ASHMEMIOC, 9)
#घोषणा ASHMEM_PURGE_ALL_CACHES	_IO(__ASHMEMIOC, 10)

#पूर्ण_अगर	/* _UAPI_LINUX_ASHMEM_H */
