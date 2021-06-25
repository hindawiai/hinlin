<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2006 Jens Axboe <axboe@kernel.dk>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/list.h>
#समावेश <linux/blk-cgroup.h>

#समावेश "../../block/blk.h"

#समावेश <trace/events/block.h>

#समावेश "trace_output.h"

#अगर_घोषित CONFIG_BLK_DEV_IO_TRACE

अटल अचिन्हित पूर्णांक blktrace_seq __पढ़ो_mostly = 1;

अटल काष्ठा trace_array *blk_tr;
अटल bool blk_tracer_enabled __पढ़ो_mostly;

अटल LIST_HEAD(running_trace_list);
अटल __cacheline_aligned_in_smp DEFINE_SPINLOCK(running_trace_lock);

/* Select an alternative, minimalistic output than the original one */
#घोषणा TRACE_BLK_OPT_CLASSIC	0x1
#घोषणा TRACE_BLK_OPT_CGROUP	0x2
#घोषणा TRACE_BLK_OPT_CGNAME	0x4

अटल काष्ठा tracer_opt blk_tracer_opts[] = अणु
	/* Default disable the minimalistic output */
	अणु TRACER_OPT(blk_classic, TRACE_BLK_OPT_CLASSIC) पूर्ण,
#अगर_घोषित CONFIG_BLK_CGROUP
	अणु TRACER_OPT(blk_cgroup, TRACE_BLK_OPT_CGROUP) पूर्ण,
	अणु TRACER_OPT(blk_cgname, TRACE_BLK_OPT_CGNAME) पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा tracer_flags blk_tracer_flags = अणु
	.val  = 0,
	.opts = blk_tracer_opts,
पूर्ण;

/* Global reference count of probes */
अटल DEFINE_MUTEX(blk_probe_mutex);
अटल पूर्णांक blk_probes_ref;

अटल व्योम blk_रेजिस्टर_tracepoपूर्णांकs(व्योम);
अटल व्योम blk_unरेजिस्टर_tracepoपूर्णांकs(व्योम);

/*
 * Send out a notअगरy message.
 */
अटल व्योम trace_note(काष्ठा blk_trace *bt, pid_t pid, पूर्णांक action,
		       स्थिर व्योम *data, माप_प्रकार len, u64 cgid)
अणु
	काष्ठा blk_io_trace *t;
	काष्ठा ring_buffer_event *event = शून्य;
	काष्ठा trace_buffer *buffer = शून्य;
	अचिन्हित पूर्णांक trace_ctx = 0;
	पूर्णांक cpu = smp_processor_id();
	bool blk_tracer = blk_tracer_enabled;
	sमाप_प्रकार cgid_len = cgid ? माप(cgid) : 0;

	अगर (blk_tracer) अणु
		buffer = blk_tr->array_buffer.buffer;
		trace_ctx = tracing_gen_ctx_flags(0);
		event = trace_buffer_lock_reserve(buffer, TRACE_BLK,
						  माप(*t) + len + cgid_len,
						  trace_ctx);
		अगर (!event)
			वापस;
		t = ring_buffer_event_data(event);
		जाओ record_it;
	पूर्ण

	अगर (!bt->rchan)
		वापस;

	t = relay_reserve(bt->rchan, माप(*t) + len + cgid_len);
	अगर (t) अणु
		t->magic = BLK_IO_TRACE_MAGIC | BLK_IO_TRACE_VERSION;
		t->समय = kसमय_प्रकारo_ns(kसमय_get());
record_it:
		t->device = bt->dev;
		t->action = action | (cgid ? __BLK_TN_CGROUP : 0);
		t->pid = pid;
		t->cpu = cpu;
		t->pdu_len = len + cgid_len;
		अगर (cgid_len)
			स_नकल((व्योम *)t + माप(*t), &cgid, cgid_len);
		स_नकल((व्योम *) t + माप(*t) + cgid_len, data, len);

		अगर (blk_tracer)
			trace_buffer_unlock_commit(blk_tr, buffer, event, trace_ctx);
	पूर्ण
पूर्ण

/*
 * Send out a notअगरy क्रम this process, अगर we haven't करोne so since a trace
 * started
 */
अटल व्योम trace_note_tsk(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा blk_trace *bt;

	tsk->btrace_seq = blktrace_seq;
	spin_lock_irqsave(&running_trace_lock, flags);
	list_क्रम_each_entry(bt, &running_trace_list, running_list) अणु
		trace_note(bt, tsk->pid, BLK_TN_PROCESS, tsk->comm,
			   माप(tsk->comm), 0);
	पूर्ण
	spin_unlock_irqrestore(&running_trace_lock, flags);
पूर्ण

अटल व्योम trace_note_समय(काष्ठा blk_trace *bt)
अणु
	काष्ठा बारpec64 now;
	अचिन्हित दीर्घ flags;
	u32 words[2];

	/* need to check user space to see अगर this अवरोधs in y2038 or y2106 */
	kसमय_get_real_ts64(&now);
	words[0] = (u32)now.tv_sec;
	words[1] = now.tv_nsec;

	local_irq_save(flags);
	trace_note(bt, 0, BLK_TN_TIMESTAMP, words, माप(words), 0);
	local_irq_restore(flags);
पूर्ण

व्योम __trace_note_message(काष्ठा blk_trace *bt, काष्ठा blkcg *blkcg,
	स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक n;
	बहु_सूची args;
	अचिन्हित दीर्घ flags;
	अक्षर *buf;

	अगर (unlikely(bt->trace_state != Blktrace_running &&
		     !blk_tracer_enabled))
		वापस;

	/*
	 * If the BLK_TC_NOTIFY action mask isn't set, don't send any note
	 * message to the trace.
	 */
	अगर (!(bt->act_mask & BLK_TC_NOTIFY))
		वापस;

	local_irq_save(flags);
	buf = this_cpu_ptr(bt->msg_data);
	बहु_शुरू(args, fmt);
	n = vscnम_लिखो(buf, BLK_TN_MAX_MSG, fmt, args);
	बहु_पूर्ण(args);

	अगर (!(blk_tracer_flags.val & TRACE_BLK_OPT_CGROUP))
		blkcg = शून्य;
#अगर_घोषित CONFIG_BLK_CGROUP
	trace_note(bt, current->pid, BLK_TN_MESSAGE, buf, n,
		   blkcg ? cgroup_id(blkcg->css.cgroup) : 1);
#अन्यथा
	trace_note(bt, current->pid, BLK_TN_MESSAGE, buf, n, 0);
#पूर्ण_अगर
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(__trace_note_message);

अटल पूर्णांक act_log_check(काष्ठा blk_trace *bt, u32 what, sector_t sector,
			 pid_t pid)
अणु
	अगर (((bt->act_mask << BLK_TC_SHIFT) & what) == 0)
		वापस 1;
	अगर (sector && (sector < bt->start_lba || sector > bt->end_lba))
		वापस 1;
	अगर (bt->pid && pid != bt->pid)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Data direction bit lookup
 */
अटल स्थिर u32 ddir_act[2] = अणु BLK_TC_ACT(BLK_TC_READ),
				 BLK_TC_ACT(BLK_TC_WRITE) पूर्ण;

#घोषणा BLK_TC_RAHEAD		BLK_TC_AHEAD
#घोषणा BLK_TC_PREFLUSH		BLK_TC_FLUSH

/* The ilog2() calls fall out because they're स्थिरant */
#घोषणा MASK_TC_BIT(rw, __name) ((rw & REQ_ ## __name) << \
	  (ilog2(BLK_TC_ ## __name) + BLK_TC_SHIFT - __REQ_ ## __name))

/*
 * The worker क्रम the various blk_add_trace*() types. Fills out a
 * blk_io_trace काष्ठाure and places it in a per-cpu subbuffer.
 */
अटल व्योम __blk_add_trace(काष्ठा blk_trace *bt, sector_t sector, पूर्णांक bytes,
		     पूर्णांक op, पूर्णांक op_flags, u32 what, पूर्णांक error, पूर्णांक pdu_len,
		     व्योम *pdu_data, u64 cgid)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा ring_buffer_event *event = शून्य;
	काष्ठा trace_buffer *buffer = शून्य;
	काष्ठा blk_io_trace *t;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ *sequence;
	अचिन्हित पूर्णांक trace_ctx = 0;
	pid_t pid;
	पूर्णांक cpu;
	bool blk_tracer = blk_tracer_enabled;
	sमाप_प्रकार cgid_len = cgid ? माप(cgid) : 0;

	अगर (unlikely(bt->trace_state != Blktrace_running && !blk_tracer))
		वापस;

	what |= ddir_act[op_is_ग_लिखो(op) ? WRITE : READ];
	what |= MASK_TC_BIT(op_flags, SYNC);
	what |= MASK_TC_BIT(op_flags, RAHEAD);
	what |= MASK_TC_BIT(op_flags, META);
	what |= MASK_TC_BIT(op_flags, PREFLUSH);
	what |= MASK_TC_BIT(op_flags, FUA);
	अगर (op == REQ_OP_DISCARD || op == REQ_OP_SECURE_ERASE)
		what |= BLK_TC_ACT(BLK_TC_DISCARD);
	अगर (op == REQ_OP_FLUSH)
		what |= BLK_TC_ACT(BLK_TC_FLUSH);
	अगर (cgid)
		what |= __BLK_TA_CGROUP;

	pid = tsk->pid;
	अगर (act_log_check(bt, what, sector, pid))
		वापस;
	cpu = raw_smp_processor_id();

	अगर (blk_tracer) अणु
		tracing_record_cmdline(current);

		buffer = blk_tr->array_buffer.buffer;
		trace_ctx = tracing_gen_ctx_flags(0);
		event = trace_buffer_lock_reserve(buffer, TRACE_BLK,
						  माप(*t) + pdu_len + cgid_len,
						  trace_ctx);
		अगर (!event)
			वापस;
		t = ring_buffer_event_data(event);
		जाओ record_it;
	पूर्ण

	अगर (unlikely(tsk->btrace_seq != blktrace_seq))
		trace_note_tsk(tsk);

	/*
	 * A word about the locking here - we disable पूर्णांकerrupts to reserve
	 * some space in the relay per-cpu buffer, to prevent an irq
	 * from coming in and stepping on our toes.
	 */
	local_irq_save(flags);
	t = relay_reserve(bt->rchan, माप(*t) + pdu_len + cgid_len);
	अगर (t) अणु
		sequence = per_cpu_ptr(bt->sequence, cpu);

		t->magic = BLK_IO_TRACE_MAGIC | BLK_IO_TRACE_VERSION;
		t->sequence = ++(*sequence);
		t->समय = kसमय_प्रकारo_ns(kसमय_get());
record_it:
		/*
		 * These two are not needed in ftrace as they are in the
		 * generic trace_entry, filled by tracing_generic_entry_update,
		 * but क्रम the trace_event->bin() synthesizer benefit we करो it
		 * here too.
		 */
		t->cpu = cpu;
		t->pid = pid;

		t->sector = sector;
		t->bytes = bytes;
		t->action = what;
		t->device = bt->dev;
		t->error = error;
		t->pdu_len = pdu_len + cgid_len;

		अगर (cgid_len)
			स_नकल((व्योम *)t + माप(*t), &cgid, cgid_len);
		अगर (pdu_len)
			स_नकल((व्योम *)t + माप(*t) + cgid_len, pdu_data, pdu_len);

		अगर (blk_tracer) अणु
			trace_buffer_unlock_commit(blk_tr, buffer, event, trace_ctx);
			वापस;
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम blk_trace_मुक्त(काष्ठा blk_trace *bt)
अणु
	relay_बंद(bt->rchan);
	debugfs_हटाओ(bt->dir);
	मुक्त_percpu(bt->sequence);
	मुक्त_percpu(bt->msg_data);
	kमुक्त(bt);
पूर्ण

अटल व्योम get_probe_ref(व्योम)
अणु
	mutex_lock(&blk_probe_mutex);
	अगर (++blk_probes_ref == 1)
		blk_रेजिस्टर_tracepoपूर्णांकs();
	mutex_unlock(&blk_probe_mutex);
पूर्ण

अटल व्योम put_probe_ref(व्योम)
अणु
	mutex_lock(&blk_probe_mutex);
	अगर (!--blk_probes_ref)
		blk_unरेजिस्टर_tracepoपूर्णांकs();
	mutex_unlock(&blk_probe_mutex);
पूर्ण

अटल व्योम blk_trace_cleanup(काष्ठा blk_trace *bt)
अणु
	synchronize_rcu();
	blk_trace_मुक्त(bt);
	put_probe_ref();
पूर्ण

अटल पूर्णांक __blk_trace_हटाओ(काष्ठा request_queue *q)
अणु
	काष्ठा blk_trace *bt;

	bt = rcu_replace_poपूर्णांकer(q->blk_trace, शून्य,
				 lockdep_is_held(&q->debugfs_mutex));
	अगर (!bt)
		वापस -EINVAL;

	अगर (bt->trace_state != Blktrace_running)
		blk_trace_cleanup(bt);

	वापस 0;
पूर्ण

पूर्णांक blk_trace_हटाओ(काष्ठा request_queue *q)
अणु
	पूर्णांक ret;

	mutex_lock(&q->debugfs_mutex);
	ret = __blk_trace_हटाओ(q);
	mutex_unlock(&q->debugfs_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blk_trace_हटाओ);

अटल sमाप_प्रकार blk_dropped_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_trace *bt = filp->निजी_data;
	अक्षर buf[16];

	snम_लिखो(buf, माप(buf), "%u\n", atomic_पढ़ो(&bt->dropped));

	वापस simple_पढ़ो_from_buffer(buffer, count, ppos, buf, म_माप(buf));
पूर्ण

अटल स्थिर काष्ठा file_operations blk_dropped_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		simple_खोलो,
	.पढ़ो =		blk_dropped_पढ़ो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार blk_msg_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
				माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *msg;
	काष्ठा blk_trace *bt;

	अगर (count >= BLK_TN_MAX_MSG)
		वापस -EINVAL;

	msg = memdup_user_nul(buffer, count);
	अगर (IS_ERR(msg))
		वापस PTR_ERR(msg);

	bt = filp->निजी_data;
	__trace_note_message(bt, शून्य, "%s", msg);
	kमुक्त(msg);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations blk_msg_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		simple_खोलो,
	.ग_लिखो =	blk_msg_ग_लिखो,
	.llseek =	noop_llseek,
पूर्ण;

/*
 * Keep track of how many बार we encountered a full subbuffer, to aid
 * the user space app in telling how many lost events there were.
 */
अटल पूर्णांक blk_subbuf_start_callback(काष्ठा rchan_buf *buf, व्योम *subbuf,
				     व्योम *prev_subbuf, माप_प्रकार prev_padding)
अणु
	काष्ठा blk_trace *bt;

	अगर (!relay_buf_full(buf))
		वापस 1;

	bt = buf->chan->निजी_data;
	atomic_inc(&bt->dropped);
	वापस 0;
पूर्ण

अटल पूर्णांक blk_हटाओ_buf_file_callback(काष्ठा dentry *dentry)
अणु
	debugfs_हटाओ(dentry);

	वापस 0;
पूर्ण

अटल काष्ठा dentry *blk_create_buf_file_callback(स्थिर अक्षर *filename,
						   काष्ठा dentry *parent,
						   umode_t mode,
						   काष्ठा rchan_buf *buf,
						   पूर्णांक *is_global)
अणु
	वापस debugfs_create_file(filename, mode, parent, buf,
					&relay_file_operations);
पूर्ण

अटल स्थिर काष्ठा rchan_callbacks blk_relay_callbacks = अणु
	.subbuf_start		= blk_subbuf_start_callback,
	.create_buf_file	= blk_create_buf_file_callback,
	.हटाओ_buf_file	= blk_हटाओ_buf_file_callback,
पूर्ण;

अटल व्योम blk_trace_setup_lba(काष्ठा blk_trace *bt,
				काष्ठा block_device *bdev)
अणु
	अगर (bdev) अणु
		bt->start_lba = bdev->bd_start_sect;
		bt->end_lba = bdev->bd_start_sect + bdev_nr_sectors(bdev);
	पूर्ण अन्यथा अणु
		bt->start_lba = 0;
		bt->end_lba = -1ULL;
	पूर्ण
पूर्ण

/*
 * Setup everything required to start tracing
 */
अटल पूर्णांक करो_blk_trace_setup(काष्ठा request_queue *q, अक्षर *name, dev_t dev,
			      काष्ठा block_device *bdev,
			      काष्ठा blk_user_trace_setup *buts)
अणु
	काष्ठा blk_trace *bt = शून्य;
	काष्ठा dentry *dir = शून्य;
	पूर्णांक ret;

	lockdep_निश्चित_held(&q->debugfs_mutex);

	अगर (!buts->buf_size || !buts->buf_nr)
		वापस -EINVAL;

	म_नकलन(buts->name, name, BLKTRACE_BDEV_SIZE);
	buts->name[BLKTRACE_BDEV_SIZE - 1] = '\0';

	/*
	 * some device names have larger paths - convert the slashes
	 * to underscores क्रम this to work as expected
	 */
	strreplace(buts->name, '/', '_');

	/*
	 * bdev can be शून्य, as with scsi-generic, this is a helpful as
	 * we can be.
	 */
	अगर (rcu_dereference_रक्षित(q->blk_trace,
				      lockdep_is_held(&q->debugfs_mutex))) अणु
		pr_warn("Concurrent blktraces are not allowed on %s\n",
			buts->name);
		वापस -EBUSY;
	पूर्ण

	bt = kzalloc(माप(*bt), GFP_KERNEL);
	अगर (!bt)
		वापस -ENOMEM;

	ret = -ENOMEM;
	bt->sequence = alloc_percpu(अचिन्हित दीर्घ);
	अगर (!bt->sequence)
		जाओ err;

	bt->msg_data = __alloc_percpu(BLK_TN_MAX_MSG, __alignof__(अक्षर));
	अगर (!bt->msg_data)
		जाओ err;

	/*
	 * When tracing the whole disk reuse the existing debugfs directory
	 * created by the block layer on init. For partitions block devices,
	 * and scsi-generic block devices we create a temporary new debugfs
	 * directory that will be हटाओd once the trace ends.
	 */
	अगर (bdev && !bdev_is_partition(bdev))
		dir = q->debugfs_dir;
	अन्यथा
		bt->dir = dir = debugfs_create_dir(buts->name, blk_debugfs_root);

	/*
	 * As blktrace relies on debugfs क्रम its पूर्णांकerface the debugfs directory
	 * is required, contrary to the usual mantra of not checking क्रम debugfs
	 * files or directories.
	 */
	अगर (IS_ERR_OR_शून्य(dir)) अणु
		pr_warn("debugfs_dir not present for %s so skipping\n",
			buts->name);
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	bt->dev = dev;
	atomic_set(&bt->dropped, 0);
	INIT_LIST_HEAD(&bt->running_list);

	ret = -EIO;
	debugfs_create_file("dropped", 0444, dir, bt, &blk_dropped_fops);
	debugfs_create_file("msg", 0222, dir, bt, &blk_msg_fops);

	bt->rchan = relay_खोलो("trace", dir, buts->buf_size,
				buts->buf_nr, &blk_relay_callbacks, bt);
	अगर (!bt->rchan)
		जाओ err;

	bt->act_mask = buts->act_mask;
	अगर (!bt->act_mask)
		bt->act_mask = (u16) -1;

	blk_trace_setup_lba(bt, bdev);

	/* overग_लिखो with user settings */
	अगर (buts->start_lba)
		bt->start_lba = buts->start_lba;
	अगर (buts->end_lba)
		bt->end_lba = buts->end_lba;

	bt->pid = buts->pid;
	bt->trace_state = Blktrace_setup;

	rcu_assign_poपूर्णांकer(q->blk_trace, bt);
	get_probe_ref();

	ret = 0;
err:
	अगर (ret)
		blk_trace_मुक्त(bt);
	वापस ret;
पूर्ण

अटल पूर्णांक __blk_trace_setup(काष्ठा request_queue *q, अक्षर *name, dev_t dev,
			     काष्ठा block_device *bdev, अक्षर __user *arg)
अणु
	काष्ठा blk_user_trace_setup buts;
	पूर्णांक ret;

	ret = copy_from_user(&buts, arg, माप(buts));
	अगर (ret)
		वापस -EFAULT;

	ret = करो_blk_trace_setup(q, name, dev, bdev, &buts);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(arg, &buts, माप(buts))) अणु
		__blk_trace_हटाओ(q);
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक blk_trace_setup(काष्ठा request_queue *q, अक्षर *name, dev_t dev,
		    काष्ठा block_device *bdev,
		    अक्षर __user *arg)
अणु
	पूर्णांक ret;

	mutex_lock(&q->debugfs_mutex);
	ret = __blk_trace_setup(q, name, dev, bdev, arg);
	mutex_unlock(&q->debugfs_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blk_trace_setup);

#अगर defined(CONFIG_COMPAT) && defined(CONFIG_X86_64)
अटल पूर्णांक compat_blk_trace_setup(काष्ठा request_queue *q, अक्षर *name,
				  dev_t dev, काष्ठा block_device *bdev,
				  अक्षर __user *arg)
अणु
	काष्ठा blk_user_trace_setup buts;
	काष्ठा compat_blk_user_trace_setup cbuts;
	पूर्णांक ret;

	अगर (copy_from_user(&cbuts, arg, माप(cbuts)))
		वापस -EFAULT;

	buts = (काष्ठा blk_user_trace_setup) अणु
		.act_mask = cbuts.act_mask,
		.buf_size = cbuts.buf_size,
		.buf_nr = cbuts.buf_nr,
		.start_lba = cbuts.start_lba,
		.end_lba = cbuts.end_lba,
		.pid = cbuts.pid,
	पूर्ण;

	ret = करो_blk_trace_setup(q, name, dev, bdev, &buts);
	अगर (ret)
		वापस ret;

	अगर (copy_to_user(arg, &buts.name, ARRAY_SIZE(buts.name))) अणु
		__blk_trace_हटाओ(q);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __blk_trace_startstop(काष्ठा request_queue *q, पूर्णांक start)
अणु
	पूर्णांक ret;
	काष्ठा blk_trace *bt;

	bt = rcu_dereference_रक्षित(q->blk_trace,
				       lockdep_is_held(&q->debugfs_mutex));
	अगर (bt == शून्य)
		वापस -EINVAL;

	/*
	 * For starting a trace, we can transition from a setup or stopped
	 * trace. For stopping a trace, the state must be running
	 */
	ret = -EINVAL;
	अगर (start) अणु
		अगर (bt->trace_state == Blktrace_setup ||
		    bt->trace_state == Blktrace_stopped) अणु
			blktrace_seq++;
			smp_mb();
			bt->trace_state = Blktrace_running;
			spin_lock_irq(&running_trace_lock);
			list_add(&bt->running_list, &running_trace_list);
			spin_unlock_irq(&running_trace_lock);

			trace_note_समय(bt);
			ret = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bt->trace_state == Blktrace_running) अणु
			bt->trace_state = Blktrace_stopped;
			spin_lock_irq(&running_trace_lock);
			list_del_init(&bt->running_list);
			spin_unlock_irq(&running_trace_lock);
			relay_flush(bt->rchan);
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक blk_trace_startstop(काष्ठा request_queue *q, पूर्णांक start)
अणु
	पूर्णांक ret;

	mutex_lock(&q->debugfs_mutex);
	ret = __blk_trace_startstop(q, start);
	mutex_unlock(&q->debugfs_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blk_trace_startstop);

/*
 * When पढ़ोing or writing the blktrace sysfs files, the references to the
 * खोलोed sysfs or device files should prevent the underlying block device
 * from being हटाओd. So no further delete protection is really needed.
 */

/**
 * blk_trace_ioctl: - handle the ioctls associated with tracing
 * @bdev:	the block device
 * @cmd:	the ioctl cmd
 * @arg:	the argument data, अगर any
 *
 **/
पूर्णांक blk_trace_ioctl(काष्ठा block_device *bdev, अचिन्हित cmd, अक्षर __user *arg)
अणु
	काष्ठा request_queue *q;
	पूर्णांक ret, start = 0;
	अक्षर b[BDEVNAME_SIZE];

	q = bdev_get_queue(bdev);
	अगर (!q)
		वापस -ENXIO;

	mutex_lock(&q->debugfs_mutex);

	चयन (cmd) अणु
	हाल BLKTRACESETUP:
		bdevname(bdev, b);
		ret = __blk_trace_setup(q, b, bdev->bd_dev, bdev, arg);
		अवरोध;
#अगर defined(CONFIG_COMPAT) && defined(CONFIG_X86_64)
	हाल BLKTRACESETUP32:
		bdevname(bdev, b);
		ret = compat_blk_trace_setup(q, b, bdev->bd_dev, bdev, arg);
		अवरोध;
#पूर्ण_अगर
	हाल BLKTRACESTART:
		start = 1;
		fallthrough;
	हाल BLKTRACESTOP:
		ret = __blk_trace_startstop(q, start);
		अवरोध;
	हाल BLKTRACETEARDOWN:
		ret = __blk_trace_हटाओ(q);
		अवरोध;
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण

	mutex_unlock(&q->debugfs_mutex);
	वापस ret;
पूर्ण

/**
 * blk_trace_shutकरोwn: - stop and cleanup trace काष्ठाures
 * @q:    the request queue associated with the device
 *
 **/
व्योम blk_trace_shutकरोwn(काष्ठा request_queue *q)
अणु
	mutex_lock(&q->debugfs_mutex);
	अगर (rcu_dereference_रक्षित(q->blk_trace,
				      lockdep_is_held(&q->debugfs_mutex))) अणु
		__blk_trace_startstop(q, 0);
		__blk_trace_हटाओ(q);
	पूर्ण

	mutex_unlock(&q->debugfs_mutex);
पूर्ण

#अगर_घोषित CONFIG_BLK_CGROUP
अटल u64 blk_trace_bio_get_cgid(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	काष्ठा blk_trace *bt;

	/* We करोn't use the 'bt' value here except as an optimization... */
	bt = rcu_dereference_रक्षित(q->blk_trace, 1);
	अगर (!bt || !(blk_tracer_flags.val & TRACE_BLK_OPT_CGROUP))
		वापस 0;

	अगर (!bio->bi_blkg)
		वापस 0;
	वापस cgroup_id(bio_blkcg(bio)->css.cgroup);
पूर्ण
#अन्यथा
अटल u64 blk_trace_bio_get_cgid(काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल u64
blk_trace_request_get_cgid(काष्ठा request *rq)
अणु
	अगर (!rq->bio)
		वापस 0;
	/* Use the first bio */
	वापस blk_trace_bio_get_cgid(rq->q, rq->bio);
पूर्ण

/*
 * blktrace probes
 */

/**
 * blk_add_trace_rq - Add a trace क्रम a request oriented action
 * @rq:		the source request
 * @error:	वापस status to log
 * @nr_bytes:	number of completed bytes
 * @what:	the action
 * @cgid:	the cgroup info
 *
 * Description:
 *     Records an action against a request. Will log the bio offset + size.
 *
 **/
अटल व्योम blk_add_trace_rq(काष्ठा request *rq, पूर्णांक error,
			     अचिन्हित पूर्णांक nr_bytes, u32 what, u64 cgid)
अणु
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(rq->q->blk_trace);
	अगर (likely(!bt)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (blk_rq_is_passthrough(rq))
		what |= BLK_TC_ACT(BLK_TC_PC);
	अन्यथा
		what |= BLK_TC_ACT(BLK_TC_FS);

	__blk_add_trace(bt, blk_rq_trace_sector(rq), nr_bytes, req_op(rq),
			rq->cmd_flags, what, error, 0, शून्य, cgid);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम blk_add_trace_rq_insert(व्योम *ignore, काष्ठा request *rq)
अणु
	blk_add_trace_rq(rq, 0, blk_rq_bytes(rq), BLK_TA_INSERT,
			 blk_trace_request_get_cgid(rq));
पूर्ण

अटल व्योम blk_add_trace_rq_issue(व्योम *ignore, काष्ठा request *rq)
अणु
	blk_add_trace_rq(rq, 0, blk_rq_bytes(rq), BLK_TA_ISSUE,
			 blk_trace_request_get_cgid(rq));
पूर्ण

अटल व्योम blk_add_trace_rq_merge(व्योम *ignore, काष्ठा request *rq)
अणु
	blk_add_trace_rq(rq, 0, blk_rq_bytes(rq), BLK_TA_BACKMERGE,
			 blk_trace_request_get_cgid(rq));
पूर्ण

अटल व्योम blk_add_trace_rq_requeue(व्योम *ignore, काष्ठा request *rq)
अणु
	blk_add_trace_rq(rq, 0, blk_rq_bytes(rq), BLK_TA_REQUEUE,
			 blk_trace_request_get_cgid(rq));
पूर्ण

अटल व्योम blk_add_trace_rq_complete(व्योम *ignore, काष्ठा request *rq,
			पूर्णांक error, अचिन्हित पूर्णांक nr_bytes)
अणु
	blk_add_trace_rq(rq, error, nr_bytes, BLK_TA_COMPLETE,
			 blk_trace_request_get_cgid(rq));
पूर्ण

/**
 * blk_add_trace_bio - Add a trace क्रम a bio oriented action
 * @q:		queue the io is क्रम
 * @bio:	the source bio
 * @what:	the action
 * @error:	error, अगर any
 *
 * Description:
 *     Records an action against a bio. Will log the bio offset + size.
 *
 **/
अटल व्योम blk_add_trace_bio(काष्ठा request_queue *q, काष्ठा bio *bio,
			      u32 what, पूर्णांक error)
अणु
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	अगर (likely(!bt)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	__blk_add_trace(bt, bio->bi_iter.bi_sector, bio->bi_iter.bi_size,
			bio_op(bio), bio->bi_opf, what, error, 0, शून्य,
			blk_trace_bio_get_cgid(q, bio));
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम blk_add_trace_bio_bounce(व्योम *ignore, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(bio->bi_bdev->bd_disk->queue, bio, BLK_TA_BOUNCE, 0);
पूर्ण

अटल व्योम blk_add_trace_bio_complete(व्योम *ignore,
				       काष्ठा request_queue *q, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(q, bio, BLK_TA_COMPLETE,
			  blk_status_to_त्रुटि_सं(bio->bi_status));
पूर्ण

अटल व्योम blk_add_trace_bio_backmerge(व्योम *ignore, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(bio->bi_bdev->bd_disk->queue, bio, BLK_TA_BACKMERGE,
			0);
पूर्ण

अटल व्योम blk_add_trace_bio_fronपंचांगerge(व्योम *ignore, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(bio->bi_bdev->bd_disk->queue, bio, BLK_TA_FRONTMERGE,
			0);
पूर्ण

अटल व्योम blk_add_trace_bio_queue(व्योम *ignore, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(bio->bi_bdev->bd_disk->queue, bio, BLK_TA_QUEUE, 0);
पूर्ण

अटल व्योम blk_add_trace_getrq(व्योम *ignore, काष्ठा bio *bio)
अणु
	blk_add_trace_bio(bio->bi_bdev->bd_disk->queue, bio, BLK_TA_GETRQ, 0);
पूर्ण

अटल व्योम blk_add_trace_plug(व्योम *ignore, काष्ठा request_queue *q)
अणु
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	अगर (bt)
		__blk_add_trace(bt, 0, 0, 0, 0, BLK_TA_PLUG, 0, 0, शून्य, 0);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम blk_add_trace_unplug(व्योम *ignore, काष्ठा request_queue *q,
				    अचिन्हित पूर्णांक depth, bool explicit)
अणु
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	अगर (bt) अणु
		__be64 rpdu = cpu_to_be64(depth);
		u32 what;

		अगर (explicit)
			what = BLK_TA_UNPLUG_IO;
		अन्यथा
			what = BLK_TA_UNPLUG_TIMER;

		__blk_add_trace(bt, 0, 0, 0, 0, what, 0, माप(rpdu), &rpdu, 0);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम blk_add_trace_split(व्योम *ignore, काष्ठा bio *bio, अचिन्हित पूर्णांक pdu)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	अगर (bt) अणु
		__be64 rpdu = cpu_to_be64(pdu);

		__blk_add_trace(bt, bio->bi_iter.bi_sector,
				bio->bi_iter.bi_size, bio_op(bio), bio->bi_opf,
				BLK_TA_SPLIT,
				blk_status_to_त्रुटि_सं(bio->bi_status),
				माप(rpdu), &rpdu,
				blk_trace_bio_get_cgid(q, bio));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * blk_add_trace_bio_remap - Add a trace क्रम a bio-remap operation
 * @ignore:	trace callback data parameter (not used)
 * @bio:	the source bio
 * @dev:	source device
 * @from:	source sector
 *
 * Called after a bio is remapped to a dअगरferent device and/or sector.
 **/
अटल व्योम blk_add_trace_bio_remap(व्योम *ignore, काष्ठा bio *bio, dev_t dev,
				    sector_t from)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	काष्ठा blk_trace *bt;
	काष्ठा blk_io_trace_remap r;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(q->blk_trace);
	अगर (likely(!bt)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	r.device_from = cpu_to_be32(dev);
	r.device_to   = cpu_to_be32(bio_dev(bio));
	r.sector_from = cpu_to_be64(from);

	__blk_add_trace(bt, bio->bi_iter.bi_sector, bio->bi_iter.bi_size,
			bio_op(bio), bio->bi_opf, BLK_TA_REMAP,
			blk_status_to_त्रुटि_सं(bio->bi_status),
			माप(r), &r, blk_trace_bio_get_cgid(q, bio));
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * blk_add_trace_rq_remap - Add a trace क्रम a request-remap operation
 * @ignore:	trace callback data parameter (not used)
 * @rq:		the source request
 * @dev:	target device
 * @from:	source sector
 *
 * Description:
 *     Device mapper remaps request to other devices.
 *     Add a trace क्रम that action.
 *
 **/
अटल व्योम blk_add_trace_rq_remap(व्योम *ignore, काष्ठा request *rq, dev_t dev,
				   sector_t from)
अणु
	काष्ठा blk_trace *bt;
	काष्ठा blk_io_trace_remap r;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(rq->q->blk_trace);
	अगर (likely(!bt)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	r.device_from = cpu_to_be32(dev);
	r.device_to   = cpu_to_be32(disk_devt(rq->rq_disk));
	r.sector_from = cpu_to_be64(from);

	__blk_add_trace(bt, blk_rq_pos(rq), blk_rq_bytes(rq),
			rq_data_dir(rq), 0, BLK_TA_REMAP, 0,
			माप(r), &r, blk_trace_request_get_cgid(rq));
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * blk_add_driver_data - Add binary message with driver-specअगरic data
 * @rq:		io request
 * @data:	driver-specअगरic data
 * @len:	length of driver-specअगरic data
 *
 * Description:
 *     Some drivers might want to ग_लिखो driver-specअगरic data per request.
 *
 **/
व्योम blk_add_driver_data(काष्ठा request *rq, व्योम *data, माप_प्रकार len)
अणु
	काष्ठा blk_trace *bt;

	rcu_पढ़ो_lock();
	bt = rcu_dereference(rq->q->blk_trace);
	अगर (likely(!bt)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	__blk_add_trace(bt, blk_rq_trace_sector(rq), blk_rq_bytes(rq), 0, 0,
				BLK_TA_DRV_DATA, 0, len, data,
				blk_trace_request_get_cgid(rq));
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(blk_add_driver_data);

अटल व्योम blk_रेजिस्टर_tracepoपूर्णांकs(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_trace_block_rq_insert(blk_add_trace_rq_insert, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_rq_issue(blk_add_trace_rq_issue, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_rq_merge(blk_add_trace_rq_merge, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_rq_requeue(blk_add_trace_rq_requeue, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_rq_complete(blk_add_trace_rq_complete, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_bounce(blk_add_trace_bio_bounce, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_complete(blk_add_trace_bio_complete, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_backmerge(blk_add_trace_bio_backmerge, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_fronपंचांगerge(blk_add_trace_bio_fronपंचांगerge, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_queue(blk_add_trace_bio_queue, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_getrq(blk_add_trace_getrq, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_plug(blk_add_trace_plug, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_unplug(blk_add_trace_unplug, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_split(blk_add_trace_split, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_bio_remap(blk_add_trace_bio_remap, शून्य);
	WARN_ON(ret);
	ret = रेजिस्टर_trace_block_rq_remap(blk_add_trace_rq_remap, शून्य);
	WARN_ON(ret);
पूर्ण

अटल व्योम blk_unरेजिस्टर_tracepoपूर्णांकs(व्योम)
अणु
	unरेजिस्टर_trace_block_rq_remap(blk_add_trace_rq_remap, शून्य);
	unरेजिस्टर_trace_block_bio_remap(blk_add_trace_bio_remap, शून्य);
	unरेजिस्टर_trace_block_split(blk_add_trace_split, शून्य);
	unरेजिस्टर_trace_block_unplug(blk_add_trace_unplug, शून्य);
	unरेजिस्टर_trace_block_plug(blk_add_trace_plug, शून्य);
	unरेजिस्टर_trace_block_getrq(blk_add_trace_getrq, शून्य);
	unरेजिस्टर_trace_block_bio_queue(blk_add_trace_bio_queue, शून्य);
	unरेजिस्टर_trace_block_bio_fronपंचांगerge(blk_add_trace_bio_fronपंचांगerge, शून्य);
	unरेजिस्टर_trace_block_bio_backmerge(blk_add_trace_bio_backmerge, शून्य);
	unरेजिस्टर_trace_block_bio_complete(blk_add_trace_bio_complete, शून्य);
	unरेजिस्टर_trace_block_bio_bounce(blk_add_trace_bio_bounce, शून्य);
	unरेजिस्टर_trace_block_rq_complete(blk_add_trace_rq_complete, शून्य);
	unरेजिस्टर_trace_block_rq_requeue(blk_add_trace_rq_requeue, शून्य);
	unरेजिस्टर_trace_block_rq_merge(blk_add_trace_rq_merge, शून्य);
	unरेजिस्टर_trace_block_rq_issue(blk_add_trace_rq_issue, शून्य);
	unरेजिस्टर_trace_block_rq_insert(blk_add_trace_rq_insert, शून्य);

	tracepoपूर्णांक_synchronize_unरेजिस्टर();
पूर्ण

/*
 * काष्ठा blk_io_tracer क्रमmatting routines
 */

अटल व्योम fill_rwbs(अक्षर *rwbs, स्थिर काष्ठा blk_io_trace *t)
अणु
	पूर्णांक i = 0;
	पूर्णांक tc = t->action >> BLK_TC_SHIFT;

	अगर ((t->action & ~__BLK_TN_CGROUP) == BLK_TN_MESSAGE) अणु
		rwbs[i++] = 'N';
		जाओ out;
	पूर्ण

	अगर (tc & BLK_TC_FLUSH)
		rwbs[i++] = 'F';

	अगर (tc & BLK_TC_DISCARD)
		rwbs[i++] = 'D';
	अन्यथा अगर (tc & BLK_TC_WRITE)
		rwbs[i++] = 'W';
	अन्यथा अगर (t->bytes)
		rwbs[i++] = 'R';
	अन्यथा
		rwbs[i++] = 'N';

	अगर (tc & BLK_TC_FUA)
		rwbs[i++] = 'F';
	अगर (tc & BLK_TC_AHEAD)
		rwbs[i++] = 'A';
	अगर (tc & BLK_TC_SYNC)
		rwbs[i++] = 'S';
	अगर (tc & BLK_TC_META)
		rwbs[i++] = 'M';
out:
	rwbs[i] = '\0';
पूर्ण

अटल अंतरभूत
स्थिर काष्ठा blk_io_trace *te_blk_io_trace(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस (स्थिर काष्ठा blk_io_trace *)ent;
पूर्ण

अटल अंतरभूत स्थिर व्योम *pdu_start(स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	वापस (व्योम *)(te_blk_io_trace(ent) + 1) + (has_cg ? माप(u64) : 0);
पूर्ण

अटल अंतरभूत u64 t_cgid(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस *(u64 *)(te_blk_io_trace(ent) + 1);
पूर्ण

अटल अंतरभूत पूर्णांक pdu_real_len(स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	वापस te_blk_io_trace(ent)->pdu_len - (has_cg ? माप(u64) : 0);
पूर्ण

अटल अंतरभूत u32 t_action(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस te_blk_io_trace(ent)->action;
पूर्ण

अटल अंतरभूत u32 t_bytes(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस te_blk_io_trace(ent)->bytes;
पूर्ण

अटल अंतरभूत u32 t_sec(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस te_blk_io_trace(ent)->bytes >> 9;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ t_sector(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस te_blk_io_trace(ent)->sector;
पूर्ण

अटल अंतरभूत __u16 t_error(स्थिर काष्ठा trace_entry *ent)
अणु
	वापस te_blk_io_trace(ent)->error;
पूर्ण

अटल __u64 get_pdu_पूर्णांक(स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	स्थिर __be64 *val = pdu_start(ent, has_cg);
	वापस be64_to_cpu(*val);
पूर्ण

प्रकार व्योम (blk_log_action_t) (काष्ठा trace_iterator *iter, स्थिर अक्षर *act,
	bool has_cg);

अटल व्योम blk_log_action_classic(काष्ठा trace_iterator *iter, स्थिर अक्षर *act,
	bool has_cg)
अणु
	अक्षर rwbs[RWBS_LEN];
	अचिन्हित दीर्घ दीर्घ ts  = iter->ts;
	अचिन्हित दीर्घ nsec_rem = करो_भाग(ts, NSEC_PER_SEC);
	अचिन्हित secs	       = (अचिन्हित दीर्घ)ts;
	स्थिर काष्ठा blk_io_trace *t = te_blk_io_trace(iter->ent);

	fill_rwbs(rwbs, t);

	trace_seq_म_लिखो(&iter->seq,
			 "%3d,%-3d %2d %5d.%09lu %5u %2s %3s ",
			 MAJOR(t->device), MINOR(t->device), iter->cpu,
			 secs, nsec_rem, iter->ent->pid, act, rwbs);
पूर्ण

अटल व्योम blk_log_action(काष्ठा trace_iterator *iter, स्थिर अक्षर *act,
	bool has_cg)
अणु
	अक्षर rwbs[RWBS_LEN];
	स्थिर काष्ठा blk_io_trace *t = te_blk_io_trace(iter->ent);

	fill_rwbs(rwbs, t);
	अगर (has_cg) अणु
		u64 id = t_cgid(iter->ent);

		अगर (blk_tracer_flags.val & TRACE_BLK_OPT_CGNAME) अणु
			अक्षर blkcg_name_buf[NAME_MAX + 1] = "<...>";

			cgroup_path_from_kernfs_id(id, blkcg_name_buf,
				माप(blkcg_name_buf));
			trace_seq_म_लिखो(&iter->seq, "%3d,%-3d %s %2s %3s ",
				 MAJOR(t->device), MINOR(t->device),
				 blkcg_name_buf, act, rwbs);
		पूर्ण अन्यथा अणु
			/*
			 * The cgid portion used to be "INO,GEN".  Userland
			 * builds a खाताID_INO32_GEN fid out of them and
			 * खोलोs the cgroup using खोलो_by_handle_at(2).
			 * While 32bit ino setups are still the same, 64bit
			 * ones now use the 64bit ino as the whole ID and
			 * no दीर्घer use generation.
			 *
			 * Regardless of the content, always output
			 * "LOW32,HIGH32" so that खाताID_INO32_GEN fid can
			 * be mapped back to @id on both 64 and 32bit ino
			 * setups.  See __kernfs_fh_to_dentry().
			 */
			trace_seq_म_लिखो(&iter->seq,
				 "%3d,%-3d %llx,%-llx %2s %3s ",
				 MAJOR(t->device), MINOR(t->device),
				 id & U32_MAX, id >> 32, act, rwbs);
		पूर्ण
	पूर्ण अन्यथा
		trace_seq_म_लिखो(&iter->seq, "%3d,%-3d %2s %3s ",
				 MAJOR(t->device), MINOR(t->device), act, rwbs);
पूर्ण

अटल व्योम blk_log_dump_pdu(काष्ठा trace_seq *s,
	स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	स्थिर अचिन्हित अक्षर *pdu_buf;
	पूर्णांक pdu_len;
	पूर्णांक i, end;

	pdu_buf = pdu_start(ent, has_cg);
	pdu_len = pdu_real_len(ent, has_cg);

	अगर (!pdu_len)
		वापस;

	/* find the last zero that needs to be prपूर्णांकed */
	क्रम (end = pdu_len - 1; end >= 0; end--)
		अगर (pdu_buf[end])
			अवरोध;
	end++;

	trace_seq_अ_दो(s, '(');

	क्रम (i = 0; i < pdu_len; i++) अणु

		trace_seq_म_लिखो(s, "%s%02x",
				 i == 0 ? "" : " ", pdu_buf[i]);

		/*
		 * stop when the rest is just zeros and indicate so
		 * with a ".." appended
		 */
		अगर (i == end && end != pdu_len - 1) अणु
			trace_seq_माला_दो(s, " ..) ");
			वापस;
		पूर्ण
	पूर्ण

	trace_seq_माला_दो(s, ") ");
पूर्ण

अटल व्योम blk_log_generic(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	अक्षर cmd[TASK_COMM_LEN];

	trace_find_cmdline(ent->pid, cmd);

	अगर (t_action(ent) & BLK_TC_ACT(BLK_TC_PC)) अणु
		trace_seq_म_लिखो(s, "%u ", t_bytes(ent));
		blk_log_dump_pdu(s, ent, has_cg);
		trace_seq_म_लिखो(s, "[%s]\n", cmd);
	पूर्ण अन्यथा अणु
		अगर (t_sec(ent))
			trace_seq_म_लिखो(s, "%llu + %u [%s]\n",
						t_sector(ent), t_sec(ent), cmd);
		अन्यथा
			trace_seq_म_लिखो(s, "[%s]\n", cmd);
	पूर्ण
पूर्ण

अटल व्योम blk_log_with_error(काष्ठा trace_seq *s,
			      स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	अगर (t_action(ent) & BLK_TC_ACT(BLK_TC_PC)) अणु
		blk_log_dump_pdu(s, ent, has_cg);
		trace_seq_म_लिखो(s, "[%d]\n", t_error(ent));
	पूर्ण अन्यथा अणु
		अगर (t_sec(ent))
			trace_seq_म_लिखो(s, "%llu + %u [%d]\n",
					 t_sector(ent),
					 t_sec(ent), t_error(ent));
		अन्यथा
			trace_seq_म_लिखो(s, "%llu [%d]\n",
					 t_sector(ent), t_error(ent));
	पूर्ण
पूर्ण

अटल व्योम blk_log_remap(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	स्थिर काष्ठा blk_io_trace_remap *__r = pdu_start(ent, has_cg);

	trace_seq_म_लिखो(s, "%llu + %u <- (%d,%d) %llu\n",
			 t_sector(ent), t_sec(ent),
			 MAJOR(be32_to_cpu(__r->device_from)),
			 MINOR(be32_to_cpu(__r->device_from)),
			 be64_to_cpu(__r->sector_from));
पूर्ण

अटल व्योम blk_log_plug(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	अक्षर cmd[TASK_COMM_LEN];

	trace_find_cmdline(ent->pid, cmd);

	trace_seq_म_लिखो(s, "[%s]\n", cmd);
पूर्ण

अटल व्योम blk_log_unplug(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	अक्षर cmd[TASK_COMM_LEN];

	trace_find_cmdline(ent->pid, cmd);

	trace_seq_म_लिखो(s, "[%s] %llu\n", cmd, get_pdu_पूर्णांक(ent, has_cg));
पूर्ण

अटल व्योम blk_log_split(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent, bool has_cg)
अणु
	अक्षर cmd[TASK_COMM_LEN];

	trace_find_cmdline(ent->pid, cmd);

	trace_seq_म_लिखो(s, "%llu / %llu [%s]\n", t_sector(ent),
			 get_pdu_पूर्णांक(ent, has_cg), cmd);
पूर्ण

अटल व्योम blk_log_msg(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent,
			bool has_cg)
अणु

	trace_seq_puपंचांगem(s, pdu_start(ent, has_cg),
		pdu_real_len(ent, has_cg));
	trace_seq_अ_दो(s, '\n');
पूर्ण

/*
 * काष्ठा tracer operations
 */

अटल व्योम blk_tracer_prपूर्णांक_header(काष्ठा seq_file *m)
अणु
	अगर (!(blk_tracer_flags.val & TRACE_BLK_OPT_CLASSIC))
		वापस;
	seq_माला_दो(m, "# DEV   CPU TIMESTAMP     PID ACT FLG\n"
		    "#  |     |     |           |   |   |\n");
पूर्ण

अटल व्योम blk_tracer_start(काष्ठा trace_array *tr)
अणु
	blk_tracer_enabled = true;
पूर्ण

अटल पूर्णांक blk_tracer_init(काष्ठा trace_array *tr)
अणु
	blk_tr = tr;
	blk_tracer_start(tr);
	वापस 0;
पूर्ण

अटल व्योम blk_tracer_stop(काष्ठा trace_array *tr)
अणु
	blk_tracer_enabled = false;
पूर्ण

अटल व्योम blk_tracer_reset(काष्ठा trace_array *tr)
अणु
	blk_tracer_stop(tr);
पूर्ण

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *act[2];
	व्योम	   (*prपूर्णांक)(काष्ठा trace_seq *s, स्थिर काष्ठा trace_entry *ent,
			    bool has_cg);
पूर्ण what2act[] = अणु
	[__BLK_TA_QUEUE]	= अणुअणु  "Q", "queue" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_BACKMERGE]	= अणुअणु  "M", "backmerge" पूर्ण,  blk_log_generic पूर्ण,
	[__BLK_TA_FRONTMERGE]	= अणुअणु  "F", "frontmerge" पूर्ण, blk_log_generic पूर्ण,
	[__BLK_TA_GETRQ]	= अणुअणु  "G", "getrq" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_SLEEPRQ]	= अणुअणु  "S", "sleeprq" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_REQUEUE]	= अणुअणु  "R", "requeue" पूर्ण,	   blk_log_with_error पूर्ण,
	[__BLK_TA_ISSUE]	= अणुअणु  "D", "issue" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_COMPLETE]	= अणुअणु  "C", "complete" पूर्ण,   blk_log_with_error पूर्ण,
	[__BLK_TA_PLUG]		= अणुअणु  "P", "plug" पूर्ण,	   blk_log_plug पूर्ण,
	[__BLK_TA_UNPLUG_IO]	= अणुअणु  "U", "unplug_io" पूर्ण,  blk_log_unplug पूर्ण,
	[__BLK_TA_UNPLUG_TIMER]	= अणुअणु "UT", "unplug_timer" पूर्ण, blk_log_unplug पूर्ण,
	[__BLK_TA_INSERT]	= अणुअणु  "I", "insert" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_SPLIT]	= अणुअणु  "X", "split" पूर्ण,	   blk_log_split पूर्ण,
	[__BLK_TA_BOUNCE]	= अणुअणु  "B", "bounce" पूर्ण,	   blk_log_generic पूर्ण,
	[__BLK_TA_REMAP]	= अणुअणु  "A", "remap" पूर्ण,	   blk_log_remap पूर्ण,
पूर्ण;

अटल क्रमागत prपूर्णांक_line_t prपूर्णांक_one_line(काष्ठा trace_iterator *iter,
					bool classic)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	स्थिर काष्ठा blk_io_trace *t;
	u16 what;
	bool दीर्घ_act;
	blk_log_action_t *log_action;
	bool has_cg;

	t	   = te_blk_io_trace(iter->ent);
	what	   = (t->action & ((1 << BLK_TC_SHIFT) - 1)) & ~__BLK_TA_CGROUP;
	दीर्घ_act   = !!(tr->trace_flags & TRACE_ITER_VERBOSE);
	log_action = classic ? &blk_log_action_classic : &blk_log_action;
	has_cg	   = t->action & __BLK_TA_CGROUP;

	अगर ((t->action & ~__BLK_TN_CGROUP) == BLK_TN_MESSAGE) अणु
		log_action(iter, दीर्घ_act ? "message" : "m", has_cg);
		blk_log_msg(s, iter->ent, has_cg);
		वापस trace_handle_वापस(s);
	पूर्ण

	अगर (unlikely(what == 0 || what >= ARRAY_SIZE(what2act)))
		trace_seq_म_लिखो(s, "Unknown action %x\n", what);
	अन्यथा अणु
		log_action(iter, what2act[what].act[दीर्घ_act], has_cg);
		what2act[what].prपूर्णांक(s, iter->ent, has_cg);
	पूर्ण

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t blk_trace_event_prपूर्णांक(काष्ठा trace_iterator *iter,
					       पूर्णांक flags, काष्ठा trace_event *event)
अणु
	वापस prपूर्णांक_one_line(iter, false);
पूर्ण

अटल व्योम blk_trace_synthesize_old_trace(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा blk_io_trace *t = (काष्ठा blk_io_trace *)iter->ent;
	स्थिर पूर्णांक offset = दुरत्व(काष्ठा blk_io_trace, sector);
	काष्ठा blk_io_trace old = अणु
		.magic	  = BLK_IO_TRACE_MAGIC | BLK_IO_TRACE_VERSION,
		.समय     = iter->ts,
	पूर्ण;

	trace_seq_puपंचांगem(s, &old, offset);
	trace_seq_puपंचांगem(s, &t->sector,
			 माप(old) - offset + t->pdu_len);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
blk_trace_event_prपूर्णांक_binary(काष्ठा trace_iterator *iter, पूर्णांक flags,
			     काष्ठा trace_event *event)
अणु
	blk_trace_synthesize_old_trace(iter);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t blk_tracer_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	अगर (!(blk_tracer_flags.val & TRACE_BLK_OPT_CLASSIC))
		वापस TRACE_TYPE_UNHANDLED;

	वापस prपूर्णांक_one_line(iter, true);
पूर्ण

अटल पूर्णांक
blk_tracer_set_flag(काष्ठा trace_array *tr, u32 old_flags, u32 bit, पूर्णांक set)
अणु
	/* करोn't output context-info क्रम blk_classic output */
	अगर (bit == TRACE_BLK_OPT_CLASSIC) अणु
		अगर (set)
			tr->trace_flags &= ~TRACE_ITER_CONTEXT_INFO;
		अन्यथा
			tr->trace_flags |= TRACE_ITER_CONTEXT_INFO;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा tracer blk_tracer __पढ़ो_mostly = अणु
	.name		= "blk",
	.init		= blk_tracer_init,
	.reset		= blk_tracer_reset,
	.start		= blk_tracer_start,
	.stop		= blk_tracer_stop,
	.prपूर्णांक_header	= blk_tracer_prपूर्णांक_header,
	.prपूर्णांक_line	= blk_tracer_prपूर्णांक_line,
	.flags		= &blk_tracer_flags,
	.set_flag	= blk_tracer_set_flag,
पूर्ण;

अटल काष्ठा trace_event_functions trace_blk_event_funcs = अणु
	.trace		= blk_trace_event_prपूर्णांक,
	.binary		= blk_trace_event_prपूर्णांक_binary,
पूर्ण;

अटल काष्ठा trace_event trace_blk_event = अणु
	.type		= TRACE_BLK,
	.funcs		= &trace_blk_event_funcs,
पूर्ण;

अटल पूर्णांक __init init_blk_tracer(व्योम)
अणु
	अगर (!रेजिस्टर_trace_event(&trace_blk_event)) अणु
		pr_warn("Warning: could not register block events\n");
		वापस 1;
	पूर्ण

	अगर (रेजिस्टर_tracer(&blk_tracer) != 0) अणु
		pr_warn("Warning: could not register the block tracer\n");
		unरेजिस्टर_trace_event(&trace_blk_event);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

device_initcall(init_blk_tracer);

अटल पूर्णांक blk_trace_हटाओ_queue(काष्ठा request_queue *q)
अणु
	काष्ठा blk_trace *bt;

	bt = rcu_replace_poपूर्णांकer(q->blk_trace, शून्य,
				 lockdep_is_held(&q->debugfs_mutex));
	अगर (bt == शून्य)
		वापस -EINVAL;

	put_probe_ref();
	synchronize_rcu();
	blk_trace_मुक्त(bt);
	वापस 0;
पूर्ण

/*
 * Setup everything required to start tracing
 */
अटल पूर्णांक blk_trace_setup_queue(काष्ठा request_queue *q,
				 काष्ठा block_device *bdev)
अणु
	काष्ठा blk_trace *bt = शून्य;
	पूर्णांक ret = -ENOMEM;

	bt = kzalloc(माप(*bt), GFP_KERNEL);
	अगर (!bt)
		वापस -ENOMEM;

	bt->msg_data = __alloc_percpu(BLK_TN_MAX_MSG, __alignof__(अक्षर));
	अगर (!bt->msg_data)
		जाओ मुक्त_bt;

	bt->dev = bdev->bd_dev;
	bt->act_mask = (u16)-1;

	blk_trace_setup_lba(bt, bdev);

	rcu_assign_poपूर्णांकer(q->blk_trace, bt);
	get_probe_ref();
	वापस 0;

मुक्त_bt:
	blk_trace_मुक्त(bt);
	वापस ret;
पूर्ण

/*
 * sysfs पूर्णांकerface to enable and configure tracing
 */

अटल sमाप_प्रकार sysfs_blk_trace_attr_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf);
अटल sमाप_प्रकार sysfs_blk_trace_attr_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count);
#घोषणा BLK_TRACE_DEVICE_ATTR(_name) \
	DEVICE_ATTR(_name, S_IRUGO | S_IWUSR, \
		    sysfs_blk_trace_attr_show, \
		    sysfs_blk_trace_attr_store)

अटल BLK_TRACE_DEVICE_ATTR(enable);
अटल BLK_TRACE_DEVICE_ATTR(act_mask);
अटल BLK_TRACE_DEVICE_ATTR(pid);
अटल BLK_TRACE_DEVICE_ATTR(start_lba);
अटल BLK_TRACE_DEVICE_ATTR(end_lba);

अटल काष्ठा attribute *blk_trace_attrs[] = अणु
	&dev_attr_enable.attr,
	&dev_attr_act_mask.attr,
	&dev_attr_pid.attr,
	&dev_attr_start_lba.attr,
	&dev_attr_end_lba.attr,
	शून्य
पूर्ण;

काष्ठा attribute_group blk_trace_attr_group = अणु
	.name  = "trace",
	.attrs = blk_trace_attrs,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक mask;
	स्थिर अक्षर *str;
पूर्ण mask_maps[] = अणु
	अणु BLK_TC_READ,		"read"		पूर्ण,
	अणु BLK_TC_WRITE,		"write"		पूर्ण,
	अणु BLK_TC_FLUSH,		"flush"		पूर्ण,
	अणु BLK_TC_SYNC,		"sync"		पूर्ण,
	अणु BLK_TC_QUEUE,		"queue"		पूर्ण,
	अणु BLK_TC_REQUEUE,	"requeue"	पूर्ण,
	अणु BLK_TC_ISSUE,		"issue"		पूर्ण,
	अणु BLK_TC_COMPLETE,	"complete"	पूर्ण,
	अणु BLK_TC_FS,		"fs"		पूर्ण,
	अणु BLK_TC_PC,		"pc"		पूर्ण,
	अणु BLK_TC_NOTIFY,	"notify"	पूर्ण,
	अणु BLK_TC_AHEAD,		"ahead"		पूर्ण,
	अणु BLK_TC_META,		"meta"		पूर्ण,
	अणु BLK_TC_DISCARD,	"discard"	पूर्ण,
	अणु BLK_TC_DRV_DATA,	"drv_data"	पूर्ण,
	अणु BLK_TC_FUA,		"fua"		पूर्ण,
पूर्ण;

अटल पूर्णांक blk_trace_str2mask(स्थिर अक्षर *str)
अणु
	पूर्णांक i;
	पूर्णांक mask = 0;
	अक्षर *buf, *s, *token;

	buf = kstrdup(str, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;
	s = म_मालाip(buf);

	जबतक (1) अणु
		token = strsep(&s, ",");
		अगर (token == शून्य)
			अवरोध;

		अगर (*token == '\0')
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(mask_maps); i++) अणु
			अगर (strहालcmp(token, mask_maps[i].str) == 0) अणु
				mask |= mask_maps[i].mask;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(mask_maps)) अणु
			mask = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	kमुक्त(buf);

	वापस mask;
पूर्ण

अटल sमाप_प्रकार blk_trace_mask2str(अक्षर *buf, पूर्णांक mask)
अणु
	पूर्णांक i;
	अक्षर *p = buf;

	क्रम (i = 0; i < ARRAY_SIZE(mask_maps); i++) अणु
		अगर (mask & mask_maps[i].mask) अणु
			p += प्र_लिखो(p, "%s%s",
				    (p == buf) ? "" : ",", mask_maps[i].str);
		पूर्ण
	पूर्ण
	*p++ = '\n';

	वापस p - buf;
पूर्ण

अटल sमाप_प्रकार sysfs_blk_trace_attr_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	काष्ठा blk_trace *bt;
	sमाप_प्रकार ret = -ENXIO;

	mutex_lock(&q->debugfs_mutex);

	bt = rcu_dereference_रक्षित(q->blk_trace,
				       lockdep_is_held(&q->debugfs_mutex));
	अगर (attr == &dev_attr_enable) अणु
		ret = प्र_लिखो(buf, "%u\n", !!bt);
		जाओ out_unlock_bdev;
	पूर्ण

	अगर (bt == शून्य)
		ret = प्र_लिखो(buf, "disabled\n");
	अन्यथा अगर (attr == &dev_attr_act_mask)
		ret = blk_trace_mask2str(buf, bt->act_mask);
	अन्यथा अगर (attr == &dev_attr_pid)
		ret = प्र_लिखो(buf, "%u\n", bt->pid);
	अन्यथा अगर (attr == &dev_attr_start_lba)
		ret = प्र_लिखो(buf, "%llu\n", bt->start_lba);
	अन्यथा अगर (attr == &dev_attr_end_lba)
		ret = प्र_लिखो(buf, "%llu\n", bt->end_lba);

out_unlock_bdev:
	mutex_unlock(&q->debugfs_mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार sysfs_blk_trace_attr_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा block_device *bdev = dev_to_bdev(dev);
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	काष्ठा blk_trace *bt;
	u64 value;
	sमाप_प्रकार ret = -EINVAL;

	अगर (count == 0)
		जाओ out;

	अगर (attr == &dev_attr_act_mask) अणु
		अगर (kम_से_अदीर्घl(buf, 0, &value)) अणु
			/* Assume it is a list of trace category names */
			ret = blk_trace_str2mask(buf);
			अगर (ret < 0)
				जाओ out;
			value = ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (kम_से_अदीर्घl(buf, 0, &value))
			जाओ out;
	पूर्ण

	mutex_lock(&q->debugfs_mutex);

	bt = rcu_dereference_रक्षित(q->blk_trace,
				       lockdep_is_held(&q->debugfs_mutex));
	अगर (attr == &dev_attr_enable) अणु
		अगर (!!value == !!bt) अणु
			ret = 0;
			जाओ out_unlock_bdev;
		पूर्ण
		अगर (value)
			ret = blk_trace_setup_queue(q, bdev);
		अन्यथा
			ret = blk_trace_हटाओ_queue(q);
		जाओ out_unlock_bdev;
	पूर्ण

	ret = 0;
	अगर (bt == शून्य) अणु
		ret = blk_trace_setup_queue(q, bdev);
		bt = rcu_dereference_रक्षित(q->blk_trace,
				lockdep_is_held(&q->debugfs_mutex));
	पूर्ण

	अगर (ret == 0) अणु
		अगर (attr == &dev_attr_act_mask)
			bt->act_mask = value;
		अन्यथा अगर (attr == &dev_attr_pid)
			bt->pid = value;
		अन्यथा अगर (attr == &dev_attr_start_lba)
			bt->start_lba = value;
		अन्यथा अगर (attr == &dev_attr_end_lba)
			bt->end_lba = value;
	पूर्ण

out_unlock_bdev:
	mutex_unlock(&q->debugfs_mutex);
out:
	वापस ret ? ret : count;
पूर्ण

पूर्णांक blk_trace_init_sysfs(काष्ठा device *dev)
अणु
	वापस sysfs_create_group(&dev->kobj, &blk_trace_attr_group);
पूर्ण

व्योम blk_trace_हटाओ_sysfs(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &blk_trace_attr_group);
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_IO_TRACE */

#अगर_घोषित CONFIG_EVENT_TRACING

/**
 * blk_fill_rwbs - Fill the buffer rwbs by mapping op to अक्षरacter string.
 * @rwbs:	buffer to be filled
 * @op:		REQ_OP_XXX क्रम the tracepoपूर्णांक
 *
 * Description:
 *     Maps the REQ_OP_XXX to अक्षरacter and fills the buffer provided by the
 *     caller with resulting string.
 *
 **/
व्योम blk_fill_rwbs(अक्षर *rwbs, अचिन्हित पूर्णांक op)
अणु
	पूर्णांक i = 0;

	अगर (op & REQ_PREFLUSH)
		rwbs[i++] = 'F';

	चयन (op & REQ_OP_MASK) अणु
	हाल REQ_OP_WRITE:
	हाल REQ_OP_WRITE_SAME:
		rwbs[i++] = 'W';
		अवरोध;
	हाल REQ_OP_DISCARD:
		rwbs[i++] = 'D';
		अवरोध;
	हाल REQ_OP_SECURE_ERASE:
		rwbs[i++] = 'D';
		rwbs[i++] = 'E';
		अवरोध;
	हाल REQ_OP_FLUSH:
		rwbs[i++] = 'F';
		अवरोध;
	हाल REQ_OP_READ:
		rwbs[i++] = 'R';
		अवरोध;
	शेष:
		rwbs[i++] = 'N';
	पूर्ण

	अगर (op & REQ_FUA)
		rwbs[i++] = 'F';
	अगर (op & REQ_RAHEAD)
		rwbs[i++] = 'A';
	अगर (op & REQ_SYNC)
		rwbs[i++] = 'S';
	अगर (op & REQ_META)
		rwbs[i++] = 'M';

	rwbs[i] = '\0';
पूर्ण
EXPORT_SYMBOL_GPL(blk_fill_rwbs);

#पूर्ण_अगर /* CONFIG_EVENT_TRACING */

