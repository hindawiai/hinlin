<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Express I/O Virtualization (IOV) support
 *   Single Root IOV 1.0
 *   Address Translation Service 1.0
 *
 * Copyright (C) 2009 Intel Corporation, Yu Zhao <yu.zhao@पूर्णांकel.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश "pci.h"

#घोषणा VIRTFN_ID_LEN	16

पूर्णांक pci_iov_virtfn_bus(काष्ठा pci_dev *dev, पूर्णांक vf_id)
अणु
	अगर (!dev->is_physfn)
		वापस -EINVAL;
	वापस dev->bus->number + ((dev->devfn + dev->sriov->offset +
				    dev->sriov->stride * vf_id) >> 8);
पूर्ण

पूर्णांक pci_iov_virtfn_devfn(काष्ठा pci_dev *dev, पूर्णांक vf_id)
अणु
	अगर (!dev->is_physfn)
		वापस -EINVAL;
	वापस (dev->devfn + dev->sriov->offset +
		dev->sriov->stride * vf_id) & 0xff;
पूर्ण
EXPORT_SYMBOL_GPL(pci_iov_virtfn_devfn);

/*
 * Per SR-IOV spec sec 3.3.10 and 3.3.11, First VF Offset and VF Stride may
 * change when NumVFs changes.
 *
 * Update iov->offset and iov->stride when NumVFs is written.
 */
अटल अंतरभूत व्योम pci_iov_set_numvfs(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn)
अणु
	काष्ठा pci_sriov *iov = dev->sriov;

	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_NUM_VF, nr_virtfn);
	pci_पढ़ो_config_word(dev, iov->pos + PCI_SRIOV_VF_OFFSET, &iov->offset);
	pci_पढ़ो_config_word(dev, iov->pos + PCI_SRIOV_VF_STRIDE, &iov->stride);
पूर्ण

/*
 * The PF consumes one bus number.  NumVFs, First VF Offset, and VF Stride
 * determine how many additional bus numbers will be consumed by VFs.
 *
 * Iterate over all valid NumVFs, validate offset and stride, and calculate
 * the maximum number of bus numbers that could ever be required.
 */
अटल पूर्णांक compute_max_vf_buses(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_sriov *iov = dev->sriov;
	पूर्णांक nr_virtfn, busnr, rc = 0;

	क्रम (nr_virtfn = iov->total_VFs; nr_virtfn; nr_virtfn--) अणु
		pci_iov_set_numvfs(dev, nr_virtfn);
		अगर (!iov->offset || (nr_virtfn > 1 && !iov->stride)) अणु
			rc = -EIO;
			जाओ out;
		पूर्ण

		busnr = pci_iov_virtfn_bus(dev, nr_virtfn - 1);
		अगर (busnr > iov->max_VF_buses)
			iov->max_VF_buses = busnr;
	पूर्ण

out:
	pci_iov_set_numvfs(dev, 0);
	वापस rc;
पूर्ण

अटल काष्ठा pci_bus *virtfn_add_bus(काष्ठा pci_bus *bus, पूर्णांक busnr)
अणु
	काष्ठा pci_bus *child;

	अगर (bus->number == busnr)
		वापस bus;

	child = pci_find_bus(pci_करोमुख्य_nr(bus), busnr);
	अगर (child)
		वापस child;

	child = pci_add_new_bus(bus, शून्य, busnr);
	अगर (!child)
		वापस शून्य;

	pci_bus_insert_busn_res(child, busnr, busnr);

	वापस child;
पूर्ण

अटल व्योम virtfn_हटाओ_bus(काष्ठा pci_bus *physbus, काष्ठा pci_bus *virtbus)
अणु
	अगर (physbus != virtbus && list_empty(&virtbus->devices))
		pci_हटाओ_bus(virtbus);
पूर्ण

resource_माप_प्रकार pci_iov_resource_size(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	अगर (!dev->is_physfn)
		वापस 0;

	वापस dev->sriov->barsz[resno - PCI_IOV_RESOURCES];
पूर्ण

अटल व्योम pci_पढ़ो_vf_config_common(काष्ठा pci_dev *virtfn)
अणु
	काष्ठा pci_dev *physfn = virtfn->physfn;

	/*
	 * Some config रेजिस्टरs are the same across all associated VFs.
	 * Read them once from VF0 so we can skip पढ़ोing them from the
	 * other VFs.
	 *
	 * PCIe r4.0, sec 9.3.4.1, technically करोesn't require all VFs to
	 * have the same Revision ID and Subप्रणाली ID, but we assume they
	 * करो.
	 */
	pci_पढ़ो_config_dword(virtfn, PCI_CLASS_REVISION,
			      &physfn->sriov->class);
	pci_पढ़ो_config_byte(virtfn, PCI_HEADER_TYPE,
			     &physfn->sriov->hdr_type);
	pci_पढ़ो_config_word(virtfn, PCI_SUBSYSTEM_VENDOR_ID,
			     &physfn->sriov->subप्रणाली_venकरोr);
	pci_पढ़ो_config_word(virtfn, PCI_SUBSYSTEM_ID,
			     &physfn->sriov->subप्रणाली_device);
पूर्ण

पूर्णांक pci_iov_sysfs_link(काष्ठा pci_dev *dev,
		काष्ठा pci_dev *virtfn, पूर्णांक id)
अणु
	अक्षर buf[VIRTFN_ID_LEN];
	पूर्णांक rc;

	प्र_लिखो(buf, "virtfn%u", id);
	rc = sysfs_create_link(&dev->dev.kobj, &virtfn->dev.kobj, buf);
	अगर (rc)
		जाओ failed;
	rc = sysfs_create_link(&virtfn->dev.kobj, &dev->dev.kobj, "physfn");
	अगर (rc)
		जाओ failed1;

	kobject_uevent(&virtfn->dev.kobj, KOBJ_CHANGE);

	वापस 0;

failed1:
	sysfs_हटाओ_link(&dev->dev.kobj, buf);
failed:
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल sमाप_प्रकार sriov_vf_total_msix_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u32 vf_total_msix = 0;

	device_lock(dev);
	अगर (!pdev->driver || !pdev->driver->sriov_get_vf_total_msix)
		जाओ unlock;

	vf_total_msix = pdev->driver->sriov_get_vf_total_msix(pdev);
unlock:
	device_unlock(dev);
	वापस sysfs_emit(buf, "%u\n", vf_total_msix);
पूर्ण
अटल DEVICE_ATTR_RO(sriov_vf_total_msix);

अटल sमाप_प्रकार sriov_vf_msix_count_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *vf_dev = to_pci_dev(dev);
	काष्ठा pci_dev *pdev = pci_physfn(vf_dev);
	पूर्णांक val, ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < 0)
		वापस -EINVAL;

	device_lock(&pdev->dev);
	अगर (!pdev->driver || !pdev->driver->sriov_set_msix_vec_count) अणु
		ret = -EOPNOTSUPP;
		जाओ err_pdev;
	पूर्ण

	device_lock(&vf_dev->dev);
	अगर (vf_dev->driver) अणु
		/*
		 * A driver is alपढ़ोy attached to this VF and has configured
		 * itself based on the current MSI-X vector count. Changing
		 * the vector size could mess up the driver, so block it.
		 */
		ret = -EBUSY;
		जाओ err_dev;
	पूर्ण

	ret = pdev->driver->sriov_set_msix_vec_count(vf_dev, val);

err_dev:
	device_unlock(&vf_dev->dev);
err_pdev:
	device_unlock(&pdev->dev);
	वापस ret ? : count;
पूर्ण
अटल DEVICE_ATTR_WO(sriov_vf_msix_count);
#पूर्ण_अगर

अटल काष्ठा attribute *sriov_vf_dev_attrs[] = अणु
#अगर_घोषित CONFIG_PCI_MSI
	&dev_attr_sriov_vf_msix_count.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल umode_t sriov_vf_attrs_are_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	अगर (!pdev->is_virtfn)
		वापस 0;

	वापस a->mode;
पूर्ण

स्थिर काष्ठा attribute_group sriov_vf_dev_attr_group = अणु
	.attrs = sriov_vf_dev_attrs,
	.is_visible = sriov_vf_attrs_are_visible,
पूर्ण;

पूर्णांक pci_iov_add_virtfn(काष्ठा pci_dev *dev, पूर्णांक id)
अणु
	पूर्णांक i;
	पूर्णांक rc = -ENOMEM;
	u64 size;
	काष्ठा pci_dev *virtfn;
	काष्ठा resource *res;
	काष्ठा pci_sriov *iov = dev->sriov;
	काष्ठा pci_bus *bus;

	bus = virtfn_add_bus(dev->bus, pci_iov_virtfn_bus(dev, id));
	अगर (!bus)
		जाओ failed;

	virtfn = pci_alloc_dev(bus);
	अगर (!virtfn)
		जाओ failed0;

	virtfn->devfn = pci_iov_virtfn_devfn(dev, id);
	virtfn->venकरोr = dev->venकरोr;
	virtfn->device = iov->vf_device;
	virtfn->is_virtfn = 1;
	virtfn->physfn = pci_dev_get(dev);
	virtfn->no_command_memory = 1;

	अगर (id == 0)
		pci_पढ़ो_vf_config_common(virtfn);

	rc = pci_setup_device(virtfn);
	अगर (rc)
		जाओ failed1;

	virtfn->dev.parent = dev->dev.parent;
	virtfn->multअगरunction = 0;

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		अगर (!res->parent)
			जारी;
		virtfn->resource[i].name = pci_name(virtfn);
		virtfn->resource[i].flags = res->flags;
		size = pci_iov_resource_size(dev, i + PCI_IOV_RESOURCES);
		virtfn->resource[i].start = res->start + size * id;
		virtfn->resource[i].end = virtfn->resource[i].start + size - 1;
		rc = request_resource(res, &virtfn->resource[i]);
		BUG_ON(rc);
	पूर्ण

	pci_device_add(virtfn, virtfn->bus);
	rc = pci_iov_sysfs_link(dev, virtfn, id);
	अगर (rc)
		जाओ failed1;

	pci_bus_add_device(virtfn);

	वापस 0;

failed1:
	pci_stop_and_हटाओ_bus_device(virtfn);
	pci_dev_put(dev);
failed0:
	virtfn_हटाओ_bus(dev->bus, bus);
failed:

	वापस rc;
पूर्ण

व्योम pci_iov_हटाओ_virtfn(काष्ठा pci_dev *dev, पूर्णांक id)
अणु
	अक्षर buf[VIRTFN_ID_LEN];
	काष्ठा pci_dev *virtfn;

	virtfn = pci_get_करोमुख्य_bus_and_slot(pci_करोमुख्य_nr(dev->bus),
					     pci_iov_virtfn_bus(dev, id),
					     pci_iov_virtfn_devfn(dev, id));
	अगर (!virtfn)
		वापस;

	प्र_लिखो(buf, "virtfn%u", id);
	sysfs_हटाओ_link(&dev->dev.kobj, buf);
	/*
	 * pci_stop_dev() could have been called क्रम this virtfn alपढ़ोy,
	 * so the directory क्रम the virtfn may have been हटाओd beक्रमe.
	 * Double check to aव्योम spurious sysfs warnings.
	 */
	अगर (virtfn->dev.kobj.sd)
		sysfs_हटाओ_link(&virtfn->dev.kobj, "physfn");

	pci_stop_and_हटाओ_bus_device(virtfn);
	virtfn_हटाओ_bus(dev->bus, virtfn->bus);

	/* balance pci_get_करोमुख्य_bus_and_slot() */
	pci_dev_put(virtfn);
	pci_dev_put(dev);
पूर्ण

अटल sमाप_प्रकार sriov_totalvfs_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस प्र_लिखो(buf, "%u\n", pci_sriov_get_totalvfs(pdev));
पूर्ण

अटल sमाप_प्रकार sriov_numvfs_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	u16 num_vfs;

	/* Serialize vs sriov_numvfs_store() so पढ़ोers see valid num_VFs */
	device_lock(&pdev->dev);
	num_vfs = pdev->sriov->num_VFs;
	device_unlock(&pdev->dev);

	वापस प्र_लिखो(buf, "%u\n", num_vfs);
पूर्ण

/*
 * num_vfs > 0; number of VFs to enable
 * num_vfs = 0; disable all VFs
 *
 * Note: SRIOV spec करोes not allow partial VF
 *	 disable, so it's all or none.
 */
अटल sमाप_प्रकार sriov_numvfs_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;
	u16 num_vfs;

	ret = kstrtou16(buf, 0, &num_vfs);
	अगर (ret < 0)
		वापस ret;

	अगर (num_vfs > pci_sriov_get_totalvfs(pdev))
		वापस -दुस्फल;

	device_lock(&pdev->dev);

	अगर (num_vfs == pdev->sriov->num_VFs)
		जाओ निकास;

	/* is PF driver loaded w/callback */
	अगर (!pdev->driver || !pdev->driver->sriov_configure) अणु
		pci_info(pdev, "Driver does not support SRIOV configuration via sysfs\n");
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	अगर (num_vfs == 0) अणु
		/* disable VFs */
		ret = pdev->driver->sriov_configure(pdev, 0);
		जाओ निकास;
	पूर्ण

	/* enable VFs */
	अगर (pdev->sriov->num_VFs) अणु
		pci_warn(pdev, "%d VFs already enabled. Disable before enabling %d VFs\n",
			 pdev->sriov->num_VFs, num_vfs);
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	ret = pdev->driver->sriov_configure(pdev, num_vfs);
	अगर (ret < 0)
		जाओ निकास;

	अगर (ret != num_vfs)
		pci_warn(pdev, "%d VFs requested; only %d enabled\n",
			 num_vfs, ret);

निकास:
	device_unlock(&pdev->dev);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार sriov_offset_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस प्र_लिखो(buf, "%u\n", pdev->sriov->offset);
पूर्ण

अटल sमाप_प्रकार sriov_stride_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस प्र_लिखो(buf, "%u\n", pdev->sriov->stride);
पूर्ण

अटल sमाप_प्रकार sriov_vf_device_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस प्र_लिखो(buf, "%x\n", pdev->sriov->vf_device);
पूर्ण

अटल sमाप_प्रकार sriov_drivers_स्वतःprobe_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस प्र_लिखो(buf, "%u\n", pdev->sriov->drivers_स्वतःprobe);
पूर्ण

अटल sमाप_प्रकार sriov_drivers_स्वतःprobe_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	bool drivers_स्वतःprobe;

	अगर (kstrtobool(buf, &drivers_स्वतःprobe) < 0)
		वापस -EINVAL;

	pdev->sriov->drivers_स्वतःprobe = drivers_स्वतःprobe;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RO(sriov_totalvfs);
अटल DEVICE_ATTR_RW(sriov_numvfs);
अटल DEVICE_ATTR_RO(sriov_offset);
अटल DEVICE_ATTR_RO(sriov_stride);
अटल DEVICE_ATTR_RO(sriov_vf_device);
अटल DEVICE_ATTR_RW(sriov_drivers_स्वतःprobe);

अटल काष्ठा attribute *sriov_pf_dev_attrs[] = अणु
	&dev_attr_sriov_totalvfs.attr,
	&dev_attr_sriov_numvfs.attr,
	&dev_attr_sriov_offset.attr,
	&dev_attr_sriov_stride.attr,
	&dev_attr_sriov_vf_device.attr,
	&dev_attr_sriov_drivers_स्वतःprobe.attr,
#अगर_घोषित CONFIG_PCI_MSI
	&dev_attr_sriov_vf_total_msix.attr,
#पूर्ण_अगर
	शून्य,
पूर्ण;

अटल umode_t sriov_pf_attrs_are_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	अगर (!dev_is_pf(dev))
		वापस 0;

	वापस a->mode;
पूर्ण

स्थिर काष्ठा attribute_group sriov_pf_dev_attr_group = अणु
	.attrs = sriov_pf_dev_attrs,
	.is_visible = sriov_pf_attrs_are_visible,
पूर्ण;

पूर्णांक __weak pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	वापस 0;
पूर्ण

पूर्णांक __weak pcibios_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sriov_add_vfs(काष्ठा pci_dev *dev, u16 num_vfs)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	अगर (dev->no_vf_scan)
		वापस 0;

	क्रम (i = 0; i < num_vfs; i++) अणु
		rc = pci_iov_add_virtfn(dev, i);
		अगर (rc)
			जाओ failed;
	पूर्ण
	वापस 0;
failed:
	जबतक (i--)
		pci_iov_हटाओ_virtfn(dev, i);

	वापस rc;
पूर्ण

अटल पूर्णांक sriov_enable(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	पूर्णांक nres;
	u16 initial;
	काष्ठा resource *res;
	काष्ठा pci_dev *pdev;
	काष्ठा pci_sriov *iov = dev->sriov;
	पूर्णांक bars = 0;
	पूर्णांक bus;

	अगर (!nr_virtfn)
		वापस 0;

	अगर (iov->num_VFs)
		वापस -EINVAL;

	pci_पढ़ो_config_word(dev, iov->pos + PCI_SRIOV_INITIAL_VF, &initial);
	अगर (initial > iov->total_VFs ||
	    (!(iov->cap & PCI_SRIOV_CAP_VFM) && (initial != iov->total_VFs)))
		वापस -EIO;

	अगर (nr_virtfn < 0 || nr_virtfn > iov->total_VFs ||
	    (!(iov->cap & PCI_SRIOV_CAP_VFM) && (nr_virtfn > initial)))
		वापस -EINVAL;

	nres = 0;
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		bars |= (1 << (i + PCI_IOV_RESOURCES));
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		अगर (res->parent)
			nres++;
	पूर्ण
	अगर (nres != iov->nres) अणु
		pci_err(dev, "not enough MMIO resources for SR-IOV\n");
		वापस -ENOMEM;
	पूर्ण

	bus = pci_iov_virtfn_bus(dev, nr_virtfn - 1);
	अगर (bus > dev->bus->busn_res.end) अणु
		pci_err(dev, "can't enable %d VFs (bus %02x out of range of %pR)\n",
			nr_virtfn, bus, &dev->bus->busn_res);
		वापस -ENOMEM;
	पूर्ण

	अगर (pci_enable_resources(dev, bars)) अणु
		pci_err(dev, "SR-IOV: IOV BARS not allocated\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (iov->link != dev->devfn) अणु
		pdev = pci_get_slot(dev->bus, iov->link);
		अगर (!pdev)
			वापस -ENODEV;

		अगर (!pdev->is_physfn) अणु
			pci_dev_put(pdev);
			वापस -ENOSYS;
		पूर्ण

		rc = sysfs_create_link(&dev->dev.kobj,
					&pdev->dev.kobj, "dep_link");
		pci_dev_put(pdev);
		अगर (rc)
			वापस rc;
	पूर्ण

	iov->initial_VFs = initial;
	अगर (nr_virtfn < initial)
		initial = nr_virtfn;

	rc = pcibios_sriov_enable(dev, initial);
	अगर (rc) अणु
		pci_err(dev, "failure %d from pcibios_sriov_enable()\n", rc);
		जाओ err_pcibios;
	पूर्ण

	pci_iov_set_numvfs(dev, nr_virtfn);
	iov->ctrl |= PCI_SRIOV_CTRL_VFE | PCI_SRIOV_CTRL_MSE;
	pci_cfg_access_lock(dev);
	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, iov->ctrl);
	msleep(100);
	pci_cfg_access_unlock(dev);

	rc = sriov_add_vfs(dev, initial);
	अगर (rc)
		जाओ err_pcibios;

	kobject_uevent(&dev->dev.kobj, KOBJ_CHANGE);
	iov->num_VFs = nr_virtfn;

	वापस 0;

err_pcibios:
	iov->ctrl &= ~(PCI_SRIOV_CTRL_VFE | PCI_SRIOV_CTRL_MSE);
	pci_cfg_access_lock(dev);
	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, iov->ctrl);
	ssleep(1);
	pci_cfg_access_unlock(dev);

	pcibios_sriov_disable(dev);

	अगर (iov->link != dev->devfn)
		sysfs_हटाओ_link(&dev->dev.kobj, "dep_link");

	pci_iov_set_numvfs(dev, 0);
	वापस rc;
पूर्ण

अटल व्योम sriov_del_vfs(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_sriov *iov = dev->sriov;
	पूर्णांक i;

	क्रम (i = 0; i < iov->num_VFs; i++)
		pci_iov_हटाओ_virtfn(dev, i);
पूर्ण

अटल व्योम sriov_disable(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_sriov *iov = dev->sriov;

	अगर (!iov->num_VFs)
		वापस;

	sriov_del_vfs(dev);
	iov->ctrl &= ~(PCI_SRIOV_CTRL_VFE | PCI_SRIOV_CTRL_MSE);
	pci_cfg_access_lock(dev);
	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, iov->ctrl);
	ssleep(1);
	pci_cfg_access_unlock(dev);

	pcibios_sriov_disable(dev);

	अगर (iov->link != dev->devfn)
		sysfs_हटाओ_link(&dev->dev.kobj, "dep_link");

	iov->num_VFs = 0;
	pci_iov_set_numvfs(dev, 0);
पूर्ण

अटल पूर्णांक sriov_init(काष्ठा pci_dev *dev, पूर्णांक pos)
अणु
	पूर्णांक i, bar64;
	पूर्णांक rc;
	पूर्णांक nres;
	u32 pgsz;
	u16 ctrl, total;
	काष्ठा pci_sriov *iov;
	काष्ठा resource *res;
	काष्ठा pci_dev *pdev;

	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_CTRL, &ctrl);
	अगर (ctrl & PCI_SRIOV_CTRL_VFE) अणु
		pci_ग_लिखो_config_word(dev, pos + PCI_SRIOV_CTRL, 0);
		ssleep(1);
	पूर्ण

	ctrl = 0;
	list_क्रम_each_entry(pdev, &dev->bus->devices, bus_list)
		अगर (pdev->is_physfn)
			जाओ found;

	pdev = शून्य;
	अगर (pci_ari_enabled(dev->bus))
		ctrl |= PCI_SRIOV_CTRL_ARI;

found:
	pci_ग_लिखो_config_word(dev, pos + PCI_SRIOV_CTRL, ctrl);

	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_TOTAL_VF, &total);
	अगर (!total)
		वापस 0;

	pci_पढ़ो_config_dword(dev, pos + PCI_SRIOV_SUP_PGSIZE, &pgsz);
	i = PAGE_SHIFT > 12 ? PAGE_SHIFT - 12 : 0;
	pgsz &= ~((1 << i) - 1);
	अगर (!pgsz)
		वापस -EIO;

	pgsz &= ~(pgsz - 1);
	pci_ग_लिखो_config_dword(dev, pos + PCI_SRIOV_SYS_PGSIZE, pgsz);

	iov = kzalloc(माप(*iov), GFP_KERNEL);
	अगर (!iov)
		वापस -ENOMEM;

	nres = 0;
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		/*
		 * If it is alपढ़ोy FIXED, करोn't change it, something
		 * (perhaps EA or header fixups) wants it this way.
		 */
		अगर (res->flags & IORESOURCE_PCI_FIXED)
			bar64 = (res->flags & IORESOURCE_MEM_64) ? 1 : 0;
		अन्यथा
			bar64 = __pci_पढ़ो_base(dev, pci_bar_unknown, res,
						pos + PCI_SRIOV_BAR + i * 4);
		अगर (!res->flags)
			जारी;
		अगर (resource_size(res) & (PAGE_SIZE - 1)) अणु
			rc = -EIO;
			जाओ failed;
		पूर्ण
		iov->barsz[i] = resource_size(res);
		res->end = res->start + resource_size(res) * total - 1;
		pci_info(dev, "VF(n) BAR%d space: %pR (contains BAR%d for %d VFs)\n",
			 i, res, i, total);
		i += bar64;
		nres++;
	पूर्ण

	iov->pos = pos;
	iov->nres = nres;
	iov->ctrl = ctrl;
	iov->total_VFs = total;
	iov->driver_max_VFs = total;
	pci_पढ़ो_config_word(dev, pos + PCI_SRIOV_VF_DID, &iov->vf_device);
	iov->pgsz = pgsz;
	iov->self = dev;
	iov->drivers_स्वतःprobe = true;
	pci_पढ़ो_config_dword(dev, pos + PCI_SRIOV_CAP, &iov->cap);
	pci_पढ़ो_config_byte(dev, pos + PCI_SRIOV_FUNC_LINK, &iov->link);
	अगर (pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END)
		iov->link = PCI_DEVFN(PCI_SLOT(dev->devfn), iov->link);

	अगर (pdev)
		iov->dev = pci_dev_get(pdev);
	अन्यथा
		iov->dev = dev;

	dev->sriov = iov;
	dev->is_physfn = 1;
	rc = compute_max_vf_buses(dev);
	अगर (rc)
		जाओ fail_max_buses;

	वापस 0;

fail_max_buses:
	dev->sriov = शून्य;
	dev->is_physfn = 0;
failed:
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		res->flags = 0;
	पूर्ण

	kमुक्त(iov);
	वापस rc;
पूर्ण

अटल व्योम sriov_release(काष्ठा pci_dev *dev)
अणु
	BUG_ON(dev->sriov->num_VFs);

	अगर (dev != dev->sriov->dev)
		pci_dev_put(dev->sriov->dev);

	kमुक्त(dev->sriov);
	dev->sriov = शून्य;
पूर्ण

अटल व्योम sriov_restore_state(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	u16 ctrl;
	काष्ठा pci_sriov *iov = dev->sriov;

	pci_पढ़ो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, &ctrl);
	अगर (ctrl & PCI_SRIOV_CTRL_VFE)
		वापस;

	/*
	 * Restore PCI_SRIOV_CTRL_ARI beक्रमe pci_iov_set_numvfs() because
	 * it पढ़ोs offset & stride, which depend on PCI_SRIOV_CTRL_ARI.
	 */
	ctrl &= ~PCI_SRIOV_CTRL_ARI;
	ctrl |= iov->ctrl & PCI_SRIOV_CTRL_ARI;
	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, ctrl);

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++)
		pci_update_resource(dev, i + PCI_IOV_RESOURCES);

	pci_ग_लिखो_config_dword(dev, iov->pos + PCI_SRIOV_SYS_PGSIZE, iov->pgsz);
	pci_iov_set_numvfs(dev, iov->num_VFs);
	pci_ग_लिखो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, iov->ctrl);
	अगर (iov->ctrl & PCI_SRIOV_CTRL_VFE)
		msleep(100);
पूर्ण

/**
 * pci_iov_init - initialize the IOV capability
 * @dev: the PCI device
 *
 * Returns 0 on success, or negative on failure.
 */
पूर्णांक pci_iov_init(काष्ठा pci_dev *dev)
अणु
	पूर्णांक pos;

	अगर (!pci_is_pcie(dev))
		वापस -ENODEV;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_SRIOV);
	अगर (pos)
		वापस sriov_init(dev, pos);

	वापस -ENODEV;
पूर्ण

/**
 * pci_iov_release - release resources used by the IOV capability
 * @dev: the PCI device
 */
व्योम pci_iov_release(काष्ठा pci_dev *dev)
अणु
	अगर (dev->is_physfn)
		sriov_release(dev);
पूर्ण

/**
 * pci_iov_हटाओ - clean up SR-IOV state after PF driver is detached
 * @dev: the PCI device
 */
व्योम pci_iov_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_sriov *iov = dev->sriov;

	अगर (!dev->is_physfn)
		वापस;

	iov->driver_max_VFs = iov->total_VFs;
	अगर (iov->num_VFs)
		pci_warn(dev, "driver left SR-IOV enabled after remove\n");
पूर्ण

/**
 * pci_iov_update_resource - update a VF BAR
 * @dev: the PCI device
 * @resno: the resource number
 *
 * Update a VF BAR in the SR-IOV capability of a PF.
 */
व्योम pci_iov_update_resource(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	काष्ठा pci_sriov *iov = dev->is_physfn ? dev->sriov : शून्य;
	काष्ठा resource *res = dev->resource + resno;
	पूर्णांक vf_bar = resno - PCI_IOV_RESOURCES;
	काष्ठा pci_bus_region region;
	u16 cmd;
	u32 new;
	पूर्णांक reg;

	/*
	 * The generic pci_restore_bars() path calls this क्रम all devices,
	 * including VFs and non-SR-IOV devices.  If this is not a PF, we
	 * have nothing to करो.
	 */
	अगर (!iov)
		वापस;

	pci_पढ़ो_config_word(dev, iov->pos + PCI_SRIOV_CTRL, &cmd);
	अगर ((cmd & PCI_SRIOV_CTRL_VFE) && (cmd & PCI_SRIOV_CTRL_MSE)) अणु
		dev_WARN(&dev->dev, "can't update enabled VF BAR%d %pR\n",
			 vf_bar, res);
		वापस;
	पूर्ण

	/*
	 * Ignore unimplemented BARs, unused resource slots क्रम 64-bit
	 * BARs, and non-movable resources, e.g., those described via
	 * Enhanced Allocation.
	 */
	अगर (!res->flags)
		वापस;

	अगर (res->flags & IORESOURCE_UNSET)
		वापस;

	अगर (res->flags & IORESOURCE_PCI_FIXED)
		वापस;

	pcibios_resource_to_bus(dev->bus, &region, res);
	new = region.start;
	new |= res->flags & ~PCI_BASE_ADDRESS_MEM_MASK;

	reg = iov->pos + PCI_SRIOV_BAR + 4 * vf_bar;
	pci_ग_लिखो_config_dword(dev, reg, new);
	अगर (res->flags & IORESOURCE_MEM_64) अणु
		new = region.start >> 16 >> 16;
		pci_ग_लिखो_config_dword(dev, reg + 4, new);
	पूर्ण
पूर्ण

resource_माप_प्रकार __weak pcibios_iov_resource_alignment(काष्ठा pci_dev *dev,
						      पूर्णांक resno)
अणु
	वापस pci_iov_resource_size(dev, resno);
पूर्ण

/**
 * pci_sriov_resource_alignment - get resource alignment क्रम VF BAR
 * @dev: the PCI device
 * @resno: the resource number
 *
 * Returns the alignment of the VF BAR found in the SR-IOV capability.
 * This is not the same as the resource size which is defined as
 * the VF BAR size multiplied by the number of VFs.  The alignment
 * is just the VF BAR size.
 */
resource_माप_प्रकार pci_sriov_resource_alignment(काष्ठा pci_dev *dev, पूर्णांक resno)
अणु
	वापस pcibios_iov_resource_alignment(dev, resno);
पूर्ण

/**
 * pci_restore_iov_state - restore the state of the IOV capability
 * @dev: the PCI device
 */
व्योम pci_restore_iov_state(काष्ठा pci_dev *dev)
अणु
	अगर (dev->is_physfn)
		sriov_restore_state(dev);
पूर्ण

/**
 * pci_vf_drivers_स्वतःprobe - set PF property drivers_स्वतःprobe क्रम VFs
 * @dev: the PCI device
 * @स्वतः_probe: set VF drivers स्वतः probe flag
 */
व्योम pci_vf_drivers_स्वतःprobe(काष्ठा pci_dev *dev, bool स्वतः_probe)
अणु
	अगर (dev->is_physfn)
		dev->sriov->drivers_स्वतःprobe = स्वतः_probe;
पूर्ण

/**
 * pci_iov_bus_range - find bus range used by Virtual Function
 * @bus: the PCI bus
 *
 * Returns max number of buses (exclude current one) used by Virtual
 * Functions.
 */
पूर्णांक pci_iov_bus_range(काष्ठा pci_bus *bus)
अणु
	पूर्णांक max = 0;
	काष्ठा pci_dev *dev;

	list_क्रम_each_entry(dev, &bus->devices, bus_list) अणु
		अगर (!dev->is_physfn)
			जारी;
		अगर (dev->sriov->max_VF_buses > max)
			max = dev->sriov->max_VF_buses;
	पूर्ण

	वापस max ? max - bus->number : 0;
पूर्ण

/**
 * pci_enable_sriov - enable the SR-IOV capability
 * @dev: the PCI device
 * @nr_virtfn: number of भव functions to enable
 *
 * Returns 0 on success, or negative on failure.
 */
पूर्णांक pci_enable_sriov(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn)
अणु
	might_sleep();

	अगर (!dev->is_physfn)
		वापस -ENOSYS;

	वापस sriov_enable(dev, nr_virtfn);
पूर्ण
EXPORT_SYMBOL_GPL(pci_enable_sriov);

/**
 * pci_disable_sriov - disable the SR-IOV capability
 * @dev: the PCI device
 */
व्योम pci_disable_sriov(काष्ठा pci_dev *dev)
अणु
	might_sleep();

	अगर (!dev->is_physfn)
		वापस;

	sriov_disable(dev);
पूर्ण
EXPORT_SYMBOL_GPL(pci_disable_sriov);

/**
 * pci_num_vf - वापस number of VFs associated with a PF device_release_driver
 * @dev: the PCI device
 *
 * Returns number of VFs, or 0 अगर SR-IOV is not enabled.
 */
पूर्णांक pci_num_vf(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->is_physfn)
		वापस 0;

	वापस dev->sriov->num_VFs;
पूर्ण
EXPORT_SYMBOL_GPL(pci_num_vf);

/**
 * pci_vfs_asचिन्हित - वापसs number of VFs are asचिन्हित to a guest
 * @dev: the PCI device
 *
 * Returns number of VFs beदीर्घing to this device that are asचिन्हित to a guest.
 * If device is not a physical function वापसs 0.
 */
पूर्णांक pci_vfs_asचिन्हित(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *vfdev;
	अचिन्हित पूर्णांक vfs_asचिन्हित = 0;
	अचिन्हित लघु dev_id;

	/* only search अगर we are a PF */
	अगर (!dev->is_physfn)
		वापस 0;

	/*
	 * determine the device ID क्रम the VFs, the venकरोr ID will be the
	 * same as the PF so there is no need to check क्रम that one
	 */
	dev_id = dev->sriov->vf_device;

	/* loop through all the VFs to see अगर we own any that are asचिन्हित */
	vfdev = pci_get_device(dev->venकरोr, dev_id, शून्य);
	जबतक (vfdev) अणु
		/*
		 * It is considered asचिन्हित अगर it is a भव function with
		 * our dev as the physical function and the asचिन्हित bit is set
		 */
		अगर (vfdev->is_virtfn && (vfdev->physfn == dev) &&
			pci_is_dev_asचिन्हित(vfdev))
			vfs_asचिन्हित++;

		vfdev = pci_get_device(dev->venकरोr, dev_id, vfdev);
	पूर्ण

	वापस vfs_asचिन्हित;
पूर्ण
EXPORT_SYMBOL_GPL(pci_vfs_asचिन्हित);

/**
 * pci_sriov_set_totalvfs -- reduce the TotalVFs available
 * @dev: the PCI PF device
 * @numvfs: number that should be used क्रम TotalVFs supported
 *
 * Should be called from PF driver's probe routine with
 * device's mutex held.
 *
 * Returns 0 अगर PF is an SRIOV-capable device and
 * value of numvfs valid. If not a PF वापस -ENOSYS;
 * अगर numvfs is invalid वापस -EINVAL;
 * अगर VFs alपढ़ोy enabled, वापस -EBUSY.
 */
पूर्णांक pci_sriov_set_totalvfs(काष्ठा pci_dev *dev, u16 numvfs)
अणु
	अगर (!dev->is_physfn)
		वापस -ENOSYS;

	अगर (numvfs > dev->sriov->total_VFs)
		वापस -EINVAL;

	/* Shouldn't change अगर VFs alपढ़ोy enabled */
	अगर (dev->sriov->ctrl & PCI_SRIOV_CTRL_VFE)
		वापस -EBUSY;

	dev->sriov->driver_max_VFs = numvfs;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_sriov_set_totalvfs);

/**
 * pci_sriov_get_totalvfs -- get total VFs supported on this device
 * @dev: the PCI PF device
 *
 * For a PCIe device with SRIOV support, वापस the PCIe
 * SRIOV capability value of TotalVFs or the value of driver_max_VFs
 * अगर the driver reduced it.  Otherwise 0.
 */
पूर्णांक pci_sriov_get_totalvfs(काष्ठा pci_dev *dev)
अणु
	अगर (!dev->is_physfn)
		वापस 0;

	वापस dev->sriov->driver_max_VFs;
पूर्ण
EXPORT_SYMBOL_GPL(pci_sriov_get_totalvfs);

/**
 * pci_sriov_configure_simple - helper to configure SR-IOV
 * @dev: the PCI device
 * @nr_virtfn: number of भव functions to enable, 0 to disable
 *
 * Enable or disable SR-IOV क्रम devices that करोn't require any PF setup
 * beक्रमe enabling SR-IOV.  Return value is negative on error, or number of
 * VFs allocated on success.
 */
पूर्णांक pci_sriov_configure_simple(काष्ठा pci_dev *dev, पूर्णांक nr_virtfn)
अणु
	पूर्णांक rc;

	might_sleep();

	अगर (!dev->is_physfn)
		वापस -ENODEV;

	अगर (pci_vfs_asचिन्हित(dev)) अणु
		pci_warn(dev, "Cannot modify SR-IOV while VFs are assigned\n");
		वापस -EPERM;
	पूर्ण

	अगर (nr_virtfn == 0) अणु
		sriov_disable(dev);
		वापस 0;
	पूर्ण

	rc = sriov_enable(dev, nr_virtfn);
	अगर (rc < 0)
		वापस rc;

	वापस nr_virtfn;
पूर्ण
EXPORT_SYMBOL_GPL(pci_sriov_configure_simple);
