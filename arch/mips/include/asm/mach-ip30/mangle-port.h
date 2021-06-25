<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2003, 2004 Ralf Baechle
 */
#अगर_अघोषित __ASM_MACH_IP30_MANGLE_PORT_H
#घोषणा __ASM_MACH_IP30_MANGLE_PORT_H

#घोषणा __swizzle_addr_b(port)	((port)^3)
#घोषणा __swizzle_addr_w(port)	((port)^2)
#घोषणा __swizzle_addr_l(port)	(port)
#घोषणा __swizzle_addr_q(port)	(port)

#घोषणा ioswabb(a, x)		(x)
#घोषणा __mem_ioswabb(a, x)	(x)
#घोषणा ioswabw(a, x)		(x)
#घोषणा __mem_ioswabw(a, x)	((__क्रमce u16)cpu_to_le16(x))
#घोषणा ioswabl(a, x)		(x)
#घोषणा __mem_ioswabl(a, x)	((__क्रमce u32)cpu_to_le32(x))
#घोषणा ioswabq(a, x)		(x)
#घोषणा __mem_ioswabq(a, x)	((__क्रमce u64)cpu_to_le64(x))

#पूर्ण_अगर /* __ASM_MACH_IP30_MANGLE_PORT_H */
