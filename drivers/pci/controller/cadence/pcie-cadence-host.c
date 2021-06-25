<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Cadence
// Cadence PCIe host controller driver.
// Author: Cyrille Pitchen <cyrille.pitchen@मुक्त-electrons.com>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pcie-cadence.h"

अटल u64 bar_max_size[] = अणु
	[RP_BAR0] = _ULL(128 * SZ_2G),
	[RP_BAR1] = SZ_2G,
	[RP_NO_BAR] = _BITULL(63),
पूर्ण;

अटल u8 bar_aperture_mask[] = अणु
	[RP_BAR0] = 0x1F,
	[RP_BAR1] = 0xF,
पूर्ण;

व्योम __iomem *cdns_pci_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where)
अणु
	काष्ठा pci_host_bridge *bridge = pci_find_host_bridge(bus);
	काष्ठा cdns_pcie_rc *rc = pci_host_bridge_priv(bridge);
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	अचिन्हित पूर्णांक busn = bus->number;
	u32 addr0, desc0;

	अगर (pci_is_root_bus(bus)) अणु
		/*
		 * Only the root port (devfn == 0) is connected to this bus.
		 * All other PCI devices are behind some bridge hence on another
		 * bus.
		 */
		अगर (devfn)
			वापस शून्य;

		वापस pcie->reg_base + (where & 0xfff);
	पूर्ण
	/* Check that the link is up */
	अगर (!(cdns_pcie_पढ़ोl(pcie, CDNS_PCIE_LM_BASE) & 0x1))
		वापस शून्य;
	/* Clear AXI link-करोwn status */
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_LINKDOWN, 0x0);

	/* Update Output रेजिस्टरs क्रम AXI region 0. */
	addr0 = CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(12) |
		CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN(devfn) |
		CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS(busn);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(0), addr0);

	/* Configuration Type 0 or Type 1 access. */
	desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID |
		CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
	/*
	 * The bus number was alपढ़ोy set once क्रम all in desc1 by
	 * cdns_pcie_host_init_address_translation().
	 */
	अगर (busn == bridge->busnr + 1)
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE0;
	अन्यथा
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE1;
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(0), desc0);

	वापस rc->cfg_base + (where & 0xfff);
पूर्ण

अटल काष्ठा pci_ops cdns_pcie_host_ops = अणु
	.map_bus	= cdns_pci_map_bus,
	.पढ़ो		= pci_generic_config_पढ़ो,
	.ग_लिखो		= pci_generic_config_ग_लिखो,
पूर्ण;

अटल पूर्णांक cdns_pcie_host_रुको_क्रम_link(काष्ठा cdns_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	पूर्णांक retries;

	/* Check अगर the link is up or not */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) अणु
		अगर (cdns_pcie_link_up(pcie)) अणु
			dev_info(dev, "Link up\n");
			वापस 0;
		पूर्ण
		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक cdns_pcie_retrain(काष्ठा cdns_pcie *pcie)
अणु
	u32 lnk_cap_sls, pcie_cap_off = CDNS_PCIE_RP_CAP_OFFSET;
	u16 lnk_stat, lnk_ctl;
	पूर्णांक ret = 0;

	/*
	 * Set retrain bit अगर current speed is 2.5 GB/s,
	 * but the PCIe root port support is > 2.5 GB/s.
	 */

	lnk_cap_sls = cdns_pcie_पढ़ोl(pcie, (CDNS_PCIE_RP_BASE + pcie_cap_off +
					     PCI_EXP_LNKCAP));
	अगर ((lnk_cap_sls & PCI_EXP_LNKCAP_SLS) <= PCI_EXP_LNKCAP_SLS_2_5GB)
		वापस ret;

	lnk_stat = cdns_pcie_rp_पढ़ोw(pcie, pcie_cap_off + PCI_EXP_LNKSTA);
	अगर ((lnk_stat & PCI_EXP_LNKSTA_CLS) == PCI_EXP_LNKSTA_CLS_2_5GB) अणु
		lnk_ctl = cdns_pcie_rp_पढ़ोw(pcie,
					     pcie_cap_off + PCI_EXP_LNKCTL);
		lnk_ctl |= PCI_EXP_LNKCTL_RL;
		cdns_pcie_rp_ग_लिखोw(pcie, pcie_cap_off + PCI_EXP_LNKCTL,
				    lnk_ctl);

		ret = cdns_pcie_host_रुको_क्रम_link(pcie);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cdns_pcie_host_start_link(काष्ठा cdns_pcie_rc *rc)
अणु
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	पूर्णांक ret;

	ret = cdns_pcie_host_रुको_क्रम_link(pcie);

	/*
	 * Retrain link क्रम Gen2 training defect
	 * अगर quirk flag is set.
	 */
	अगर (!ret && rc->quirk_retrain_flag)
		ret = cdns_pcie_retrain(pcie);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns_pcie_host_init_root_port(काष्ठा cdns_pcie_rc *rc)
अणु
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	u32 value, ctrl;
	u32 id;

	/*
	 * Set the root complex BAR configuration रेजिस्टर:
	 * - disable both BAR0 and BAR1.
	 * - enable Prefetchable Memory Base and Limit रेजिस्टरs in type 1
	 *   config space (64 bits).
	 * - enable IO Base and Limit रेजिस्टरs in type 1 config
	 *   space (32 bits).
	 */
	ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED;
	value = CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS;
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_RC_BAR_CFG, value);

	/* Set root port configuration space */
	अगर (rc->venकरोr_id != 0xffff) अणु
		id = CDNS_PCIE_LM_ID_VENDOR(rc->venकरोr_id) |
			CDNS_PCIE_LM_ID_SUBSYS(rc->venकरोr_id);
		cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_ID, id);
	पूर्ण

	अगर (rc->device_id != 0xffff)
		cdns_pcie_rp_ग_लिखोw(pcie, PCI_DEVICE_ID, rc->device_id);

	cdns_pcie_rp_ग_लिखोb(pcie, PCI_CLASS_REVISION, 0);
	cdns_pcie_rp_ग_लिखोb(pcie, PCI_CLASS_PROG, 0);
	cdns_pcie_rp_ग_लिखोw(pcie, PCI_CLASS_DEVICE, PCI_CLASS_BRIDGE_PCI);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_host_bar_ib_config(काष्ठा cdns_pcie_rc *rc,
					क्रमागत cdns_pcie_rp_bar bar,
					u64 cpu_addr, u64 size,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	u32 addr0, addr1, aperture, value;

	अगर (!rc->avail_ib_bar[bar])
		वापस -EBUSY;

	rc->avail_ib_bar[bar] = false;

	aperture = ilog2(size);
	addr0 = CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS(aperture) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_RP_BAR_ADDR0(bar), addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_RP_BAR_ADDR1(bar), addr1);

	अगर (bar == RP_NO_BAR)
		वापस 0;

	value = cdns_pcie_पढ़ोl(pcie, CDNS_PCIE_LM_RC_BAR_CFG);
	value &= ~(LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar) |
		   LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar) |
		   LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar) |
		   LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar) |
		   LM_RC_BAR_CFG_APERTURE(bar, bar_aperture_mask[bar] + 2));
	अगर (size + cpu_addr >= SZ_4G) अणु
		अगर (!(flags & IORESOURCE_PREFETCH))
			value |= LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar);
		value |= LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar);
	पूर्ण अन्यथा अणु
		अगर (!(flags & IORESOURCE_PREFETCH))
			value |= LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar);
		value |= LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar);
	पूर्ण

	value |= LM_RC_BAR_CFG_APERTURE(bar, aperture);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_RC_BAR_CFG, value);

	वापस 0;
पूर्ण

अटल क्रमागत cdns_pcie_rp_bar
cdns_pcie_host_find_min_bar(काष्ठा cdns_pcie_rc *rc, u64 size)
अणु
	क्रमागत cdns_pcie_rp_bar bar, sel_bar;

	sel_bar = RP_BAR_UNDEFINED;
	क्रम (bar = RP_BAR0; bar <= RP_NO_BAR; bar++) अणु
		अगर (!rc->avail_ib_bar[bar])
			जारी;

		अगर (size <= bar_max_size[bar]) अणु
			अगर (sel_bar == RP_BAR_UNDEFINED) अणु
				sel_bar = bar;
				जारी;
			पूर्ण

			अगर (bar_max_size[bar] < bar_max_size[sel_bar])
				sel_bar = bar;
		पूर्ण
	पूर्ण

	वापस sel_bar;
पूर्ण

अटल क्रमागत cdns_pcie_rp_bar
cdns_pcie_host_find_max_bar(काष्ठा cdns_pcie_rc *rc, u64 size)
अणु
	क्रमागत cdns_pcie_rp_bar bar, sel_bar;

	sel_bar = RP_BAR_UNDEFINED;
	क्रम (bar = RP_BAR0; bar <= RP_NO_BAR; bar++) अणु
		अगर (!rc->avail_ib_bar[bar])
			जारी;

		अगर (size >= bar_max_size[bar]) अणु
			अगर (sel_bar == RP_BAR_UNDEFINED) अणु
				sel_bar = bar;
				जारी;
			पूर्ण

			अगर (bar_max_size[bar] > bar_max_size[sel_bar])
				sel_bar = bar;
		पूर्ण
	पूर्ण

	वापस sel_bar;
पूर्ण

अटल पूर्णांक cdns_pcie_host_bar_config(काष्ठा cdns_pcie_rc *rc,
				     काष्ठा resource_entry *entry)
अणु
	u64 cpu_addr, pci_addr, size, winsize;
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	काष्ठा device *dev = pcie->dev;
	क्रमागत cdns_pcie_rp_bar bar;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	cpu_addr = entry->res->start;
	pci_addr = entry->res->start - entry->offset;
	flags = entry->res->flags;
	size = resource_size(entry->res);

	अगर (entry->offset) अणु
		dev_err(dev, "PCI addr: %llx must be equal to CPU addr: %llx\n",
			pci_addr, cpu_addr);
		वापस -EINVAL;
	पूर्ण

	जबतक (size > 0) अणु
		/*
		 * Try to find a minimum BAR whose size is greater than
		 * or equal to the reमुख्यing resource_entry size. This will
		 * fail अगर the size of each of the available BARs is less than
		 * the reमुख्यing resource_entry size.
		 * If a minimum BAR is found, IB ATU will be configured and
		 * निकासed.
		 */
		bar = cdns_pcie_host_find_min_bar(rc, size);
		अगर (bar != RP_BAR_UNDEFINED) अणु
			ret = cdns_pcie_host_bar_ib_config(rc, bar, cpu_addr,
							   size, flags);
			अगर (ret)
				dev_err(dev, "IB BAR: %d config failed\n", bar);
			वापस ret;
		पूर्ण

		/*
		 * If the control reaches here, it would mean the reमुख्यing
		 * resource_entry size cannot be fitted in a single BAR. So we
		 * find a maximum BAR whose size is less than or equal to the
		 * reमुख्यing resource_entry size and split the resource entry
		 * so that part of resource entry is fitted inside the maximum
		 * BAR. The reमुख्यing size would be fitted during the next
		 * iteration of the loop.
		 * If a maximum BAR is not found, there is no way we can fit
		 * this resource_entry, so we error out.
		 */
		bar = cdns_pcie_host_find_max_bar(rc, size);
		अगर (bar == RP_BAR_UNDEFINED) अणु
			dev_err(dev, "No free BAR to map cpu_addr %llx\n",
				cpu_addr);
			वापस -EINVAL;
		पूर्ण

		winsize = bar_max_size[bar];
		ret = cdns_pcie_host_bar_ib_config(rc, bar, cpu_addr, winsize,
						   flags);
		अगर (ret) अणु
			dev_err(dev, "IB BAR: %d config failed\n", bar);
			वापस ret;
		पूर्ण

		size -= winsize;
		cpu_addr += winsize;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_host_dma_ranges_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
					 स्थिर काष्ठा list_head *b)
अणु
	काष्ठा resource_entry *entry1, *entry2;

        entry1 = container_of(a, काष्ठा resource_entry, node);
        entry2 = container_of(b, काष्ठा resource_entry, node);

        वापस resource_size(entry2->res) - resource_size(entry1->res);
पूर्ण

अटल पूर्णांक cdns_pcie_host_map_dma_ranges(काष्ठा cdns_pcie_rc *rc)
अणु
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	काष्ठा device *dev = pcie->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा resource_entry *entry;
	u32 no_bar_nbits = 32;
	पूर्णांक err;

	bridge = pci_host_bridge_from_priv(rc);
	अगर (!bridge)
		वापस -ENOMEM;

	अगर (list_empty(&bridge->dma_ranges)) अणु
		of_property_पढ़ो_u32(np, "cdns,no-bar-match-nbits",
				     &no_bar_nbits);
		err = cdns_pcie_host_bar_ib_config(rc, RP_NO_BAR, 0x0,
						   (u64)1 << no_bar_nbits, 0);
		अगर (err)
			dev_err(dev, "IB BAR: %d config failed\n", RP_NO_BAR);
		वापस err;
	पूर्ण

	list_sort(शून्य, &bridge->dma_ranges, cdns_pcie_host_dma_ranges_cmp);

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges) अणु
		err = cdns_pcie_host_bar_config(rc, entry);
		अगर (err) अणु
			dev_err(dev, "Fail to configure IB using dma-ranges\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_host_init_address_translation(काष्ठा cdns_pcie_rc *rc)
अणु
	काष्ठा cdns_pcie *pcie = &rc->pcie;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(rc);
	काष्ठा resource *cfg_res = rc->cfg_res;
	काष्ठा resource_entry *entry;
	u64 cpu_addr = cfg_res->start;
	u32 addr0, addr1, desc1;
	पूर्णांक r, busnr = 0;

	entry = resource_list_first_type(&bridge->winकरोws, IORESOURCE_BUS);
	अगर (entry)
		busnr = entry->res->start;

	/*
	 * Reserve region 0 क्रम PCI configure space accesses:
	 * OB_REGION_PCI_ADDR0 and OB_REGION_DESC0 are updated dynamically by
	 * cdns_pci_map_bus(), other region रेजिस्टरs are set here once क्रम all.
	 */
	addr1 = 0; /* Should be programmed to zero. */
	desc1 = CDNS_PCIE_AT_OB_REGION_DESC1_BUS(busnr);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(0), addr1);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(0), desc1);

	अगर (pcie->ops->cpu_addr_fixup)
		cpu_addr = pcie->ops->cpu_addr_fixup(pcie, cpu_addr);

	addr0 = CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(12) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(0), addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(0), addr1);

	r = 1;
	resource_list_क्रम_each_entry(entry, &bridge->winकरोws) अणु
		काष्ठा resource *res = entry->res;
		u64 pci_addr = res->start - entry->offset;

		अगर (resource_type(res) == IORESOURCE_IO)
			cdns_pcie_set_outbound_region(pcie, busnr, 0, r,
						      true,
						      pci_pio_to_address(res->start),
						      pci_addr,
						      resource_size(res));
		अन्यथा
			cdns_pcie_set_outbound_region(pcie, busnr, 0, r,
						      false,
						      res->start,
						      pci_addr,
						      resource_size(res));

		r++;
	पूर्ण

	वापस cdns_pcie_host_map_dma_ranges(rc);
पूर्ण

अटल पूर्णांक cdns_pcie_host_init(काष्ठा device *dev,
			       काष्ठा cdns_pcie_rc *rc)
अणु
	पूर्णांक err;

	err = cdns_pcie_host_init_root_port(rc);
	अगर (err)
		वापस err;

	वापस cdns_pcie_host_init_address_translation(rc);
पूर्ण

पूर्णांक cdns_pcie_host_setup(काष्ठा cdns_pcie_rc *rc)
अणु
	काष्ठा device *dev = rc->pcie.dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा pci_host_bridge *bridge;
	क्रमागत cdns_pcie_rp_bar bar;
	काष्ठा cdns_pcie *pcie;
	काष्ठा resource *res;
	पूर्णांक ret;

	bridge = pci_host_bridge_from_priv(rc);
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = &rc->pcie;
	pcie->is_rc = true;

	rc->venकरोr_id = 0xffff;
	of_property_पढ़ो_u32(np, "vendor-id", &rc->venकरोr_id);

	rc->device_id = 0xffff;
	of_property_पढ़ो_u32(np, "device-id", &rc->device_id);

	pcie->reg_base = devm_platक्रमm_ioremap_resource_byname(pdev, "reg");
	अगर (IS_ERR(pcie->reg_base)) अणु
		dev_err(dev, "missing \"reg\"\n");
		वापस PTR_ERR(pcie->reg_base);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "cfg");
	rc->cfg_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(rc->cfg_base))
		वापस PTR_ERR(rc->cfg_base);
	rc->cfg_res = res;

	ret = cdns_pcie_start_link(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to start link\n");
		वापस ret;
	पूर्ण

	ret = cdns_pcie_host_start_link(rc);
	अगर (ret)
		dev_dbg(dev, "PCIe link never came up\n");

	क्रम (bar = RP_BAR0; bar <= RP_NO_BAR; bar++)
		rc->avail_ib_bar[bar] = true;

	ret = cdns_pcie_host_init(dev, rc);
	अगर (ret)
		वापस ret;

	अगर (!bridge->ops)
		bridge->ops = &cdns_pcie_host_ops;

	ret = pci_host_probe(bridge);
	अगर (ret < 0)
		जाओ err_init;

	वापस 0;

 err_init:
	pm_runसमय_put_sync(dev);

	वापस ret;
पूर्ण
