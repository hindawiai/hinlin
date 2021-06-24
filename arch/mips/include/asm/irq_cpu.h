<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/irq_cpu.h
 *
 *	MIPS CPU पूर्णांकerrupt definitions.
 *
 *	Copyright (C) 2002  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_IRQ_CPU_H
#घोषणा _ASM_IRQ_CPU_H

बाह्य व्योम mips_cpu_irq_init(व्योम);

#अगर_घोषित CONFIG_IRQ_DOMAIN
काष्ठा device_node;
बाह्य पूर्णांक mips_cpu_irq_of_init(काष्ठा device_node *of_node,
				काष्ठा device_node *parent);
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IRQ_CPU_H */
