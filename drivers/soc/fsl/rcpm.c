<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rcpm.c - Freescale QorIQ RCPM driver
//
// Copyright 2019-2020 NXP
//
// Author: Ran Wang <ran.wang_1@nxp.com>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>

#घोषणा RCPM_WAKEUP_CELL_MAX_SIZE	7

काष्ठा rcpm अणु
	अचिन्हित पूर्णांक	wakeup_cells;
	व्योम __iomem	*ippdexpcr_base;
	bool		little_endian;
पूर्ण;

#घोषणा  SCFG_SPARECR8	0x051c

अटल व्योम copy_ippdexpcr1_setting(u32 val)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *regs;
	u32 reg_val;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,ls1021a-scfg");
	अगर (!np)
		वापस;

	regs = of_iomap(np, 0);
	अगर (!regs)
		वापस;

	reg_val = ioपढ़ो32be(regs + SCFG_SPARECR8);
	ioग_लिखो32be(val | reg_val, regs + SCFG_SPARECR8);

	iounmap(regs);
पूर्ण

/**
 * rcpm_pm_prepare - perक्रमms device-level tasks associated with घातer
 * management, such as programming related to the wakeup source control.
 * @dev: Device to handle.
 *
 */
अटल पूर्णांक rcpm_pm_prepare(काष्ठा device *dev)
अणु
	पूर्णांक i, ret, idx;
	व्योम __iomem *base;
	काष्ठा wakeup_source	*ws;
	काष्ठा rcpm		*rcpm;
	काष्ठा device_node	*np = dev->of_node;
	u32 value[RCPM_WAKEUP_CELL_MAX_SIZE + 1];
	u32 setting[RCPM_WAKEUP_CELL_MAX_SIZE] = अणु0पूर्ण;

	rcpm = dev_get_drvdata(dev);
	अगर (!rcpm)
		वापस -EINVAL;

	base = rcpm->ippdexpcr_base;
	idx = wakeup_sources_पढ़ो_lock();

	/* Begin with first रेजिस्टरed wakeup source */
	क्रम_each_wakeup_source(ws) अणु

		/* skip object which is not attached to device */
		अगर (!ws->dev || !ws->dev->parent)
			जारी;

		ret = device_property_पढ़ो_u32_array(ws->dev->parent,
				"fsl,rcpm-wakeup", value,
				rcpm->wakeup_cells + 1);

		अगर (ret)
			जारी;

		/*
		 * For DT mode, would handle devices with "fsl,rcpm-wakeup"
		 * poपूर्णांकing to the current RCPM node.
		 *
		 * For ACPI mode, currently we assume there is only one
		 * RCPM controller existing.
		 */
		अगर (is_of_node(dev->fwnode))
			अगर (np->phandle != value[0])
				जारी;

		/* Property "#fsl,rcpm-wakeup-cells" of rcpm node defines the
		 * number of IPPDEXPCR रेजिस्टर cells, and "fsl,rcpm-wakeup"
		 * of wakeup source IP contains an पूर्णांकeger array: <phandle to
		 * RCPM node, IPPDEXPCR0 setting, IPPDEXPCR1 setting,
		 * IPPDEXPCR2 setting, etc>.
		 *
		 * So we will go thought them to collect setting data.
		 */
		क्रम (i = 0; i < rcpm->wakeup_cells; i++)
			setting[i] |= value[i + 1];
	पूर्ण

	wakeup_sources_पढ़ो_unlock(idx);

	/* Program all IPPDEXPCRn once */
	क्रम (i = 0; i < rcpm->wakeup_cells; i++) अणु
		u32 पंचांगp = setting[i];
		व्योम __iomem *address = base + i * 4;

		अगर (!पंचांगp)
			जारी;

		/* We can only OR related bits */
		अगर (rcpm->little_endian) अणु
			पंचांगp |= ioपढ़ो32(address);
			ioग_लिखो32(पंचांगp, address);
		पूर्ण अन्यथा अणु
			पंचांगp |= ioपढ़ो32be(address);
			ioग_लिखो32be(पंचांगp, address);
		पूर्ण
		/*
		 * Workaround of errata A-008646 on SoC LS1021A:
		 * There is a bug of रेजिस्टर ippdexpcr1.
		 * Reading configuration रेजिस्टर RCPM_IPPDEXPCR1
		 * always वापस zero. So save ippdexpcr1's value
		 * to रेजिस्टर SCFG_SPARECR8.And the value of
		 * ippdexpcr1 will be पढ़ो from SCFG_SPARECR8.
		 */
		अगर (dev_of_node(dev) && (i == 1))
			अगर (of_device_is_compatible(np, "fsl,ls1021a-rcpm"))
				copy_ippdexpcr1_setting(पंचांगp);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rcpm_pm_ops = अणु
	.prepare =  rcpm_pm_prepare,
पूर्ण;

अटल पूर्णांक rcpm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device	*dev = &pdev->dev;
	काष्ठा resource *r;
	काष्ठा rcpm	*rcpm;
	पूर्णांक ret;

	rcpm = devm_kzalloc(dev, माप(*rcpm), GFP_KERNEL);
	अगर (!rcpm)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r)
		वापस -ENODEV;

	rcpm->ippdexpcr_base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(rcpm->ippdexpcr_base)) अणु
		ret =  PTR_ERR(rcpm->ippdexpcr_base);
		वापस ret;
	पूर्ण

	rcpm->little_endian = device_property_पढ़ो_bool(
			&pdev->dev, "little-endian");

	ret = device_property_पढ़ो_u32(&pdev->dev,
			"#fsl,rcpm-wakeup-cells", &rcpm->wakeup_cells);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(&pdev->dev, rcpm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcpm_of_match[] = अणु
	अणु .compatible = "fsl,qoriq-rcpm-2.1+", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcpm_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rcpm_acpi_ids[] = अणु
	अणु"NXP0015",पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rcpm_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rcpm_driver = अणु
	.driver = अणु
		.name = "rcpm",
		.of_match_table = rcpm_of_match,
		.acpi_match_table = ACPI_PTR(rcpm_acpi_ids),
		.pm	= &rcpm_pm_ops,
	पूर्ण,
	.probe = rcpm_probe,
पूर्ण;

module_platक्रमm_driver(rcpm_driver);
