<शैली गुरु>
/*
 * arch/xtensa/kernel/syscall.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Copyright (C) 1995 - 2000 by Ralf Baechle
 *
 * Joe Taylor <joe@tensilica.com, joetylr@yahoo.com>
 * Marc Gauthier <marc@tensilica.com, marc@alumni.uwaterloo.ca>
 * Chris Zankel <chris@zankel.net>
 * Kevin Chea
 *
 */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/syscall.h>
#समावेश <linux/linkage.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/shm.h>

syscall_t sys_call_table[] /* FIXME __cacheline_aligned */= अणु
#घोषणा __SYSCALL(nr, entry)	(syscall_t)entry,
#समावेश <यंत्र/syscall_table.h>
पूर्ण;

#घोषणा COLOUR_ALIGN(addr, pgoff) \
	((((addr) + SHMLBA - 1) & ~(SHMLBA - 1)) + \
	 (((pgoff) << PAGE_SHIFT) & (SHMLBA - 1)))

यंत्रlinkage दीर्घ xtensa_shmat(पूर्णांक shmid, अक्षर __user *shmaddr, पूर्णांक shmflg)
अणु
	अचिन्हित दीर्घ ret;
	दीर्घ err;

	err = करो_shmat(shmid, shmaddr, shmflg, &ret, SHMLBA);
	अगर (err)
		वापस err;
	वापस (दीर्घ)ret;
पूर्ण

यंत्रlinkage दीर्घ xtensa_fadvise64_64(पूर्णांक fd, पूर्णांक advice,
		अचिन्हित दीर्घ दीर्घ offset, अचिन्हित दीर्घ दीर्घ len)
अणु
	वापस ksys_fadvise64_64(fd, offset, len, advice);
पूर्ण

#अगर_घोषित CONFIG_MMU
अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vmm;

	अगर (flags & MAP_FIXED) अणु
		/* We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
				((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1)))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (len > TASK_SIZE)
		वापस -ENOMEM;
	अगर (!addr)
		addr = TASK_UNMAPPED_BASE;

	अगर (flags & MAP_SHARED)
		addr = COLOUR_ALIGN(addr, pgoff);
	अन्यथा
		addr = PAGE_ALIGN(addr);

	क्रम (vmm = find_vma(current->mm, addr); ; vmm = vmm->vm_next) अणु
		/* At this poपूर्णांक:  (!vmm || addr < vmm->vm_end). */
		अगर (TASK_SIZE - len < addr)
			वापस -ENOMEM;
		अगर (!vmm || addr + len <= vm_start_gap(vmm))
			वापस addr;
		addr = vmm->vm_end;
		अगर (flags & MAP_SHARED)
			addr = COLOUR_ALIGN(addr, pgoff);
	पूर्ण
पूर्ण
#पूर्ण_अगर
