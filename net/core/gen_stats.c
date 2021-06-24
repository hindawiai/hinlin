<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/gen_stats.c
 *
 * Authors:  Thomas Graf <tgraf@suug.ch>
 *           Jamal Hadi Salim
 *           Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 * See Documentation/networking/gen_stats.rst
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/socket.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/gen_stats.h>
#समावेश <net/netlink.h>
#समावेश <net/gen_stats.h>


अटल अंतरभूत पूर्णांक
gnet_stats_copy(काष्ठा gnet_dump *d, पूर्णांक type, व्योम *buf, पूर्णांक size, पूर्णांक padattr)
अणु
	अगर (nla_put_64bit(d->skb, type, size, buf, padattr))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	अगर (d->lock)
		spin_unlock_bh(d->lock);
	kमुक्त(d->xstats);
	d->xstats = शून्य;
	d->xstats_len = 0;
	वापस -1;
पूर्ण

/**
 * gnet_stats_start_copy_compat - start dumping procedure in compatibility mode
 * @skb: socket buffer to put statistics TLVs पूर्णांकo
 * @type: TLV type क्रम top level statistic TLV
 * @tc_stats_type: TLV type क्रम backward compatibility काष्ठा tc_stats TLV
 * @xstats_type: TLV type क्रम backward compatibility xstats TLV
 * @lock: statistics lock
 * @d: dumping handle
 * @padattr: padding attribute
 *
 * Initializes the dumping handle, grअसल the statistic lock and appends
 * an empty TLV header to the socket buffer क्रम use a container क्रम all
 * other statistic TLVS.
 *
 * The dumping handle is marked to be in backward compatibility mode telling
 * all gnet_stats_copy_XXX() functions to fill a local copy of काष्ठा tc_stats.
 *
 * Returns 0 on success or -1 अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_start_copy_compat(काष्ठा sk_buff *skb, पूर्णांक type, पूर्णांक tc_stats_type,
			     पूर्णांक xstats_type, spinlock_t *lock,
			     काष्ठा gnet_dump *d, पूर्णांक padattr)
	__acquires(lock)
अणु
	स_रखो(d, 0, माप(*d));

	अगर (type)
		d->tail = (काष्ठा nlattr *)skb_tail_poपूर्णांकer(skb);
	d->skb = skb;
	d->compat_tc_stats = tc_stats_type;
	d->compat_xstats = xstats_type;
	d->padattr = padattr;
	अगर (lock) अणु
		d->lock = lock;
		spin_lock_bh(lock);
	पूर्ण
	अगर (d->tail) अणु
		पूर्णांक ret = gnet_stats_copy(d, type, शून्य, 0, padattr);

		/* The initial attribute added in gnet_stats_copy() may be
		 * preceded by a padding attribute, in which हाल d->tail will
		 * end up poपूर्णांकing at the padding instead of the real attribute.
		 * Fix this so gnet_stats_finish_copy() adjusts the length of
		 * the right attribute.
		 */
		अगर (ret == 0 && d->tail->nla_type == padattr)
			d->tail = (काष्ठा nlattr *)((अक्षर *)d->tail +
						    NLA_ALIGN(d->tail->nla_len));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gnet_stats_start_copy_compat);

/**
 * gnet_stats_start_copy - start dumping procedure in compatibility mode
 * @skb: socket buffer to put statistics TLVs पूर्णांकo
 * @type: TLV type क्रम top level statistic TLV
 * @lock: statistics lock
 * @d: dumping handle
 * @padattr: padding attribute
 *
 * Initializes the dumping handle, grअसल the statistic lock and appends
 * an empty TLV header to the socket buffer क्रम use a container क्रम all
 * other statistic TLVS.
 *
 * Returns 0 on success or -1 अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_start_copy(काष्ठा sk_buff *skb, पूर्णांक type, spinlock_t *lock,
		      काष्ठा gnet_dump *d, पूर्णांक padattr)
अणु
	वापस gnet_stats_start_copy_compat(skb, type, 0, 0, lock, d, padattr);
पूर्ण
EXPORT_SYMBOL(gnet_stats_start_copy);

अटल व्योम
__gnet_stats_copy_basic_cpu(काष्ठा gnet_stats_basic_packed *bstats,
			    काष्ठा gnet_stats_basic_cpu __percpu *cpu)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा gnet_stats_basic_cpu *bcpu = per_cpu_ptr(cpu, i);
		अचिन्हित पूर्णांक start;
		u64 bytes, packets;

		करो अणु
			start = u64_stats_fetch_begin_irq(&bcpu->syncp);
			bytes = bcpu->bstats.bytes;
			packets = bcpu->bstats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&bcpu->syncp, start));

		bstats->bytes += bytes;
		bstats->packets += packets;
	पूर्ण
पूर्ण

व्योम
__gnet_stats_copy_basic(स्थिर seqcount_t *running,
			काष्ठा gnet_stats_basic_packed *bstats,
			काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			काष्ठा gnet_stats_basic_packed *b)
अणु
	अचिन्हित पूर्णांक seq;

	अगर (cpu) अणु
		__gnet_stats_copy_basic_cpu(bstats, cpu);
		वापस;
	पूर्ण
	करो अणु
		अगर (running)
			seq = पढ़ो_seqcount_begin(running);
		bstats->bytes = b->bytes;
		bstats->packets = b->packets;
	पूर्ण जबतक (running && पढ़ो_seqcount_retry(running, seq));
पूर्ण
EXPORT_SYMBOL(__gnet_stats_copy_basic);

अटल पूर्णांक
___gnet_stats_copy_basic(स्थिर seqcount_t *running,
			 काष्ठा gnet_dump *d,
			 काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			 काष्ठा gnet_stats_basic_packed *b,
			 पूर्णांक type)
अणु
	काष्ठा gnet_stats_basic_packed bstats = अणु0पूर्ण;

	__gnet_stats_copy_basic(running, &bstats, cpu, b);

	अगर (d->compat_tc_stats && type == TCA_STATS_BASIC) अणु
		d->tc_stats.bytes = bstats.bytes;
		d->tc_stats.packets = bstats.packets;
	पूर्ण

	अगर (d->tail) अणु
		काष्ठा gnet_stats_basic sb;
		पूर्णांक res;

		स_रखो(&sb, 0, माप(sb));
		sb.bytes = bstats.bytes;
		sb.packets = bstats.packets;
		res = gnet_stats_copy(d, type, &sb, माप(sb), TCA_STATS_PAD);
		अगर (res < 0 || sb.packets == bstats.packets)
			वापस res;
		/* emit 64bit stats only अगर needed */
		वापस gnet_stats_copy(d, TCA_STATS_PKT64, &bstats.packets,
				       माप(bstats.packets), TCA_STATS_PAD);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * gnet_stats_copy_basic - copy basic statistics पूर्णांकo statistic TLV
 * @running: seqcount_t poपूर्णांकer
 * @d: dumping handle
 * @cpu: copy statistic per cpu
 * @b: basic statistics
 *
 * Appends the basic statistics to the top level TLV created by
 * gnet_stats_start_copy().
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_copy_basic(स्थिर seqcount_t *running,
		      काष्ठा gnet_dump *d,
		      काष्ठा gnet_stats_basic_cpu __percpu *cpu,
		      काष्ठा gnet_stats_basic_packed *b)
अणु
	वापस ___gnet_stats_copy_basic(running, d, cpu, b,
					TCA_STATS_BASIC);
पूर्ण
EXPORT_SYMBOL(gnet_stats_copy_basic);

/**
 * gnet_stats_copy_basic_hw - copy basic hw statistics पूर्णांकo statistic TLV
 * @running: seqcount_t poपूर्णांकer
 * @d: dumping handle
 * @cpu: copy statistic per cpu
 * @b: basic statistics
 *
 * Appends the basic statistics to the top level TLV created by
 * gnet_stats_start_copy().
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_copy_basic_hw(स्थिर seqcount_t *running,
			 काष्ठा gnet_dump *d,
			 काष्ठा gnet_stats_basic_cpu __percpu *cpu,
			 काष्ठा gnet_stats_basic_packed *b)
अणु
	वापस ___gnet_stats_copy_basic(running, d, cpu, b,
					TCA_STATS_BASIC_HW);
पूर्ण
EXPORT_SYMBOL(gnet_stats_copy_basic_hw);

/**
 * gnet_stats_copy_rate_est - copy rate estimator statistics पूर्णांकo statistics TLV
 * @d: dumping handle
 * @rate_est: rate estimator
 *
 * Appends the rate estimator statistics to the top level TLV created by
 * gnet_stats_start_copy().
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_copy_rate_est(काष्ठा gnet_dump *d,
			 काष्ठा net_rate_estimator __rcu **rate_est)
अणु
	काष्ठा gnet_stats_rate_est64 sample;
	काष्ठा gnet_stats_rate_est est;
	पूर्णांक res;

	अगर (!gen_estimator_पढ़ो(rate_est, &sample))
		वापस 0;
	est.bps = min_t(u64, अच_पूर्णांक_उच्च, sample.bps);
	/* we have some समय beक्रमe reaching 2^32 packets per second */
	est.pps = sample.pps;

	अगर (d->compat_tc_stats) अणु
		d->tc_stats.bps = est.bps;
		d->tc_stats.pps = est.pps;
	पूर्ण

	अगर (d->tail) अणु
		res = gnet_stats_copy(d, TCA_STATS_RATE_EST, &est, माप(est),
				      TCA_STATS_PAD);
		अगर (res < 0 || est.bps == sample.bps)
			वापस res;
		/* emit 64bit stats only अगर needed */
		वापस gnet_stats_copy(d, TCA_STATS_RATE_EST64, &sample,
				       माप(sample), TCA_STATS_PAD);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gnet_stats_copy_rate_est);

अटल व्योम
__gnet_stats_copy_queue_cpu(काष्ठा gnet_stats_queue *qstats,
			    स्थिर काष्ठा gnet_stats_queue __percpu *q)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा gnet_stats_queue *qcpu = per_cpu_ptr(q, i);

		qstats->qlen = 0;
		qstats->backlog += qcpu->backlog;
		qstats->drops += qcpu->drops;
		qstats->requeues += qcpu->requeues;
		qstats->overlimits += qcpu->overlimits;
	पूर्ण
पूर्ण

व्योम __gnet_stats_copy_queue(काष्ठा gnet_stats_queue *qstats,
			     स्थिर काष्ठा gnet_stats_queue __percpu *cpu,
			     स्थिर काष्ठा gnet_stats_queue *q,
			     __u32 qlen)
अणु
	अगर (cpu) अणु
		__gnet_stats_copy_queue_cpu(qstats, cpu);
	पूर्ण अन्यथा अणु
		qstats->qlen = q->qlen;
		qstats->backlog = q->backlog;
		qstats->drops = q->drops;
		qstats->requeues = q->requeues;
		qstats->overlimits = q->overlimits;
	पूर्ण

	qstats->qlen = qlen;
पूर्ण
EXPORT_SYMBOL(__gnet_stats_copy_queue);

/**
 * gnet_stats_copy_queue - copy queue statistics पूर्णांकo statistics TLV
 * @d: dumping handle
 * @cpu_q: per cpu queue statistics
 * @q: queue statistics
 * @qlen: queue length statistics
 *
 * Appends the queue statistics to the top level TLV created by
 * gnet_stats_start_copy(). Using per cpu queue statistics अगर
 * they are available.
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_copy_queue(काष्ठा gnet_dump *d,
		      काष्ठा gnet_stats_queue __percpu *cpu_q,
		      काष्ठा gnet_stats_queue *q, __u32 qlen)
अणु
	काष्ठा gnet_stats_queue qstats = अणु0पूर्ण;

	__gnet_stats_copy_queue(&qstats, cpu_q, q, qlen);

	अगर (d->compat_tc_stats) अणु
		d->tc_stats.drops = qstats.drops;
		d->tc_stats.qlen = qstats.qlen;
		d->tc_stats.backlog = qstats.backlog;
		d->tc_stats.overlimits = qstats.overlimits;
	पूर्ण

	अगर (d->tail)
		वापस gnet_stats_copy(d, TCA_STATS_QUEUE,
				       &qstats, माप(qstats),
				       TCA_STATS_PAD);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(gnet_stats_copy_queue);

/**
 * gnet_stats_copy_app - copy application specअगरic statistics पूर्णांकo statistics TLV
 * @d: dumping handle
 * @st: application specअगरic statistics data
 * @len: length of data
 *
 * Appends the application specअगरic statistics to the top level TLV created by
 * gnet_stats_start_copy() and remembers the data क्रम XSTATS अगर the dumping
 * handle is in backward compatibility mode.
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_copy_app(काष्ठा gnet_dump *d, व्योम *st, पूर्णांक len)
अणु
	अगर (d->compat_xstats) अणु
		d->xstats = kmemdup(st, len, GFP_ATOMIC);
		अगर (!d->xstats)
			जाओ err_out;
		d->xstats_len = len;
	पूर्ण

	अगर (d->tail)
		वापस gnet_stats_copy(d, TCA_STATS_APP, st, len,
				       TCA_STATS_PAD);

	वापस 0;

err_out:
	अगर (d->lock)
		spin_unlock_bh(d->lock);
	d->xstats_len = 0;
	वापस -1;
पूर्ण
EXPORT_SYMBOL(gnet_stats_copy_app);

/**
 * gnet_stats_finish_copy - finish dumping procedure
 * @d: dumping handle
 *
 * Corrects the length of the top level TLV to include all TLVs added
 * by gnet_stats_copy_XXX() calls. Adds the backward compatibility TLVs
 * अगर gnet_stats_start_copy_compat() was used and releases the statistics
 * lock.
 *
 * Returns 0 on success or -1 with the statistic lock released
 * अगर the room in the socket buffer was not sufficient.
 */
पूर्णांक
gnet_stats_finish_copy(काष्ठा gnet_dump *d)
अणु
	अगर (d->tail)
		d->tail->nla_len = skb_tail_poपूर्णांकer(d->skb) - (u8 *)d->tail;

	अगर (d->compat_tc_stats)
		अगर (gnet_stats_copy(d, d->compat_tc_stats, &d->tc_stats,
				    माप(d->tc_stats), d->padattr) < 0)
			वापस -1;

	अगर (d->compat_xstats && d->xstats) अणु
		अगर (gnet_stats_copy(d, d->compat_xstats, d->xstats,
				    d->xstats_len, d->padattr) < 0)
			वापस -1;
	पूर्ण

	अगर (d->lock)
		spin_unlock_bh(d->lock);
	kमुक्त(d->xstats);
	d->xstats = शून्य;
	d->xstats_len = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(gnet_stats_finish_copy);
