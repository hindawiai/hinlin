<शैली गुरु>
/*
 * Copyright (C) 2005 Paolo 'Blaisorblade' Giarrusso <blaisorblade@yahoo.it>
 * Licensed under the GPL
 */

#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace-abi.h>
#समावेश <os.h>
#समावेश <skas.h>
#समावेश <sysdep/tls.h>

/*
 * If needed we can detect when it's uninitialized.
 *
 * These are initialized in an initcall and unchanged thereafter.
 */
अटल पूर्णांक host_supports_tls = -1;
पूर्णांक host_gdt_entry_tls_min;

पूर्णांक करो_set_thपढ़ो_area(काष्ठा user_desc *info)
अणु
	पूर्णांक ret;
	u32 cpu;

	cpu = get_cpu();
	ret = os_set_thपढ़ो_area(info, userspace_pid[cpu]);
	put_cpu();

	अगर (ret)
		prपूर्णांकk(KERN_ERR "PTRACE_SET_THREAD_AREA failed, err = %d, "
		       "index = %d\n", ret, info->entry_number);

	वापस ret;
पूर्ण

पूर्णांक करो_get_thपढ़ो_area(काष्ठा user_desc *info)
अणु
	पूर्णांक ret;
	u32 cpu;

	cpu = get_cpu();
	ret = os_get_thपढ़ो_area(info, userspace_pid[cpu]);
	put_cpu();

	अगर (ret)
		prपूर्णांकk(KERN_ERR "PTRACE_GET_THREAD_AREA failed, err = %d, "
		       "index = %d\n", ret, info->entry_number);

	वापस ret;
पूर्ण

/*
 * sys_get_thपढ़ो_area: get a yet unused TLS descriptor index.
 * XXX: Consider leaving one मुक्त slot क्रम glibc usage at first place. This must
 * be करोne here (and by changing GDT_ENTRY_TLS_* macros) and nowhere अन्यथा.
 *
 * Also, this must be tested when compiling in SKAS mode with dynamic linking
 * and running against NPTL.
 */
अटल पूर्णांक get_मुक्त_idx(काष्ठा task_काष्ठा* task)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &task->thपढ़ो;
	पूर्णांक idx;

	अगर (!t->arch.tls_array)
		वापस GDT_ENTRY_TLS_MIN;

	क्रम (idx = 0; idx < GDT_ENTRY_TLS_ENTRIES; idx++)
		अगर (!t->arch.tls_array[idx].present)
			वापस idx + GDT_ENTRY_TLS_MIN;
	वापस -ESRCH;
पूर्ण

अटल अंतरभूत व्योम clear_user_desc(काष्ठा user_desc* info)
अणु
	/* Postcondition: LDT_empty(info) वापसs true. */
	स_रखो(info, 0, माप(*info));

	/*
	 * Check the LDT_empty or the i386 sys_get_thपढ़ो_area code - we obtain
	 * indeed an empty user_desc.
	 */
	info->पढ़ो_exec_only = 1;
	info->seg_not_present = 1;
पूर्ण

#घोषणा O_FORCE 1

अटल पूर्णांक load_TLS(पूर्णांक flags, काष्ठा task_काष्ठा *to)
अणु
	पूर्णांक ret = 0;
	पूर्णांक idx;

	क्रम (idx = GDT_ENTRY_TLS_MIN; idx < GDT_ENTRY_TLS_MAX; idx++) अणु
		काष्ठा uml_tls_काष्ठा* curr =
			&to->thपढ़ो.arch.tls_array[idx - GDT_ENTRY_TLS_MIN];

		/*
		 * Actually, now अगर it wasn't flushed it माला_लो cleared and
		 * flushed to the host, which will clear it.
		 */
		अगर (!curr->present) अणु
			अगर (!curr->flushed) अणु
				clear_user_desc(&curr->tls);
				curr->tls.entry_number = idx;
			पूर्ण अन्यथा अणु
				WARN_ON(!LDT_empty(&curr->tls));
				जारी;
			पूर्ण
		पूर्ण

		अगर (!(flags & O_FORCE) && curr->flushed)
			जारी;

		ret = करो_set_thपढ़ो_area(&curr->tls);
		अगर (ret)
			जाओ out;

		curr->flushed = 1;
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Verअगरy अगर we need to करो a flush क्रम the new process, i.e. अगर there are any
 * present desc's, only if they haven't been flushed.
 */
अटल अंतरभूत पूर्णांक needs_TLS_update(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = GDT_ENTRY_TLS_MIN; i < GDT_ENTRY_TLS_MAX; i++) अणु
		काष्ठा uml_tls_काष्ठा* curr =
			&task->thपढ़ो.arch.tls_array[i - GDT_ENTRY_TLS_MIN];

		/*
		 * Can't test curr->present, we may need to clear a descriptor
		 * which had a value.
		 */
		अगर (curr->flushed)
			जारी;
		ret = 1;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * On a newly विभाजनed process, the TLS descriptors haven't yet been flushed. So
 * we mark them as such and the first चयन_to will करो the job.
 */
व्योम clear_flushed_tls(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक i;

	क्रम (i = GDT_ENTRY_TLS_MIN; i < GDT_ENTRY_TLS_MAX; i++) अणु
		काष्ठा uml_tls_काष्ठा* curr =
			&task->thपढ़ो.arch.tls_array[i - GDT_ENTRY_TLS_MIN];

		/*
		 * Still correct to करो this, अगर it wasn't present on the host it
		 * will reमुख्य as flushed as it was.
		 */
		अगर (!curr->present)
			जारी;

		curr->flushed = 0;
	पूर्ण
पूर्ण

/*
 * In SKAS0 mode, currently, multiple guest thपढ़ोs sharing the same ->mm have a
 * common host process. So this is needed in SKAS0 too.
 *
 * However, अगर each thपढ़ो had a dअगरferent host process (and this was discussed
 * क्रम SMP support) this won't be needed.
 *
 * And this will not need be used when (and अगर) we'll add support to the host
 * SKAS patch.
 */

पूर्णांक arch_चयन_tls(काष्ठा task_काष्ठा *to)
अणु
	अगर (!host_supports_tls)
		वापस 0;

	/*
	 * We have no need whatsoever to चयन TLS क्रम kernel thपढ़ोs; beyond
	 * that, that would also result in us calling os_set_thपढ़ो_area with
	 * userspace_pid[cpu] == 0, which gives an error.
	 */
	अगर (likely(to->mm))
		वापस load_TLS(O_FORCE, to);

	वापस 0;
पूर्ण

अटल पूर्णांक set_tls_entry(काष्ठा task_काष्ठा* task, काष्ठा user_desc *info,
			 पूर्णांक idx, पूर्णांक flushed)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &task->thपढ़ो;

	अगर (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		वापस -EINVAL;

	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].tls = *info;
	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].present = 1;
	t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].flushed = flushed;

	वापस 0;
पूर्ण

पूर्णांक arch_set_tls(काष्ठा task_काष्ठा *new, अचिन्हित दीर्घ tls)
अणु
	काष्ठा user_desc info;
	पूर्णांक idx, ret = -EFAULT;

	अगर (copy_from_user(&info, (व्योम __user *) tls, माप(info)))
		जाओ out;

	ret = -EINVAL;
	अगर (LDT_empty(&info))
		जाओ out;

	idx = info.entry_number;

	ret = set_tls_entry(new, &info, idx, 0);
out:
	वापस ret;
पूर्ण

/* XXX: use करो_get_thपढ़ो_area to पढ़ो the host value? I'm not at all sure! */
अटल पूर्णांक get_tls_entry(काष्ठा task_काष्ठा *task, काष्ठा user_desc *info,
			 पूर्णांक idx)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &task->thपढ़ो;

	अगर (!t->arch.tls_array)
		जाओ clear;

	अगर (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		वापस -EINVAL;

	अगर (!t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].present)
		जाओ clear;

	*info = t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].tls;

out:
	/*
	 * Temporary debugging check, to make sure that things have been
	 * flushed. This could be triggered अगर load_TLS() failed.
	 */
	अगर (unlikely(task == current &&
		     !t->arch.tls_array[idx - GDT_ENTRY_TLS_MIN].flushed)) अणु
		prपूर्णांकk(KERN_ERR "get_tls_entry: task with pid %d got here "
				"without flushed TLS.", current->pid);
	पूर्ण

	वापस 0;
clear:
	/*
	 * When the TLS entry has not been set, the values पढ़ो to user in the
	 * tls_array are 0 (because it's cleared at boot, see
	 * arch/i386/kernel/head.S:cpu_gdt_table). Emulate that.
	 */
	clear_user_desc(info);
	info->entry_number = idx;
	जाओ out;
पूर्ण

SYSCALL_DEFINE1(set_thपढ़ो_area, काष्ठा user_desc __user *, user_desc)
अणु
	काष्ठा user_desc info;
	पूर्णांक idx, ret;

	अगर (!host_supports_tls)
		वापस -ENOSYS;

	अगर (copy_from_user(&info, user_desc, माप(info)))
		वापस -EFAULT;

	idx = info.entry_number;

	अगर (idx == -1) अणु
		idx = get_मुक्त_idx(current);
		अगर (idx < 0)
			वापस idx;
		info.entry_number = idx;
		/* Tell the user which slot we chose क्रम him.*/
		अगर (put_user(idx, &user_desc->entry_number))
			वापस -EFAULT;
	पूर्ण

	ret = करो_set_thपढ़ो_area(&info);
	अगर (ret)
		वापस ret;
	वापस set_tls_entry(current, &info, idx, 1);
पूर्ण

/*
 * Perक्रमm set_thपढ़ो_area on behalf of the traced child.
 * Note: error handling is not करोne on the deferred load, and this dअगरfer from
 * i386. However the only possible error are caused by bugs.
 */
पूर्णांक ptrace_set_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
			   काष्ठा user_desc __user *user_desc)
अणु
	काष्ठा user_desc info;

	अगर (!host_supports_tls)
		वापस -EIO;

	अगर (copy_from_user(&info, user_desc, माप(info)))
		वापस -EFAULT;

	वापस set_tls_entry(child, &info, idx, 0);
पूर्ण

SYSCALL_DEFINE1(get_thपढ़ो_area, काष्ठा user_desc __user *, user_desc)
अणु
	काष्ठा user_desc info;
	पूर्णांक idx, ret;

	अगर (!host_supports_tls)
		वापस -ENOSYS;

	अगर (get_user(idx, &user_desc->entry_number))
		वापस -EFAULT;

	ret = get_tls_entry(current, &info, idx);
	अगर (ret < 0)
		जाओ out;

	अगर (copy_to_user(user_desc, &info, माप(info)))
		ret = -EFAULT;

out:
	वापस ret;
पूर्ण

/*
 * Perक्रमm get_thपढ़ो_area on behalf of the traced child.
 */
पूर्णांक ptrace_get_thपढ़ो_area(काष्ठा task_काष्ठा *child, पूर्णांक idx,
		काष्ठा user_desc __user *user_desc)
अणु
	काष्ठा user_desc info;
	पूर्णांक ret;

	अगर (!host_supports_tls)
		वापस -EIO;

	ret = get_tls_entry(child, &info, idx);
	अगर (ret < 0)
		जाओ out;

	अगर (copy_to_user(user_desc, &info, माप(info)))
		ret = -EFAULT;
out:
	वापस ret;
पूर्ण

/*
 * This code is really i386-only, but it detects and logs x86_64 GDT indexes
 * अगर a 32-bit UML is running on a 64-bit host.
 */
अटल पूर्णांक __init __setup_host_supports_tls(व्योम)
अणु
	check_host_supports_tls(&host_supports_tls, &host_gdt_entry_tls_min);
	अगर (host_supports_tls) अणु
		prपूर्णांकk(KERN_INFO "Host TLS support detected\n");
		prपूर्णांकk(KERN_INFO "Detected host type: ");
		चयन (host_gdt_entry_tls_min) अणु
		हाल GDT_ENTRY_TLS_MIN_I386:
			prपूर्णांकk(KERN_CONT "i386");
			अवरोध;
		हाल GDT_ENTRY_TLS_MIN_X86_64:
			prपूर्णांकk(KERN_CONT "x86_64");
			अवरोध;
		पूर्ण
		prपूर्णांकk(KERN_CONT " (GDT indexes %d to %d)\n",
		       host_gdt_entry_tls_min,
		       host_gdt_entry_tls_min + GDT_ENTRY_TLS_ENTRIES);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "  Host TLS support NOT detected! "
				"TLS support inside UML will not work\n");
	वापस 0;
पूर्ण

__initcall(__setup_host_supports_tls);
