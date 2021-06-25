<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#समावेश <linux/kernel.h>
#समावेश "gdm_endian.h"

__dev16 gdm_cpu_to_dev16(u8 dev_ed, u16 x)
अणु
	अगर (dev_ed == ENDIANNESS_LITTLE)
		वापस (__क्रमce __dev16)cpu_to_le16(x);
	अन्यथा
		वापस (__क्रमce __dev16)cpu_to_be16(x);
पूर्ण

u16 gdm_dev16_to_cpu(u8 dev_ed, __dev16 x)
अणु
	अगर (dev_ed == ENDIANNESS_LITTLE)
		वापस le16_to_cpu((__क्रमce __le16)x);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)x);
पूर्ण

__dev32 gdm_cpu_to_dev32(u8 dev_ed, u32 x)
अणु
	अगर (dev_ed == ENDIANNESS_LITTLE)
		वापस (__क्रमce __dev32)cpu_to_le32(x);
	अन्यथा
		वापस (__क्रमce __dev32)cpu_to_be32(x);
पूर्ण

u32 gdm_dev32_to_cpu(u8 dev_ed, __dev32 x)
अणु
	अगर (dev_ed == ENDIANNESS_LITTLE)
		वापस le32_to_cpu((__क्रमce __le32)x);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)x);
पूर्ण
