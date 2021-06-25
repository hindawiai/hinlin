<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  a.out loader क्रम x86-64
 *
 *  Copyright (C) 1991, 1992, 1996  Linus Torvalds
 *  Hacked together by Andi Kleen
 */

#समावेश <linux/module.h>

#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/a.out.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/personality.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/user32.h>
#समावेश <यंत्र/ia32.h>

#अघोषित WARN_OLD

अटल पूर्णांक load_aout_binary(काष्ठा linux_binprm *);
अटल पूर्णांक load_aout_library(काष्ठा file *);

अटल काष्ठा linux_binfmt aout_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_aout_binary,
	.load_shlib	= load_aout_library,
पूर्ण;

अटल पूर्णांक set_brk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start = PAGE_ALIGN(start);
	end = PAGE_ALIGN(end);
	अगर (end <= start)
		वापस 0;
	वापस vm_brk(start, end - start);
पूर्ण


/*
 * create_aout_tables() parses the env- and arg-strings in new user
 * memory and creates the poपूर्णांकer tables from them, and माला_दो their
 * addresses on the "stack", वापसing the new stack poपूर्णांकer value.
 */
अटल u32 __user *create_aout_tables(अक्षर __user *p, काष्ठा linux_binprm *bprm)
अणु
	u32 __user *argv, *envp, *sp;
	पूर्णांक argc = bprm->argc, envc = bprm->envc;

	sp = (u32 __user *) ((-(अचिन्हित दीर्घ)माप(u32)) & (अचिन्हित दीर्घ) p);
	sp -= envc+1;
	envp = sp;
	sp -= argc+1;
	argv = sp;
	put_user((अचिन्हित दीर्घ) envp, --sp);
	put_user((अचिन्हित दीर्घ) argv, --sp);
	put_user(argc, --sp);
	current->mm->arg_start = (अचिन्हित दीर्घ) p;
	जबतक (argc-- > 0) अणु
		अक्षर c;

		put_user((u32)(अचिन्हित दीर्घ)p, argv++);
		करो अणु
			get_user(c, p++);
		पूर्ण जबतक (c);
	पूर्ण
	put_user(0, argv);
	current->mm->arg_end = current->mm->env_start = (अचिन्हित दीर्घ) p;
	जबतक (envc-- > 0) अणु
		अक्षर c;

		put_user((u32)(अचिन्हित दीर्घ)p, envp++);
		करो अणु
			get_user(c, p++);
		पूर्ण जबतक (c);
	पूर्ण
	put_user(0, envp);
	current->mm->env_end = (अचिन्हित दीर्घ) p;
	वापस sp;
पूर्ण

/*
 * These are the functions used to load a.out style executables and shared
 * libraries.  There is no binary dependent code anywhere अन्यथा.
 */
अटल पूर्णांक load_aout_binary(काष्ठा linux_binprm *bprm)
अणु
	अचिन्हित दीर्घ error, fd_offset, rlim;
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा exec ex;
	पूर्णांक retval;

	ex = *((काष्ठा exec *) bprm->buf);		/* exec-header */
	अगर ((N_MAGIC(ex) != ZMAGIC && N_MAGIC(ex) != OMAGIC &&
	     N_MAGIC(ex) != QMAGIC && N_MAGIC(ex) != NMAGIC) ||
	    N_TRSIZE(ex) || N_DRSIZE(ex) ||
	    i_size_पढ़ो(file_inode(bprm->file)) <
	    ex.a_text+ex.a_data+N_SYMSIZE(ex)+N_TXTOFF(ex)) अणु
		वापस -ENOEXEC;
	पूर्ण

	fd_offset = N_TXTOFF(ex);

	/* Check initial limits. This aव्योमs letting people circumvent
	 * size limits imposed on them by creating programs with large
	 * arrays in the data or bss.
	 */
	rlim = rlimit(RLIMIT_DATA);
	अगर (rlim >= RLIM_अनन्त)
		rlim = ~0;
	अगर (ex.a_data + ex.a_bss > rlim)
		वापस -ENOMEM;

	/* Flush all traces of the currently running executable */
	retval = begin_new_exec(bprm);
	अगर (retval)
		वापस retval;

	/* OK, This is the poपूर्णांक of no वापस */
	set_personality(PER_LINUX);
	set_personality_ia32(false);

	setup_new_exec(bprm);

	regs->cs = __USER32_CS;
	regs->r8 = regs->r9 = regs->r10 = regs->r11 = regs->r12 =
		regs->r13 = regs->r14 = regs->r15 = 0;

	current->mm->end_code = ex.a_text +
		(current->mm->start_code = N_TXTADDR(ex));
	current->mm->end_data = ex.a_data +
		(current->mm->start_data = N_DATADDR(ex));
	current->mm->brk = ex.a_bss +
		(current->mm->start_brk = N_BSSADDR(ex));

	retval = setup_arg_pages(bprm, IA32_STACK_TOP, EXSTACK_DEFAULT);
	अगर (retval < 0)
		वापस retval;

	अगर (N_MAGIC(ex) == OMAGIC) अणु
		अचिन्हित दीर्घ text_addr, map_size;

		text_addr = N_TXTADDR(ex);
		map_size = ex.a_text+ex.a_data;

		error = vm_brk(text_addr & PAGE_MASK, map_size);

		अगर (error)
			वापस error;

		error = पढ़ो_code(bprm->file, text_addr, 32,
				  ex.a_text + ex.a_data);
		अगर ((चिन्हित दीर्घ)error < 0)
			वापस error;
	पूर्ण अन्यथा अणु
#अगर_घोषित WARN_OLD
		अटल अचिन्हित दीर्घ error_समय, error_समय2;
		अगर ((ex.a_text & 0xfff || ex.a_data & 0xfff) &&
		    (N_MAGIC(ex) != NMAGIC) &&
				समय_after(jअगरfies, error_समय2 + 5*HZ)) अणु
			prपूर्णांकk(KERN_NOTICE "executable not page aligned\n");
			error_समय2 = jअगरfies;
		पूर्ण

		अगर ((fd_offset & ~PAGE_MASK) != 0 &&
			    समय_after(jअगरfies, error_समय + 5*HZ)) अणु
			prपूर्णांकk(KERN_WARNING
			       "fd_offset is not page aligned. Please convert "
			       "program: %pD\n",
			       bprm->file);
			error_समय = jअगरfies;
		पूर्ण
#पूर्ण_अगर

		अगर (!bprm->file->f_op->mmap || (fd_offset & ~PAGE_MASK) != 0) अणु
			error = vm_brk(N_TXTADDR(ex), ex.a_text+ex.a_data);
			अगर (error)
				वापस error;

			पढ़ो_code(bprm->file, N_TXTADDR(ex), fd_offset,
					ex.a_text+ex.a_data);
			जाओ beyond_अगर;
		पूर्ण

		error = vm_mmap(bprm->file, N_TXTADDR(ex), ex.a_text,
				PROT_READ | PROT_EXEC,
				MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE |
				MAP_EXECUTABLE | MAP_32BIT,
				fd_offset);

		अगर (error != N_TXTADDR(ex))
			वापस error;

		error = vm_mmap(bprm->file, N_DATADDR(ex), ex.a_data,
				PROT_READ | PROT_WRITE | PROT_EXEC,
				MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE |
				MAP_EXECUTABLE | MAP_32BIT,
				fd_offset + ex.a_text);
		अगर (error != N_DATADDR(ex))
			वापस error;
	पूर्ण

beyond_अगर:
	error = set_brk(current->mm->start_brk, current->mm->brk);
	अगर (error)
		वापस error;

	set_binfmt(&aout_क्रमmat);

	current->mm->start_stack =
		(अचिन्हित दीर्घ)create_aout_tables((अक्षर __user *)bprm->p, bprm);
	/* start thपढ़ो */
	loadsegment(fs, 0);
	loadsegment(ds, __USER32_DS);
	loadsegment(es, __USER32_DS);
	load_gs_index(0);
	(regs)->ip = ex.a_entry;
	(regs)->sp = current->mm->start_stack;
	(regs)->flags = 0x200;
	(regs)->cs = __USER32_CS;
	(regs)->ss = __USER32_DS;
	regs->r8 = regs->r9 = regs->r10 = regs->r11 =
	regs->r12 = regs->r13 = regs->r14 = regs->r15 = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक load_aout_library(काष्ठा file *file)
अणु
	अचिन्हित दीर्घ bss, start_addr, len, error;
	पूर्णांक retval;
	काष्ठा exec ex;
	loff_t pos = 0;

	retval = -ENOEXEC;
	error = kernel_पढ़ो(file, &ex, माप(ex), &pos);
	अगर (error != माप(ex))
		जाओ out;

	/* We come in here क्रम the regular a.out style of shared libraries */
	अगर ((N_MAGIC(ex) != ZMAGIC && N_MAGIC(ex) != QMAGIC) || N_TRSIZE(ex) ||
	    N_DRSIZE(ex) || ((ex.a_entry & 0xfff) && N_MAGIC(ex) == ZMAGIC) ||
	    i_size_पढ़ो(file_inode(file)) <
	    ex.a_text+ex.a_data+N_SYMSIZE(ex)+N_TXTOFF(ex)) अणु
		जाओ out;
	पूर्ण

	अगर (N_FLAGS(ex))
		जाओ out;

	/* For  QMAGIC, the starting address is 0x20 पूर्णांकo the page.  We mask
	   this off to get the starting address क्रम the page */

	start_addr =  ex.a_entry & 0xfffff000;

	अगर ((N_TXTOFF(ex) & ~PAGE_MASK) != 0) अणु
#अगर_घोषित WARN_OLD
		अटल अचिन्हित दीर्घ error_समय;
		अगर (समय_after(jअगरfies, error_समय + 5*HZ)) अणु
			prपूर्णांकk(KERN_WARNING
			       "N_TXTOFF is not page aligned. Please convert "
			       "library: %pD\n",
			       file);
			error_समय = jअगरfies;
		पूर्ण
#पूर्ण_अगर
		retval = vm_brk(start_addr, ex.a_text + ex.a_data + ex.a_bss);
		अगर (retval)
			जाओ out;

		पढ़ो_code(file, start_addr, N_TXTOFF(ex),
			  ex.a_text + ex.a_data);
		retval = 0;
		जाओ out;
	पूर्ण
	/* Now use mmap to map the library पूर्णांकo memory. */
	error = vm_mmap(file, start_addr, ex.a_text + ex.a_data,
			PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE | MAP_32BIT,
			N_TXTOFF(ex));
	retval = error;
	अगर (error != start_addr)
		जाओ out;

	len = PAGE_ALIGN(ex.a_text + ex.a_data);
	bss = ex.a_text + ex.a_data + ex.a_bss;
	अगर (bss > len) अणु
		retval = vm_brk(start_addr + len, bss - len);
		अगर (retval)
			जाओ out;
	पूर्ण
	retval = 0;
out:
	वापस retval;
पूर्ण

अटल पूर्णांक __init init_aout_binfmt(व्योम)
अणु
	रेजिस्टर_binfmt(&aout_क्रमmat);
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_aout_binfmt(व्योम)
अणु
	unरेजिस्टर_binfmt(&aout_क्रमmat);
पूर्ण

module_init(init_aout_binfmt);
module_निकास(निकास_aout_binfmt);
MODULE_LICENSE("GPL");
