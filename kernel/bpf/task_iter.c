<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2020 Facebook */

#समावेश <linux/init.h>
#समावेश <linux/namei.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/fs.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/filter.h>
#समावेश <linux/btf_ids.h>

काष्ठा bpf_iter_seq_task_common अणु
	काष्ठा pid_namespace *ns;
पूर्ण;

काष्ठा bpf_iter_seq_task_info अणु
	/* The first field must be काष्ठा bpf_iter_seq_task_common.
	 * this is assumed by अणुinit, finiपूर्ण_seq_pidns() callback functions.
	 */
	काष्ठा bpf_iter_seq_task_common common;
	u32 tid;
पूर्ण;

अटल काष्ठा task_काष्ठा *task_seq_get_next(काष्ठा pid_namespace *ns,
					     u32 *tid,
					     bool skip_अगर_dup_files)
अणु
	काष्ठा task_काष्ठा *task = शून्य;
	काष्ठा pid *pid;

	rcu_पढ़ो_lock();
retry:
	pid = find_ge_pid(*tid, ns);
	अगर (pid) अणु
		*tid = pid_nr_ns(pid, ns);
		task = get_pid_task(pid, PIDTYPE_PID);
		अगर (!task) अणु
			++*tid;
			जाओ retry;
		पूर्ण अन्यथा अगर (skip_अगर_dup_files && !thपढ़ो_group_leader(task) &&
			   task->files == task->group_leader->files) अणु
			put_task_काष्ठा(task);
			task = शून्य;
			++*tid;
			जाओ retry;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस task;
पूर्ण

अटल व्योम *task_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_info *info = seq->निजी;
	काष्ठा task_काष्ठा *task;

	task = task_seq_get_next(info->common.ns, &info->tid, false);
	अगर (!task)
		वापस शून्य;

	अगर (*pos == 0)
		++*pos;
	वापस task;
पूर्ण

अटल व्योम *task_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_info *info = seq->निजी;
	काष्ठा task_काष्ठा *task;

	++*pos;
	++info->tid;
	put_task_काष्ठा((काष्ठा task_काष्ठा *)v);
	task = task_seq_get_next(info->common.ns, &info->tid, false);
	अगर (!task)
		वापस शून्य;

	वापस task;
पूर्ण

काष्ठा bpf_iter__task अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा task_काष्ठा *, task);
पूर्ण;

DEFINE_BPF_ITER_FUNC(task, काष्ठा bpf_iter_meta *meta, काष्ठा task_काष्ठा *task)

अटल पूर्णांक __task_seq_show(काष्ठा seq_file *seq, काष्ठा task_काष्ठा *task,
			   bool in_stop)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_iter__task ctx;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, in_stop);
	अगर (!prog)
		वापस 0;

	meta.seq = seq;
	ctx.meta = &meta;
	ctx.task = task;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक task_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __task_seq_show(seq, v, false);
पूर्ण

अटल व्योम task_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (!v)
		(व्योम)__task_seq_show(seq, v, true);
	अन्यथा
		put_task_काष्ठा((काष्ठा task_काष्ठा *)v);
पूर्ण

अटल स्थिर काष्ठा seq_operations task_seq_ops = अणु
	.start	= task_seq_start,
	.next	= task_seq_next,
	.stop	= task_seq_stop,
	.show	= task_seq_show,
पूर्ण;

काष्ठा bpf_iter_seq_task_file_info अणु
	/* The first field must be काष्ठा bpf_iter_seq_task_common.
	 * this is assumed by अणुinit, finiपूर्ण_seq_pidns() callback functions.
	 */
	काष्ठा bpf_iter_seq_task_common common;
	काष्ठा task_काष्ठा *task;
	u32 tid;
	u32 fd;
पूर्ण;

अटल काष्ठा file *
task_file_seq_get_next(काष्ठा bpf_iter_seq_task_file_info *info)
अणु
	काष्ठा pid_namespace *ns = info->common.ns;
	u32 curr_tid = info->tid;
	काष्ठा task_काष्ठा *curr_task;
	अचिन्हित पूर्णांक curr_fd = info->fd;

	/* If this function वापसs a non-शून्य file object,
	 * it held a reference to the task/file.
	 * Otherwise, it करोes not hold any reference.
	 */
again:
	अगर (info->task) अणु
		curr_task = info->task;
		curr_fd = info->fd;
	पूर्ण अन्यथा अणु
                curr_task = task_seq_get_next(ns, &curr_tid, true);
                अगर (!curr_task) अणु
                        info->task = शून्य;
                        info->tid = curr_tid;
                        वापस शून्य;
                पूर्ण

                /* set info->task and info->tid */
		info->task = curr_task;
		अगर (curr_tid == info->tid) अणु
			curr_fd = info->fd;
		पूर्ण अन्यथा अणु
			info->tid = curr_tid;
			curr_fd = 0;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम (;; curr_fd++) अणु
		काष्ठा file *f;
		f = task_lookup_next_fd_rcu(curr_task, &curr_fd);
		अगर (!f)
			अवरोध;
		अगर (!get_file_rcu(f))
			जारी;

		/* set info->fd */
		info->fd = curr_fd;
		rcu_पढ़ो_unlock();
		वापस f;
	पूर्ण

	/* the current task is करोne, go to the next task */
	rcu_पढ़ो_unlock();
	put_task_काष्ठा(curr_task);
	info->task = शून्य;
	info->fd = 0;
	curr_tid = ++(info->tid);
	जाओ again;
पूर्ण

अटल व्योम *task_file_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_file_info *info = seq->निजी;
	काष्ठा file *file;

	info->task = शून्य;
	file = task_file_seq_get_next(info);
	अगर (file && *pos == 0)
		++*pos;

	वापस file;
पूर्ण

अटल व्योम *task_file_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_file_info *info = seq->निजी;

	++*pos;
	++info->fd;
	fput((काष्ठा file *)v);
	वापस task_file_seq_get_next(info);
पूर्ण

काष्ठा bpf_iter__task_file अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा task_काष्ठा *, task);
	u32 fd __aligned(8);
	__bpf_md_ptr(काष्ठा file *, file);
पूर्ण;

DEFINE_BPF_ITER_FUNC(task_file, काष्ठा bpf_iter_meta *meta,
		     काष्ठा task_काष्ठा *task, u32 fd,
		     काष्ठा file *file)

अटल पूर्णांक __task_file_seq_show(काष्ठा seq_file *seq, काष्ठा file *file,
				bool in_stop)
अणु
	काष्ठा bpf_iter_seq_task_file_info *info = seq->निजी;
	काष्ठा bpf_iter__task_file ctx;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, in_stop);
	अगर (!prog)
		वापस 0;

	ctx.meta = &meta;
	ctx.task = info->task;
	ctx.fd = info->fd;
	ctx.file = file;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक task_file_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __task_file_seq_show(seq, v, false);
पूर्ण

अटल व्योम task_file_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_seq_task_file_info *info = seq->निजी;

	अगर (!v) अणु
		(व्योम)__task_file_seq_show(seq, v, true);
	पूर्ण अन्यथा अणु
		fput((काष्ठा file *)v);
		put_task_काष्ठा(info->task);
		info->task = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक init_seq_pidns(व्योम *priv_data, काष्ठा bpf_iter_aux_info *aux)
अणु
	काष्ठा bpf_iter_seq_task_common *common = priv_data;

	common->ns = get_pid_ns(task_active_pid_ns(current));
	वापस 0;
पूर्ण

अटल व्योम fini_seq_pidns(व्योम *priv_data)
अणु
	काष्ठा bpf_iter_seq_task_common *common = priv_data;

	put_pid_ns(common->ns);
पूर्ण

अटल स्थिर काष्ठा seq_operations task_file_seq_ops = अणु
	.start	= task_file_seq_start,
	.next	= task_file_seq_next,
	.stop	= task_file_seq_stop,
	.show	= task_file_seq_show,
पूर्ण;

काष्ठा bpf_iter_seq_task_vma_info अणु
	/* The first field must be काष्ठा bpf_iter_seq_task_common.
	 * this is assumed by अणुinit, finiपूर्ण_seq_pidns() callback functions.
	 */
	काष्ठा bpf_iter_seq_task_common common;
	काष्ठा task_काष्ठा *task;
	काष्ठा vm_area_काष्ठा *vma;
	u32 tid;
	अचिन्हित दीर्घ prev_vm_start;
	अचिन्हित दीर्घ prev_vm_end;
पूर्ण;

क्रमागत bpf_task_vma_iter_find_op अणु
	task_vma_iter_first_vma,   /* use mm->mmap */
	task_vma_iter_next_vma,    /* use curr_vma->vm_next */
	task_vma_iter_find_vma,    /* use find_vma() to find next vma */
पूर्ण;

अटल काष्ठा vm_area_काष्ठा *
task_vma_seq_get_next(काष्ठा bpf_iter_seq_task_vma_info *info)
अणु
	काष्ठा pid_namespace *ns = info->common.ns;
	क्रमागत bpf_task_vma_iter_find_op op;
	काष्ठा vm_area_काष्ठा *curr_vma;
	काष्ठा task_काष्ठा *curr_task;
	u32 curr_tid = info->tid;

	/* If this function वापसs a non-शून्य vma, it holds a reference to
	 * the task_काष्ठा, and holds पढ़ो lock on vma->mm->mmap_lock.
	 * If this function वापसs शून्य, it करोes not hold any reference or
	 * lock.
	 */
	अगर (info->task) अणु
		curr_task = info->task;
		curr_vma = info->vma;
		/* In हाल of lock contention, drop mmap_lock to unblock
		 * the ग_लिखोr.
		 *
		 * After relock, call find(mm, prev_vm_end - 1) to find
		 * new vma to process.
		 *
		 *   +------+------+-----------+
		 *   | VMA1 | VMA2 | VMA3      |
		 *   +------+------+-----------+
		 *   |      |      |           |
		 *  4k     8k     16k         400k
		 *
		 * For example, curr_vma == VMA2. Beक्रमe unlock, we set
		 *
		 *    prev_vm_start = 8k
		 *    prev_vm_end   = 16k
		 *
		 * There are a few हालs:
		 *
		 * 1) VMA2 is मुक्तd, but VMA3 exists.
		 *
		 *    find_vma() will वापस VMA3, just process VMA3.
		 *
		 * 2) VMA2 still exists.
		 *
		 *    find_vma() will वापस VMA2, process VMA2->next.
		 *
		 * 3) no more vma in this mm.
		 *
		 *    Process the next task.
		 *
		 * 4) find_vma() वापसs a dअगरferent vma, VMA2'.
		 *
		 *    4.1) If VMA2 covers same range as VMA2', skip VMA2',
		 *         because we alपढ़ोy covered the range;
		 *    4.2) VMA2 and VMA2' covers dअगरferent ranges, process
		 *         VMA2'.
		 */
		अगर (mmap_lock_is_contended(curr_task->mm)) अणु
			info->prev_vm_start = curr_vma->vm_start;
			info->prev_vm_end = curr_vma->vm_end;
			op = task_vma_iter_find_vma;
			mmap_पढ़ो_unlock(curr_task->mm);
			अगर (mmap_पढ़ो_lock_समाप्तable(curr_task->mm))
				जाओ finish;
		पूर्ण अन्यथा अणु
			op = task_vma_iter_next_vma;
		पूर्ण
	पूर्ण अन्यथा अणु
again:
		curr_task = task_seq_get_next(ns, &curr_tid, true);
		अगर (!curr_task) अणु
			info->tid = curr_tid + 1;
			जाओ finish;
		पूर्ण

		अगर (curr_tid != info->tid) अणु
			info->tid = curr_tid;
			/* new task, process the first vma */
			op = task_vma_iter_first_vma;
		पूर्ण अन्यथा अणु
			/* Found the same tid, which means the user space
			 * finished data in previous buffer and पढ़ो more.
			 * We dropped mmap_lock beक्रमe वापसing to user
			 * space, so it is necessary to use find_vma() to
			 * find the next vma to process.
			 */
			op = task_vma_iter_find_vma;
		पूर्ण

		अगर (!curr_task->mm)
			जाओ next_task;

		अगर (mmap_पढ़ो_lock_समाप्तable(curr_task->mm))
			जाओ finish;
	पूर्ण

	चयन (op) अणु
	हाल task_vma_iter_first_vma:
		curr_vma = curr_task->mm->mmap;
		अवरोध;
	हाल task_vma_iter_next_vma:
		curr_vma = curr_vma->vm_next;
		अवरोध;
	हाल task_vma_iter_find_vma:
		/* We dropped mmap_lock so it is necessary to use find_vma
		 * to find the next vma. This is similar to the  mechanism
		 * in show_smaps_rollup().
		 */
		curr_vma = find_vma(curr_task->mm, info->prev_vm_end - 1);
		/* हाल 1) and 4.2) above just use curr_vma */

		/* check क्रम हाल 2) or हाल 4.1) above */
		अगर (curr_vma &&
		    curr_vma->vm_start == info->prev_vm_start &&
		    curr_vma->vm_end == info->prev_vm_end)
			curr_vma = curr_vma->vm_next;
		अवरोध;
	पूर्ण
	अगर (!curr_vma) अणु
		/* हाल 3) above, or हाल 2) 4.1) with vma->next == शून्य */
		mmap_पढ़ो_unlock(curr_task->mm);
		जाओ next_task;
	पूर्ण
	info->task = curr_task;
	info->vma = curr_vma;
	वापस curr_vma;

next_task:
	put_task_काष्ठा(curr_task);
	info->task = शून्य;
	curr_tid++;
	जाओ again;

finish:
	अगर (curr_task)
		put_task_काष्ठा(curr_task);
	info->task = शून्य;
	info->vma = शून्य;
	वापस शून्य;
पूर्ण

अटल व्योम *task_vma_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_vma_info *info = seq->निजी;
	काष्ठा vm_area_काष्ठा *vma;

	vma = task_vma_seq_get_next(info);
	अगर (vma && *pos == 0)
		++*pos;

	वापस vma;
पूर्ण

अटल व्योम *task_vma_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा bpf_iter_seq_task_vma_info *info = seq->निजी;

	++*pos;
	वापस task_vma_seq_get_next(info);
पूर्ण

काष्ठा bpf_iter__task_vma अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा task_काष्ठा *, task);
	__bpf_md_ptr(काष्ठा vm_area_काष्ठा *, vma);
पूर्ण;

DEFINE_BPF_ITER_FUNC(task_vma, काष्ठा bpf_iter_meta *meta,
		     काष्ठा task_काष्ठा *task, काष्ठा vm_area_काष्ठा *vma)

अटल पूर्णांक __task_vma_seq_show(काष्ठा seq_file *seq, bool in_stop)
अणु
	काष्ठा bpf_iter_seq_task_vma_info *info = seq->निजी;
	काष्ठा bpf_iter__task_vma ctx;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, in_stop);
	अगर (!prog)
		वापस 0;

	ctx.meta = &meta;
	ctx.task = info->task;
	ctx.vma = info->vma;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक task_vma_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस __task_vma_seq_show(seq, false);
पूर्ण

अटल व्योम task_vma_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_seq_task_vma_info *info = seq->निजी;

	अगर (!v) अणु
		(व्योम)__task_vma_seq_show(seq, true);
	पूर्ण अन्यथा अणु
		/* info->vma has not been seen by the BPF program. If the
		 * user space पढ़ोs more, task_vma_seq_get_next should
		 * वापस this vma again. Set prev_vm_start to ~0UL,
		 * so that we करोn't skip the vma वापसed by the next
		 * find_vma() (हाल task_vma_iter_find_vma in
		 * task_vma_seq_get_next()).
		 */
		info->prev_vm_start = ~0UL;
		info->prev_vm_end = info->vma->vm_end;
		mmap_पढ़ो_unlock(info->task->mm);
		put_task_काष्ठा(info->task);
		info->task = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा seq_operations task_vma_seq_ops = अणु
	.start	= task_vma_seq_start,
	.next	= task_vma_seq_next,
	.stop	= task_vma_seq_stop,
	.show	= task_vma_seq_show,
पूर्ण;

BTF_ID_LIST(btf_task_file_ids)
BTF_ID(काष्ठा, task_काष्ठा)
BTF_ID(काष्ठा, file)
BTF_ID(काष्ठा, vm_area_काष्ठा)

अटल स्थिर काष्ठा bpf_iter_seq_info task_seq_info = अणु
	.seq_ops		= &task_seq_ops,
	.init_seq_निजी	= init_seq_pidns,
	.fini_seq_निजी	= fini_seq_pidns,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_task_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg task_reg_info = अणु
	.target			= "task",
	.feature		= BPF_ITER_RESCHED,
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__task, task),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &task_seq_info,
पूर्ण;

अटल स्थिर काष्ठा bpf_iter_seq_info task_file_seq_info = अणु
	.seq_ops		= &task_file_seq_ops,
	.init_seq_निजी	= init_seq_pidns,
	.fini_seq_निजी	= fini_seq_pidns,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_task_file_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg task_file_reg_info = अणु
	.target			= "task_file",
	.feature		= BPF_ITER_RESCHED,
	.ctx_arg_info_size	= 2,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__task_file, task),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
		अणु दुरत्व(काष्ठा bpf_iter__task_file, file),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &task_file_seq_info,
पूर्ण;

अटल स्थिर काष्ठा bpf_iter_seq_info task_vma_seq_info = अणु
	.seq_ops		= &task_vma_seq_ops,
	.init_seq_निजी	= init_seq_pidns,
	.fini_seq_निजी	= fini_seq_pidns,
	.seq_priv_size		= माप(काष्ठा bpf_iter_seq_task_vma_info),
पूर्ण;

अटल काष्ठा bpf_iter_reg task_vma_reg_info = अणु
	.target			= "task_vma",
	.feature		= BPF_ITER_RESCHED,
	.ctx_arg_info_size	= 2,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__task_vma, task),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
		अणु दुरत्व(काष्ठा bpf_iter__task_vma, vma),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &task_vma_seq_info,
पूर्ण;

अटल पूर्णांक __init task_iter_init(व्योम)
अणु
	पूर्णांक ret;

	task_reg_info.ctx_arg_info[0].btf_id = btf_task_file_ids[0];
	ret = bpf_iter_reg_target(&task_reg_info);
	अगर (ret)
		वापस ret;

	task_file_reg_info.ctx_arg_info[0].btf_id = btf_task_file_ids[0];
	task_file_reg_info.ctx_arg_info[1].btf_id = btf_task_file_ids[1];
	ret =  bpf_iter_reg_target(&task_file_reg_info);
	अगर (ret)
		वापस ret;

	task_vma_reg_info.ctx_arg_info[0].btf_id = btf_task_file_ids[0];
	task_vma_reg_info.ctx_arg_info[1].btf_id = btf_task_file_ids[2];
	वापस bpf_iter_reg_target(&task_vma_reg_info);
पूर्ण
late_initcall(task_iter_init);
