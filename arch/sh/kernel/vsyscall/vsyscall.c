<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/vsyscall/vsyscall.c
 *
 *  Copyright (C) 2006 Paul Mundt
 *
 * vDSO अक्रमomization
 * Copyright(C) 2005-2006, Red Hat, Inc., Ingo Molnar
 */
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/elf.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>

/*
 * Should the kernel map a VDSO page पूर्णांकo processes and pass its
 * address करोwn to glibc upon exec()?
 */
अचिन्हित पूर्णांक __पढ़ो_mostly vdso_enabled = 1;
EXPORT_SYMBOL_GPL(vdso_enabled);

अटल पूर्णांक __init vdso_setup(अक्षर *s)
अणु
	vdso_enabled = simple_म_से_अदीर्घ(s, शून्य, 0);
	वापस 1;
पूर्ण
__setup("vdso=", vdso_setup);

/*
 * These symbols are defined by vsyscall.o to mark the bounds
 * of the ELF DSO images included therein.
 */
बाह्य स्थिर अक्षर vsyscall_trapa_start, vsyscall_trapa_end;
अटल काष्ठा page *syscall_pages[1];

पूर्णांक __init vsyscall_init(व्योम)
अणु
	व्योम *syscall_page = (व्योम *)get_zeroed_page(GFP_ATOMIC);
	syscall_pages[0] = virt_to_page(syscall_page);

	/*
	 * XXX: Map this page to a fixmap entry अगर we get around
	 * to adding the page to ELF core dumps
	 */

	स_नकल(syscall_page,
	       &vsyscall_trapa_start,
	       &vsyscall_trapa_end - &vsyscall_trapa_start);

	वापस 0;
पूर्ण

/* Setup a VMA at program startup क्रम the vsyscall page */
पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	addr = get_unmapped_area(शून्य, 0, PAGE_SIZE, 0, 0);
	अगर (IS_ERR_VALUE(addr)) अणु
		ret = addr;
		जाओ up_fail;
	पूर्ण

	ret = install_special_mapping(mm, addr, PAGE_SIZE,
				      VM_READ | VM_EXEC |
				      VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC,
				      syscall_pages);
	अगर (unlikely(ret))
		जाओ up_fail;

	current->mm->context.vdso = (व्योम *)addr;

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
