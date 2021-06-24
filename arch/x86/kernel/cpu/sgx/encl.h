<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
 * Copyright(c) 2016-20 Intel Corporation.
 *
 * Contains the software defined data काष्ठाures क्रम enclaves.
 */
#अगर_अघोषित _X86_ENCL_H
#घोषणा _X86_ENCL_H

#समावेश <linux/cpumask.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/srcu.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/xarray.h>
#समावेश "sgx.h"

/* 'desc' bits holding the offset in the VA (version array) page. */
#घोषणा SGX_ENCL_PAGE_VA_OFFSET_MASK	GENMASK_ULL(11, 3)

/* 'desc' bit marking that the page is being reclaimed. */
#घोषणा SGX_ENCL_PAGE_BEING_RECLAIMED	BIT(3)

काष्ठा sgx_encl_page अणु
	अचिन्हित दीर्घ desc;
	अचिन्हित दीर्घ vm_max_prot_bits;
	काष्ठा sgx_epc_page *epc_page;
	काष्ठा sgx_encl *encl;
	काष्ठा sgx_va_page *va_page;
पूर्ण;

क्रमागत sgx_encl_flags अणु
	SGX_ENCL_IOCTL		= BIT(0),
	SGX_ENCL_DEBUG		= BIT(1),
	SGX_ENCL_CREATED	= BIT(2),
	SGX_ENCL_INITIALIZED	= BIT(3),
पूर्ण;

काष्ठा sgx_encl_mm अणु
	काष्ठा sgx_encl *encl;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा list_head list;
	काष्ठा mmu_notअगरier mmu_notअगरier;
पूर्ण;

काष्ठा sgx_encl अणु
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक page_cnt;
	अचिन्हित पूर्णांक secs_child_cnt;
	काष्ठा mutex lock;
	काष्ठा xarray page_array;
	काष्ठा sgx_encl_page secs;
	अचिन्हित दीर्घ attributes;
	अचिन्हित दीर्घ attributes_mask;

	cpumask_t cpumask;
	काष्ठा file *backing;
	काष्ठा kref refcount;
	काष्ठा list_head va_pages;
	अचिन्हित दीर्घ mm_list_version;
	काष्ठा list_head mm_list;
	spinlock_t mm_lock;
	काष्ठा srcu_काष्ठा srcu;
पूर्ण;

#घोषणा SGX_VA_SLOT_COUNT 512

काष्ठा sgx_va_page अणु
	काष्ठा sgx_epc_page *epc_page;
	DECLARE_BITMAP(slots, SGX_VA_SLOT_COUNT);
	काष्ठा list_head list;
पूर्ण;

काष्ठा sgx_backing अणु
	pgoff_t page_index;
	काष्ठा page *contents;
	काष्ठा page *pcmd;
	अचिन्हित दीर्घ pcmd_offset;
पूर्ण;

बाह्य स्थिर काष्ठा vm_operations_काष्ठा sgx_vm_ops;

अटल अंतरभूत पूर्णांक sgx_encl_find(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				काष्ठा vm_area_काष्ठा **vma)
अणु
	काष्ठा vm_area_काष्ठा *result;

	result = find_vma(mm, addr);
	अगर (!result || result->vm_ops != &sgx_vm_ops || addr < result->vm_start)
		वापस -EINVAL;

	*vma = result;

	वापस 0;
पूर्ण

पूर्णांक sgx_encl_may_map(काष्ठा sgx_encl *encl, अचिन्हित दीर्घ start,
		     अचिन्हित दीर्घ end, अचिन्हित दीर्घ vm_flags);

व्योम sgx_encl_release(काष्ठा kref *ref);
पूर्णांक sgx_encl_mm_add(काष्ठा sgx_encl *encl, काष्ठा mm_काष्ठा *mm);
पूर्णांक sgx_encl_get_backing(काष्ठा sgx_encl *encl, अचिन्हित दीर्घ page_index,
			 काष्ठा sgx_backing *backing);
व्योम sgx_encl_put_backing(काष्ठा sgx_backing *backing, bool करो_ग_लिखो);
पूर्णांक sgx_encl_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
				  काष्ठा sgx_encl_page *page);

काष्ठा sgx_epc_page *sgx_alloc_va_page(व्योम);
अचिन्हित पूर्णांक sgx_alloc_va_slot(काष्ठा sgx_va_page *va_page);
व्योम sgx_मुक्त_va_slot(काष्ठा sgx_va_page *va_page, अचिन्हित पूर्णांक offset);
bool sgx_va_page_full(काष्ठा sgx_va_page *va_page);
व्योम sgx_encl_मुक्त_epc_page(काष्ठा sgx_epc_page *page);

#पूर्ण_अगर /* _X86_ENCL_H */
