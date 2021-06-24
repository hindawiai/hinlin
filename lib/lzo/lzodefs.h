<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  lzodefs.h -- architecture, OS and compiler specअगरic defines
 *
 *  Copyright (C) 1996-2012 Markus F.X.J. Oberhumer <markus@oberhumer.com>
 *
 *  The full LZO package can be found at:
 *  http://www.oberhumer.com/खोलोsource/lzo/
 *
 *  Changed क्रम Linux kernel use by:
 *  Nitin Gupta <nitingupta910@gmail.com>
 *  Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */


/* Version
 * 0: original lzo version
 * 1: lzo with support क्रम RLE
 */
#घोषणा LZO_VERSION 1

#घोषणा COPY4(dst, src)	\
		put_unaligned(get_unaligned((स्थिर u32 *)(src)), (u32 *)(dst))
#अगर defined(CONFIG_X86_64) || defined(CONFIG_ARM64)
#घोषणा COPY8(dst, src)	\
		put_unaligned(get_unaligned((स्थिर u64 *)(src)), (u64 *)(dst))
#अन्यथा
#घोषणा COPY8(dst, src)	\
		COPY4(dst, src); COPY4((dst) + 4, (src) + 4)
#पूर्ण_अगर

#अगर defined(__BIG_ENDIAN) && defined(__LITTLE_ENDIAN)
#त्रुटि "conflicting endian definitions"
#या_अगर defined(CONFIG_X86_64) || defined(CONFIG_ARM64)
#घोषणा LZO_USE_CTZ64	1
#घोषणा LZO_USE_CTZ32	1
#घोषणा LZO_FAST_64BIT_MEMORY_ACCESS
#या_अगर defined(CONFIG_X86) || defined(CONFIG_PPC)
#घोषणा LZO_USE_CTZ32	1
#या_अगर defined(CONFIG_ARM) && (__LINUX_ARM_ARCH__ >= 5)
#घोषणा LZO_USE_CTZ32	1
#पूर्ण_अगर

#घोषणा M1_MAX_OFFSET	0x0400
#घोषणा M2_MAX_OFFSET	0x0800
#घोषणा M3_MAX_OFFSET	0x4000
#घोषणा M4_MAX_OFFSET_V0	0xbfff
#घोषणा M4_MAX_OFFSET_V1	0xbffe

#घोषणा M1_MIN_LEN	2
#घोषणा M1_MAX_LEN	2
#घोषणा M2_MIN_LEN	3
#घोषणा M2_MAX_LEN	8
#घोषणा M3_MIN_LEN	3
#घोषणा M3_MAX_LEN	33
#घोषणा M4_MIN_LEN	3
#घोषणा M4_MAX_LEN	9

#घोषणा M1_MARKER	0
#घोषणा M2_MARKER	64
#घोषणा M3_MARKER	32
#घोषणा M4_MARKER	16

#घोषणा MIN_ZERO_RUN_LENGTH	4
#घोषणा MAX_ZERO_RUN_LENGTH	(2047 + MIN_ZERO_RUN_LENGTH)

#घोषणा lzo_dict_t      अचिन्हित लघु
#घोषणा D_BITS		13
#घोषणा D_SIZE		(1u << D_BITS)
#घोषणा D_MASK		(D_SIZE - 1)
#घोषणा D_HIGH		((D_MASK >> 1) + 1)
