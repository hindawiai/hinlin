<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Facebook
 */

#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/debugfs.h>

#समावेश <linux/blk-mq.h>
#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-mq-tag.h"
#समावेश "blk-rq-qos.h"

अटल व्योम prपूर्णांक_stat(काष्ठा seq_file *m, काष्ठा blk_rq_stat *stat)
अणु
	अगर (stat->nr_samples) अणु
		seq_म_लिखो(m, "samples=%d, mean=%llu, min=%llu, max=%llu",
			   stat->nr_samples, stat->mean, stat->min, stat->max);
	पूर्ण अन्यथा अणु
		seq_माला_दो(m, "samples=0");
	पूर्ण
पूर्ण

अटल पूर्णांक queue_poll_stat_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	पूर्णांक bucket;

	क्रम (bucket = 0; bucket < (BLK_MQ_POLL_STATS_BKTS / 2); bucket++) अणु
		seq_म_लिखो(m, "read  (%d Bytes): ", 1 << (9 + bucket));
		prपूर्णांक_stat(m, &q->poll_stat[2 * bucket]);
		seq_माला_दो(m, "\n");

		seq_म_लिखो(m, "write (%d Bytes): ",  1 << (9 + bucket));
		prपूर्णांक_stat(m, &q->poll_stat[2 * bucket + 1]);
		seq_माला_दो(m, "\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम *queue_requeue_list_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(&q->requeue_lock)
अणु
	काष्ठा request_queue *q = m->निजी;

	spin_lock_irq(&q->requeue_lock);
	वापस seq_list_start(&q->requeue_list, *pos);
पूर्ण

अटल व्योम *queue_requeue_list_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा request_queue *q = m->निजी;

	वापस seq_list_next(v, &q->requeue_list, pos);
पूर्ण

अटल व्योम queue_requeue_list_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&q->requeue_lock)
अणु
	काष्ठा request_queue *q = m->निजी;

	spin_unlock_irq(&q->requeue_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations queue_requeue_list_seq_ops = अणु
	.start	= queue_requeue_list_start,
	.next	= queue_requeue_list_next,
	.stop	= queue_requeue_list_stop,
	.show	= blk_mq_debugfs_rq_show,
पूर्ण;

अटल पूर्णांक blk_flags_show(काष्ठा seq_file *m, स्थिर अचिन्हित दीर्घ flags,
			  स्थिर अक्षर *स्थिर *flag_name, पूर्णांक flag_name_count)
अणु
	bool sep = false;
	पूर्णांक i;

	क्रम (i = 0; i < माप(flags) * BITS_PER_BYTE; i++) अणु
		अगर (!(flags & BIT(i)))
			जारी;
		अगर (sep)
			seq_माला_दो(m, "|");
		sep = true;
		अगर (i < flag_name_count && flag_name[i])
			seq_माला_दो(m, flag_name[i]);
		अन्यथा
			seq_म_लिखो(m, "%d", i);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक queue_pm_only_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;

	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&q->pm_only));
	वापस 0;
पूर्ण

#घोषणा QUEUE_FLAG_NAME(name) [QUEUE_FLAG_##name] = #name
अटल स्थिर अक्षर *स्थिर blk_queue_flag_name[] = अणु
	QUEUE_FLAG_NAME(STOPPED),
	QUEUE_FLAG_NAME(DYING),
	QUEUE_FLAG_NAME(NOMERGES),
	QUEUE_FLAG_NAME(SAME_COMP),
	QUEUE_FLAG_NAME(FAIL_IO),
	QUEUE_FLAG_NAME(NONROT),
	QUEUE_FLAG_NAME(IO_STAT),
	QUEUE_FLAG_NAME(DISCARD),
	QUEUE_FLAG_NAME(NOXMERGES),
	QUEUE_FLAG_NAME(ADD_RANDOM),
	QUEUE_FLAG_NAME(SECERASE),
	QUEUE_FLAG_NAME(SAME_FORCE),
	QUEUE_FLAG_NAME(DEAD),
	QUEUE_FLAG_NAME(INIT_DONE),
	QUEUE_FLAG_NAME(STABLE_WRITES),
	QUEUE_FLAG_NAME(POLL),
	QUEUE_FLAG_NAME(WC),
	QUEUE_FLAG_NAME(FUA),
	QUEUE_FLAG_NAME(DAX),
	QUEUE_FLAG_NAME(STATS),
	QUEUE_FLAG_NAME(POLL_STATS),
	QUEUE_FLAG_NAME(REGISTERED),
	QUEUE_FLAG_NAME(SCSI_PASSTHROUGH),
	QUEUE_FLAG_NAME(QUIESCED),
	QUEUE_FLAG_NAME(PCI_P2PDMA),
	QUEUE_FLAG_NAME(ZONE_RESETALL),
	QUEUE_FLAG_NAME(RQ_ALLOC_TIME),
	QUEUE_FLAG_NAME(NOWAIT),
पूर्ण;
#अघोषित QUEUE_FLAG_NAME

अटल पूर्णांक queue_state_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;

	blk_flags_show(m, q->queue_flags, blk_queue_flag_name,
		       ARRAY_SIZE(blk_queue_flag_name));
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

अटल sमाप_प्रकार queue_state_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा request_queue *q = data;
	अक्षर opbuf[16] = अणु पूर्ण, *op;

	/*
	 * The "state" attribute is हटाओd after blk_cleanup_queue() has called
	 * blk_mq_मुक्त_queue(). Return अगर QUEUE_FLAG_DEAD has been set to aव्योम
	 * triggering a use-after-मुक्त.
	 */
	अगर (blk_queue_dead(q))
		वापस -ENOENT;

	अगर (count >= माप(opbuf)) अणु
		pr_err("%s: operation too long\n", __func__);
		जाओ inval;
	पूर्ण

	अगर (copy_from_user(opbuf, buf, count))
		वापस -EFAULT;
	op = म_मालाip(opbuf);
	अगर (म_भेद(op, "run") == 0) अणु
		blk_mq_run_hw_queues(q, true);
	पूर्ण अन्यथा अगर (म_भेद(op, "start") == 0) अणु
		blk_mq_start_stopped_hw_queues(q, true);
	पूर्ण अन्यथा अगर (म_भेद(op, "kick") == 0) अणु
		blk_mq_kick_requeue_list(q);
	पूर्ण अन्यथा अणु
		pr_err("%s: unsupported operation '%s'\n", __func__, op);
inval:
		pr_err("%s: use 'run', 'start' or 'kick'\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक queue_ग_लिखो_hपूर्णांक_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	पूर्णांक i;

	क्रम (i = 0; i < BLK_MAX_WRITE_HINTS; i++)
		seq_म_लिखो(m, "hint%d: %llu\n", i, q->ग_लिखो_hपूर्णांकs[i]);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार queue_ग_लिखो_hपूर्णांक_store(व्योम *data, स्थिर अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा request_queue *q = data;
	पूर्णांक i;

	क्रम (i = 0; i < BLK_MAX_WRITE_HINTS; i++)
		q->ग_लिखो_hपूर्णांकs[i] = 0;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा blk_mq_debugfs_attr blk_mq_debugfs_queue_attrs[] = अणु
	अणु "poll_stat", 0400, queue_poll_stat_show पूर्ण,
	अणु "requeue_list", 0400, .seq_ops = &queue_requeue_list_seq_ops पूर्ण,
	अणु "pm_only", 0600, queue_pm_only_show, शून्य पूर्ण,
	अणु "state", 0600, queue_state_show, queue_state_ग_लिखो पूर्ण,
	अणु "write_hints", 0600, queue_ग_लिखो_hपूर्णांक_show, queue_ग_लिखो_hपूर्णांक_store पूर्ण,
	अणु "zone_wlock", 0400, queue_zone_wlock_show, शून्य पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा HCTX_STATE_NAME(name) [BLK_MQ_S_##name] = #name
अटल स्थिर अक्षर *स्थिर hctx_state_name[] = अणु
	HCTX_STATE_NAME(STOPPED),
	HCTX_STATE_NAME(TAG_ACTIVE),
	HCTX_STATE_NAME(SCHED_RESTART),
	HCTX_STATE_NAME(INACTIVE),
पूर्ण;
#अघोषित HCTX_STATE_NAME

अटल पूर्णांक hctx_state_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	blk_flags_show(m, hctx->state, hctx_state_name,
		       ARRAY_SIZE(hctx_state_name));
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा BLK_TAG_ALLOC_NAME(name) [BLK_TAG_ALLOC_##name] = #name
अटल स्थिर अक्षर *स्थिर alloc_policy_name[] = अणु
	BLK_TAG_ALLOC_NAME(FIFO),
	BLK_TAG_ALLOC_NAME(RR),
पूर्ण;
#अघोषित BLK_TAG_ALLOC_NAME

#घोषणा HCTX_FLAG_NAME(name) [ilog2(BLK_MQ_F_##name)] = #name
अटल स्थिर अक्षर *स्थिर hctx_flag_name[] = अणु
	HCTX_FLAG_NAME(SHOULD_MERGE),
	HCTX_FLAG_NAME(TAG_QUEUE_SHARED),
	HCTX_FLAG_NAME(BLOCKING),
	HCTX_FLAG_NAME(NO_SCHED),
	HCTX_FLAG_NAME(STACKING),
	HCTX_FLAG_NAME(TAG_HCTX_SHARED),
पूर्ण;
#अघोषित HCTX_FLAG_NAME

अटल पूर्णांक hctx_flags_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	स्थिर पूर्णांक alloc_policy = BLK_MQ_FLAG_TO_ALLOC_POLICY(hctx->flags);

	seq_माला_दो(m, "alloc_policy=");
	अगर (alloc_policy < ARRAY_SIZE(alloc_policy_name) &&
	    alloc_policy_name[alloc_policy])
		seq_माला_दो(m, alloc_policy_name[alloc_policy]);
	अन्यथा
		seq_म_लिखो(m, "%d", alloc_policy);
	seq_माला_दो(m, " ");
	blk_flags_show(m,
		       hctx->flags ^ BLK_ALLOC_POLICY_TO_MQ_FLAG(alloc_policy),
		       hctx_flag_name, ARRAY_SIZE(hctx_flag_name));
	seq_माला_दो(m, "\n");
	वापस 0;
पूर्ण

#घोषणा CMD_FLAG_NAME(name) [__REQ_##name] = #name
अटल स्थिर अक्षर *स्थिर cmd_flag_name[] = अणु
	CMD_FLAG_NAME(FAILFAST_DEV),
	CMD_FLAG_NAME(FAILFAST_TRANSPORT),
	CMD_FLAG_NAME(FAILFAST_DRIVER),
	CMD_FLAG_NAME(SYNC),
	CMD_FLAG_NAME(META),
	CMD_FLAG_NAME(PRIO),
	CMD_FLAG_NAME(NOMERGE),
	CMD_FLAG_NAME(IDLE),
	CMD_FLAG_NAME(INTEGRITY),
	CMD_FLAG_NAME(FUA),
	CMD_FLAG_NAME(PREFLUSH),
	CMD_FLAG_NAME(RAHEAD),
	CMD_FLAG_NAME(BACKGROUND),
	CMD_FLAG_NAME(NOWAIT),
	CMD_FLAG_NAME(NOUNMAP),
	CMD_FLAG_NAME(HIPRI),
पूर्ण;
#अघोषित CMD_FLAG_NAME

#घोषणा RQF_NAME(name) [ilog2((__क्रमce u32)RQF_##name)] = #name
अटल स्थिर अक्षर *स्थिर rqf_name[] = अणु
	RQF_NAME(STARTED),
	RQF_NAME(SOFTBARRIER),
	RQF_NAME(FLUSH_SEQ),
	RQF_NAME(MIXED_MERGE),
	RQF_NAME(MQ_INFLIGHT),
	RQF_NAME(DONTPREP),
	RQF_NAME(FAILED),
	RQF_NAME(QUIET),
	RQF_NAME(ELVPRIV),
	RQF_NAME(IO_STAT),
	RQF_NAME(PM),
	RQF_NAME(HASHED),
	RQF_NAME(STATS),
	RQF_NAME(SPECIAL_PAYLOAD),
	RQF_NAME(ZONE_WRITE_LOCKED),
	RQF_NAME(MQ_POLL_SLEPT),
पूर्ण;
#अघोषित RQF_NAME

अटल स्थिर अक्षर *स्थिर blk_mq_rq_state_name_array[] = अणु
	[MQ_RQ_IDLE]		= "idle",
	[MQ_RQ_IN_FLIGHT]	= "in_flight",
	[MQ_RQ_COMPLETE]	= "complete",
पूर्ण;

अटल स्थिर अक्षर *blk_mq_rq_state_name(क्रमागत mq_rq_state rq_state)
अणु
	अगर (WARN_ON_ONCE((अचिन्हित पूर्णांक)rq_state >=
			 ARRAY_SIZE(blk_mq_rq_state_name_array)))
		वापस "(?)";
	वापस blk_mq_rq_state_name_array[rq_state];
पूर्ण

पूर्णांक __blk_mq_debugfs_rq_show(काष्ठा seq_file *m, काष्ठा request *rq)
अणु
	स्थिर काष्ठा blk_mq_ops *स्थिर mq_ops = rq->q->mq_ops;
	स्थिर अचिन्हित पूर्णांक op = req_op(rq);
	स्थिर अक्षर *op_str = blk_op_str(op);

	seq_म_लिखो(m, "%p {.op=", rq);
	अगर (म_भेद(op_str, "UNKNOWN") == 0)
		seq_म_लिखो(m, "%u", op);
	अन्यथा
		seq_म_लिखो(m, "%s", op_str);
	seq_माला_दो(m, ", .cmd_flags=");
	blk_flags_show(m, rq->cmd_flags & ~REQ_OP_MASK, cmd_flag_name,
		       ARRAY_SIZE(cmd_flag_name));
	seq_माला_दो(m, ", .rq_flags=");
	blk_flags_show(m, (__क्रमce अचिन्हित पूर्णांक)rq->rq_flags, rqf_name,
		       ARRAY_SIZE(rqf_name));
	seq_म_लिखो(m, ", .state=%s", blk_mq_rq_state_name(blk_mq_rq_state(rq)));
	seq_म_लिखो(m, ", .tag=%d, .internal_tag=%d", rq->tag,
		   rq->पूर्णांकernal_tag);
	अगर (mq_ops->show_rq)
		mq_ops->show_rq(m, rq);
	seq_माला_दो(m, "}\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__blk_mq_debugfs_rq_show);

पूर्णांक blk_mq_debugfs_rq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	वापस __blk_mq_debugfs_rq_show(m, list_entry_rq(v));
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_debugfs_rq_show);

अटल व्योम *hctx_dispatch_start(काष्ठा seq_file *m, loff_t *pos)
	__acquires(&hctx->lock)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;

	spin_lock(&hctx->lock);
	वापस seq_list_start(&hctx->dispatch, *pos);
पूर्ण

अटल व्योम *hctx_dispatch_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;

	वापस seq_list_next(v, &hctx->dispatch, pos);
पूर्ण

अटल व्योम hctx_dispatch_stop(काष्ठा seq_file *m, व्योम *v)
	__releases(&hctx->lock)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = m->निजी;

	spin_unlock(&hctx->lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations hctx_dispatch_seq_ops = अणु
	.start	= hctx_dispatch_start,
	.next	= hctx_dispatch_next,
	.stop	= hctx_dispatch_stop,
	.show	= blk_mq_debugfs_rq_show,
पूर्ण;

काष्ठा show_busy_params अणु
	काष्ठा seq_file		*m;
	काष्ठा blk_mq_hw_ctx	*hctx;
पूर्ण;

/*
 * Note: the state of a request may change जबतक this function is in progress,
 * e.g. due to a concurrent blk_mq_finish_request() call. Returns true to
 * keep iterating requests.
 */
अटल bool hctx_show_busy_rq(काष्ठा request *rq, व्योम *data, bool reserved)
अणु
	स्थिर काष्ठा show_busy_params *params = data;

	अगर (rq->mq_hctx == params->hctx)
		__blk_mq_debugfs_rq_show(params->m, rq);

	वापस true;
पूर्ण

अटल पूर्णांक hctx_busy_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा show_busy_params params = अणु .m = m, .hctx = hctx पूर्ण;

	blk_mq_tagset_busy_iter(hctx->queue->tag_set, hctx_show_busy_rq,
				&params);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *स्थिर hctx_types[] = अणु
	[HCTX_TYPE_DEFAULT]	= "default",
	[HCTX_TYPE_READ]	= "read",
	[HCTX_TYPE_POLL]	= "poll",
पूर्ण;

अटल पूर्णांक hctx_type_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	BUILD_BUG_ON(ARRAY_SIZE(hctx_types) != HCTX_MAX_TYPES);
	seq_म_लिखो(m, "%s\n", hctx_types[hctx->type]);
	वापस 0;
पूर्ण

अटल पूर्णांक hctx_ctx_map_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	sbiपंचांगap_biपंचांगap_show(&hctx->ctx_map, m);
	वापस 0;
पूर्ण

अटल व्योम blk_mq_debugfs_tags_show(काष्ठा seq_file *m,
				     काष्ठा blk_mq_tags *tags)
अणु
	seq_म_लिखो(m, "nr_tags=%u\n", tags->nr_tags);
	seq_म_लिखो(m, "nr_reserved_tags=%u\n", tags->nr_reserved_tags);
	seq_म_लिखो(m, "active_queues=%d\n",
		   atomic_पढ़ो(&tags->active_queues));

	seq_माला_दो(m, "\nbitmap_tags:\n");
	sbiपंचांगap_queue_show(tags->biपंचांगap_tags, m);

	अगर (tags->nr_reserved_tags) अणु
		seq_माला_दो(m, "\nbreserved_tags:\n");
		sbiपंचांगap_queue_show(tags->breserved_tags, m);
	पूर्ण
पूर्ण

अटल पूर्णांक hctx_tags_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा request_queue *q = hctx->queue;
	पूर्णांक res;

	res = mutex_lock_पूर्णांकerruptible(&q->sysfs_lock);
	अगर (res)
		जाओ out;
	अगर (hctx->tags)
		blk_mq_debugfs_tags_show(m, hctx->tags);
	mutex_unlock(&q->sysfs_lock);

out:
	वापस res;
पूर्ण

अटल पूर्णांक hctx_tags_biपंचांगap_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा request_queue *q = hctx->queue;
	पूर्णांक res;

	res = mutex_lock_पूर्णांकerruptible(&q->sysfs_lock);
	अगर (res)
		जाओ out;
	अगर (hctx->tags)
		sbiपंचांगap_biपंचांगap_show(&hctx->tags->biपंचांगap_tags->sb, m);
	mutex_unlock(&q->sysfs_lock);

out:
	वापस res;
पूर्ण

अटल पूर्णांक hctx_sched_tags_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा request_queue *q = hctx->queue;
	पूर्णांक res;

	res = mutex_lock_पूर्णांकerruptible(&q->sysfs_lock);
	अगर (res)
		जाओ out;
	अगर (hctx->sched_tags)
		blk_mq_debugfs_tags_show(m, hctx->sched_tags);
	mutex_unlock(&q->sysfs_lock);

out:
	वापस res;
पूर्ण

अटल पूर्णांक hctx_sched_tags_biपंचांगap_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	काष्ठा request_queue *q = hctx->queue;
	पूर्णांक res;

	res = mutex_lock_पूर्णांकerruptible(&q->sysfs_lock);
	अगर (res)
		जाओ out;
	अगर (hctx->sched_tags)
		sbiपंचांगap_biपंचांगap_show(&hctx->sched_tags->biपंचांगap_tags->sb, m);
	mutex_unlock(&q->sysfs_lock);

out:
	वापस res;
पूर्ण

अटल पूर्णांक hctx_io_poll_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	seq_म_लिखो(m, "considered=%lu\n", hctx->poll_considered);
	seq_म_लिखो(m, "invoked=%lu\n", hctx->poll_invoked);
	seq_म_लिखो(m, "success=%lu\n", hctx->poll_success);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hctx_io_poll_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	hctx->poll_considered = hctx->poll_invoked = hctx->poll_success = 0;
	वापस count;
पूर्ण

अटल पूर्णांक hctx_dispatched_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	पूर्णांक i;

	seq_म_लिखो(m, "%8u\t%lu\n", 0U, hctx->dispatched[0]);

	क्रम (i = 1; i < BLK_MQ_MAX_DISPATCH_ORDER - 1; i++) अणु
		अचिन्हित पूर्णांक d = 1U << (i - 1);

		seq_म_लिखो(m, "%8u\t%lu\n", d, hctx->dispatched[i]);
	पूर्ण

	seq_म_लिखो(m, "%8u+\t%lu\n", 1U << (i - 1), hctx->dispatched[i]);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hctx_dispatched_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;
	पूर्णांक i;

	क्रम (i = 0; i < BLK_MQ_MAX_DISPATCH_ORDER; i++)
		hctx->dispatched[i] = 0;
	वापस count;
पूर्ण

अटल पूर्णांक hctx_queued_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	seq_म_लिखो(m, "%lu\n", hctx->queued);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hctx_queued_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	hctx->queued = 0;
	वापस count;
पूर्ण

अटल पूर्णांक hctx_run_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	seq_म_लिखो(m, "%lu\n", hctx->run);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार hctx_run_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf, माप_प्रकार count,
			      loff_t *ppos)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	hctx->run = 0;
	वापस count;
पूर्ण

अटल पूर्णांक hctx_active_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	seq_म_लिखो(m, "%d\n", atomic_पढ़ो(&hctx->nr_active));
	वापस 0;
पूर्ण

अटल पूर्णांक hctx_dispatch_busy_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_hw_ctx *hctx = data;

	seq_म_लिखो(m, "%u\n", hctx->dispatch_busy);
	वापस 0;
पूर्ण

#घोषणा CTX_RQ_SEQ_OPS(name, type)					\
अटल व्योम *ctx_##name##_rq_list_start(काष्ठा seq_file *m, loff_t *pos) \
	__acquires(&ctx->lock)						\
अणु									\
	काष्ठा blk_mq_ctx *ctx = m->निजी;				\
									\
	spin_lock(&ctx->lock);						\
	वापस seq_list_start(&ctx->rq_lists[type], *pos);		\
पूर्ण									\
									\
अटल व्योम *ctx_##name##_rq_list_next(काष्ठा seq_file *m, व्योम *v,	\
				     loff_t *pos)			\
अणु									\
	काष्ठा blk_mq_ctx *ctx = m->निजी;				\
									\
	वापस seq_list_next(v, &ctx->rq_lists[type], pos);		\
पूर्ण									\
									\
अटल व्योम ctx_##name##_rq_list_stop(काष्ठा seq_file *m, व्योम *v)	\
	__releases(&ctx->lock)						\
अणु									\
	काष्ठा blk_mq_ctx *ctx = m->निजी;				\
									\
	spin_unlock(&ctx->lock);					\
पूर्ण									\
									\
अटल स्थिर काष्ठा seq_operations ctx_##name##_rq_list_seq_ops = अणु	\
	.start	= ctx_##name##_rq_list_start,				\
	.next	= ctx_##name##_rq_list_next,				\
	.stop	= ctx_##name##_rq_list_stop,				\
	.show	= blk_mq_debugfs_rq_show,				\
पूर्ण

CTX_RQ_SEQ_OPS(शेष, HCTX_TYPE_DEFAULT);
CTX_RQ_SEQ_OPS(पढ़ो, HCTX_TYPE_READ);
CTX_RQ_SEQ_OPS(poll, HCTX_TYPE_POLL);

अटल पूर्णांक ctx_dispatched_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	seq_म_लिखो(m, "%lu %lu\n", ctx->rq_dispatched[1], ctx->rq_dispatched[0]);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ctx_dispatched_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	ctx->rq_dispatched[0] = ctx->rq_dispatched[1] = 0;
	वापस count;
पूर्ण

अटल पूर्णांक ctx_merged_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	seq_म_लिखो(m, "%lu\n", ctx->rq_merged);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ctx_merged_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	ctx->rq_merged = 0;
	वापस count;
पूर्ण

अटल पूर्णांक ctx_completed_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	seq_म_लिखो(m, "%lu %lu\n", ctx->rq_completed[1], ctx->rq_completed[0]);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ctx_completed_ग_लिखो(व्योम *data, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा blk_mq_ctx *ctx = data;

	ctx->rq_completed[0] = ctx->rq_completed[1] = 0;
	वापस count;
पूर्ण

अटल पूर्णांक blk_mq_debugfs_show(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर काष्ठा blk_mq_debugfs_attr *attr = m->निजी;
	व्योम *data = d_inode(m->file->f_path.dentry->d_parent)->i_निजी;

	वापस attr->show(data, m);
पूर्ण

अटल sमाप_प्रकार blk_mq_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	स्थिर काष्ठा blk_mq_debugfs_attr *attr = m->निजी;
	व्योम *data = d_inode(file->f_path.dentry->d_parent)->i_निजी;

	/*
	 * Attributes that only implement .seq_ops are पढ़ो-only and 'attr' is
	 * the same with 'data' in this हाल.
	 */
	अगर (attr == data || !attr->ग_लिखो)
		वापस -EPERM;

	वापस attr->ग_लिखो(data, buf, count, ppos);
पूर्ण

अटल पूर्णांक blk_mq_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा blk_mq_debugfs_attr *attr = inode->i_निजी;
	व्योम *data = d_inode(file->f_path.dentry->d_parent)->i_निजी;
	काष्ठा seq_file *m;
	पूर्णांक ret;

	अगर (attr->seq_ops) अणु
		ret = seq_खोलो(file, attr->seq_ops);
		अगर (!ret) अणु
			m = file->निजी_data;
			m->निजी = data;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (WARN_ON_ONCE(!attr->show))
		वापस -EPERM;

	वापस single_खोलो(file, blk_mq_debugfs_show, inode->i_निजी);
पूर्ण

अटल पूर्णांक blk_mq_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	स्थिर काष्ठा blk_mq_debugfs_attr *attr = inode->i_निजी;

	अगर (attr->show)
		वापस single_release(inode, file);

	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations blk_mq_debugfs_fops = अणु
	.खोलो		= blk_mq_debugfs_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= blk_mq_debugfs_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= blk_mq_debugfs_release,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_debugfs_attr blk_mq_debugfs_hctx_attrs[] = अणु
	अणु"state", 0400, hctx_state_showपूर्ण,
	अणु"flags", 0400, hctx_flags_showपूर्ण,
	अणु"dispatch", 0400, .seq_ops = &hctx_dispatch_seq_opsपूर्ण,
	अणु"busy", 0400, hctx_busy_showपूर्ण,
	अणु"ctx_map", 0400, hctx_ctx_map_showपूर्ण,
	अणु"tags", 0400, hctx_tags_showपूर्ण,
	अणु"tags_bitmap", 0400, hctx_tags_biपंचांगap_showपूर्ण,
	अणु"sched_tags", 0400, hctx_sched_tags_showपूर्ण,
	अणु"sched_tags_bitmap", 0400, hctx_sched_tags_biपंचांगap_showपूर्ण,
	अणु"io_poll", 0600, hctx_io_poll_show, hctx_io_poll_ग_लिखोपूर्ण,
	अणु"dispatched", 0600, hctx_dispatched_show, hctx_dispatched_ग_लिखोपूर्ण,
	अणु"queued", 0600, hctx_queued_show, hctx_queued_ग_लिखोपूर्ण,
	अणु"run", 0600, hctx_run_show, hctx_run_ग_लिखोपूर्ण,
	अणु"active", 0400, hctx_active_showपूर्ण,
	अणु"dispatch_busy", 0400, hctx_dispatch_busy_showपूर्ण,
	अणु"type", 0400, hctx_type_showपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_debugfs_attr blk_mq_debugfs_ctx_attrs[] = अणु
	अणु"default_rq_list", 0400, .seq_ops = &ctx_शेष_rq_list_seq_opsपूर्ण,
	अणु"read_rq_list", 0400, .seq_ops = &ctx_पढ़ो_rq_list_seq_opsपूर्ण,
	अणु"poll_rq_list", 0400, .seq_ops = &ctx_poll_rq_list_seq_opsपूर्ण,
	अणु"dispatched", 0600, ctx_dispatched_show, ctx_dispatched_ग_लिखोपूर्ण,
	अणु"merged", 0600, ctx_merged_show, ctx_merged_ग_लिखोपूर्ण,
	अणु"completed", 0600, ctx_completed_show, ctx_completed_ग_लिखोपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम debugfs_create_files(काष्ठा dentry *parent, व्योम *data,
				 स्थिर काष्ठा blk_mq_debugfs_attr *attr)
अणु
	अगर (IS_ERR_OR_शून्य(parent))
		वापस;

	d_inode(parent)->i_निजी = data;

	क्रम (; attr->name; attr++)
		debugfs_create_file(attr->name, attr->mode, parent,
				    (व्योम *)attr, &blk_mq_debugfs_fops);
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	debugfs_create_files(q->debugfs_dir, q, blk_mq_debugfs_queue_attrs);

	/*
	 * blk_mq_init_sched() attempted to करो this alपढ़ोy, but q->debugfs_dir
	 * didn't exist yet (because we don't know what to name the directory
	 * until the queue is रेजिस्टरed to a gendisk).
	 */
	अगर (q->elevator && !q->sched_debugfs_dir)
		blk_mq_debugfs_रेजिस्टर_sched(q);

	/* Similarly, blk_mq_init_hctx() couldn't करो this previously. */
	queue_क्रम_each_hw_ctx(q, hctx, i) अणु
		अगर (!hctx->debugfs_dir)
			blk_mq_debugfs_रेजिस्टर_hctx(q, hctx);
		अगर (q->elevator && !hctx->sched_debugfs_dir)
			blk_mq_debugfs_रेजिस्टर_sched_hctx(q, hctx);
	पूर्ण

	अगर (q->rq_qos) अणु
		काष्ठा rq_qos *rqos = q->rq_qos;

		जबतक (rqos) अणु
			blk_mq_debugfs_रेजिस्टर_rqos(rqos);
			rqos = rqos->next;
		पूर्ण
	पूर्ण
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर(काष्ठा request_queue *q)
अणु
	q->sched_debugfs_dir = शून्य;
पूर्ण

अटल व्योम blk_mq_debugfs_रेजिस्टर_ctx(काष्ठा blk_mq_hw_ctx *hctx,
					काष्ठा blk_mq_ctx *ctx)
अणु
	काष्ठा dentry *ctx_dir;
	अक्षर name[20];

	snम_लिखो(name, माप(name), "cpu%u", ctx->cpu);
	ctx_dir = debugfs_create_dir(name, hctx->debugfs_dir);

	debugfs_create_files(ctx_dir, ctx, blk_mq_debugfs_ctx_attrs);
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर_hctx(काष्ठा request_queue *q,
				  काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा blk_mq_ctx *ctx;
	अक्षर name[20];
	पूर्णांक i;

	snम_लिखो(name, माप(name), "hctx%u", hctx->queue_num);
	hctx->debugfs_dir = debugfs_create_dir(name, q->debugfs_dir);

	debugfs_create_files(hctx->debugfs_dir, hctx, blk_mq_debugfs_hctx_attrs);

	hctx_क्रम_each_ctx(hctx, ctx, i)
		blk_mq_debugfs_रेजिस्टर_ctx(hctx, ctx);
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	debugfs_हटाओ_recursive(hctx->debugfs_dir);
	hctx->sched_debugfs_dir = शून्य;
	hctx->debugfs_dir = शून्य;
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर_hctxs(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_debugfs_रेजिस्टर_hctx(q, hctx);
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_hctxs(काष्ठा request_queue *q)
अणु
	काष्ठा blk_mq_hw_ctx *hctx;
	पूर्णांक i;

	queue_क्रम_each_hw_ctx(q, hctx, i)
		blk_mq_debugfs_unरेजिस्टर_hctx(hctx);
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर_sched(काष्ठा request_queue *q)
अणु
	काष्ठा elevator_type *e = q->elevator->type;

	/*
	 * If the parent directory has not been created yet, वापस, we will be
	 * called again later on and the directory/files will be created then.
	 */
	अगर (!q->debugfs_dir)
		वापस;

	अगर (!e->queue_debugfs_attrs)
		वापस;

	q->sched_debugfs_dir = debugfs_create_dir("sched", q->debugfs_dir);

	debugfs_create_files(q->sched_debugfs_dir, q, e->queue_debugfs_attrs);
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_sched(काष्ठा request_queue *q)
अणु
	debugfs_हटाओ_recursive(q->sched_debugfs_dir);
	q->sched_debugfs_dir = शून्य;
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_rqos(काष्ठा rq_qos *rqos)
अणु
	debugfs_हटाओ_recursive(rqos->debugfs_dir);
	rqos->debugfs_dir = शून्य;
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर_rqos(काष्ठा rq_qos *rqos)
अणु
	काष्ठा request_queue *q = rqos->q;
	स्थिर अक्षर *dir_name = rq_qos_id_to_name(rqos->id);

	अगर (rqos->debugfs_dir || !rqos->ops->debugfs_attrs)
		वापस;

	अगर (!q->rqos_debugfs_dir)
		q->rqos_debugfs_dir = debugfs_create_dir("rqos",
							 q->debugfs_dir);

	rqos->debugfs_dir = debugfs_create_dir(dir_name,
					       rqos->q->rqos_debugfs_dir);

	debugfs_create_files(rqos->debugfs_dir, rqos, rqos->ops->debugfs_attrs);
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_queue_rqos(काष्ठा request_queue *q)
अणु
	debugfs_हटाओ_recursive(q->rqos_debugfs_dir);
	q->rqos_debugfs_dir = शून्य;
पूर्ण

व्योम blk_mq_debugfs_रेजिस्टर_sched_hctx(काष्ठा request_queue *q,
					काष्ठा blk_mq_hw_ctx *hctx)
अणु
	काष्ठा elevator_type *e = q->elevator->type;

	/*
	 * If the parent debugfs directory has not been created yet, वापस;
	 * We will be called again later on with appropriate parent debugfs
	 * directory from blk_रेजिस्टर_queue()
	 */
	अगर (!hctx->debugfs_dir)
		वापस;

	अगर (!e->hctx_debugfs_attrs)
		वापस;

	hctx->sched_debugfs_dir = debugfs_create_dir("sched",
						     hctx->debugfs_dir);
	debugfs_create_files(hctx->sched_debugfs_dir, hctx,
			     e->hctx_debugfs_attrs);
पूर्ण

व्योम blk_mq_debugfs_unरेजिस्टर_sched_hctx(काष्ठा blk_mq_hw_ctx *hctx)
अणु
	debugfs_हटाओ_recursive(hctx->sched_debugfs_dir);
	hctx->sched_debugfs_dir = शून्य;
पूर्ण
