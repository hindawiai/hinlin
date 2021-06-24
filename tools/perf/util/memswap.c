<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <byteswap.h>
#समावेश "memswap.h"
#समावेश <linux/types.h>

व्योम mem_bswap_32(व्योम *src, पूर्णांक byte_size)
अणु
	u32 *m = src;
	जबतक (byte_size > 0) अणु
		*m = bswap_32(*m);
		byte_size -= माप(u32);
		++m;
	पूर्ण
पूर्ण

व्योम mem_bswap_64(व्योम *src, पूर्णांक byte_size)
अणु
	u64 *m = src;

	जबतक (byte_size > 0) अणु
		*m = bswap_64(*m);
		byte_size -= माप(u64);
		++m;
	पूर्ण
पूर्ण
