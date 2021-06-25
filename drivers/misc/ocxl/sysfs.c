<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2017 IBM Corp.
#समावेश <linux/sysfs.h>
#समावेश "ocxl_internal.h"

अटल अंतरभूत काष्ठा ocxl_afu *to_afu(काष्ठा device *device)
अणु
	काष्ठा ocxl_file_info *info = container_of(device, काष्ठा ocxl_file_info, dev);

	वापस info->afu;
पूर्ण

अटल sमाप_प्रकार global_mmio_size_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			afu->config.global_mmio_size);
पूर्ण

अटल sमाप_प्रकार pp_mmio_size_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n",
			afu->config.pp_mmio_stride);
पूर्ण

अटल sमाप_प्रकार afu_version_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%hhu:%hhu\n",
			afu->config.version_major,
			afu->config.version_minor);
पूर्ण

अटल sमाप_प्रकार contexts_show(काष्ठा device *device,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d/%d\n",
			afu->pasid_count, afu->pasid_max);
पूर्ण

अटल sमाप_प्रकार reload_on_reset_show(काष्ठा device *device,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);
	काष्ठा ocxl_fn *fn = afu->fn;
	काष्ठा pci_dev *pci_dev = to_pci_dev(fn->dev.parent);
	पूर्णांक val;

	अगर (ocxl_config_get_reset_reload(pci_dev, &val))
		वापस scnम_लिखो(buf, PAGE_SIZE, "unavailable\n");

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार reload_on_reset_store(काष्ठा device *device,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ocxl_afu *afu = to_afu(device);
	काष्ठा ocxl_fn *fn = afu->fn;
	काष्ठा pci_dev *pci_dev = to_pci_dev(fn->dev.parent);
	पूर्णांक rc, val;

	rc = kstrtoपूर्णांक(buf, 0, &val);
	अगर (rc || (val != 0 && val != 1))
		वापस -EINVAL;

	अगर (ocxl_config_set_reset_reload(pci_dev, val))
		वापस -ENODEV;

	वापस count;
पूर्ण

अटल काष्ठा device_attribute afu_attrs[] = अणु
	__ATTR_RO(global_mmio_size),
	__ATTR_RO(pp_mmio_size),
	__ATTR_RO(afu_version),
	__ATTR_RO(contexts),
	__ATTR_RW(reload_on_reset),
पूर्ण;

अटल sमाप_प्रकार global_mmio_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr, अक्षर *buf,
				loff_t off, माप_प्रकार count)
अणु
	काष्ठा ocxl_afu *afu = to_afu(kobj_to_dev(kobj));

	अगर (count == 0 || off < 0 ||
		off >= afu->config.global_mmio_size)
		वापस 0;
	स_नकल_fromio(buf, afu->global_mmio_ptr + off, count);
	वापस count;
पूर्ण

अटल vm_fault_t global_mmio_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा ocxl_afu *afu = vma->vm_निजी_data;
	अचिन्हित दीर्घ offset;

	अगर (vmf->pgoff >= (afu->config.global_mmio_size >> PAGE_SHIFT))
		वापस VM_FAULT_SIGBUS;

	offset = vmf->pgoff;
	offset += (afu->global_mmio_start >> PAGE_SHIFT);
	वापस vmf_insert_pfn(vma, vmf->address, offset);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा global_mmio_vmops = अणु
	.fault = global_mmio_fault,
पूर्ण;

अटल पूर्णांक global_mmio_mmap(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा ocxl_afu *afu = to_afu(kobj_to_dev(kobj));

	अगर ((vma_pages(vma) + vma->vm_pgoff) >
		(afu->config.global_mmio_size >> PAGE_SHIFT))
		वापस -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &global_mmio_vmops;
	vma->vm_निजी_data = afu;
	वापस 0;
पूर्ण

पूर्णांक ocxl_sysfs_रेजिस्टर_afu(काष्ठा ocxl_file_info *info)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < ARRAY_SIZE(afu_attrs); i++) अणु
		rc = device_create_file(&info->dev, &afu_attrs[i]);
		अगर (rc)
			जाओ err;
	पूर्ण

	sysfs_attr_init(&info->attr_global_mmio.attr);
	info->attr_global_mmio.attr.name = "global_mmio_area";
	info->attr_global_mmio.attr.mode = 0600;
	info->attr_global_mmio.size = info->afu->config.global_mmio_size;
	info->attr_global_mmio.पढ़ो = global_mmio_पढ़ो;
	info->attr_global_mmio.mmap = global_mmio_mmap;
	rc = device_create_bin_file(&info->dev, &info->attr_global_mmio);
	अगर (rc) अणु
		dev_err(&info->dev, "Unable to create global mmio attr for afu: %d\n", rc);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	क्रम (i--; i >= 0; i--)
		device_हटाओ_file(&info->dev, &afu_attrs[i]);

	वापस rc;
पूर्ण

व्योम ocxl_sysfs_unरेजिस्टर_afu(काष्ठा ocxl_file_info *info)
अणु
	पूर्णांक i;

	/*
	 * device_हटाओ_bin_file is safe to call अगर the file is not added as
	 * the files are हटाओd by name, and early निकास अगर not found
	 */
	क्रम (i = 0; i < ARRAY_SIZE(afu_attrs); i++)
		device_हटाओ_file(&info->dev, &afu_attrs[i]);
	device_हटाओ_bin_file(&info->dev, &info->attr_global_mmio);
पूर्ण
