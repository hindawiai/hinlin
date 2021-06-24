<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Endpoपूर्णांक *Controller* Address Space Management
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/pci-epc.h>

/**
 * pci_epc_mem_get_order() - determine the allocation order of a memory size
 * @mem: address space of the endpoपूर्णांक controller
 * @size: the size क्रम which to get the order
 *
 * Reimplement get_order() क्रम mem->page_size since the generic get_order
 * always माला_लो order with a स्थिरant PAGE_SIZE.
 */
अटल पूर्णांक pci_epc_mem_get_order(काष्ठा pci_epc_mem *mem, माप_प्रकार size)
अणु
	पूर्णांक order;
	अचिन्हित पूर्णांक page_shअगरt = ilog2(mem->winकरोw.page_size);

	size--;
	size >>= page_shअगरt;
#अगर BITS_PER_LONG == 32
	order = fls(size);
#अन्यथा
	order = fls64(size);
#पूर्ण_अगर
	वापस order;
पूर्ण

/**
 * pci_epc_multi_mem_init() - initialize the pci_epc_mem काष्ठाure
 * @epc: the EPC device that invoked pci_epc_mem_init
 * @winकरोws: poपूर्णांकer to winकरोws supported by the device
 * @num_winकरोws: number of winकरोws device supports
 *
 * Invoke to initialize the pci_epc_mem काष्ठाure used by the
 * endpoपूर्णांक functions to allocate mapped PCI address.
 */
पूर्णांक pci_epc_multi_mem_init(काष्ठा pci_epc *epc,
			   काष्ठा pci_epc_mem_winकरोw *winकरोws,
			   अचिन्हित पूर्णांक num_winकरोws)
अणु
	काष्ठा pci_epc_mem *mem = शून्य;
	अचिन्हित दीर्घ *biपंचांगap = शून्य;
	अचिन्हित पूर्णांक page_shअगरt;
	माप_प्रकार page_size;
	पूर्णांक biपंचांगap_size;
	पूर्णांक pages;
	पूर्णांक ret;
	पूर्णांक i;

	epc->num_winकरोws = 0;

	अगर (!winकरोws || !num_winकरोws)
		वापस -EINVAL;

	epc->winकरोws = kसुस्मृति(num_winकरोws, माप(*epc->winकरोws), GFP_KERNEL);
	अगर (!epc->winकरोws)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_winकरोws; i++) अणु
		page_size = winकरोws[i].page_size;
		अगर (page_size < PAGE_SIZE)
			page_size = PAGE_SIZE;
		page_shअगरt = ilog2(page_size);
		pages = winकरोws[i].size >> page_shअगरt;
		biपंचांगap_size = BITS_TO_LONGS(pages) * माप(दीर्घ);

		mem = kzalloc(माप(*mem), GFP_KERNEL);
		अगर (!mem) अणु
			ret = -ENOMEM;
			i--;
			जाओ err_mem;
		पूर्ण

		biपंचांगap = kzalloc(biपंचांगap_size, GFP_KERNEL);
		अगर (!biपंचांगap) अणु
			ret = -ENOMEM;
			kमुक्त(mem);
			i--;
			जाओ err_mem;
		पूर्ण

		mem->winकरोw.phys_base = winकरोws[i].phys_base;
		mem->winकरोw.size = winकरोws[i].size;
		mem->winकरोw.page_size = page_size;
		mem->biपंचांगap = biपंचांगap;
		mem->pages = pages;
		mutex_init(&mem->lock);
		epc->winकरोws[i] = mem;
	पूर्ण

	epc->mem = epc->winकरोws[0];
	epc->num_winकरोws = num_winकरोws;

	वापस 0;

err_mem:
	क्रम (; i >= 0; i--) अणु
		mem = epc->winकरोws[i];
		kमुक्त(mem->biपंचांगap);
		kमुक्त(mem);
	पूर्ण
	kमुक्त(epc->winकरोws);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_multi_mem_init);

पूर्णांक pci_epc_mem_init(काष्ठा pci_epc *epc, phys_addr_t base,
		     माप_प्रकार size, माप_प्रकार page_size)
अणु
	काष्ठा pci_epc_mem_winकरोw mem_winकरोw;

	mem_winकरोw.phys_base = base;
	mem_winकरोw.size = size;
	mem_winकरोw.page_size = page_size;

	वापस pci_epc_multi_mem_init(epc, &mem_winकरोw, 1);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_mem_init);

/**
 * pci_epc_mem_निकास() - cleanup the pci_epc_mem काष्ठाure
 * @epc: the EPC device that invoked pci_epc_mem_निकास
 *
 * Invoke to cleanup the pci_epc_mem काष्ठाure allocated in
 * pci_epc_mem_init().
 */
व्योम pci_epc_mem_निकास(काष्ठा pci_epc *epc)
अणु
	काष्ठा pci_epc_mem *mem;
	पूर्णांक i;

	अगर (!epc->num_winकरोws)
		वापस;

	क्रम (i = 0; i < epc->num_winकरोws; i++) अणु
		mem = epc->winकरोws[i];
		kमुक्त(mem->biपंचांगap);
		kमुक्त(mem);
	पूर्ण
	kमुक्त(epc->winकरोws);

	epc->winकरोws = शून्य;
	epc->mem = शून्य;
	epc->num_winकरोws = 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_mem_निकास);

/**
 * pci_epc_mem_alloc_addr() - allocate memory address from EPC addr space
 * @epc: the EPC device on which memory has to be allocated
 * @phys_addr: populate the allocated physical address here
 * @size: the size of the address space that has to be allocated
 *
 * Invoke to allocate memory address from the EPC address space. This
 * is usually करोne to map the remote RC address पूर्णांकo the local प्रणाली.
 */
व्योम __iomem *pci_epc_mem_alloc_addr(काष्ठा pci_epc *epc,
				     phys_addr_t *phys_addr, माप_प्रकार size)
अणु
	व्योम __iomem *virt_addr = शून्य;
	काष्ठा pci_epc_mem *mem;
	अचिन्हित पूर्णांक page_shअगरt;
	माप_प्रकार align_size;
	पूर्णांक pageno;
	पूर्णांक order;
	पूर्णांक i;

	क्रम (i = 0; i < epc->num_winकरोws; i++) अणु
		mem = epc->winकरोws[i];
		mutex_lock(&mem->lock);
		align_size = ALIGN(size, mem->winकरोw.page_size);
		order = pci_epc_mem_get_order(mem, align_size);

		pageno = biपंचांगap_find_मुक्त_region(mem->biपंचांगap, mem->pages,
						 order);
		अगर (pageno >= 0) अणु
			page_shअगरt = ilog2(mem->winकरोw.page_size);
			*phys_addr = mem->winकरोw.phys_base +
				((phys_addr_t)pageno << page_shअगरt);
			virt_addr = ioremap(*phys_addr, align_size);
			अगर (!virt_addr) अणु
				biपंचांगap_release_region(mem->biपंचांगap,
						      pageno, order);
				mutex_unlock(&mem->lock);
				जारी;
			पूर्ण
			mutex_unlock(&mem->lock);
			वापस virt_addr;
		पूर्ण
		mutex_unlock(&mem->lock);
	पूर्ण

	वापस virt_addr;
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_mem_alloc_addr);

अटल काष्ठा pci_epc_mem *pci_epc_get_matching_winकरोw(काष्ठा pci_epc *epc,
						       phys_addr_t phys_addr)
अणु
	काष्ठा pci_epc_mem *mem;
	पूर्णांक i;

	क्रम (i = 0; i < epc->num_winकरोws; i++) अणु
		mem = epc->winकरोws[i];

		अगर (phys_addr >= mem->winकरोw.phys_base &&
		    phys_addr < (mem->winकरोw.phys_base + mem->winकरोw.size))
			वापस mem;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * pci_epc_mem_मुक्त_addr() - मुक्त the allocated memory address
 * @epc: the EPC device on which memory was allocated
 * @phys_addr: the allocated physical address
 * @virt_addr: भव address of the allocated mem space
 * @size: the size of the allocated address space
 *
 * Invoke to मुक्त the memory allocated using pci_epc_mem_alloc_addr.
 */
व्योम pci_epc_mem_मुक्त_addr(काष्ठा pci_epc *epc, phys_addr_t phys_addr,
			   व्योम __iomem *virt_addr, माप_प्रकार size)
अणु
	काष्ठा pci_epc_mem *mem;
	अचिन्हित पूर्णांक page_shअगरt;
	माप_प्रकार page_size;
	पूर्णांक pageno;
	पूर्णांक order;

	mem = pci_epc_get_matching_winकरोw(epc, phys_addr);
	अगर (!mem) अणु
		pr_err("failed to get matching window\n");
		वापस;
	पूर्ण

	page_size = mem->winकरोw.page_size;
	page_shअगरt = ilog2(page_size);
	iounmap(virt_addr);
	pageno = (phys_addr - mem->winकरोw.phys_base) >> page_shअगरt;
	size = ALIGN(size, page_size);
	order = pci_epc_mem_get_order(mem, size);
	mutex_lock(&mem->lock);
	biपंचांगap_release_region(mem->biपंचांगap, pageno, order);
	mutex_unlock(&mem->lock);
पूर्ण
EXPORT_SYMBOL_GPL(pci_epc_mem_मुक्त_addr);

MODULE_DESCRIPTION("PCI EPC Address Space Management");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
