<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_RENESAS_SDK7780_H
#घोषणा __ASM_SH_RENESAS_SDK7780_H

/*
 * linux/include/यंत्र-sh/sdk7780.h
 *
 * Renesas Solutions SH7780 SDK Support
 * Copyright (C) 2008 Nicholas Beck <nbeck@mpc-data.co.uk>
 */
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/addrspace.h>

/* Box specअगरic addresses.  */
#घोषणा SE_AREA0_WIDTH	4		/* Area0: 32bit */
#घोषणा PA_ROM			0xa0000000	/* EPROM */
#घोषणा PA_ROM_SIZE		0x00400000	/* EPROM size 4M byte */
#घोषणा PA_FROM			0xa0800000	/* Flash-ROM */
#घोषणा PA_FROM_SIZE	0x00400000	/* Flash-ROM size 4M byte */
#घोषणा PA_EXT1			0xa4000000
#घोषणा PA_EXT1_SIZE	0x04000000
#घोषणा PA_SDRAM		0xa8000000	/* DDR-SDRAM(Area2/3) 128MB */
#घोषणा PA_SDRAM_SIZE	0x08000000

#घोषणा PA_EXT4			0xb0000000
#घोषणा PA_EXT4_SIZE	0x04000000
#घोषणा PA_EXT_USER		PA_EXT4		/* User Expansion Space */

#घोषणा PA_PERIPHERAL	PA_AREA5_IO

/* SRAM/Reserved */
#घोषणा PA_RESERVED	(PA_PERIPHERAL + 0)
/* FPGA base address */
#घोषणा PA_FPGA		(PA_PERIPHERAL + 0x01000000)
/* SMC LAN91C111 */
#घोषणा PA_LAN		(PA_PERIPHERAL + 0x01800000)


#घोषणा FPGA_SRSTR      (PA_FPGA + 0x000)	/* System reset */
#घोषणा FPGA_IRQ0SR     (PA_FPGA + 0x010)	/* IRQ0 status */
#घोषणा FPGA_IRQ0MR     (PA_FPGA + 0x020)	/* IRQ0 mask */
#घोषणा FPGA_BDMR       (PA_FPGA + 0x030)	/* Board operating mode */
#घोषणा FPGA_INTT0PRTR  (PA_FPGA + 0x040)	/* Interrupt test mode0 port */
#घोषणा FPGA_INTT0SELR  (PA_FPGA + 0x050)	/* Int. test mode0 select */
#घोषणा FPGA_INTT1POLR  (PA_FPGA + 0x060)	/* Int. test mode0 polarity */
#घोषणा FPGA_NMIR       (PA_FPGA + 0x070)	/* NMI source */
#घोषणा FPGA_NMIMR      (PA_FPGA + 0x080)	/* NMI mask */
#घोषणा FPGA_IRQR       (PA_FPGA + 0x090)	/* IRQX source */
#घोषणा FPGA_IRQMR      (PA_FPGA + 0x0A0)	/* IRQX mask */
#घोषणा FPGA_SLEDR      (PA_FPGA + 0x0B0)	/* LED control */
#घोषणा PA_LED			FPGA_SLEDR
#घोषणा FPGA_MAPSWR     (PA_FPGA + 0x0C0)	/* Map चयन */
#घोषणा FPGA_FPVERR     (PA_FPGA + 0x0D0)	/* FPGA version */
#घोषणा FPGA_FPDATER    (PA_FPGA + 0x0E0)	/* FPGA date */
#घोषणा FPGA_RSE        (PA_FPGA + 0x100)	/* Reset source */
#घोषणा FPGA_EASR       (PA_FPGA + 0x110)	/* External area select */
#घोषणा FPGA_SPER       (PA_FPGA + 0x120)	/* Serial port enable */
#घोषणा FPGA_IMSR       (PA_FPGA + 0x130)	/* Interrupt mode select */
#घोषणा FPGA_PCIMR      (PA_FPGA + 0x140)	/* PCI Mode */
#घोषणा FPGA_DIPSWMR    (PA_FPGA + 0x150)	/* DIPSW monitor */
#घोषणा FPGA_FPODR      (PA_FPGA + 0x160)	/* Output port data */
#घोषणा FPGA_ATAESR     (PA_FPGA + 0x170)	/* ATA extended bus status */
#घोषणा FPGA_IRQPOLR    (PA_FPGA + 0x180)	/* IRQx polarity */


#घोषणा SDK7780_NR_IRL			15
/* IDE/ATA पूर्णांकerrupt */
#घोषणा IRQ_CFCARD			evt2irq(0x3c0)
/* SMC पूर्णांकerrupt */
#घोषणा IRQ_ETHERNET			evt2irq(0x2c0)


/* arch/sh/boards/renesas/sdk7780/irq.c */
व्योम init_sdk7780_IRQ(व्योम);

#घोषणा __IO_PREFIX		sdk7780
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_RENESAS_SDK7780_H */
