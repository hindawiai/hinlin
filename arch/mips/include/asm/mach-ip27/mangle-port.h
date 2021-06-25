<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_IP27_MANGLE_PORT_H
#घोषणा __ASM_MACH_IP27_MANGLE_PORT_H

#घोषणा __swizzle_addr_b(port)	((port) ^ 3)
#घोषणा __swizzle_addr_w(port)	((port) ^ 2)
#घोषणा __swizzle_addr_l(port)	(port)
#घोषणा __swizzle_addr_q(port)	(port)

# define ioswabb(a, x)		(x)
# define __mem_ioswabb(a, x)	(x)
# define ioswabw(a, x)		(x)
# define __mem_ioswabw(a, x)	((__क्रमce u16)cpu_to_le16(x))
# define ioswabl(a, x)		(x)
# define __mem_ioswabl(a, x)	((__क्रमce u32)cpu_to_le32(x))
# define ioswabq(a, x)		(x)
# define __mem_ioswabq(a, x)	((__क्रमce u64)cpu_to_le64(x))

#पूर्ण_अगर /* __ASM_MACH_IP27_MANGLE_PORT_H */
