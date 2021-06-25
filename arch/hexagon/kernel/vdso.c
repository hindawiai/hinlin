<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vDSO implementation क्रम Hexagon
 *
 * Copyright (c) 2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/binfmts.h>

#समावेश <यंत्र/vdso.h>

अटल काष्ठा page *vdso_page;

/* Create a vDSO page holding the संकेत trampoline.
 * We want this क्रम a non-executable stack.
 */
अटल पूर्णांक __init vdso_init(व्योम)
अणु
	काष्ठा hexagon_vdso *vdso;

	vdso_page = alloc_page(GFP_KERNEL);
	अगर (!vdso_page)
		panic("Cannot allocate vdso");

	vdso = vmap(&vdso_page, 1, 0, PAGE_KERNEL);
	अगर (!vdso)
		panic("Cannot map vdso");
	clear_page(vdso);

	/* Install the संकेत trampoline; currently looks like this:
	 *	r6 = #__NR_rt_sigवापस;
	 *	trap0(#1);
	 */
	vdso->rt_संकेत_trampoline[0] = __rt_sigtramp_ढाँचा[0];
	vdso->rt_संकेत_trampoline[1] = __rt_sigtramp_ढाँचा[1];

	vunmap(vdso);

	वापस 0;
पूर्ण
arch_initcall(vdso_init);

/*
 * Called from binfmt_elf.  Create a VMA क्रम the vDSO page.
 */
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ vdso_base;
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	/* Try to get it loaded right near ld.so/glibc. */
	vdso_base = STACK_TOP;

	vdso_base = get_unmapped_area(शून्य, vdso_base, PAGE_SIZE, 0, 0);
	अगर (IS_ERR_VALUE(vdso_base)) अणु
		ret = vdso_base;
		जाओ up_fail;
	पूर्ण

	/* MAYWRITE to allow gdb to COW and set अवरोधpoपूर्णांकs. */
	ret = install_special_mapping(mm, vdso_base, PAGE_SIZE,
				      VM_READ|VM_EXEC|
				      VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
				      &vdso_page);

	अगर (ret)
		जाओ up_fail;

	mm->context.vdso = (व्योम *)vdso_base;

up_fail:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_mm && vma->vm_start == (दीर्घ)vma->vm_mm->context.vdso)
		वापस "[vdso]";
	वापस शून्य;
पूर्ण
