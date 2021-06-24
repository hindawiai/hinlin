<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Cadence
// Cadence PCIe controller driver.
// Author: Cyrille Pitchen <cyrille.pitchen@मुक्त-electrons.com>

#समावेश <linux/kernel.h>

#समावेश "pcie-cadence.h"

व्योम cdns_pcie_set_outbound_region(काष्ठा cdns_pcie *pcie, u8 busnr, u8 fn,
				   u32 r, bool is_io,
				   u64 cpu_addr, u64 pci_addr, माप_प्रकार size)
अणु
	/*
	 * roundup_घात_of_two() वापसs an अचिन्हित दीर्घ, which is not suited
	 * क्रम 64bit values.
	 */
	u64 sz = 1ULL << fls64(size - 1);
	पूर्णांक nbits = ilog2(sz);
	u32 addr0, addr1, desc0, desc1;

	अगर (nbits < 8)
		nbits = 8;

	/* Set the PCI address */
	addr0 = CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(nbits) |
		(lower_32_bits(pci_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(pci_addr);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r), addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r), addr1);

	/* Set the PCIe header descriptor */
	अगर (is_io)
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO;
	अन्यथा
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM;
	desc1 = 0;

	/*
	 * Whatever Bit [23] is set or not inside DESC0 रेजिस्टर of the outbound
	 * PCIe descriptor, the PCI function number must be set पूर्णांकo
	 * Bits [26:24] of DESC0 anyway.
	 *
	 * In Root Complex mode, the function number is always 0 but in Endpoपूर्णांक
	 * mode, the PCIe controller may support more than one function. This
	 * function number needs to be set properly पूर्णांकo the outbound PCIe
	 * descriptor.
	 *
	 * Besides, setting Bit [23] is mandatory when in Root Complex mode:
	 * then the driver must provide the bus, resp. device, number in
	 * Bits [7:0] of DESC1, resp. Bits[31:27] of DESC0. Like the function
	 * number, the device number is always 0 in Root Complex mode.
	 *
	 * However when in Endpoपूर्णांक mode, we can clear Bit [23] of DESC0, hence
	 * the PCIe controller will use the captured values क्रम the bus and
	 * device numbers.
	 */
	अगर (pcie->is_rc) अणु
		/* The device and function numbers are always 0. */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID |
			 CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_REGION_DESC1_BUS(busnr);
	पूर्ण अन्यथा अणु
		/*
		 * Use captured values क्रम bus and device numbers but still
		 * need to set the function number.
		 */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(fn);
	पूर्ण

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(r), desc0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(r), desc1);

	/* Set the CPU address */
	अगर (pcie->ops->cpu_addr_fixup)
		cpu_addr = pcie->ops->cpu_addr_fixup(pcie, cpu_addr);

	addr0 = CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(nbits) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r), addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r), addr1);
पूर्ण

व्योम cdns_pcie_set_outbound_region_क्रम_normal_msg(काष्ठा cdns_pcie *pcie,
						  u8 busnr, u8 fn,
						  u32 r, u64 cpu_addr)
अणु
	u32 addr0, addr1, desc0, desc1;

	desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_NORMAL_MSG;
	desc1 = 0;

	/* See cdns_pcie_set_outbound_region() comments above. */
	अगर (pcie->is_rc) अणु
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID |
			 CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_REGION_DESC1_BUS(busnr);
	पूर्ण अन्यथा अणु
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(fn);
	पूर्ण

	/* Set the CPU address */
	अगर (pcie->ops->cpu_addr_fixup)
		cpu_addr = pcie->ops->cpu_addr_fixup(pcie, cpu_addr);

	addr0 = CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(17) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(r), desc0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(r), desc1);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r), addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r), addr1);
पूर्ण

व्योम cdns_pcie_reset_outbound_region(काष्ठा cdns_pcie *pcie, u32 r)
अणु
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(r), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(r), 0);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(r), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(r), 0);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(r), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(r), 0);
पूर्ण

व्योम cdns_pcie_disable_phy(काष्ठा cdns_pcie *pcie)
अणु
	पूर्णांक i = pcie->phy_count;

	जबतक (i--) अणु
		phy_घातer_off(pcie->phy[i]);
		phy_निकास(pcie->phy[i]);
	पूर्ण
पूर्ण

पूर्णांक cdns_pcie_enable_phy(काष्ठा cdns_pcie *pcie)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < pcie->phy_count; i++) अणु
		ret = phy_init(pcie->phy[i]);
		अगर (ret < 0)
			जाओ err_phy;

		ret = phy_घातer_on(pcie->phy[i]);
		अगर (ret < 0) अणु
			phy_निकास(pcie->phy[i]);
			जाओ err_phy;
		पूर्ण
	पूर्ण

	वापस 0;

err_phy:
	जबतक (--i >= 0) अणु
		phy_घातer_off(pcie->phy[i]);
		phy_निकास(pcie->phy[i]);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक cdns_pcie_init_phy(काष्ठा device *dev, काष्ठा cdns_pcie *pcie)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक phy_count;
	काष्ठा phy **phy;
	काष्ठा device_link **link;
	पूर्णांक i;
	पूर्णांक ret;
	स्थिर अक्षर *name;

	phy_count = of_property_count_strings(np, "phy-names");
	अगर (phy_count < 1) अणु
		dev_err(dev, "no phy-names.  PHY will not be initialized\n");
		pcie->phy_count = 0;
		वापस 0;
	पूर्ण

	phy = devm_kसुस्मृति(dev, phy_count, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	link = devm_kसुस्मृति(dev, phy_count, माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	क्रम (i = 0; i < phy_count; i++) अणु
		of_property_पढ़ो_string_index(np, "phy-names", i, &name);
		phy[i] = devm_phy_get(dev, name);
		अगर (IS_ERR(phy[i])) अणु
			ret = PTR_ERR(phy[i]);
			जाओ err_phy;
		पूर्ण
		link[i] = device_link_add(dev, &phy[i]->dev, DL_FLAG_STATELESS);
		अगर (!link[i]) अणु
			devm_phy_put(dev, phy[i]);
			ret = -EINVAL;
			जाओ err_phy;
		पूर्ण
	पूर्ण

	pcie->phy_count = phy_count;
	pcie->phy = phy;
	pcie->link = link;

	ret =  cdns_pcie_enable_phy(pcie);
	अगर (ret)
		जाओ err_phy;

	वापस 0;

err_phy:
	जबतक (--i >= 0) अणु
		device_link_del(link[i]);
		devm_phy_put(dev, phy[i]);
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cdns_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा cdns_pcie *pcie = dev_get_drvdata(dev);

	cdns_pcie_disable_phy(pcie);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा cdns_pcie *pcie = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = cdns_pcie_enable_phy(pcie);
	अगर (ret) अणु
		dev_err(dev, "failed to enable phy\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops cdns_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(cdns_pcie_suspend_noirq,
				      cdns_pcie_resume_noirq)
पूर्ण;
