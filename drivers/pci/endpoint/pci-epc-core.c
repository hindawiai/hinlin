<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Endpoपूर्णांक *Controller* (EPC) library
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/pci-ep-cfs.h>

अटल काष्ठा class *pci_epc_class;

अटल व्योम devm_pci_epc_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा pci_epc *epc = *(काष्ठा pci_epc **)res;

	pci_epc_destroy(epc);
पूर्ण

अटल पूर्णांक devm_pci_epc_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	काष्ठा pci_epc **epc = res;

	वापस *epc == match_data;
पूर्ण

/**
 * pci_epc_put() - release the PCI endpoपूर्णांक controller
 * @epc: epc वापसed by pci_epc_get()
 *
 * release the refcount the caller obtained by invoking pci_epc_get()
 */
व्योम pci_epc_put(काष्ठा pci_epc *epc)
अणु
	अगर (!epc || IS_ERR(epc))
		वापस;

	module_put(epc->ops->owner);
	put_device(&epc->dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_put);

/**
 * pci_epc_get() - get the PCI endpoपूर्णांक controller
 * @epc_name: device name of the endpoपूर्णांक controller
 *
 * Invoke to get काष्ठा pci_epc * corresponding to the device name of the
 * endpoपूर्णांक controller
 */
काष्ठा pci_epc *pci_epc_get(स्थिर अक्षर *epc_name)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा pci_epc *epc;
	काष्ठा device *dev;
	काष्ठा class_dev_iter iter;

	class_dev_iter_init(&iter, pci_epc_class, शून्य, शून्य);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		अगर (म_भेद(epc_name, dev_name(dev)))
			जारी;

		epc = to_pci_epc(dev);
		अगर (!try_module_get(epc->ops->owner)) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		class_dev_iter_निकास(&iter);
		get_device(&epc->dev);
		वापस epc;
	पूर्ण

err:
	class_dev_iter_निकास(&iter);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get);

/**
 * pci_epc_get_first_मुक्त_bar() - helper to get first unreserved BAR
 * @epc_features: pci_epc_features काष्ठाure that holds the reserved bar biपंचांगap
 *
 * Invoke to get the first unreserved BAR that can be used by the endpoपूर्णांक
 * function. For any incorrect value in reserved_bar वापस '0'.
 */
क्रमागत pci_barno
pci_epc_get_first_मुक्त_bar(स्थिर काष्ठा pci_epc_features *epc_features)
अणु
	वापस pci_epc_get_next_मुक्त_bar(epc_features, BAR_0);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get_first_मुक्त_bar);

/**
 * pci_epc_get_next_मुक्त_bar() - helper to get unreserved BAR starting from @bar
 * @epc_features: pci_epc_features काष्ठाure that holds the reserved bar biपंचांगap
 * @bar: the starting BAR number from where unreserved BAR should be searched
 *
 * Invoke to get the next unreserved BAR starting from @bar that can be used
 * क्रम endpoपूर्णांक function. For any incorrect value in reserved_bar वापस '0'.
 */
क्रमागत pci_barno pci_epc_get_next_मुक्त_bar(स्थिर काष्ठा pci_epc_features
					 *epc_features, क्रमागत pci_barno bar)
अणु
	अचिन्हित दीर्घ मुक्त_bar;

	अगर (!epc_features)
		वापस BAR_0;

	/* If 'bar - 1' is a 64-bit BAR, move to the next BAR */
	अगर ((epc_features->bar_fixed_64bit << 1) & 1 << bar)
		bar++;

	/* Find अगर the reserved BAR is also a 64-bit BAR */
	मुक्त_bar = epc_features->reserved_bar & epc_features->bar_fixed_64bit;

	/* Set the adjacent bit अगर the reserved BAR is also a 64-bit BAR */
	मुक्त_bar <<= 1;
	मुक्त_bar |= epc_features->reserved_bar;

	मुक्त_bar = find_next_zero_bit(&मुक्त_bar, 6, bar);
	अगर (मुक्त_bar > 5)
		वापस NO_BAR;

	वापस मुक्त_bar;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get_next_मुक्त_bar);

/**
 * pci_epc_get_features() - get the features supported by EPC
 * @epc: the features supported by *this* EPC device will be वापसed
 * @func_no: the features supported by the EPC device specअगरic to the
 *	     endpoपूर्णांक function with func_no will be वापसed
 *
 * Invoke to get the features provided by the EPC which may be
 * specअगरic to an endpoपूर्णांक function. Returns pci_epc_features on success
 * and शून्य क्रम any failures.
 */
स्थिर काष्ठा pci_epc_features *pci_epc_get_features(काष्ठा pci_epc *epc,
						    u8 func_no)
अणु
	स्थिर काष्ठा pci_epc_features *epc_features;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस शून्य;

	अगर (!epc->ops->get_features)
		वापस शून्य;

	mutex_lock(&epc->lock);
	epc_features = epc->ops->get_features(epc, func_no);
	mutex_unlock(&epc->lock);

	वापस epc_features;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get_features);

/**
 * pci_epc_stop() - stop the PCI link
 * @epc: the link of the EPC device that has to be stopped
 *
 * Invoke to stop the PCI link
 */
व्योम pci_epc_stop(काष्ठा pci_epc *epc)
अणु
	अगर (IS_ERR(epc) || !epc->ops->stop)
		वापस;

	mutex_lock(&epc->lock);
	epc->ops->stop(epc);
	mutex_unlock(&epc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_stop);

/**
 * pci_epc_start() - start the PCI link
 * @epc: the link of *this* EPC device has to be started
 *
 * Invoke to start the PCI link
 */
पूर्णांक pci_epc_start(काष्ठा pci_epc *epc)
अणु
	पूर्णांक ret;

	अगर (IS_ERR(epc))
		वापस -EINVAL;

	अगर (!epc->ops->start)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->start(epc);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_start);

/**
 * pci_epc_उठाओ_irq() - पूर्णांकerrupt the host प्रणाली
 * @epc: the EPC device which has to पूर्णांकerrupt the host
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @type: specअगरy the type of पूर्णांकerrupt; legacy, MSI or MSI-X
 * @पूर्णांकerrupt_num: the MSI or MSI-X पूर्णांकerrupt number
 *
 * Invoke to उठाओ an legacy, MSI or MSI-X पूर्णांकerrupt
 */
पूर्णांक pci_epc_उठाओ_irq(काष्ठा pci_epc *epc, u8 func_no,
		      क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस -EINVAL;

	अगर (!epc->ops->उठाओ_irq)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->उठाओ_irq(epc, func_no, type, पूर्णांकerrupt_num);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_उठाओ_irq);

/**
 * pci_epc_map_msi_irq() - Map physical address to MSI address and वापस
 *                         MSI data
 * @epc: the EPC device which has the MSI capability
 * @func_no: the physical endpoपूर्णांक function number in the EPC device
 * @phys_addr: the physical address of the outbound region
 * @पूर्णांकerrupt_num: the MSI पूर्णांकerrupt number
 * @entry_size: Size of Outbound address region क्रम each पूर्णांकerrupt
 * @msi_data: the data that should be written in order to उठाओ MSI पूर्णांकerrupt
 *            with पूर्णांकerrupt number as 'interrupt num'
 * @msi_addr_offset: Offset of MSI address from the aligned outbound address
 *                   to which the MSI address is mapped
 *
 * Invoke to map physical address to MSI address and वापस MSI data. The
 * physical address should be an address in the outbound region. This is
 * required to implement करोorbell functionality of NTB wherein EPC on either
 * side of the पूर्णांकerface (primary and secondary) can directly ग_लिखो to the
 * physical address (in outbound region) of the other पूर्णांकerface to ring
 * करोorbell.
 */
पूर्णांक pci_epc_map_msi_irq(काष्ठा pci_epc *epc, u8 func_no, phys_addr_t phys_addr,
			u8 पूर्णांकerrupt_num, u32 entry_size, u32 *msi_data,
			u32 *msi_addr_offset)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(epc))
		वापस -EINVAL;

	अगर (!epc->ops->map_msi_irq)
		वापस -EINVAL;

	mutex_lock(&epc->lock);
	ret = epc->ops->map_msi_irq(epc, func_no, phys_addr, पूर्णांकerrupt_num,
				    entry_size, msi_data, msi_addr_offset);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_map_msi_irq);

/**
 * pci_epc_get_msi() - get the number of MSI पूर्णांकerrupt numbers allocated
 * @epc: the EPC device to which MSI पूर्णांकerrupts was requested
 * @func_no: the endpoपूर्णांक function number in the EPC device
 *
 * Invoke to get the number of MSI पूर्णांकerrupts allocated by the RC
 */
पूर्णांक pci_epc_get_msi(काष्ठा pci_epc *epc, u8 func_no)
अणु
	पूर्णांक पूर्णांकerrupt;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस 0;

	अगर (!epc->ops->get_msi)
		वापस 0;

	mutex_lock(&epc->lock);
	पूर्णांकerrupt = epc->ops->get_msi(epc, func_no);
	mutex_unlock(&epc->lock);

	अगर (पूर्णांकerrupt < 0)
		वापस 0;

	पूर्णांकerrupt = 1 << पूर्णांकerrupt;

	वापस पूर्णांकerrupt;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get_msi);

/**
 * pci_epc_set_msi() - set the number of MSI पूर्णांकerrupt numbers required
 * @epc: the EPC device on which MSI has to be configured
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @पूर्णांकerrupts: number of MSI पूर्णांकerrupts required by the EPF
 *
 * Invoke to set the required number of MSI पूर्णांकerrupts.
 */
पूर्णांक pci_epc_set_msi(काष्ठा pci_epc *epc, u8 func_no, u8 पूर्णांकerrupts)
अणु
	पूर्णांक ret;
	u8 encode_पूर्णांक;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions ||
	    पूर्णांकerrupts > 32)
		वापस -EINVAL;

	अगर (!epc->ops->set_msi)
		वापस 0;

	encode_पूर्णांक = order_base_2(पूर्णांकerrupts);

	mutex_lock(&epc->lock);
	ret = epc->ops->set_msi(epc, func_no, encode_पूर्णांक);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_set_msi);

/**
 * pci_epc_get_msix() - get the number of MSI-X पूर्णांकerrupt numbers allocated
 * @epc: the EPC device to which MSI-X पूर्णांकerrupts was requested
 * @func_no: the endpoपूर्णांक function number in the EPC device
 *
 * Invoke to get the number of MSI-X पूर्णांकerrupts allocated by the RC
 */
पूर्णांक pci_epc_get_msix(काष्ठा pci_epc *epc, u8 func_no)
अणु
	पूर्णांक पूर्णांकerrupt;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस 0;

	अगर (!epc->ops->get_msix)
		वापस 0;

	mutex_lock(&epc->lock);
	पूर्णांकerrupt = epc->ops->get_msix(epc, func_no);
	mutex_unlock(&epc->lock);

	अगर (पूर्णांकerrupt < 0)
		वापस 0;

	वापस पूर्णांकerrupt + 1;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_get_msix);

/**
 * pci_epc_set_msix() - set the number of MSI-X पूर्णांकerrupt numbers required
 * @epc: the EPC device on which MSI-X has to be configured
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @पूर्णांकerrupts: number of MSI-X पूर्णांकerrupts required by the EPF
 * @bir: BAR where the MSI-X table resides
 * @offset: Offset poपूर्णांकing to the start of MSI-X table
 *
 * Invoke to set the required number of MSI-X पूर्णांकerrupts.
 */
पूर्णांक pci_epc_set_msix(काष्ठा pci_epc *epc, u8 func_no, u16 पूर्णांकerrupts,
		     क्रमागत pci_barno bir, u32 offset)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions ||
	    पूर्णांकerrupts < 1 || पूर्णांकerrupts > 2048)
		वापस -EINVAL;

	अगर (!epc->ops->set_msix)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->set_msix(epc, func_no, पूर्णांकerrupts - 1, bir, offset);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_set_msix);

/**
 * pci_epc_unmap_addr() - unmap CPU address from PCI address
 * @epc: the EPC device on which address is allocated
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @phys_addr: physical address of the local प्रणाली
 *
 * Invoke to unmap the CPU address from PCI address.
 */
व्योम pci_epc_unmap_addr(काष्ठा pci_epc *epc, u8 func_no,
			phys_addr_t phys_addr)
अणु
	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस;

	अगर (!epc->ops->unmap_addr)
		वापस;

	mutex_lock(&epc->lock);
	epc->ops->unmap_addr(epc, func_no, phys_addr);
	mutex_unlock(&epc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_unmap_addr);

/**
 * pci_epc_map_addr() - map CPU address to PCI address
 * @epc: the EPC device on which address is allocated
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @phys_addr: physical address of the local प्रणाली
 * @pci_addr: PCI address to which the physical address should be mapped
 * @size: the size of the allocation
 *
 * Invoke to map CPU address with PCI address.
 */
पूर्णांक pci_epc_map_addr(काष्ठा pci_epc *epc, u8 func_no,
		     phys_addr_t phys_addr, u64 pci_addr, माप_प्रकार size)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस -EINVAL;

	अगर (!epc->ops->map_addr)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->map_addr(epc, func_no, phys_addr, pci_addr, size);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_map_addr);

/**
 * pci_epc_clear_bar() - reset the BAR
 * @epc: the EPC device क्रम which the BAR has to be cleared
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @epf_bar: the काष्ठा epf_bar that contains the BAR inक्रमmation
 *
 * Invoke to reset the BAR of the endpoपूर्णांक device.
 */
व्योम pci_epc_clear_bar(काष्ठा pci_epc *epc, u8 func_no,
		       काष्ठा pci_epf_bar *epf_bar)
अणु
	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions ||
	    (epf_bar->barno == BAR_5 &&
	     epf_bar->flags & PCI_BASE_ADDRESS_MEM_TYPE_64))
		वापस;

	अगर (!epc->ops->clear_bar)
		वापस;

	mutex_lock(&epc->lock);
	epc->ops->clear_bar(epc, func_no, epf_bar);
	mutex_unlock(&epc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_clear_bar);

/**
 * pci_epc_set_bar() - configure BAR in order क्रम host to assign PCI addr space
 * @epc: the EPC device on which BAR has to be configured
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @epf_bar: the काष्ठा epf_bar that contains the BAR inक्रमmation
 *
 * Invoke to configure the BAR of the endpoपूर्णांक device.
 */
पूर्णांक pci_epc_set_bar(काष्ठा pci_epc *epc, u8 func_no,
		    काष्ठा pci_epf_bar *epf_bar)
अणु
	पूर्णांक ret;
	पूर्णांक flags = epf_bar->flags;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions ||
	    (epf_bar->barno == BAR_5 &&
	     flags & PCI_BASE_ADDRESS_MEM_TYPE_64) ||
	    (flags & PCI_BASE_ADDRESS_SPACE_IO &&
	     flags & PCI_BASE_ADDRESS_IO_MASK) ||
	    (upper_32_bits(epf_bar->size) &&
	     !(flags & PCI_BASE_ADDRESS_MEM_TYPE_64)))
		वापस -EINVAL;

	अगर (!epc->ops->set_bar)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->set_bar(epc, func_no, epf_bar);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_set_bar);

/**
 * pci_epc_ग_लिखो_header() - ग_लिखो standard configuration header
 * @epc: the EPC device to which the configuration header should be written
 * @func_no: the endpoपूर्णांक function number in the EPC device
 * @header: standard configuration header fields
 *
 * Invoke to ग_लिखो the configuration header to the endpoपूर्णांक controller. Every
 * endpoपूर्णांक controller will have a dedicated location to which the standard
 * configuration header would be written. The callback function should ग_लिखो
 * the header fields to this dedicated location.
 */
पूर्णांक pci_epc_ग_लिखो_header(काष्ठा pci_epc *epc, u8 func_no,
			 काष्ठा pci_epf_header *header)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(epc) || func_no >= epc->max_functions)
		वापस -EINVAL;

	अगर (!epc->ops->ग_लिखो_header)
		वापस 0;

	mutex_lock(&epc->lock);
	ret = epc->ops->ग_लिखो_header(epc, func_no, header);
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_ग_लिखो_header);

/**
 * pci_epc_add_epf() - bind PCI endpoपूर्णांक function to an endpoपूर्णांक controller
 * @epc: the EPC device to which the endpoपूर्णांक function should be added
 * @epf: the endpoपूर्णांक function to be added
 * @type: Identअगरies अगर the EPC is connected to the primary or secondary
 *        पूर्णांकerface of EPF
 *
 * A PCI endpoपूर्णांक device can have one or more functions. In the हाल of PCIe,
 * the specअगरication allows up to 8 PCIe endpoपूर्णांक functions. Invoke
 * pci_epc_add_epf() to add a PCI endpoपूर्णांक function to an endpoपूर्णांक controller.
 */
पूर्णांक pci_epc_add_epf(काष्ठा pci_epc *epc, काष्ठा pci_epf *epf,
		    क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा list_head *list;
	u32 func_no;
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(epc))
		वापस -EINVAL;

	अगर (type == PRIMARY_INTERFACE && epf->epc)
		वापस -EBUSY;

	अगर (type == SECONDARY_INTERFACE && epf->sec_epc)
		वापस -EBUSY;

	mutex_lock(&epc->lock);
	func_no = find_first_zero_bit(&epc->function_num_map,
				      BITS_PER_LONG);
	अगर (func_no >= BITS_PER_LONG) अणु
		ret = -EINVAL;
		जाओ ret;
	पूर्ण

	अगर (func_no > epc->max_functions - 1) अणु
		dev_err(&epc->dev, "Exceeding max supported Function Number\n");
		ret = -EINVAL;
		जाओ ret;
	पूर्ण

	set_bit(func_no, &epc->function_num_map);
	अगर (type == PRIMARY_INTERFACE) अणु
		epf->func_no = func_no;
		epf->epc = epc;
		list = &epf->list;
	पूर्ण अन्यथा अणु
		epf->sec_epc_func_no = func_no;
		epf->sec_epc = epc;
		list = &epf->sec_epc_list;
	पूर्ण

	list_add_tail(list, &epc->pci_epf);
ret:
	mutex_unlock(&epc->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_add_epf);

/**
 * pci_epc_हटाओ_epf() - हटाओ PCI endpoपूर्णांक function from endpoपूर्णांक controller
 * @epc: the EPC device from which the endpoपूर्णांक function should be हटाओd
 * @epf: the endpoपूर्णांक function to be हटाओd
 * @type: identअगरies अगर the EPC is connected to the primary or secondary
 *        पूर्णांकerface of EPF
 *
 * Invoke to हटाओ PCI endpoपूर्णांक function from the endpoपूर्णांक controller.
 */
व्योम pci_epc_हटाओ_epf(काष्ठा pci_epc *epc, काष्ठा pci_epf *epf,
			क्रमागत pci_epc_पूर्णांकerface_type type)
अणु
	काष्ठा list_head *list;
	u32 func_no = 0;

	अगर (!epc || IS_ERR(epc) || !epf)
		वापस;

	अगर (type == PRIMARY_INTERFACE) अणु
		func_no = epf->func_no;
		list = &epf->list;
	पूर्ण अन्यथा अणु
		func_no = epf->sec_epc_func_no;
		list = &epf->sec_epc_list;
	पूर्ण

	mutex_lock(&epc->lock);
	clear_bit(func_no, &epc->function_num_map);
	list_del(list);
	epf->epc = शून्य;
	mutex_unlock(&epc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_हटाओ_epf);

/**
 * pci_epc_linkup() - Notअगरy the EPF device that EPC device has established a
 *		      connection with the Root Complex.
 * @epc: the EPC device which has established link with the host
 *
 * Invoke to Notअगरy the EPF device that the EPC device has established a
 * connection with the Root Complex.
 */
व्योम pci_epc_linkup(काष्ठा pci_epc *epc)
अणु
	अगर (!epc || IS_ERR(epc))
		वापस;

	atomic_notअगरier_call_chain(&epc->notअगरier, LINK_UP, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_linkup);

/**
 * pci_epc_init_notअगरy() - Notअगरy the EPF device that EPC device's core
 *			   initialization is completed.
 * @epc: the EPC device whose core initialization is completeds
 *
 * Invoke to Notअगरy the EPF device that the EPC device's initialization
 * is completed.
 */
व्योम pci_epc_init_notअगरy(काष्ठा pci_epc *epc)
अणु
	अगर (!epc || IS_ERR(epc))
		वापस;

	atomic_notअगरier_call_chain(&epc->notअगरier, CORE_INIT, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_init_notअगरy);

/**
 * pci_epc_destroy() - destroy the EPC device
 * @epc: the EPC device that has to be destroyed
 *
 * Invoke to destroy the PCI EPC device
 */
व्योम pci_epc_destroy(काष्ठा pci_epc *epc)
अणु
	pci_ep_cfs_हटाओ_epc_group(epc->group);
	device_unरेजिस्टर(&epc->dev);
	kमुक्त(epc);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_destroy);

/**
 * devm_pci_epc_destroy() - destroy the EPC device
 * @dev: device that wants to destroy the EPC
 * @epc: the EPC device that has to be destroyed
 *
 * Invoke to destroy the devres associated with this
 * pci_epc and destroy the EPC device.
 */
व्योम devm_pci_epc_destroy(काष्ठा device *dev, काष्ठा pci_epc *epc)
अणु
	पूर्णांक r;

	r = devres_destroy(dev, devm_pci_epc_release, devm_pci_epc_match,
			   epc);
	dev_WARN_ONCE(dev, r, "couldn't find PCI EPC resource\n");
पूर्ण
EXPORT_SYMBOL_GPL(devm_pci_epc_destroy);

/**
 * __pci_epc_create() - create a new endpoपूर्णांक controller (EPC) device
 * @dev: device that is creating the new EPC
 * @ops: function poपूर्णांकers क्रम perक्रमming EPC operations
 * @owner: the owner of the module that creates the EPC device
 *
 * Invoke to create a new EPC device and add it to pci_epc class.
 */
काष्ठा pci_epc *
__pci_epc_create(काष्ठा device *dev, स्थिर काष्ठा pci_epc_ops *ops,
		 काष्ठा module *owner)
अणु
	पूर्णांक ret;
	काष्ठा pci_epc *epc;

	अगर (WARN_ON(!dev)) अणु
		ret = -EINVAL;
		जाओ err_ret;
	पूर्ण

	epc = kzalloc(माप(*epc), GFP_KERNEL);
	अगर (!epc) अणु
		ret = -ENOMEM;
		जाओ err_ret;
	पूर्ण

	mutex_init(&epc->lock);
	INIT_LIST_HEAD(&epc->pci_epf);
	ATOMIC_INIT_NOTIFIER_HEAD(&epc->notअगरier);

	device_initialize(&epc->dev);
	epc->dev.class = pci_epc_class;
	epc->dev.parent = dev;
	epc->ops = ops;

	ret = dev_set_name(&epc->dev, "%s", dev_name(dev));
	अगर (ret)
		जाओ put_dev;

	ret = device_add(&epc->dev);
	अगर (ret)
		जाओ put_dev;

	epc->group = pci_ep_cfs_add_epc_group(dev_name(dev));

	वापस epc;

put_dev:
	put_device(&epc->dev);
	kमुक्त(epc);

err_ret:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(__pci_epc_create);

/**
 * __devm_pci_epc_create() - create a new endpoपूर्णांक controller (EPC) device
 * @dev: device that is creating the new EPC
 * @ops: function poपूर्णांकers क्रम perक्रमming EPC operations
 * @owner: the owner of the module that creates the EPC device
 *
 * Invoke to create a new EPC device and add it to pci_epc class.
 * While at that, it also associates the device with the pci_epc using devres.
 * On driver detach, release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 */
काष्ठा pci_epc *
__devm_pci_epc_create(काष्ठा device *dev, स्थिर काष्ठा pci_epc_ops *ops,
		      काष्ठा module *owner)
अणु
	काष्ठा pci_epc **ptr, *epc;

	ptr = devres_alloc(devm_pci_epc_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	epc = __pci_epc_create(dev, ops, owner);
	अगर (!IS_ERR(epc)) अणु
		*ptr = epc;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस epc;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_pci_epc_create);

अटल पूर्णांक __init pci_epc_init(व्योम)
अणु
	pci_epc_class = class_create(THIS_MODULE, "pci_epc");
	अगर (IS_ERR(pci_epc_class)) अणु
		pr_err("failed to create pci epc class --> %ld\n",
		       PTR_ERR(pci_epc_class));
		वापस PTR_ERR(pci_epc_class);
	पूर्ण

	वापस 0;
पूर्ण
module_init(pci_epc_init);

अटल व्योम __निकास pci_epc_निकास(व्योम)
अणु
	class_destroy(pci_epc_class);
पूर्ण
module_निकास(pci_epc_निकास);

MODULE_DESCRIPTION("PCI EPC Library");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
