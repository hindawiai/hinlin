<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/drivers/अक्षर/mem.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Added devfs support.
 *    Jan-11-1998, C. Scott Ananian <cananian@alumni.princeton.edu>
 *  Shared /dev/zero mmapping support, Feb 2000, Kanoj Sarcar <kanoj@sgi.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mman.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/init.h>
#समावेश <linux/raw.h>
#समावेश <linux/tty.h>
#समावेश <linux/capability.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/device.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/splice.h>
#समावेश <linux/pfn.h>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/uपन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/security.h>

#अगर_घोषित CONFIG_IA64
# include <linux/efi.h>
#पूर्ण_अगर

#घोषणा DEVMEM_MINOR	1
#घोषणा DEVPORT_MINOR	4

अटल अंतरभूत अचिन्हित दीर्घ size_inside_page(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ sz;

	sz = PAGE_SIZE - (start & (PAGE_SIZE - 1));

	वापस min(sz, size);
पूर्ण

#अगर_अघोषित ARCH_HAS_VALID_PHYS_ADDR_RANGE
अटल अंतरभूत पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार count)
अणु
	वापस addr + count <= __pa(high_memory);
पूर्ण

अटल अंतरभूत पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_STRICT_DEVMEM
अटल अंतरभूत पूर्णांक page_is_allowed(अचिन्हित दीर्घ pfn)
अणु
	वापस devmem_is_allowed(pfn);
पूर्ण
अटल अंतरभूत पूर्णांक range_is_allowed(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	u64 from = ((u64)pfn) << PAGE_SHIFT;
	u64 to = from + size;
	u64 cursor = from;

	जबतक (cursor < to) अणु
		अगर (!devmem_is_allowed(pfn))
			वापस 0;
		cursor += PAGE_SIZE;
		pfn++;
	पूर्ण
	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक page_is_allowed(अचिन्हित दीर्घ pfn)
अणु
	वापस 1;
पूर्ण
अटल अंतरभूत पूर्णांक range_is_allowed(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित unxlate_dev_mem_ptr
#घोषणा unxlate_dev_mem_ptr unxlate_dev_mem_ptr
व्योम __weak unxlate_dev_mem_ptr(phys_addr_t phys, व्योम *addr)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool should_stop_iteration(व्योम)
अणु
	अगर (need_resched())
		cond_resched();
	वापस fatal_संकेत_pending(current);
पूर्ण

/*
 * This funcion पढ़ोs the *physical* memory. The f_pos poपूर्णांकs directly to the
 * memory location.
 */
अटल sमाप_प्रकार पढ़ो_mem(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	phys_addr_t p = *ppos;
	sमाप_प्रकार पढ़ो, sz;
	व्योम *ptr;
	अक्षर *bounce;
	पूर्णांक err;

	अगर (p != *ppos)
		वापस 0;

	अगर (!valid_phys_addr_range(p, count))
		वापस -EFAULT;
	पढ़ो = 0;
#अगर_घोषित __ARCH_HAS_NO_PAGE_ZERO_MAPPED
	/* we करोn't have page 0 mapped on sparc and m68k.. */
	अगर (p < PAGE_SIZE) अणु
		sz = size_inside_page(p, count);
		अगर (sz > 0) अणु
			अगर (clear_user(buf, sz))
				वापस -EFAULT;
			buf += sz;
			p += sz;
			count -= sz;
			पढ़ो += sz;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	bounce = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!bounce)
		वापस -ENOMEM;

	जबतक (count > 0) अणु
		अचिन्हित दीर्घ reमुख्यing;
		पूर्णांक allowed, probe;

		sz = size_inside_page(p, count);

		err = -EPERM;
		allowed = page_is_allowed(p >> PAGE_SHIFT);
		अगर (!allowed)
			जाओ failed;

		err = -EFAULT;
		अगर (allowed == 2) अणु
			/* Show zeros क्रम restricted memory. */
			reमुख्यing = clear_user(buf, sz);
		पूर्ण अन्यथा अणु
			/*
			 * On ia64 अगर a page has been mapped somewhere as
			 * uncached, then it must also be accessed uncached
			 * by the kernel or data corruption may occur.
			 */
			ptr = xlate_dev_mem_ptr(p);
			अगर (!ptr)
				जाओ failed;

			probe = copy_from_kernel_nofault(bounce, ptr, sz);
			unxlate_dev_mem_ptr(p, ptr);
			अगर (probe)
				जाओ failed;

			reमुख्यing = copy_to_user(buf, bounce, sz);
		पूर्ण

		अगर (reमुख्यing)
			जाओ failed;

		buf += sz;
		p += sz;
		count -= sz;
		पढ़ो += sz;
		अगर (should_stop_iteration())
			अवरोध;
	पूर्ण
	kमुक्त(bounce);

	*ppos += पढ़ो;
	वापस पढ़ो;

failed:
	kमुक्त(bounce);
	वापस err;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_mem(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	phys_addr_t p = *ppos;
	sमाप_प्रकार written, sz;
	अचिन्हित दीर्घ copied;
	व्योम *ptr;

	अगर (p != *ppos)
		वापस -EFBIG;

	अगर (!valid_phys_addr_range(p, count))
		वापस -EFAULT;

	written = 0;

#अगर_घोषित __ARCH_HAS_NO_PAGE_ZERO_MAPPED
	/* we करोn't have page 0 mapped on sparc and m68k.. */
	अगर (p < PAGE_SIZE) अणु
		sz = size_inside_page(p, count);
		/* Hmm. Do something? */
		buf += sz;
		p += sz;
		count -= sz;
		written += sz;
	पूर्ण
#पूर्ण_अगर

	जबतक (count > 0) अणु
		पूर्णांक allowed;

		sz = size_inside_page(p, count);

		allowed = page_is_allowed(p >> PAGE_SHIFT);
		अगर (!allowed)
			वापस -EPERM;

		/* Skip actual writing when a page is marked as restricted. */
		अगर (allowed == 1) अणु
			/*
			 * On ia64 अगर a page has been mapped somewhere as
			 * uncached, then it must also be accessed uncached
			 * by the kernel or data corruption may occur.
			 */
			ptr = xlate_dev_mem_ptr(p);
			अगर (!ptr) अणु
				अगर (written)
					अवरोध;
				वापस -EFAULT;
			पूर्ण

			copied = copy_from_user(ptr, buf, sz);
			unxlate_dev_mem_ptr(p, ptr);
			अगर (copied) अणु
				written += sz - copied;
				अगर (written)
					अवरोध;
				वापस -EFAULT;
			पूर्ण
		पूर्ण

		buf += sz;
		p += sz;
		count -= sz;
		written += sz;
		अगर (should_stop_iteration())
			अवरोध;
	पूर्ण

	*ppos += written;
	वापस written;
पूर्ण

पूर्णांक __weak phys_mem_access_prot_allowed(काष्ठा file *file,
	अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t *vma_prot)
अणु
	वापस 1;
पूर्ण

#अगर_अघोषित __HAVE_PHYS_MEM_ACCESS_PROT

/*
 * Architectures vary in how they handle caching क्रम addresses
 * outside of मुख्य memory.
 *
 */
#अगर_घोषित pgprot_noncached
अटल पूर्णांक uncached_access(काष्ठा file *file, phys_addr_t addr)
अणु
#अगर defined(CONFIG_IA64)
	/*
	 * On ia64, we ignore O_DSYNC because we cannot tolerate memory
	 * attribute aliases.
	 */
	वापस !(efi_mem_attributes(addr) & EFI_MEMORY_WB);
#अन्यथा
	/*
	 * Accessing memory above the top the kernel knows about or through a
	 * file poपूर्णांकer
	 * that was marked O_DSYNC will be करोne non-cached.
	 */
	अगर (file->f_flags & O_DSYNC)
		वापस 1;
	वापस addr >= __pa(high_memory);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
#अगर_घोषित pgprot_noncached
	phys_addr_t offset = pfn << PAGE_SHIFT;

	अगर (uncached_access(file, offset))
		वापस pgprot_noncached(vma_prot);
#पूर्ण_अगर
	वापस vma_prot;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित CONFIG_MMU
अटल अचिन्हित दीर्घ get_unmapped_area_mem(काष्ठा file *file,
					   अचिन्हित दीर्घ addr,
					   अचिन्हित दीर्घ len,
					   अचिन्हित दीर्घ pgoff,
					   अचिन्हित दीर्घ flags)
अणु
	अगर (!valid_mmap_phys_addr_range(pgoff, len))
		वापस (अचिन्हित दीर्घ) -EINVAL;
	वापस pgoff << PAGE_SHIFT;
पूर्ण

/* permit direct mmap, क्रम पढ़ो, ग_लिखो or exec */
अटल अचिन्हित memory_mmap_capabilities(काष्ठा file *file)
अणु
	वापस NOMMU_MAP_सूचीECT |
		NOMMU_MAP_READ | NOMMU_MAP_WRITE | NOMMU_MAP_EXEC;
पूर्ण

अटल अचिन्हित zero_mmap_capabilities(काष्ठा file *file)
अणु
	वापस NOMMU_MAP_COPY;
पूर्ण

/* can't do an in-place private mapping if there's no MMU */
अटल अंतरभूत पूर्णांक निजी_mapping_ok(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस vma->vm_flags & VM_MAYSHARE;
पूर्ण
#अन्यथा

अटल अंतरभूत पूर्णांक निजी_mapping_ok(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा vm_operations_काष्ठा mmap_mem_ops = अणु
#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक mmap_mem(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार size = vma->vm_end - vma->vm_start;
	phys_addr_t offset = (phys_addr_t)vma->vm_pgoff << PAGE_SHIFT;

	/* Does it even fit in phys_addr_t? */
	अगर (offset >> PAGE_SHIFT != vma->vm_pgoff)
		वापस -EINVAL;

	/* It's illegal to wrap around the end of the physical address space. */
	अगर (offset + (phys_addr_t)size - 1 < offset)
		वापस -EINVAL;

	अगर (!valid_mmap_phys_addr_range(vma->vm_pgoff, size))
		वापस -EINVAL;

	अगर (!निजी_mapping_ok(vma))
		वापस -ENOSYS;

	अगर (!range_is_allowed(vma->vm_pgoff, size))
		वापस -EPERM;

	अगर (!phys_mem_access_prot_allowed(file, vma->vm_pgoff, size,
						&vma->vm_page_prot))
		वापस -EINVAL;

	vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff,
						 size,
						 vma->vm_page_prot);

	vma->vm_ops = &mmap_mem_ops;

	/* Remap-pfn-range will mark the range VM_IO */
	अगर (remap_pfn_range(vma,
			    vma->vm_start,
			    vma->vm_pgoff,
			    size,
			    vma->vm_page_prot)) अणु
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार पढ़ो_port(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ i = *ppos;
	अक्षर __user *पंचांगp = buf;

	अगर (!access_ok(buf, count))
		वापस -EFAULT;
	जबतक (count-- > 0 && i < 65536) अणु
		अगर (__put_user(inb(i), पंचांगp) < 0)
			वापस -EFAULT;
		i++;
		पंचांगp++;
	पूर्ण
	*ppos = i;
	वापस पंचांगp-buf;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_port(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ i = *ppos;
	स्थिर अक्षर __user *पंचांगp = buf;

	अगर (!access_ok(buf, count))
		वापस -EFAULT;
	जबतक (count-- > 0 && i < 65536) अणु
		अक्षर c;

		अगर (__get_user(c, पंचांगp)) अणु
			अगर (पंचांगp > buf)
				अवरोध;
			वापस -EFAULT;
		पूर्ण
		outb(c, i);
		i++;
		पंचांगp++;
	पूर्ण
	*ppos = i;
	वापस पंचांगp-buf;
पूर्ण

अटल sमाप_प्रकार पढ़ो_null(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_null(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

अटल sमाप_प्रकार पढ़ो_iter_null(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_iter_null(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	माप_प्रकार count = iov_iter_count(from);
	iov_iter_advance(from, count);
	वापस count;
पूर्ण

अटल पूर्णांक pipe_to_null(काष्ठा pipe_inode_info *info, काष्ठा pipe_buffer *buf,
			काष्ठा splice_desc *sd)
अणु
	वापस sd->len;
पूर्ण

अटल sमाप_प्रकार splice_ग_लिखो_null(काष्ठा pipe_inode_info *pipe, काष्ठा file *out,
				 loff_t *ppos, माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	वापस splice_from_pipe(pipe, out, ppos, len, flags, pipe_to_null);
पूर्ण

अटल sमाप_प्रकार पढ़ो_iter_zero(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	माप_प्रकार written = 0;

	जबतक (iov_iter_count(iter)) अणु
		माप_प्रकार chunk = iov_iter_count(iter), n;

		अगर (chunk > PAGE_SIZE)
			chunk = PAGE_SIZE;	/* Just क्रम latency reasons */
		n = iov_iter_zero(chunk, iter);
		अगर (!n && iov_iter_count(iter))
			वापस written ? written : -EFAULT;
		written += n;
		अगर (संकेत_pending(current))
			वापस written ? written : -ERESTARTSYS;
		cond_resched();
	पूर्ण
	वापस written;
पूर्ण

अटल sमाप_प्रकार पढ़ो_zero(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	माप_प्रकार cleared = 0;

	जबतक (count) अणु
		माप_प्रकार chunk = min_t(माप_प्रकार, count, PAGE_SIZE);
		माप_प्रकार left;

		left = clear_user(buf + cleared, chunk);
		अगर (unlikely(left)) अणु
			cleared += (chunk - left);
			अगर (!cleared)
				वापस -EFAULT;
			अवरोध;
		पूर्ण
		cleared += chunk;
		count -= chunk;

		अगर (संकेत_pending(current))
			अवरोध;
		cond_resched();
	पूर्ण

	वापस cleared;
पूर्ण

अटल पूर्णांक mmap_zero(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
#अगर_अघोषित CONFIG_MMU
	वापस -ENOSYS;
#पूर्ण_अगर
	अगर (vma->vm_flags & VM_SHARED)
		वापस shmem_zero_setup(vma);
	vma_set_anonymous(vma);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ get_unmapped_area_zero(काष्ठा file *file,
				अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
#अगर_घोषित CONFIG_MMU
	अगर (flags & MAP_SHARED) अणु
		/*
		 * mmap_zero() will call shmem_zero_setup() to create a file,
		 * so use shmem's get_unmapped_area in हाल it can be huge;
		 * and pass शून्य क्रम file as in mmap.c's get_unmapped_area(),
		 * so as not to confuse shmem with our handle on "/dev/zero".
		 */
		वापस shmem_get_unmapped_area(शून्य, addr, len, pgoff, flags);
	पूर्ण

	/* Otherwise flags & MAP_PRIVATE: with no shmem object beneath it */
	वापस current->mm->get_unmapped_area(file, addr, len, pgoff, flags);
#अन्यथा
	वापस -ENOSYS;
#पूर्ण_अगर
पूर्ण

अटल sमाप_प्रकार ग_लिखो_full(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	वापस -ENOSPC;
पूर्ण

/*
 * Special lseek() function क्रम /dev/null and /dev/zero.  Most notably, you
 * can ख_खोलो() both devices with "a" now.  This was previously impossible.
 * -- SRB.
 */
अटल loff_t null_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	वापस file->f_pos = 0;
पूर्ण

/*
 * The memory devices use the full 32/64 bits of the offset, and so we cannot
 * check against negative addresses: they are ok. The वापस value is weird,
 * though, in that हाल (0).
 *
 * also note that seeking relative to the "end of file" isn't supported:
 * it has no meaning, so it वापसs -EINVAL.
 */
अटल loff_t memory_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	loff_t ret;

	inode_lock(file_inode(file));
	चयन (orig) अणु
	हाल प्रस्तुत_से:
		offset += file->f_pos;
		fallthrough;
	हाल शुरू_से:
		/* to aव्योम userland mistaking f_pos=-9 as -EBADF=-9 */
		अगर ((अचिन्हित दीर्घ दीर्घ)offset >= -MAX_ERRNO) अणु
			ret = -EOVERFLOW;
			अवरोध;
		पूर्ण
		file->f_pos = offset;
		ret = file->f_pos;
		क्रमce_successful_syscall_वापस();
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	inode_unlock(file_inode(file));
	वापस ret;
पूर्ण

अटल पूर्णांक खोलो_port(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक rc;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	rc = security_locked_करोwn(LOCKDOWN_DEV_MEM);
	अगर (rc)
		वापस rc;

	अगर (iminor(inode) != DEVMEM_MINOR)
		वापस 0;

	/*
	 * Use a unअगरied address space to have a single poपूर्णांक to manage
	 * revocations when drivers want to take over a /dev/mem mapped
	 * range.
	 */
	filp->f_mapping = iomem_get_mapping();

	वापस 0;
पूर्ण

#घोषणा zero_lseek	null_lseek
#घोषणा full_lseek      null_lseek
#घोषणा ग_लिखो_zero	ग_लिखो_null
#घोषणा ग_लिखो_iter_zero	ग_लिखो_iter_null
#घोषणा खोलो_mem	खोलो_port

अटल स्थिर काष्ठा file_operations __maybe_unused mem_fops = अणु
	.llseek		= memory_lseek,
	.पढ़ो		= पढ़ो_mem,
	.ग_लिखो		= ग_लिखो_mem,
	.mmap		= mmap_mem,
	.खोलो		= खोलो_mem,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = get_unmapped_area_mem,
	.mmap_capabilities = memory_mmap_capabilities,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा file_operations null_fops = अणु
	.llseek		= null_lseek,
	.पढ़ो		= पढ़ो_null,
	.ग_लिखो		= ग_लिखो_null,
	.पढ़ो_iter	= पढ़ो_iter_null,
	.ग_लिखो_iter	= ग_लिखो_iter_null,
	.splice_ग_लिखो	= splice_ग_लिखो_null,
पूर्ण;

अटल स्थिर काष्ठा file_operations __maybe_unused port_fops = अणु
	.llseek		= memory_lseek,
	.पढ़ो		= पढ़ो_port,
	.ग_लिखो		= ग_लिखो_port,
	.खोलो		= खोलो_port,
पूर्ण;

अटल स्थिर काष्ठा file_operations zero_fops = अणु
	.llseek		= zero_lseek,
	.ग_लिखो		= ग_लिखो_zero,
	.पढ़ो_iter	= पढ़ो_iter_zero,
	.पढ़ो		= पढ़ो_zero,
	.ग_लिखो_iter	= ग_लिखो_iter_zero,
	.mmap		= mmap_zero,
	.get_unmapped_area = get_unmapped_area_zero,
#अगर_अघोषित CONFIG_MMU
	.mmap_capabilities = zero_mmap_capabilities,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा file_operations full_fops = अणु
	.llseek		= full_lseek,
	.पढ़ो_iter	= पढ़ो_iter_zero,
	.ग_लिखो		= ग_लिखो_full,
पूर्ण;

अटल स्थिर काष्ठा memdev अणु
	स्थिर अक्षर *name;
	umode_t mode;
	स्थिर काष्ठा file_operations *fops;
	भ_शेषe_t भ_शेषe;
पूर्ण devlist[] = अणु
#अगर_घोषित CONFIG_DEVMEM
	 [DEVMEM_MINOR] = अणु "mem", 0, &mem_fops, FMODE_UNSIGNED_OFFSET पूर्ण,
#पूर्ण_अगर
	 [3] = अणु "null", 0666, &null_fops, 0 पूर्ण,
#अगर_घोषित CONFIG_DEVPORT
	 [4] = अणु "port", 0, &port_fops, 0 पूर्ण,
#पूर्ण_अगर
	 [5] = अणु "zero", 0666, &zero_fops, 0 पूर्ण,
	 [7] = अणु "full", 0666, &full_fops, 0 पूर्ण,
	 [8] = अणु "random", 0666, &अक्रमom_fops, 0 पूर्ण,
	 [9] = अणु "urandom", 0666, &uअक्रमom_fops, 0 पूर्ण,
#अगर_घोषित CONFIG_PRINTK
	[11] = अणु "kmsg", 0644, &kmsg_fops, 0 पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक memory_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक minor;
	स्थिर काष्ठा memdev *dev;

	minor = iminor(inode);
	अगर (minor >= ARRAY_SIZE(devlist))
		वापस -ENXIO;

	dev = &devlist[minor];
	अगर (!dev->fops)
		वापस -ENXIO;

	filp->f_op = dev->fops;
	filp->f_mode |= dev->भ_शेषe;

	अगर (dev->fops->खोलो)
		वापस dev->fops->खोलो(inode, filp);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations memory_fops = अणु
	.खोलो = memory_खोलो,
	.llseek = noop_llseek,
पूर्ण;

अटल अक्षर *mem_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode && devlist[MINOR(dev->devt)].mode)
		*mode = devlist[MINOR(dev->devt)].mode;
	वापस शून्य;
पूर्ण

अटल काष्ठा class *mem_class;

अटल पूर्णांक __init chr_dev_init(व्योम)
अणु
	पूर्णांक minor;

	अगर (रेजिस्टर_chrdev(MEM_MAJOR, "mem", &memory_fops))
		prपूर्णांकk("unable to get major %d for memory devs\n", MEM_MAJOR);

	mem_class = class_create(THIS_MODULE, "mem");
	अगर (IS_ERR(mem_class))
		वापस PTR_ERR(mem_class);

	mem_class->devnode = mem_devnode;
	क्रम (minor = 1; minor < ARRAY_SIZE(devlist); minor++) अणु
		अगर (!devlist[minor].name)
			जारी;

		/*
		 * Create /dev/port?
		 */
		अगर ((minor == DEVPORT_MINOR) && !arch_has_dev_port())
			जारी;

		device_create(mem_class, शून्य, MKDEV(MEM_MAJOR, minor),
			      शून्य, devlist[minor].name);
	पूर्ण

	वापस tty_init();
पूर्ण

fs_initcall(chr_dev_init);
