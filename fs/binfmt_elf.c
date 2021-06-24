<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/binfmt_elf.c
 *
 * These are the functions used to load ELF क्रमmat executables as used
 * on SVr4 machines.  Inक्रमmation on the क्रमmat may be found in the book
 * "UNIX SYSTEM V RELEASE 4 Programmers Guide: Ansi C and Programming Support
 * Tools".
 *
 * Copyright 1993, 1994: Eric Youngdale (ericy@cais.com).
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/log2.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/binfmts.h>
#समावेश <linux/माला.स>
#समावेश <linux/file.h>
#समावेश <linux/slab.h>
#समावेश <linux/personality.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/init.h>
#समावेश <linux/highuid.h>
#समावेश <linux/compiler.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/security.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/elf.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/utsname.h>
#समावेश <linux/coredump.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/sizes.h>
#समावेश <linux/types.h>
#समावेश <linux/cred.h>
#समावेश <linux/dax.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/page.h>

#अगर_अघोषित ELF_COMPAT
#घोषणा ELF_COMPAT 0
#पूर्ण_अगर

#अगर_अघोषित user_दीर्घ_t
#घोषणा user_दीर्घ_t दीर्घ
#पूर्ण_अगर
#अगर_अघोषित user_siginfo_t
#घोषणा user_siginfo_t siginfo_t
#पूर्ण_अगर

/* That's क्रम binfmt_elf_fdpic to deal with */
#अगर_अघोषित elf_check_fdpic
#घोषणा elf_check_fdpic(ex) false
#पूर्ण_अगर

अटल पूर्णांक load_elf_binary(काष्ठा linux_binprm *bprm);

#अगर_घोषित CONFIG_USELIB
अटल पूर्णांक load_elf_library(काष्ठा file *);
#अन्यथा
#घोषणा load_elf_library शून्य
#पूर्ण_अगर

/*
 * If we करोn't support core dumping, then supply a शून्य so we
 * करोn't even try.
 */
#अगर_घोषित CONFIG_ELF_CORE
अटल पूर्णांक elf_core_dump(काष्ठा coredump_params *cprm);
#अन्यथा
#घोषणा elf_core_dump	शून्य
#पूर्ण_अगर

#अगर ELF_EXEC_PAGESIZE > PAGE_SIZE
#घोषणा ELF_MIN_ALIGN	ELF_EXEC_PAGESIZE
#अन्यथा
#घोषणा ELF_MIN_ALIGN	PAGE_SIZE
#पूर्ण_अगर

#अगर_अघोषित ELF_CORE_EFLAGS
#घोषणा ELF_CORE_EFLAGS	0
#पूर्ण_अगर

#घोषणा ELF_PAGESTART(_v) ((_v) & ~(अचिन्हित दीर्घ)(ELF_MIN_ALIGN-1))
#घोषणा ELF_PAGखातापूर्णFSET(_v) ((_v) & (ELF_MIN_ALIGN-1))
#घोषणा ELF_PAGEALIGN(_v) (((_v) + ELF_MIN_ALIGN - 1) & ~(ELF_MIN_ALIGN - 1))

अटल काष्ठा linux_binfmt elf_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_elf_binary,
	.load_shlib	= load_elf_library,
	.core_dump	= elf_core_dump,
	.min_coredump	= ELF_EXEC_PAGESIZE,
पूर्ण;

#घोषणा BAD_ADDR(x) (unlikely((अचिन्हित दीर्घ)(x) >= TASK_SIZE))

अटल पूर्णांक set_brk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक prot)
अणु
	start = ELF_PAGEALIGN(start);
	end = ELF_PAGEALIGN(end);
	अगर (end > start) अणु
		/*
		 * Map the last of the bss segment.
		 * If the header is requesting these pages to be
		 * executable, honour that (ppc32 needs this).
		 */
		पूर्णांक error = vm_brk_flags(start, end - start,
				prot & PROT_EXEC ? VM_EXEC : 0);
		अगर (error)
			वापस error;
	पूर्ण
	current->mm->start_brk = current->mm->brk = end;
	वापस 0;
पूर्ण

/* We need to explicitly zero any fractional pages
   after the data section (i.e. bss).  This would
   contain the junk from the file that should not
   be in memory
 */
अटल पूर्णांक padzero(अचिन्हित दीर्घ elf_bss)
अणु
	अचिन्हित दीर्घ nbyte;

	nbyte = ELF_PAGखातापूर्णFSET(elf_bss);
	अगर (nbyte) अणु
		nbyte = ELF_MIN_ALIGN - nbyte;
		अगर (clear_user((व्योम __user *) elf_bss, nbyte))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

/* Let's use some macros to make this stack manipulation a little clearer */
#अगर_घोषित CONFIG_STACK_GROWSUP
#घोषणा STACK_ADD(sp, items) ((elf_addr_t __user *)(sp) + (items))
#घोषणा STACK_ROUND(sp, items) \
	((15 + (अचिन्हित दीर्घ) ((sp) + (items))) &~ 15UL)
#घोषणा STACK_ALLOC(sp, len) (अणु \
	elf_addr_t __user *old_sp = (elf_addr_t __user *)sp; sp += len; \
	old_sp; पूर्ण)
#अन्यथा
#घोषणा STACK_ADD(sp, items) ((elf_addr_t __user *)(sp) - (items))
#घोषणा STACK_ROUND(sp, items) \
	(((अचिन्हित दीर्घ) (sp - items)) &~ 15UL)
#घोषणा STACK_ALLOC(sp, len) (अणु sp -= len ; sp; पूर्ण)
#पूर्ण_अगर

#अगर_अघोषित ELF_BASE_PLATFORM
/*
 * AT_BASE_PLATFORM indicates the "real" hardware/microarchitecture.
 * If the arch defines ELF_BASE_PLATFORM (in यंत्र/elf.h), the value
 * will be copied to the user stack in the same manner as AT_PLATFORM.
 */
#घोषणा ELF_BASE_PLATFORM शून्य
#पूर्ण_अगर

अटल पूर्णांक
create_elf_tables(काष्ठा linux_binprm *bprm, स्थिर काष्ठा elfhdr *exec,
		अचिन्हित दीर्घ load_addr, अचिन्हित दीर्घ पूर्णांकerp_load_addr,
		अचिन्हित दीर्घ e_entry)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ p = bprm->p;
	पूर्णांक argc = bprm->argc;
	पूर्णांक envc = bprm->envc;
	elf_addr_t __user *sp;
	elf_addr_t __user *u_platक्रमm;
	elf_addr_t __user *u_base_platक्रमm;
	elf_addr_t __user *u_अक्रम_bytes;
	स्थिर अक्षर *k_platक्रमm = ELF_PLATFORM;
	स्थिर अक्षर *k_base_platक्रमm = ELF_BASE_PLATFORM;
	अचिन्हित अक्षर k_अक्रम_bytes[16];
	पूर्णांक items;
	elf_addr_t *elf_info;
	elf_addr_t flags = 0;
	पूर्णांक ei_index;
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * In some हालs (e.g. Hyper-Thपढ़ोing), we want to aव्योम L1
	 * evictions by the processes running on the same package. One
	 * thing we can करो is to shuffle the initial stack क्रम them.
	 */

	p = arch_align_stack(p);

	/*
	 * If this architecture has a platक्रमm capability string, copy it
	 * to userspace.  In some हालs (Sparc), this info is impossible
	 * क्रम userspace to get any other way, in others (i386) it is
	 * merely dअगरficult.
	 */
	u_platक्रमm = शून्य;
	अगर (k_platक्रमm) अणु
		माप_प्रकार len = म_माप(k_platक्रमm) + 1;

		u_platक्रमm = (elf_addr_t __user *)STACK_ALLOC(p, len);
		अगर (copy_to_user(u_platक्रमm, k_platक्रमm, len))
			वापस -EFAULT;
	पूर्ण

	/*
	 * If this architecture has a "base" platक्रमm capability
	 * string, copy it to userspace.
	 */
	u_base_platक्रमm = शून्य;
	अगर (k_base_platक्रमm) अणु
		माप_प्रकार len = म_माप(k_base_platक्रमm) + 1;

		u_base_platक्रमm = (elf_addr_t __user *)STACK_ALLOC(p, len);
		अगर (copy_to_user(u_base_platक्रमm, k_base_platक्रमm, len))
			वापस -EFAULT;
	पूर्ण

	/*
	 * Generate 16 अक्रमom bytes क्रम userspace PRNG seeding.
	 */
	get_अक्रमom_bytes(k_अक्रम_bytes, माप(k_अक्रम_bytes));
	u_अक्रम_bytes = (elf_addr_t __user *)
		       STACK_ALLOC(p, माप(k_अक्रम_bytes));
	अगर (copy_to_user(u_अक्रम_bytes, k_अक्रम_bytes, माप(k_अक्रम_bytes)))
		वापस -EFAULT;

	/* Create the ELF पूर्णांकerpreter info */
	elf_info = (elf_addr_t *)mm->saved_auxv;
	/* update AT_VECTOR_SIZE_BASE अगर the number of NEW_AUX_ENT() changes */
#घोषणा NEW_AUX_ENT(id, val) \
	करो अणु \
		*elf_info++ = id; \
		*elf_info++ = val; \
	पूर्ण जबतक (0)

#अगर_घोषित ARCH_DLINFO
	/* 
	 * ARCH_DLINFO must come first so PPC can करो its special alignment of
	 * AUXV.
	 * update AT_VECTOR_SIZE_ARCH अगर the number of NEW_AUX_ENT() in
	 * ARCH_DLINFO changes
	 */
	ARCH_DLINFO;
#पूर्ण_अगर
	NEW_AUX_ENT(AT_HWCAP, ELF_HWCAP);
	NEW_AUX_ENT(AT_PAGESZ, ELF_EXEC_PAGESIZE);
	NEW_AUX_ENT(AT_CLKTCK, CLOCKS_PER_SEC);
	NEW_AUX_ENT(AT_PHDR, load_addr + exec->e_phoff);
	NEW_AUX_ENT(AT_PHENT, माप(काष्ठा elf_phdr));
	NEW_AUX_ENT(AT_PHNUM, exec->e_phnum);
	NEW_AUX_ENT(AT_BASE, पूर्णांकerp_load_addr);
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_PRESERVE_ARGV0)
		flags |= AT_FLAGS_PRESERVE_ARGV0;
	NEW_AUX_ENT(AT_FLAGS, flags);
	NEW_AUX_ENT(AT_ENTRY, e_entry);
	NEW_AUX_ENT(AT_UID, from_kuid_munged(cred->user_ns, cred->uid));
	NEW_AUX_ENT(AT_EUID, from_kuid_munged(cred->user_ns, cred->euid));
	NEW_AUX_ENT(AT_GID, from_kgid_munged(cred->user_ns, cred->gid));
	NEW_AUX_ENT(AT_EGID, from_kgid_munged(cred->user_ns, cred->egid));
	NEW_AUX_ENT(AT_SECURE, bprm->secureexec);
	NEW_AUX_ENT(AT_RANDOM, (elf_addr_t)(अचिन्हित दीर्घ)u_अक्रम_bytes);
#अगर_घोषित ELF_HWCAP2
	NEW_AUX_ENT(AT_HWCAP2, ELF_HWCAP2);
#पूर्ण_अगर
	NEW_AUX_ENT(AT_EXECFN, bprm->exec);
	अगर (k_platक्रमm) अणु
		NEW_AUX_ENT(AT_PLATFORM,
			    (elf_addr_t)(अचिन्हित दीर्घ)u_platक्रमm);
	पूर्ण
	अगर (k_base_platक्रमm) अणु
		NEW_AUX_ENT(AT_BASE_PLATFORM,
			    (elf_addr_t)(अचिन्हित दीर्घ)u_base_platक्रमm);
	पूर्ण
	अगर (bprm->have_execfd) अणु
		NEW_AUX_ENT(AT_EXECFD, bprm->execfd);
	पूर्ण
#अघोषित NEW_AUX_ENT
	/* AT_शून्य is zero; clear the rest too */
	स_रखो(elf_info, 0, (अक्षर *)mm->saved_auxv +
			माप(mm->saved_auxv) - (अक्षर *)elf_info);

	/* And advance past the AT_शून्य entry.  */
	elf_info += 2;

	ei_index = elf_info - (elf_addr_t *)mm->saved_auxv;
	sp = STACK_ADD(p, ei_index);

	items = (argc + 1) + (envc + 1) + 1;
	bprm->p = STACK_ROUND(sp, items);

	/* Poपूर्णांक sp at the lowest address on the stack */
#अगर_घोषित CONFIG_STACK_GROWSUP
	sp = (elf_addr_t __user *)bprm->p - items - ei_index;
	bprm->exec = (अचिन्हित दीर्घ)sp; /* XXX: PARISC HACK */
#अन्यथा
	sp = (elf_addr_t __user *)bprm->p;
#पूर्ण_अगर


	/*
	 * Grow the stack manually; some architectures have a limit on how
	 * far ahead a user-space access may be in order to grow the stack.
	 */
	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		वापस -EINTR;
	vma = find_extend_vma(mm, bprm->p);
	mmap_पढ़ो_unlock(mm);
	अगर (!vma)
		वापस -EFAULT;

	/* Now, let's put argc (and argv, envp अगर appropriate) on the stack */
	अगर (put_user(argc, sp++))
		वापस -EFAULT;

	/* Populate list of argv poपूर्णांकers back to argv strings. */
	p = mm->arg_end = mm->arg_start;
	जबतक (argc-- > 0) अणु
		माप_प्रकार len;
		अगर (put_user((elf_addr_t)p, sp++))
			वापस -EFAULT;
		len = strnlen_user((व्योम __user *)p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(0, sp++))
		वापस -EFAULT;
	mm->arg_end = p;

	/* Populate list of envp poपूर्णांकers back to envp strings. */
	mm->env_end = mm->env_start = p;
	जबतक (envc-- > 0) अणु
		माप_प्रकार len;
		अगर (put_user((elf_addr_t)p, sp++))
			वापस -EFAULT;
		len = strnlen_user((व्योम __user *)p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(0, sp++))
		वापस -EFAULT;
	mm->env_end = p;

	/* Put the elf_info on the stack in the right place.  */
	अगर (copy_to_user(sp, mm->saved_auxv, ei_index * माप(elf_addr_t)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ elf_map(काष्ठा file *filep, अचिन्हित दीर्घ addr,
		स्थिर काष्ठा elf_phdr *eppnt, पूर्णांक prot, पूर्णांक type,
		अचिन्हित दीर्घ total_size)
अणु
	अचिन्हित दीर्घ map_addr;
	अचिन्हित दीर्घ size = eppnt->p_filesz + ELF_PAGखातापूर्णFSET(eppnt->p_vaddr);
	अचिन्हित दीर्घ off = eppnt->p_offset - ELF_PAGखातापूर्णFSET(eppnt->p_vaddr);
	addr = ELF_PAGESTART(addr);
	size = ELF_PAGEALIGN(size);

	/* mmap() will वापस -EINVAL अगर given a zero size, but a
	 * segment with zero filesize is perfectly valid */
	अगर (!size)
		वापस addr;

	/*
	* total_size is the size of the ELF (पूर्णांकerpreter) image.
	* The _first_ mmap needs to know the full size, otherwise
	* अक्रमomization might put this image पूर्णांकo an overlapping
	* position with the ELF binary image. (since size < total_size)
	* So we first map the 'big' image - and unmap the reमुख्यder at
	* the end. (which unmap is needed क्रम ELF images with holes.)
	*/
	अगर (total_size) अणु
		total_size = ELF_PAGEALIGN(total_size);
		map_addr = vm_mmap(filep, addr, total_size, prot, type, off);
		अगर (!BAD_ADDR(map_addr))
			vm_munmap(map_addr+size, total_size-size);
	पूर्ण अन्यथा
		map_addr = vm_mmap(filep, addr, size, prot, type, off);

	अगर ((type & MAP_FIXED_NOREPLACE) &&
	    PTR_ERR((व्योम *)map_addr) == -EEXIST)
		pr_info("%d (%s): Uhuuh, elf segment at %px requested but the memory is mapped already\n",
			task_pid_nr(current), current->comm, (व्योम *)addr);

	वापस(map_addr);
पूर्ण

अटल अचिन्हित दीर्घ total_mapping_size(स्थिर काष्ठा elf_phdr *cmds, पूर्णांक nr)
अणु
	पूर्णांक i, first_idx = -1, last_idx = -1;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (cmds[i].p_type == PT_LOAD) अणु
			last_idx = i;
			अगर (first_idx == -1)
				first_idx = i;
		पूर्ण
	पूर्ण
	अगर (first_idx == -1)
		वापस 0;

	वापस cmds[last_idx].p_vaddr + cmds[last_idx].p_memsz -
				ELF_PAGESTART(cmds[first_idx].p_vaddr);
पूर्ण

अटल पूर्णांक elf_पढ़ो(काष्ठा file *file, व्योम *buf, माप_प्रकार len, loff_t pos)
अणु
	sमाप_प्रकार rv;

	rv = kernel_पढ़ो(file, buf, len, &pos);
	अगर (unlikely(rv != len)) अणु
		वापस (rv < 0) ? rv : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ maximum_alignment(काष्ठा elf_phdr *cmds, पूर्णांक nr)
अणु
	अचिन्हित दीर्घ alignment = 0;
	पूर्णांक i;

	क्रम (i = 0; i < nr; i++) अणु
		अगर (cmds[i].p_type == PT_LOAD) अणु
			अचिन्हित दीर्घ p_align = cmds[i].p_align;

			/* skip non-घातer of two alignments as invalid */
			अगर (!is_घातer_of_2(p_align))
				जारी;
			alignment = max(alignment, p_align);
		पूर्ण
	पूर्ण

	/* ensure we align to at least one page */
	वापस ELF_PAGEALIGN(alignment);
पूर्ण

/**
 * load_elf_phdrs() - load ELF program headers
 * @elf_ex:   ELF header of the binary whose program headers should be loaded
 * @elf_file: the खोलोed ELF binary file
 *
 * Loads ELF program headers from the binary file elf_file, which has the ELF
 * header poपूर्णांकed to by elf_ex, पूर्णांकo a newly allocated array. The caller is
 * responsible क्रम मुक्तing the allocated data. Returns an ERR_PTR upon failure.
 */
अटल काष्ठा elf_phdr *load_elf_phdrs(स्थिर काष्ठा elfhdr *elf_ex,
				       काष्ठा file *elf_file)
अणु
	काष्ठा elf_phdr *elf_phdata = शून्य;
	पूर्णांक retval, err = -1;
	अचिन्हित पूर्णांक size;

	/*
	 * If the size of this काष्ठाure has changed, then punt, since
	 * we will be करोing the wrong thing.
	 */
	अगर (elf_ex->e_phentsize != माप(काष्ठा elf_phdr))
		जाओ out;

	/* Sanity check the number of program headers... */
	/* ...and their total size. */
	size = माप(काष्ठा elf_phdr) * elf_ex->e_phnum;
	अगर (size == 0 || size > 65536 || size > ELF_MIN_ALIGN)
		जाओ out;

	elf_phdata = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!elf_phdata)
		जाओ out;

	/* Read in the program headers */
	retval = elf_पढ़ो(elf_file, elf_phdata, size, elf_ex->e_phoff);
	अगर (retval < 0) अणु
		err = retval;
		जाओ out;
	पूर्ण

	/* Success! */
	err = 0;
out:
	अगर (err) अणु
		kमुक्त(elf_phdata);
		elf_phdata = शून्य;
	पूर्ण
	वापस elf_phdata;
पूर्ण

#अगर_अघोषित CONFIG_ARCH_BINFMT_ELF_STATE

/**
 * काष्ठा arch_elf_state - arch-specअगरic ELF loading state
 *
 * This काष्ठाure is used to preserve architecture specअगरic data during
 * the loading of an ELF file, throughout the checking of architecture
 * specअगरic ELF headers & through to the poपूर्णांक where the ELF load is
 * known to be proceeding (ie. SET_PERSONALITY).
 *
 * This implementation is a dummy क्रम architectures which require no
 * specअगरic state.
 */
काष्ठा arch_elf_state अणु
पूर्ण;

#घोषणा INIT_ARCH_ELF_STATE अणुपूर्ण

/**
 * arch_elf_pt_proc() - check a PT_LOPROC..PT_HIPROC ELF program header
 * @ehdr:	The मुख्य ELF header
 * @phdr:	The program header to check
 * @elf:	The खोलो ELF file
 * @is_पूर्णांकerp:	True अगर the phdr is from the पूर्णांकerpreter of the ELF being
 *		loaded, अन्यथा false.
 * @state:	Architecture-specअगरic state preserved throughout the process
 *		of loading the ELF.
 *
 * Inspects the program header phdr to validate its correctness and/or
 * suitability क्रम the प्रणाली. Called once per ELF program header in the
 * range PT_LOPROC to PT_HIPROC, क्रम both the ELF being loaded and its
 * पूर्णांकerpreter.
 *
 * Return: Zero to proceed with the ELF load, non-zero to fail the ELF load
 *         with that वापस code.
 */
अटल अंतरभूत पूर्णांक arch_elf_pt_proc(काष्ठा elfhdr *ehdr,
				   काष्ठा elf_phdr *phdr,
				   काष्ठा file *elf, bool is_पूर्णांकerp,
				   काष्ठा arch_elf_state *state)
अणु
	/* Dummy implementation, always proceed */
	वापस 0;
पूर्ण

/**
 * arch_check_elf() - check an ELF executable
 * @ehdr:	The मुख्य ELF header
 * @has_पूर्णांकerp:	True अगर the ELF has an पूर्णांकerpreter, अन्यथा false.
 * @पूर्णांकerp_ehdr: The पूर्णांकerpreter's ELF header
 * @state:	Architecture-specअगरic state preserved throughout the process
 *		of loading the ELF.
 *
 * Provides a final opportunity क्रम architecture code to reject the loading
 * of the ELF & cause an exec syscall to वापस an error. This is called after
 * all program headers to be checked by arch_elf_pt_proc have been.
 *
 * Return: Zero to proceed with the ELF load, non-zero to fail the ELF load
 *         with that वापस code.
 */
अटल अंतरभूत पूर्णांक arch_check_elf(काष्ठा elfhdr *ehdr, bool has_पूर्णांकerp,
				 काष्ठा elfhdr *पूर्णांकerp_ehdr,
				 काष्ठा arch_elf_state *state)
अणु
	/* Dummy implementation, always proceed */
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_ARCH_BINFMT_ELF_STATE */

अटल अंतरभूत पूर्णांक make_prot(u32 p_flags, काष्ठा arch_elf_state *arch_state,
			    bool has_पूर्णांकerp, bool is_पूर्णांकerp)
अणु
	पूर्णांक prot = 0;

	अगर (p_flags & PF_R)
		prot |= PROT_READ;
	अगर (p_flags & PF_W)
		prot |= PROT_WRITE;
	अगर (p_flags & PF_X)
		prot |= PROT_EXEC;

	वापस arch_elf_adjust_prot(prot, arch_state, has_पूर्णांकerp, is_पूर्णांकerp);
पूर्ण

/* This is much more generalized than the library routine पढ़ो function,
   so we keep this separate.  Technically the library पढ़ो function
   is only provided so that we can पढ़ो a.out libraries that have
   an ELF header */

अटल अचिन्हित दीर्घ load_elf_पूर्णांकerp(काष्ठा elfhdr *पूर्णांकerp_elf_ex,
		काष्ठा file *पूर्णांकerpreter,
		अचिन्हित दीर्घ no_base, काष्ठा elf_phdr *पूर्णांकerp_elf_phdata,
		काष्ठा arch_elf_state *arch_state)
अणु
	काष्ठा elf_phdr *eppnt;
	अचिन्हित दीर्घ load_addr = 0;
	पूर्णांक load_addr_set = 0;
	अचिन्हित दीर्घ last_bss = 0, elf_bss = 0;
	पूर्णांक bss_prot = 0;
	अचिन्हित दीर्घ error = ~0UL;
	अचिन्हित दीर्घ total_size;
	पूर्णांक i;

	/* First of all, some simple consistency checks */
	अगर (पूर्णांकerp_elf_ex->e_type != ET_EXEC &&
	    पूर्णांकerp_elf_ex->e_type != ET_DYN)
		जाओ out;
	अगर (!elf_check_arch(पूर्णांकerp_elf_ex) ||
	    elf_check_fdpic(पूर्णांकerp_elf_ex))
		जाओ out;
	अगर (!पूर्णांकerpreter->f_op->mmap)
		जाओ out;

	total_size = total_mapping_size(पूर्णांकerp_elf_phdata,
					पूर्णांकerp_elf_ex->e_phnum);
	अगर (!total_size) अणु
		error = -EINVAL;
		जाओ out;
	पूर्ण

	eppnt = पूर्णांकerp_elf_phdata;
	क्रम (i = 0; i < पूर्णांकerp_elf_ex->e_phnum; i++, eppnt++) अणु
		अगर (eppnt->p_type == PT_LOAD) अणु
			पूर्णांक elf_type = MAP_PRIVATE | MAP_DENYWRITE;
			पूर्णांक elf_prot = make_prot(eppnt->p_flags, arch_state,
						 true, true);
			अचिन्हित दीर्घ vaddr = 0;
			अचिन्हित दीर्घ k, map_addr;

			vaddr = eppnt->p_vaddr;
			अगर (पूर्णांकerp_elf_ex->e_type == ET_EXEC || load_addr_set)
				elf_type |= MAP_FIXED_NOREPLACE;
			अन्यथा अगर (no_base && पूर्णांकerp_elf_ex->e_type == ET_DYN)
				load_addr = -vaddr;

			map_addr = elf_map(पूर्णांकerpreter, load_addr + vaddr,
					eppnt, elf_prot, elf_type, total_size);
			total_size = 0;
			error = map_addr;
			अगर (BAD_ADDR(map_addr))
				जाओ out;

			अगर (!load_addr_set &&
			    पूर्णांकerp_elf_ex->e_type == ET_DYN) अणु
				load_addr = map_addr - ELF_PAGESTART(vaddr);
				load_addr_set = 1;
			पूर्ण

			/*
			 * Check to see अगर the section's size will overflow the
			 * allowed task size. Note that p_filesz must always be
			 * <= p_memsize so it's only necessary to check p_memsz.
			 */
			k = load_addr + eppnt->p_vaddr;
			अगर (BAD_ADDR(k) ||
			    eppnt->p_filesz > eppnt->p_memsz ||
			    eppnt->p_memsz > TASK_SIZE ||
			    TASK_SIZE - eppnt->p_memsz < k) अणु
				error = -ENOMEM;
				जाओ out;
			पूर्ण

			/*
			 * Find the end of the file mapping क्रम this phdr, and
			 * keep track of the largest address we see क्रम this.
			 */
			k = load_addr + eppnt->p_vaddr + eppnt->p_filesz;
			अगर (k > elf_bss)
				elf_bss = k;

			/*
			 * Do the same thing क्रम the memory mapping - between
			 * elf_bss and last_bss is the bss section.
			 */
			k = load_addr + eppnt->p_vaddr + eppnt->p_memsz;
			अगर (k > last_bss) अणु
				last_bss = k;
				bss_prot = elf_prot;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Now fill out the bss section: first pad the last page from
	 * the file up to the page boundary, and zero it from elf_bss
	 * up to the end of the page.
	 */
	अगर (padzero(elf_bss)) अणु
		error = -EFAULT;
		जाओ out;
	पूर्ण
	/*
	 * Next, align both the file and mem bss up to the page size,
	 * since this is where elf_bss was just zeroed up to, and where
	 * last_bss will end after the vm_brk_flags() below.
	 */
	elf_bss = ELF_PAGEALIGN(elf_bss);
	last_bss = ELF_PAGEALIGN(last_bss);
	/* Finally, अगर there is still more bss to allocate, करो it. */
	अगर (last_bss > elf_bss) अणु
		error = vm_brk_flags(elf_bss, last_bss - elf_bss,
				bss_prot & PROT_EXEC ? VM_EXEC : 0);
		अगर (error)
			जाओ out;
	पूर्ण

	error = load_addr;
out:
	वापस error;
पूर्ण

/*
 * These are the functions used to load ELF style executables and shared
 * libraries.  There is no binary dependent code anywhere अन्यथा.
 */

अटल पूर्णांक parse_elf_property(स्थिर अक्षर *data, माप_प्रकार *off, माप_प्रकार datasz,
			      काष्ठा arch_elf_state *arch,
			      bool have_prev_type, u32 *prev_type)
अणु
	माप_प्रकार o, step;
	स्थिर काष्ठा gnu_property *pr;
	पूर्णांक ret;

	अगर (*off == datasz)
		वापस -ENOENT;

	अगर (WARN_ON_ONCE(*off > datasz || *off % ELF_GNU_PROPERTY_ALIGN))
		वापस -EIO;
	o = *off;
	datasz -= *off;

	अगर (datasz < माप(*pr))
		वापस -ENOEXEC;
	pr = (स्थिर काष्ठा gnu_property *)(data + o);
	o += माप(*pr);
	datasz -= माप(*pr);

	अगर (pr->pr_datasz > datasz)
		वापस -ENOEXEC;

	WARN_ON_ONCE(o % ELF_GNU_PROPERTY_ALIGN);
	step = round_up(pr->pr_datasz, ELF_GNU_PROPERTY_ALIGN);
	अगर (step > datasz)
		वापस -ENOEXEC;

	/* Properties are supposed to be unique and sorted on pr_type: */
	अगर (have_prev_type && pr->pr_type <= *prev_type)
		वापस -ENOEXEC;
	*prev_type = pr->pr_type;

	ret = arch_parse_elf_property(pr->pr_type, data + o,
				      pr->pr_datasz, ELF_COMPAT, arch);
	अगर (ret)
		वापस ret;

	*off = o + step;
	वापस 0;
पूर्ण

#घोषणा NOTE_DATA_SZ SZ_1K
#घोषणा GNU_PROPERTY_TYPE_0_NAME "GNU"
#घोषणा NOTE_NAME_SZ (माप(GNU_PROPERTY_TYPE_0_NAME))

अटल पूर्णांक parse_elf_properties(काष्ठा file *f, स्थिर काष्ठा elf_phdr *phdr,
				काष्ठा arch_elf_state *arch)
अणु
	जोड़ अणु
		काष्ठा elf_note nhdr;
		अक्षर data[NOTE_DATA_SZ];
	पूर्ण note;
	loff_t pos;
	sमाप_प्रकार n;
	माप_प्रकार off, datasz;
	पूर्णांक ret;
	bool have_prev_type;
	u32 prev_type;

	अगर (!IS_ENABLED(CONFIG_ARCH_USE_GNU_PROPERTY) || !phdr)
		वापस 0;

	/* load_elf_binary() shouldn't call us unless this is true... */
	अगर (WARN_ON_ONCE(phdr->p_type != PT_GNU_PROPERTY))
		वापस -ENOEXEC;

	/* If the properties are crazy large, that's too bad (क्रम now): */
	अगर (phdr->p_filesz > माप(note))
		वापस -ENOEXEC;

	pos = phdr->p_offset;
	n = kernel_पढ़ो(f, &note, phdr->p_filesz, &pos);

	BUILD_BUG_ON(माप(note) < माप(note.nhdr) + NOTE_NAME_SZ);
	अगर (n < 0 || n < माप(note.nhdr) + NOTE_NAME_SZ)
		वापस -EIO;

	अगर (note.nhdr.n_type != NT_GNU_PROPERTY_TYPE_0 ||
	    note.nhdr.n_namesz != NOTE_NAME_SZ ||
	    म_भेदन(note.data + माप(note.nhdr),
		    GNU_PROPERTY_TYPE_0_NAME, n - माप(note.nhdr)))
		वापस -ENOEXEC;

	off = round_up(माप(note.nhdr) + NOTE_NAME_SZ,
		       ELF_GNU_PROPERTY_ALIGN);
	अगर (off > n)
		वापस -ENOEXEC;

	अगर (note.nhdr.n_descsz > n - off)
		वापस -ENOEXEC;
	datasz = off + note.nhdr.n_descsz;

	have_prev_type = false;
	करो अणु
		ret = parse_elf_property(note.data, &off, datasz, arch,
					 have_prev_type, &prev_type);
		have_prev_type = true;
	पूर्ण जबतक (!ret);

	वापस ret == -ENOENT ? 0 : ret;
पूर्ण

अटल पूर्णांक load_elf_binary(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा file *पूर्णांकerpreter = शून्य; /* to shut gcc up */
 	अचिन्हित दीर्घ load_addr = 0, load_bias = 0;
	पूर्णांक load_addr_set = 0;
	अचिन्हित दीर्घ error;
	काष्ठा elf_phdr *elf_ppnt, *elf_phdata, *पूर्णांकerp_elf_phdata = शून्य;
	काष्ठा elf_phdr *elf_property_phdata = शून्य;
	अचिन्हित दीर्घ elf_bss, elf_brk;
	पूर्णांक bss_prot = 0;
	पूर्णांक retval, i;
	अचिन्हित दीर्घ elf_entry;
	अचिन्हित दीर्घ e_entry;
	अचिन्हित दीर्घ पूर्णांकerp_load_addr = 0;
	अचिन्हित दीर्घ start_code, end_code, start_data, end_data;
	अचिन्हित दीर्घ reloc_func_desc __maybe_unused = 0;
	पूर्णांक executable_stack = EXSTACK_DEFAULT;
	काष्ठा elfhdr *elf_ex = (काष्ठा elfhdr *)bprm->buf;
	काष्ठा elfhdr *पूर्णांकerp_elf_ex = शून्य;
	काष्ठा arch_elf_state arch_state = INIT_ARCH_ELF_STATE;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा pt_regs *regs;

	retval = -ENOEXEC;
	/* First of all, some simple consistency checks */
	अगर (स_भेद(elf_ex->e_ident, ELFMAG, SELFMAG) != 0)
		जाओ out;

	अगर (elf_ex->e_type != ET_EXEC && elf_ex->e_type != ET_DYN)
		जाओ out;
	अगर (!elf_check_arch(elf_ex))
		जाओ out;
	अगर (elf_check_fdpic(elf_ex))
		जाओ out;
	अगर (!bprm->file->f_op->mmap)
		जाओ out;

	elf_phdata = load_elf_phdrs(elf_ex, bprm->file);
	अगर (!elf_phdata)
		जाओ out;

	elf_ppnt = elf_phdata;
	क्रम (i = 0; i < elf_ex->e_phnum; i++, elf_ppnt++) अणु
		अक्षर *elf_पूर्णांकerpreter;

		अगर (elf_ppnt->p_type == PT_GNU_PROPERTY) अणु
			elf_property_phdata = elf_ppnt;
			जारी;
		पूर्ण

		अगर (elf_ppnt->p_type != PT_INTERP)
			जारी;

		/*
		 * This is the program पूर्णांकerpreter used क्रम shared libraries -
		 * क्रम now assume that this is an a.out क्रमmat binary.
		 */
		retval = -ENOEXEC;
		अगर (elf_ppnt->p_filesz > PATH_MAX || elf_ppnt->p_filesz < 2)
			जाओ out_मुक्त_ph;

		retval = -ENOMEM;
		elf_पूर्णांकerpreter = kदो_स्मृति(elf_ppnt->p_filesz, GFP_KERNEL);
		अगर (!elf_पूर्णांकerpreter)
			जाओ out_मुक्त_ph;

		retval = elf_पढ़ो(bprm->file, elf_पूर्णांकerpreter, elf_ppnt->p_filesz,
				  elf_ppnt->p_offset);
		अगर (retval < 0)
			जाओ out_मुक्त_पूर्णांकerp;
		/* make sure path is शून्य terminated */
		retval = -ENOEXEC;
		अगर (elf_पूर्णांकerpreter[elf_ppnt->p_filesz - 1] != '\0')
			जाओ out_मुक्त_पूर्णांकerp;

		पूर्णांकerpreter = खोलो_exec(elf_पूर्णांकerpreter);
		kमुक्त(elf_पूर्णांकerpreter);
		retval = PTR_ERR(पूर्णांकerpreter);
		अगर (IS_ERR(पूर्णांकerpreter))
			जाओ out_मुक्त_ph;

		/*
		 * If the binary is not पढ़ोable then enक्रमce mm->dumpable = 0
		 * regardless of the पूर्णांकerpreter's permissions.
		 */
		would_dump(bprm, पूर्णांकerpreter);

		पूर्णांकerp_elf_ex = kदो_स्मृति(माप(*पूर्णांकerp_elf_ex), GFP_KERNEL);
		अगर (!पूर्णांकerp_elf_ex) अणु
			retval = -ENOMEM;
			जाओ out_मुक्त_ph;
		पूर्ण

		/* Get the exec headers */
		retval = elf_पढ़ो(पूर्णांकerpreter, पूर्णांकerp_elf_ex,
				  माप(*पूर्णांकerp_elf_ex), 0);
		अगर (retval < 0)
			जाओ out_मुक्त_dentry;

		अवरोध;

out_मुक्त_पूर्णांकerp:
		kमुक्त(elf_पूर्णांकerpreter);
		जाओ out_मुक्त_ph;
	पूर्ण

	elf_ppnt = elf_phdata;
	क्रम (i = 0; i < elf_ex->e_phnum; i++, elf_ppnt++)
		चयन (elf_ppnt->p_type) अणु
		हाल PT_GNU_STACK:
			अगर (elf_ppnt->p_flags & PF_X)
				executable_stack = EXSTACK_ENABLE_X;
			अन्यथा
				executable_stack = EXSTACK_DISABLE_X;
			अवरोध;

		हाल PT_LOPROC ... PT_HIPROC:
			retval = arch_elf_pt_proc(elf_ex, elf_ppnt,
						  bprm->file, false,
						  &arch_state);
			अगर (retval)
				जाओ out_मुक्त_dentry;
			अवरोध;
		पूर्ण

	/* Some simple consistency checks क्रम the पूर्णांकerpreter */
	अगर (पूर्णांकerpreter) अणु
		retval = -ELIBBAD;
		/* Not an ELF पूर्णांकerpreter */
		अगर (स_भेद(पूर्णांकerp_elf_ex->e_ident, ELFMAG, SELFMAG) != 0)
			जाओ out_मुक्त_dentry;
		/* Verअगरy the पूर्णांकerpreter has a valid arch */
		अगर (!elf_check_arch(पूर्णांकerp_elf_ex) ||
		    elf_check_fdpic(पूर्णांकerp_elf_ex))
			जाओ out_मुक्त_dentry;

		/* Load the पूर्णांकerpreter program headers */
		पूर्णांकerp_elf_phdata = load_elf_phdrs(पूर्णांकerp_elf_ex,
						   पूर्णांकerpreter);
		अगर (!पूर्णांकerp_elf_phdata)
			जाओ out_मुक्त_dentry;

		/* Pass PT_LOPROC..PT_HIPROC headers to arch code */
		elf_property_phdata = शून्य;
		elf_ppnt = पूर्णांकerp_elf_phdata;
		क्रम (i = 0; i < पूर्णांकerp_elf_ex->e_phnum; i++, elf_ppnt++)
			चयन (elf_ppnt->p_type) अणु
			हाल PT_GNU_PROPERTY:
				elf_property_phdata = elf_ppnt;
				अवरोध;

			हाल PT_LOPROC ... PT_HIPROC:
				retval = arch_elf_pt_proc(पूर्णांकerp_elf_ex,
							  elf_ppnt, पूर्णांकerpreter,
							  true, &arch_state);
				अगर (retval)
					जाओ out_मुक्त_dentry;
				अवरोध;
			पूर्ण
	पूर्ण

	retval = parse_elf_properties(पूर्णांकerpreter ?: bprm->file,
				      elf_property_phdata, &arch_state);
	अगर (retval)
		जाओ out_मुक्त_dentry;

	/*
	 * Allow arch code to reject the ELF at this poपूर्णांक, whilst it's
	 * still possible to वापस an error to the code that invoked
	 * the exec syscall.
	 */
	retval = arch_check_elf(elf_ex,
				!!पूर्णांकerpreter, पूर्णांकerp_elf_ex,
				&arch_state);
	अगर (retval)
		जाओ out_मुक्त_dentry;

	/* Flush all traces of the currently running executable */
	retval = begin_new_exec(bprm);
	अगर (retval)
		जाओ out_मुक्त_dentry;

	/* Do this immediately, since STACK_TOP as used in setup_arg_pages
	   may depend on the personality.  */
	SET_PERSONALITY2(*elf_ex, &arch_state);
	अगर (elf_पढ़ो_implies_exec(*elf_ex, executable_stack))
		current->personality |= READ_IMPLIES_EXEC;

	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		current->flags |= PF_RANDOMIZE;

	setup_new_exec(bprm);

	/* Do this so that we can load the पूर्णांकerpreter, अगर need be.  We will
	   change some of these later */
	retval = setup_arg_pages(bprm, अक्रमomize_stack_top(STACK_TOP),
				 executable_stack);
	अगर (retval < 0)
		जाओ out_मुक्त_dentry;
	
	elf_bss = 0;
	elf_brk = 0;

	start_code = ~0UL;
	end_code = 0;
	start_data = 0;
	end_data = 0;

	/* Now we करो a little grungy work by mmapping the ELF image पूर्णांकo
	   the correct location in memory. */
	क्रम(i = 0, elf_ppnt = elf_phdata;
	    i < elf_ex->e_phnum; i++, elf_ppnt++) अणु
		पूर्णांक elf_prot, elf_flags;
		अचिन्हित दीर्घ k, vaddr;
		अचिन्हित दीर्घ total_size = 0;
		अचिन्हित दीर्घ alignment;

		अगर (elf_ppnt->p_type != PT_LOAD)
			जारी;

		अगर (unlikely (elf_brk > elf_bss)) अणु
			अचिन्हित दीर्घ nbyte;
	            
			/* There was a PT_LOAD segment with p_memsz > p_filesz
			   beक्रमe this one. Map anonymous pages, अगर needed,
			   and clear the area.  */
			retval = set_brk(elf_bss + load_bias,
					 elf_brk + load_bias,
					 bss_prot);
			अगर (retval)
				जाओ out_मुक्त_dentry;
			nbyte = ELF_PAGखातापूर्णFSET(elf_bss);
			अगर (nbyte) अणु
				nbyte = ELF_MIN_ALIGN - nbyte;
				अगर (nbyte > elf_brk - elf_bss)
					nbyte = elf_brk - elf_bss;
				अगर (clear_user((व्योम __user *)elf_bss +
							load_bias, nbyte)) अणु
					/*
					 * This bss-zeroing can fail अगर the ELF
					 * file specअगरies odd protections. So
					 * we करोn't check the वापस value
					 */
				पूर्ण
			पूर्ण
		पूर्ण

		elf_prot = make_prot(elf_ppnt->p_flags, &arch_state,
				     !!पूर्णांकerpreter, false);

		elf_flags = MAP_PRIVATE | MAP_DENYWRITE | MAP_EXECUTABLE;

		vaddr = elf_ppnt->p_vaddr;
		/*
		 * If we are loading ET_EXEC or we have alपढ़ोy perक्रमmed
		 * the ET_DYN load_addr calculations, proceed normally.
		 */
		अगर (elf_ex->e_type == ET_EXEC || load_addr_set) अणु
			elf_flags |= MAP_FIXED;
		पूर्ण अन्यथा अगर (elf_ex->e_type == ET_DYN) अणु
			/*
			 * This logic is run once क्रम the first LOAD Program
			 * Header क्रम ET_DYN binaries to calculate the
			 * अक्रमomization (load_bias) क्रम all the LOAD
			 * Program Headers, and to calculate the entire
			 * size of the ELF mapping (total_size). (Note that
			 * load_addr_set is set to true later once the
			 * initial mapping is perक्रमmed.)
			 *
			 * There are effectively two types of ET_DYN
			 * binaries: programs (i.e. PIE: ET_DYN with INTERP)
			 * and loaders (ET_DYN without INTERP, since they
			 * _are_ the ELF पूर्णांकerpreter). The loaders must
			 * be loaded away from programs since the program
			 * may otherwise collide with the loader (especially
			 * क्रम ET_EXEC which करोes not have a अक्रमomized
			 * position). For example to handle invocations of
			 * "./ld.so someprog" to test out a new version of
			 * the loader, the subsequent program that the
			 * loader loads must aव्योम the loader itself, so
			 * they cannot share the same load range. Sufficient
			 * room क्रम the brk must be allocated with the
			 * loader as well, since brk must be available with
			 * the loader.
			 *
			 * Thereक्रमe, programs are loaded offset from
			 * ELF_ET_DYN_BASE and loaders are loaded पूर्णांकo the
			 * independently अक्रमomized mmap region (0 load_bias
			 * without MAP_FIXED).
			 */
			अगर (पूर्णांकerpreter) अणु
				load_bias = ELF_ET_DYN_BASE;
				अगर (current->flags & PF_RANDOMIZE)
					load_bias += arch_mmap_rnd();
				alignment = maximum_alignment(elf_phdata, elf_ex->e_phnum);
				अगर (alignment)
					load_bias &= ~(alignment - 1);
				elf_flags |= MAP_FIXED;
			पूर्ण अन्यथा
				load_bias = 0;

			/*
			 * Since load_bias is used क्रम all subsequent loading
			 * calculations, we must lower it by the first vaddr
			 * so that the reमुख्यing calculations based on the
			 * ELF vaddrs will be correctly offset. The result
			 * is then page aligned.
			 */
			load_bias = ELF_PAGESTART(load_bias - vaddr);

			total_size = total_mapping_size(elf_phdata,
							elf_ex->e_phnum);
			अगर (!total_size) अणु
				retval = -EINVAL;
				जाओ out_मुक्त_dentry;
			पूर्ण
		पूर्ण

		error = elf_map(bprm->file, load_bias + vaddr, elf_ppnt,
				elf_prot, elf_flags, total_size);
		अगर (BAD_ADDR(error)) अणु
			retval = IS_ERR((व्योम *)error) ?
				PTR_ERR((व्योम*)error) : -EINVAL;
			जाओ out_मुक्त_dentry;
		पूर्ण

		अगर (!load_addr_set) अणु
			load_addr_set = 1;
			load_addr = (elf_ppnt->p_vaddr - elf_ppnt->p_offset);
			अगर (elf_ex->e_type == ET_DYN) अणु
				load_bias += error -
				             ELF_PAGESTART(load_bias + vaddr);
				load_addr += load_bias;
				reloc_func_desc = load_bias;
			पूर्ण
		पूर्ण
		k = elf_ppnt->p_vaddr;
		अगर ((elf_ppnt->p_flags & PF_X) && k < start_code)
			start_code = k;
		अगर (start_data < k)
			start_data = k;

		/*
		 * Check to see अगर the section's size will overflow the
		 * allowed task size. Note that p_filesz must always be
		 * <= p_memsz so it is only necessary to check p_memsz.
		 */
		अगर (BAD_ADDR(k) || elf_ppnt->p_filesz > elf_ppnt->p_memsz ||
		    elf_ppnt->p_memsz > TASK_SIZE ||
		    TASK_SIZE - elf_ppnt->p_memsz < k) अणु
			/* set_brk can never work. Aव्योम overflows. */
			retval = -EINVAL;
			जाओ out_मुक्त_dentry;
		पूर्ण

		k = elf_ppnt->p_vaddr + elf_ppnt->p_filesz;

		अगर (k > elf_bss)
			elf_bss = k;
		अगर ((elf_ppnt->p_flags & PF_X) && end_code < k)
			end_code = k;
		अगर (end_data < k)
			end_data = k;
		k = elf_ppnt->p_vaddr + elf_ppnt->p_memsz;
		अगर (k > elf_brk) अणु
			bss_prot = elf_prot;
			elf_brk = k;
		पूर्ण
	पूर्ण

	e_entry = elf_ex->e_entry + load_bias;
	elf_bss += load_bias;
	elf_brk += load_bias;
	start_code += load_bias;
	end_code += load_bias;
	start_data += load_bias;
	end_data += load_bias;

	/* Calling set_brk effectively mmaps the pages that we need
	 * क्रम the bss and अवरोध sections.  We must करो this beक्रमe
	 * mapping in the पूर्णांकerpreter, to make sure it करोesn't wind
	 * up getting placed where the bss needs to go.
	 */
	retval = set_brk(elf_bss, elf_brk, bss_prot);
	अगर (retval)
		जाओ out_मुक्त_dentry;
	अगर (likely(elf_bss != elf_brk) && unlikely(padzero(elf_bss))) अणु
		retval = -EFAULT; /* Nobody माला_लो to see this, but.. */
		जाओ out_मुक्त_dentry;
	पूर्ण

	अगर (पूर्णांकerpreter) अणु
		elf_entry = load_elf_पूर्णांकerp(पूर्णांकerp_elf_ex,
					    पूर्णांकerpreter,
					    load_bias, पूर्णांकerp_elf_phdata,
					    &arch_state);
		अगर (!IS_ERR((व्योम *)elf_entry)) अणु
			/*
			 * load_elf_पूर्णांकerp() वापसs relocation
			 * adjusपंचांगent
			 */
			पूर्णांकerp_load_addr = elf_entry;
			elf_entry += पूर्णांकerp_elf_ex->e_entry;
		पूर्ण
		अगर (BAD_ADDR(elf_entry)) अणु
			retval = IS_ERR((व्योम *)elf_entry) ?
					(पूर्णांक)elf_entry : -EINVAL;
			जाओ out_मुक्त_dentry;
		पूर्ण
		reloc_func_desc = पूर्णांकerp_load_addr;

		allow_ग_लिखो_access(पूर्णांकerpreter);
		fput(पूर्णांकerpreter);

		kमुक्त(पूर्णांकerp_elf_ex);
		kमुक्त(पूर्णांकerp_elf_phdata);
	पूर्ण अन्यथा अणु
		elf_entry = e_entry;
		अगर (BAD_ADDR(elf_entry)) अणु
			retval = -EINVAL;
			जाओ out_मुक्त_dentry;
		पूर्ण
	पूर्ण

	kमुक्त(elf_phdata);

	set_binfmt(&elf_क्रमmat);

#अगर_घोषित ARCH_HAS_SETUP_ADDITIONAL_PAGES
	retval = ARCH_SETUP_ADDITIONAL_PAGES(bprm, elf_ex, !!पूर्णांकerpreter);
	अगर (retval < 0)
		जाओ out;
#पूर्ण_अगर /* ARCH_HAS_SETUP_ADDITIONAL_PAGES */

	retval = create_elf_tables(bprm, elf_ex,
			  load_addr, पूर्णांकerp_load_addr, e_entry);
	अगर (retval < 0)
		जाओ out;

	mm = current->mm;
	mm->end_code = end_code;
	mm->start_code = start_code;
	mm->start_data = start_data;
	mm->end_data = end_data;
	mm->start_stack = bprm->p;

	अगर ((current->flags & PF_RANDOMIZE) && (अक्रमomize_va_space > 1)) अणु
		/*
		 * For architectures with ELF अक्रमomization, when executing
		 * a loader directly (i.e. no पूर्णांकerpreter listed in ELF
		 * headers), move the brk area out of the mmap region
		 * (since it grows up, and may collide early with the stack
		 * growing करोwn), and पूर्णांकo the unused ELF_ET_DYN_BASE region.
		 */
		अगर (IS_ENABLED(CONFIG_ARCH_HAS_ELF_RANDOMIZE) &&
		    elf_ex->e_type == ET_DYN && !पूर्णांकerpreter) अणु
			mm->brk = mm->start_brk = ELF_ET_DYN_BASE;
		पूर्ण

		mm->brk = mm->start_brk = arch_अक्रमomize_brk(mm);
#अगर_घोषित compat_brk_अक्रमomized
		current->brk_अक्रमomized = 1;
#पूर्ण_अगर
	पूर्ण

	अगर (current->personality & MMAP_PAGE_ZERO) अणु
		/* Why this, you ask???  Well SVr4 maps page 0 as पढ़ो-only,
		   and some applications "depend" upon this behavior.
		   Since we करो not have the घातer to recompile these, we
		   emulate the SVr4 behavior. Sigh. */
		error = vm_mmap(शून्य, 0, PAGE_SIZE, PROT_READ | PROT_EXEC,
				MAP_FIXED | MAP_PRIVATE, 0);
	पूर्ण

	regs = current_pt_regs();
#अगर_घोषित ELF_PLAT_INIT
	/*
	 * The ABI may specअगरy that certain रेजिस्टरs be set up in special
	 * ways (on i386 %edx is the address of a DT_FINI function, क्रम
	 * example.  In addition, it may also specअगरy (eg, PowerPC64 ELF)
	 * that the e_entry field is the address of the function descriptor
	 * क्रम the startup routine, rather than the address of the startup
	 * routine itself.  This macro perक्रमms whatever initialization to
	 * the regs काष्ठाure is required as well as any relocations to the
	 * function descriptor entries when executing dynamically links apps.
	 */
	ELF_PLAT_INIT(regs, reloc_func_desc);
#पूर्ण_अगर

	finalize_exec(bprm);
	START_THREAD(elf_ex, regs, elf_entry, bprm->p);
	retval = 0;
out:
	वापस retval;

	/* error cleanup */
out_मुक्त_dentry:
	kमुक्त(पूर्णांकerp_elf_ex);
	kमुक्त(पूर्णांकerp_elf_phdata);
	allow_ग_लिखो_access(पूर्णांकerpreter);
	अगर (पूर्णांकerpreter)
		fput(पूर्णांकerpreter);
out_मुक्त_ph:
	kमुक्त(elf_phdata);
	जाओ out;
पूर्ण

#अगर_घोषित CONFIG_USELIB
/* This is really simpleminded and specialized - we are loading an
   a.out library that is given an ELF header. */
अटल पूर्णांक load_elf_library(काष्ठा file *file)
अणु
	काष्ठा elf_phdr *elf_phdata;
	काष्ठा elf_phdr *eppnt;
	अचिन्हित दीर्घ elf_bss, bss, len;
	पूर्णांक retval, error, i, j;
	काष्ठा elfhdr elf_ex;

	error = -ENOEXEC;
	retval = elf_पढ़ो(file, &elf_ex, माप(elf_ex), 0);
	अगर (retval < 0)
		जाओ out;

	अगर (स_भेद(elf_ex.e_ident, ELFMAG, SELFMAG) != 0)
		जाओ out;

	/* First of all, some simple consistency checks */
	अगर (elf_ex.e_type != ET_EXEC || elf_ex.e_phnum > 2 ||
	    !elf_check_arch(&elf_ex) || !file->f_op->mmap)
		जाओ out;
	अगर (elf_check_fdpic(&elf_ex))
		जाओ out;

	/* Now पढ़ो in all of the header inक्रमmation */

	j = माप(काष्ठा elf_phdr) * elf_ex.e_phnum;
	/* j < ELF_MIN_ALIGN because elf_ex.e_phnum <= 2 */

	error = -ENOMEM;
	elf_phdata = kदो_स्मृति(j, GFP_KERNEL);
	अगर (!elf_phdata)
		जाओ out;

	eppnt = elf_phdata;
	error = -ENOEXEC;
	retval = elf_पढ़ो(file, eppnt, j, elf_ex.e_phoff);
	अगर (retval < 0)
		जाओ out_मुक्त_ph;

	क्रम (j = 0, i = 0; i<elf_ex.e_phnum; i++)
		अगर ((eppnt + i)->p_type == PT_LOAD)
			j++;
	अगर (j != 1)
		जाओ out_मुक्त_ph;

	जबतक (eppnt->p_type != PT_LOAD)
		eppnt++;

	/* Now use mmap to map the library पूर्णांकo memory. */
	error = vm_mmap(file,
			ELF_PAGESTART(eppnt->p_vaddr),
			(eppnt->p_filesz +
			 ELF_PAGखातापूर्णFSET(eppnt->p_vaddr)),
			PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_FIXED_NOREPLACE | MAP_PRIVATE | MAP_DENYWRITE,
			(eppnt->p_offset -
			 ELF_PAGखातापूर्णFSET(eppnt->p_vaddr)));
	अगर (error != ELF_PAGESTART(eppnt->p_vaddr))
		जाओ out_मुक्त_ph;

	elf_bss = eppnt->p_vaddr + eppnt->p_filesz;
	अगर (padzero(elf_bss)) अणु
		error = -EFAULT;
		जाओ out_मुक्त_ph;
	पूर्ण

	len = ELF_PAGEALIGN(eppnt->p_filesz + eppnt->p_vaddr);
	bss = ELF_PAGEALIGN(eppnt->p_memsz + eppnt->p_vaddr);
	अगर (bss > len) अणु
		error = vm_brk(len, bss - len);
		अगर (error)
			जाओ out_मुक्त_ph;
	पूर्ण
	error = 0;

out_मुक्त_ph:
	kमुक्त(elf_phdata);
out:
	वापस error;
पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_USELIB */

#अगर_घोषित CONFIG_ELF_CORE
/*
 * ELF core dumper
 *
 * Modelled on fs/exec.c:aout_core_dump()
 * Jeremy Fitzhardinge <jeremy@sw.oz.au>
 */

/* An ELF note in memory */
काष्ठा memelfnote
अणु
	स्थिर अक्षर *name;
	पूर्णांक type;
	अचिन्हित पूर्णांक datasz;
	व्योम *data;
पूर्ण;

अटल पूर्णांक notesize(काष्ठा memelfnote *en)
अणु
	पूर्णांक sz;

	sz = माप(काष्ठा elf_note);
	sz += roundup(म_माप(en->name) + 1, 4);
	sz += roundup(en->datasz, 4);

	वापस sz;
पूर्ण

अटल पूर्णांक ग_लिखोnote(काष्ठा memelfnote *men, काष्ठा coredump_params *cprm)
अणु
	काष्ठा elf_note en;
	en.n_namesz = म_माप(men->name) + 1;
	en.n_descsz = men->datasz;
	en.n_type = men->type;

	वापस dump_emit(cprm, &en, माप(en)) &&
	    dump_emit(cprm, men->name, en.n_namesz) && dump_align(cprm, 4) &&
	    dump_emit(cprm, men->data, men->datasz) && dump_align(cprm, 4);
पूर्ण

अटल व्योम fill_elf_header(काष्ठा elfhdr *elf, पूर्णांक segs,
			    u16 machine, u32 flags)
अणु
	स_रखो(elf, 0, माप(*elf));

	स_नकल(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELF_DATA;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;

	elf->e_type = ET_CORE;
	elf->e_machine = machine;
	elf->e_version = EV_CURRENT;
	elf->e_phoff = माप(काष्ठा elfhdr);
	elf->e_flags = flags;
	elf->e_ehsize = माप(काष्ठा elfhdr);
	elf->e_phentsize = माप(काष्ठा elf_phdr);
	elf->e_phnum = segs;
पूर्ण

अटल व्योम fill_elf_note_phdr(काष्ठा elf_phdr *phdr, पूर्णांक sz, loff_t offset)
अणु
	phdr->p_type = PT_NOTE;
	phdr->p_offset = offset;
	phdr->p_vaddr = 0;
	phdr->p_paddr = 0;
	phdr->p_filesz = sz;
	phdr->p_memsz = 0;
	phdr->p_flags = 0;
	phdr->p_align = 0;
पूर्ण

अटल व्योम fill_note(काष्ठा memelfnote *note, स्थिर अक्षर *name, पूर्णांक type, 
		अचिन्हित पूर्णांक sz, व्योम *data)
अणु
	note->name = name;
	note->type = type;
	note->datasz = sz;
	note->data = data;
पूर्ण

/*
 * fill up all the fields in prstatus from the given task काष्ठा, except
 * रेजिस्टरs which need to be filled up separately.
 */
अटल व्योम fill_prstatus(काष्ठा elf_prstatus_common *prstatus,
		काष्ठा task_काष्ठा *p, दीर्घ signr)
अणु
	prstatus->pr_info.si_signo = prstatus->pr_cursig = signr;
	prstatus->pr_sigpend = p->pending.संकेत.sig[0];
	prstatus->pr_sighold = p->blocked.sig[0];
	rcu_पढ़ो_lock();
	prstatus->pr_ppid = task_pid_vnr(rcu_dereference(p->real_parent));
	rcu_पढ़ो_unlock();
	prstatus->pr_pid = task_pid_vnr(p);
	prstatus->pr_pgrp = task_pgrp_vnr(p);
	prstatus->pr_sid = task_session_vnr(p);
	अगर (thपढ़ो_group_leader(p)) अणु
		काष्ठा task_cpuसमय cpuसमय;

		/*
		 * This is the record क्रम the group leader.  It shows the
		 * group-wide total, not its inभागidual thपढ़ो total.
		 */
		thपढ़ो_group_cpuसमय(p, &cpuसमय);
		prstatus->pr_uसमय = ns_to_kernel_old_समयval(cpuसमय.uसमय);
		prstatus->pr_sसमय = ns_to_kernel_old_समयval(cpuसमय.sसमय);
	पूर्ण अन्यथा अणु
		u64 uसमय, sसमय;

		task_cpuसमय(p, &uसमय, &sसमय);
		prstatus->pr_uसमय = ns_to_kernel_old_समयval(uसमय);
		prstatus->pr_sसमय = ns_to_kernel_old_समयval(sसमय);
	पूर्ण

	prstatus->pr_cuसमय = ns_to_kernel_old_समयval(p->संकेत->cuसमय);
	prstatus->pr_csसमय = ns_to_kernel_old_समयval(p->संकेत->csसमय);
पूर्ण

अटल पूर्णांक fill_psinfo(काष्ठा elf_prpsinfo *psinfo, काष्ठा task_काष्ठा *p,
		       काष्ठा mm_काष्ठा *mm)
अणु
	स्थिर काष्ठा cred *cred;
	अचिन्हित पूर्णांक i, len;
	
	/* first copy the parameters from user space */
	स_रखो(psinfo, 0, माप(काष्ठा elf_prpsinfo));

	len = mm->arg_end - mm->arg_start;
	अगर (len >= ELF_PRARGSZ)
		len = ELF_PRARGSZ-1;
	अगर (copy_from_user(&psinfo->pr_psargs,
		           (स्थिर अक्षर __user *)mm->arg_start, len))
		वापस -EFAULT;
	क्रम(i = 0; i < len; i++)
		अगर (psinfo->pr_psargs[i] == 0)
			psinfo->pr_psargs[i] = ' ';
	psinfo->pr_psargs[len] = 0;

	rcu_पढ़ो_lock();
	psinfo->pr_ppid = task_pid_vnr(rcu_dereference(p->real_parent));
	rcu_पढ़ो_unlock();
	psinfo->pr_pid = task_pid_vnr(p);
	psinfo->pr_pgrp = task_pgrp_vnr(p);
	psinfo->pr_sid = task_session_vnr(p);

	i = p->state ? ffz(~p->state) + 1 : 0;
	psinfo->pr_state = i;
	psinfo->pr_sname = (i > 5) ? '.' : "RSDTZW"[i];
	psinfo->pr_zomb = psinfo->pr_sname == 'Z';
	psinfo->pr_nice = task_nice(p);
	psinfo->pr_flag = p->flags;
	rcu_पढ़ो_lock();
	cred = __task_cred(p);
	SET_UID(psinfo->pr_uid, from_kuid_munged(cred->user_ns, cred->uid));
	SET_GID(psinfo->pr_gid, from_kgid_munged(cred->user_ns, cred->gid));
	rcu_पढ़ो_unlock();
	म_नकलन(psinfo->pr_fname, p->comm, माप(psinfo->pr_fname));
	
	वापस 0;
पूर्ण

अटल व्योम fill_auxv_note(काष्ठा memelfnote *note, काष्ठा mm_काष्ठा *mm)
अणु
	elf_addr_t *auxv = (elf_addr_t *) mm->saved_auxv;
	पूर्णांक i = 0;
	करो
		i += 2;
	जबतक (auxv[i - 2] != AT_शून्य);
	fill_note(note, "CORE", NT_AUXV, i * माप(elf_addr_t), auxv);
पूर्ण

अटल व्योम fill_siginfo_note(काष्ठा memelfnote *note, user_siginfo_t *csigdata,
		स्थिर kernel_siginfo_t *siginfo)
अणु
	copy_siginfo_to_बाह्यal(csigdata, siginfo);
	fill_note(note, "CORE", NT_SIGINFO, माप(*csigdata), csigdata);
पूर्ण

#घोषणा MAX_खाता_NOTE_SIZE (4*1024*1024)
/*
 * Format of NT_खाता note:
 *
 * दीर्घ count     -- how many files are mapped
 * दीर्घ page_size -- units क्रम file_ofs
 * array of [COUNT] elements of
 *   दीर्घ start
 *   दीर्घ end
 *   दीर्घ file_ofs
 * followed by COUNT filenames in ASCII: "FILE1" NUL "FILE2" NUL...
 */
अटल पूर्णांक fill_files_note(काष्ठा memelfnote *note)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित count, size, names_ofs, reमुख्यing, n;
	user_दीर्घ_t *data;
	user_दीर्घ_t *start_end_ofs;
	अक्षर *name_base, *name_curpos;

	/* *Estimated* file count and total data size needed */
	count = mm->map_count;
	अगर (count > अच_पूर्णांक_उच्च / 64)
		वापस -EINVAL;
	size = count * 64;

	names_ofs = (2 + 3 * count) * माप(data[0]);
 alloc:
	अगर (size >= MAX_खाता_NOTE_SIZE) /* paranoia check */
		वापस -EINVAL;
	size = round_up(size, PAGE_SIZE);
	/*
	 * "size" can be 0 here legitimately.
	 * Let it ENOMEM and omit NT_खाता section which will be empty anyway.
	 */
	data = kvदो_स्मृति(size, GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(data))
		वापस -ENOMEM;

	start_end_ofs = data + 2;
	name_base = name_curpos = ((अक्षर *)data) + names_ofs;
	reमुख्यing = size - names_ofs;
	count = 0;
	क्रम (vma = mm->mmap; vma != शून्य; vma = vma->vm_next) अणु
		काष्ठा file *file;
		स्थिर अक्षर *filename;

		file = vma->vm_file;
		अगर (!file)
			जारी;
		filename = file_path(file, name_curpos, reमुख्यing);
		अगर (IS_ERR(filename)) अणु
			अगर (PTR_ERR(filename) == -ENAMETOOLONG) अणु
				kvमुक्त(data);
				size = size * 5 / 4;
				जाओ alloc;
			पूर्ण
			जारी;
		पूर्ण

		/* file_path() fills at the end, move name करोwn */
		/* n = म_माप(filename) + 1: */
		n = (name_curpos + reमुख्यing) - filename;
		reमुख्यing = filename - name_curpos;
		स_हटाओ(name_curpos, filename, n);
		name_curpos += n;

		*start_end_ofs++ = vma->vm_start;
		*start_end_ofs++ = vma->vm_end;
		*start_end_ofs++ = vma->vm_pgoff;
		count++;
	पूर्ण

	/* Now we know exact count of files, can store it */
	data[0] = count;
	data[1] = PAGE_SIZE;
	/*
	 * Count usually is less than mm->map_count,
	 * we need to move filenames करोwn.
	 */
	n = mm->map_count - count;
	अगर (n != 0) अणु
		अचिन्हित shअगरt_bytes = n * 3 * माप(data[0]);
		स_हटाओ(name_base - shअगरt_bytes, name_base,
			name_curpos - name_base);
		name_curpos -= shअगरt_bytes;
	पूर्ण

	size = name_curpos - (अक्षर *)data;
	fill_note(note, "CORE", NT_खाता, size, data);
	वापस 0;
पूर्ण

#अगर_घोषित CORE_DUMP_USE_REGSET
#समावेश <linux/regset.h>

काष्ठा elf_thपढ़ो_core_info अणु
	काष्ठा elf_thपढ़ो_core_info *next;
	काष्ठा task_काष्ठा *task;
	काष्ठा elf_prstatus prstatus;
	काष्ठा memelfnote notes[];
पूर्ण;

काष्ठा elf_note_info अणु
	काष्ठा elf_thपढ़ो_core_info *thपढ़ो;
	काष्ठा memelfnote psinfo;
	काष्ठा memelfnote signote;
	काष्ठा memelfnote auxv;
	काष्ठा memelfnote files;
	user_siginfo_t csigdata;
	माप_प्रकार size;
	पूर्णांक thपढ़ो_notes;
पूर्ण;

/*
 * When a regset has a ग_लिखोback hook, we call it on each thपढ़ो beक्रमe
 * dumping user memory.  On रेजिस्टर winकरोw machines, this makes sure the
 * user memory backing the रेजिस्टर data is up to date beक्रमe we पढ़ो it.
 */
अटल व्योम करो_thपढ़ो_regset_ग_लिखोback(काष्ठा task_काष्ठा *task,
				       स्थिर काष्ठा user_regset *regset)
अणु
	अगर (regset->ग_लिखोback)
		regset->ग_लिखोback(task, regset, 1);
पूर्ण

#अगर_अघोषित PRSTATUS_SIZE
#घोषणा PRSTATUS_SIZE माप(काष्ठा elf_prstatus)
#पूर्ण_अगर

#अगर_अघोषित SET_PR_FPVALID
#घोषणा SET_PR_FPVALID(S) ((S)->pr_fpvalid = 1)
#पूर्ण_अगर

अटल पूर्णांक fill_thपढ़ो_core_info(काष्ठा elf_thपढ़ो_core_info *t,
				 स्थिर काष्ठा user_regset_view *view,
				 दीर्घ signr, माप_प्रकार *total)
अणु
	अचिन्हित पूर्णांक i;

	/*
	 * NT_PRSTATUS is the one special हाल, because the regset data
	 * goes पूर्णांकo the pr_reg field inside the note contents, rather
	 * than being the whole note contents.  We fill the reset in here.
	 * We assume that regset 0 is NT_PRSTATUS.
	 */
	fill_prstatus(&t->prstatus.common, t->task, signr);
	regset_get(t->task, &view->regsets[0],
		   माप(t->prstatus.pr_reg), &t->prstatus.pr_reg);

	fill_note(&t->notes[0], "CORE", NT_PRSTATUS,
		  PRSTATUS_SIZE, &t->prstatus);
	*total += notesize(&t->notes[0]);

	करो_thपढ़ो_regset_ग_लिखोback(t->task, &view->regsets[0]);

	/*
	 * Each other regset might generate a note too.  For each regset
	 * that has no core_note_type or is inactive, we leave t->notes[i]
	 * all zero and we'll know to skip writing it later.
	 */
	क्रम (i = 1; i < view->n; ++i) अणु
		स्थिर काष्ठा user_regset *regset = &view->regsets[i];
		पूर्णांक note_type = regset->core_note_type;
		bool is_fpreg = note_type == NT_PRFPREG;
		व्योम *data;
		पूर्णांक ret;

		करो_thपढ़ो_regset_ग_लिखोback(t->task, regset);
		अगर (!note_type) // not क्रम coredumps
			जारी;
		अगर (regset->active && regset->active(t->task, regset) <= 0)
			जारी;

		ret = regset_get_alloc(t->task, regset, ~0U, &data);
		अगर (ret < 0)
			जारी;

		अगर (is_fpreg)
			SET_PR_FPVALID(&t->prstatus);

		fill_note(&t->notes[i], is_fpreg ? "CORE" : "LINUX",
			  note_type, ret, data);

		*total += notesize(&t->notes[i]);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक fill_note_info(काष्ठा elfhdr *elf, पूर्णांक phdrs,
			  काष्ठा elf_note_info *info,
			  स्थिर kernel_siginfo_t *siginfo, काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *dump_task = current;
	स्थिर काष्ठा user_regset_view *view = task_user_regset_view(dump_task);
	काष्ठा elf_thपढ़ो_core_info *t;
	काष्ठा elf_prpsinfo *psinfo;
	काष्ठा core_thपढ़ो *ct;
	अचिन्हित पूर्णांक i;

	info->size = 0;
	info->thपढ़ो = शून्य;

	psinfo = kदो_स्मृति(माप(*psinfo), GFP_KERNEL);
	अगर (psinfo == शून्य) अणु
		info->psinfo.data = शून्य; /* So we करोn't मुक्त this wrongly */
		वापस 0;
	पूर्ण

	fill_note(&info->psinfo, "CORE", NT_PRPSINFO, माप(*psinfo), psinfo);

	/*
	 * Figure out how many notes we're going to need क्रम each thपढ़ो.
	 */
	info->thपढ़ो_notes = 0;
	क्रम (i = 0; i < view->n; ++i)
		अगर (view->regsets[i].core_note_type != 0)
			++info->thपढ़ो_notes;

	/*
	 * Sanity check.  We rely on regset 0 being in NT_PRSTATUS,
	 * since it is our one special हाल.
	 */
	अगर (unlikely(info->thपढ़ो_notes == 0) ||
	    unlikely(view->regsets[0].core_note_type != NT_PRSTATUS)) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	/*
	 * Initialize the ELF file header.
	 */
	fill_elf_header(elf, phdrs,
			view->e_machine, view->e_flags);

	/*
	 * Allocate a काष्ठाure क्रम each thपढ़ो.
	 */
	क्रम (ct = &dump_task->mm->core_state->dumper; ct; ct = ct->next) अणु
		t = kzalloc(दुरत्व(काष्ठा elf_thपढ़ो_core_info,
				     notes[info->thपढ़ो_notes]),
			    GFP_KERNEL);
		अगर (unlikely(!t))
			वापस 0;

		t->task = ct->task;
		अगर (ct->task == dump_task || !info->thपढ़ो) अणु
			t->next = info->thपढ़ो;
			info->thपढ़ो = t;
		पूर्ण अन्यथा अणु
			/*
			 * Make sure to keep the original task at
			 * the head of the list.
			 */
			t->next = info->thपढ़ो->next;
			info->thपढ़ो->next = t;
		पूर्ण
	पूर्ण

	/*
	 * Now fill in each thपढ़ो's inक्रमmation.
	 */
	क्रम (t = info->thपढ़ो; t != शून्य; t = t->next)
		अगर (!fill_thपढ़ो_core_info(t, view, siginfo->si_signo, &info->size))
			वापस 0;

	/*
	 * Fill in the two process-wide notes.
	 */
	fill_psinfo(psinfo, dump_task->group_leader, dump_task->mm);
	info->size += notesize(&info->psinfo);

	fill_siginfo_note(&info->signote, &info->csigdata, siginfo);
	info->size += notesize(&info->signote);

	fill_auxv_note(&info->auxv, current->mm);
	info->size += notesize(&info->auxv);

	अगर (fill_files_note(&info->files) == 0)
		info->size += notesize(&info->files);

	वापस 1;
पूर्ण

अटल माप_प्रकार get_note_info_size(काष्ठा elf_note_info *info)
अणु
	वापस info->size;
पूर्ण

/*
 * Write all the notes क्रम each thपढ़ो.  When writing the first thपढ़ो, the
 * process-wide notes are पूर्णांकerleaved after the first thपढ़ो-specअगरic note.
 */
अटल पूर्णांक ग_लिखो_note_info(काष्ठा elf_note_info *info,
			   काष्ठा coredump_params *cprm)
अणु
	bool first = true;
	काष्ठा elf_thपढ़ो_core_info *t = info->thपढ़ो;

	करो अणु
		पूर्णांक i;

		अगर (!ग_लिखोnote(&t->notes[0], cprm))
			वापस 0;

		अगर (first && !ग_लिखोnote(&info->psinfo, cprm))
			वापस 0;
		अगर (first && !ग_लिखोnote(&info->signote, cprm))
			वापस 0;
		अगर (first && !ग_लिखोnote(&info->auxv, cprm))
			वापस 0;
		अगर (first && info->files.data &&
				!ग_लिखोnote(&info->files, cprm))
			वापस 0;

		क्रम (i = 1; i < info->thपढ़ो_notes; ++i)
			अगर (t->notes[i].data &&
			    !ग_लिखोnote(&t->notes[i], cprm))
				वापस 0;

		first = false;
		t = t->next;
	पूर्ण जबतक (t);

	वापस 1;
पूर्ण

अटल व्योम मुक्त_note_info(काष्ठा elf_note_info *info)
अणु
	काष्ठा elf_thपढ़ो_core_info *thपढ़ोs = info->thपढ़ो;
	जबतक (thपढ़ोs) अणु
		अचिन्हित पूर्णांक i;
		काष्ठा elf_thपढ़ो_core_info *t = thपढ़ोs;
		thपढ़ोs = t->next;
		WARN_ON(t->notes[0].data && t->notes[0].data != &t->prstatus);
		क्रम (i = 1; i < info->thपढ़ो_notes; ++i)
			kमुक्त(t->notes[i].data);
		kमुक्त(t);
	पूर्ण
	kमुक्त(info->psinfo.data);
	kvमुक्त(info->files.data);
पूर्ण

#अन्यथा

/* Here is the काष्ठाure in which status of each thपढ़ो is captured. */
काष्ठा elf_thपढ़ो_status
अणु
	काष्ठा list_head list;
	काष्ठा elf_prstatus prstatus;	/* NT_PRSTATUS */
	elf_fpregset_t fpu;		/* NT_PRFPREG */
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा memelfnote notes[3];
	पूर्णांक num_notes;
पूर्ण;

/*
 * In order to add the specअगरic thपढ़ो inक्रमmation क्रम the elf file क्रमmat,
 * we need to keep a linked list of every thपढ़ोs pr_status and then create
 * a single section क्रम them in the final core file.
 */
अटल पूर्णांक elf_dump_thपढ़ो_status(दीर्घ signr, काष्ठा elf_thपढ़ो_status *t)
अणु
	पूर्णांक sz = 0;
	काष्ठा task_काष्ठा *p = t->thपढ़ो;
	t->num_notes = 0;

	fill_prstatus(&t->prstatus.common, p, signr);
	elf_core_copy_task_regs(p, &t->prstatus.pr_reg);	
	
	fill_note(&t->notes[0], "CORE", NT_PRSTATUS, माप(t->prstatus),
		  &(t->prstatus));
	t->num_notes++;
	sz += notesize(&t->notes[0]);

	अगर ((t->prstatus.pr_fpvalid = elf_core_copy_task_fpregs(p, शून्य,
								&t->fpu))) अणु
		fill_note(&t->notes[1], "CORE", NT_PRFPREG, माप(t->fpu),
			  &(t->fpu));
		t->num_notes++;
		sz += notesize(&t->notes[1]);
	पूर्ण
	वापस sz;
पूर्ण

काष्ठा elf_note_info अणु
	काष्ठा memelfnote *notes;
	काष्ठा memelfnote *notes_files;
	काष्ठा elf_prstatus *prstatus;	/* NT_PRSTATUS */
	काष्ठा elf_prpsinfo *psinfo;	/* NT_PRPSINFO */
	काष्ठा list_head thपढ़ो_list;
	elf_fpregset_t *fpu;
	user_siginfo_t csigdata;
	पूर्णांक thपढ़ो_status_size;
	पूर्णांक numnote;
पूर्ण;

अटल पूर्णांक elf_note_info_init(काष्ठा elf_note_info *info)
अणु
	स_रखो(info, 0, माप(*info));
	INIT_LIST_HEAD(&info->thपढ़ो_list);

	/* Allocate space क्रम ELF notes */
	info->notes = kदो_स्मृति_array(8, माप(काष्ठा memelfnote), GFP_KERNEL);
	अगर (!info->notes)
		वापस 0;
	info->psinfo = kदो_स्मृति(माप(*info->psinfo), GFP_KERNEL);
	अगर (!info->psinfo)
		वापस 0;
	info->prstatus = kदो_स्मृति(माप(*info->prstatus), GFP_KERNEL);
	अगर (!info->prstatus)
		वापस 0;
	info->fpu = kदो_स्मृति(माप(*info->fpu), GFP_KERNEL);
	अगर (!info->fpu)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक fill_note_info(काष्ठा elfhdr *elf, पूर्णांक phdrs,
			  काष्ठा elf_note_info *info,
			  स्थिर kernel_siginfo_t *siginfo, काष्ठा pt_regs *regs)
अणु
	काष्ठा core_thपढ़ो *ct;
	काष्ठा elf_thपढ़ो_status *ets;

	अगर (!elf_note_info_init(info))
		वापस 0;

	क्रम (ct = current->mm->core_state->dumper.next;
					ct; ct = ct->next) अणु
		ets = kzalloc(माप(*ets), GFP_KERNEL);
		अगर (!ets)
			वापस 0;

		ets->thपढ़ो = ct->task;
		list_add(&ets->list, &info->thपढ़ो_list);
	पूर्ण

	list_क्रम_each_entry(ets, &info->thपढ़ो_list, list) अणु
		पूर्णांक sz;

		sz = elf_dump_thपढ़ो_status(siginfo->si_signo, ets);
		info->thपढ़ो_status_size += sz;
	पूर्ण
	/* now collect the dump क्रम the current */
	स_रखो(info->prstatus, 0, माप(*info->prstatus));
	fill_prstatus(&info->prstatus->common, current, siginfo->si_signo);
	elf_core_copy_regs(&info->prstatus->pr_reg, regs);

	/* Set up header */
	fill_elf_header(elf, phdrs, ELF_ARCH, ELF_CORE_EFLAGS);

	/*
	 * Set up the notes in similar क्रमm to SVR4 core dumps made
	 * with info from their /proc.
	 */

	fill_note(info->notes + 0, "CORE", NT_PRSTATUS,
		  माप(*info->prstatus), info->prstatus);
	fill_psinfo(info->psinfo, current->group_leader, current->mm);
	fill_note(info->notes + 1, "CORE", NT_PRPSINFO,
		  माप(*info->psinfo), info->psinfo);

	fill_siginfo_note(info->notes + 2, &info->csigdata, siginfo);
	fill_auxv_note(info->notes + 3, current->mm);
	info->numnote = 4;

	अगर (fill_files_note(info->notes + info->numnote) == 0) अणु
		info->notes_files = info->notes + info->numnote;
		info->numnote++;
	पूर्ण

	/* Try to dump the FPU. */
	info->prstatus->pr_fpvalid = elf_core_copy_task_fpregs(current, regs,
							       info->fpu);
	अगर (info->prstatus->pr_fpvalid)
		fill_note(info->notes + info->numnote++,
			  "CORE", NT_PRFPREG, माप(*info->fpu), info->fpu);
	वापस 1;
पूर्ण

अटल माप_प्रकार get_note_info_size(काष्ठा elf_note_info *info)
अणु
	पूर्णांक sz = 0;
	पूर्णांक i;

	क्रम (i = 0; i < info->numnote; i++)
		sz += notesize(info->notes + i);

	sz += info->thपढ़ो_status_size;

	वापस sz;
पूर्ण

अटल पूर्णांक ग_लिखो_note_info(काष्ठा elf_note_info *info,
			   काष्ठा coredump_params *cprm)
अणु
	काष्ठा elf_thपढ़ो_status *ets;
	पूर्णांक i;

	क्रम (i = 0; i < info->numnote; i++)
		अगर (!ग_लिखोnote(info->notes + i, cprm))
			वापस 0;

	/* ग_लिखो out the thपढ़ो status notes section */
	list_क्रम_each_entry(ets, &info->thपढ़ो_list, list) अणु
		क्रम (i = 0; i < ets->num_notes; i++)
			अगर (!ग_लिखोnote(&ets->notes[i], cprm))
				वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम मुक्त_note_info(काष्ठा elf_note_info *info)
अणु
	जबतक (!list_empty(&info->thपढ़ो_list)) अणु
		काष्ठा list_head *पंचांगp = info->thपढ़ो_list.next;
		list_del(पंचांगp);
		kमुक्त(list_entry(पंचांगp, काष्ठा elf_thपढ़ो_status, list));
	पूर्ण

	/* Free data possibly allocated by fill_files_note(): */
	अगर (info->notes_files)
		kvमुक्त(info->notes_files->data);

	kमुक्त(info->prstatus);
	kमुक्त(info->psinfo);
	kमुक्त(info->notes);
	kमुक्त(info->fpu);
पूर्ण

#पूर्ण_अगर

अटल व्योम fill_extnum_info(काष्ठा elfhdr *elf, काष्ठा elf_shdr *shdr4extnum,
			     elf_addr_t e_shoff, पूर्णांक segs)
अणु
	elf->e_shoff = e_shoff;
	elf->e_shentsize = माप(*shdr4extnum);
	elf->e_shnum = 1;
	elf->e_shstrndx = SHN_UNDEF;

	स_रखो(shdr4extnum, 0, माप(*shdr4extnum));

	shdr4extnum->sh_type = SHT_शून्य;
	shdr4extnum->sh_size = elf->e_shnum;
	shdr4extnum->sh_link = elf->e_shstrndx;
	shdr4extnum->sh_info = segs;
पूर्ण

/*
 * Actual dumper
 *
 * This is a two-pass process; first we find the offsets of the bits,
 * and then they are actually written out.  If we run out of core limit
 * we just truncate.
 */
अटल पूर्णांक elf_core_dump(काष्ठा coredump_params *cprm)
अणु
	पूर्णांक has_dumped = 0;
	पूर्णांक vma_count, segs, i;
	माप_प्रकार vma_data_size;
	काष्ठा elfhdr elf;
	loff_t offset = 0, dataoff;
	काष्ठा elf_note_info info = अणु पूर्ण;
	काष्ठा elf_phdr *phdr4note = शून्य;
	काष्ठा elf_shdr *shdr4extnum = शून्य;
	Elf_Half e_phnum;
	elf_addr_t e_shoff;
	काष्ठा core_vma_metadata *vma_meta;

	अगर (dump_vma_snapshot(cprm, &vma_count, &vma_meta, &vma_data_size))
		वापस 0;

	/*
	 * The number of segs are recored पूर्णांकo ELF header as 16bit value.
	 * Please check DEFAULT_MAX_MAP_COUNT definition when you modअगरy here.
	 */
	segs = vma_count + elf_core_extra_phdrs();

	/* क्रम notes section */
	segs++;

	/* If segs > PN_XNUM(0xffff), then e_phnum overflows. To aव्योम
	 * this, kernel supports extended numbering. Have a look at
	 * include/linux/elf.h क्रम further inक्रमmation. */
	e_phnum = segs > PN_XNUM ? PN_XNUM : segs;

	/*
	 * Collect all the non-memory inक्रमmation about the process क्रम the
	 * notes.  This also sets up the file header.
	 */
	अगर (!fill_note_info(&elf, e_phnum, &info, cprm->siginfo, cprm->regs))
		जाओ end_coredump;

	has_dumped = 1;

	offset += माप(elf);				/* Elf header */
	offset += segs * माप(काष्ठा elf_phdr);	/* Program headers */

	/* Write notes phdr entry */
	अणु
		माप_प्रकार sz = get_note_info_size(&info);

		/* For cell spufs */
		sz += elf_coredump_extra_notes_size();

		phdr4note = kदो_स्मृति(माप(*phdr4note), GFP_KERNEL);
		अगर (!phdr4note)
			जाओ end_coredump;

		fill_elf_note_phdr(phdr4note, sz, offset);
		offset += sz;
	पूर्ण

	dataoff = offset = roundup(offset, ELF_EXEC_PAGESIZE);

	offset += vma_data_size;
	offset += elf_core_extra_data_size();
	e_shoff = offset;

	अगर (e_phnum == PN_XNUM) अणु
		shdr4extnum = kदो_स्मृति(माप(*shdr4extnum), GFP_KERNEL);
		अगर (!shdr4extnum)
			जाओ end_coredump;
		fill_extnum_info(&elf, shdr4extnum, e_shoff, segs);
	पूर्ण

	offset = dataoff;

	अगर (!dump_emit(cprm, &elf, माप(elf)))
		जाओ end_coredump;

	अगर (!dump_emit(cprm, phdr4note, माप(*phdr4note)))
		जाओ end_coredump;

	/* Write program headers क्रम segments dump */
	क्रम (i = 0; i < vma_count; i++) अणु
		काष्ठा core_vma_metadata *meta = vma_meta + i;
		काष्ठा elf_phdr phdr;

		phdr.p_type = PT_LOAD;
		phdr.p_offset = offset;
		phdr.p_vaddr = meta->start;
		phdr.p_paddr = 0;
		phdr.p_filesz = meta->dump_size;
		phdr.p_memsz = meta->end - meta->start;
		offset += phdr.p_filesz;
		phdr.p_flags = 0;
		अगर (meta->flags & VM_READ)
			phdr.p_flags |= PF_R;
		अगर (meta->flags & VM_WRITE)
			phdr.p_flags |= PF_W;
		अगर (meta->flags & VM_EXEC)
			phdr.p_flags |= PF_X;
		phdr.p_align = ELF_EXEC_PAGESIZE;

		अगर (!dump_emit(cprm, &phdr, माप(phdr)))
			जाओ end_coredump;
	पूर्ण

	अगर (!elf_core_ग_लिखो_extra_phdrs(cprm, offset))
		जाओ end_coredump;

 	/* ग_लिखो out the notes section */
	अगर (!ग_लिखो_note_info(&info, cprm))
		जाओ end_coredump;

	/* For cell spufs */
	अगर (elf_coredump_extra_notes_ग_लिखो(cprm))
		जाओ end_coredump;

	/* Align to page */
	dump_skip_to(cprm, dataoff);

	क्रम (i = 0; i < vma_count; i++) अणु
		काष्ठा core_vma_metadata *meta = vma_meta + i;

		अगर (!dump_user_range(cprm, meta->start, meta->dump_size))
			जाओ end_coredump;
	पूर्ण

	अगर (!elf_core_ग_लिखो_extra_data(cprm))
		जाओ end_coredump;

	अगर (e_phnum == PN_XNUM) अणु
		अगर (!dump_emit(cprm, shdr4extnum, माप(*shdr4extnum)))
			जाओ end_coredump;
	पूर्ण

end_coredump:
	मुक्त_note_info(&info);
	kमुक्त(shdr4extnum);
	kvमुक्त(vma_meta);
	kमुक्त(phdr4note);
	वापस has_dumped;
पूर्ण

#पूर्ण_अगर		/* CONFIG_ELF_CORE */

अटल पूर्णांक __init init_elf_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&elf_क्रमmat);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_elf_binfmt(व्योम)
अणु
	/* Remove the COFF and ELF loaders. */
	unरेजिस्टर_binfmt(&elf_क्रमmat);
पूर्ण

core_initcall(init_elf_binfmt);
module_निकास(निकास_elf_binfmt);
MODULE_LICENSE("GPL");
