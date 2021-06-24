<शैली गुरु>
/*
 * ID and revision inक्रमmation क्रम mvebu SoCs
 *
 * Copyright (C) 2014 Marvell
 *
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * All the mvebu SoCs have inक्रमmation related to their variant and
 * revision that can be पढ़ो from the PCI control रेजिस्टर. This is
 * करोne beक्रमe the PCI initialization to aव्योम any conflict. Once the
 * ID and revision are retrieved, the mapping is मुक्तd.
 */

#घोषणा pr_fmt(fmt) "mvebu-soc-id: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश "common.h"
#समावेश "mvebu-soc-id.h"

#घोषणा PCIE_DEV_ID_OFF		0x0
#घोषणा PCIE_DEV_REV_OFF	0x8

#घोषणा SOC_ID_MASK	    0xFFFF0000
#घोषणा SOC_REV_MASK	    0xFF

अटल u32 soc_dev_id;
अटल u32 soc_rev;
अटल bool is_id_valid;

अटल स्थिर काष्ठा of_device_id mvebu_pcie_of_match_table[] = अणु
	अणु .compatible = "marvell,armada-xp-pcie", पूर्ण,
	अणु .compatible = "marvell,armada-370-pcie", पूर्ण,
	अणु .compatible = "marvell,kirkwood-pcie" पूर्ण,
	अणुपूर्ण,
पूर्ण;

पूर्णांक mvebu_get_soc_id(u32 *dev, u32 *rev)
अणु
	अगर (is_id_valid) अणु
		*dev = soc_dev_id;
		*rev = soc_rev;
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENODEV;
पूर्ण

अटल पूर्णांक __init get_soc_id_by_pci(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret = 0;
	व्योम __iomem *pci_base;
	काष्ठा clk *clk;
	काष्ठा device_node *child;

	np = of_find_matching_node(शून्य, mvebu_pcie_of_match_table);
	अगर (!np)
		वापस ret;

	/*
	 * ID and revision are available from any port, so we
	 * just pick the first one
	 */
	child = of_get_next_child(np, शून्य);
	अगर (child == शून्य) अणु
		pr_err("cannot get pci node\n");
		ret = -ENOMEM;
		जाओ clk_err;
	पूर्ण

	clk = of_clk_get_by_name(child, शून्य);
	अगर (IS_ERR(clk)) अणु
		pr_err("cannot get clock\n");
		ret = -ENOMEM;
		जाओ clk_err;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("cannot enable clock\n");
		जाओ clk_err;
	पूर्ण

	pci_base = of_iomap(child, 0);
	अगर (pci_base == शून्य) अणु
		pr_err("cannot map registers\n");
		ret = -ENOMEM;
		जाओ res_ioremap;
	पूर्ण

	/* SoC ID */
	soc_dev_id = पढ़ोl(pci_base + PCIE_DEV_ID_OFF) >> 16;

	/* SoC revision */
	soc_rev = पढ़ोl(pci_base + PCIE_DEV_REV_OFF) & SOC_REV_MASK;

	is_id_valid = true;

	pr_info("MVEBU SoC ID=0x%X, Rev=0x%X\n", soc_dev_id, soc_rev);

	iounmap(pci_base);

res_ioremap:
	/*
	 * If the PCIe unit is actually enabled and we have PCI
	 * support in the kernel, we पूर्णांकentionally करो not release the
	 * reference to the घड़ी. We want to keep it running since
	 * the bootloader करोes some PCIe link configuration that the
	 * kernel is क्रम now unable to करो, and gating the घड़ी would
	 * make us loose this precious configuration.
	 */
	अगर (!of_device_is_available(child) || !IS_ENABLED(CONFIG_PCI_MVEBU)) अणु
		clk_disable_unprepare(clk);
		clk_put(clk);
	पूर्ण

clk_err:
	of_node_put(child);
	of_node_put(np);

	वापस ret;
पूर्ण

अटल पूर्णांक __init mvebu_soc_id_init(व्योम)
अणु

	/*
	 * First try to get the ID and the revision by the प्रणाली
	 * रेजिस्टर and use PCI रेजिस्टरs only अगर it is not possible
	 */
	अगर (!mvebu_प्रणाली_controller_get_soc_id(&soc_dev_id, &soc_rev)) अणु
		is_id_valid = true;
		pr_info("MVEBU SoC ID=0x%X, Rev=0x%X\n", soc_dev_id, soc_rev);
		वापस 0;
	पूर्ण

	वापस get_soc_id_by_pci();
पूर्ण
early_initcall(mvebu_soc_id_init);

अटल पूर्णांक __init mvebu_soc_device(व्योम)
अणु
	काष्ठा soc_device_attribute *soc_dev_attr;
	काष्ठा soc_device *soc_dev;

	/* Also protects against running on non-mvebu प्रणालीs */
	अगर (!is_id_valid)
		वापस 0;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस -ENOMEM;

	soc_dev_attr->family = kaप्र_लिखो(GFP_KERNEL, "Marvell");
	soc_dev_attr->revision = kaप्र_लिखो(GFP_KERNEL, "%X", soc_rev);
	soc_dev_attr->soc_id = kaप्र_लिखो(GFP_KERNEL, "%X", soc_dev_id);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->family);
		kमुक्त(soc_dev_attr->revision);
		kमुक्त(soc_dev_attr->soc_id);
		kमुक्त(soc_dev_attr);
	पूर्ण

	वापस 0;
पूर्ण
postcore_initcall(mvebu_soc_device);
