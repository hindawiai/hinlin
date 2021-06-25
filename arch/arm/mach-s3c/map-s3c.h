<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX - Memory map definitions
 */

#अगर_अघोषित __ASM_PLAT_MAP_S3C_H
#घोषणा __ASM_PLAT_MAP_S3C_H __खाता__

#समावेश "map.h"

#घोषणा S3C24XX_VA_IRQ		S3C_VA_IRQ
#घोषणा S3C24XX_VA_MEMCTRL	S3C_VA_MEM
#घोषणा S3C24XX_VA_UART		S3C_VA_UART

#घोषणा S3C24XX_VA_TIMER	S3C_VA_TIMER
#घोषणा S3C24XX_VA_CLKPWR	S3C_VA_SYS
#घोषणा S3C24XX_VA_WATCHDOG	S3C_VA_WATCHDOG

#घोषणा S3C2412_VA_SSMC		S3C_ADDR_CPU(0x00000000)
#घोषणा S3C2412_VA_EBI		S3C_ADDR_CPU(0x00100000)

#घोषणा S3C2410_PA_UART		(0x50000000)
#घोषणा S3C24XX_PA_UART		S3C2410_PA_UART

/*
 * GPIO ports
 *
 * the calculation क्रम the VA of this must ensure that
 * it is the same distance apart from the UART in the
 * phsyical address space, as the initial mapping क्रम the IO
 * is करोne as a 1:1 mapping. This माला_दो it (currently) at
 * 0xFA800000, which is not in the way of any current mapping
 * by the base प्रणाली.
*/

#घोषणा S3C2410_PA_GPIO		(0x56000000)
#घोषणा S3C24XX_PA_GPIO		S3C2410_PA_GPIO

#घोषणा S3C24XX_VA_GPIO		((S3C24XX_PA_GPIO - S3C24XX_PA_UART) + S3C24XX_VA_UART)
#घोषणा S3C64XX_VA_GPIO		S3C_ADDR_CPU(0x00000000)

#घोषणा S3C64XX_VA_MODEM	S3C_ADDR_CPU(0x00100000)
#घोषणा S3C64XX_VA_USB_HSPHY	S3C_ADDR_CPU(0x00200000)

#घोषणा S3C_VA_USB_HSPHY	S3C64XX_VA_USB_HSPHY

#घोषणा S3C2410_ADDR(x)		S3C_ADDR(x)

/* deal with the रेजिस्टरs that move under the 2412/2413 */

#अगर defined(CONFIG_CPU_S3C2412)
#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम __iomem *s3c24xx_va_gpio2;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_S3C2412_ONLY
#घोषणा S3C24XX_VA_GPIO2	(S3C24XX_VA_GPIO + 0x10)
#अन्यथा
#घोषणा S3C24XX_VA_GPIO2 s3c24xx_va_gpio2
#पूर्ण_अगर
#अन्यथा
#घोषणा s3c24xx_va_gpio2 S3C24XX_VA_GPIO
#घोषणा S3C24XX_VA_GPIO2 S3C24XX_VA_GPIO
#पूर्ण_अगर

#समावेश "map-s5p.h"

#पूर्ण_अगर /* __ASM_PLAT_MAP_S3C_H */
