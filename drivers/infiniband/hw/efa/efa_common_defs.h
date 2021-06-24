<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-2-Clause */
/*
 * Copyright 2018-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */

#अगर_अघोषित _EFA_COMMON_H_
#घोषणा _EFA_COMMON_H_

#समावेश <linux/bitfield.h>

#घोषणा EFA_COMMON_SPEC_VERSION_MAJOR        2
#घोषणा EFA_COMMON_SPEC_VERSION_MINOR        0

#घोषणा EFA_GET(ptr, mask) FIELD_GET(mask##_MASK, *(ptr))

#घोषणा EFA_SET(ptr, mask, value)                                              \
	(अणु                                                                     \
		typeof(ptr) _ptr = ptr;                                        \
		*_ptr = (*_ptr & ~(mask##_MASK)) |                             \
			FIELD_PREP(mask##_MASK, value);                        \
	पूर्ण)

काष्ठा efa_common_mem_addr अणु
	u32 mem_addr_low;

	u32 mem_addr_high;
पूर्ण;

#पूर्ण_अगर /* _EFA_COMMON_H_ */
