<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#घोषणा REG_ILL_ACC_ADDR	0x10
#घोषणा REG_ILL_ACC_TYPE	0x14

#घोषणा ILL_INT_STATUS		BIT(31)
#घोषणा ILL_ACC_WRITE		BIT(30)
#घोषणा ILL_ACC_LEN_M		0xff
#घोषणा ILL_ACC_OFF_M		0xf
#घोषणा ILL_ACC_OFF_S		16
#घोषणा ILL_ACC_ID_M		0x7
#घोषणा ILL_ACC_ID_S		8

#घोषणा	DRV_NAME		"ill_acc"

अटल स्थिर अक्षर * स्थिर ill_acc_ids[] = अणु
	"cpu", "dma", "ppe", "pdma rx", "pdma tx", "pci/e", "wmac", "usb",
पूर्ण;

अटल irqवापस_t ill_acc_irq_handler(पूर्णांक irq, व्योम *_priv)
अणु
	काष्ठा device *dev = (काष्ठा device *) _priv;
	u32 addr = rt_memc_r32(REG_ILL_ACC_ADDR);
	u32 type = rt_memc_r32(REG_ILL_ACC_TYPE);

	dev_err(dev, "illegal %s access from %s - addr:0x%08x offset:%d len:%d\n",
		(type & ILL_ACC_WRITE) ? ("write") : ("read"),
		ill_acc_ids[(type >> ILL_ACC_ID_S) & ILL_ACC_ID_M],
		addr, (type >> ILL_ACC_OFF_S) & ILL_ACC_OFF_M,
		type & ILL_ACC_LEN_M);

	rt_memc_w32(ILL_INT_STATUS, REG_ILL_ACC_TYPE);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init ill_acc_of_setup(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	पूर्णांक irq;

	/* somehow this driver अवरोधs on RT5350 */
	अगर (of_machine_is_compatible("ralink,rt5350-soc"))
		वापस -EINVAL;

	np = of_find_compatible_node(शून्य, शून्य, "ralink,rt3050-memc");
	अगर (!np)
		वापस -EINVAL;

	pdev = of_find_device_by_node(np);
	अगर (!pdev) अणु
		pr_err("%pOFn: failed to lookup pdev\n", np);
		वापस -EINVAL;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "failed to get irq\n");
		put_device(&pdev->dev);
		वापस -EINVAL;
	पूर्ण

	अगर (request_irq(irq, ill_acc_irq_handler, 0, "ill_acc", &pdev->dev)) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		put_device(&pdev->dev);
		वापस -EINVAL;
	पूर्ण

	rt_memc_w32(ILL_INT_STATUS, REG_ILL_ACC_TYPE);

	dev_info(&pdev->dev, "irq registered\n");

	वापस 0;
पूर्ण

arch_initcall(ill_acc_of_setup);
