<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helpers क्रम IOMMU drivers implementing SVA
 */
#समावेश <linux/mutex.h>
#समावेश <linux/sched/mm.h>

#समावेश "iommu-sva-lib.h"

अटल DEFINE_MUTEX(iommu_sva_lock);
अटल DECLARE_IOASID_SET(iommu_sva_pasid);

/**
 * iommu_sva_alloc_pasid - Allocate a PASID क्रम the mm
 * @mm: the mm
 * @min: minimum PASID value (inclusive)
 * @max: maximum PASID value (inclusive)
 *
 * Try to allocate a PASID क्रम this mm, or take a reference to the existing one
 * provided it fits within the [@min, @max] range. On success the PASID is
 * available in mm->pasid, and must be released with iommu_sva_मुक्त_pasid().
 * @min must be greater than 0, because 0 indicates an unused mm->pasid.
 *
 * Returns 0 on success and < 0 on error.
 */
पूर्णांक iommu_sva_alloc_pasid(काष्ठा mm_काष्ठा *mm, ioasid_t min, ioasid_t max)
अणु
	पूर्णांक ret = 0;
	ioasid_t pasid;

	अगर (min == INVALID_IOASID || max == INVALID_IOASID ||
	    min == 0 || max < min)
		वापस -EINVAL;

	mutex_lock(&iommu_sva_lock);
	अगर (mm->pasid) अणु
		अगर (mm->pasid >= min && mm->pasid <= max)
			ioasid_get(mm->pasid);
		अन्यथा
			ret = -EOVERFLOW;
	पूर्ण अन्यथा अणु
		pasid = ioasid_alloc(&iommu_sva_pasid, min, max, mm);
		अगर (pasid == INVALID_IOASID)
			ret = -ENOMEM;
		अन्यथा
			mm->pasid = pasid;
	पूर्ण
	mutex_unlock(&iommu_sva_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_alloc_pasid);

/**
 * iommu_sva_मुक्त_pasid - Release the mm's PASID
 * @mm: the mm
 *
 * Drop one reference to a PASID allocated with iommu_sva_alloc_pasid()
 */
व्योम iommu_sva_मुक्त_pasid(काष्ठा mm_काष्ठा *mm)
अणु
	mutex_lock(&iommu_sva_lock);
	अगर (ioasid_put(mm->pasid))
		mm->pasid = 0;
	mutex_unlock(&iommu_sva_lock);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_मुक्त_pasid);

/* ioasid_find getter() requires a व्योम * argument */
अटल bool __mmget_not_zero(व्योम *mm)
अणु
	वापस mmget_not_zero(mm);
पूर्ण

/**
 * iommu_sva_find() - Find mm associated to the given PASID
 * @pasid: Process Address Space ID asचिन्हित to the mm
 *
 * On success a reference to the mm is taken, and must be released with mmput().
 *
 * Returns the mm corresponding to this PASID, or an error अगर not found.
 */
काष्ठा mm_काष्ठा *iommu_sva_find(ioasid_t pasid)
अणु
	वापस ioasid_find(&iommu_sva_pasid, pasid, __mmget_not_zero);
पूर्ण
EXPORT_SYMBOL_GPL(iommu_sva_find);
