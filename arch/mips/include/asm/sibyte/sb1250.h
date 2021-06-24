<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation
 */

#अगर_अघोषित _ASM_SIBYTE_SB1250_H
#घोषणा _ASM_SIBYTE_SB1250_H

/*
 * yymmddpp: year, month, day, patch.
 * should sync with Makefile EXTRAVERSION
 */
#घोषणा SIBYTE_RELEASE 0x02111403

#घोषणा SB1250_NR_IRQS 64

#घोषणा BCM1480_NR_IRQS			128
#घोषणा BCM1480_NR_IRQS_HALF		64

#घोषणा SB1250_DUART_MINOR_BASE		64

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/addrspace.h>

/* For revision/pass inक्रमmation */
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>
बाह्य अचिन्हित पूर्णांक sb1_pass;
बाह्य अचिन्हित पूर्णांक soc_pass;
बाह्य अचिन्हित पूर्णांक soc_type;
बाह्य अचिन्हित पूर्णांक periph_rev;
बाह्य अचिन्हित पूर्णांक zbbus_mhz;

बाह्य व्योम sb1250_समय_init(व्योम);
बाह्य व्योम sb1250_mask_irq(पूर्णांक cpu, पूर्णांक irq);
बाह्य व्योम sb1250_unmask_irq(पूर्णांक cpu, पूर्णांक irq);

बाह्य व्योम bcm1480_समय_init(व्योम);
बाह्य व्योम bcm1480_mask_irq(पूर्णांक cpu, पूर्णांक irq);
बाह्य व्योम bcm1480_unmask_irq(पूर्णांक cpu, पूर्णांक irq);

#घोषणा AT_spin \
	__यंत्र__ __अस्थिर__ (		\
		".set noat\n"		\
		"li $at, 0\n"		\
		"1: beqz $at, 1b\n"	\
		".set at\n"		\
		)

#पूर्ण_अगर

#घोषणा IOADDR(a) ((व्योम __iomem *)(IO_BASE + (a)))

#पूर्ण_अगर
