<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Synopsys DesignWare PCIe Endpoपूर्णांक controller driver
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "pcie-designware.h"
#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>

#समावेश "../../pci.h"

व्योम dw_pcie_ep_linkup(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा pci_epc *epc = ep->epc;

	pci_epc_linkup(epc);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ep_linkup);

व्योम dw_pcie_ep_init_notअगरy(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा pci_epc *epc = ep->epc;

	pci_epc_init_notअगरy(epc);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ep_init_notअगरy);

काष्ठा dw_pcie_ep_func *
dw_pcie_ep_get_func_from_ep(काष्ठा dw_pcie_ep *ep, u8 func_no)
अणु
	काष्ठा dw_pcie_ep_func *ep_func;

	list_क्रम_each_entry(ep_func, &ep->func_list, list) अणु
		अगर (ep_func->func_no == func_no)
			वापस ep_func;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक dw_pcie_ep_func_select(काष्ठा dw_pcie_ep *ep, u8 func_no)
अणु
	अचिन्हित पूर्णांक func_offset = 0;

	अगर (ep->ops->func_conf_select)
		func_offset = ep->ops->func_conf_select(ep, func_no);

	वापस func_offset;
पूर्ण

अटल व्योम __dw_pcie_ep_reset_bar(काष्ठा dw_pcie *pci, u8 func_no,
				   क्रमागत pci_barno bar, पूर्णांक flags)
अणु
	u32 reg;
	अचिन्हित पूर्णांक func_offset = 0;
	काष्ठा dw_pcie_ep *ep = &pci->ep;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = func_offset + PCI_BASE_ADDRESS_0 + (4 * bar);
	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_ग_लिखोl_dbi2(pci, reg, 0x0);
	dw_pcie_ग_लिखोl_dbi(pci, reg, 0x0);
	अगर (flags & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
		dw_pcie_ग_लिखोl_dbi2(pci, reg + 4, 0x0);
		dw_pcie_ग_लिखोl_dbi(pci, reg + 4, 0x0);
	पूर्ण
	dw_pcie_dbi_ro_wr_dis(pci);
पूर्ण

व्योम dw_pcie_ep_reset_bar(काष्ठा dw_pcie *pci, क्रमागत pci_barno bar)
अणु
	u8 func_no, funcs;

	funcs = pci->ep.epc->max_functions;

	क्रम (func_no = 0; func_no < funcs; func_no++)
		__dw_pcie_ep_reset_bar(pci, func_no, bar, 0);
पूर्ण

अटल u8 __dw_pcie_ep_find_next_cap(काष्ठा dw_pcie_ep *ep, u8 func_no,
		u8 cap_ptr, u8 cap)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	अचिन्हित पूर्णांक func_offset = 0;
	u8 cap_id, next_cap_ptr;
	u16 reg;

	अगर (!cap_ptr)
		वापस 0;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = dw_pcie_पढ़ोw_dbi(pci, func_offset + cap_ptr);
	cap_id = (reg & 0x00ff);

	अगर (cap_id > PCI_CAP_ID_MAX)
		वापस 0;

	अगर (cap_id == cap)
		वापस cap_ptr;

	next_cap_ptr = (reg & 0xff00) >> 8;
	वापस __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptr, cap);
पूर्ण

अटल u8 dw_pcie_ep_find_capability(काष्ठा dw_pcie_ep *ep, u8 func_no, u8 cap)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	अचिन्हित पूर्णांक func_offset = 0;
	u8 next_cap_ptr;
	u16 reg;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = dw_pcie_पढ़ोw_dbi(pci, func_offset + PCI_CAPABILITY_LIST);
	next_cap_ptr = (reg & 0x00ff);

	वापस __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptr, cap);
पूर्ण

अटल पूर्णांक dw_pcie_ep_ग_लिखो_header(काष्ठा pci_epc *epc, u8 func_no,
				   काष्ठा pci_epf_header *hdr)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	अचिन्हित पूर्णांक func_offset = 0;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_ग_लिखोw_dbi(pci, func_offset + PCI_VENDOR_ID, hdr->venकरोrid);
	dw_pcie_ग_लिखोw_dbi(pci, func_offset + PCI_DEVICE_ID, hdr->deviceid);
	dw_pcie_ग_लिखोb_dbi(pci, func_offset + PCI_REVISION_ID, hdr->revid);
	dw_pcie_ग_लिखोb_dbi(pci, func_offset + PCI_CLASS_PROG, hdr->progअगर_code);
	dw_pcie_ग_लिखोw_dbi(pci, func_offset + PCI_CLASS_DEVICE,
			   hdr->subclass_code | hdr->baseclass_code << 8);
	dw_pcie_ग_लिखोb_dbi(pci, func_offset + PCI_CACHE_LINE_SIZE,
			   hdr->cache_line_size);
	dw_pcie_ग_लिखोw_dbi(pci, func_offset + PCI_SUBSYSTEM_VENDOR_ID,
			   hdr->subsys_venकरोr_id);
	dw_pcie_ग_लिखोw_dbi(pci, func_offset + PCI_SUBSYSTEM_ID, hdr->subsys_id);
	dw_pcie_ग_लिखोb_dbi(pci, func_offset + PCI_INTERRUPT_PIN,
			   hdr->पूर्णांकerrupt_pin);
	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_ep_inbound_atu(काष्ठा dw_pcie_ep *ep, u8 func_no,
				  क्रमागत pci_barno bar, dma_addr_t cpu_addr,
				  क्रमागत dw_pcie_as_type as_type)
अणु
	पूर्णांक ret;
	u32 मुक्त_win;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	मुक्त_win = find_first_zero_bit(ep->ib_winकरोw_map, pci->num_ib_winकरोws);
	अगर (मुक्त_win >= pci->num_ib_winकरोws) अणु
		dev_err(pci->dev, "No free inbound window\n");
		वापस -EINVAL;
	पूर्ण

	ret = dw_pcie_prog_inbound_atu(pci, func_no, मुक्त_win, bar, cpu_addr,
				       as_type);
	अगर (ret < 0) अणु
		dev_err(pci->dev, "Failed to program IB window\n");
		वापस ret;
	पूर्ण

	ep->bar_to_atu[bar] = मुक्त_win;
	set_bit(मुक्त_win, ep->ib_winकरोw_map);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_ep_outbound_atu(काष्ठा dw_pcie_ep *ep, u8 func_no,
				   phys_addr_t phys_addr,
				   u64 pci_addr, माप_प्रकार size)
अणु
	u32 मुक्त_win;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	मुक्त_win = find_first_zero_bit(ep->ob_winकरोw_map, pci->num_ob_winकरोws);
	अगर (मुक्त_win >= pci->num_ob_winकरोws) अणु
		dev_err(pci->dev, "No free outbound window\n");
		वापस -EINVAL;
	पूर्ण

	dw_pcie_prog_ep_outbound_atu(pci, func_no, मुक्त_win, PCIE_ATU_TYPE_MEM,
				     phys_addr, pci_addr, size);

	set_bit(मुक्त_win, ep->ob_winकरोw_map);
	ep->outbound_addr[मुक्त_win] = phys_addr;

	वापस 0;
पूर्ण

अटल व्योम dw_pcie_ep_clear_bar(काष्ठा pci_epc *epc, u8 func_no,
				 काष्ठा pci_epf_bar *epf_bar)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	क्रमागत pci_barno bar = epf_bar->barno;
	u32 atu_index = ep->bar_to_atu[bar];

	__dw_pcie_ep_reset_bar(pci, func_no, bar, epf_bar->flags);

	dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_INBOUND);
	clear_bit(atu_index, ep->ib_winकरोw_map);
	ep->epf_bar[bar] = शून्य;
पूर्ण

अटल पूर्णांक dw_pcie_ep_set_bar(काष्ठा pci_epc *epc, u8 func_no,
			      काष्ठा pci_epf_bar *epf_bar)
अणु
	पूर्णांक ret;
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	क्रमागत pci_barno bar = epf_bar->barno;
	माप_प्रकार size = epf_bar->size;
	पूर्णांक flags = epf_bar->flags;
	क्रमागत dw_pcie_as_type as_type;
	u32 reg;
	अचिन्हित पूर्णांक func_offset = 0;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = PCI_BASE_ADDRESS_0 + (4 * bar) + func_offset;

	अगर (!(flags & PCI_BASE_ADDRESS_SPACE))
		as_type = DW_PCIE_AS_MEM;
	अन्यथा
		as_type = DW_PCIE_AS_IO;

	ret = dw_pcie_ep_inbound_atu(ep, func_no, bar,
				     epf_bar->phys_addr, as_type);
	अगर (ret)
		वापस ret;

	dw_pcie_dbi_ro_wr_en(pci);

	dw_pcie_ग_लिखोl_dbi2(pci, reg, lower_32_bits(size - 1));
	dw_pcie_ग_लिखोl_dbi(pci, reg, flags);

	अगर (flags & PCI_BASE_ADDRESS_MEM_TYPE_64) अणु
		dw_pcie_ग_लिखोl_dbi2(pci, reg + 4, upper_32_bits(size - 1));
		dw_pcie_ग_लिखोl_dbi(pci, reg + 4, 0);
	पूर्ण

	ep->epf_bar[bar] = epf_bar;
	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_find_index(काष्ठा dw_pcie_ep *ep, phys_addr_t addr,
			      u32 *atu_index)
अणु
	u32 index;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	क्रम (index = 0; index < pci->num_ob_winकरोws; index++) अणु
		अगर (ep->outbound_addr[index] != addr)
			जारी;
		*atu_index = index;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम dw_pcie_ep_unmap_addr(काष्ठा pci_epc *epc, u8 func_no,
				  phys_addr_t addr)
अणु
	पूर्णांक ret;
	u32 atu_index;
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	ret = dw_pcie_find_index(ep, addr, &atu_index);
	अगर (ret < 0)
		वापस;

	dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_OUTBOUND);
	clear_bit(atu_index, ep->ob_winकरोw_map);
पूर्ण

अटल पूर्णांक dw_pcie_ep_map_addr(काष्ठा pci_epc *epc, u8 func_no,
			       phys_addr_t addr,
			       u64 pci_addr, माप_प्रकार size)
अणु
	पूर्णांक ret;
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	ret = dw_pcie_ep_outbound_atu(ep, func_no, addr, pci_addr, size);
	अगर (ret) अणु
		dev_err(pci->dev, "Failed to enable address\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_ep_get_msi(काष्ठा pci_epc *epc, u8 func_no)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	u32 val, reg;
	अचिन्हित पूर्णांक func_offset = 0;
	काष्ठा dw_pcie_ep_func *ep_func;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msi_cap)
		वापस -EINVAL;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = ep_func->msi_cap + func_offset + PCI_MSI_FLAGS;
	val = dw_pcie_पढ़ोw_dbi(pci, reg);
	अगर (!(val & PCI_MSI_FLAGS_ENABLE))
		वापस -EINVAL;

	val = (val & PCI_MSI_FLAGS_QSIZE) >> 4;

	वापस val;
पूर्ण

अटल पूर्णांक dw_pcie_ep_set_msi(काष्ठा pci_epc *epc, u8 func_no, u8 पूर्णांकerrupts)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	u32 val, reg;
	अचिन्हित पूर्णांक func_offset = 0;
	काष्ठा dw_pcie_ep_func *ep_func;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msi_cap)
		वापस -EINVAL;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = ep_func->msi_cap + func_offset + PCI_MSI_FLAGS;
	val = dw_pcie_पढ़ोw_dbi(pci, reg);
	val &= ~PCI_MSI_FLAGS_QMASK;
	val |= (पूर्णांकerrupts << 1) & PCI_MSI_FLAGS_QMASK;
	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_ग_लिखोw_dbi(pci, reg, val);
	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_ep_get_msix(काष्ठा pci_epc *epc, u8 func_no)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	u32 val, reg;
	अचिन्हित पूर्णांक func_offset = 0;
	काष्ठा dw_pcie_ep_func *ep_func;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msix_cap)
		वापस -EINVAL;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = ep_func->msix_cap + func_offset + PCI_MSIX_FLAGS;
	val = dw_pcie_पढ़ोw_dbi(pci, reg);
	अगर (!(val & PCI_MSIX_FLAGS_ENABLE))
		वापस -EINVAL;

	val &= PCI_MSIX_FLAGS_QSIZE;

	वापस val;
पूर्ण

अटल पूर्णांक dw_pcie_ep_set_msix(काष्ठा pci_epc *epc, u8 func_no, u16 पूर्णांकerrupts,
			       क्रमागत pci_barno bir, u32 offset)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	u32 val, reg;
	अचिन्हित पूर्णांक func_offset = 0;
	काष्ठा dw_pcie_ep_func *ep_func;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msix_cap)
		वापस -EINVAL;

	dw_pcie_dbi_ro_wr_en(pci);

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = ep_func->msix_cap + func_offset + PCI_MSIX_FLAGS;
	val = dw_pcie_पढ़ोw_dbi(pci, reg);
	val &= ~PCI_MSIX_FLAGS_QSIZE;
	val |= पूर्णांकerrupts;
	dw_pcie_ग_लिखोw_dbi(pci, reg, val);

	reg = ep_func->msix_cap + func_offset + PCI_MSIX_TABLE;
	val = offset | bir;
	dw_pcie_ग_लिखोl_dbi(pci, reg, val);

	reg = ep_func->msix_cap + func_offset + PCI_MSIX_PBA;
	val = (offset + (पूर्णांकerrupts * PCI_MSIX_ENTRY_SIZE)) | bir;
	dw_pcie_ग_लिखोl_dbi(pci, reg, val);

	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_pcie_ep_उठाओ_irq(काष्ठा pci_epc *epc, u8 func_no,
				क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);

	अगर (!ep->ops->उठाओ_irq)
		वापस -EINVAL;

	वापस ep->ops->उठाओ_irq(ep, func_no, type, पूर्णांकerrupt_num);
पूर्ण

अटल व्योम dw_pcie_ep_stop(काष्ठा pci_epc *epc)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	अगर (pci->ops && pci->ops->stop_link)
		pci->ops->stop_link(pci);
पूर्ण

अटल पूर्णांक dw_pcie_ep_start(काष्ठा pci_epc *epc)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	अगर (!pci->ops || !pci->ops->start_link)
		वापस -EINVAL;

	वापस pci->ops->start_link(pci);
पूर्ण

अटल स्थिर काष्ठा pci_epc_features*
dw_pcie_ep_get_features(काष्ठा pci_epc *epc, u8 func_no)
अणु
	काष्ठा dw_pcie_ep *ep = epc_get_drvdata(epc);

	अगर (!ep->ops->get_features)
		वापस शून्य;

	वापस ep->ops->get_features(ep);
पूर्ण

अटल स्थिर काष्ठा pci_epc_ops epc_ops = अणु
	.ग_लिखो_header		= dw_pcie_ep_ग_लिखो_header,
	.set_bar		= dw_pcie_ep_set_bar,
	.clear_bar		= dw_pcie_ep_clear_bar,
	.map_addr		= dw_pcie_ep_map_addr,
	.unmap_addr		= dw_pcie_ep_unmap_addr,
	.set_msi		= dw_pcie_ep_set_msi,
	.get_msi		= dw_pcie_ep_get_msi,
	.set_msix		= dw_pcie_ep_set_msix,
	.get_msix		= dw_pcie_ep_get_msix,
	.उठाओ_irq		= dw_pcie_ep_उठाओ_irq,
	.start			= dw_pcie_ep_start,
	.stop			= dw_pcie_ep_stop,
	.get_features		= dw_pcie_ep_get_features,
पूर्ण;

पूर्णांक dw_pcie_ep_उठाओ_legacy_irq(काष्ठा dw_pcie_ep *ep, u8 func_no)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा device *dev = pci->dev;

	dev_err(dev, "EP cannot trigger legacy IRQs\n");

	वापस -EINVAL;
पूर्ण

पूर्णांक dw_pcie_ep_उठाओ_msi_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
			     u8 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा dw_pcie_ep_func *ep_func;
	काष्ठा pci_epc *epc = ep->epc;
	अचिन्हित पूर्णांक aligned_offset;
	अचिन्हित पूर्णांक func_offset = 0;
	u16 msg_ctrl, msg_data;
	u32 msg_addr_lower, msg_addr_upper, reg;
	u64 msg_addr;
	bool has_upper;
	पूर्णांक ret;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msi_cap)
		वापस -EINVAL;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	/* Raise MSI per the PCI Local Bus Specअगरication Revision 3.0, 6.8.1. */
	reg = ep_func->msi_cap + func_offset + PCI_MSI_FLAGS;
	msg_ctrl = dw_pcie_पढ़ोw_dbi(pci, reg);
	has_upper = !!(msg_ctrl & PCI_MSI_FLAGS_64BIT);
	reg = ep_func->msi_cap + func_offset + PCI_MSI_ADDRESS_LO;
	msg_addr_lower = dw_pcie_पढ़ोl_dbi(pci, reg);
	अगर (has_upper) अणु
		reg = ep_func->msi_cap + func_offset + PCI_MSI_ADDRESS_HI;
		msg_addr_upper = dw_pcie_पढ़ोl_dbi(pci, reg);
		reg = ep_func->msi_cap + func_offset + PCI_MSI_DATA_64;
		msg_data = dw_pcie_पढ़ोw_dbi(pci, reg);
	पूर्ण अन्यथा अणु
		msg_addr_upper = 0;
		reg = ep_func->msi_cap + func_offset + PCI_MSI_DATA_32;
		msg_data = dw_pcie_पढ़ोw_dbi(pci, reg);
	पूर्ण
	aligned_offset = msg_addr_lower & (epc->mem->winकरोw.page_size - 1);
	msg_addr = ((u64)msg_addr_upper) << 32 |
			(msg_addr_lower & ~aligned_offset);
	ret = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phys, msg_addr,
				  epc->mem->winकरोw.page_size);
	अगर (ret)
		वापस ret;

	ग_लिखोl(msg_data | (पूर्णांकerrupt_num - 1), ep->msi_mem + aligned_offset);

	dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phys);

	वापस 0;
पूर्ण

पूर्णांक dw_pcie_ep_उठाओ_msix_irq_करोorbell(काष्ठा dw_pcie_ep *ep, u8 func_no,
				       u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा dw_pcie_ep_func *ep_func;
	u32 msg_data;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msix_cap)
		वापस -EINVAL;

	msg_data = (func_no << PCIE_MSIX_DOORBELL_PF_SHIFT) |
		   (पूर्णांकerrupt_num - 1);

	dw_pcie_ग_लिखोl_dbi(pci, PCIE_MSIX_DOORBELL, msg_data);

	वापस 0;
पूर्ण

पूर्णांक dw_pcie_ep_उठाओ_msix_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
			      u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा dw_pcie_ep_func *ep_func;
	काष्ठा pci_epf_msix_tbl *msix_tbl;
	काष्ठा pci_epc *epc = ep->epc;
	अचिन्हित पूर्णांक func_offset = 0;
	u32 reg, msg_data, vec_ctrl;
	अचिन्हित पूर्णांक aligned_offset;
	u32 tbl_offset;
	u64 msg_addr;
	पूर्णांक ret;
	u8 bir;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
	अगर (!ep_func || !ep_func->msix_cap)
		वापस -EINVAL;

	func_offset = dw_pcie_ep_func_select(ep, func_no);

	reg = ep_func->msix_cap + func_offset + PCI_MSIX_TABLE;
	tbl_offset = dw_pcie_पढ़ोl_dbi(pci, reg);
	bir = (tbl_offset & PCI_MSIX_TABLE_BIR);
	tbl_offset &= PCI_MSIX_TABLE_OFFSET;

	msix_tbl = ep->epf_bar[bir]->addr + tbl_offset;
	msg_addr = msix_tbl[(पूर्णांकerrupt_num - 1)].msg_addr;
	msg_data = msix_tbl[(पूर्णांकerrupt_num - 1)].msg_data;
	vec_ctrl = msix_tbl[(पूर्णांकerrupt_num - 1)].vector_ctrl;

	अगर (vec_ctrl & PCI_MSIX_ENTRY_CTRL_MASKBIT) अणु
		dev_dbg(pci->dev, "MSI-X entry ctrl set\n");
		वापस -EPERM;
	पूर्ण

	aligned_offset = msg_addr & (epc->mem->winकरोw.page_size - 1);
	ret = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phys,  msg_addr,
				  epc->mem->winकरोw.page_size);
	अगर (ret)
		वापस ret;

	ग_लिखोl(msg_data, ep->msi_mem + aligned_offset);

	dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phys);

	वापस 0;
पूर्ण

व्योम dw_pcie_ep_निकास(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा pci_epc *epc = ep->epc;

	pci_epc_mem_मुक्त_addr(epc, ep->msi_mem_phys, ep->msi_mem,
			      epc->mem->winकरोw.page_size);

	pci_epc_mem_निकास(epc);
पूर्ण

अटल अचिन्हित पूर्णांक dw_pcie_ep_find_ext_capability(काष्ठा dw_pcie *pci, पूर्णांक cap)
अणु
	u32 header;
	पूर्णांक pos = PCI_CFG_SPACE_SIZE;

	जबतक (pos) अणु
		header = dw_pcie_पढ़ोl_dbi(pci, pos);
		अगर (PCI_EXT_CAP_ID(header) == cap)
			वापस pos;

		pos = PCI_EXT_CAP_NEXT(header);
		अगर (!pos)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dw_pcie_ep_init_complete(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक nbars;
	u8 hdr_type;
	u32 reg;
	पूर्णांक i;

	hdr_type = dw_pcie_पढ़ोb_dbi(pci, PCI_HEADER_TYPE) &
		   PCI_HEADER_TYPE_MASK;
	अगर (hdr_type != PCI_HEADER_TYPE_NORMAL) अणु
		dev_err(pci->dev,
			"PCIe controller is not set to EP mode (hdr_type:0x%x)!\n",
			hdr_type);
		वापस -EIO;
	पूर्ण

	offset = dw_pcie_ep_find_ext_capability(pci, PCI_EXT_CAP_ID_REBAR);

	dw_pcie_dbi_ro_wr_en(pci);

	अगर (offset) अणु
		reg = dw_pcie_पढ़ोl_dbi(pci, offset + PCI_REBAR_CTRL);
		nbars = (reg & PCI_REBAR_CTRL_NBAR_MASK) >>
			PCI_REBAR_CTRL_NBAR_SHIFT;

		क्रम (i = 0; i < nbars; i++, offset += PCI_REBAR_CTRL)
			dw_pcie_ग_लिखोl_dbi(pci, offset + PCI_REBAR_CAP, 0x0);
	पूर्ण

	dw_pcie_setup(pci);
	dw_pcie_dbi_ro_wr_dis(pci);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ep_init_complete);

पूर्णांक dw_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	पूर्णांक ret;
	व्योम *addr;
	u8 func_no;
	काष्ठा resource *res;
	काष्ठा pci_epc *epc;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा device *dev = pci->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा pci_epc_features *epc_features;
	काष्ठा dw_pcie_ep_func *ep_func;

	INIT_LIST_HEAD(&ep->func_list);

	अगर (!pci->dbi_base) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
		pci->dbi_base = devm_pci_remap_cfg_resource(dev, res);
		अगर (IS_ERR(pci->dbi_base))
			वापस PTR_ERR(pci->dbi_base);
	पूर्ण

	अगर (!pci->dbi_base2) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dbi2");
		अगर (!res)
			pci->dbi_base2 = pci->dbi_base + SZ_4K;
		अन्यथा अणु
			pci->dbi_base2 = devm_pci_remap_cfg_resource(dev, res);
			अगर (IS_ERR(pci->dbi_base2))
				वापस PTR_ERR(pci->dbi_base2);
		पूर्ण
	पूर्ण

	dw_pcie_iatu_detect(pci);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "addr_space");
	अगर (!res)
		वापस -EINVAL;

	ep->phys_base = res->start;
	ep->addr_size = resource_size(res);

	ep->ib_winकरोw_map = devm_kसुस्मृति(dev,
					 BITS_TO_LONGS(pci->num_ib_winकरोws),
					 माप(दीर्घ),
					 GFP_KERNEL);
	अगर (!ep->ib_winकरोw_map)
		वापस -ENOMEM;

	ep->ob_winकरोw_map = devm_kसुस्मृति(dev,
					 BITS_TO_LONGS(pci->num_ob_winकरोws),
					 माप(दीर्घ),
					 GFP_KERNEL);
	अगर (!ep->ob_winकरोw_map)
		वापस -ENOMEM;

	addr = devm_kसुस्मृति(dev, pci->num_ob_winकरोws, माप(phys_addr_t),
			    GFP_KERNEL);
	अगर (!addr)
		वापस -ENOMEM;
	ep->outbound_addr = addr;

	अगर (pci->link_gen < 1)
		pci->link_gen = of_pci_get_max_link_speed(np);

	epc = devm_pci_epc_create(dev, &epc_ops);
	अगर (IS_ERR(epc)) अणु
		dev_err(dev, "Failed to create epc device\n");
		वापस PTR_ERR(epc);
	पूर्ण

	ep->epc = epc;
	epc_set_drvdata(epc, ep);

	ret = of_property_पढ़ो_u8(np, "max-functions", &epc->max_functions);
	अगर (ret < 0)
		epc->max_functions = 1;

	क्रम (func_no = 0; func_no < epc->max_functions; func_no++) अणु
		ep_func = devm_kzalloc(dev, माप(*ep_func), GFP_KERNEL);
		अगर (!ep_func)
			वापस -ENOMEM;

		ep_func->func_no = func_no;
		ep_func->msi_cap = dw_pcie_ep_find_capability(ep, func_no,
							      PCI_CAP_ID_MSI);
		ep_func->msix_cap = dw_pcie_ep_find_capability(ep, func_no,
							       PCI_CAP_ID_MSIX);

		list_add_tail(&ep_func->list, &ep->func_list);
	पूर्ण

	अगर (ep->ops->ep_init)
		ep->ops->ep_init(ep);

	ret = pci_epc_mem_init(epc, ep->phys_base, ep->addr_size,
			       ep->page_size);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to initialize address space\n");
		वापस ret;
	पूर्ण

	ep->msi_mem = pci_epc_mem_alloc_addr(epc, &ep->msi_mem_phys,
					     epc->mem->winकरोw.page_size);
	अगर (!ep->msi_mem) अणु
		dev_err(dev, "Failed to reserve memory for MSI/MSI-X\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (ep->ops->get_features) अणु
		epc_features = ep->ops->get_features(ep);
		अगर (epc_features->core_init_notअगरier)
			वापस 0;
	पूर्ण

	वापस dw_pcie_ep_init_complete(ep);
पूर्ण
EXPORT_SYMBOL_GPL(dw_pcie_ep_init);
