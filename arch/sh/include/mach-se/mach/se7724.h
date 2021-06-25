<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SE7724_H
#घोषणा __ASM_SH_SE7724_H

/*
 * linux/include/यंत्र-sh/se7724.h
 *
 * Copyright (C) 2009 Renesas Solutions Corp.
 *
 * Kuninori Morimoto <morimoto.kuninori@renesas.com>
 *
 * Hitachi UL SolutionEngine 7724 Support.
 *
 * Based on se7722.h
 * Copyright (C) 2007  Nobuhiro Iwamatsu
 */
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <यंत्र/addrspace.h>

/* SH Eth */
#घोषणा SH_ETH_ADDR	(0xA4600000)
#घोषणा SH_ETH_MAHR	(SH_ETH_ADDR + 0x1C0)
#घोषणा SH_ETH_MALR	(SH_ETH_ADDR + 0x1C8)

#घोषणा PA_LED		(0xba203000)	/* 8bit LED */
#घोषणा IRQ_MODE	(0xba200010)
#घोषणा IRQ0_SR		(0xba200014)
#घोषणा IRQ1_SR		(0xba200018)
#घोषणा IRQ2_SR		(0xba20001c)
#घोषणा IRQ0_MR		(0xba200020)
#घोषणा IRQ1_MR		(0xba200024)
#घोषणा IRQ2_MR		(0xba200028)

/* IRQ */
#घोषणा IRQ0_IRQ        evt2irq(0x600)
#घोषणा IRQ1_IRQ        evt2irq(0x620)
#घोषणा IRQ2_IRQ        evt2irq(0x640)

/* Bits in IRQ012 रेजिस्टरs */
#घोषणा SE7724_FPGA_IRQ_BASE	220

/* IRQ0 */
#घोषणा IRQ0_BASE	SE7724_FPGA_IRQ_BASE
#घोषणा IRQ0_KEY	(IRQ0_BASE + 12)
#घोषणा IRQ0_RMII	(IRQ0_BASE + 13)
#घोषणा IRQ0_SMC	(IRQ0_BASE + 14)
#घोषणा IRQ0_MASK	0x7fff
#घोषणा IRQ0_END	IRQ0_SMC
/* IRQ1 */
#घोषणा IRQ1_BASE	(IRQ0_END + 1)
#घोषणा IRQ1_TS		(IRQ1_BASE + 0)
#घोषणा IRQ1_MASK	0x0001
#घोषणा IRQ1_END	IRQ1_TS
/* IRQ2 */
#घोषणा IRQ2_BASE	(IRQ1_END + 1)
#घोषणा IRQ2_USB0	(IRQ1_BASE + 0)
#घोषणा IRQ2_USB1	(IRQ1_BASE + 1)
#घोषणा IRQ2_MASK	0x0003
#घोषणा IRQ2_END	IRQ2_USB1

#घोषणा SE7724_FPGA_IRQ_NR	(IRQ2_END - IRQ0_BASE)

/* arch/sh/boards/se/7724/irq.c */
व्योम init_se7724_IRQ(व्योम);

#घोषणा __IO_PREFIX		se7724
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_SE7724_H */
