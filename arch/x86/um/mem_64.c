<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <यंत्र/elf.h>

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma->vm_mm && vma->vm_start == um_vdso_addr)
		वापस "[vdso]";

	वापस शून्य;
पूर्ण
