<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/exec.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * #!-checking implemented by tytso.
 */
/*
 * Demand-loading implemented 01.12.91 - no need to पढ़ो anything but
 * the header पूर्णांकo memory. The inode of the executable is put पूर्णांकo
 * "current->executable", and page faults करो the actual loading. Clean.
 *
 * Once more I can proudly say that linux stood up to being changed: it
 * was less than 2 hours work to get demand-loading completely implemented.
 *
 * Demand loading changed July 1993 by Eric Youngdale.   Use mmap instead,
 * current->executable is only used by the procfs.  This allows a dispatch
 * table to check क्रम several dअगरferent types  of binary क्रमmats.  We keep
 * trying until we recognize the file or we run out of supported binary
 * क्रमmats.
 */

#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/mm.h>
#समावेश <linux/vmacache.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/swap.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/numa_balancing.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/key.h>
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/utsname.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/module.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tsacct_kern.h>
#समावेश <linux/cn_proc.h>
#समावेश <linux/audit.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/kmod.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/oom.h>
#समावेश <linux/compat.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/io_uring.h>
#समावेश <linux/syscall_user_dispatch.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>

#समावेश <trace/events/task.h>
#समावेश "internal.h"

#समावेश <trace/events/sched.h>

अटल पूर्णांक bprm_creds_from_file(काष्ठा linux_binprm *bprm);

पूर्णांक suid_dumpable = 0;

अटल LIST_HEAD(क्रमmats);
अटल DEFINE_RWLOCK(binfmt_lock);

व्योम __रेजिस्टर_binfmt(काष्ठा linux_binfmt * fmt, पूर्णांक insert)
अणु
	BUG_ON(!fmt);
	अगर (WARN_ON(!fmt->load_binary))
		वापस;
	ग_लिखो_lock(&binfmt_lock);
	insert ? list_add(&fmt->lh, &क्रमmats) :
		 list_add_tail(&fmt->lh, &क्रमmats);
	ग_लिखो_unlock(&binfmt_lock);
पूर्ण

EXPORT_SYMBOL(__रेजिस्टर_binfmt);

व्योम unरेजिस्टर_binfmt(काष्ठा linux_binfmt * fmt)
अणु
	ग_लिखो_lock(&binfmt_lock);
	list_del(&fmt->lh);
	ग_लिखो_unlock(&binfmt_lock);
पूर्ण

EXPORT_SYMBOL(unरेजिस्टर_binfmt);

अटल अंतरभूत व्योम put_binfmt(काष्ठा linux_binfmt * fmt)
अणु
	module_put(fmt->module);
पूर्ण

bool path_noexec(स्थिर काष्ठा path *path)
अणु
	वापस (path->mnt->mnt_flags & MNT_NOEXEC) ||
	       (path->mnt->mnt_sb->s_अगरlags & SB_I_NOEXEC);
पूर्ण

#अगर_घोषित CONFIG_USELIB
/*
 * Note that a shared library must be both पढ़ोable and executable due to
 * security reasons.
 *
 * Also note that we take the address to load from from the file itself.
 */
SYSCALL_DEFINE1(uselib, स्थिर अक्षर __user *, library)
अणु
	काष्ठा linux_binfmt *fmt;
	काष्ठा file *file;
	काष्ठा filename *पंचांगp = getname(library);
	पूर्णांक error = PTR_ERR(पंचांगp);
	अटल स्थिर काष्ठा खोलो_flags uselib_flags = अणु
		.खोलो_flag = O_LARGEखाता | O_RDONLY | __FMODE_EXEC,
		.acc_mode = MAY_READ | MAY_EXEC,
		.पूर्णांकent = LOOKUP_OPEN,
		.lookup_flags = LOOKUP_FOLLOW,
	पूर्ण;

	अगर (IS_ERR(पंचांगp))
		जाओ out;

	file = करो_filp_खोलो(AT_FDCWD, पंचांगp, &uselib_flags);
	putname(पंचांगp);
	error = PTR_ERR(file);
	अगर (IS_ERR(file))
		जाओ out;

	/*
	 * may_खोलो() has alपढ़ोy checked क्रम this, so it should be
	 * impossible to trip now. But we need to be extra cautious
	 * and check again at the very end too.
	 */
	error = -EACCES;
	अगर (WARN_ON_ONCE(!S_ISREG(file_inode(file)->i_mode) ||
			 path_noexec(&file->f_path)))
		जाओ निकास;

	fsnotअगरy_खोलो(file);

	error = -ENOEXEC;

	पढ़ो_lock(&binfmt_lock);
	list_क्रम_each_entry(fmt, &क्रमmats, lh) अणु
		अगर (!fmt->load_shlib)
			जारी;
		अगर (!try_module_get(fmt->module))
			जारी;
		पढ़ो_unlock(&binfmt_lock);
		error = fmt->load_shlib(file);
		पढ़ो_lock(&binfmt_lock);
		put_binfmt(fmt);
		अगर (error != -ENOEXEC)
			अवरोध;
	पूर्ण
	पढ़ो_unlock(&binfmt_lock);
निकास:
	fput(file);
out:
  	वापस error;
पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_USELIB */

#अगर_घोषित CONFIG_MMU
/*
 * The nascent bprm->mm is not visible until exec_mmap() but it can
 * use a lot of memory, account these pages in current->mm temporary
 * क्रम oom_badness()->get_mm_rss(). Once exec succeeds or fails, we
 * change the counter back via acct_arg_size(0).
 */
अटल व्योम acct_arg_size(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pages)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	दीर्घ dअगरf = (दीर्घ)(pages - bprm->vma_pages);

	अगर (!mm || !dअगरf)
		वापस;

	bprm->vma_pages = pages;
	add_mm_counter(mm, MM_ANONPAGES, dअगरf);
पूर्ण

अटल काष्ठा page *get_arg_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		पूर्णांक ग_लिखो)
अणु
	काष्ठा page *page;
	पूर्णांक ret;
	अचिन्हित पूर्णांक gup_flags = FOLL_FORCE;

#अगर_घोषित CONFIG_STACK_GROWSUP
	अगर (ग_लिखो) अणु
		ret = expand_करोwnwards(bprm->vma, pos);
		अगर (ret < 0)
			वापस शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (ग_लिखो)
		gup_flags |= FOLL_WRITE;

	/*
	 * We are करोing an exec().  'current' is the process
	 * करोing the exec and bprm->mm is the new process's mm.
	 */
	ret = get_user_pages_remote(bprm->mm, pos, 1, gup_flags,
			&page, शून्य, शून्य);
	अगर (ret <= 0)
		वापस शून्य;

	अगर (ग_लिखो)
		acct_arg_size(bprm, vma_pages(bprm->vma));

	वापस page;
पूर्ण

अटल व्योम put_arg_page(काष्ठा page *page)
अणु
	put_page(page);
पूर्ण

अटल व्योम मुक्त_arg_pages(काष्ठा linux_binprm *bprm)
अणु
पूर्ण

अटल व्योम flush_arg_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		काष्ठा page *page)
अणु
	flush_cache_page(bprm->vma, pos, page_to_pfn(page));
पूर्ण

अटल पूर्णांक __bprm_mm_init(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक err;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा mm_काष्ठा *mm = bprm->mm;

	bprm->vma = vma = vm_area_alloc(mm);
	अगर (!vma)
		वापस -ENOMEM;
	vma_set_anonymous(vma);

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm)) अणु
		err = -EINTR;
		जाओ err_मुक्त;
	पूर्ण

	/*
	 * Place the stack at the largest stack address the architecture
	 * supports. Later, we'll move this to an appropriate place. We don't
	 * use STACK_TOP because that can depend on attributes which aren't
	 * configured yet.
	 */
	BUILD_BUG_ON(VM_STACK_FLAGS & VM_STACK_INCOMPLETE_SETUP);
	vma->vm_end = STACK_TOP_MAX;
	vma->vm_start = vma->vm_end - PAGE_SIZE;
	vma->vm_flags = VM_SOFTसूचीTY | VM_STACK_FLAGS | VM_STACK_INCOMPLETE_SETUP;
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);

	err = insert_vm_काष्ठा(mm, vma);
	अगर (err)
		जाओ err;

	mm->stack_vm = mm->total_vm = 1;
	mmap_ग_लिखो_unlock(mm);
	bprm->p = vma->vm_end - माप(व्योम *);
	वापस 0;
err:
	mmap_ग_लिखो_unlock(mm);
err_मुक्त:
	bprm->vma = शून्य;
	vm_area_मुक्त(vma);
	वापस err;
पूर्ण

अटल bool valid_arg_len(काष्ठा linux_binprm *bprm, दीर्घ len)
अणु
	वापस len <= MAX_ARG_STRLEN;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम acct_arg_size(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pages)
अणु
पूर्ण

अटल काष्ठा page *get_arg_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		पूर्णांक ग_लिखो)
अणु
	काष्ठा page *page;

	page = bprm->page[pos / PAGE_SIZE];
	अगर (!page && ग_लिखो) अणु
		page = alloc_page(GFP_HIGHUSER|__GFP_ZERO);
		अगर (!page)
			वापस शून्य;
		bprm->page[pos / PAGE_SIZE] = page;
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम put_arg_page(काष्ठा page *page)
अणु
पूर्ण

अटल व्योम मुक्त_arg_page(काष्ठा linux_binprm *bprm, पूर्णांक i)
अणु
	अगर (bprm->page[i]) अणु
		__मुक्त_page(bprm->page[i]);
		bprm->page[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम मुक्त_arg_pages(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_ARG_PAGES; i++)
		मुक्त_arg_page(bprm, i);
पूर्ण

अटल व्योम flush_arg_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		काष्ठा page *page)
अणु
पूर्ण

अटल पूर्णांक __bprm_mm_init(काष्ठा linux_binprm *bprm)
अणु
	bprm->p = PAGE_SIZE * MAX_ARG_PAGES - माप(व्योम *);
	वापस 0;
पूर्ण

अटल bool valid_arg_len(काष्ठा linux_binprm *bprm, दीर्घ len)
अणु
	वापस len <= bprm->p;
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

/*
 * Create a new mm_काष्ठा and populate it with a temporary stack
 * vm_area_काष्ठा.  We करोn't have enough context at this poपूर्णांक to set the stack
 * flags, permissions, and offset, so we use temporary values.  We'll update
 * them later in setup_arg_pages().
 */
अटल पूर्णांक bprm_mm_init(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक err;
	काष्ठा mm_काष्ठा *mm = शून्य;

	bprm->mm = mm = mm_alloc();
	err = -ENOMEM;
	अगर (!mm)
		जाओ err;

	/* Save current stack limit क्रम all calculations made during exec. */
	task_lock(current->group_leader);
	bprm->rlim_stack = current->संकेत->rlim[RLIMIT_STACK];
	task_unlock(current->group_leader);

	err = __bprm_mm_init(bprm);
	अगर (err)
		जाओ err;

	वापस 0;

err:
	अगर (mm) अणु
		bprm->mm = शून्य;
		mmdrop(mm);
	पूर्ण

	वापस err;
पूर्ण

काष्ठा user_arg_ptr अणु
#अगर_घोषित CONFIG_COMPAT
	bool is_compat;
#पूर्ण_अगर
	जोड़ अणु
		स्थिर अक्षर __user *स्थिर __user *native;
#अगर_घोषित CONFIG_COMPAT
		स्थिर compat_uptr_t __user *compat;
#पूर्ण_अगर
	पूर्ण ptr;
पूर्ण;

अटल स्थिर अक्षर __user *get_user_arg_ptr(काष्ठा user_arg_ptr argv, पूर्णांक nr)
अणु
	स्थिर अक्षर __user *native;

#अगर_घोषित CONFIG_COMPAT
	अगर (unlikely(argv.is_compat)) अणु
		compat_uptr_t compat;

		अगर (get_user(compat, argv.ptr.compat + nr))
			वापस ERR_PTR(-EFAULT);

		वापस compat_ptr(compat);
	पूर्ण
#पूर्ण_अगर

	अगर (get_user(native, argv.ptr.native + nr))
		वापस ERR_PTR(-EFAULT);

	वापस native;
पूर्ण

/*
 * count() counts the number of strings in array ARGV.
 */
अटल पूर्णांक count(काष्ठा user_arg_ptr argv, पूर्णांक max)
अणु
	पूर्णांक i = 0;

	अगर (argv.ptr.native != शून्य) अणु
		क्रम (;;) अणु
			स्थिर अक्षर __user *p = get_user_arg_ptr(argv, i);

			अगर (!p)
				अवरोध;

			अगर (IS_ERR(p))
				वापस -EFAULT;

			अगर (i >= max)
				वापस -E2BIG;
			++i;

			अगर (fatal_संकेत_pending(current))
				वापस -ERESTARTNOHAND;
			cond_resched();
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक count_strings_kernel(स्थिर अक्षर *स्थिर *argv)
अणु
	पूर्णांक i;

	अगर (!argv)
		वापस 0;

	क्रम (i = 0; argv[i]; ++i) अणु
		अगर (i >= MAX_ARG_STRINGS)
			वापस -E2BIG;
		अगर (fatal_संकेत_pending(current))
			वापस -ERESTARTNOHAND;
		cond_resched();
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक bprm_stack_limits(काष्ठा linux_binprm *bprm)
अणु
	अचिन्हित दीर्घ limit, ptr_size;

	/*
	 * Limit to 1/4 of the max stack size or 3/4 of _STK_LIM
	 * (whichever is smaller) क्रम the argv+env strings.
	 * This ensures that:
	 *  - the reमुख्यing binfmt code will not run out of stack space,
	 *  - the program will have a reasonable amount of stack left
	 *    to work from.
	 */
	limit = _STK_LIM / 4 * 3;
	limit = min(limit, bprm->rlim_stack.rlim_cur / 4);
	/*
	 * We've historically supported up to 32 pages (ARG_MAX)
	 * of argument strings even with small stacks
	 */
	limit = max_t(अचिन्हित दीर्घ, limit, ARG_MAX);
	/*
	 * We must account क्रम the size of all the argv and envp poपूर्णांकers to
	 * the argv and envp strings, since they will also take up space in
	 * the stack. They aren't stored until much later when we can't
	 * संकेत to the parent that the child has run out of stack space.
	 * Instead, calculate it here so it's possible to fail gracefully.
	 */
	ptr_size = (bprm->argc + bprm->envc) * माप(व्योम *);
	अगर (limit <= ptr_size)
		वापस -E2BIG;
	limit -= ptr_size;

	bprm->argmin = bprm->p - limit;
	वापस 0;
पूर्ण

/*
 * 'copy_strings()' copies argument/environment strings from the old
 * processes's memory to the new process's stack.  The call to get_user_pages()
 * ensures the destination page is created and not swapped out.
 */
अटल पूर्णांक copy_strings(पूर्णांक argc, काष्ठा user_arg_ptr argv,
			काष्ठा linux_binprm *bprm)
अणु
	काष्ठा page *kmapped_page = शून्य;
	अक्षर *kaddr = शून्य;
	अचिन्हित दीर्घ kpos = 0;
	पूर्णांक ret;

	जबतक (argc-- > 0) अणु
		स्थिर अक्षर __user *str;
		पूर्णांक len;
		अचिन्हित दीर्घ pos;

		ret = -EFAULT;
		str = get_user_arg_ptr(argv, argc);
		अगर (IS_ERR(str))
			जाओ out;

		len = strnlen_user(str, MAX_ARG_STRLEN);
		अगर (!len)
			जाओ out;

		ret = -E2BIG;
		अगर (!valid_arg_len(bprm, len))
			जाओ out;

		/* We're going to work our way backwords. */
		pos = bprm->p;
		str += len;
		bprm->p -= len;
#अगर_घोषित CONFIG_MMU
		अगर (bprm->p < bprm->argmin)
			जाओ out;
#पूर्ण_अगर

		जबतक (len > 0) अणु
			पूर्णांक offset, bytes_to_copy;

			अगर (fatal_संकेत_pending(current)) अणु
				ret = -ERESTARTNOHAND;
				जाओ out;
			पूर्ण
			cond_resched();

			offset = pos % PAGE_SIZE;
			अगर (offset == 0)
				offset = PAGE_SIZE;

			bytes_to_copy = offset;
			अगर (bytes_to_copy > len)
				bytes_to_copy = len;

			offset -= bytes_to_copy;
			pos -= bytes_to_copy;
			str -= bytes_to_copy;
			len -= bytes_to_copy;

			अगर (!kmapped_page || kpos != (pos & PAGE_MASK)) अणु
				काष्ठा page *page;

				page = get_arg_page(bprm, pos, 1);
				अगर (!page) अणु
					ret = -E2BIG;
					जाओ out;
				पूर्ण

				अगर (kmapped_page) अणु
					flush_kernel_dcache_page(kmapped_page);
					kunmap(kmapped_page);
					put_arg_page(kmapped_page);
				पूर्ण
				kmapped_page = page;
				kaddr = kmap(kmapped_page);
				kpos = pos & PAGE_MASK;
				flush_arg_page(bprm, kpos, kmapped_page);
			पूर्ण
			अगर (copy_from_user(kaddr+offset, str, bytes_to_copy)) अणु
				ret = -EFAULT;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = 0;
out:
	अगर (kmapped_page) अणु
		flush_kernel_dcache_page(kmapped_page);
		kunmap(kmapped_page);
		put_arg_page(kmapped_page);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Copy and argument/environment string from the kernel to the processes stack.
 */
पूर्णांक copy_string_kernel(स्थिर अक्षर *arg, काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक len = strnlen(arg, MAX_ARG_STRLEN) + 1 /* terminating NUL */;
	अचिन्हित दीर्घ pos = bprm->p;

	अगर (len == 0)
		वापस -EFAULT;
	अगर (!valid_arg_len(bprm, len))
		वापस -E2BIG;

	/* We're going to work our way backwards. */
	arg += len;
	bprm->p -= len;
	अगर (IS_ENABLED(CONFIG_MMU) && bprm->p < bprm->argmin)
		वापस -E2BIG;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक bytes_to_copy = min_t(अचिन्हित पूर्णांक, len,
				min_not_zero(offset_in_page(pos), PAGE_SIZE));
		काष्ठा page *page;
		अक्षर *kaddr;

		pos -= bytes_to_copy;
		arg -= bytes_to_copy;
		len -= bytes_to_copy;

		page = get_arg_page(bprm, pos, 1);
		अगर (!page)
			वापस -E2BIG;
		kaddr = kmap_atomic(page);
		flush_arg_page(bprm, pos & PAGE_MASK, page);
		स_नकल(kaddr + offset_in_page(pos), arg, bytes_to_copy);
		flush_kernel_dcache_page(page);
		kunmap_atomic(kaddr);
		put_arg_page(page);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(copy_string_kernel);

अटल पूर्णांक copy_strings_kernel(पूर्णांक argc, स्थिर अक्षर *स्थिर *argv,
			       काष्ठा linux_binprm *bprm)
अणु
	जबतक (argc-- > 0) अणु
		पूर्णांक ret = copy_string_kernel(argv[argc], bprm);
		अगर (ret < 0)
			वापस ret;
		अगर (fatal_संकेत_pending(current))
			वापस -ERESTARTNOHAND;
		cond_resched();
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MMU

/*
 * During bprm_mm_init(), we create a temporary stack at STACK_TOP_MAX.  Once
 * the binfmt code determines where the new stack should reside, we shअगरt it to
 * its final location.  The process proceeds as follows:
 *
 * 1) Use shअगरt to calculate the new vma endpoपूर्णांकs.
 * 2) Extend vma to cover both the old and new ranges.  This ensures the
 *    arguments passed to subsequent functions are consistent.
 * 3) Move vma's page tables to the new range.
 * 4) Free up any cleared pgd range.
 * 5) Shrink the vma to cover only the new range.
 */
अटल पूर्णांक shअगरt_arg_pages(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ shअगरt)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ old_start = vma->vm_start;
	अचिन्हित दीर्घ old_end = vma->vm_end;
	अचिन्हित दीर्घ length = old_end - old_start;
	अचिन्हित दीर्घ new_start = old_start - shअगरt;
	अचिन्हित दीर्घ new_end = old_end - shअगरt;
	काष्ठा mmu_gather tlb;

	BUG_ON(new_start > new_end);

	/*
	 * ensure there are no vmas between where we want to go
	 * and where we are
	 */
	अगर (vma != find_vma(mm, new_start))
		वापस -EFAULT;

	/*
	 * cover the whole range: [new_start, old_end)
	 */
	अगर (vma_adjust(vma, new_start, old_end, vma->vm_pgoff, शून्य))
		वापस -ENOMEM;

	/*
	 * move the page tables करोwnwards, on failure we rely on
	 * process cleanup to हटाओ whatever mess we made.
	 */
	अगर (length != move_page_tables(vma, old_start,
				       vma, new_start, length, false))
		वापस -ENOMEM;

	lru_add_drain();
	tlb_gather_mmu(&tlb, mm);
	अगर (new_end > old_start) अणु
		/*
		 * when the old and new regions overlap clear from new_end.
		 */
		मुक्त_pgd_range(&tlb, new_end, old_end, new_end,
			vma->vm_next ? vma->vm_next->vm_start : USER_PGTABLES_CEILING);
	पूर्ण अन्यथा अणु
		/*
		 * otherwise, clean from old_start; this is करोne to not touch
		 * the address space in [new_end, old_start) some architectures
		 * have स्थिरraपूर्णांकs on va-space that make this illegal (IA64) -
		 * क्रम the others its just a little faster.
		 */
		मुक्त_pgd_range(&tlb, old_start, old_end, new_end,
			vma->vm_next ? vma->vm_next->vm_start : USER_PGTABLES_CEILING);
	पूर्ण
	tlb_finish_mmu(&tlb);

	/*
	 * Shrink the vma to just the new range.  Always succeeds.
	 */
	vma_adjust(vma, new_start, new_end, vma->vm_pgoff, शून्य);

	वापस 0;
पूर्ण

/*
 * Finalizes the stack vm_area_काष्ठा. The flags and permissions are updated,
 * the stack is optionally relocated, and some extra space is added.
 */
पूर्णांक setup_arg_pages(काष्ठा linux_binprm *bprm,
		    अचिन्हित दीर्घ stack_top,
		    पूर्णांक executable_stack)
अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ stack_shअगरt;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma = bprm->vma;
	काष्ठा vm_area_काष्ठा *prev = शून्य;
	अचिन्हित दीर्घ vm_flags;
	अचिन्हित दीर्घ stack_base;
	अचिन्हित दीर्घ stack_size;
	अचिन्हित दीर्घ stack_expand;
	अचिन्हित दीर्घ rlim_stack;

#अगर_घोषित CONFIG_STACK_GROWSUP
	/* Limit stack size */
	stack_base = bprm->rlim_stack.rlim_max;

	stack_base = calc_max_stack_size(stack_base);

	/* Add space क्रम stack अक्रमomization. */
	stack_base += (STACK_RND_MASK << PAGE_SHIFT);

	/* Make sure we didn't let the argument array grow too large. */
	अगर (vma->vm_end - vma->vm_start > stack_base)
		वापस -ENOMEM;

	stack_base = PAGE_ALIGN(stack_top - stack_base);

	stack_shअगरt = vma->vm_start - stack_base;
	mm->arg_start = bprm->p - stack_shअगरt;
	bprm->p = vma->vm_end - stack_shअगरt;
#अन्यथा
	stack_top = arch_align_stack(stack_top);
	stack_top = PAGE_ALIGN(stack_top);

	अगर (unlikely(stack_top < mmap_min_addr) ||
	    unlikely(vma->vm_end - vma->vm_start >= stack_top - mmap_min_addr))
		वापस -ENOMEM;

	stack_shअगरt = vma->vm_end - stack_top;

	bprm->p -= stack_shअगरt;
	mm->arg_start = bprm->p;
#पूर्ण_अगर

	अगर (bprm->loader)
		bprm->loader -= stack_shअगरt;
	bprm->exec -= stack_shअगरt;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	vm_flags = VM_STACK_FLAGS;

	/*
	 * Adjust stack execute permissions; explicitly enable क्रम
	 * EXSTACK_ENABLE_X, disable क्रम EXSTACK_DISABLE_X and leave alone
	 * (arch शेष) otherwise.
	 */
	अगर (unlikely(executable_stack == EXSTACK_ENABLE_X))
		vm_flags |= VM_EXEC;
	अन्यथा अगर (executable_stack == EXSTACK_DISABLE_X)
		vm_flags &= ~VM_EXEC;
	vm_flags |= mm->def_flags;
	vm_flags |= VM_STACK_INCOMPLETE_SETUP;

	ret = mprotect_fixup(vma, &prev, vma->vm_start, vma->vm_end,
			vm_flags);
	अगर (ret)
		जाओ out_unlock;
	BUG_ON(prev != vma);

	अगर (unlikely(vm_flags & VM_EXEC)) अणु
		pr_warn_once("process '%pD4' started with executable stack\n",
			     bprm->file);
	पूर्ण

	/* Move stack pages करोwn in memory. */
	अगर (stack_shअगरt) अणु
		ret = shअगरt_arg_pages(vma, stack_shअगरt);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	/* mprotect_fixup is overसमाप्त to हटाओ the temporary stack flags */
	vma->vm_flags &= ~VM_STACK_INCOMPLETE_SETUP;

	stack_expand = 131072UL; /* अक्रमomly 32*4k (or 2*64k) pages */
	stack_size = vma->vm_end - vma->vm_start;
	/*
	 * Align this करोwn to a page boundary as expand_stack
	 * will align it up.
	 */
	rlim_stack = bprm->rlim_stack.rlim_cur & PAGE_MASK;
#अगर_घोषित CONFIG_STACK_GROWSUP
	अगर (stack_size + stack_expand > rlim_stack)
		stack_base = vma->vm_start + rlim_stack;
	अन्यथा
		stack_base = vma->vm_end + stack_expand;
#अन्यथा
	अगर (stack_size + stack_expand > rlim_stack)
		stack_base = vma->vm_end - rlim_stack;
	अन्यथा
		stack_base = vma->vm_start - stack_expand;
#पूर्ण_अगर
	current->mm->start_stack = bprm->p;
	ret = expand_stack(vma, stack_base);
	अगर (ret)
		ret = -EFAULT;

out_unlock:
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(setup_arg_pages);

#अन्यथा

/*
 * Transfer the program arguments and environment from the holding pages
 * onto the stack. The provided stack poपूर्णांकer is adjusted accordingly.
 */
पूर्णांक transfer_args_to_stack(काष्ठा linux_binprm *bprm,
			   अचिन्हित दीर्घ *sp_location)
अणु
	अचिन्हित दीर्घ index, stop, sp;
	पूर्णांक ret = 0;

	stop = bprm->p >> PAGE_SHIFT;
	sp = *sp_location;

	क्रम (index = MAX_ARG_PAGES - 1; index >= stop; index--) अणु
		अचिन्हित पूर्णांक offset = index == stop ? bprm->p & ~PAGE_MASK : 0;
		अक्षर *src = kmap(bprm->page[index]) + offset;
		sp -= PAGE_SIZE - offset;
		अगर (copy_to_user((व्योम *) sp, src, PAGE_SIZE - offset) != 0)
			ret = -EFAULT;
		kunmap(bprm->page[index]);
		अगर (ret)
			जाओ out;
	पूर्ण

	*sp_location = sp;

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(transfer_args_to_stack);

#पूर्ण_अगर /* CONFIG_MMU */

अटल काष्ठा file *करो_खोलो_execat(पूर्णांक fd, काष्ठा filename *name, पूर्णांक flags)
अणु
	काष्ठा file *file;
	पूर्णांक err;
	काष्ठा खोलो_flags खोलो_exec_flags = अणु
		.खोलो_flag = O_LARGEखाता | O_RDONLY | __FMODE_EXEC,
		.acc_mode = MAY_EXEC,
		.पूर्णांकent = LOOKUP_OPEN,
		.lookup_flags = LOOKUP_FOLLOW,
	पूर्ण;

	अगर ((flags & ~(AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH)) != 0)
		वापस ERR_PTR(-EINVAL);
	अगर (flags & AT_SYMLINK_NOFOLLOW)
		खोलो_exec_flags.lookup_flags &= ~LOOKUP_FOLLOW;
	अगर (flags & AT_EMPTY_PATH)
		खोलो_exec_flags.lookup_flags |= LOOKUP_EMPTY;

	file = करो_filp_खोलो(fd, name, &खोलो_exec_flags);
	अगर (IS_ERR(file))
		जाओ out;

	/*
	 * may_खोलो() has alपढ़ोy checked क्रम this, so it should be
	 * impossible to trip now. But we need to be extra cautious
	 * and check again at the very end too.
	 */
	err = -EACCES;
	अगर (WARN_ON_ONCE(!S_ISREG(file_inode(file)->i_mode) ||
			 path_noexec(&file->f_path)))
		जाओ निकास;

	err = deny_ग_लिखो_access(file);
	अगर (err)
		जाओ निकास;

	अगर (name->name[0] != '\0')
		fsnotअगरy_खोलो(file);

out:
	वापस file;

निकास:
	fput(file);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा file *खोलो_exec(स्थिर अक्षर *name)
अणु
	काष्ठा filename *filename = getname_kernel(name);
	काष्ठा file *f = ERR_CAST(filename);

	अगर (!IS_ERR(filename)) अणु
		f = करो_खोलो_execat(AT_FDCWD, filename, 0);
		putname(filename);
	पूर्ण
	वापस f;
पूर्ण
EXPORT_SYMBOL(खोलो_exec);

#अगर defined(CONFIG_HAVE_AOUT) || defined(CONFIG_BINFMT_FLAT) || \
    defined(CONFIG_BINFMT_ELF_FDPIC)
sमाप_प्रकार पढ़ो_code(काष्ठा file *file, अचिन्हित दीर्घ addr, loff_t pos, माप_प्रकार len)
अणु
	sमाप_प्रकार res = vfs_पढ़ो(file, (व्योम __user *)addr, len, &pos);
	अगर (res > 0)
		flush_icache_user_range(addr, addr + len);
	वापस res;
पूर्ण
EXPORT_SYMBOL(पढ़ो_code);
#पूर्ण_अगर

/*
 * Maps the mm_काष्ठा mm पूर्णांकo the current task काष्ठा.
 * On success, this function वापसs with exec_update_lock
 * held क्रम writing.
 */
अटल पूर्णांक exec_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *old_mm, *active_mm;
	पूर्णांक ret;

	/* Notअगरy parent that we're no दीर्घer पूर्णांकerested in the old VM */
	tsk = current;
	old_mm = current->mm;
	exec_mm_release(tsk, old_mm);
	अगर (old_mm)
		sync_mm_rss(old_mm);

	ret = करोwn_ग_लिखो_समाप्तable(&tsk->संकेत->exec_update_lock);
	अगर (ret)
		वापस ret;

	अगर (old_mm) अणु
		/*
		 * Make sure that अगर there is a core dump in progress
		 * क्रम the old mm, we get out and die instead of going
		 * through with the exec.  We must hold mmap_lock around
		 * checking core_state and changing tsk->mm.
		 */
		mmap_पढ़ो_lock(old_mm);
		अगर (unlikely(old_mm->core_state)) अणु
			mmap_पढ़ो_unlock(old_mm);
			up_ग_लिखो(&tsk->संकेत->exec_update_lock);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	task_lock(tsk);
	membarrier_exec_mmap(mm);

	local_irq_disable();
	active_mm = tsk->active_mm;
	tsk->active_mm = mm;
	tsk->mm = mm;
	/*
	 * This prevents preemption जबतक active_mm is being loaded and
	 * it and mm are being updated, which could cause problems क्रम
	 * lazy tlb mm refcounting when these are updated by context
	 * चयनes. Not all architectures can handle irqs off over
	 * activate_mm yet.
	 */
	अगर (!IS_ENABLED(CONFIG_ARCH_WANT_IRQS_OFF_ACTIVATE_MM))
		local_irq_enable();
	activate_mm(active_mm, mm);
	अगर (IS_ENABLED(CONFIG_ARCH_WANT_IRQS_OFF_ACTIVATE_MM))
		local_irq_enable();
	tsk->mm->vmacache_seqnum = 0;
	vmacache_flush(tsk);
	task_unlock(tsk);
	अगर (old_mm) अणु
		mmap_पढ़ो_unlock(old_mm);
		BUG_ON(active_mm != old_mm);
		seपंचांगax_mm_hiwater_rss(&tsk->संकेत->maxrss, old_mm);
		mm_update_next_owner(old_mm);
		mmput(old_mm);
		वापस 0;
	पूर्ण
	mmdrop(active_mm);
	वापस 0;
पूर्ण

अटल पूर्णांक de_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा संकेत_काष्ठा *sig = tsk->संकेत;
	काष्ठा sighand_काष्ठा *oldsighand = tsk->sighand;
	spinlock_t *lock = &oldsighand->siglock;

	अगर (thपढ़ो_group_empty(tsk))
		जाओ no_thपढ़ो_group;

	/*
	 * Kill all other thपढ़ोs in the thपढ़ो group.
	 */
	spin_lock_irq(lock);
	अगर (संकेत_group_निकास(sig)) अणु
		/*
		 * Another group action in progress, just
		 * वापस so that the संकेत is processed.
		 */
		spin_unlock_irq(lock);
		वापस -EAGAIN;
	पूर्ण

	sig->group_निकास_task = tsk;
	sig->notअगरy_count = zap_other_thपढ़ोs(tsk);
	अगर (!thपढ़ो_group_leader(tsk))
		sig->notअगरy_count--;

	जबतक (sig->notअगरy_count) अणु
		__set_current_state(TASK_KILLABLE);
		spin_unlock_irq(lock);
		schedule();
		अगर (__fatal_संकेत_pending(tsk))
			जाओ समाप्तed;
		spin_lock_irq(lock);
	पूर्ण
	spin_unlock_irq(lock);

	/*
	 * At this poपूर्णांक all other thपढ़ोs have निकासed, all we have to
	 * करो is to रुको क्रम the thपढ़ो group leader to become inactive,
	 * and to assume its PID:
	 */
	अगर (!thपढ़ो_group_leader(tsk)) अणु
		काष्ठा task_काष्ठा *leader = tsk->group_leader;

		क्रम (;;) अणु
			cgroup_thपढ़ोgroup_change_begin(tsk);
			ग_लिखो_lock_irq(&tasklist_lock);
			/*
			 * Do this under tasklist_lock to ensure that
			 * निकास_notअगरy() can't miss ->group_निकास_task
			 */
			sig->notअगरy_count = -1;
			अगर (likely(leader->निकास_state))
				अवरोध;
			__set_current_state(TASK_KILLABLE);
			ग_लिखो_unlock_irq(&tasklist_lock);
			cgroup_thपढ़ोgroup_change_end(tsk);
			schedule();
			अगर (__fatal_संकेत_pending(tsk))
				जाओ समाप्तed;
		पूर्ण

		/*
		 * The only record we have of the real-समय age of a
		 * process, regardless of execs it's करोne, is start_समय.
		 * All the past CPU समय is accumulated in संकेत_काष्ठा
		 * from sister thपढ़ोs now dead.  But in this non-leader
		 * exec, nothing survives from the original leader thपढ़ो,
		 * whose birth marks the true age of this process now.
		 * When we take on its identity by चयनing to its PID, we
		 * also take its birthdate (always earlier than our own).
		 */
		tsk->start_समय = leader->start_समय;
		tsk->start_bootसमय = leader->start_bootसमय;

		BUG_ON(!same_thपढ़ो_group(leader, tsk));
		/*
		 * An exec() starts a new thपढ़ो group with the
		 * TGID of the previous thपढ़ो group. Rehash the
		 * two thपढ़ोs with a चयनed PID, and release
		 * the क्रमmer thपढ़ो group leader:
		 */

		/* Become a process group leader with the old leader's pid.
		 * The old leader becomes a thपढ़ो of the this thपढ़ो group.
		 */
		exchange_tids(tsk, leader);
		transfer_pid(leader, tsk, PIDTYPE_TGID);
		transfer_pid(leader, tsk, PIDTYPE_PGID);
		transfer_pid(leader, tsk, PIDTYPE_SID);

		list_replace_rcu(&leader->tasks, &tsk->tasks);
		list_replace_init(&leader->sibling, &tsk->sibling);

		tsk->group_leader = tsk;
		leader->group_leader = tsk;

		tsk->निकास_संकेत = SIGCHLD;
		leader->निकास_संकेत = -1;

		BUG_ON(leader->निकास_state != EXIT_ZOMBIE);
		leader->निकास_state = EXIT_DEAD;

		/*
		 * We are going to release_task()->ptrace_unlink() silently,
		 * the tracer can sleep in करो_रुको(). EXIT_DEAD guarantees
		 * the tracer wont't block again रुकोing क्रम this thपढ़ो.
		 */
		अगर (unlikely(leader->ptrace))
			__wake_up_parent(leader, leader->parent);
		ग_लिखो_unlock_irq(&tasklist_lock);
		cgroup_thपढ़ोgroup_change_end(tsk);

		release_task(leader);
	पूर्ण

	sig->group_निकास_task = शून्य;
	sig->notअगरy_count = 0;

no_thपढ़ो_group:
	/* we have changed execution करोमुख्य */
	tsk->निकास_संकेत = SIGCHLD;

	BUG_ON(!thपढ़ो_group_leader(tsk));
	वापस 0;

समाप्तed:
	/* protects against निकास_notअगरy() and __निकास_संकेत() */
	पढ़ो_lock(&tasklist_lock);
	sig->group_निकास_task = शून्य;
	sig->notअगरy_count = 0;
	पढ़ो_unlock(&tasklist_lock);
	वापस -EAGAIN;
पूर्ण


/*
 * This function makes sure the current process has its own संकेत table,
 * so that flush_संकेत_handlers can later reset the handlers without
 * disturbing other processes.  (Other processes might share the संकेत
 * table via the CLONE_SIGHAND option to clone().)
 */
अटल पूर्णांक unshare_sighand(काष्ठा task_काष्ठा *me)
अणु
	काष्ठा sighand_काष्ठा *oldsighand = me->sighand;

	अगर (refcount_पढ़ो(&oldsighand->count) != 1) अणु
		काष्ठा sighand_काष्ठा *newsighand;
		/*
		 * This ->sighand is shared with the CLONE_SIGHAND
		 * but not CLONE_THREAD task, चयन to the new one.
		 */
		newsighand = kmem_cache_alloc(sighand_cachep, GFP_KERNEL);
		अगर (!newsighand)
			वापस -ENOMEM;

		refcount_set(&newsighand->count, 1);
		स_नकल(newsighand->action, oldsighand->action,
		       माप(newsighand->action));

		ग_लिखो_lock_irq(&tasklist_lock);
		spin_lock(&oldsighand->siglock);
		rcu_assign_poपूर्णांकer(me->sighand, newsighand);
		spin_unlock(&oldsighand->siglock);
		ग_लिखो_unlock_irq(&tasklist_lock);

		__cleanup_sighand(oldsighand);
	पूर्ण
	वापस 0;
पूर्ण

अक्षर *__get_task_comm(अक्षर *buf, माप_प्रकार buf_size, काष्ठा task_काष्ठा *tsk)
अणु
	task_lock(tsk);
	म_नकलन(buf, tsk->comm, buf_size);
	task_unlock(tsk);
	वापस buf;
पूर्ण
EXPORT_SYMBOL_GPL(__get_task_comm);

/*
 * These functions flushes out all traces of the currently running executable
 * so that a new one can be started
 */

व्योम __set_task_comm(काष्ठा task_काष्ठा *tsk, स्थिर अक्षर *buf, bool exec)
अणु
	task_lock(tsk);
	trace_task_नाम(tsk, buf);
	strlcpy(tsk->comm, buf, माप(tsk->comm));
	task_unlock(tsk);
	perf_event_comm(tsk, exec);
पूर्ण

/*
 * Calling this is the poपूर्णांक of no वापस. None of the failures will be
 * seen by userspace since either the process is alपढ़ोy taking a fatal
 * संकेत (via de_thपढ़ो() or coredump), or will have SEGV उठाओd
 * (after exec_mmap()) by search_binary_handler (see below).
 */
पूर्णांक begin_new_exec(काष्ठा linux_binprm * bprm)
अणु
	काष्ठा task_काष्ठा *me = current;
	पूर्णांक retval;

	/* Once we are committed compute the creds */
	retval = bprm_creds_from_file(bprm);
	अगर (retval)
		वापस retval;

	/*
	 * Ensure all future errors are fatal.
	 */
	bprm->poपूर्णांक_of_no_वापस = true;

	/*
	 * Make this the only thपढ़ो in the thपढ़ो group.
	 */
	retval = de_thपढ़ो(me);
	अगर (retval)
		जाओ out;

	/*
	 * Cancel any io_uring activity across execve
	 */
	io_uring_task_cancel();

	/* Ensure the files table is not shared. */
	retval = unshare_files();
	अगर (retval)
		जाओ out;

	/*
	 * Must be called _beक्रमe_ exec_mmap() as bprm->mm is
	 * not visibile until then. This also enables the update
	 * to be lockless.
	 */
	set_mm_exe_file(bprm->mm, bprm->file);

	/* If the binary is not पढ़ोable then enक्रमce mm->dumpable=0 */
	would_dump(bprm, bprm->file);
	अगर (bprm->have_execfd)
		would_dump(bprm, bprm->executable);

	/*
	 * Release all of the old mmap stuff
	 */
	acct_arg_size(bprm, 0);
	retval = exec_mmap(bprm->mm);
	अगर (retval)
		जाओ out;

	bprm->mm = शून्य;

#अगर_घोषित CONFIG_POSIX_TIMERS
	निकास_iसमयrs(me->संकेत);
	flush_iसमयr_संकेतs();
#पूर्ण_अगर

	/*
	 * Make the संकेत table निजी.
	 */
	retval = unshare_sighand(me);
	अगर (retval)
		जाओ out_unlock;

	/*
	 * Ensure that the uaccess routines can actually operate on userspace
	 * poपूर्णांकers:
	 */
	क्रमce_uaccess_begin();

	me->flags &= ~(PF_RANDOMIZE | PF_FORKNOEXEC | PF_KTHREAD |
					PF_NOFREEZE | PF_NO_SETAFFINITY);
	flush_thपढ़ो();
	me->personality &= ~bprm->per_clear;

	clear_syscall_work_syscall_user_dispatch(me);

	/*
	 * We have to apply CLOEXEC beक्रमe we change whether the process is
	 * dumpable (in setup_new_exec) to aव्योम a race with a process in userspace
	 * trying to access the should-be-बंदd file descriptors of a process
	 * undergoing exec(2).
	 */
	करो_बंद_on_exec(me->files);

	अगर (bprm->secureexec) अणु
		/* Make sure parent cannot संकेत privileged process. */
		me->pdeath_संकेत = 0;

		/*
		 * For secureexec, reset the stack limit to sane शेष to
		 * aव्योम bad behavior from the prior rlimits. This has to
		 * happen beक्रमe arch_pick_mmap_layout(), which examines
		 * RLIMIT_STACK, but after the poपूर्णांक of no वापस to aव्योम
		 * needing to clean up the change on failure.
		 */
		अगर (bprm->rlim_stack.rlim_cur > _STK_LIM)
			bprm->rlim_stack.rlim_cur = _STK_LIM;
	पूर्ण

	me->sas_ss_sp = me->sas_ss_size = 0;

	/*
	 * Figure out dumpability. Note that this checking only of current
	 * is wrong, but userspace depends on it. This should be testing
	 * bprm->secureexec instead.
	 */
	अगर (bprm->पूर्णांकerp_flags & BINPRM_FLAGS_ENFORCE_NONDUMP ||
	    !(uid_eq(current_euid(), current_uid()) &&
	      gid_eq(current_egid(), current_gid())))
		set_dumpable(current->mm, suid_dumpable);
	अन्यथा
		set_dumpable(current->mm, SUID_DUMP_USER);

	perf_event_exec();
	__set_task_comm(me, kbasename(bprm->filename), true);

	/* An exec changes our करोमुख्य. We are no दीर्घer part of the thपढ़ो
	   group */
	WRITE_ONCE(me->self_exec_id, me->self_exec_id + 1);
	flush_संकेत_handlers(me, 0);

	/*
	 * install the new credentials क्रम this executable
	 */
	security_bprm_committing_creds(bprm);

	commit_creds(bprm->cred);
	bprm->cred = शून्य;

	/*
	 * Disable monitoring क्रम regular users
	 * when executing setuid binaries. Must
	 * रुको until new credentials are committed
	 * by commit_creds() above
	 */
	अगर (get_dumpable(me->mm) != SUID_DUMP_USER)
		perf_event_निकास_task(me);
	/*
	 * cred_guard_mutex must be held at least to this poपूर्णांक to prevent
	 * ptrace_attach() from altering our determination of the task's
	 * credentials; any समय after this it may be unlocked.
	 */
	security_bprm_committed_creds(bprm);

	/* Pass the खोलोed binary to the पूर्णांकerpreter. */
	अगर (bprm->have_execfd) अणु
		retval = get_unused_fd_flags(0);
		अगर (retval < 0)
			जाओ out_unlock;
		fd_install(retval, bprm->executable);
		bprm->executable = शून्य;
		bprm->execfd = retval;
	पूर्ण
	वापस 0;

out_unlock:
	up_ग_लिखो(&me->संकेत->exec_update_lock);
out:
	वापस retval;
पूर्ण
EXPORT_SYMBOL(begin_new_exec);

व्योम would_dump(काष्ठा linux_binprm *bprm, काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा user_namespace *mnt_userns = file_mnt_user_ns(file);
	अगर (inode_permission(mnt_userns, inode, MAY_READ) < 0) अणु
		काष्ठा user_namespace *old, *user_ns;
		bprm->पूर्णांकerp_flags |= BINPRM_FLAGS_ENFORCE_NONDUMP;

		/* Ensure mm->user_ns contains the executable */
		user_ns = old = bprm->mm->user_ns;
		जबतक ((user_ns != &init_user_ns) &&
		       !privileged_wrt_inode_uidgid(user_ns, mnt_userns, inode))
			user_ns = user_ns->parent;

		अगर (old != user_ns) अणु
			bprm->mm->user_ns = get_user_ns(user_ns);
			put_user_ns(old);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(would_dump);

व्योम setup_new_exec(काष्ठा linux_binprm * bprm)
अणु
	/* Setup things that can depend upon the personality */
	काष्ठा task_काष्ठा *me = current;

	arch_pick_mmap_layout(me->mm, &bprm->rlim_stack);

	arch_setup_new_exec();

	/* Set the new mm task size. We have to करो that late because it may
	 * depend on TIF_32BIT which is only updated in flush_thपढ़ो() on
	 * some architectures like घातerpc
	 */
	me->mm->task_size = TASK_SIZE;
	up_ग_लिखो(&me->संकेत->exec_update_lock);
	mutex_unlock(&me->संकेत->cred_guard_mutex);
पूर्ण
EXPORT_SYMBOL(setup_new_exec);

/* Runs immediately beक्रमe start_thपढ़ो() takes over. */
व्योम finalize_exec(काष्ठा linux_binprm *bprm)
अणु
	/* Store any stack rlimit changes beक्रमe starting thपढ़ो. */
	task_lock(current->group_leader);
	current->संकेत->rlim[RLIMIT_STACK] = bprm->rlim_stack;
	task_unlock(current->group_leader);
पूर्ण
EXPORT_SYMBOL(finalize_exec);

/*
 * Prepare credentials and lock ->cred_guard_mutex.
 * setup_new_exec() commits the new creds and drops the lock.
 * Or, अगर exec fails beक्रमe, मुक्त_bprm() should release ->cred
 * and unlock.
 */
अटल पूर्णांक prepare_bprm_creds(काष्ठा linux_binprm *bprm)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&current->संकेत->cred_guard_mutex))
		वापस -ERESTARTNOINTR;

	bprm->cred = prepare_exec_creds();
	अगर (likely(bprm->cred))
		वापस 0;

	mutex_unlock(&current->संकेत->cred_guard_mutex);
	वापस -ENOMEM;
पूर्ण

अटल व्योम मुक्त_bprm(काष्ठा linux_binprm *bprm)
अणु
	अगर (bprm->mm) अणु
		acct_arg_size(bprm, 0);
		mmput(bprm->mm);
	पूर्ण
	मुक्त_arg_pages(bprm);
	अगर (bprm->cred) अणु
		mutex_unlock(&current->संकेत->cred_guard_mutex);
		पात_creds(bprm->cred);
	पूर्ण
	अगर (bprm->file) अणु
		allow_ग_लिखो_access(bprm->file);
		fput(bprm->file);
	पूर्ण
	अगर (bprm->executable)
		fput(bprm->executable);
	/* If a binfmt changed the पूर्णांकerp, मुक्त it. */
	अगर (bprm->पूर्णांकerp != bprm->filename)
		kमुक्त(bprm->पूर्णांकerp);
	kमुक्त(bprm->fdpath);
	kमुक्त(bprm);
पूर्ण

अटल काष्ठा linux_binprm *alloc_bprm(पूर्णांक fd, काष्ठा filename *filename)
अणु
	काष्ठा linux_binprm *bprm = kzalloc(माप(*bprm), GFP_KERNEL);
	पूर्णांक retval = -ENOMEM;
	अगर (!bprm)
		जाओ out;

	अगर (fd == AT_FDCWD || filename->name[0] == '/') अणु
		bprm->filename = filename->name;
	पूर्ण अन्यथा अणु
		अगर (filename->name[0] == '\0')
			bprm->fdpath = kaप्र_लिखो(GFP_KERNEL, "/dev/fd/%d", fd);
		अन्यथा
			bprm->fdpath = kaप्र_लिखो(GFP_KERNEL, "/dev/fd/%d/%s",
						  fd, filename->name);
		अगर (!bprm->fdpath)
			जाओ out_मुक्त;

		bprm->filename = bprm->fdpath;
	पूर्ण
	bprm->पूर्णांकerp = bprm->filename;

	retval = bprm_mm_init(bprm);
	अगर (retval)
		जाओ out_मुक्त;
	वापस bprm;

out_मुक्त:
	मुक्त_bprm(bprm);
out:
	वापस ERR_PTR(retval);
पूर्ण

पूर्णांक bprm_change_पूर्णांकerp(स्थिर अक्षर *पूर्णांकerp, काष्ठा linux_binprm *bprm)
अणु
	/* If a binfmt changed the पूर्णांकerp, मुक्त it first. */
	अगर (bprm->पूर्णांकerp != bprm->filename)
		kमुक्त(bprm->पूर्णांकerp);
	bprm->पूर्णांकerp = kstrdup(पूर्णांकerp, GFP_KERNEL);
	अगर (!bprm->पूर्णांकerp)
		वापस -ENOMEM;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bprm_change_पूर्णांकerp);

/*
 * determine how safe it is to execute the proposed program
 * - the caller must hold ->cred_guard_mutex to protect against
 *   PTRACE_ATTACH or seccomp thपढ़ो-sync
 */
अटल व्योम check_unsafe_exec(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा task_काष्ठा *p = current, *t;
	अचिन्हित n_fs;

	अगर (p->ptrace)
		bprm->unsafe |= LSM_UNSAFE_PTRACE;

	/*
	 * This isn't strictly necessary, but it makes it harder क्रम LSMs to
	 * mess up.
	 */
	अगर (task_no_new_privs(current))
		bprm->unsafe |= LSM_UNSAFE_NO_NEW_PRIVS;

	t = p;
	n_fs = 1;
	spin_lock(&p->fs->lock);
	rcu_पढ़ो_lock();
	जबतक_each_thपढ़ो(p, t) अणु
		अगर (t->fs == p->fs)
			n_fs++;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (p->fs->users > n_fs)
		bprm->unsafe |= LSM_UNSAFE_SHARE;
	अन्यथा
		p->fs->in_exec = 1;
	spin_unlock(&p->fs->lock);
पूर्ण

अटल व्योम bprm_fill_uid(काष्ठा linux_binprm *bprm, काष्ठा file *file)
अणु
	/* Handle suid and sgid on files */
	काष्ठा user_namespace *mnt_userns;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक mode;
	kuid_t uid;
	kgid_t gid;

	अगर (!mnt_may_suid(file->f_path.mnt))
		वापस;

	अगर (task_no_new_privs(current))
		वापस;

	inode = file->f_path.dentry->d_inode;
	mode = READ_ONCE(inode->i_mode);
	अगर (!(mode & (S_ISUID|S_ISGID)))
		वापस;

	mnt_userns = file_mnt_user_ns(file);

	/* Be careful अगर suid/sgid is set */
	inode_lock(inode);

	/* reload atomically mode/uid/gid now that lock held */
	mode = inode->i_mode;
	uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	gid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);
	inode_unlock(inode);

	/* We ignore suid/sgid अगर there are no mappings क्रम them in the ns */
	अगर (!kuid_has_mapping(bprm->cred->user_ns, uid) ||
		 !kgid_has_mapping(bprm->cred->user_ns, gid))
		वापस;

	अगर (mode & S_ISUID) अणु
		bprm->per_clear |= PER_CLEAR_ON_SETID;
		bprm->cred->euid = uid;
	पूर्ण

	अगर ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) अणु
		bprm->per_clear |= PER_CLEAR_ON_SETID;
		bprm->cred->egid = gid;
	पूर्ण
पूर्ण

/*
 * Compute brpm->cred based upon the final binary.
 */
अटल पूर्णांक bprm_creds_from_file(काष्ठा linux_binprm *bprm)
अणु
	/* Compute creds based on which file? */
	काष्ठा file *file = bprm->execfd_creds ? bprm->executable : bprm->file;

	bprm_fill_uid(bprm, file);
	वापस security_bprm_creds_from_file(bprm, file);
पूर्ण

/*
 * Fill the binprm काष्ठाure from the inode.
 * Read the first BINPRM_BUF_SIZE bytes
 *
 * This may be called multiple बार क्रम binary chains (scripts क्रम example).
 */
अटल पूर्णांक prepare_binprm(काष्ठा linux_binprm *bprm)
अणु
	loff_t pos = 0;

	स_रखो(bprm->buf, 0, BINPRM_BUF_SIZE);
	वापस kernel_पढ़ो(bprm->file, bprm->buf, BINPRM_BUF_SIZE, &pos);
पूर्ण

/*
 * Arguments are '\0' separated strings found at the location bprm->p
 * poपूर्णांकs to; chop off the first by relocating brpm->p to right after
 * the first '\0' encountered.
 */
पूर्णांक हटाओ_arg_zero(काष्ठा linux_binprm *bprm)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ offset;
	अक्षर *kaddr;
	काष्ठा page *page;

	अगर (!bprm->argc)
		वापस 0;

	करो अणु
		offset = bprm->p & ~PAGE_MASK;
		page = get_arg_page(bprm, bprm->p, 0);
		अगर (!page) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		kaddr = kmap_atomic(page);

		क्रम (; offset < PAGE_SIZE && kaddr[offset];
				offset++, bprm->p++)
			;

		kunmap_atomic(kaddr);
		put_arg_page(page);
	पूर्ण जबतक (offset == PAGE_SIZE);

	bprm->p++;
	bprm->argc--;
	ret = 0;

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(हटाओ_arg_zero);

#घोषणा prपूर्णांकable(c) (((c)=='\t') || ((c)=='\n') || (0x20<=(c) && (c)<=0x7e))
/*
 * cycle the list of binary क्रमmats handler, until one recognizes the image
 */
अटल पूर्णांक search_binary_handler(काष्ठा linux_binprm *bprm)
अणु
	bool need_retry = IS_ENABLED(CONFIG_MODULES);
	काष्ठा linux_binfmt *fmt;
	पूर्णांक retval;

	retval = prepare_binprm(bprm);
	अगर (retval < 0)
		वापस retval;

	retval = security_bprm_check(bprm);
	अगर (retval)
		वापस retval;

	retval = -ENOENT;
 retry:
	पढ़ो_lock(&binfmt_lock);
	list_क्रम_each_entry(fmt, &क्रमmats, lh) अणु
		अगर (!try_module_get(fmt->module))
			जारी;
		पढ़ो_unlock(&binfmt_lock);

		retval = fmt->load_binary(bprm);

		पढ़ो_lock(&binfmt_lock);
		put_binfmt(fmt);
		अगर (bprm->poपूर्णांक_of_no_वापस || (retval != -ENOEXEC)) अणु
			पढ़ो_unlock(&binfmt_lock);
			वापस retval;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&binfmt_lock);

	अगर (need_retry) अणु
		अगर (prपूर्णांकable(bprm->buf[0]) && prपूर्णांकable(bprm->buf[1]) &&
		    prपूर्णांकable(bprm->buf[2]) && prपूर्णांकable(bprm->buf[3]))
			वापस retval;
		अगर (request_module("binfmt-%04x", *(uलघु *)(bprm->buf + 2)) < 0)
			वापस retval;
		need_retry = false;
		जाओ retry;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक exec_binprm(काष्ठा linux_binprm *bprm)
अणु
	pid_t old_pid, old_vpid;
	पूर्णांक ret, depth;

	/* Need to fetch pid beक्रमe load_binary changes it */
	old_pid = current->pid;
	rcu_पढ़ो_lock();
	old_vpid = task_pid_nr_ns(current, task_active_pid_ns(current->parent));
	rcu_पढ़ो_unlock();

	/* This allows 4 levels of binfmt reग_लिखोs beक्रमe failing hard. */
	क्रम (depth = 0;; depth++) अणु
		काष्ठा file *exec;
		अगर (depth > 5)
			वापस -ELOOP;

		ret = search_binary_handler(bprm);
		अगर (ret < 0)
			वापस ret;
		अगर (!bprm->पूर्णांकerpreter)
			अवरोध;

		exec = bprm->file;
		bprm->file = bprm->पूर्णांकerpreter;
		bprm->पूर्णांकerpreter = शून्य;

		allow_ग_लिखो_access(exec);
		अगर (unlikely(bprm->have_execfd)) अणु
			अगर (bprm->executable) अणु
				fput(exec);
				वापस -ENOEXEC;
			पूर्ण
			bprm->executable = exec;
		पूर्ण अन्यथा
			fput(exec);
	पूर्ण

	audit_bprm(bprm);
	trace_sched_process_exec(current, old_pid, bprm);
	ptrace_event(PTRACE_EVENT_EXEC, old_vpid);
	proc_exec_connector(current);
	वापस 0;
पूर्ण

/*
 * sys_execve() executes a new program.
 */
अटल पूर्णांक bprm_execve(काष्ठा linux_binprm *bprm,
		       पूर्णांक fd, काष्ठा filename *filename, पूर्णांक flags)
अणु
	काष्ठा file *file;
	पूर्णांक retval;

	retval = prepare_bprm_creds(bprm);
	अगर (retval)
		वापस retval;

	check_unsafe_exec(bprm);
	current->in_execve = 1;

	file = करो_खोलो_execat(fd, filename, flags);
	retval = PTR_ERR(file);
	अगर (IS_ERR(file))
		जाओ out_unmark;

	sched_exec();

	bprm->file = file;
	/*
	 * Record that a name derived from an O_CLOEXEC fd will be
	 * inaccessible after exec.  This allows the code in exec to
	 * choose to fail when the executable is not mmaped पूर्णांकo the
	 * पूर्णांकerpreter and an खोलो file descriptor is not passed to
	 * the पूर्णांकerpreter.  This makes क्रम a better user experience
	 * than having the पूर्णांकerpreter start and then immediately fail
	 * when it finds the executable is inaccessible.
	 */
	अगर (bprm->fdpath && get_बंद_on_exec(fd))
		bprm->पूर्णांकerp_flags |= BINPRM_FLAGS_PATH_INACCESSIBLE;

	/* Set the unchanging part of bprm->cred */
	retval = security_bprm_creds_क्रम_exec(bprm);
	अगर (retval)
		जाओ out;

	retval = exec_binprm(bprm);
	अगर (retval < 0)
		जाओ out;

	/* execve succeeded */
	current->fs->in_exec = 0;
	current->in_execve = 0;
	rseq_execve(current);
	acct_update_पूर्णांकegrals(current);
	task_numa_मुक्त(current, false);
	वापस retval;

out:
	/*
	 * If past the poपूर्णांक of no वापस ensure the code never
	 * वापसs to the userspace process.  Use an existing fatal
	 * संकेत अगर present otherwise terminate the process with
	 * संक_अंश.
	 */
	अगर (bprm->poपूर्णांक_of_no_वापस && !fatal_संकेत_pending(current))
		क्रमce_sigsegv(संक_अंश);

out_unmark:
	current->fs->in_exec = 0;
	current->in_execve = 0;

	वापस retval;
पूर्ण

अटल पूर्णांक करो_execveat_common(पूर्णांक fd, काष्ठा filename *filename,
			      काष्ठा user_arg_ptr argv,
			      काष्ठा user_arg_ptr envp,
			      पूर्णांक flags)
अणु
	काष्ठा linux_binprm *bprm;
	पूर्णांक retval;

	अगर (IS_ERR(filename))
		वापस PTR_ERR(filename);

	/*
	 * We move the actual failure in हाल of RLIMIT_NPROC excess from
	 * set*uid() to execve() because too many poorly written programs
	 * करोn't check setuid() वापस code.  Here we additionally recheck
	 * whether NPROC limit is still exceeded.
	 */
	अगर ((current->flags & PF_NPROC_EXCEEDED) &&
	    atomic_पढ़ो(&current_user()->processes) > rlimit(RLIMIT_NPROC)) अणु
		retval = -EAGAIN;
		जाओ out_ret;
	पूर्ण

	/* We're below the limit (still or again), so we don't want to make
	 * further execve() calls fail. */
	current->flags &= ~PF_NPROC_EXCEEDED;

	bprm = alloc_bprm(fd, filename);
	अगर (IS_ERR(bprm)) अणु
		retval = PTR_ERR(bprm);
		जाओ out_ret;
	पूर्ण

	retval = count(argv, MAX_ARG_STRINGS);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->argc = retval;

	retval = count(envp, MAX_ARG_STRINGS);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->envc = retval;

	retval = bprm_stack_limits(bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = copy_string_kernel(bprm->filename, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->exec = bprm->p;

	retval = copy_strings(bprm->envc, envp, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = copy_strings(bprm->argc, argv, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = bprm_execve(bprm, fd, filename, flags);
out_मुक्त:
	मुक्त_bprm(bprm);

out_ret:
	putname(filename);
	वापस retval;
पूर्ण

पूर्णांक kernel_execve(स्थिर अक्षर *kernel_filename,
		  स्थिर अक्षर *स्थिर *argv, स्थिर अक्षर *स्थिर *envp)
अणु
	काष्ठा filename *filename;
	काष्ठा linux_binprm *bprm;
	पूर्णांक fd = AT_FDCWD;
	पूर्णांक retval;

	filename = getname_kernel(kernel_filename);
	अगर (IS_ERR(filename))
		वापस PTR_ERR(filename);

	bprm = alloc_bprm(fd, filename);
	अगर (IS_ERR(bprm)) अणु
		retval = PTR_ERR(bprm);
		जाओ out_ret;
	पूर्ण

	retval = count_strings_kernel(argv);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->argc = retval;

	retval = count_strings_kernel(envp);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->envc = retval;

	retval = bprm_stack_limits(bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = copy_string_kernel(bprm->filename, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;
	bprm->exec = bprm->p;

	retval = copy_strings_kernel(bprm->envc, envp, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = copy_strings_kernel(bprm->argc, argv, bprm);
	अगर (retval < 0)
		जाओ out_मुक्त;

	retval = bprm_execve(bprm, fd, filename, 0);
out_मुक्त:
	मुक्त_bprm(bprm);
out_ret:
	putname(filename);
	वापस retval;
पूर्ण

अटल पूर्णांक करो_execve(काष्ठा filename *filename,
	स्थिर अक्षर __user *स्थिर __user *__argv,
	स्थिर अक्षर __user *स्थिर __user *__envp)
अणु
	काष्ठा user_arg_ptr argv = अणु .ptr.native = __argv पूर्ण;
	काष्ठा user_arg_ptr envp = अणु .ptr.native = __envp पूर्ण;
	वापस करो_execveat_common(AT_FDCWD, filename, argv, envp, 0);
पूर्ण

अटल पूर्णांक करो_execveat(पूर्णांक fd, काष्ठा filename *filename,
		स्थिर अक्षर __user *स्थिर __user *__argv,
		स्थिर अक्षर __user *स्थिर __user *__envp,
		पूर्णांक flags)
अणु
	काष्ठा user_arg_ptr argv = अणु .ptr.native = __argv पूर्ण;
	काष्ठा user_arg_ptr envp = अणु .ptr.native = __envp पूर्ण;

	वापस करो_execveat_common(fd, filename, argv, envp, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक compat_करो_execve(काष्ठा filename *filename,
	स्थिर compat_uptr_t __user *__argv,
	स्थिर compat_uptr_t __user *__envp)
अणु
	काष्ठा user_arg_ptr argv = अणु
		.is_compat = true,
		.ptr.compat = __argv,
	पूर्ण;
	काष्ठा user_arg_ptr envp = अणु
		.is_compat = true,
		.ptr.compat = __envp,
	पूर्ण;
	वापस करो_execveat_common(AT_FDCWD, filename, argv, envp, 0);
पूर्ण

अटल पूर्णांक compat_करो_execveat(पूर्णांक fd, काष्ठा filename *filename,
			      स्थिर compat_uptr_t __user *__argv,
			      स्थिर compat_uptr_t __user *__envp,
			      पूर्णांक flags)
अणु
	काष्ठा user_arg_ptr argv = अणु
		.is_compat = true,
		.ptr.compat = __argv,
	पूर्ण;
	काष्ठा user_arg_ptr envp = अणु
		.is_compat = true,
		.ptr.compat = __envp,
	पूर्ण;
	वापस करो_execveat_common(fd, filename, argv, envp, flags);
पूर्ण
#पूर्ण_अगर

व्योम set_binfmt(काष्ठा linux_binfmt *new)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	अगर (mm->binfmt)
		module_put(mm->binfmt->module);

	mm->binfmt = new;
	अगर (new)
		__module_get(new->module);
पूर्ण
EXPORT_SYMBOL(set_binfmt);

/*
 * set_dumpable stores three-value SUID_DUMP_* पूर्णांकo mm->flags.
 */
व्योम set_dumpable(काष्ठा mm_काष्ठा *mm, पूर्णांक value)
अणु
	अगर (WARN_ON((अचिन्हित)value > SUID_DUMP_ROOT))
		वापस;

	set_mask_bits(&mm->flags, MMF_DUMPABLE_MASK, value);
पूर्ण

SYSCALL_DEFINE3(execve,
		स्थिर अक्षर __user *, filename,
		स्थिर अक्षर __user *स्थिर __user *, argv,
		स्थिर अक्षर __user *स्थिर __user *, envp)
अणु
	वापस करो_execve(getname(filename), argv, envp);
पूर्ण

SYSCALL_DEFINE5(execveat,
		पूर्णांक, fd, स्थिर अक्षर __user *, filename,
		स्थिर अक्षर __user *स्थिर __user *, argv,
		स्थिर अक्षर __user *स्थिर __user *, envp,
		पूर्णांक, flags)
अणु
	पूर्णांक lookup_flags = (flags & AT_EMPTY_PATH) ? LOOKUP_EMPTY : 0;

	वापस करो_execveat(fd,
			   getname_flags(filename, lookup_flags, शून्य),
			   argv, envp, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE3(execve, स्थिर अक्षर __user *, filename,
	स्थिर compat_uptr_t __user *, argv,
	स्थिर compat_uptr_t __user *, envp)
अणु
	वापस compat_करो_execve(getname(filename), argv, envp);
पूर्ण

COMPAT_SYSCALL_DEFINE5(execveat, पूर्णांक, fd,
		       स्थिर अक्षर __user *, filename,
		       स्थिर compat_uptr_t __user *, argv,
		       स्थिर compat_uptr_t __user *, envp,
		       पूर्णांक,  flags)
अणु
	पूर्णांक lookup_flags = (flags & AT_EMPTY_PATH) ? LOOKUP_EMPTY : 0;

	वापस compat_करो_execveat(fd,
				  getname_flags(filename, lookup_flags, शून्य),
				  argv, envp, flags);
पूर्ण
#पूर्ण_अगर
