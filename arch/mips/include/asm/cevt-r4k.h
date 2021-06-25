<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Kevin D. Kissell
 */

/*
 * Definitions used क्रम common event समयr implementation
 * क्रम MIPS 4K-type processors and their MIPS MT variants.
 * Aव्योमs unsightly बाह्य declarations in C files.
 */
#अगर_अघोषित __ASM_CEVT_R4K_H
#घोषणा __ASM_CEVT_R4K_H

#समावेश <linux/घड़ीchips.h>
#समावेश <यंत्र/समय.स>

DECLARE_PER_CPU(काष्ठा घड़ी_event_device, mips_घड़ीevent_device);

व्योम mips_event_handler(काष्ठा घड़ी_event_device *dev);
पूर्णांक c0_compare_पूर्णांक_usable(व्योम);
irqवापस_t c0_compare_पूर्णांकerrupt(पूर्णांक, व्योम *);

बाह्य काष्ठा irqaction c0_compare_irqaction;
बाह्य पूर्णांक cp0_समयr_irq_installed;

#पूर्ण_अगर /* __ASM_CEVT_R4K_H */
