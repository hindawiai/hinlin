<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2009 ST-Ericsson SA
 *
 * Author: Srinidhi KASAGAR <srinidhi.kasagar@stericsson.com>
 */
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/platक्रमm_data/arm-ux500-pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regulator/machine.h>

#समावेश <यंत्र/outercache.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "db8500-regs.h"
#समावेश "pm_domains.h"

अटल पूर्णांक __init ux500_l2x0_unlock(व्योम)
अणु
	पूर्णांक i;
	काष्ठा device_node *np;
	व्योम __iomem *l2x0_base;

	np = of_find_compatible_node(शून्य, शून्य, "arm,pl310-cache");
	l2x0_base = of_iomap(np, 0);
	of_node_put(np);
	अगर (!l2x0_base)
		वापस -ENODEV;

	/*
	 * Unlock Data and Inकाष्ठाion Lock अगर locked. Ux500 U-Boot versions
	 * apparently locks both caches beक्रमe jumping to the kernel. The
	 * l2x0 core will not touch the unlock रेजिस्टरs अगर the l2x0 is
	 * alपढ़ोy enabled, so we करो it right here instead. The PL310 has
	 * 8 sets of रेजिस्टरs, one per possible CPU.
	 */
	क्रम (i = 0; i < 8; i++) अणु
		ग_लिखोl_relaxed(0x0, l2x0_base + L2X0_LOCKDOWN_WAY_D_BASE +
			       i * L2X0_LOCKDOWN_STRIDE);
		ग_लिखोl_relaxed(0x0, l2x0_base + L2X0_LOCKDOWN_WAY_I_BASE +
			       i * L2X0_LOCKDOWN_STRIDE);
	पूर्ण
	iounmap(l2x0_base);
	वापस 0;
पूर्ण

अटल व्योम ux500_l2c310_ग_लिखो_sec(अचिन्हित दीर्घ val, अचिन्हित reg)
अणु
	/*
	 * We can't ग_लिखो to secure रेजिस्टरs as we are in non-secure
	 * mode, until we have some SMI service available.
	 */
पूर्ण

/*
 * FIXME: Should we set up the GPIO करोमुख्य here?
 *
 * The problem is that we cannot put the पूर्णांकerrupt resources पूर्णांकo the platक्रमm
 * device until the irqकरोमुख्य has been added. Right now, we set the GIC पूर्णांकerrupt
 * करोमुख्य from init_irq(), then load the gpio driver from
 * core_initcall(nmk_gpio_init) and add the platक्रमm devices from
 * arch_initcall(customize_machine).
 *
 * This feels fragile because it depends on the gpio device getting probed
 * _beक्रमe_ any device uses the gpio पूर्णांकerrupts.
*/
अटल व्योम __init ux500_init_irq(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource r;

	irqchip_init();
	prcmu_early_init();
	np = of_find_compatible_node(शून्य, शून्य, "stericsson,db8500-prcmu");
	of_address_to_resource(np, 0, &r);
	of_node_put(np);
	अगर (!r.start) अणु
		pr_err("could not find PRCMU base resource\n");
		वापस;
	पूर्ण
	ux500_pm_init(r.start, r.end-r.start);

	/* Unlock beक्रमe init */
	ux500_l2x0_unlock();
	outer_cache.ग_लिखो_sec = ux500_l2c310_ग_लिखो_sec;
पूर्ण

अटल व्योम ux500_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	local_irq_disable();
	local_fiq_disable();

	prcmu_प्रणाली_reset(0);
पूर्ण

अटल स्थिर काष्ठा of_device_id u8500_local_bus_nodes[] = अणु
	/* only create devices below soc node */
	अणु .compatible = "stericsson,db8500", पूर्ण,
	अणु .compatible = "simple-bus"पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम __init u8500_init_machine(व्योम)
अणु
	/* Initialize ux500 घातer करोमुख्यs */
	ux500_pm_करोमुख्यs_init();

	of_platक्रमm_populate(शून्य, u8500_local_bus_nodes,
			     शून्य, शून्य);
पूर्ण

अटल स्थिर अक्षर * stericsson_dt_platक्रमm_compat[] = अणु
	"st-ericsson,u8500",
	"st-ericsson,u9500",
	शून्य,
पूर्ण;

DT_MACHINE_START(U8500_DT, "ST-Ericsson Ux5x0 platform (Device Tree Support)")
	.l2c_aux_val    = 0,
	.l2c_aux_mask	= ~0,
	.init_irq	= ux500_init_irq,
	.init_machine	= u8500_init_machine,
	.dt_compat      = stericsson_dt_platक्रमm_compat,
	.restart        = ux500_restart,
MACHINE_END
