<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom BCM63138 PMB initialization क्रम secondary CPU(s)
 *
 * Copyright (C) 2015 Broadcom Corporation
 * Author: Florian Fainelli <f.fainelli@gmail.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/reset/bcm63xx_pmb.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश "bcm63xx_smp.h"

/* ARM Control रेजिस्टर definitions */
#घोषणा CORE_PWR_CTRL_SHIFT	0
#घोषणा CORE_PWR_CTRL_MASK	0x3
#घोषणा PLL_PWR_ON		BIT(8)
#घोषणा PLL_LDO_PWR_ON		BIT(9)
#घोषणा PLL_CLAMP_ON		BIT(10)
#घोषणा CPU_RESET_N(x)		BIT(13 + (x))
#घोषणा NEON_RESET_N		BIT(15)
#घोषणा PWR_CTRL_STATUS_SHIFT	28
#घोषणा PWR_CTRL_STATUS_MASK	0x3
#घोषणा PWR_DOWN_SHIFT		30
#घोषणा PWR_DOWN_MASK		0x3

/* CPU Power control रेजिस्टर definitions */
#घोषणा MEM_PWR_OK		BIT(0)
#घोषणा MEM_PWR_ON		BIT(1)
#घोषणा MEM_CLAMP_ON		BIT(2)
#घोषणा MEM_PWR_OK_STATUS	BIT(4)
#घोषणा MEM_PWR_ON_STATUS	BIT(5)
#घोषणा MEM_PDA_SHIFT		8
#घोषणा MEM_PDA_MASK		0xf
#घोषणा  MEM_PDA_CPU_MASK	0x1
#घोषणा  MEM_PDA_NEON_MASK	0xf
#घोषणा CLAMP_ON		BIT(15)
#घोषणा PWR_OK_SHIFT		16
#घोषणा PWR_OK_MASK		0xf
#घोषणा PWR_ON_SHIFT		20
#घोषणा  PWR_CPU_MASK		0x03
#घोषणा  PWR_NEON_MASK		0x01
#घोषणा PWR_ON_MASK		0xf
#घोषणा PWR_OK_STATUS_SHIFT	24
#घोषणा PWR_OK_STATUS_MASK	0xf
#घोषणा PWR_ON_STATUS_SHIFT	28
#घोषणा PWR_ON_STATUS_MASK	0xf

#घोषणा ARM_CONTROL		0x30
#घोषणा ARM_PWR_CONTROL_BASE	0x34
#घोषणा ARM_PWR_CONTROL(x)	(ARM_PWR_CONTROL_BASE + (x) * 0x4)
#घोषणा ARM_NEON_L2		0x3c

/* Perक्रमm a value ग_लिखो, then spin until the value shअगरted by
 * shअगरt is seen, masked with mask and is dअगरferent from cond.
 */
अटल पूर्णांक bpcm_wr_rd_mask(व्योम __iomem *master,
			   अचिन्हित पूर्णांक addr, u32 off, u32 *val,
			   u32 shअगरt, u32 mask, u32 cond)
अणु
	पूर्णांक ret;

	ret = bpcm_wr(master, addr, off, *val);
	अगर (ret)
		वापस ret;

	करो अणु
		ret = bpcm_rd(master, addr, off, val);
		अगर (ret)
			वापस ret;

		cpu_relax();
	पूर्ण जबतक (((*val >> shअगरt) & mask) != cond);

	वापस ret;
पूर्ण

/* Global lock to serialize accesses to the PMB रेजिस्टरs जबतक we
 * are bringing up the secondary CPU
 */
अटल DEFINE_SPINLOCK(pmb_lock);

अटल पूर्णांक bcm63xx_pmb_get_resources(काष्ठा device_node *dn,
				     व्योम __iomem **base,
				     अचिन्हित पूर्णांक *cpu,
				     अचिन्हित पूर्णांक *addr)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(dn, "reg", cpu);
	अगर (ret) अणु
		pr_err("CPU is missing a reg node\n");
		वापस ret;
	पूर्ण

	ret = of_parse_phandle_with_args(dn, "resets", "#reset-cells",
					 0, &args);
	अगर (ret) अणु
		pr_err("CPU is missing a resets phandle\n");
		वापस ret;
	पूर्ण

	अगर (args.args_count != 2) अणु
		pr_err("reset-controller does not conform to reset-cells\n");
		वापस -EINVAL;
	पूर्ण

	*base = of_iomap(args.np, 0);
	अगर (!*base) अणु
		pr_err("failed remapping PMB register\n");
		वापस -ENOMEM;
	पूर्ण

	/* We करो not need the number of zones */
	*addr = args.args[0];

	वापस 0;
पूर्ण

पूर्णांक bcm63xx_pmb_घातer_on_cpu(काष्ठा device_node *dn)
अणु
	व्योम __iomem *base;
	अचिन्हित पूर्णांक cpu, addr;
	अचिन्हित दीर्घ flags;
	u32 val, ctrl;
	पूर्णांक ret;

	ret = bcm63xx_pmb_get_resources(dn, &base, &cpu, &addr);
	अगर (ret)
		वापस ret;

	/* We would not know how to enable a third and greater CPU */
	WARN_ON(cpu > 1);

	spin_lock_irqsave(&pmb_lock, flags);

	/* Check अगर the CPU is alपढ़ोy on and save the ARM_CONTROL रेजिस्टर
	 * value since we will use it later क्रम CPU de-निश्चित once करोne with
	 * the CPU-specअगरic घातer sequence
	 */
	ret = bpcm_rd(base, addr, ARM_CONTROL, &ctrl);
	अगर (ret)
		जाओ out;

	अगर (ctrl & CPU_RESET_N(cpu)) अणु
		pr_info("PMB: CPU%d is already powered on\n", cpu);
		ret = 0;
		जाओ out;
	पूर्ण

	/* Power on PLL */
	ret = bpcm_rd(base, addr, ARM_PWR_CONTROL(cpu), &val);
	अगर (ret)
		जाओ out;

	val |= (PWR_CPU_MASK << PWR_ON_SHIFT);

	ret = bpcm_wr_rd_mask(base, addr, ARM_PWR_CONTROL(cpu), &val,
			PWR_ON_STATUS_SHIFT, PWR_CPU_MASK, PWR_CPU_MASK);
	अगर (ret)
		जाओ out;

	val |= (PWR_CPU_MASK << PWR_OK_SHIFT);

	ret = bpcm_wr_rd_mask(base, addr, ARM_PWR_CONTROL(cpu), &val,
			PWR_OK_STATUS_SHIFT, PWR_CPU_MASK, PWR_CPU_MASK);
	अगर (ret)
		जाओ out;

	val &= ~CLAMP_ON;

	ret = bpcm_wr(base, addr, ARM_PWR_CONTROL(cpu), val);
	अगर (ret)
		जाओ out;

	/* Power on CPU<N> RAM */
	val &= ~(MEM_PDA_MASK << MEM_PDA_SHIFT);

	ret = bpcm_wr(base, addr, ARM_PWR_CONTROL(cpu), val);
	अगर (ret)
		जाओ out;

	val |= MEM_PWR_ON;

	ret = bpcm_wr_rd_mask(base, addr, ARM_PWR_CONTROL(cpu), &val,
			0, MEM_PWR_ON_STATUS, MEM_PWR_ON_STATUS);
	अगर (ret)
		जाओ out;

	val |= MEM_PWR_OK;

	ret = bpcm_wr_rd_mask(base, addr, ARM_PWR_CONTROL(cpu), &val,
			0, MEM_PWR_OK_STATUS, MEM_PWR_OK_STATUS);
	अगर (ret)
		जाओ out;

	val &= ~MEM_CLAMP_ON;

	ret = bpcm_wr(base, addr, ARM_PWR_CONTROL(cpu), val);
	अगर (ret)
		जाओ out;

	/* De-निश्चित CPU reset */
	ctrl |= CPU_RESET_N(cpu);

	ret = bpcm_wr(base, addr, ARM_CONTROL, ctrl);
out:
	spin_unlock_irqrestore(&pmb_lock, flags);
	iounmap(base);
	वापस ret;
पूर्ण
