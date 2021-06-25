<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Riअक्षरd Weinberger <richrd@nod.at>
 */

#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/elf.h>
#समावेश <linux/init.h>

अटल अचिन्हित पूर्णांक __पढ़ो_mostly vdso_enabled = 1;
अचिन्हित दीर्घ um_vdso_addr;

बाह्य अचिन्हित दीर्घ task_size;
बाह्य अक्षर vdso_start[], vdso_end[];

अटल काष्ठा page **vdsop;

अटल पूर्णांक __init init_vdso(व्योम)
अणु
	काष्ठा page *um_vdso;

	BUG_ON(vdso_end - vdso_start > PAGE_SIZE);

	um_vdso_addr = task_size - PAGE_SIZE;

	vdsop = kदो_स्मृति(माप(काष्ठा page *), GFP_KERNEL);
	अगर (!vdsop)
		जाओ oom;

	um_vdso = alloc_page(GFP_KERNEL);
	अगर (!um_vdso) अणु
		kमुक्त(vdsop);

		जाओ oom;
	पूर्ण

	copy_page(page_address(um_vdso), vdso_start);
	*vdsop = um_vdso;

	वापस 0;

oom:
	prपूर्णांकk(KERN_ERR "Cannot allocate vdso\n");
	vdso_enabled = 0;

	वापस -ENOMEM;
पूर्ण
subsys_initcall(init_vdso);

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	पूर्णांक err;
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (!vdso_enabled)
		वापस 0;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	err = install_special_mapping(mm, um_vdso_addr, PAGE_SIZE,
		VM_READ|VM_EXEC|
		VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
		vdsop);

	mmap_ग_लिखो_unlock(mm);

	वापस err;
पूर्ण
