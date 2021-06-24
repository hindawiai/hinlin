<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* audit.c -- Auditing support
 * Gateway between the kernel (e.g., selinux) and the user-space audit daemon.
 * System-call specअगरic features have moved to auditsc.c
 *
 * Copyright 2003-2007 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * Written by Rickard E. (Rik) Faith <faith@redhat.com>
 *
 * Goals: 1) Integrate fully with Security Modules.
 *	  2) Minimal run-समय overhead:
 *	     a) Minimal when syscall auditing is disabled (audit_enable=0).
 *	     b) Small when syscall auditing is enabled and no audit record
 *		is generated (defer as much work as possible to record
 *		generation समय):
 *		i) context is allocated,
 *		ii) names from getname are stored without a copy, and
 *		iii) inode inक्रमmation stored from path_lookup.
 *	  3) Ability to disable syscall auditing at boot समय (audit=0).
 *	  4) Usable by other parts of the kernel (अगर audit_log* is called,
 *	     then a syscall record will be generated स्वतःmatically क्रम the
 *	     current syscall).
 *	  5) Netlink पूर्णांकerface to user-space.
 *	  6) Support low-overhead kernel-based filtering to minimize the
 *	     inक्रमmation that must be passed to user-space.
 *
 * Audit userspace, करोcumentation, tests, and bug/issue trackers:
 * 	https://github.com/linux-audit
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/file.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pid.h>

#समावेश <linux/audit.h>

#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <linux/skbuff.h>
#अगर_घोषित CONFIG_SECURITY
#समावेश <linux/security.h>
#पूर्ण_अगर
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/pid_namespace.h>
#समावेश <net/netns/generic.h>

#समावेश "audit.h"

/* No auditing will take place until audit_initialized == AUDIT_INITIALIZED.
 * (Initialization happens after skb_init is called.) */
#घोषणा AUDIT_DISABLED		-1
#घोषणा AUDIT_UNINITIALIZED	0
#घोषणा AUDIT_INITIALIZED	1
अटल पूर्णांक	audit_initialized = AUDIT_UNINITIALIZED;

u32		audit_enabled = AUDIT_OFF;
bool		audit_ever_enabled = !!AUDIT_OFF;

EXPORT_SYMBOL_GPL(audit_enabled);

/* Default state when kernel boots without any parameters. */
अटल u32	audit_शेष = AUDIT_OFF;

/* If auditing cannot proceed, audit_failure selects what happens. */
अटल u32	audit_failure = AUDIT_FAIL_PRINTK;

/* निजी audit network namespace index */
अटल अचिन्हित पूर्णांक audit_net_id;

/**
 * काष्ठा audit_net - audit निजी network namespace data
 * @sk: communication socket
 */
काष्ठा audit_net अणु
	काष्ठा sock *sk;
पूर्ण;

/**
 * काष्ठा auditd_connection - kernel/auditd connection state
 * @pid: auditd PID
 * @portid: netlink portid
 * @net: the associated network namespace
 * @rcu: RCU head
 *
 * Description:
 * This काष्ठा is RCU रक्षित; you must either hold the RCU lock क्रम पढ़ोing
 * or the associated spinlock क्रम writing.
 */
काष्ठा auditd_connection अणु
	काष्ठा pid *pid;
	u32 portid;
	काष्ठा net *net;
	काष्ठा rcu_head rcu;
पूर्ण;
अटल काष्ठा auditd_connection __rcu *auditd_conn;
अटल DEFINE_SPINLOCK(auditd_conn_lock);

/* If audit_rate_limit is non-zero, limit the rate of sending audit records
 * to that number per second.  This prevents DoS attacks, but results in
 * audit records being dropped. */
अटल u32	audit_rate_limit;

/* Number of outstanding audit_buffers allowed.
 * When set to zero, this means unlimited. */
अटल u32	audit_backlog_limit = 64;
#घोषणा AUDIT_BACKLOG_WAIT_TIME (60 * HZ)
अटल u32	audit_backlog_रुको_समय = AUDIT_BACKLOG_WAIT_TIME;

/* The identity of the user shutting करोwn the audit प्रणाली. */
अटल kuid_t		audit_sig_uid = INVALID_UID;
अटल pid_t		audit_sig_pid = -1;
अटल u32		audit_sig_sid;

/* Records can be lost in several ways:
   0) [suppressed in audit_alloc]
   1) out of memory in audit_log_start [kदो_स्मृति of काष्ठा audit_buffer]
   2) out of memory in audit_log_move [alloc_skb]
   3) suppressed due to audit_rate_limit
   4) suppressed due to audit_backlog_limit
*/
अटल atomic_t	audit_lost = ATOMIC_INIT(0);

/* Monotonically increasing sum of समय the kernel has spent
 * रुकोing जबतक the backlog limit is exceeded.
 */
अटल atomic_t audit_backlog_रुको_समय_actual = ATOMIC_INIT(0);

/* Hash क्रम inode-based rules */
काष्ठा list_head audit_inode_hash[AUDIT_INODE_BUCKETS];

अटल काष्ठा kmem_cache *audit_buffer_cache;

/* queue msgs to send via kauditd_task */
अटल काष्ठा sk_buff_head audit_queue;
/* queue msgs due to temporary unicast send problems */
अटल काष्ठा sk_buff_head audit_retry_queue;
/* queue msgs रुकोing क्रम new auditd connection */
अटल काष्ठा sk_buff_head audit_hold_queue;

/* queue servicing thपढ़ो */
अटल काष्ठा task_काष्ठा *kauditd_task;
अटल DECLARE_WAIT_QUEUE_HEAD(kauditd_रुको);

/* रुकोqueue क्रम callers who are blocked on the audit backlog */
अटल DECLARE_WAIT_QUEUE_HEAD(audit_backlog_रुको);

अटल काष्ठा audit_features af = अणु.vers = AUDIT_FEATURE_VERSION,
				   .mask = -1,
				   .features = 0,
				   .lock = 0,पूर्ण;

अटल अक्षर *audit_feature_names[2] = अणु
	"only_unset_loginuid",
	"loginuid_immutable",
पूर्ण;

/**
 * काष्ठा audit_ctl_mutex - serialize requests from userspace
 * @lock: the mutex used क्रम locking
 * @owner: the task which owns the lock
 *
 * Description:
 * This is the lock काष्ठा used to ensure we only process userspace requests
 * in an orderly fashion.  We can't simply use a mutex/lock here because we
 * need to track lock ownership so we करोn't end up blocking the lock owner in
 * audit_log_start() or similar.
 */
अटल काष्ठा audit_ctl_mutex अणु
	काष्ठा mutex lock;
	व्योम *owner;
पूर्ण audit_cmd_mutex;

/* AUDIT_बफ_मान is the size of the temporary buffer used क्रम क्रमmatting
 * audit records.  Since prपूर्णांकk uses a 1024 byte buffer, this buffer
 * should be at least that large. */
#घोषणा AUDIT_बफ_मान 1024

/* The audit_buffer is used when क्रमmatting an audit record.  The caller
 * locks briefly to get the record off the मुक्तlist or to allocate the
 * buffer, and locks briefly to send the buffer to the netlink layer or
 * to place it on a transmit queue.  Multiple audit_buffers can be in
 * use simultaneously. */
काष्ठा audit_buffer अणु
	काष्ठा sk_buff       *skb;	/* क्रमmatted skb पढ़ोy to send */
	काष्ठा audit_context *ctx;	/* शून्य or associated context */
	gfp_t		     gfp_mask;
पूर्ण;

काष्ठा audit_reply अणु
	__u32 portid;
	काष्ठा net *net;
	काष्ठा sk_buff *skb;
पूर्ण;

/**
 * auditd_test_task - Check to see अगर a given task is an audit daemon
 * @task: the task to check
 *
 * Description:
 * Return 1 अगर the task is a रेजिस्टरed audit daemon, 0 otherwise.
 */
पूर्णांक auditd_test_task(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक rc;
	काष्ठा auditd_connection *ac;

	rcu_पढ़ो_lock();
	ac = rcu_dereference(auditd_conn);
	rc = (ac && ac->pid == task_tgid(task) ? 1 : 0);
	rcu_पढ़ो_unlock();

	वापस rc;
पूर्ण

/**
 * audit_ctl_lock - Take the audit control lock
 */
व्योम audit_ctl_lock(व्योम)
अणु
	mutex_lock(&audit_cmd_mutex.lock);
	audit_cmd_mutex.owner = current;
पूर्ण

/**
 * audit_ctl_unlock - Drop the audit control lock
 */
व्योम audit_ctl_unlock(व्योम)
अणु
	audit_cmd_mutex.owner = शून्य;
	mutex_unlock(&audit_cmd_mutex.lock);
पूर्ण

/**
 * audit_ctl_owner_current - Test to see अगर the current task owns the lock
 *
 * Description:
 * Return true अगर the current task owns the audit control lock, false अगर it
 * करोesn't own the lock.
 */
अटल bool audit_ctl_owner_current(व्योम)
अणु
	वापस (current == audit_cmd_mutex.owner);
पूर्ण

/**
 * auditd_pid_vnr - Return the auditd PID relative to the namespace
 *
 * Description:
 * Returns the PID in relation to the namespace, 0 on failure.
 */
अटल pid_t auditd_pid_vnr(व्योम)
अणु
	pid_t pid;
	स्थिर काष्ठा auditd_connection *ac;

	rcu_पढ़ो_lock();
	ac = rcu_dereference(auditd_conn);
	अगर (!ac || !ac->pid)
		pid = 0;
	अन्यथा
		pid = pid_vnr(ac->pid);
	rcu_पढ़ो_unlock();

	वापस pid;
पूर्ण

/**
 * audit_get_sk - Return the audit socket क्रम the given network namespace
 * @net: the destination network namespace
 *
 * Description:
 * Returns the sock poपूर्णांकer अगर valid, शून्य otherwise.  The caller must ensure
 * that a reference is held क्रम the network namespace जबतक the sock is in use.
 */
अटल काष्ठा sock *audit_get_sk(स्थिर काष्ठा net *net)
अणु
	काष्ठा audit_net *aunet;

	अगर (!net)
		वापस शून्य;

	aunet = net_generic(net, audit_net_id);
	वापस aunet->sk;
पूर्ण

व्योम audit_panic(स्थिर अक्षर *message)
अणु
	चयन (audit_failure) अणु
	हाल AUDIT_FAIL_SILENT:
		अवरोध;
	हाल AUDIT_FAIL_PRINTK:
		अगर (prपूर्णांकk_ratelimit())
			pr_err("%s\n", message);
		अवरोध;
	हाल AUDIT_FAIL_PANIC:
		panic("audit: %s\n", message);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक audit_rate_check(व्योम)
अणु
	अटल अचिन्हित दीर्घ	last_check = 0;
	अटल पूर्णांक		messages   = 0;
	अटल DEFINE_SPINLOCK(lock);
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		now;
	अचिन्हित दीर्घ		elapsed;
	पूर्णांक			retval	   = 0;

	अगर (!audit_rate_limit) वापस 1;

	spin_lock_irqsave(&lock, flags);
	अगर (++messages < audit_rate_limit) अणु
		retval = 1;
	पूर्ण अन्यथा अणु
		now     = jअगरfies;
		elapsed = now - last_check;
		अगर (elapsed > HZ) अणु
			last_check = now;
			messages   = 0;
			retval     = 1;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&lock, flags);

	वापस retval;
पूर्ण

/**
 * audit_log_lost - conditionally log lost audit message event
 * @message: the message stating reason क्रम lost audit message
 *
 * Emit at least 1 message per second, even अगर audit_rate_check is
 * throttling.
 * Always increment the lost messages counter.
*/
व्योम audit_log_lost(स्थिर अक्षर *message)
अणु
	अटल अचिन्हित दीर्घ	last_msg = 0;
	अटल DEFINE_SPINLOCK(lock);
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		now;
	पूर्णांक			prपूर्णांक;

	atomic_inc(&audit_lost);

	prपूर्णांक = (audit_failure == AUDIT_FAIL_PANIC || !audit_rate_limit);

	अगर (!prपूर्णांक) अणु
		spin_lock_irqsave(&lock, flags);
		now = jअगरfies;
		अगर (now - last_msg > HZ) अणु
			prपूर्णांक = 1;
			last_msg = now;
		पूर्ण
		spin_unlock_irqrestore(&lock, flags);
	पूर्ण

	अगर (prपूर्णांक) अणु
		अगर (prपूर्णांकk_ratelimit())
			pr_warn("audit_lost=%u audit_rate_limit=%u audit_backlog_limit=%u\n",
				atomic_पढ़ो(&audit_lost),
				audit_rate_limit,
				audit_backlog_limit);
		audit_panic(message);
	पूर्ण
पूर्ण

अटल पूर्णांक audit_log_config_change(अक्षर *function_name, u32 new, u32 old,
				   पूर्णांक allow_changes)
अणु
	काष्ठा audit_buffer *ab;
	पूर्णांक rc = 0;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	अगर (unlikely(!ab))
		वापस rc;
	audit_log_क्रमmat(ab, "op=set %s=%u old=%u ", function_name, new, old);
	audit_log_session_info(ab);
	rc = audit_log_task_context(ab);
	अगर (rc)
		allow_changes = 0; /* Something weird, deny request */
	audit_log_क्रमmat(ab, " res=%d", allow_changes);
	audit_log_end(ab);
	वापस rc;
पूर्ण

अटल पूर्णांक audit_करो_config_change(अक्षर *function_name, u32 *to_change, u32 new)
अणु
	पूर्णांक allow_changes, rc = 0;
	u32 old = *to_change;

	/* check अगर we are locked */
	अगर (audit_enabled == AUDIT_LOCKED)
		allow_changes = 0;
	अन्यथा
		allow_changes = 1;

	अगर (audit_enabled != AUDIT_OFF) अणु
		rc = audit_log_config_change(function_name, new, old, allow_changes);
		अगर (rc)
			allow_changes = 0;
	पूर्ण

	/* If we are allowed, make the change */
	अगर (allow_changes == 1)
		*to_change = new;
	/* Not allowed, update reason */
	अन्यथा अगर (rc == 0)
		rc = -EPERM;
	वापस rc;
पूर्ण

अटल पूर्णांक audit_set_rate_limit(u32 limit)
अणु
	वापस audit_करो_config_change("audit_rate_limit", &audit_rate_limit, limit);
पूर्ण

अटल पूर्णांक audit_set_backlog_limit(u32 limit)
अणु
	वापस audit_करो_config_change("audit_backlog_limit", &audit_backlog_limit, limit);
पूर्ण

अटल पूर्णांक audit_set_backlog_रुको_समय(u32 समयout)
अणु
	वापस audit_करो_config_change("audit_backlog_wait_time",
				      &audit_backlog_रुको_समय, समयout);
पूर्ण

अटल पूर्णांक audit_set_enabled(u32 state)
अणु
	पूर्णांक rc;
	अगर (state > AUDIT_LOCKED)
		वापस -EINVAL;

	rc =  audit_करो_config_change("audit_enabled", &audit_enabled, state);
	अगर (!rc)
		audit_ever_enabled |= !!state;

	वापस rc;
पूर्ण

अटल पूर्णांक audit_set_failure(u32 state)
अणु
	अगर (state != AUDIT_FAIL_SILENT
	    && state != AUDIT_FAIL_PRINTK
	    && state != AUDIT_FAIL_PANIC)
		वापस -EINVAL;

	वापस audit_करो_config_change("audit_failure", &audit_failure, state);
पूर्ण

/**
 * auditd_conn_मुक्त - RCU helper to release an auditd connection काष्ठा
 * @rcu: RCU head
 *
 * Description:
 * Drop any references inside the auditd connection tracking काष्ठा and मुक्त
 * the memory.
 */
अटल व्योम auditd_conn_मुक्त(काष्ठा rcu_head *rcu)
अणु
	काष्ठा auditd_connection *ac;

	ac = container_of(rcu, काष्ठा auditd_connection, rcu);
	put_pid(ac->pid);
	put_net(ac->net);
	kमुक्त(ac);
पूर्ण

/**
 * auditd_set - Set/Reset the auditd connection state
 * @pid: auditd PID
 * @portid: auditd netlink portid
 * @net: auditd network namespace poपूर्णांकer
 *
 * Description:
 * This function will obtain and drop network namespace references as
 * necessary.  Returns zero on success, negative values on failure.
 */
अटल पूर्णांक auditd_set(काष्ठा pid *pid, u32 portid, काष्ठा net *net)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा auditd_connection *ac_old, *ac_new;

	अगर (!pid || !net)
		वापस -EINVAL;

	ac_new = kzalloc(माप(*ac_new), GFP_KERNEL);
	अगर (!ac_new)
		वापस -ENOMEM;
	ac_new->pid = get_pid(pid);
	ac_new->portid = portid;
	ac_new->net = get_net(net);

	spin_lock_irqsave(&auditd_conn_lock, flags);
	ac_old = rcu_dereference_रक्षित(auditd_conn,
					   lockdep_is_held(&auditd_conn_lock));
	rcu_assign_poपूर्णांकer(auditd_conn, ac_new);
	spin_unlock_irqrestore(&auditd_conn_lock, flags);

	अगर (ac_old)
		call_rcu(&ac_old->rcu, auditd_conn_मुक्त);

	वापस 0;
पूर्ण

/**
 * kauditd_prपूर्णांकk_skb - Prपूर्णांक the audit record to the ring buffer
 * @skb: audit record
 *
 * Whatever the reason, this packet may not make it to the auditd connection
 * so ग_लिखो it via prपूर्णांकk so the inक्रमmation isn't completely lost.
 */
अटल व्योम kauditd_prपूर्णांकk_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा nlmsghdr *nlh = nlmsg_hdr(skb);
	अक्षर *data = nlmsg_data(nlh);

	अगर (nlh->nlmsg_type != AUDIT_EOE && prपूर्णांकk_ratelimit())
		pr_notice("type=%d %s\n", nlh->nlmsg_type, data);
पूर्ण

/**
 * kauditd_rehold_skb - Handle a audit record send failure in the hold queue
 * @skb: audit record
 *
 * Description:
 * This should only be used by the kauditd_thपढ़ो when it fails to flush the
 * hold queue.
 */
अटल व्योम kauditd_rehold_skb(काष्ठा sk_buff *skb)
अणु
	/* put the record back in the queue at the same place */
	skb_queue_head(&audit_hold_queue, skb);
पूर्ण

/**
 * kauditd_hold_skb - Queue an audit record, रुकोing क्रम auditd
 * @skb: audit record
 *
 * Description:
 * Queue the audit record, रुकोing क्रम an instance of auditd.  When this
 * function is called we haven't given up yet on sending the record, but things
 * are not looking good.  The first thing we want to करो is try to ग_लिखो the
 * record via prपूर्णांकk and then see अगर we want to try and hold on to the record
 * and queue it, अगर we have room.  If we want to hold on to the record, but we
 * करोn't have room, record a record lost message.
 */
अटल व्योम kauditd_hold_skb(काष्ठा sk_buff *skb)
अणु
	/* at this poपूर्णांक it is uncertain अगर we will ever send this to auditd so
	 * try to send the message via prपूर्णांकk beक्रमe we go any further */
	kauditd_prपूर्णांकk_skb(skb);

	/* can we just silently drop the message? */
	अगर (!audit_शेष) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* अगर we have room, queue the message */
	अगर (!audit_backlog_limit ||
	    skb_queue_len(&audit_hold_queue) < audit_backlog_limit) अणु
		skb_queue_tail(&audit_hold_queue, skb);
		वापस;
	पूर्ण

	/* we have no other options - drop the message */
	audit_log_lost("kauditd hold queue overflow");
	kमुक्त_skb(skb);
पूर्ण

/**
 * kauditd_retry_skb - Queue an audit record, attempt to send again to auditd
 * @skb: audit record
 *
 * Description:
 * Not as serious as kauditd_hold_skb() as we still have a connected auditd,
 * but क्रम some reason we are having problems sending it audit records so
 * queue the given record and attempt to resend.
 */
अटल व्योम kauditd_retry_skb(काष्ठा sk_buff *skb)
अणु
	/* NOTE: because records should only live in the retry queue क्रम a
	 * लघु period of समय, beक्रमe either being sent or moved to the hold
	 * queue, we करोn't currently enक्रमce a limit on this queue */
	skb_queue_tail(&audit_retry_queue, skb);
पूर्ण

/**
 * auditd_reset - Disconnect the auditd connection
 * @ac: auditd connection state
 *
 * Description:
 * Break the auditd/kauditd connection and move all the queued records पूर्णांकo the
 * hold queue in हाल auditd reconnects.  It is important to note that the @ac
 * poपूर्णांकer should never be dereferenced inside this function as it may be शून्य
 * or invalid, you can only compare the memory address!  If @ac is शून्य then
 * the connection will always be reset.
 */
अटल व्योम auditd_reset(स्थिर काष्ठा auditd_connection *ac)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	काष्ठा auditd_connection *ac_old;

	/* अगर it isn't alपढ़ोy broken, अवरोध the connection */
	spin_lock_irqsave(&auditd_conn_lock, flags);
	ac_old = rcu_dereference_रक्षित(auditd_conn,
					   lockdep_is_held(&auditd_conn_lock));
	अगर (ac && ac != ac_old) अणु
		/* someone alपढ़ोy रेजिस्टरed a new auditd connection */
		spin_unlock_irqrestore(&auditd_conn_lock, flags);
		वापस;
	पूर्ण
	rcu_assign_poपूर्णांकer(auditd_conn, शून्य);
	spin_unlock_irqrestore(&auditd_conn_lock, flags);

	अगर (ac_old)
		call_rcu(&ac_old->rcu, auditd_conn_मुक्त);

	/* flush the retry queue to the hold queue, but करोn't touch the मुख्य
	 * queue since we need to process that normally क्रम multicast */
	जबतक ((skb = skb_dequeue(&audit_retry_queue)))
		kauditd_hold_skb(skb);
पूर्ण

/**
 * auditd_send_unicast_skb - Send a record via unicast to auditd
 * @skb: audit record
 *
 * Description:
 * Send a skb to the audit daemon, वापसs positive/zero values on success and
 * negative values on failure; in all हालs the skb will be consumed by this
 * function.  If the send results in -ECONNREFUSED the connection with auditd
 * will be reset.  This function may sleep so callers should not hold any locks
 * where this would cause a problem.
 */
अटल पूर्णांक auditd_send_unicast_skb(काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc;
	u32 portid;
	काष्ठा net *net;
	काष्ठा sock *sk;
	काष्ठा auditd_connection *ac;

	/* NOTE: we can't call netlink_unicast जबतक in the RCU section so
	 *       take a reference to the network namespace and grab local
	 *       copies of the namespace, the sock, and the portid; the
	 *       namespace and sock aren't going to go away जबतक we hold a
	 *       reference and अगर the portid करोes become invalid after the RCU
	 *       section netlink_unicast() should safely वापस an error */

	rcu_पढ़ो_lock();
	ac = rcu_dereference(auditd_conn);
	अगर (!ac) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		rc = -ECONNREFUSED;
		जाओ err;
	पूर्ण
	net = get_net(ac->net);
	sk = audit_get_sk(net);
	portid = ac->portid;
	rcu_पढ़ो_unlock();

	rc = netlink_unicast(sk, skb, portid, 0);
	put_net(net);
	अगर (rc < 0)
		जाओ err;

	वापस rc;

err:
	अगर (ac && rc == -ECONNREFUSED)
		auditd_reset(ac);
	वापस rc;
पूर्ण

/**
 * kauditd_send_queue - Helper क्रम kauditd_thपढ़ो to flush skb queues
 * @sk: the sending sock
 * @portid: the netlink destination
 * @queue: the skb queue to process
 * @retry_limit: limit on number of netlink unicast failures
 * @skb_hook: per-skb hook क्रम additional processing
 * @err_hook: hook called अगर the skb fails the netlink unicast send
 *
 * Description:
 * Run through the given queue and attempt to send the audit records to auditd,
 * वापसs zero on success, negative values on failure.  It is up to the caller
 * to ensure that the @sk is valid क्रम the duration of this function.
 *
 */
अटल पूर्णांक kauditd_send_queue(काष्ठा sock *sk, u32 portid,
			      काष्ठा sk_buff_head *queue,
			      अचिन्हित पूर्णांक retry_limit,
			      व्योम (*skb_hook)(काष्ठा sk_buff *skb),
			      व्योम (*err_hook)(काष्ठा sk_buff *skb))
अणु
	पूर्णांक rc = 0;
	काष्ठा sk_buff *skb;
	अटल अचिन्हित पूर्णांक failed = 0;

	/* NOTE: kauditd_thपढ़ो takes care of all our locking, we just use
	 *       the netlink info passed to us (e.g. sk and portid) */

	जबतक ((skb = skb_dequeue(queue))) अणु
		/* call the skb_hook क्रम each skb we touch */
		अगर (skb_hook)
			(*skb_hook)(skb);

		/* can we send to anyone via unicast? */
		अगर (!sk) अणु
			अगर (err_hook)
				(*err_hook)(skb);
			जारी;
		पूर्ण

		/* grab an extra skb reference in हाल of error */
		skb_get(skb);
		rc = netlink_unicast(sk, skb, portid, 0);
		अगर (rc < 0) अणु
			/* fatal failure क्रम our queue flush attempt? */
			अगर (++failed >= retry_limit ||
			    rc == -ECONNREFUSED || rc == -EPERM) अणु
				/* yes - error processing क्रम the queue */
				sk = शून्य;
				अगर (err_hook)
					(*err_hook)(skb);
				अगर (!skb_hook)
					जाओ out;
				/* keep processing with the skb_hook */
				जारी;
			पूर्ण अन्यथा
				/* no - requeue to preserve ordering */
				skb_queue_head(queue, skb);
		पूर्ण अन्यथा अणु
			/* it worked - drop the extra reference and जारी */
			consume_skb(skb);
			failed = 0;
		पूर्ण
	पूर्ण

out:
	वापस (rc >= 0 ? 0 : rc);
पूर्ण

/*
 * kauditd_send_multicast_skb - Send a record to any multicast listeners
 * @skb: audit record
 *
 * Description:
 * Write a multicast message to anyone listening in the initial network
 * namespace.  This function करोesn't consume an skb as might be expected since
 * it has to copy it anyways.
 */
अटल व्योम kauditd_send_multicast_skb(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *copy;
	काष्ठा sock *sock = audit_get_sk(&init_net);
	काष्ठा nlmsghdr *nlh;

	/* NOTE: we are not taking an additional reference क्रम init_net since
	 *       we करोn't have to worry about it going away */

	अगर (!netlink_has_listeners(sock, AUDIT_NLGRP_READLOG))
		वापस;

	/*
	 * The seemingly wasteful skb_copy() rather than bumping the refcount
	 * using skb_get() is necessary because non-standard mods are made to
	 * the skb by the original kaudit unicast socket send routine.  The
	 * existing auditd daemon assumes this अवरोधage.  Fixing this would
	 * require co-ordinating a change in the established protocol between
	 * the kaudit kernel subप्रणाली and the auditd userspace code.  There is
	 * no reason क्रम new multicast clients to जारी with this
	 * non-compliance.
	 */
	copy = skb_copy(skb, GFP_KERNEL);
	अगर (!copy)
		वापस;
	nlh = nlmsg_hdr(copy);
	nlh->nlmsg_len = skb->len;

	nlmsg_multicast(sock, copy, 0, AUDIT_NLGRP_READLOG, GFP_KERNEL);
पूर्ण

/**
 * kauditd_thपढ़ो - Worker thपढ़ो to send audit records to userspace
 * @dummy: unused
 */
अटल पूर्णांक kauditd_thपढ़ो(व्योम *dummy)
अणु
	पूर्णांक rc;
	u32 portid = 0;
	काष्ठा net *net = शून्य;
	काष्ठा sock *sk = शून्य;
	काष्ठा auditd_connection *ac;

#घोषणा UNICAST_RETRIES 5

	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु
		/* NOTE: see the lock comments in auditd_send_unicast_skb() */
		rcu_पढ़ो_lock();
		ac = rcu_dereference(auditd_conn);
		अगर (!ac) अणु
			rcu_पढ़ो_unlock();
			जाओ मुख्य_queue;
		पूर्ण
		net = get_net(ac->net);
		sk = audit_get_sk(net);
		portid = ac->portid;
		rcu_पढ़ो_unlock();

		/* attempt to flush the hold queue */
		rc = kauditd_send_queue(sk, portid,
					&audit_hold_queue, UNICAST_RETRIES,
					शून्य, kauditd_rehold_skb);
		अगर (rc < 0) अणु
			sk = शून्य;
			auditd_reset(ac);
			जाओ मुख्य_queue;
		पूर्ण

		/* attempt to flush the retry queue */
		rc = kauditd_send_queue(sk, portid,
					&audit_retry_queue, UNICAST_RETRIES,
					शून्य, kauditd_hold_skb);
		अगर (rc < 0) अणु
			sk = शून्य;
			auditd_reset(ac);
			जाओ मुख्य_queue;
		पूर्ण

मुख्य_queue:
		/* process the मुख्य queue - करो the multicast send and attempt
		 * unicast, dump failed record sends to the retry queue; अगर
		 * sk == शून्य due to previous failures we will just करो the
		 * multicast send and move the record to the hold queue */
		rc = kauditd_send_queue(sk, portid, &audit_queue, 1,
					kauditd_send_multicast_skb,
					(sk ?
					 kauditd_retry_skb : kauditd_hold_skb));
		अगर (ac && rc < 0)
			auditd_reset(ac);
		sk = शून्य;

		/* drop our netns reference, no auditd sends past this line */
		अगर (net) अणु
			put_net(net);
			net = शून्य;
		पूर्ण

		/* we have processed all the queues so wake everyone */
		wake_up(&audit_backlog_रुको);

		/* NOTE: we want to wake up अगर there is anything on the queue,
		 *       regardless of अगर an auditd is connected, as we need to
		 *       करो the multicast send and rotate records from the
		 *       मुख्य queue to the retry/hold queues */
		रुको_event_मुक्तzable(kauditd_रुको,
				     (skb_queue_len(&audit_queue) ? 1 : 0));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक audit_send_list_thपढ़ो(व्योम *_dest)
अणु
	काष्ठा audit_netlink_list *dest = _dest;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk = audit_get_sk(dest->net);

	/* रुको क्रम parent to finish and send an ACK */
	audit_ctl_lock();
	audit_ctl_unlock();

	जबतक ((skb = __skb_dequeue(&dest->q)) != शून्य)
		netlink_unicast(sk, skb, dest->portid, 0);

	put_net(dest->net);
	kमुक्त(dest);

	वापस 0;
पूर्ण

काष्ठा sk_buff *audit_make_reply(पूर्णांक seq, पूर्णांक type, पूर्णांक करोne,
				 पूर्णांक multi, स्थिर व्योम *payload, पूर्णांक size)
अणु
	काष्ठा sk_buff	*skb;
	काष्ठा nlmsghdr	*nlh;
	व्योम		*data;
	पूर्णांक		flags = multi ? NLM_F_MULTI : 0;
	पूर्णांक		t     = करोne  ? NLMSG_DONE  : type;

	skb = nlmsg_new(size, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	nlh	= nlmsg_put(skb, 0, seq, t, size, flags);
	अगर (!nlh)
		जाओ out_kमुक्त_skb;
	data = nlmsg_data(nlh);
	स_नकल(data, payload, size);
	वापस skb;

out_kमुक्त_skb:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

अटल व्योम audit_मुक्त_reply(काष्ठा audit_reply *reply)
अणु
	अगर (!reply)
		वापस;

	kमुक्त_skb(reply->skb);
	अगर (reply->net)
		put_net(reply->net);
	kमुक्त(reply);
पूर्ण

अटल पूर्णांक audit_send_reply_thपढ़ो(व्योम *arg)
अणु
	काष्ठा audit_reply *reply = (काष्ठा audit_reply *)arg;

	audit_ctl_lock();
	audit_ctl_unlock();

	/* Ignore failure. It'll only happen अगर the sender goes away,
	   because our समयout is set to infinite. */
	netlink_unicast(audit_get_sk(reply->net), reply->skb, reply->portid, 0);
	reply->skb = शून्य;
	audit_मुक्त_reply(reply);
	वापस 0;
पूर्ण

/**
 * audit_send_reply - send an audit reply message via netlink
 * @request_skb: skb of request we are replying to (used to target the reply)
 * @seq: sequence number
 * @type: audit message type
 * @करोne: करोne (last) flag
 * @multi: multi-part message flag
 * @payload: payload data
 * @size: payload size
 *
 * Allocates a skb, builds the netlink message, and sends it to the port id.
 */
अटल व्योम audit_send_reply(काष्ठा sk_buff *request_skb, पूर्णांक seq, पूर्णांक type, पूर्णांक करोne,
			     पूर्णांक multi, स्थिर व्योम *payload, पूर्णांक size)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा audit_reply *reply;

	reply = kzalloc(माप(*reply), GFP_KERNEL);
	अगर (!reply)
		वापस;

	reply->skb = audit_make_reply(seq, type, करोne, multi, payload, size);
	अगर (!reply->skb)
		जाओ err;
	reply->net = get_net(sock_net(NETLINK_CB(request_skb).sk));
	reply->portid = NETLINK_CB(request_skb).portid;

	tsk = kthपढ़ो_run(audit_send_reply_thपढ़ो, reply, "audit_send_reply");
	अगर (IS_ERR(tsk))
		जाओ err;

	वापस;

err:
	audit_मुक्त_reply(reply);
पूर्ण

/*
 * Check क्रम appropriate CAP_AUDIT_ capabilities on incoming audit
 * control messages.
 */
अटल पूर्णांक audit_netlink_ok(काष्ठा sk_buff *skb, u16 msg_type)
अणु
	पूर्णांक err = 0;

	/* Only support initial user namespace क्रम now. */
	/*
	 * We वापस ECONNREFUSED because it tricks userspace पूर्णांकo thinking
	 * that audit was not configured पूर्णांकo the kernel.  Lots of users
	 * configure their PAM stack (because that's what the distro करोes)
	 * to reject login अगर unable to send messages to audit.  If we वापस
	 * ECONNREFUSED the PAM stack thinks the kernel करोes not have audit
	 * configured in and will let login proceed.  If we वापस EPERM
	 * userspace will reject all logins.  This should be हटाओd when we
	 * support non init namespaces!!
	 */
	अगर (current_user_ns() != &init_user_ns)
		वापस -ECONNREFUSED;

	चयन (msg_type) अणु
	हाल AUDIT_LIST:
	हाल AUDIT_ADD:
	हाल AUDIT_DEL:
		वापस -EOPNOTSUPP;
	हाल AUDIT_GET:
	हाल AUDIT_SET:
	हाल AUDIT_GET_FEATURE:
	हाल AUDIT_SET_FEATURE:
	हाल AUDIT_LIST_RULES:
	हाल AUDIT_ADD_RULE:
	हाल AUDIT_DEL_RULE:
	हाल AUDIT_SIGNAL_INFO:
	हाल AUDIT_TTY_GET:
	हाल AUDIT_TTY_SET:
	हाल AUDIT_TRIM:
	हाल AUDIT_MAKE_EQUIV:
		/* Only support auditd and auditctl in initial pid namespace
		 * क्रम now. */
		अगर (task_active_pid_ns(current) != &init_pid_ns)
			वापस -EPERM;

		अगर (!netlink_capable(skb, CAP_AUDIT_CONTROL))
			err = -EPERM;
		अवरोध;
	हाल AUDIT_USER:
	हाल AUDIT_FIRST_USER_MSG ... AUDIT_LAST_USER_MSG:
	हाल AUDIT_FIRST_USER_MSG2 ... AUDIT_LAST_USER_MSG2:
		अगर (!netlink_capable(skb, CAP_AUDIT_WRITE))
			err = -EPERM;
		अवरोध;
	शेष:  /* bad msg */
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम audit_log_common_recv_msg(काष्ठा audit_context *context,
					काष्ठा audit_buffer **ab, u16 msg_type)
अणु
	uid_t uid = from_kuid(&init_user_ns, current_uid());
	pid_t pid = task_tgid_nr(current);

	अगर (!audit_enabled && msg_type != AUDIT_USER_AVC) अणु
		*ab = शून्य;
		वापस;
	पूर्ण

	*ab = audit_log_start(context, GFP_KERNEL, msg_type);
	अगर (unlikely(!*ab))
		वापस;
	audit_log_क्रमmat(*ab, "pid=%d uid=%u ", pid, uid);
	audit_log_session_info(*ab);
	audit_log_task_context(*ab);
पूर्ण

अटल अंतरभूत व्योम audit_log_user_recv_msg(काष्ठा audit_buffer **ab,
					   u16 msg_type)
अणु
	audit_log_common_recv_msg(शून्य, ab, msg_type);
पूर्ण

पूर्णांक is_audit_feature_set(पूर्णांक i)
अणु
	वापस af.features & AUDIT_FEATURE_TO_MASK(i);
पूर्ण


अटल पूर्णांक audit_get_feature(काष्ठा sk_buff *skb)
अणु
	u32 seq;

	seq = nlmsg_hdr(skb)->nlmsg_seq;

	audit_send_reply(skb, seq, AUDIT_GET_FEATURE, 0, 0, &af, माप(af));

	वापस 0;
पूर्ण

अटल व्योम audit_log_feature_change(पूर्णांक which, u32 old_feature, u32 new_feature,
				     u32 old_lock, u32 new_lock, पूर्णांक res)
अणु
	काष्ठा audit_buffer *ab;

	अगर (audit_enabled == AUDIT_OFF)
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_FEATURE_CHANGE);
	अगर (!ab)
		वापस;
	audit_log_task_info(ab);
	audit_log_क्रमmat(ab, " feature=%s old=%u new=%u old_lock=%u new_lock=%u res=%d",
			 audit_feature_names[which], !!old_feature, !!new_feature,
			 !!old_lock, !!new_lock, res);
	audit_log_end(ab);
पूर्ण

अटल पूर्णांक audit_set_feature(काष्ठा audit_features *uaf)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(AUDIT_LAST_FEATURE + 1 > ARRAY_SIZE(audit_feature_names));

	/* अगर there is ever a version 2 we should handle that here */

	क्रम (i = 0; i <= AUDIT_LAST_FEATURE; i++) अणु
		u32 feature = AUDIT_FEATURE_TO_MASK(i);
		u32 old_feature, new_feature, old_lock, new_lock;

		/* अगर we are not changing this feature, move aदीर्घ */
		अगर (!(feature & uaf->mask))
			जारी;

		old_feature = af.features & feature;
		new_feature = uaf->features & feature;
		new_lock = (uaf->lock | af.lock) & feature;
		old_lock = af.lock & feature;

		/* are we changing a locked feature? */
		अगर (old_lock && (new_feature != old_feature)) अणु
			audit_log_feature_change(i, old_feature, new_feature,
						 old_lock, new_lock, 0);
			वापस -EPERM;
		पूर्ण
	पूर्ण
	/* nothing invalid, करो the changes */
	क्रम (i = 0; i <= AUDIT_LAST_FEATURE; i++) अणु
		u32 feature = AUDIT_FEATURE_TO_MASK(i);
		u32 old_feature, new_feature, old_lock, new_lock;

		/* अगर we are not changing this feature, move aदीर्घ */
		अगर (!(feature & uaf->mask))
			जारी;

		old_feature = af.features & feature;
		new_feature = uaf->features & feature;
		old_lock = af.lock & feature;
		new_lock = (uaf->lock | af.lock) & feature;

		अगर (new_feature != old_feature)
			audit_log_feature_change(i, old_feature, new_feature,
						 old_lock, new_lock, 1);

		अगर (new_feature)
			af.features |= feature;
		अन्यथा
			af.features &= ~feature;
		af.lock |= new_lock;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक audit_replace(काष्ठा pid *pid)
अणु
	pid_t pvnr;
	काष्ठा sk_buff *skb;

	pvnr = pid_vnr(pid);
	skb = audit_make_reply(0, AUDIT_REPLACE, 0, 0, &pvnr, माप(pvnr));
	अगर (!skb)
		वापस -ENOMEM;
	वापस auditd_send_unicast_skb(skb);
पूर्ण

अटल पूर्णांक audit_receive_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	u32			seq;
	व्योम			*data;
	पूर्णांक			data_len;
	पूर्णांक			err;
	काष्ठा audit_buffer	*ab;
	u16			msg_type = nlh->nlmsg_type;
	काष्ठा audit_sig_info   *sig_data;
	अक्षर			*ctx = शून्य;
	u32			len;

	err = audit_netlink_ok(skb, msg_type);
	अगर (err)
		वापस err;

	seq  = nlh->nlmsg_seq;
	data = nlmsg_data(nlh);
	data_len = nlmsg_len(nlh);

	चयन (msg_type) अणु
	हाल AUDIT_GET: अणु
		काष्ठा audit_status	s;
		स_रखो(&s, 0, माप(s));
		s.enabled		   = audit_enabled;
		s.failure		   = audit_failure;
		/* NOTE: use pid_vnr() so the PID is relative to the current
		 *       namespace */
		s.pid			   = auditd_pid_vnr();
		s.rate_limit		   = audit_rate_limit;
		s.backlog_limit		   = audit_backlog_limit;
		s.lost			   = atomic_पढ़ो(&audit_lost);
		s.backlog		   = skb_queue_len(&audit_queue);
		s.feature_biपंचांगap	   = AUDIT_FEATURE_BITMAP_ALL;
		s.backlog_रुको_समय	   = audit_backlog_रुको_समय;
		s.backlog_रुको_समय_actual = atomic_पढ़ो(&audit_backlog_रुको_समय_actual);
		audit_send_reply(skb, seq, AUDIT_GET, 0, 0, &s, माप(s));
		अवरोध;
	पूर्ण
	हाल AUDIT_SET: अणु
		काष्ठा audit_status	s;
		स_रखो(&s, 0, माप(s));
		/* guard against past and future API changes */
		स_नकल(&s, data, min_t(माप_प्रकार, माप(s), data_len));
		अगर (s.mask & AUDIT_STATUS_ENABLED) अणु
			err = audit_set_enabled(s.enabled);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (s.mask & AUDIT_STATUS_FAILURE) अणु
			err = audit_set_failure(s.failure);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (s.mask & AUDIT_STATUS_PID) अणु
			/* NOTE: we are using the vnr PID functions below
			 *       because the s.pid value is relative to the
			 *       namespace of the caller; at present this
			 *       करोesn't matter much since you can really only
			 *       run auditd from the initial pid namespace, but
			 *       something to keep in mind अगर this changes */
			pid_t new_pid = s.pid;
			pid_t auditd_pid;
			काष्ठा pid *req_pid = task_tgid(current);

			/* Sanity check - PID values must match. Setting
			 * pid to 0 is how auditd ends auditing. */
			अगर (new_pid && (new_pid != pid_vnr(req_pid)))
				वापस -EINVAL;

			/* test the auditd connection */
			audit_replace(req_pid);

			auditd_pid = auditd_pid_vnr();
			अगर (auditd_pid) अणु
				/* replacing a healthy auditd is not allowed */
				अगर (new_pid) अणु
					audit_log_config_change("audit_pid",
							new_pid, auditd_pid, 0);
					वापस -EEXIST;
				पूर्ण
				/* only current auditd can unरेजिस्टर itself */
				अगर (pid_vnr(req_pid) != auditd_pid) अणु
					audit_log_config_change("audit_pid",
							new_pid, auditd_pid, 0);
					वापस -EACCES;
				पूर्ण
			पूर्ण

			अगर (new_pid) अणु
				/* रेजिस्टर a new auditd connection */
				err = auditd_set(req_pid,
						 NETLINK_CB(skb).portid,
						 sock_net(NETLINK_CB(skb).sk));
				अगर (audit_enabled != AUDIT_OFF)
					audit_log_config_change("audit_pid",
								new_pid,
								auditd_pid,
								err ? 0 : 1);
				अगर (err)
					वापस err;

				/* try to process any backlog */
				wake_up_पूर्णांकerruptible(&kauditd_रुको);
			पूर्ण अन्यथा अणु
				अगर (audit_enabled != AUDIT_OFF)
					audit_log_config_change("audit_pid",
								new_pid,
								auditd_pid, 1);

				/* unरेजिस्टर the auditd connection */
				auditd_reset(शून्य);
			पूर्ण
		पूर्ण
		अगर (s.mask & AUDIT_STATUS_RATE_LIMIT) अणु
			err = audit_set_rate_limit(s.rate_limit);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (s.mask & AUDIT_STATUS_BACKLOG_LIMIT) अणु
			err = audit_set_backlog_limit(s.backlog_limit);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (s.mask & AUDIT_STATUS_BACKLOG_WAIT_TIME) अणु
			अगर (माप(s) > (माप_प्रकार)nlh->nlmsg_len)
				वापस -EINVAL;
			अगर (s.backlog_रुको_समय > 10*AUDIT_BACKLOG_WAIT_TIME)
				वापस -EINVAL;
			err = audit_set_backlog_रुको_समय(s.backlog_रुको_समय);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (s.mask == AUDIT_STATUS_LOST) अणु
			u32 lost = atomic_xchg(&audit_lost, 0);

			audit_log_config_change("lost", 0, lost, 1);
			वापस lost;
		पूर्ण
		अगर (s.mask == AUDIT_STATUS_BACKLOG_WAIT_TIME_ACTUAL) अणु
			u32 actual = atomic_xchg(&audit_backlog_रुको_समय_actual, 0);

			audit_log_config_change("backlog_wait_time_actual", 0, actual, 1);
			वापस actual;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल AUDIT_GET_FEATURE:
		err = audit_get_feature(skb);
		अगर (err)
			वापस err;
		अवरोध;
	हाल AUDIT_SET_FEATURE:
		अगर (data_len < माप(काष्ठा audit_features))
			वापस -EINVAL;
		err = audit_set_feature(data);
		अगर (err)
			वापस err;
		अवरोध;
	हाल AUDIT_USER:
	हाल AUDIT_FIRST_USER_MSG ... AUDIT_LAST_USER_MSG:
	हाल AUDIT_FIRST_USER_MSG2 ... AUDIT_LAST_USER_MSG2:
		अगर (!audit_enabled && msg_type != AUDIT_USER_AVC)
			वापस 0;
		/* निकास early अगर there isn't at least one अक्षरacter to prपूर्णांक */
		अगर (data_len < 2)
			वापस -EINVAL;

		err = audit_filter(msg_type, AUDIT_FILTER_USER);
		अगर (err == 1) अणु /* match or error */
			अक्षर *str = data;

			err = 0;
			अगर (msg_type == AUDIT_USER_TTY) अणु
				err = tty_audit_push();
				अगर (err)
					अवरोध;
			पूर्ण
			audit_log_user_recv_msg(&ab, msg_type);
			अगर (msg_type != AUDIT_USER_TTY) अणु
				/* ensure शून्य termination */
				str[data_len - 1] = '\0';
				audit_log_क्रमmat(ab, " msg='%.*s'",
						 AUDIT_MESSAGE_TEXT_MAX,
						 str);
			पूर्ण अन्यथा अणु
				audit_log_क्रमmat(ab, " data=");
				अगर (data_len > 0 && str[data_len - 1] == '\0')
					data_len--;
				audit_log_n_untrustedstring(ab, str, data_len);
			पूर्ण
			audit_log_end(ab);
		पूर्ण
		अवरोध;
	हाल AUDIT_ADD_RULE:
	हाल AUDIT_DEL_RULE:
		अगर (data_len < माप(काष्ठा audit_rule_data))
			वापस -EINVAL;
		अगर (audit_enabled == AUDIT_LOCKED) अणु
			audit_log_common_recv_msg(audit_context(), &ab,
						  AUDIT_CONFIG_CHANGE);
			audit_log_क्रमmat(ab, " op=%s audit_enabled=%d res=0",
					 msg_type == AUDIT_ADD_RULE ?
						"add_rule" : "remove_rule",
					 audit_enabled);
			audit_log_end(ab);
			वापस -EPERM;
		पूर्ण
		err = audit_rule_change(msg_type, seq, data, data_len);
		अवरोध;
	हाल AUDIT_LIST_RULES:
		err = audit_list_rules_send(skb, seq);
		अवरोध;
	हाल AUDIT_TRIM:
		audit_trim_trees();
		audit_log_common_recv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_log_क्रमmat(ab, " op=trim res=1");
		audit_log_end(ab);
		अवरोध;
	हाल AUDIT_MAKE_EQUIV: अणु
		व्योम *bufp = data;
		u32 sizes[2];
		माप_प्रकार msglen = data_len;
		अक्षर *old, *new;

		err = -EINVAL;
		अगर (msglen < 2 * माप(u32))
			अवरोध;
		स_नकल(sizes, bufp, 2 * माप(u32));
		bufp += 2 * माप(u32);
		msglen -= 2 * माप(u32);
		old = audit_unpack_string(&bufp, &msglen, sizes[0]);
		अगर (IS_ERR(old)) अणु
			err = PTR_ERR(old);
			अवरोध;
		पूर्ण
		new = audit_unpack_string(&bufp, &msglen, sizes[1]);
		अगर (IS_ERR(new)) अणु
			err = PTR_ERR(new);
			kमुक्त(old);
			अवरोध;
		पूर्ण
		/* OK, here comes... */
		err = audit_tag_tree(old, new);

		audit_log_common_recv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_log_क्रमmat(ab, " op=make_equiv old=");
		audit_log_untrustedstring(ab, old);
		audit_log_क्रमmat(ab, " new=");
		audit_log_untrustedstring(ab, new);
		audit_log_क्रमmat(ab, " res=%d", !err);
		audit_log_end(ab);
		kमुक्त(old);
		kमुक्त(new);
		अवरोध;
	पूर्ण
	हाल AUDIT_SIGNAL_INFO:
		len = 0;
		अगर (audit_sig_sid) अणु
			err = security_secid_to_secctx(audit_sig_sid, &ctx, &len);
			अगर (err)
				वापस err;
		पूर्ण
		sig_data = kदो_स्मृति(माप(*sig_data) + len, GFP_KERNEL);
		अगर (!sig_data) अणु
			अगर (audit_sig_sid)
				security_release_secctx(ctx, len);
			वापस -ENOMEM;
		पूर्ण
		sig_data->uid = from_kuid(&init_user_ns, audit_sig_uid);
		sig_data->pid = audit_sig_pid;
		अगर (audit_sig_sid) अणु
			स_नकल(sig_data->ctx, ctx, len);
			security_release_secctx(ctx, len);
		पूर्ण
		audit_send_reply(skb, seq, AUDIT_SIGNAL_INFO, 0, 0,
				 sig_data, माप(*sig_data) + len);
		kमुक्त(sig_data);
		अवरोध;
	हाल AUDIT_TTY_GET: अणु
		काष्ठा audit_tty_status s;
		अचिन्हित पूर्णांक t;

		t = READ_ONCE(current->संकेत->audit_tty);
		s.enabled = t & AUDIT_TTY_ENABLE;
		s.log_passwd = !!(t & AUDIT_TTY_LOG_PASSWD);

		audit_send_reply(skb, seq, AUDIT_TTY_GET, 0, 0, &s, माप(s));
		अवरोध;
	पूर्ण
	हाल AUDIT_TTY_SET: अणु
		काष्ठा audit_tty_status s, old;
		काष्ठा audit_buffer	*ab;
		अचिन्हित पूर्णांक t;

		स_रखो(&s, 0, माप(s));
		/* guard against past and future API changes */
		स_नकल(&s, data, min_t(माप_प्रकार, माप(s), data_len));
		/* check अगर new data is valid */
		अगर ((s.enabled != 0 && s.enabled != 1) ||
		    (s.log_passwd != 0 && s.log_passwd != 1))
			err = -EINVAL;

		अगर (err)
			t = READ_ONCE(current->संकेत->audit_tty);
		अन्यथा अणु
			t = s.enabled | (-s.log_passwd & AUDIT_TTY_LOG_PASSWD);
			t = xchg(&current->संकेत->audit_tty, t);
		पूर्ण
		old.enabled = t & AUDIT_TTY_ENABLE;
		old.log_passwd = !!(t & AUDIT_TTY_LOG_PASSWD);

		audit_log_common_recv_msg(audit_context(), &ab,
					  AUDIT_CONFIG_CHANGE);
		audit_log_क्रमmat(ab, " op=tty_set old-enabled=%d new-enabled=%d"
				 " old-log_passwd=%d new-log_passwd=%d res=%d",
				 old.enabled, s.enabled, old.log_passwd,
				 s.log_passwd, !err);
		audit_log_end(ab);
		अवरोध;
	पूर्ण
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err < 0 ? err : 0;
पूर्ण

/**
 * audit_receive - receive messages from a netlink control socket
 * @skb: the message buffer
 *
 * Parse the provided skb and deal with any messages that may be present,
 * malक्रमmed skbs are discarded.
 */
अटल व्योम audit_receive(काष्ठा sk_buff  *skb)
अणु
	काष्ठा nlmsghdr *nlh;
	/*
	 * len MUST be चिन्हित क्रम nlmsg_next to be able to dec it below 0
	 * अगर the nlmsg_len was not aligned
	 */
	पूर्णांक len;
	पूर्णांक err;

	nlh = nlmsg_hdr(skb);
	len = skb->len;

	audit_ctl_lock();
	जबतक (nlmsg_ok(nlh, len)) अणु
		err = audit_receive_msg(skb, nlh);
		/* अगर err or अगर this message says it wants a response */
		अगर (err || (nlh->nlmsg_flags & NLM_F_ACK))
			netlink_ack(skb, nlh, err, शून्य);

		nlh = nlmsg_next(nlh, &len);
	पूर्ण
	audit_ctl_unlock();
पूर्ण

/* Log inक्रमmation about who is connecting to the audit multicast socket */
अटल व्योम audit_log_multicast(पूर्णांक group, स्थिर अक्षर *op, पूर्णांक err)
अणु
	स्थिर काष्ठा cred *cred;
	काष्ठा tty_काष्ठा *tty;
	अक्षर comm[माप(current->comm)];
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_EVENT_LISTENER);
	अगर (!ab)
		वापस;

	cred = current_cred();
	tty = audit_get_tty();
	audit_log_क्रमmat(ab, "pid=%u uid=%u auid=%u tty=%s ses=%u",
			 task_pid_nr(current),
			 from_kuid(&init_user_ns, cred->uid),
			 from_kuid(&init_user_ns, audit_get_loginuid(current)),
			 tty ? tty_name(tty) : "(none)",
			 audit_get_sessionid(current));
	audit_put_tty(tty);
	audit_log_task_context(ab); /* subj= */
	audit_log_क्रमmat(ab, " comm=");
	audit_log_untrustedstring(ab, get_task_comm(comm, current));
	audit_log_d_path_exe(ab, current->mm); /* exe= */
	audit_log_क्रमmat(ab, " nl-mcgrp=%d op=%s res=%d", group, op, !err);
	audit_log_end(ab);
पूर्ण

/* Run custom bind function on netlink socket group connect or bind requests. */
अटल पूर्णांक audit_multicast_bind(काष्ठा net *net, पूर्णांक group)
अणु
	पूर्णांक err = 0;

	अगर (!capable(CAP_AUDIT_READ))
		err = -EPERM;
	audit_log_multicast(group, "connect", err);
	वापस err;
पूर्ण

अटल व्योम audit_multicast_unbind(काष्ठा net *net, पूर्णांक group)
अणु
	audit_log_multicast(group, "disconnect", 0);
पूर्ण

अटल पूर्णांक __net_init audit_net_init(काष्ठा net *net)
अणु
	काष्ठा netlink_kernel_cfg cfg = अणु
		.input	= audit_receive,
		.bind	= audit_multicast_bind,
		.unbind	= audit_multicast_unbind,
		.flags	= NL_CFG_F_NONROOT_RECV,
		.groups	= AUDIT_NLGRP_MAX,
	पूर्ण;

	काष्ठा audit_net *aunet = net_generic(net, audit_net_id);

	aunet->sk = netlink_kernel_create(net, NETLINK_AUDIT, &cfg);
	अगर (aunet->sk == शून्य) अणु
		audit_panic("cannot initialize netlink socket in namespace");
		वापस -ENOMEM;
	पूर्ण
	aunet->sk->sk_sndसमयo = MAX_SCHEDULE_TIMEOUT;

	वापस 0;
पूर्ण

अटल व्योम __net_निकास audit_net_निकास(काष्ठा net *net)
अणु
	काष्ठा audit_net *aunet = net_generic(net, audit_net_id);

	/* NOTE: you would think that we would want to check the auditd
	 * connection and potentially reset it here अगर it lives in this
	 * namespace, but since the auditd connection tracking काष्ठा holds a
	 * reference to this namespace (see auditd_set()) we are only ever
	 * going to get here after that connection has been released */

	netlink_kernel_release(aunet->sk);
पूर्ण

अटल काष्ठा pernet_operations audit_net_ops __net_initdata = अणु
	.init = audit_net_init,
	.निकास = audit_net_निकास,
	.id = &audit_net_id,
	.size = माप(काष्ठा audit_net),
पूर्ण;

/* Initialize audit support at boot समय. */
अटल पूर्णांक __init audit_init(व्योम)
अणु
	पूर्णांक i;

	अगर (audit_initialized == AUDIT_DISABLED)
		वापस 0;

	audit_buffer_cache = kmem_cache_create("audit_buffer",
					       माप(काष्ठा audit_buffer),
					       0, SLAB_PANIC, शून्य);

	skb_queue_head_init(&audit_queue);
	skb_queue_head_init(&audit_retry_queue);
	skb_queue_head_init(&audit_hold_queue);

	क्रम (i = 0; i < AUDIT_INODE_BUCKETS; i++)
		INIT_LIST_HEAD(&audit_inode_hash[i]);

	mutex_init(&audit_cmd_mutex.lock);
	audit_cmd_mutex.owner = शून्य;

	pr_info("initializing netlink subsys (%s)\n",
		audit_शेष ? "enabled" : "disabled");
	रेजिस्टर_pernet_subsys(&audit_net_ops);

	audit_initialized = AUDIT_INITIALIZED;

	kauditd_task = kthपढ़ो_run(kauditd_thपढ़ो, शून्य, "kauditd");
	अगर (IS_ERR(kauditd_task)) अणु
		पूर्णांक err = PTR_ERR(kauditd_task);
		panic("audit: failed to start the kauditd thread (%d)\n", err);
	पूर्ण

	audit_log(शून्य, GFP_KERNEL, AUDIT_KERNEL,
		"state=initialized audit_enabled=%u res=1",
		 audit_enabled);

	वापस 0;
पूर्ण
postcore_initcall(audit_init);

/*
 * Process kernel command-line parameter at boot समय.
 * audit=अणु0|offपूर्ण or audit=अणु1|onपूर्ण.
 */
अटल पूर्णांक __init audit_enable(अक्षर *str)
अणु
	अगर (!strहालcmp(str, "off") || !म_भेद(str, "0"))
		audit_शेष = AUDIT_OFF;
	अन्यथा अगर (!strहालcmp(str, "on") || !म_भेद(str, "1"))
		audit_शेष = AUDIT_ON;
	अन्यथा अणु
		pr_err("audit: invalid 'audit' parameter value (%s)\n", str);
		audit_शेष = AUDIT_ON;
	पूर्ण

	अगर (audit_शेष == AUDIT_OFF)
		audit_initialized = AUDIT_DISABLED;
	अगर (audit_set_enabled(audit_शेष))
		pr_err("audit: error setting audit state (%d)\n",
		       audit_शेष);

	pr_info("%s\n", audit_शेष ?
		"enabled (after initialization)" : "disabled (until reboot)");

	वापस 1;
पूर्ण
__setup("audit=", audit_enable);

/* Process kernel command-line parameter at boot समय.
 * audit_backlog_limit=<n> */
अटल पूर्णांक __init audit_backlog_limit_set(अक्षर *str)
अणु
	u32 audit_backlog_limit_arg;

	pr_info("audit_backlog_limit: ");
	अगर (kstrtouपूर्णांक(str, 0, &audit_backlog_limit_arg)) अणु
		pr_cont("using default of %u, unable to parse %s\n",
			audit_backlog_limit, str);
		वापस 1;
	पूर्ण

	audit_backlog_limit = audit_backlog_limit_arg;
	pr_cont("%d\n", audit_backlog_limit);

	वापस 1;
पूर्ण
__setup("audit_backlog_limit=", audit_backlog_limit_set);

अटल व्योम audit_buffer_मुक्त(काष्ठा audit_buffer *ab)
अणु
	अगर (!ab)
		वापस;

	kमुक्त_skb(ab->skb);
	kmem_cache_मुक्त(audit_buffer_cache, ab);
पूर्ण

अटल काष्ठा audit_buffer *audit_buffer_alloc(काष्ठा audit_context *ctx,
					       gfp_t gfp_mask, पूर्णांक type)
अणु
	काष्ठा audit_buffer *ab;

	ab = kmem_cache_alloc(audit_buffer_cache, gfp_mask);
	अगर (!ab)
		वापस शून्य;

	ab->skb = nlmsg_new(AUDIT_बफ_मान, gfp_mask);
	अगर (!ab->skb)
		जाओ err;
	अगर (!nlmsg_put(ab->skb, 0, 0, type, 0, 0))
		जाओ err;

	ab->ctx = ctx;
	ab->gfp_mask = gfp_mask;

	वापस ab;

err:
	audit_buffer_मुक्त(ab);
	वापस शून्य;
पूर्ण

/**
 * audit_serial - compute a serial number क्रम the audit record
 *
 * Compute a serial number क्रम the audit record.  Audit records are
 * written to user-space as soon as they are generated, so a complete
 * audit record may be written in several pieces.  The बारtamp of the
 * record and this serial number are used by the user-space tools to
 * determine which pieces beदीर्घ to the same audit record.  The
 * (बारtamp,serial) tuple is unique क्रम each syscall and is live from
 * syscall entry to syscall निकास.
 *
 * NOTE: Another possibility is to store the क्रमmatted records off the
 * audit context (क्रम those records that have a context), and emit them
 * all at syscall निकास.  However, this could delay the reporting of
 * signअगरicant errors until syscall निकास (or never, अगर the प्रणाली
 * halts).
 */
अचिन्हित पूर्णांक audit_serial(व्योम)
अणु
	अटल atomic_t serial = ATOMIC_INIT(0);

	वापस atomic_inc_वापस(&serial);
पूर्ण

अटल अंतरभूत व्योम audit_get_stamp(काष्ठा audit_context *ctx,
				   काष्ठा बारpec64 *t, अचिन्हित पूर्णांक *serial)
अणु
	अगर (!ctx || !auditsc_get_stamp(ctx, t, serial)) अणु
		kसमय_get_coarse_real_ts64(t);
		*serial = audit_serial();
	पूर्ण
पूर्ण

/**
 * audit_log_start - obtain an audit buffer
 * @ctx: audit_context (may be शून्य)
 * @gfp_mask: type of allocation
 * @type: audit message type
 *
 * Returns audit_buffer poपूर्णांकer on success or शून्य on error.
 *
 * Obtain an audit buffer.  This routine करोes locking to obtain the
 * audit buffer, but then no locking is required क्रम calls to
 * audit_log_*क्रमmat.  If the task (ctx) is a task that is currently in a
 * syscall, then the syscall is marked as auditable and an audit record
 * will be written at syscall निकास.  If there is no associated task, then
 * task context (ctx) should be शून्य.
 */
काष्ठा audit_buffer *audit_log_start(काष्ठा audit_context *ctx, gfp_t gfp_mask,
				     पूर्णांक type)
अणु
	काष्ठा audit_buffer *ab;
	काष्ठा बारpec64 t;
	अचिन्हित पूर्णांक serial;

	अगर (audit_initialized != AUDIT_INITIALIZED)
		वापस शून्य;

	अगर (unlikely(!audit_filter(type, AUDIT_FILTER_EXCLUDE)))
		वापस शून्य;

	/* NOTE: करोn't ever fail/sleep on these two conditions:
	 * 1. auditd generated record - since we need auditd to drain the
	 *    queue; also, when we are checking क्रम auditd, compare PIDs using
	 *    task_tgid_vnr() since auditd_pid is set in audit_receive_msg()
	 *    using a PID anchored in the caller's namespace
	 * 2. generator holding the audit_cmd_mutex - we करोn't want to block
	 *    जबतक holding the mutex */
	अगर (!(auditd_test_task(current) || audit_ctl_owner_current())) अणु
		दीर्घ sसमय = audit_backlog_रुको_समय;

		जबतक (audit_backlog_limit &&
		       (skb_queue_len(&audit_queue) > audit_backlog_limit)) अणु
			/* wake kauditd to try and flush the queue */
			wake_up_पूर्णांकerruptible(&kauditd_रुको);

			/* sleep अगर we are allowed and we haven't exhausted our
			 * backlog रुको limit */
			अगर (gfpflags_allow_blocking(gfp_mask) && (sसमय > 0)) अणु
				दीर्घ rसमय = sसमय;

				DECLARE_WAITQUEUE(रुको, current);

				add_रुको_queue_exclusive(&audit_backlog_रुको,
							 &रुको);
				set_current_state(TASK_UNINTERRUPTIBLE);
				sसमय = schedule_समयout(rसमय);
				atomic_add(rसमय - sसमय, &audit_backlog_रुको_समय_actual);
				हटाओ_रुको_queue(&audit_backlog_रुको, &रुको);
			पूर्ण अन्यथा अणु
				अगर (audit_rate_check() && prपूर्णांकk_ratelimit())
					pr_warn("audit_backlog=%d > audit_backlog_limit=%d\n",
						skb_queue_len(&audit_queue),
						audit_backlog_limit);
				audit_log_lost("backlog limit exceeded");
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	ab = audit_buffer_alloc(ctx, gfp_mask, type);
	अगर (!ab) अणु
		audit_log_lost("out of memory in audit_log_start");
		वापस शून्य;
	पूर्ण

	audit_get_stamp(ab->ctx, &t, &serial);
	/* cancel dummy context to enable supporting records */
	अगर (ctx)
		ctx->dummy = 0;
	audit_log_क्रमmat(ab, "audit(%llu.%03lu:%u): ",
			 (अचिन्हित दीर्घ दीर्घ)t.tv_sec, t.tv_nsec/1000000, serial);

	वापस ab;
पूर्ण

/**
 * audit_expand - expand skb in the audit buffer
 * @ab: audit_buffer
 * @extra: space to add at tail of the skb
 *
 * Returns 0 (no space) on failed expansion, or available space अगर
 * successful.
 */
अटल अंतरभूत पूर्णांक audit_expand(काष्ठा audit_buffer *ab, पूर्णांक extra)
अणु
	काष्ठा sk_buff *skb = ab->skb;
	पूर्णांक oldtail = skb_tailroom(skb);
	पूर्णांक ret = pskb_expand_head(skb, 0, extra, ab->gfp_mask);
	पूर्णांक newtail = skb_tailroom(skb);

	अगर (ret < 0) अणु
		audit_log_lost("out of memory in audit_expand");
		वापस 0;
	पूर्ण

	skb->truesize += newtail - oldtail;
	वापस newtail;
पूर्ण

/*
 * Format an audit message पूर्णांकo the audit buffer.  If there isn't enough
 * room in the audit buffer, more room will be allocated and vsnprपूर्णांक
 * will be called a second समय.  Currently, we assume that a prपूर्णांकk
 * can't format message larger than 1024 bytes, so we don't either.
 */
अटल व्योम audit_log_vक्रमmat(काष्ठा audit_buffer *ab, स्थिर अक्षर *fmt,
			      बहु_सूची args)
अणु
	पूर्णांक len, avail;
	काष्ठा sk_buff *skb;
	बहु_सूची args2;

	अगर (!ab)
		वापस;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avail = skb_tailroom(skb);
	अगर (avail == 0) अणु
		avail = audit_expand(ab, AUDIT_बफ_मान);
		अगर (!avail)
			जाओ out;
	पूर्ण
	va_copy(args2, args);
	len = vsnम_लिखो(skb_tail_poपूर्णांकer(skb), avail, fmt, args);
	अगर (len >= avail) अणु
		/* The prपूर्णांकk buffer is 1024 bytes दीर्घ, so अगर we get
		 * here and AUDIT_बफ_मान is at least 1024, then we can
		 * log everything that prपूर्णांकk could have logged. */
		avail = audit_expand(ab,
			max_t(अचिन्हित, AUDIT_बफ_मान, 1+len-avail));
		अगर (!avail)
			जाओ out_बहु_पूर्ण;
		len = vsnम_लिखो(skb_tail_poपूर्णांकer(skb), avail, fmt, args2);
	पूर्ण
	अगर (len > 0)
		skb_put(skb, len);
out_बहु_पूर्ण:
	बहु_पूर्ण(args2);
out:
	वापस;
पूर्ण

/**
 * audit_log_क्रमmat - क्रमmat a message पूर्णांकo the audit buffer.
 * @ab: audit_buffer
 * @fmt: क्रमmat string
 * @...: optional parameters matching @fmt string
 *
 * All the work is करोne in audit_log_vक्रमmat.
 */
व्योम audit_log_क्रमmat(काष्ठा audit_buffer *ab, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (!ab)
		वापस;
	बहु_शुरू(args, fmt);
	audit_log_vक्रमmat(ab, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

/**
 * audit_log_n_hex - convert a buffer to hex and append it to the audit skb
 * @ab: the audit_buffer
 * @buf: buffer to convert to hex
 * @len: length of @buf to be converted
 *
 * No वापस value; failure to expand is silently ignored.
 *
 * This function will take the passed buf and convert it पूर्णांकo a string of
 * ascii hex digits. The new string is placed onto the skb.
 */
व्योम audit_log_n_hex(काष्ठा audit_buffer *ab, स्थिर अचिन्हित अक्षर *buf,
		माप_प्रकार len)
अणु
	पूर्णांक i, avail, new_len;
	अचिन्हित अक्षर *ptr;
	काष्ठा sk_buff *skb;

	अगर (!ab)
		वापस;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avail = skb_tailroom(skb);
	new_len = len<<1;
	अगर (new_len >= avail) अणु
		/* Round the buffer request up to the next multiple */
		new_len = AUDIT_बफ_मान*(((new_len-avail)/AUDIT_बफ_मान) + 1);
		avail = audit_expand(ab, new_len);
		अगर (!avail)
			वापस;
	पूर्ण

	ptr = skb_tail_poपूर्णांकer(skb);
	क्रम (i = 0; i < len; i++)
		ptr = hex_byte_pack_upper(ptr, buf[i]);
	*ptr = 0;
	skb_put(skb, len << 1); /* new string is twice the old string */
पूर्ण

/*
 * Format a string of no more than slen अक्षरacters पूर्णांकo the audit buffer,
 * enबंदd in quote marks.
 */
व्योम audit_log_n_string(काष्ठा audit_buffer *ab, स्थिर अक्षर *string,
			माप_प्रकार slen)
अणु
	पूर्णांक avail, new_len;
	अचिन्हित अक्षर *ptr;
	काष्ठा sk_buff *skb;

	अगर (!ab)
		वापस;

	BUG_ON(!ab->skb);
	skb = ab->skb;
	avail = skb_tailroom(skb);
	new_len = slen + 3;	/* enclosing quotes + null terminator */
	अगर (new_len > avail) अणु
		avail = audit_expand(ab, new_len);
		अगर (!avail)
			वापस;
	पूर्ण
	ptr = skb_tail_poपूर्णांकer(skb);
	*ptr++ = '"';
	स_नकल(ptr, string, slen);
	ptr += slen;
	*ptr++ = '"';
	*ptr = 0;
	skb_put(skb, slen + 2);	/* करोn't include null terminator */
पूर्ण

/**
 * audit_string_contains_control - करोes a string need to be logged in hex
 * @string: string to be checked
 * @len: max length of the string to check
 */
bool audit_string_contains_control(स्थिर अक्षर *string, माप_प्रकार len)
अणु
	स्थिर अचिन्हित अक्षर *p;
	क्रम (p = string; p < (स्थिर अचिन्हित अक्षर *)string + len; p++) अणु
		अगर (*p == '"' || *p < 0x21 || *p > 0x7e)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * audit_log_n_untrustedstring - log a string that may contain अक्रमom अक्षरacters
 * @ab: audit_buffer
 * @len: length of string (not including trailing null)
 * @string: string to be logged
 *
 * This code will escape a string that is passed to it अगर the string
 * contains a control अक्षरacter, unprपूर्णांकable अक्षरacter, द्विगुन quote mark,
 * or a space. Unescaped strings will start and end with a द्विगुन quote mark.
 * Strings that are escaped are prपूर्णांकed in hex (2 digits per अक्षर).
 *
 * The caller specअगरies the number of अक्षरacters in the string to log, which may
 * or may not be the entire string.
 */
व्योम audit_log_n_untrustedstring(काष्ठा audit_buffer *ab, स्थिर अक्षर *string,
				 माप_प्रकार len)
अणु
	अगर (audit_string_contains_control(string, len))
		audit_log_n_hex(ab, string, len);
	अन्यथा
		audit_log_n_string(ab, string, len);
पूर्ण

/**
 * audit_log_untrustedstring - log a string that may contain अक्रमom अक्षरacters
 * @ab: audit_buffer
 * @string: string to be logged
 *
 * Same as audit_log_n_untrustedstring(), except that म_माप is used to
 * determine string length.
 */
व्योम audit_log_untrustedstring(काष्ठा audit_buffer *ab, स्थिर अक्षर *string)
अणु
	audit_log_n_untrustedstring(ab, string, म_माप(string));
पूर्ण

/* This is a helper-function to prपूर्णांक the escaped d_path */
व्योम audit_log_d_path(काष्ठा audit_buffer *ab, स्थिर अक्षर *prefix,
		      स्थिर काष्ठा path *path)
अणु
	अक्षर *p, *pathname;

	अगर (prefix)
		audit_log_क्रमmat(ab, "%s", prefix);

	/* We will allow 11 spaces क्रम ' (deleted)' to be appended */
	pathname = kदो_स्मृति(PATH_MAX+11, ab->gfp_mask);
	अगर (!pathname) अणु
		audit_log_क्रमmat(ab, "\"<no_memory>\"");
		वापस;
	पूर्ण
	p = d_path(path, pathname, PATH_MAX+11);
	अगर (IS_ERR(p)) अणु /* Should never happen since we send PATH_MAX */
		/* FIXME: can we save some inक्रमmation here? */
		audit_log_क्रमmat(ab, "\"<too_long>\"");
	पूर्ण अन्यथा
		audit_log_untrustedstring(ab, p);
	kमुक्त(pathname);
पूर्ण

व्योम audit_log_session_info(काष्ठा audit_buffer *ab)
अणु
	अचिन्हित पूर्णांक sessionid = audit_get_sessionid(current);
	uid_t auid = from_kuid(&init_user_ns, audit_get_loginuid(current));

	audit_log_क्रमmat(ab, "auid=%u ses=%u", auid, sessionid);
पूर्ण

व्योम audit_log_key(काष्ठा audit_buffer *ab, अक्षर *key)
अणु
	audit_log_क्रमmat(ab, " key=");
	अगर (key)
		audit_log_untrustedstring(ab, key);
	अन्यथा
		audit_log_क्रमmat(ab, "(null)");
पूर्ण

पूर्णांक audit_log_task_context(काष्ठा audit_buffer *ab)
अणु
	अक्षर *ctx = शून्य;
	अचिन्हित len;
	पूर्णांक error;
	u32 sid;

	security_task_माला_लोecid_subj(current, &sid);
	अगर (!sid)
		वापस 0;

	error = security_secid_to_secctx(sid, &ctx, &len);
	अगर (error) अणु
		अगर (error != -EINVAL)
			जाओ error_path;
		वापस 0;
	पूर्ण

	audit_log_क्रमmat(ab, " subj=%s", ctx);
	security_release_secctx(ctx, len);
	वापस 0;

error_path:
	audit_panic("error in audit_log_task_context");
	वापस error;
पूर्ण
EXPORT_SYMBOL(audit_log_task_context);

व्योम audit_log_d_path_exe(काष्ठा audit_buffer *ab,
			  काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा file *exe_file;

	अगर (!mm)
		जाओ out_null;

	exe_file = get_mm_exe_file(mm);
	अगर (!exe_file)
		जाओ out_null;

	audit_log_d_path(ab, " exe=", &exe_file->f_path);
	fput(exe_file);
	वापस;
out_null:
	audit_log_क्रमmat(ab, " exe=(null)");
पूर्ण

काष्ठा tty_काष्ठा *audit_get_tty(व्योम)
अणु
	काष्ठा tty_काष्ठा *tty = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&current->sighand->siglock, flags);
	अगर (current->संकेत)
		tty = tty_kref_get(current->संकेत->tty);
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
	वापस tty;
पूर्ण

व्योम audit_put_tty(काष्ठा tty_काष्ठा *tty)
अणु
	tty_kref_put(tty);
पूर्ण

व्योम audit_log_task_info(काष्ठा audit_buffer *ab)
अणु
	स्थिर काष्ठा cred *cred;
	अक्षर comm[माप(current->comm)];
	काष्ठा tty_काष्ठा *tty;

	अगर (!ab)
		वापस;

	cred = current_cred();
	tty = audit_get_tty();
	audit_log_क्रमmat(ab,
			 " ppid=%d pid=%d auid=%u uid=%u gid=%u"
			 " euid=%u suid=%u fsuid=%u"
			 " egid=%u sgid=%u fsgid=%u tty=%s ses=%u",
			 task_ppid_nr(current),
			 task_tgid_nr(current),
			 from_kuid(&init_user_ns, audit_get_loginuid(current)),
			 from_kuid(&init_user_ns, cred->uid),
			 from_kgid(&init_user_ns, cred->gid),
			 from_kuid(&init_user_ns, cred->euid),
			 from_kuid(&init_user_ns, cred->suid),
			 from_kuid(&init_user_ns, cred->fsuid),
			 from_kgid(&init_user_ns, cred->egid),
			 from_kgid(&init_user_ns, cred->sgid),
			 from_kgid(&init_user_ns, cred->fsgid),
			 tty ? tty_name(tty) : "(none)",
			 audit_get_sessionid(current));
	audit_put_tty(tty);
	audit_log_क्रमmat(ab, " comm=");
	audit_log_untrustedstring(ab, get_task_comm(comm, current));
	audit_log_d_path_exe(ab, current->mm);
	audit_log_task_context(ab);
पूर्ण
EXPORT_SYMBOL(audit_log_task_info);

/**
 * audit_log_path_denied - report a path restriction denial
 * @type: audit message type (AUDIT_ANOM_LINK, AUDIT_ANOM_CREAT, etc)
 * @operation: specअगरic operation name
 */
व्योम audit_log_path_denied(पूर्णांक type, स्थिर अक्षर *operation)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled || audit_dummy_context())
		वापस;

	/* Generate log with subject, operation, outcome. */
	ab = audit_log_start(audit_context(), GFP_KERNEL, type);
	अगर (!ab)
		वापस;
	audit_log_क्रमmat(ab, "op=%s", operation);
	audit_log_task_info(ab);
	audit_log_क्रमmat(ab, " res=0");
	audit_log_end(ab);
पूर्ण

/* global counter which is incremented every समय something logs in */
अटल atomic_t session_id = ATOMIC_INIT(0);

अटल पूर्णांक audit_set_loginuid_perm(kuid_t loginuid)
अणु
	/* अगर we are unset, we करोn't need privs */
	अगर (!audit_loginuid_set(current))
		वापस 0;
	/* अगर AUDIT_FEATURE_LOGINUID_IMMUTABLE means never ever allow a change*/
	अगर (is_audit_feature_set(AUDIT_FEATURE_LOGINUID_IMMUTABLE))
		वापस -EPERM;
	/* it is set, you need permission */
	अगर (!capable(CAP_AUDIT_CONTROL))
		वापस -EPERM;
	/* reject अगर this is not an unset and we करोn't allow that */
	अगर (is_audit_feature_set(AUDIT_FEATURE_ONLY_UNSET_LOGINUID)
				 && uid_valid(loginuid))
		वापस -EPERM;
	वापस 0;
पूर्ण

अटल व्योम audit_log_set_loginuid(kuid_t koldloginuid, kuid_t kloginuid,
				   अचिन्हित पूर्णांक oldsessionid,
				   अचिन्हित पूर्णांक sessionid, पूर्णांक rc)
अणु
	काष्ठा audit_buffer *ab;
	uid_t uid, oldloginuid, loginuid;
	काष्ठा tty_काष्ठा *tty;

	अगर (!audit_enabled)
		वापस;

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_LOGIN);
	अगर (!ab)
		वापस;

	uid = from_kuid(&init_user_ns, task_uid(current));
	oldloginuid = from_kuid(&init_user_ns, koldloginuid);
	loginuid = from_kuid(&init_user_ns, kloginuid);
	tty = audit_get_tty();

	audit_log_क्रमmat(ab, "pid=%d uid=%u", task_tgid_nr(current), uid);
	audit_log_task_context(ab);
	audit_log_क्रमmat(ab, " old-auid=%u auid=%u tty=%s old-ses=%u ses=%u res=%d",
			 oldloginuid, loginuid, tty ? tty_name(tty) : "(none)",
			 oldsessionid, sessionid, !rc);
	audit_put_tty(tty);
	audit_log_end(ab);
पूर्ण

/**
 * audit_set_loginuid - set current task's loginuid
 * @loginuid: loginuid value
 *
 * Returns 0.
 *
 * Called (set) from fs/proc/base.c::proc_loginuid_ग_लिखो().
 */
पूर्णांक audit_set_loginuid(kuid_t loginuid)
अणु
	अचिन्हित पूर्णांक oldsessionid, sessionid = AUDIT_SID_UNSET;
	kuid_t oldloginuid;
	पूर्णांक rc;

	oldloginuid = audit_get_loginuid(current);
	oldsessionid = audit_get_sessionid(current);

	rc = audit_set_loginuid_perm(loginuid);
	अगर (rc)
		जाओ out;

	/* are we setting or clearing? */
	अगर (uid_valid(loginuid)) अणु
		sessionid = (अचिन्हित पूर्णांक)atomic_inc_वापस(&session_id);
		अगर (unlikely(sessionid == AUDIT_SID_UNSET))
			sessionid = (अचिन्हित पूर्णांक)atomic_inc_वापस(&session_id);
	पूर्ण

	current->sessionid = sessionid;
	current->loginuid = loginuid;
out:
	audit_log_set_loginuid(oldloginuid, loginuid, oldsessionid, sessionid, rc);
	वापस rc;
पूर्ण

/**
 * audit_संकेत_info - record संकेत info क्रम shutting करोwn audit subप्रणाली
 * @sig: संकेत value
 * @t: task being संकेतed
 *
 * If the audit subप्रणाली is being terminated, record the task (pid)
 * and uid that is करोing that.
 */
पूर्णांक audit_संकेत_info(पूर्णांक sig, काष्ठा task_काष्ठा *t)
अणु
	kuid_t uid = current_uid(), auid;

	अगर (auditd_test_task(t) &&
	    (sig == संक_इति || sig == SIGHUP ||
	     sig == SIGUSR1 || sig == SIGUSR2)) अणु
		audit_sig_pid = task_tgid_nr(current);
		auid = audit_get_loginuid(current);
		अगर (uid_valid(auid))
			audit_sig_uid = auid;
		अन्यथा
			audit_sig_uid = uid;
		security_task_माला_लोecid_subj(current, &audit_sig_sid);
	पूर्ण

	वापस audit_संकेत_info_syscall(t);
पूर्ण

/**
 * audit_log_end - end one audit record
 * @ab: the audit_buffer
 *
 * We can not करो a netlink send inside an irq context because it blocks (last
 * arg, flags, is not set to MSG_DONTWAIT), so the audit buffer is placed on a
 * queue and a kthपढ़ो is scheduled to हटाओ them from the queue outside the
 * irq context.  May be called in any context.
 */
व्योम audit_log_end(काष्ठा audit_buffer *ab)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *nlh;

	अगर (!ab)
		वापस;

	अगर (audit_rate_check()) अणु
		skb = ab->skb;
		ab->skb = शून्य;

		/* setup the netlink header, see the comments in
		 * kauditd_send_multicast_skb() क्रम length quirks */
		nlh = nlmsg_hdr(skb);
		nlh->nlmsg_len = skb->len - NLMSG_HDRLEN;

		/* queue the netlink packet and poke the kauditd thपढ़ो */
		skb_queue_tail(&audit_queue, skb);
		wake_up_पूर्णांकerruptible(&kauditd_रुको);
	पूर्ण अन्यथा
		audit_log_lost("rate limit exceeded");

	audit_buffer_मुक्त(ab);
पूर्ण

/**
 * audit_log - Log an audit record
 * @ctx: audit context
 * @gfp_mask: type of allocation
 * @type: audit message type
 * @fmt: क्रमmat string to use
 * @...: variable parameters matching the क्रमmat string
 *
 * This is a convenience function that calls audit_log_start,
 * audit_log_vक्रमmat, and audit_log_end.  It may be called
 * in any context.
 */
व्योम audit_log(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type,
	       स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा audit_buffer *ab;
	बहु_सूची args;

	ab = audit_log_start(ctx, gfp_mask, type);
	अगर (ab) अणु
		बहु_शुरू(args, fmt);
		audit_log_vक्रमmat(ab, fmt, args);
		बहु_पूर्ण(args);
		audit_log_end(ab);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(audit_log_start);
EXPORT_SYMBOL(audit_log_end);
EXPORT_SYMBOL(audit_log_क्रमmat);
EXPORT_SYMBOL(audit_log);
