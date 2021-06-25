<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* binfmt_elf_fdpic.c: FDPIC ELF binary क्रमmat
 *
 * Copyright (C) 2003, 2004, 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 * Derived from binfmt_elf.c
 */

#समावेश <linux/module.h>

#समावेश <linux/fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/binfmts.h>
#समावेश <linux/माला.स>
#समावेश <linux/file.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/security.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/highuid.h>
#समावेश <linux/personality.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/init.h>
#समावेश <linux/elf.h>
#समावेश <linux/elf-fdpic.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/coredump.h>
#समावेश <linux/dax.h>
#समावेश <linux/regset.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/param.h>

प्रकार अक्षर *elf_caddr_t;

#अगर 0
#घोषणा kdebug(fmt, ...) prपूर्णांकk("FDPIC "fmt"\n" ,##__VA_ARGS__ )
#अन्यथा
#घोषणा kdebug(fmt, ...) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

#अगर 0
#घोषणा kdcore(fmt, ...) prपूर्णांकk("FDPIC "fmt"\n" ,##__VA_ARGS__ )
#अन्यथा
#घोषणा kdcore(fmt, ...) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

MODULE_LICENSE("GPL");

अटल पूर्णांक load_elf_fdpic_binary(काष्ठा linux_binprm *);
अटल पूर्णांक elf_fdpic_fetch_phdrs(काष्ठा elf_fdpic_params *, काष्ठा file *);
अटल पूर्णांक elf_fdpic_map_file(काष्ठा elf_fdpic_params *, काष्ठा file *,
			      काष्ठा mm_काष्ठा *, स्थिर अक्षर *);

अटल पूर्णांक create_elf_fdpic_tables(काष्ठा linux_binprm *, काष्ठा mm_काष्ठा *,
				   काष्ठा elf_fdpic_params *,
				   काष्ठा elf_fdpic_params *);

#अगर_अघोषित CONFIG_MMU
अटल पूर्णांक elf_fdpic_map_file_स्थिरdisp_on_uclinux(काष्ठा elf_fdpic_params *,
						   काष्ठा file *,
						   काष्ठा mm_काष्ठा *);
#पूर्ण_अगर

अटल पूर्णांक elf_fdpic_map_file_by_direct_mmap(काष्ठा elf_fdpic_params *,
					     काष्ठा file *, काष्ठा mm_काष्ठा *);

#अगर_घोषित CONFIG_ELF_CORE
अटल पूर्णांक elf_fdpic_core_dump(काष्ठा coredump_params *cprm);
#पूर्ण_अगर

अटल काष्ठा linux_binfmt elf_fdpic_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_elf_fdpic_binary,
#अगर_घोषित CONFIG_ELF_CORE
	.core_dump	= elf_fdpic_core_dump,
#पूर्ण_अगर
	.min_coredump	= ELF_EXEC_PAGESIZE,
पूर्ण;

अटल पूर्णांक __init init_elf_fdpic_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&elf_fdpic_क्रमmat);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_elf_fdpic_binfmt(व्योम)
अणु
	unरेजिस्टर_binfmt(&elf_fdpic_क्रमmat);
पूर्ण

core_initcall(init_elf_fdpic_binfmt);
module_निकास(निकास_elf_fdpic_binfmt);

अटल पूर्णांक is_elf(काष्ठा elfhdr *hdr, काष्ठा file *file)
अणु
	अगर (स_भेद(hdr->e_ident, ELFMAG, SELFMAG) != 0)
		वापस 0;
	अगर (hdr->e_type != ET_EXEC && hdr->e_type != ET_DYN)
		वापस 0;
	अगर (!elf_check_arch(hdr))
		वापस 0;
	अगर (!file->f_op->mmap)
		वापस 0;
	वापस 1;
पूर्ण

#अगर_अघोषित elf_check_fdpic
#घोषणा elf_check_fdpic(x) 0
#पूर्ण_अगर

#अगर_अघोषित elf_check_स्थिर_displacement
#घोषणा elf_check_स्थिर_displacement(x) 0
#पूर्ण_अगर

अटल पूर्णांक is_स्थिरdisp(काष्ठा elfhdr *hdr)
अणु
	अगर (!elf_check_fdpic(hdr))
		वापस 1;
	अगर (elf_check_स्थिर_displacement(hdr))
		वापस 1;
	वापस 0;
पूर्ण

/*****************************************************************************/
/*
 * पढ़ो the program headers table पूर्णांकo memory
 */
अटल पूर्णांक elf_fdpic_fetch_phdrs(काष्ठा elf_fdpic_params *params,
				 काष्ठा file *file)
अणु
	काष्ठा elf32_phdr *phdr;
	अचिन्हित दीर्घ size;
	पूर्णांक retval, loop;
	loff_t pos = params->hdr.e_phoff;

	अगर (params->hdr.e_phentsize != माप(काष्ठा elf_phdr))
		वापस -ENOMEM;
	अगर (params->hdr.e_phnum > 65536U / माप(काष्ठा elf_phdr))
		वापस -ENOMEM;

	size = params->hdr.e_phnum * माप(काष्ठा elf_phdr);
	params->phdrs = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!params->phdrs)
		वापस -ENOMEM;

	retval = kernel_पढ़ो(file, params->phdrs, size, &pos);
	अगर (unlikely(retval != size))
		वापस retval < 0 ? retval : -ENOEXEC;

	/* determine stack size क्रम this binary */
	phdr = params->phdrs;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अगर (phdr->p_type != PT_GNU_STACK)
			जारी;

		अगर (phdr->p_flags & PF_X)
			params->flags |= ELF_FDPIC_FLAG_EXEC_STACK;
		अन्यथा
			params->flags |= ELF_FDPIC_FLAG_NOEXEC_STACK;

		params->stack_size = phdr->p_memsz;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*****************************************************************************/
/*
 * load an fdpic binary पूर्णांकo various bits of memory
 */
अटल पूर्णांक load_elf_fdpic_binary(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा elf_fdpic_params exec_params, पूर्णांकerp_params;
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा elf_phdr *phdr;
	अचिन्हित दीर्घ stack_size, entryaddr;
#अगर_घोषित ELF_FDPIC_PLAT_INIT
	अचिन्हित दीर्घ dynaddr;
#पूर्ण_अगर
#अगर_अघोषित CONFIG_MMU
	अचिन्हित दीर्घ stack_prot;
#पूर्ण_अगर
	काष्ठा file *पूर्णांकerpreter = शून्य; /* to shut gcc up */
	अक्षर *पूर्णांकerpreter_name = शून्य;
	पूर्णांक executable_stack;
	पूर्णांक retval, i;
	loff_t pos;

	kdebug("____ LOAD %d ____", current->pid);

	स_रखो(&exec_params, 0, माप(exec_params));
	स_रखो(&पूर्णांकerp_params, 0, माप(पूर्णांकerp_params));

	exec_params.hdr = *(काष्ठा elfhdr *) bprm->buf;
	exec_params.flags = ELF_FDPIC_FLAG_PRESENT | ELF_FDPIC_FLAG_EXECUTABLE;

	/* check that this is a binary we know how to deal with */
	retval = -ENOEXEC;
	अगर (!is_elf(&exec_params.hdr, bprm->file))
		जाओ error;
	अगर (!elf_check_fdpic(&exec_params.hdr)) अणु
#अगर_घोषित CONFIG_MMU
		/* binfmt_elf handles non-fdpic elf except on nommu */
		जाओ error;
#अन्यथा
		/* nommu can only load ET_DYN (PIE) ELF */
		अगर (exec_params.hdr.e_type != ET_DYN)
			जाओ error;
#पूर्ण_अगर
	पूर्ण

	/* पढ़ो the program header table */
	retval = elf_fdpic_fetch_phdrs(&exec_params, bprm->file);
	अगर (retval < 0)
		जाओ error;

	/* scan क्रम a program header that specअगरies an पूर्णांकerpreter */
	phdr = exec_params.phdrs;

	क्रम (i = 0; i < exec_params.hdr.e_phnum; i++, phdr++) अणु
		चयन (phdr->p_type) अणु
		हाल PT_INTERP:
			retval = -ENOMEM;
			अगर (phdr->p_filesz > PATH_MAX)
				जाओ error;
			retval = -ENOENT;
			अगर (phdr->p_filesz < 2)
				जाओ error;

			/* पढ़ो the name of the पूर्णांकerpreter पूर्णांकo memory */
			पूर्णांकerpreter_name = kदो_स्मृति(phdr->p_filesz, GFP_KERNEL);
			अगर (!पूर्णांकerpreter_name)
				जाओ error;

			pos = phdr->p_offset;
			retval = kernel_पढ़ो(bprm->file, पूर्णांकerpreter_name,
					     phdr->p_filesz, &pos);
			अगर (unlikely(retval != phdr->p_filesz)) अणु
				अगर (retval >= 0)
					retval = -ENOEXEC;
				जाओ error;
			पूर्ण

			retval = -ENOENT;
			अगर (पूर्णांकerpreter_name[phdr->p_filesz - 1] != '\0')
				जाओ error;

			kdebug("Using ELF interpreter %s", पूर्णांकerpreter_name);

			/* replace the program with the पूर्णांकerpreter */
			पूर्णांकerpreter = खोलो_exec(पूर्णांकerpreter_name);
			retval = PTR_ERR(पूर्णांकerpreter);
			अगर (IS_ERR(पूर्णांकerpreter)) अणु
				पूर्णांकerpreter = शून्य;
				जाओ error;
			पूर्ण

			/*
			 * If the binary is not पढ़ोable then enक्रमce
			 * mm->dumpable = 0 regardless of the पूर्णांकerpreter's
			 * permissions.
			 */
			would_dump(bprm, पूर्णांकerpreter);

			pos = 0;
			retval = kernel_पढ़ो(पूर्णांकerpreter, bprm->buf,
					BINPRM_BUF_SIZE, &pos);
			अगर (unlikely(retval != BINPRM_BUF_SIZE)) अणु
				अगर (retval >= 0)
					retval = -ENOEXEC;
				जाओ error;
			पूर्ण

			पूर्णांकerp_params.hdr = *((काष्ठा elfhdr *) bprm->buf);
			अवरोध;

		हाल PT_LOAD:
#अगर_घोषित CONFIG_MMU
			अगर (exec_params.load_addr == 0)
				exec_params.load_addr = phdr->p_vaddr;
#पूर्ण_अगर
			अवरोध;
		पूर्ण

	पूर्ण

	अगर (is_स्थिरdisp(&exec_params.hdr))
		exec_params.flags |= ELF_FDPIC_FLAG_CONSTDISP;

	/* perक्रमm insanity checks on the पूर्णांकerpreter */
	अगर (पूर्णांकerpreter_name) अणु
		retval = -ELIBBAD;
		अगर (!is_elf(&पूर्णांकerp_params.hdr, पूर्णांकerpreter))
			जाओ error;

		पूर्णांकerp_params.flags = ELF_FDPIC_FLAG_PRESENT;

		/* पढ़ो the पूर्णांकerpreter's program header table */
		retval = elf_fdpic_fetch_phdrs(&पूर्णांकerp_params, पूर्णांकerpreter);
		अगर (retval < 0)
			जाओ error;
	पूर्ण

	stack_size = exec_params.stack_size;
	अगर (exec_params.flags & ELF_FDPIC_FLAG_EXEC_STACK)
		executable_stack = EXSTACK_ENABLE_X;
	अन्यथा अगर (exec_params.flags & ELF_FDPIC_FLAG_NOEXEC_STACK)
		executable_stack = EXSTACK_DISABLE_X;
	अन्यथा
		executable_stack = EXSTACK_DEFAULT;

	अगर (stack_size == 0) अणु
		stack_size = पूर्णांकerp_params.stack_size;
		अगर (पूर्णांकerp_params.flags & ELF_FDPIC_FLAG_EXEC_STACK)
			executable_stack = EXSTACK_ENABLE_X;
		अन्यथा अगर (पूर्णांकerp_params.flags & ELF_FDPIC_FLAG_NOEXEC_STACK)
			executable_stack = EXSTACK_DISABLE_X;
		अन्यथा
			executable_stack = EXSTACK_DEFAULT;
	पूर्ण

	retval = -ENOEXEC;
	अगर (stack_size == 0)
		stack_size = 131072UL; /* same as exec.c's शेष commit */

	अगर (is_स्थिरdisp(&पूर्णांकerp_params.hdr))
		पूर्णांकerp_params.flags |= ELF_FDPIC_FLAG_CONSTDISP;

	/* flush all traces of the currently running executable */
	retval = begin_new_exec(bprm);
	अगर (retval)
		जाओ error;

	/* there's now no turning back... the old userspace image is dead,
	 * defunct, deceased, etc.
	 */
	अगर (elf_check_fdpic(&exec_params.hdr))
		set_personality(PER_LINUX_FDPIC);
	अन्यथा
		set_personality(PER_LINUX);
	अगर (elf_पढ़ो_implies_exec(&exec_params.hdr, executable_stack))
		current->personality |= READ_IMPLIES_EXEC;

	setup_new_exec(bprm);

	set_binfmt(&elf_fdpic_क्रमmat);

	current->mm->start_code = 0;
	current->mm->end_code = 0;
	current->mm->start_stack = 0;
	current->mm->start_data = 0;
	current->mm->end_data = 0;
	current->mm->context.exec_fdpic_loadmap = 0;
	current->mm->context.पूर्णांकerp_fdpic_loadmap = 0;

#अगर_घोषित CONFIG_MMU
	elf_fdpic_arch_lay_out_mm(&exec_params,
				  &पूर्णांकerp_params,
				  &current->mm->start_stack,
				  &current->mm->start_brk);

	retval = setup_arg_pages(bprm, current->mm->start_stack,
				 executable_stack);
	अगर (retval < 0)
		जाओ error;
#अगर_घोषित ARCH_HAS_SETUP_ADDITIONAL_PAGES
	retval = arch_setup_additional_pages(bprm, !!पूर्णांकerpreter_name);
	अगर (retval < 0)
		जाओ error;
#पूर्ण_अगर
#पूर्ण_अगर

	/* load the executable and पूर्णांकerpreter पूर्णांकo memory */
	retval = elf_fdpic_map_file(&exec_params, bprm->file, current->mm,
				    "executable");
	अगर (retval < 0)
		जाओ error;

	अगर (पूर्णांकerpreter_name) अणु
		retval = elf_fdpic_map_file(&पूर्णांकerp_params, पूर्णांकerpreter,
					    current->mm, "interpreter");
		अगर (retval < 0) अणु
			prपूर्णांकk(KERN_ERR "Unable to load interpreter\n");
			जाओ error;
		पूर्ण

		allow_ग_लिखो_access(पूर्णांकerpreter);
		fput(पूर्णांकerpreter);
		पूर्णांकerpreter = शून्य;
	पूर्ण

#अगर_घोषित CONFIG_MMU
	अगर (!current->mm->start_brk)
		current->mm->start_brk = current->mm->end_data;

	current->mm->brk = current->mm->start_brk =
		PAGE_ALIGN(current->mm->start_brk);

#अन्यथा
	/* create a stack area and zero-size brk area */
	stack_size = (stack_size + PAGE_SIZE - 1) & PAGE_MASK;
	अगर (stack_size < PAGE_SIZE * 2)
		stack_size = PAGE_SIZE * 2;

	stack_prot = PROT_READ | PROT_WRITE;
	अगर (executable_stack == EXSTACK_ENABLE_X ||
	    (executable_stack == EXSTACK_DEFAULT && VM_STACK_FLAGS & VM_EXEC))
		stack_prot |= PROT_EXEC;

	current->mm->start_brk = vm_mmap(शून्य, 0, stack_size, stack_prot,
					 MAP_PRIVATE | MAP_ANONYMOUS |
					 MAP_UNINITIALIZED | MAP_GROWSDOWN,
					 0);

	अगर (IS_ERR_VALUE(current->mm->start_brk)) अणु
		retval = current->mm->start_brk;
		current->mm->start_brk = 0;
		जाओ error;
	पूर्ण

	current->mm->brk = current->mm->start_brk;
	current->mm->context.end_brk = current->mm->start_brk;
	current->mm->start_stack = current->mm->start_brk + stack_size;
#पूर्ण_अगर

	अगर (create_elf_fdpic_tables(bprm, current->mm,
				    &exec_params, &पूर्णांकerp_params) < 0)
		जाओ error;

	kdebug("- start_code  %lx", current->mm->start_code);
	kdebug("- end_code    %lx", current->mm->end_code);
	kdebug("- start_data  %lx", current->mm->start_data);
	kdebug("- end_data    %lx", current->mm->end_data);
	kdebug("- start_brk   %lx", current->mm->start_brk);
	kdebug("- brk         %lx", current->mm->brk);
	kdebug("- start_stack %lx", current->mm->start_stack);

#अगर_घोषित ELF_FDPIC_PLAT_INIT
	/*
	 * The ABI may specअगरy that certain रेजिस्टरs be set up in special
	 * ways (on i386 %edx is the address of a DT_FINI function, क्रम
	 * example.  This macro perक्रमms whatever initialization to
	 * the regs काष्ठाure is required.
	 */
	dynaddr = पूर्णांकerp_params.dynamic_addr ?: exec_params.dynamic_addr;
	ELF_FDPIC_PLAT_INIT(regs, exec_params.map_addr, पूर्णांकerp_params.map_addr,
			    dynaddr);
#पूर्ण_अगर

	finalize_exec(bprm);
	/* everything is now पढ़ोy... get the userspace context पढ़ोy to roll */
	entryaddr = पूर्णांकerp_params.entry_addr ?: exec_params.entry_addr;
	start_thपढ़ो(regs, entryaddr, current->mm->start_stack);

	retval = 0;

error:
	अगर (पूर्णांकerpreter) अणु
		allow_ग_लिखो_access(पूर्णांकerpreter);
		fput(पूर्णांकerpreter);
	पूर्ण
	kमुक्त(पूर्णांकerpreter_name);
	kमुक्त(exec_params.phdrs);
	kमुक्त(exec_params.loadmap);
	kमुक्त(पूर्णांकerp_params.phdrs);
	kमुक्त(पूर्णांकerp_params.loadmap);
	वापस retval;
पूर्ण

/*****************************************************************************/

#अगर_अघोषित ELF_BASE_PLATFORM
/*
 * AT_BASE_PLATFORM indicates the "real" hardware/microarchitecture.
 * If the arch defines ELF_BASE_PLATFORM (in यंत्र/elf.h), the value
 * will be copied to the user stack in the same manner as AT_PLATFORM.
 */
#घोषणा ELF_BASE_PLATFORM शून्य
#पूर्ण_अगर

/*
 * present useful inक्रमmation to the program by shovelling it onto the new
 * process's stack
 */
अटल पूर्णांक create_elf_fdpic_tables(काष्ठा linux_binprm *bprm,
				   काष्ठा mm_काष्ठा *mm,
				   काष्ठा elf_fdpic_params *exec_params,
				   काष्ठा elf_fdpic_params *पूर्णांकerp_params)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	अचिन्हित दीर्घ sp, csp, nitems;
	elf_caddr_t __user *argv, *envp;
	माप_प्रकार platक्रमm_len = 0, len;
	अक्षर *k_platक्रमm, *k_base_platक्रमm;
	अक्षर __user *u_platक्रमm, *u_base_platक्रमm, *p;
	पूर्णांक loop;
	पूर्णांक nr;	/* reset क्रम each csp adjusपंचांगent */
	अचिन्हित दीर्घ flags = 0;

#अगर_घोषित CONFIG_MMU
	/* In some हालs (e.g. Hyper-Thपढ़ोing), we want to aव्योम L1 evictions
	 * by the processes running on the same package. One thing we can करो is
	 * to shuffle the initial stack क्रम them, so we give the architecture
	 * an opportunity to करो so here.
	 */
	sp = arch_align_stack(bprm->p);
#अन्यथा
	sp = mm->start_stack;

	/* stack the program arguments and environment */
	अगर (transfer_args_to_stack(bprm, &sp) < 0)
		वापस -EFAULT;
	sp &= ~15;
#पूर्ण_अगर

	/*
	 * If this architecture has a platक्रमm capability string, copy it
	 * to userspace.  In some हालs (Sparc), this info is impossible
	 * क्रम userspace to get any other way, in others (i386) it is
	 * merely dअगरficult.
	 */
	k_platक्रमm = ELF_PLATFORM;
	u_platक्रमm = शून्य;

	अगर (k_platक्रमm) अणु
		platक्रमm_len = म_माप(k_platक्रमm) + 1;
		sp -= platक्रमm_len;
		u_platक्रमm = (अक्षर __user *) sp;
		अगर (copy_to_user(u_platक्रमm, k_platक्रमm, platक्रमm_len) != 0)
			वापस -EFAULT;
	पूर्ण

	/*
	 * If this architecture has a "base" platक्रमm capability
	 * string, copy it to userspace.
	 */
	k_base_platक्रमm = ELF_BASE_PLATFORM;
	u_base_platक्रमm = शून्य;

	अगर (k_base_platक्रमm) अणु
		platक्रमm_len = म_माप(k_base_platक्रमm) + 1;
		sp -= platक्रमm_len;
		u_base_platक्रमm = (अक्षर __user *) sp;
		अगर (copy_to_user(u_base_platक्रमm, k_base_platक्रमm, platक्रमm_len) != 0)
			वापस -EFAULT;
	पूर्ण

	sp &= ~7UL;

	/* stack the load map(s) */
	len = माप(काष्ठा elf32_fdpic_loadmap);
	len += माप(काष्ठा elf32_fdpic_loadseg) * exec_params->loadmap->nsegs;
	sp = (sp - len) & ~7UL;
	exec_params->map_addr = sp;

	अगर (copy_to_user((व्योम __user *) sp, exec_params->loadmap, len) != 0)
		वापस -EFAULT;

	current->mm->context.exec_fdpic_loadmap = (अचिन्हित दीर्घ) sp;

	अगर (पूर्णांकerp_params->loadmap) अणु
		len = माप(काष्ठा elf32_fdpic_loadmap);
		len += माप(काष्ठा elf32_fdpic_loadseg) *
			पूर्णांकerp_params->loadmap->nsegs;
		sp = (sp - len) & ~7UL;
		पूर्णांकerp_params->map_addr = sp;

		अगर (copy_to_user((व्योम __user *) sp, पूर्णांकerp_params->loadmap,
				 len) != 0)
			वापस -EFAULT;

		current->mm->context.पूर्णांकerp_fdpic_loadmap = (अचिन्हित दीर्घ) sp;
	पूर्ण

	/* क्रमce 16 byte _final_ alignment here क्रम generality */
#घोषणा DLINFO_ITEMS 15

	nitems = 1 + DLINFO_ITEMS + (k_platक्रमm ? 1 : 0) +
		(k_base_platक्रमm ? 1 : 0) + AT_VECTOR_SIZE_ARCH;

	अगर (bprm->have_execfd)
		nitems++;

	csp = sp;
	sp -= nitems * 2 * माप(अचिन्हित दीर्घ);
	sp -= (bprm->envc + 1) * माप(अक्षर *);	/* envv[] */
	sp -= (bprm->argc + 1) * माप(अक्षर *);	/* argv[] */
	sp -= 1 * माप(अचिन्हित दीर्घ);		/* argc */

	csp -= sp & 15UL;
	sp -= sp & 15UL;

	/* put the ELF पूर्णांकerpreter info on the stack */
#घोषणा NEW_AUX_ENT(id, val)						\
	करो अणु								\
		काष्ठा अणु अचिन्हित दीर्घ _id, _val; पूर्ण __user *ent, v;	\
									\
		ent = (व्योम __user *) csp;				\
		v._id = (id);						\
		v._val = (val);						\
		अगर (copy_to_user(ent + nr, &v, माप(v)))		\
			वापस -EFAULT;					\
		nr++;							\
	पूर्ण जबतक (0)

	nr = 0;
	csp -= 2 * माप(अचिन्हित दीर्घ);
	NEW_AUX_ENT(AT_शून्य, 0);
	अगर (k_platक्रमm) अणु
		nr = 0;
		csp -= 2 * माप(अचिन्हित दीर्घ);
		NEW_AUX_ENT(AT_PLATFORM,
			    (elf_addr_t) (अचिन्हित दीर्घ) u_platक्रमm);
	पूर्ण

	अगर (k_base_platक्रमm) अणु
		nr = 0;
		csp -= 2 * माप(अचिन्हित दीर्घ);
		NEW_AUX_ENT(AT_BASE_PLATFORM,
			    (elf_addr_t) (अचिन्हित दीर्घ) u_base_platक्रमm);
	पूर्ण

	अगर (bprm->have_execfd) अणु
		nr = 0;
		csp -= 2 * माप(अचिन्हित दीर्घ);
		NEW_AUX_ENT(AT_EXECFD, bprm->execfd);
	पूर्ण

	nr = 0;
	csp -= DLINFO_ITEMS * 2 * माप(अचिन्हित दीर्घ);
	NEW_AUX_ENT(AT_HWCAP,	ELF_HWCAP);
#अगर_घोषित ELF_HWCAP2
	NEW_AUX_ENT(AT_HWCAP2,	ELF_HWCAP2);
#पूर्ण_अगर
	NEW_AUX_ENT(AT_PAGESZ,	PAGE_SIZE);
	NEW_AUX_ENT(AT_CLKTCK,	CLOCKS_PER_SEC);
	NEW_AUX_ENT(AT_PHDR,	exec_params->ph_addr);
	NEW_AUX_ENT(AT_PHENT,	माप(काष्ठा elf_phdr));
	NEW_AUX_ENT(AT_PHNUM,	exec_params->hdr.e_phnum);
	NEW_AUX_ENT(AT_BASE,	पूर्णांकerp_params->elfhdr_addr);
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_PRESERVE_ARGV0)
		flags |= AT_FLAGS_PRESERVE_ARGV0;
	NEW_AUX_ENT(AT_FLAGS,	flags);
	NEW_AUX_ENT(AT_ENTRY,	exec_params->entry_addr);
	NEW_AUX_ENT(AT_UID,	(elf_addr_t) from_kuid_munged(cred->user_ns, cred->uid));
	NEW_AUX_ENT(AT_EUID,	(elf_addr_t) from_kuid_munged(cred->user_ns, cred->euid));
	NEW_AUX_ENT(AT_GID,	(elf_addr_t) from_kgid_munged(cred->user_ns, cred->gid));
	NEW_AUX_ENT(AT_EGID,	(elf_addr_t) from_kgid_munged(cred->user_ns, cred->egid));
	NEW_AUX_ENT(AT_SECURE,	bprm->secureexec);
	NEW_AUX_ENT(AT_EXECFN,	bprm->exec);

#अगर_घोषित ARCH_DLINFO
	nr = 0;
	csp -= AT_VECTOR_SIZE_ARCH * 2 * माप(अचिन्हित दीर्घ);

	/* ARCH_DLINFO must come last so platक्रमm specअगरic code can enक्रमce
	 * special alignment requirements on the AUXV अगर necessary (eg. PPC).
	 */
	ARCH_DLINFO;
#पूर्ण_अगर
#अघोषित NEW_AUX_ENT

	/* allocate room क्रम argv[] and envv[] */
	csp -= (bprm->envc + 1) * माप(elf_caddr_t);
	envp = (elf_caddr_t __user *) csp;
	csp -= (bprm->argc + 1) * माप(elf_caddr_t);
	argv = (elf_caddr_t __user *) csp;

	/* stack argc */
	csp -= माप(अचिन्हित दीर्घ);
	अगर (put_user(bprm->argc, (अचिन्हित दीर्घ __user *) csp))
		वापस -EFAULT;

	BUG_ON(csp != sp);

	/* fill in the argv[] array */
#अगर_घोषित CONFIG_MMU
	current->mm->arg_start = bprm->p;
#अन्यथा
	current->mm->arg_start = current->mm->start_stack -
		(MAX_ARG_PAGES * PAGE_SIZE - bprm->p);
#पूर्ण_अगर

	p = (अक्षर __user *) current->mm->arg_start;
	क्रम (loop = bprm->argc; loop > 0; loop--) अणु
		अगर (put_user((elf_caddr_t) p, argv++))
			वापस -EFAULT;
		len = strnlen_user(p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(शून्य, argv))
		वापस -EFAULT;
	current->mm->arg_end = (अचिन्हित दीर्घ) p;

	/* fill in the envv[] array */
	current->mm->env_start = (अचिन्हित दीर्घ) p;
	क्रम (loop = bprm->envc; loop > 0; loop--) अणु
		अगर (put_user((elf_caddr_t)(अचिन्हित दीर्घ) p, envp++))
			वापस -EFAULT;
		len = strnlen_user(p, MAX_ARG_STRLEN);
		अगर (!len || len > MAX_ARG_STRLEN)
			वापस -EINVAL;
		p += len;
	पूर्ण
	अगर (put_user(शून्य, envp))
		वापस -EFAULT;
	current->mm->env_end = (अचिन्हित दीर्घ) p;

	mm->start_stack = (अचिन्हित दीर्घ) sp;
	वापस 0;
पूर्ण

/*****************************************************************************/
/*
 * load the appropriate binary image (executable or पूर्णांकerpreter) पूर्णांकo memory
 * - we assume no MMU is available
 * - अगर no other PIC bits are set in params->hdr->e_flags
 *   - we assume that the LOADable segments in the binary are independently relocatable
 *   - we assume R/O executable segments are shareable
 * - अन्यथा
 *   - we assume the loadable parts of the image to require fixed displacement
 *   - the image is not shareable
 */
अटल पूर्णांक elf_fdpic_map_file(काष्ठा elf_fdpic_params *params,
			      काष्ठा file *file,
			      काष्ठा mm_काष्ठा *mm,
			      स्थिर अक्षर *what)
अणु
	काष्ठा elf32_fdpic_loadmap *loadmap;
#अगर_घोषित CONFIG_MMU
	काष्ठा elf32_fdpic_loadseg *mseg;
#पूर्ण_अगर
	काष्ठा elf32_fdpic_loadseg *seg;
	काष्ठा elf32_phdr *phdr;
	अचिन्हित दीर्घ load_addr, stop;
	अचिन्हित nloads, पंचांगp;
	माप_प्रकार size;
	पूर्णांक loop, ret;

	/* allocate a load map table */
	nloads = 0;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++)
		अगर (params->phdrs[loop].p_type == PT_LOAD)
			nloads++;

	अगर (nloads == 0)
		वापस -ELIBBAD;

	size = माप(*loadmap) + nloads * माप(*seg);
	loadmap = kzalloc(size, GFP_KERNEL);
	अगर (!loadmap)
		वापस -ENOMEM;

	params->loadmap = loadmap;

	loadmap->version = ELF32_FDPIC_LOADMAP_VERSION;
	loadmap->nsegs = nloads;

	load_addr = params->load_addr;
	seg = loadmap->segs;

	/* map the requested LOADs पूर्णांकo the memory space */
	चयन (params->flags & ELF_FDPIC_FLAG_ARRANGEMENT) अणु
	हाल ELF_FDPIC_FLAG_CONSTDISP:
	हाल ELF_FDPIC_FLAG_CONTIGUOUS:
#अगर_अघोषित CONFIG_MMU
		ret = elf_fdpic_map_file_स्थिरdisp_on_uclinux(params, file, mm);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
#पूर्ण_अगर
	शेष:
		ret = elf_fdpic_map_file_by_direct_mmap(params, file, mm);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	पूर्ण

	/* map the entry poपूर्णांक */
	अगर (params->hdr.e_entry) अणु
		seg = loadmap->segs;
		क्रम (loop = loadmap->nsegs; loop > 0; loop--, seg++) अणु
			अगर (params->hdr.e_entry >= seg->p_vaddr &&
			    params->hdr.e_entry < seg->p_vaddr + seg->p_memsz) अणु
				params->entry_addr =
					(params->hdr.e_entry - seg->p_vaddr) +
					seg->addr;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* determine where the program header table has wound up अगर mapped */
	stop = params->hdr.e_phoff;
	stop += params->hdr.e_phnum * माप (काष्ठा elf_phdr);
	phdr = params->phdrs;

	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अगर (phdr->p_type != PT_LOAD)
			जारी;

		अगर (phdr->p_offset > params->hdr.e_phoff ||
		    phdr->p_offset + phdr->p_filesz < stop)
			जारी;

		seg = loadmap->segs;
		क्रम (loop = loadmap->nsegs; loop > 0; loop--, seg++) अणु
			अगर (phdr->p_vaddr >= seg->p_vaddr &&
			    phdr->p_vaddr + phdr->p_filesz <=
			    seg->p_vaddr + seg->p_memsz) अणु
				params->ph_addr =
					(phdr->p_vaddr - seg->p_vaddr) +
					seg->addr +
					params->hdr.e_phoff - phdr->p_offset;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* determine where the dynamic section has wound up अगर there is one */
	phdr = params->phdrs;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अगर (phdr->p_type != PT_DYNAMIC)
			जारी;

		seg = loadmap->segs;
		क्रम (loop = loadmap->nsegs; loop > 0; loop--, seg++) अणु
			अगर (phdr->p_vaddr >= seg->p_vaddr &&
			    phdr->p_vaddr + phdr->p_memsz <=
			    seg->p_vaddr + seg->p_memsz) अणु
				Elf32_Dyn __user *dyn;
				Elf32_Sword d_tag;

				params->dynamic_addr =
					(phdr->p_vaddr - seg->p_vaddr) +
					seg->addr;

				/* check the dynamic section contains at least
				 * one item, and that the last item is a शून्य
				 * entry */
				अगर (phdr->p_memsz == 0 ||
				    phdr->p_memsz % माप(Elf32_Dyn) != 0)
					जाओ dynamic_error;

				पंचांगp = phdr->p_memsz / माप(Elf32_Dyn);
				dyn = (Elf32_Dyn __user *)params->dynamic_addr;
				अगर (get_user(d_tag, &dyn[पंचांगp - 1].d_tag) ||
				    d_tag != 0)
					जाओ dynamic_error;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* now elide adjacent segments in the load map on MMU linux
	 * - on uClinux the holes between may actually be filled with प्रणाली
	 *   stuff or stuff from other processes
	 */
#अगर_घोषित CONFIG_MMU
	nloads = loadmap->nsegs;
	mseg = loadmap->segs;
	seg = mseg + 1;
	क्रम (loop = 1; loop < nloads; loop++) अणु
		/* see अगर we have a candidate क्रम merging */
		अगर (seg->p_vaddr - mseg->p_vaddr == seg->addr - mseg->addr) अणु
			load_addr = PAGE_ALIGN(mseg->addr + mseg->p_memsz);
			अगर (load_addr == (seg->addr & PAGE_MASK)) अणु
				mseg->p_memsz +=
					load_addr -
					(mseg->addr + mseg->p_memsz);
				mseg->p_memsz += seg->addr & ~PAGE_MASK;
				mseg->p_memsz += seg->p_memsz;
				loadmap->nsegs--;
				जारी;
			पूर्ण
		पूर्ण

		mseg++;
		अगर (mseg != seg)
			*mseg = *seg;
	पूर्ण
#पूर्ण_अगर

	kdebug("Mapped Object [%s]:", what);
	kdebug("- elfhdr   : %lx", params->elfhdr_addr);
	kdebug("- entry    : %lx", params->entry_addr);
	kdebug("- PHDR[]   : %lx", params->ph_addr);
	kdebug("- DYNAMIC[]: %lx", params->dynamic_addr);
	seg = loadmap->segs;
	क्रम (loop = 0; loop < loadmap->nsegs; loop++, seg++)
		kdebug("- LOAD[%d] : %08x-%08x [va=%x ms=%x]",
		       loop,
		       seg->addr, seg->addr + seg->p_memsz - 1,
		       seg->p_vaddr, seg->p_memsz);

	वापस 0;

dynamic_error:
	prपूर्णांकk("ELF FDPIC %s with invalid DYNAMIC section (inode=%lu)\n",
	       what, file_inode(file)->i_ino);
	वापस -ELIBBAD;
पूर्ण

/*****************************************************************************/
/*
 * map a file with स्थिरant displacement under uClinux
 */
#अगर_अघोषित CONFIG_MMU
अटल पूर्णांक elf_fdpic_map_file_स्थिरdisp_on_uclinux(
	काष्ठा elf_fdpic_params *params,
	काष्ठा file *file,
	काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा elf32_fdpic_loadseg *seg;
	काष्ठा elf32_phdr *phdr;
	अचिन्हित दीर्घ load_addr, base = अच_दीर्घ_उच्च, top = 0, maddr = 0, mflags;
	पूर्णांक loop, ret;

	load_addr = params->load_addr;
	seg = params->loadmap->segs;

	/* determine the bounds of the contiguous overall allocation we must
	 * make */
	phdr = params->phdrs;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अगर (params->phdrs[loop].p_type != PT_LOAD)
			जारी;

		अगर (base > phdr->p_vaddr)
			base = phdr->p_vaddr;
		अगर (top < phdr->p_vaddr + phdr->p_memsz)
			top = phdr->p_vaddr + phdr->p_memsz;
	पूर्ण

	/* allocate one big anon block क्रम everything */
	mflags = MAP_PRIVATE;
	अगर (params->flags & ELF_FDPIC_FLAG_EXECUTABLE)
		mflags |= MAP_EXECUTABLE;

	maddr = vm_mmap(शून्य, load_addr, top - base,
			PROT_READ | PROT_WRITE | PROT_EXEC, mflags, 0);
	अगर (IS_ERR_VALUE(maddr))
		वापस (पूर्णांक) maddr;

	अगर (load_addr != 0)
		load_addr += PAGE_ALIGN(top - base);

	/* and then load the file segments पूर्णांकo it */
	phdr = params->phdrs;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अगर (params->phdrs[loop].p_type != PT_LOAD)
			जारी;

		seg->addr = maddr + (phdr->p_vaddr - base);
		seg->p_vaddr = phdr->p_vaddr;
		seg->p_memsz = phdr->p_memsz;

		ret = पढ़ो_code(file, seg->addr, phdr->p_offset,
				       phdr->p_filesz);
		अगर (ret < 0)
			वापस ret;

		/* map the ELF header address अगर in this segment */
		अगर (phdr->p_offset == 0)
			params->elfhdr_addr = seg->addr;

		/* clear any space allocated but not loaded */
		अगर (phdr->p_filesz < phdr->p_memsz) अणु
			अगर (clear_user((व्योम *) (seg->addr + phdr->p_filesz),
				       phdr->p_memsz - phdr->p_filesz))
				वापस -EFAULT;
		पूर्ण

		अगर (mm) अणु
			अगर (phdr->p_flags & PF_X) अणु
				अगर (!mm->start_code) अणु
					mm->start_code = seg->addr;
					mm->end_code = seg->addr +
						phdr->p_memsz;
				पूर्ण
			पूर्ण अन्यथा अगर (!mm->start_data) अणु
				mm->start_data = seg->addr;
				mm->end_data = seg->addr + phdr->p_memsz;
			पूर्ण
		पूर्ण

		seg++;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*****************************************************************************/
/*
 * map a binary by direct mmap() of the inभागidual PT_LOAD segments
 */
अटल पूर्णांक elf_fdpic_map_file_by_direct_mmap(काष्ठा elf_fdpic_params *params,
					     काष्ठा file *file,
					     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा elf32_fdpic_loadseg *seg;
	काष्ठा elf32_phdr *phdr;
	अचिन्हित दीर्घ load_addr, delta_vaddr;
	पूर्णांक loop, dvset;

	load_addr = params->load_addr;
	delta_vaddr = 0;
	dvset = 0;

	seg = params->loadmap->segs;

	/* deal with each load segment separately */
	phdr = params->phdrs;
	क्रम (loop = 0; loop < params->hdr.e_phnum; loop++, phdr++) अणु
		अचिन्हित दीर्घ maddr, disp, excess, excess1;
		पूर्णांक prot = 0, flags;

		अगर (phdr->p_type != PT_LOAD)
			जारी;

		kdebug("[LOAD] va=%lx of=%lx fs=%lx ms=%lx",
		       (अचिन्हित दीर्घ) phdr->p_vaddr,
		       (अचिन्हित दीर्घ) phdr->p_offset,
		       (अचिन्हित दीर्घ) phdr->p_filesz,
		       (अचिन्हित दीर्घ) phdr->p_memsz);

		/* determine the mapping parameters */
		अगर (phdr->p_flags & PF_R) prot |= PROT_READ;
		अगर (phdr->p_flags & PF_W) prot |= PROT_WRITE;
		अगर (phdr->p_flags & PF_X) prot |= PROT_EXEC;

		flags = MAP_PRIVATE | MAP_DENYWRITE;
		अगर (params->flags & ELF_FDPIC_FLAG_EXECUTABLE)
			flags |= MAP_EXECUTABLE;

		maddr = 0;

		चयन (params->flags & ELF_FDPIC_FLAG_ARRANGEMENT) अणु
		हाल ELF_FDPIC_FLAG_INDEPENDENT:
			/* PT_LOADs are independently locatable */
			अवरोध;

		हाल ELF_FDPIC_FLAG_HONOURVADDR:
			/* the specअगरied भव address must be honoured */
			maddr = phdr->p_vaddr;
			flags |= MAP_FIXED;
			अवरोध;

		हाल ELF_FDPIC_FLAG_CONSTDISP:
			/* स्थिरant displacement
			 * - can be mapped anywhere, but must be mapped as a
			 *   unit
			 */
			अगर (!dvset) अणु
				maddr = load_addr;
				delta_vaddr = phdr->p_vaddr;
				dvset = 1;
			पूर्ण अन्यथा अणु
				maddr = load_addr + phdr->p_vaddr - delta_vaddr;
				flags |= MAP_FIXED;
			पूर्ण
			अवरोध;

		हाल ELF_FDPIC_FLAG_CONTIGUOUS:
			/* contiguity handled later */
			अवरोध;

		शेष:
			BUG();
		पूर्ण

		maddr &= PAGE_MASK;

		/* create the mapping */
		disp = phdr->p_vaddr & ~PAGE_MASK;
		maddr = vm_mmap(file, maddr, phdr->p_memsz + disp, prot, flags,
				phdr->p_offset - disp);

		kdebug("mmap[%d] <file> sz=%lx pr=%x fl=%x of=%lx --> %08lx",
		       loop, phdr->p_memsz + disp, prot, flags,
		       phdr->p_offset - disp, maddr);

		अगर (IS_ERR_VALUE(maddr))
			वापस (पूर्णांक) maddr;

		अगर ((params->flags & ELF_FDPIC_FLAG_ARRANGEMENT) ==
		    ELF_FDPIC_FLAG_CONTIGUOUS)
			load_addr += PAGE_ALIGN(phdr->p_memsz + disp);

		seg->addr = maddr + disp;
		seg->p_vaddr = phdr->p_vaddr;
		seg->p_memsz = phdr->p_memsz;

		/* map the ELF header address अगर in this segment */
		अगर (phdr->p_offset == 0)
			params->elfhdr_addr = seg->addr;

		/* clear the bit between beginning of mapping and beginning of
		 * PT_LOAD */
		अगर (prot & PROT_WRITE && disp > 0) अणु
			kdebug("clear[%d] ad=%lx sz=%lx", loop, maddr, disp);
			अगर (clear_user((व्योम __user *) maddr, disp))
				वापस -EFAULT;
			maddr += disp;
		पूर्ण

		/* clear any space allocated but not loaded
		 * - on uClinux we can just clear the lot
		 * - on MMU linux we'll get a SIGBUS beyond the last page
		 *   extant in the file
		 */
		excess = phdr->p_memsz - phdr->p_filesz;
		excess1 = PAGE_SIZE - ((maddr + phdr->p_filesz) & ~PAGE_MASK);

#अगर_घोषित CONFIG_MMU
		अगर (excess > excess1) अणु
			अचिन्हित दीर्घ xaddr = maddr + phdr->p_filesz + excess1;
			अचिन्हित दीर्घ xmaddr;

			flags |= MAP_FIXED | MAP_ANONYMOUS;
			xmaddr = vm_mmap(शून्य, xaddr, excess - excess1,
					 prot, flags, 0);

			kdebug("mmap[%d] <anon>"
			       " ad=%lx sz=%lx pr=%x fl=%x of=0 --> %08lx",
			       loop, xaddr, excess - excess1, prot, flags,
			       xmaddr);

			अगर (xmaddr != xaddr)
				वापस -ENOMEM;
		पूर्ण

		अगर (prot & PROT_WRITE && excess1 > 0) अणु
			kdebug("clear[%d] ad=%lx sz=%lx",
			       loop, maddr + phdr->p_filesz, excess1);
			अगर (clear_user((व्योम __user *) maddr + phdr->p_filesz,
				       excess1))
				वापस -EFAULT;
		पूर्ण

#अन्यथा
		अगर (excess > 0) अणु
			kdebug("clear[%d] ad=%lx sz=%lx",
			       loop, maddr + phdr->p_filesz, excess);
			अगर (clear_user((व्योम *) maddr + phdr->p_filesz, excess))
				वापस -EFAULT;
		पूर्ण
#पूर्ण_अगर

		अगर (mm) अणु
			अगर (phdr->p_flags & PF_X) अणु
				अगर (!mm->start_code) अणु
					mm->start_code = maddr;
					mm->end_code = maddr + phdr->p_memsz;
				पूर्ण
			पूर्ण अन्यथा अगर (!mm->start_data) अणु
				mm->start_data = maddr;
				mm->end_data = maddr + phdr->p_memsz;
			पूर्ण
		पूर्ण

		seg++;
	पूर्ण

	वापस 0;
पूर्ण

/*****************************************************************************/
/*
 * ELF-FDPIC core dumper
 *
 * Modelled on fs/exec.c:aout_core_dump()
 * Jeremy Fitzhardinge <jeremy@sw.oz.au>
 *
 * Modelled on fs/binfmt_elf.c core dumper
 */
#अगर_घोषित CONFIG_ELF_CORE

काष्ठा elf_prstatus_fdpic
अणु
	काष्ठा elf_prstatus_common	common;
	elf_gregset_t pr_reg;	/* GP रेजिस्टरs */
	/* When using FDPIC, the loadmap addresses need to be communicated
	 * to GDB in order क्रम GDB to करो the necessary relocations.  The
	 * fields (below) used to communicate this inक्रमmation are placed
	 * immediately after ``pr_reg'', so that the loadmap addresses may
	 * be viewed as part of the रेजिस्टर set अगर so desired.
	 */
	अचिन्हित दीर्घ pr_exec_fdpic_loadmap;
	अचिन्हित दीर्घ pr_पूर्णांकerp_fdpic_loadmap;
	पूर्णांक pr_fpvalid;		/* True अगर math co-processor being used.  */
पूर्ण;

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

/* #घोषणा DEBUG */

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

अटल अंतरभूत व्योम fill_elf_fdpic_header(काष्ठा elfhdr *elf, पूर्णांक segs)
अणु
	स_नकल(elf->e_ident, ELFMAG, SELFMAG);
	elf->e_ident[EI_CLASS] = ELF_CLASS;
	elf->e_ident[EI_DATA] = ELF_DATA;
	elf->e_ident[EI_VERSION] = EV_CURRENT;
	elf->e_ident[EI_OSABI] = ELF_OSABI;
	स_रखो(elf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);

	elf->e_type = ET_CORE;
	elf->e_machine = ELF_ARCH;
	elf->e_version = EV_CURRENT;
	elf->e_entry = 0;
	elf->e_phoff = माप(काष्ठा elfhdr);
	elf->e_shoff = 0;
	elf->e_flags = ELF_FDPIC_CORE_EFLAGS;
	elf->e_ehsize = माप(काष्ठा elfhdr);
	elf->e_phentsize = माप(काष्ठा elf_phdr);
	elf->e_phnum = segs;
	elf->e_shentsize = 0;
	elf->e_shnum = 0;
	elf->e_shstrndx = 0;
	वापस;
पूर्ण

अटल अंतरभूत व्योम fill_elf_note_phdr(काष्ठा elf_phdr *phdr, पूर्णांक sz, loff_t offset)
अणु
	phdr->p_type = PT_NOTE;
	phdr->p_offset = offset;
	phdr->p_vaddr = 0;
	phdr->p_paddr = 0;
	phdr->p_filesz = sz;
	phdr->p_memsz = 0;
	phdr->p_flags = 0;
	phdr->p_align = 0;
	वापस;
पूर्ण

अटल अंतरभूत व्योम fill_note(काष्ठा memelfnote *note, स्थिर अक्षर *name, पूर्णांक type,
		अचिन्हित पूर्णांक sz, व्योम *data)
अणु
	note->name = name;
	note->type = type;
	note->datasz = sz;
	note->data = data;
	वापस;
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
		len = ELF_PRARGSZ - 1;
	अगर (copy_from_user(&psinfo->pr_psargs,
		           (स्थिर अक्षर __user *) mm->arg_start, len))
		वापस -EFAULT;
	क्रम (i = 0; i < len; i++)
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

/* Here is the काष्ठाure in which status of each thपढ़ो is captured. */
काष्ठा elf_thपढ़ो_status
अणु
	काष्ठा elf_thपढ़ो_status *next;
	काष्ठा elf_prstatus_fdpic prstatus;	/* NT_PRSTATUS */
	elf_fpregset_t fpu;		/* NT_PRFPREG */
	काष्ठा memelfnote notes[2];
	पूर्णांक num_notes;
पूर्ण;

/*
 * In order to add the specअगरic thपढ़ो inक्रमmation क्रम the elf file क्रमmat,
 * we need to keep a linked list of every thपढ़ो's pr_status and then create
 * a single section क्रम them in the final core file.
 */
अटल काष्ठा elf_thपढ़ो_status *elf_dump_thपढ़ो_status(दीर्घ signr, काष्ठा task_काष्ठा *p, पूर्णांक *sz)
अणु
	स्थिर काष्ठा user_regset_view *view = task_user_regset_view(p);
	काष्ठा elf_thपढ़ो_status *t;
	पूर्णांक i, ret;

	t = kzalloc(माप(काष्ठा elf_thपढ़ो_status), GFP_KERNEL);
	अगर (!t)
		वापस t;

	fill_prstatus(&t->prstatus.common, p, signr);
	t->prstatus.pr_exec_fdpic_loadmap = p->mm->context.exec_fdpic_loadmap;
	t->prstatus.pr_पूर्णांकerp_fdpic_loadmap = p->mm->context.पूर्णांकerp_fdpic_loadmap;
	regset_get(p, &view->regsets[0],
		   माप(t->prstatus.pr_reg), &t->prstatus.pr_reg);

	fill_note(&t->notes[0], "CORE", NT_PRSTATUS, माप(t->prstatus),
		  &t->prstatus);
	t->num_notes++;
	*sz += notesize(&t->notes[0]);

	क्रम (i = 1; i < view->n; ++i) अणु
		स्थिर काष्ठा user_regset *regset = &view->regsets[i];
		अगर (regset->core_note_type != NT_PRFPREG)
			जारी;
		अगर (regset->active && regset->active(p, regset) <= 0)
			जारी;
		ret = regset_get(p, regset, माप(t->fpu), &t->fpu);
		अगर (ret >= 0)
			t->prstatus.pr_fpvalid = 1;
		अवरोध;
	पूर्ण

	अगर (t->prstatus.pr_fpvalid) अणु
		fill_note(&t->notes[1], "CORE", NT_PRFPREG, माप(t->fpu),
			  &t->fpu);
		t->num_notes++;
		*sz += notesize(&t->notes[1]);
	पूर्ण
	वापस t;
पूर्ण

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
 * dump the segments क्रम an MMU process
 */
अटल bool elf_fdpic_dump_segments(काष्ठा coredump_params *cprm,
				    काष्ठा core_vma_metadata *vma_meta,
				    पूर्णांक vma_count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < vma_count; i++) अणु
		काष्ठा core_vma_metadata *meta = vma_meta + i;

		अगर (!dump_user_range(cprm, meta->start, meta->dump_size))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Actual dumper
 *
 * This is a two-pass process; first we find the offsets of the bits,
 * and then they are actually written out.  If we run out of core limit
 * we just truncate.
 */
अटल पूर्णांक elf_fdpic_core_dump(काष्ठा coredump_params *cprm)
अणु
	पूर्णांक has_dumped = 0;
	पूर्णांक vma_count, segs;
	पूर्णांक i;
	काष्ठा elfhdr *elf = शून्य;
	loff_t offset = 0, dataoff;
	काष्ठा memelfnote psinfo_note, auxv_note;
	काष्ठा elf_prpsinfo *psinfo = शून्य;	/* NT_PRPSINFO */
	काष्ठा elf_thपढ़ो_status *thपढ़ो_list = शून्य;
	पूर्णांक thपढ़ो_status_size = 0;
	elf_addr_t *auxv;
	काष्ठा elf_phdr *phdr4note = शून्य;
	काष्ठा elf_shdr *shdr4extnum = शून्य;
	Elf_Half e_phnum;
	elf_addr_t e_shoff;
	काष्ठा core_thपढ़ो *ct;
	काष्ठा elf_thपढ़ो_status *पंचांगp;
	काष्ठा core_vma_metadata *vma_meta = शून्य;
	माप_प्रकार vma_data_size;

	/* alloc memory क्रम large data काष्ठाures: too large to be on stack */
	elf = kदो_स्मृति(माप(*elf), GFP_KERNEL);
	अगर (!elf)
		जाओ end_coredump;
	psinfo = kदो_स्मृति(माप(*psinfo), GFP_KERNEL);
	अगर (!psinfo)
		जाओ end_coredump;

	अगर (dump_vma_snapshot(cprm, &vma_count, &vma_meta, &vma_data_size))
		जाओ end_coredump;

	क्रम (ct = current->mm->core_state->dumper.next;
					ct; ct = ct->next) अणु
		पंचांगp = elf_dump_thपढ़ो_status(cprm->siginfo->si_signo,
					     ct->task, &thपढ़ो_status_size);
		अगर (!पंचांगp)
			जाओ end_coredump;

		पंचांगp->next = thपढ़ो_list;
		thपढ़ो_list = पंचांगp;
	पूर्ण

	/* now collect the dump क्रम the current */
	पंचांगp = elf_dump_thपढ़ो_status(cprm->siginfo->si_signo,
				     current, &thपढ़ो_status_size);
	अगर (!पंचांगp)
		जाओ end_coredump;
	पंचांगp->next = thपढ़ो_list;
	thपढ़ो_list = पंचांगp;

	segs = vma_count + elf_core_extra_phdrs();

	/* क्रम notes section */
	segs++;

	/* If segs > PN_XNUM(0xffff), then e_phnum overflows. To aव्योम
	 * this, kernel supports extended numbering. Have a look at
	 * include/linux/elf.h क्रम further inक्रमmation. */
	e_phnum = segs > PN_XNUM ? PN_XNUM : segs;

	/* Set up header */
	fill_elf_fdpic_header(elf, e_phnum);

	has_dumped = 1;
	/*
	 * Set up the notes in similar क्रमm to SVR4 core dumps made
	 * with info from their /proc.
	 */

	fill_psinfo(psinfo, current->group_leader, current->mm);
	fill_note(&psinfo_note, "CORE", NT_PRPSINFO, माप(*psinfo), psinfo);
	thपढ़ो_status_size += notesize(&psinfo_note);

	auxv = (elf_addr_t *) current->mm->saved_auxv;
	i = 0;
	करो
		i += 2;
	जबतक (auxv[i - 2] != AT_शून्य);
	fill_note(&auxv_note, "CORE", NT_AUXV, i * माप(elf_addr_t), auxv);
	thपढ़ो_status_size += notesize(&auxv_note);

	offset = माप(*elf);				/* Elf header */
	offset += segs * माप(काष्ठा elf_phdr);	/* Program headers */

	/* Write notes phdr entry */
	phdr4note = kदो_स्मृति(माप(*phdr4note), GFP_KERNEL);
	अगर (!phdr4note)
		जाओ end_coredump;

	fill_elf_note_phdr(phdr4note, thपढ़ो_status_size, offset);
	offset += thपढ़ो_status_size;

	/* Page-align dumped data */
	dataoff = offset = roundup(offset, ELF_EXEC_PAGESIZE);

	offset += vma_data_size;
	offset += elf_core_extra_data_size();
	e_shoff = offset;

	अगर (e_phnum == PN_XNUM) अणु
		shdr4extnum = kदो_स्मृति(माप(*shdr4extnum), GFP_KERNEL);
		अगर (!shdr4extnum)
			जाओ end_coredump;
		fill_extnum_info(elf, shdr4extnum, e_shoff, segs);
	पूर्ण

	offset = dataoff;

	अगर (!dump_emit(cprm, elf, माप(*elf)))
		जाओ end_coredump;

	अगर (!dump_emit(cprm, phdr4note, माप(*phdr4note)))
		जाओ end_coredump;

	/* ग_लिखो program headers क्रम segments dump */
	क्रम (i = 0; i < vma_count; i++) अणु
		काष्ठा core_vma_metadata *meta = vma_meta + i;
		काष्ठा elf_phdr phdr;
		माप_प्रकार sz;

		sz = meta->end - meta->start;

		phdr.p_type = PT_LOAD;
		phdr.p_offset = offset;
		phdr.p_vaddr = meta->start;
		phdr.p_paddr = 0;
		phdr.p_filesz = meta->dump_size;
		phdr.p_memsz = sz;
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
	अगर (!ग_लिखोnote(thपढ़ो_list->notes, cprm))
		जाओ end_coredump;
	अगर (!ग_लिखोnote(&psinfo_note, cprm))
		जाओ end_coredump;
	अगर (!ग_लिखोnote(&auxv_note, cprm))
		जाओ end_coredump;
	क्रम (i = 1; i < thपढ़ो_list->num_notes; i++)
		अगर (!ग_लिखोnote(thपढ़ो_list->notes + i, cprm))
			जाओ end_coredump;

	/* ग_लिखो out the thपढ़ो status notes section */
	क्रम (पंचांगp = thपढ़ो_list->next; पंचांगp; पंचांगp = पंचांगp->next) अणु
		क्रम (i = 0; i < पंचांगp->num_notes; i++)
			अगर (!ग_लिखोnote(&पंचांगp->notes[i], cprm))
				जाओ end_coredump;
	पूर्ण

	dump_skip_to(cprm, dataoff);

	अगर (!elf_fdpic_dump_segments(cprm, vma_meta, vma_count))
		जाओ end_coredump;

	अगर (!elf_core_ग_लिखो_extra_data(cprm))
		जाओ end_coredump;

	अगर (e_phnum == PN_XNUM) अणु
		अगर (!dump_emit(cprm, shdr4extnum, माप(*shdr4extnum)))
			जाओ end_coredump;
	पूर्ण

	अगर (cprm->file->f_pos != offset) अणु
		/* Sanity check */
		prपूर्णांकk(KERN_WARNING
		       "elf_core_dump: file->f_pos (%lld) != offset (%lld)\n",
		       cprm->file->f_pos, offset);
	पूर्ण

end_coredump:
	जबतक (thपढ़ो_list) अणु
		पंचांगp = thपढ़ो_list;
		thपढ़ो_list = thपढ़ो_list->next;
		kमुक्त(पंचांगp);
	पूर्ण
	kvमुक्त(vma_meta);
	kमुक्त(phdr4note);
	kमुक्त(elf);
	kमुक्त(psinfo);
	kमुक्त(shdr4extnum);
	वापस has_dumped;
पूर्ण

#पूर्ण_अगर		/* CONFIG_ELF_CORE */
