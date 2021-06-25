<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * cn_proc.c - process events connector
 *
 * Copyright (C) Matt Helsley, IBM Corp. 2005
 * Based on cn_विभाजन.c by Guillaume Thouvenin <guillaume.thouvenin@bull.net>
 * Original copyright notice follows:
 * Copyright (C) 2005 BULL SA.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/init.h>
#समावेश <linux/connector.h>
#समावेश <linux/gfp.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/atomic.h>
#समावेश <linux/pid_namespace.h>

#समावेश <linux/cn_proc.h>
#समावेश <linux/local_lock.h>

/*
 * Size of a cn_msg followed by a proc_event काष्ठाure.  Since the
 * माप काष्ठा cn_msg is a multiple of 4 bytes, but not 8 bytes, we
 * add one 4-byte word to the size here, and then start the actual
 * cn_msg काष्ठाure 4 bytes पूर्णांकo the stack buffer.  The result is that
 * the immediately following proc_event काष्ठाure is aligned to 8 bytes.
 */
#घोषणा CN_PROC_MSG_SIZE (माप(काष्ठा cn_msg) + माप(काष्ठा proc_event) + 4)

/* See comment above; we test our assumption about माप काष्ठा cn_msg here. */
अटल अंतरभूत काष्ठा cn_msg *buffer_to_cn_msg(__u8 *buffer)
अणु
	BUILD_BUG_ON(माप(काष्ठा cn_msg) != 20);
	वापस (काष्ठा cn_msg *)(buffer + 4);
पूर्ण

अटल atomic_t proc_event_num_listeners = ATOMIC_INIT(0);
अटल काष्ठा cb_id cn_proc_event_id = अणु CN_IDX_PROC, CN_VAL_PROC पूर्ण;

/* local_event.count is used as the sequence number of the netlink message */
काष्ठा local_event अणु
	local_lock_t lock;
	__u32 count;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा local_event, local_event) = अणु
	.lock = INIT_LOCAL_LOCK(lock),
पूर्ण;

अटल अंतरभूत व्योम send_msg(काष्ठा cn_msg *msg)
अणु
	local_lock(&local_event.lock);

	msg->seq = __this_cpu_inc_वापस(local_event.count) - 1;
	((काष्ठा proc_event *)msg->data)->cpu = smp_processor_id();

	/*
	 * local_lock() disables preemption during send to ensure the messages
	 * are ordered according to their sequence numbers.
	 *
	 * If cn_netlink_send() fails, the data is not sent.
	 */
	cn_netlink_send(msg, 0, CN_IDX_PROC, GFP_NOWAIT);

	local_unlock(&local_event.lock);
पूर्ण

व्योम proc_विभाजन_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);
	काष्ठा task_काष्ठा *parent;

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_FORK;
	rcu_पढ़ो_lock();
	parent = rcu_dereference(task->real_parent);
	ev->event_data.विभाजन.parent_pid = parent->pid;
	ev->event_data.विभाजन.parent_tgid = parent->tgid;
	rcu_पढ़ो_unlock();
	ev->event_data.विभाजन.child_pid = task->pid;
	ev->event_data.विभाजन.child_tgid = task->tgid;

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_exec_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_EXEC;
	ev->event_data.exec.process_pid = task->pid;
	ev->event_data.exec.process_tgid = task->tgid;

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_id_connector(काष्ठा task_काष्ठा *task, पूर्णांक which_id)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);
	स्थिर काष्ठा cred *cred;

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->what = which_id;
	ev->event_data.id.process_pid = task->pid;
	ev->event_data.id.process_tgid = task->tgid;
	rcu_पढ़ो_lock();
	cred = __task_cred(task);
	अगर (which_id == PROC_EVENT_UID) अणु
		ev->event_data.id.r.ruid = from_kuid_munged(&init_user_ns, cred->uid);
		ev->event_data.id.e.euid = from_kuid_munged(&init_user_ns, cred->euid);
	पूर्ण अन्यथा अगर (which_id == PROC_EVENT_GID) अणु
		ev->event_data.id.r.rgid = from_kgid_munged(&init_user_ns, cred->gid);
		ev->event_data.id.e.egid = from_kgid_munged(&init_user_ns, cred->egid);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
	ev->बारtamp_ns = kसमय_get_ns();

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_sid_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_SID;
	ev->event_data.sid.process_pid = task->pid;
	ev->event_data.sid.process_tgid = task->tgid;

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_ptrace_connector(काष्ठा task_काष्ठा *task, पूर्णांक ptrace_id)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_PTRACE;
	ev->event_data.ptrace.process_pid  = task->pid;
	ev->event_data.ptrace.process_tgid = task->tgid;
	अगर (ptrace_id == PTRACE_ATTACH) अणु
		ev->event_data.ptrace.tracer_pid  = current->pid;
		ev->event_data.ptrace.tracer_tgid = current->tgid;
	पूर्ण अन्यथा अगर (ptrace_id == PTRACE_DETACH) अणु
		ev->event_data.ptrace.tracer_pid  = 0;
		ev->event_data.ptrace.tracer_tgid = 0;
	पूर्ण अन्यथा
		वापस;

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_comm_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_COMM;
	ev->event_data.comm.process_pid  = task->pid;
	ev->event_data.comm.process_tgid = task->tgid;
	get_task_comm(ev->event_data.comm.comm, task);

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_coredump_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	काष्ठा task_काष्ठा *parent;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_COREDUMP;
	ev->event_data.coredump.process_pid = task->pid;
	ev->event_data.coredump.process_tgid = task->tgid;

	rcu_पढ़ो_lock();
	अगर (pid_alive(task)) अणु
		parent = rcu_dereference(task->real_parent);
		ev->event_data.coredump.parent_pid = parent->pid;
		ev->event_data.coredump.parent_tgid = parent->tgid;
	पूर्ण
	rcu_पढ़ो_unlock();

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

व्योम proc_निकास_connector(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	काष्ठा task_काष्ठा *parent;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	ev->बारtamp_ns = kसमय_get_ns();
	ev->what = PROC_EVENT_EXIT;
	ev->event_data.निकास.process_pid = task->pid;
	ev->event_data.निकास.process_tgid = task->tgid;
	ev->event_data.निकास.निकास_code = task->निकास_code;
	ev->event_data.निकास.निकास_संकेत = task->निकास_संकेत;

	rcu_पढ़ो_lock();
	अगर (pid_alive(task)) अणु
		parent = rcu_dereference(task->real_parent);
		ev->event_data.निकास.parent_pid = parent->pid;
		ev->event_data.निकास.parent_tgid = parent->tgid;
	पूर्ण
	rcu_पढ़ो_unlock();

	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = 0; /* not used */
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

/*
 * Send an acknowledgement message to userspace
 *
 * Use 0 क्रम success, EFOO otherwise.
 * Note: this is the negative of conventional kernel error
 * values because it's not being वापसed via syscall वापस
 * mechanisms.
 */
अटल व्योम cn_proc_ack(पूर्णांक err, पूर्णांक rcvd_seq, पूर्णांक rcvd_ack)
अणु
	काष्ठा cn_msg *msg;
	काष्ठा proc_event *ev;
	__u8 buffer[CN_PROC_MSG_SIZE] __aligned(8);

	अगर (atomic_पढ़ो(&proc_event_num_listeners) < 1)
		वापस;

	msg = buffer_to_cn_msg(buffer);
	ev = (काष्ठा proc_event *)msg->data;
	स_रखो(&ev->event_data, 0, माप(ev->event_data));
	msg->seq = rcvd_seq;
	ev->बारtamp_ns = kसमय_get_ns();
	ev->cpu = -1;
	ev->what = PROC_EVENT_NONE;
	ev->event_data.ack.err = err;
	स_नकल(&msg->id, &cn_proc_event_id, माप(msg->id));
	msg->ack = rcvd_ack + 1;
	msg->len = माप(*ev);
	msg->flags = 0; /* not used */
	send_msg(msg);
पूर्ण

/**
 * cn_proc_mcast_ctl
 * @data: message sent from userspace via the connector
 */
अटल व्योम cn_proc_mcast_ctl(काष्ठा cn_msg *msg,
			      काष्ठा netlink_skb_parms *nsp)
अणु
	क्रमागत proc_cn_mcast_op *mc_op = शून्य;
	पूर्णांक err = 0;

	अगर (msg->len != माप(*mc_op))
		वापस;

	/* 
	 * Events are reported with respect to the initial pid
	 * and user namespaces so ignore requestors from
	 * other namespaces.
	 */
	अगर ((current_user_ns() != &init_user_ns) ||
	    (task_active_pid_ns(current) != &init_pid_ns))
		वापस;

	/* Can only change अगर privileged. */
	अगर (!__netlink_ns_capable(nsp, &init_user_ns, CAP_NET_ADMIN)) अणु
		err = EPERM;
		जाओ out;
	पूर्ण

	mc_op = (क्रमागत proc_cn_mcast_op *)msg->data;
	चयन (*mc_op) अणु
	हाल PROC_CN_MCAST_LISTEN:
		atomic_inc(&proc_event_num_listeners);
		अवरोध;
	हाल PROC_CN_MCAST_IGNORE:
		atomic_dec(&proc_event_num_listeners);
		अवरोध;
	शेष:
		err = EINVAL;
		अवरोध;
	पूर्ण

out:
	cn_proc_ack(err, msg->seq, msg->ack);
पूर्ण

/*
 * cn_proc_init - initialization entry poपूर्णांक
 *
 * Adds the connector callback to the connector driver.
 */
अटल पूर्णांक __init cn_proc_init(व्योम)
अणु
	पूर्णांक err = cn_add_callback(&cn_proc_event_id,
				  "cn_proc",
				  &cn_proc_mcast_ctl);
	अगर (err) अणु
		pr_warn("cn_proc failed to register\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(cn_proc_init);
