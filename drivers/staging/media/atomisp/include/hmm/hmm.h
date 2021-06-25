<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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

#अगर_अघोषित	__HMM_H__
#घोषणा	__HMM_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश "hmm/hmm_pool.h"
#समावेश "ia_css_types.h"

#घोषणा mmgr_शून्य              ((ia_css_ptr)0)
#घोषणा mmgr_EXCEPTION         ((ia_css_ptr) - 1)

पूर्णांक hmm_pool_रेजिस्टर(अचिन्हित पूर्णांक pool_size, क्रमागत hmm_pool_type pool_type);
व्योम hmm_pool_unरेजिस्टर(क्रमागत hmm_pool_type pool_type);

पूर्णांक hmm_init(व्योम);
व्योम hmm_cleanup(व्योम);

ia_css_ptr hmm_alloc(माप_प्रकार bytes, क्रमागत hmm_bo_type type,
		     पूर्णांक from_highmem, स्थिर व्योम __user *userptr,
		     स्थिर uपूर्णांक16_t attrs);
व्योम hmm_मुक्त(ia_css_ptr ptr);
पूर्णांक hmm_load(ia_css_ptr virt, व्योम *data, अचिन्हित पूर्णांक bytes);
पूर्णांक hmm_store(ia_css_ptr virt, स्थिर व्योम *data, अचिन्हित पूर्णांक bytes);
पूर्णांक hmm_set(ia_css_ptr virt, पूर्णांक c, अचिन्हित पूर्णांक bytes);
पूर्णांक hmm_flush(ia_css_ptr virt, अचिन्हित पूर्णांक bytes);

/*
 * get kernel memory physical address from ISP भव address.
 */
phys_addr_t hmm_virt_to_phys(ia_css_ptr virt);

/*
 * map ISP memory starts with virt to kernel भव address
 * by using vmap. वापस शून्य अगर failed.
 *
 * virt must be the start address of ISP memory (वापस by hmm_alloc),
 * करो not pass any other address.
 */
व्योम *hmm_vmap(ia_css_ptr virt, bool cached);
व्योम hmm_vunmap(ia_css_ptr virt);

/*
 * flush the cache क्रम the vmapped buffer.
 * अगर the buffer has not been vmapped, वापस directly.
 */
व्योम hmm_flush_vmap(ia_css_ptr virt);

/*
 * Address translation from ISP shared memory address to kernel भव address
 * अगर the memory is not vmmaped,  then करो it.
 */
व्योम *hmm_isp_vaddr_to_host_vaddr(ia_css_ptr ptr, bool cached);

/*
 * Address translation from kernel भव address to ISP shared memory address
 */
ia_css_ptr hmm_host_vaddr_to_hrt_vaddr(स्थिर व्योम *ptr);

/*
 * map ISP memory starts with virt to specअगरic vma.
 *
 * used क्रम mmap operation.
 *
 * virt must be the start address of ISP memory (वापस by hmm_alloc),
 * करो not pass any other address.
 */
पूर्णांक hmm_mmap(काष्ठा vm_area_काष्ठा *vma, ia_css_ptr virt);

/* show memory statistic
 */
व्योम hmm_show_mem_stat(स्थिर अक्षर *func, स्थिर पूर्णांक line);

/* init memory statistic
 */
व्योम hmm_init_mem_stat(पूर्णांक res_pgnr, पूर्णांक dyc_en, पूर्णांक dyc_pgnr);

बाह्य bool dypool_enable;
बाह्य अचिन्हित पूर्णांक dypool_pgnr;
बाह्य काष्ठा hmm_bo_device bo_device;

#पूर्ण_अगर
