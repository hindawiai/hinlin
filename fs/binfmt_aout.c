<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/binfmt_aout.c
 *
 *  Copyright (C) 1991, 1992, 1996  Linus Torvalds
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
#समावेश <linux/coredump.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

अटल पूर्णांक load_aout_binary(काष्ठा linux_binprm *);
अटल पूर्णांक load_aout_library(काष्ठा file*);

अटल काष्ठा linux_binfmt aout_क्रमmat = अणु
	.module		= THIS_MODULE,
	.load_binary	= load_aout_binary,
	.load_shlib	= load_aout_library,
पूर्ण;

#घोषणा BAD_ADDR(x)	((अचिन्हित दीर्घ)(x) >= TASK_SIZE)

अटल पूर्णांक set_brk(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start = PAGE_ALIGN(start);
	end = PAGE_ALIGN(end);
	अगर (end > start)
		वापस vm_brk(start, end - start);
	वापस 0;
पूर्ण

/*
 * create_aout_tables() parses the env- and arg-strings in new user
 * memory and creates the poपूर्णांकer tables from them, and माला_दो their
 * addresses on the "stack", वापसing the new stack poपूर्णांकer value.
 */
अटल अचिन्हित दीर्घ __user *create_aout_tables(अक्षर __user *p, काष्ठा linux_binprm * bprm)
अणु
	अक्षर __user * __user *argv;
	अक्षर __user * __user *envp;
	अचिन्हित दीर्घ __user *sp;
	पूर्णांक argc = bprm->argc;
	पूर्णांक envc = bprm->envc;

	sp = (व्योम __user *)((-(अचिन्हित दीर्घ)माप(अक्षर *)) & (अचिन्हित दीर्घ) p);
#अगर_घोषित __alpha__
/* whee.. test-programs are so much fun. */
	put_user(0, --sp);
	put_user(0, --sp);
	अगर (bprm->loader) अणु
		put_user(0, --sp);
		put_user(1003, --sp);
		put_user(bprm->loader, --sp);
		put_user(1002, --sp);
	पूर्ण
	put_user(bprm->exec, --sp);
	put_user(1001, --sp);
#पूर्ण_अगर
	sp -= envc+1;
	envp = (अक्षर __user * __user *) sp;
	sp -= argc+1;
	argv = (अक्षर __user * __user *) sp;
#अगर_अघोषित __alpha__
	put_user((अचिन्हित दीर्घ) envp,--sp);
	put_user((अचिन्हित दीर्घ) argv,--sp);
#पूर्ण_अगर
	put_user(argc,--sp);
	current->mm->arg_start = (अचिन्हित दीर्घ) p;
	जबतक (argc-->0) अणु
		अक्षर c;
		put_user(p,argv++);
		करो अणु
			get_user(c,p++);
		पूर्ण जबतक (c);
	पूर्ण
	put_user(शून्य,argv);
	current->mm->arg_end = current->mm->env_start = (अचिन्हित दीर्घ) p;
	जबतक (envc-->0) अणु
		अक्षर c;
		put_user(p,envp++);
		करो अणु
			get_user(c,p++);
		पूर्ण जबतक (c);
	पूर्ण
	put_user(शून्य,envp);
	current->mm->env_end = (अचिन्हित दीर्घ) p;
	वापस sp;
पूर्ण

/*
 * These are the functions used to load a.out style executables and shared
 * libraries.  There is no binary dependent code anywhere अन्यथा.
 */

अटल पूर्णांक load_aout_binary(काष्ठा linux_binprm * bprm)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	काष्ठा exec ex;
	अचिन्हित दीर्घ error;
	अचिन्हित दीर्घ fd_offset;
	अचिन्हित दीर्घ rlim;
	पूर्णांक retval;

	ex = *((काष्ठा exec *) bprm->buf);		/* exec-header */
	अगर ((N_MAGIC(ex) != ZMAGIC && N_MAGIC(ex) != OMAGIC &&
	     N_MAGIC(ex) != QMAGIC && N_MAGIC(ex) != NMAGIC) ||
	    N_TRSIZE(ex) || N_DRSIZE(ex) ||
	    i_size_पढ़ो(file_inode(bprm->file)) < ex.a_text+ex.a_data+N_SYMSIZE(ex)+N_TXTOFF(ex)) अणु
		वापस -ENOEXEC;
	पूर्ण

	/*
	 * Requires a mmap handler. This prevents people from using a.out
	 * as part of an exploit attack against /proc-related vulnerabilities.
	 */
	अगर (!bprm->file->f_op->mmap)
		वापस -ENOEXEC;

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
#अगर_घोषित __alpha__
	SET_AOUT_PERSONALITY(bprm, ex);
#अन्यथा
	set_personality(PER_LINUX);
#पूर्ण_अगर
	setup_new_exec(bprm);

	current->mm->end_code = ex.a_text +
		(current->mm->start_code = N_TXTADDR(ex));
	current->mm->end_data = ex.a_data +
		(current->mm->start_data = N_DATADDR(ex));
	current->mm->brk = ex.a_bss +
		(current->mm->start_brk = N_BSSADDR(ex));

	retval = setup_arg_pages(bprm, STACK_TOP, EXSTACK_DEFAULT);
	अगर (retval < 0)
		वापस retval;


	अगर (N_MAGIC(ex) == OMAGIC) अणु
		अचिन्हित दीर्घ text_addr, map_size;
		loff_t pos;

		text_addr = N_TXTADDR(ex);

#अगर_घोषित __alpha__
		pos = fd_offset;
		map_size = ex.a_text+ex.a_data + PAGE_SIZE - 1;
#अन्यथा
		pos = 32;
		map_size = ex.a_text+ex.a_data;
#पूर्ण_अगर
		error = vm_brk(text_addr & PAGE_MASK, map_size);
		अगर (error)
			वापस error;

		error = पढ़ो_code(bprm->file, text_addr, pos,
				  ex.a_text+ex.a_data);
		अगर ((चिन्हित दीर्घ)error < 0)
			वापस error;
	पूर्ण अन्यथा अणु
		अगर ((ex.a_text & 0xfff || ex.a_data & 0xfff) &&
		    (N_MAGIC(ex) != NMAGIC) && prपूर्णांकk_ratelimit())
		अणु
			prपूर्णांकk(KERN_NOTICE "executable not page aligned\n");
		पूर्ण

		अगर ((fd_offset & ~PAGE_MASK) != 0 && prपूर्णांकk_ratelimit())
		अणु
			prपूर्णांकk(KERN_WARNING 
			       "fd_offset is not page aligned. Please convert program: %pD\n",
			       bprm->file);
		पूर्ण

		अगर (!bprm->file->f_op->mmap||((fd_offset & ~PAGE_MASK) != 0)) अणु
			error = vm_brk(N_TXTADDR(ex), ex.a_text+ex.a_data);
			अगर (error)
				वापस error;

			पढ़ो_code(bprm->file, N_TXTADDR(ex), fd_offset,
				  ex.a_text + ex.a_data);
			जाओ beyond_अगर;
		पूर्ण

		error = vm_mmap(bprm->file, N_TXTADDR(ex), ex.a_text,
			PROT_READ | PROT_EXEC,
			MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE | MAP_EXECUTABLE,
			fd_offset);

		अगर (error != N_TXTADDR(ex))
			वापस error;

		error = vm_mmap(bprm->file, N_DATADDR(ex), ex.a_data,
				PROT_READ | PROT_WRITE | PROT_EXEC,
				MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE | MAP_EXECUTABLE,
				fd_offset + ex.a_text);
		अगर (error != N_DATADDR(ex))
			वापस error;
	पूर्ण
beyond_अगर:
	set_binfmt(&aout_क्रमmat);

	retval = set_brk(current->mm->start_brk, current->mm->brk);
	अगर (retval < 0)
		वापस retval;

	current->mm->start_stack =
		(अचिन्हित दीर्घ) create_aout_tables((अक्षर __user *) bprm->p, bprm);
#अगर_घोषित __alpha__
	regs->gp = ex.a_gpvalue;
#पूर्ण_अगर
	finalize_exec(bprm);
	start_thपढ़ो(regs, ex.a_entry, current->mm->start_stack);
	वापस 0;
पूर्ण

अटल पूर्णांक load_aout_library(काष्ठा file *file)
अणु
	काष्ठा inode * inode;
	अचिन्हित दीर्घ bss, start_addr, len;
	अचिन्हित दीर्घ error;
	पूर्णांक retval;
	काष्ठा exec ex;
	loff_t pos = 0;

	inode = file_inode(file);

	retval = -ENOEXEC;
	error = kernel_पढ़ो(file, &ex, माप(ex), &pos);
	अगर (error != माप(ex))
		जाओ out;

	/* We come in here क्रम the regular a.out style of shared libraries */
	अगर ((N_MAGIC(ex) != ZMAGIC && N_MAGIC(ex) != QMAGIC) || N_TRSIZE(ex) ||
	    N_DRSIZE(ex) || ((ex.a_entry & 0xfff) && N_MAGIC(ex) == ZMAGIC) ||
	    i_size_पढ़ो(inode) < ex.a_text+ex.a_data+N_SYMSIZE(ex)+N_TXTOFF(ex)) अणु
		जाओ out;
	पूर्ण

	/*
	 * Requires a mmap handler. This prevents people from using a.out
	 * as part of an exploit attack against /proc-related vulnerabilities.
	 */
	अगर (!file->f_op->mmap)
		जाओ out;

	अगर (N_FLAGS(ex))
		जाओ out;

	/* For  QMAGIC, the starting address is 0x20 पूर्णांकo the page.  We mask
	   this off to get the starting address क्रम the page */

	start_addr =  ex.a_entry & 0xfffff000;

	अगर ((N_TXTOFF(ex) & ~PAGE_MASK) != 0) अणु
		अगर (prपूर्णांकk_ratelimit())
		अणु
			prपूर्णांकk(KERN_WARNING 
			       "N_TXTOFF is not page aligned. Please convert library: %pD\n",
			       file);
		पूर्ण
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
			MAP_FIXED | MAP_PRIVATE | MAP_DENYWRITE,
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

core_initcall(init_aout_binfmt);
module_निकास(निकास_aout_binfmt);
MODULE_LICENSE("GPL");
