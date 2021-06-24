<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/kernel/sys_sh.c
 *
 * This file contains various अक्रमom प्रणाली calls that
 * have a non-standard calling sequence on the Linux/SuperH
 * platक्रमm.
 *
 * Taken from i386 version.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/utsname.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/ipc.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachectl.h>

यंत्रlinkage पूर्णांक old_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
	पूर्णांक fd, अचिन्हित दीर्घ off)
अणु
	अगर (off & ~PAGE_MASK)
		वापस -EINVAL;
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, off>>PAGE_SHIFT);
पूर्ण

यंत्रlinkage दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
	अचिन्हित दीर्घ fd, अचिन्हित दीर्घ pgoff)
अणु
	/*
	 * The shअगरt क्रम mmap2 is स्थिरant, regardless of PAGE_SIZE
	 * setting.
	 */
	अगर (pgoff & ((1 << (PAGE_SHIFT - 12)) - 1))
		वापस -EINVAL;

	pgoff >>= PAGE_SHIFT - 12;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
पूर्ण

/* sys_cacheflush -- flush (part of) the processor cache.  */
यंत्रlinkage पूर्णांक sys_cacheflush(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, पूर्णांक op)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	अगर ((op <= 0) || (op > (CACHEFLUSH_D_PURGE|CACHEFLUSH_I)))
		वापस -EINVAL;

	/*
	 * Verअगरy that the specअगरied address region actually beदीर्घs
	 * to this process.
	 */
	अगर (addr + len < addr)
		वापस -EFAULT;

	mmap_पढ़ो_lock(current->mm);
	vma = find_vma (current->mm, addr);
	अगर (vma == शून्य || addr < vma->vm_start || addr + len > vma->vm_end) अणु
		mmap_पढ़ो_unlock(current->mm);
		वापस -EFAULT;
	पूर्ण

	चयन (op & CACHEFLUSH_D_PURGE) अणु
		हाल CACHEFLUSH_D_INVAL:
			__flush_invalidate_region((व्योम *)addr, len);
			अवरोध;
		हाल CACHEFLUSH_D_WB:
			__flush_wback_region((व्योम *)addr, len);
			अवरोध;
		हाल CACHEFLUSH_D_PURGE:
			__flush_purge_region((व्योम *)addr, len);
			अवरोध;
	पूर्ण

	अगर (op & CACHEFLUSH_I)
		flush_icache_range(addr, addr+len);

	mmap_पढ़ो_unlock(current->mm);
	वापस 0;
पूर्ण
