<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel MID platक्रमm PM support
 *
 * Copyright (C) 2016, Intel Corporation
 *
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>

#समावेश "pci.h"

अटल bool mid_pci_घातer_manageable(काष्ठा pci_dev *dev)
अणु
	वापस true;
पूर्ण

अटल पूर्णांक mid_pci_set_घातer_state(काष्ठा pci_dev *pdev, pci_घातer_t state)
अणु
	वापस पूर्णांकel_mid_pci_set_घातer_state(pdev, state);
पूर्ण

अटल pci_घातer_t mid_pci_get_घातer_state(काष्ठा pci_dev *pdev)
अणु
	वापस पूर्णांकel_mid_pci_get_घातer_state(pdev);
पूर्ण

अटल pci_घातer_t mid_pci_choose_state(काष्ठा pci_dev *pdev)
अणु
	वापस PCI_D3hot;
पूर्ण

अटल पूर्णांक mid_pci_wakeup(काष्ठा pci_dev *dev, bool enable)
अणु
	वापस 0;
पूर्ण

अटल bool mid_pci_need_resume(काष्ठा pci_dev *dev)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा pci_platक्रमm_pm_ops mid_pci_platक्रमm_pm = अणु
	.is_manageable	= mid_pci_घातer_manageable,
	.set_state	= mid_pci_set_घातer_state,
	.get_state	= mid_pci_get_घातer_state,
	.choose_state	= mid_pci_choose_state,
	.set_wakeup	= mid_pci_wakeup,
	.need_resume	= mid_pci_need_resume,
पूर्ण;

/*
 * This table should be in sync with the one in
 * arch/x86/platक्रमm/पूर्णांकel-mid/pwr.c.
 */
अटल स्थिर काष्ठा x86_cpu_id lpss_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SALTWELL_MID, शून्य),
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID, शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init mid_pci_init(व्योम)
अणु
	स्थिर काष्ठा x86_cpu_id *id;

	id = x86_match_cpu(lpss_cpu_ids);
	अगर (id)
		pci_set_platक्रमm_pm(&mid_pci_platक्रमm_pm);
	वापस 0;
पूर्ण
arch_initcall(mid_pci_init);
