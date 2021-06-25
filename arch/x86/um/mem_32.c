<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Riअक्षरd Weinberger <richrd@nod.at>
 */

#समावेश <linux/mm.h>
#समावेश <यंत्र/elf.h>

अटल काष्ठा vm_area_काष्ठा gate_vma;

अटल पूर्णांक __init gate_vma_init(व्योम)
अणु
	अगर (!FIXADDR_USER_START)
		वापस 0;

	vma_init(&gate_vma, शून्य);
	gate_vma.vm_start = FIXADDR_USER_START;
	gate_vma.vm_end = FIXADDR_USER_END;
	gate_vma.vm_flags = VM_READ | VM_MAYREAD | VM_EXEC | VM_MAYEXEC;
	gate_vma.vm_page_prot = __P101;

	वापस 0;
पूर्ण
__initcall(gate_vma_init);

काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm)
अणु
	वापस FIXADDR_USER_START ? &gate_vma : शून्य;
पूर्ण

पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr)
अणु
	अगर (!FIXADDR_USER_START)
		वापस 0;

	अगर ((addr >= FIXADDR_USER_START) && (addr < FIXADDR_USER_END))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma = get_gate_vma(mm);

	अगर (!vma)
		वापस 0;

	वापस (addr >= vma->vm_start) && (addr < vma->vm_end);
पूर्ण
