<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * configfs to configure the PCI endpoपूर्णांक
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>

#समावेश <linux/pci-epc.h>
#समावेश <linux/pci-epf.h>
#समावेश <linux/pci-ep-cfs.h>

अटल DEFINE_IDR(functions_idr);
अटल DEFINE_MUTEX(functions_mutex);
अटल काष्ठा config_group *functions_group;
अटल काष्ठा config_group *controllers_group;

काष्ठा pci_epf_group अणु
	काष्ठा config_group group;
	काष्ठा config_group primary_epc_group;
	काष्ठा config_group secondary_epc_group;
	काष्ठा delayed_work cfs_work;
	काष्ठा pci_epf *epf;
	पूर्णांक index;
पूर्ण;

काष्ठा pci_epc_group अणु
	काष्ठा config_group group;
	काष्ठा pci_epc *epc;
	bool start;
पूर्ण;

अटल अंतरभूत काष्ठा pci_epf_group *to_pci_epf_group(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा pci_epf_group, group);
पूर्ण

अटल अंतरभूत काष्ठा pci_epc_group *to_pci_epc_group(काष्ठा config_item *item)
अणु
	वापस container_of(to_config_group(item), काष्ठा pci_epc_group, group);
पूर्ण

अटल पूर्णांक pci_secondary_epc_epf_link(काष्ठा config_item *epf_item,
				      काष्ठा config_item *epc_item)
अणु
	पूर्णांक ret;
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item->ci_parent);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	काष्ठा pci_epc *epc = epc_group->epc;
	काष्ठा pci_epf *epf = epf_group->epf;

	ret = pci_epc_add_epf(epc, epf, SECONDARY_INTERFACE);
	अगर (ret)
		वापस ret;

	ret = pci_epf_bind(epf);
	अगर (ret) अणु
		pci_epc_हटाओ_epf(epc, epf, SECONDARY_INTERFACE);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_secondary_epc_epf_unlink(काष्ठा config_item *epc_item,
					 काष्ठा config_item *epf_item)
अणु
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item->ci_parent);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	काष्ठा pci_epc *epc;
	काष्ठा pci_epf *epf;

	WARN_ON_ONCE(epc_group->start);

	epc = epc_group->epc;
	epf = epf_group->epf;
	pci_epf_unbind(epf);
	pci_epc_हटाओ_epf(epc, epf, SECONDARY_INTERFACE);
पूर्ण

अटल काष्ठा configfs_item_operations pci_secondary_epc_item_ops = अणु
	.allow_link	= pci_secondary_epc_epf_link,
	.drop_link	= pci_secondary_epc_epf_unlink,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_secondary_epc_type = अणु
	.ct_item_ops	= &pci_secondary_epc_item_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group
*pci_ep_cfs_add_secondary_group(काष्ठा pci_epf_group *epf_group)
अणु
	काष्ठा config_group *secondary_epc_group;

	secondary_epc_group = &epf_group->secondary_epc_group;
	config_group_init_type_name(secondary_epc_group, "secondary",
				    &pci_secondary_epc_type);
	configfs_रेजिस्टर_group(&epf_group->group, secondary_epc_group);

	वापस secondary_epc_group;
पूर्ण

अटल पूर्णांक pci_primary_epc_epf_link(काष्ठा config_item *epf_item,
				    काष्ठा config_item *epc_item)
अणु
	पूर्णांक ret;
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item->ci_parent);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	काष्ठा pci_epc *epc = epc_group->epc;
	काष्ठा pci_epf *epf = epf_group->epf;

	ret = pci_epc_add_epf(epc, epf, PRIMARY_INTERFACE);
	अगर (ret)
		वापस ret;

	ret = pci_epf_bind(epf);
	अगर (ret) अणु
		pci_epc_हटाओ_epf(epc, epf, PRIMARY_INTERFACE);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_primary_epc_epf_unlink(काष्ठा config_item *epc_item,
				       काष्ठा config_item *epf_item)
अणु
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item->ci_parent);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	काष्ठा pci_epc *epc;
	काष्ठा pci_epf *epf;

	WARN_ON_ONCE(epc_group->start);

	epc = epc_group->epc;
	epf = epf_group->epf;
	pci_epf_unbind(epf);
	pci_epc_हटाओ_epf(epc, epf, PRIMARY_INTERFACE);
पूर्ण

अटल काष्ठा configfs_item_operations pci_primary_epc_item_ops = अणु
	.allow_link	= pci_primary_epc_epf_link,
	.drop_link	= pci_primary_epc_epf_unlink,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_primary_epc_type = अणु
	.ct_item_ops	= &pci_primary_epc_item_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा config_group
*pci_ep_cfs_add_primary_group(काष्ठा pci_epf_group *epf_group)
अणु
	काष्ठा config_group *primary_epc_group = &epf_group->primary_epc_group;

	config_group_init_type_name(primary_epc_group, "primary",
				    &pci_primary_epc_type);
	configfs_रेजिस्टर_group(&epf_group->group, primary_epc_group);

	वापस primary_epc_group;
पूर्ण

अटल sमाप_प्रकार pci_epc_start_store(काष्ठा config_item *item, स्थिर अक्षर *page,
				   माप_प्रकार len)
अणु
	पूर्णांक ret;
	bool start;
	काष्ठा pci_epc *epc;
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(item);

	epc = epc_group->epc;

	ret = kstrtobool(page, &start);
	अगर (ret)
		वापस ret;

	अगर (!start) अणु
		pci_epc_stop(epc);
		epc_group->start = 0;
		वापस len;
	पूर्ण

	ret = pci_epc_start(epc);
	अगर (ret) अणु
		dev_err(&epc->dev, "failed to start endpoint controller\n");
		वापस -EINVAL;
	पूर्ण

	epc_group->start = start;

	वापस len;
पूर्ण

अटल sमाप_प्रकार pci_epc_start_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		       to_pci_epc_group(item)->start);
पूर्ण

CONFIGFS_ATTR(pci_epc_, start);

अटल काष्ठा configfs_attribute *pci_epc_attrs[] = अणु
	&pci_epc_attr_start,
	शून्य,
पूर्ण;

अटल पूर्णांक pci_epc_epf_link(काष्ठा config_item *epc_item,
			    काष्ठा config_item *epf_item)
अणु
	पूर्णांक ret;
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);
	काष्ठा pci_epc *epc = epc_group->epc;
	काष्ठा pci_epf *epf = epf_group->epf;

	ret = pci_epc_add_epf(epc, epf, PRIMARY_INTERFACE);
	अगर (ret)
		वापस ret;

	ret = pci_epf_bind(epf);
	अगर (ret) अणु
		pci_epc_हटाओ_epf(epc, epf, PRIMARY_INTERFACE);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pci_epc_epf_unlink(काष्ठा config_item *epc_item,
			       काष्ठा config_item *epf_item)
अणु
	काष्ठा pci_epc *epc;
	काष्ठा pci_epf *epf;
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(epf_item);
	काष्ठा pci_epc_group *epc_group = to_pci_epc_group(epc_item);

	WARN_ON_ONCE(epc_group->start);

	epc = epc_group->epc;
	epf = epf_group->epf;
	pci_epf_unbind(epf);
	pci_epc_हटाओ_epf(epc, epf, PRIMARY_INTERFACE);
पूर्ण

अटल काष्ठा configfs_item_operations pci_epc_item_ops = अणु
	.allow_link	= pci_epc_epf_link,
	.drop_link	= pci_epc_epf_unlink,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_epc_type = अणु
	.ct_item_ops	= &pci_epc_item_ops,
	.ct_attrs	= pci_epc_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

काष्ठा config_group *pci_ep_cfs_add_epc_group(स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा pci_epc *epc;
	काष्ठा config_group *group;
	काष्ठा pci_epc_group *epc_group;

	epc_group = kzalloc(माप(*epc_group), GFP_KERNEL);
	अगर (!epc_group) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	group = &epc_group->group;

	config_group_init_type_name(group, name, &pci_epc_type);
	ret = configfs_रेजिस्टर_group(controllers_group, group);
	अगर (ret) अणु
		pr_err("failed to register configfs group for %s\n", name);
		जाओ err_रेजिस्टर_group;
	पूर्ण

	epc = pci_epc_get(name);
	अगर (IS_ERR(epc)) अणु
		ret = PTR_ERR(epc);
		जाओ err_epc_get;
	पूर्ण

	epc_group->epc = epc;

	वापस group;

err_epc_get:
	configfs_unरेजिस्टर_group(group);

err_रेजिस्टर_group:
	kमुक्त(epc_group);

err:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(pci_ep_cfs_add_epc_group);

व्योम pci_ep_cfs_हटाओ_epc_group(काष्ठा config_group *group)
अणु
	काष्ठा pci_epc_group *epc_group;

	अगर (!group)
		वापस;

	epc_group = container_of(group, काष्ठा pci_epc_group, group);
	pci_epc_put(epc_group->epc);
	configfs_unरेजिस्टर_group(&epc_group->group);
	kमुक्त(epc_group);
पूर्ण
EXPORT_SYMBOL(pci_ep_cfs_हटाओ_epc_group);

#घोषणा PCI_EPF_HEADER_R(_name)						       \
अटल sमाप_प्रकार pci_epf_##_name##_show(काष्ठा config_item *item,	अक्षर *page)    \
अणु									       \
	काष्ठा pci_epf *epf = to_pci_epf_group(item)->epf;		       \
	अगर (WARN_ON_ONCE(!epf->header))					       \
		वापस -EINVAL;						       \
	वापस प्र_लिखो(page, "0x%04x\n", epf->header->_name);		       \
पूर्ण

#घोषणा PCI_EPF_HEADER_W_u32(_name)					       \
अटल sमाप_प्रकार pci_epf_##_name##_store(काष्ठा config_item *item,	       \
				       स्थिर अक्षर *page, माप_प्रकार len)	       \
अणु									       \
	u32 val;							       \
	पूर्णांक ret;							       \
	काष्ठा pci_epf *epf = to_pci_epf_group(item)->epf;		       \
	अगर (WARN_ON_ONCE(!epf->header))					       \
		वापस -EINVAL;						       \
	ret = kstrtou32(page, 0, &val);					       \
	अगर (ret)							       \
		वापस ret;						       \
	epf->header->_name = val;					       \
	वापस len;							       \
पूर्ण

#घोषणा PCI_EPF_HEADER_W_u16(_name)					       \
अटल sमाप_प्रकार pci_epf_##_name##_store(काष्ठा config_item *item,	       \
				       स्थिर अक्षर *page, माप_प्रकार len)	       \
अणु									       \
	u16 val;							       \
	पूर्णांक ret;							       \
	काष्ठा pci_epf *epf = to_pci_epf_group(item)->epf;		       \
	अगर (WARN_ON_ONCE(!epf->header))					       \
		वापस -EINVAL;						       \
	ret = kstrtou16(page, 0, &val);					       \
	अगर (ret)							       \
		वापस ret;						       \
	epf->header->_name = val;					       \
	वापस len;							       \
पूर्ण

#घोषणा PCI_EPF_HEADER_W_u8(_name)					       \
अटल sमाप_प्रकार pci_epf_##_name##_store(काष्ठा config_item *item,	       \
				       स्थिर अक्षर *page, माप_प्रकार len)	       \
अणु									       \
	u8 val;								       \
	पूर्णांक ret;							       \
	काष्ठा pci_epf *epf = to_pci_epf_group(item)->epf;		       \
	अगर (WARN_ON_ONCE(!epf->header))					       \
		वापस -EINVAL;						       \
	ret = kstrtou8(page, 0, &val);					       \
	अगर (ret)							       \
		वापस ret;						       \
	epf->header->_name = val;					       \
	वापस len;							       \
पूर्ण

अटल sमाप_प्रकार pci_epf_msi_पूर्णांकerrupts_store(काष्ठा config_item *item,
					    स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u8 val;
	पूर्णांक ret;

	ret = kstrtou8(page, 0, &val);
	अगर (ret)
		वापस ret;

	to_pci_epf_group(item)->epf->msi_पूर्णांकerrupts = val;

	वापस len;
पूर्ण

अटल sमाप_प्रकार pci_epf_msi_पूर्णांकerrupts_show(काष्ठा config_item *item,
					   अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		       to_pci_epf_group(item)->epf->msi_पूर्णांकerrupts);
पूर्ण

अटल sमाप_प्रकार pci_epf_msix_पूर्णांकerrupts_store(काष्ठा config_item *item,
					     स्थिर अक्षर *page, माप_प्रकार len)
अणु
	u16 val;
	पूर्णांक ret;

	ret = kstrtou16(page, 0, &val);
	अगर (ret)
		वापस ret;

	to_pci_epf_group(item)->epf->msix_पूर्णांकerrupts = val;

	वापस len;
पूर्ण

अटल sमाप_प्रकार pci_epf_msix_पूर्णांकerrupts_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n",
		       to_pci_epf_group(item)->epf->msix_पूर्णांकerrupts);
पूर्ण

PCI_EPF_HEADER_R(venकरोrid)
PCI_EPF_HEADER_W_u16(venकरोrid)

PCI_EPF_HEADER_R(deviceid)
PCI_EPF_HEADER_W_u16(deviceid)

PCI_EPF_HEADER_R(revid)
PCI_EPF_HEADER_W_u8(revid)

PCI_EPF_HEADER_R(progअगर_code)
PCI_EPF_HEADER_W_u8(progअगर_code)

PCI_EPF_HEADER_R(subclass_code)
PCI_EPF_HEADER_W_u8(subclass_code)

PCI_EPF_HEADER_R(baseclass_code)
PCI_EPF_HEADER_W_u8(baseclass_code)

PCI_EPF_HEADER_R(cache_line_size)
PCI_EPF_HEADER_W_u8(cache_line_size)

PCI_EPF_HEADER_R(subsys_venकरोr_id)
PCI_EPF_HEADER_W_u16(subsys_venकरोr_id)

PCI_EPF_HEADER_R(subsys_id)
PCI_EPF_HEADER_W_u16(subsys_id)

PCI_EPF_HEADER_R(पूर्णांकerrupt_pin)
PCI_EPF_HEADER_W_u8(पूर्णांकerrupt_pin)

CONFIGFS_ATTR(pci_epf_, venकरोrid);
CONFIGFS_ATTR(pci_epf_, deviceid);
CONFIGFS_ATTR(pci_epf_, revid);
CONFIGFS_ATTR(pci_epf_, progअगर_code);
CONFIGFS_ATTR(pci_epf_, subclass_code);
CONFIGFS_ATTR(pci_epf_, baseclass_code);
CONFIGFS_ATTR(pci_epf_, cache_line_size);
CONFIGFS_ATTR(pci_epf_, subsys_venकरोr_id);
CONFIGFS_ATTR(pci_epf_, subsys_id);
CONFIGFS_ATTR(pci_epf_, पूर्णांकerrupt_pin);
CONFIGFS_ATTR(pci_epf_, msi_पूर्णांकerrupts);
CONFIGFS_ATTR(pci_epf_, msix_पूर्णांकerrupts);

अटल काष्ठा configfs_attribute *pci_epf_attrs[] = अणु
	&pci_epf_attr_venकरोrid,
	&pci_epf_attr_deviceid,
	&pci_epf_attr_revid,
	&pci_epf_attr_progअगर_code,
	&pci_epf_attr_subclass_code,
	&pci_epf_attr_baseclass_code,
	&pci_epf_attr_cache_line_size,
	&pci_epf_attr_subsys_venकरोr_id,
	&pci_epf_attr_subsys_id,
	&pci_epf_attr_पूर्णांकerrupt_pin,
	&pci_epf_attr_msi_पूर्णांकerrupts,
	&pci_epf_attr_msix_पूर्णांकerrupts,
	शून्य,
पूर्ण;

अटल व्योम pci_epf_release(काष्ठा config_item *item)
अणु
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(item);

	mutex_lock(&functions_mutex);
	idr_हटाओ(&functions_idr, epf_group->index);
	mutex_unlock(&functions_mutex);
	pci_epf_destroy(epf_group->epf);
	kमुक्त(epf_group);
पूर्ण

अटल काष्ठा configfs_item_operations pci_epf_ops = अणु
	.release		= pci_epf_release,
पूर्ण;

अटल काष्ठा config_group *pci_epf_type_make(काष्ठा config_group *group,
					      स्थिर अक्षर *name)
अणु
	काष्ठा pci_epf_group *epf_group = to_pci_epf_group(&group->cg_item);
	काष्ठा config_group *epf_type_group;

	epf_type_group = pci_epf_type_add_cfs(epf_group->epf, group);
	वापस epf_type_group;
पूर्ण

अटल व्योम pci_epf_type_drop(काष्ठा config_group *group,
			      काष्ठा config_item *item)
अणु
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations pci_epf_type_group_ops = अणु
	.make_group     = &pci_epf_type_make,
	.drop_item      = &pci_epf_type_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_epf_type = अणु
	.ct_group_ops	= &pci_epf_type_group_ops,
	.ct_item_ops	= &pci_epf_ops,
	.ct_attrs	= pci_epf_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल व्योम pci_epf_cfs_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pci_epf_group *epf_group;
	काष्ठा config_group *group;

	epf_group = container_of(work, काष्ठा pci_epf_group, cfs_work.work);
	group = pci_ep_cfs_add_primary_group(epf_group);
	अगर (IS_ERR(group)) अणु
		pr_err("failed to create 'primary' EPC interface\n");
		वापस;
	पूर्ण

	group = pci_ep_cfs_add_secondary_group(epf_group);
	अगर (IS_ERR(group)) अणु
		pr_err("failed to create 'secondary' EPC interface\n");
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा config_group *pci_epf_make(काष्ठा config_group *group,
					 स्थिर अक्षर *name)
अणु
	काष्ठा pci_epf_group *epf_group;
	काष्ठा pci_epf *epf;
	अक्षर *epf_name;
	पूर्णांक index, err;

	epf_group = kzalloc(माप(*epf_group), GFP_KERNEL);
	अगर (!epf_group)
		वापस ERR_PTR(-ENOMEM);

	mutex_lock(&functions_mutex);
	index = idr_alloc(&functions_idr, epf_group, 0, 0, GFP_KERNEL);
	mutex_unlock(&functions_mutex);
	अगर (index < 0) अणु
		err = index;
		जाओ मुक्त_group;
	पूर्ण

	epf_group->index = index;

	config_group_init_type_name(&epf_group->group, name, &pci_epf_type);

	epf_name = kaप्र_लिखो(GFP_KERNEL, "%s.%d",
			     group->cg_item.ci_name, epf_group->index);
	अगर (!epf_name) अणु
		err = -ENOMEM;
		जाओ हटाओ_idr;
	पूर्ण

	epf = pci_epf_create(epf_name);
	अगर (IS_ERR(epf)) अणु
		pr_err("failed to create endpoint function device\n");
		err = -EINVAL;
		जाओ मुक्त_name;
	पूर्ण

	epf->group = &epf_group->group;
	epf_group->epf = epf;

	kमुक्त(epf_name);

	INIT_DELAYED_WORK(&epf_group->cfs_work, pci_epf_cfs_work);
	queue_delayed_work(प्रणाली_wq, &epf_group->cfs_work,
			   msecs_to_jअगरfies(1));

	वापस &epf_group->group;

मुक्त_name:
	kमुक्त(epf_name);

हटाओ_idr:
	mutex_lock(&functions_mutex);
	idr_हटाओ(&functions_idr, epf_group->index);
	mutex_unlock(&functions_mutex);

मुक्त_group:
	kमुक्त(epf_group);

	वापस ERR_PTR(err);
पूर्ण

अटल व्योम pci_epf_drop(काष्ठा config_group *group, काष्ठा config_item *item)
अणु
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations pci_epf_group_ops = अणु
	.make_group     = &pci_epf_make,
	.drop_item      = &pci_epf_drop,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_epf_group_type = अणु
	.ct_group_ops	= &pci_epf_group_ops,
	.ct_owner	= THIS_MODULE,
पूर्ण;

काष्ठा config_group *pci_ep_cfs_add_epf_group(स्थिर अक्षर *name)
अणु
	काष्ठा config_group *group;

	group = configfs_रेजिस्टर_शेष_group(functions_group, name,
						&pci_epf_group_type);
	अगर (IS_ERR(group))
		pr_err("failed to register configfs group for %s function\n",
		       name);

	वापस group;
पूर्ण
EXPORT_SYMBOL(pci_ep_cfs_add_epf_group);

व्योम pci_ep_cfs_हटाओ_epf_group(काष्ठा config_group *group)
अणु
	अगर (IS_ERR_OR_शून्य(group))
		वापस;

	configfs_unरेजिस्टर_शेष_group(group);
पूर्ण
EXPORT_SYMBOL(pci_ep_cfs_हटाओ_epf_group);

अटल स्थिर काष्ठा config_item_type pci_functions_type = अणु
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_controllers_type = अणु
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा config_item_type pci_ep_type = अणु
	.ct_owner	= THIS_MODULE,
पूर्ण;

अटल काष्ठा configfs_subप्रणाली pci_ep_cfs_subsys = अणु
	.su_group = अणु
		.cg_item = अणु
			.ci_namebuf = "pci_ep",
			.ci_type = &pci_ep_type,
		पूर्ण,
	पूर्ण,
	.su_mutex = __MUTEX_INITIALIZER(pci_ep_cfs_subsys.su_mutex),
पूर्ण;

अटल पूर्णांक __init pci_ep_cfs_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा config_group *root = &pci_ep_cfs_subsys.su_group;

	config_group_init(root);

	ret = configfs_रेजिस्टर_subप्रणाली(&pci_ep_cfs_subsys);
	अगर (ret) अणु
		pr_err("Error %d while registering subsystem %s\n",
		       ret, root->cg_item.ci_namebuf);
		जाओ err;
	पूर्ण

	functions_group = configfs_रेजिस्टर_शेष_group(root, "functions",
							  &pci_functions_type);
	अगर (IS_ERR(functions_group)) अणु
		ret = PTR_ERR(functions_group);
		pr_err("Error %d while registering functions group\n",
		       ret);
		जाओ err_functions_group;
	पूर्ण

	controllers_group =
		configfs_रेजिस्टर_शेष_group(root, "controllers",
						&pci_controllers_type);
	अगर (IS_ERR(controllers_group)) अणु
		ret = PTR_ERR(controllers_group);
		pr_err("Error %d while registering controllers group\n",
		       ret);
		जाओ err_controllers_group;
	पूर्ण

	वापस 0;

err_controllers_group:
	configfs_unरेजिस्टर_शेष_group(functions_group);

err_functions_group:
	configfs_unरेजिस्टर_subप्रणाली(&pci_ep_cfs_subsys);

err:
	वापस ret;
पूर्ण
module_init(pci_ep_cfs_init);

अटल व्योम __निकास pci_ep_cfs_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_शेष_group(controllers_group);
	configfs_unरेजिस्टर_शेष_group(functions_group);
	configfs_unरेजिस्टर_subप्रणाली(&pci_ep_cfs_subsys);
पूर्ण
module_निकास(pci_ep_cfs_निकास);

MODULE_DESCRIPTION("PCI EP CONFIGFS");
MODULE_AUTHOR("Kishon Vijay Abraham I <kishon@ti.com>");
MODULE_LICENSE("GPL v2");
