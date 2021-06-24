<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_LBOXRE2_H
#घोषणा __ASM_SH_LBOXRE2_H

/*
 * Copyright (C) 2007 Nobuhiro Iwamatsu
 *
 * NTT COMWARE L-BOX RE2 support
 */
#समावेश <linux/sh_पूर्णांकc.h>

#घोषणा IRQ_CF1		evt2irq(0x320)	/* CF1 */
#घोषणा IRQ_CF0		evt2irq(0x340)	/* CF0 */
#घोषणा IRQ_INTD	evt2irq(0x360)	/* INTD */
#घोषणा IRQ_ETH1	evt2irq(0x380)	/* Ether1 */
#घोषणा IRQ_ETH0	evt2irq(0x3a0)	/* Ether0 */
#घोषणा IRQ_INTA	evt2irq(0x3c0)	/* INTA */

व्योम init_lboxre2_IRQ(व्योम);

#घोषणा __IO_PREFIX	lboxre2
#समावेश <यंत्र/io_generic.h>

#पूर्ण_अगर  /* __ASM_SH_LBOXRE2_H */
