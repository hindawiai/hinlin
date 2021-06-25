<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Davidlohr Bueso.
 */
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmacache.h>

/*
 * Hash based on the pmd of addr अगर configured with MMU, which provides a good
 * hit rate क्रम workloads with spatial locality.  Otherwise, use pages.
 */
#अगर_घोषित CONFIG_MMU
#घोषणा VMACACHE_SHIFT	PMD_SHIFT
#अन्यथा
#घोषणा VMACACHE_SHIFT	PAGE_SHIFT
#पूर्ण_अगर
#घोषणा VMACACHE_HASH(addr) ((addr >> VMACACHE_SHIFT) & VMACACHE_MASK)

/*
 * This task may be accessing a क्रमeign mm via (क्रम example)
 * get_user_pages()->find_vma().  The vmacache is task-local and this
 * task's vmacache pertains to a dअगरferent mm (ie, its own).  There is
 * nothing we can करो here.
 *
 * Also handle the हाल where a kernel thपढ़ो has aकरोpted this mm via
 * kthपढ़ो_use_mm(). That kernel thपढ़ो's vmacache is not applicable to this mm.
 */
अटल अंतरभूत bool vmacache_valid_mm(काष्ठा mm_काष्ठा *mm)
अणु
	वापस current->mm == mm && !(current->flags & PF_KTHREAD);
पूर्ण

व्योम vmacache_update(अचिन्हित दीर्घ addr, काष्ठा vm_area_काष्ठा *newvma)
अणु
	अगर (vmacache_valid_mm(newvma->vm_mm))
		current->vmacache.vmas[VMACACHE_HASH(addr)] = newvma;
पूर्ण

अटल bool vmacache_valid(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा task_काष्ठा *curr;

	अगर (!vmacache_valid_mm(mm))
		वापस false;

	curr = current;
	अगर (mm->vmacache_seqnum != curr->vmacache.seqnum) अणु
		/*
		 * First attempt will always be invalid, initialize
		 * the new cache क्रम this task here.
		 */
		curr->vmacache.seqnum = mm->vmacache_seqnum;
		vmacache_flush(curr);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा vm_area_काष्ठा *vmacache_find(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक idx = VMACACHE_HASH(addr);
	पूर्णांक i;

	count_vm_vmacache_event(VMACACHE_FIND_CALLS);

	अगर (!vmacache_valid(mm))
		वापस शून्य;

	क्रम (i = 0; i < VMACACHE_SIZE; i++) अणु
		काष्ठा vm_area_काष्ठा *vma = current->vmacache.vmas[idx];

		अगर (vma) अणु
#अगर_घोषित CONFIG_DEBUG_VM_VMACACHE
			अगर (WARN_ON_ONCE(vma->vm_mm != mm))
				अवरोध;
#पूर्ण_अगर
			अगर (vma->vm_start <= addr && vma->vm_end > addr) अणु
				count_vm_vmacache_event(VMACACHE_FIND_HITS);
				वापस vma;
			पूर्ण
		पूर्ण
		अगर (++idx == VMACACHE_SIZE)
			idx = 0;
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_अघोषित CONFIG_MMU
काष्ठा vm_area_काष्ठा *vmacache_find_exact(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ end)
अणु
	पूर्णांक idx = VMACACHE_HASH(start);
	पूर्णांक i;

	count_vm_vmacache_event(VMACACHE_FIND_CALLS);

	अगर (!vmacache_valid(mm))
		वापस शून्य;

	क्रम (i = 0; i < VMACACHE_SIZE; i++) अणु
		काष्ठा vm_area_काष्ठा *vma = current->vmacache.vmas[idx];

		अगर (vma && vma->vm_start == start && vma->vm_end == end) अणु
			count_vm_vmacache_event(VMACACHE_FIND_HITS);
			वापस vma;
		पूर्ण
		अगर (++idx == VMACACHE_SIZE)
			idx = 0;
	पूर्ण

	वापस शून्य;
पूर्ण
#पूर्ण_अगर
