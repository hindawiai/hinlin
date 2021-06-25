<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Rockchip AXI PCIe endpoपूर्णांक controller driver
 *
 * Copyright (c) 2018 Rockchip, Inc.
 *
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 *         Simon Xue <xxm@rock-chips.com>
 */

#समावेश <linux/configfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/pci-epc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/sizes.h>

#समावेश "pcie-rockchip.h"

/**
 * काष्ठा rockchip_pcie_ep - निजी data क्रम PCIe endpoपूर्णांक controller driver
 * @rockchip: Rockchip PCIe controller
 * @epc: PCI EPC device
 * @max_regions: maximum number of regions supported by hardware
 * @ob_region_map: biपंचांगask of mapped outbound regions
 * @ob_addr: base addresses in the AXI bus where the outbound regions start
 * @irq_phys_addr: base address on the AXI bus where the MSI/legacy IRQ
 *		   dedicated outbound regions is mapped.
 * @irq_cpu_addr: base address in the CPU space where a ग_लिखो access triggers
 *		  the sending of a memory ग_लिखो (MSI) / normal message (legacy
 *		  IRQ) TLP through the PCIe bus.
 * @irq_pci_addr: used to save the current mapping of the MSI/legacy IRQ
 *		  dedicated outbound region.
 * @irq_pci_fn: the latest PCI function that has updated the mapping of
 *		the MSI/legacy IRQ dedicated outbound region.
 * @irq_pending: biपंचांगask of निश्चितed legacy IRQs.
 */
काष्ठा rockchip_pcie_ep अणु
	काष्ठा rockchip_pcie	rockchip;
	काष्ठा pci_epc		*epc;
	u32			max_regions;
	अचिन्हित दीर्घ		ob_region_map;
	phys_addr_t		*ob_addr;
	phys_addr_t		irq_phys_addr;
	व्योम __iomem		*irq_cpu_addr;
	u64			irq_pci_addr;
	u8			irq_pci_fn;
	u8			irq_pending;
पूर्ण;

अटल व्योम rockchip_pcie_clear_ep_ob_atu(काष्ठा rockchip_pcie *rockchip,
					  u32 region)
अणु
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(region));
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(region));
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(region));
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(region));
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0(region));
	rockchip_pcie_ग_लिखो(rockchip, 0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1(region));
पूर्ण

अटल व्योम rockchip_pcie_prog_ep_ob_atu(काष्ठा rockchip_pcie *rockchip, u8 fn,
					 u32 r, u32 type, u64 cpu_addr,
					 u64 pci_addr, माप_प्रकार size)
अणु
	u64 sz = 1ULL << fls64(size - 1);
	पूर्णांक num_pass_bits = ilog2(sz);
	u32 addr0, addr1, desc0, desc1;
	bool is_nor_msg = (type == AXI_WRAPPER_NOR_MSG);

	/* The minimal region size is 1MB */
	अगर (num_pass_bits < 8)
		num_pass_bits = 8;

	cpu_addr -= rockchip->mem_res->start;
	addr0 = ((is_nor_msg ? 0x10 : (num_pass_bits - 1)) &
		PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
		(lower_32_bits(cpu_addr) & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
	addr1 = upper_32_bits(is_nor_msg ? cpu_addr : pci_addr);
	desc0 = ROCKCHIP_PCIE_AT_OB_REGION_DESC0_DEVFN(fn) | type;
	desc1 = 0;

	अगर (is_nor_msg) अणु
		rockchip_pcie_ग_लिखो(rockchip, 0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(r));
		rockchip_pcie_ग_लिखो(rockchip, 0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(r));
		rockchip_pcie_ग_लिखो(rockchip, desc0,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(r));
		rockchip_pcie_ग_लिखो(rockchip, desc1,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(r));
	पूर्ण अन्यथा अणु
		/* PCI bus address region */
		rockchip_pcie_ग_लिखो(rockchip, addr0,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR0(r));
		rockchip_pcie_ग_लिखो(rockchip, addr1,
				    ROCKCHIP_PCIE_AT_OB_REGION_PCI_ADDR1(r));
		rockchip_pcie_ग_लिखो(rockchip, desc0,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC0(r));
		rockchip_pcie_ग_लिखो(rockchip, desc1,
				    ROCKCHIP_PCIE_AT_OB_REGION_DESC1(r));

		addr0 =
		    ((num_pass_bits - 1) & PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
		    (lower_32_bits(cpu_addr) &
		     PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
		addr1 = upper_32_bits(cpu_addr);
	पूर्ण

	/* CPU bus address region */
	rockchip_pcie_ग_लिखो(rockchip, addr0,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR0(r));
	rockchip_pcie_ग_लिखो(rockchip, addr1,
			    ROCKCHIP_PCIE_AT_OB_REGION_CPU_ADDR1(r));
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_ग_लिखो_header(काष्ठा pci_epc *epc, u8 fn,
					 काष्ठा pci_epf_header *hdr)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;

	/* All functions share the same venकरोr ID with function 0 */
	अगर (fn == 0) अणु
		u32 vid_regs = (hdr->venकरोrid & GENMASK(15, 0)) |
			       (hdr->subsys_venकरोr_id & GENMASK(31, 16)) << 16;

		rockchip_pcie_ग_लिखो(rockchip, vid_regs,
				    PCIE_CORE_CONFIG_VENDOR);
	पूर्ण

	rockchip_pcie_ग_लिखो(rockchip, hdr->deviceid << 16,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) + PCI_VENDOR_ID);

	rockchip_pcie_ग_लिखो(rockchip,
			    hdr->revid |
			    hdr->progअगर_code << 8 |
			    hdr->subclass_code << 16 |
			    hdr->baseclass_code << 24,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) + PCI_REVISION_ID);
	rockchip_pcie_ग_लिखो(rockchip, hdr->cache_line_size,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_CACHE_LINE_SIZE);
	rockchip_pcie_ग_लिखो(rockchip, hdr->subsys_id << 16,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_SUBSYSTEM_VENDOR_ID);
	rockchip_pcie_ग_लिखो(rockchip, hdr->पूर्णांकerrupt_pin << 8,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_INTERRUPT_LINE);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_set_bar(काष्ठा pci_epc *epc, u8 fn,
				    काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	dma_addr_t bar_phys = epf_bar->phys_addr;
	क्रमागत pci_barno bar = epf_bar->barno;
	पूर्णांक flags = epf_bar->flags;
	u32 addr0, addr1, reg, cfg, b, aperture, ctrl;
	u64 sz;

	/* BAR size is 2^(aperture + 7) */
	sz = max_t(माप_प्रकार, epf_bar->size, MIN_EP_APERTURE);

	/*
	 * roundup_घात_of_two() वापसs an अचिन्हित दीर्घ, which is not suited
	 * क्रम 64bit values.
	 */
	sz = 1ULL << fls64(sz - 1);
	aperture = ilog2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

	अगर ((flags & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) अणु
		ctrl = ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_IO_32BITS;
	पूर्ण अन्यथा अणु
		bool is_prefetch = !!(flags & PCI_BASE_ADDRESS_MEM_PREFETCH);
		bool is_64bits = sz > SZ_2G;

		अगर (is_64bits && (bar & 1))
			वापस -EINVAL;

		अगर (is_64bits && is_prefetch)
			ctrl =
			    ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_64BITS;
		अन्यथा अगर (is_prefetch)
			ctrl =
			    ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_32BITS;
		अन्यथा अगर (is_64bits)
			ctrl = ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_MEM_64BITS;
		अन्यथा
			ctrl = ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_MEM_32BITS;
	पूर्ण

	अगर (bar < BAR_4) अणु
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	पूर्ण अन्यथा अणु
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	पूर्ण

	addr0 = lower_32_bits(bar_phys);
	addr1 = upper_32_bits(bar_phys);

	cfg = rockchip_pcie_पढ़ो(rockchip, reg);
	cfg &= ~(ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= (ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE(b, aperture) |
		ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl));

	rockchip_pcie_ग_लिखो(rockchip, cfg, reg);
	rockchip_pcie_ग_लिखो(rockchip, addr0,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar));
	rockchip_pcie_ग_लिखो(rockchip, addr1,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar));

	वापस 0;
पूर्ण

अटल व्योम rockchip_pcie_ep_clear_bar(काष्ठा pci_epc *epc, u8 fn,
				       काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u32 reg, cfg, b, ctrl;
	क्रमागत pci_barno bar = epf_bar->barno;

	अगर (bar < BAR_4) अणु
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	पूर्ण अन्यथा अणु
		reg = ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	पूर्ण

	ctrl = ROCKCHIP_PCIE_CORE_BAR_CFG_CTRL_DISABLED;
	cfg = rockchip_pcie_पढ़ो(rockchip, reg);
	cfg &= ~(ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= ROCKCHIP_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);

	rockchip_pcie_ग_लिखो(rockchip, cfg, reg);
	rockchip_pcie_ग_लिखो(rockchip, 0x0,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar));
	rockchip_pcie_ग_लिखो(rockchip, 0x0,
			    ROCKCHIP_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar));
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_map_addr(काष्ठा pci_epc *epc, u8 fn,
				     phys_addr_t addr, u64 pci_addr,
				     माप_प्रकार size)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *pcie = &ep->rockchip;
	u32 r;

	r = find_first_zero_bit(&ep->ob_region_map,
				माप(ep->ob_region_map) * BITS_PER_LONG);
	/*
	 * Region 0 is reserved क्रम configuration space and shouldn't
	 * be used अन्यथाwhere per TRM, so leave it out.
	 */
	अगर (r >= ep->max_regions - 1) अणु
		dev_err(&epc->dev, "no free outbound region\n");
		वापस -EINVAL;
	पूर्ण

	rockchip_pcie_prog_ep_ob_atu(pcie, fn, r, AXI_WRAPPER_MEM_WRITE, addr,
				     pci_addr, size);

	set_bit(r, &ep->ob_region_map);
	ep->ob_addr[r] = addr;

	वापस 0;
पूर्ण

अटल व्योम rockchip_pcie_ep_unmap_addr(काष्ठा pci_epc *epc, u8 fn,
					phys_addr_t addr)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u32 r;

	क्रम (r = 0; r < ep->max_regions - 1; r++)
		अगर (ep->ob_addr[r] == addr)
			अवरोध;

	/*
	 * Region 0 is reserved क्रम configuration space and shouldn't
	 * be used अन्यथाwhere per TRM, so leave it out.
	 */
	अगर (r == ep->max_regions - 1)
		वापस;

	rockchip_pcie_clear_ep_ob_atu(rockchip, r);

	ep->ob_addr[r] = 0;
	clear_bit(r, &ep->ob_region_map);
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_set_msi(काष्ठा pci_epc *epc, u8 fn,
				    u8 multi_msg_cap)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags;

	flags = rockchip_pcie_पढ़ो(rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	flags &= ~ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_MASK;
	flags |=
	   ((multi_msg_cap << 1) <<  ROCKCHIP_PCIE_EP_MSI_CTRL_MMC_OFFSET) |
	   PCI_MSI_FLAGS_64BIT;
	flags &= ~ROCKCHIP_PCIE_EP_MSI_CTRL_MASK_MSI_CAP;
	rockchip_pcie_ग_लिखो(rockchip, flags,
			    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_get_msi(काष्ठा pci_epc *epc, u8 fn)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags;

	flags = rockchip_pcie_पढ़ो(rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	अगर (!(flags & ROCKCHIP_PCIE_EP_MSI_CTRL_ME))
		वापस -EINVAL;

	वापस ((flags & ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK) >>
			ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET);
पूर्ण

अटल व्योम rockchip_pcie_ep_निश्चित_पूर्णांकx(काष्ठा rockchip_pcie_ep *ep, u8 fn,
					 u8 पूर्णांकx, bool is_निश्चितed)
अणु
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u32 r = ep->max_regions - 1;
	u32 offset;
	u32 status;
	u8 msg_code;

	अगर (unlikely(ep->irq_pci_addr != ROCKCHIP_PCIE_EP_PCI_LEGACY_IRQ_ADDR ||
		     ep->irq_pci_fn != fn)) अणु
		rockchip_pcie_prog_ep_ob_atu(rockchip, fn, r,
					     AXI_WRAPPER_NOR_MSG,
					     ep->irq_phys_addr, 0, 0);
		ep->irq_pci_addr = ROCKCHIP_PCIE_EP_PCI_LEGACY_IRQ_ADDR;
		ep->irq_pci_fn = fn;
	पूर्ण

	पूर्णांकx &= 3;
	अगर (is_निश्चितed) अणु
		ep->irq_pending |= BIT(पूर्णांकx);
		msg_code = ROCKCHIP_PCIE_MSG_CODE_ASSERT_INTA + पूर्णांकx;
	पूर्ण अन्यथा अणु
		ep->irq_pending &= ~BIT(पूर्णांकx);
		msg_code = ROCKCHIP_PCIE_MSG_CODE_DEASSERT_INTA + पूर्णांकx;
	पूर्ण

	status = rockchip_pcie_पढ़ो(rockchip,
				    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				    ROCKCHIP_PCIE_EP_CMD_STATUS);
	status &= ROCKCHIP_PCIE_EP_CMD_STATUS_IS;

	अगर ((status != 0) ^ (ep->irq_pending != 0)) अणु
		status ^= ROCKCHIP_PCIE_EP_CMD_STATUS_IS;
		rockchip_pcie_ग_लिखो(rockchip, status,
				    ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				    ROCKCHIP_PCIE_EP_CMD_STATUS);
	पूर्ण

	offset =
	   ROCKCHIP_PCIE_MSG_ROUTING(ROCKCHIP_PCIE_MSG_ROUTING_LOCAL_INTX) |
	   ROCKCHIP_PCIE_MSG_CODE(msg_code) | ROCKCHIP_PCIE_MSG_NO_DATA;
	ग_लिखोl(0, ep->irq_cpu_addr + offset);
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_send_legacy_irq(काष्ठा rockchip_pcie_ep *ep, u8 fn,
					    u8 पूर्णांकx)
अणु
	u16 cmd;

	cmd = rockchip_pcie_पढ़ो(&ep->rockchip,
				 ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				 ROCKCHIP_PCIE_EP_CMD_STATUS);

	अगर (cmd & PCI_COMMAND_INTX_DISABLE)
		वापस -EINVAL;

	/*
	 * Should add some delay between toggling INTx per TRM vaguely saying
	 * it depends on some cycles of the AHB bus घड़ी to function it. So
	 * add sufficient 1ms here.
	 */
	rockchip_pcie_ep_निश्चित_पूर्णांकx(ep, fn, पूर्णांकx, true);
	mdelay(1);
	rockchip_pcie_ep_निश्चित_पूर्णांकx(ep, fn, पूर्णांकx, false);
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_send_msi_irq(काष्ठा rockchip_pcie_ep *ep, u8 fn,
					 u8 पूर्णांकerrupt_num)
अणु
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags, mme, data, data_mask;
	u8 msi_count;
	u64 pci_addr, pci_addr_mask = 0xff;

	/* Check MSI enable bit */
	flags = rockchip_pcie_पढ़ो(&ep->rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	अगर (!(flags & ROCKCHIP_PCIE_EP_MSI_CTRL_ME))
		वापस -EINVAL;

	/* Get MSI numbers from MME */
	mme = ((flags & ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK) >>
			ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET);
	msi_count = 1 << mme;
	अगर (!पूर्णांकerrupt_num || पूर्णांकerrupt_num > msi_count)
		वापस -EINVAL;

	/* Set MSI निजी data */
	data_mask = msi_count - 1;
	data = rockchip_pcie_पढ़ो(rockchip,
				  ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				  ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				  PCI_MSI_DATA_64);
	data = (data & ~data_mask) | ((पूर्णांकerrupt_num - 1) & data_mask);

	/* Get MSI PCI address */
	pci_addr = rockchip_pcie_पढ़ो(rockchip,
				      ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				      ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				      PCI_MSI_ADDRESS_HI);
	pci_addr <<= 32;
	pci_addr |= rockchip_pcie_पढ़ो(rockchip,
				       ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				       ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				       PCI_MSI_ADDRESS_LO);
	pci_addr &= GENMASK_ULL(63, 2);

	/* Set the outbound region अगर needed. */
	अगर (unlikely(ep->irq_pci_addr != (pci_addr & ~pci_addr_mask) ||
		     ep->irq_pci_fn != fn)) अणु
		rockchip_pcie_prog_ep_ob_atu(rockchip, fn, ep->max_regions - 1,
					     AXI_WRAPPER_MEM_WRITE,
					     ep->irq_phys_addr,
					     pci_addr & ~pci_addr_mask,
					     pci_addr_mask + 1);
		ep->irq_pci_addr = (pci_addr & ~pci_addr_mask);
		ep->irq_pci_fn = fn;
	पूर्ण

	ग_लिखोw(data, ep->irq_cpu_addr + (pci_addr & pci_addr_mask));
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_उठाओ_irq(काष्ठा pci_epc *epc, u8 fn,
				      क्रमागत pci_epc_irq_type type,
				      u16 पूर्णांकerrupt_num)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस rockchip_pcie_ep_send_legacy_irq(ep, fn, 0);
	हाल PCI_EPC_IRQ_MSI:
		वापस rockchip_pcie_ep_send_msi_irq(ep, fn, पूर्णांकerrupt_num);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rockchip_pcie_ep_start(काष्ठा pci_epc *epc)
अणु
	काष्ठा rockchip_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा rockchip_pcie *rockchip = &ep->rockchip;
	काष्ठा pci_epf *epf;
	u32 cfg;

	cfg = BIT(0);
	list_क्रम_each_entry(epf, &epc->pci_epf, list)
		cfg |= BIT(epf->func_no);

	rockchip_pcie_ग_लिखो(rockchip, cfg, PCIE_CORE_PHY_FUNC_CFG);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features rockchip_pcie_epc_features = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = false,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
rockchip_pcie_ep_get_features(काष्ठा pci_epc *epc, u8 func_no)
अणु
	वापस &rockchip_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा pci_epc_ops rockchip_pcie_epc_ops = अणु
	.ग_लिखो_header	= rockchip_pcie_ep_ग_लिखो_header,
	.set_bar	= rockchip_pcie_ep_set_bar,
	.clear_bar	= rockchip_pcie_ep_clear_bar,
	.map_addr	= rockchip_pcie_ep_map_addr,
	.unmap_addr	= rockchip_pcie_ep_unmap_addr,
	.set_msi	= rockchip_pcie_ep_set_msi,
	.get_msi	= rockchip_pcie_ep_get_msi,
	.उठाओ_irq	= rockchip_pcie_ep_उठाओ_irq,
	.start		= rockchip_pcie_ep_start,
	.get_features	= rockchip_pcie_ep_get_features,
पूर्ण;

अटल पूर्णांक rockchip_pcie_parse_ep_dt(काष्ठा rockchip_pcie *rockchip,
				     काष्ठा rockchip_pcie_ep *ep)
अणु
	काष्ठा device *dev = rockchip->dev;
	पूर्णांक err;

	err = rockchip_pcie_parse_dt(rockchip);
	अगर (err)
		वापस err;

	err = rockchip_pcie_get_phys(rockchip);
	अगर (err)
		वापस err;

	err = of_property_पढ़ो_u32(dev->of_node,
				   "rockchip,max-outbound-regions",
				   &ep->max_regions);
	अगर (err < 0 || ep->max_regions > MAX_REGION_LIMIT)
		ep->max_regions = MAX_REGION_LIMIT;

	err = of_property_पढ़ो_u8(dev->of_node, "max-functions",
				  &ep->epc->max_functions);
	अगर (err < 0)
		ep->epc->max_functions = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_pcie_ep_of_match[] = अणु
	अणु .compatible = "rockchip,rk3399-pcie-ep"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक rockchip_pcie_ep_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_pcie_ep *ep;
	काष्ठा rockchip_pcie *rockchip;
	काष्ठा pci_epc *epc;
	माप_प्रकार max_regions;
	पूर्णांक err;

	ep = devm_kzalloc(dev, माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	rockchip = &ep->rockchip;
	rockchip->is_rc = false;
	rockchip->dev = dev;

	epc = devm_pci_epc_create(dev, &rockchip_pcie_epc_ops);
	अगर (IS_ERR(epc)) अणु
		dev_err(dev, "failed to create epc device\n");
		वापस PTR_ERR(epc);
	पूर्ण

	ep->epc = epc;
	epc_set_drvdata(epc, ep);

	err = rockchip_pcie_parse_ep_dt(rockchip, ep);
	अगर (err)
		वापस err;

	err = rockchip_pcie_enable_घड़ीs(rockchip);
	अगर (err)
		वापस err;

	err = rockchip_pcie_init_port(rockchip);
	अगर (err)
		जाओ err_disable_घड़ीs;

	/* Establish the link स्वतःmatically */
	rockchip_pcie_ग_लिखो(rockchip, PCIE_CLIENT_LINK_TRAIN_ENABLE,
			    PCIE_CLIENT_CONFIG);

	max_regions = ep->max_regions;
	ep->ob_addr = devm_kसुस्मृति(dev, max_regions, माप(*ep->ob_addr),
				   GFP_KERNEL);

	अगर (!ep->ob_addr) अणु
		err = -ENOMEM;
		जाओ err_uninit_port;
	पूर्ण

	/* Only enable function 0 by शेष */
	rockchip_pcie_ग_लिखो(rockchip, BIT(0), PCIE_CORE_PHY_FUNC_CFG);

	err = pci_epc_mem_init(epc, rockchip->mem_res->start,
			       resource_size(rockchip->mem_res), PAGE_SIZE);
	अगर (err < 0) अणु
		dev_err(dev, "failed to initialize the memory space\n");
		जाओ err_uninit_port;
	पूर्ण

	ep->irq_cpu_addr = pci_epc_mem_alloc_addr(epc, &ep->irq_phys_addr,
						  SZ_128K);
	अगर (!ep->irq_cpu_addr) अणु
		dev_err(dev, "failed to reserve memory space for MSI\n");
		err = -ENOMEM;
		जाओ err_epc_mem_निकास;
	पूर्ण

	ep->irq_pci_addr = ROCKCHIP_PCIE_EP_DUMMY_IRQ_ADDR;

	वापस 0;
err_epc_mem_निकास:
	pci_epc_mem_निकास(epc);
err_uninit_port:
	rockchip_pcie_deinit_phys(rockchip);
err_disable_घड़ीs:
	rockchip_pcie_disable_घड़ीs(rockchip);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_pcie_ep_driver = अणु
	.driver = अणु
		.name = "rockchip-pcie-ep",
		.of_match_table = rockchip_pcie_ep_of_match,
	पूर्ण,
	.probe = rockchip_pcie_ep_probe,
पूर्ण;

builtin_platक्रमm_driver(rockchip_pcie_ep_driver);
