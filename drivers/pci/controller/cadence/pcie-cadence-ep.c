<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Cadence
// Cadence PCIe endpoपूर्णांक controller driver.
// Author: Cyrille Pitchen <cyrille.pitchen@मुक्त-electrons.com>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/pci-epc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sizes.h>

#समावेश "pcie-cadence.h"

#घोषणा CDNS_PCIE_EP_MIN_APERTURE		128	/* 128 bytes */
#घोषणा CDNS_PCIE_EP_IRQ_PCI_ADDR_NONE		0x1
#घोषणा CDNS_PCIE_EP_IRQ_PCI_ADDR_LEGACY	0x3

अटल पूर्णांक cdns_pcie_ep_ग_लिखो_header(काष्ठा pci_epc *epc, u8 fn,
				     काष्ठा pci_epf_header *hdr)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;

	cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, PCI_DEVICE_ID, hdr->deviceid);
	cdns_pcie_ep_fn_ग_लिखोb(pcie, fn, PCI_REVISION_ID, hdr->revid);
	cdns_pcie_ep_fn_ग_लिखोb(pcie, fn, PCI_CLASS_PROG, hdr->progअगर_code);
	cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, PCI_CLASS_DEVICE,
			       hdr->subclass_code | hdr->baseclass_code << 8);
	cdns_pcie_ep_fn_ग_लिखोb(pcie, fn, PCI_CACHE_LINE_SIZE,
			       hdr->cache_line_size);
	cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, PCI_SUBSYSTEM_ID, hdr->subsys_id);
	cdns_pcie_ep_fn_ग_लिखोb(pcie, fn, PCI_INTERRUPT_PIN, hdr->पूर्णांकerrupt_pin);

	/*
	 * Venकरोr ID can only be modअगरied from function 0, all other functions
	 * use the same venकरोr ID as function 0.
	 */
	अगर (fn == 0) अणु
		/* Update the venकरोr IDs. */
		u32 id = CDNS_PCIE_LM_ID_VENDOR(hdr->venकरोrid) |
			 CDNS_PCIE_LM_ID_SUBSYS(hdr->subsys_venकरोr_id);

		cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_ID, id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_set_bar(काष्ठा pci_epc *epc, u8 fn,
				काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie_epf *epf = &ep->epf[fn];
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	dma_addr_t bar_phys = epf_bar->phys_addr;
	क्रमागत pci_barno bar = epf_bar->barno;
	पूर्णांक flags = epf_bar->flags;
	u32 addr0, addr1, reg, cfg, b, aperture, ctrl;
	u64 sz;

	/* BAR size is 2^(aperture + 7) */
	sz = max_t(माप_प्रकार, epf_bar->size, CDNS_PCIE_EP_MIN_APERTURE);
	/*
	 * roundup_घात_of_two() वापसs an अचिन्हित दीर्घ, which is not suited
	 * क्रम 64bit values.
	 */
	sz = 1ULL << fls64(sz - 1);
	aperture = ilog2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

	अगर ((flags & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) अणु
		ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS;
	पूर्ण अन्यथा अणु
		bool is_prefetch = !!(flags & PCI_BASE_ADDRESS_MEM_PREFETCH);
		bool is_64bits = sz > SZ_2G;

		अगर (is_64bits && (bar & 1))
			वापस -EINVAL;

		अगर (is_64bits && !(flags & PCI_BASE_ADDRESS_MEM_TYPE_64))
			epf_bar->flags |= PCI_BASE_ADDRESS_MEM_TYPE_64;

		अगर (is_64bits && is_prefetch)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS;
		अन्यथा अगर (is_prefetch)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS;
		अन्यथा अगर (is_64bits)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS;
		अन्यथा
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS;
	पूर्ण

	addr0 = lower_32_bits(bar_phys);
	addr1 = upper_32_bits(bar_phys);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar),
			 addr0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar),
			 addr1);

	अगर (bar < BAR_4) अणु
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	पूर्ण अन्यथा अणु
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	पूर्ण

	cfg = cdns_pcie_पढ़ोl(pcie, reg);
	cfg &= ~(CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= (CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, aperture) |
		CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl));
	cdns_pcie_ग_लिखोl(pcie, reg, cfg);

	epf->epf_bar[bar] = epf_bar;

	वापस 0;
पूर्ण

अटल व्योम cdns_pcie_ep_clear_bar(काष्ठा pci_epc *epc, u8 fn,
				   काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie_epf *epf = &ep->epf[fn];
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	क्रमागत pci_barno bar = epf_bar->barno;
	u32 reg, cfg, b, ctrl;

	अगर (bar < BAR_4) अणु
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	पूर्ण अन्यथा अणु
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	पूर्ण

	ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED;
	cfg = cdns_pcie_पढ़ोl(pcie, reg);
	cfg &= ~(CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		 CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);
	cdns_pcie_ग_लिखोl(pcie, reg, cfg);

	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar), 0);
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar), 0);

	epf->epf_bar[bar] = शून्य;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_map_addr(काष्ठा pci_epc *epc, u8 fn, phys_addr_t addr,
				 u64 pci_addr, माप_प्रकार size)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 r;

	r = find_first_zero_bit(&ep->ob_region_map,
				माप(ep->ob_region_map) * BITS_PER_LONG);
	अगर (r >= ep->max_regions - 1) अणु
		dev_err(&epc->dev, "no free outbound region\n");
		वापस -EINVAL;
	पूर्ण

	cdns_pcie_set_outbound_region(pcie, 0, fn, r, false, addr, pci_addr, size);

	set_bit(r, &ep->ob_region_map);
	ep->ob_addr[r] = addr;

	वापस 0;
पूर्ण

अटल व्योम cdns_pcie_ep_unmap_addr(काष्ठा pci_epc *epc, u8 fn,
				    phys_addr_t addr)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 r;

	क्रम (r = 0; r < ep->max_regions - 1; r++)
		अगर (ep->ob_addr[r] == addr)
			अवरोध;

	अगर (r == ep->max_regions - 1)
		वापस;

	cdns_pcie_reset_outbound_region(pcie, r);

	ep->ob_addr[r] = 0;
	clear_bit(r, &ep->ob_region_map);
पूर्ण

अटल पूर्णांक cdns_pcie_ep_set_msi(काष्ठा pci_epc *epc, u8 fn, u8 mmc)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 flags;

	/*
	 * Set the Multiple Message Capable bitfield पूर्णांकo the Message Control
	 * रेजिस्टर.
	 */
	flags = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_FLAGS);
	flags = (flags & ~PCI_MSI_FLAGS_QMASK) | (mmc << 1);
	flags |= PCI_MSI_FLAGS_64BIT;
	flags &= ~PCI_MSI_FLAGS_MASKBIT;
	cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, cap + PCI_MSI_FLAGS, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_get_msi(काष्ठा pci_epc *epc, u8 fn)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 flags, mme;

	/* Validate that the MSI feature is actually enabled. */
	flags = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_FLAGS);
	अगर (!(flags & PCI_MSI_FLAGS_ENABLE))
		वापस -EINVAL;

	/*
	 * Get the Multiple Message Enable bitfield from the Message Control
	 * रेजिस्टर.
	 */
	mme = (flags & PCI_MSI_FLAGS_QSIZE) >> 4;

	वापस mme;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_get_msix(काष्ठा pci_epc *epc, u8 func_no)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 val, reg;

	reg = cap + PCI_MSIX_FLAGS;
	val = cdns_pcie_ep_fn_पढ़ोw(pcie, func_no, reg);
	अगर (!(val & PCI_MSIX_FLAGS_ENABLE))
		वापस -EINVAL;

	val &= PCI_MSIX_FLAGS_QSIZE;

	वापस val;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_set_msix(काष्ठा pci_epc *epc, u8 fn, u16 पूर्णांकerrupts,
				 क्रमागत pci_barno bir, u32 offset)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 val, reg;

	reg = cap + PCI_MSIX_FLAGS;
	val = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, reg);
	val &= ~PCI_MSIX_FLAGS_QSIZE;
	val |= पूर्णांकerrupts;
	cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, reg, val);

	/* Set MSIX BAR and offset */
	reg = cap + PCI_MSIX_TABLE;
	val = offset | bir;
	cdns_pcie_ep_fn_ग_लिखोl(pcie, fn, reg, val);

	/* Set PBA BAR and offset.  BAR must match MSIX BAR */
	reg = cap + PCI_MSIX_PBA;
	val = (offset + (पूर्णांकerrupts * PCI_MSIX_ENTRY_SIZE)) | bir;
	cdns_pcie_ep_fn_ग_लिखोl(pcie, fn, reg, val);

	वापस 0;
पूर्ण

अटल व्योम cdns_pcie_ep_निश्चित_पूर्णांकx(काष्ठा cdns_pcie_ep *ep, u8 fn,
				     u8 पूर्णांकx, bool is_निश्चितed)
अणु
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	अचिन्हित दीर्घ flags;
	u32 offset;
	u16 status;
	u8 msg_code;

	पूर्णांकx &= 3;

	/* Set the outbound region अगर needed. */
	अगर (unlikely(ep->irq_pci_addr != CDNS_PCIE_EP_IRQ_PCI_ADDR_LEGACY ||
		     ep->irq_pci_fn != fn)) अणु
		/* First region was reserved क्रम IRQ ग_लिखोs. */
		cdns_pcie_set_outbound_region_क्रम_normal_msg(pcie, 0, fn, 0,
							     ep->irq_phys_addr);
		ep->irq_pci_addr = CDNS_PCIE_EP_IRQ_PCI_ADDR_LEGACY;
		ep->irq_pci_fn = fn;
	पूर्ण

	अगर (is_निश्चितed) अणु
		ep->irq_pending |= BIT(पूर्णांकx);
		msg_code = MSG_CODE_ASSERT_INTA + पूर्णांकx;
	पूर्ण अन्यथा अणु
		ep->irq_pending &= ~BIT(पूर्णांकx);
		msg_code = MSG_CODE_DEASSERT_INTA + पूर्णांकx;
	पूर्ण

	spin_lock_irqsave(&ep->lock, flags);
	status = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, PCI_STATUS);
	अगर (((status & PCI_STATUS_INTERRUPT) != 0) ^ (ep->irq_pending != 0)) अणु
		status ^= PCI_STATUS_INTERRUPT;
		cdns_pcie_ep_fn_ग_लिखोw(pcie, fn, PCI_STATUS, status);
	पूर्ण
	spin_unlock_irqrestore(&ep->lock, flags);

	offset = CDNS_PCIE_NORMAL_MSG_ROUTING(MSG_ROUTING_LOCAL) |
		 CDNS_PCIE_NORMAL_MSG_CODE(msg_code) |
		 CDNS_PCIE_MSG_NO_DATA;
	ग_लिखोl(0, ep->irq_cpu_addr + offset);
पूर्ण

अटल पूर्णांक cdns_pcie_ep_send_legacy_irq(काष्ठा cdns_pcie_ep *ep, u8 fn, u8 पूर्णांकx)
अणु
	u16 cmd;

	cmd = cdns_pcie_ep_fn_पढ़ोw(&ep->pcie, fn, PCI_COMMAND);
	अगर (cmd & PCI_COMMAND_INTX_DISABLE)
		वापस -EINVAL;

	cdns_pcie_ep_निश्चित_पूर्णांकx(ep, fn, पूर्णांकx, true);
	/*
	 * The mdelay() value was taken from dra7xx_pcie_उठाओ_legacy_irq()
	 */
	mdelay(1);
	cdns_pcie_ep_निश्चित_पूर्णांकx(ep, fn, पूर्णांकx, false);
	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_send_msi_irq(काष्ठा cdns_pcie_ep *ep, u8 fn,
				     u8 पूर्णांकerrupt_num)
अणु
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 flags, mme, data, data_mask;
	u8 msi_count;
	u64 pci_addr, pci_addr_mask = 0xff;

	/* Check whether the MSI feature has been enabled by the PCI host. */
	flags = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_FLAGS);
	अगर (!(flags & PCI_MSI_FLAGS_ENABLE))
		वापस -EINVAL;

	/* Get the number of enabled MSIs */
	mme = (flags & PCI_MSI_FLAGS_QSIZE) >> 4;
	msi_count = 1 << mme;
	अगर (!पूर्णांकerrupt_num || पूर्णांकerrupt_num > msi_count)
		वापस -EINVAL;

	/* Compute the data value to be written. */
	data_mask = msi_count - 1;
	data = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_DATA_64);
	data = (data & ~data_mask) | ((पूर्णांकerrupt_num - 1) & data_mask);

	/* Get the PCI address where to ग_लिखो the data पूर्णांकo. */
	pci_addr = cdns_pcie_ep_fn_पढ़ोl(pcie, fn, cap + PCI_MSI_ADDRESS_HI);
	pci_addr <<= 32;
	pci_addr |= cdns_pcie_ep_fn_पढ़ोl(pcie, fn, cap + PCI_MSI_ADDRESS_LO);
	pci_addr &= GENMASK_ULL(63, 2);

	/* Set the outbound region अगर needed. */
	अगर (unlikely(ep->irq_pci_addr != (pci_addr & ~pci_addr_mask) ||
		     ep->irq_pci_fn != fn)) अणु
		/* First region was reserved क्रम IRQ ग_लिखोs. */
		cdns_pcie_set_outbound_region(pcie, 0, fn, 0,
					      false,
					      ep->irq_phys_addr,
					      pci_addr & ~pci_addr_mask,
					      pci_addr_mask + 1);
		ep->irq_pci_addr = (pci_addr & ~pci_addr_mask);
		ep->irq_pci_fn = fn;
	पूर्ण
	ग_लिखोl(data, ep->irq_cpu_addr + (pci_addr & pci_addr_mask));

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_map_msi_irq(काष्ठा pci_epc *epc, u8 fn,
				    phys_addr_t addr, u8 पूर्णांकerrupt_num,
				    u32 entry_size, u32 *msi_data,
				    u32 *msi_addr_offset)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	u64 pci_addr, pci_addr_mask = 0xff;
	u16 flags, mme, data, data_mask;
	u8 msi_count;
	पूर्णांक ret;
	पूर्णांक i;

	/* Check whether the MSI feature has been enabled by the PCI host. */
	flags = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_FLAGS);
	अगर (!(flags & PCI_MSI_FLAGS_ENABLE))
		वापस -EINVAL;

	/* Get the number of enabled MSIs */
	mme = (flags & PCI_MSI_FLAGS_QSIZE) >> 4;
	msi_count = 1 << mme;
	अगर (!पूर्णांकerrupt_num || पूर्णांकerrupt_num > msi_count)
		वापस -EINVAL;

	/* Compute the data value to be written. */
	data_mask = msi_count - 1;
	data = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSI_DATA_64);
	data = data & ~data_mask;

	/* Get the PCI address where to ग_लिखो the data पूर्णांकo. */
	pci_addr = cdns_pcie_ep_fn_पढ़ोl(pcie, fn, cap + PCI_MSI_ADDRESS_HI);
	pci_addr <<= 32;
	pci_addr |= cdns_pcie_ep_fn_पढ़ोl(pcie, fn, cap + PCI_MSI_ADDRESS_LO);
	pci_addr &= GENMASK_ULL(63, 2);

	क्रम (i = 0; i < पूर्णांकerrupt_num; i++) अणु
		ret = cdns_pcie_ep_map_addr(epc, fn, addr,
					    pci_addr & ~pci_addr_mask,
					    entry_size);
		अगर (ret)
			वापस ret;
		addr = addr + entry_size;
	पूर्ण

	*msi_data = data;
	*msi_addr_offset = pci_addr & pci_addr_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_send_msix_irq(काष्ठा cdns_pcie_ep *ep, u8 fn,
				      u16 पूर्णांकerrupt_num)
अणु
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 tbl_offset, msg_data, reg;
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	काष्ठा pci_epf_msix_tbl *msix_tbl;
	काष्ठा cdns_pcie_epf *epf;
	u64 pci_addr_mask = 0xff;
	u64 msg_addr;
	u16 flags;
	u8 bir;

	/* Check whether the MSI-X feature has been enabled by the PCI host. */
	flags = cdns_pcie_ep_fn_पढ़ोw(pcie, fn, cap + PCI_MSIX_FLAGS);
	अगर (!(flags & PCI_MSIX_FLAGS_ENABLE))
		वापस -EINVAL;

	reg = cap + PCI_MSIX_TABLE;
	tbl_offset = cdns_pcie_ep_fn_पढ़ोl(pcie, fn, reg);
	bir = tbl_offset & PCI_MSIX_TABLE_BIR;
	tbl_offset &= PCI_MSIX_TABLE_OFFSET;

	epf = &ep->epf[fn];
	msix_tbl = epf->epf_bar[bir]->addr + tbl_offset;
	msg_addr = msix_tbl[(पूर्णांकerrupt_num - 1)].msg_addr;
	msg_data = msix_tbl[(पूर्णांकerrupt_num - 1)].msg_data;

	/* Set the outbound region अगर needed. */
	अगर (ep->irq_pci_addr != (msg_addr & ~pci_addr_mask) ||
	    ep->irq_pci_fn != fn) अणु
		/* First region was reserved क्रम IRQ ग_लिखोs. */
		cdns_pcie_set_outbound_region(pcie, 0, fn, 0,
					      false,
					      ep->irq_phys_addr,
					      msg_addr & ~pci_addr_mask,
					      pci_addr_mask + 1);
		ep->irq_pci_addr = (msg_addr & ~pci_addr_mask);
		ep->irq_pci_fn = fn;
	पूर्ण
	ग_लिखोl(msg_data, ep->irq_cpu_addr + (msg_addr & pci_addr_mask));

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_उठाओ_irq(काष्ठा pci_epc *epc, u8 fn,
				  क्रमागत pci_epc_irq_type type,
				  u16 पूर्णांकerrupt_num)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस cdns_pcie_ep_send_legacy_irq(ep, fn, 0);

	हाल PCI_EPC_IRQ_MSI:
		वापस cdns_pcie_ep_send_msi_irq(ep, fn, पूर्णांकerrupt_num);

	हाल PCI_EPC_IRQ_MSIX:
		वापस cdns_pcie_ep_send_msix_irq(ep, fn, पूर्णांकerrupt_num);

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cdns_pcie_ep_start(काष्ठा pci_epc *epc)
अणु
	काष्ठा cdns_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	काष्ठा device *dev = pcie->dev;
	पूर्णांक ret;

	/*
	 * BIT(0) is hardwired to 1, hence function 0 is always enabled
	 * and can't be disabled anyway.
	 */
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_EP_FUNC_CFG, epc->function_num_map);

	ret = cdns_pcie_start_link(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to start link\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features cdns_pcie_epc_features = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = true,
	.align = 256,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
cdns_pcie_ep_get_features(काष्ठा pci_epc *epc, u8 func_no)
अणु
	वापस &cdns_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा pci_epc_ops cdns_pcie_epc_ops = अणु
	.ग_लिखो_header	= cdns_pcie_ep_ग_लिखो_header,
	.set_bar	= cdns_pcie_ep_set_bar,
	.clear_bar	= cdns_pcie_ep_clear_bar,
	.map_addr	= cdns_pcie_ep_map_addr,
	.unmap_addr	= cdns_pcie_ep_unmap_addr,
	.set_msi	= cdns_pcie_ep_set_msi,
	.get_msi	= cdns_pcie_ep_get_msi,
	.set_msix	= cdns_pcie_ep_set_msix,
	.get_msix	= cdns_pcie_ep_get_msix,
	.उठाओ_irq	= cdns_pcie_ep_उठाओ_irq,
	.map_msi_irq	= cdns_pcie_ep_map_msi_irq,
	.start		= cdns_pcie_ep_start,
	.get_features	= cdns_pcie_ep_get_features,
पूर्ण;


पूर्णांक cdns_pcie_ep_setup(काष्ठा cdns_pcie_ep *ep)
अणु
	काष्ठा device *dev = ep->pcie.dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cdns_pcie *pcie = &ep->pcie;
	काष्ठा resource *res;
	काष्ठा pci_epc *epc;
	पूर्णांक ret;

	pcie->is_rc = false;

	pcie->reg_base = devm_platक्रमm_ioremap_resource_byname(pdev, "reg");
	अगर (IS_ERR(pcie->reg_base)) अणु
		dev_err(dev, "missing \"reg\"\n");
		वापस PTR_ERR(pcie->reg_base);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mem");
	अगर (!res) अणु
		dev_err(dev, "missing \"mem\"\n");
		वापस -EINVAL;
	पूर्ण
	pcie->mem_res = res;

	ep->max_regions = CDNS_PCIE_MAX_OB;
	of_property_पढ़ो_u32(np, "cdns,max-outbound-regions", &ep->max_regions);

	ep->ob_addr = devm_kसुस्मृति(dev,
				   ep->max_regions, माप(*ep->ob_addr),
				   GFP_KERNEL);
	अगर (!ep->ob_addr)
		वापस -ENOMEM;

	/* Disable all but function 0 (anyway BIT(0) is hardwired to 1). */
	cdns_pcie_ग_लिखोl(pcie, CDNS_PCIE_LM_EP_FUNC_CFG, BIT(0));

	epc = devm_pci_epc_create(dev, &cdns_pcie_epc_ops);
	अगर (IS_ERR(epc)) अणु
		dev_err(dev, "failed to create epc device\n");
		वापस PTR_ERR(epc);
	पूर्ण

	epc_set_drvdata(epc, ep);

	अगर (of_property_पढ़ो_u8(np, "max-functions", &epc->max_functions) < 0)
		epc->max_functions = 1;

	ep->epf = devm_kसुस्मृति(dev, epc->max_functions, माप(*ep->epf),
			       GFP_KERNEL);
	अगर (!ep->epf)
		वापस -ENOMEM;

	ret = pci_epc_mem_init(epc, pcie->mem_res->start,
			       resource_size(pcie->mem_res), PAGE_SIZE);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize the memory space\n");
		वापस ret;
	पूर्ण

	ep->irq_cpu_addr = pci_epc_mem_alloc_addr(epc, &ep->irq_phys_addr,
						  SZ_128K);
	अगर (!ep->irq_cpu_addr) अणु
		dev_err(dev, "failed to reserve memory space for MSI\n");
		ret = -ENOMEM;
		जाओ मुक्त_epc_mem;
	पूर्ण
	ep->irq_pci_addr = CDNS_PCIE_EP_IRQ_PCI_ADDR_NONE;
	/* Reserve region 0 क्रम IRQs */
	set_bit(0, &ep->ob_region_map);
	spin_lock_init(&ep->lock);

	वापस 0;

 मुक्त_epc_mem:
	pci_epc_mem_निकास(epc);

	वापस ret;
पूर्ण
