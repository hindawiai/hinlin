<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2012 ARM Limited
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/cache.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/elf.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/vdso_datapage.h>
#समावेश <यंत्र/vdso_समयr_info.h>
#समावेश <यंत्र/cache_info.h>
बाह्य काष्ठा cache_info L1_cache_info[2];
बाह्य अक्षर vdso_start[], vdso_end[];
अटल अचिन्हित दीर्घ vdso_pages __ro_after_init;
अटल अचिन्हित दीर्घ समयr_mapping_base;

काष्ठा समयr_info_t समयr_info = अणु
	.cycle_count_करोwn = true,
	.mapping_base = EMPTY_TIMER_MAPPING,
	.cycle_count_reg_offset = EMPTY_REG_OFFSET
पूर्ण;
/*
 * The vDSO data page.
 */
अटल काष्ठा page *no_pages[] = अणु शून्य पूर्ण;

अटल जोड़ अणु
	काष्ठा vdso_data data;
	u8 page[PAGE_SIZE];
पूर्ण vdso_data_store __page_aligned_data;
काष्ठा vdso_data *vdso_data = &vdso_data_store.data;
अटल काष्ठा vm_special_mapping vdso_spec[2] __ro_after_init = अणु
	अणु
	 .name = "[vvar]",
	 .pages = no_pages,
	 पूर्ण,
	अणु
	 .name = "[vdso]",
	 पूर्ण,
पूर्ण;

अटल व्योम get_समयr_node_info(व्योम)
अणु
	समयr_mapping_base = समयr_info.mapping_base;
	vdso_data->cycle_count_offset =
		समयr_info.cycle_count_reg_offset;
	vdso_data->cycle_count_करोwn =
		समयr_info.cycle_count_करोwn;
पूर्ण

अटल पूर्णांक __init vdso_init(व्योम)
अणु
	पूर्णांक i;
	काष्ठा page **vdso_pagelist;

	अगर (स_भेद(vdso_start, "\177ELF", 4)) अणु
		pr_err("vDSO is not a valid ELF object!\n");
		वापस -EINVAL;
	पूर्ण
	/* Creat a समयr io mapping to get घड़ी cycles counter */
	get_समयr_node_info();

	vdso_pages = (vdso_end - vdso_start) >> PAGE_SHIFT;
	pr_info("vdso: %ld pages (%ld code @ %p, %ld data @ %p)\n",
		vdso_pages + 1, vdso_pages, vdso_start, 1L, vdso_data);

	/* Allocate the vDSO pagelist */
	vdso_pagelist = kसुस्मृति(vdso_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (vdso_pagelist == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < vdso_pages; i++)
		vdso_pagelist[i] = virt_to_page(vdso_start + i * PAGE_SIZE);
	vdso_spec[1].pages = &vdso_pagelist[0];

	वापस 0;
पूर्ण

arch_initcall(vdso_init);

अचिन्हित दीर्घ अंतरभूत vdso_अक्रमom_addr(अचिन्हित दीर्घ vdso_mapping_len)
अणु
	अचिन्हित दीर्घ start = current->mm->mmap_base, end, offset, addr;
	start = PAGE_ALIGN(start);

	/* Round the lowest possible end address up to a PMD boundary. */
	end = (start + vdso_mapping_len + PMD_SIZE - 1) & PMD_MASK;
	अगर (end >= TASK_SIZE)
		end = TASK_SIZE;
	end -= vdso_mapping_len;

	अगर (end > start) अणु
		offset = get_अक्रमom_पूर्णांक() % (((end - start) >> PAGE_SHIFT) + 1);
		addr = start + (offset << PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		addr = start;
	पूर्ण
	वापस addr;
पूर्ण

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ vdso_base, vdso_text_len, vdso_mapping_len;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr = 0;
	pgprot_t prot;
	पूर्णांक ret, vvar_page_num = 2;

	vdso_text_len = vdso_pages << PAGE_SHIFT;

	अगर(समयr_mapping_base == EMPTY_VALUE)
		vvar_page_num = 1;
	/* Be sure to map the data page */
	vdso_mapping_len = vdso_text_len + vvar_page_num * PAGE_SIZE;
#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
	vdso_mapping_len += L1_cache_info[DCACHE].aliasing_num - 1;
#पूर्ण_अगर

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	addr = vdso_अक्रमom_addr(vdso_mapping_len);
	vdso_base = get_unmapped_area(शून्य, addr, vdso_mapping_len, 0, 0);
	अगर (IS_ERR_VALUE(vdso_base)) अणु
		ret = vdso_base;
		जाओ up_fail;
	पूर्ण

#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
	अणु
		अचिन्हित पूर्णांक aliasing_mask =
		    L1_cache_info[DCACHE].aliasing_mask;
		अचिन्हित पूर्णांक page_colour_ofs;
		page_colour_ofs = ((अचिन्हित पूर्णांक)vdso_data & aliasing_mask) -
		    (vdso_base & aliasing_mask);
		vdso_base += page_colour_ofs & aliasing_mask;
	पूर्ण
#पूर्ण_अगर

	vma = _install_special_mapping(mm, vdso_base, vvar_page_num * PAGE_SIZE,
				       VM_READ | VM_MAYREAD, &vdso_spec[0]);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ up_fail;
	पूर्ण

	/*Map vdata to user space */
	ret = io_remap_pfn_range(vma, vdso_base,
				 virt_to_phys(vdso_data) >> PAGE_SHIFT,
				 PAGE_SIZE, vma->vm_page_prot);
	अगर (ret)
		जाओ up_fail;

	/*Map समयr to user space */
	vdso_base += PAGE_SIZE;
	prot = __pgprot(_PAGE_V | _PAGE_M_UR_KR | _PAGE_D |  _PAGE_C_DEV);
	ret = io_remap_pfn_range(vma, vdso_base, समयr_mapping_base >> PAGE_SHIFT,
				 PAGE_SIZE, prot);
	अगर (ret)
		जाओ up_fail;

	/*Map vdso to user space */
	vdso_base += PAGE_SIZE;
	mm->context.vdso = (व्योम *)vdso_base;
	vma = _install_special_mapping(mm, vdso_base, vdso_text_len,
				       VM_READ | VM_EXEC |
				       VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
				       &vdso_spec[1]);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ up_fail;
	पूर्ण

	mmap_ग_लिखो_unlock(mm);
	वापस 0;

up_fail:
	mm->context.vdso = शून्य;
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण

अटल व्योम vdso_ग_लिखो_begin(काष्ठा vdso_data *vdata)
अणु
	++vdso_data->seq_count;
	smp_wmb();		/* Pairs with smp_rmb in vdso_पढ़ो_retry */
पूर्ण

अटल व्योम vdso_ग_लिखो_end(काष्ठा vdso_data *vdata)
अणु
	smp_wmb();		/* Pairs with smp_rmb in vdso_पढ़ो_begin */
	++vdso_data->seq_count;
पूर्ण

व्योम update_vsyscall(काष्ठा समयkeeper *tk)
अणु
	vdso_ग_लिखो_begin(vdso_data);
	vdso_data->cs_mask = tk->tkr_mono.mask;
	vdso_data->cs_mult = tk->tkr_mono.mult;
	vdso_data->cs_shअगरt = tk->tkr_mono.shअगरt;
	vdso_data->cs_cycle_last = tk->tkr_mono.cycle_last;
	vdso_data->wपंचांग_घड़ी_sec = tk->wall_to_monotonic.tv_sec;
	vdso_data->wपंचांग_घड़ी_nsec = tk->wall_to_monotonic.tv_nsec;
	vdso_data->xसमय_घड़ी_sec = tk->xसमय_sec;
	vdso_data->xसमय_घड़ी_nsec = tk->tkr_mono.xसमय_nsec;
	vdso_data->xसमय_coarse_sec = tk->xसमय_sec;
	vdso_data->xसमय_coarse_nsec = tk->tkr_mono.xसमय_nsec >>
	    tk->tkr_mono.shअगरt;
	vdso_data->hrसमयr_res = hrसमयr_resolution;
	vdso_ग_लिखो_end(vdso_data);
पूर्ण

व्योम update_vsyscall_tz(व्योम)
अणु
	vdso_data->tz_minuteswest = sys_tz.tz_minuteswest;
	vdso_data->tz_dstसमय = sys_tz.tz_dstसमय;
पूर्ण
