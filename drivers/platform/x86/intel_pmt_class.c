<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Platक्रमm Monitory Technology Telemetry driver
 *
 * Copyright (c) 2020, Intel Corporation.
 * All Rights Reserved.
 *
 * Author: "Alexander Duyck" <alexander.h.duyck@linux.पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>

#समावेश "intel_pmt_class.h"

#घोषणा PMT_XA_START		0
#घोषणा PMT_XA_MAX		पूर्णांक_उच्च
#घोषणा PMT_XA_LIMIT		XA_LIMIT(PMT_XA_START, PMT_XA_MAX)

/*
 * Early implementations of PMT on client platक्रमms have some
 * dअगरferences from the server platक्रमms (which use the Out Of Band
 * Management Services Module OOBMSM). This list tracks those
 * platक्रमms as needed to handle those dअगरferences. Newer client
 * platक्रमms are expected to be fully compatible with server.
 */
अटल स्थिर काष्ठा pci_device_id pmt_telem_early_client_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x467d) पूर्ण, /* ADL */
	अणु PCI_VDEVICE(INTEL, 0x490e) पूर्ण, /* DG1 */
	अणु PCI_VDEVICE(INTEL, 0x9a0d) पूर्ण, /* TGL */
	अणु पूर्ण
पूर्ण;

bool पूर्णांकel_pmt_is_early_client_hw(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *parent = to_pci_dev(dev->parent);

	वापस !!pci_match_id(pmt_telem_early_client_pci_ids, parent);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmt_is_early_client_hw);

/*
 * sysfs
 */
अटल sमाप_प्रकार
पूर्णांकel_pmt_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
	       काष्ठा bin_attribute *attr, अक्षर *buf, loff_t off,
	       माप_प्रकार count)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = container_of(attr,
						     काष्ठा पूर्णांकel_pmt_entry,
						     pmt_bin_attr);

	अगर (off < 0)
		वापस -EINVAL;

	अगर (off >= entry->size)
		वापस 0;

	अगर (count > entry->size - off)
		count = entry->size - off;

	स_नकल_fromio(buf, entry->base + off, count);

	वापस count;
पूर्ण

अटल पूर्णांक
पूर्णांकel_pmt_mmap(काष्ठा file *filp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = container_of(attr,
						     काष्ठा पूर्णांकel_pmt_entry,
						     pmt_bin_attr);
	अचिन्हित दीर्घ vsize = vma->vm_end - vma->vm_start;
	काष्ठा device *dev = kobj_to_dev(kobj);
	अचिन्हित दीर्घ phys = entry->base_addr;
	अचिन्हित दीर्घ pfn = PFN_DOWN(phys);
	अचिन्हित दीर्घ psize;

	अगर (vma->vm_flags & (VM_WRITE | VM_MAYWRITE))
		वापस -EROFS;

	psize = (PFN_UP(entry->base_addr + entry->size) - pfn) * PAGE_SIZE;
	अगर (vsize > psize) अणु
		dev_err(dev, "Requested mmap size is too large\n");
		वापस -EINVAL;
	पूर्ण

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	अगर (io_remap_pfn_range(vma, vma->vm_start, pfn,
		vsize, vma->vm_page_prot))
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
guid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "0x%x\n", entry->guid);
पूर्ण
अटल DEVICE_ATTR_RO(guid);

अटल sमाप_प्रकार size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%zu\n", entry->size);
पूर्ण
अटल DEVICE_ATTR_RO(size);

अटल sमाप_प्रकार
offset_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_pmt_entry *entry = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%lu\n", offset_in_page(entry->base_addr));
पूर्ण
अटल DEVICE_ATTR_RO(offset);

अटल काष्ठा attribute *पूर्णांकel_pmt_attrs[] = अणु
	&dev_attr_guid.attr,
	&dev_attr_size.attr,
	&dev_attr_offset.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(पूर्णांकel_pmt);

अटल काष्ठा class पूर्णांकel_pmt_class = अणु
	.name = "intel_pmt",
	.owner = THIS_MODULE,
	.dev_groups = पूर्णांकel_pmt_groups,
पूर्ण;

अटल पूर्णांक पूर्णांकel_pmt_populate_entry(काष्ठा पूर्णांकel_pmt_entry *entry,
				    काष्ठा पूर्णांकel_pmt_header *header,
				    काष्ठा device *dev,
				    काष्ठा resource *disc_res)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev->parent);
	u8 bir;

	/*
	 * The base offset should always be 8 byte aligned.
	 *
	 * For non-local access types the lower 3 bits of base offset
	 * contains the index of the base address रेजिस्टर where the
	 * telemetry can be found.
	 */
	bir = GET_BIR(header->base_offset);

	/* Local access and BARID only क्रम now */
	चयन (header->access_type) अणु
	हाल ACCESS_LOCAL:
		अगर (bir) अणु
			dev_err(dev,
				"Unsupported BAR index %d for access type %d\n",
				bir, header->access_type);
			वापस -EINVAL;
		पूर्ण
		/*
		 * For access_type LOCAL, the base address is as follows:
		 * base address = end of discovery region + base offset
		 */
		entry->base_addr = disc_res->end + 1 + header->base_offset;

		/*
		 * Some hardware use a dअगरferent calculation क्रम the base address
		 * when access_type == ACCESS_LOCAL. On the these प्रणालीs
		 * ACCCESS_LOCAL refers to an address in the same BAR as the
		 * header but at a fixed offset. But as the header address was
		 * supplied to the driver, we करोn't know which BAR it was in.
		 * So search क्रम the bar whose range includes the header address.
		 */
		अगर (पूर्णांकel_pmt_is_early_client_hw(dev)) अणु
			पूर्णांक i;

			entry->base_addr = 0;
			क्रम (i = 0; i < 6; i++)
				अगर (disc_res->start >= pci_resource_start(pci_dev, i) &&
				   (disc_res->start <= pci_resource_end(pci_dev, i))) अणु
					entry->base_addr = pci_resource_start(pci_dev, i) +
							   header->base_offset;
					अवरोध;
				पूर्ण
			अगर (!entry->base_addr)
				वापस -EINVAL;
		पूर्ण

		अवरोध;
	हाल ACCESS_BARID:
		/*
		 * If another BAR was specअगरied then the base offset
		 * represents the offset within that BAR. SO retrieve the
		 * address from the parent PCI device and add offset.
		 */
		entry->base_addr = pci_resource_start(pci_dev, bir) +
				   GET_ADDRESS(header->base_offset);
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported access type %d\n",
			header->access_type);
		वापस -EINVAL;
	पूर्ण

	entry->guid = header->guid;
	entry->size = header->size;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pmt_dev_रेजिस्टर(काष्ठा पूर्णांकel_pmt_entry *entry,
				  काष्ठा पूर्णांकel_pmt_namespace *ns,
				  काष्ठा device *parent)
अणु
	काष्ठा resource res = अणु0पूर्ण;
	काष्ठा device *dev;
	पूर्णांक ret;

	ret = xa_alloc(ns->xa, &entry->devid, entry, PMT_XA_LIMIT, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	dev = device_create(&पूर्णांकel_pmt_class, parent, MKDEV(0, 0), entry,
			    "%s%d", ns->name, entry->devid);

	अगर (IS_ERR(dev)) अणु
		dev_err(parent, "Could not create %s%d device node\n",
			ns->name, entry->devid);
		ret = PTR_ERR(dev);
		जाओ fail_dev_create;
	पूर्ण

	entry->kobj = &dev->kobj;

	अगर (ns->attr_grp) अणु
		ret = sysfs_create_group(entry->kobj, ns->attr_grp);
		अगर (ret)
			जाओ fail_sysfs;
	पूर्ण

	/* अगर size is 0 assume no data buffer, so no file needed */
	अगर (!entry->size)
		वापस 0;

	res.start = entry->base_addr;
	res.end = res.start + entry->size - 1;
	res.flags = IORESOURCE_MEM;

	entry->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(entry->base)) अणु
		ret = PTR_ERR(entry->base);
		जाओ fail_ioremap;
	पूर्ण

	sysfs_bin_attr_init(&entry->pmt_bin_attr);
	entry->pmt_bin_attr.attr.name = ns->name;
	entry->pmt_bin_attr.attr.mode = 0440;
	entry->pmt_bin_attr.mmap = पूर्णांकel_pmt_mmap;
	entry->pmt_bin_attr.पढ़ो = पूर्णांकel_pmt_पढ़ो;
	entry->pmt_bin_attr.size = entry->size;

	ret = sysfs_create_bin_file(&dev->kobj, &entry->pmt_bin_attr);
	अगर (!ret)
		वापस 0;

fail_ioremap:
	अगर (ns->attr_grp)
		sysfs_हटाओ_group(entry->kobj, ns->attr_grp);
fail_sysfs:
	device_unरेजिस्टर(dev);
fail_dev_create:
	xa_erase(ns->xa, entry->devid);

	वापस ret;
पूर्ण

पूर्णांक पूर्णांकel_pmt_dev_create(काष्ठा पूर्णांकel_pmt_entry *entry,
			 काष्ठा पूर्णांकel_pmt_namespace *ns,
			 काष्ठा platक्रमm_device *pdev, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_pmt_header header;
	काष्ठा resource	*disc_res;
	पूर्णांक ret = -ENODEV;

	disc_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, idx);
	अगर (!disc_res)
		वापस ret;

	entry->disc_table = devm_platक्रमm_ioremap_resource(pdev, idx);
	अगर (IS_ERR(entry->disc_table))
		वापस PTR_ERR(entry->disc_table);

	ret = ns->pmt_header_decode(entry, &header, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_pmt_populate_entry(entry, &header, &pdev->dev, disc_res);
	अगर (ret)
		वापस ret;

	वापस पूर्णांकel_pmt_dev_रेजिस्टर(entry, ns, &pdev->dev);

पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmt_dev_create);

व्योम पूर्णांकel_pmt_dev_destroy(काष्ठा पूर्णांकel_pmt_entry *entry,
			   काष्ठा पूर्णांकel_pmt_namespace *ns)
अणु
	काष्ठा device *dev = kobj_to_dev(entry->kobj);

	अगर (entry->size)
		sysfs_हटाओ_bin_file(entry->kobj, &entry->pmt_bin_attr);

	अगर (ns->attr_grp)
		sysfs_हटाओ_group(entry->kobj, ns->attr_grp);

	device_unरेजिस्टर(dev);
	xa_erase(ns->xa, entry->devid);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pmt_dev_destroy);

अटल पूर्णांक __init pmt_class_init(व्योम)
अणु
	वापस class_रेजिस्टर(&पूर्णांकel_pmt_class);
पूर्ण

अटल व्योम __निकास pmt_class_निकास(व्योम)
अणु
	class_unरेजिस्टर(&पूर्णांकel_pmt_class);
पूर्ण

module_init(pmt_class_init);
module_निकास(pmt_class_निकास);

MODULE_AUTHOR("Alexander Duyck <alexander.h.duyck@linux.intel.com>");
MODULE_DESCRIPTION("Intel PMT Class driver");
MODULE_LICENSE("GPL v2");
