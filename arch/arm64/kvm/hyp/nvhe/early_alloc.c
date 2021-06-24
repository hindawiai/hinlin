<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <यंत्र/kvm_pgtable.h>

#समावेश <nvhe/early_भाग.स>
#समावेश <nvhe/memory.h>

काष्ठा kvm_pgtable_mm_ops hyp_early_alloc_mm_ops;
s64 __ro_after_init hyp_physvirt_offset;

अटल अचिन्हित दीर्घ base;
अटल अचिन्हित दीर्घ end;
अटल अचिन्हित दीर्घ cur;

अचिन्हित दीर्घ hyp_early_alloc_nr_used_pages(व्योम)
अणु
	वापस (cur - base) >> PAGE_SHIFT;
पूर्ण

व्योम *hyp_early_alloc_contig(अचिन्हित पूर्णांक nr_pages)
अणु
	अचिन्हित दीर्घ size = (nr_pages << PAGE_SHIFT);
	व्योम *ret = (व्योम *)cur;

	अगर (!nr_pages)
		वापस शून्य;

	अगर (end - cur < size)
		वापस शून्य;

	cur += size;
	स_रखो(ret, 0, size);

	वापस ret;
पूर्ण

व्योम *hyp_early_alloc_page(व्योम *arg)
अणु
	वापस hyp_early_alloc_contig(1);
पूर्ण

व्योम hyp_early_alloc_init(व्योम *virt, अचिन्हित दीर्घ size)
अणु
	base = cur = (अचिन्हित दीर्घ)virt;
	end = base + size;

	hyp_early_alloc_mm_ops.zalloc_page = hyp_early_alloc_page;
	hyp_early_alloc_mm_ops.phys_to_virt = hyp_phys_to_virt;
	hyp_early_alloc_mm_ops.virt_to_phys = hyp_virt_to_phys;
पूर्ण
