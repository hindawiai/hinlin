<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sch_plug.c Queue traffic until an explicit release command
 *
 * There are two ways to use this qdisc:
 * 1. A simple "instantaneous" plug/unplug operation, by issuing an alternating
 *    sequence of TCQ_PLUG_BUFFER & TCQ_PLUG_RELEASE_INDEFINITE commands.
 *
 * 2. For network output buffering (a.k.a output commit) functionality.
 *    Output commit property is commonly used by applications using checkpoपूर्णांक
 *    based fault-tolerance to ensure that the checkpoपूर्णांक from which a प्रणाली
 *    is being restored is consistent w.r.t outside world.
 *
 *    Consider क्रम e.g. Remus - a Virtual Machine checkpoपूर्णांकing प्रणाली,
 *    wherein a VM is checkpoपूर्णांकed, say every 50ms. The checkpoपूर्णांक is replicated
 *    asynchronously to the backup host, जबतक the VM जारीs executing the
 *    next epoch speculatively.
 *
 *    The following is a typical sequence of output buffer operations:
 *       1.At epoch i, start_buffer(i)
 *       2. At end of epoch i (i.e. after 50ms):
 *          2.1 Stop VM and take checkpoपूर्णांक(i).
 *          2.2 start_buffer(i+1) and Resume VM
 *       3. While speculatively executing epoch(i+1), asynchronously replicate
 *          checkpoपूर्णांक(i) to backup host.
 *       4. When checkpoपूर्णांक_ack(i) is received from backup, release_buffer(i)
 *    Thus, this Qdisc would receive the following sequence of commands:
 *       TCQ_PLUG_BUFFER (epoch i)
 *       .. TCQ_PLUG_BUFFER (epoch i+1)
 *       ....TCQ_PLUG_RELEASE_ONE (epoch i)
 *       ......TCQ_PLUG_BUFFER (epoch i+2)
 *       ........
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <net/pkt_sched.h>

/*
 * State of the queue, when used क्रम network output buffering:
 *
 *                 plug(i+1)            plug(i)          head
 * ------------------+--------------------+---------------->
 *                   |                    |
 *                   |                    |
 * pkts_current_epoch| pkts_last_epoch    |pkts_to_release
 * ----------------->|<--------+--------->|+--------------->
 *                   v                    v
 *
 */

काष्ठा plug_sched_data अणु
	/* If true, the dequeue function releases all packets
	 * from head to end of the queue. The queue turns पूर्णांकo
	 * a pass-through queue क्रम newly arriving packets.
	 */
	bool unplug_indefinite;

	bool throttled;

	/* Queue Limit in bytes */
	u32 limit;

	/* Number of packets (output) from the current speculatively
	 * executing epoch.
	 */
	u32 pkts_current_epoch;

	/* Number of packets corresponding to the recently finished
	 * epoch. These will be released when we receive a
	 * TCQ_PLUG_RELEASE_ONE command. This command is typically
	 * issued after committing a checkpoपूर्णांक at the target.
	 */
	u32 pkts_last_epoch;

	/*
	 * Number of packets from the head of the queue, that can
	 * be released (committed checkpoपूर्णांक).
	 */
	u32 pkts_to_release;
पूर्ण;

अटल पूर्णांक plug_enqueue(काष्ठा sk_buff *skb, काष्ठा Qdisc *sch,
			काष्ठा sk_buff **to_मुक्त)
अणु
	काष्ठा plug_sched_data *q = qdisc_priv(sch);

	अगर (likely(sch->qstats.backlog + skb->len <= q->limit)) अणु
		अगर (!q->unplug_indefinite)
			q->pkts_current_epoch++;
		वापस qdisc_enqueue_tail(skb, sch);
	पूर्ण

	वापस qdisc_drop(skb, sch, to_मुक्त);
पूर्ण

अटल काष्ठा sk_buff *plug_dequeue(काष्ठा Qdisc *sch)
अणु
	काष्ठा plug_sched_data *q = qdisc_priv(sch);

	अगर (q->throttled)
		वापस शून्य;

	अगर (!q->unplug_indefinite) अणु
		अगर (!q->pkts_to_release) अणु
			/* No more packets to dequeue. Block the queue
			 * and रुको क्रम the next release command.
			 */
			q->throttled = true;
			वापस शून्य;
		पूर्ण
		q->pkts_to_release--;
	पूर्ण

	वापस qdisc_dequeue_head(sch);
पूर्ण

अटल पूर्णांक plug_init(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा plug_sched_data *q = qdisc_priv(sch);

	q->pkts_current_epoch = 0;
	q->pkts_last_epoch = 0;
	q->pkts_to_release = 0;
	q->unplug_indefinite = false;

	अगर (opt == शून्य) अणु
		q->limit = qdisc_dev(sch)->tx_queue_len
		           * psched_mtu(qdisc_dev(sch));
	पूर्ण अन्यथा अणु
		काष्ठा tc_plug_qopt *ctl = nla_data(opt);

		अगर (nla_len(opt) < माप(*ctl))
			वापस -EINVAL;

		q->limit = ctl->limit;
	पूर्ण

	q->throttled = true;
	वापस 0;
पूर्ण

/* Receives 4 types of messages:
 * TCQ_PLUG_BUFFER: Inset a plug पूर्णांकo the queue and
 *  buffer any incoming packets
 * TCQ_PLUG_RELEASE_ONE: Dequeue packets from queue head
 *   to beginning of the next plug.
 * TCQ_PLUG_RELEASE_INDEFINITE: Dequeue all packets from queue.
 *   Stop buffering packets until the next TCQ_PLUG_BUFFER
 *   command is received (just act as a pass-thru queue).
 * TCQ_PLUG_LIMIT: Increase/decrease queue size
 */
अटल पूर्णांक plug_change(काष्ठा Qdisc *sch, काष्ठा nlattr *opt,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा plug_sched_data *q = qdisc_priv(sch);
	काष्ठा tc_plug_qopt *msg;

	अगर (opt == शून्य)
		वापस -EINVAL;

	msg = nla_data(opt);
	अगर (nla_len(opt) < माप(*msg))
		वापस -EINVAL;

	चयन (msg->action) अणु
	हाल TCQ_PLUG_BUFFER:
		/* Save size of the current buffer */
		q->pkts_last_epoch = q->pkts_current_epoch;
		q->pkts_current_epoch = 0;
		अगर (q->unplug_indefinite)
			q->throttled = true;
		q->unplug_indefinite = false;
		अवरोध;
	हाल TCQ_PLUG_RELEASE_ONE:
		/* Add packets from the last complete buffer to the
		 * packets to be released set.
		 */
		q->pkts_to_release += q->pkts_last_epoch;
		q->pkts_last_epoch = 0;
		q->throttled = false;
		netअगर_schedule_queue(sch->dev_queue);
		अवरोध;
	हाल TCQ_PLUG_RELEASE_INDEFINITE:
		q->unplug_indefinite = true;
		q->pkts_to_release = 0;
		q->pkts_last_epoch = 0;
		q->pkts_current_epoch = 0;
		q->throttled = false;
		netअगर_schedule_queue(sch->dev_queue);
		अवरोध;
	हाल TCQ_PLUG_LIMIT:
		/* Limit is supplied in bytes */
		q->limit = msg->limit;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा Qdisc_ops plug_qdisc_ops __पढ़ो_mostly = अणु
	.id          =       "plug",
	.priv_size   =       माप(काष्ठा plug_sched_data),
	.enqueue     =       plug_enqueue,
	.dequeue     =       plug_dequeue,
	.peek        =       qdisc_peek_head,
	.init        =       plug_init,
	.change      =       plug_change,
	.reset       =	     qdisc_reset_queue,
	.owner       =       THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init plug_module_init(व्योम)
अणु
	वापस रेजिस्टर_qdisc(&plug_qdisc_ops);
पूर्ण

अटल व्योम __निकास plug_module_निकास(व्योम)
अणु
	unरेजिस्टर_qdisc(&plug_qdisc_ops);
पूर्ण
module_init(plug_module_init)
module_निकास(plug_module_निकास)
MODULE_LICENSE("GPL");
