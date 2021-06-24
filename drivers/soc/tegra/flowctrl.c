<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/soc/tegra/flowctrl.c
 *
 * Functions and macros to control the flowcontroller
 *
 * Copyright (c) 2010-2012, NVIDIA Corporation. All rights reserved.
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <soc/tegra/common.h>
#समावेश <soc/tegra/flowctrl.h>
#समावेश <soc/tegra/fuse.h>

अटल u8 flowctrl_offset_halt_cpu[] = अणु
	FLOW_CTRL_HALT_CPU0_EVENTS,
	FLOW_CTRL_HALT_CPU1_EVENTS,
	FLOW_CTRL_HALT_CPU1_EVENTS + 8,
	FLOW_CTRL_HALT_CPU1_EVENTS + 16,
पूर्ण;

अटल u8 flowctrl_offset_cpu_csr[] = अणु
	FLOW_CTRL_CPU0_CSR,
	FLOW_CTRL_CPU1_CSR,
	FLOW_CTRL_CPU1_CSR + 8,
	FLOW_CTRL_CPU1_CSR + 16,
पूर्ण;

अटल व्योम __iomem *tegra_flowctrl_base;

अटल व्योम flowctrl_update(u8 offset, u32 value)
अणु
	अगर (WARN_ONCE(IS_ERR_OR_शून्य(tegra_flowctrl_base),
		      "Tegra flowctrl not initialised!\n"))
		वापस;

	ग_लिखोl(value, tegra_flowctrl_base + offset);

	/* ensure the update has reached the flow controller */
	wmb();
	पढ़ोl_relaxed(tegra_flowctrl_base + offset);
पूर्ण

u32 flowctrl_पढ़ो_cpu_csr(अचिन्हित पूर्णांक cpuid)
अणु
	u8 offset = flowctrl_offset_cpu_csr[cpuid];

	अगर (WARN_ONCE(IS_ERR_OR_शून्य(tegra_flowctrl_base),
		      "Tegra flowctrl not initialised!\n"))
		वापस 0;

	वापस पढ़ोl(tegra_flowctrl_base + offset);
पूर्ण

व्योम flowctrl_ग_लिखो_cpu_csr(अचिन्हित पूर्णांक cpuid, u32 value)
अणु
	वापस flowctrl_update(flowctrl_offset_cpu_csr[cpuid], value);
पूर्ण

व्योम flowctrl_ग_लिखो_cpu_halt(अचिन्हित पूर्णांक cpuid, u32 value)
अणु
	वापस flowctrl_update(flowctrl_offset_halt_cpu[cpuid], value);
पूर्ण

व्योम flowctrl_cpu_suspend_enter(अचिन्हित पूर्णांक cpuid)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;

	reg = flowctrl_पढ़ो_cpu_csr(cpuid);
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		/* clear wfe biपंचांगap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi biपंचांगap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP;
		/* pwr gating on wfe */
		reg |= TEGRA20_FLOW_CTRL_CSR_WFE_CPU0 << cpuid;
		अवरोध;
	हाल TEGRA30:
	हाल TEGRA114:
	हाल TEGRA124:
		/* clear wfe biपंचांगap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi biपंचांगap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP;

		अगर (tegra_get_chip_id() == TEGRA30) अणु
			/*
			 * The wfi करोesn't work well on Tegra30 because
			 * CPU hangs under some odd circumstances after
			 * घातer-gating (like memory running off PLLP),
			 * hence use wfe that is working perfectly fine.
			 * Note that Tegra30 TRM करोc clearly stands that
			 * wfi should be used क्रम the "Cluster Switching",
			 * जबतक wfe क्रम the घातer-gating, just like it
			 * is करोne on Tegra20.
			 */
			reg |= TEGRA20_FLOW_CTRL_CSR_WFE_CPU0 << cpuid;
		पूर्ण अन्यथा अणु
			/* pwr gating on wfi */
			reg |= TEGRA30_FLOW_CTRL_CSR_WFI_CPU0 << cpuid;
		पूर्ण
		अवरोध;
	पूर्ण
	reg |= FLOW_CTRL_CSR_INTR_FLAG;			/* clear पूर्णांकr flag */
	reg |= FLOW_CTRL_CSR_EVENT_FLAG;		/* clear event flag */
	reg |= FLOW_CTRL_CSR_ENABLE;			/* pwr gating */
	flowctrl_ग_लिखो_cpu_csr(cpuid, reg);

	क्रम (i = 0; i < num_possible_cpus(); i++) अणु
		अगर (i == cpuid)
			जारी;
		reg = flowctrl_पढ़ो_cpu_csr(i);
		reg |= FLOW_CTRL_CSR_EVENT_FLAG;
		reg |= FLOW_CTRL_CSR_INTR_FLAG;
		flowctrl_ग_लिखो_cpu_csr(i, reg);
	पूर्ण
पूर्ण

व्योम flowctrl_cpu_suspend_निकास(अचिन्हित पूर्णांक cpuid)
अणु
	अचिन्हित पूर्णांक reg;

	/* Disable घातergating via flow controller क्रम CPU0 */
	reg = flowctrl_पढ़ो_cpu_csr(cpuid);
	चयन (tegra_get_chip_id()) अणु
	हाल TEGRA20:
		/* clear wfe biपंचांगap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi biपंचांगap */
		reg &= ~TEGRA20_FLOW_CTRL_CSR_WFI_BITMAP;
		अवरोध;
	हाल TEGRA30:
	हाल TEGRA114:
	हाल TEGRA124:
		/* clear wfe biपंचांगap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFE_BITMAP;
		/* clear wfi biपंचांगap */
		reg &= ~TEGRA30_FLOW_CTRL_CSR_WFI_BITMAP;
		अवरोध;
	पूर्ण
	reg &= ~FLOW_CTRL_CSR_ENABLE;			/* clear enable */
	reg |= FLOW_CTRL_CSR_INTR_FLAG;			/* clear पूर्णांकr */
	reg |= FLOW_CTRL_CSR_EVENT_FLAG;		/* clear event */
	flowctrl_ग_लिखो_cpu_csr(cpuid, reg);
पूर्ण

अटल पूर्णांक tegra_flowctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	व्योम __iomem *base = tegra_flowctrl_base;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tegra_flowctrl_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(tegra_flowctrl_base))
		वापस PTR_ERR(tegra_flowctrl_base);

	iounmap(base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_flowctrl_match[] = अणु
	अणु .compatible = "nvidia,tegra210-flowctrl" पूर्ण,
	अणु .compatible = "nvidia,tegra124-flowctrl" पूर्ण,
	अणु .compatible = "nvidia,tegra114-flowctrl" पूर्ण,
	अणु .compatible = "nvidia,tegra30-flowctrl" पूर्ण,
	अणु .compatible = "nvidia,tegra20-flowctrl" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_flowctrl_driver = अणु
	.driver = अणु
		.name = "tegra-flowctrl",
		.suppress_bind_attrs = true,
		.of_match_table = tegra_flowctrl_match,
	पूर्ण,
	.probe = tegra_flowctrl_probe,
पूर्ण;
builtin_platक्रमm_driver(tegra_flowctrl_driver);

अटल पूर्णांक __init tegra_flowctrl_init(व्योम)
अणु
	काष्ठा resource res;
	काष्ठा device_node *np;

	अगर (!soc_is_tegra())
		वापस 0;

	np = of_find_matching_node(शून्य, tegra_flowctrl_match);
	अगर (np) अणु
		अगर (of_address_to_resource(np, 0, &res) < 0) अणु
			pr_err("failed to get flowctrl register\n");
			वापस -ENXIO;
		पूर्ण
		of_node_put(np);
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_ARM)) अणु
		/*
		 * Hardcoded fallback क्रम 32-bit Tegra
		 * devices अगर device tree node is missing.
		 */
		res.start = 0x60007000;
		res.end = 0x60007fff;
		res.flags = IORESOURCE_MEM;
	पूर्ण अन्यथा अणु
		/*
		 * At this poपूर्णांक we're running on a Tegra,
		 * that करोesn't support the flow controller
		 * (eg. Tegra186), so just वापस.
		 */
		वापस 0;
	पूर्ण

	tegra_flowctrl_base = ioremap(res.start, resource_size(&res));
	अगर (!tegra_flowctrl_base)
		वापस -ENXIO;

	वापस 0;
पूर्ण
early_initcall(tegra_flowctrl_init);
