<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/mm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/swap.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/key.h>
#समावेश <linux/personality.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/coredump.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
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
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/oom.h>
#समावेश <linux/compat.h>
#समावेश <linux/fs.h>
#समावेश <linux/path.h>
#समावेश <linux/समयkeeping.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/exec.h>

#समावेश <trace/events/task.h>
#समावेश "internal.h"

#समावेश <trace/events/sched.h>

पूर्णांक core_uses_pid;
अचिन्हित पूर्णांक core_pipe_limit;
अक्षर core_pattern[CORENAME_MAX_SIZE] = "core";
अटल पूर्णांक core_name_size = CORENAME_MAX_SIZE;

काष्ठा core_name अणु
	अक्षर *coनाम;
	पूर्णांक used, size;
पूर्ण;

/* The maximal length of core_pattern is also specअगरied in sysctl.c */

अटल पूर्णांक expand_coनाम(काष्ठा core_name *cn, पूर्णांक size)
अणु
	अक्षर *coनाम = kपुनः_स्मृति(cn->coनाम, size, GFP_KERNEL);

	अगर (!coनाम)
		वापस -ENOMEM;

	अगर (size > core_name_size) /* racy but harmless */
		core_name_size = size;

	cn->size = ksize(coनाम);
	cn->coनाम = coनाम;
	वापस 0;
पूर्ण

अटल __म_लिखो(2, 0) पूर्णांक cn_भ_लिखो(काष्ठा core_name *cn, स्थिर अक्षर *fmt,
				     बहु_सूची arg)
अणु
	पूर्णांक मुक्त, need;
	बहु_सूची arg_copy;

again:
	मुक्त = cn->size - cn->used;

	va_copy(arg_copy, arg);
	need = vsnम_लिखो(cn->coनाम + cn->used, मुक्त, fmt, arg_copy);
	बहु_पूर्ण(arg_copy);

	अगर (need < मुक्त) अणु
		cn->used += need;
		वापस 0;
	पूर्ण

	अगर (!expand_coनाम(cn, cn->size + need - मुक्त + 1))
		जाओ again;

	वापस -ENOMEM;
पूर्ण

अटल __म_लिखो(2, 3) पूर्णांक cn_म_लिखो(काष्ठा core_name *cn, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची arg;
	पूर्णांक ret;

	बहु_शुरू(arg, fmt);
	ret = cn_भ_लिखो(cn, fmt, arg);
	बहु_पूर्ण(arg);

	वापस ret;
पूर्ण

अटल __म_लिखो(2, 3)
पूर्णांक cn_esc_म_लिखो(काष्ठा core_name *cn, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक cur = cn->used;
	बहु_सूची arg;
	पूर्णांक ret;

	बहु_शुरू(arg, fmt);
	ret = cn_भ_लिखो(cn, fmt, arg);
	बहु_पूर्ण(arg);

	अगर (ret == 0) अणु
		/*
		 * Ensure that this coredump name component can't cause the
		 * resulting corefile path to consist of a ".." or ".".
		 */
		अगर ((cn->used - cur == 1 && cn->coनाम[cur] == '.') ||
				(cn->used - cur == 2 && cn->coनाम[cur] == '.'
				&& cn->coनाम[cur+1] == '.'))
			cn->coनाम[cur] = '!';

		/*
		 * Empty names are fishy and could be used to create a "//" in a
		 * corefile name, causing the coredump to happen one directory
		 * level too high. Enक्रमce that all components of the core
		 * pattern are at least one अक्षरacter दीर्घ.
		 */
		अगर (cn->used == cur)
			ret = cn_म_लिखो(cn, "!");
	पूर्ण

	क्रम (; cur < cn->used; ++cur) अणु
		अगर (cn->coनाम[cur] == '/')
			cn->coनाम[cur] = '!';
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cn_prपूर्णांक_exe_file(काष्ठा core_name *cn, bool name_only)
अणु
	काष्ठा file *exe_file;
	अक्षर *pathbuf, *path, *ptr;
	पूर्णांक ret;

	exe_file = get_mm_exe_file(current->mm);
	अगर (!exe_file)
		वापस cn_esc_म_लिखो(cn, "%s (path unknown)", current->comm);

	pathbuf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!pathbuf) अणु
		ret = -ENOMEM;
		जाओ put_exe_file;
	पूर्ण

	path = file_path(exe_file, pathbuf, PATH_MAX);
	अगर (IS_ERR(path)) अणु
		ret = PTR_ERR(path);
		जाओ मुक्त_buf;
	पूर्ण

	अगर (name_only) अणु
		ptr = म_खोजप(path, '/');
		अगर (ptr)
			path = ptr + 1;
	पूर्ण
	ret = cn_esc_म_लिखो(cn, "%s", path);

मुक्त_buf:
	kमुक्त(pathbuf);
put_exe_file:
	fput(exe_file);
	वापस ret;
पूर्ण

/* क्रमmat_coनाम will inspect the pattern parameter, and output a
 * name पूर्णांकo coनाम, which must have space क्रम at least
 * CORENAME_MAX_SIZE bytes plus one byte क्रम the zero terminator.
 */
अटल पूर्णांक क्रमmat_coनाम(काष्ठा core_name *cn, काष्ठा coredump_params *cprm,
			   माप_प्रकार **argv, पूर्णांक *argc)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	स्थिर अक्षर *pat_ptr = core_pattern;
	पूर्णांक ispipe = (*pat_ptr == '|');
	bool was_space = false;
	पूर्णांक pid_in_pattern = 0;
	पूर्णांक err = 0;

	cn->used = 0;
	cn->coनाम = शून्य;
	अगर (expand_coनाम(cn, core_name_size))
		वापस -ENOMEM;
	cn->coनाम[0] = '\0';

	अगर (ispipe) अणु
		पूर्णांक argvs = माप(core_pattern) / 2;
		(*argv) = kदो_स्मृति_array(argvs, माप(**argv), GFP_KERNEL);
		अगर (!(*argv))
			वापस -ENOMEM;
		(*argv)[(*argc)++] = 0;
		++pat_ptr;
		अगर (!(*pat_ptr))
			वापस -ENOMEM;
	पूर्ण

	/* Repeat as दीर्घ as we have more pattern to process and more output
	   space */
	जबतक (*pat_ptr) अणु
		/*
		 * Split on spaces beक्रमe करोing ढाँचा expansion so that
		 * %e and %E करोn't get split अगर they have spaces in them
		 */
		अगर (ispipe) अणु
			अगर (है_खाली(*pat_ptr)) अणु
				अगर (cn->used != 0)
					was_space = true;
				pat_ptr++;
				जारी;
			पूर्ण अन्यथा अगर (was_space) अणु
				was_space = false;
				err = cn_म_लिखो(cn, "%c", '\0');
				अगर (err)
					वापस err;
				(*argv)[(*argc)++] = cn->used;
			पूर्ण
		पूर्ण
		अगर (*pat_ptr != '%') अणु
			err = cn_म_लिखो(cn, "%c", *pat_ptr++);
		पूर्ण अन्यथा अणु
			चयन (*++pat_ptr) अणु
			/* single % at the end, drop that */
			हाल 0:
				जाओ out;
			/* Double percent, output one percent */
			हाल '%':
				err = cn_म_लिखो(cn, "%c", '%');
				अवरोध;
			/* pid */
			हाल 'p':
				pid_in_pattern = 1;
				err = cn_म_लिखो(cn, "%d",
					      task_tgid_vnr(current));
				अवरोध;
			/* global pid */
			हाल 'P':
				err = cn_म_लिखो(cn, "%d",
					      task_tgid_nr(current));
				अवरोध;
			हाल 'i':
				err = cn_म_लिखो(cn, "%d",
					      task_pid_vnr(current));
				अवरोध;
			हाल 'I':
				err = cn_म_लिखो(cn, "%d",
					      task_pid_nr(current));
				अवरोध;
			/* uid */
			हाल 'u':
				err = cn_म_लिखो(cn, "%u",
						from_kuid(&init_user_ns,
							  cred->uid));
				अवरोध;
			/* gid */
			हाल 'g':
				err = cn_म_लिखो(cn, "%u",
						from_kgid(&init_user_ns,
							  cred->gid));
				अवरोध;
			हाल 'd':
				err = cn_म_लिखो(cn, "%d",
					__get_dumpable(cprm->mm_flags));
				अवरोध;
			/* संकेत that caused the coredump */
			हाल 's':
				err = cn_म_लिखो(cn, "%d",
						cprm->siginfo->si_signo);
				अवरोध;
			/* UNIX समय of coredump */
			हाल 't': अणु
				समय64_t समय;

				समय = kसमय_get_real_seconds();
				err = cn_म_लिखो(cn, "%lld", समय);
				अवरोध;
			पूर्ण
			/* hostname */
			हाल 'h':
				करोwn_पढ़ो(&uts_sem);
				err = cn_esc_म_लिखो(cn, "%s",
					      utsname()->nodename);
				up_पढ़ो(&uts_sem);
				अवरोध;
			/* executable, could be changed by prctl PR_SET_NAME etc */
			हाल 'e':
				err = cn_esc_म_लिखो(cn, "%s", current->comm);
				अवरोध;
			/* file name of executable */
			हाल 'f':
				err = cn_prपूर्णांक_exe_file(cn, true);
				अवरोध;
			हाल 'E':
				err = cn_prपूर्णांक_exe_file(cn, false);
				अवरोध;
			/* core limit size */
			हाल 'c':
				err = cn_म_लिखो(cn, "%lu",
					      rlimit(RLIMIT_CORE));
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			++pat_ptr;
		पूर्ण

		अगर (err)
			वापस err;
	पूर्ण

out:
	/* Backward compatibility with core_uses_pid:
	 *
	 * If core_pattern करोes not include a %p (as is the शेष)
	 * and core_uses_pid is set, then .%pid will be appended to
	 * the filename. Do not करो this क्रम piped commands. */
	अगर (!ispipe && !pid_in_pattern && core_uses_pid) अणु
		err = cn_म_लिखो(cn, ".%d", task_tgid_vnr(current));
		अगर (err)
			वापस err;
	पूर्ण
	वापस ispipe;
पूर्ण

अटल पूर्णांक zap_process(काष्ठा task_काष्ठा *start, पूर्णांक निकास_code, पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *t;
	पूर्णांक nr = 0;

	/* ignore all संकेतs except SIGKILL, see prepare_संकेत() */
	start->संकेत->flags = SIGNAL_GROUP_COREDUMP | flags;
	start->संकेत->group_निकास_code = निकास_code;
	start->संकेत->group_stop_count = 0;

	क्रम_each_thपढ़ो(start, t) अणु
		task_clear_jobctl_pending(t, JOBCTL_PENDING_MASK);
		अगर (t != current && t->mm) अणु
			sigaddset(&t->pending.संकेत, SIGKILL);
			संकेत_wake_up(t, 1);
			nr++;
		पूर्ण
	पूर्ण

	वापस nr;
पूर्ण

अटल पूर्णांक zap_thपढ़ोs(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm,
			काष्ठा core_state *core_state, पूर्णांक निकास_code)
अणु
	काष्ठा task_काष्ठा *g, *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक nr = -EAGAIN;

	spin_lock_irq(&tsk->sighand->siglock);
	अगर (!संकेत_group_निकास(tsk->संकेत)) अणु
		mm->core_state = core_state;
		tsk->संकेत->group_निकास_task = tsk;
		nr = zap_process(tsk, निकास_code, 0);
		clear_tsk_thपढ़ो_flag(tsk, TIF_SIGPENDING);
	पूर्ण
	spin_unlock_irq(&tsk->sighand->siglock);
	अगर (unlikely(nr < 0))
		वापस nr;

	tsk->flags |= PF_DUMPCORE;
	अगर (atomic_पढ़ो(&mm->mm_users) == nr + 1)
		जाओ करोne;
	/*
	 * We should find and समाप्त all tasks which use this mm, and we should
	 * count them correctly पूर्णांकo ->nr_thपढ़ोs. We करोn't take tasklist
	 * lock, but this is safe wrt:
	 *
	 * विभाजन:
	 *	None of sub-thपढ़ोs can विभाजन after zap_process(leader). All
	 *	processes which were created beक्रमe this poपूर्णांक should be
	 *	visible to zap_thपढ़ोs() because copy_process() adds the new
	 *	process to the tail of init_task.tasks list, and lock/unlock
	 *	of ->siglock provides a memory barrier.
	 *
	 * करो_निकास:
	 *	The caller holds mm->mmap_lock. This means that the task which
	 *	uses this mm can't pass exit_mm(), so it can't निकास or clear
	 *	its ->mm.
	 *
	 * de_thपढ़ो:
	 *	It करोes list_replace_rcu(&leader->tasks, &current->tasks),
	 *	we must see either old or new leader, this करोes not matter.
	 *	However, it can change p->sighand, so lock_task_sighand(p)
	 *	must be used. Since p->mm != शून्य and we hold ->mmap_lock
	 *	it can't fail.
	 *
	 *	Note also that "g" can be the old leader with ->mm == शून्य
	 *	and alपढ़ोy unhashed and thus हटाओd from ->thपढ़ो_group.
	 *	This is OK, __unhash_process()->list_del_rcu() करोes not
	 *	clear the ->next poपूर्णांकer, we will find the new leader via
	 *	next_thपढ़ो().
	 */
	rcu_पढ़ो_lock();
	क्रम_each_process(g) अणु
		अगर (g == tsk->group_leader)
			जारी;
		अगर (g->flags & PF_KTHREAD)
			जारी;

		क्रम_each_thपढ़ो(g, p) अणु
			अगर (unlikely(!p->mm))
				जारी;
			अगर (unlikely(p->mm == mm)) अणु
				lock_task_sighand(p, &flags);
				nr += zap_process(p, निकास_code,
							SIGNAL_GROUP_EXIT);
				unlock_task_sighand(p, &flags);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
करोne:
	atomic_set(&core_state->nr_thपढ़ोs, nr);
	वापस nr;
पूर्ण

अटल पूर्णांक coredump_रुको(पूर्णांक निकास_code, काष्ठा core_state *core_state)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा mm_काष्ठा *mm = tsk->mm;
	पूर्णांक core_रुकोers = -EBUSY;

	init_completion(&core_state->startup);
	core_state->dumper.task = tsk;
	core_state->dumper.next = शून्य;

	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	अगर (!mm->core_state)
		core_रुकोers = zap_thपढ़ोs(tsk, mm, core_state, निकास_code);
	mmap_ग_लिखो_unlock(mm);

	अगर (core_रुकोers > 0) अणु
		काष्ठा core_thपढ़ो *ptr;

		मुक्तzer_करो_not_count();
		रुको_क्रम_completion(&core_state->startup);
		मुक्तzer_count();
		/*
		 * Wait क्रम all the thपढ़ोs to become inactive, so that
		 * all the thपढ़ो context (extended रेजिस्टर state, like
		 * fpu etc) माला_लो copied to the memory.
		 */
		ptr = core_state->dumper.next;
		जबतक (ptr != शून्य) अणु
			रुको_task_inactive(ptr->task, 0);
			ptr = ptr->next;
		पूर्ण
	पूर्ण

	वापस core_रुकोers;
पूर्ण

अटल व्योम coredump_finish(काष्ठा mm_काष्ठा *mm, bool core_dumped)
अणु
	काष्ठा core_thपढ़ो *curr, *next;
	काष्ठा task_काष्ठा *task;

	spin_lock_irq(&current->sighand->siglock);
	अगर (core_dumped && !__fatal_संकेत_pending(current))
		current->संकेत->group_निकास_code |= 0x80;
	current->संकेत->group_निकास_task = शून्य;
	current->संकेत->flags = SIGNAL_GROUP_EXIT;
	spin_unlock_irq(&current->sighand->siglock);

	next = mm->core_state->dumper.next;
	जबतक ((curr = next) != शून्य) अणु
		next = curr->next;
		task = curr->task;
		/*
		 * see निकास_mm(), curr->task must not see
		 * ->task == शून्य beक्रमe we पढ़ो ->next.
		 */
		smp_mb();
		curr->task = शून्य;
		wake_up_process(task);
	पूर्ण

	mm->core_state = शून्य;
पूर्ण

अटल bool dump_पूर्णांकerrupted(व्योम)
अणु
	/*
	 * SIGKILL or मुक्तzing() पूर्णांकerrupt the coredumping. Perhaps we
	 * can करो try_to_मुक्तze() and check __fatal_संकेत_pending(),
	 * but then we need to teach dump_ग_लिखो() to restart and clear
	 * TIF_SIGPENDING.
	 */
	वापस fatal_संकेत_pending(current) || मुक्तzing(current);
पूर्ण

अटल व्योम रुको_क्रम_dump_helpers(काष्ठा file *file)
अणु
	काष्ठा pipe_inode_info *pipe = file->निजी_data;

	pipe_lock(pipe);
	pipe->पढ़ोers++;
	pipe->ग_लिखोrs--;
	wake_up_पूर्णांकerruptible_sync(&pipe->rd_रुको);
	समाप्त_fasync(&pipe->fasync_पढ़ोers, SIGIO, POLL_IN);
	pipe_unlock(pipe);

	/*
	 * We actually want रुको_event_मुक्तzable() but then we need
	 * to clear TIF_SIGPENDING and improve dump_पूर्णांकerrupted().
	 */
	रुको_event_पूर्णांकerruptible(pipe->rd_रुको, pipe->पढ़ोers == 1);

	pipe_lock(pipe);
	pipe->पढ़ोers--;
	pipe->ग_लिखोrs++;
	pipe_unlock(pipe);
पूर्ण

/*
 * umh_pipe_setup
 * helper function to customize the process used
 * to collect the core in userspace.  Specअगरically
 * it sets up a pipe and installs it as fd 0 (मानक_निवेश)
 * क्रम the process.  Returns 0 on success, or
 * PTR_ERR on failure.
 * Note that it also sets the core limit to 1.  This
 * is a special value that we use to trap recursive
 * core dumps
 */
अटल पूर्णांक umh_pipe_setup(काष्ठा subprocess_info *info, काष्ठा cred *new)
अणु
	काष्ठा file *files[2];
	काष्ठा coredump_params *cp = (काष्ठा coredump_params *)info->data;
	पूर्णांक err = create_pipe_files(files, 0);
	अगर (err)
		वापस err;

	cp->file = files[1];

	err = replace_fd(0, files[0], 0);
	fput(files[0]);
	/* and disallow core files too */
	current->संकेत->rlim[RLIMIT_CORE] = (काष्ठा rlimit)अणु1, 1पूर्ण;

	वापस err;
पूर्ण

व्योम करो_coredump(स्थिर kernel_siginfo_t *siginfo)
अणु
	काष्ठा core_state core_state;
	काष्ठा core_name cn;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा linux_binfmt * binfmt;
	स्थिर काष्ठा cred *old_cred;
	काष्ठा cred *cred;
	पूर्णांक retval = 0;
	पूर्णांक ispipe;
	माप_प्रकार *argv = शून्य;
	पूर्णांक argc = 0;
	/* require nonrelative corefile path and be extra careful */
	bool need_suid_safe = false;
	bool core_dumped = false;
	अटल atomic_t core_dump_count = ATOMIC_INIT(0);
	काष्ठा coredump_params cprm = अणु
		.siginfo = siginfo,
		.regs = संकेत_pt_regs(),
		.limit = rlimit(RLIMIT_CORE),
		/*
		 * We must use the same mm->flags जबतक dumping core to aव्योम
		 * inconsistency of bit flags, since this flag is not रक्षित
		 * by any locks.
		 */
		.mm_flags = mm->flags,
	पूर्ण;

	audit_core_dumps(siginfo->si_signo);

	binfmt = mm->binfmt;
	अगर (!binfmt || !binfmt->core_dump)
		जाओ fail;
	अगर (!__get_dumpable(cprm.mm_flags))
		जाओ fail;

	cred = prepare_creds();
	अगर (!cred)
		जाओ fail;
	/*
	 * We cannot trust fsuid as being the "true" uid of the process
	 * nor करो we know its entire history. We only know it was taपूर्णांकed
	 * so we dump it as root in mode 2, and only पूर्णांकo a controlled
	 * environment (pipe handler or fully qualअगरied path).
	 */
	अगर (__get_dumpable(cprm.mm_flags) == SUID_DUMP_ROOT) अणु
		/* Setuid core dump mode */
		cred->fsuid = GLOBAL_ROOT_UID;	/* Dump root निजी */
		need_suid_safe = true;
	पूर्ण

	retval = coredump_रुको(siginfo->si_signo, &core_state);
	अगर (retval < 0)
		जाओ fail_creds;

	old_cred = override_creds(cred);

	ispipe = क्रमmat_coनाम(&cn, &cprm, &argv, &argc);

	अगर (ispipe) अणु
		पूर्णांक argi;
		पूर्णांक dump_count;
		अक्षर **helper_argv;
		काष्ठा subprocess_info *sub_info;

		अगर (ispipe < 0) अणु
			prपूर्णांकk(KERN_WARNING "format_corename failed\n");
			prपूर्णांकk(KERN_WARNING "Aborting core\n");
			जाओ fail_unlock;
		पूर्ण

		अगर (cprm.limit == 1) अणु
			/* See umh_pipe_setup() which sets RLIMIT_CORE = 1.
			 *
			 * Normally core limits are irrelevant to pipes, since
			 * we're not writing to the file प्रणाली, but we use
			 * cprm.limit of 1 here as a special value, this is a
			 * consistent way to catch recursive crashes.
			 * We can still crash अगर the core_pattern binary sets
			 * RLIM_CORE = !1, but it runs as root, and can करो
			 * lots of stupid things.
			 *
			 * Note that we use task_tgid_vnr here to grab the pid
			 * of the process group leader.  That way we get the
			 * right pid अगर a thपढ़ो in a multi-thपढ़ोed
			 * core_pattern process dies.
			 */
			prपूर्णांकk(KERN_WARNING
				"Process %d(%s) has RLIMIT_CORE set to 1\n",
				task_tgid_vnr(current), current->comm);
			prपूर्णांकk(KERN_WARNING "Aborting core\n");
			जाओ fail_unlock;
		पूर्ण
		cprm.limit = RLIM_अनन्त;

		dump_count = atomic_inc_वापस(&core_dump_count);
		अगर (core_pipe_limit && (core_pipe_limit < dump_count)) अणु
			prपूर्णांकk(KERN_WARNING "Pid %d(%s) over core_pipe_limit\n",
			       task_tgid_vnr(current), current->comm);
			prपूर्णांकk(KERN_WARNING "Skipping core dump\n");
			जाओ fail_dropcount;
		पूर्ण

		helper_argv = kदो_स्मृति_array(argc + 1, माप(*helper_argv),
					    GFP_KERNEL);
		अगर (!helper_argv) अणु
			prपूर्णांकk(KERN_WARNING "%s failed to allocate memory\n",
			       __func__);
			जाओ fail_dropcount;
		पूर्ण
		क्रम (argi = 0; argi < argc; argi++)
			helper_argv[argi] = cn.coनाम + argv[argi];
		helper_argv[argi] = शून्य;

		retval = -ENOMEM;
		sub_info = call_usermodehelper_setup(helper_argv[0],
						helper_argv, शून्य, GFP_KERNEL,
						umh_pipe_setup, शून्य, &cprm);
		अगर (sub_info)
			retval = call_usermodehelper_exec(sub_info,
							  UMH_WAIT_EXEC);

		kमुक्त(helper_argv);
		अगर (retval) अणु
			prपूर्णांकk(KERN_INFO "Core dump to |%s pipe failed\n",
			       cn.coनाम);
			जाओ बंद_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा user_namespace *mnt_userns;
		काष्ठा inode *inode;
		पूर्णांक खोलो_flags = O_CREAT | O_RDWR | O_NOFOLLOW |
				 O_LARGEखाता | O_EXCL;

		अगर (cprm.limit < binfmt->min_coredump)
			जाओ fail_unlock;

		अगर (need_suid_safe && cn.coनाम[0] != '/') अणु
			prपूर्णांकk(KERN_WARNING "Pid %d(%s) can only dump core "\
				"to fully qualified path!\n",
				task_tgid_vnr(current), current->comm);
			prपूर्णांकk(KERN_WARNING "Skipping core dump\n");
			जाओ fail_unlock;
		पूर्ण

		/*
		 * Unlink the file अगर it exists unless this is a SUID
		 * binary - in that हाल, we're running around with root
		 * privs and करोn't want to unlink another user's coredump.
		 */
		अगर (!need_suid_safe) अणु
			/*
			 * If it करोesn't exist, that's fine. If there's some
			 * other problem, we'll catch it at the filp_खोलो().
			 */
			करो_unlinkat(AT_FDCWD, getname_kernel(cn.coनाम));
		पूर्ण

		/*
		 * There is a race between unlinking and creating the
		 * file, but अगर that causes an EEXIST here, that's
		 * fine - another process raced with us जबतक creating
		 * the corefile, and the other process won. To userspace,
		 * what matters is that at least one of the two processes
		 * ग_लिखोs its coredump successfully, not which one.
		 */
		अगर (need_suid_safe) अणु
			/*
			 * Using user namespaces, normal user tasks can change
			 * their current->fs->root to poपूर्णांक to arbitrary
			 * directories. Since the पूर्णांकention of the "only dump
			 * with a fully qualअगरied path" rule is to control where
			 * coredumps may be placed using root privileges,
			 * current->fs->root must not be used. Instead, use the
			 * root directory of init_task.
			 */
			काष्ठा path root;

			task_lock(&init_task);
			get_fs_root(init_task.fs, &root);
			task_unlock(&init_task);
			cprm.file = file_खोलो_root(root.dentry, root.mnt,
				cn.coनाम, खोलो_flags, 0600);
			path_put(&root);
		पूर्ण अन्यथा अणु
			cprm.file = filp_खोलो(cn.coनाम, खोलो_flags, 0600);
		पूर्ण
		अगर (IS_ERR(cprm.file))
			जाओ fail_unlock;

		inode = file_inode(cprm.file);
		अगर (inode->i_nlink > 1)
			जाओ बंद_fail;
		अगर (d_unhashed(cprm.file->f_path.dentry))
			जाओ बंद_fail;
		/*
		 * AK: actually i see no reason to not allow this क्रम named
		 * pipes etc, but keep the previous behaviour क्रम now.
		 */
		अगर (!S_ISREG(inode->i_mode))
			जाओ बंद_fail;
		/*
		 * Don't dump core अगर the fileप्रणाली changed owner or mode
		 * of the file during file creation. This is an issue when
		 * a process dumps core जबतक its cwd is e.g. on a vfat
		 * fileप्रणाली.
		 */
		mnt_userns = file_mnt_user_ns(cprm.file);
		अगर (!uid_eq(i_uid_पूर्णांकo_mnt(mnt_userns, inode), current_fsuid()))
			जाओ बंद_fail;
		अगर ((inode->i_mode & 0677) != 0600)
			जाओ बंद_fail;
		अगर (!(cprm.file->f_mode & FMODE_CAN_WRITE))
			जाओ बंद_fail;
		अगर (करो_truncate(mnt_userns, cprm.file->f_path.dentry,
				0, 0, cprm.file))
			जाओ बंद_fail;
	पूर्ण

	/* get us an unshared descriptor table; almost always a no-op */
	/* The cell spufs coredump code पढ़ोs the file descriptor tables */
	retval = unshare_files();
	अगर (retval)
		जाओ बंद_fail;
	अगर (!dump_पूर्णांकerrupted()) अणु
		/*
		 * umh disabled with CONFIG_STATIC_USERMODEHELPER_PATH="" would
		 * have this set to शून्य.
		 */
		अगर (!cprm.file) अणु
			pr_info("Core dump to |%s disabled\n", cn.coनाम);
			जाओ बंद_fail;
		पूर्ण
		file_start_ग_लिखो(cprm.file);
		core_dumped = binfmt->core_dump(&cprm);
		/*
		 * Ensures that file size is big enough to contain the current
		 * file postion. This prevents gdb from complaining about
		 * a truncated file अगर the last "write" to the file was
		 * dump_skip.
		 */
		अगर (cprm.to_skip) अणु
			cprm.to_skip--;
			dump_emit(&cprm, "", 1);
		पूर्ण
		file_end_ग_लिखो(cprm.file);
	पूर्ण
	अगर (ispipe && core_pipe_limit)
		रुको_क्रम_dump_helpers(cprm.file);
बंद_fail:
	अगर (cprm.file)
		filp_बंद(cprm.file, शून्य);
fail_dropcount:
	अगर (ispipe)
		atomic_dec(&core_dump_count);
fail_unlock:
	kमुक्त(argv);
	kमुक्त(cn.coनाम);
	coredump_finish(mm, core_dumped);
	revert_creds(old_cred);
fail_creds:
	put_cred(cred);
fail:
	वापस;
पूर्ण

/*
 * Core dumping helper functions.  These are the only things you should
 * करो on a core-file: use only these functions to ग_लिखो out all the
 * necessary info.
 */
अटल पूर्णांक __dump_emit(काष्ठा coredump_params *cprm, स्थिर व्योम *addr, पूर्णांक nr)
अणु
	काष्ठा file *file = cprm->file;
	loff_t pos = file->f_pos;
	sमाप_प्रकार n;
	अगर (cprm->written + nr > cprm->limit)
		वापस 0;


	अगर (dump_पूर्णांकerrupted())
		वापस 0;
	n = __kernel_ग_लिखो(file, addr, nr, &pos);
	अगर (n != nr)
		वापस 0;
	file->f_pos = pos;
	cprm->written += n;
	cprm->pos += n;

	वापस 1;
पूर्ण

अटल पूर्णांक __dump_skip(काष्ठा coredump_params *cprm, माप_प्रकार nr)
अणु
	अटल अक्षर zeroes[PAGE_SIZE];
	काष्ठा file *file = cprm->file;
	अगर (file->f_op->llseek && file->f_op->llseek != no_llseek) अणु
		अगर (dump_पूर्णांकerrupted() ||
		    file->f_op->llseek(file, nr, प्रस्तुत_से) < 0)
			वापस 0;
		cprm->pos += nr;
		वापस 1;
	पूर्ण अन्यथा अणु
		जबतक (nr > PAGE_SIZE) अणु
			अगर (!__dump_emit(cprm, zeroes, PAGE_SIZE))
				वापस 0;
			nr -= PAGE_SIZE;
		पूर्ण
		वापस __dump_emit(cprm, zeroes, nr);
	पूर्ण
पूर्ण

पूर्णांक dump_emit(काष्ठा coredump_params *cprm, स्थिर व्योम *addr, पूर्णांक nr)
अणु
	अगर (cprm->to_skip) अणु
		अगर (!__dump_skip(cprm, cprm->to_skip))
			वापस 0;
		cprm->to_skip = 0;
	पूर्ण
	वापस __dump_emit(cprm, addr, nr);
पूर्ण
EXPORT_SYMBOL(dump_emit);

व्योम dump_skip_to(काष्ठा coredump_params *cprm, अचिन्हित दीर्घ pos)
अणु
	cprm->to_skip = pos - cprm->pos;
पूर्ण
EXPORT_SYMBOL(dump_skip_to);

व्योम dump_skip(काष्ठा coredump_params *cprm, माप_प्रकार nr)
अणु
	cprm->to_skip += nr;
पूर्ण
EXPORT_SYMBOL(dump_skip);

#अगर_घोषित CONFIG_ELF_CORE
पूर्णांक dump_user_range(काष्ठा coredump_params *cprm, अचिन्हित दीर्घ start,
		    अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr < start + len; addr += PAGE_SIZE) अणु
		काष्ठा page *page;
		पूर्णांक stop;

		/*
		 * To aव्योम having to allocate page tables क्रम भव address
		 * ranges that have never been used yet, and also to make it
		 * easy to generate sparse core files, use a helper that वापसs
		 * शून्य when encountering an empty page table entry that would
		 * otherwise have been filled with the zero page.
		 */
		page = get_dump_page(addr);
		अगर (page) अणु
			व्योम *kaddr = kmap_local_page(page);

			stop = !dump_emit(cprm, kaddr, PAGE_SIZE);
			kunmap_local(kaddr);
			put_page(page);
			अगर (stop)
				वापस 0;
		पूर्ण अन्यथा अणु
			dump_skip(cprm, PAGE_SIZE);
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण
#पूर्ण_अगर

पूर्णांक dump_align(काष्ठा coredump_params *cprm, पूर्णांक align)
अणु
	अचिन्हित mod = (cprm->pos + cprm->to_skip) & (align - 1);
	अगर (align & (align - 1))
		वापस 0;
	अगर (mod)
		cprm->to_skip += align - mod;
	वापस 1;
पूर्ण
EXPORT_SYMBOL(dump_align);

/*
 * The purpose of always_dump_vma() is to make sure that special kernel mappings
 * that are useful क्रम post-mortem analysis are included in every core dump.
 * In that way we ensure that the core dump is fully पूर्णांकerpretable later
 * without matching up the same kernel and hardware config to see what PC values
 * meant. These special mappings include - vDSO, vsyscall, and other
 * architecture specअगरic mappings
 */
अटल bool always_dump_vma(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* Any vsyscall mappings? */
	अगर (vma == get_gate_vma(vma->vm_mm))
		वापस true;

	/*
	 * Assume that all vmas with a .name op should always be dumped.
	 * If this changes, a new vm_ops field can easily be added.
	 */
	अगर (vma->vm_ops && vma->vm_ops->name && vma->vm_ops->name(vma))
		वापस true;

	/*
	 * arch_vma_name() वापसs non-शून्य क्रम special architecture mappings,
	 * such as vDSO sections.
	 */
	अगर (arch_vma_name(vma))
		वापस true;

	वापस false;
पूर्ण

/*
 * Decide how much of @vma's contents should be included in a core dump.
 */
अटल अचिन्हित दीर्घ vma_dump_size(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ mm_flags)
अणु
#घोषणा FILTER(type)	(mm_flags & (1UL << MMF_DUMP_##type))

	/* always dump the vdso and vsyscall sections */
	अगर (always_dump_vma(vma))
		जाओ whole;

	अगर (vma->vm_flags & VM_DONTDUMP)
		वापस 0;

	/* support क्रम DAX */
	अगर (vma_is_dax(vma)) अणु
		अगर ((vma->vm_flags & VM_SHARED) && FILTER(DAX_SHARED))
			जाओ whole;
		अगर (!(vma->vm_flags & VM_SHARED) && FILTER(DAX_PRIVATE))
			जाओ whole;
		वापस 0;
	पूर्ण

	/* Hugetlb memory check */
	अगर (is_vm_hugetlb_page(vma)) अणु
		अगर ((vma->vm_flags & VM_SHARED) && FILTER(HUGETLB_SHARED))
			जाओ whole;
		अगर (!(vma->vm_flags & VM_SHARED) && FILTER(HUGETLB_PRIVATE))
			जाओ whole;
		वापस 0;
	पूर्ण

	/* Do not dump I/O mapped devices or special mappings */
	अगर (vma->vm_flags & VM_IO)
		वापस 0;

	/* By शेष, dump shared memory अगर mapped from an anonymous file. */
	अगर (vma->vm_flags & VM_SHARED) अणु
		अगर (file_inode(vma->vm_file)->i_nlink == 0 ?
		    FILTER(ANON_SHARED) : FILTER(MAPPED_SHARED))
			जाओ whole;
		वापस 0;
	पूर्ण

	/* Dump segments that have been written to.  */
	अगर ((!IS_ENABLED(CONFIG_MMU) || vma->anon_vma) && FILTER(ANON_PRIVATE))
		जाओ whole;
	अगर (vma->vm_file == शून्य)
		वापस 0;

	अगर (FILTER(MAPPED_PRIVATE))
		जाओ whole;

	/*
	 * If this is the beginning of an executable file mapping,
	 * dump the first page to aid in determining what was mapped here.
	 */
	अगर (FILTER(ELF_HEADERS) &&
	    vma->vm_pgoff == 0 && (vma->vm_flags & VM_READ) &&
	    (READ_ONCE(file_inode(vma->vm_file)->i_mode) & 0111) != 0)
		वापस PAGE_SIZE;

#अघोषित	FILTER

	वापस 0;

whole:
	वापस vma->vm_end - vma->vm_start;
पूर्ण

अटल काष्ठा vm_area_काष्ठा *first_vma(काष्ठा task_काष्ठा *tsk,
					काष्ठा vm_area_काष्ठा *gate_vma)
अणु
	काष्ठा vm_area_काष्ठा *ret = tsk->mm->mmap;

	अगर (ret)
		वापस ret;
	वापस gate_vma;
पूर्ण

/*
 * Helper function क्रम iterating across a vma list.  It ensures that the caller
 * will visit `gate_vma' prior to terminating the search.
 */
अटल काष्ठा vm_area_काष्ठा *next_vma(काष्ठा vm_area_काष्ठा *this_vma,
				       काष्ठा vm_area_काष्ठा *gate_vma)
अणु
	काष्ठा vm_area_काष्ठा *ret;

	ret = this_vma->vm_next;
	अगर (ret)
		वापस ret;
	अगर (this_vma == gate_vma)
		वापस शून्य;
	वापस gate_vma;
पूर्ण

/*
 * Under the mmap_lock, take a snapshot of relevant inक्रमmation about the task's
 * VMAs.
 */
पूर्णांक dump_vma_snapshot(काष्ठा coredump_params *cprm, पूर्णांक *vma_count,
		      काष्ठा core_vma_metadata **vma_meta,
		      माप_प्रकार *vma_data_size_ptr)
अणु
	काष्ठा vm_area_काष्ठा *vma, *gate_vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक i;
	माप_प्रकार vma_data_size = 0;

	/*
	 * Once the stack expansion code is fixed to not change VMA bounds
	 * under mmap_lock in पढ़ो mode, this can be changed to take the
	 * mmap_lock in पढ़ो mode.
	 */
	अगर (mmap_ग_लिखो_lock_समाप्तable(mm))
		वापस -EINTR;

	gate_vma = get_gate_vma(mm);
	*vma_count = mm->map_count + (gate_vma ? 1 : 0);

	*vma_meta = kvदो_स्मृति_array(*vma_count, माप(**vma_meta), GFP_KERNEL);
	अगर (!*vma_meta) अणु
		mmap_ग_लिखो_unlock(mm);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0, vma = first_vma(current, gate_vma); vma != शून्य;
			vma = next_vma(vma, gate_vma), i++) अणु
		काष्ठा core_vma_metadata *m = (*vma_meta) + i;

		m->start = vma->vm_start;
		m->end = vma->vm_end;
		m->flags = vma->vm_flags;
		m->dump_size = vma_dump_size(vma, cprm->mm_flags);

		vma_data_size += m->dump_size;
	पूर्ण

	mmap_ग_लिखो_unlock(mm);

	अगर (WARN_ON(i != *vma_count))
		वापस -EFAULT;

	*vma_data_size_ptr = vma_data_size;
	वापस 0;
पूर्ण
