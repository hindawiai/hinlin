<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * SH version cribbed from the MIPS copy:
 *
 * Copyright (C) 2003, 2004 Ralf Baechle
 */
#अगर_अघोषित __MACH_COMMON_MANGLE_PORT_H
#घोषणा __MACH_COMMON_MANGLE_PORT_H

/*
 * Sane hardware offers swapping of PCI/ISA I/O space accesses in hardware;
 * less sane hardware क्रमces software to fiddle with this...
 *
 * Regardless, अगर the host bus endianness mismatches that of PCI/ISA, then
 * you can't have the numerical value of data and byte addresses within
 * multibyte quantities both preserved at the same समय.  Hence two
 * variations of functions: non-prefixed ones that preserve the value
 * and prefixed ones that preserve byte addresses.  The latters are
 * typically used क्रम moving raw data between a peripheral and memory (cf.
 * string I/O functions), hence the "__mem_" prefix.
 */
#अगर defined(CONFIG_SWAP_IO_SPACE)

# define ioswabb(x)		(x)
# define __mem_ioswabb(x)	(x)
# define ioswabw(x)		le16_to_cpu(x)
# define __mem_ioswabw(x)	(x)
# define ioswabl(x)		le32_to_cpu(x)
# define __mem_ioswabl(x)	(x)
# define ioswabq(x)		le64_to_cpu(x)
# define __mem_ioswabq(x)	(x)

#अन्यथा

# define ioswabb(x)		(x)
# define __mem_ioswabb(x)	(x)
# define ioswabw(x)		(x)
# define __mem_ioswabw(x)	cpu_to_le16(x)
# define ioswabl(x)		(x)
# define __mem_ioswabl(x)	cpu_to_le32(x)
# define ioswabq(x)		(x)
# define __mem_ioswabq(x)	cpu_to_le32(x)

#पूर्ण_अगर

#पूर्ण_अगर /* __MACH_COMMON_MANGLE_PORT_H */
