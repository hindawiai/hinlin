<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2008-2017 Andes Technology Corporation

#समावेश <linux/init.h>
#समावेश <linux/suspend.h>
#समावेश <linux/device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <यंत्र/suspend.h>
#समावेश <nds32_पूर्णांकrinsic.h>

अचिन्हित पूर्णांक resume_addr;
अचिन्हित पूर्णांक *phy_addr_sp_पंचांगp;

अटल व्योम nds32_suspend2ram(व्योम)
अणु
	pgd_t *pgdv;
	p4d_t *p4dv;
	pud_t *pudv;
	pmd_t *pmdv;
	pte_t *ptev;

	pgdv = (pgd_t *)__va((__nds32__mfsr(NDS32_SR_L1_PPTB) &
		L1_PPTB_mskBASE)) + pgd_index((अचिन्हित पूर्णांक)cpu_resume);

	p4dv = p4d_offset(pgdv, (अचिन्हित पूर्णांक)cpu_resume);
	pudv = pud_offset(p4dv, (अचिन्हित पूर्णांक)cpu_resume);
	pmdv = pmd_offset(pudv, (अचिन्हित पूर्णांक)cpu_resume);
	ptev = pte_offset_map(pmdv, (अचिन्हित पूर्णांक)cpu_resume);

	resume_addr = ((*ptev) & TLB_DATA_mskPPN)
			| ((अचिन्हित पूर्णांक)cpu_resume & 0x00000fff);

	suspend2ram();
पूर्ण

अटल व्योम nds32_suspend_cpu(व्योम)
अणु
	जबतक (!(__nds32__mfsr(NDS32_SR_INT_PEND) & wake_mask))
		__यंत्र__ अस्थिर ("standby no_wake_grant\n\t");
पूर्ण

अटल पूर्णांक nds32_pm_valid(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_ON:
	हाल PM_SUSPEND_STANDBY:
	हाल PM_SUSPEND_MEM:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक nds32_pm_enter(suspend_state_t state)
अणु
	pr_debug("%s:state:%d\n", __func__, state);
	चयन (state) अणु
	हाल PM_SUSPEND_STANDBY:
		nds32_suspend_cpu();
		वापस 0;
	हाल PM_SUSPEND_MEM:
		nds32_suspend2ram();
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops nds32_pm_ops = अणु
	.valid = nds32_pm_valid,
	.enter = nds32_pm_enter,
पूर्ण;

अटल पूर्णांक __init nds32_pm_init(व्योम)
अणु
	pr_debug("Enter %s\n", __func__);
	suspend_set_ops(&nds32_pm_ops);
	वापस 0;
पूर्ण
late_initcall(nds32_pm_init);
