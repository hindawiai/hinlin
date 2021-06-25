<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_TX39XX_MANGLE_PORT_H
#घोषणा __ASM_MACH_TX39XX_MANGLE_PORT_H

#अगर defined(CONFIG_TOSHIBA_JMR3927)
बाह्य अचिन्हित दीर्घ (*__swizzle_addr_b)(अचिन्हित दीर्घ port);
#घोषणा NEEDS_TXX9_SWIZZLE_ADDR_B
#अन्यथा
#घोषणा __swizzle_addr_b(port)	(port)
#पूर्ण_अगर
#घोषणा __swizzle_addr_w(port)	(port)
#घोषणा __swizzle_addr_l(port)	(port)
#घोषणा __swizzle_addr_q(port)	(port)

#घोषणा ioswabb(a, x)		(x)
#घोषणा __mem_ioswabb(a, x)	(x)
#घोषणा ioswabw(a, x)		le16_to_cpu((__क्रमce __le16)(x))
#घोषणा __mem_ioswabw(a, x)	(x)
#घोषणा ioswabl(a, x)		le32_to_cpu((__क्रमce __le32)(x))
#घोषणा __mem_ioswabl(a, x)	(x)
#घोषणा ioswabq(a, x)		le64_to_cpu((__क्रमce __le64)(x))
#घोषणा __mem_ioswabq(a, x)	(x)

#पूर्ण_अगर /* __ASM_MACH_TX39XX_MANGLE_PORT_H */
