<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_IRQ_H
#घोषणा __ASM_ARC_IRQ_H

/*
 * ARCv2 can support 240 पूर्णांकerrupts in the core पूर्णांकerrupts controllers and
 * 128 पूर्णांकerrupts in IDU. Thus 512 भव IRQs must be enough क्रम most
 * configurations of boards.
 * This करोesnt affect ARCompact, but we change it to same value
 */
#घोषणा NR_IRQS		512

/* Platक्रमm Independent IRQs */
#अगर_घोषित CONFIG_ISA_ARCV2
#घोषणा IPI_IRQ		19
#घोषणा SOFTIRQ_IRQ	21
#घोषणा FIRST_EXT_IRQ	24
#पूर्ण_अगर

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र-generic/irq.h>

बाह्य व्योम arc_init_IRQ(व्योम);

#पूर्ण_अगर
