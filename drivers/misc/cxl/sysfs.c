<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2014 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pci_regs.h>

#समावेश "cxl.h"

#घोषणा to_afu_अक्षरdev_m(d) dev_get_drvdata(d)

/*********  Adapter attributes  **********************************************/

अटल sमाप_प्रकार caia_version_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i.%i\n", adapter->caia_major,
			 adapter->caia_minor);
पूर्ण

अटल sमाप_प्रकार psl_revision_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", adapter->psl_rev);
पूर्ण

अटल sमाप_प्रकार base_image_show(काष्ठा device *device,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", adapter->base_image);
पूर्ण

अटल sमाप_प्रकार image_loaded_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	अगर (adapter->user_image_loaded)
		वापस scnम_लिखो(buf, PAGE_SIZE, "user\n");
	वापस scnम_लिखो(buf, PAGE_SIZE, "factory\n");
पूर्ण

अटल sमाप_प्रकार psl_समयbase_synced_show(काष्ठा device *device,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);
	u64 psl_tb, delta;

	/* Recompute the status only in native mode */
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		psl_tb = adapter->native->sl_ops->समयbase_पढ़ो(adapter);
		delta = असल(mftb() - psl_tb);

		/* CORE TB and PSL TB dअगरference <= 16usecs ? */
		adapter->psl_समयbase_synced = (tb_to_ns(delta) < 16000) ? true : false;
		pr_devel("PSL timebase %s - delta: 0x%016llx\n",
			 (tb_to_ns(delta) < 16000) ? "synchronized" :
			 "not synchronized", tb_to_ns(delta));
	पूर्ण
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", adapter->psl_समयbase_synced);
पूर्ण

अटल sमाप_प्रकार tunneled_ops_supported_show(काष्ठा device *device,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", adapter->tunneled_ops_supported);
पूर्ण

अटल sमाप_प्रकार reset_adapter_store(काष्ठा device *device,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);
	पूर्णांक rc;
	पूर्णांक val;

	rc = माला_पूछो(buf, "%i", &val);
	अगर ((rc != 1) || (val != 1 && val != -1))
		वापस -EINVAL;

	/*
	 * See अगर we can lock the context mapping that's only allowed
	 * when there are no contexts attached to the adapter. Once
	 * taken this will also prevent any context from getting activated.
	 */
	अगर (val == 1) अणु
		rc =  cxl_adapter_context_lock(adapter);
		अगर (rc)
			जाओ out;

		rc = cxl_ops->adapter_reset(adapter);
		/* In हाल reset failed release context lock */
		अगर (rc)
			cxl_adapter_context_unlock(adapter);

	पूर्ण अन्यथा अगर (val == -1) अणु
		/* Perक्रमm a क्रमced adapter reset */
		rc = cxl_ops->adapter_reset(adapter);
	पूर्ण

out:
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार load_image_on_perst_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	अगर (!adapter->perst_loads_image)
		वापस scnम_लिखो(buf, PAGE_SIZE, "none\n");

	अगर (adapter->perst_select_user)
		वापस scnम_लिखो(buf, PAGE_SIZE, "user\n");
	वापस scnम_लिखो(buf, PAGE_SIZE, "factory\n");
पूर्ण

अटल sमाप_प्रकार load_image_on_perst_store(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);
	पूर्णांक rc;

	अगर (!म_भेदन(buf, "none", 4))
		adapter->perst_loads_image = false;
	अन्यथा अगर (!म_भेदन(buf, "user", 4)) अणु
		adapter->perst_select_user = true;
		adapter->perst_loads_image = true;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "factory", 7)) अणु
		adapter->perst_select_user = false;
		adapter->perst_loads_image = true;
	पूर्ण अन्यथा
		वापस -EINVAL;

	अगर ((rc = cxl_update_image_control(adapter)))
		वापस rc;

	वापस count;
पूर्ण

अटल sमाप_प्रकार perst_reloads_same_image_show(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", adapter->perst_same_image);
पूर्ण

अटल sमाप_प्रकार perst_reloads_same_image_store(काष्ठा device *device,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl *adapter = to_cxl_adapter(device);
	पूर्णांक rc;
	पूर्णांक val;

	rc = माला_पूछो(buf, "%i", &val);
	अगर ((rc != 1) || !(val == 1 || val == 0))
		वापस -EINVAL;

	adapter->perst_same_image = (val == 1);
	वापस count;
पूर्ण

अटल काष्ठा device_attribute adapter_attrs[] = अणु
	__ATTR_RO(caia_version),
	__ATTR_RO(psl_revision),
	__ATTR_RO(base_image),
	__ATTR_RO(image_loaded),
	__ATTR_RO(psl_समयbase_synced),
	__ATTR_RO(tunneled_ops_supported),
	__ATTR_RW(load_image_on_perst),
	__ATTR_RW(perst_reloads_same_image),
	__ATTR(reset, S_IWUSR, शून्य, reset_adapter_store),
पूर्ण;


/*********  AFU master specअगरic attributes  **********************************/

अटल sमाप_प्रकार mmio_size_show_master(काष्ठा device *device,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_afu_अक्षरdev_m(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", afu->adapter->ps_size);
पूर्ण

अटल sमाप_प्रकार pp_mmio_off_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_afu_अक्षरdev_m(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", afu->native->pp_offset);
पूर्ण

अटल sमाप_प्रकार pp_mmio_len_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_afu_अक्षरdev_m(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", afu->pp_size);
पूर्ण

अटल काष्ठा device_attribute afu_master_attrs[] = अणु
	__ATTR(mmio_size, S_IRUGO, mmio_size_show_master, शून्य),
	__ATTR_RO(pp_mmio_off),
	__ATTR_RO(pp_mmio_len),
पूर्ण;


/*********  AFU attributes  **************************************************/

अटल sमाप_प्रकार mmio_size_show(काष्ठा device *device,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);

	अगर (afu->pp_size)
		वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", afu->pp_size);
	वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n", afu->adapter->ps_size);
पूर्ण

अटल sमाप_प्रकार reset_store_afu(काष्ठा device *device,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);
	पूर्णांक rc;

	/* Not safe to reset अगर it is currently in use */
	mutex_lock(&afu->contexts_lock);
	अगर (!idr_is_empty(&afu->contexts_idr)) अणु
		rc = -EBUSY;
		जाओ err;
	पूर्ण

	अगर ((rc = cxl_ops->afu_reset(afu)))
		जाओ err;

	rc = count;
err:
	mutex_unlock(&afu->contexts_lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार irqs_min_show(काष्ठा device *device,
			     काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", afu->pp_irqs);
पूर्ण

अटल sमाप_प्रकार irqs_max_show(काष्ठा device *device,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", afu->irqs_max);
पूर्ण

अटल sमाप_प्रकार irqs_max_store(काष्ठा device *device,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);
	sमाप_प्रकार ret;
	पूर्णांक irqs_max;

	ret = माला_पूछो(buf, "%i", &irqs_max);
	अगर (ret != 1)
		वापस -EINVAL;

	अगर (irqs_max < afu->pp_irqs)
		वापस -EINVAL;

	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		अगर (irqs_max > afu->adapter->user_irqs)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* pHyp sets a per-AFU limit */
		अगर (irqs_max > afu->guest->max_पूर्णांकs)
			वापस -EINVAL;
	पूर्ण

	afu->irqs_max = irqs_max;
	वापस count;
पूर्ण

अटल sमाप_प्रकार modes_supported_show(काष्ठा device *device,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);
	अक्षर *p = buf, *end = buf + PAGE_SIZE;

	अगर (afu->modes_supported & CXL_MODE_DEDICATED)
		p += scnम_लिखो(p, end - p, "dedicated_process\n");
	अगर (afu->modes_supported & CXL_MODE_सूचीECTED)
		p += scnम_लिखो(p, end - p, "afu_directed\n");
	वापस (p - buf);
पूर्ण

अटल sमाप_प्रकार prefault_mode_show(काष्ठा device *device,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);

	चयन (afu->prefault_mode) अणु
	हाल CXL_PREFAULT_WED:
		वापस scnम_लिखो(buf, PAGE_SIZE, "work_element_descriptor\n");
	हाल CXL_PREFAULT_ALL:
		वापस scnम_लिखो(buf, PAGE_SIZE, "all\n");
	शेष:
		वापस scnम_लिखो(buf, PAGE_SIZE, "none\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार prefault_mode_store(काष्ठा device *device,
			  काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);
	क्रमागत prefault_modes mode = -1;

	अगर (!म_भेदन(buf, "none", 4))
		mode = CXL_PREFAULT_NONE;
	अन्यथा अणु
		अगर (!radix_enabled()) अणु

			/* only allowed when not in radix mode */
			अगर (!म_भेदन(buf, "work_element_descriptor", 23))
				mode = CXL_PREFAULT_WED;
			अगर (!म_भेदन(buf, "all", 3))
				mode = CXL_PREFAULT_ALL;
		पूर्ण अन्यथा अणु
			dev_err(device, "Cannot prefault with radix enabled\n");
		पूर्ण
	पूर्ण

	अगर (mode == -1)
		वापस -EINVAL;

	afu->prefault_mode = mode;
	वापस count;
पूर्ण

अटल sमाप_प्रकार mode_show(काष्ठा device *device,
			 काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);

	अगर (afu->current_mode == CXL_MODE_DEDICATED)
		वापस scnम_लिखो(buf, PAGE_SIZE, "dedicated_process\n");
	अगर (afu->current_mode == CXL_MODE_सूचीECTED)
		वापस scnम_लिखो(buf, PAGE_SIZE, "afu_directed\n");
	वापस scnम_लिखो(buf, PAGE_SIZE, "none\n");
पूर्ण

अटल sमाप_प्रकार mode_store(काष्ठा device *device, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(device);
	पूर्णांक old_mode, mode = -1;
	पूर्णांक rc = -EBUSY;

	/* can't change this अगर we have a user */
	mutex_lock(&afu->contexts_lock);
	अगर (!idr_is_empty(&afu->contexts_idr))
		जाओ err;

	अगर (!म_भेदन(buf, "dedicated_process", 17))
		mode = CXL_MODE_DEDICATED;
	अगर (!म_भेदन(buf, "afu_directed", 12))
		mode = CXL_MODE_सूचीECTED;
	अगर (!म_भेदन(buf, "none", 4))
		mode = 0;

	अगर (mode == -1) अणु
		rc = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * afu_deactivate_mode needs to be करोne outside the lock, prevent
	 * other contexts coming in beक्रमe we are पढ़ोy:
	 */
	old_mode = afu->current_mode;
	afu->current_mode = 0;
	afu->num_procs = 0;

	mutex_unlock(&afu->contexts_lock);

	अगर ((rc = cxl_ops->afu_deactivate_mode(afu, old_mode)))
		वापस rc;
	अगर ((rc = cxl_ops->afu_activate_mode(afu, mode)))
		वापस rc;

	वापस count;
err:
	mutex_unlock(&afu->contexts_lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार api_version_show(काष्ठा device *device,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", CXL_API_VERSION);
पूर्ण

अटल sमाप_प्रकार api_version_compatible_show(काष्ठा device *device,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	वापस scnम_लिखो(buf, PAGE_SIZE, "%i\n", CXL_API_VERSION_COMPATIBLE);
पूर्ण

अटल sमाप_प्रकार afu_eb_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t off, माप_प्रकार count)
अणु
	काष्ठा cxl_afu *afu = to_cxl_afu(kobj_to_dev(kobj));

	वापस cxl_ops->afu_पढ़ो_err_buffer(afu, buf, off, count);
पूर्ण

अटल काष्ठा device_attribute afu_attrs[] = अणु
	__ATTR_RO(mmio_size),
	__ATTR_RO(irqs_min),
	__ATTR_RW(irqs_max),
	__ATTR_RO(modes_supported),
	__ATTR_RW(mode),
	__ATTR_RW(prefault_mode),
	__ATTR_RO(api_version),
	__ATTR_RO(api_version_compatible),
	__ATTR(reset, S_IWUSR, शून्य, reset_store_afu),
पूर्ण;

पूर्णांक cxl_sysfs_adapter_add(काष्ठा cxl *adapter)
अणु
	काष्ठा device_attribute *dev_attr;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ARRAY_SIZE(adapter_attrs); i++) अणु
		dev_attr = &adapter_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_ADAPTER_ATTRS)) अणु
			अगर ((rc = device_create_file(&adapter->dev, dev_attr)))
				जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;
err:
	क्रम (i--; i >= 0; i--) अणु
		dev_attr = &adapter_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_ADAPTER_ATTRS))
			device_हटाओ_file(&adapter->dev, dev_attr);
	पूर्ण
	वापस rc;
पूर्ण

व्योम cxl_sysfs_adapter_हटाओ(काष्ठा cxl *adapter)
अणु
	काष्ठा device_attribute *dev_attr;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adapter_attrs); i++) अणु
		dev_attr = &adapter_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_ADAPTER_ATTRS))
			device_हटाओ_file(&adapter->dev, dev_attr);
	पूर्ण
पूर्ण

काष्ठा afu_config_record अणु
	काष्ठा kobject kobj;
	काष्ठा bin_attribute config_attr;
	काष्ठा list_head list;
	पूर्णांक cr;
	u16 device;
	u16 venकरोr;
	u32 class;
पूर्ण;

#घोषणा to_cr(obj) container_of(obj, काष्ठा afu_config_record, kobj)

अटल sमाप_प्रकार venकरोr_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा afu_config_record *cr = to_cr(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%.4x\n", cr->venकरोr);
पूर्ण

अटल sमाप_प्रकार device_show(काष्ठा kobject *kobj,
			   काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा afu_config_record *cr = to_cr(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%.4x\n", cr->device);
पूर्ण

अटल sमाप_प्रकार class_show(काष्ठा kobject *kobj,
			  काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा afu_config_record *cr = to_cr(kobj);

	वापस scnम_लिखो(buf, PAGE_SIZE, "0x%.6x\n", cr->class);
पूर्ण

अटल sमाप_प्रकार afu_पढ़ो_config(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			       loff_t off, माप_प्रकार count)
अणु
	काष्ठा afu_config_record *cr = to_cr(kobj);
	काष्ठा cxl_afu *afu = to_cxl_afu(kobj_to_dev(kobj->parent));

	u64 i, j, val, rc;

	क्रम (i = 0; i < count;) अणु
		rc = cxl_ops->afu_cr_पढ़ो64(afu, cr->cr, off & ~0x7, &val);
		अगर (rc)
			val = ~0ULL;
		क्रम (j = off & 0x7; j < 8 && i < count; i++, j++, off++)
			buf[i] = (val >> (j * 8)) & 0xff;
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute venकरोr_attribute =
	__ATTR_RO(venकरोr);
अटल काष्ठा kobj_attribute device_attribute =
	__ATTR_RO(device);
अटल काष्ठा kobj_attribute class_attribute =
	__ATTR_RO(class);

अटल काष्ठा attribute *afu_cr_attrs[] = अणु
	&venकरोr_attribute.attr,
	&device_attribute.attr,
	&class_attribute.attr,
	शून्य,
पूर्ण;

अटल व्योम release_afu_config_record(काष्ठा kobject *kobj)
अणु
	काष्ठा afu_config_record *cr = to_cr(kobj);

	kमुक्त(cr);
पूर्ण

अटल काष्ठा kobj_type afu_config_record_type = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = release_afu_config_record,
	.शेष_attrs = afu_cr_attrs,
पूर्ण;

अटल काष्ठा afu_config_record *cxl_sysfs_afu_new_cr(काष्ठा cxl_afu *afu, पूर्णांक cr_idx)
अणु
	काष्ठा afu_config_record *cr;
	पूर्णांक rc;

	cr = kzalloc(माप(काष्ठा afu_config_record), GFP_KERNEL);
	अगर (!cr)
		वापस ERR_PTR(-ENOMEM);

	cr->cr = cr_idx;

	rc = cxl_ops->afu_cr_पढ़ो16(afu, cr_idx, PCI_DEVICE_ID, &cr->device);
	अगर (rc)
		जाओ err;
	rc = cxl_ops->afu_cr_पढ़ो16(afu, cr_idx, PCI_VENDOR_ID, &cr->venकरोr);
	अगर (rc)
		जाओ err;
	rc = cxl_ops->afu_cr_पढ़ो32(afu, cr_idx, PCI_CLASS_REVISION, &cr->class);
	अगर (rc)
		जाओ err;
	cr->class >>= 8;

	/*
	 * Export raw AFU PCIe like config record. For now this is पढ़ो only by
	 * root - we can expand that later to be पढ़ोable by non-root and maybe
	 * even writable provided we have a good use-हाल. Once we support
	 * exposing AFUs through a भव PHB they will get that क्रम मुक्त from
	 * Linux' PCI infrastructure, but until then it's not clear that we
	 * need it क्रम anything since the मुख्य use हाल is just identअगरying
	 * AFUs, which can be करोne via the venकरोr, device and class attributes.
	 */
	sysfs_bin_attr_init(&cr->config_attr);
	cr->config_attr.attr.name = "config";
	cr->config_attr.attr.mode = S_IRUSR;
	cr->config_attr.size = afu->crs_len;
	cr->config_attr.पढ़ो = afu_पढ़ो_config;

	rc = kobject_init_and_add(&cr->kobj, &afu_config_record_type,
				  &afu->dev.kobj, "cr%i", cr->cr);
	अगर (rc)
		जाओ err1;

	rc = sysfs_create_bin_file(&cr->kobj, &cr->config_attr);
	अगर (rc)
		जाओ err1;

	rc = kobject_uevent(&cr->kobj, KOBJ_ADD);
	अगर (rc)
		जाओ err2;

	वापस cr;
err2:
	sysfs_हटाओ_bin_file(&cr->kobj, &cr->config_attr);
err1:
	kobject_put(&cr->kobj);
	वापस ERR_PTR(rc);
err:
	kमुक्त(cr);
	वापस ERR_PTR(rc);
पूर्ण

व्योम cxl_sysfs_afu_हटाओ(काष्ठा cxl_afu *afu)
अणु
	काष्ठा device_attribute *dev_attr;
	काष्ठा afu_config_record *cr, *पंचांगp;
	पूर्णांक i;

	/* हटाओ the err buffer bin attribute */
	अगर (afu->eb_len)
		device_हटाओ_bin_file(&afu->dev, &afu->attr_eb);

	क्रम (i = 0; i < ARRAY_SIZE(afu_attrs); i++) अणु
		dev_attr = &afu_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_ATTRS))
			device_हटाओ_file(&afu->dev, &afu_attrs[i]);
	पूर्ण

	list_क्रम_each_entry_safe(cr, पंचांगp, &afu->crs, list) अणु
		sysfs_हटाओ_bin_file(&cr->kobj, &cr->config_attr);
		kobject_put(&cr->kobj);
	पूर्ण
पूर्ण

पूर्णांक cxl_sysfs_afu_add(काष्ठा cxl_afu *afu)
अणु
	काष्ठा device_attribute *dev_attr;
	काष्ठा afu_config_record *cr;
	पूर्णांक i, rc;

	INIT_LIST_HEAD(&afu->crs);

	क्रम (i = 0; i < ARRAY_SIZE(afu_attrs); i++) अणु
		dev_attr = &afu_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_ATTRS)) अणु
			अगर ((rc = device_create_file(&afu->dev, &afu_attrs[i])))
				जाओ err;
		पूर्ण
	पूर्ण

	/* conditionally create the add the binary file क्रम error info buffer */
	अगर (afu->eb_len) अणु
		sysfs_attr_init(&afu->attr_eb.attr);

		afu->attr_eb.attr.name = "afu_err_buff";
		afu->attr_eb.attr.mode = S_IRUGO;
		afu->attr_eb.size = afu->eb_len;
		afu->attr_eb.पढ़ो = afu_eb_पढ़ो;

		rc = device_create_bin_file(&afu->dev, &afu->attr_eb);
		अगर (rc) अणु
			dev_err(&afu->dev,
				"Unable to create eb attr for the afu. Err(%d)\n",
				rc);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < afu->crs_num; i++) अणु
		cr = cxl_sysfs_afu_new_cr(afu, i);
		अगर (IS_ERR(cr)) अणु
			rc = PTR_ERR(cr);
			जाओ err1;
		पूर्ण
		list_add(&cr->list, &afu->crs);
	पूर्ण

	वापस 0;

err1:
	cxl_sysfs_afu_हटाओ(afu);
	वापस rc;
err:
	/* reset the eb_len as we havent created the bin attr */
	afu->eb_len = 0;

	क्रम (i--; i >= 0; i--) अणु
		dev_attr = &afu_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_ATTRS))
		device_हटाओ_file(&afu->dev, &afu_attrs[i]);
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक cxl_sysfs_afu_m_add(काष्ठा cxl_afu *afu)
अणु
	काष्ठा device_attribute *dev_attr;
	पूर्णांक i, rc;

	क्रम (i = 0; i < ARRAY_SIZE(afu_master_attrs); i++) अणु
		dev_attr = &afu_master_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_MASTER_ATTRS)) अणु
			अगर ((rc = device_create_file(afu->अक्षरdev_m, &afu_master_attrs[i])))
				जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (i--; i >= 0; i--) अणु
		dev_attr = &afu_master_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_MASTER_ATTRS))
			device_हटाओ_file(afu->अक्षरdev_m, &afu_master_attrs[i]);
	पूर्ण
	वापस rc;
पूर्ण

व्योम cxl_sysfs_afu_m_हटाओ(काष्ठा cxl_afu *afu)
अणु
	काष्ठा device_attribute *dev_attr;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(afu_master_attrs); i++) अणु
		dev_attr = &afu_master_attrs[i];
		अगर (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_MASTER_ATTRS))
			device_हटाओ_file(afu->अक्षरdev_m, &afu_master_attrs[i]);
	पूर्ण
पूर्ण
