<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * PCI Endpoपूर्णांक *Controller* (EPC) header file
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __LINUX_PCI_EPC_H
#घोषणा __LINUX_PCI_EPC_H

#समावेश <linux/pci-epf.h>

काष्ठा pci_epc;

क्रमागत pci_epc_पूर्णांकerface_type अणु
	UNKNOWN_INTERFACE = -1,
	PRIMARY_INTERFACE,
	SECONDARY_INTERFACE,
पूर्ण;

क्रमागत pci_epc_irq_type अणु
	PCI_EPC_IRQ_UNKNOWN,
	PCI_EPC_IRQ_LEGACY,
	PCI_EPC_IRQ_MSI,
	PCI_EPC_IRQ_MSIX,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *
pci_epc_पूर्णांकerface_string(क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	चयन (type) अणु
	हाल PRIMARY_INTERFACE:
		वापस "primary";
	हाल SECONDARY_INTERFACE:
		वापस "secondary";
	शेष:
		वापस "UNKNOWN interface";
	पूर्ण
पूर्ण

/**
 * काष्ठा pci_epc_ops - set of function poपूर्णांकers क्रम perक्रमming EPC operations
 * @ग_लिखो_header: ops to populate configuration space header
 * @set_bar: ops to configure the BAR
 * @clear_bar: ops to reset the BAR
 * @map_addr: ops to map CPU address to PCI address
 * @unmap_addr: ops to unmap CPU address and PCI address
 * @set_msi: ops to set the requested number of MSI पूर्णांकerrupts in the MSI
 *	     capability रेजिस्टर
 * @get_msi: ops to get the number of MSI पूर्णांकerrupts allocated by the RC from
 *	     the MSI capability रेजिस्टर
 * @set_msix: ops to set the requested number of MSI-X पूर्णांकerrupts in the
 *	     MSI-X capability रेजिस्टर
 * @get_msix: ops to get the number of MSI-X पूर्णांकerrupts allocated by the RC
 *	     from the MSI-X capability रेजिस्टर
 * @उठाओ_irq: ops to उठाओ a legacy, MSI or MSI-X पूर्णांकerrupt
 * @map_msi_irq: ops to map physical address to MSI address and वापस MSI data
 * @start: ops to start the PCI link
 * @stop: ops to stop the PCI link
 * @owner: the module owner containing the ops
 */
काष्ठा pci_epc_ops अणु
	पूर्णांक	(*ग_लिखो_header)(काष्ठा pci_epc *epc, u8 func_no,
				काष्ठा pci_epf_header *hdr);
	पूर्णांक	(*set_bar)(काष्ठा pci_epc *epc, u8 func_no,
			   काष्ठा pci_epf_bar *epf_bar);
	व्योम	(*clear_bar)(काष्ठा pci_epc *epc, u8 func_no,
			     काष्ठा pci_epf_bar *epf_bar);
	पूर्णांक	(*map_addr)(काष्ठा pci_epc *epc, u8 func_no,
			    phys_addr_t addr, u64 pci_addr, माप_प्रकार size);
	व्योम	(*unmap_addr)(काष्ठा pci_epc *epc, u8 func_no,
			      phys_addr_t addr);
	पूर्णांक	(*set_msi)(काष्ठा pci_epc *epc, u8 func_no, u8 पूर्णांकerrupts);
	पूर्णांक	(*get_msi)(काष्ठा pci_epc *epc, u8 func_no);
	पूर्णांक	(*set_msix)(काष्ठा pci_epc *epc, u8 func_no, u16 पूर्णांकerrupts,
			    क्रमागत pci_barno, u32 offset);
	पूर्णांक	(*get_msix)(काष्ठा pci_epc *epc, u8 func_no);
	पूर्णांक	(*उठाओ_irq)(काष्ठा pci_epc *epc, u8 func_no,
			     क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num);
	पूर्णांक	(*map_msi_irq)(काष्ठा pci_epc *epc, u8 func_no,
			       phys_addr_t phys_addr, u8 पूर्णांकerrupt_num,
			       u32 entry_size, u32 *msi_data,
			       u32 *msi_addr_offset);
	पूर्णांक	(*start)(काष्ठा pci_epc *epc);
	व्योम	(*stop)(काष्ठा pci_epc *epc);
	स्थिर काष्ठा pci_epc_features* (*get_features)(काष्ठा pci_epc *epc,
						       u8 func_no);
	काष्ठा module *owner;
पूर्ण;

/**
 * काष्ठा pci_epc_mem_winकरोw - address winकरोw of the endpoपूर्णांक controller
 * @phys_base: physical base address of the PCI address winकरोw
 * @size: the size of the PCI address winकरोw
 * @page_size: size of each page
 */
काष्ठा pci_epc_mem_winकरोw अणु
	phys_addr_t	phys_base;
	माप_प्रकार		size;
	माप_प्रकार		page_size;
पूर्ण;

/**
 * काष्ठा pci_epc_mem - address space of the endpoपूर्णांक controller
 * @winकरोw: address winकरोw of the endpoपूर्णांक controller
 * @biपंचांगap: biपंचांगap to manage the PCI address space
 * @pages: number of bits representing the address region
 * @lock: mutex to protect biपंचांगap
 */
काष्ठा pci_epc_mem अणु
	काष्ठा pci_epc_mem_winकरोw winकरोw;
	अचिन्हित दीर्घ	*biपंचांगap;
	पूर्णांक		pages;
	/* mutex to protect against concurrent access क्रम memory allocation*/
	काष्ठा mutex	lock;
पूर्ण;

/**
 * काष्ठा pci_epc - represents the PCI EPC device
 * @dev: PCI EPC device
 * @pci_epf: list of endpoपूर्णांक functions present in this EPC device
 * @ops: function poपूर्णांकers क्रम perक्रमming endpoपूर्णांक operations
 * @winकरोws: array of address space of the endpoपूर्णांक controller
 * @mem: first winकरोw of the endpoपूर्णांक controller, which corresponds to
 *       शेष address space of the endpoपूर्णांक controller supporting
 *       single winकरोw.
 * @num_winकरोws: number of winकरोws supported by device
 * @max_functions: max number of functions that can be configured in this EPC
 * @group: configfs group representing the PCI EPC device
 * @lock: mutex to protect pci_epc ops
 * @function_num_map: biपंचांगap to manage physical function number
 * @notअगरier: used to notअगरy EPF of any EPC events (like linkup)
 */
काष्ठा pci_epc अणु
	काष्ठा device			dev;
	काष्ठा list_head		pci_epf;
	स्थिर काष्ठा pci_epc_ops	*ops;
	काष्ठा pci_epc_mem		**winकरोws;
	काष्ठा pci_epc_mem		*mem;
	अचिन्हित पूर्णांक			num_winकरोws;
	u8				max_functions;
	काष्ठा config_group		*group;
	/* mutex to protect against concurrent access of EP controller */
	काष्ठा mutex			lock;
	अचिन्हित दीर्घ			function_num_map;
	काष्ठा atomic_notअगरier_head	notअगरier;
पूर्ण;

/**
 * काष्ठा pci_epc_features - features supported by a EPC device per function
 * @linkup_notअगरier: indicate अगर the EPC device can notअगरy EPF driver on link up
 * @msi_capable: indicate अगर the endpoपूर्णांक function has MSI capability
 * @msix_capable: indicate अगर the endpoपूर्णांक function has MSI-X capability
 * @reserved_bar: biपंचांगap to indicate reserved BAR unavailable to function driver
 * @bar_fixed_64bit: biपंचांगap to indicate fixed 64bit BARs
 * @bar_fixed_size: Array specअगरying the size supported by each BAR
 * @align: alignment size required क्रम BAR buffer allocation
 */
काष्ठा pci_epc_features अणु
	अचिन्हित पूर्णांक	linkup_notअगरier : 1;
	अचिन्हित पूर्णांक	core_init_notअगरier : 1;
	अचिन्हित पूर्णांक	msi_capable : 1;
	अचिन्हित पूर्णांक	msix_capable : 1;
	u8	reserved_bar;
	u8	bar_fixed_64bit;
	u64	bar_fixed_size[PCI_STD_NUM_BARS];
	माप_प्रकार	align;
पूर्ण;

#घोषणा to_pci_epc(device) container_of((device), काष्ठा pci_epc, dev)

#घोषणा pci_epc_create(dev, ops)    \
		__pci_epc_create((dev), (ops), THIS_MODULE)
#घोषणा devm_pci_epc_create(dev, ops)    \
		__devm_pci_epc_create((dev), (ops), THIS_MODULE)

अटल अंतरभूत व्योम epc_set_drvdata(काष्ठा pci_epc *epc, व्योम *data)
अणु
	dev_set_drvdata(&epc->dev, data);
पूर्ण

अटल अंतरभूत व्योम *epc_get_drvdata(काष्ठा pci_epc *epc)
अणु
	वापस dev_get_drvdata(&epc->dev);
पूर्ण

अटल अंतरभूत पूर्णांक
pci_epc_रेजिस्टर_notअगरier(काष्ठा pci_epc *epc, काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&epc->notअगरier, nb);
पूर्ण

काष्ठा pci_epc *
__devm_pci_epc_create(काष्ठा device *dev, स्थिर काष्ठा pci_epc_ops *ops,
		      काष्ठा module *owner);
काष्ठा pci_epc *
__pci_epc_create(काष्ठा device *dev, स्थिर काष्ठा pci_epc_ops *ops,
		 काष्ठा module *owner);
व्योम devm_pci_epc_destroy(काष्ठा device *dev, काष्ठा pci_epc *epc);
व्योम pci_epc_destroy(काष्ठा pci_epc *epc);
पूर्णांक pci_epc_add_epf(काष्ठा pci_epc *epc, काष्ठा pci_epf *epf,
		    क्रमागत pci_epc_पूर्णांकerface_type type);
व्योम pci_epc_linkup(काष्ठा pci_epc *epc);
व्योम pci_epc_init_notअगरy(काष्ठा pci_epc *epc);
व्योम pci_epc_हटाओ_epf(काष्ठा pci_epc *epc, काष्ठा pci_epf *epf,
			क्रमागत pci_epc_पूर्णांकerface_type type);
पूर्णांक pci_epc_ग_लिखो_header(काष्ठा pci_epc *epc, u8 func_no,
			 काष्ठा pci_epf_header *hdr);
पूर्णांक pci_epc_set_bar(काष्ठा pci_epc *epc, u8 func_no,
		    काष्ठा pci_epf_bar *epf_bar);
व्योम pci_epc_clear_bar(काष्ठा pci_epc *epc, u8 func_no,
		       काष्ठा pci_epf_bar *epf_bar);
पूर्णांक pci_epc_map_addr(काष्ठा pci_epc *epc, u8 func_no,
		     phys_addr_t phys_addr,
		     u64 pci_addr, माप_प्रकार size);
व्योम pci_epc_unmap_addr(काष्ठा pci_epc *epc, u8 func_no,
			phys_addr_t phys_addr);
पूर्णांक pci_epc_set_msi(काष्ठा pci_epc *epc, u8 func_no, u8 पूर्णांकerrupts);
पूर्णांक pci_epc_get_msi(काष्ठा pci_epc *epc, u8 func_no);
पूर्णांक pci_epc_set_msix(काष्ठा pci_epc *epc, u8 func_no, u16 पूर्णांकerrupts,
		     क्रमागत pci_barno, u32 offset);
पूर्णांक pci_epc_get_msix(काष्ठा pci_epc *epc, u8 func_no);
पूर्णांक pci_epc_map_msi_irq(काष्ठा pci_epc *epc, u8 func_no,
			phys_addr_t phys_addr, u8 पूर्णांकerrupt_num,
			u32 entry_size, u32 *msi_data, u32 *msi_addr_offset);
पूर्णांक pci_epc_उठाओ_irq(काष्ठा pci_epc *epc, u8 func_no,
		      क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num);
पूर्णांक pci_epc_start(काष्ठा pci_epc *epc);
व्योम pci_epc_stop(काष्ठा pci_epc *epc);
स्थिर काष्ठा pci_epc_features *pci_epc_get_features(काष्ठा pci_epc *epc,
						    u8 func_no);
क्रमागत pci_barno
pci_epc_get_first_मुक्त_bar(स्थिर काष्ठा pci_epc_features *epc_features);
क्रमागत pci_barno pci_epc_get_next_मुक्त_bar(स्थिर काष्ठा pci_epc_features
					 *epc_features, क्रमागत pci_barno bar);
काष्ठा pci_epc *pci_epc_get(स्थिर अक्षर *epc_name);
व्योम pci_epc_put(काष्ठा pci_epc *epc);

पूर्णांक pci_epc_mem_init(काष्ठा pci_epc *epc, phys_addr_t base,
		     माप_प्रकार size, माप_प्रकार page_size);
पूर्णांक pci_epc_multi_mem_init(काष्ठा pci_epc *epc,
			   काष्ठा pci_epc_mem_winकरोw *winकरोw,
			   अचिन्हित पूर्णांक num_winकरोws);
व्योम pci_epc_mem_निकास(काष्ठा pci_epc *epc);
व्योम __iomem *pci_epc_mem_alloc_addr(काष्ठा pci_epc *epc,
				     phys_addr_t *phys_addr, माप_प्रकार size);
व्योम pci_epc_mem_मुक्त_addr(काष्ठा pci_epc *epc, phys_addr_t phys_addr,
			   व्योम __iomem *virt_addr, माप_प्रकार size);
#पूर्ण_अगर /* __LINUX_PCI_EPC_H */
