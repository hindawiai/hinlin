<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2003, 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - Memory map definitions (भव addresses)
 */

#अगर_अघोषित __ASM_PLAT_MAP_H
#घोषणा __ASM_PLAT_MAP_H __खाता__

/* Fit all our रेजिस्टरs in at 0xF6000000 upwards, trying to use as
 * little of the VA space as possible so vदो_स्मृति and मित्रs have a
 * better chance of getting memory.
 *
 * we try to ensure stuff like the IRQ रेजिस्टरs are available क्रम
 * an single MOVS inकाष्ठाion (ie, only 8 bits of set data)
 */

#घोषणा S3C_ADDR_BASE	0xF6000000

#अगर_अघोषित __ASSEMBLY__
#घोषणा S3C_ADDR(x)	((व्योम __iomem __क्रमce *)S3C_ADDR_BASE + (x))
#अन्यथा
#घोषणा S3C_ADDR(x)	(S3C_ADDR_BASE + (x))
#पूर्ण_अगर

#घोषणा S3C_VA_IRQ	S3C_ADDR(0x00000000)	/* irq controller(s) */
#घोषणा S3C_VA_SYS	S3C_ADDR(0x00100000)	/* प्रणाली control */
#घोषणा S3C_VA_MEM	S3C_ADDR(0x00200000)	/* memory control */
#घोषणा S3C_VA_TIMER	S3C_ADDR(0x00300000)	/* समयr block */
#घोषणा S3C_VA_WATCHDOG	S3C_ADDR(0x00400000)	/* watchकरोg */
#घोषणा S3C_VA_UART	S3C_ADDR(0x01000000)	/* UART */

/* This is used क्रम the CPU specअगरic mappings that may be needed, so that
 * they करो not need to directly used S3C_ADDR() and thus make it easier to
 * modअगरy the space क्रम mapping.
 */
#घोषणा S3C_ADDR_CPU(x)	S3C_ADDR(0x00500000 + (x))

#पूर्ण_अगर /* __ASM_PLAT_MAP_H */
