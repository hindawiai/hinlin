<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Numascale NumaConnect-Specअगरic Header file
 *
 * Copyright (C) 2011 Numascale AS. All rights reserved.
 *
 * Send feedback to <support@numascale.com>
 *
 */

#अगर_अघोषित _ASM_X86_NUMACHIP_NUMACHIP_CSR_H
#घोषणा _ASM_X86_NUMACHIP_NUMACHIP_CSR_H

#समावेश <linux/smp.h>
#समावेश <linux/पन.स>

#घोषणा CSR_NODE_SHIFT		16
#घोषणा CSR_NODE_BITS(p)	(((अचिन्हित दीर्घ)(p)) << CSR_NODE_SHIFT)
#घोषणा CSR_NODE_MASK		0x0fff		/* 4K nodes */

/* 32K CSR space, b15 indicates geo/non-geo */
#घोषणा CSR_OFFSET_MASK	0x7fffUL
#घोषणा CSR_G0_NODE_IDS (0x008 + (0 << 12))
#घोषणा CSR_G3_EXT_IRQ_GEN (0x030 + (3 << 12))

/*
 * Local CSR space starts in global CSR space with "nodeid" = 0xfff0, however
 * when using the direct mapping on x86_64, both start and size needs to be
 * aligned with PMD_SIZE which is 2M
 */
#घोषणा NUMACHIP_LCSR_BASE	0x3ffffe000000ULL
#घोषणा NUMACHIP_LCSR_LIM	0x3fffffffffffULL
#घोषणा NUMACHIP_LCSR_SIZE	(NUMACHIP_LCSR_LIM - NUMACHIP_LCSR_BASE + 1)
#घोषणा NUMACHIP_LAPIC_BITS	8

अटल अंतरभूत व्योम *lcsr_address(अचिन्हित दीर्घ offset)
अणु
	वापस __va(NUMACHIP_LCSR_BASE | (1UL << 15) |
		CSR_NODE_BITS(0xfff0) | (offset & CSR_OFFSET_MASK));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_lcsr(अचिन्हित दीर्घ offset)
अणु
	वापस swab32(पढ़ोl(lcsr_address(offset)));
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_lcsr(अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(swab32(val), lcsr_address(offset));
पूर्ण

/*
 * On NumaChip2, local CSR space is 16MB and starts at fixed offset below 4G
 */

#घोषणा NUMACHIP2_LCSR_BASE       0xf0000000UL
#घोषणा NUMACHIP2_LCSR_SIZE       0x1000000UL
#घोषणा NUMACHIP2_APIC_ICR        0x100000
#घोषणा NUMACHIP2_TIMER_DEADLINE  0x200000
#घोषणा NUMACHIP2_TIMER_INT       0x200008
#घोषणा NUMACHIP2_TIMER_NOW       0x200018
#घोषणा NUMACHIP2_TIMER_RESET     0x200020

अटल अंतरभूत व्योम __iomem *numachip2_lcsr_address(अचिन्हित दीर्घ offset)
अणु
	वापस (व्योम __iomem *)__va(NUMACHIP2_LCSR_BASE |
		(offset & (NUMACHIP2_LCSR_SIZE - 1)));
पूर्ण

अटल अंतरभूत u32 numachip2_पढ़ो32_lcsr(अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(numachip2_lcsr_address(offset));
पूर्ण

अटल अंतरभूत u64 numachip2_पढ़ो64_lcsr(अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोq(numachip2_lcsr_address(offset));
पूर्ण

अटल अंतरभूत व्योम numachip2_ग_लिखो32_lcsr(अचिन्हित दीर्घ offset, u32 val)
अणु
	ग_लिखोl(val, numachip2_lcsr_address(offset));
पूर्ण

अटल अंतरभूत व्योम numachip2_ग_लिखो64_lcsr(अचिन्हित दीर्घ offset, u64 val)
अणु
	ग_लिखोq(val, numachip2_lcsr_address(offset));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक numachip2_समयr(व्योम)
अणु
	वापस (smp_processor_id() % 48) << 6;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_NUMACHIP_NUMACHIP_CSR_H */
