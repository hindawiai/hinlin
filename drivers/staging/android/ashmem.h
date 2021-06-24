<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Apache-2.0 */
/*
 * include/linux/ashस्मृति.स
 *
 * Copyright 2008 Google Inc.
 * Author: Robert Love
 */

#अगर_अघोषित _LINUX_ASHMEM_H
#घोषणा _LINUX_ASHMEM_H

#समावेश <linux/सीमा.स>
#समावेश <linux/ioctl.h>
#समावेश <linux/compat.h>

#समावेश "uapi/ashmem.h"

/* support of 32bit userspace on 64bit platक्रमms */
#अगर_घोषित CONFIG_COMPAT
#घोषणा COMPAT_ASHMEM_SET_SIZE		_IOW(__ASHMEMIOC, 3, compat_माप_प्रकार)
#घोषणा COMPAT_ASHMEM_SET_PROT_MASK	_IOW(__ASHMEMIOC, 5, अचिन्हित पूर्णांक)
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_ASHMEM_H */
