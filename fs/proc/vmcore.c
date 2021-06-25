<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	fs/proc/vmcore.c Interface क्रम accessing the crash
 * 				 dump from the प्रणाली's previous lअगरe.
 * 	Heavily borrowed from fs/proc/kcore.c
 *	Created by: Hariprasad Nellitheertha (hari@in.ibm.com)
 *	Copyright (C) IBM Corporation, 2004. All rights reserved
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/kcore.h>
#समावेश <linux/user.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <यंत्र/पन.स>
#समावेश "internal.h"

/* List representing chunks of contiguous memory areas and their offsets in
 * vmcore file.
 */
अटल LIST_HEAD(vmcore_list);

/* Stores the poपूर्णांकer to the buffer containing kernel elf core headers. */
अटल अक्षर *elfcorebuf;
अटल माप_प्रकार elfcorebuf_sz;
अटल माप_प्रकार elfcorebuf_sz_orig;

अटल अक्षर *elfnotes_buf;
अटल माप_प्रकार elfnotes_sz;
/* Size of all notes minus the device dump notes */
अटल माप_प्रकार elfnotes_orig_sz;

/* Total size of vmcore file. */
अटल u64 vmcore_size;

अटल काष्ठा proc_dir_entry *proc_vmcore;

#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
/* Device Dump list and mutex to synchronize access to list */
अटल LIST_HEAD(vmcoredd_list);
अटल DEFINE_MUTEX(vmcoredd_mutex);

अटल bool vmcoredd_disabled;
core_param(novmcoredd, vmcoredd_disabled, bool, 0);
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

/* Device Dump Size */
अटल माप_प्रकार vmcoredd_orig_sz;

/*
 * Returns > 0 क्रम RAM pages, 0 क्रम non-RAM pages, < 0 on error
 * The called function has to take care of module refcounting.
 */
अटल पूर्णांक (*oldmem_pfn_is_ram)(अचिन्हित दीर्घ pfn);

पूर्णांक रेजिस्टर_oldmem_pfn_is_ram(पूर्णांक (*fn)(अचिन्हित दीर्घ pfn))
अणु
	अगर (oldmem_pfn_is_ram)
		वापस -EBUSY;
	oldmem_pfn_is_ram = fn;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_oldmem_pfn_is_ram);

व्योम unरेजिस्टर_oldmem_pfn_is_ram(व्योम)
अणु
	oldmem_pfn_is_ram = शून्य;
	wmb();
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_oldmem_pfn_is_ram);

अटल पूर्णांक pfn_is_ram(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक (*fn)(अचिन्हित दीर्घ pfn);
	/* pfn is ram unless fn() checks pagetype */
	पूर्णांक ret = 1;

	/*
	 * Ask hypervisor अगर the pfn is really ram.
	 * A ballooned page contains no data and पढ़ोing from such a page
	 * will cause high load in the hypervisor.
	 */
	fn = oldmem_pfn_is_ram;
	अगर (fn)
		ret = fn(pfn);

	वापस ret;
पूर्ण

/* Reads a page from the oldmem device from given offset. */
sमाप_प्रकार पढ़ो_from_oldmem(अक्षर *buf, माप_प्रकार count,
			 u64 *ppos, पूर्णांक userbuf,
			 bool encrypted)
अणु
	अचिन्हित दीर्घ pfn, offset;
	माप_प्रकार nr_bytes;
	sमाप_प्रकार पढ़ो = 0, पंचांगp;

	अगर (!count)
		वापस 0;

	offset = (अचिन्हित दीर्घ)(*ppos % PAGE_SIZE);
	pfn = (अचिन्हित दीर्घ)(*ppos / PAGE_SIZE);

	करो अणु
		अगर (count > (PAGE_SIZE - offset))
			nr_bytes = PAGE_SIZE - offset;
		अन्यथा
			nr_bytes = count;

		/* If pfn is not ram, वापस zeros क्रम sparse dump files */
		अगर (pfn_is_ram(pfn) == 0)
			स_रखो(buf, 0, nr_bytes);
		अन्यथा अणु
			अगर (encrypted)
				पंचांगp = copy_oldmem_page_encrypted(pfn, buf,
								 nr_bytes,
								 offset,
								 userbuf);
			अन्यथा
				पंचांगp = copy_oldmem_page(pfn, buf, nr_bytes,
						       offset, userbuf);

			अगर (पंचांगp < 0)
				वापस पंचांगp;
		पूर्ण
		*ppos += nr_bytes;
		count -= nr_bytes;
		buf += nr_bytes;
		पढ़ो += nr_bytes;
		++pfn;
		offset = 0;
	पूर्ण जबतक (count);

	वापस पढ़ो;
पूर्ण

/*
 * Architectures may override this function to allocate ELF header in 2nd kernel
 */
पूर्णांक __weak elfcorehdr_alloc(अचिन्हित दीर्घ दीर्घ *addr, अचिन्हित दीर्घ दीर्घ *size)
अणु
	वापस 0;
पूर्ण

/*
 * Architectures may override this function to मुक्त header
 */
व्योम __weak elfcorehdr_मुक्त(अचिन्हित दीर्घ दीर्घ addr)
अणुपूर्ण

/*
 * Architectures may override this function to पढ़ो from ELF header
 */
sमाप_प्रकार __weak elfcorehdr_पढ़ो(अक्षर *buf, माप_प्रकार count, u64 *ppos)
अणु
	वापस पढ़ो_from_oldmem(buf, count, ppos, 0, false);
पूर्ण

/*
 * Architectures may override this function to पढ़ो from notes sections
 */
sमाप_प्रकार __weak elfcorehdr_पढ़ो_notes(अक्षर *buf, माप_प्रकार count, u64 *ppos)
अणु
	वापस पढ़ो_from_oldmem(buf, count, ppos, 0, mem_encrypt_active());
पूर्ण

/*
 * Architectures may override this function to map oldmem
 */
पूर्णांक __weak remap_oldmem_pfn_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
				  अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	prot = pgprot_encrypted(prot);
	वापस remap_pfn_range(vma, from, pfn, size, prot);
पूर्ण

/*
 * Architectures which support memory encryption override this.
 */
sमाप_प्रकार __weak
copy_oldmem_page_encrypted(अचिन्हित दीर्घ pfn, अक्षर *buf, माप_प्रकार csize,
			   अचिन्हित दीर्घ offset, पूर्णांक userbuf)
अणु
	वापस copy_oldmem_page(pfn, buf, csize, offset, userbuf);
पूर्ण

/*
 * Copy to either kernel or user space
 */
अटल पूर्णांक copy_to(व्योम *target, व्योम *src, माप_प्रकार size, पूर्णांक userbuf)
अणु
	अगर (userbuf) अणु
		अगर (copy_to_user((अक्षर __user *) target, src, size))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		स_नकल(target, src, size);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
अटल पूर्णांक vmcoredd_copy_dumps(व्योम *dst, u64 start, माप_प्रकार size, पूर्णांक userbuf)
अणु
	काष्ठा vmcoredd_node *dump;
	u64 offset = 0;
	पूर्णांक ret = 0;
	माप_प्रकार tsz;
	अक्षर *buf;

	mutex_lock(&vmcoredd_mutex);
	list_क्रम_each_entry(dump, &vmcoredd_list, list) अणु
		अगर (start < offset + dump->size) अणु
			tsz = min(offset + (u64)dump->size - start, (u64)size);
			buf = dump->buf + start - offset;
			अगर (copy_to(dst, buf, tsz, userbuf)) अणु
				ret = -EFAULT;
				जाओ out_unlock;
			पूर्ण

			size -= tsz;
			start += tsz;
			dst += tsz;

			/* Leave now अगर buffer filled alपढ़ोy */
			अगर (!size)
				जाओ out_unlock;
		पूर्ण
		offset += dump->size;
	पूर्ण

out_unlock:
	mutex_unlock(&vmcoredd_mutex);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_MMU
अटल पूर्णांक vmcoredd_mmap_dumps(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ dst,
			       u64 start, माप_प्रकार size)
अणु
	काष्ठा vmcoredd_node *dump;
	u64 offset = 0;
	पूर्णांक ret = 0;
	माप_प्रकार tsz;
	अक्षर *buf;

	mutex_lock(&vmcoredd_mutex);
	list_क्रम_each_entry(dump, &vmcoredd_list, list) अणु
		अगर (start < offset + dump->size) अणु
			tsz = min(offset + (u64)dump->size - start, (u64)size);
			buf = dump->buf + start - offset;
			अगर (remap_vदो_स्मृति_range_partial(vma, dst, buf, 0,
							tsz)) अणु
				ret = -EFAULT;
				जाओ out_unlock;
			पूर्ण

			size -= tsz;
			start += tsz;
			dst += tsz;

			/* Leave now अगर buffer filled alपढ़ोy */
			अगर (!size)
				जाओ out_unlock;
		पूर्ण
		offset += dump->size;
	पूर्ण

out_unlock:
	mutex_unlock(&vmcoredd_mutex);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

/* Read from the ELF header and then the crash dump. On error, negative value is
 * वापसed otherwise number of bytes पढ़ो are वापसed.
 */
अटल sमाप_प्रकार __पढ़ो_vmcore(अक्षर *buffer, माप_प्रकार buflen, loff_t *fpos,
			     पूर्णांक userbuf)
अणु
	sमाप_प्रकार acc = 0, पंचांगp;
	माप_प्रकार tsz;
	u64 start;
	काष्ठा vmcore *m = शून्य;

	अगर (buflen == 0 || *fpos >= vmcore_size)
		वापस 0;

	/* trim buflen to not go beyond खातापूर्ण */
	अगर (buflen > vmcore_size - *fpos)
		buflen = vmcore_size - *fpos;

	/* Read ELF core header */
	अगर (*fpos < elfcorebuf_sz) अणु
		tsz = min(elfcorebuf_sz - (माप_प्रकार)*fpos, buflen);
		अगर (copy_to(buffer, elfcorebuf + *fpos, tsz, userbuf))
			वापस -EFAULT;
		buflen -= tsz;
		*fpos += tsz;
		buffer += tsz;
		acc += tsz;

		/* leave now अगर filled buffer alपढ़ोy */
		अगर (buflen == 0)
			वापस acc;
	पूर्ण

	/* Read Elf note segment */
	अगर (*fpos < elfcorebuf_sz + elfnotes_sz) अणु
		व्योम *kaddr;

		/* We add device dumps beक्रमe other elf notes because the
		 * other elf notes may not fill the elf notes buffer
		 * completely and we will end up with zero-filled data
		 * between the elf notes and the device dumps. Tools will
		 * then try to decode this zero-filled data as valid notes
		 * and we करोn't want that. Hence, adding device dumps beक्रमe
		 * the other elf notes ensure that zero-filled data can be
		 * aव्योमed.
		 */
#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
		/* Read device dumps */
		अगर (*fpos < elfcorebuf_sz + vmcoredd_orig_sz) अणु
			tsz = min(elfcorebuf_sz + vmcoredd_orig_sz -
				  (माप_प्रकार)*fpos, buflen);
			start = *fpos - elfcorebuf_sz;
			अगर (vmcoredd_copy_dumps(buffer, start, tsz, userbuf))
				वापस -EFAULT;

			buflen -= tsz;
			*fpos += tsz;
			buffer += tsz;
			acc += tsz;

			/* leave now अगर filled buffer alपढ़ोy */
			अगर (!buflen)
				वापस acc;
		पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

		/* Read reमुख्यing elf notes */
		tsz = min(elfcorebuf_sz + elfnotes_sz - (माप_प्रकार)*fpos, buflen);
		kaddr = elfnotes_buf + *fpos - elfcorebuf_sz - vmcoredd_orig_sz;
		अगर (copy_to(buffer, kaddr, tsz, userbuf))
			वापस -EFAULT;

		buflen -= tsz;
		*fpos += tsz;
		buffer += tsz;
		acc += tsz;

		/* leave now अगर filled buffer alपढ़ोy */
		अगर (buflen == 0)
			वापस acc;
	पूर्ण

	list_क्रम_each_entry(m, &vmcore_list, list) अणु
		अगर (*fpos < m->offset + m->size) अणु
			tsz = (माप_प्रकार)min_t(अचिन्हित दीर्घ दीर्घ,
					    m->offset + m->size - *fpos,
					    buflen);
			start = m->paddr + *fpos - m->offset;
			पंचांगp = पढ़ो_from_oldmem(buffer, tsz, &start,
					       userbuf, mem_encrypt_active());
			अगर (पंचांगp < 0)
				वापस पंचांगp;
			buflen -= tsz;
			*fpos += tsz;
			buffer += tsz;
			acc += tsz;

			/* leave now अगर filled buffer alपढ़ोy */
			अगर (buflen == 0)
				वापस acc;
		पूर्ण
	पूर्ण

	वापस acc;
पूर्ण

अटल sमाप_प्रकार पढ़ो_vmcore(काष्ठा file *file, अक्षर __user *buffer,
			   माप_प्रकार buflen, loff_t *fpos)
अणु
	वापस __पढ़ो_vmcore((__क्रमce अक्षर *) buffer, buflen, fpos, 1);
पूर्ण

/*
 * The vmcore fault handler uses the page cache and fills data using the
 * standard __vmcore_पढ़ो() function.
 *
 * On s390 the fault handler is used क्रम memory regions that can't be mapped
 * directly with remap_pfn_range().
 */
अटल vm_fault_t mmap_vmcore_fault(काष्ठा vm_fault *vmf)
अणु
#अगर_घोषित CONFIG_S390
	काष्ठा address_space *mapping = vmf->vma->vm_file->f_mapping;
	pgoff_t index = vmf->pgoff;
	काष्ठा page *page;
	loff_t offset;
	अक्षर *buf;
	पूर्णांक rc;

	page = find_or_create_page(mapping, index, GFP_KERNEL);
	अगर (!page)
		वापस VM_FAULT_OOM;
	अगर (!PageUptodate(page)) अणु
		offset = (loff_t) index << PAGE_SHIFT;
		buf = __va((page_to_pfn(page) << PAGE_SHIFT));
		rc = __पढ़ो_vmcore(buf, PAGE_SIZE, &offset, 0);
		अगर (rc < 0) अणु
			unlock_page(page);
			put_page(page);
			वापस vmf_error(rc);
		पूर्ण
		SetPageUptodate(page);
	पूर्ण
	unlock_page(page);
	vmf->page = page;
	वापस 0;
#अन्यथा
	वापस VM_FAULT_SIGBUS;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vmcore_mmap_ops = अणु
	.fault = mmap_vmcore_fault,
पूर्ण;

/**
 * vmcore_alloc_buf - allocate buffer in vदो_स्मृति memory
 * @sizez: size of buffer
 *
 * If CONFIG_MMU is defined, use vदो_स्मृति_user() to allow users to mmap
 * the buffer to user-space by means of remap_vदो_स्मृति_range().
 *
 * If CONFIG_MMU is not defined, use vzalloc() since mmap_vmcore() is
 * disabled and there's no need to allow users to mmap the buffer.
 */
अटल अंतरभूत अक्षर *vmcore_alloc_buf(माप_प्रकार size)
अणु
#अगर_घोषित CONFIG_MMU
	वापस vदो_स्मृति_user(size);
#अन्यथा
	वापस vzalloc(size);
#पूर्ण_अगर
पूर्ण

/*
 * Disable mmap_vmcore() अगर CONFIG_MMU is not defined. MMU is
 * essential क्रम mmap_vmcore() in order to map physically
 * non-contiguous objects (ELF header, ELF note segment and memory
 * regions in the 1st kernel poपूर्णांकed to by PT_LOAD entries) पूर्णांकo
 * भवly contiguous user-space in ELF layout.
 */
#अगर_घोषित CONFIG_MMU
/*
 * remap_oldmem_pfn_checked - करो remap_oldmem_pfn_range replacing all pages
 * reported as not being ram with the zero page.
 *
 * @vma: vm_area_काष्ठा describing requested mapping
 * @from: start remapping from
 * @pfn: page frame number to start remapping to
 * @size: remapping size
 * @prot: protection bits
 *
 * Returns zero on success, -EAGAIN on failure.
 */
अटल पूर्णांक remap_oldmem_pfn_checked(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
				    अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ map_size;
	अचिन्हित दीर्घ pos_start, pos_end, pos;
	अचिन्हित दीर्घ zeropage_pfn = my_zero_pfn(0);
	माप_प्रकार len = 0;

	pos_start = pfn;
	pos_end = pfn + (size >> PAGE_SHIFT);

	क्रम (pos = pos_start; pos < pos_end; ++pos) अणु
		अगर (!pfn_is_ram(pos)) अणु
			/*
			 * We hit a page which is not ram. Remap the continuous
			 * region between pos_start and pos-1 and replace
			 * the non-ram page at pos with the zero page.
			 */
			अगर (pos > pos_start) अणु
				/* Remap continuous region */
				map_size = (pos - pos_start) << PAGE_SHIFT;
				अगर (remap_oldmem_pfn_range(vma, from + len,
							   pos_start, map_size,
							   prot))
					जाओ fail;
				len += map_size;
			पूर्ण
			/* Remap the zero page */
			अगर (remap_oldmem_pfn_range(vma, from + len,
						   zeropage_pfn,
						   PAGE_SIZE, prot))
				जाओ fail;
			len += PAGE_SIZE;
			pos_start = pos + 1;
		पूर्ण
	पूर्ण
	अगर (pos > pos_start) अणु
		/* Remap the rest */
		map_size = (pos - pos_start) << PAGE_SHIFT;
		अगर (remap_oldmem_pfn_range(vma, from + len, pos_start,
					   map_size, prot))
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	करो_munmap(vma->vm_mm, from, len, शून्य);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक vmcore_remap_oldmem_pfn(काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
			    अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	/*
	 * Check अगर oldmem_pfn_is_ram was रेजिस्टरed to aव्योम
	 * looping over all pages without a reason.
	 */
	अगर (oldmem_pfn_is_ram)
		वापस remap_oldmem_pfn_checked(vma, from, pfn, size, prot);
	अन्यथा
		वापस remap_oldmem_pfn_range(vma, from, pfn, size, prot);
पूर्ण

अटल पूर्णांक mmap_vmcore(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	माप_प्रकार size = vma->vm_end - vma->vm_start;
	u64 start, end, len, tsz;
	काष्ठा vmcore *m;

	start = (u64)vma->vm_pgoff << PAGE_SHIFT;
	end = start + size;

	अगर (size > vmcore_size || end > vmcore_size)
		वापस -EINVAL;

	अगर (vma->vm_flags & (VM_WRITE | VM_EXEC))
		वापस -EPERM;

	vma->vm_flags &= ~(VM_MAYWRITE | VM_MAYEXEC);
	vma->vm_flags |= VM_MIXEDMAP;
	vma->vm_ops = &vmcore_mmap_ops;

	len = 0;

	अगर (start < elfcorebuf_sz) अणु
		u64 pfn;

		tsz = min(elfcorebuf_sz - (माप_प्रकार)start, size);
		pfn = __pa(elfcorebuf + start) >> PAGE_SHIFT;
		अगर (remap_pfn_range(vma, vma->vm_start, pfn, tsz,
				    vma->vm_page_prot))
			वापस -EAGAIN;
		size -= tsz;
		start += tsz;
		len += tsz;

		अगर (size == 0)
			वापस 0;
	पूर्ण

	अगर (start < elfcorebuf_sz + elfnotes_sz) अणु
		व्योम *kaddr;

		/* We add device dumps beक्रमe other elf notes because the
		 * other elf notes may not fill the elf notes buffer
		 * completely and we will end up with zero-filled data
		 * between the elf notes and the device dumps. Tools will
		 * then try to decode this zero-filled data as valid notes
		 * and we करोn't want that. Hence, adding device dumps beक्रमe
		 * the other elf notes ensure that zero-filled data can be
		 * aव्योमed. This also ensures that the device dumps and
		 * other elf notes can be properly mmaped at page aligned
		 * address.
		 */
#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
		/* Read device dumps */
		अगर (start < elfcorebuf_sz + vmcoredd_orig_sz) अणु
			u64 start_off;

			tsz = min(elfcorebuf_sz + vmcoredd_orig_sz -
				  (माप_प्रकार)start, size);
			start_off = start - elfcorebuf_sz;
			अगर (vmcoredd_mmap_dumps(vma, vma->vm_start + len,
						start_off, tsz))
				जाओ fail;

			size -= tsz;
			start += tsz;
			len += tsz;

			/* leave now अगर filled buffer alपढ़ोy */
			अगर (!size)
				वापस 0;
		पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

		/* Read reमुख्यing elf notes */
		tsz = min(elfcorebuf_sz + elfnotes_sz - (माप_प्रकार)start, size);
		kaddr = elfnotes_buf + start - elfcorebuf_sz - vmcoredd_orig_sz;
		अगर (remap_vदो_स्मृति_range_partial(vma, vma->vm_start + len,
						kaddr, 0, tsz))
			जाओ fail;

		size -= tsz;
		start += tsz;
		len += tsz;

		अगर (size == 0)
			वापस 0;
	पूर्ण

	list_क्रम_each_entry(m, &vmcore_list, list) अणु
		अगर (start < m->offset + m->size) अणु
			u64 paddr = 0;

			tsz = (माप_प्रकार)min_t(अचिन्हित दीर्घ दीर्घ,
					    m->offset + m->size - start, size);
			paddr = m->paddr + start - m->offset;
			अगर (vmcore_remap_oldmem_pfn(vma, vma->vm_start + len,
						    paddr >> PAGE_SHIFT, tsz,
						    vma->vm_page_prot))
				जाओ fail;
			size -= tsz;
			start += tsz;
			len += tsz;

			अगर (size == 0)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	करो_munmap(vma->vm_mm, vma->vm_start, len, शून्य);
	वापस -EAGAIN;
पूर्ण
#अन्यथा
अटल पूर्णांक mmap_vmcore(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा proc_ops vmcore_proc_ops = अणु
	.proc_पढ़ो	= पढ़ो_vmcore,
	.proc_lseek	= शेष_llseek,
	.proc_mmap	= mmap_vmcore,
पूर्ण;

अटल काष्ठा vmcore* __init get_new_element(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा vmcore), GFP_KERNEL);
पूर्ण

अटल u64 get_vmcore_size(माप_प्रकार elfsz, माप_प्रकार elfnotesegsz,
			   काष्ठा list_head *vc_list)
अणु
	u64 size;
	काष्ठा vmcore *m;

	size = elfsz + elfnotesegsz;
	list_क्रम_each_entry(m, vc_list, list) अणु
		size += m->size;
	पूर्ण
	वापस size;
पूर्ण

/**
 * update_note_header_size_elf64 - update p_memsz member of each PT_NOTE entry
 *
 * @ehdr_ptr: ELF header
 *
 * This function updates p_memsz member of each PT_NOTE entry in the
 * program header table poपूर्णांकed to by @ehdr_ptr to real size of ELF
 * note segment.
 */
अटल पूर्णांक __init update_note_header_size_elf64(स्थिर Elf64_Ehdr *ehdr_ptr)
अणु
	पूर्णांक i, rc=0;
	Elf64_Phdr *phdr_ptr;
	Elf64_Nhdr *nhdr_ptr;

	phdr_ptr = (Elf64_Phdr *)(ehdr_ptr + 1);
	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		व्योम *notes_section;
		u64 offset, max_sz, sz, real_sz = 0;
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		max_sz = phdr_ptr->p_memsz;
		offset = phdr_ptr->p_offset;
		notes_section = kदो_स्मृति(max_sz, GFP_KERNEL);
		अगर (!notes_section)
			वापस -ENOMEM;
		rc = elfcorehdr_पढ़ो_notes(notes_section, max_sz, &offset);
		अगर (rc < 0) अणु
			kमुक्त(notes_section);
			वापस rc;
		पूर्ण
		nhdr_ptr = notes_section;
		जबतक (nhdr_ptr->n_namesz != 0) अणु
			sz = माप(Elf64_Nhdr) +
				(((u64)nhdr_ptr->n_namesz + 3) & ~3) +
				(((u64)nhdr_ptr->n_descsz + 3) & ~3);
			अगर ((real_sz + sz) > max_sz) अणु
				pr_warn("Warning: Exceeded p_memsz, dropping PT_NOTE entry n_namesz=0x%x, n_descsz=0x%x\n",
					nhdr_ptr->n_namesz, nhdr_ptr->n_descsz);
				अवरोध;
			पूर्ण
			real_sz += sz;
			nhdr_ptr = (Elf64_Nhdr*)((अक्षर*)nhdr_ptr + sz);
		पूर्ण
		kमुक्त(notes_section);
		phdr_ptr->p_memsz = real_sz;
		अगर (real_sz == 0) अणु
			pr_warn("Warning: Zero PT_NOTE entries found\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_note_number_and_size_elf64 - get the number of PT_NOTE program
 * headers and sum of real size of their ELF note segment headers and
 * data.
 *
 * @ehdr_ptr: ELF header
 * @nr_ptnote: buffer क्रम the number of PT_NOTE program headers
 * @sz_ptnote: buffer क्रम size of unique PT_NOTE program header
 *
 * This function is used to merge multiple PT_NOTE program headers
 * पूर्णांकo a unique single one. The resulting unique entry will have
 * @sz_ptnote in its phdr->p_mem.
 *
 * It is assumed that program headers with PT_NOTE type poपूर्णांकed to by
 * @ehdr_ptr has alपढ़ोy been updated by update_note_header_size_elf64
 * and each of PT_NOTE program headers has actual ELF note segment
 * size in its p_memsz member.
 */
अटल पूर्णांक __init get_note_number_and_size_elf64(स्थिर Elf64_Ehdr *ehdr_ptr,
						 पूर्णांक *nr_ptnote, u64 *sz_ptnote)
अणु
	पूर्णांक i;
	Elf64_Phdr *phdr_ptr;

	*nr_ptnote = *sz_ptnote = 0;

	phdr_ptr = (Elf64_Phdr *)(ehdr_ptr + 1);
	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		*nr_ptnote += 1;
		*sz_ptnote += phdr_ptr->p_memsz;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * copy_notes_elf64 - copy ELF note segments in a given buffer
 *
 * @ehdr_ptr: ELF header
 * @notes_buf: buffer पूर्णांकo which ELF note segments are copied
 *
 * This function is used to copy ELF note segment in the 1st kernel
 * पूर्णांकo the buffer @notes_buf in the 2nd kernel. It is assumed that
 * size of the buffer @notes_buf is equal to or larger than sum of the
 * real ELF note segment headers and data.
 *
 * It is assumed that program headers with PT_NOTE type poपूर्णांकed to by
 * @ehdr_ptr has alपढ़ोy been updated by update_note_header_size_elf64
 * and each of PT_NOTE program headers has actual ELF note segment
 * size in its p_memsz member.
 */
अटल पूर्णांक __init copy_notes_elf64(स्थिर Elf64_Ehdr *ehdr_ptr, अक्षर *notes_buf)
अणु
	पूर्णांक i, rc=0;
	Elf64_Phdr *phdr_ptr;

	phdr_ptr = (Elf64_Phdr*)(ehdr_ptr + 1);

	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		u64 offset;
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		offset = phdr_ptr->p_offset;
		rc = elfcorehdr_पढ़ो_notes(notes_buf, phdr_ptr->p_memsz,
					   &offset);
		अगर (rc < 0)
			वापस rc;
		notes_buf += phdr_ptr->p_memsz;
	पूर्ण

	वापस 0;
पूर्ण

/* Merges all the PT_NOTE headers पूर्णांकo one. */
अटल पूर्णांक __init merge_note_headers_elf64(अक्षर *elfptr, माप_प्रकार *elfsz,
					   अक्षर **notes_buf, माप_प्रकार *notes_sz)
अणु
	पूर्णांक i, nr_ptnote=0, rc=0;
	अक्षर *पंचांगp;
	Elf64_Ehdr *ehdr_ptr;
	Elf64_Phdr phdr;
	u64 phdr_sz = 0, note_off;

	ehdr_ptr = (Elf64_Ehdr *)elfptr;

	rc = update_note_header_size_elf64(ehdr_ptr);
	अगर (rc < 0)
		वापस rc;

	rc = get_note_number_and_size_elf64(ehdr_ptr, &nr_ptnote, &phdr_sz);
	अगर (rc < 0)
		वापस rc;

	*notes_sz = roundup(phdr_sz, PAGE_SIZE);
	*notes_buf = vmcore_alloc_buf(*notes_sz);
	अगर (!*notes_buf)
		वापस -ENOMEM;

	rc = copy_notes_elf64(ehdr_ptr, *notes_buf);
	अगर (rc < 0)
		वापस rc;

	/* Prepare merged PT_NOTE program header. */
	phdr.p_type    = PT_NOTE;
	phdr.p_flags   = 0;
	note_off = माप(Elf64_Ehdr) +
			(ehdr_ptr->e_phnum - nr_ptnote +1) * माप(Elf64_Phdr);
	phdr.p_offset  = roundup(note_off, PAGE_SIZE);
	phdr.p_vaddr   = phdr.p_paddr = 0;
	phdr.p_filesz  = phdr.p_memsz = phdr_sz;
	phdr.p_align   = 0;

	/* Add merged PT_NOTE program header*/
	पंचांगp = elfptr + माप(Elf64_Ehdr);
	स_नकल(पंचांगp, &phdr, माप(phdr));
	पंचांगp += माप(phdr);

	/* Remove unwanted PT_NOTE program headers. */
	i = (nr_ptnote - 1) * माप(Elf64_Phdr);
	*elfsz = *elfsz - i;
	स_हटाओ(पंचांगp, पंचांगp+i, ((*elfsz)-माप(Elf64_Ehdr)-माप(Elf64_Phdr)));
	स_रखो(elfptr + *elfsz, 0, i);
	*elfsz = roundup(*elfsz, PAGE_SIZE);

	/* Modअगरy e_phnum to reflect merged headers. */
	ehdr_ptr->e_phnum = ehdr_ptr->e_phnum - nr_ptnote + 1;

	/* Store the size of all notes.  We need this to update the note
	 * header when the device dumps will be added.
	 */
	elfnotes_orig_sz = phdr.p_memsz;

	वापस 0;
पूर्ण

/**
 * update_note_header_size_elf32 - update p_memsz member of each PT_NOTE entry
 *
 * @ehdr_ptr: ELF header
 *
 * This function updates p_memsz member of each PT_NOTE entry in the
 * program header table poपूर्णांकed to by @ehdr_ptr to real size of ELF
 * note segment.
 */
अटल पूर्णांक __init update_note_header_size_elf32(स्थिर Elf32_Ehdr *ehdr_ptr)
अणु
	पूर्णांक i, rc=0;
	Elf32_Phdr *phdr_ptr;
	Elf32_Nhdr *nhdr_ptr;

	phdr_ptr = (Elf32_Phdr *)(ehdr_ptr + 1);
	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		व्योम *notes_section;
		u64 offset, max_sz, sz, real_sz = 0;
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		max_sz = phdr_ptr->p_memsz;
		offset = phdr_ptr->p_offset;
		notes_section = kदो_स्मृति(max_sz, GFP_KERNEL);
		अगर (!notes_section)
			वापस -ENOMEM;
		rc = elfcorehdr_पढ़ो_notes(notes_section, max_sz, &offset);
		अगर (rc < 0) अणु
			kमुक्त(notes_section);
			वापस rc;
		पूर्ण
		nhdr_ptr = notes_section;
		जबतक (nhdr_ptr->n_namesz != 0) अणु
			sz = माप(Elf32_Nhdr) +
				(((u64)nhdr_ptr->n_namesz + 3) & ~3) +
				(((u64)nhdr_ptr->n_descsz + 3) & ~3);
			अगर ((real_sz + sz) > max_sz) अणु
				pr_warn("Warning: Exceeded p_memsz, dropping PT_NOTE entry n_namesz=0x%x, n_descsz=0x%x\n",
					nhdr_ptr->n_namesz, nhdr_ptr->n_descsz);
				अवरोध;
			पूर्ण
			real_sz += sz;
			nhdr_ptr = (Elf32_Nhdr*)((अक्षर*)nhdr_ptr + sz);
		पूर्ण
		kमुक्त(notes_section);
		phdr_ptr->p_memsz = real_sz;
		अगर (real_sz == 0) अणु
			pr_warn("Warning: Zero PT_NOTE entries found\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * get_note_number_and_size_elf32 - get the number of PT_NOTE program
 * headers and sum of real size of their ELF note segment headers and
 * data.
 *
 * @ehdr_ptr: ELF header
 * @nr_ptnote: buffer क्रम the number of PT_NOTE program headers
 * @sz_ptnote: buffer क्रम size of unique PT_NOTE program header
 *
 * This function is used to merge multiple PT_NOTE program headers
 * पूर्णांकo a unique single one. The resulting unique entry will have
 * @sz_ptnote in its phdr->p_mem.
 *
 * It is assumed that program headers with PT_NOTE type poपूर्णांकed to by
 * @ehdr_ptr has alपढ़ोy been updated by update_note_header_size_elf32
 * and each of PT_NOTE program headers has actual ELF note segment
 * size in its p_memsz member.
 */
अटल पूर्णांक __init get_note_number_and_size_elf32(स्थिर Elf32_Ehdr *ehdr_ptr,
						 पूर्णांक *nr_ptnote, u64 *sz_ptnote)
अणु
	पूर्णांक i;
	Elf32_Phdr *phdr_ptr;

	*nr_ptnote = *sz_ptnote = 0;

	phdr_ptr = (Elf32_Phdr *)(ehdr_ptr + 1);
	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		*nr_ptnote += 1;
		*sz_ptnote += phdr_ptr->p_memsz;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * copy_notes_elf32 - copy ELF note segments in a given buffer
 *
 * @ehdr_ptr: ELF header
 * @notes_buf: buffer पूर्णांकo which ELF note segments are copied
 *
 * This function is used to copy ELF note segment in the 1st kernel
 * पूर्णांकo the buffer @notes_buf in the 2nd kernel. It is assumed that
 * size of the buffer @notes_buf is equal to or larger than sum of the
 * real ELF note segment headers and data.
 *
 * It is assumed that program headers with PT_NOTE type poपूर्णांकed to by
 * @ehdr_ptr has alपढ़ोy been updated by update_note_header_size_elf32
 * and each of PT_NOTE program headers has actual ELF note segment
 * size in its p_memsz member.
 */
अटल पूर्णांक __init copy_notes_elf32(स्थिर Elf32_Ehdr *ehdr_ptr, अक्षर *notes_buf)
अणु
	पूर्णांक i, rc=0;
	Elf32_Phdr *phdr_ptr;

	phdr_ptr = (Elf32_Phdr*)(ehdr_ptr + 1);

	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		u64 offset;
		अगर (phdr_ptr->p_type != PT_NOTE)
			जारी;
		offset = phdr_ptr->p_offset;
		rc = elfcorehdr_पढ़ो_notes(notes_buf, phdr_ptr->p_memsz,
					   &offset);
		अगर (rc < 0)
			वापस rc;
		notes_buf += phdr_ptr->p_memsz;
	पूर्ण

	वापस 0;
पूर्ण

/* Merges all the PT_NOTE headers पूर्णांकo one. */
अटल पूर्णांक __init merge_note_headers_elf32(अक्षर *elfptr, माप_प्रकार *elfsz,
					   अक्षर **notes_buf, माप_प्रकार *notes_sz)
अणु
	पूर्णांक i, nr_ptnote=0, rc=0;
	अक्षर *पंचांगp;
	Elf32_Ehdr *ehdr_ptr;
	Elf32_Phdr phdr;
	u64 phdr_sz = 0, note_off;

	ehdr_ptr = (Elf32_Ehdr *)elfptr;

	rc = update_note_header_size_elf32(ehdr_ptr);
	अगर (rc < 0)
		वापस rc;

	rc = get_note_number_and_size_elf32(ehdr_ptr, &nr_ptnote, &phdr_sz);
	अगर (rc < 0)
		वापस rc;

	*notes_sz = roundup(phdr_sz, PAGE_SIZE);
	*notes_buf = vmcore_alloc_buf(*notes_sz);
	अगर (!*notes_buf)
		वापस -ENOMEM;

	rc = copy_notes_elf32(ehdr_ptr, *notes_buf);
	अगर (rc < 0)
		वापस rc;

	/* Prepare merged PT_NOTE program header. */
	phdr.p_type    = PT_NOTE;
	phdr.p_flags   = 0;
	note_off = माप(Elf32_Ehdr) +
			(ehdr_ptr->e_phnum - nr_ptnote +1) * माप(Elf32_Phdr);
	phdr.p_offset  = roundup(note_off, PAGE_SIZE);
	phdr.p_vaddr   = phdr.p_paddr = 0;
	phdr.p_filesz  = phdr.p_memsz = phdr_sz;
	phdr.p_align   = 0;

	/* Add merged PT_NOTE program header*/
	पंचांगp = elfptr + माप(Elf32_Ehdr);
	स_नकल(पंचांगp, &phdr, माप(phdr));
	पंचांगp += माप(phdr);

	/* Remove unwanted PT_NOTE program headers. */
	i = (nr_ptnote - 1) * माप(Elf32_Phdr);
	*elfsz = *elfsz - i;
	स_हटाओ(पंचांगp, पंचांगp+i, ((*elfsz)-माप(Elf32_Ehdr)-माप(Elf32_Phdr)));
	स_रखो(elfptr + *elfsz, 0, i);
	*elfsz = roundup(*elfsz, PAGE_SIZE);

	/* Modअगरy e_phnum to reflect merged headers. */
	ehdr_ptr->e_phnum = ehdr_ptr->e_phnum - nr_ptnote + 1;

	/* Store the size of all notes.  We need this to update the note
	 * header when the device dumps will be added.
	 */
	elfnotes_orig_sz = phdr.p_memsz;

	वापस 0;
पूर्ण

/* Add memory chunks represented by program headers to vmcore list. Also update
 * the new offset fields of exported program headers. */
अटल पूर्णांक __init process_ptload_program_headers_elf64(अक्षर *elfptr,
						माप_प्रकार elfsz,
						माप_प्रकार elfnotes_sz,
						काष्ठा list_head *vc_list)
अणु
	पूर्णांक i;
	Elf64_Ehdr *ehdr_ptr;
	Elf64_Phdr *phdr_ptr;
	loff_t vmcore_off;
	काष्ठा vmcore *new;

	ehdr_ptr = (Elf64_Ehdr *)elfptr;
	phdr_ptr = (Elf64_Phdr*)(elfptr + माप(Elf64_Ehdr)); /* PT_NOTE hdr */

	/* Skip Elf header, program headers and Elf note segment. */
	vmcore_off = elfsz + elfnotes_sz;

	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		u64 paddr, start, end, size;

		अगर (phdr_ptr->p_type != PT_LOAD)
			जारी;

		paddr = phdr_ptr->p_offset;
		start = roundकरोwn(paddr, PAGE_SIZE);
		end = roundup(paddr + phdr_ptr->p_memsz, PAGE_SIZE);
		size = end - start;

		/* Add this contiguous chunk of memory to vmcore list.*/
		new = get_new_element();
		अगर (!new)
			वापस -ENOMEM;
		new->paddr = start;
		new->size = size;
		list_add_tail(&new->list, vc_list);

		/* Update the program header offset. */
		phdr_ptr->p_offset = vmcore_off + (paddr - start);
		vmcore_off = vmcore_off + size;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init process_ptload_program_headers_elf32(अक्षर *elfptr,
						माप_प्रकार elfsz,
						माप_प्रकार elfnotes_sz,
						काष्ठा list_head *vc_list)
अणु
	पूर्णांक i;
	Elf32_Ehdr *ehdr_ptr;
	Elf32_Phdr *phdr_ptr;
	loff_t vmcore_off;
	काष्ठा vmcore *new;

	ehdr_ptr = (Elf32_Ehdr *)elfptr;
	phdr_ptr = (Elf32_Phdr*)(elfptr + माप(Elf32_Ehdr)); /* PT_NOTE hdr */

	/* Skip Elf header, program headers and Elf note segment. */
	vmcore_off = elfsz + elfnotes_sz;

	क्रम (i = 0; i < ehdr_ptr->e_phnum; i++, phdr_ptr++) अणु
		u64 paddr, start, end, size;

		अगर (phdr_ptr->p_type != PT_LOAD)
			जारी;

		paddr = phdr_ptr->p_offset;
		start = roundकरोwn(paddr, PAGE_SIZE);
		end = roundup(paddr + phdr_ptr->p_memsz, PAGE_SIZE);
		size = end - start;

		/* Add this contiguous chunk of memory to vmcore list.*/
		new = get_new_element();
		अगर (!new)
			वापस -ENOMEM;
		new->paddr = start;
		new->size = size;
		list_add_tail(&new->list, vc_list);

		/* Update the program header offset */
		phdr_ptr->p_offset = vmcore_off + (paddr - start);
		vmcore_off = vmcore_off + size;
	पूर्ण
	वापस 0;
पूर्ण

/* Sets offset fields of vmcore elements. */
अटल व्योम set_vmcore_list_offsets(माप_प्रकार elfsz, माप_प्रकार elfnotes_sz,
				    काष्ठा list_head *vc_list)
अणु
	loff_t vmcore_off;
	काष्ठा vmcore *m;

	/* Skip Elf header, program headers and Elf note segment. */
	vmcore_off = elfsz + elfnotes_sz;

	list_क्रम_each_entry(m, vc_list, list) अणु
		m->offset = vmcore_off;
		vmcore_off += m->size;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_elfcorebuf(व्योम)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)elfcorebuf, get_order(elfcorebuf_sz_orig));
	elfcorebuf = शून्य;
	vमुक्त(elfnotes_buf);
	elfnotes_buf = शून्य;
पूर्ण

अटल पूर्णांक __init parse_crash_elf64_headers(व्योम)
अणु
	पूर्णांक rc=0;
	Elf64_Ehdr ehdr;
	u64 addr;

	addr = elfcorehdr_addr;

	/* Read Elf header */
	rc = elfcorehdr_पढ़ो((अक्षर *)&ehdr, माप(Elf64_Ehdr), &addr);
	अगर (rc < 0)
		वापस rc;

	/* Do some basic Verअगरication. */
	अगर (स_भेद(ehdr.e_ident, ELFMAG, SELFMAG) != 0 ||
		(ehdr.e_type != ET_CORE) ||
		!vmcore_elf64_check_arch(&ehdr) ||
		ehdr.e_ident[EI_CLASS] != ELFCLASS64 ||
		ehdr.e_ident[EI_VERSION] != EV_CURRENT ||
		ehdr.e_version != EV_CURRENT ||
		ehdr.e_ehsize != माप(Elf64_Ehdr) ||
		ehdr.e_phentsize != माप(Elf64_Phdr) ||
		ehdr.e_phnum == 0) अणु
		pr_warn("Warning: Core image elf header is not sane\n");
		वापस -EINVAL;
	पूर्ण

	/* Read in all elf headers. */
	elfcorebuf_sz_orig = माप(Elf64_Ehdr) +
				ehdr.e_phnum * माप(Elf64_Phdr);
	elfcorebuf_sz = elfcorebuf_sz_orig;
	elfcorebuf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					      get_order(elfcorebuf_sz_orig));
	अगर (!elfcorebuf)
		वापस -ENOMEM;
	addr = elfcorehdr_addr;
	rc = elfcorehdr_पढ़ो(elfcorebuf, elfcorebuf_sz_orig, &addr);
	अगर (rc < 0)
		जाओ fail;

	/* Merge all PT_NOTE headers पूर्णांकo one. */
	rc = merge_note_headers_elf64(elfcorebuf, &elfcorebuf_sz,
				      &elfnotes_buf, &elfnotes_sz);
	अगर (rc)
		जाओ fail;
	rc = process_ptload_program_headers_elf64(elfcorebuf, elfcorebuf_sz,
						  elfnotes_sz, &vmcore_list);
	अगर (rc)
		जाओ fail;
	set_vmcore_list_offsets(elfcorebuf_sz, elfnotes_sz, &vmcore_list);
	वापस 0;
fail:
	मुक्त_elfcorebuf();
	वापस rc;
पूर्ण

अटल पूर्णांक __init parse_crash_elf32_headers(व्योम)
अणु
	पूर्णांक rc=0;
	Elf32_Ehdr ehdr;
	u64 addr;

	addr = elfcorehdr_addr;

	/* Read Elf header */
	rc = elfcorehdr_पढ़ो((अक्षर *)&ehdr, माप(Elf32_Ehdr), &addr);
	अगर (rc < 0)
		वापस rc;

	/* Do some basic Verअगरication. */
	अगर (स_भेद(ehdr.e_ident, ELFMAG, SELFMAG) != 0 ||
		(ehdr.e_type != ET_CORE) ||
		!vmcore_elf32_check_arch(&ehdr) ||
		ehdr.e_ident[EI_CLASS] != ELFCLASS32||
		ehdr.e_ident[EI_VERSION] != EV_CURRENT ||
		ehdr.e_version != EV_CURRENT ||
		ehdr.e_ehsize != माप(Elf32_Ehdr) ||
		ehdr.e_phentsize != माप(Elf32_Phdr) ||
		ehdr.e_phnum == 0) अणु
		pr_warn("Warning: Core image elf header is not sane\n");
		वापस -EINVAL;
	पूर्ण

	/* Read in all elf headers. */
	elfcorebuf_sz_orig = माप(Elf32_Ehdr) + ehdr.e_phnum * माप(Elf32_Phdr);
	elfcorebuf_sz = elfcorebuf_sz_orig;
	elfcorebuf = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					      get_order(elfcorebuf_sz_orig));
	अगर (!elfcorebuf)
		वापस -ENOMEM;
	addr = elfcorehdr_addr;
	rc = elfcorehdr_पढ़ो(elfcorebuf, elfcorebuf_sz_orig, &addr);
	अगर (rc < 0)
		जाओ fail;

	/* Merge all PT_NOTE headers पूर्णांकo one. */
	rc = merge_note_headers_elf32(elfcorebuf, &elfcorebuf_sz,
				      &elfnotes_buf, &elfnotes_sz);
	अगर (rc)
		जाओ fail;
	rc = process_ptload_program_headers_elf32(elfcorebuf, elfcorebuf_sz,
						  elfnotes_sz, &vmcore_list);
	अगर (rc)
		जाओ fail;
	set_vmcore_list_offsets(elfcorebuf_sz, elfnotes_sz, &vmcore_list);
	वापस 0;
fail:
	मुक्त_elfcorebuf();
	वापस rc;
पूर्ण

अटल पूर्णांक __init parse_crash_elf_headers(व्योम)
अणु
	अचिन्हित अक्षर e_ident[EI_NIDENT];
	u64 addr;
	पूर्णांक rc=0;

	addr = elfcorehdr_addr;
	rc = elfcorehdr_पढ़ो(e_ident, EI_NIDENT, &addr);
	अगर (rc < 0)
		वापस rc;
	अगर (स_भेद(e_ident, ELFMAG, SELFMAG) != 0) अणु
		pr_warn("Warning: Core image elf header not found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (e_ident[EI_CLASS] == ELFCLASS64) अणु
		rc = parse_crash_elf64_headers();
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अगर (e_ident[EI_CLASS] == ELFCLASS32) अणु
		rc = parse_crash_elf32_headers();
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		pr_warn("Warning: Core image elf header is not sane\n");
		वापस -EINVAL;
	पूर्ण

	/* Determine vmcore size. */
	vmcore_size = get_vmcore_size(elfcorebuf_sz, elfnotes_sz,
				      &vmcore_list);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
/**
 * vmcoredd_ग_लिखो_header - Write vmcore device dump header at the
 * beginning of the dump's buffer.
 * @buf: Output buffer where the note is written
 * @data: Dump info
 * @size: Size of the dump
 *
 * Fills beginning of the dump's buffer with vmcore device dump header.
 */
अटल व्योम vmcoredd_ग_लिखो_header(व्योम *buf, काष्ठा vmcoredd_data *data,
				  u32 size)
अणु
	काष्ठा vmcoredd_header *vdd_hdr = (काष्ठा vmcoredd_header *)buf;

	vdd_hdr->n_namesz = माप(vdd_hdr->name);
	vdd_hdr->n_descsz = size + माप(vdd_hdr->dump_name);
	vdd_hdr->n_type = NT_VMCOREDD;

	म_नकलन((अक्षर *)vdd_hdr->name, VMCOREDD_NOTE_NAME,
		माप(vdd_hdr->name));
	स_नकल(vdd_hdr->dump_name, data->dump_name, माप(vdd_hdr->dump_name));
पूर्ण

/**
 * vmcoredd_update_program_headers - Update all Elf program headers
 * @elfptr: Poपूर्णांकer to elf header
 * @elfnotesz: Size of elf notes aligned to page size
 * @vmcoreddsz: Size of device dumps to be added to elf note header
 *
 * Determine type of Elf header (Elf64 or Elf32) and update the elf note size.
 * Also update the offsets of all the program headers after the elf note header.
 */
अटल व्योम vmcoredd_update_program_headers(अक्षर *elfptr, माप_प्रकार elfnotesz,
					    माप_प्रकार vmcoreddsz)
अणु
	अचिन्हित अक्षर *e_ident = (अचिन्हित अक्षर *)elfptr;
	u64 start, end, size;
	loff_t vmcore_off;
	u32 i;

	vmcore_off = elfcorebuf_sz + elfnotesz;

	अगर (e_ident[EI_CLASS] == ELFCLASS64) अणु
		Elf64_Ehdr *ehdr = (Elf64_Ehdr *)elfptr;
		Elf64_Phdr *phdr = (Elf64_Phdr *)(elfptr + माप(Elf64_Ehdr));

		/* Update all program headers */
		क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
			अगर (phdr->p_type == PT_NOTE) अणु
				/* Update note size */
				phdr->p_memsz = elfnotes_orig_sz + vmcoreddsz;
				phdr->p_filesz = phdr->p_memsz;
				जारी;
			पूर्ण

			start = roundकरोwn(phdr->p_offset, PAGE_SIZE);
			end = roundup(phdr->p_offset + phdr->p_memsz,
				      PAGE_SIZE);
			size = end - start;
			phdr->p_offset = vmcore_off + (phdr->p_offset - start);
			vmcore_off += size;
		पूर्ण
	पूर्ण अन्यथा अणु
		Elf32_Ehdr *ehdr = (Elf32_Ehdr *)elfptr;
		Elf32_Phdr *phdr = (Elf32_Phdr *)(elfptr + माप(Elf32_Ehdr));

		/* Update all program headers */
		क्रम (i = 0; i < ehdr->e_phnum; i++, phdr++) अणु
			अगर (phdr->p_type == PT_NOTE) अणु
				/* Update note size */
				phdr->p_memsz = elfnotes_orig_sz + vmcoreddsz;
				phdr->p_filesz = phdr->p_memsz;
				जारी;
			पूर्ण

			start = roundकरोwn(phdr->p_offset, PAGE_SIZE);
			end = roundup(phdr->p_offset + phdr->p_memsz,
				      PAGE_SIZE);
			size = end - start;
			phdr->p_offset = vmcore_off + (phdr->p_offset - start);
			vmcore_off += size;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * vmcoredd_update_size - Update the total size of the device dumps and update
 * Elf header
 * @dump_size: Size of the current device dump to be added to total size
 *
 * Update the total size of all the device dumps and update the Elf program
 * headers. Calculate the new offsets क्रम the vmcore list and update the
 * total vmcore size.
 */
अटल व्योम vmcoredd_update_size(माप_प्रकार dump_size)
अणु
	vmcoredd_orig_sz += dump_size;
	elfnotes_sz = roundup(elfnotes_orig_sz, PAGE_SIZE) + vmcoredd_orig_sz;
	vmcoredd_update_program_headers(elfcorebuf, elfnotes_sz,
					vmcoredd_orig_sz);

	/* Update vmcore list offsets */
	set_vmcore_list_offsets(elfcorebuf_sz, elfnotes_sz, &vmcore_list);

	vmcore_size = get_vmcore_size(elfcorebuf_sz, elfnotes_sz,
				      &vmcore_list);
	proc_vmcore->size = vmcore_size;
पूर्ण

/**
 * vmcore_add_device_dump - Add a buffer containing device dump to vmcore
 * @data: dump info.
 *
 * Allocate a buffer and invoke the calling driver's dump collect routine.
 * Write Elf note at the beginning of the buffer to indicate vmcore device
 * dump and add the dump to global list.
 */
पूर्णांक vmcore_add_device_dump(काष्ठा vmcoredd_data *data)
अणु
	काष्ठा vmcoredd_node *dump;
	व्योम *buf = शून्य;
	माप_प्रकार data_size;
	पूर्णांक ret;

	अगर (vmcoredd_disabled) अणु
		pr_err_once("Device dump is disabled\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!data || !म_माप(data->dump_name) ||
	    !data->vmcoredd_callback || !data->size)
		वापस -EINVAL;

	dump = vzalloc(माप(*dump));
	अगर (!dump) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/* Keep size of the buffer page aligned so that it can be mmaped */
	data_size = roundup(माप(काष्ठा vmcoredd_header) + data->size,
			    PAGE_SIZE);

	/* Allocate buffer क्रम driver's to ग_लिखो their dumps */
	buf = vmcore_alloc_buf(data_size);
	अगर (!buf) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	vmcoredd_ग_लिखो_header(buf, data, data_size -
			      माप(काष्ठा vmcoredd_header));

	/* Invoke the driver's dump collection routing */
	ret = data->vmcoredd_callback(data, buf +
				      माप(काष्ठा vmcoredd_header));
	अगर (ret)
		जाओ out_err;

	dump->buf = buf;
	dump->size = data_size;

	/* Add the dump to driver sysfs list */
	mutex_lock(&vmcoredd_mutex);
	list_add_tail(&dump->list, &vmcoredd_list);
	mutex_unlock(&vmcoredd_mutex);

	vmcoredd_update_size(data_size);
	वापस 0;

out_err:
	vमुक्त(buf);
	vमुक्त(dump);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vmcore_add_device_dump);
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

/* Free all dumps in vmcore device dump list */
अटल व्योम vmcore_मुक्त_device_dumps(व्योम)
अणु
#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
	mutex_lock(&vmcoredd_mutex);
	जबतक (!list_empty(&vmcoredd_list)) अणु
		काष्ठा vmcoredd_node *dump;

		dump = list_first_entry(&vmcoredd_list, काष्ठा vmcoredd_node,
					list);
		list_del(&dump->list);
		vमुक्त(dump->buf);
		vमुक्त(dump);
	पूर्ण
	mutex_unlock(&vmcoredd_mutex);
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */
पूर्ण

/* Init function क्रम vmcore module. */
अटल पूर्णांक __init vmcore_init(व्योम)
अणु
	पूर्णांक rc = 0;

	/* Allow architectures to allocate ELF header in 2nd kernel */
	rc = elfcorehdr_alloc(&elfcorehdr_addr, &elfcorehdr_size);
	अगर (rc)
		वापस rc;
	/*
	 * If elfcorehdr= has been passed in cmdline or created in 2nd kernel,
	 * then capture the dump.
	 */
	अगर (!(is_vmcore_usable()))
		वापस rc;
	rc = parse_crash_elf_headers();
	अगर (rc) अणु
		pr_warn("Kdump: vmcore not initialized\n");
		वापस rc;
	पूर्ण
	elfcorehdr_मुक्त(elfcorehdr_addr);
	elfcorehdr_addr = ELFCORE_ADDR_ERR;

	proc_vmcore = proc_create("vmcore", S_IRUSR, शून्य, &vmcore_proc_ops);
	अगर (proc_vmcore)
		proc_vmcore->size = vmcore_size;
	वापस 0;
पूर्ण
fs_initcall(vmcore_init);

/* Cleanup function क्रम vmcore module. */
व्योम vmcore_cleanup(व्योम)
अणु
	अगर (proc_vmcore) अणु
		proc_हटाओ(proc_vmcore);
		proc_vmcore = शून्य;
	पूर्ण

	/* clear the vmcore list. */
	जबतक (!list_empty(&vmcore_list)) अणु
		काष्ठा vmcore *m;

		m = list_first_entry(&vmcore_list, काष्ठा vmcore, list);
		list_del(&m->list);
		kमुक्त(m);
	पूर्ण
	मुक्त_elfcorebuf();

	/* clear vmcore device dump list */
	vmcore_मुक्त_device_dumps();
पूर्ण
