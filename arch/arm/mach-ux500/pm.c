<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010-2013
 * Author: Rickard Andersson <rickard.andersson@stericsson.com> क्रम
 *         ST-Ericsson.
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org> क्रम Linaro.
 * Author: Ulf Hansson <ulf.hansson@linaro.org> क्रम Linaro.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/suspend.h>
#समावेश <linux/platक्रमm_data/arm-ux500-pm.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "db8500-regs.h"

/* ARM WFI Standby संकेत रेजिस्टर */
#घोषणा PRCM_ARM_WFI_STANDBY    (prcmu_base + 0x130)
#घोषणा PRCM_ARM_WFI_STANDBY_WFI0		0x08
#घोषणा PRCM_ARM_WFI_STANDBY_WFI1		0x10
#घोषणा PRCM_IOCR		(prcmu_base + 0x310)
#घोषणा PRCM_IOCR_IOFORCE			0x1

/* Dual A9 core पूर्णांकerrupt management unit रेजिस्टरs */
#घोषणा PRCM_A9_MASK_REQ	(prcmu_base + 0x328)
#घोषणा PRCM_A9_MASK_REQ_PRCM_A9_MASK_REQ	0x1

#घोषणा PRCM_A9_MASK_ACK	(prcmu_base + 0x32c)
#घोषणा PRCM_ARMITMSK31TO0	(prcmu_base + 0x11c)
#घोषणा PRCM_ARMITMSK63TO32	(prcmu_base + 0x120)
#घोषणा PRCM_ARMITMSK95TO64	(prcmu_base + 0x124)
#घोषणा PRCM_ARMITMSK127TO96	(prcmu_base + 0x128)
#घोषणा PRCM_POWER_STATE_VAL	(prcmu_base + 0x25C)
#घोषणा PRCM_ARMITVAL31TO0	(prcmu_base + 0x260)
#घोषणा PRCM_ARMITVAL63TO32	(prcmu_base + 0x264)
#घोषणा PRCM_ARMITVAL95TO64	(prcmu_base + 0x268)
#घोषणा PRCM_ARMITVAL127TO96	(prcmu_base + 0x26C)

अटल व्योम __iomem *prcmu_base;
अटल व्योम __iomem *dist_base;

/* This function decouple the gic from the prcmu */
पूर्णांक prcmu_gic_decouple(व्योम)
अणु
	u32 val = पढ़ोl(PRCM_A9_MASK_REQ);

	/* Set bit 0 रेजिस्टर value to 1 */
	ग_लिखोl(val | PRCM_A9_MASK_REQ_PRCM_A9_MASK_REQ,
	       PRCM_A9_MASK_REQ);

	/* Make sure the रेजिस्टर is updated */
	पढ़ोl(PRCM_A9_MASK_REQ);

	/* Wait a few cycles क्रम the gic mask completion */
	udelay(1);

	वापस 0;
पूर्ण

/* This function recouple the gic with the prcmu */
पूर्णांक prcmu_gic_recouple(व्योम)
अणु
	u32 val = पढ़ोl(PRCM_A9_MASK_REQ);

	/* Set bit 0 रेजिस्टर value to 0 */
	ग_लिखोl(val & ~PRCM_A9_MASK_REQ_PRCM_A9_MASK_REQ, PRCM_A9_MASK_REQ);

	वापस 0;
पूर्ण

#घोषणा PRCMU_GIC_NUMBER_REGS 5

/*
 * This function checks अगर there are pending irq on the gic. It only
 * makes sense अगर the gic has been decoupled beक्रमe with the
 * db8500_prcmu_gic_decouple function. Disabling an पूर्णांकerrupt only
 * disables the क्रमwarding of the पूर्णांकerrupt to any CPU पूर्णांकerface. It
 * करोes not prevent the पूर्णांकerrupt from changing state, क्रम example
 * becoming pending, or active and pending अगर it is alपढ़ोy
 * active. Hence, we have to check the पूर्णांकerrupt is pending *and* is
 * active.
 */
bool prcmu_gic_pending_irq(व्योम)
अणु
	u32 pr; /* Pending रेजिस्टर */
	u32 er; /* Enable रेजिस्टर */
	पूर्णांक i;

	/* 5 रेजिस्टरs. STI & PPI not skipped */
	क्रम (i = 0; i < PRCMU_GIC_NUMBER_REGS; i++) अणु

		pr = पढ़ोl_relaxed(dist_base + GIC_DIST_PENDING_SET + i * 4);
		er = पढ़ोl_relaxed(dist_base + GIC_DIST_ENABLE_SET + i * 4);

		अगर (pr & er)
			वापस true; /* There is a pending पूर्णांकerrupt */
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function checks अगर there are pending पूर्णांकerrupt on the
 * prcmu which has been delegated to monitor the irqs with the
 * db8500_prcmu_copy_gic_settings function.
 */
bool prcmu_pending_irq(व्योम)
अणु
	u32 it, im;
	पूर्णांक i;

	क्रम (i = 0; i < PRCMU_GIC_NUMBER_REGS - 1; i++) अणु
		it = पढ़ोl(PRCM_ARMITVAL31TO0 + i * 4);
		im = पढ़ोl(PRCM_ARMITMSK31TO0 + i * 4);
		अगर (it & im)
			वापस true; /* There is a pending पूर्णांकerrupt */
	पूर्ण

	वापस false;
पूर्ण

/*
 * This function checks अगर the specअगरied cpu is in in WFI. It's usage
 * makes sense only अगर the gic is decoupled with the db8500_prcmu_gic_decouple
 * function. Of course passing smp_processor_id() to this function will
 * always वापस false...
 */
bool prcmu_is_cpu_in_wfi(पूर्णांक cpu)
अणु
	वापस पढ़ोl(PRCM_ARM_WFI_STANDBY) &
		(cpu ? PRCM_ARM_WFI_STANDBY_WFI1 : PRCM_ARM_WFI_STANDBY_WFI0);
पूर्ण

/*
 * This function copies the gic SPI settings to the prcmu in order to
 * monitor them and पात/finish the retention/off sequence or state.
 */
पूर्णांक prcmu_copy_gic_settings(व्योम)
अणु
	u32 er; /* Enable रेजिस्टर */
	पूर्णांक i;

	/* We skip the STI and PPI */
	क्रम (i = 0; i < PRCMU_GIC_NUMBER_REGS - 1; i++) अणु
		er = पढ़ोl_relaxed(dist_base +
				   GIC_DIST_ENABLE_SET + (i + 1) * 4);
		ग_लिखोl(er, PRCM_ARMITMSK31TO0 + i * 4);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक ux500_suspend_enter(suspend_state_t state)
अणु
	cpu_करो_idle();
	वापस 0;
पूर्ण

अटल पूर्णांक ux500_suspend_valid(suspend_state_t state)
अणु
	वापस state == PM_SUSPEND_MEM || state == PM_SUSPEND_STANDBY;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops ux500_suspend_ops = अणु
	.enter	      = ux500_suspend_enter,
	.valid	      = ux500_suspend_valid,
पूर्ण;
#घोषणा UX500_SUSPEND_OPS	(&ux500_suspend_ops)
#अन्यथा
#घोषणा UX500_SUSPEND_OPS	शून्य
#पूर्ण_अगर

व्योम __init ux500_pm_init(u32 phy_base, u32 size)
अणु
	काष्ठा device_node *np;

	prcmu_base = ioremap(phy_base, size);
	अगर (!prcmu_base) अणु
		pr_err("could not remap PRCMU for PM functions\n");
		वापस;
	पूर्ण
	np = of_find_compatible_node(शून्य, शून्य, "arm,cortex-a9-gic");
	dist_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!dist_base) अणु
		pr_err("could not remap GIC dist base for PM functions\n");
		वापस;
	पूर्ण

	/*
	 * On watchकरोg reboot the GIC is in some हालs decoupled.
	 * This will make sure that the GIC is correctly configured.
	 */
	prcmu_gic_recouple();

	/* Set up ux500 suspend callbacks. */
	suspend_set_ops(UX500_SUSPEND_OPS);
पूर्ण
