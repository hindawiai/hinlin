<शैली गुरु>
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2011-2012 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>

/* sys_cacheflush -- flush the processor cache. */
यंत्रlinkage पूर्णांक sys_cacheflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				अचिन्हित पूर्णांक op)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (len == 0)
		वापस 0;

	/* We only support op 0 now, वापस error अगर op is non-zero.*/
	अगर (op)
		वापस -EINVAL;

	/* Check क्रम overflow */
	अगर (addr + len < addr)
		वापस -EFAULT;

	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस -EINTR;

	/*
	 * Verअगरy that the specअगरied address region actually beदीर्घs
	 * to this process.
	 */
	vma = find_vma(mm, addr);
	अगर (vma == शून्य || addr < vma->vm_start || addr + len > vma->vm_end) अणु
		mmap_पढ़ो_unlock(mm);
		वापस -EFAULT;
	पूर्ण

	flush_cache_range(vma, addr, addr + len);

	mmap_पढ़ो_unlock(mm);
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक sys_getpagesize(व्योम)
अणु
	वापस PAGE_SIZE;
पूर्ण
