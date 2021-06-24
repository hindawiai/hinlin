<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	fs/proc/kcore.c kernel ELF core dumper
 *
 *	Modelled on fs/exec.c:aout_core_dump()
 *	Jeremy Fitzhardinge <jeremy@sw.oz.au>
 *	ELF version written by David Howells <David.Howells@nexor.co.uk>
 *	Modअगरied and incorporated पूर्णांकo 2.3.x by Tigran Aivazian <tigran@veritas.com>
 *	Support to dump vदो_स्मृति'd areas (ELF only), Tigran Aivazian <tigran@veritas.com>
 *	Safe accesses to vदो_स्मृति/direct-mapped discontiguous areas, Kanoj Sarcar <kanoj@sgi.com>
 */

#समावेश <linux/crash_core.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/kcore.h>
#समावेश <linux/user.h>
#समावेश <linux/capability.h>
#समावेश <linux/elf.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/ioport.h>
#समावेश <linux/memory.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/sections.h>
#समावेश "internal.h"

#घोषणा CORE_STR "CORE"

#अगर_अघोषित ELF_CORE_EFLAGS
#घोषणा ELF_CORE_EFLAGS	0
#पूर्ण_अगर

अटल काष्ठा proc_dir_entry *proc_root_kcore;


#अगर_अघोषित kc_vaddr_to_offset
#घोषणा	kc_vaddr_to_offset(v) ((v) - PAGE_OFFSET)
#पूर्ण_अगर
#अगर_अघोषित	kc_offset_to_vaddr
#घोषणा	kc_offset_to_vaddr(o) ((o) + PAGE_OFFSET)
#पूर्ण_अगर

अटल LIST_HEAD(kclist_head);
अटल DECLARE_RWSEM(kclist_lock);
अटल पूर्णांक kcore_need_update = 1;

/*
 * Returns > 0 क्रम RAM pages, 0 क्रम non-RAM pages, < 0 on error
 * Same as oldmem_pfn_is_ram in vmcore
 */
अटल पूर्णांक (*mem_pfn_is_ram)(अचिन्हित दीर्घ pfn);

पूर्णांक __init रेजिस्टर_mem_pfn_is_ram(पूर्णांक (*fn)(अचिन्हित दीर्घ pfn))
अणु
	अगर (mem_pfn_is_ram)
		वापस -EBUSY;
	mem_pfn_is_ram = fn;
	वापस 0;
पूर्ण

अटल पूर्णांक pfn_is_ram(अचिन्हित दीर्घ pfn)
अणु
	अगर (mem_pfn_is_ram)
		वापस mem_pfn_is_ram(pfn);
	अन्यथा
		वापस 1;
पूर्ण

/* This करोesn't grab kclist_lock, so it should only be used at init समय. */
व्योम __init kclist_add(काष्ठा kcore_list *new, व्योम *addr, माप_प्रकार size,
		       पूर्णांक type)
अणु
	new->addr = (अचिन्हित दीर्घ)addr;
	new->size = size;
	new->type = type;

	list_add_tail(&new->list, &kclist_head);
पूर्ण

अटल माप_प्रकार get_kcore_size(पूर्णांक *nphdr, माप_प्रकार *phdrs_len, माप_प्रकार *notes_len,
			     माप_प्रकार *data_offset)
अणु
	माप_प्रकार try, size;
	काष्ठा kcore_list *m;

	*nphdr = 1; /* PT_NOTE */
	size = 0;

	list_क्रम_each_entry(m, &kclist_head, list) अणु
		try = kc_vaddr_to_offset((माप_प्रकार)m->addr + m->size);
		अगर (try > size)
			size = try;
		*nphdr = *nphdr + 1;
	पूर्ण

	*phdrs_len = *nphdr * माप(काष्ठा elf_phdr);
	*notes_len = (4 * माप(काष्ठा elf_note) +
		      3 * ALIGN(माप(CORE_STR), 4) +
		      VMCOREINFO_NOTE_NAME_BYTES +
		      ALIGN(माप(काष्ठा elf_prstatus), 4) +
		      ALIGN(माप(काष्ठा elf_prpsinfo), 4) +
		      ALIGN(arch_task_काष्ठा_size, 4) +
		      ALIGN(vmcoreinfo_size, 4));
	*data_offset = PAGE_ALIGN(माप(काष्ठा elfhdr) + *phdrs_len +
				  *notes_len);
	वापस *data_offset + size;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/*
 * If no highmem, we can assume [0...max_low_pfn) continuous range of memory
 * because memory hole is not as big as !HIGHMEM हाल.
 * (HIGHMEM is special because part of memory is _invisible_ from the kernel.)
 */
अटल पूर्णांक kcore_ram_list(काष्ठा list_head *head)
अणु
	काष्ठा kcore_list *ent;

	ent = kदो_स्मृति(माप(*ent), GFP_KERNEL);
	अगर (!ent)
		वापस -ENOMEM;
	ent->addr = (अचिन्हित दीर्घ)__va(0);
	ent->size = max_low_pfn << PAGE_SHIFT;
	ent->type = KCORE_RAM;
	list_add(&ent->list, head);
	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_HIGHMEM */

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
/* calculate vmemmap's address from given प्रणाली ram pfn and रेजिस्टर it */
अटल पूर्णांक
get_sparsemem_vmemmap_info(काष्ठा kcore_list *ent, काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ pfn = __pa(ent->addr) >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = ent->size >> PAGE_SHIFT;
	अचिन्हित दीर्घ start, end;
	काष्ठा kcore_list *vmm, *पंचांगp;


	start = ((अचिन्हित दीर्घ)pfn_to_page(pfn)) & PAGE_MASK;
	end = ((अचिन्हित दीर्घ)pfn_to_page(pfn + nr_pages)) - 1;
	end = PAGE_ALIGN(end);
	/* overlap check (because we have to align page */
	list_क्रम_each_entry(पंचांगp, head, list) अणु
		अगर (पंचांगp->type != KCORE_VMEMMAP)
			जारी;
		अगर (start < पंचांगp->addr + पंचांगp->size)
			अगर (end > पंचांगp->addr)
				end = पंचांगp->addr;
	पूर्ण
	अगर (start < end) अणु
		vmm = kदो_स्मृति(माप(*vmm), GFP_KERNEL);
		अगर (!vmm)
			वापस 0;
		vmm->addr = start;
		vmm->size = end - start;
		vmm->type = KCORE_VMEMMAP;
		list_add_tail(&vmm->list, head);
	पूर्ण
	वापस 1;

पूर्ण
#अन्यथा
अटल पूर्णांक
get_sparsemem_vmemmap_info(काष्ठा kcore_list *ent, काष्ठा list_head *head)
अणु
	वापस 1;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक
kclist_add_निजी(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ nr_pages, व्योम *arg)
अणु
	काष्ठा list_head *head = (काष्ठा list_head *)arg;
	काष्ठा kcore_list *ent;
	काष्ठा page *p;

	अगर (!pfn_valid(pfn))
		वापस 1;

	p = pfn_to_page(pfn);

	ent = kदो_स्मृति(माप(*ent), GFP_KERNEL);
	अगर (!ent)
		वापस -ENOMEM;
	ent->addr = (अचिन्हित दीर्घ)page_to_virt(p);
	ent->size = nr_pages << PAGE_SHIFT;

	अगर (!virt_addr_valid(ent->addr))
		जाओ मुक्त_out;

	/* cut not-mapped area. ....from ppc-32 code. */
	अगर (अच_दीर्घ_उच्च - ent->addr < ent->size)
		ent->size = अच_दीर्घ_उच्च - ent->addr;

	/*
	 * We've alपढ़ोy checked virt_addr_valid so we know this address
	 * is a valid poपूर्णांकer, thereक्रमe we can check against it to determine
	 * अगर we need to trim
	 */
	अगर (VMALLOC_START > ent->addr) अणु
		अगर (VMALLOC_START - ent->addr < ent->size)
			ent->size = VMALLOC_START - ent->addr;
	पूर्ण

	ent->type = KCORE_RAM;
	list_add_tail(&ent->list, head);

	अगर (!get_sparsemem_vmemmap_info(ent, head)) अणु
		list_del(&ent->list);
		जाओ मुक्त_out;
	पूर्ण

	वापस 0;
मुक्त_out:
	kमुक्त(ent);
	वापस 1;
पूर्ण

अटल पूर्णांक kcore_ram_list(काष्ठा list_head *list)
अणु
	पूर्णांक nid, ret;
	अचिन्हित दीर्घ end_pfn;

	/* Not inialized....update now */
	/* find out "max pfn" */
	end_pfn = 0;
	क्रम_each_node_state(nid, N_MEMORY) अणु
		अचिन्हित दीर्घ node_end;
		node_end = node_end_pfn(nid);
		अगर (end_pfn < node_end)
			end_pfn = node_end;
	पूर्ण
	/* scan 0 to max_pfn */
	ret = walk_प्रणाली_ram_range(0, end_pfn, list, kclist_add_निजी);
	अगर (ret)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

अटल पूर्णांक kcore_update_ram(व्योम)
अणु
	LIST_HEAD(list);
	LIST_HEAD(garbage);
	पूर्णांक nphdr;
	माप_प्रकार phdrs_len, notes_len, data_offset;
	काष्ठा kcore_list *पंचांगp, *pos;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&kclist_lock);
	अगर (!xchg(&kcore_need_update, 0))
		जाओ out;

	ret = kcore_ram_list(&list);
	अगर (ret) अणु
		/* Couldn't get the RAM list, try again next समय. */
		WRITE_ONCE(kcore_need_update, 1);
		list_splice_tail(&list, &garbage);
		जाओ out;
	पूर्ण

	list_क्रम_each_entry_safe(pos, पंचांगp, &kclist_head, list) अणु
		अगर (pos->type == KCORE_RAM || pos->type == KCORE_VMEMMAP)
			list_move(&pos->list, &garbage);
	पूर्ण
	list_splice_tail(&list, &kclist_head);

	proc_root_kcore->size = get_kcore_size(&nphdr, &phdrs_len, &notes_len,
					       &data_offset);

out:
	up_ग_लिखो(&kclist_lock);
	list_क्रम_each_entry_safe(pos, पंचांगp, &garbage, list) अणु
		list_del(&pos->list);
		kमुक्त(pos);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम append_kcore_note(अक्षर *notes, माप_प्रकार *i, स्थिर अक्षर *name,
			      अचिन्हित पूर्णांक type, स्थिर व्योम *desc,
			      माप_प्रकार descsz)
अणु
	काष्ठा elf_note *note = (काष्ठा elf_note *)&notes[*i];

	note->n_namesz = म_माप(name) + 1;
	note->n_descsz = descsz;
	note->n_type = type;
	*i += माप(*note);
	स_नकल(&notes[*i], name, note->n_namesz);
	*i = ALIGN(*i + note->n_namesz, 4);
	स_नकल(&notes[*i], desc, descsz);
	*i = ALIGN(*i + descsz, 4);
पूर्ण

अटल sमाप_प्रकार
पढ़ो_kcore(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार buflen, loff_t *fpos)
अणु
	अक्षर *buf = file->निजी_data;
	माप_प्रकार phdrs_offset, notes_offset, data_offset;
	माप_प्रकार phdrs_len, notes_len;
	काष्ठा kcore_list *m;
	माप_प्रकार tsz;
	पूर्णांक nphdr;
	अचिन्हित दीर्घ start;
	माप_प्रकार orig_buflen = buflen;
	पूर्णांक ret = 0;

	करोwn_पढ़ो(&kclist_lock);

	get_kcore_size(&nphdr, &phdrs_len, &notes_len, &data_offset);
	phdrs_offset = माप(काष्ठा elfhdr);
	notes_offset = phdrs_offset + phdrs_len;

	/* ELF file header. */
	अगर (buflen && *fpos < माप(काष्ठा elfhdr)) अणु
		काष्ठा elfhdr ehdr = अणु
			.e_ident = अणु
				[EI_MAG0] = ELFMAG0,
				[EI_MAG1] = ELFMAG1,
				[EI_MAG2] = ELFMAG2,
				[EI_MAG3] = ELFMAG3,
				[EI_CLASS] = ELF_CLASS,
				[EI_DATA] = ELF_DATA,
				[EI_VERSION] = EV_CURRENT,
				[EI_OSABI] = ELF_OSABI,
			पूर्ण,
			.e_type = ET_CORE,
			.e_machine = ELF_ARCH,
			.e_version = EV_CURRENT,
			.e_phoff = माप(काष्ठा elfhdr),
			.e_flags = ELF_CORE_EFLAGS,
			.e_ehsize = माप(काष्ठा elfhdr),
			.e_phentsize = माप(काष्ठा elf_phdr),
			.e_phnum = nphdr,
		पूर्ण;

		tsz = min_t(माप_प्रकार, buflen, माप(काष्ठा elfhdr) - *fpos);
		अगर (copy_to_user(buffer, (अक्षर *)&ehdr + *fpos, tsz)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		buffer += tsz;
		buflen -= tsz;
		*fpos += tsz;
	पूर्ण

	/* ELF program headers. */
	अगर (buflen && *fpos < phdrs_offset + phdrs_len) अणु
		काष्ठा elf_phdr *phdrs, *phdr;

		phdrs = kzalloc(phdrs_len, GFP_KERNEL);
		अगर (!phdrs) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		phdrs[0].p_type = PT_NOTE;
		phdrs[0].p_offset = notes_offset;
		phdrs[0].p_filesz = notes_len;

		phdr = &phdrs[1];
		list_क्रम_each_entry(m, &kclist_head, list) अणु
			phdr->p_type = PT_LOAD;
			phdr->p_flags = PF_R | PF_W | PF_X;
			phdr->p_offset = kc_vaddr_to_offset(m->addr) + data_offset;
			अगर (m->type == KCORE_REMAP)
				phdr->p_vaddr = (माप_प्रकार)m->vaddr;
			अन्यथा
				phdr->p_vaddr = (माप_प्रकार)m->addr;
			अगर (m->type == KCORE_RAM || m->type == KCORE_REMAP)
				phdr->p_paddr = __pa(m->addr);
			अन्यथा अगर (m->type == KCORE_TEXT)
				phdr->p_paddr = __pa_symbol(m->addr);
			अन्यथा
				phdr->p_paddr = (elf_addr_t)-1;
			phdr->p_filesz = phdr->p_memsz = m->size;
			phdr->p_align = PAGE_SIZE;
			phdr++;
		पूर्ण

		tsz = min_t(माप_प्रकार, buflen, phdrs_offset + phdrs_len - *fpos);
		अगर (copy_to_user(buffer, (अक्षर *)phdrs + *fpos - phdrs_offset,
				 tsz)) अणु
			kमुक्त(phdrs);
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		kमुक्त(phdrs);

		buffer += tsz;
		buflen -= tsz;
		*fpos += tsz;
	पूर्ण

	/* ELF note segment. */
	अगर (buflen && *fpos < notes_offset + notes_len) अणु
		काष्ठा elf_prstatus prstatus = अणुपूर्ण;
		काष्ठा elf_prpsinfo prpsinfo = अणु
			.pr_sname = 'R',
			.pr_fname = "vmlinux",
		पूर्ण;
		अक्षर *notes;
		माप_प्रकार i = 0;

		strlcpy(prpsinfo.pr_psargs, saved_command_line,
			माप(prpsinfo.pr_psargs));

		notes = kzalloc(notes_len, GFP_KERNEL);
		अगर (!notes) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		append_kcore_note(notes, &i, CORE_STR, NT_PRSTATUS, &prstatus,
				  माप(prstatus));
		append_kcore_note(notes, &i, CORE_STR, NT_PRPSINFO, &prpsinfo,
				  माप(prpsinfo));
		append_kcore_note(notes, &i, CORE_STR, NT_TASKSTRUCT, current,
				  arch_task_काष्ठा_size);
		/*
		 * vmcoreinfo_size is mostly स्थिरant after init समय, but it
		 * can be changed by crash_save_vmcoreinfo(). Racing here with a
		 * panic on another CPU beक्रमe the machine goes करोwn is insanely
		 * unlikely, but it's better to not leave potential buffer
		 * overflows lying around, regardless.
		 */
		append_kcore_note(notes, &i, VMCOREINFO_NOTE_NAME, 0,
				  vmcoreinfo_data,
				  min(vmcoreinfo_size, notes_len - i));

		tsz = min_t(माप_प्रकार, buflen, notes_offset + notes_len - *fpos);
		अगर (copy_to_user(buffer, notes + *fpos - notes_offset, tsz)) अणु
			kमुक्त(notes);
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		kमुक्त(notes);

		buffer += tsz;
		buflen -= tsz;
		*fpos += tsz;
	पूर्ण

	/*
	 * Check to see अगर our file offset matches with any of
	 * the addresses in the elf_phdr on our list.
	 */
	start = kc_offset_to_vaddr(*fpos - data_offset);
	अगर ((tsz = (PAGE_SIZE - (start & ~PAGE_MASK))) > buflen)
		tsz = buflen;

	m = शून्य;
	जबतक (buflen) अणु
		/*
		 * If this is the first iteration or the address is not within
		 * the previous entry, search क्रम a matching entry.
		 */
		अगर (!m || start < m->addr || start >= m->addr + m->size) अणु
			list_क्रम_each_entry(m, &kclist_head, list) अणु
				अगर (start >= m->addr &&
				    start < m->addr + m->size)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (&m->list == &kclist_head) अणु
			अगर (clear_user(buffer, tsz)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
			m = शून्य;	/* skip the list anchor */
		पूर्ण अन्यथा अगर (!pfn_is_ram(__pa(start) >> PAGE_SHIFT)) अणु
			अगर (clear_user(buffer, tsz)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (m->type == KCORE_VMALLOC) अणु
			vपढ़ो(buf, (अक्षर *)start, tsz);
			/* we have to zero-fill user buffer even अगर no पढ़ो */
			अगर (copy_to_user(buffer, buf, tsz)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (m->type == KCORE_USER) अणु
			/* User page is handled prior to normal kernel page: */
			अगर (copy_to_user(buffer, (अक्षर *)start, tsz)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (kern_addr_valid(start)) अणु
				/*
				 * Using bounce buffer to bypass the
				 * hardened user copy kernel text checks.
				 */
				अगर (copy_from_kernel_nofault(buf, (व्योम *)start,
						tsz)) अणु
					अगर (clear_user(buffer, tsz)) अणु
						ret = -EFAULT;
						जाओ out;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (copy_to_user(buffer, buf, tsz)) अणु
						ret = -EFAULT;
						जाओ out;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (clear_user(buffer, tsz)) अणु
					ret = -EFAULT;
					जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
		buflen -= tsz;
		*fpos += tsz;
		buffer += tsz;
		start += tsz;
		tsz = (buflen > PAGE_SIZE ? PAGE_SIZE : buflen);
	पूर्ण

out:
	up_पढ़ो(&kclist_lock);
	अगर (ret)
		वापस ret;
	वापस orig_buflen - buflen;
पूर्ण

अटल पूर्णांक खोलो_kcore(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret = security_locked_करोwn(LOCKDOWN_KCORE);

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	अगर (ret)
		वापस ret;

	filp->निजी_data = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!filp->निजी_data)
		वापस -ENOMEM;

	अगर (kcore_need_update)
		kcore_update_ram();
	अगर (i_size_पढ़ो(inode) != proc_root_kcore->size) अणु
		inode_lock(inode);
		i_size_ग_लिखो(inode, proc_root_kcore->size);
		inode_unlock(inode);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक release_kcore(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops kcore_proc_ops = अणु
	.proc_पढ़ो	= पढ़ो_kcore,
	.proc_खोलो	= खोलो_kcore,
	.proc_release	= release_kcore,
	.proc_lseek	= शेष_llseek,
पूर्ण;

/* just remember that we have to update kcore */
अटल पूर्णांक __meminit kcore_callback(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ action, व्योम *arg)
अणु
	चयन (action) अणु
	हाल MEM_ONLINE:
	हाल MEM_OFFLINE:
		kcore_need_update = 1;
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block kcore_callback_nb __meminitdata = अणु
	.notअगरier_call = kcore_callback,
	.priority = 0,
पूर्ण;

अटल काष्ठा kcore_list kcore_vदो_स्मृति;

#अगर_घोषित CONFIG_ARCH_PROC_KCORE_TEXT
अटल काष्ठा kcore_list kcore_text;
/*
 * If defined, special segment is used क्रम mapping kernel text instead of
 * direct-map area. We need to create special TEXT section.
 */
अटल व्योम __init proc_kcore_text_init(व्योम)
अणु
	kclist_add(&kcore_text, _text, _end - _text, KCORE_TEXT);
पूर्ण
#अन्यथा
अटल व्योम __init proc_kcore_text_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MODULES) && defined(MODULES_VADDR)
/*
 * MODULES_VADDR has no पूर्णांकersection with VMALLOC_ADDR.
 */
अटल काष्ठा kcore_list kcore_modules;
अटल व्योम __init add_modules_range(व्योम)
अणु
	अगर (MODULES_VADDR != VMALLOC_START && MODULES_END != VMALLOC_END) अणु
		kclist_add(&kcore_modules, (व्योम *)MODULES_VADDR,
			MODULES_END - MODULES_VADDR, KCORE_VMALLOC);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init add_modules_range(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init proc_kcore_init(व्योम)
अणु
	proc_root_kcore = proc_create("kcore", S_IRUSR, शून्य, &kcore_proc_ops);
	अगर (!proc_root_kcore) अणु
		pr_err("couldn't create /proc/kcore\n");
		वापस 0; /* Always वापसs 0. */
	पूर्ण
	/* Store text area अगर it's special */
	proc_kcore_text_init();
	/* Store vदो_स्मृति area */
	kclist_add(&kcore_vदो_स्मृति, (व्योम *)VMALLOC_START,
		VMALLOC_END - VMALLOC_START, KCORE_VMALLOC);
	add_modules_range();
	/* Store direct-map area from physical memory map */
	kcore_update_ram();
	रेजिस्टर_hoपंचांगemory_notअगरier(&kcore_callback_nb);

	वापस 0;
पूर्ण
fs_initcall(proc_kcore_init);
