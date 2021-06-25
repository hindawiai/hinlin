<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pervasive backend क्रम the cbe_cpufreq driver
 *
 * This driver makes use of the pervasive unit to
 * engage the desired frequency.
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005-2007
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/cell-regs.h>

#समावेश "ppc_cbe_cpufreq.h"

/* to ग_लिखो to MIC रेजिस्टर */
अटल u64 MIC_Slow_Fast_Timer_table[] = अणु
	[0 ... 7] = 0x007fc00000000000ull,
पूर्ण;

/* more values क्रम the MIC */
अटल u64 MIC_Slow_Next_Timer_table[] = अणु
	0x0000240000000000ull,
	0x0000268000000000ull,
	0x000029C000000000ull,
	0x00002D0000000000ull,
	0x0000300000000000ull,
	0x0000334000000000ull,
	0x000039C000000000ull,
	0x00003FC000000000ull,
पूर्ण;


पूर्णांक cbe_cpufreq_set_pmode(पूर्णांक cpu, अचिन्हित पूर्णांक pmode)
अणु
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;
	काष्ठा cbe_mic_पंचांग_regs __iomem *mic_पंचांग_regs;
	अचिन्हित दीर्घ flags;
	u64 value;
#अगर_घोषित DEBUG
	दीर्घ समय;
#पूर्ण_अगर

	local_irq_save(flags);

	mic_पंचांग_regs = cbe_get_cpu_mic_पंचांग_regs(cpu);
	pmd_regs = cbe_get_cpu_pmd_regs(cpu);

#अगर_घोषित DEBUG
	समय = jअगरfies;
#पूर्ण_अगर

	out_be64(&mic_पंचांग_regs->slow_fast_समयr_0, MIC_Slow_Fast_Timer_table[pmode]);
	out_be64(&mic_पंचांग_regs->slow_fast_समयr_1, MIC_Slow_Fast_Timer_table[pmode]);

	out_be64(&mic_पंचांग_regs->slow_next_समयr_0, MIC_Slow_Next_Timer_table[pmode]);
	out_be64(&mic_पंचांग_regs->slow_next_समयr_1, MIC_Slow_Next_Timer_table[pmode]);

	value = in_be64(&pmd_regs->pmcr);
	/* set bits to zero */
	value &= 0xFFFFFFFFFFFFFFF8ull;
	/* set bits to next pmode */
	value |= pmode;

	out_be64(&pmd_regs->pmcr, value);

#अगर_घोषित DEBUG
	/* रुको until new pmode appears in status रेजिस्टर */
	value = in_be64(&pmd_regs->pmsr) & 0x07;
	जबतक (value != pmode) अणु
		cpu_relax();
		value = in_be64(&pmd_regs->pmsr) & 0x07;
	पूर्ण

	समय = jअगरfies  - समय;
	समय = jअगरfies_to_msecs(समय);
	pr_debug("had to wait %lu ms for a transition using " \
		 "pervasive unit\n", समय);
#पूर्ण_अगर
	local_irq_restore(flags);

	वापस 0;
पूर्ण


पूर्णांक cbe_cpufreq_get_pmode(पूर्णांक cpu)
अणु
	पूर्णांक ret;
	काष्ठा cbe_pmd_regs __iomem *pmd_regs;

	pmd_regs = cbe_get_cpu_pmd_regs(cpu);
	ret = in_be64(&pmd_regs->pmsr) & 0x07;

	वापस ret;
पूर्ण

