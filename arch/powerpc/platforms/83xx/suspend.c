<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MPC83xx suspend support
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 *
 * Copyright (c) 2006-2007 Freescale Semiconductor, Inc.
 */

#समावेश <linux/pm.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/suspend.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mpc6xx.h>
#समावेश <यंत्र/चयन_to.h>

#समावेश <sysdev/fsl_soc.h>

#घोषणा PMCCR1_NEXT_STATE       0x0C /* Next state क्रम घातer management */
#घोषणा PMCCR1_NEXT_STATE_SHIFT 2
#घोषणा PMCCR1_CURR_STATE       0x03 /* Current state क्रम घातer management*/
#घोषणा IMMR_SYSCR_OFFSET       0x100
#घोषणा IMMR_RCW_OFFSET         0x900
#घोषणा RCW_PCI_HOST            0x80000000

व्योम mpc83xx_enter_deep_sleep(phys_addr_t immrbase);

काष्ठा mpc83xx_pmc अणु
	u32 config;
#घोषणा PMCCR_DLPEN 2 /* DDR SDRAM low घातer enable */
#घोषणा PMCCR_SLPEN 1 /* System low घातer enable */

	u32 event;
	u32 mask;
/* All but PMCI are deep-sleep only */
#घोषणा PMCER_GPIO   0x100
#घोषणा PMCER_PCI    0x080
#घोषणा PMCER_USB    0x040
#घोषणा PMCER_ETSEC1 0x020
#घोषणा PMCER_ETSEC2 0x010
#घोषणा PMCER_TIMER  0x008
#घोषणा PMCER_INT1   0x004
#घोषणा PMCER_INT2   0x002
#घोषणा PMCER_PMCI   0x001
#घोषणा PMCER_ALL    0x1FF

	/* deep-sleep only */
	u32 config1;
#घोषणा PMCCR1_USE_STATE  0x80000000
#घोषणा PMCCR1_PME_EN     0x00000080
#घोषणा PMCCR1_ASSERT_PME 0x00000040
#घोषणा PMCCR1_POWER_OFF  0x00000020

	/* deep-sleep only */
	u32 config2;
पूर्ण;

काष्ठा mpc83xx_rcw अणु
	u32 rcwlr;
	u32 rcwhr;
पूर्ण;

काष्ठा mpc83xx_घड़ी अणु
	u32 spmr;
	u32 occr;
	u32 sccr;
पूर्ण;

काष्ठा mpc83xx_syscr अणु
	__be32 sgprl;
	__be32 sgprh;
	__be32 spridr;
	__be32 :32;
	__be32 spcr;
	__be32 sicrl;
	__be32 sicrh;
पूर्ण;

काष्ठा mpc83xx_saved अणु
	u32 sicrl;
	u32 sicrh;
	u32 sccr;
पूर्ण;

काष्ठा pmc_type अणु
	पूर्णांक has_deep_sleep;
पूर्ण;

अटल काष्ठा platक्रमm_device *pmc_dev;
अटल पूर्णांक has_deep_sleep, deep_sleeping;
अटल पूर्णांक pmc_irq;
अटल काष्ठा mpc83xx_pmc __iomem *pmc_regs;
अटल काष्ठा mpc83xx_घड़ी __iomem *घड़ी_regs;
अटल काष्ठा mpc83xx_syscr __iomem *syscr_regs;
अटल काष्ठा mpc83xx_saved saved_regs;
अटल पूर्णांक is_pci_agent, wake_from_pci;
अटल phys_addr_t immrbase;
अटल पूर्णांक pci_pm_state;
अटल DECLARE_WAIT_QUEUE_HEAD(agent_wq);

पूर्णांक fsl_deep_sleep(व्योम)
अणु
	वापस deep_sleeping;
पूर्ण
EXPORT_SYMBOL(fsl_deep_sleep);

अटल पूर्णांक mpc83xx_change_state(व्योम)
अणु
	u32 curr_state;
	u32 reg_cfg1 = in_be32(&pmc_regs->config1);

	अगर (is_pci_agent) अणु
		pci_pm_state = (reg_cfg1 & PMCCR1_NEXT_STATE) >>
		               PMCCR1_NEXT_STATE_SHIFT;
		curr_state = reg_cfg1 & PMCCR1_CURR_STATE;

		अगर (curr_state != pci_pm_state) अणु
			reg_cfg1 &= ~PMCCR1_CURR_STATE;
			reg_cfg1 |= pci_pm_state;
			out_be32(&pmc_regs->config1, reg_cfg1);

			wake_up(&agent_wq);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t pmc_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 event = in_be32(&pmc_regs->event);
	पूर्णांक ret = IRQ_NONE;

	अगर (mpc83xx_change_state())
		ret = IRQ_HANDLED;

	अगर (event) अणु
		out_be32(&pmc_regs->event, event);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mpc83xx_suspend_restore_regs(व्योम)
अणु
	out_be32(&syscr_regs->sicrl, saved_regs.sicrl);
	out_be32(&syscr_regs->sicrh, saved_regs.sicrh);
	out_be32(&घड़ी_regs->sccr, saved_regs.sccr);
पूर्ण

अटल व्योम mpc83xx_suspend_save_regs(व्योम)
अणु
	saved_regs.sicrl = in_be32(&syscr_regs->sicrl);
	saved_regs.sicrh = in_be32(&syscr_regs->sicrh);
	saved_regs.sccr = in_be32(&घड़ी_regs->sccr);
पूर्ण

अटल पूर्णांक mpc83xx_suspend_enter(suspend_state_t state)
अणु
	पूर्णांक ret = -EAGAIN;

	/* Don't go to sleep if there's a race where pci_pm_state changes
	 * between the agent thपढ़ो checking it and the PM code disabling
	 * पूर्णांकerrupts.
	 */
	अगर (wake_from_pci) अणु
		अगर (pci_pm_state != (deep_sleeping ? 3 : 2))
			जाओ out;

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) | PMCCR1_PME_EN);
	पूर्ण

	/* Put the प्रणाली पूर्णांकo low-घातer mode and the RAM
	 * पूर्णांकo self-refresh mode once the core goes to
	 * sleep.
	 */

	out_be32(&pmc_regs->config, PMCCR_SLPEN | PMCCR_DLPEN);

	/* If it has deep sleep (i.e. it's an 831x or compatible),
	 * disable घातer to the core upon entering sleep mode.  This will
	 * require going through the boot firmware upon a wakeup event.
	 */

	अगर (deep_sleeping) अणु
		mpc83xx_suspend_save_regs();

		out_be32(&pmc_regs->mask, PMCER_ALL);

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) | PMCCR1_POWER_OFF);

		enable_kernel_fp();

		mpc83xx_enter_deep_sleep(immrbase);

		out_be32(&pmc_regs->config1,
		         in_be32(&pmc_regs->config1) & ~PMCCR1_POWER_OFF);

		out_be32(&pmc_regs->mask, PMCER_PMCI);

		mpc83xx_suspend_restore_regs();
	पूर्ण अन्यथा अणु
		out_be32(&pmc_regs->mask, PMCER_PMCI);

		mpc6xx_enter_standby();
	पूर्ण

	ret = 0;

out:
	out_be32(&pmc_regs->config1,
	         in_be32(&pmc_regs->config1) & ~PMCCR1_PME_EN);

	वापस ret;
पूर्ण

अटल व्योम mpc83xx_suspend_end(व्योम)
अणु
	deep_sleeping = 0;
पूर्ण

अटल पूर्णांक mpc83xx_suspend_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_STANDBY || state == PM_SUSPEND_MEM;
पूर्ण

अटल पूर्णांक mpc83xx_suspend_begin(suspend_state_t state)
अणु
	चयन (state) अणु
		हाल PM_SUSPEND_STANDBY:
			deep_sleeping = 0;
			वापस 0;

		हाल PM_SUSPEND_MEM:
			अगर (has_deep_sleep)
				deep_sleeping = 1;

			वापस 0;

		शेष:
			वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक agent_thपढ़ो_fn(व्योम *data)
अणु
	जबतक (1) अणु
		रुको_event_पूर्णांकerruptible(agent_wq, pci_pm_state >= 2);
		try_to_मुक्तze();

		अगर (संकेत_pending(current) || pci_pm_state < 2)
			जारी;

		/* With a preemptible kernel (or SMP), this could race with
		 * a userspace-driven suspend request.  It's probably best
		 * to aव्योम mixing the two with such a configuration (or
		 * अन्यथा fix it by adding a mutex to state_store that we can
		 * synchronize with).
		 */

		wake_from_pci = 1;

		pm_suspend(pci_pm_state == 3 ? PM_SUSPEND_MEM :
		                               PM_SUSPEND_STANDBY);

		wake_from_pci = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mpc83xx_set_agent(व्योम)
अणु
	out_be32(&pmc_regs->config1, PMCCR1_USE_STATE);
	out_be32(&pmc_regs->mask, PMCER_PMCI);

	kthपढ़ो_run(agent_thपढ़ो_fn, शून्य, "PCI power mgt");
पूर्ण

अटल पूर्णांक mpc83xx_is_pci_agent(व्योम)
अणु
	काष्ठा mpc83xx_rcw __iomem *rcw_regs;
	पूर्णांक ret;

	rcw_regs = ioremap(get_immrbase() + IMMR_RCW_OFFSET,
	                   माप(काष्ठा mpc83xx_rcw));

	अगर (!rcw_regs)
		वापस -ENOMEM;

	ret = !(in_be32(&rcw_regs->rcwhr) & RCW_PCI_HOST);

	iounmap(rcw_regs);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops mpc83xx_suspend_ops = अणु
	.valid = mpc83xx_suspend_valid,
	.begin = mpc83xx_suspend_begin,
	.enter = mpc83xx_suspend_enter,
	.end = mpc83xx_suspend_end,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[];
अटल पूर्णांक pmc_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा resource res;
	स्थिर काष्ठा pmc_type *type;
	पूर्णांक ret = 0;

	match = of_match_device(pmc_match, &ofdev->dev);
	अगर (!match)
		वापस -EINVAL;

	type = match->data;

	अगर (!of_device_is_available(np))
		वापस -ENODEV;

	has_deep_sleep = type->has_deep_sleep;
	immrbase = get_immrbase();
	pmc_dev = ofdev;

	is_pci_agent = mpc83xx_is_pci_agent();
	अगर (is_pci_agent < 0)
		वापस is_pci_agent;

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		वापस -ENODEV;

	pmc_irq = irq_of_parse_and_map(np, 0);
	अगर (pmc_irq) अणु
		ret = request_irq(pmc_irq, pmc_irq_handler, IRQF_SHARED,
		                  "pmc", ofdev);

		अगर (ret)
			वापस -EBUSY;
	पूर्ण

	pmc_regs = ioremap(res.start, माप(*pmc_regs));

	अगर (!pmc_regs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = of_address_to_resource(np, 1, &res);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ out_pmc;
	पूर्ण

	घड़ी_regs = ioremap(res.start, माप(*घड़ी_regs));

	अगर (!घड़ी_regs) अणु
		ret = -ENOMEM;
		जाओ out_pmc;
	पूर्ण

	अगर (has_deep_sleep) अणु
		syscr_regs = ioremap(immrbase + IMMR_SYSCR_OFFSET,
				     माप(*syscr_regs));
		अगर (!syscr_regs) अणु
			ret = -ENOMEM;
			जाओ out_syscr;
		पूर्ण
	पूर्ण

	अगर (is_pci_agent)
		mpc83xx_set_agent();

	suspend_set_ops(&mpc83xx_suspend_ops);
	वापस 0;

out_syscr:
	iounmap(घड़ी_regs);
out_pmc:
	iounmap(pmc_regs);
out:
	अगर (pmc_irq)
		मुक्त_irq(pmc_irq, ofdev);

	वापस ret;
पूर्ण

अटल पूर्णांक pmc_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	वापस -EPERM;
पूर्ण;

अटल काष्ठा pmc_type pmc_types[] = अणु
	अणु
		.has_deep_sleep = 1,
	पूर्ण,
	अणु
		.has_deep_sleep = 0,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id pmc_match[] = अणु
	अणु
		.compatible = "fsl,mpc8313-pmc",
		.data = &pmc_types[0],
	पूर्ण,
	अणु
		.compatible = "fsl,mpc8349-pmc",
		.data = &pmc_types[1],
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver pmc_driver = अणु
	.driver = अणु
		.name = "mpc83xx-pmc",
		.of_match_table = pmc_match,
	पूर्ण,
	.probe = pmc_probe,
	.हटाओ = pmc_हटाओ
पूर्ण;

builtin_platक्रमm_driver(pmc_driver);
