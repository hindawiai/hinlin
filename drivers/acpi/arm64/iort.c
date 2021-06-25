<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016, Semihalf
 *	Author: Tomasz Nowicki <tn@semihalf.com>
 *
 * This file implements early detection/parsing of I/O mapping
 * reported to OS through firmware via I/O Remapping Table (IORT)
 * IORT करोcument number: ARM DEN 0049A
 */

#घोषणा pr_fmt(fmt)	"ACPI: IORT: " fmt

#समावेश <linux/acpi_iort.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-map-ops.h>

#घोषणा IORT_TYPE_MASK(type)	(1 << (type))
#घोषणा IORT_MSI_TYPE		(1 << ACPI_IORT_NODE_ITS_GROUP)
#घोषणा IORT_IOMMU_TYPE		((1 << ACPI_IORT_NODE_SMMU) |	\
				(1 << ACPI_IORT_NODE_SMMU_V3))

काष्ठा iort_its_msi_chip अणु
	काष्ठा list_head	list;
	काष्ठा fwnode_handle	*fw_node;
	phys_addr_t		base_addr;
	u32			translation_id;
पूर्ण;

काष्ठा iort_fwnode अणु
	काष्ठा list_head list;
	काष्ठा acpi_iort_node *iort_node;
	काष्ठा fwnode_handle *fwnode;
पूर्ण;
अटल LIST_HEAD(iort_fwnode_list);
अटल DEFINE_SPINLOCK(iort_fwnode_lock);

/**
 * iort_set_fwnode() - Create iort_fwnode and use it to रेजिस्टर
 *		       iommu data in the iort_fwnode_list
 *
 * @iort_node: IORT table node associated with the IOMMU
 * @fwnode: fwnode associated with the IORT node
 *
 * Returns: 0 on success
 *          <0 on failure
 */
अटल अंतरभूत पूर्णांक iort_set_fwnode(काष्ठा acpi_iort_node *iort_node,
				  काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा iort_fwnode *np;

	np = kzalloc(माप(काष्ठा iort_fwnode), GFP_ATOMIC);

	अगर (WARN_ON(!np))
		वापस -ENOMEM;

	INIT_LIST_HEAD(&np->list);
	np->iort_node = iort_node;
	np->fwnode = fwnode;

	spin_lock(&iort_fwnode_lock);
	list_add_tail(&np->list, &iort_fwnode_list);
	spin_unlock(&iort_fwnode_lock);

	वापस 0;
पूर्ण

/**
 * iort_get_fwnode() - Retrieve fwnode associated with an IORT node
 *
 * @node: IORT table node to be looked-up
 *
 * Returns: fwnode_handle poपूर्णांकer on success, शून्य on failure
 */
अटल अंतरभूत काष्ठा fwnode_handle *iort_get_fwnode(
			काष्ठा acpi_iort_node *node)
अणु
	काष्ठा iort_fwnode *curr;
	काष्ठा fwnode_handle *fwnode = शून्य;

	spin_lock(&iort_fwnode_lock);
	list_क्रम_each_entry(curr, &iort_fwnode_list, list) अणु
		अगर (curr->iort_node == node) अणु
			fwnode = curr->fwnode;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_fwnode_lock);

	वापस fwnode;
पूर्ण

/**
 * iort_delete_fwnode() - Delete fwnode associated with an IORT node
 *
 * @node: IORT table node associated with fwnode to delete
 */
अटल अंतरभूत व्योम iort_delete_fwnode(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा iort_fwnode *curr, *पंचांगp;

	spin_lock(&iort_fwnode_lock);
	list_क्रम_each_entry_safe(curr, पंचांगp, &iort_fwnode_list, list) अणु
		अगर (curr->iort_node == node) अणु
			list_del(&curr->list);
			kमुक्त(curr);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_fwnode_lock);
पूर्ण

/**
 * iort_get_iort_node() - Retrieve iort_node associated with an fwnode
 *
 * @fwnode: fwnode associated with device to be looked-up
 *
 * Returns: iort_node poपूर्णांकer on success, शून्य on failure
 */
अटल अंतरभूत काष्ठा acpi_iort_node *iort_get_iort_node(
			काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा iort_fwnode *curr;
	काष्ठा acpi_iort_node *iort_node = शून्य;

	spin_lock(&iort_fwnode_lock);
	list_क्रम_each_entry(curr, &iort_fwnode_list, list) अणु
		अगर (curr->fwnode == fwnode) अणु
			iort_node = curr->iort_node;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_fwnode_lock);

	वापस iort_node;
पूर्ण

प्रकार acpi_status (*iort_find_node_callback)
	(काष्ठा acpi_iort_node *node, व्योम *context);

/* Root poपूर्णांकer to the mapped IORT table */
अटल काष्ठा acpi_table_header *iort_table;

अटल LIST_HEAD(iort_msi_chip_list);
अटल DEFINE_SPINLOCK(iort_msi_chip_lock);

/**
 * iort_रेजिस्टर_करोमुख्य_token() - रेजिस्टर करोमुख्य token aदीर्घ with related
 * ITS ID and base address to the list from where we can get it back later on.
 * @trans_id: ITS ID.
 * @base: ITS base address.
 * @fw_node: Doमुख्य token.
 *
 * Returns: 0 on success, -ENOMEM अगर no memory when allocating list element
 */
पूर्णांक iort_रेजिस्टर_करोमुख्य_token(पूर्णांक trans_id, phys_addr_t base,
			       काष्ठा fwnode_handle *fw_node)
अणु
	काष्ठा iort_its_msi_chip *its_msi_chip;

	its_msi_chip = kzalloc(माप(*its_msi_chip), GFP_KERNEL);
	अगर (!its_msi_chip)
		वापस -ENOMEM;

	its_msi_chip->fw_node = fw_node;
	its_msi_chip->translation_id = trans_id;
	its_msi_chip->base_addr = base;

	spin_lock(&iort_msi_chip_lock);
	list_add(&its_msi_chip->list, &iort_msi_chip_list);
	spin_unlock(&iort_msi_chip_lock);

	वापस 0;
पूर्ण

/**
 * iort_deरेजिस्टर_करोमुख्य_token() - Deरेजिस्टर करोमुख्य token based on ITS ID
 * @trans_id: ITS ID.
 *
 * Returns: none.
 */
व्योम iort_deरेजिस्टर_करोमुख्य_token(पूर्णांक trans_id)
अणु
	काष्ठा iort_its_msi_chip *its_msi_chip, *t;

	spin_lock(&iort_msi_chip_lock);
	list_क्रम_each_entry_safe(its_msi_chip, t, &iort_msi_chip_list, list) अणु
		अगर (its_msi_chip->translation_id == trans_id) अणु
			list_del(&its_msi_chip->list);
			kमुक्त(its_msi_chip);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_msi_chip_lock);
पूर्ण

/**
 * iort_find_करोमुख्य_token() - Find करोमुख्य token based on given ITS ID
 * @trans_id: ITS ID.
 *
 * Returns: करोमुख्य token when find on the list, शून्य otherwise
 */
काष्ठा fwnode_handle *iort_find_करोमुख्य_token(पूर्णांक trans_id)
अणु
	काष्ठा fwnode_handle *fw_node = शून्य;
	काष्ठा iort_its_msi_chip *its_msi_chip;

	spin_lock(&iort_msi_chip_lock);
	list_क्रम_each_entry(its_msi_chip, &iort_msi_chip_list, list) अणु
		अगर (its_msi_chip->translation_id == trans_id) अणु
			fw_node = its_msi_chip->fw_node;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_msi_chip_lock);

	वापस fw_node;
पूर्ण

अटल काष्ठा acpi_iort_node *iort_scan_node(क्रमागत acpi_iort_node_type type,
					     iort_find_node_callback callback,
					     व्योम *context)
अणु
	काष्ठा acpi_iort_node *iort_node, *iort_end;
	काष्ठा acpi_table_iort *iort;
	पूर्णांक i;

	अगर (!iort_table)
		वापस शून्य;

	/* Get the first IORT node */
	iort = (काष्ठा acpi_table_iort *)iort_table;
	iort_node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort,
				 iort->node_offset);
	iort_end = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_table,
				iort_table->length);

	क्रम (i = 0; i < iort->node_count; i++) अणु
		अगर (WARN_TAINT(iort_node >= iort_end, TAINT_FIRMWARE_WORKAROUND,
			       "IORT node pointer overflows, bad table!\n"))
			वापस शून्य;

		अगर (iort_node->type == type &&
		    ACPI_SUCCESS(callback(iort_node, context)))
			वापस iort_node;

		iort_node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_node,
					 iort_node->length);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल acpi_status iort_match_node_callback(काष्ठा acpi_iort_node *node,
					    व्योम *context)
अणु
	काष्ठा device *dev = context;
	acpi_status status = AE_NOT_FOUND;

	अगर (node->type == ACPI_IORT_NODE_NAMED_COMPONENT) अणु
		काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
		काष्ठा acpi_device *adev;
		काष्ठा acpi_iort_named_component *ncomp;
		काष्ठा device *nc_dev = dev;

		/*
		 * Walk the device tree to find a device with an
		 * ACPI companion; there is no poपूर्णांक in scanning
		 * IORT क्रम a device matching a named component अगर
		 * the device करोes not have an ACPI companion to
		 * start with.
		 */
		करो अणु
			adev = ACPI_COMPANION(nc_dev);
			अगर (adev)
				अवरोध;

			nc_dev = nc_dev->parent;
		पूर्ण जबतक (nc_dev);

		अगर (!adev)
			जाओ out;

		status = acpi_get_name(adev->handle, ACPI_FULL_PATHNAME, &buf);
		अगर (ACPI_FAILURE(status)) अणु
			dev_warn(nc_dev, "Can't get device full path name\n");
			जाओ out;
		पूर्ण

		ncomp = (काष्ठा acpi_iort_named_component *)node->node_data;
		status = !म_भेद(ncomp->device_name, buf.poपूर्णांकer) ?
							AE_OK : AE_NOT_FOUND;
		acpi_os_मुक्त(buf.poपूर्णांकer);
	पूर्ण अन्यथा अगर (node->type == ACPI_IORT_NODE_PCI_ROOT_COMPLEX) अणु
		काष्ठा acpi_iort_root_complex *pci_rc;
		काष्ठा pci_bus *bus;

		bus = to_pci_bus(dev);
		pci_rc = (काष्ठा acpi_iort_root_complex *)node->node_data;

		/*
		 * It is assumed that PCI segment numbers maps one-to-one
		 * with root complexes. Each segment number can represent only
		 * one root complex.
		 */
		status = pci_rc->pci_segment_number == pci_करोमुख्य_nr(bus) ?
							AE_OK : AE_NOT_FOUND;
	पूर्ण
out:
	वापस status;
पूर्ण

अटल पूर्णांक iort_id_map(काष्ठा acpi_iort_id_mapping *map, u8 type, u32 rid_in,
		       u32 *rid_out, bool check_overlap)
अणु
	/* Single mapping करोes not care क्रम input id */
	अगर (map->flags & ACPI_IORT_ID_SINGLE_MAPPING) अणु
		अगर (type == ACPI_IORT_NODE_NAMED_COMPONENT ||
		    type == ACPI_IORT_NODE_PCI_ROOT_COMPLEX) अणु
			*rid_out = map->output_base;
			वापस 0;
		पूर्ण

		pr_warn(FW_BUG "[map %p] SINGLE MAPPING flag not allowed for node type %d, skipping ID map\n",
			map, type);
		वापस -ENXIO;
	पूर्ण

	अगर (rid_in < map->input_base ||
	    (rid_in > map->input_base + map->id_count))
		वापस -ENXIO;

	अगर (check_overlap) अणु
		/*
		 * We alपढ़ोy found a mapping क्रम this input ID at the end of
		 * another region. If it coincides with the start of this
		 * region, we assume the prior match was due to the off-by-1
		 * issue mentioned below, and allow it to be superseded.
		 * Otherwise, things are *really* broken, and we just disregard
		 * duplicate matches entirely to retain compatibility.
		 */
		pr_err(FW_BUG "[map %p] conflicting mapping for input ID 0x%x\n",
		       map, rid_in);
		अगर (rid_in != map->input_base)
			वापस -ENXIO;

		pr_err(FW_BUG "applying workaround.\n");
	पूर्ण

	*rid_out = map->output_base + (rid_in - map->input_base);

	/*
	 * Due to confusion regarding the meaning of the id_count field (which
	 * carries the number of IDs *minus 1*), we may have to disregard this
	 * match अगर it is at the end of the range, and overlaps with the start
	 * of another one.
	 */
	अगर (map->id_count > 0 && rid_in == map->input_base + map->id_count)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

अटल काष्ठा acpi_iort_node *iort_node_get_id(काष्ठा acpi_iort_node *node,
					       u32 *id_out, पूर्णांक index)
अणु
	काष्ठा acpi_iort_node *parent;
	काष्ठा acpi_iort_id_mapping *map;

	अगर (!node->mapping_offset || !node->mapping_count ||
				     index >= node->mapping_count)
		वापस शून्य;

	map = ACPI_ADD_PTR(काष्ठा acpi_iort_id_mapping, node,
			   node->mapping_offset + index * माप(*map));

	/* Firmware bug! */
	अगर (!map->output_reference) अणु
		pr_err(FW_BUG "[node %p type %d] ID map has NULL parent reference\n",
		       node, node->type);
		वापस शून्य;
	पूर्ण

	parent = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_table,
			       map->output_reference);

	अगर (map->flags & ACPI_IORT_ID_SINGLE_MAPPING) अणु
		अगर (node->type == ACPI_IORT_NODE_NAMED_COMPONENT ||
		    node->type == ACPI_IORT_NODE_PCI_ROOT_COMPLEX ||
		    node->type == ACPI_IORT_NODE_SMMU_V3 ||
		    node->type == ACPI_IORT_NODE_PMCG) अणु
			*id_out = map->output_base;
			वापस parent;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक iort_get_id_mapping_index(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu_v3 *smmu;
	काष्ठा acpi_iort_pmcg *pmcg;

	चयन (node->type) अणु
	हाल ACPI_IORT_NODE_SMMU_V3:
		/*
		 * SMMUv3 dev ID mapping index was पूर्णांकroduced in revision 1
		 * table, not available in revision 0
		 */
		अगर (node->revision < 1)
			वापस -EINVAL;

		smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;
		/*
		 * ID mapping index is only ignored अगर all पूर्णांकerrupts are
		 * GSIV based
		 */
		अगर (smmu->event_gsiv && smmu->pri_gsiv && smmu->gerr_gsiv
		    && smmu->sync_gsiv)
			वापस -EINVAL;

		अगर (smmu->id_mapping_index >= node->mapping_count) अणु
			pr_err(FW_BUG "[node %p type %d] ID mapping index overflows valid mappings\n",
			       node, node->type);
			वापस -EINVAL;
		पूर्ण

		वापस smmu->id_mapping_index;
	हाल ACPI_IORT_NODE_PMCG:
		pmcg = (काष्ठा acpi_iort_pmcg *)node->node_data;
		अगर (pmcg->overflow_gsiv || node->mapping_count == 0)
			वापस -EINVAL;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा acpi_iort_node *iort_node_map_id(काष्ठा acpi_iort_node *node,
					       u32 id_in, u32 *id_out,
					       u8 type_mask)
अणु
	u32 id = id_in;

	/* Parse the ID mapping tree to find specअगरied node type */
	जबतक (node) अणु
		काष्ठा acpi_iort_id_mapping *map;
		पूर्णांक i, index, rc = 0;
		u32 out_ref = 0, map_id = id;

		अगर (IORT_TYPE_MASK(node->type) & type_mask) अणु
			अगर (id_out)
				*id_out = id;
			वापस node;
		पूर्ण

		अगर (!node->mapping_offset || !node->mapping_count)
			जाओ fail_map;

		map = ACPI_ADD_PTR(काष्ठा acpi_iort_id_mapping, node,
				   node->mapping_offset);

		/* Firmware bug! */
		अगर (!map->output_reference) अणु
			pr_err(FW_BUG "[node %p type %d] ID map has NULL parent reference\n",
			       node, node->type);
			जाओ fail_map;
		पूर्ण

		/*
		 * Get the special ID mapping index (अगर any) and skip its
		 * associated ID map to prevent erroneous multi-stage
		 * IORT ID translations.
		 */
		index = iort_get_id_mapping_index(node);

		/* Do the ID translation */
		क्रम (i = 0; i < node->mapping_count; i++, map++) अणु
			/* अगर it is special mapping index, skip it */
			अगर (i == index)
				जारी;

			rc = iort_id_map(map, node->type, map_id, &id, out_ref);
			अगर (!rc)
				अवरोध;
			अगर (rc == -EAGAIN)
				out_ref = map->output_reference;
		पूर्ण

		अगर (i == node->mapping_count && !out_ref)
			जाओ fail_map;

		node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_table,
				    rc ? out_ref : map->output_reference);
	पूर्ण

fail_map:
	/* Map input ID to output ID unchanged on mapping failure */
	अगर (id_out)
		*id_out = id_in;

	वापस शून्य;
पूर्ण

अटल काष्ठा acpi_iort_node *iort_node_map_platक्रमm_id(
		काष्ठा acpi_iort_node *node, u32 *id_out, u8 type_mask,
		पूर्णांक index)
अणु
	काष्ठा acpi_iort_node *parent;
	u32 id;

	/* step 1: retrieve the initial dev id */
	parent = iort_node_get_id(node, &id, index);
	अगर (!parent)
		वापस शून्य;

	/*
	 * optional step 2: map the initial dev id अगर its parent is not
	 * the target type we want, map it again क्रम the use हालs such
	 * as NC (named component) -> SMMU -> ITS. If the type is matched,
	 * वापस the initial dev id and its parent poपूर्णांकer directly.
	 */
	अगर (!(IORT_TYPE_MASK(parent->type) & type_mask))
		parent = iort_node_map_id(parent, id, id_out, type_mask);
	अन्यथा
		अगर (id_out)
			*id_out = id;

	वापस parent;
पूर्ण

अटल काष्ठा acpi_iort_node *iort_find_dev_node(काष्ठा device *dev)
अणु
	काष्ठा pci_bus *pbus;

	अगर (!dev_is_pci(dev)) अणु
		काष्ठा acpi_iort_node *node;
		/*
		 * scan iort_fwnode_list to see अगर it's an iort platक्रमm
		 * device (such as SMMU, PMCG),its iort node alपढ़ोy cached
		 * and associated with fwnode when iort platक्रमm devices
		 * were initialized.
		 */
		node = iort_get_iort_node(dev->fwnode);
		अगर (node)
			वापस node;
		/*
		 * अगर not, then it should be a platक्रमm device defined in
		 * DSDT/SSDT (with Named Component node in IORT)
		 */
		वापस iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
				      iort_match_node_callback, dev);
	पूर्ण

	pbus = to_pci_dev(dev)->bus;

	वापस iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
			      iort_match_node_callback, &pbus->dev);
पूर्ण

/**
 * iort_msi_map_id() - Map a MSI input ID क्रम a device
 * @dev: The device क्रम which the mapping is to be करोne.
 * @input_id: The device input ID.
 *
 * Returns: mapped MSI ID on success, input ID otherwise
 */
u32 iort_msi_map_id(काष्ठा device *dev, u32 input_id)
अणु
	काष्ठा acpi_iort_node *node;
	u32 dev_id;

	node = iort_find_dev_node(dev);
	अगर (!node)
		वापस input_id;

	iort_node_map_id(node, input_id, &dev_id, IORT_MSI_TYPE);
	वापस dev_id;
पूर्ण

/**
 * iort_pmsi_get_dev_id() - Get the device id क्रम a device
 * @dev: The device क्रम which the mapping is to be करोne.
 * @dev_id: The device ID found.
 *
 * Returns: 0 क्रम successful find a dev id, -ENODEV on error
 */
पूर्णांक iort_pmsi_get_dev_id(काष्ठा device *dev, u32 *dev_id)
अणु
	पूर्णांक i, index;
	काष्ठा acpi_iort_node *node;

	node = iort_find_dev_node(dev);
	अगर (!node)
		वापस -ENODEV;

	index = iort_get_id_mapping_index(node);
	/* अगर there is a valid index, go get the dev_id directly */
	अगर (index >= 0) अणु
		अगर (iort_node_get_id(node, dev_id, index))
			वापस 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < node->mapping_count; i++) अणु
			अगर (iort_node_map_platक्रमm_id(node, dev_id,
						      IORT_MSI_TYPE, i))
				वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक __maybe_unused iort_find_its_base(u32 its_id, phys_addr_t *base)
अणु
	काष्ठा iort_its_msi_chip *its_msi_chip;
	पूर्णांक ret = -ENODEV;

	spin_lock(&iort_msi_chip_lock);
	list_क्रम_each_entry(its_msi_chip, &iort_msi_chip_list, list) अणु
		अगर (its_msi_chip->translation_id == its_id) अणु
			*base = its_msi_chip->base_addr;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&iort_msi_chip_lock);

	वापस ret;
पूर्ण

/**
 * iort_dev_find_its_id() - Find the ITS identअगरier क्रम a device
 * @dev: The device.
 * @id: Device's ID
 * @idx: Index of the ITS identअगरier list.
 * @its_id: ITS identअगरier.
 *
 * Returns: 0 on success, appropriate error value otherwise
 */
अटल पूर्णांक iort_dev_find_its_id(काष्ठा device *dev, u32 id,
				अचिन्हित पूर्णांक idx, पूर्णांक *its_id)
अणु
	काष्ठा acpi_iort_its_group *its;
	काष्ठा acpi_iort_node *node;

	node = iort_find_dev_node(dev);
	अगर (!node)
		वापस -ENXIO;

	node = iort_node_map_id(node, id, शून्य, IORT_MSI_TYPE);
	अगर (!node)
		वापस -ENXIO;

	/* Move to ITS specअगरic data */
	its = (काष्ठा acpi_iort_its_group *)node->node_data;
	अगर (idx >= its->its_count) अणु
		dev_err(dev, "requested ITS ID index [%d] overruns ITS entries [%d]\n",
			idx, its->its_count);
		वापस -ENXIO;
	पूर्ण

	*its_id = its->identअगरiers[idx];
	वापस 0;
पूर्ण

/**
 * iort_get_device_करोमुख्य() - Find MSI करोमुख्य related to a device
 * @dev: The device.
 * @id: Requester ID क्रम the device.
 * @bus_token: irq करोमुख्य bus token.
 *
 * Returns: the MSI करोमुख्य क्रम this device, शून्य otherwise
 */
काष्ठा irq_करोमुख्य *iort_get_device_करोमुख्य(काष्ठा device *dev, u32 id,
					  क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	काष्ठा fwnode_handle *handle;
	पूर्णांक its_id;

	अगर (iort_dev_find_its_id(dev, id, 0, &its_id))
		वापस शून्य;

	handle = iort_find_करोमुख्य_token(its_id);
	अगर (!handle)
		वापस शून्य;

	वापस irq_find_matching_fwnode(handle, bus_token);
पूर्ण

अटल व्योम iort_set_device_करोमुख्य(काष्ठा device *dev,
				   काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_its_group *its;
	काष्ठा acpi_iort_node *msi_parent;
	काष्ठा acpi_iort_id_mapping *map;
	काष्ठा fwnode_handle *iort_fwnode;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	पूर्णांक index;

	index = iort_get_id_mapping_index(node);
	अगर (index < 0)
		वापस;

	map = ACPI_ADD_PTR(काष्ठा acpi_iort_id_mapping, node,
			   node->mapping_offset + index * माप(*map));

	/* Firmware bug! */
	अगर (!map->output_reference ||
	    !(map->flags & ACPI_IORT_ID_SINGLE_MAPPING)) अणु
		pr_err(FW_BUG "[node %p type %d] Invalid MSI mapping\n",
		       node, node->type);
		वापस;
	पूर्ण

	msi_parent = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_table,
				  map->output_reference);

	अगर (!msi_parent || msi_parent->type != ACPI_IORT_NODE_ITS_GROUP)
		वापस;

	/* Move to ITS specअगरic data */
	its = (काष्ठा acpi_iort_its_group *)msi_parent->node_data;

	iort_fwnode = iort_find_करोमुख्य_token(its->identअगरiers[0]);
	अगर (!iort_fwnode)
		वापस;

	करोमुख्य = irq_find_matching_fwnode(iort_fwnode, DOMAIN_BUS_PLATFORM_MSI);
	अगर (करोमुख्य)
		dev_set_msi_करोमुख्य(dev, करोमुख्य);
पूर्ण

/**
 * iort_get_platक्रमm_device_करोमुख्य() - Find MSI करोमुख्य related to a
 * platक्रमm device
 * @dev: the dev poपूर्णांकer associated with the platक्रमm device
 *
 * Returns: the MSI करोमुख्य क्रम this device, शून्य otherwise
 */
अटल काष्ठा irq_करोमुख्य *iort_get_platक्रमm_device_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा acpi_iort_node *node, *msi_parent = शून्य;
	काष्ठा fwnode_handle *iort_fwnode;
	काष्ठा acpi_iort_its_group *its;
	पूर्णांक i;

	/* find its associated iort node */
	node = iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
			      iort_match_node_callback, dev);
	अगर (!node)
		वापस शून्य;

	/* then find its msi parent node */
	क्रम (i = 0; i < node->mapping_count; i++) अणु
		msi_parent = iort_node_map_platक्रमm_id(node, शून्य,
						       IORT_MSI_TYPE, i);
		अगर (msi_parent)
			अवरोध;
	पूर्ण

	अगर (!msi_parent)
		वापस शून्य;

	/* Move to ITS specअगरic data */
	its = (काष्ठा acpi_iort_its_group *)msi_parent->node_data;

	iort_fwnode = iort_find_करोमुख्य_token(its->identअगरiers[0]);
	अगर (!iort_fwnode)
		वापस शून्य;

	वापस irq_find_matching_fwnode(iort_fwnode, DOMAIN_BUS_PLATFORM_MSI);
पूर्ण

व्योम acpi_configure_pmsi_करोमुख्य(काष्ठा device *dev)
अणु
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;

	msi_करोमुख्य = iort_get_platक्रमm_device_करोमुख्य(dev);
	अगर (msi_करोमुख्य)
		dev_set_msi_करोमुख्य(dev, msi_करोमुख्य);
पूर्ण

#अगर_घोषित CONFIG_IOMMU_API
अटल काष्ठा acpi_iort_node *iort_get_msi_resv_iommu(काष्ठा device *dev)
अणु
	काष्ठा acpi_iort_node *iommu;
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	iommu = iort_get_iort_node(fwspec->iommu_fwnode);

	अगर (iommu && (iommu->type == ACPI_IORT_NODE_SMMU_V3)) अणु
		काष्ठा acpi_iort_smmu_v3 *smmu;

		smmu = (काष्ठा acpi_iort_smmu_v3 *)iommu->node_data;
		अगर (smmu->model == ACPI_IORT_SMMU_V3_HISILICON_HI161X)
			वापस iommu;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा iommu_ops *iort_fwspec_iommu_ops(काष्ठा device *dev)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	वापस (fwspec && fwspec->ops) ? fwspec->ops : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक iort_add_device_replay(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;

	अगर (dev->bus && !device_iommu_mapped(dev))
		err = iommu_probe_device(dev);

	वापस err;
पूर्ण

/**
 * iort_iommu_msi_get_resv_regions - Reserved region driver helper
 * @dev: Device from iommu_get_resv_regions()
 * @head: Reserved region list from iommu_get_resv_regions()
 *
 * Returns: Number of msi reserved regions on success (0 अगर platक्रमm
 *          करोesn't require the reservation or no associated msi regions),
 *          appropriate error value otherwise. The ITS पूर्णांकerrupt translation
 *          spaces (ITS_base + SZ_64K, SZ_64K) associated with the device
 *          are the msi reserved regions.
 */
पूर्णांक iort_iommu_msi_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *head)
अणु
	काष्ठा iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);
	काष्ठा acpi_iort_its_group *its;
	काष्ठा acpi_iort_node *iommu_node, *its_node = शून्य;
	पूर्णांक i, resv = 0;

	iommu_node = iort_get_msi_resv_iommu(dev);
	अगर (!iommu_node)
		वापस 0;

	/*
	 * Current logic to reserve ITS regions relies on HW topologies
	 * where a given PCI or named component maps its IDs to only one
	 * ITS group; अगर a PCI or named component can map its IDs to
	 * dअगरferent ITS groups through IORT mappings this function has
	 * to be reworked to ensure we reserve regions क्रम all ITS groups
	 * a given PCI or named component may map IDs to.
	 */

	क्रम (i = 0; i < fwspec->num_ids; i++) अणु
		its_node = iort_node_map_id(iommu_node,
					fwspec->ids[i],
					शून्य, IORT_MSI_TYPE);
		अगर (its_node)
			अवरोध;
	पूर्ण

	अगर (!its_node)
		वापस 0;

	/* Move to ITS specअगरic data */
	its = (काष्ठा acpi_iort_its_group *)its_node->node_data;

	क्रम (i = 0; i < its->its_count; i++) अणु
		phys_addr_t base;

		अगर (!iort_find_its_base(its->identअगरiers[i], &base)) अणु
			पूर्णांक prot = IOMMU_WRITE | IOMMU_NOEXEC | IOMMU_MMIO;
			काष्ठा iommu_resv_region *region;

			region = iommu_alloc_resv_region(base + SZ_64K, SZ_64K,
							 prot, IOMMU_RESV_MSI);
			अगर (region) अणु
				list_add_tail(&region->list, head);
				resv++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (resv == its->its_count) ? resv : -ENODEV;
पूर्ण

अटल अंतरभूत bool iort_iommu_driver_enabled(u8 type)
अणु
	चयन (type) अणु
	हाल ACPI_IORT_NODE_SMMU_V3:
		वापस IS_ENABLED(CONFIG_ARM_SMMU_V3);
	हाल ACPI_IORT_NODE_SMMU:
		वापस IS_ENABLED(CONFIG_ARM_SMMU);
	शेष:
		pr_warn("IORT node type %u does not describe an SMMU\n", type);
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक arm_smmu_iort_xlate(काष्ठा device *dev, u32 streamid,
			       काष्ठा fwnode_handle *fwnode,
			       स्थिर काष्ठा iommu_ops *ops)
अणु
	पूर्णांक ret = iommu_fwspec_init(dev, fwnode, ops);

	अगर (!ret)
		ret = iommu_fwspec_add_ids(dev, &streamid, 1);

	वापस ret;
पूर्ण

अटल bool iort_pci_rc_supports_ats(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_root_complex *pci_rc;

	pci_rc = (काष्ठा acpi_iort_root_complex *)node->node_data;
	वापस pci_rc->ats_attribute & ACPI_IORT_ATS_SUPPORTED;
पूर्ण

अटल पूर्णांक iort_iommu_xlate(काष्ठा device *dev, काष्ठा acpi_iort_node *node,
			    u32 streamid)
अणु
	स्थिर काष्ठा iommu_ops *ops;
	काष्ठा fwnode_handle *iort_fwnode;

	अगर (!node)
		वापस -ENODEV;

	iort_fwnode = iort_get_fwnode(node);
	अगर (!iort_fwnode)
		वापस -ENODEV;

	/*
	 * If the ops look-up fails, this means that either
	 * the SMMU drivers have not been probed yet or that
	 * the SMMU drivers are not built in the kernel;
	 * Depending on whether the SMMU drivers are built-in
	 * in the kernel or not, defer the IOMMU configuration
	 * or just पात it.
	 */
	ops = iommu_ops_from_fwnode(iort_fwnode);
	अगर (!ops)
		वापस iort_iommu_driver_enabled(node->type) ?
		       -EPROBE_DEFER : -ENODEV;

	वापस arm_smmu_iort_xlate(dev, streamid, iort_fwnode, ops);
पूर्ण

काष्ठा iort_pci_alias_info अणु
	काष्ठा device *dev;
	काष्ठा acpi_iort_node *node;
पूर्ण;

अटल पूर्णांक iort_pci_iommu_init(काष्ठा pci_dev *pdev, u16 alias, व्योम *data)
अणु
	काष्ठा iort_pci_alias_info *info = data;
	काष्ठा acpi_iort_node *parent;
	u32 streamid;

	parent = iort_node_map_id(info->node, alias, &streamid,
				  IORT_IOMMU_TYPE);
	वापस iort_iommu_xlate(info->dev, parent, streamid);
पूर्ण

अटल व्योम iort_named_component_init(काष्ठा device *dev,
				      काष्ठा acpi_iort_node *node)
अणु
	काष्ठा property_entry props[2] = अणुपूर्ण;
	काष्ठा acpi_iort_named_component *nc;

	nc = (काष्ठा acpi_iort_named_component *)node->node_data;
	props[0] = PROPERTY_ENTRY_U32("pasid-num-bits",
				      FIELD_GET(ACPI_IORT_NC_PASID_BITS,
						nc->node_flags));

	अगर (device_add_properties(dev, props))
		dev_warn(dev, "Could not add device properties\n");
पूर्ण

अटल पूर्णांक iort_nc_iommu_map(काष्ठा device *dev, काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_node *parent;
	पूर्णांक err = -ENODEV, i = 0;
	u32 streamid = 0;

	करो अणु

		parent = iort_node_map_platक्रमm_id(node, &streamid,
						   IORT_IOMMU_TYPE,
						   i++);

		अगर (parent)
			err = iort_iommu_xlate(dev, parent, streamid);
	पूर्ण जबतक (parent && !err);

	वापस err;
पूर्ण

अटल पूर्णांक iort_nc_iommu_map_id(काष्ठा device *dev,
				काष्ठा acpi_iort_node *node,
				स्थिर u32 *in_id)
अणु
	काष्ठा acpi_iort_node *parent;
	u32 streamid;

	parent = iort_node_map_id(node, *in_id, &streamid, IORT_IOMMU_TYPE);
	अगर (parent)
		वापस iort_iommu_xlate(dev, parent, streamid);

	वापस -ENODEV;
पूर्ण


/**
 * iort_iommu_configure_id - Set-up IOMMU configuration क्रम a device.
 *
 * @dev: device to configure
 * @id_in: optional input id स्थिर value poपूर्णांकer
 *
 * Returns: iommu_ops poपूर्णांकer on configuration success
 *          शून्य on configuration failure
 */
स्थिर काष्ठा iommu_ops *iort_iommu_configure_id(काष्ठा device *dev,
						स्थिर u32 *id_in)
अणु
	काष्ठा acpi_iort_node *node;
	स्थिर काष्ठा iommu_ops *ops;
	पूर्णांक err = -ENODEV;

	/*
	 * If we alपढ़ोy translated the fwspec there
	 * is nothing left to करो, वापस the iommu_ops.
	 */
	ops = iort_fwspec_iommu_ops(dev);
	अगर (ops)
		वापस ops;

	अगर (dev_is_pci(dev)) अणु
		काष्ठा iommu_fwspec *fwspec;
		काष्ठा pci_bus *bus = to_pci_dev(dev)->bus;
		काष्ठा iort_pci_alias_info info = अणु .dev = dev पूर्ण;

		node = iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
				      iort_match_node_callback, &bus->dev);
		अगर (!node)
			वापस शून्य;

		info.node = node;
		err = pci_क्रम_each_dma_alias(to_pci_dev(dev),
					     iort_pci_iommu_init, &info);

		fwspec = dev_iommu_fwspec_get(dev);
		अगर (fwspec && iort_pci_rc_supports_ats(node))
			fwspec->flags |= IOMMU_FWSPEC_PCI_RC_ATS;
	पूर्ण अन्यथा अणु
		node = iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
				      iort_match_node_callback, dev);
		अगर (!node)
			वापस शून्य;

		err = id_in ? iort_nc_iommu_map_id(dev, node, id_in) :
			      iort_nc_iommu_map(dev, node);

		अगर (!err)
			iort_named_component_init(dev, node);
	पूर्ण

	/*
	 * If we have reason to believe the IOMMU driver missed the initial
	 * add_device callback क्रम dev, replay it to get things in order.
	 */
	अगर (!err) अणु
		ops = iort_fwspec_iommu_ops(dev);
		err = iort_add_device_replay(dev);
	पूर्ण

	/* Ignore all other errors apart from EPROBE_DEFER */
	अगर (err == -EPROBE_DEFER) अणु
		ops = ERR_PTR(err);
	पूर्ण अन्यथा अगर (err) अणु
		dev_dbg(dev, "Adding to IOMMU failed: %d\n", err);
		ops = शून्य;
	पूर्ण

	वापस ops;
पूर्ण

#अन्यथा
पूर्णांक iort_iommu_msi_get_resv_regions(काष्ठा device *dev, काष्ठा list_head *head)
अणु वापस 0; पूर्ण
स्थिर काष्ठा iommu_ops *iort_iommu_configure_id(काष्ठा device *dev,
						स्थिर u32 *input_id)
अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nc_dma_get_range(काष्ठा device *dev, u64 *size)
अणु
	काष्ठा acpi_iort_node *node;
	काष्ठा acpi_iort_named_component *ncomp;

	node = iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
			      iort_match_node_callback, dev);
	अगर (!node)
		वापस -ENODEV;

	ncomp = (काष्ठा acpi_iort_named_component *)node->node_data;

	अगर (!ncomp->memory_address_limit) अणु
		pr_warn(FW_BUG "Named component missing memory address limit\n");
		वापस -EINVAL;
	पूर्ण

	*size = ncomp->memory_address_limit >= 64 ? U64_MAX :
			1ULL<<ncomp->memory_address_limit;

	वापस 0;
पूर्ण

अटल पूर्णांक rc_dma_get_range(काष्ठा device *dev, u64 *size)
अणु
	काष्ठा acpi_iort_node *node;
	काष्ठा acpi_iort_root_complex *rc;
	काष्ठा pci_bus *pbus = to_pci_dev(dev)->bus;

	node = iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
			      iort_match_node_callback, &pbus->dev);
	अगर (!node || node->revision < 1)
		वापस -ENODEV;

	rc = (काष्ठा acpi_iort_root_complex *)node->node_data;

	अगर (!rc->memory_address_limit) अणु
		pr_warn(FW_BUG "Root complex missing memory address limit\n");
		वापस -EINVAL;
	पूर्ण

	*size = rc->memory_address_limit >= 64 ? U64_MAX :
			1ULL<<rc->memory_address_limit;

	वापस 0;
पूर्ण

/**
 * iort_dma_setup() - Set-up device DMA parameters.
 *
 * @dev: device to configure
 * @dma_addr: device DMA address result poपूर्णांकer
 * @dma_size: DMA range size result poपूर्णांकer
 */
व्योम iort_dma_setup(काष्ठा device *dev, u64 *dma_addr, u64 *dma_size)
अणु
	u64 end, mask, dmaaddr = 0, size = 0, offset = 0;
	पूर्णांक ret;

	/*
	 * If @dev is expected to be DMA-capable then the bus code that created
	 * it should have initialised its dma_mask poपूर्णांकer by this poपूर्णांक. For
	 * now, we'll जारी the legacy behaviour of coercing it to the
	 * coherent mask अगर not, but we'll no दीर्घer करो so quietly.
	 */
	अगर (!dev->dma_mask) अणु
		dev_warn(dev, "DMA mask not set\n");
		dev->dma_mask = &dev->coherent_dma_mask;
	पूर्ण

	अगर (dev->coherent_dma_mask)
		size = max(dev->coherent_dma_mask, dev->coherent_dma_mask + 1);
	अन्यथा
		size = 1ULL << 32;

	ret = acpi_dma_get_range(dev, &dmaaddr, &offset, &size);
	अगर (ret == -ENODEV)
		ret = dev_is_pci(dev) ? rc_dma_get_range(dev, &size)
				      : nc_dma_get_range(dev, &size);

	अगर (!ret) अणु
		/*
		 * Limit coherent and dma mask based on size retrieved from
		 * firmware.
		 */
		end = dmaaddr + size - 1;
		mask = DMA_BIT_MASK(ilog2(end) + 1);
		dev->bus_dma_limit = end;
		dev->coherent_dma_mask = min(dev->coherent_dma_mask, mask);
		*dev->dma_mask = min(*dev->dma_mask, mask);
	पूर्ण

	*dma_addr = dmaaddr;
	*dma_size = size;

	ret = dma_direct_set_offset(dev, dmaaddr + offset, dmaaddr, size);

	dev_dbg(dev, "dma_offset(%#08llx)%s\n", offset, ret ? " failed!" : "");
पूर्ण

अटल व्योम __init acpi_iort_रेजिस्टर_irq(पूर्णांक hwirq, स्थिर अक्षर *name,
					  पूर्णांक trigger,
					  काष्ठा resource *res)
अणु
	पूर्णांक irq = acpi_रेजिस्टर_gsi(शून्य, hwirq, trigger,
				    ACPI_ACTIVE_HIGH);

	अगर (irq <= 0) अणु
		pr_err("could not register gsi hwirq %d name [%s]\n", hwirq,
								      name);
		वापस;
	पूर्ण

	res->start = irq;
	res->end = irq;
	res->flags = IORESOURCE_IRQ;
	res->name = name;
पूर्ण

अटल पूर्णांक __init arm_smmu_v3_count_resources(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu_v3 *smmu;
	/* Always present mem resource */
	पूर्णांक num_res = 1;

	/* Retrieve SMMUv3 specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;

	अगर (smmu->event_gsiv)
		num_res++;

	अगर (smmu->pri_gsiv)
		num_res++;

	अगर (smmu->gerr_gsiv)
		num_res++;

	अगर (smmu->sync_gsiv)
		num_res++;

	वापस num_res;
पूर्ण

अटल bool arm_smmu_v3_is_combined_irq(काष्ठा acpi_iort_smmu_v3 *smmu)
अणु
	/*
	 * Cavium ThunderX2 implementation करोesn't not support unique
	 * irq line. Use single irq line क्रम all the SMMUv3 पूर्णांकerrupts.
	 */
	अगर (smmu->model != ACPI_IORT_SMMU_V3_CAVIUM_CN99XX)
		वापस false;

	/*
	 * ThunderX2 करोesn't support MSIs from the SMMU, so we're checking
	 * SPI numbers here.
	 */
	वापस smmu->event_gsiv == smmu->pri_gsiv &&
	       smmu->event_gsiv == smmu->gerr_gsiv &&
	       smmu->event_gsiv == smmu->sync_gsiv;
पूर्ण

अटल अचिन्हित दीर्घ arm_smmu_v3_resource_size(काष्ठा acpi_iort_smmu_v3 *smmu)
अणु
	/*
	 * Override the size, क्रम Cavium ThunderX2 implementation
	 * which करोesn't support the page 1 SMMU रेजिस्टर space.
	 */
	अगर (smmu->model == ACPI_IORT_SMMU_V3_CAVIUM_CN99XX)
		वापस SZ_64K;

	वापस SZ_128K;
पूर्ण

अटल व्योम __init arm_smmu_v3_init_resources(काष्ठा resource *res,
					      काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu_v3 *smmu;
	पूर्णांक num_res = 0;

	/* Retrieve SMMUv3 specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;

	res[num_res].start = smmu->base_address;
	res[num_res].end = smmu->base_address +
				arm_smmu_v3_resource_size(smmu) - 1;
	res[num_res].flags = IORESOURCE_MEM;

	num_res++;
	अगर (arm_smmu_v3_is_combined_irq(smmu)) अणु
		अगर (smmu->event_gsiv)
			acpi_iort_रेजिस्टर_irq(smmu->event_gsiv, "combined",
					       ACPI_EDGE_SENSITIVE,
					       &res[num_res++]);
	पूर्ण अन्यथा अणु

		अगर (smmu->event_gsiv)
			acpi_iort_रेजिस्टर_irq(smmu->event_gsiv, "eventq",
					       ACPI_EDGE_SENSITIVE,
					       &res[num_res++]);

		अगर (smmu->pri_gsiv)
			acpi_iort_रेजिस्टर_irq(smmu->pri_gsiv, "priq",
					       ACPI_EDGE_SENSITIVE,
					       &res[num_res++]);

		अगर (smmu->gerr_gsiv)
			acpi_iort_रेजिस्टर_irq(smmu->gerr_gsiv, "gerror",
					       ACPI_EDGE_SENSITIVE,
					       &res[num_res++]);

		अगर (smmu->sync_gsiv)
			acpi_iort_रेजिस्टर_irq(smmu->sync_gsiv, "cmdq-sync",
					       ACPI_EDGE_SENSITIVE,
					       &res[num_res++]);
	पूर्ण
पूर्ण

अटल व्योम __init arm_smmu_v3_dma_configure(काष्ठा device *dev,
					     काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu_v3 *smmu;
	क्रमागत dev_dma_attr attr;

	/* Retrieve SMMUv3 specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;

	attr = (smmu->flags & ACPI_IORT_SMMU_V3_COHACC_OVERRIDE) ?
			DEV_DMA_COHERENT : DEV_DMA_NON_COHERENT;

	/* We expect the dma masks to be equivalent क्रम all SMMUv3 set-ups */
	dev->dma_mask = &dev->coherent_dma_mask;

	/* Configure DMA क्रम the page table walker */
	acpi_dma_configure(dev, attr);
पूर्ण

#अगर defined(CONFIG_ACPI_NUMA)
/*
 * set numa proximity करोमुख्य क्रम smmuv3 device
 */
अटल पूर्णांक  __init arm_smmu_v3_set_proximity(काष्ठा device *dev,
					      काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu_v3 *smmu;

	smmu = (काष्ठा acpi_iort_smmu_v3 *)node->node_data;
	अगर (smmu->flags & ACPI_IORT_SMMU_V3_PXM_VALID) अणु
		पूर्णांक dev_node = pxm_to_node(smmu->pxm);

		अगर (dev_node != NUMA_NO_NODE && !node_online(dev_node))
			वापस -EINVAL;

		set_dev_node(dev, dev_node);
		pr_info("SMMU-v3[%llx] Mapped to Proximity domain %d\n",
			smmu->base_address,
			smmu->pxm);
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा arm_smmu_v3_set_proximity शून्य
#पूर्ण_अगर

अटल पूर्णांक __init arm_smmu_count_resources(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu *smmu;

	/* Retrieve SMMU specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu *)node->node_data;

	/*
	 * Only consider the global fault पूर्णांकerrupt and ignore the
	 * configuration access पूर्णांकerrupt.
	 *
	 * MMIO address and global fault पूर्णांकerrupt resources are always
	 * present so add them to the context पूर्णांकerrupt count as a अटल
	 * value.
	 */
	वापस smmu->context_पूर्णांकerrupt_count + 2;
पूर्ण

अटल व्योम __init arm_smmu_init_resources(काष्ठा resource *res,
					   काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu *smmu;
	पूर्णांक i, hw_irq, trigger, num_res = 0;
	u64 *ctx_irq, *glb_irq;

	/* Retrieve SMMU specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu *)node->node_data;

	res[num_res].start = smmu->base_address;
	res[num_res].end = smmu->base_address + smmu->span - 1;
	res[num_res].flags = IORESOURCE_MEM;
	num_res++;

	glb_irq = ACPI_ADD_PTR(u64, node, smmu->global_पूर्णांकerrupt_offset);
	/* Global IRQs */
	hw_irq = IORT_IRQ_MASK(glb_irq[0]);
	trigger = IORT_IRQ_TRIGGER_MASK(glb_irq[0]);

	acpi_iort_रेजिस्टर_irq(hw_irq, "arm-smmu-global", trigger,
				     &res[num_res++]);

	/* Context IRQs */
	ctx_irq = ACPI_ADD_PTR(u64, node, smmu->context_पूर्णांकerrupt_offset);
	क्रम (i = 0; i < smmu->context_पूर्णांकerrupt_count; i++) अणु
		hw_irq = IORT_IRQ_MASK(ctx_irq[i]);
		trigger = IORT_IRQ_TRIGGER_MASK(ctx_irq[i]);

		acpi_iort_रेजिस्टर_irq(hw_irq, "arm-smmu-context", trigger,
				       &res[num_res++]);
	पूर्ण
पूर्ण

अटल व्योम __init arm_smmu_dma_configure(काष्ठा device *dev,
					  काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_smmu *smmu;
	क्रमागत dev_dma_attr attr;

	/* Retrieve SMMU specअगरic data */
	smmu = (काष्ठा acpi_iort_smmu *)node->node_data;

	attr = (smmu->flags & ACPI_IORT_SMMU_COHERENT_WALK) ?
			DEV_DMA_COHERENT : DEV_DMA_NON_COHERENT;

	/* We expect the dma masks to be equivalent क्रम SMMU set-ups */
	dev->dma_mask = &dev->coherent_dma_mask;

	/* Configure DMA क्रम the page table walker */
	acpi_dma_configure(dev, attr);
पूर्ण

अटल पूर्णांक __init arm_smmu_v3_pmcg_count_resources(काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_pmcg *pmcg;

	/* Retrieve PMCG specअगरic data */
	pmcg = (काष्ठा acpi_iort_pmcg *)node->node_data;

	/*
	 * There are always 2 memory resources.
	 * If the overflow_gsiv is present then add that क्रम a total of 3.
	 */
	वापस pmcg->overflow_gsiv ? 3 : 2;
पूर्ण

अटल व्योम __init arm_smmu_v3_pmcg_init_resources(काष्ठा resource *res,
						   काष्ठा acpi_iort_node *node)
अणु
	काष्ठा acpi_iort_pmcg *pmcg;

	/* Retrieve PMCG specअगरic data */
	pmcg = (काष्ठा acpi_iort_pmcg *)node->node_data;

	res[0].start = pmcg->page0_base_address;
	res[0].end = pmcg->page0_base_address + SZ_4K - 1;
	res[0].flags = IORESOURCE_MEM;
	res[1].start = pmcg->page1_base_address;
	res[1].end = pmcg->page1_base_address + SZ_4K - 1;
	res[1].flags = IORESOURCE_MEM;

	अगर (pmcg->overflow_gsiv)
		acpi_iort_रेजिस्टर_irq(pmcg->overflow_gsiv, "overflow",
				       ACPI_EDGE_SENSITIVE, &res[2]);
पूर्ण

अटल काष्ठा acpi_platक्रमm_list pmcg_plat_info[] __initdata = अणु
	/* HiSilicon Hip08 Platक्रमm */
	अणु"HISI  ", "HIP08   ", 0, ACPI_SIG_IORT, greater_than_or_equal,
	 "Erratum #162001800", IORT_SMMU_V3_PMCG_HISI_HIP08पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक __init arm_smmu_v3_pmcg_add_platdata(काष्ठा platक्रमm_device *pdev)
अणु
	u32 model;
	पूर्णांक idx;

	idx = acpi_match_platक्रमm_list(pmcg_plat_info);
	अगर (idx >= 0)
		model = pmcg_plat_info[idx].data;
	अन्यथा
		model = IORT_SMMU_V3_PMCG_GENERIC;

	वापस platक्रमm_device_add_data(pdev, &model, माप(model));
पूर्ण

काष्ठा iort_dev_config अणु
	स्थिर अक्षर *name;
	पूर्णांक (*dev_init)(काष्ठा acpi_iort_node *node);
	व्योम (*dev_dma_configure)(काष्ठा device *dev,
				  काष्ठा acpi_iort_node *node);
	पूर्णांक (*dev_count_resources)(काष्ठा acpi_iort_node *node);
	व्योम (*dev_init_resources)(काष्ठा resource *res,
				     काष्ठा acpi_iort_node *node);
	पूर्णांक (*dev_set_proximity)(काष्ठा device *dev,
				    काष्ठा acpi_iort_node *node);
	पूर्णांक (*dev_add_platdata)(काष्ठा platक्रमm_device *pdev);
पूर्ण;

अटल स्थिर काष्ठा iort_dev_config iort_arm_smmu_v3_cfg __initस्थिर = अणु
	.name = "arm-smmu-v3",
	.dev_dma_configure = arm_smmu_v3_dma_configure,
	.dev_count_resources = arm_smmu_v3_count_resources,
	.dev_init_resources = arm_smmu_v3_init_resources,
	.dev_set_proximity = arm_smmu_v3_set_proximity,
पूर्ण;

अटल स्थिर काष्ठा iort_dev_config iort_arm_smmu_cfg __initस्थिर = अणु
	.name = "arm-smmu",
	.dev_dma_configure = arm_smmu_dma_configure,
	.dev_count_resources = arm_smmu_count_resources,
	.dev_init_resources = arm_smmu_init_resources,
पूर्ण;

अटल स्थिर काष्ठा iort_dev_config iort_arm_smmu_v3_pmcg_cfg __initस्थिर = अणु
	.name = "arm-smmu-v3-pmcg",
	.dev_count_resources = arm_smmu_v3_pmcg_count_resources,
	.dev_init_resources = arm_smmu_v3_pmcg_init_resources,
	.dev_add_platdata = arm_smmu_v3_pmcg_add_platdata,
पूर्ण;

अटल __init स्थिर काष्ठा iort_dev_config *iort_get_dev_cfg(
			काष्ठा acpi_iort_node *node)
अणु
	चयन (node->type) अणु
	हाल ACPI_IORT_NODE_SMMU_V3:
		वापस &iort_arm_smmu_v3_cfg;
	हाल ACPI_IORT_NODE_SMMU:
		वापस &iort_arm_smmu_cfg;
	हाल ACPI_IORT_NODE_PMCG:
		वापस &iort_arm_smmu_v3_pmcg_cfg;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * iort_add_platक्रमm_device() - Allocate a platक्रमm device क्रम IORT node
 * @node: Poपूर्णांकer to device ACPI IORT node
 * @ops: Poपूर्णांकer to IORT device config काष्ठा
 *
 * Returns: 0 on success, <0 failure
 */
अटल पूर्णांक __init iort_add_platक्रमm_device(काष्ठा acpi_iort_node *node,
					   स्थिर काष्ठा iort_dev_config *ops)
अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा resource *r;
	पूर्णांक ret, count;

	pdev = platक्रमm_device_alloc(ops->name, PLATFORM_DEVID_AUTO);
	अगर (!pdev)
		वापस -ENOMEM;

	अगर (ops->dev_set_proximity) अणु
		ret = ops->dev_set_proximity(&pdev->dev, node);
		अगर (ret)
			जाओ dev_put;
	पूर्ण

	count = ops->dev_count_resources(node);

	r = kसुस्मृति(count, माप(*r), GFP_KERNEL);
	अगर (!r) अणु
		ret = -ENOMEM;
		जाओ dev_put;
	पूर्ण

	ops->dev_init_resources(r, node);

	ret = platक्रमm_device_add_resources(pdev, r, count);
	/*
	 * Resources are duplicated in platक्रमm_device_add_resources,
	 * मुक्त their allocated memory
	 */
	kमुक्त(r);

	अगर (ret)
		जाओ dev_put;

	/*
	 * Platक्रमm devices based on PMCG nodes uses platक्रमm_data to
	 * pass the hardware model info to the driver. For others, add
	 * a copy of IORT node poपूर्णांकer to platक्रमm_data to be used to
	 * retrieve IORT data inक्रमmation.
	 */
	अगर (ops->dev_add_platdata)
		ret = ops->dev_add_platdata(pdev);
	अन्यथा
		ret = platक्रमm_device_add_data(pdev, &node, माप(node));

	अगर (ret)
		जाओ dev_put;

	fwnode = iort_get_fwnode(node);

	अगर (!fwnode) अणु
		ret = -ENODEV;
		जाओ dev_put;
	पूर्ण

	pdev->dev.fwnode = fwnode;

	अगर (ops->dev_dma_configure)
		ops->dev_dma_configure(&pdev->dev, node);

	iort_set_device_करोमुख्य(&pdev->dev, node);

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ dma_deconfigure;

	वापस 0;

dma_deconfigure:
	arch_tearकरोwn_dma_ops(&pdev->dev);
dev_put:
	platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PCI
अटल व्योम __init iort_enable_acs(काष्ठा acpi_iort_node *iort_node)
अणु
	अटल bool acs_enabled __initdata;

	अगर (acs_enabled)
		वापस;

	अगर (iort_node->type == ACPI_IORT_NODE_PCI_ROOT_COMPLEX) अणु
		काष्ठा acpi_iort_node *parent;
		काष्ठा acpi_iort_id_mapping *map;
		पूर्णांक i;

		map = ACPI_ADD_PTR(काष्ठा acpi_iort_id_mapping, iort_node,
				   iort_node->mapping_offset);

		क्रम (i = 0; i < iort_node->mapping_count; i++, map++) अणु
			अगर (!map->output_reference)
				जारी;

			parent = ACPI_ADD_PTR(काष्ठा acpi_iort_node,
					iort_table,  map->output_reference);
			/*
			 * If we detect a RC->SMMU mapping, make sure
			 * we enable ACS on the प्रणाली.
			 */
			अगर ((parent->type == ACPI_IORT_NODE_SMMU) ||
				(parent->type == ACPI_IORT_NODE_SMMU_V3)) अणु
				pci_request_acs();
				acs_enabled = true;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम iort_enable_acs(काष्ठा acpi_iort_node *iort_node) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम __init iort_init_platक्रमm_devices(व्योम)
अणु
	काष्ठा acpi_iort_node *iort_node, *iort_end;
	काष्ठा acpi_table_iort *iort;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक i, ret;
	स्थिर काष्ठा iort_dev_config *ops;

	/*
	 * iort_table and iort both poपूर्णांक to the start of IORT table, but
	 * have dअगरferent काष्ठा types
	 */
	iort = (काष्ठा acpi_table_iort *)iort_table;

	/* Get the first IORT node */
	iort_node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort,
				 iort->node_offset);
	iort_end = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort,
				iort_table->length);

	क्रम (i = 0; i < iort->node_count; i++) अणु
		अगर (iort_node >= iort_end) अणु
			pr_err("iort node pointer overflows, bad table\n");
			वापस;
		पूर्ण

		iort_enable_acs(iort_node);

		ops = iort_get_dev_cfg(iort_node);
		अगर (ops) अणु
			fwnode = acpi_alloc_fwnode_अटल();
			अगर (!fwnode)
				वापस;

			iort_set_fwnode(iort_node, fwnode);

			ret = iort_add_platक्रमm_device(iort_node, ops);
			अगर (ret) अणु
				iort_delete_fwnode(iort_node);
				acpi_मुक्त_fwnode_अटल(fwnode);
				वापस;
			पूर्ण
		पूर्ण

		iort_node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort_node,
					 iort_node->length);
	पूर्ण
पूर्ण

व्योम __init acpi_iort_init(व्योम)
अणु
	acpi_status status;

	/* iort_table will be used at runसमय after the iort init,
	 * so we करोn't need to call acpi_put_table() to release
	 * the IORT table mapping.
	 */
	status = acpi_get_table(ACPI_SIG_IORT, 0, &iort_table);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND) अणु
			स्थिर अक्षर *msg = acpi_क्रमmat_exception(status);

			pr_err("Failed to get table, %s\n", msg);
		पूर्ण

		वापस;
	पूर्ण

	iort_init_platक्रमm_devices();
पूर्ण

#अगर_घोषित CONFIG_ZONE_DMA
/*
 * Extract the highest CPU physical address accessible to all DMA masters in
 * the प्रणाली. PHYS_ADDR_MAX is वापसed when no स्थिरrained device is found.
 */
phys_addr_t __init acpi_iort_dma_get_max_cpu_address(व्योम)
अणु
	phys_addr_t limit = PHYS_ADDR_MAX;
	काष्ठा acpi_iort_node *node, *end;
	काष्ठा acpi_table_iort *iort;
	acpi_status status;
	पूर्णांक i;

	अगर (acpi_disabled)
		वापस limit;

	status = acpi_get_table(ACPI_SIG_IORT, 0,
				(काष्ठा acpi_table_header **)&iort);
	अगर (ACPI_FAILURE(status))
		वापस limit;

	node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort, iort->node_offset);
	end = ACPI_ADD_PTR(काष्ठा acpi_iort_node, iort, iort->header.length);

	क्रम (i = 0; i < iort->node_count; i++) अणु
		अगर (node >= end)
			अवरोध;

		चयन (node->type) अणु
			काष्ठा acpi_iort_named_component *ncomp;
			काष्ठा acpi_iort_root_complex *rc;
			phys_addr_t local_limit;

		हाल ACPI_IORT_NODE_NAMED_COMPONENT:
			ncomp = (काष्ठा acpi_iort_named_component *)node->node_data;
			local_limit = DMA_BIT_MASK(ncomp->memory_address_limit);
			limit = min_not_zero(limit, local_limit);
			अवरोध;

		हाल ACPI_IORT_NODE_PCI_ROOT_COMPLEX:
			अगर (node->revision < 1)
				अवरोध;

			rc = (काष्ठा acpi_iort_root_complex *)node->node_data;
			local_limit = DMA_BIT_MASK(rc->memory_address_limit);
			limit = min_not_zero(limit, local_limit);
			अवरोध;
		पूर्ण
		node = ACPI_ADD_PTR(काष्ठा acpi_iort_node, node, node->length);
	पूर्ण
	acpi_put_table(&iort->header);
	वापस limit;
पूर्ण
#पूर्ण_अगर
