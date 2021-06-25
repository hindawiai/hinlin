<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_TX49XX_MANGLE_PORT_H
#घोषणा __ASM_MACH_TX49XX_MANGLE_PORT_H

#घोषणा __swizzle_addr_b(port)	(port)
#घोषणा __swizzle_addr_w(port)	(port)
#घोषणा __swizzle_addr_l(port)	(port)
#घोषणा __swizzle_addr_q(port)	(port)

#घोषणा ioswabb(a, x)		(x)
#घोषणा __mem_ioswabb(a, x)	(x)
#अगर defined(CONFIG_TOSHIBA_RBTX4939) && \
	IS_ENABLED(CONFIG_SMC91X) && \
	defined(__BIG_ENDIAN)
#घोषणा NEEDS_TXX9_IOSWABW
बाह्य u16 (*ioswabw)(अस्थिर u16 *a, u16 x);
बाह्य u16 (*__mem_ioswabw)(अस्थिर u16 *a, u16 x);
#अन्यथा
#घोषणा ioswabw(a, x)		le16_to_cpu((__क्रमce __le16)(x))
#घोषणा __mem_ioswabw(a, x)	(x)
#पूर्ण_अगर
#घोषणा ioswabl(a, x)		le32_to_cpu((__क्रमce __le32)(x))
#घोषणा __mem_ioswabl(a, x)	(x)
#घोषणा ioswabq(a, x)		le64_to_cpu((__क्रमce __le64)(x))
#घोषणा __mem_ioswabq(a, x)	(x)

#पूर्ण_अगर /* __ASM_MACH_TX49XX_MANGLE_PORT_H */
