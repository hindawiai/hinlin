<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/of_address.h>

क्रमागत devm_ioremap_type अणु
	DEVM_IOREMAP = 0,
	DEVM_IOREMAP_UC,
	DEVM_IOREMAP_WC,
	DEVM_IOREMAP_NP,
पूर्ण;

व्योम devm_ioremap_release(काष्ठा device *dev, व्योम *res)
अणु
	iounmap(*(व्योम __iomem **)res);
पूर्ण

अटल पूर्णांक devm_ioremap_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	वापस *(व्योम **)res == match_data;
पूर्ण

अटल व्योम __iomem *__devm_ioremap(काष्ठा device *dev, resource_माप_प्रकार offset,
				    resource_माप_प्रकार size,
				    क्रमागत devm_ioremap_type type)
अणु
	व्योम __iomem **ptr, *addr = शून्य;

	ptr = devres_alloc(devm_ioremap_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	चयन (type) अणु
	हाल DEVM_IOREMAP:
		addr = ioremap(offset, size);
		अवरोध;
	हाल DEVM_IOREMAP_UC:
		addr = ioremap_uc(offset, size);
		अवरोध;
	हाल DEVM_IOREMAP_WC:
		addr = ioremap_wc(offset, size);
		अवरोध;
	हाल DEVM_IOREMAP_NP:
		addr = ioremap_np(offset, size);
		अवरोध;
	पूर्ण

	अगर (addr) अणु
		*ptr = addr;
		devres_add(dev, ptr);
	पूर्ण अन्यथा
		devres_मुक्त(ptr);

	वापस addr;
पूर्ण

/**
 * devm_ioremap - Managed ioremap()
 * @dev: Generic device to remap IO address क्रम
 * @offset: Resource address to map
 * @size: Size of map
 *
 * Managed ioremap().  Map is स्वतःmatically unmapped on driver detach.
 */
व्योम __iomem *devm_ioremap(काष्ठा device *dev, resource_माप_प्रकार offset,
			   resource_माप_प्रकार size)
अणु
	वापस __devm_ioremap(dev, offset, size, DEVM_IOREMAP);
पूर्ण
EXPORT_SYMBOL(devm_ioremap);

/**
 * devm_ioremap_uc - Managed ioremap_uc()
 * @dev: Generic device to remap IO address क्रम
 * @offset: Resource address to map
 * @size: Size of map
 *
 * Managed ioremap_uc().  Map is स्वतःmatically unmapped on driver detach.
 */
व्योम __iomem *devm_ioremap_uc(काष्ठा device *dev, resource_माप_प्रकार offset,
			      resource_माप_प्रकार size)
अणु
	वापस __devm_ioremap(dev, offset, size, DEVM_IOREMAP_UC);
पूर्ण
EXPORT_SYMBOL_GPL(devm_ioremap_uc);

/**
 * devm_ioremap_wc - Managed ioremap_wc()
 * @dev: Generic device to remap IO address क्रम
 * @offset: Resource address to map
 * @size: Size of map
 *
 * Managed ioremap_wc().  Map is स्वतःmatically unmapped on driver detach.
 */
व्योम __iomem *devm_ioremap_wc(काष्ठा device *dev, resource_माप_प्रकार offset,
			      resource_माप_प्रकार size)
अणु
	वापस __devm_ioremap(dev, offset, size, DEVM_IOREMAP_WC);
पूर्ण
EXPORT_SYMBOL(devm_ioremap_wc);

/**
 * devm_ioremap_np - Managed ioremap_np()
 * @dev: Generic device to remap IO address क्रम
 * @offset: Resource address to map
 * @size: Size of map
 *
 * Managed ioremap_np().  Map is स्वतःmatically unmapped on driver detach.
 */
व्योम __iomem *devm_ioremap_np(काष्ठा device *dev, resource_माप_प्रकार offset,
			      resource_माप_प्रकार size)
अणु
	वापस __devm_ioremap(dev, offset, size, DEVM_IOREMAP_NP);
पूर्ण
EXPORT_SYMBOL(devm_ioremap_np);

/**
 * devm_iounmap - Managed iounmap()
 * @dev: Generic device to unmap क्रम
 * @addr: Address to unmap
 *
 * Managed iounmap().  @addr must have been mapped using devm_ioremap*().
 */
व्योम devm_iounmap(काष्ठा device *dev, व्योम __iomem *addr)
अणु
	WARN_ON(devres_destroy(dev, devm_ioremap_release, devm_ioremap_match,
			       (__क्रमce व्योम *)addr));
	iounmap(addr);
पूर्ण
EXPORT_SYMBOL(devm_iounmap);

अटल व्योम __iomem *
__devm_ioremap_resource(काष्ठा device *dev, स्थिर काष्ठा resource *res,
			क्रमागत devm_ioremap_type type)
अणु
	resource_माप_प्रकार size;
	व्योम __iomem *dest_ptr;
	अक्षर *pretty_name;

	BUG_ON(!dev);

	अगर (!res || resource_type(res) != IORESOURCE_MEM) अणु
		dev_err(dev, "invalid resource\n");
		वापस IOMEM_ERR_PTR(-EINVAL);
	पूर्ण

	अगर (type == DEVM_IOREMAP && res->flags & IORESOURCE_MEM_NONPOSTED)
		type = DEVM_IOREMAP_NP;

	size = resource_size(res);

	अगर (res->name)
		pretty_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s %s",
					     dev_name(dev), res->name);
	अन्यथा
		pretty_name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!pretty_name)
		वापस IOMEM_ERR_PTR(-ENOMEM);

	अगर (!devm_request_mem_region(dev, res->start, size, pretty_name)) अणु
		dev_err(dev, "can't request region for resource %pR\n", res);
		वापस IOMEM_ERR_PTR(-EBUSY);
	पूर्ण

	dest_ptr = __devm_ioremap(dev, res->start, size, type);
	अगर (!dest_ptr) अणु
		dev_err(dev, "ioremap failed for resource %pR\n", res);
		devm_release_mem_region(dev, res->start, size);
		dest_ptr = IOMEM_ERR_PTR(-ENOMEM);
	पूर्ण

	वापस dest_ptr;
पूर्ण

/**
 * devm_ioremap_resource() - check, request region, and ioremap resource
 * @dev: generic device to handle the resource क्रम
 * @res: resource to be handled
 *
 * Checks that a resource is a valid memory region, requests the memory
 * region and ioremaps it. All operations are managed and will be unकरोne
 * on driver detach.
 *
 * Usage example:
 *
 *	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
 *	base = devm_ioremap_resource(&pdev->dev, res);
 *	अगर (IS_ERR(base))
 *		वापस PTR_ERR(base);
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *devm_ioremap_resource(काष्ठा device *dev,
				    स्थिर काष्ठा resource *res)
अणु
	वापस __devm_ioremap_resource(dev, res, DEVM_IOREMAP);
पूर्ण
EXPORT_SYMBOL(devm_ioremap_resource);

/**
 * devm_ioremap_resource_wc() - ग_लिखो-combined variant of
 *				devm_ioremap_resource()
 * @dev: generic device to handle the resource क्रम
 * @res: resource to be handled
 *
 * Return: a poपूर्णांकer to the remapped memory or an ERR_PTR() encoded error code
 * on failure.
 */
व्योम __iomem *devm_ioremap_resource_wc(काष्ठा device *dev,
				       स्थिर काष्ठा resource *res)
अणु
	वापस __devm_ioremap_resource(dev, res, DEVM_IOREMAP_WC);
पूर्ण

/*
 * devm_of_iomap - Requests a resource and maps the memory mapped IO
 *		   क्रम a given device_node managed by a given device
 *
 * Checks that a resource is a valid memory region, requests the memory
 * region and ioremaps it. All operations are managed and will be unकरोne
 * on driver detach of the device.
 *
 * This is to be used when a device requests/maps resources described
 * by other device tree nodes (children or otherwise).
 *
 * @dev:	The device "managing" the resource
 * @node:       The device-tree node where the resource resides
 * @index:	index of the MMIO range in the "reg" property
 * @size:	Returns the size of the resource (pass शून्य अगर not needed)
 *
 * Usage example:
 *
 *	base = devm_of_iomap(&pdev->dev, node, 0, शून्य);
 *	अगर (IS_ERR(base))
 *		वापस PTR_ERR(base);
 *
 * Please Note: This is not a one-to-one replacement क्रम of_iomap() because the
 * of_iomap() function करोes not track whether the region is alपढ़ोy mapped.  If
 * two drivers try to map the same memory, the of_iomap() function will succeed
 * but the devm_of_iomap() function will वापस -EBUSY.
 *
 * Return: a poपूर्णांकer to the requested and mapped memory or an ERR_PTR() encoded
 * error code on failure.
 */
व्योम __iomem *devm_of_iomap(काष्ठा device *dev, काष्ठा device_node *node, पूर्णांक index,
			    resource_माप_प्रकार *size)
अणु
	काष्ठा resource res;

	अगर (of_address_to_resource(node, index, &res))
		वापस IOMEM_ERR_PTR(-EINVAL);
	अगर (size)
		*size = resource_size(&res);
	वापस devm_ioremap_resource(dev, &res);
पूर्ण
EXPORT_SYMBOL(devm_of_iomap);

#अगर_घोषित CONFIG_HAS_IOPORT_MAP
/*
 * Generic iomap devres
 */
अटल व्योम devm_ioport_map_release(काष्ठा device *dev, व्योम *res)
अणु
	ioport_unmap(*(व्योम __iomem **)res);
पूर्ण

अटल पूर्णांक devm_ioport_map_match(काष्ठा device *dev, व्योम *res,
				 व्योम *match_data)
अणु
	वापस *(व्योम **)res == match_data;
पूर्ण

/**
 * devm_ioport_map - Managed ioport_map()
 * @dev: Generic device to map ioport क्रम
 * @port: Port to map
 * @nr: Number of ports to map
 *
 * Managed ioport_map().  Map is स्वतःmatically unmapped on driver
 * detach.
 *
 * Return: a poपूर्णांकer to the remapped memory or शून्य on failure.
 */
व्योम __iomem *devm_ioport_map(काष्ठा device *dev, अचिन्हित दीर्घ port,
			       अचिन्हित पूर्णांक nr)
अणु
	व्योम __iomem **ptr, *addr;

	ptr = devres_alloc(devm_ioport_map_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	addr = ioport_map(port, nr);
	अगर (addr) अणु
		*ptr = addr;
		devres_add(dev, ptr);
	पूर्ण अन्यथा
		devres_मुक्त(ptr);

	वापस addr;
पूर्ण
EXPORT_SYMBOL(devm_ioport_map);

/**
 * devm_ioport_unmap - Managed ioport_unmap()
 * @dev: Generic device to unmap क्रम
 * @addr: Address to unmap
 *
 * Managed ioport_unmap().  @addr must have been mapped using
 * devm_ioport_map().
 */
व्योम devm_ioport_unmap(काष्ठा device *dev, व्योम __iomem *addr)
अणु
	ioport_unmap(addr);
	WARN_ON(devres_destroy(dev, devm_ioport_map_release,
			       devm_ioport_map_match, (__क्रमce व्योम *)addr));
पूर्ण
EXPORT_SYMBOL(devm_ioport_unmap);
#पूर्ण_अगर /* CONFIG_HAS_IOPORT_MAP */

#अगर_घोषित CONFIG_PCI
/*
 * PCI iomap devres
 */
#घोषणा PCIM_IOMAP_MAX	PCI_STD_NUM_BARS

काष्ठा pcim_iomap_devres अणु
	व्योम __iomem *table[PCIM_IOMAP_MAX];
पूर्ण;

अटल व्योम pcim_iomap_release(काष्ठा device *gendev, व्योम *res)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(gendev);
	काष्ठा pcim_iomap_devres *this = res;
	पूर्णांक i;

	क्रम (i = 0; i < PCIM_IOMAP_MAX; i++)
		अगर (this->table[i])
			pci_iounmap(dev, this->table[i]);
पूर्ण

/**
 * pcim_iomap_table - access iomap allocation table
 * @pdev: PCI device to access iomap table क्रम
 *
 * Access iomap allocation table क्रम @dev.  If iomap table करोesn't
 * exist and @pdev is managed, it will be allocated.  All iomaps
 * recorded in the iomap table are स्वतःmatically unmapped on driver
 * detach.
 *
 * This function might sleep when the table is first allocated but can
 * be safely called without context and guaranteed to succed once
 * allocated.
 */
व्योम __iomem * स्थिर *pcim_iomap_table(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pcim_iomap_devres *dr, *new_dr;

	dr = devres_find(&pdev->dev, pcim_iomap_release, शून्य, शून्य);
	अगर (dr)
		वापस dr->table;

	new_dr = devres_alloc(pcim_iomap_release, माप(*new_dr), GFP_KERNEL);
	अगर (!new_dr)
		वापस शून्य;
	dr = devres_get(&pdev->dev, new_dr, शून्य, शून्य);
	वापस dr->table;
पूर्ण
EXPORT_SYMBOL(pcim_iomap_table);

/**
 * pcim_iomap - Managed pcim_iomap()
 * @pdev: PCI device to iomap क्रम
 * @bar: BAR to iomap
 * @maxlen: Maximum length of iomap
 *
 * Managed pci_iomap().  Map is स्वतःmatically unmapped on driver
 * detach.
 */
व्योम __iomem *pcim_iomap(काष्ठा pci_dev *pdev, पूर्णांक bar, अचिन्हित दीर्घ maxlen)
अणु
	व्योम __iomem **tbl;

	BUG_ON(bar >= PCIM_IOMAP_MAX);

	tbl = (व्योम __iomem **)pcim_iomap_table(pdev);
	अगर (!tbl || tbl[bar])	/* duplicate mappings not allowed */
		वापस शून्य;

	tbl[bar] = pci_iomap(pdev, bar, maxlen);
	वापस tbl[bar];
पूर्ण
EXPORT_SYMBOL(pcim_iomap);

/**
 * pcim_iounmap - Managed pci_iounmap()
 * @pdev: PCI device to iounmap क्रम
 * @addr: Address to unmap
 *
 * Managed pci_iounmap().  @addr must have been mapped using pcim_iomap().
 */
व्योम pcim_iounmap(काष्ठा pci_dev *pdev, व्योम __iomem *addr)
अणु
	व्योम __iomem **tbl;
	पूर्णांक i;

	pci_iounmap(pdev, addr);

	tbl = (व्योम __iomem **)pcim_iomap_table(pdev);
	BUG_ON(!tbl);

	क्रम (i = 0; i < PCIM_IOMAP_MAX; i++)
		अगर (tbl[i] == addr) अणु
			tbl[i] = शून्य;
			वापस;
		पूर्ण
	WARN_ON(1);
पूर्ण
EXPORT_SYMBOL(pcim_iounmap);

/**
 * pcim_iomap_regions - Request and iomap PCI BARs
 * @pdev: PCI device to map IO resources क्रम
 * @mask: Mask of BARs to request and iomap
 * @name: Name used when requesting regions
 *
 * Request and iomap regions specअगरied by @mask.
 */
पूर्णांक pcim_iomap_regions(काष्ठा pci_dev *pdev, पूर्णांक mask, स्थिर अक्षर *name)
अणु
	व्योम __iomem * स्थिर *iomap;
	पूर्णांक i, rc;

	iomap = pcim_iomap_table(pdev);
	अगर (!iomap)
		वापस -ENOMEM;

	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		अचिन्हित दीर्घ len;

		अगर (!(mask & (1 << i)))
			जारी;

		rc = -EINVAL;
		len = pci_resource_len(pdev, i);
		अगर (!len)
			जाओ err_inval;

		rc = pci_request_region(pdev, i, name);
		अगर (rc)
			जाओ err_inval;

		rc = -ENOMEM;
		अगर (!pcim_iomap(pdev, i, 0))
			जाओ err_region;
	पूर्ण

	वापस 0;

 err_region:
	pci_release_region(pdev, i);
 err_inval:
	जबतक (--i >= 0) अणु
		अगर (!(mask & (1 << i)))
			जारी;
		pcim_iounmap(pdev, iomap[i]);
		pci_release_region(pdev, i);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL(pcim_iomap_regions);

/**
 * pcim_iomap_regions_request_all - Request all BARs and iomap specअगरied ones
 * @pdev: PCI device to map IO resources क्रम
 * @mask: Mask of BARs to iomap
 * @name: Name used when requesting regions
 *
 * Request all PCI BARs and iomap regions specअगरied by @mask.
 */
पूर्णांक pcim_iomap_regions_request_all(काष्ठा pci_dev *pdev, पूर्णांक mask,
				   स्थिर अक्षर *name)
अणु
	पूर्णांक request_mask = ((1 << 6) - 1) & ~mask;
	पूर्णांक rc;

	rc = pci_request_selected_regions(pdev, request_mask, name);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, mask, name);
	अगर (rc)
		pci_release_selected_regions(pdev, request_mask);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(pcim_iomap_regions_request_all);

/**
 * pcim_iounmap_regions - Unmap and release PCI BARs
 * @pdev: PCI device to map IO resources क्रम
 * @mask: Mask of BARs to unmap and release
 *
 * Unmap and release regions specअगरied by @mask.
 */
व्योम pcim_iounmap_regions(काष्ठा pci_dev *pdev, पूर्णांक mask)
अणु
	व्योम __iomem * स्थिर *iomap;
	पूर्णांक i;

	iomap = pcim_iomap_table(pdev);
	अगर (!iomap)
		वापस;

	क्रम (i = 0; i < PCIM_IOMAP_MAX; i++) अणु
		अगर (!(mask & (1 << i)))
			जारी;

		pcim_iounmap(pdev, iomap[i]);
		pci_release_region(pdev, i);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(pcim_iounmap_regions);
#पूर्ण_अगर /* CONFIG_PCI */
