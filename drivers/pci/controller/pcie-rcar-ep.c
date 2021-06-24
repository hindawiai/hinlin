<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe endpoपूर्णांक driver क्रम Renesas R-Car SoCs
 *  Copyright (c) 2020 Renesas Electronics Europe GmbH
 *
 * Author: Lad Prabhakar <prabhakar.mahadev-lad.rj@bp.renesas.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-epc.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pcie-rcar.h"

#घोषणा RCAR_EPC_MAX_FUNCTIONS		1

/* Structure representing the PCIe पूर्णांकerface */
काष्ठा rcar_pcie_endpoपूर्णांक अणु
	काष्ठा rcar_pcie	pcie;
	phys_addr_t		*ob_mapped_addr;
	काष्ठा pci_epc_mem_winकरोw *ob_winकरोw;
	u8			max_functions;
	अचिन्हित पूर्णांक		bar_to_atu[MAX_NR_INBOUND_MAPS];
	अचिन्हित दीर्घ		*ib_winकरोw_map;
	u32			num_ib_winकरोws;
	u32			num_ob_winकरोws;
पूर्ण;

अटल व्योम rcar_pcie_ep_hw_init(काष्ठा rcar_pcie *pcie)
अणु
	u32 val;

	rcar_pci_ग_लिखो_reg(pcie, 0, PCIETCTLR);

	/* Set endpoपूर्णांक mode */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIEMSR);

	/* Initialize शेष capabilities. */
	rcar_rmw32(pcie, REXPCAP(0), 0xff, PCI_CAP_ID_EXP);
	rcar_rmw32(pcie, REXPCAP(PCI_EXP_FLAGS),
		   PCI_EXP_FLAGS_TYPE, PCI_EXP_TYPE_ENDPOINT << 4);
	rcar_rmw32(pcie, RCONF(PCI_HEADER_TYPE), 0x7f,
		   PCI_HEADER_TYPE_NORMAL);

	/* Write out the physical slot number = 0 */
	rcar_rmw32(pcie, REXPCAP(PCI_EXP_SLTCAP), PCI_EXP_SLTCAP_PSN, 0);

	val = rcar_pci_पढ़ो_reg(pcie, EXPCAP(1));
	/* device supports fixed 128 bytes MPSS */
	val &= ~GENMASK(2, 0);
	rcar_pci_ग_लिखो_reg(pcie, val, EXPCAP(1));

	val = rcar_pci_पढ़ो_reg(pcie, EXPCAP(2));
	/* पढ़ो requests size 128 bytes */
	val &= ~GENMASK(14, 12);
	/* payload size 128 bytes */
	val &= ~GENMASK(7, 5);
	rcar_pci_ग_लिखो_reg(pcie, val, EXPCAP(2));

	/* Set target link speed to 5.0 GT/s */
	rcar_rmw32(pcie, EXPCAP(12), PCI_EXP_LNKSTA_CLS,
		   PCI_EXP_LNKSTA_CLS_5_0GB);

	/* Set the completion समयr समयout to the maximum 50ms. */
	rcar_rmw32(pcie, TLCTLR + 1, 0x3f, 50);

	/* Terminate list of capabilities (Next Capability Offset=0) */
	rcar_rmw32(pcie, RVCCAP(0), 0xfff00000, 0);

	/* flush modअगरications */
	wmb();
पूर्ण

अटल पूर्णांक rcar_pcie_ep_get_winकरोw(काष्ठा rcar_pcie_endpoपूर्णांक *ep,
				   phys_addr_t addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ep->num_ob_winकरोws; i++)
		अगर (ep->ob_winकरोw[i].phys_base == addr)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rcar_pcie_parse_outbound_ranges(काष्ठा rcar_pcie_endpoपूर्णांक *ep,
					   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	अक्षर outbound_name[10];
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i = 0;

	ep->num_ob_winकरोws = 0;
	क्रम (i = 0; i < RCAR_PCI_MAX_RESOURCES; i++) अणु
		प्र_लिखो(outbound_name, "memory%u", i);
		res = platक्रमm_get_resource_byname(pdev,
						   IORESOURCE_MEM,
						   outbound_name);
		अगर (!res) अणु
			dev_err(pcie->dev, "missing outbound window %u\n", i);
			वापस -EINVAL;
		पूर्ण
		अगर (!devm_request_mem_region(&pdev->dev, res->start,
					     resource_size(res),
					     outbound_name)) अणु
			dev_err(pcie->dev, "Cannot request memory region %s.\n",
				outbound_name);
			वापस -EIO;
		पूर्ण

		ep->ob_winकरोw[i].phys_base = res->start;
		ep->ob_winकरोw[i].size = resource_size(res);
		/* controller करोesn't support multiple allocation
		 * from same winकरोw, so set page_size to winकरोw size
		 */
		ep->ob_winकरोw[i].page_size = resource_size(res);
	पूर्ण
	ep->num_ob_winकरोws = i;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_get_pdata(काष्ठा rcar_pcie_endpoपूर्णांक *ep,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	काष्ठा pci_epc_mem_winकरोw *winकरोw;
	काष्ठा device *dev = pcie->dev;
	काष्ठा resource res;
	पूर्णांक err;

	err = of_address_to_resource(dev->of_node, 0, &res);
	अगर (err)
		वापस err;
	pcie->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(pcie->base))
		वापस PTR_ERR(pcie->base);

	ep->ob_winकरोw = devm_kसुस्मृति(dev, RCAR_PCI_MAX_RESOURCES,
				     माप(*winकरोw), GFP_KERNEL);
	अगर (!ep->ob_winकरोw)
		वापस -ENOMEM;

	rcar_pcie_parse_outbound_ranges(ep, pdev);

	err = of_property_पढ़ो_u8(dev->of_node, "max-functions",
				  &ep->max_functions);
	अगर (err < 0 || ep->max_functions > RCAR_EPC_MAX_FUNCTIONS)
		ep->max_functions = RCAR_EPC_MAX_FUNCTIONS;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_ग_लिखो_header(काष्ठा pci_epc *epc, u8 fn,
				     काष्ठा pci_epf_header *hdr)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	u32 val;

	अगर (!fn)
		val = hdr->venकरोrid;
	अन्यथा
		val = rcar_pci_पढ़ो_reg(pcie, IDSETR0);
	val |= hdr->deviceid << 16;
	rcar_pci_ग_लिखो_reg(pcie, val, IDSETR0);

	val = hdr->revid;
	val |= hdr->progअगर_code << 8;
	val |= hdr->subclass_code << 16;
	val |= hdr->baseclass_code << 24;
	rcar_pci_ग_लिखो_reg(pcie, val, IDSETR1);

	अगर (!fn)
		val = hdr->subsys_venकरोr_id;
	अन्यथा
		val = rcar_pci_पढ़ो_reg(pcie, SUBIDSETR);
	val |= hdr->subsys_id << 16;
	rcar_pci_ग_लिखो_reg(pcie, val, SUBIDSETR);

	अगर (hdr->पूर्णांकerrupt_pin > PCI_INTERRUPT_INTA)
		वापस -EINVAL;
	val = rcar_pci_पढ़ो_reg(pcie, PCICONF(15));
	val |= (hdr->पूर्णांकerrupt_pin << 8);
	rcar_pci_ग_लिखो_reg(pcie, val, PCICONF(15));

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_set_bar(काष्ठा pci_epc *epc, u8 func_no,
				काष्ठा pci_epf_bar *epf_bar)
अणु
	पूर्णांक flags = epf_bar->flags | LAR_ENABLE | LAM_64BIT;
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	u64 size = 1ULL << fls64(epf_bar->size - 1);
	dma_addr_t cpu_addr = epf_bar->phys_addr;
	क्रमागत pci_barno bar = epf_bar->barno;
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	u32 mask;
	पूर्णांक idx;
	पूर्णांक err;

	idx = find_first_zero_bit(ep->ib_winकरोw_map, ep->num_ib_winकरोws);
	अगर (idx >= ep->num_ib_winकरोws) अणु
		dev_err(pcie->dev, "no free inbound window\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((flags & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO)
		flags |= IO_SPACE;

	ep->bar_to_atu[bar] = idx;
	/* use 64-bit BARs */
	set_bit(idx, ep->ib_winकरोw_map);
	set_bit(idx + 1, ep->ib_winकरोw_map);

	अगर (cpu_addr > 0) अणु
		अचिन्हित दीर्घ nr_zeros = __ffs64(cpu_addr);
		u64 alignment = 1ULL << nr_zeros;

		size = min(size, alignment);
	पूर्ण

	size = min(size, 1ULL << 32);

	mask = roundup_घात_of_two(size) - 1;
	mask &= ~0xf;

	rcar_pcie_set_inbound(pcie, cpu_addr,
			      0x0, mask | flags, idx, false);

	err = rcar_pcie_रुको_क्रम_phyrdy(pcie);
	अगर (err) अणु
		dev_err(pcie->dev, "phy not ready\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcar_pcie_ep_clear_bar(काष्ठा pci_epc *epc, u8 fn,
				   काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	क्रमागत pci_barno bar = epf_bar->barno;
	u32 atu_index = ep->bar_to_atu[bar];

	rcar_pcie_set_inbound(&ep->pcie, 0x0, 0x0, 0x0, bar, false);

	clear_bit(atu_index, ep->ib_winकरोw_map);
	clear_bit(atu_index + 1, ep->ib_winकरोw_map);
पूर्ण

अटल पूर्णांक rcar_pcie_ep_set_msi(काष्ठा pci_epc *epc, u8 fn, u8 पूर्णांकerrupts)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	u32 flags;

	flags = rcar_pci_पढ़ो_reg(pcie, MSICAP(fn));
	flags |= पूर्णांकerrupts << MSICAP0_MMESCAP_OFFSET;
	rcar_pci_ग_लिखो_reg(pcie, flags, MSICAP(fn));

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_get_msi(काष्ठा pci_epc *epc, u8 fn)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	u32 flags;

	flags = rcar_pci_पढ़ो_reg(pcie, MSICAP(fn));
	अगर (!(flags & MSICAP0_MSIE))
		वापस -EINVAL;

	वापस ((flags & MSICAP0_MMESE_MASK) >> MSICAP0_MMESE_OFFSET);
पूर्ण

अटल पूर्णांक rcar_pcie_ep_map_addr(काष्ठा pci_epc *epc, u8 fn,
				 phys_addr_t addr, u64 pci_addr, माप_प्रकार size)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	काष्ठा resource_entry win;
	काष्ठा resource res;
	पूर्णांक winकरोw;
	पूर्णांक err;

	/* check अगर we have a link. */
	err = rcar_pcie_रुको_क्रम_dl(pcie);
	अगर (err) अणु
		dev_err(pcie->dev, "link not up\n");
		वापस err;
	पूर्ण

	winकरोw = rcar_pcie_ep_get_winकरोw(ep, addr);
	अगर (winकरोw < 0) अणु
		dev_err(pcie->dev, "failed to get corresponding window\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&win, 0x0, माप(win));
	स_रखो(&res, 0x0, माप(res));
	res.start = pci_addr;
	res.end = pci_addr + size - 1;
	res.flags = IORESOURCE_MEM;
	win.res = &res;

	rcar_pcie_set_outbound(pcie, winकरोw, &win);

	ep->ob_mapped_addr[winकरोw] = addr;

	वापस 0;
पूर्ण

अटल व्योम rcar_pcie_ep_unmap_addr(काष्ठा pci_epc *epc, u8 fn,
				    phys_addr_t addr)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);
	काष्ठा resource_entry win;
	काष्ठा resource res;
	पूर्णांक idx;

	क्रम (idx = 0; idx < ep->num_ob_winकरोws; idx++)
		अगर (ep->ob_mapped_addr[idx] == addr)
			अवरोध;

	अगर (idx >= ep->num_ob_winकरोws)
		वापस;

	स_रखो(&win, 0x0, माप(win));
	स_रखो(&res, 0x0, माप(res));
	win.res = &res;
	rcar_pcie_set_outbound(&ep->pcie, idx, &win);

	ep->ob_mapped_addr[idx] = 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_निश्चित_पूर्णांकx(काष्ठा rcar_pcie_endpoपूर्णांक *ep,
				    u8 fn, u8 पूर्णांकx)
अणु
	काष्ठा rcar_pcie *pcie = &ep->pcie;
	u32 val;

	val = rcar_pci_पढ़ो_reg(pcie, PCIEMSITXR);
	अगर ((val & PCI_MSI_FLAGS_ENABLE)) अणु
		dev_err(pcie->dev, "MSI is enabled, cannot assert INTx\n");
		वापस -EINVAL;
	पूर्ण

	val = rcar_pci_पढ़ो_reg(pcie, PCICONF(1));
	अगर ((val & INTDIS)) अणु
		dev_err(pcie->dev, "INTx message transmission is disabled\n");
		वापस -EINVAL;
	पूर्ण

	val = rcar_pci_पढ़ो_reg(pcie, PCIEINTXR);
	अगर ((val & ASTINTX)) अणु
		dev_err(pcie->dev, "INTx is already asserted\n");
		वापस -EINVAL;
	पूर्ण

	val |= ASTINTX;
	rcar_pci_ग_लिखो_reg(pcie, val, PCIEINTXR);
	usleep_range(1000, 1001);
	val = rcar_pci_पढ़ो_reg(pcie, PCIEINTXR);
	val &= ~ASTINTX;
	rcar_pci_ग_लिखो_reg(pcie, val, PCIEINTXR);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_निश्चित_msi(काष्ठा rcar_pcie *pcie,
				   u8 fn, u8 पूर्णांकerrupt_num)
अणु
	u16 msi_count;
	u32 val;

	/* Check MSI enable bit */
	val = rcar_pci_पढ़ो_reg(pcie, MSICAP(fn));
	अगर (!(val & MSICAP0_MSIE))
		वापस -EINVAL;

	/* Get MSI numbers from MME */
	msi_count = ((val & MSICAP0_MMESE_MASK) >> MSICAP0_MMESE_OFFSET);
	msi_count = 1 << msi_count;

	अगर (!पूर्णांकerrupt_num || पूर्णांकerrupt_num > msi_count)
		वापस -EINVAL;

	val = rcar_pci_पढ़ो_reg(pcie, PCIEMSITXR);
	rcar_pci_ग_लिखो_reg(pcie, val | (पूर्णांकerrupt_num - 1), PCIEMSITXR);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_ep_उठाओ_irq(काष्ठा pci_epc *epc, u8 fn,
				  क्रमागत pci_epc_irq_type type,
				  u16 पूर्णांकerrupt_num)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस rcar_pcie_ep_निश्चित_पूर्णांकx(ep, fn, 0);

	हाल PCI_EPC_IRQ_MSI:
		वापस rcar_pcie_ep_निश्चित_msi(&ep->pcie, fn, पूर्णांकerrupt_num);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_pcie_ep_start(काष्ठा pci_epc *epc)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);

	rcar_pci_ग_लिखो_reg(&ep->pcie, MACCTLR_INIT_VAL, MACCTLR);
	rcar_pci_ग_लिखो_reg(&ep->pcie, CFINIT, PCIETCTLR);

	वापस 0;
पूर्ण

अटल व्योम rcar_pcie_ep_stop(काष्ठा pci_epc *epc)
अणु
	काष्ठा rcar_pcie_endpoपूर्णांक *ep = epc_get_drvdata(epc);

	rcar_pci_ग_लिखो_reg(&ep->pcie, 0, PCIETCTLR);
पूर्ण

अटल स्थिर काष्ठा pci_epc_features rcar_pcie_epc_features = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = false,
	/* use 64-bit BARs so mark BAR[1,3,5] as reserved */
	.reserved_bar = 1 << BAR_1 | 1 << BAR_3 | 1 << BAR_5,
	.bar_fixed_64bit = 1 << BAR_0 | 1 << BAR_2 | 1 << BAR_4,
	.bar_fixed_size[0] = 128,
	.bar_fixed_size[2] = 256,
	.bar_fixed_size[4] = 256,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
rcar_pcie_ep_get_features(काष्ठा pci_epc *epc, u8 func_no)
अणु
	वापस &rcar_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा pci_epc_ops rcar_pcie_epc_ops = अणु
	.ग_लिखो_header	= rcar_pcie_ep_ग_लिखो_header,
	.set_bar	= rcar_pcie_ep_set_bar,
	.clear_bar	= rcar_pcie_ep_clear_bar,
	.set_msi	= rcar_pcie_ep_set_msi,
	.get_msi	= rcar_pcie_ep_get_msi,
	.map_addr	= rcar_pcie_ep_map_addr,
	.unmap_addr	= rcar_pcie_ep_unmap_addr,
	.उठाओ_irq	= rcar_pcie_ep_उठाओ_irq,
	.start		= rcar_pcie_ep_start,
	.stop		= rcar_pcie_ep_stop,
	.get_features	= rcar_pcie_ep_get_features,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_pcie_ep_of_match[] = अणु
	अणु .compatible = "renesas,r8a774c0-pcie-ep", पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-pcie-ep" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक rcar_pcie_ep_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_pcie_endpoपूर्णांक *ep;
	काष्ठा rcar_pcie *pcie;
	काष्ठा pci_epc *epc;
	पूर्णांक err;

	ep = devm_kzalloc(dev, माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	pcie = &ep->pcie;
	pcie->dev = dev;

	pm_runसमय_enable(dev);
	err = pm_runसमय_get_sync(dev);
	अगर (err < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_pm_disable;
	पूर्ण

	err = rcar_pcie_ep_get_pdata(ep, pdev);
	अगर (err < 0) अणु
		dev_err(dev, "failed to request resources: %d\n", err);
		जाओ err_pm_put;
	पूर्ण

	ep->num_ib_winकरोws = MAX_NR_INBOUND_MAPS;
	ep->ib_winकरोw_map =
			devm_kसुस्मृति(dev, BITS_TO_LONGS(ep->num_ib_winकरोws),
				     माप(दीर्घ), GFP_KERNEL);
	अगर (!ep->ib_winकरोw_map) अणु
		err = -ENOMEM;
		dev_err(dev, "failed to allocate memory for inbound map\n");
		जाओ err_pm_put;
	पूर्ण

	ep->ob_mapped_addr = devm_kसुस्मृति(dev, ep->num_ob_winकरोws,
					  माप(*ep->ob_mapped_addr),
					  GFP_KERNEL);
	अगर (!ep->ob_mapped_addr) अणु
		err = -ENOMEM;
		dev_err(dev, "failed to allocate memory for outbound memory pointers\n");
		जाओ err_pm_put;
	पूर्ण

	epc = devm_pci_epc_create(dev, &rcar_pcie_epc_ops);
	अगर (IS_ERR(epc)) अणु
		dev_err(dev, "failed to create epc device\n");
		err = PTR_ERR(epc);
		जाओ err_pm_put;
	पूर्ण

	epc->max_functions = ep->max_functions;
	epc_set_drvdata(epc, ep);

	rcar_pcie_ep_hw_init(pcie);

	err = pci_epc_multi_mem_init(epc, ep->ob_winकरोw, ep->num_ob_winकरोws);
	अगर (err < 0) अणु
		dev_err(dev, "failed to initialize the epc memory space\n");
		जाओ err_pm_put;
	पूर्ण

	वापस 0;

err_pm_put:
	pm_runसमय_put(dev);

err_pm_disable:
	pm_runसमय_disable(dev);

	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver rcar_pcie_ep_driver = अणु
	.driver = अणु
		.name = "rcar-pcie-ep",
		.of_match_table = rcar_pcie_ep_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = rcar_pcie_ep_probe,
पूर्ण;
builtin_platक्रमm_driver(rcar_pcie_ep_driver);
