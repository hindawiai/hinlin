<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_GENERIC_MANGLE_PORT_H
#घोषणा __ASM_MACH_GENERIC_MANGLE_PORT_H

#समावेश <यंत्र/byteorder.h>

#अगर_घोषित __BIG_ENDIAN

अटल अंतरभूत bool __should_swizzle_bits(अस्थिर व्योम *a)
अणु
	बाह्य स्थिर bool octeon_should_swizzle_table[];
	u64 did = ((u64)(uपूर्णांकptr_t)a >> 40) & 0xff;

	वापस octeon_should_swizzle_table[did];
पूर्ण

# define __swizzle_addr_b(port)	(port)
# define __swizzle_addr_w(port)	(port)
# define __swizzle_addr_l(port)	(port)
# define __swizzle_addr_q(port)	(port)

#अन्यथा /* __LITTLE_ENDIAN */

#घोषणा __should_swizzle_bits(a)	false

अटल अंतरभूत bool __should_swizzle_addr(u64 p)
अणु
	/* boot bus? */
	वापस ((p >> 40) & 0xff) == 0;
पूर्ण

# define __swizzle_addr_b(port)	\
	(__should_swizzle_addr(port) ? (port) ^ 7 : (port))
# define __swizzle_addr_w(port)	\
	(__should_swizzle_addr(port) ? (port) ^ 6 : (port))
# define __swizzle_addr_l(port)	\
	(__should_swizzle_addr(port) ? (port) ^ 4 : (port))
# define __swizzle_addr_q(port)	(port)

#पूर्ण_अगर /* __BIG_ENDIAN */


# define ioswabb(a, x)		(x)
# define __mem_ioswabb(a, x)	(x)
# define ioswabw(a, x)		(__should_swizzle_bits(a) ?		\
				 le16_to_cpu((__क्रमce __le16)(x)) :	\
				 (x))
# define __mem_ioswabw(a, x)	(x)
# define ioswabl(a, x)		(__should_swizzle_bits(a) ?		\
				 le32_to_cpu((__क्रमce __le32)(x)) :	\
				 (x))
# define __mem_ioswabl(a, x)	(x)
# define ioswabq(a, x)		(__should_swizzle_bits(a) ?		\
				 le64_to_cpu((__क्रमce __le64)(x)) :	\
				 (x))
# define __mem_ioswabq(a, x)	(x)

#पूर्ण_अगर /* __ASM_MACH_GENERIC_MANGLE_PORT_H */
