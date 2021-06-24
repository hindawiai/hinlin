<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"
#समावेश "msm_mmu.h"

अटल व्योम
msm_gem_address_space_destroy(काष्ठा kref *kref)
अणु
	काष्ठा msm_gem_address_space *aspace = container_of(kref,
			काष्ठा msm_gem_address_space, kref);

	drm_mm_takeकरोwn(&aspace->mm);
	अगर (aspace->mmu)
		aspace->mmu->funcs->destroy(aspace->mmu);
	put_pid(aspace->pid);
	kमुक्त(aspace);
पूर्ण


व्योम msm_gem_address_space_put(काष्ठा msm_gem_address_space *aspace)
अणु
	अगर (aspace)
		kref_put(&aspace->kref, msm_gem_address_space_destroy);
पूर्ण

काष्ठा msm_gem_address_space *
msm_gem_address_space_get(काष्ठा msm_gem_address_space *aspace)
अणु
	अगर (!IS_ERR_OR_शून्य(aspace))
		kref_get(&aspace->kref);

	वापस aspace;
पूर्ण

/* Actually unmap memory क्रम the vma */
व्योम msm_gem_purge_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma)
अणु
	अचिन्हित size = vma->node.size << PAGE_SHIFT;

	/* Prपूर्णांक a message अगर we try to purge a vma in use */
	अगर (WARN_ON(vma->inuse > 0))
		वापस;

	/* Don't do anything if the memory isn't mapped */
	अगर (!vma->mapped)
		वापस;

	अगर (aspace->mmu)
		aspace->mmu->funcs->unmap(aspace->mmu, vma->iova, size);

	vma->mapped = false;
पूर्ण

/* Remove reference counts क्रम the mapping */
व्योम msm_gem_unmap_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma)
अणु
	अगर (!WARN_ON(!vma->iova))
		vma->inuse--;
पूर्ण

पूर्णांक
msm_gem_map_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma, पूर्णांक prot,
		काष्ठा sg_table *sgt, पूर्णांक npages)
अणु
	अचिन्हित size = npages << PAGE_SHIFT;
	पूर्णांक ret = 0;

	अगर (WARN_ON(!vma->iova))
		वापस -EINVAL;

	/* Increase the usage counter */
	vma->inuse++;

	अगर (vma->mapped)
		वापस 0;

	vma->mapped = true;

	अगर (aspace && aspace->mmu)
		ret = aspace->mmu->funcs->map(aspace->mmu, vma->iova, sgt,
				size, prot);

	अगर (ret) अणु
		vma->mapped = false;
		vma->inuse--;
	पूर्ण

	वापस ret;
पूर्ण

/* Close an iova.  Warn अगर it is still in use */
व्योम msm_gem_बंद_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma)
अणु
	अगर (WARN_ON(vma->inuse > 0 || vma->mapped))
		वापस;

	spin_lock(&aspace->lock);
	अगर (vma->iova)
		drm_mm_हटाओ_node(&vma->node);
	spin_unlock(&aspace->lock);

	vma->iova = 0;

	msm_gem_address_space_put(aspace);
पूर्ण

/* Initialize a new vma and allocate an iova क्रम it */
पूर्णांक msm_gem_init_vma(काष्ठा msm_gem_address_space *aspace,
		काष्ठा msm_gem_vma *vma, पूर्णांक npages,
		u64 range_start, u64 range_end)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(vma->iova))
		वापस -EBUSY;

	spin_lock(&aspace->lock);
	ret = drm_mm_insert_node_in_range(&aspace->mm, &vma->node, npages, 0,
		0, range_start, range_end, 0);
	spin_unlock(&aspace->lock);

	अगर (ret)
		वापस ret;

	vma->iova = vma->node.start << PAGE_SHIFT;
	vma->mapped = false;

	kref_get(&aspace->kref);

	वापस 0;
पूर्ण

काष्ठा msm_gem_address_space *
msm_gem_address_space_create(काष्ठा msm_mmu *mmu, स्थिर अक्षर *name,
		u64 बहु_शुरू, u64 size)
अणु
	काष्ठा msm_gem_address_space *aspace;

	अगर (IS_ERR(mmu))
		वापस ERR_CAST(mmu);

	aspace = kzalloc(माप(*aspace), GFP_KERNEL);
	अगर (!aspace)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&aspace->lock);
	aspace->name = name;
	aspace->mmu = mmu;

	drm_mm_init(&aspace->mm, बहु_शुरू >> PAGE_SHIFT, size >> PAGE_SHIFT);

	kref_init(&aspace->kref);

	वापस aspace;
पूर्ण
