<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/proc/base.c
 *
 *  Copyright (C) 1991, 1992 Linus Torvalds
 *
 *  proc base directory handling functions
 *
 *  1999, Al Viro. Rewritten. Now it covers the whole per-process part.
 *  Instead of using magical inumbers to determine the kind of object
 *  we allocate and fill in-core inodes upon lookup. They करोn't even
 *  go पूर्णांकo icache. We cache the reference to task_काष्ठा upon lookup too.
 *  Eventually it should become a fileप्रणाली in its own. We करोn't use the
 *  rest of procfs anymore.
 *
 *
 *  Changelog:
 *  17-Jan-2005
 *  Allan Bezerra
 *  Bruna Moreira <bruna.moreira@indt.org.br>
 *  Edjard Mota <edjard.mota@indt.org.br>
 *  Ilias Biris <ilias.biris@indt.org.br>
 *  Mauricio Lin <mauricio.lin@indt.org.br>
 *
 *  Embedded Linux Lab - 10LE Instituto Nokia de Tecnologia - INdT
 *
 *  A new process specअगरic entry (smaps) included in /proc. It shows the
 *  size of rss क्रम each memory area. The maps entry lacks inक्रमmation
 *  about physical memory size (rss) क्रम each mapped file, i.e.,
 *  rss inक्रमmation क्रम executables and library files.
 *  This additional inक्रमmation is useful क्रम any tools that need to know
 *  about physical memory consumption क्रम a process specअगरic library.
 *
 *  Changelog:
 *  21-Feb-2005
 *  Embedded Linux Lab - 10LE Instituto Nokia de Tecnologia - INdT
 *  Pud inclusion in the page table walking.
 *
 *  ChangeLog:
 *  10-Mar-2005
 *  10LE Instituto Nokia de Tecnologia - INdT:
 *  A better way to walks through the page table as suggested by Hugh Dickins.
 *
 *  Simo Piiroinen <simo.piiroinen@nokia.com>:
 *  Smaps inक्रमmation related to shared, निजी, clean and dirty pages.
 *
 *  Paul Mundt <paul.mundt@nokia.com>:
 *  Overall revision about smaps.
 */

#समावेश <linux/uaccess.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/generic-radix-tree.h>
#समावेश <linux/माला.स>
#समावेश <linux/seq_file.h>
#समावेश <linux/namei.h>
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/resource.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/security.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/cache.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/audit.h>
#समावेश <linux/poll.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/oom.h>
#समावेश <linux/elf.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/स्वतःgroup.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/समय_namespace.h>
#समावेश <linux/resctrl.h>
#समावेश <trace/events/oom.h>
#समावेश "internal.h"
#समावेश "fd.h"

#समावेश "../../lib/kstrtox.h"

/* NOTE:
 *	Implementing inode permission operations in /proc is almost
 *	certainly an error.  Permission checks need to happen during
 *	each प्रणाली call not at खोलो समय.  The reason is that most of
 *	what we wish to check क्रम permissions in /proc varies at runसमय.
 *
 *	The classic example of a problem is खोलोing file descriptors
 *	in /proc क्रम a task beक्रमe it execs a suid executable.
 */

अटल u8 nlink_tid __ro_after_init;
अटल u8 nlink_tgid __ro_after_init;

काष्ठा pid_entry अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक len;
	umode_t mode;
	स्थिर काष्ठा inode_operations *iop;
	स्थिर काष्ठा file_operations *fop;
	जोड़ proc_op op;
पूर्ण;

#घोषणा NOD(NAME, MODE, IOP, FOP, OP) अणु			\
	.name = (NAME),					\
	.len  = माप(NAME) - 1,			\
	.mode = MODE,					\
	.iop  = IOP,					\
	.fop  = FOP,					\
	.op   = OP,					\
पूर्ण

#घोषणा सूची(NAME, MODE, iops, fops)	\
	NOD(NAME, (S_IFसूची|(MODE)), &iops, &fops, अणुपूर्ण )
#घोषणा LNK(NAME, get_link)					\
	NOD(NAME, (S_IFLNK|S_IRWXUGO),				\
		&proc_pid_link_inode_operations, शून्य,		\
		अणु .proc_get_link = get_link पूर्ण )
#घोषणा REG(NAME, MODE, fops)				\
	NOD(NAME, (S_IFREG|(MODE)), शून्य, &fops, अणुपूर्ण)
#घोषणा ONE(NAME, MODE, show)				\
	NOD(NAME, (S_IFREG|(MODE)),			\
		शून्य, &proc_single_file_operations,	\
		अणु .proc_show = show पूर्ण )
#घोषणा ATTR(LSM, NAME, MODE)				\
	NOD(NAME, (S_IFREG|(MODE)),			\
		शून्य, &proc_pid_attr_operations,	\
		अणु .lsm = LSM पूर्ण)

/*
 * Count the number of hardlinks क्रम the pid_entry table, excluding the .
 * and .. links.
 */
अटल अचिन्हित पूर्णांक __init pid_entry_nlink(स्थिर काष्ठा pid_entry *entries,
	अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक count;

	count = 2;
	क्रम (i = 0; i < n; ++i) अणु
		अगर (S_ISसूची(entries[i].mode))
			++count;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक get_task_root(काष्ठा task_काष्ठा *task, काष्ठा path *root)
अणु
	पूर्णांक result = -ENOENT;

	task_lock(task);
	अगर (task->fs) अणु
		get_fs_root(task->fs, root);
		result = 0;
	पूर्ण
	task_unlock(task);
	वापस result;
पूर्ण

अटल पूर्णांक proc_cwd_link(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(d_inode(dentry));
	पूर्णांक result = -ENOENT;

	अगर (task) अणु
		task_lock(task);
		अगर (task->fs) अणु
			get_fs_pwd(task->fs, path);
			result = 0;
		पूर्ण
		task_unlock(task);
		put_task_काष्ठा(task);
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक proc_root_link(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(d_inode(dentry));
	पूर्णांक result = -ENOENT;

	अगर (task) अणु
		result = get_task_root(task, path);
		put_task_काष्ठा(task);
	पूर्ण
	वापस result;
पूर्ण

/*
 * If the user used setproctitle(), we just get the string from
 * user space at arg_start, and limit it to a maximum of one page.
 */
अटल sमाप_प्रकार get_mm_proctitle(काष्ठा mm_काष्ठा *mm, अक्षर __user *buf,
				माप_प्रकार count, अचिन्हित दीर्घ pos,
				अचिन्हित दीर्घ arg_start)
अणु
	अक्षर *page;
	पूर्णांक ret, got;

	अगर (pos >= PAGE_SIZE)
		वापस 0;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	ret = 0;
	got = access_remote_vm(mm, arg_start, page, PAGE_SIZE, FOLL_ANON);
	अगर (got > 0) अणु
		पूर्णांक len = strnlen(page, got);

		/* Include the NUL अक्षरacter अगर it was found */
		अगर (len < got)
			len++;

		अगर (len > pos) अणु
			len -= pos;
			अगर (len > count)
				len = count;
			len -= copy_to_user(buf, page+pos, len);
			अगर (!len)
				len = -EFAULT;
			ret = len;
		पूर्ण
	पूर्ण
	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार get_mm_cmdline(काष्ठा mm_काष्ठा *mm, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ arg_start, arg_end, env_start, env_end;
	अचिन्हित दीर्घ pos, len;
	अक्षर *page, c;

	/* Check अगर process spawned far enough to have cmdline. */
	अगर (!mm->env_end)
		वापस 0;

	spin_lock(&mm->arg_lock);
	arg_start = mm->arg_start;
	arg_end = mm->arg_end;
	env_start = mm->env_start;
	env_end = mm->env_end;
	spin_unlock(&mm->arg_lock);

	अगर (arg_start >= arg_end)
		वापस 0;

	/*
	 * We allow setproctitle() to overग_लिखो the argument
	 * strings, and overflow past the original end. But
	 * only when it overflows पूर्णांकo the environment area.
	 */
	अगर (env_start != arg_end || env_end < env_start)
		env_start = env_end = arg_end;
	len = env_end - arg_start;

	/* We're not going to care अगर "*ppos" has high bits set */
	pos = *ppos;
	अगर (pos >= len)
		वापस 0;
	अगर (count > len - pos)
		count = len - pos;
	अगर (!count)
		वापस 0;

	/*
	 * Magical special हाल: अगर the argv[] end byte is not
	 * zero, the user has overwritten it with setproctitle(3).
	 *
	 * Possible future enhancement: करो this only once when
	 * pos is 0, and set a flag in the 'struct file'.
	 */
	अगर (access_remote_vm(mm, arg_end-1, &c, 1, FOLL_ANON) == 1 && c)
		वापस get_mm_proctitle(mm, buf, count, pos, arg_start);

	/*
	 * For the non-setproctitle() हाल we limit things strictly
	 * to the [arg_start, arg_end[ range.
	 */
	pos += arg_start;
	अगर (pos < arg_start || pos >= arg_end)
		वापस 0;
	अगर (count > arg_end - pos)
		count = arg_end - pos;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	len = 0;
	जबतक (count) अणु
		पूर्णांक got;
		माप_प्रकार size = min_t(माप_प्रकार, PAGE_SIZE, count);

		got = access_remote_vm(mm, pos, page, size, FOLL_ANON);
		अगर (got <= 0)
			अवरोध;
		got -= copy_to_user(buf, page, got);
		अगर (unlikely(!got)) अणु
			अगर (!len)
				len = -EFAULT;
			अवरोध;
		पूर्ण
		pos += got;
		buf += got;
		len += got;
		count -= got;
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)page);
	वापस len;
पूर्ण

अटल sमाप_प्रकार get_task_cmdline(काष्ठा task_काष्ठा *tsk, अक्षर __user *buf,
				माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा mm_काष्ठा *mm;
	sमाप_प्रकार ret;

	mm = get_task_mm(tsk);
	अगर (!mm)
		वापस 0;

	ret = get_mm_cmdline(mm, buf, count, pos);
	mmput(mm);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार proc_pid_cmdline_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा task_काष्ठा *tsk;
	sमाप_प्रकार ret;

	BUG_ON(*pos < 0);

	tsk = get_proc_task(file_inode(file));
	अगर (!tsk)
		वापस -ESRCH;
	ret = get_task_cmdline(tsk, buf, count, pos);
	put_task_काष्ठा(tsk);
	अगर (ret > 0)
		*pos += ret;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_cmdline_ops = अणु
	.पढ़ो	= proc_pid_cmdline_पढ़ो,
	.llseek	= generic_file_llseek,
पूर्ण;

#अगर_घोषित CONFIG_KALLSYMS
/*
 * Provides a wchan file via kallsyms in a proper one-value-per-file क्रमmat.
 * Returns the resolved symbol.  If that fails, simply वापस the address.
 */
अटल पूर्णांक proc_pid_wchan(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			  काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ wchan;

	अगर (ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
		wchan = get_wchan(task);
	अन्यथा
		wchan = 0;

	अगर (wchan)
		seq_म_लिखो(m, "%ps", (व्योम *) wchan);
	अन्यथा
		seq_अ_दो(m, '0');

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_KALLSYMS */

अटल पूर्णांक lock_trace(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक err = करोwn_पढ़ो_समाप्तable(&task->संकेत->exec_update_lock);
	अगर (err)
		वापस err;
	अगर (!ptrace_may_access(task, PTRACE_MODE_ATTACH_FSCREDS)) अणु
		up_पढ़ो(&task->संकेत->exec_update_lock);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम unlock_trace(काष्ठा task_काष्ठा *task)
अणु
	up_पढ़ो(&task->संकेत->exec_update_lock);
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

#घोषणा MAX_STACK_TRACE_DEPTH	64

अटल पूर्णांक proc_pid_stack(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			  काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ *entries;
	पूर्णांक err;

	/*
	 * The ability to racily run the kernel stack unwinder on a running task
	 * and then observe the unwinder output is scary; जबतक it is useful क्रम
	 * debugging kernel issues, it can also allow an attacker to leak kernel
	 * stack contents.
	 * Doing this in a manner that is at least safe from races would require
	 * some work to ensure that the remote task can not be scheduled; and
	 * even then, this would still expose the unwinder as local attack
	 * surface.
	 * Thereक्रमe, this पूर्णांकerface is restricted to root.
	 */
	अगर (!file_ns_capable(m->file, &init_user_ns, CAP_SYS_ADMIN))
		वापस -EACCES;

	entries = kदो_स्मृति_array(MAX_STACK_TRACE_DEPTH, माप(*entries),
				GFP_KERNEL);
	अगर (!entries)
		वापस -ENOMEM;

	err = lock_trace(task);
	अगर (!err) अणु
		अचिन्हित पूर्णांक i, nr_entries;

		nr_entries = stack_trace_save_tsk(task, entries,
						  MAX_STACK_TRACE_DEPTH, 0);

		क्रम (i = 0; i < nr_entries; i++) अणु
			seq_म_लिखो(m, "[<0>] %pB\n", (व्योम *)entries[i]);
		पूर्ण

		unlock_trace(task);
	पूर्ण
	kमुक्त(entries);

	वापस err;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_INFO
/*
 * Provides /proc/PID/schedstat
 */
अटल पूर्णांक proc_pid_schedstat(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			      काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(!sched_info_on()))
		seq_माला_दो(m, "0 0 0\n");
	अन्यथा
		seq_म_लिखो(m, "%llu %llu %lu\n",
		   (अचिन्हित दीर्घ दीर्घ)task->se.sum_exec_runसमय,
		   (अचिन्हित दीर्घ दीर्घ)task->sched_info.run_delay,
		   task->sched_info.pcount);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_LATENCYTOP
अटल पूर्णांक lstats_show_proc(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक i;
	काष्ठा inode *inode = m->निजी;
	काष्ठा task_काष्ठा *task = get_proc_task(inode);

	अगर (!task)
		वापस -ESRCH;
	seq_माला_दो(m, "Latency Top version : v0.1\n");
	क्रम (i = 0; i < LT_SAVECOUNT; i++) अणु
		काष्ठा latency_record *lr = &task->latency_record[i];
		अगर (lr->backtrace[0]) अणु
			पूर्णांक q;
			seq_म_लिखो(m, "%i %li %li",
				   lr->count, lr->समय, lr->max);
			क्रम (q = 0; q < LT_BACKTRACEDEPTH; q++) अणु
				अचिन्हित दीर्घ bt = lr->backtrace[q];

				अगर (!bt)
					अवरोध;
				seq_म_लिखो(m, " %ps", (व्योम *)bt);
			पूर्ण
			seq_अ_दो(m, '\n');
		पूर्ण

	पूर्ण
	put_task_काष्ठा(task);
	वापस 0;
पूर्ण

अटल पूर्णांक lstats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, lstats_show_proc, inode);
पूर्ण

अटल sमाप_प्रकार lstats_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *offs)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));

	अगर (!task)
		वापस -ESRCH;
	clear_tsk_latency_tracing(task);
	put_task_काष्ठा(task);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_lstats_operations = अणु
	.खोलो		= lstats_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= lstats_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#पूर्ण_अगर

अटल पूर्णांक proc_oom_score(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			  काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ totalpages = totalram_pages() + total_swap_pages;
	अचिन्हित दीर्घ poपूर्णांकs = 0;
	दीर्घ badness;

	badness = oom_badness(task, totalpages);
	/*
	 * Special हाल OOM_SCORE_ADJ_MIN क्रम all others scale the
	 * badness value पूर्णांकo [0, 2000] range which we have been
	 * exporting क्रम a दीर्घ समय so userspace might depend on it.
	 */
	अगर (badness != दीर्घ_न्यून)
		poपूर्णांकs = (1000 + badness * 1000 / (दीर्घ)totalpages) * 2 / 3;

	seq_म_लिखो(m, "%lu\n", poपूर्णांकs);

	वापस 0;
पूर्ण

काष्ठा limit_names अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *unit;
पूर्ण;

अटल स्थिर काष्ठा limit_names lnames[RLIM_NLIMITS] = अणु
	[RLIMIT_CPU] = अणु"Max cpu time", "seconds"पूर्ण,
	[RLIMIT_FSIZE] = अणु"Max file size", "bytes"पूर्ण,
	[RLIMIT_DATA] = अणु"Max data size", "bytes"पूर्ण,
	[RLIMIT_STACK] = अणु"Max stack size", "bytes"पूर्ण,
	[RLIMIT_CORE] = अणु"Max core file size", "bytes"पूर्ण,
	[RLIMIT_RSS] = अणु"Max resident set", "bytes"पूर्ण,
	[RLIMIT_NPROC] = अणु"Max processes", "processes"पूर्ण,
	[RLIMIT_NOखाता] = अणु"Max open files", "files"पूर्ण,
	[RLIMIT_MEMLOCK] = अणु"Max locked memory", "bytes"पूर्ण,
	[RLIMIT_AS] = अणु"Max address space", "bytes"पूर्ण,
	[RLIMIT_LOCKS] = अणु"Max file locks", "locks"पूर्ण,
	[RLIMIT_SIGPENDING] = अणु"Max pending signals", "signals"पूर्ण,
	[RLIMIT_MSGQUEUE] = अणु"Max msgqueue size", "bytes"पूर्ण,
	[RLIMIT_NICE] = अणु"Max nice priority", शून्यपूर्ण,
	[RLIMIT_RTPRIO] = अणु"Max realtime priority", शून्यपूर्ण,
	[RLIMIT_RTTIME] = अणु"Max realtime timeout", "us"पूर्ण,
पूर्ण;

/* Display limits क्रम a process */
अटल पूर्णांक proc_pid_limits(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			   काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;

	काष्ठा rlimit rlim[RLIM_NLIMITS];

	अगर (!lock_task_sighand(task, &flags))
		वापस 0;
	स_नकल(rlim, task->संकेत->rlim, माप(काष्ठा rlimit) * RLIM_NLIMITS);
	unlock_task_sighand(task, &flags);

	/*
	 * prपूर्णांक the file header
	 */
	seq_माला_दो(m, "Limit                     "
		"Soft Limit           "
		"Hard Limit           "
		"Units     \n");

	क्रम (i = 0; i < RLIM_NLIMITS; i++) अणु
		अगर (rlim[i].rlim_cur == RLIM_अनन्त)
			seq_म_लिखो(m, "%-25s %-20s ",
				   lnames[i].name, "unlimited");
		अन्यथा
			seq_म_लिखो(m, "%-25s %-20lu ",
				   lnames[i].name, rlim[i].rlim_cur);

		अगर (rlim[i].rlim_max == RLIM_अनन्त)
			seq_म_लिखो(m, "%-20s ", "unlimited");
		अन्यथा
			seq_म_लिखो(m, "%-20lu ", rlim[i].rlim_max);

		अगर (lnames[i].unit)
			seq_म_लिखो(m, "%-10s\n", lnames[i].unit);
		अन्यथा
			seq_अ_दो(m, '\n');
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK
अटल पूर्णांक proc_pid_syscall(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			    काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा syscall_info info;
	u64 *args = &info.data.args[0];
	पूर्णांक res;

	res = lock_trace(task);
	अगर (res)
		वापस res;

	अगर (task_current_syscall(task, &info))
		seq_माला_दो(m, "running\n");
	अन्यथा अगर (info.data.nr < 0)
		seq_म_लिखो(m, "%d 0x%llx 0x%llx\n",
			   info.data.nr, info.sp, info.data.inकाष्ठाion_poपूर्णांकer);
	अन्यथा
		seq_म_लिखो(m,
		       "%d 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx 0x%llx\n",
		       info.data.nr,
		       args[0], args[1], args[2], args[3], args[4], args[5],
		       info.sp, info.data.inकाष्ठाion_poपूर्णांकer);
	unlock_trace(task);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_TRACEHOOK */

/************************************************************************/
/*                       Here the fs part begins                        */
/************************************************************************/

/* permission checks */
अटल पूर्णांक proc_fd_access_allowed(काष्ठा inode *inode)
अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक allowed = 0;
	/* Allow access to a task's file descriptors अगर it is us or we
	 * may use ptrace attach to the process and find out that
	 * inक्रमmation.
	 */
	task = get_proc_task(inode);
	अगर (task) अणु
		allowed = ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS);
		put_task_काष्ठा(task);
	पूर्ण
	वापस allowed;
पूर्ण

पूर्णांक proc_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	पूर्णांक error;
	काष्ठा inode *inode = d_inode(dentry);

	अगर (attr->ia_valid & ATTR_MODE)
		वापस -EPERM;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

/*
 * May current process learn task's sched/cmdline info (क्रम hide_pid_min=1)
 * or euid/egid (क्रम hide_pid_min=2)?
 */
अटल bool has_pid_permissions(काष्ठा proc_fs_info *fs_info,
				 काष्ठा task_काष्ठा *task,
				 क्रमागत proc_hidepid hide_pid_min)
अणु
	/*
	 * If 'hidpid' mount option is set क्रमce a ptrace check,
	 * we indicate that we are using a fileप्रणाली syscall
	 * by passing PTRACE_MODE_READ_FSCREDS
	 */
	अगर (fs_info->hide_pid == HIDEPID_NOT_PTRACEABLE)
		वापस ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS);

	अगर (fs_info->hide_pid < hide_pid_min)
		वापस true;
	अगर (in_group_p(fs_info->pid_gid))
		वापस true;
	वापस ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS);
पूर्ण


अटल पूर्णांक proc_pid_permission(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा proc_fs_info *fs_info = proc_sb_info(inode->i_sb);
	काष्ठा task_काष्ठा *task;
	bool has_perms;

	task = get_proc_task(inode);
	अगर (!task)
		वापस -ESRCH;
	has_perms = has_pid_permissions(fs_info, task, HIDEPID_NO_ACCESS);
	put_task_काष्ठा(task);

	अगर (!has_perms) अणु
		अगर (fs_info->hide_pid == HIDEPID_INVISIBLE) अणु
			/*
			 * Let's make getdents(), stat(), and खोलो()
			 * consistent with each other.  If a process
			 * may not stat() a file, it shouldn't be seen
			 * in procfs at all.
			 */
			वापस -ENOENT;
		पूर्ण

		वापस -EPERM;
	पूर्ण
	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण



अटल स्थिर काष्ठा inode_operations proc_def_inode_operations = अणु
	.setattr	= proc_setattr,
पूर्ण;

अटल पूर्णांक proc_single_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा pid_namespace *ns = proc_pid_ns(inode->i_sb);
	काष्ठा pid *pid = proc_pid(inode);
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	task = get_pid_task(pid, PIDTYPE_PID);
	अगर (!task)
		वापस -ESRCH;

	ret = PROC_I(inode)->op.proc_show(m, ns, pid, task);

	put_task_काष्ठा(task);
	वापस ret;
पूर्ण

अटल पूर्णांक proc_single_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, proc_single_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_single_file_operations = अणु
	.खोलो		= proc_single_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;


काष्ठा mm_काष्ठा *proc_mem_खोलो(काष्ठा inode *inode, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(inode);
	काष्ठा mm_काष्ठा *mm = ERR_PTR(-ESRCH);

	अगर (task) अणु
		mm = mm_access(task, mode | PTRACE_MODE_FSCREDS);
		put_task_काष्ठा(task);

		अगर (!IS_ERR_OR_शून्य(mm)) अणु
			/* ensure this mm_काष्ठा can't be मुक्तd */
			mmgrab(mm);
			/* but करो not pin its memory */
			mmput(mm);
		पूर्ण
	पूर्ण

	वापस mm;
पूर्ण

अटल पूर्णांक __mem_खोलो(काष्ठा inode *inode, काष्ठा file *file, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mm_काष्ठा *mm = proc_mem_खोलो(inode, mode);

	अगर (IS_ERR(mm))
		वापस PTR_ERR(mm);

	file->निजी_data = mm;
	वापस 0;
पूर्ण

अटल पूर्णांक mem_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = __mem_खोलो(inode, file, PTRACE_MODE_ATTACH);

	/* OK to pass negative loff_t, we can catch out-of-range */
	file->f_mode |= FMODE_UNSIGNED_OFFSET;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mem_rw(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos, पूर्णांक ग_लिखो)
अणु
	काष्ठा mm_काष्ठा *mm = file->निजी_data;
	अचिन्हित दीर्घ addr = *ppos;
	sमाप_प्रकार copied;
	अक्षर *page;
	अचिन्हित पूर्णांक flags;

	अगर (!mm)
		वापस 0;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	copied = 0;
	अगर (!mmget_not_zero(mm))
		जाओ मुक्त;

	flags = FOLL_FORCE | (ग_लिखो ? FOLL_WRITE : 0);

	जबतक (count > 0) अणु
		पूर्णांक this_len = min_t(पूर्णांक, count, PAGE_SIZE);

		अगर (ग_लिखो && copy_from_user(page, buf, this_len)) अणु
			copied = -EFAULT;
			अवरोध;
		पूर्ण

		this_len = access_remote_vm(mm, addr, page, this_len, flags);
		अगर (!this_len) अणु
			अगर (!copied)
				copied = -EIO;
			अवरोध;
		पूर्ण

		अगर (!ग_लिखो && copy_to_user(buf, page, this_len)) अणु
			copied = -EFAULT;
			अवरोध;
		पूर्ण

		buf += this_len;
		addr += this_len;
		copied += this_len;
		count -= this_len;
	पूर्ण
	*ppos = addr;

	mmput(mm);
मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) page);
	वापस copied;
पूर्ण

अटल sमाप_प्रकार mem_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	वापस mem_rw(file, buf, count, ppos, 0);
पूर्ण

अटल sमाप_प्रकार mem_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	वापस mem_rw(file, (अक्षर __user*)buf, count, ppos, 1);
पूर्ण

loff_t mem_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	चयन (orig) अणु
	हाल 0:
		file->f_pos = offset;
		अवरोध;
	हाल 1:
		file->f_pos += offset;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	क्रमce_successful_syscall_वापस();
	वापस file->f_pos;
पूर्ण

अटल पूर्णांक mem_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mm_काष्ठा *mm = file->निजी_data;
	अगर (mm)
		mmdrop(mm);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_mem_operations = अणु
	.llseek		= mem_lseek,
	.पढ़ो		= mem_पढ़ो,
	.ग_लिखो		= mem_ग_लिखो,
	.खोलो		= mem_खोलो,
	.release	= mem_release,
पूर्ण;

अटल पूर्णांक environ_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __mem_खोलो(inode, file, PTRACE_MODE_READ);
पूर्ण

अटल sमाप_प्रकार environ_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *page;
	अचिन्हित दीर्घ src = *ppos;
	पूर्णांक ret = 0;
	काष्ठा mm_काष्ठा *mm = file->निजी_data;
	अचिन्हित दीर्घ env_start, env_end;

	/* Ensure the process spawned far enough to have an environment. */
	अगर (!mm || !mm->env_end)
		वापस 0;

	page = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	ret = 0;
	अगर (!mmget_not_zero(mm))
		जाओ मुक्त;

	spin_lock(&mm->arg_lock);
	env_start = mm->env_start;
	env_end = mm->env_end;
	spin_unlock(&mm->arg_lock);

	जबतक (count > 0) अणु
		माप_प्रकार this_len, max_len;
		पूर्णांक retval;

		अगर (src >= (env_end - env_start))
			अवरोध;

		this_len = env_end - (env_start + src);

		max_len = min_t(माप_प्रकार, PAGE_SIZE, count);
		this_len = min(max_len, this_len);

		retval = access_remote_vm(mm, (env_start + src), page, this_len, FOLL_ANON);

		अगर (retval <= 0) अणु
			ret = retval;
			अवरोध;
		पूर्ण

		अगर (copy_to_user(buf, page, retval)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		ret += retval;
		src += retval;
		buf += retval;
		count -= retval;
	पूर्ण
	*ppos = src;
	mmput(mm);

मुक्त:
	मुक्त_page((अचिन्हित दीर्घ) page);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_environ_operations = अणु
	.खोलो		= environ_खोलो,
	.पढ़ो		= environ_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= mem_release,
पूर्ण;

अटल पूर्णांक auxv_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __mem_खोलो(inode, file, PTRACE_MODE_READ_FSCREDS);
पूर्ण

अटल sमाप_प्रकार auxv_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mm_काष्ठा *mm = file->निजी_data;
	अचिन्हित पूर्णांक nwords = 0;

	अगर (!mm)
		वापस 0;
	करो अणु
		nwords += 2;
	पूर्ण जबतक (mm->saved_auxv[nwords - 2] != 0); /* AT_शून्य */
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, mm->saved_auxv,
				       nwords * माप(mm->saved_auxv[0]));
पूर्ण

अटल स्थिर काष्ठा file_operations proc_auxv_operations = अणु
	.खोलो		= auxv_खोलो,
	.पढ़ो		= auxv_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= mem_release,
पूर्ण;

अटल sमाप_प्रकार oom_adj_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			    loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	अक्षर buffer[PROC_NUMBUF];
	पूर्णांक oom_adj = OOM_ADJUST_MIN;
	माप_प्रकार len;

	अगर (!task)
		वापस -ESRCH;
	अगर (task->संकेत->oom_score_adj == OOM_SCORE_ADJ_MAX)
		oom_adj = OOM_ADJUST_MAX;
	अन्यथा
		oom_adj = (task->संकेत->oom_score_adj * -OOM_DISABLE) /
			  OOM_SCORE_ADJ_MAX;
	put_task_काष्ठा(task);
	अगर (oom_adj > OOM_ADJUST_MAX)
		oom_adj = OOM_ADJUST_MAX;
	len = snम_लिखो(buffer, माप(buffer), "%d\n", oom_adj);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, buffer, len);
पूर्ण

अटल पूर्णांक __set_oom_adj(काष्ठा file *file, पूर्णांक oom_adj, bool legacy)
अणु
	काष्ठा mm_काष्ठा *mm = शून्य;
	काष्ठा task_काष्ठा *task;
	पूर्णांक err = 0;

	task = get_proc_task(file_inode(file));
	अगर (!task)
		वापस -ESRCH;

	mutex_lock(&oom_adj_mutex);
	अगर (legacy) अणु
		अगर (oom_adj < task->संकेत->oom_score_adj &&
				!capable(CAP_SYS_RESOURCE)) अणु
			err = -EACCES;
			जाओ err_unlock;
		पूर्ण
		/*
		 * /proc/pid/oom_adj is provided क्रम legacy purposes, ask users to use
		 * /proc/pid/oom_score_adj instead.
		 */
		pr_warn_once("%s (%d): /proc/%d/oom_adj is deprecated, please use /proc/%d/oom_score_adj instead.\n",
			  current->comm, task_pid_nr(current), task_pid_nr(task),
			  task_pid_nr(task));
	पूर्ण अन्यथा अणु
		अगर ((लघु)oom_adj < task->संकेत->oom_score_adj_min &&
				!capable(CAP_SYS_RESOURCE)) अणु
			err = -EACCES;
			जाओ err_unlock;
		पूर्ण
	पूर्ण

	/*
	 * Make sure we will check other processes sharing the mm अगर this is
	 * not vfrok which wants its own oom_score_adj.
	 * pin the mm so it करोesn't go away and get reused after task_unlock
	 */
	अगर (!task->vविभाजन_करोne) अणु
		काष्ठा task_काष्ठा *p = find_lock_task_mm(task);

		अगर (p) अणु
			अगर (test_bit(MMF_MULTIPROCESS, &p->mm->flags)) अणु
				mm = p->mm;
				mmgrab(mm);
			पूर्ण
			task_unlock(p);
		पूर्ण
	पूर्ण

	task->संकेत->oom_score_adj = oom_adj;
	अगर (!legacy && has_capability_noaudit(current, CAP_SYS_RESOURCE))
		task->संकेत->oom_score_adj_min = (लघु)oom_adj;
	trace_oom_score_adj_update(task);

	अगर (mm) अणु
		काष्ठा task_काष्ठा *p;

		rcu_पढ़ो_lock();
		क्रम_each_process(p) अणु
			अगर (same_thपढ़ो_group(task, p))
				जारी;

			/* करो not touch kernel thपढ़ोs or the global init */
			अगर (p->flags & PF_KTHREAD || is_global_init(p))
				जारी;

			task_lock(p);
			अगर (!p->vविभाजन_करोne && process_shares_mm(p, mm)) अणु
				p->संकेत->oom_score_adj = oom_adj;
				अगर (!legacy && has_capability_noaudit(current, CAP_SYS_RESOURCE))
					p->संकेत->oom_score_adj_min = (लघु)oom_adj;
			पूर्ण
			task_unlock(p);
		पूर्ण
		rcu_पढ़ो_unlock();
		mmdrop(mm);
	पूर्ण
err_unlock:
	mutex_unlock(&oom_adj_mutex);
	put_task_काष्ठा(task);
	वापस err;
पूर्ण

/*
 * /proc/pid/oom_adj exists solely क्रम backwards compatibility with previous
 * kernels.  The effective policy is defined by oom_score_adj, which has a
 * dअगरferent scale: oom_adj grew exponentially and oom_score_adj grows linearly.
 * Values written to oom_adj are simply mapped linearly to oom_score_adj.
 * Processes that become oom disabled via oom_adj will still be oom disabled
 * with this implementation.
 *
 * oom_adj cannot be हटाओd since existing userspace binaries use it.
 */
अटल sमाप_प्रकार oom_adj_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buffer[PROC_NUMBUF];
	पूर्णांक oom_adj;
	पूर्णांक err;

	स_रखो(buffer, 0, माप(buffer));
	अगर (count > माप(buffer) - 1)
		count = माप(buffer) - 1;
	अगर (copy_from_user(buffer, buf, count)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	err = kstrtoपूर्णांक(म_मालाip(buffer), 0, &oom_adj);
	अगर (err)
		जाओ out;
	अगर ((oom_adj < OOM_ADJUST_MIN || oom_adj > OOM_ADJUST_MAX) &&
	     oom_adj != OOM_DISABLE) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Scale /proc/pid/oom_score_adj appropriately ensuring that a maximum
	 * value is always attainable.
	 */
	अगर (oom_adj == OOM_ADJUST_MAX)
		oom_adj = OOM_SCORE_ADJ_MAX;
	अन्यथा
		oom_adj = (oom_adj * OOM_SCORE_ADJ_MAX) / -OOM_DISABLE;

	err = __set_oom_adj(file, oom_adj, true);
out:
	वापस err < 0 ? err : count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_oom_adj_operations = अणु
	.पढ़ो		= oom_adj_पढ़ो,
	.ग_लिखो		= oom_adj_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार oom_score_adj_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	अक्षर buffer[PROC_NUMBUF];
	लघु oom_score_adj = OOM_SCORE_ADJ_MIN;
	माप_प्रकार len;

	अगर (!task)
		वापस -ESRCH;
	oom_score_adj = task->संकेत->oom_score_adj;
	put_task_काष्ठा(task);
	len = snम_लिखो(buffer, माप(buffer), "%hd\n", oom_score_adj);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, buffer, len);
पूर्ण

अटल sमाप_प्रकार oom_score_adj_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buffer[PROC_NUMBUF];
	पूर्णांक oom_score_adj;
	पूर्णांक err;

	स_रखो(buffer, 0, माप(buffer));
	अगर (count > माप(buffer) - 1)
		count = माप(buffer) - 1;
	अगर (copy_from_user(buffer, buf, count)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	err = kstrtoपूर्णांक(म_मालाip(buffer), 0, &oom_score_adj);
	अगर (err)
		जाओ out;
	अगर (oom_score_adj < OOM_SCORE_ADJ_MIN ||
			oom_score_adj > OOM_SCORE_ADJ_MAX) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = __set_oom_adj(file, oom_score_adj, false);
out:
	वापस err < 0 ? err : count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_oom_score_adj_operations = अणु
	.पढ़ो		= oom_score_adj_पढ़ो,
	.ग_लिखो		= oom_score_adj_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

#अगर_घोषित CONFIG_AUDIT
#घोषणा TMPBUFLEN 11
अटल sमाप_प्रकार proc_loginuid_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode * inode = file_inode(file);
	काष्ठा task_काष्ठा *task = get_proc_task(inode);
	sमाप_प्रकार length;
	अक्षर पंचांगpbuf[TMPBUFLEN];

	अगर (!task)
		वापस -ESRCH;
	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%u",
			   from_kuid(file->f_cred->user_ns,
				     audit_get_loginuid(task)));
	put_task_काष्ठा(task);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल sमाप_प्रकार proc_loginuid_ग_लिखो(काष्ठा file * file, स्थिर अक्षर __user * buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode * inode = file_inode(file);
	uid_t loginuid;
	kuid_t kloginuid;
	पूर्णांक rv;

	/* Don't let kthपढ़ोs ग_लिखो their own loginuid */
	अगर (current->flags & PF_KTHREAD)
		वापस -EPERM;

	rcu_पढ़ो_lock();
	अगर (current != pid_task(proc_pid(inode), PIDTYPE_PID)) अणु
		rcu_पढ़ो_unlock();
		वापस -EPERM;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (*ppos != 0) अणु
		/* No partial ग_लिखोs. */
		वापस -EINVAL;
	पूर्ण

	rv = kstrtou32_from_user(buf, count, 10, &loginuid);
	अगर (rv < 0)
		वापस rv;

	/* is userspace tring to explicitly UNSET the loginuid? */
	अगर (loginuid == AUDIT_UID_UNSET) अणु
		kloginuid = INVALID_UID;
	पूर्ण अन्यथा अणु
		kloginuid = make_kuid(file->f_cred->user_ns, loginuid);
		अगर (!uid_valid(kloginuid))
			वापस -EINVAL;
	पूर्ण

	rv = audit_set_loginuid(kloginuid);
	अगर (rv < 0)
		वापस rv;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_loginuid_operations = अणु
	.पढ़ो		= proc_loginuid_पढ़ो,
	.ग_लिखो		= proc_loginuid_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार proc_sessionid_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode * inode = file_inode(file);
	काष्ठा task_काष्ठा *task = get_proc_task(inode);
	sमाप_प्रकार length;
	अक्षर पंचांगpbuf[TMPBUFLEN];

	अगर (!task)
		वापस -ESRCH;
	length = scnम_लिखो(पंचांगpbuf, TMPBUFLEN, "%u",
				audit_get_sessionid(task));
	put_task_काष्ठा(task);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगpbuf, length);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_sessionid_operations = अणु
	.पढ़ो		= proc_sessionid_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FAULT_INJECTION
अटल sमाप_प्रकार proc_fault_inject_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	अक्षर buffer[PROC_NUMBUF];
	माप_प्रकार len;
	पूर्णांक make_it_fail;

	अगर (!task)
		वापस -ESRCH;
	make_it_fail = task->make_it_fail;
	put_task_काष्ठा(task);

	len = snम_लिखो(buffer, माप(buffer), "%i\n", make_it_fail);

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, buffer, len);
पूर्ण

अटल sमाप_प्रकार proc_fault_inject_ग_लिखो(काष्ठा file * file,
			स्थिर अक्षर __user * buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर buffer[PROC_NUMBUF];
	पूर्णांक make_it_fail;
	पूर्णांक rv;

	अगर (!capable(CAP_SYS_RESOURCE))
		वापस -EPERM;
	स_रखो(buffer, 0, माप(buffer));
	अगर (count > माप(buffer) - 1)
		count = माप(buffer) - 1;
	अगर (copy_from_user(buffer, buf, count))
		वापस -EFAULT;
	rv = kstrtoपूर्णांक(म_मालाip(buffer), 0, &make_it_fail);
	अगर (rv < 0)
		वापस rv;
	अगर (make_it_fail < 0 || make_it_fail > 1)
		वापस -EINVAL;

	task = get_proc_task(file_inode(file));
	अगर (!task)
		वापस -ESRCH;
	task->make_it_fail = make_it_fail;
	put_task_काष्ठा(task);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_fault_inject_operations = अणु
	.पढ़ो		= proc_fault_inject_पढ़ो,
	.ग_लिखो		= proc_fault_inject_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार proc_fail_nth_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक err;
	अचिन्हित पूर्णांक n;

	err = kstrtouपूर्णांक_from_user(buf, count, 0, &n);
	अगर (err)
		वापस err;

	task = get_proc_task(file_inode(file));
	अगर (!task)
		वापस -ESRCH;
	task->fail_nth = n;
	put_task_काष्ठा(task);

	वापस count;
पूर्ण

अटल sमाप_प्रकार proc_fail_nth_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task;
	अक्षर numbuf[PROC_NUMBUF];
	sमाप_प्रकार len;

	task = get_proc_task(file_inode(file));
	अगर (!task)
		वापस -ESRCH;
	len = snम_लिखो(numbuf, माप(numbuf), "%u\n", task->fail_nth);
	put_task_काष्ठा(task);
	वापस simple_पढ़ो_from_buffer(buf, count, ppos, numbuf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_fail_nth_operations = अणु
	.पढ़ो		= proc_fail_nth_पढ़ो,
	.ग_लिखो		= proc_fail_nth_ग_लिखो,
पूर्ण;
#पूर्ण_अगर


#अगर_घोषित CONFIG_SCHED_DEBUG
/*
 * Prपूर्णांक out various scheduling related per-task fields:
 */
अटल पूर्णांक sched_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा pid_namespace *ns = proc_pid_ns(inode->i_sb);
	काष्ठा task_काष्ठा *p;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;
	proc_sched_show_task(p, ns, m);

	put_task_काष्ठा(p);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
sched_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	    माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा task_काष्ठा *p;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;
	proc_sched_set_task(p);

	put_task_काष्ठा(p);

	वापस count;
पूर्ण

अटल पूर्णांक sched_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, sched_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_sched_operations = अणु
	.खोलो		= sched_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= sched_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHED_AUTOGROUP
/*
 * Prपूर्णांक out स्वतःgroup related inक्रमmation:
 */
अटल पूर्णांक sched_स्वतःgroup_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा task_काष्ठा *p;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;
	proc_sched_स्वतःgroup_show_task(p, m);

	put_task_काष्ठा(p);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
sched_स्वतःgroup_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	    माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा task_काष्ठा *p;
	अक्षर buffer[PROC_NUMBUF];
	पूर्णांक nice;
	पूर्णांक err;

	स_रखो(buffer, 0, माप(buffer));
	अगर (count > माप(buffer) - 1)
		count = माप(buffer) - 1;
	अगर (copy_from_user(buffer, buf, count))
		वापस -EFAULT;

	err = kstrtoपूर्णांक(म_मालाip(buffer), 0, &nice);
	अगर (err < 0)
		वापस err;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;

	err = proc_sched_स्वतःgroup_set_nice(p, nice);
	अगर (err)
		count = err;

	put_task_काष्ठा(p);

	वापस count;
पूर्ण

अटल पूर्णांक sched_स्वतःgroup_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;

	ret = single_खोलो(filp, sched_स्वतःgroup_show, शून्य);
	अगर (!ret) अणु
		काष्ठा seq_file *m = filp->निजी_data;

		m->निजी = inode;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_sched_स्वतःgroup_operations = अणु
	.खोलो		= sched_स्वतःgroup_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= sched_स्वतःgroup_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

#पूर्ण_अगर /* CONFIG_SCHED_AUTOGROUP */

#अगर_घोषित CONFIG_TIME_NS
अटल पूर्णांक समयns_offsets_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा task_काष्ठा *p;

	p = get_proc_task(file_inode(m->file));
	अगर (!p)
		वापस -ESRCH;
	proc_समयns_show_offsets(p, m);

	put_task_काष्ठा(p);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार समयns_offsets_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा proc_समयns_offset offsets[2];
	अक्षर *kbuf = शून्य, *pos, *next_line;
	काष्ठा task_काष्ठा *p;
	पूर्णांक ret, noffsets;

	/* Only allow < page size ग_लिखोs at the beginning of the file */
	अगर ((*ppos != 0) || (count >= PAGE_SIZE))
		वापस -EINVAL;

	/* Slurp in the user data */
	kbuf = memdup_user_nul(buf, count);
	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);

	/* Parse the user data */
	ret = -EINVAL;
	noffsets = 0;
	क्रम (pos = kbuf; pos; pos = next_line) अणु
		काष्ठा proc_समयns_offset *off = &offsets[noffsets];
		अक्षर घड़ी[10];
		पूर्णांक err;

		/* Find the end of line and ensure we करोn't look past it */
		next_line = म_अक्षर(pos, '\n');
		अगर (next_line) अणु
			*next_line = '\0';
			next_line++;
			अगर (*next_line == '\0')
				next_line = शून्य;
		पूर्ण

		err = माला_पूछो(pos, "%9s %lld %lu", घड़ी,
				&off->val.tv_sec, &off->val.tv_nsec);
		अगर (err != 3 || off->val.tv_nsec >= NSEC_PER_SEC)
			जाओ out;

		घड़ी[माप(घड़ी) - 1] = 0;
		अगर (म_भेद(घड़ी, "monotonic") == 0 ||
		    म_भेद(घड़ी, __stringअगरy(CLOCK_MONOTONIC)) == 0)
			off->घड़ीid = CLOCK_MONOTONIC;
		अन्यथा अगर (म_भेद(घड़ी, "boottime") == 0 ||
			 म_भेद(घड़ी, __stringअगरy(CLOCK_BOOTTIME)) == 0)
			off->घड़ीid = CLOCK_BOOTTIME;
		अन्यथा
			जाओ out;

		noffsets++;
		अगर (noffsets == ARRAY_SIZE(offsets)) अणु
			अगर (next_line)
				count = next_line - kbuf;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = -ESRCH;
	p = get_proc_task(inode);
	अगर (!p)
		जाओ out;
	ret = proc_समयns_set_offset(file, p, offsets, noffsets);
	put_task_काष्ठा(p);
	अगर (ret)
		जाओ out;

	ret = count;
out:
	kमुक्त(kbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक समयns_offsets_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, समयns_offsets_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_समयns_offsets_operations = अणु
	.खोलो		= समयns_offsets_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= समयns_offsets_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_TIME_NS */

अटल sमाप_प्रकार comm_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा task_काष्ठा *p;
	अक्षर buffer[TASK_COMM_LEN];
	स्थिर माप_प्रकार maxlen = माप(buffer) - 1;

	स_रखो(buffer, 0, माप(buffer));
	अगर (copy_from_user(buffer, buf, count > maxlen ? maxlen : count))
		वापस -EFAULT;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;

	अगर (same_thपढ़ो_group(current, p))
		set_task_comm(p, buffer);
	अन्यथा
		count = -EINVAL;

	put_task_काष्ठा(p);

	वापस count;
पूर्ण

अटल पूर्णांक comm_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा task_काष्ठा *p;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;

	proc_task_name(m, p, false);
	seq_अ_दो(m, '\n');

	put_task_काष्ठा(p);

	वापस 0;
पूर्ण

अटल पूर्णांक comm_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, comm_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_set_comm_operations = अणु
	.खोलो		= comm_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= comm_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक proc_exe_link(काष्ठा dentry *dentry, काष्ठा path *exe_path)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा file *exe_file;

	task = get_proc_task(d_inode(dentry));
	अगर (!task)
		वापस -ENOENT;
	exe_file = get_task_exe_file(task);
	put_task_काष्ठा(task);
	अगर (exe_file) अणु
		*exe_path = exe_file->f_path;
		path_get(&exe_file->f_path);
		fput(exe_file);
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENOENT;
पूर्ण

अटल स्थिर अक्षर *proc_pid_get_link(काष्ठा dentry *dentry,
				     काष्ठा inode *inode,
				     काष्ठा delayed_call *करोne)
अणु
	काष्ठा path path;
	पूर्णांक error = -EACCES;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	/* Are we allowed to snoop on the tasks file descriptors? */
	अगर (!proc_fd_access_allowed(inode))
		जाओ out;

	error = PROC_I(inode)->op.proc_get_link(dentry, &path);
	अगर (error)
		जाओ out;

	error = nd_jump_link(&path);
out:
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक करो_proc_पढ़ोlink(काष्ठा path *path, अक्षर __user *buffer, पूर्णांक buflen)
अणु
	अक्षर *पंचांगp = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अक्षर *pathname;
	पूर्णांक len;

	अगर (!पंचांगp)
		वापस -ENOMEM;

	pathname = d_path(path, पंचांगp, PAGE_SIZE);
	len = PTR_ERR(pathname);
	अगर (IS_ERR(pathname))
		जाओ out;
	len = पंचांगp + PAGE_SIZE - 1 - pathname;

	अगर (len > buflen)
		len = buflen;
	अगर (copy_to_user(buffer, pathname, len))
		len = -EFAULT;
 out:
	मुक्त_page((अचिन्हित दीर्घ)पंचांगp);
	वापस len;
पूर्ण

अटल पूर्णांक proc_pid_पढ़ोlink(काष्ठा dentry * dentry, अक्षर __user * buffer, पूर्णांक buflen)
अणु
	पूर्णांक error = -EACCES;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा path path;

	/* Are we allowed to snoop on the tasks file descriptors? */
	अगर (!proc_fd_access_allowed(inode))
		जाओ out;

	error = PROC_I(inode)->op.proc_get_link(dentry, &path);
	अगर (error)
		जाओ out;

	error = करो_proc_पढ़ोlink(&path, buffer, buflen);
	path_put(&path);
out:
	वापस error;
पूर्ण

स्थिर काष्ठा inode_operations proc_pid_link_inode_operations = अणु
	.पढ़ोlink	= proc_pid_पढ़ोlink,
	.get_link	= proc_pid_get_link,
	.setattr	= proc_setattr,
पूर्ण;


/* building an inode */

व्योम task_dump_owner(काष्ठा task_काष्ठा *task, umode_t mode,
		     kuid_t *ruid, kgid_t *rgid)
अणु
	/* Depending on the state of dumpable compute who should own a
	 * proc file क्रम a task.
	 */
	स्थिर काष्ठा cred *cred;
	kuid_t uid;
	kgid_t gid;

	अगर (unlikely(task->flags & PF_KTHREAD)) अणु
		*ruid = GLOBAL_ROOT_UID;
		*rgid = GLOBAL_ROOT_GID;
		वापस;
	पूर्ण

	/* Default to the tasks effective ownership */
	rcu_पढ़ो_lock();
	cred = __task_cred(task);
	uid = cred->euid;
	gid = cred->egid;
	rcu_पढ़ो_unlock();

	/*
	 * Beक्रमe the /proc/pid/status file was created the only way to पढ़ो
	 * the effective uid of a /process was to stat /proc/pid.  Reading
	 * /proc/pid/status is slow enough that procps and other packages
	 * kept stating /proc/pid.  To keep the rules in /proc simple I have
	 * made this apply to all per process world पढ़ोable and executable
	 * directories.
	 */
	अगर (mode != (S_IFसूची|S_IRUGO|S_IXUGO)) अणु
		काष्ठा mm_काष्ठा *mm;
		task_lock(task);
		mm = task->mm;
		/* Make non-dumpable tasks owned by some root */
		अगर (mm) अणु
			अगर (get_dumpable(mm) != SUID_DUMP_USER) अणु
				काष्ठा user_namespace *user_ns = mm->user_ns;

				uid = make_kuid(user_ns, 0);
				अगर (!uid_valid(uid))
					uid = GLOBAL_ROOT_UID;

				gid = make_kgid(user_ns, 0);
				अगर (!gid_valid(gid))
					gid = GLOBAL_ROOT_GID;
			पूर्ण
		पूर्ण अन्यथा अणु
			uid = GLOBAL_ROOT_UID;
			gid = GLOBAL_ROOT_GID;
		पूर्ण
		task_unlock(task);
	पूर्ण
	*ruid = uid;
	*rgid = gid;
पूर्ण

व्योम proc_pid_evict_inode(काष्ठा proc_inode *ei)
अणु
	काष्ठा pid *pid = ei->pid;

	अगर (S_ISसूची(ei->vfs_inode.i_mode)) अणु
		spin_lock(&pid->lock);
		hlist_del_init_rcu(&ei->sibling_inodes);
		spin_unlock(&pid->lock);
	पूर्ण

	put_pid(pid);
पूर्ण

काष्ठा inode *proc_pid_make_inode(काष्ठा super_block * sb,
				  काष्ठा task_काष्ठा *task, umode_t mode)
अणु
	काष्ठा inode * inode;
	काष्ठा proc_inode *ei;
	काष्ठा pid *pid;

	/* We need a new inode */

	inode = new_inode(sb);
	अगर (!inode)
		जाओ out;

	/* Common stuff */
	ei = PROC_I(inode);
	inode->i_mode = mode;
	inode->i_ino = get_next_ino();
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_op = &proc_def_inode_operations;

	/*
	 * grab the reference to task.
	 */
	pid = get_task_pid(task, PIDTYPE_PID);
	अगर (!pid)
		जाओ out_unlock;

	/* Let the pid remember us क्रम quick removal */
	ei->pid = pid;
	अगर (S_ISसूची(mode)) अणु
		spin_lock(&pid->lock);
		hlist_add_head_rcu(&ei->sibling_inodes, &pid->inodes);
		spin_unlock(&pid->lock);
	पूर्ण

	task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);
	security_task_to_inode(task, inode);

out:
	वापस inode;

out_unlock:
	iput(inode);
	वापस शून्य;
पूर्ण

पूर्णांक pid_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा proc_fs_info *fs_info = proc_sb_info(inode->i_sb);
	काष्ठा task_काष्ठा *task;

	generic_fillattr(&init_user_ns, inode, stat);

	stat->uid = GLOBAL_ROOT_UID;
	stat->gid = GLOBAL_ROOT_GID;
	rcu_पढ़ो_lock();
	task = pid_task(proc_pid(inode), PIDTYPE_PID);
	अगर (task) अणु
		अगर (!has_pid_permissions(fs_info, task, HIDEPID_INVISIBLE)) अणु
			rcu_पढ़ो_unlock();
			/*
			 * This करोesn't prevent learning whether PID exists,
			 * it only makes getattr() consistent with सूची_पढ़ो().
			 */
			वापस -ENOENT;
		पूर्ण
		task_dump_owner(task, inode->i_mode, &stat->uid, &stat->gid);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/* dentry stuff */

/*
 * Set <pid>/... inode ownership (can change due to setuid(), etc.)
 */
व्योम pid_update_inode(काष्ठा task_काष्ठा *task, काष्ठा inode *inode)
अणु
	task_dump_owner(task, inode->i_mode, &inode->i_uid, &inode->i_gid);

	inode->i_mode &= ~(S_ISUID | S_ISGID);
	security_task_to_inode(task, inode);
पूर्ण

/*
 * Reग_लिखो the inode's ownerships here because the owning task may have
 * perक्रमmed a setuid(), etc.
 *
 */
अटल पूर्णांक pid_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा task_काष्ठा *task;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	task = get_proc_task(inode);

	अगर (task) अणु
		pid_update_inode(task, inode);
		put_task_काष्ठा(task);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool proc_inode_is_dead(काष्ठा inode *inode)
अणु
	वापस !proc_pid(inode)->tasks[PIDTYPE_PID].first;
पूर्ण

पूर्णांक pid_delete_dentry(स्थिर काष्ठा dentry *dentry)
अणु
	/* Is the task we represent dead?
	 * If so, then करोn't put the dentry on the lru list,
	 * समाप्त it immediately.
	 */
	वापस proc_inode_is_dead(d_inode(dentry));
पूर्ण

स्थिर काष्ठा dentry_operations pid_dentry_operations =
अणु
	.d_revalidate	= pid_revalidate,
	.d_delete	= pid_delete_dentry,
पूर्ण;

/* Lookups */

/*
 * Fill a directory entry.
 *
 * If possible create the dcache entry and derive our inode number and
 * file type from dcache entry.
 *
 * Since all of the proc inode numbers are dynamically generated, the inode
 * numbers करो not exist until the inode is cache.  This means creating
 * the dcache entry in सूची_पढ़ो is necessary to keep the inode numbers
 * reported by सूची_पढ़ो in sync with the inode numbers reported
 * by stat.
 */
bool proc_fill_cache(काष्ठा file *file, काष्ठा dir_context *ctx,
	स्थिर अक्षर *name, अचिन्हित पूर्णांक len,
	instantiate_t instantiate, काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	काष्ठा dentry *child, *dir = file->f_path.dentry;
	काष्ठा qstr qname = QSTR_INIT(name, len);
	काष्ठा inode *inode;
	अचिन्हित type = DT_UNKNOWN;
	ino_t ino = 1;

	child = d_hash_and_lookup(dir, &qname);
	अगर (!child) अणु
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		child = d_alloc_parallel(dir, &qname, &wq);
		अगर (IS_ERR(child))
			जाओ end_instantiate;
		अगर (d_in_lookup(child)) अणु
			काष्ठा dentry *res;
			res = instantiate(child, task, ptr);
			d_lookup_करोne(child);
			अगर (unlikely(res)) अणु
				dput(child);
				child = res;
				अगर (IS_ERR(child))
					जाओ end_instantiate;
			पूर्ण
		पूर्ण
	पूर्ण
	inode = d_inode(child);
	ino = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
end_instantiate:
	वापस dir_emit(ctx, name, len, ino, type);
पूर्ण

/*
 * dname_to_vma_addr - maps a dentry name पूर्णांकo two अचिन्हित दीर्घs
 * which represent vma start and end addresses.
 */
अटल पूर्णांक dname_to_vma_addr(काष्ठा dentry *dentry,
			     अचिन्हित दीर्घ *start, अचिन्हित दीर्घ *end)
अणु
	स्थिर अक्षर *str = dentry->d_name.name;
	अचिन्हित दीर्घ दीर्घ sval, eval;
	अचिन्हित पूर्णांक len;

	अगर (str[0] == '0' && str[1] != '-')
		वापस -EINVAL;
	len = _parse_पूर्णांकeger(str, 16, &sval);
	अगर (len & KSTRTOX_OVERFLOW)
		वापस -EINVAL;
	अगर (sval != (अचिन्हित दीर्घ)sval)
		वापस -EINVAL;
	str += len;

	अगर (*str != '-')
		वापस -EINVAL;
	str++;

	अगर (str[0] == '0' && str[1])
		वापस -EINVAL;
	len = _parse_पूर्णांकeger(str, 16, &eval);
	अगर (len & KSTRTOX_OVERFLOW)
		वापस -EINVAL;
	अगर (eval != (अचिन्हित दीर्घ)eval)
		वापस -EINVAL;
	str += len;

	अगर (*str != '\0')
		वापस -EINVAL;

	*start = sval;
	*end = eval;

	वापस 0;
पूर्ण

अटल पूर्णांक map_files_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ vm_start, vm_end;
	bool exact_vma_exists = false;
	काष्ठा mm_काष्ठा *mm = शून्य;
	काष्ठा task_काष्ठा *task;
	काष्ठा inode *inode;
	पूर्णांक status = 0;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	task = get_proc_task(inode);
	अगर (!task)
		जाओ out_notask;

	mm = mm_access(task, PTRACE_MODE_READ_FSCREDS);
	अगर (IS_ERR_OR_शून्य(mm))
		जाओ out;

	अगर (!dname_to_vma_addr(dentry, &vm_start, &vm_end)) अणु
		status = mmap_पढ़ो_lock_समाप्तable(mm);
		अगर (!status) अणु
			exact_vma_exists = !!find_exact_vma(mm, vm_start,
							    vm_end);
			mmap_पढ़ो_unlock(mm);
		पूर्ण
	पूर्ण

	mmput(mm);

	अगर (exact_vma_exists) अणु
		task_dump_owner(task, 0, &inode->i_uid, &inode->i_gid);

		security_task_to_inode(task, inode);
		status = 1;
	पूर्ण

out:
	put_task_काष्ठा(task);

out_notask:
	वापस status;
पूर्ण

अटल स्थिर काष्ठा dentry_operations tid_map_files_dentry_operations = अणु
	.d_revalidate	= map_files_d_revalidate,
	.d_delete	= pid_delete_dentry,
पूर्ण;

अटल पूर्णांक map_files_get_link(काष्ठा dentry *dentry, काष्ठा path *path)
अणु
	अचिन्हित दीर्घ vm_start, vm_end;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक rc;

	rc = -ENOENT;
	task = get_proc_task(d_inode(dentry));
	अगर (!task)
		जाओ out;

	mm = get_task_mm(task);
	put_task_काष्ठा(task);
	अगर (!mm)
		जाओ out;

	rc = dname_to_vma_addr(dentry, &vm_start, &vm_end);
	अगर (rc)
		जाओ out_mmput;

	rc = mmap_पढ़ो_lock_समाप्तable(mm);
	अगर (rc)
		जाओ out_mmput;

	rc = -ENOENT;
	vma = find_exact_vma(mm, vm_start, vm_end);
	अगर (vma && vma->vm_file) अणु
		*path = vma->vm_file->f_path;
		path_get(path);
		rc = 0;
	पूर्ण
	mmap_पढ़ो_unlock(mm);

out_mmput:
	mmput(mm);
out:
	वापस rc;
पूर्ण

काष्ठा map_files_info अणु
	अचिन्हित दीर्घ	start;
	अचिन्हित दीर्घ	end;
	भ_शेषe_t		mode;
पूर्ण;

/*
 * Only allow CAP_SYS_ADMIN and CAP_CHECKPOINT_RESTORE to follow the links, due
 * to concerns about how the symlinks may be used to bypass permissions on
 * ancestor directories in the path to the file in question.
 */
अटल स्थिर अक्षर *
proc_map_files_get_link(काष्ठा dentry *dentry,
			काष्ठा inode *inode,
		        काष्ठा delayed_call *करोne)
अणु
	अगर (!checkpoपूर्णांक_restore_ns_capable(&init_user_ns))
		वापस ERR_PTR(-EPERM);

	वापस proc_pid_get_link(dentry, inode, करोne);
पूर्ण

/*
 * Identical to proc_pid_link_inode_operations except क्रम get_link()
 */
अटल स्थिर काष्ठा inode_operations proc_map_files_link_inode_operations = अणु
	.पढ़ोlink	= proc_pid_पढ़ोlink,
	.get_link	= proc_map_files_get_link,
	.setattr	= proc_setattr,
पूर्ण;

अटल काष्ठा dentry *
proc_map_files_instantiate(काष्ठा dentry *dentry,
			   काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	भ_शेषe_t mode = (भ_शेषe_t)(अचिन्हित दीर्घ)ptr;
	काष्ठा proc_inode *ei;
	काष्ठा inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK |
				    ((mode & FMODE_READ ) ? S_IRUSR : 0) |
				    ((mode & FMODE_WRITE) ? S_IWUSR : 0));
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	ei->op.proc_get_link = map_files_get_link;

	inode->i_op = &proc_map_files_link_inode_operations;
	inode->i_size = 64;

	d_set_d_op(dentry, &tid_map_files_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा dentry *proc_map_files_lookup(काष्ठा inode *dir,
		काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित दीर्घ vm_start, vm_end;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *task;
	काष्ठा dentry *result;
	काष्ठा mm_काष्ठा *mm;

	result = ERR_PTR(-ENOENT);
	task = get_proc_task(dir);
	अगर (!task)
		जाओ out;

	result = ERR_PTR(-EACCES);
	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
		जाओ out_put_task;

	result = ERR_PTR(-ENOENT);
	अगर (dname_to_vma_addr(dentry, &vm_start, &vm_end))
		जाओ out_put_task;

	mm = get_task_mm(task);
	अगर (!mm)
		जाओ out_put_task;

	result = ERR_PTR(-EINTR);
	अगर (mmap_पढ़ो_lock_समाप्तable(mm))
		जाओ out_put_mm;

	result = ERR_PTR(-ENOENT);
	vma = find_exact_vma(mm, vm_start, vm_end);
	अगर (!vma)
		जाओ out_no_vma;

	अगर (vma->vm_file)
		result = proc_map_files_instantiate(dentry, task,
				(व्योम *)(अचिन्हित दीर्घ)vma->vm_file->f_mode);

out_no_vma:
	mmap_पढ़ो_unlock(mm);
out_put_mm:
	mmput(mm);
out_put_task:
	put_task_काष्ठा(task);
out:
	वापस result;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_map_files_inode_operations = अणु
	.lookup		= proc_map_files_lookup,
	.permission	= proc_fd_permission,
	.setattr	= proc_setattr,
पूर्ण;

अटल पूर्णांक
proc_map_files_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ nr_files, pos, i;
	GENRADIX(काष्ठा map_files_info) fa;
	काष्ठा map_files_info *p;
	पूर्णांक ret;

	genradix_init(&fa);

	ret = -ENOENT;
	task = get_proc_task(file_inode(file));
	अगर (!task)
		जाओ out;

	ret = -EACCES;
	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
		जाओ out_put_task;

	ret = 0;
	अगर (!dir_emit_करोts(file, ctx))
		जाओ out_put_task;

	mm = get_task_mm(task);
	अगर (!mm)
		जाओ out_put_task;

	ret = mmap_पढ़ो_lock_समाप्तable(mm);
	अगर (ret) अणु
		mmput(mm);
		जाओ out_put_task;
	पूर्ण

	nr_files = 0;

	/*
	 * We need two passes here:
	 *
	 *  1) Collect vmas of mapped files with mmap_lock taken
	 *  2) Release mmap_lock and instantiate entries
	 *
	 * otherwise we get lockdep complained, since filldir()
	 * routine might require mmap_lock taken in might_fault().
	 */

	क्रम (vma = mm->mmap, pos = 2; vma; vma = vma->vm_next) अणु
		अगर (!vma->vm_file)
			जारी;
		अगर (++pos <= ctx->pos)
			जारी;

		p = genradix_ptr_alloc(&fa, nr_files++, GFP_KERNEL);
		अगर (!p) अणु
			ret = -ENOMEM;
			mmap_पढ़ो_unlock(mm);
			mmput(mm);
			जाओ out_put_task;
		पूर्ण

		p->start = vma->vm_start;
		p->end = vma->vm_end;
		p->mode = vma->vm_file->f_mode;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	क्रम (i = 0; i < nr_files; i++) अणु
		अक्षर buf[4 * माप(दीर्घ) + 2];	/* max: %lx-%lx\0 */
		अचिन्हित पूर्णांक len;

		p = genradix_ptr(&fa, i);
		len = snम_लिखो(buf, माप(buf), "%lx-%lx", p->start, p->end);
		अगर (!proc_fill_cache(file, ctx,
				      buf, len,
				      proc_map_files_instantiate,
				      task,
				      (व्योम *)(अचिन्हित दीर्घ)p->mode))
			अवरोध;
		ctx->pos++;
	पूर्ण

out_put_task:
	put_task_काष्ठा(task);
out:
	genradix_मुक्त(&fa);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_map_files_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_map_files_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

#अगर defined(CONFIG_CHECKPOINT_RESTORE) && defined(CONFIG_POSIX_TIMERS)
काष्ठा समयrs_निजी अणु
	काष्ठा pid *pid;
	काष्ठा task_काष्ठा *task;
	काष्ठा sighand_काष्ठा *sighand;
	काष्ठा pid_namespace *ns;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल व्योम *समयrs_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा समयrs_निजी *tp = m->निजी;

	tp->task = get_pid_task(tp->pid, PIDTYPE_PID);
	अगर (!tp->task)
		वापस ERR_PTR(-ESRCH);

	tp->sighand = lock_task_sighand(tp->task, &tp->flags);
	अगर (!tp->sighand)
		वापस ERR_PTR(-ESRCH);

	वापस seq_list_start(&tp->task->संकेत->posix_समयrs, *pos);
पूर्ण

अटल व्योम *समयrs_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा समयrs_निजी *tp = m->निजी;
	वापस seq_list_next(v, &tp->task->संकेत->posix_समयrs, pos);
पूर्ण

अटल व्योम समयrs_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा समयrs_निजी *tp = m->निजी;

	अगर (tp->sighand) अणु
		unlock_task_sighand(tp->task, &tp->flags);
		tp->sighand = शून्य;
	पूर्ण

	अगर (tp->task) अणु
		put_task_काष्ठा(tp->task);
		tp->task = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक show_समयr(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा k_iसमयr *समयr;
	काष्ठा समयrs_निजी *tp = m->निजी;
	पूर्णांक notअगरy;
	अटल स्थिर अक्षर * स्थिर nstr[] = अणु
		[SIGEV_SIGNAL] = "signal",
		[SIGEV_NONE] = "none",
		[SIGEV_THREAD] = "thread",
	पूर्ण;

	समयr = list_entry((काष्ठा list_head *)v, काष्ठा k_iसमयr, list);
	notअगरy = समयr->it_sigev_notअगरy;

	seq_म_लिखो(m, "ID: %d\n", समयr->it_id);
	seq_म_लिखो(m, "signal: %d/%px\n",
		   समयr->sigq->info.si_signo,
		   समयr->sigq->info.si_value.sival_ptr);
	seq_म_लिखो(m, "notify: %s/%s.%d\n",
		   nstr[notअगरy & ~SIGEV_THREAD_ID],
		   (notअगरy & SIGEV_THREAD_ID) ? "tid" : "pid",
		   pid_nr_ns(समयr->it_pid, tp->ns));
	seq_म_लिखो(m, "ClockID: %d\n", समयr->it_घड़ी);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations proc_समयrs_seq_ops = अणु
	.start	= समयrs_start,
	.next	= समयrs_next,
	.stop	= समयrs_stop,
	.show	= show_समयr,
पूर्ण;

अटल पूर्णांक proc_समयrs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा समयrs_निजी *tp;

	tp = __seq_खोलो_निजी(file, &proc_समयrs_seq_ops,
			माप(काष्ठा समयrs_निजी));
	अगर (!tp)
		वापस -ENOMEM;

	tp->pid = proc_pid(inode);
	tp->ns = proc_pid_ns(inode->i_sb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_समयrs_operations = अणु
	.खोलो		= proc_समयrs_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release_निजी,
पूर्ण;
#पूर्ण_अगर

अटल sमाप_प्रकार समयrslack_ns_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा task_काष्ठा *p;
	u64 slack_ns;
	पूर्णांक err;

	err = kम_से_अदीर्घl_from_user(buf, count, 10, &slack_ns);
	अगर (err < 0)
		वापस err;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;

	अगर (p != current) अणु
		rcu_पढ़ो_lock();
		अगर (!ns_capable(__task_cred(p)->user_ns, CAP_SYS_NICE)) अणु
			rcu_पढ़ो_unlock();
			count = -EPERM;
			जाओ out;
		पूर्ण
		rcu_पढ़ो_unlock();

		err = security_task_setscheduler(p);
		अगर (err) अणु
			count = err;
			जाओ out;
		पूर्ण
	पूर्ण

	task_lock(p);
	अगर (slack_ns == 0)
		p->समयr_slack_ns = p->शेष_समयr_slack_ns;
	अन्यथा
		p->समयr_slack_ns = slack_ns;
	task_unlock(p);

out:
	put_task_काष्ठा(p);

	वापस count;
पूर्ण

अटल पूर्णांक समयrslack_ns_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा inode *inode = m->निजी;
	काष्ठा task_काष्ठा *p;
	पूर्णांक err = 0;

	p = get_proc_task(inode);
	अगर (!p)
		वापस -ESRCH;

	अगर (p != current) अणु
		rcu_पढ़ो_lock();
		अगर (!ns_capable(__task_cred(p)->user_ns, CAP_SYS_NICE)) अणु
			rcu_पढ़ो_unlock();
			err = -EPERM;
			जाओ out;
		पूर्ण
		rcu_पढ़ो_unlock();

		err = security_task_माला_लोcheduler(p);
		अगर (err)
			जाओ out;
	पूर्ण

	task_lock(p);
	seq_म_लिखो(m, "%llu\n", p->समयr_slack_ns);
	task_unlock(p);

out:
	put_task_काष्ठा(p);

	वापस err;
पूर्ण

अटल पूर्णांक समयrslack_ns_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस single_खोलो(filp, समयrslack_ns_show, inode);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_set_समयrslack_ns_operations = अणु
	.खोलो		= समयrslack_ns_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= समयrslack_ns_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल काष्ठा dentry *proc_pident_instantiate(काष्ठा dentry *dentry,
	काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा pid_entry *p = ptr;
	काष्ठा inode *inode;
	काष्ठा proc_inode *ei;

	inode = proc_pid_make_inode(dentry->d_sb, task, p->mode);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	अगर (S_ISसूची(inode->i_mode))
		set_nlink(inode, 2);	/* Use getattr to fix अगर necessary */
	अगर (p->iop)
		inode->i_op = p->iop;
	अगर (p->fop)
		inode->i_fop = p->fop;
	ei->op = p->op;
	pid_update_inode(task, inode);
	d_set_d_op(dentry, &pid_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा dentry *proc_pident_lookup(काष्ठा inode *dir, 
					 काष्ठा dentry *dentry,
					 स्थिर काष्ठा pid_entry *p,
					 स्थिर काष्ठा pid_entry *end)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(dir);
	काष्ठा dentry *res = ERR_PTR(-ENOENT);

	अगर (!task)
		जाओ out_no_task;

	/*
	 * Yes, it करोes not scale. And it should not. Don't add
	 * new entries पूर्णांकo /proc/<tgid>/ without very good reasons.
	 */
	क्रम (; p < end; p++) अणु
		अगर (p->len != dentry->d_name.len)
			जारी;
		अगर (!स_भेद(dentry->d_name.name, p->name, p->len)) अणु
			res = proc_pident_instantiate(dentry, task, p);
			अवरोध;
		पूर्ण
	पूर्ण
	put_task_काष्ठा(task);
out_no_task:
	वापस res;
पूर्ण

अटल पूर्णांक proc_pident_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx,
		स्थिर काष्ठा pid_entry *ents, अचिन्हित पूर्णांक nents)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	स्थिर काष्ठा pid_entry *p;

	अगर (!task)
		वापस -ENOENT;

	अगर (!dir_emit_करोts(file, ctx))
		जाओ out;

	अगर (ctx->pos >= nents + 2)
		जाओ out;

	क्रम (p = ents + (ctx->pos - 2); p < ents + nents; p++) अणु
		अगर (!proc_fill_cache(file, ctx, p->name, p->len,
				proc_pident_instantiate, task, p))
			अवरोध;
		ctx->pos++;
	पूर्ण
out:
	put_task_काष्ठा(task);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SECURITY
अटल पूर्णांक proc_pid_attr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = शून्य;
	__mem_खोलो(inode, file, PTRACE_MODE_READ_FSCREDS);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार proc_pid_attr_पढ़ो(काष्ठा file * file, अक्षर __user * buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode * inode = file_inode(file);
	अक्षर *p = शून्य;
	sमाप_प्रकार length;
	काष्ठा task_काष्ठा *task = get_proc_task(inode);

	अगर (!task)
		वापस -ESRCH;

	length = security_getprocattr(task, PROC_I(inode)->op.lsm,
				      (अक्षर*)file->f_path.dentry->d_name.name,
				      &p);
	put_task_काष्ठा(task);
	अगर (length > 0)
		length = simple_पढ़ो_from_buffer(buf, count, ppos, p, length);
	kमुक्त(p);
	वापस length;
पूर्ण

अटल sमाप_प्रकार proc_pid_attr_ग_लिखो(काष्ठा file * file, स्थिर अक्षर __user * buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा inode * inode = file_inode(file);
	काष्ठा task_काष्ठा *task;
	व्योम *page;
	पूर्णांक rv;

	/* A task may only ग_लिखो when it was the खोलोer. */
	अगर (file->निजी_data != current->mm)
		वापस -EPERM;

	rcu_पढ़ो_lock();
	task = pid_task(proc_pid(inode), PIDTYPE_PID);
	अगर (!task) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण
	/* A task may only ग_लिखो its own attributes. */
	अगर (current != task) अणु
		rcu_पढ़ो_unlock();
		वापस -EACCES;
	पूर्ण
	/* Prevent changes to overridden credentials. */
	अगर (current_cred() != current_real_cred()) अणु
		rcu_पढ़ो_unlock();
		वापस -EBUSY;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (count > PAGE_SIZE)
		count = PAGE_SIZE;

	/* No partial ग_लिखोs. */
	अगर (*ppos != 0)
		वापस -EINVAL;

	page = memdup_user(buf, count);
	अगर (IS_ERR(page)) अणु
		rv = PTR_ERR(page);
		जाओ out;
	पूर्ण

	/* Guard against adverse ptrace पूर्णांकeraction */
	rv = mutex_lock_पूर्णांकerruptible(&current->संकेत->cred_guard_mutex);
	अगर (rv < 0)
		जाओ out_मुक्त;

	rv = security_setprocattr(PROC_I(inode)->op.lsm,
				  file->f_path.dentry->d_name.name, page,
				  count);
	mutex_unlock(&current->संकेत->cred_guard_mutex);
out_मुक्त:
	kमुक्त(page);
out:
	वापस rv;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_pid_attr_operations = अणु
	.खोलो		= proc_pid_attr_खोलो,
	.पढ़ो		= proc_pid_attr_पढ़ो,
	.ग_लिखो		= proc_pid_attr_ग_लिखो,
	.llseek		= generic_file_llseek,
	.release	= mem_release,
पूर्ण;

#घोषणा LSM_सूची_OPS(LSM) \
अटल पूर्णांक proc_##LSM##_attr_dir_iterate(काष्ठा file *filp, \
			     काष्ठा dir_context *ctx) \
अणु \
	वापस proc_pident_सूची_पढ़ो(filp, ctx, \
				   LSM##_attr_dir_stuff, \
				   ARRAY_SIZE(LSM##_attr_dir_stuff)); \
पूर्ण \
\
अटल स्थिर काष्ठा file_operations proc_##LSM##_attr_dir_ops = अणु \
	.पढ़ो		= generic_पढ़ो_dir, \
	.iterate	= proc_##LSM##_attr_dir_iterate, \
	.llseek		= शेष_llseek, \
पूर्ण; \
\
अटल काष्ठा dentry *proc_##LSM##_attr_dir_lookup(काष्ठा inode *dir, \
				काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags) \
अणु \
	वापस proc_pident_lookup(dir, dentry, \
				  LSM##_attr_dir_stuff, \
				  LSM##_attr_dir_stuff + ARRAY_SIZE(LSM##_attr_dir_stuff)); \
पूर्ण \
\
अटल स्थिर काष्ठा inode_operations proc_##LSM##_attr_dir_inode_ops = अणु \
	.lookup		= proc_##LSM##_attr_dir_lookup, \
	.getattr	= pid_getattr, \
	.setattr	= proc_setattr, \
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SMACK
अटल स्थिर काष्ठा pid_entry smack_attr_dir_stuff[] = अणु
	ATTR("smack", "current",	0666),
पूर्ण;
LSM_सूची_OPS(smack);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SECURITY_APPARMOR
अटल स्थिर काष्ठा pid_entry apparmor_attr_dir_stuff[] = अणु
	ATTR("apparmor", "current",	0666),
	ATTR("apparmor", "prev",	0444),
	ATTR("apparmor", "exec",	0666),
पूर्ण;
LSM_सूची_OPS(apparmor);
#पूर्ण_अगर

अटल स्थिर काष्ठा pid_entry attr_dir_stuff[] = अणु
	ATTR(शून्य, "current",		0666),
	ATTR(शून्य, "prev",		0444),
	ATTR(शून्य, "exec",		0666),
	ATTR(शून्य, "fscreate",		0666),
	ATTR(शून्य, "keycreate",		0666),
	ATTR(शून्य, "sockcreate",	0666),
#अगर_घोषित CONFIG_SECURITY_SMACK
	सूची("smack",			0555,
	    proc_smack_attr_dir_inode_ops, proc_smack_attr_dir_ops),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_APPARMOR
	सूची("apparmor",			0555,
	    proc_apparmor_attr_dir_inode_ops, proc_apparmor_attr_dir_ops),
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक proc_attr_dir_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस proc_pident_सूची_पढ़ो(file, ctx, 
				   attr_dir_stuff, ARRAY_SIZE(attr_dir_stuff));
पूर्ण

अटल स्थिर काष्ठा file_operations proc_attr_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_attr_dir_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल काष्ठा dentry *proc_attr_dir_lookup(काष्ठा inode *dir,
				काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस proc_pident_lookup(dir, dentry,
				  attr_dir_stuff,
				  attr_dir_stuff + ARRAY_SIZE(attr_dir_stuff));
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_attr_dir_inode_operations = अणु
	.lookup		= proc_attr_dir_lookup,
	.getattr	= pid_getattr,
	.setattr	= proc_setattr,
पूर्ण;

#पूर्ण_अगर

#अगर_घोषित CONFIG_ELF_CORE
अटल sमाप_प्रकार proc_coredump_filter_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	काष्ठा mm_काष्ठा *mm;
	अक्षर buffer[PROC_NUMBUF];
	माप_प्रकार len;
	पूर्णांक ret;

	अगर (!task)
		वापस -ESRCH;

	ret = 0;
	mm = get_task_mm(task);
	अगर (mm) अणु
		len = snम_लिखो(buffer, माप(buffer), "%08lx\n",
			       ((mm->flags & MMF_DUMP_FILTER_MASK) >>
				MMF_DUMP_FILTER_SHIFT));
		mmput(mm);
		ret = simple_पढ़ो_from_buffer(buf, count, ppos, buffer, len);
	पूर्ण

	put_task_काष्ठा(task);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार proc_coredump_filter_ग_लिखो(काष्ठा file *file,
					  स्थिर अक्षर __user *buf,
					  माप_प्रकार count,
					  loff_t *ppos)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित दीर्घ mask;

	ret = kstrtouपूर्णांक_from_user(buf, count, 0, &val);
	अगर (ret < 0)
		वापस ret;

	ret = -ESRCH;
	task = get_proc_task(file_inode(file));
	अगर (!task)
		जाओ out_no_task;

	mm = get_task_mm(task);
	अगर (!mm)
		जाओ out_no_mm;
	ret = 0;

	क्रम (i = 0, mask = 1; i < MMF_DUMP_FILTER_BITS; i++, mask <<= 1) अणु
		अगर (val & mask)
			set_bit(i + MMF_DUMP_FILTER_SHIFT, &mm->flags);
		अन्यथा
			clear_bit(i + MMF_DUMP_FILTER_SHIFT, &mm->flags);
	पूर्ण

	mmput(mm);
 out_no_mm:
	put_task_काष्ठा(task);
 out_no_task:
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_coredump_filter_operations = अणु
	.पढ़ो		= proc_coredump_filter_पढ़ो,
	.ग_लिखो		= proc_coredump_filter_ग_लिखो,
	.llseek		= generic_file_llseek,
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
अटल पूर्णांक करो_io_accounting(काष्ठा task_काष्ठा *task, काष्ठा seq_file *m, पूर्णांक whole)
अणु
	काष्ठा task_io_accounting acct = task->ioac;
	अचिन्हित दीर्घ flags;
	पूर्णांक result;

	result = करोwn_पढ़ो_समाप्तable(&task->संकेत->exec_update_lock);
	अगर (result)
		वापस result;

	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS)) अणु
		result = -EACCES;
		जाओ out_unlock;
	पूर्ण

	अगर (whole && lock_task_sighand(task, &flags)) अणु
		काष्ठा task_काष्ठा *t = task;

		task_io_accounting_add(&acct, &task->संकेत->ioac);
		जबतक_each_thपढ़ो(task, t)
			task_io_accounting_add(&acct, &t->ioac);

		unlock_task_sighand(task, &flags);
	पूर्ण
	seq_म_लिखो(m,
		   "rchar: %llu\n"
		   "wchar: %llu\n"
		   "syscr: %llu\n"
		   "syscw: %llu\n"
		   "read_bytes: %llu\n"
		   "write_bytes: %llu\n"
		   "cancelled_write_bytes: %llu\n",
		   (अचिन्हित दीर्घ दीर्घ)acct.rअक्षर,
		   (अचिन्हित दीर्घ दीर्घ)acct.wअक्षर,
		   (अचिन्हित दीर्घ दीर्घ)acct.syscr,
		   (अचिन्हित दीर्घ दीर्घ)acct.syscw,
		   (अचिन्हित दीर्घ दीर्घ)acct.पढ़ो_bytes,
		   (अचिन्हित दीर्घ दीर्घ)acct.ग_लिखो_bytes,
		   (अचिन्हित दीर्घ दीर्घ)acct.cancelled_ग_लिखो_bytes);
	result = 0;

out_unlock:
	up_पढ़ो(&task->संकेत->exec_update_lock);
	वापस result;
पूर्ण

अटल पूर्णांक proc_tid_io_accounting(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				  काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	वापस करो_io_accounting(task, m, 0);
पूर्ण

अटल पूर्णांक proc_tgid_io_accounting(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				   काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	वापस करो_io_accounting(task, m, 1);
पूर्ण
#पूर्ण_अगर /* CONFIG_TASK_IO_ACCOUNTING */

#अगर_घोषित CONFIG_USER_NS
अटल पूर्णांक proc_id_map_खोलो(काष्ठा inode *inode, काष्ठा file *file,
	स्थिर काष्ठा seq_operations *seq_ops)
अणु
	काष्ठा user_namespace *ns = शून्य;
	काष्ठा task_काष्ठा *task;
	काष्ठा seq_file *seq;
	पूर्णांक ret = -EINVAL;

	task = get_proc_task(inode);
	अगर (task) अणु
		rcu_पढ़ो_lock();
		ns = get_user_ns(task_cred_xxx(task, user_ns));
		rcu_पढ़ो_unlock();
		put_task_काष्ठा(task);
	पूर्ण
	अगर (!ns)
		जाओ err;

	ret = seq_खोलो(file, seq_ops);
	अगर (ret)
		जाओ err_put_ns;

	seq = file->निजी_data;
	seq->निजी = ns;

	वापस 0;
err_put_ns:
	put_user_ns(ns);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक proc_id_map_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	put_user_ns(ns);
	वापस seq_release(inode, file);
पूर्ण

अटल पूर्णांक proc_uid_map_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस proc_id_map_खोलो(inode, file, &proc_uid_seq_operations);
पूर्ण

अटल पूर्णांक proc_gid_map_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस proc_id_map_खोलो(inode, file, &proc_gid_seq_operations);
पूर्ण

अटल पूर्णांक proc_projid_map_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस proc_id_map_खोलो(inode, file, &proc_projid_seq_operations);
पूर्ण

अटल स्थिर काष्ठा file_operations proc_uid_map_operations = अणु
	.खोलो		= proc_uid_map_खोलो,
	.ग_लिखो		= proc_uid_map_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_id_map_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_gid_map_operations = अणु
	.खोलो		= proc_gid_map_खोलो,
	.ग_लिखो		= proc_gid_map_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_id_map_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_projid_map_operations = अणु
	.खोलो		= proc_projid_map_खोलो,
	.ग_लिखो		= proc_projid_map_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_id_map_release,
पूर्ण;

अटल पूर्णांक proc_setgroups_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा user_namespace *ns = शून्य;
	काष्ठा task_काष्ठा *task;
	पूर्णांक ret;

	ret = -ESRCH;
	task = get_proc_task(inode);
	अगर (task) अणु
		rcu_पढ़ो_lock();
		ns = get_user_ns(task_cred_xxx(task, user_ns));
		rcu_पढ़ो_unlock();
		put_task_काष्ठा(task);
	पूर्ण
	अगर (!ns)
		जाओ err;

	अगर (file->f_mode & FMODE_WRITE) अणु
		ret = -EACCES;
		अगर (!ns_capable(ns, CAP_SYS_ADMIN))
			जाओ err_put_ns;
	पूर्ण

	ret = single_खोलो(file, &proc_setgroups_show, ns);
	अगर (ret)
		जाओ err_put_ns;

	वापस 0;
err_put_ns:
	put_user_ns(ns);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक proc_setgroups_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा user_namespace *ns = seq->निजी;
	पूर्णांक ret = single_release(inode, file);
	put_user_ns(ns);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_setgroups_operations = अणु
	.खोलो		= proc_setgroups_खोलो,
	.ग_लिखो		= proc_setgroups_ग_लिखो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= proc_setgroups_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_USER_NS */

अटल पूर्णांक proc_pid_personality(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक err = lock_trace(task);
	अगर (!err) अणु
		seq_म_लिखो(m, "%08x\n", task->personality);
		unlock_trace(task);
	पूर्ण
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_LIVEPATCH
अटल पूर्णांक proc_pid_patch_state(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	seq_म_लिखो(m, "%d\n", task->patch_state);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_LIVEPATCH */

#अगर_घोषित CONFIG_STACKLEAK_METRICS
अटल पूर्णांक proc_stack_depth(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
				काष्ठा pid *pid, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ prev_depth = THREAD_SIZE -
				(task->prev_lowest_stack & (THREAD_SIZE - 1));
	अचिन्हित दीर्घ depth = THREAD_SIZE -
				(task->lowest_stack & (THREAD_SIZE - 1));

	seq_म_लिखो(m, "previous stack depth: %lu\nstack depth: %lu\n",
							prev_depth, depth);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_STACKLEAK_METRICS */

/*
 * Thपढ़ो groups
 */
अटल स्थिर काष्ठा file_operations proc_task_operations;
अटल स्थिर काष्ठा inode_operations proc_task_inode_operations;

अटल स्थिर काष्ठा pid_entry tgid_base_stuff[] = अणु
	सूची("task",       S_IRUGO|S_IXUGO, proc_task_inode_operations, proc_task_operations),
	सूची("fd",         S_IRUSR|S_IXUSR, proc_fd_inode_operations, proc_fd_operations),
	सूची("map_files",  S_IRUSR|S_IXUSR, proc_map_files_inode_operations, proc_map_files_operations),
	सूची("fdinfo",     S_IRUSR|S_IXUSR, proc_fdinfo_inode_operations, proc_fdinfo_operations),
	सूची("ns",	  S_IRUSR|S_IXUGO, proc_ns_dir_inode_operations, proc_ns_dir_operations),
#अगर_घोषित CONFIG_NET
	सूची("net",        S_IRUGO|S_IXUGO, proc_net_inode_operations, proc_net_operations),
#पूर्ण_अगर
	REG("environ",    S_IRUSR, proc_environ_operations),
	REG("auxv",       S_IRUSR, proc_auxv_operations),
	ONE("status",     S_IRUGO, proc_pid_status),
	ONE("personality", S_IRUSR, proc_pid_personality),
	ONE("limits",	  S_IRUGO, proc_pid_limits),
#अगर_घोषित CONFIG_SCHED_DEBUG
	REG("sched",      S_IRUGO|S_IWUSR, proc_pid_sched_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_AUTOGROUP
	REG("autogroup",  S_IRUGO|S_IWUSR, proc_pid_sched_स्वतःgroup_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIME_NS
	REG("timens_offsets",  S_IRUGO|S_IWUSR, proc_समयns_offsets_operations),
#पूर्ण_अगर
	REG("comm",      S_IRUGO|S_IWUSR, proc_pid_set_comm_operations),
#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK
	ONE("syscall",    S_IRUSR, proc_pid_syscall),
#पूर्ण_अगर
	REG("cmdline",    S_IRUGO, proc_pid_cmdline_ops),
	ONE("stat",       S_IRUGO, proc_tgid_stat),
	ONE("statm",      S_IRUGO, proc_pid_staपंचांग),
	REG("maps",       S_IRUGO, proc_pid_maps_operations),
#अगर_घोषित CONFIG_NUMA
	REG("numa_maps",  S_IRUGO, proc_pid_numa_maps_operations),
#पूर्ण_अगर
	REG("mem",        S_IRUSR|S_IWUSR, proc_mem_operations),
	LNK("cwd",        proc_cwd_link),
	LNK("root",       proc_root_link),
	LNK("exe",        proc_exe_link),
	REG("mounts",     S_IRUGO, proc_mounts_operations),
	REG("mountinfo",  S_IRUGO, proc_mountinfo_operations),
	REG("mountstats", S_IRUSR, proc_mountstats_operations),
#अगर_घोषित CONFIG_PROC_PAGE_MONITOR
	REG("clear_refs", S_IWUSR, proc_clear_refs_operations),
	REG("smaps",      S_IRUGO, proc_pid_smaps_operations),
	REG("smaps_rollup", S_IRUGO, proc_pid_smaps_rollup_operations),
	REG("pagemap",    S_IRUSR, proc_pagemap_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY
	सूची("attr",       S_IRUGO|S_IXUGO, proc_attr_dir_inode_operations, proc_attr_dir_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_KALLSYMS
	ONE("wchan",      S_IRUGO, proc_pid_wchan),
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKTRACE
	ONE("stack",      S_IRUSR, proc_pid_stack),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_INFO
	ONE("schedstat",  S_IRUGO, proc_pid_schedstat),
#पूर्ण_अगर
#अगर_घोषित CONFIG_LATENCYTOP
	REG("latency",  S_IRUGO, proc_lstats_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_PID_CPUSET
	ONE("cpuset",     S_IRUGO, proc_cpuset_show),
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	ONE("cgroup",  S_IRUGO, proc_cgroup_show),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_CPU_RESCTRL
	ONE("cpu_resctrl_groups", S_IRUGO, proc_resctrl_show),
#पूर्ण_अगर
	ONE("oom_score",  S_IRUGO, proc_oom_score),
	REG("oom_adj",    S_IRUGO|S_IWUSR, proc_oom_adj_operations),
	REG("oom_score_adj", S_IRUGO|S_IWUSR, proc_oom_score_adj_operations),
#अगर_घोषित CONFIG_AUDIT
	REG("loginuid",   S_IWUSR|S_IRUGO, proc_loginuid_operations),
	REG("sessionid",  S_IRUGO, proc_sessionid_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_FAULT_INJECTION
	REG("make-it-fail", S_IRUGO|S_IWUSR, proc_fault_inject_operations),
	REG("fail-nth", 0644, proc_fail_nth_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_ELF_CORE
	REG("coredump_filter", S_IRUGO|S_IWUSR, proc_coredump_filter_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
	ONE("io",	S_IRUSR, proc_tgid_io_accounting),
#पूर्ण_अगर
#अगर_घोषित CONFIG_USER_NS
	REG("uid_map",    S_IRUGO|S_IWUSR, proc_uid_map_operations),
	REG("gid_map",    S_IRUGO|S_IWUSR, proc_gid_map_operations),
	REG("projid_map", S_IRUGO|S_IWUSR, proc_projid_map_operations),
	REG("setgroups",  S_IRUGO|S_IWUSR, proc_setgroups_operations),
#पूर्ण_अगर
#अगर defined(CONFIG_CHECKPOINT_RESTORE) && defined(CONFIG_POSIX_TIMERS)
	REG("timers",	  S_IRUGO, proc_समयrs_operations),
#पूर्ण_अगर
	REG("timerslack_ns", S_IRUGO|S_IWUGO, proc_pid_set_समयrslack_ns_operations),
#अगर_घोषित CONFIG_LIVEPATCH
	ONE("patch_state",  S_IRUSR, proc_pid_patch_state),
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKLEAK_METRICS
	ONE("stack_depth", S_IRUGO, proc_stack_depth),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_PID_ARCH_STATUS
	ONE("arch_status", S_IRUGO, proc_pid_arch_status),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECCOMP_CACHE_DEBUG
	ONE("seccomp_cache", S_IRUSR, proc_pid_seccomp_cache),
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक proc_tgid_base_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस proc_pident_सूची_पढ़ो(file, ctx,
				   tgid_base_stuff, ARRAY_SIZE(tgid_base_stuff));
पूर्ण

अटल स्थिर काष्ठा file_operations proc_tgid_base_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_tgid_base_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

काष्ठा pid *tgid_pidfd_to_pid(स्थिर काष्ठा file *file)
अणु
	अगर (file->f_op != &proc_tgid_base_operations)
		वापस ERR_PTR(-EBADF);

	वापस proc_pid(file_inode(file));
पूर्ण

अटल काष्ठा dentry *proc_tgid_base_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस proc_pident_lookup(dir, dentry,
				  tgid_base_stuff,
				  tgid_base_stuff + ARRAY_SIZE(tgid_base_stuff));
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_tgid_base_inode_operations = अणु
	.lookup		= proc_tgid_base_lookup,
	.getattr	= pid_getattr,
	.setattr	= proc_setattr,
	.permission	= proc_pid_permission,
पूर्ण;

/**
 * proc_flush_pid -  Remove dcache entries क्रम @pid from the /proc dcache.
 * @pid: pid that should be flushed.
 *
 * This function walks a list of inodes (that beदीर्घ to any proc
 * fileप्रणाली) that are attached to the pid and flushes them from
 * the dentry cache.
 *
 * It is safe and reasonable to cache /proc entries क्रम a task until
 * that task निकासs.  After that they just clog up the dcache with
 * useless entries, possibly causing useful dcache entries to be
 * flushed instead.  This routine is provided to flush those useless
 * dcache entries when a process is reaped.
 *
 * NOTE: This routine is just an optimization so it करोes not guarantee
 *       that no dcache entries will exist after a process is reaped
 *       it just makes it very unlikely that any will persist.
 */

व्योम proc_flush_pid(काष्ठा pid *pid)
अणु
	proc_invalidate_siblings_dcache(&pid->inodes, &pid->lock);
पूर्ण

अटल काष्ठा dentry *proc_pid_instantiate(काष्ठा dentry * dentry,
				   काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	काष्ठा inode *inode;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFसूची | S_IRUGO | S_IXUGO);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	inode->i_op = &proc_tgid_base_inode_operations;
	inode->i_fop = &proc_tgid_base_operations;
	inode->i_flags|=S_IMMUTABLE;

	set_nlink(inode, nlink_tgid);
	pid_update_inode(task, inode);

	d_set_d_op(dentry, &pid_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

काष्ठा dentry *proc_pid_lookup(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *task;
	अचिन्हित tgid;
	काष्ठा proc_fs_info *fs_info;
	काष्ठा pid_namespace *ns;
	काष्ठा dentry *result = ERR_PTR(-ENOENT);

	tgid = name_to_पूर्णांक(&dentry->d_name);
	अगर (tgid == ~0U)
		जाओ out;

	fs_info = proc_sb_info(dentry->d_sb);
	ns = fs_info->pid_ns;
	rcu_पढ़ो_lock();
	task = find_task_by_pid_ns(tgid, ns);
	अगर (task)
		get_task_काष्ठा(task);
	rcu_पढ़ो_unlock();
	अगर (!task)
		जाओ out;

	/* Limit procfs to only ptraceable tasks */
	अगर (fs_info->hide_pid == HIDEPID_NOT_PTRACEABLE) अणु
		अगर (!has_pid_permissions(fs_info, task, HIDEPID_NO_ACCESS))
			जाओ out_put_task;
	पूर्ण

	result = proc_pid_instantiate(dentry, task, शून्य);
out_put_task:
	put_task_काष्ठा(task);
out:
	वापस result;
पूर्ण

/*
 * Find the first task with tgid >= tgid
 *
 */
काष्ठा tgid_iter अणु
	अचिन्हित पूर्णांक tgid;
	काष्ठा task_काष्ठा *task;
पूर्ण;
अटल काष्ठा tgid_iter next_tgid(काष्ठा pid_namespace *ns, काष्ठा tgid_iter iter)
अणु
	काष्ठा pid *pid;

	अगर (iter.task)
		put_task_काष्ठा(iter.task);
	rcu_पढ़ो_lock();
retry:
	iter.task = शून्य;
	pid = find_ge_pid(iter.tgid, ns);
	अगर (pid) अणु
		iter.tgid = pid_nr_ns(pid, ns);
		iter.task = pid_task(pid, PIDTYPE_TGID);
		अगर (!iter.task) अणु
			iter.tgid += 1;
			जाओ retry;
		पूर्ण
		get_task_काष्ठा(iter.task);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस iter;
पूर्ण

#घोषणा TGID_OFFSET (FIRST_PROCESS_ENTRY + 2)

/* क्रम the /proc/ directory itself, after non-process stuff has been करोne */
पूर्णांक proc_pid_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा tgid_iter iter;
	काष्ठा proc_fs_info *fs_info = proc_sb_info(file_inode(file)->i_sb);
	काष्ठा pid_namespace *ns = proc_pid_ns(file_inode(file)->i_sb);
	loff_t pos = ctx->pos;

	अगर (pos >= PID_MAX_LIMIT + TGID_OFFSET)
		वापस 0;

	अगर (pos == TGID_OFFSET - 2) अणु
		काष्ठा inode *inode = d_inode(fs_info->proc_self);
		अगर (!dir_emit(ctx, "self", 4, inode->i_ino, DT_LNK))
			वापस 0;
		ctx->pos = pos = pos + 1;
	पूर्ण
	अगर (pos == TGID_OFFSET - 1) अणु
		काष्ठा inode *inode = d_inode(fs_info->proc_thपढ़ो_self);
		अगर (!dir_emit(ctx, "thread-self", 11, inode->i_ino, DT_LNK))
			वापस 0;
		ctx->pos = pos = pos + 1;
	पूर्ण
	iter.tgid = pos - TGID_OFFSET;
	iter.task = शून्य;
	क्रम (iter = next_tgid(ns, iter);
	     iter.task;
	     iter.tgid += 1, iter = next_tgid(ns, iter)) अणु
		अक्षर name[10 + 1];
		अचिन्हित पूर्णांक len;

		cond_resched();
		अगर (!has_pid_permissions(fs_info, iter.task, HIDEPID_INVISIBLE))
			जारी;

		len = snम_लिखो(name, माप(name), "%u", iter.tgid);
		ctx->pos = iter.tgid + TGID_OFFSET;
		अगर (!proc_fill_cache(file, ctx, name, len,
				     proc_pid_instantiate, iter.task, शून्य)) अणु
			put_task_काष्ठा(iter.task);
			वापस 0;
		पूर्ण
	पूर्ण
	ctx->pos = PID_MAX_LIMIT + TGID_OFFSET;
	वापस 0;
पूर्ण

/*
 * proc_tid_comm_permission is a special permission function exclusively
 * used क्रम the node /proc/<pid>/task/<tid>/comm.
 * It bypasses generic permission checks in the हाल where a task of the same
 * task group attempts to access the node.
 * The rationale behind this is that glibc and bionic access this node क्रम
 * cross thपढ़ो naming (pthपढ़ो_set/getname_np(!self)). However, अगर
 * PR_SET_DUMPABLE माला_लो set to 0 this node among others becomes uid=0 gid=0,
 * which locks out the cross thपढ़ो naming implementation.
 * This function makes sure that the node is always accessible क्रम members of
 * same thपढ़ो group.
 */
अटल पूर्णांक proc_tid_comm_permission(काष्ठा user_namespace *mnt_userns,
				    काष्ठा inode *inode, पूर्णांक mask)
अणु
	bool is_same_tgroup;
	काष्ठा task_काष्ठा *task;

	task = get_proc_task(inode);
	अगर (!task)
		वापस -ESRCH;
	is_same_tgroup = same_thपढ़ो_group(current, task);
	put_task_काष्ठा(task);

	अगर (likely(is_same_tgroup && !(mask & MAY_EXEC))) अणु
		/* This file (/proc/<pid>/task/<tid>/comm) can always be
		 * पढ़ो or written by the members of the corresponding
		 * thपढ़ो group.
		 */
		वापस 0;
	पूर्ण

	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_tid_comm_inode_operations = अणु
		.permission = proc_tid_comm_permission,
पूर्ण;

/*
 * Tasks
 */
अटल स्थिर काष्ठा pid_entry tid_base_stuff[] = अणु
	सूची("fd",        S_IRUSR|S_IXUSR, proc_fd_inode_operations, proc_fd_operations),
	सूची("fdinfo",    S_IRUSR|S_IXUSR, proc_fdinfo_inode_operations, proc_fdinfo_operations),
	सूची("ns",	 S_IRUSR|S_IXUGO, proc_ns_dir_inode_operations, proc_ns_dir_operations),
#अगर_घोषित CONFIG_NET
	सूची("net",        S_IRUGO|S_IXUGO, proc_net_inode_operations, proc_net_operations),
#पूर्ण_अगर
	REG("environ",   S_IRUSR, proc_environ_operations),
	REG("auxv",      S_IRUSR, proc_auxv_operations),
	ONE("status",    S_IRUGO, proc_pid_status),
	ONE("personality", S_IRUSR, proc_pid_personality),
	ONE("limits",	 S_IRUGO, proc_pid_limits),
#अगर_घोषित CONFIG_SCHED_DEBUG
	REG("sched",     S_IRUGO|S_IWUSR, proc_pid_sched_operations),
#पूर्ण_अगर
	NOD("comm",      S_IFREG|S_IRUGO|S_IWUSR,
			 &proc_tid_comm_inode_operations,
			 &proc_pid_set_comm_operations, अणुपूर्ण),
#अगर_घोषित CONFIG_HAVE_ARCH_TRACEHOOK
	ONE("syscall",   S_IRUSR, proc_pid_syscall),
#पूर्ण_अगर
	REG("cmdline",   S_IRUGO, proc_pid_cmdline_ops),
	ONE("stat",      S_IRUGO, proc_tid_stat),
	ONE("statm",     S_IRUGO, proc_pid_staपंचांग),
	REG("maps",      S_IRUGO, proc_pid_maps_operations),
#अगर_घोषित CONFIG_PROC_CHILDREN
	REG("children",  S_IRUGO, proc_tid_children_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	REG("numa_maps", S_IRUGO, proc_pid_numa_maps_operations),
#पूर्ण_अगर
	REG("mem",       S_IRUSR|S_IWUSR, proc_mem_operations),
	LNK("cwd",       proc_cwd_link),
	LNK("root",      proc_root_link),
	LNK("exe",       proc_exe_link),
	REG("mounts",    S_IRUGO, proc_mounts_operations),
	REG("mountinfo",  S_IRUGO, proc_mountinfo_operations),
#अगर_घोषित CONFIG_PROC_PAGE_MONITOR
	REG("clear_refs", S_IWUSR, proc_clear_refs_operations),
	REG("smaps",     S_IRUGO, proc_pid_smaps_operations),
	REG("smaps_rollup", S_IRUGO, proc_pid_smaps_rollup_operations),
	REG("pagemap",    S_IRUSR, proc_pagemap_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY
	सूची("attr",      S_IRUGO|S_IXUGO, proc_attr_dir_inode_operations, proc_attr_dir_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_KALLSYMS
	ONE("wchan",     S_IRUGO, proc_pid_wchan),
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKTRACE
	ONE("stack",      S_IRUSR, proc_pid_stack),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_INFO
	ONE("schedstat", S_IRUGO, proc_pid_schedstat),
#पूर्ण_अगर
#अगर_घोषित CONFIG_LATENCYTOP
	REG("latency",  S_IRUGO, proc_lstats_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_PID_CPUSET
	ONE("cpuset",    S_IRUGO, proc_cpuset_show),
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	ONE("cgroup",  S_IRUGO, proc_cgroup_show),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_CPU_RESCTRL
	ONE("cpu_resctrl_groups", S_IRUGO, proc_resctrl_show),
#पूर्ण_अगर
	ONE("oom_score", S_IRUGO, proc_oom_score),
	REG("oom_adj",   S_IRUGO|S_IWUSR, proc_oom_adj_operations),
	REG("oom_score_adj", S_IRUGO|S_IWUSR, proc_oom_score_adj_operations),
#अगर_घोषित CONFIG_AUDIT
	REG("loginuid",  S_IWUSR|S_IRUGO, proc_loginuid_operations),
	REG("sessionid",  S_IRUGO, proc_sessionid_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_FAULT_INJECTION
	REG("make-it-fail", S_IRUGO|S_IWUSR, proc_fault_inject_operations),
	REG("fail-nth", 0644, proc_fail_nth_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_TASK_IO_ACCOUNTING
	ONE("io",	S_IRUSR, proc_tid_io_accounting),
#पूर्ण_अगर
#अगर_घोषित CONFIG_USER_NS
	REG("uid_map",    S_IRUGO|S_IWUSR, proc_uid_map_operations),
	REG("gid_map",    S_IRUGO|S_IWUSR, proc_gid_map_operations),
	REG("projid_map", S_IRUGO|S_IWUSR, proc_projid_map_operations),
	REG("setgroups",  S_IRUGO|S_IWUSR, proc_setgroups_operations),
#पूर्ण_अगर
#अगर_घोषित CONFIG_LIVEPATCH
	ONE("patch_state",  S_IRUSR, proc_pid_patch_state),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_PID_ARCH_STATUS
	ONE("arch_status", S_IRUGO, proc_pid_arch_status),
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECCOMP_CACHE_DEBUG
	ONE("seccomp_cache", S_IRUSR, proc_pid_seccomp_cache),
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक proc_tid_base_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस proc_pident_सूची_पढ़ो(file, ctx,
				   tid_base_stuff, ARRAY_SIZE(tid_base_stuff));
पूर्ण

अटल काष्ठा dentry *proc_tid_base_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस proc_pident_lookup(dir, dentry,
				  tid_base_stuff,
				  tid_base_stuff + ARRAY_SIZE(tid_base_stuff));
पूर्ण

अटल स्थिर काष्ठा file_operations proc_tid_base_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_tid_base_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा inode_operations proc_tid_base_inode_operations = अणु
	.lookup		= proc_tid_base_lookup,
	.getattr	= pid_getattr,
	.setattr	= proc_setattr,
पूर्ण;

अटल काष्ठा dentry *proc_task_instantiate(काष्ठा dentry *dentry,
	काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	काष्ठा inode *inode;
	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFसूची | S_IRUGO | S_IXUGO);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	inode->i_op = &proc_tid_base_inode_operations;
	inode->i_fop = &proc_tid_base_operations;
	inode->i_flags |= S_IMMUTABLE;

	set_nlink(inode, nlink_tid);
	pid_update_inode(task, inode);

	d_set_d_op(dentry, &pid_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा dentry *proc_task_lookup(काष्ठा inode *dir, काष्ठा dentry * dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा task_काष्ठा *leader = get_proc_task(dir);
	अचिन्हित tid;
	काष्ठा proc_fs_info *fs_info;
	काष्ठा pid_namespace *ns;
	काष्ठा dentry *result = ERR_PTR(-ENOENT);

	अगर (!leader)
		जाओ out_no_task;

	tid = name_to_पूर्णांक(&dentry->d_name);
	अगर (tid == ~0U)
		जाओ out;

	fs_info = proc_sb_info(dentry->d_sb);
	ns = fs_info->pid_ns;
	rcu_पढ़ो_lock();
	task = find_task_by_pid_ns(tid, ns);
	अगर (task)
		get_task_काष्ठा(task);
	rcu_पढ़ो_unlock();
	अगर (!task)
		जाओ out;
	अगर (!same_thपढ़ो_group(leader, task))
		जाओ out_drop_task;

	result = proc_task_instantiate(dentry, task, शून्य);
out_drop_task:
	put_task_काष्ठा(task);
out:
	put_task_काष्ठा(leader);
out_no_task:
	वापस result;
पूर्ण

/*
 * Find the first tid of a thपढ़ो group to वापस to user space.
 *
 * Usually this is just the thपढ़ो group leader, but अगर the users
 * buffer was too small or there was a seek पूर्णांकo the middle of the
 * directory we have more work toकरो.
 *
 * In the हाल of a लघु पढ़ो we start with find_task_by_pid.
 *
 * In the हाल of a seek we start with the leader and walk nr
 * thपढ़ोs past it.
 */
अटल काष्ठा task_काष्ठा *first_tid(काष्ठा pid *pid, पूर्णांक tid, loff_t f_pos,
					काष्ठा pid_namespace *ns)
अणु
	काष्ठा task_काष्ठा *pos, *task;
	अचिन्हित दीर्घ nr = f_pos;

	अगर (nr != f_pos)	/* 32bit overflow? */
		वापस शून्य;

	rcu_पढ़ो_lock();
	task = pid_task(pid, PIDTYPE_PID);
	अगर (!task)
		जाओ fail;

	/* Attempt to start with the tid of a thपढ़ो */
	अगर (tid && nr) अणु
		pos = find_task_by_pid_ns(tid, ns);
		अगर (pos && same_thपढ़ो_group(pos, task))
			जाओ found;
	पूर्ण

	/* If nr exceeds the number of thपढ़ोs there is nothing toकरो */
	अगर (nr >= get_nr_thपढ़ोs(task))
		जाओ fail;

	/* If we haven't found our starting place yet start
	 * with the leader and walk nr thपढ़ोs क्रमward.
	 */
	pos = task = task->group_leader;
	करो अणु
		अगर (!nr--)
			जाओ found;
	पूर्ण जबतक_each_thपढ़ो(task, pos);
fail:
	pos = शून्य;
	जाओ out;
found:
	get_task_काष्ठा(pos);
out:
	rcu_पढ़ो_unlock();
	वापस pos;
पूर्ण

/*
 * Find the next thपढ़ो in the thपढ़ो list.
 * Return शून्य अगर there is an error or no next thपढ़ो.
 *
 * The reference to the input task_काष्ठा is released.
 */
अटल काष्ठा task_काष्ठा *next_tid(काष्ठा task_काष्ठा *start)
अणु
	काष्ठा task_काष्ठा *pos = शून्य;
	rcu_पढ़ो_lock();
	अगर (pid_alive(start)) अणु
		pos = next_thपढ़ो(start);
		अगर (thपढ़ो_group_leader(pos))
			pos = शून्य;
		अन्यथा
			get_task_काष्ठा(pos);
	पूर्ण
	rcu_पढ़ो_unlock();
	put_task_काष्ठा(start);
	वापस pos;
पूर्ण

/* क्रम the /proc/TGID/task/ directories */
अटल पूर्णांक proc_task_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा task_काष्ठा *task;
	काष्ठा pid_namespace *ns;
	पूर्णांक tid;

	अगर (proc_inode_is_dead(inode))
		वापस -ENOENT;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;

	/* f_version caches the tgid value that the last सूची_पढ़ो call couldn't
	 * वापस. lseek aka telldir स्वतःmagically resets f_version to 0.
	 */
	ns = proc_pid_ns(inode->i_sb);
	tid = (पूर्णांक)file->f_version;
	file->f_version = 0;
	क्रम (task = first_tid(proc_pid(inode), tid, ctx->pos - 2, ns);
	     task;
	     task = next_tid(task), ctx->pos++) अणु
		अक्षर name[10 + 1];
		अचिन्हित पूर्णांक len;
		tid = task_pid_nr_ns(task, ns);
		len = snम_लिखो(name, माप(name), "%u", tid);
		अगर (!proc_fill_cache(file, ctx, name, len,
				proc_task_instantiate, task, शून्य)) अणु
			/* वापसing this tgid failed, save it as the first
			 * pid क्रम the next पढ़ोir call */
			file->f_version = (u64)tid;
			put_task_काष्ठा(task);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक proc_task_getattr(काष्ठा user_namespace *mnt_userns,
			     स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			     u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा task_काष्ठा *p = get_proc_task(inode);
	generic_fillattr(&init_user_ns, inode, stat);

	अगर (p) अणु
		stat->nlink += get_nr_thपढ़ोs(p);
		put_task_काष्ठा(p);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_task_inode_operations = अणु
	.lookup		= proc_task_lookup,
	.getattr	= proc_task_getattr,
	.setattr	= proc_setattr,
	.permission	= proc_pid_permission,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_task_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_task_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

व्योम __init set_proc_pid_nlink(व्योम)
अणु
	nlink_tid = pid_entry_nlink(tid_base_stuff, ARRAY_SIZE(tid_base_stuff));
	nlink_tgid = pid_entry_nlink(tgid_base_stuff, ARRAY_SIZE(tgid_base_stuff));
पूर्ण
