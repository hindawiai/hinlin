<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO-KVM bridge pseuकरो device
 *
 * Copyright (C) 2013 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/file.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश "vfio.h"

#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
#समावेश <यंत्र/kvm_ppc.h>
#पूर्ण_अगर

काष्ठा kvm_vfio_group अणु
	काष्ठा list_head node;
	काष्ठा vfio_group *vfio_group;
पूर्ण;

काष्ठा kvm_vfio अणु
	काष्ठा list_head group_list;
	काष्ठा mutex lock;
	bool noncoherent;
पूर्ण;

अटल काष्ठा vfio_group *kvm_vfio_group_get_बाह्यal_user(काष्ठा file *filep)
अणु
	काष्ठा vfio_group *vfio_group;
	काष्ठा vfio_group *(*fn)(काष्ठा file *);

	fn = symbol_get(vfio_group_get_बाह्यal_user);
	अगर (!fn)
		वापस ERR_PTR(-EINVAL);

	vfio_group = fn(filep);

	symbol_put(vfio_group_get_बाह्यal_user);

	वापस vfio_group;
पूर्ण

अटल bool kvm_vfio_बाह्यal_group_match_file(काष्ठा vfio_group *group,
					       काष्ठा file *filep)
अणु
	bool ret, (*fn)(काष्ठा vfio_group *, काष्ठा file *);

	fn = symbol_get(vfio_बाह्यal_group_match_file);
	अगर (!fn)
		वापस false;

	ret = fn(group, filep);

	symbol_put(vfio_बाह्यal_group_match_file);

	वापस ret;
पूर्ण

अटल व्योम kvm_vfio_group_put_बाह्यal_user(काष्ठा vfio_group *vfio_group)
अणु
	व्योम (*fn)(काष्ठा vfio_group *);

	fn = symbol_get(vfio_group_put_बाह्यal_user);
	अगर (!fn)
		वापस;

	fn(vfio_group);

	symbol_put(vfio_group_put_बाह्यal_user);
पूर्ण

अटल व्योम kvm_vfio_group_set_kvm(काष्ठा vfio_group *group, काष्ठा kvm *kvm)
अणु
	व्योम (*fn)(काष्ठा vfio_group *, काष्ठा kvm *);

	fn = symbol_get(vfio_group_set_kvm);
	अगर (!fn)
		वापस;

	fn(group, kvm);

	symbol_put(vfio_group_set_kvm);
पूर्ण

अटल bool kvm_vfio_group_is_coherent(काष्ठा vfio_group *vfio_group)
अणु
	दीर्घ (*fn)(काष्ठा vfio_group *, अचिन्हित दीर्घ);
	दीर्घ ret;

	fn = symbol_get(vfio_बाह्यal_check_extension);
	अगर (!fn)
		वापस false;

	ret = fn(vfio_group, VFIO_DMA_CC_IOMMU);

	symbol_put(vfio_बाह्यal_check_extension);

	वापस ret > 0;
पूर्ण

#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
अटल पूर्णांक kvm_vfio_बाह्यal_user_iommu_id(काष्ठा vfio_group *vfio_group)
अणु
	पूर्णांक (*fn)(काष्ठा vfio_group *);
	पूर्णांक ret = -EINVAL;

	fn = symbol_get(vfio_बाह्यal_user_iommu_id);
	अगर (!fn)
		वापस ret;

	ret = fn(vfio_group);

	symbol_put(vfio_बाह्यal_user_iommu_id);

	वापस ret;
पूर्ण

अटल काष्ठा iommu_group *kvm_vfio_group_get_iommu_group(
		काष्ठा vfio_group *group)
अणु
	पूर्णांक group_id = kvm_vfio_बाह्यal_user_iommu_id(group);

	अगर (group_id < 0)
		वापस शून्य;

	वापस iommu_group_get_by_id(group_id);
पूर्ण

अटल व्योम kvm_spapr_tce_release_vfio_group(काष्ठा kvm *kvm,
		काष्ठा vfio_group *vfio_group)
अणु
	काष्ठा iommu_group *grp = kvm_vfio_group_get_iommu_group(vfio_group);

	अगर (WARN_ON_ONCE(!grp))
		वापस;

	kvm_spapr_tce_release_iommu_group(kvm, grp);
	iommu_group_put(grp);
पूर्ण
#पूर्ण_अगर

/*
 * Groups can use the same or dअगरferent IOMMU करोमुख्यs.  If the same then
 * adding a new group may change the coherency of groups we've previously
 * been told about.  We करोn't want to care about any of that so we retest
 * each group and bail as soon as we find one that's noncoherent.  This
 * means we only ever [un]रेजिस्टर_noncoherent_dma once क्रम the whole device.
 */
अटल व्योम kvm_vfio_update_coherency(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvm_vfio *kv = dev->निजी;
	bool noncoherent = false;
	काष्ठा kvm_vfio_group *kvg;

	mutex_lock(&kv->lock);

	list_क्रम_each_entry(kvg, &kv->group_list, node) अणु
		अगर (!kvm_vfio_group_is_coherent(kvg->vfio_group)) अणु
			noncoherent = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (noncoherent != kv->noncoherent) अणु
		kv->noncoherent = noncoherent;

		अगर (kv->noncoherent)
			kvm_arch_रेजिस्टर_noncoherent_dma(dev->kvm);
		अन्यथा
			kvm_arch_unरेजिस्टर_noncoherent_dma(dev->kvm);
	पूर्ण

	mutex_unlock(&kv->lock);
पूर्ण

अटल पूर्णांक kvm_vfio_set_group(काष्ठा kvm_device *dev, दीर्घ attr, u64 arg)
अणु
	काष्ठा kvm_vfio *kv = dev->निजी;
	काष्ठा vfio_group *vfio_group;
	काष्ठा kvm_vfio_group *kvg;
	पूर्णांक32_t __user *argp = (पूर्णांक32_t __user *)(अचिन्हित दीर्घ)arg;
	काष्ठा fd f;
	पूर्णांक32_t fd;
	पूर्णांक ret;

	चयन (attr) अणु
	हाल KVM_DEV_VFIO_GROUP_ADD:
		अगर (get_user(fd, argp))
			वापस -EFAULT;

		f = fdget(fd);
		अगर (!f.file)
			वापस -EBADF;

		vfio_group = kvm_vfio_group_get_बाह्यal_user(f.file);
		fdput(f);

		अगर (IS_ERR(vfio_group))
			वापस PTR_ERR(vfio_group);

		mutex_lock(&kv->lock);

		list_क्रम_each_entry(kvg, &kv->group_list, node) अणु
			अगर (kvg->vfio_group == vfio_group) अणु
				mutex_unlock(&kv->lock);
				kvm_vfio_group_put_बाह्यal_user(vfio_group);
				वापस -EEXIST;
			पूर्ण
		पूर्ण

		kvg = kzalloc(माप(*kvg), GFP_KERNEL_ACCOUNT);
		अगर (!kvg) अणु
			mutex_unlock(&kv->lock);
			kvm_vfio_group_put_बाह्यal_user(vfio_group);
			वापस -ENOMEM;
		पूर्ण

		list_add_tail(&kvg->node, &kv->group_list);
		kvg->vfio_group = vfio_group;

		kvm_arch_start_assignment(dev->kvm);

		mutex_unlock(&kv->lock);

		kvm_vfio_group_set_kvm(vfio_group, dev->kvm);

		kvm_vfio_update_coherency(dev);

		वापस 0;

	हाल KVM_DEV_VFIO_GROUP_DEL:
		अगर (get_user(fd, argp))
			वापस -EFAULT;

		f = fdget(fd);
		अगर (!f.file)
			वापस -EBADF;

		ret = -ENOENT;

		mutex_lock(&kv->lock);

		list_क्रम_each_entry(kvg, &kv->group_list, node) अणु
			अगर (!kvm_vfio_बाह्यal_group_match_file(kvg->vfio_group,
								f.file))
				जारी;

			list_del(&kvg->node);
			kvm_arch_end_assignment(dev->kvm);
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
			kvm_spapr_tce_release_vfio_group(dev->kvm,
							 kvg->vfio_group);
#पूर्ण_अगर
			kvm_vfio_group_set_kvm(kvg->vfio_group, शून्य);
			kvm_vfio_group_put_बाह्यal_user(kvg->vfio_group);
			kमुक्त(kvg);
			ret = 0;
			अवरोध;
		पूर्ण

		mutex_unlock(&kv->lock);

		fdput(f);

		kvm_vfio_update_coherency(dev);

		वापस ret;

#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	हाल KVM_DEV_VFIO_GROUP_SET_SPAPR_TCE: अणु
		काष्ठा kvm_vfio_spapr_tce param;
		काष्ठा kvm_vfio *kv = dev->निजी;
		काष्ठा vfio_group *vfio_group;
		काष्ठा kvm_vfio_group *kvg;
		काष्ठा fd f;
		काष्ठा iommu_group *grp;

		अगर (copy_from_user(&param, (व्योम __user *)arg,
				माप(काष्ठा kvm_vfio_spapr_tce)))
			वापस -EFAULT;

		f = fdget(param.groupfd);
		अगर (!f.file)
			वापस -EBADF;

		vfio_group = kvm_vfio_group_get_बाह्यal_user(f.file);
		fdput(f);

		अगर (IS_ERR(vfio_group))
			वापस PTR_ERR(vfio_group);

		grp = kvm_vfio_group_get_iommu_group(vfio_group);
		अगर (WARN_ON_ONCE(!grp)) अणु
			kvm_vfio_group_put_बाह्यal_user(vfio_group);
			वापस -EIO;
		पूर्ण

		ret = -ENOENT;

		mutex_lock(&kv->lock);

		list_क्रम_each_entry(kvg, &kv->group_list, node) अणु
			अगर (kvg->vfio_group != vfio_group)
				जारी;

			ret = kvm_spapr_tce_attach_iommu_group(dev->kvm,
					param.tablefd, grp);
			अवरोध;
		पूर्ण

		mutex_unlock(&kv->lock);

		iommu_group_put(grp);
		kvm_vfio_group_put_बाह्यal_user(vfio_group);

		वापस ret;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SPAPR_TCE_IOMMU */
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvm_vfio_set_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_VFIO_GROUP:
		वापस kvm_vfio_set_group(dev, attr->attr, attr->addr);
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक kvm_vfio_has_attr(काष्ठा kvm_device *dev,
			     काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_VFIO_GROUP:
		चयन (attr->attr) अणु
		हाल KVM_DEV_VFIO_GROUP_ADD:
		हाल KVM_DEV_VFIO_GROUP_DEL:
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
		हाल KVM_DEV_VFIO_GROUP_SET_SPAPR_TCE:
#पूर्ण_अगर
			वापस 0;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल व्योम kvm_vfio_destroy(काष्ठा kvm_device *dev)
अणु
	काष्ठा kvm_vfio *kv = dev->निजी;
	काष्ठा kvm_vfio_group *kvg, *पंचांगp;

	list_क्रम_each_entry_safe(kvg, पंचांगp, &kv->group_list, node) अणु
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
		kvm_spapr_tce_release_vfio_group(dev->kvm, kvg->vfio_group);
#पूर्ण_अगर
		kvm_vfio_group_set_kvm(kvg->vfio_group, शून्य);
		kvm_vfio_group_put_बाह्यal_user(kvg->vfio_group);
		list_del(&kvg->node);
		kमुक्त(kvg);
		kvm_arch_end_assignment(dev->kvm);
	पूर्ण

	kvm_vfio_update_coherency(dev);

	kमुक्त(kv);
	kमुक्त(dev); /* alloc by kvm_ioctl_create_device, मुक्त by .destroy */
पूर्ण

अटल पूर्णांक kvm_vfio_create(काष्ठा kvm_device *dev, u32 type);

अटल काष्ठा kvm_device_ops kvm_vfio_ops = अणु
	.name = "kvm-vfio",
	.create = kvm_vfio_create,
	.destroy = kvm_vfio_destroy,
	.set_attr = kvm_vfio_set_attr,
	.has_attr = kvm_vfio_has_attr,
पूर्ण;

अटल पूर्णांक kvm_vfio_create(काष्ठा kvm_device *dev, u32 type)
अणु
	काष्ठा kvm_device *पंचांगp;
	काष्ठा kvm_vfio *kv;

	/* Only one VFIO "device" per VM */
	list_क्रम_each_entry(पंचांगp, &dev->kvm->devices, vm_node)
		अगर (पंचांगp->ops == &kvm_vfio_ops)
			वापस -EBUSY;

	kv = kzalloc(माप(*kv), GFP_KERNEL_ACCOUNT);
	अगर (!kv)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&kv->group_list);
	mutex_init(&kv->lock);

	dev->निजी = kv;

	वापस 0;
पूर्ण

पूर्णांक kvm_vfio_ops_init(व्योम)
अणु
	वापस kvm_रेजिस्टर_device_ops(&kvm_vfio_ops, KVM_DEV_TYPE_VFIO);
पूर्ण

व्योम kvm_vfio_ops_निकास(व्योम)
अणु
	kvm_unरेजिस्टर_device_ops(KVM_DEV_TYPE_VFIO);
पूर्ण
