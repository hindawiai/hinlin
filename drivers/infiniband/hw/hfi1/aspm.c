<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2019 Intel Corporation.
 *
 */

#समावेश "aspm.h"

/* Time after which the समयr पूर्णांकerrupt will re-enable ASPM */
#घोषणा ASPM_TIMER_MS 1000
/* Time क्रम which पूर्णांकerrupts are ignored after a समयr has been scheduled */
#घोषणा ASPM_RESCHED_TIMER_MS (ASPM_TIMER_MS / 2)
/* Two पूर्णांकerrupts within this समय trigger ASPM disable */
#घोषणा ASPM_TRIGGER_MS 1
#घोषणा ASPM_TRIGGER_NS (ASPM_TRIGGER_MS * 1000 * 1000ull)
#घोषणा ASPM_L1_SUPPORTED(reg) \
	((((reg) & PCI_EXP_LNKCAP_ASPMS) >> 10) & 0x2)

uपूर्णांक aspm_mode = ASPM_MODE_DISABLED;
module_param_named(aspm, aspm_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(aspm, "PCIe ASPM: 0: disable, 1: enable, 2: dynamic");

अटल bool aspm_hw_l1_supported(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *parent = dd->pcidev->bus->self;
	u32 up, dn;

	/*
	 * If the driver करोes not have access to the upstream component,
	 * it cannot support ASPM L1 at all.
	 */
	अगर (!parent)
		वापस false;

	pcie_capability_पढ़ो_dword(dd->pcidev, PCI_EXP_LNKCAP, &dn);
	dn = ASPM_L1_SUPPORTED(dn);

	pcie_capability_पढ़ो_dword(parent, PCI_EXP_LNKCAP, &up);
	up = ASPM_L1_SUPPORTED(up);

	/* ASPM works on A-step but is reported as not supported */
	वापस (!!dn || is_ax(dd)) && !!up;
पूर्ण

/* Set L1 entrance latency क्रम slower entry to L1 */
अटल व्योम aspm_hw_set_l1_ent_latency(काष्ठा hfi1_devdata *dd)
अणु
	u32 l1_ent_lat = 0x4u;
	u32 reg32;

	pci_पढ़ो_config_dword(dd->pcidev, PCIE_CFG_REG_PL3, &reg32);
	reg32 &= ~PCIE_CFG_REG_PL3_L1_ENT_LATENCY_SMASK;
	reg32 |= l1_ent_lat << PCIE_CFG_REG_PL3_L1_ENT_LATENCY_SHIFT;
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_REG_PL3, reg32);
पूर्ण

अटल व्योम aspm_hw_enable_l1(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *parent = dd->pcidev->bus->self;

	/*
	 * If the driver करोes not have access to the upstream component,
	 * it cannot support ASPM L1 at all.
	 */
	अगर (!parent)
		वापस;

	/* Enable ASPM L1 first in upstream component and then करोwnstream */
	pcie_capability_clear_and_set_word(parent, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC,
					   PCI_EXP_LNKCTL_ASPM_L1);
	pcie_capability_clear_and_set_word(dd->pcidev, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC,
					   PCI_EXP_LNKCTL_ASPM_L1);
पूर्ण

व्योम aspm_hw_disable_l1(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *parent = dd->pcidev->bus->self;

	/* Disable ASPM L1 first in करोwnstream component and then upstream */
	pcie_capability_clear_and_set_word(dd->pcidev, PCI_EXP_LNKCTL,
					   PCI_EXP_LNKCTL_ASPMC, 0x0);
	अगर (parent)
		pcie_capability_clear_and_set_word(parent, PCI_EXP_LNKCTL,
						   PCI_EXP_LNKCTL_ASPMC, 0x0);
पूर्ण

अटल  व्योम aspm_enable(काष्ठा hfi1_devdata *dd)
अणु
	अगर (dd->aspm_enabled || aspm_mode == ASPM_MODE_DISABLED ||
	    !dd->aspm_supported)
		वापस;

	aspm_hw_enable_l1(dd);
	dd->aspm_enabled = true;
पूर्ण

अटल  व्योम aspm_disable(काष्ठा hfi1_devdata *dd)
अणु
	अगर (!dd->aspm_enabled || aspm_mode == ASPM_MODE_ENABLED)
		वापस;

	aspm_hw_disable_l1(dd);
	dd->aspm_enabled = false;
पूर्ण

अटल  व्योम aspm_disable_inc(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->aspm_lock, flags);
	aspm_disable(dd);
	atomic_inc(&dd->aspm_disabled_cnt);
	spin_unlock_irqrestore(&dd->aspm_lock, flags);
पूर्ण

अटल  व्योम aspm_enable_dec(काष्ठा hfi1_devdata *dd)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->aspm_lock, flags);
	अगर (atomic_dec_and_test(&dd->aspm_disabled_cnt))
		aspm_enable(dd);
	spin_unlock_irqrestore(&dd->aspm_lock, flags);
पूर्ण

/* ASPM processing क्रम each receive context पूर्णांकerrupt */
व्योम __aspm_ctx_disable(काष्ठा hfi1_ctxtdata *rcd)
अणु
	bool restart_समयr;
	bool बंद_पूर्णांकerrupts;
	अचिन्हित दीर्घ flags;
	kसमय_प्रकार now, prev;

	spin_lock_irqsave(&rcd->aspm_lock, flags);
	/* PSM contexts are खोलो */
	अगर (!rcd->aspm_पूर्णांकr_enable)
		जाओ unlock;

	prev = rcd->aspm_ts_last_पूर्णांकr;
	now = kसमय_get();
	rcd->aspm_ts_last_पूर्णांकr = now;

	/* An पूर्णांकerrupt pair बंद together in समय */
	बंद_पूर्णांकerrupts = kसमय_प्रकारo_ns(kसमय_sub(now, prev)) < ASPM_TRIGGER_NS;

	/* Don't push out our समयr till this much समय has elapsed */
	restart_समयr = kसमय_प्रकारo_ns(kसमय_sub(now, rcd->aspm_ts_समयr_sched)) >
				    ASPM_RESCHED_TIMER_MS * NSEC_PER_MSEC;
	restart_समयr = restart_समयr && बंद_पूर्णांकerrupts;

	/* Disable ASPM and schedule समयr */
	अगर (rcd->aspm_enabled && बंद_पूर्णांकerrupts) अणु
		aspm_disable_inc(rcd->dd);
		rcd->aspm_enabled = false;
		restart_समयr = true;
	पूर्ण

	अगर (restart_समयr) अणु
		mod_समयr(&rcd->aspm_समयr,
			  jअगरfies + msecs_to_jअगरfies(ASPM_TIMER_MS));
		rcd->aspm_ts_समयr_sched = now;
	पूर्ण
unlock:
	spin_unlock_irqrestore(&rcd->aspm_lock, flags);
पूर्ण

/* Timer function क्रम re-enabling ASPM in the असलence of पूर्णांकerrupt activity */
अटल  व्योम aspm_ctx_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_ctxtdata *rcd = from_समयr(rcd, t, aspm_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rcd->aspm_lock, flags);
	aspm_enable_dec(rcd->dd);
	rcd->aspm_enabled = true;
	spin_unlock_irqrestore(&rcd->aspm_lock, flags);
पूर्ण

/*
 * Disable पूर्णांकerrupt processing क्रम verbs contexts when PSM or VNIC contexts
 * are खोलो.
 */
व्योम aspm_disable_all(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	अचिन्हित दीर्घ flags;
	u16 i;

	क्रम (i = 0; i < dd->first_dyn_alloc_ctxt; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (rcd) अणु
			del_समयr_sync(&rcd->aspm_समयr);
			spin_lock_irqsave(&rcd->aspm_lock, flags);
			rcd->aspm_पूर्णांकr_enable = false;
			spin_unlock_irqrestore(&rcd->aspm_lock, flags);
			hfi1_rcd_put(rcd);
		पूर्ण
	पूर्ण

	aspm_disable(dd);
	atomic_set(&dd->aspm_disabled_cnt, 0);
पूर्ण

/* Re-enable पूर्णांकerrupt processing क्रम verbs contexts */
व्योम aspm_enable_all(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	अचिन्हित दीर्घ flags;
	u16 i;

	aspm_enable(dd);

	अगर (aspm_mode != ASPM_MODE_DYNAMIC)
		वापस;

	क्रम (i = 0; i < dd->first_dyn_alloc_ctxt; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (rcd) अणु
			spin_lock_irqsave(&rcd->aspm_lock, flags);
			rcd->aspm_पूर्णांकr_enable = true;
			rcd->aspm_enabled = true;
			spin_unlock_irqrestore(&rcd->aspm_lock, flags);
			hfi1_rcd_put(rcd);
		पूर्ण
	पूर्ण
पूर्ण

अटल  व्योम aspm_ctx_init(काष्ठा hfi1_ctxtdata *rcd)
अणु
	spin_lock_init(&rcd->aspm_lock);
	समयr_setup(&rcd->aspm_समयr, aspm_ctx_समयr_function, 0);
	rcd->aspm_पूर्णांकr_supported = rcd->dd->aspm_supported &&
		aspm_mode == ASPM_MODE_DYNAMIC &&
		rcd->ctxt < rcd->dd->first_dyn_alloc_ctxt;
पूर्ण

व्योम aspm_init(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा hfi1_ctxtdata *rcd;
	u16 i;

	spin_lock_init(&dd->aspm_lock);
	dd->aspm_supported = aspm_hw_l1_supported(dd);

	क्रम (i = 0; i < dd->first_dyn_alloc_ctxt; i++) अणु
		rcd = hfi1_rcd_get_by_index(dd, i);
		अगर (rcd)
			aspm_ctx_init(rcd);
		hfi1_rcd_put(rcd);
	पूर्ण

	/* Start with ASPM disabled */
	aspm_hw_set_l1_ent_latency(dd);
	dd->aspm_enabled = false;
	aspm_hw_disable_l1(dd);

	/* Now turn on ASPM अगर configured */
	aspm_enable_all(dd);
पूर्ण

व्योम aspm_निकास(काष्ठा hfi1_devdata *dd)
अणु
	aspm_disable_all(dd);

	/* Turn on ASPM on निकास to conserve घातer */
	aspm_enable(dd);
पूर्ण

