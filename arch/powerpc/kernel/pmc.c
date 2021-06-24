<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  arch/घातerpc/kernel/pmc.c
 *
 *  Copyright (C) 2004 David Gibson, IBM Corporation.
 *  Includes code क्रमmerly from arch/ppc/kernel/perfmon.c:
 *    Author: Andy Fleming
 *    Copyright (c) 2004 Freescale Semiconductor, Inc
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bug.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/pmc.h>

#अगर_अघोषित MMCR0_PMAO
#घोषणा MMCR0_PMAO	0
#पूर्ण_अगर

अटल व्योम dummy_perf(काष्ठा pt_regs *regs)
अणु
#अगर defined(CONFIG_FSL_EMB_PERFMON)
	mtpmr(PMRN_PMGC0, mfpmr(PMRN_PMGC0) & ~PMGC0_PMIE);
#या_अगर defined(CONFIG_PPC64) || defined(CONFIG_PPC_BOOK3S_32)
	अगर (cur_cpu_spec->pmc_type == PPC_PMC_IBM)
		mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~(MMCR0_PMXE|MMCR0_PMAO));
#अन्यथा
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_PMXE);
#पूर्ण_अगर
पूर्ण


अटल DEFINE_RAW_SPINLOCK(pmc_owner_lock);
अटल व्योम *pmc_owner_caller; /* mostly क्रम debugging */
perf_irq_t perf_irq = dummy_perf;

पूर्णांक reserve_pmc_hardware(perf_irq_t new_perf_irq)
अणु
	पूर्णांक err = 0;

	raw_spin_lock(&pmc_owner_lock);

	अगर (pmc_owner_caller) अणु
		prपूर्णांकk(KERN_WARNING "reserve_pmc_hardware: "
		       "PMC hardware busy (reserved by caller %p)\n",
		       pmc_owner_caller);
		err = -EBUSY;
		जाओ out;
	पूर्ण

	pmc_owner_caller = __builtin_वापस_address(0);
	perf_irq = new_perf_irq ? new_perf_irq : dummy_perf;

 out:
	raw_spin_unlock(&pmc_owner_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(reserve_pmc_hardware);

व्योम release_pmc_hardware(व्योम)
अणु
	raw_spin_lock(&pmc_owner_lock);

	WARN_ON(! pmc_owner_caller);

	pmc_owner_caller = शून्य;
	perf_irq = dummy_perf;

	raw_spin_unlock(&pmc_owner_lock);
पूर्ण
EXPORT_SYMBOL_GPL(release_pmc_hardware);

#अगर_घोषित CONFIG_PPC64
व्योम घातer4_enable_pmcs(व्योम)
अणु
	अचिन्हित दीर्घ hid0;

	hid0 = mfspr(SPRN_HID0);
	hid0 |= 1UL << (63 - 20);

	/* POWER4 requires the following sequence */
	यंत्र अस्थिर(
		"sync\n"
		"mtspr     %1, %0\n"
		"mfspr     %0, %1\n"
		"mfspr     %0, %1\n"
		"mfspr     %0, %1\n"
		"mfspr     %0, %1\n"
		"mfspr     %0, %1\n"
		"mfspr     %0, %1\n"
		"isync" : "=&r" (hid0) : "i" (SPRN_HID0), "0" (hid0):
		"memory");
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */
