<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * समयr.h:  Definitions क्रम the समयr chips on the Sparc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */


#अगर_अघोषित _SPARC_TIMER_H
#घोषणा _SPARC_TIMER_H

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/irqवापस.h>

#समावेश <यंत्र-generic/percpu.h>

#समावेश <यंत्र/cpu_type.h>  /* For SUN4M_NCPUS */

#घोषणा SBUS_CLOCK_RATE   2000000 /* 2MHz */
#घोषणा TIMER_VALUE_SHIFT 9
#घोषणा TIMER_VALUE_MASK  0x3fffff
#घोषणा TIMER_LIMIT_BIT   (1 << 31)  /* Bit 31 in Counter-Timer रेजिस्टर */

/* The counter समयr रेजिस्टर has the value offset by 9 bits.
 * From sun4m manual:
 * When a counter reaches the value in the corresponding limit रेजिस्टर,
 * the Limit bit is set and the counter is set to 500 nS (i.e. 0x00000200).
 *
 * To compensate क्रम this add one to the value.
 */
अटल अंतरभूत अचिन्हित पूर्णांक समयr_value(अचिन्हित पूर्णांक value)
अणु
	वापस (value + 1) << TIMER_VALUE_SHIFT;
पूर्ण

बाह्य अस्थिर u32 __iomem *master_l10_counter;

irqवापस_t notrace समयr_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id);

#अगर_घोषित CONFIG_SMP
DECLARE_PER_CPU(काष्ठा घड़ी_event_device, sparc32_घड़ीevent);
व्योम रेजिस्टर_percpu_ce(पूर्णांक cpu);
#पूर्ण_अगर

#पूर्ण_अगर /* !(_SPARC_TIMER_H) */
