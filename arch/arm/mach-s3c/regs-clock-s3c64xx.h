<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://armlinux.simtec.co.uk/
 *
 * S3C64XX घड़ी रेजिस्टर definitions
 */

#अगर_अघोषित __PLAT_REGS_CLOCK_H
#घोषणा __PLAT_REGS_CLOCK_H __खाता__

/*
 * FIXME: Remove reमुख्यing definitions
 */

#घोषणा S3C_CLKREG(x)		(S3C_VA_SYS + (x))

#घोषणा S3C_PCLK_GATE		S3C_CLKREG(0x34)
#घोषणा S3C6410_CLK_SRC2	S3C_CLKREG(0x10C)
#घोषणा S3C_MEM_SYS_CFG		S3C_CLKREG(0x120)

/* PCLK GATE Registers */
#घोषणा S3C_CLKCON_PCLK_UART3		(1<<4)
#घोषणा S3C_CLKCON_PCLK_UART2		(1<<3)
#घोषणा S3C_CLKCON_PCLK_UART1		(1<<2)
#घोषणा S3C_CLKCON_PCLK_UART0		(1<<1)

/* MEM_SYS_CFG */
#घोषणा MEM_SYS_CFG_INDEP_CF		0x4000
#घोषणा MEM_SYS_CFG_EBI_FIX_PRI_CFCON	0x30

#पूर्ण_अगर /* _PLAT_REGS_CLOCK_H */
