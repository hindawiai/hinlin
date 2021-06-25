<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010-2017 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
/*
 * This file contains entry functions क्रम memory management of ISP driver
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>	/* क्रम kmap */
#समावेश <linux/पन.स>		/* क्रम page_to_phys */
#समावेश <linux/sysfs.h>

#समावेश "hmm/hmm.h"
#समावेश "hmm/hmm_pool.h"
#समावेश "hmm/hmm_bo.h"

#समावेश "atomisp_internal.h"
#समावेश "asm/cacheflush.h"
#समावेश "mmu/isp_mmu.h"
#समावेश "mmu/sh_mmu_mrfld.h"

काष्ठा hmm_bo_device bo_device;
काष्ठा hmm_pool	dynamic_pool;
काष्ठा hmm_pool	reserved_pool;
अटल ia_css_ptr dummy_ptr;
अटल bool hmm_initialized;
काष्ठा _hmm_mem_stat hmm_mem_stat;

/*
 * p: निजी
 * s: shared
 * u: user
 * i: ion
 */
अटल स्थिर अक्षर hmm_bo_type_string[] = "psui";

अटल sमाप_प्रकार bo_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		       अक्षर *buf, काष्ठा list_head *bo_list, bool active)
अणु
	sमाप_प्रकार ret = 0;
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	दीर्घ total[HMM_BO_LAST] = अणु 0 पूर्ण;
	दीर्घ count[HMM_BO_LAST] = अणु 0 पूर्ण;
	पूर्णांक index1 = 0;
	पूर्णांक index2 = 0;

	ret = scnम_लिखो(buf, PAGE_SIZE, "type pgnr\n");
	अगर (ret <= 0)
		वापस 0;

	index1 += ret;

	spin_lock_irqsave(&bo_device.list_lock, flags);
	list_क्रम_each_entry(bo, bo_list, list) अणु
		अगर ((active && (bo->status & HMM_BO_ALLOCED)) ||
		    (!active && !(bo->status & HMM_BO_ALLOCED))) अणु
			ret = scnम_लिखो(buf + index1, PAGE_SIZE - index1,
					"%c %d\n",
					hmm_bo_type_string[bo->type], bo->pgnr);

			total[bo->type] += bo->pgnr;
			count[bo->type]++;
			अगर (ret > 0)
				index1 += ret;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&bo_device.list_lock, flags);

	क्रम (i = 0; i < HMM_BO_LAST; i++) अणु
		अगर (count[i]) अणु
			ret = scnम_लिखो(buf + index1 + index2,
					PAGE_SIZE - index1 - index2,
					"%ld %c buffer objects: %ld KB\n",
					count[i], hmm_bo_type_string[i],
					total[i] * 4);
			अगर (ret > 0)
				index2 += ret;
		पूर्ण
	पूर्ण

	/* Add trailing zero, not included by scnम_लिखो */
	वापस index1 + index2 + 1;
पूर्ण

अटल sमाप_प्रकार active_bo_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	वापस bo_show(dev, attr, buf, &bo_device.entire_bo_list, true);
पूर्ण

अटल sमाप_प्रकार मुक्त_bo_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस bo_show(dev, attr, buf, &bo_device.entire_bo_list, false);
पूर्ण

अटल sमाप_प्रकार reserved_pool_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;

	काष्ठा hmm_reserved_pool_info *pinfo = reserved_pool.pool_info;
	अचिन्हित दीर्घ flags;

	अगर (!pinfo || !pinfo->initialized)
		वापस 0;

	spin_lock_irqsave(&pinfo->list_lock, flags);
	ret = scnम_लिखो(buf, PAGE_SIZE, "%d out of %d pages available\n",
			pinfo->index, pinfo->pgnr);
	spin_unlock_irqrestore(&pinfo->list_lock, flags);

	अगर (ret > 0)
		ret++; /* Add trailing zero, not included by scnम_लिखो */

	वापस ret;
पूर्ण;

अटल sमाप_प्रकार dynamic_pool_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	sमाप_प्रकार ret = 0;

	काष्ठा hmm_dynamic_pool_info *pinfo = dynamic_pool.pool_info;
	अचिन्हित दीर्घ flags;

	अगर (!pinfo || !pinfo->initialized)
		वापस 0;

	spin_lock_irqsave(&pinfo->list_lock, flags);
	ret = scnम_लिखो(buf, PAGE_SIZE, "%d (max %d) pages available\n",
			pinfo->pgnr, pinfo->pool_size);
	spin_unlock_irqrestore(&pinfo->list_lock, flags);

	अगर (ret > 0)
		ret++; /* Add trailing zero, not included by scnम_लिखो */

	वापस ret;
पूर्ण;

अटल DEVICE_ATTR_RO(active_bo);
अटल DEVICE_ATTR_RO(मुक्त_bo);
अटल DEVICE_ATTR_RO(reserved_pool);
अटल DEVICE_ATTR_RO(dynamic_pool);

अटल काष्ठा attribute *sysfs_attrs_ctrl[] = अणु
	&dev_attr_active_bo.attr,
	&dev_attr_मुक्त_bo.attr,
	&dev_attr_reserved_pool.attr,
	&dev_attr_dynamic_pool.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group atomisp_attribute_group[] = अणु
	अणु.attrs = sysfs_attrs_ctrl पूर्ण,
पूर्ण;

पूर्णांक hmm_init(व्योम)
अणु
	पूर्णांक ret;

	ret = hmm_bo_device_init(&bo_device, &sh_mmu_mrfld,
				 ISP_VM_START, ISP_VM_SIZE);
	अगर (ret)
		dev_err(atomisp_dev, "hmm_bo_device_init failed.\n");

	hmm_initialized = true;

	/*
	 * As hmm use शून्य to indicate invalid ISP भव address,
	 * and ISP_VM_START is defined to 0 too, so we allocate
	 * one piece of dummy memory, which should वापस value 0,
	 * at the beginning, to aव्योम hmm_alloc वापस 0 in the
	 * further allocation.
	 */
	dummy_ptr = hmm_alloc(1, HMM_BO_PRIVATE, 0, शून्य, 0);

	अगर (!ret) अणु
		ret = sysfs_create_group(&atomisp_dev->kobj,
					 atomisp_attribute_group);
		अगर (ret)
			dev_err(atomisp_dev,
				"%s Failed to create sysfs\n", __func__);
	पूर्ण

	वापस ret;
पूर्ण

व्योम hmm_cleanup(व्योम)
अणु
	अगर (!dummy_ptr)
		वापस;
	sysfs_हटाओ_group(&atomisp_dev->kobj, atomisp_attribute_group);

	/* मुक्त dummy memory first */
	hmm_मुक्त(dummy_ptr);
	dummy_ptr = 0;

	hmm_bo_device_निकास(&bo_device);
	hmm_initialized = false;
पूर्ण

ia_css_ptr hmm_alloc(माप_प्रकार bytes, क्रमागत hmm_bo_type type,
		     पूर्णांक from_highmem, स्थिर व्योम __user *userptr,
		     स्थिर uपूर्णांक16_t attrs)
अणु
	अचिन्हित पूर्णांक pgnr;
	काष्ठा hmm_buffer_object *bo;
	bool cached = attrs & ATOMISP_MAP_FLAG_CACHED;
	पूर्णांक ret;

	WARN_ON(attrs & ATOMISP_MAP_FLAG_CONTIGUOUS);

	/*
	 * Check अगर we are initialized. In the ideal world we wouldn't need
	 * this but we can tackle it once the driver is a lot cleaner
	 */

	अगर (!hmm_initialized)
		hmm_init();
	/* Get page number from size */
	pgnr = माप_प्रकारo_pgnr_उच्चमान(bytes);

	/* Buffer object काष्ठाure init */
	bo = hmm_bo_alloc(&bo_device, pgnr);
	अगर (!bo) अणु
		dev_err(atomisp_dev, "hmm_bo_create failed.\n");
		जाओ create_bo_err;
	पूर्ण

	/* Allocate pages क्रम memory */
	ret = hmm_bo_alloc_pages(bo, type, from_highmem, userptr, cached);
	अगर (ret) अणु
		dev_err(atomisp_dev, "hmm_bo_alloc_pages failed.\n");
		जाओ alloc_page_err;
	पूर्ण

	/* Combine the भव address and pages together */
	ret = hmm_bo_bind(bo);
	अगर (ret) अणु
		dev_err(atomisp_dev, "hmm_bo_bind failed.\n");
		जाओ bind_err;
	पूर्ण

	hmm_mem_stat.tol_cnt += pgnr;

	अगर (attrs & ATOMISP_MAP_FLAG_CLEARED)
		hmm_set(bo->start, 0, bytes);

	dev_dbg(atomisp_dev,
		"%s: pages: 0x%08x (%zu bytes), type: %d from highmem %d, user ptr %p, cached %d\n",
		__func__, bo->start, bytes, type, from_highmem, userptr, cached);

	वापस bo->start;

bind_err:
	hmm_bo_मुक्त_pages(bo);
alloc_page_err:
	hmm_bo_unref(bo);
create_bo_err:
	वापस 0;
पूर्ण

व्योम hmm_मुक्त(ia_css_ptr virt)
अणु
	काष्ठा hmm_buffer_object *bo;

	dev_dbg(atomisp_dev, "%s: free 0x%08x\n", __func__, virt);

	WARN_ON(!virt);

	bo = hmm_bo_device_search_start(&bo_device, (अचिन्हित पूर्णांक)virt);

	अगर (!bo) अणु
		dev_err(atomisp_dev,
			"can not find buffer object start with address 0x%x\n",
			(अचिन्हित पूर्णांक)virt);
		वापस;
	पूर्ण

	hmm_mem_stat.tol_cnt -= bo->pgnr;

	hmm_bo_unbind(bo);
	hmm_bo_मुक्त_pages(bo);
	hmm_bo_unref(bo);
पूर्ण

अटल अंतरभूत पूर्णांक hmm_check_bo(काष्ठा hmm_buffer_object *bo, अचिन्हित पूर्णांक ptr)
अणु
	अगर (!bo) अणु
		dev_err(atomisp_dev,
			"can not find buffer object contains address 0x%x\n",
			ptr);
		वापस -EINVAL;
	पूर्ण

	अगर (!hmm_bo_page_allocated(bo)) अणु
		dev_err(atomisp_dev,
			"buffer object has no page allocated.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!hmm_bo_allocated(bo)) अणु
		dev_err(atomisp_dev,
			"buffer object has no virtual address space allocated.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Read function in ISP memory management */
अटल पूर्णांक load_and_flush_by_kmap(ia_css_ptr virt, व्योम *data,
				  अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित पूर्णांक idx, offset, len;
	अक्षर *src, *des;
	पूर्णांक ret;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	ret = hmm_check_bo(bo, virt);
	अगर (ret)
		वापस ret;

	des = (अक्षर *)data;
	जबतक (bytes) अणु
		idx = (virt - bo->start) >> PAGE_SHIFT;
		offset = (virt - bo->start) - (idx << PAGE_SHIFT);

		src = (अक्षर *)kmap(bo->page_obj[idx].page) + offset;

		अगर ((bytes + offset) >= PAGE_SIZE) अणु
			len = PAGE_SIZE - offset;
			bytes -= len;
		पूर्ण अन्यथा अणु
			len = bytes;
			bytes = 0;
		पूर्ण

		virt += len;	/* update virt क्रम next loop */

		अगर (des) अणु
			स_नकल(des, src, len);
			des += len;
		पूर्ण

		clflush_cache_range(src, len);

		kunmap(bo->page_obj[idx].page);
	पूर्ण

	वापस 0;
पूर्ण

/* Read function in ISP memory management */
अटल पूर्णांक load_and_flush(ia_css_ptr virt, व्योम *data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा hmm_buffer_object *bo;
	पूर्णांक ret;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	ret = hmm_check_bo(bo, virt);
	अगर (ret)
		वापस ret;

	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		व्योम *src = bo->vmap_addr;

		src += (virt - bo->start);
		स_नकल(data, src, bytes);
		अगर (bo->status & HMM_BO_VMAPED_CACHED)
			clflush_cache_range(src, bytes);
	पूर्ण अन्यथा अणु
		व्योम *vptr;

		vptr = hmm_bo_vmap(bo, true);
		अगर (!vptr)
			वापस load_and_flush_by_kmap(virt, data, bytes);
		अन्यथा
			vptr = vptr + (virt - bo->start);

		स_नकल(data, vptr, bytes);
		clflush_cache_range(vptr, bytes);
		hmm_bo_vunmap(bo);
	पूर्ण

	वापस 0;
पूर्ण

/* Read function in ISP memory management */
पूर्णांक hmm_load(ia_css_ptr virt, व्योम *data, अचिन्हित पूर्णांक bytes)
अणु
	अगर (!virt) अणु
		dev_warn(atomisp_dev,
			"hmm_store: address is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!data) अणु
		dev_err(atomisp_dev,
			"hmm_store: data is a NULL argument\n");
		वापस -EINVAL;
	पूर्ण
	वापस load_and_flush(virt, data, bytes);
पूर्ण

/* Flush hmm data from the data cache */
पूर्णांक hmm_flush(ia_css_ptr virt, अचिन्हित पूर्णांक bytes)
अणु
	वापस load_and_flush(virt, शून्य, bytes);
पूर्ण

/* Write function in ISP memory management */
पूर्णांक hmm_store(ia_css_ptr virt, स्थिर व्योम *data, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित पूर्णांक idx, offset, len;
	अक्षर *src, *des;
	पूर्णांक ret;

	अगर (!virt) अणु
		dev_warn(atomisp_dev,
			"hmm_store: address is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!data) अणु
		dev_err(atomisp_dev,
			"hmm_store: data is a NULL argument\n");
		वापस -EINVAL;
	पूर्ण

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	ret = hmm_check_bo(bo, virt);
	अगर (ret)
		वापस ret;

	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		व्योम *dst = bo->vmap_addr;

		dst += (virt - bo->start);
		स_नकल(dst, data, bytes);
		अगर (bo->status & HMM_BO_VMAPED_CACHED)
			clflush_cache_range(dst, bytes);
	पूर्ण अन्यथा अणु
		व्योम *vptr;

		vptr = hmm_bo_vmap(bo, true);
		अगर (vptr) अणु
			vptr = vptr + (virt - bo->start);

			स_नकल(vptr, data, bytes);
			clflush_cache_range(vptr, bytes);
			hmm_bo_vunmap(bo);
			वापस 0;
		पूर्ण
	पूर्ण

	src = (अक्षर *)data;
	जबतक (bytes) अणु
		idx = (virt - bo->start) >> PAGE_SHIFT;
		offset = (virt - bo->start) - (idx << PAGE_SHIFT);

		अगर (in_atomic())
			des = (अक्षर *)kmap_atomic(bo->page_obj[idx].page);
		अन्यथा
			des = (अक्षर *)kmap(bo->page_obj[idx].page);

		अगर (!des) अणु
			dev_err(atomisp_dev,
				"kmap buffer object page failed: pg_idx = %d\n",
				idx);
			वापस -EINVAL;
		पूर्ण

		des += offset;

		अगर ((bytes + offset) >= PAGE_SIZE) अणु
			len = PAGE_SIZE - offset;
			bytes -= len;
		पूर्ण अन्यथा अणु
			len = bytes;
			bytes = 0;
		पूर्ण

		virt += len;

		स_नकल(des, src, len);

		src += len;

		clflush_cache_range(des, len);

		अगर (in_atomic())
			/*
			 * Note: kunmap_atomic requires वापस addr from
			 * kmap_atomic, not the page. See linux/highस्मृति.स
			 */
			kunmap_atomic(des - offset);
		अन्यथा
			kunmap(bo->page_obj[idx].page);
	पूर्ण

	वापस 0;
पूर्ण

/* स_रखो function in ISP memory management */
पूर्णांक hmm_set(ia_css_ptr virt, पूर्णांक c, अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा hmm_buffer_object *bo;
	अचिन्हित पूर्णांक idx, offset, len;
	अक्षर *des;
	पूर्णांक ret;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	ret = hmm_check_bo(bo, virt);
	अगर (ret)
		वापस ret;

	अगर (bo->status & HMM_BO_VMAPED || bo->status & HMM_BO_VMAPED_CACHED) अणु
		व्योम *dst = bo->vmap_addr;

		dst += (virt - bo->start);
		स_रखो(dst, c, bytes);

		अगर (bo->status & HMM_BO_VMAPED_CACHED)
			clflush_cache_range(dst, bytes);
	पूर्ण अन्यथा अणु
		व्योम *vptr;

		vptr = hmm_bo_vmap(bo, true);
		अगर (vptr) अणु
			vptr = vptr + (virt - bo->start);
			स_रखो(vptr, c, bytes);
			clflush_cache_range(vptr, bytes);
			hmm_bo_vunmap(bo);
			वापस 0;
		पूर्ण
	पूर्ण

	जबतक (bytes) अणु
		idx = (virt - bo->start) >> PAGE_SHIFT;
		offset = (virt - bo->start) - (idx << PAGE_SHIFT);

		des = (अक्षर *)kmap(bo->page_obj[idx].page) + offset;

		अगर ((bytes + offset) >= PAGE_SIZE) अणु
			len = PAGE_SIZE - offset;
			bytes -= len;
		पूर्ण अन्यथा अणु
			len = bytes;
			bytes = 0;
		पूर्ण

		virt += len;

		स_रखो(des, c, len);

		clflush_cache_range(des, len);

		kunmap(bo->page_obj[idx].page);
	पूर्ण

	वापस 0;
पूर्ण

/* Virtual address to physical address convert */
phys_addr_t hmm_virt_to_phys(ia_css_ptr virt)
अणु
	अचिन्हित पूर्णांक idx, offset;
	काष्ठा hmm_buffer_object *bo;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	अगर (!bo) अणु
		dev_err(atomisp_dev,
			"can not find buffer object contains address 0x%x\n",
			virt);
		वापस -1;
	पूर्ण

	idx = (virt - bo->start) >> PAGE_SHIFT;
	offset = (virt - bo->start) - (idx << PAGE_SHIFT);

	वापस page_to_phys(bo->page_obj[idx].page) + offset;
पूर्ण

पूर्णांक hmm_mmap(काष्ठा vm_area_काष्ठा *vma, ia_css_ptr virt)
अणु
	काष्ठा hmm_buffer_object *bo;

	bo = hmm_bo_device_search_start(&bo_device, virt);
	अगर (!bo) अणु
		dev_err(atomisp_dev,
			"can not find buffer object start with address 0x%x\n",
			virt);
		वापस -EINVAL;
	पूर्ण

	वापस hmm_bo_mmap(vma, bo);
पूर्ण

/* Map ISP भव address पूर्णांकo IA भव address */
व्योम *hmm_vmap(ia_css_ptr virt, bool cached)
अणु
	काष्ठा hmm_buffer_object *bo;
	व्योम *ptr;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	अगर (!bo) अणु
		dev_err(atomisp_dev,
			"can not find buffer object contains address 0x%x\n",
			virt);
		वापस शून्य;
	पूर्ण

	ptr = hmm_bo_vmap(bo, cached);
	अगर (ptr)
		वापस ptr + (virt - bo->start);
	अन्यथा
		वापस शून्य;
पूर्ण

/* Flush the memory which is mapped as cached memory through hmm_vmap */
व्योम hmm_flush_vmap(ia_css_ptr virt)
अणु
	काष्ठा hmm_buffer_object *bo;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	अगर (!bo) अणु
		dev_warn(atomisp_dev,
			 "can not find buffer object contains address 0x%x\n",
			 virt);
		वापस;
	पूर्ण

	hmm_bo_flush_vmap(bo);
पूर्ण

व्योम hmm_vunmap(ia_css_ptr virt)
अणु
	काष्ठा hmm_buffer_object *bo;

	bo = hmm_bo_device_search_in_range(&bo_device, virt);
	अगर (!bo) अणु
		dev_warn(atomisp_dev,
			 "can not find buffer object contains address 0x%x\n",
			 virt);
		वापस;
	पूर्ण

	hmm_bo_vunmap(bo);
पूर्ण

पूर्णांक hmm_pool_रेजिस्टर(अचिन्हित पूर्णांक pool_size, क्रमागत hmm_pool_type pool_type)
अणु
#अगर 0	// Just use the "normal" pool
	चयन (pool_type) अणु
	हाल HMM_POOL_TYPE_RESERVED:
		reserved_pool.pops = &reserved_pops;
		वापस reserved_pool.pops->pool_init(&reserved_pool.pool_info,
						     pool_size);
	हाल HMM_POOL_TYPE_DYNAMIC:
		dynamic_pool.pops = &dynamic_pops;
		वापस dynamic_pool.pops->pool_init(&dynamic_pool.pool_info,
						    pool_size);
	शेष:
		dev_err(atomisp_dev, "invalid pool type.\n");
		वापस -EINVAL;
	पूर्ण
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

व्योम hmm_pool_unरेजिस्टर(क्रमागत hmm_pool_type pool_type)
अणु
#अगर 0	// Just use the "normal" pool
	चयन (pool_type) अणु
	हाल HMM_POOL_TYPE_RESERVED:
		अगर (reserved_pool.pops && reserved_pool.pops->pool_निकास)
			reserved_pool.pops->pool_निकास(&reserved_pool.pool_info);
		अवरोध;
	हाल HMM_POOL_TYPE_DYNAMIC:
		अगर (dynamic_pool.pops && dynamic_pool.pops->pool_निकास)
			dynamic_pool.pops->pool_निकास(&dynamic_pool.pool_info);
		अवरोध;
	शेष:
		dev_err(atomisp_dev, "invalid pool type.\n");
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	वापस;
पूर्ण

व्योम *hmm_isp_vaddr_to_host_vaddr(ia_css_ptr ptr, bool cached)
अणु
	वापस hmm_vmap(ptr, cached);
	/* vmunmap will be करोne in hmm_bo_release() */
पूर्ण

ia_css_ptr hmm_host_vaddr_to_hrt_vaddr(स्थिर व्योम *ptr)
अणु
	काष्ठा hmm_buffer_object *bo;

	bo = hmm_bo_device_search_vmap_start(&bo_device, ptr);
	अगर (bo)
		वापस bo->start;

	dev_err(atomisp_dev,
		"can not find buffer object whose kernel virtual address is %p\n",
		ptr);
	वापस 0;
पूर्ण

व्योम hmm_show_mem_stat(स्थिर अक्षर *func, स्थिर पूर्णांक line)
अणु
	pr_info("tol_cnt=%d usr_size=%d res_size=%d res_cnt=%d sys_size=%d  dyc_thr=%d dyc_size=%d.\n",
		hmm_mem_stat.tol_cnt,
		hmm_mem_stat.usr_size, hmm_mem_stat.res_size,
		hmm_mem_stat.res_cnt, hmm_mem_stat.sys_size,
		hmm_mem_stat.dyc_thr, hmm_mem_stat.dyc_size);
पूर्ण

व्योम hmm_init_mem_stat(पूर्णांक res_pgnr, पूर्णांक dyc_en, पूर्णांक dyc_pgnr)
अणु
	hmm_mem_stat.res_size = res_pgnr;
	/* If reserved mem pool is not enabled, set its "mem stat" values as -1. */
	अगर (hmm_mem_stat.res_size == 0) अणु
		hmm_mem_stat.res_size = -1;
		hmm_mem_stat.res_cnt = -1;
	पूर्ण

	/* If dynamic memory pool is not enabled, set its "mem stat" values as -1. */
	अगर (!dyc_en) अणु
		hmm_mem_stat.dyc_size = -1;
		hmm_mem_stat.dyc_thr = -1;
	पूर्ण अन्यथा अणु
		hmm_mem_stat.dyc_size = 0;
		hmm_mem_stat.dyc_thr = dyc_pgnr;
	पूर्ण
	hmm_mem_stat.usr_size = 0;
	hmm_mem_stat.sys_size = 0;
	hmm_mem_stat.tol_cnt = 0;
पूर्ण
