<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#समावेश <linux/binfmts.h>
#समावेश <linux/elf.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>

#समावेश <यंत्र/abi.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/vdso.h>
#समावेश <vdso/helpers.h>
#समावेश <vdso/vsyscall.h>

/* Kernel-provided data used by the VDSO. */
अटल जोड़ mips_vdso_data mips_vdso_data __page_aligned_data;
काष्ठा vdso_data *vdso_data = mips_vdso_data.data;

/*
 * Mapping क्रम the VDSO data/GIC pages. The real pages are mapped manually, as
 * what we map and where within the area they are mapped is determined at
 * runसमय.
 */
अटल काष्ठा page *no_pages[] = अणु शून्य पूर्ण;
अटल काष्ठा vm_special_mapping vdso_vvar_mapping = अणु
	.name = "[vvar]",
	.pages = no_pages,
पूर्ण;

अटल व्योम __init init_vdso_image(काष्ठा mips_vdso_image *image)
अणु
	अचिन्हित दीर्घ num_pages, i;
	अचिन्हित दीर्घ data_pfn;

	BUG_ON(!PAGE_ALIGNED(image->data));
	BUG_ON(!PAGE_ALIGNED(image->size));

	num_pages = image->size / PAGE_SIZE;

	data_pfn = __phys_to_pfn(__pa_symbol(image->data));
	क्रम (i = 0; i < num_pages; i++)
		image->mapping.pages[i] = pfn_to_page(data_pfn + i);
पूर्ण

अटल पूर्णांक __init init_vdso(व्योम)
अणु
	init_vdso_image(&vdso_image);

#अगर_घोषित CONFIG_MIPS32_O32
	init_vdso_image(&vdso_image_o32);
#पूर्ण_अगर

#अगर_घोषित CONFIG_MIPS32_N32
	init_vdso_image(&vdso_image_n32);
#पूर्ण_अगर

	वापस 0;
पूर्ण
subsys_initcall(init_vdso);

अटल अचिन्हित दीर्घ vdso_base(व्योम)
अणु
	अचिन्हित दीर्घ base = STACK_TOP;

	अगर (IS_ENABLED(CONFIG_MIPS_FP_SUPPORT)) अणु
		/* Skip the delay slot emulation page */
		base += PAGE_SIZE;
	पूर्ण

	अगर (current->flags & PF_RANDOMIZE) अणु
		base += get_अक्रमom_पूर्णांक() & (VDSO_RANDOMIZE_SIZE - 1);
		base = PAGE_ALIGN(base);
	पूर्ण

	वापस base;
पूर्ण

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mips_vdso_image *image = current->thपढ़ो.abi->vdso;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ gic_size, vvar_size, size, base, data_addr, vdso_addr, gic_pfn, gic_base;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	अगर (IS_ENABLED(CONFIG_MIPS_FP_SUPPORT)) अणु
		/* Map delay slot emulation page */
		base = mmap_region(शून्य, STACK_TOP, PAGE_SIZE,
				VM_READ | VM_EXEC |
				VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
				0, शून्य);
		अगर (IS_ERR_VALUE(base)) अणु
			ret = base;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Determine total area size. This includes the VDSO data itself, the
	 * data page, and the GIC user page अगर present. Always create a mapping
	 * क्रम the GIC user area अगर the GIC is present regardless of whether it
	 * is the current घड़ीsource, in हाल it comes पूर्णांकo use later on. We
	 * only map a page even though the total area is 64K, as we only need
	 * the counter रेजिस्टरs at the start.
	 */
	gic_size = mips_gic_present() ? PAGE_SIZE : 0;
	vvar_size = gic_size + PAGE_SIZE;
	size = vvar_size + image->size;

	/*
	 * Find a region that's large enough क्रम us to perक्रमm the
	 * colour-matching alignment below.
	 */
	अगर (cpu_has_dc_aliases)
		size += shm_align_mask + 1;

	base = get_unmapped_area(शून्य, vdso_base(), size, 0, 0);
	अगर (IS_ERR_VALUE(base)) अणु
		ret = base;
		जाओ out;
	पूर्ण

	/*
	 * If we suffer from dcache aliasing, ensure that the VDSO data page
	 * mapping is coloured the same as the kernel's mapping of that memory.
	 * This ensures that when the kernel updates the VDSO data userland
	 * will observe it without requiring cache invalidations.
	 */
	अगर (cpu_has_dc_aliases) अणु
		base = __ALIGN_MASK(base, shm_align_mask);
		base += ((अचिन्हित दीर्घ)vdso_data - gic_size) & shm_align_mask;
	पूर्ण

	data_addr = base + gic_size;
	vdso_addr = data_addr + PAGE_SIZE;

	vma = _install_special_mapping(mm, base, vvar_size,
				       VM_READ | VM_MAYREAD,
				       &vdso_vvar_mapping);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out;
	पूर्ण

	/* Map GIC user page. */
	अगर (gic_size) अणु
		gic_base = (अचिन्हित दीर्घ)mips_gic_base + MIPS_GIC_USER_OFS;
		gic_pfn = virt_to_phys((व्योम *)gic_base) >> PAGE_SHIFT;

		ret = io_remap_pfn_range(vma, base, gic_pfn, gic_size,
					 pgprot_noncached(vma->vm_page_prot));
		अगर (ret)
			जाओ out;
	पूर्ण

	/* Map data page. */
	ret = remap_pfn_range(vma, data_addr,
			      virt_to_phys(vdso_data) >> PAGE_SHIFT,
			      PAGE_SIZE, vma->vm_page_prot);
	अगर (ret)
		जाओ out;

	/* Map VDSO image. */
	vma = _install_special_mapping(mm, vdso_addr, image->size,
				       VM_READ | VM_EXEC |
				       VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
				       &image->mapping);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out;
	पूर्ण

	mm->context.vdso = (व्योम *)vdso_addr;
	ret = 0;

out:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
