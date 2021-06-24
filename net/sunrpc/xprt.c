<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/net/sunrpc/xprt.c
 *
 *  This is a generic RPC call पूर्णांकerface supporting congestion aव्योमance,
 *  and asynchronous calls.
 *
 *  The पूर्णांकerface works like this:
 *
 *  -	When a process places a call, it allocates a request slot अगर
 *	one is available. Otherwise, it sleeps on the backlog queue
 *	(xprt_reserve).
 *  -	Next, the caller माला_दो together the RPC message, stuffs it पूर्णांकo
 *	the request काष्ठा, and calls xprt_transmit().
 *  -	xprt_transmit sends the message and installs the caller on the
 *	transport's रुको list. At the same समय, अगर a reply is expected,
 *	it installs a समयr that is run after the packet's समयout has
 *	expired.
 *  -	When a packet arrives, the data_पढ़ोy handler walks the list of
 *	pending requests क्रम that transport. If a matching XID is found, the
 *	caller is woken up, and the समयr हटाओd.
 *  -	When no reply arrives within the समयout पूर्णांकerval, the समयr is
 *	fired by the kernel and runs xprt_समयr(). It either adjusts the
 *	समयout values (minor समयout) or wakes up the caller with a status
 *	of -ETIMEDOUT.
 *  -	When the caller receives a notअगरication from RPC that a reply arrived,
 *	it should release the RPC slot, and process the reply.
 *	If the call समयd out, it may choose to retry the operation by
 *	adjusting the initial समयout value, and simply calling rpc_call
 *	again.
 *
 *  Support क्रम async RPC is करोne through a set of RPC-specअगरic scheduling
 *  primitives that `transparently' work क्रम processes as well as async
 *  tasks that rely on callbacks.
 *
 *  Copyright (C) 1995-1997, Olaf Kirch <okir@monad.swb.de>
 *
 *  Transport चयन API copyright (C) 2005, Chuck Lever <cel@netapp.com>
 */

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/net.h>
#समावेश <linux/kसमय.स>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/mm.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "sunrpc.h"

/*
 * Local variables
 */

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_XPRT
#पूर्ण_अगर

/*
 * Local functions
 */
अटल व्योम	 xprt_init(काष्ठा rpc_xprt *xprt, काष्ठा net *net);
अटल __be32	xprt_alloc_xid(काष्ठा rpc_xprt *xprt);
अटल व्योम	 xprt_destroy(काष्ठा rpc_xprt *xprt);
अटल व्योम	 xprt_request_init(काष्ठा rpc_task *task);

अटल DEFINE_SPINLOCK(xprt_list_lock);
अटल LIST_HEAD(xprt_list);

अटल अचिन्हित दीर्घ xprt_request_समयout(स्थिर काष्ठा rpc_rqst *req)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + req->rq_समयout;

	अगर (समय_beक्रमe(समयout, req->rq_majorसमयo))
		वापस समयout;
	वापस req->rq_majorसमयo;
पूर्ण

/**
 * xprt_रेजिस्टर_transport - रेजिस्टर a transport implementation
 * @transport: transport to रेजिस्टर
 *
 * If a transport implementation is loaded as a kernel module, it can
 * call this पूर्णांकerface to make itself known to the RPC client.
 *
 * Returns:
 * 0:		transport successfully रेजिस्टरed
 * -EEXIST:	transport alपढ़ोy रेजिस्टरed
 * -EINVAL:	transport module being unloaded
 */
पूर्णांक xprt_रेजिस्टर_transport(काष्ठा xprt_class *transport)
अणु
	काष्ठा xprt_class *t;
	पूर्णांक result;

	result = -EEXIST;
	spin_lock(&xprt_list_lock);
	list_क्रम_each_entry(t, &xprt_list, list) अणु
		/* करोn't रेजिस्टर the same transport class twice */
		अगर (t->ident == transport->ident)
			जाओ out;
	पूर्ण

	list_add_tail(&transport->list, &xprt_list);
	prपूर्णांकk(KERN_INFO "RPC: Registered %s transport module.\n",
	       transport->name);
	result = 0;

out:
	spin_unlock(&xprt_list_lock);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_रेजिस्टर_transport);

/**
 * xprt_unरेजिस्टर_transport - unरेजिस्टर a transport implementation
 * @transport: transport to unरेजिस्टर
 *
 * Returns:
 * 0:		transport successfully unरेजिस्टरed
 * -ENOENT:	transport never रेजिस्टरed
 */
पूर्णांक xprt_unरेजिस्टर_transport(काष्ठा xprt_class *transport)
अणु
	काष्ठा xprt_class *t;
	पूर्णांक result;

	result = 0;
	spin_lock(&xprt_list_lock);
	list_क्रम_each_entry(t, &xprt_list, list) अणु
		अगर (t == transport) अणु
			prपूर्णांकk(KERN_INFO
				"RPC: Unregistered %s transport module.\n",
				transport->name);
			list_del_init(&transport->list);
			जाओ out;
		पूर्ण
	पूर्ण
	result = -ENOENT;

out:
	spin_unlock(&xprt_list_lock);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_unरेजिस्टर_transport);

अटल व्योम
xprt_class_release(स्थिर काष्ठा xprt_class *t)
अणु
	module_put(t->owner);
पूर्ण

अटल स्थिर काष्ठा xprt_class *
xprt_class_find_by_ident_locked(पूर्णांक ident)
अणु
	स्थिर काष्ठा xprt_class *t;

	list_क्रम_each_entry(t, &xprt_list, list) अणु
		अगर (t->ident != ident)
			जारी;
		अगर (!try_module_get(t->owner))
			जारी;
		वापस t;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा xprt_class *
xprt_class_find_by_ident(पूर्णांक ident)
अणु
	स्थिर काष्ठा xprt_class *t;

	spin_lock(&xprt_list_lock);
	t = xprt_class_find_by_ident_locked(ident);
	spin_unlock(&xprt_list_lock);
	वापस t;
पूर्ण

अटल स्थिर काष्ठा xprt_class *
xprt_class_find_by_netid_locked(स्थिर अक्षर *netid)
अणु
	स्थिर काष्ठा xprt_class *t;
	अचिन्हित पूर्णांक i;

	list_क्रम_each_entry(t, &xprt_list, list) अणु
		क्रम (i = 0; t->netid[i][0] != '\0'; i++) अणु
			अगर (म_भेद(t->netid[i], netid) != 0)
				जारी;
			अगर (!try_module_get(t->owner))
				जारी;
			वापस t;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा xprt_class *
xprt_class_find_by_netid(स्थिर अक्षर *netid)
अणु
	स्थिर काष्ठा xprt_class *t;

	spin_lock(&xprt_list_lock);
	t = xprt_class_find_by_netid_locked(netid);
	अगर (!t) अणु
		spin_unlock(&xprt_list_lock);
		request_module("rpc%s", netid);
		spin_lock(&xprt_list_lock);
		t = xprt_class_find_by_netid_locked(netid);
	पूर्ण
	spin_unlock(&xprt_list_lock);
	वापस t;
पूर्ण

/**
 * xprt_find_transport_ident - convert a netid पूर्णांकo a transport identअगरier
 * @netid: transport to load
 *
 * Returns:
 * > 0:		transport identअगरier
 * -ENOENT:	transport module not available
 */
पूर्णांक xprt_find_transport_ident(स्थिर अक्षर *netid)
अणु
	स्थिर काष्ठा xprt_class *t;
	पूर्णांक ret;

	t = xprt_class_find_by_netid(netid);
	अगर (!t)
		वापस -ENOENT;
	ret = t->ident;
	xprt_class_release(t);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_find_transport_ident);

अटल व्योम xprt_clear_locked(काष्ठा rpc_xprt *xprt)
अणु
	xprt->snd_task = शून्य;
	अगर (!test_bit(XPRT_CLOSE_WAIT, &xprt->state)) अणु
		smp_mb__beक्रमe_atomic();
		clear_bit(XPRT_LOCKED, &xprt->state);
		smp_mb__after_atomic();
	पूर्ण अन्यथा
		queue_work(xprtiod_workqueue, &xprt->task_cleanup);
पूर्ण

/**
 * xprt_reserve_xprt - serialize ग_लिखो access to transports
 * @task: task that is requesting access to the transport
 * @xprt: poपूर्णांकer to the target transport
 *
 * This prevents mixing the payload of separate requests, and prevents
 * transport connects from colliding with ग_लिखोs.  No congestion control
 * is provided.
 */
पूर्णांक xprt_reserve_xprt(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state)) अणु
		अगर (task == xprt->snd_task)
			जाओ out_locked;
		जाओ out_sleep;
	पूर्ण
	अगर (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		जाओ out_unlock;
	xprt->snd_task = task;

out_locked:
	trace_xprt_reserve_xprt(xprt, task);
	वापस 1;

out_unlock:
	xprt_clear_locked(xprt);
out_sleep:
	task->tk_status = -EAGAIN;
	अगर  (RPC_IS_SOFT(task))
		rpc_sleep_on_समयout(&xprt->sending, task, शून्य,
				xprt_request_समयout(req));
	अन्यथा
		rpc_sleep_on(&xprt->sending, task, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_reserve_xprt);

अटल bool
xprt_need_congestion_winकरोw_रुको(काष्ठा rpc_xprt *xprt)
अणु
	वापस test_bit(XPRT_CWND_WAIT, &xprt->state);
पूर्ण

अटल व्योम
xprt_set_congestion_winकरोw_रुको(काष्ठा rpc_xprt *xprt)
अणु
	अगर (!list_empty(&xprt->xmit_queue)) अणु
		/* Peek at head of queue to see अगर it can make progress */
		अगर (list_first_entry(&xprt->xmit_queue, काष्ठा rpc_rqst,
					rq_xmit)->rq_cong)
			वापस;
	पूर्ण
	set_bit(XPRT_CWND_WAIT, &xprt->state);
पूर्ण

अटल व्योम
xprt_test_and_clear_congestion_winकरोw_रुको(काष्ठा rpc_xprt *xprt)
अणु
	अगर (!RPCXPRT_CONGESTED(xprt))
		clear_bit(XPRT_CWND_WAIT, &xprt->state);
पूर्ण

/*
 * xprt_reserve_xprt_cong - serialize ग_लिखो access to transports
 * @task: task that is requesting access to the transport
 *
 * Same as xprt_reserve_xprt, but Van Jacobson congestion control is
 * पूर्णांकegrated पूर्णांकo the decision of whether a request is allowed to be
 * woken up and given access to the transport.
 * Note that the lock is only granted अगर we know there are मुक्त slots.
 */
पूर्णांक xprt_reserve_xprt_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state)) अणु
		अगर (task == xprt->snd_task)
			जाओ out_locked;
		जाओ out_sleep;
	पूर्ण
	अगर (req == शून्य) अणु
		xprt->snd_task = task;
		जाओ out_locked;
	पूर्ण
	अगर (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		जाओ out_unlock;
	अगर (!xprt_need_congestion_winकरोw_रुको(xprt)) अणु
		xprt->snd_task = task;
		जाओ out_locked;
	पूर्ण
out_unlock:
	xprt_clear_locked(xprt);
out_sleep:
	task->tk_status = -EAGAIN;
	अगर (RPC_IS_SOFT(task))
		rpc_sleep_on_समयout(&xprt->sending, task, शून्य,
				xprt_request_समयout(req));
	अन्यथा
		rpc_sleep_on(&xprt->sending, task, शून्य);
	वापस 0;
out_locked:
	trace_xprt_reserve_cong(xprt, task);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_reserve_xprt_cong);

अटल अंतरभूत पूर्णांक xprt_lock_ग_लिखो(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	पूर्णांक retval;

	अगर (test_bit(XPRT_LOCKED, &xprt->state) && xprt->snd_task == task)
		वापस 1;
	spin_lock(&xprt->transport_lock);
	retval = xprt->ops->reserve_xprt(xprt, task);
	spin_unlock(&xprt->transport_lock);
	वापस retval;
पूर्ण

अटल bool __xprt_lock_ग_लिखो_func(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा rpc_xprt *xprt = data;

	xprt->snd_task = task;
	वापस true;
पूर्ण

अटल व्योम __xprt_lock_ग_लिखो_next(काष्ठा rpc_xprt *xprt)
अणु
	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state))
		वापस;
	अगर (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		जाओ out_unlock;
	अगर (rpc_wake_up_first_on_wq(xprtiod_workqueue, &xprt->sending,
				__xprt_lock_ग_लिखो_func, xprt))
		वापस;
out_unlock:
	xprt_clear_locked(xprt);
पूर्ण

अटल व्योम __xprt_lock_ग_लिखो_next_cong(काष्ठा rpc_xprt *xprt)
अणु
	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state))
		वापस;
	अगर (test_bit(XPRT_WRITE_SPACE, &xprt->state))
		जाओ out_unlock;
	अगर (xprt_need_congestion_winकरोw_रुको(xprt))
		जाओ out_unlock;
	अगर (rpc_wake_up_first_on_wq(xprtiod_workqueue, &xprt->sending,
				__xprt_lock_ग_लिखो_func, xprt))
		वापस;
out_unlock:
	xprt_clear_locked(xprt);
पूर्ण

/**
 * xprt_release_xprt - allow other requests to use a transport
 * @xprt: transport with other tasks potentially रुकोing
 * @task: task that is releasing access to the transport
 *
 * Note that "task" can be शून्य.  No congestion control is provided.
 */
व्योम xprt_release_xprt(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	अगर (xprt->snd_task == task) अणु
		xprt_clear_locked(xprt);
		__xprt_lock_ग_लिखो_next(xprt);
	पूर्ण
	trace_xprt_release_xprt(xprt, task);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_release_xprt);

/**
 * xprt_release_xprt_cong - allow other requests to use a transport
 * @xprt: transport with other tasks potentially रुकोing
 * @task: task that is releasing access to the transport
 *
 * Note that "task" can be शून्य.  Another task is awoken to use the
 * transport अगर the transport's congestion winकरोw allows it.
 */
व्योम xprt_release_xprt_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	अगर (xprt->snd_task == task) अणु
		xprt_clear_locked(xprt);
		__xprt_lock_ग_लिखो_next_cong(xprt);
	पूर्ण
	trace_xprt_release_cong(xprt, task);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_release_xprt_cong);

अटल अंतरभूत व्योम xprt_release_ग_लिखो(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	अगर (xprt->snd_task != task)
		वापस;
	spin_lock(&xprt->transport_lock);
	xprt->ops->release_xprt(xprt, task);
	spin_unlock(&xprt->transport_lock);
पूर्ण

/*
 * Van Jacobson congestion aव्योमance. Check अगर the congestion winकरोw
 * overflowed. Put the task to sleep अगर this is the हाल.
 */
अटल पूर्णांक
__xprt_get_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	अगर (req->rq_cong)
		वापस 1;
	trace_xprt_get_cong(xprt, req->rq_task);
	अगर (RPCXPRT_CONGESTED(xprt)) अणु
		xprt_set_congestion_winकरोw_रुको(xprt);
		वापस 0;
	पूर्ण
	req->rq_cong = 1;
	xprt->cong += RPC_CWNDSCALE;
	वापस 1;
पूर्ण

/*
 * Adjust the congestion winकरोw, and wake up the next task
 * that has been sleeping due to congestion
 */
अटल व्योम
__xprt_put_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	अगर (!req->rq_cong)
		वापस;
	req->rq_cong = 0;
	xprt->cong -= RPC_CWNDSCALE;
	xprt_test_and_clear_congestion_winकरोw_रुको(xprt);
	trace_xprt_put_cong(xprt, req->rq_task);
	__xprt_lock_ग_लिखो_next_cong(xprt);
पूर्ण

/**
 * xprt_request_get_cong - Request congestion control credits
 * @xprt: poपूर्णांकer to transport
 * @req: poपूर्णांकer to RPC request
 *
 * Useful क्रम transports that require congestion control.
 */
bool
xprt_request_get_cong(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	bool ret = false;

	अगर (req->rq_cong)
		वापस true;
	spin_lock(&xprt->transport_lock);
	ret = __xprt_get_cong(xprt, req) != 0;
	spin_unlock(&xprt->transport_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_request_get_cong);

/**
 * xprt_release_rqst_cong - housekeeping when request is complete
 * @task: RPC request that recently completed
 *
 * Useful क्रम transports that require congestion control.
 */
व्योम xprt_release_rqst_cong(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	__xprt_put_cong(req->rq_xprt, req);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_release_rqst_cong);

अटल व्योम xprt_clear_congestion_winकरोw_रुको_locked(काष्ठा rpc_xprt *xprt)
अणु
	अगर (test_and_clear_bit(XPRT_CWND_WAIT, &xprt->state))
		__xprt_lock_ग_लिखो_next_cong(xprt);
पूर्ण

/*
 * Clear the congestion winकरोw रुको flag and wake up the next
 * entry on xprt->sending
 */
अटल व्योम
xprt_clear_congestion_winकरोw_रुको(काष्ठा rpc_xprt *xprt)
अणु
	अगर (test_and_clear_bit(XPRT_CWND_WAIT, &xprt->state)) अणु
		spin_lock(&xprt->transport_lock);
		__xprt_lock_ग_लिखो_next_cong(xprt);
		spin_unlock(&xprt->transport_lock);
	पूर्ण
पूर्ण

/**
 * xprt_adjust_cwnd - adjust transport congestion winकरोw
 * @xprt: poपूर्णांकer to xprt
 * @task: recently completed RPC request used to adjust winकरोw
 * @result: result code of completed RPC request
 *
 * The transport code मुख्यtains an estimate on the maximum number of out-
 * standing RPC requests, using a smoothed version of the congestion
 * aव्योमance implemented in 44BSD. This is basically the Van Jacobson
 * congestion algorithm: If a retransmit occurs, the congestion winकरोw is
 * halved; otherwise, it is incremented by 1/cwnd when
 *
 *	-	a reply is received and
 *	-	a full number of requests are outstanding and
 *	-	the congestion winकरोw hasn't been updated recently.
 */
व्योम xprt_adjust_cwnd(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task, पूर्णांक result)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	अचिन्हित दीर्घ cwnd = xprt->cwnd;

	अगर (result >= 0 && cwnd <= xprt->cong) अणु
		/* The (cwnd >> 1) term makes sure
		 * the result माला_लो rounded properly. */
		cwnd += (RPC_CWNDSCALE * RPC_CWNDSCALE + (cwnd >> 1)) / cwnd;
		अगर (cwnd > RPC_MAXCWND(xprt))
			cwnd = RPC_MAXCWND(xprt);
		__xprt_lock_ग_लिखो_next_cong(xprt);
	पूर्ण अन्यथा अगर (result == -ETIMEDOUT) अणु
		cwnd >>= 1;
		अगर (cwnd < RPC_CWNDSCALE)
			cwnd = RPC_CWNDSCALE;
	पूर्ण
	dprपूर्णांकk("RPC:       cong %ld, cwnd was %ld, now %ld\n",
			xprt->cong, xprt->cwnd, cwnd);
	xprt->cwnd = cwnd;
	__xprt_put_cong(xprt, req);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_adjust_cwnd);

/**
 * xprt_wake_pending_tasks - wake all tasks on a transport's pending queue
 * @xprt: transport with रुकोing tasks
 * @status: result code to plant in each task beक्रमe waking it
 *
 */
व्योम xprt_wake_pending_tasks(काष्ठा rpc_xprt *xprt, पूर्णांक status)
अणु
	अगर (status < 0)
		rpc_wake_up_status(&xprt->pending, status);
	अन्यथा
		rpc_wake_up(&xprt->pending);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_wake_pending_tasks);

/**
 * xprt_रुको_क्रम_buffer_space - रुको क्रम transport output buffer to clear
 * @xprt: transport
 *
 * Note that we only set the समयr क्रम the हाल of RPC_IS_SOFT(), since
 * we करोn't in general want to क्रमce a socket disconnection due to
 * an incomplete RPC call transmission.
 */
व्योम xprt_रुको_क्रम_buffer_space(काष्ठा rpc_xprt *xprt)
अणु
	set_bit(XPRT_WRITE_SPACE, &xprt->state);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_रुको_क्रम_buffer_space);

अटल bool
xprt_clear_ग_लिखो_space_locked(काष्ठा rpc_xprt *xprt)
अणु
	अगर (test_and_clear_bit(XPRT_WRITE_SPACE, &xprt->state)) अणु
		__xprt_lock_ग_लिखो_next(xprt);
		dprपूर्णांकk("RPC:       write space: waking waiting task on "
				"xprt %p\n", xprt);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * xprt_ग_लिखो_space - wake the task रुकोing क्रम transport output buffer space
 * @xprt: transport with रुकोing tasks
 *
 * Can be called in a soft IRQ context, so xprt_ग_लिखो_space never sleeps.
 */
bool xprt_ग_लिखो_space(काष्ठा rpc_xprt *xprt)
अणु
	bool ret;

	अगर (!test_bit(XPRT_WRITE_SPACE, &xprt->state))
		वापस false;
	spin_lock(&xprt->transport_lock);
	ret = xprt_clear_ग_लिखो_space_locked(xprt);
	spin_unlock(&xprt->transport_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_ग_लिखो_space);

अटल अचिन्हित दीर्घ xprt_असल_kसमय_प्रकारo_jअगरfies(kसमय_प्रकार असलसमय)
अणु
	s64 delta = kसमय_प्रकारo_ns(kसमय_get() - असलसमय);
	वापस likely(delta >= 0) ?
		jअगरfies - nsecs_to_jअगरfies(delta) :
		jअगरfies + nsecs_to_jअगरfies(-delta);
पूर्ण

अटल अचिन्हित दीर्घ xprt_calc_majorसमयo(काष्ठा rpc_rqst *req)
अणु
	स्थिर काष्ठा rpc_समयout *to = req->rq_task->tk_client->cl_समयout;
	अचिन्हित दीर्घ majorसमयo = req->rq_समयout;

	अगर (to->to_exponential)
		majorसमयo <<= to->to_retries;
	अन्यथा
		majorसमयo += to->to_increment * to->to_retries;
	अगर (majorसमयo > to->to_maxval || majorसमयo == 0)
		majorसमयo = to->to_maxval;
	वापस majorसमयo;
पूर्ण

अटल व्योम xprt_reset_majorसमयo(काष्ठा rpc_rqst *req)
अणु
	req->rq_majorसमयo += xprt_calc_majorसमयo(req);
पूर्ण

अटल व्योम xprt_reset_minorसमयo(काष्ठा rpc_rqst *req)
अणु
	req->rq_minorसमयo += req->rq_समयout;
पूर्ण

अटल व्योम xprt_init_majorसमयo(काष्ठा rpc_task *task, काष्ठा rpc_rqst *req)
अणु
	अचिन्हित दीर्घ समय_init;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (likely(xprt && xprt_connected(xprt)))
		समय_init = jअगरfies;
	अन्यथा
		समय_init = xprt_असल_kसमय_प्रकारo_jअगरfies(task->tk_start);
	req->rq_समयout = task->tk_client->cl_समयout->to_initval;
	req->rq_majorसमयo = समय_init + xprt_calc_majorसमयo(req);
	req->rq_minorसमयo = समय_init + req->rq_समयout;
पूर्ण

/**
 * xprt_adjust_समयout - adjust समयout values क्रम next retransmit
 * @req: RPC request containing parameters to use क्रम the adjusपंचांगent
 *
 */
पूर्णांक xprt_adjust_समयout(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	स्थिर काष्ठा rpc_समयout *to = req->rq_task->tk_client->cl_समयout;
	पूर्णांक status = 0;

	अगर (समय_beक्रमe(jअगरfies, req->rq_majorसमयo)) अणु
		अगर (समय_beक्रमe(jअगरfies, req->rq_minorसमयo))
			वापस status;
		अगर (to->to_exponential)
			req->rq_समयout <<= 1;
		अन्यथा
			req->rq_समयout += to->to_increment;
		अगर (to->to_maxval && req->rq_समयout >= to->to_maxval)
			req->rq_समयout = to->to_maxval;
		req->rq_retries++;
	पूर्ण अन्यथा अणु
		req->rq_समयout = to->to_initval;
		req->rq_retries = 0;
		xprt_reset_majorसमयo(req);
		/* Reset the RTT counters == "slow start" */
		spin_lock(&xprt->transport_lock);
		rpc_init_rtt(req->rq_task->tk_client->cl_rtt, to->to_initval);
		spin_unlock(&xprt->transport_lock);
		status = -ETIMEDOUT;
	पूर्ण
	xprt_reset_minorसमयo(req);

	अगर (req->rq_समयout == 0) अणु
		prपूर्णांकk(KERN_WARNING "xprt_adjust_timeout: rq_timeout = 0!\n");
		req->rq_समयout = 5 * HZ;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम xprt_स्वतःबंद(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_xprt *xprt =
		container_of(work, काष्ठा rpc_xprt, task_cleanup);
	अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();

	trace_xprt_disconnect_स्वतः(xprt);
	clear_bit(XPRT_CLOSE_WAIT, &xprt->state);
	xprt->ops->बंद(xprt);
	xprt_release_ग_लिखो(xprt, शून्य);
	wake_up_bit(&xprt->state, XPRT_LOCKED);
	meदो_स्मृति_nofs_restore(pflags);
पूर्ण

/**
 * xprt_disconnect_करोne - mark a transport as disconnected
 * @xprt: transport to flag क्रम disconnect
 *
 */
व्योम xprt_disconnect_करोne(काष्ठा rpc_xprt *xprt)
अणु
	trace_xprt_disconnect_करोne(xprt);
	spin_lock(&xprt->transport_lock);
	xprt_clear_connected(xprt);
	xprt_clear_ग_लिखो_space_locked(xprt);
	xprt_clear_congestion_winकरोw_रुको_locked(xprt);
	xprt_wake_pending_tasks(xprt, -ENOTCONN);
	spin_unlock(&xprt->transport_lock);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_disconnect_करोne);

/**
 * xprt_क्रमce_disconnect - क्रमce a transport to disconnect
 * @xprt: transport to disconnect
 *
 */
व्योम xprt_क्रमce_disconnect(काष्ठा rpc_xprt *xprt)
अणु
	trace_xprt_disconnect_क्रमce(xprt);

	/* Don't race with the test_bit() in xprt_clear_locked() */
	spin_lock(&xprt->transport_lock);
	set_bit(XPRT_CLOSE_WAIT, &xprt->state);
	/* Try to schedule an स्वतःबंद RPC call */
	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state) == 0)
		queue_work(xprtiod_workqueue, &xprt->task_cleanup);
	अन्यथा अगर (xprt->snd_task)
		rpc_wake_up_queued_task_set_status(&xprt->pending,
				xprt->snd_task, -ENOTCONN);
	spin_unlock(&xprt->transport_lock);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_क्रमce_disconnect);

अटल अचिन्हित पूर्णांक
xprt_connect_cookie(काष्ठा rpc_xprt *xprt)
अणु
	वापस READ_ONCE(xprt->connect_cookie);
पूर्ण

अटल bool
xprt_request_retransmit_after_disconnect(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	वापस req->rq_connect_cookie != xprt_connect_cookie(xprt) ||
		!xprt_connected(xprt);
पूर्ण

/**
 * xprt_conditional_disconnect - क्रमce a transport to disconnect
 * @xprt: transport to disconnect
 * @cookie: 'connection cookie'
 *
 * This attempts to अवरोध the connection अगर and only अगर 'cookie' matches
 * the current transport 'connection cookie'. It ensures that we don't
 * try to अवरोध the connection more than once when we need to retransmit
 * a batch of RPC requests.
 *
 */
व्योम xprt_conditional_disconnect(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक cookie)
अणु
	/* Don't race with the test_bit() in xprt_clear_locked() */
	spin_lock(&xprt->transport_lock);
	अगर (cookie != xprt->connect_cookie)
		जाओ out;
	अगर (test_bit(XPRT_CLOSING, &xprt->state))
		जाओ out;
	set_bit(XPRT_CLOSE_WAIT, &xprt->state);
	/* Try to schedule an स्वतःबंद RPC call */
	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state) == 0)
		queue_work(xprtiod_workqueue, &xprt->task_cleanup);
	xprt_wake_pending_tasks(xprt, -EAGAIN);
out:
	spin_unlock(&xprt->transport_lock);
पूर्ण

अटल bool
xprt_has_समयr(स्थिर काष्ठा rpc_xprt *xprt)
अणु
	वापस xprt->idle_समयout != 0;
पूर्ण

अटल व्योम
xprt_schedule_स्वतःdisconnect(काष्ठा rpc_xprt *xprt)
	__must_hold(&xprt->transport_lock)
अणु
	xprt->last_used = jअगरfies;
	अगर (RB_EMPTY_ROOT(&xprt->recv_queue) && xprt_has_समयr(xprt))
		mod_समयr(&xprt->समयr, xprt->last_used + xprt->idle_समयout);
पूर्ण

अटल व्योम
xprt_init_स्वतःdisconnect(काष्ठा समयr_list *t)
अणु
	काष्ठा rpc_xprt *xprt = from_समयr(xprt, t, समयr);

	अगर (!RB_EMPTY_ROOT(&xprt->recv_queue))
		वापस;
	/* Reset xprt->last_used to aव्योम connect/स्वतःdisconnect cycling */
	xprt->last_used = jअगरfies;
	अगर (test_and_set_bit(XPRT_LOCKED, &xprt->state))
		वापस;
	queue_work(xprtiod_workqueue, &xprt->task_cleanup);
पूर्ण

bool xprt_lock_connect(काष्ठा rpc_xprt *xprt,
		काष्ठा rpc_task *task,
		व्योम *cookie)
अणु
	bool ret = false;

	spin_lock(&xprt->transport_lock);
	अगर (!test_bit(XPRT_LOCKED, &xprt->state))
		जाओ out;
	अगर (xprt->snd_task != task)
		जाओ out;
	xprt->snd_task = cookie;
	ret = true;
out:
	spin_unlock(&xprt->transport_lock);
	वापस ret;
पूर्ण

व्योम xprt_unlock_connect(काष्ठा rpc_xprt *xprt, व्योम *cookie)
अणु
	spin_lock(&xprt->transport_lock);
	अगर (xprt->snd_task != cookie)
		जाओ out;
	अगर (!test_bit(XPRT_LOCKED, &xprt->state))
		जाओ out;
	xprt->snd_task =शून्य;
	xprt->ops->release_xprt(xprt, शून्य);
	xprt_schedule_स्वतःdisconnect(xprt);
out:
	spin_unlock(&xprt->transport_lock);
	wake_up_bit(&xprt->state, XPRT_LOCKED);
पूर्ण

/**
 * xprt_connect - schedule a transport connect operation
 * @task: RPC task that is requesting the connect
 *
 */
व्योम xprt_connect(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt	*xprt = task->tk_rqstp->rq_xprt;

	trace_xprt_connect(xprt);

	अगर (!xprt_bound(xprt)) अणु
		task->tk_status = -EAGAIN;
		वापस;
	पूर्ण
	अगर (!xprt_lock_ग_लिखो(xprt, task))
		वापस;

	अगर (test_and_clear_bit(XPRT_CLOSE_WAIT, &xprt->state)) अणु
		trace_xprt_disconnect_cleanup(xprt);
		xprt->ops->बंद(xprt);
	पूर्ण

	अगर (!xprt_connected(xprt)) अणु
		task->tk_rqstp->rq_connect_cookie = xprt->connect_cookie;
		rpc_sleep_on_समयout(&xprt->pending, task, शून्य,
				xprt_request_समयout(task->tk_rqstp));

		अगर (test_bit(XPRT_CLOSING, &xprt->state))
			वापस;
		अगर (xprt_test_and_set_connecting(xprt))
			वापस;
		/* Race अवरोधer */
		अगर (!xprt_connected(xprt)) अणु
			xprt->stat.connect_start = jअगरfies;
			xprt->ops->connect(xprt, task);
		पूर्ण अन्यथा अणु
			xprt_clear_connecting(xprt);
			task->tk_status = 0;
			rpc_wake_up_queued_task(&xprt->pending, task);
		पूर्ण
	पूर्ण
	xprt_release_ग_लिखो(xprt, task);
पूर्ण

/**
 * xprt_reconnect_delay - compute the रुको beक्रमe scheduling a connect
 * @xprt: transport instance
 *
 */
अचिन्हित दीर्घ xprt_reconnect_delay(स्थिर काष्ठा rpc_xprt *xprt)
अणु
	अचिन्हित दीर्घ start, now = jअगरfies;

	start = xprt->stat.connect_start + xprt->reestablish_समयout;
	अगर (समय_after(start, now))
		वापस start - now;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_reconnect_delay);

/**
 * xprt_reconnect_backoff - compute the new re-establish समयout
 * @xprt: transport instance
 * @init_to: initial reestablish समयout
 *
 */
व्योम xprt_reconnect_backoff(काष्ठा rpc_xprt *xprt, अचिन्हित दीर्घ init_to)
अणु
	xprt->reestablish_समयout <<= 1;
	अगर (xprt->reestablish_समयout > xprt->max_reconnect_समयout)
		xprt->reestablish_समयout = xprt->max_reconnect_समयout;
	अगर (xprt->reestablish_समयout < init_to)
		xprt->reestablish_समयout = init_to;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_reconnect_backoff);

क्रमागत xprt_xid_rb_cmp अणु
	XID_RB_EQUAL,
	XID_RB_LEFT,
	XID_RB_RIGHT,
पूर्ण;
अटल क्रमागत xprt_xid_rb_cmp
xprt_xid_cmp(__be32 xid1, __be32 xid2)
अणु
	अगर (xid1 == xid2)
		वापस XID_RB_EQUAL;
	अगर ((__क्रमce u32)xid1 < (__क्रमce u32)xid2)
		वापस XID_RB_LEFT;
	वापस XID_RB_RIGHT;
पूर्ण

अटल काष्ठा rpc_rqst *
xprt_request_rb_find(काष्ठा rpc_xprt *xprt, __be32 xid)
अणु
	काष्ठा rb_node *n = xprt->recv_queue.rb_node;
	काष्ठा rpc_rqst *req;

	जबतक (n != शून्य) अणु
		req = rb_entry(n, काष्ठा rpc_rqst, rq_recv);
		चयन (xprt_xid_cmp(xid, req->rq_xid)) अणु
		हाल XID_RB_LEFT:
			n = n->rb_left;
			अवरोध;
		हाल XID_RB_RIGHT:
			n = n->rb_right;
			अवरोध;
		हाल XID_RB_EQUAL:
			वापस req;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
xprt_request_rb_insert(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *new)
अणु
	काष्ठा rb_node **p = &xprt->recv_queue.rb_node;
	काष्ठा rb_node *n = शून्य;
	काष्ठा rpc_rqst *req;

	जबतक (*p != शून्य) अणु
		n = *p;
		req = rb_entry(n, काष्ठा rpc_rqst, rq_recv);
		चयन(xprt_xid_cmp(new->rq_xid, req->rq_xid)) अणु
		हाल XID_RB_LEFT:
			p = &n->rb_left;
			अवरोध;
		हाल XID_RB_RIGHT:
			p = &n->rb_right;
			अवरोध;
		हाल XID_RB_EQUAL:
			WARN_ON_ONCE(new != req);
			वापस;
		पूर्ण
	पूर्ण
	rb_link_node(&new->rq_recv, n, p);
	rb_insert_color(&new->rq_recv, &xprt->recv_queue);
पूर्ण

अटल व्योम
xprt_request_rb_हटाओ(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	rb_erase(&req->rq_recv, &xprt->recv_queue);
पूर्ण

/**
 * xprt_lookup_rqst - find an RPC request corresponding to an XID
 * @xprt: transport on which the original request was transmitted
 * @xid: RPC XID of incoming reply
 *
 * Caller holds xprt->queue_lock.
 */
काष्ठा rpc_rqst *xprt_lookup_rqst(काष्ठा rpc_xprt *xprt, __be32 xid)
अणु
	काष्ठा rpc_rqst *entry;

	entry = xprt_request_rb_find(xprt, xid);
	अगर (entry != शून्य) अणु
		trace_xprt_lookup_rqst(xprt, xid, 0);
		entry->rq_rtt = kसमय_sub(kसमय_get(), entry->rq_xसमय);
		वापस entry;
	पूर्ण

	dprपूर्णांकk("RPC:       xprt_lookup_rqst did not find xid %08x\n",
			ntohl(xid));
	trace_xprt_lookup_rqst(xprt, xid, -ENOENT);
	xprt->stat.bad_xids++;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_lookup_rqst);

अटल bool
xprt_is_pinned_rqst(काष्ठा rpc_rqst *req)
अणु
	वापस atomic_पढ़ो(&req->rq_pin) != 0;
पूर्ण

/**
 * xprt_pin_rqst - Pin a request on the transport receive list
 * @req: Request to pin
 *
 * Caller must ensure this is atomic with the call to xprt_lookup_rqst()
 * so should be holding xprt->queue_lock.
 */
व्योम xprt_pin_rqst(काष्ठा rpc_rqst *req)
अणु
	atomic_inc(&req->rq_pin);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_pin_rqst);

/**
 * xprt_unpin_rqst - Unpin a request on the transport receive list
 * @req: Request to pin
 *
 * Caller should be holding xprt->queue_lock.
 */
व्योम xprt_unpin_rqst(काष्ठा rpc_rqst *req)
अणु
	अगर (!test_bit(RPC_TASK_MSG_PIN_WAIT, &req->rq_task->tk_runstate)) अणु
		atomic_dec(&req->rq_pin);
		वापस;
	पूर्ण
	अगर (atomic_dec_and_test(&req->rq_pin))
		wake_up_var(&req->rq_pin);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_unpin_rqst);

अटल व्योम xprt_रुको_on_pinned_rqst(काष्ठा rpc_rqst *req)
अणु
	रुको_var_event(&req->rq_pin, !xprt_is_pinned_rqst(req));
पूर्ण

अटल bool
xprt_request_data_received(काष्ठा rpc_task *task)
अणु
	वापस !test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate) &&
		READ_ONCE(task->tk_rqstp->rq_reply_bytes_recvd) != 0;
पूर्ण

अटल bool
xprt_request_need_enqueue_receive(काष्ठा rpc_task *task, काष्ठा rpc_rqst *req)
अणु
	वापस !test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate) &&
		READ_ONCE(task->tk_rqstp->rq_reply_bytes_recvd) == 0;
पूर्ण

/**
 * xprt_request_enqueue_receive - Add an request to the receive queue
 * @task: RPC task
 *
 */
व्योम
xprt_request_enqueue_receive(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (!xprt_request_need_enqueue_receive(task, req))
		वापस;

	xprt_request_prepare(task->tk_rqstp);
	spin_lock(&xprt->queue_lock);

	/* Update the softirq receive buffer */
	स_नकल(&req->rq_निजी_buf, &req->rq_rcv_buf,
			माप(req->rq_निजी_buf));

	/* Add request to the receive list */
	xprt_request_rb_insert(xprt, req);
	set_bit(RPC_TASK_NEED_RECV, &task->tk_runstate);
	spin_unlock(&xprt->queue_lock);

	/* Turn off स्वतःdisconnect */
	del_singleshot_समयr_sync(&xprt->समयr);
पूर्ण

/**
 * xprt_request_dequeue_receive_locked - Remove a request from the receive queue
 * @task: RPC task
 *
 * Caller must hold xprt->queue_lock.
 */
अटल व्योम
xprt_request_dequeue_receive_locked(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	अगर (test_and_clear_bit(RPC_TASK_NEED_RECV, &task->tk_runstate))
		xprt_request_rb_हटाओ(req->rq_xprt, req);
पूर्ण

/**
 * xprt_update_rtt - Update RPC RTT statistics
 * @task: RPC request that recently completed
 *
 * Caller holds xprt->queue_lock.
 */
व्योम xprt_update_rtt(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_rtt *rtt = task->tk_client->cl_rtt;
	अचिन्हित पूर्णांक समयr = task->tk_msg.rpc_proc->p_समयr;
	दीर्घ m = usecs_to_jअगरfies(kसमय_प्रकारo_us(req->rq_rtt));

	अगर (समयr) अणु
		अगर (req->rq_ntrans == 1)
			rpc_update_rtt(rtt, समयr, m);
		rpc_set_समयo(rtt, समयr, req->rq_ntrans - 1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xprt_update_rtt);

/**
 * xprt_complete_rqst - called when reply processing is complete
 * @task: RPC request that recently completed
 * @copied: actual number of bytes received from the transport
 *
 * Caller holds xprt->queue_lock.
 */
व्योम xprt_complete_rqst(काष्ठा rpc_task *task, पूर्णांक copied)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	xprt->stat.recvs++;

	req->rq_निजी_buf.len = copied;
	/* Ensure all ग_लिखोs are करोne beक्रमe we update */
	/* req->rq_reply_bytes_recvd */
	smp_wmb();
	req->rq_reply_bytes_recvd = copied;
	xprt_request_dequeue_receive_locked(task);
	rpc_wake_up_queued_task(&xprt->pending, task);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_complete_rqst);

अटल व्योम xprt_समयr(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (task->tk_status != -ETIMEDOUT)
		वापस;

	trace_xprt_समयr(xprt, req->rq_xid, task->tk_status);
	अगर (!req->rq_reply_bytes_recvd) अणु
		अगर (xprt->ops->समयr)
			xprt->ops->समयr(xprt, task);
	पूर्ण अन्यथा
		task->tk_status = 0;
पूर्ण

/**
 * xprt_रुको_क्रम_reply_request_def - रुको क्रम reply
 * @task: poपूर्णांकer to rpc_task
 *
 * Set a request's retransmit timeout based on the transport's
 * शेष समयout parameters.  Used by transports that करोn't adjust
 * the retransmit समयout based on round-trip समय estimation,
 * and put the task to sleep on the pending queue.
 */
व्योम xprt_रुको_क्रम_reply_request_def(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	rpc_sleep_on_समयout(&req->rq_xprt->pending, task, xprt_समयr,
			xprt_request_समयout(req));
पूर्ण
EXPORT_SYMBOL_GPL(xprt_रुको_क्रम_reply_request_def);

/**
 * xprt_रुको_क्रम_reply_request_rtt - रुको क्रम reply using RTT estimator
 * @task: poपूर्णांकer to rpc_task
 *
 * Set a request's retransmit समयout using the RTT estimator,
 * and put the task to sleep on the pending queue.
 */
व्योम xprt_रुको_क्रम_reply_request_rtt(काष्ठा rpc_task *task)
अणु
	पूर्णांक समयr = task->tk_msg.rpc_proc->p_समयr;
	काष्ठा rpc_clnt *clnt = task->tk_client;
	काष्ठा rpc_rtt *rtt = clnt->cl_rtt;
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	अचिन्हित दीर्घ max_समयout = clnt->cl_समयout->to_maxval;
	अचिन्हित दीर्घ समयout;

	समयout = rpc_calc_rto(rtt, समयr);
	समयout <<= rpc_nसमयo(rtt, समयr) + req->rq_retries;
	अगर (समयout > max_समयout || समयout == 0)
		समयout = max_समयout;
	rpc_sleep_on_समयout(&req->rq_xprt->pending, task, xprt_समयr,
			jअगरfies + समयout);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_रुको_क्रम_reply_request_rtt);

/**
 * xprt_request_रुको_receive - रुको क्रम the reply to an RPC request
 * @task: RPC task about to send a request
 *
 */
व्योम xprt_request_रुको_receive(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (!test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate))
		वापस;
	/*
	 * Sleep on the pending queue अगर we're expecting a reply.
	 * The spinlock ensures atomicity between the test of
	 * req->rq_reply_bytes_recvd, and the call to rpc_sleep_on().
	 */
	spin_lock(&xprt->queue_lock);
	अगर (test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate)) अणु
		xprt->ops->रुको_क्रम_reply_request(task);
		/*
		 * Send an extra queue wakeup call अगर the
		 * connection was dropped in हाल the call to
		 * rpc_sleep_on() raced.
		 */
		अगर (xprt_request_retransmit_after_disconnect(task))
			rpc_wake_up_queued_task_set_status(&xprt->pending,
					task, -ENOTCONN);
	पूर्ण
	spin_unlock(&xprt->queue_lock);
पूर्ण

अटल bool
xprt_request_need_enqueue_transmit(काष्ठा rpc_task *task, काष्ठा rpc_rqst *req)
अणु
	वापस !test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate);
पूर्ण

/**
 * xprt_request_enqueue_transmit - queue a task क्रम transmission
 * @task: poपूर्णांकer to rpc_task
 *
 * Add a task to the transmission queue.
 */
व्योम
xprt_request_enqueue_transmit(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *pos, *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (xprt_request_need_enqueue_transmit(task, req)) अणु
		req->rq_bytes_sent = 0;
		spin_lock(&xprt->queue_lock);
		/*
		 * Requests that carry congestion control credits are added
		 * to the head of the list to aव्योम starvation issues.
		 */
		अगर (req->rq_cong) अणु
			xprt_clear_congestion_winकरोw_रुको(xprt);
			list_क्रम_each_entry(pos, &xprt->xmit_queue, rq_xmit) अणु
				अगर (pos->rq_cong)
					जारी;
				/* Note: req is added _beक्रमe_ pos */
				list_add_tail(&req->rq_xmit, &pos->rq_xmit);
				INIT_LIST_HEAD(&req->rq_xmit2);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (RPC_IS_SWAPPER(task)) अणु
			list_क्रम_each_entry(pos, &xprt->xmit_queue, rq_xmit) अणु
				अगर (pos->rq_cong || pos->rq_bytes_sent)
					जारी;
				अगर (RPC_IS_SWAPPER(pos->rq_task))
					जारी;
				/* Note: req is added _beक्रमe_ pos */
				list_add_tail(&req->rq_xmit, &pos->rq_xmit);
				INIT_LIST_HEAD(&req->rq_xmit2);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!req->rq_seqno) अणु
			list_क्रम_each_entry(pos, &xprt->xmit_queue, rq_xmit) अणु
				अगर (pos->rq_task->tk_owner != task->tk_owner)
					जारी;
				list_add_tail(&req->rq_xmit2, &pos->rq_xmit2);
				INIT_LIST_HEAD(&req->rq_xmit);
				जाओ out;
			पूर्ण
		पूर्ण
		list_add_tail(&req->rq_xmit, &xprt->xmit_queue);
		INIT_LIST_HEAD(&req->rq_xmit2);
out:
		atomic_दीर्घ_inc(&xprt->xmit_queuelen);
		set_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate);
		spin_unlock(&xprt->queue_lock);
	पूर्ण
पूर्ण

/**
 * xprt_request_dequeue_transmit_locked - हटाओ a task from the transmission queue
 * @task: poपूर्णांकer to rpc_task
 *
 * Remove a task from the transmission queue
 * Caller must hold xprt->queue_lock
 */
अटल व्योम
xprt_request_dequeue_transmit_locked(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	अगर (!test_and_clear_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate))
		वापस;
	अगर (!list_empty(&req->rq_xmit)) अणु
		list_del(&req->rq_xmit);
		अगर (!list_empty(&req->rq_xmit2)) अणु
			काष्ठा rpc_rqst *next = list_first_entry(&req->rq_xmit2,
					काष्ठा rpc_rqst, rq_xmit2);
			list_del(&req->rq_xmit2);
			list_add_tail(&next->rq_xmit, &next->rq_xprt->xmit_queue);
		पूर्ण
	पूर्ण अन्यथा
		list_del(&req->rq_xmit2);
	atomic_दीर्घ_dec(&req->rq_xprt->xmit_queuelen);
पूर्ण

/**
 * xprt_request_dequeue_transmit - हटाओ a task from the transmission queue
 * @task: poपूर्णांकer to rpc_task
 *
 * Remove a task from the transmission queue
 */
अटल व्योम
xprt_request_dequeue_transmit(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	spin_lock(&xprt->queue_lock);
	xprt_request_dequeue_transmit_locked(task);
	spin_unlock(&xprt->queue_lock);
पूर्ण

/**
 * xprt_request_dequeue_xprt - हटाओ a task from the transmit+receive queue
 * @task: poपूर्णांकer to rpc_task
 *
 * Remove a task from the transmit and receive queues, and ensure that
 * it is not pinned by the receive work item.
 */
व्योम
xprt_request_dequeue_xprt(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst	*req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate) ||
	    test_bit(RPC_TASK_NEED_RECV, &task->tk_runstate) ||
	    xprt_is_pinned_rqst(req)) अणु
		spin_lock(&xprt->queue_lock);
		xprt_request_dequeue_transmit_locked(task);
		xprt_request_dequeue_receive_locked(task);
		जबतक (xprt_is_pinned_rqst(req)) अणु
			set_bit(RPC_TASK_MSG_PIN_WAIT, &task->tk_runstate);
			spin_unlock(&xprt->queue_lock);
			xprt_रुको_on_pinned_rqst(req);
			spin_lock(&xprt->queue_lock);
			clear_bit(RPC_TASK_MSG_PIN_WAIT, &task->tk_runstate);
		पूर्ण
		spin_unlock(&xprt->queue_lock);
	पूर्ण
पूर्ण

/**
 * xprt_request_prepare - prepare an encoded request क्रम transport
 * @req: poपूर्णांकer to rpc_rqst
 *
 * Calls पूर्णांकo the transport layer to करो whatever is needed to prepare
 * the request क्रम transmission or receive.
 */
व्योम
xprt_request_prepare(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	अगर (xprt->ops->prepare_request)
		xprt->ops->prepare_request(req);
पूर्ण

/**
 * xprt_request_need_retransmit - Test अगर a task needs retransmission
 * @task: poपूर्णांकer to rpc_task
 *
 * Test क्रम whether a connection अवरोधage requires the task to retransmit
 */
bool
xprt_request_need_retransmit(काष्ठा rpc_task *task)
अणु
	वापस xprt_request_retransmit_after_disconnect(task);
पूर्ण

/**
 * xprt_prepare_transmit - reserve the transport beक्रमe sending a request
 * @task: RPC task about to send a request
 *
 */
bool xprt_prepare_transmit(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst	*req = task->tk_rqstp;
	काष्ठा rpc_xprt	*xprt = req->rq_xprt;

	अगर (!xprt_lock_ग_लिखो(xprt, task)) अणु
		/* Race अवरोधer: someone may have transmitted us */
		अगर (!test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate))
			rpc_wake_up_queued_task_set_status(&xprt->sending,
					task, 0);
		वापस false;

	पूर्ण
	वापस true;
पूर्ण

व्योम xprt_end_transmit(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt	*xprt = task->tk_rqstp->rq_xprt;

	xprt_inject_disconnect(xprt);
	xprt_release_ग_लिखो(xprt, task);
पूर्ण

/**
 * xprt_request_transmit - send an RPC request on a transport
 * @req: poपूर्णांकer to request to transmit
 * @snd_task: RPC task that owns the transport lock
 *
 * This perक्रमms the transmission of a single request.
 * Note that अगर the request is not the same as snd_task, then it
 * करोes need to be pinned.
 * Returns '0' on success.
 */
अटल पूर्णांक
xprt_request_transmit(काष्ठा rpc_rqst *req, काष्ठा rpc_task *snd_task)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा rpc_task *task = req->rq_task;
	अचिन्हित पूर्णांक connect_cookie;
	पूर्णांक is_retrans = RPC_WAS_SENT(task);
	पूर्णांक status;

	अगर (!req->rq_bytes_sent) अणु
		अगर (xprt_request_data_received(task)) अणु
			status = 0;
			जाओ out_dequeue;
		पूर्ण
		/* Verअगरy that our message lies in the RPCSEC_GSS winकरोw */
		अगर (rpcauth_xmit_need_reencode(task)) अणु
			status = -EBADMSG;
			जाओ out_dequeue;
		पूर्ण
		अगर (RPC_SIGNALLED(task)) अणु
			status = -ERESTARTSYS;
			जाओ out_dequeue;
		पूर्ण
	पूर्ण

	/*
	 * Update req->rq_ntrans beक्रमe transmitting to aव्योम races with
	 * xprt_update_rtt(), which needs to know that it is recording a
	 * reply to the first transmission.
	 */
	req->rq_ntrans++;

	trace_rpc_xdr_sendto(task, &req->rq_snd_buf);
	connect_cookie = xprt->connect_cookie;
	status = xprt->ops->send_request(req);
	अगर (status != 0) अणु
		req->rq_ntrans--;
		trace_xprt_transmit(req, status);
		वापस status;
	पूर्ण

	अगर (is_retrans) अणु
		task->tk_client->cl_stats->rpcretrans++;
		trace_xprt_retransmit(req);
	पूर्ण

	xprt_inject_disconnect(xprt);

	task->tk_flags |= RPC_TASK_SENT;
	spin_lock(&xprt->transport_lock);

	xprt->stat.sends++;
	xprt->stat.req_u += xprt->stat.sends - xprt->stat.recvs;
	xprt->stat.bklog_u += xprt->backlog.qlen;
	xprt->stat.sending_u += xprt->sending.qlen;
	xprt->stat.pending_u += xprt->pending.qlen;
	spin_unlock(&xprt->transport_lock);

	req->rq_connect_cookie = connect_cookie;
out_dequeue:
	trace_xprt_transmit(req, status);
	xprt_request_dequeue_transmit(task);
	rpc_wake_up_queued_task_set_status(&xprt->sending, task, status);
	वापस status;
पूर्ण

/**
 * xprt_transmit - send an RPC request on a transport
 * @task: controlling RPC task
 *
 * Attempts to drain the transmit queue. On निकास, either the transport
 * संकेतled an error that needs to be handled beक्रमe transmission can
 * resume, or @task finished transmitting, and detected that it alपढ़ोy
 * received a reply.
 */
व्योम
xprt_transmit(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *next, *req = task->tk_rqstp;
	काष्ठा rpc_xprt	*xprt = req->rq_xprt;
	पूर्णांक counter, status;

	spin_lock(&xprt->queue_lock);
	counter = 0;
	जबतक (!list_empty(&xprt->xmit_queue)) अणु
		अगर (++counter == 20)
			अवरोध;
		next = list_first_entry(&xprt->xmit_queue,
				काष्ठा rpc_rqst, rq_xmit);
		xprt_pin_rqst(next);
		spin_unlock(&xprt->queue_lock);
		status = xprt_request_transmit(next, task);
		अगर (status == -EBADMSG && next != req)
			status = 0;
		spin_lock(&xprt->queue_lock);
		xprt_unpin_rqst(next);
		अगर (status == 0) अणु
			अगर (!xprt_request_data_received(task) ||
			    test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate))
				जारी;
		पूर्ण अन्यथा अगर (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate))
			task->tk_status = status;
		अवरोध;
	पूर्ण
	spin_unlock(&xprt->queue_lock);
पूर्ण

अटल व्योम xprt_complete_request_init(काष्ठा rpc_task *task)
अणु
	अगर (task->tk_rqstp)
		xprt_request_init(task);
पूर्ण

व्योम xprt_add_backlog(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	set_bit(XPRT_CONGESTED, &xprt->state);
	rpc_sleep_on(&xprt->backlog, task, xprt_complete_request_init);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_add_backlog);

अटल bool __xprt_set_rq(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा rpc_rqst *req = data;

	अगर (task->tk_rqstp == शून्य) अणु
		स_रखो(req, 0, माप(*req));	/* mark unused */
		task->tk_rqstp = req;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool xprt_wake_up_backlog(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	अगर (rpc_wake_up_first(&xprt->backlog, __xprt_set_rq, req) == शून्य) अणु
		clear_bit(XPRT_CONGESTED, &xprt->state);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_wake_up_backlog);

अटल bool xprt_throttle_congested(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	bool ret = false;

	अगर (!test_bit(XPRT_CONGESTED, &xprt->state))
		जाओ out;
	spin_lock(&xprt->reserve_lock);
	अगर (test_bit(XPRT_CONGESTED, &xprt->state)) अणु
		xprt_add_backlog(xprt, task);
		ret = true;
	पूर्ण
	spin_unlock(&xprt->reserve_lock);
out:
	वापस ret;
पूर्ण

अटल काष्ठा rpc_rqst *xprt_dynamic_alloc_slot(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_rqst *req = ERR_PTR(-EAGAIN);

	अगर (xprt->num_reqs >= xprt->max_reqs)
		जाओ out;
	++xprt->num_reqs;
	spin_unlock(&xprt->reserve_lock);
	req = kzalloc(माप(काष्ठा rpc_rqst), GFP_NOFS);
	spin_lock(&xprt->reserve_lock);
	अगर (req != शून्य)
		जाओ out;
	--xprt->num_reqs;
	req = ERR_PTR(-ENOMEM);
out:
	वापस req;
पूर्ण

अटल bool xprt_dynamic_मुक्त_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	अगर (xprt->num_reqs > xprt->min_reqs) अणु
		--xprt->num_reqs;
		kमुक्त(req);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम xprt_alloc_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req;

	spin_lock(&xprt->reserve_lock);
	अगर (!list_empty(&xprt->मुक्त)) अणु
		req = list_entry(xprt->मुक्त.next, काष्ठा rpc_rqst, rq_list);
		list_del(&req->rq_list);
		जाओ out_init_req;
	पूर्ण
	req = xprt_dynamic_alloc_slot(xprt);
	अगर (!IS_ERR(req))
		जाओ out_init_req;
	चयन (PTR_ERR(req)) अणु
	हाल -ENOMEM:
		dprपूर्णांकk("RPC:       dynamic allocation of request slot "
				"failed! Retrying\n");
		task->tk_status = -ENOMEM;
		अवरोध;
	हाल -EAGAIN:
		xprt_add_backlog(xprt, task);
		dprपूर्णांकk("RPC:       waiting for request slot\n");
		fallthrough;
	शेष:
		task->tk_status = -EAGAIN;
	पूर्ण
	spin_unlock(&xprt->reserve_lock);
	वापस;
out_init_req:
	xprt->stat.max_slots = max_t(अचिन्हित पूर्णांक, xprt->stat.max_slots,
				     xprt->num_reqs);
	spin_unlock(&xprt->reserve_lock);

	task->tk_status = 0;
	task->tk_rqstp = req;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_alloc_slot);

व्योम xprt_मुक्त_slot(काष्ठा rpc_xprt *xprt, काष्ठा rpc_rqst *req)
अणु
	spin_lock(&xprt->reserve_lock);
	अगर (!xprt_wake_up_backlog(xprt, req) &&
	    !xprt_dynamic_मुक्त_slot(xprt, req)) अणु
		स_रखो(req, 0, माप(*req));	/* mark unused */
		list_add(&req->rq_list, &xprt->मुक्त);
	पूर्ण
	spin_unlock(&xprt->reserve_lock);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_मुक्त_slot);

अटल व्योम xprt_मुक्त_all_slots(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_rqst *req;
	जबतक (!list_empty(&xprt->मुक्त)) अणु
		req = list_first_entry(&xprt->मुक्त, काष्ठा rpc_rqst, rq_list);
		list_del(&req->rq_list);
		kमुक्त(req);
	पूर्ण
पूर्ण

काष्ठा rpc_xprt *xprt_alloc(काष्ठा net *net, माप_प्रकार size,
		अचिन्हित पूर्णांक num_pपुनः_स्मृति,
		अचिन्हित पूर्णांक max_alloc)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpc_rqst *req;
	पूर्णांक i;

	xprt = kzalloc(size, GFP_KERNEL);
	अगर (xprt == शून्य)
		जाओ out;

	xprt_init(xprt, net);

	क्रम (i = 0; i < num_pपुनः_स्मृति; i++) अणु
		req = kzalloc(माप(काष्ठा rpc_rqst), GFP_KERNEL);
		अगर (!req)
			जाओ out_मुक्त;
		list_add(&req->rq_list, &xprt->मुक्त);
	पूर्ण
	अगर (max_alloc > num_pपुनः_स्मृति)
		xprt->max_reqs = max_alloc;
	अन्यथा
		xprt->max_reqs = num_pपुनः_स्मृति;
	xprt->min_reqs = num_pपुनः_स्मृति;
	xprt->num_reqs = num_pपुनः_स्मृति;

	वापस xprt;

out_मुक्त:
	xprt_मुक्त(xprt);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_alloc);

व्योम xprt_मुक्त(काष्ठा rpc_xprt *xprt)
अणु
	put_net(xprt->xprt_net);
	xprt_मुक्त_all_slots(xprt);
	kमुक्त_rcu(xprt, rcu);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_मुक्त);

अटल व्योम
xprt_init_connect_cookie(काष्ठा rpc_rqst *req, काष्ठा rpc_xprt *xprt)
अणु
	req->rq_connect_cookie = xprt_connect_cookie(xprt) - 1;
पूर्ण

अटल __be32
xprt_alloc_xid(काष्ठा rpc_xprt *xprt)
अणु
	__be32 xid;

	spin_lock(&xprt->reserve_lock);
	xid = (__क्रमce __be32)xprt->xid++;
	spin_unlock(&xprt->reserve_lock);
	वापस xid;
पूर्ण

अटल व्योम
xprt_init_xid(काष्ठा rpc_xprt *xprt)
अणु
	xprt->xid = pअक्रमom_u32();
पूर्ण

अटल व्योम
xprt_request_init(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_xprt;
	काष्ठा rpc_rqst	*req = task->tk_rqstp;

	req->rq_task	= task;
	req->rq_xprt    = xprt;
	req->rq_buffer  = शून्य;
	req->rq_xid	= xprt_alloc_xid(xprt);
	xprt_init_connect_cookie(req, xprt);
	req->rq_snd_buf.len = 0;
	req->rq_snd_buf.buflen = 0;
	req->rq_rcv_buf.len = 0;
	req->rq_rcv_buf.buflen = 0;
	req->rq_snd_buf.bvec = शून्य;
	req->rq_rcv_buf.bvec = शून्य;
	req->rq_release_snd_buf = शून्य;
	xprt_init_majorसमयo(task, req);

	trace_xprt_reserve(req);
पूर्ण

अटल व्योम
xprt_करो_reserve(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	xprt->ops->alloc_slot(xprt, task);
	अगर (task->tk_rqstp != शून्य)
		xprt_request_init(task);
पूर्ण

/**
 * xprt_reserve - allocate an RPC request slot
 * @task: RPC task requesting a slot allocation
 *
 * If the transport is marked as being congested, or अगर no more
 * slots are available, place the task on the transport's
 * backlog queue.
 */
व्योम xprt_reserve(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_xprt;

	task->tk_status = 0;
	अगर (task->tk_rqstp != शून्य)
		वापस;

	task->tk_status = -EAGAIN;
	अगर (!xprt_throttle_congested(xprt, task))
		xprt_करो_reserve(xprt, task);
पूर्ण

/**
 * xprt_retry_reserve - allocate an RPC request slot
 * @task: RPC task requesting a slot allocation
 *
 * If no more slots are available, place the task on the transport's
 * backlog queue.
 * Note that the only dअगरference with xprt_reserve is that we now
 * ignore the value of the XPRT_CONGESTED flag.
 */
व्योम xprt_retry_reserve(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_xprt;

	task->tk_status = 0;
	अगर (task->tk_rqstp != शून्य)
		वापस;

	task->tk_status = -EAGAIN;
	xprt_करो_reserve(xprt, task);
पूर्ण

/**
 * xprt_release - release an RPC request slot
 * @task: task which is finished with the slot
 *
 */
व्योम xprt_release(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt	*xprt;
	काष्ठा rpc_rqst	*req = task->tk_rqstp;

	अगर (req == शून्य) अणु
		अगर (task->tk_client) अणु
			xprt = task->tk_xprt;
			xprt_release_ग_लिखो(xprt, task);
		पूर्ण
		वापस;
	पूर्ण

	xprt = req->rq_xprt;
	xprt_request_dequeue_xprt(task);
	spin_lock(&xprt->transport_lock);
	xprt->ops->release_xprt(xprt, task);
	अगर (xprt->ops->release_request)
		xprt->ops->release_request(task);
	xprt_schedule_स्वतःdisconnect(xprt);
	spin_unlock(&xprt->transport_lock);
	अगर (req->rq_buffer)
		xprt->ops->buf_मुक्त(task);
	xdr_मुक्त_bvec(&req->rq_rcv_buf);
	xdr_मुक्त_bvec(&req->rq_snd_buf);
	अगर (req->rq_cred != शून्य)
		put_rpccred(req->rq_cred);
	अगर (req->rq_release_snd_buf)
		req->rq_release_snd_buf(req);

	task->tk_rqstp = शून्य;
	अगर (likely(!bc_pपुनः_स्मृति(req)))
		xprt->ops->मुक्त_slot(xprt, req);
	अन्यथा
		xprt_मुक्त_bc_request(req);
पूर्ण

#अगर_घोषित CONFIG_SUNRPC_BACKCHANNEL
व्योम
xprt_init_bc_request(काष्ठा rpc_rqst *req, काष्ठा rpc_task *task)
अणु
	काष्ठा xdr_buf *xbufp = &req->rq_snd_buf;

	task->tk_rqstp = req;
	req->rq_task = task;
	xprt_init_connect_cookie(req, req->rq_xprt);
	/*
	 * Set up the xdr_buf length.
	 * This also indicates that the buffer is XDR encoded alपढ़ोy.
	 */
	xbufp->len = xbufp->head[0].iov_len + xbufp->page_len +
		xbufp->tail[0].iov_len;
पूर्ण
#पूर्ण_अगर

अटल व्योम xprt_init(काष्ठा rpc_xprt *xprt, काष्ठा net *net)
अणु
	kref_init(&xprt->kref);

	spin_lock_init(&xprt->transport_lock);
	spin_lock_init(&xprt->reserve_lock);
	spin_lock_init(&xprt->queue_lock);

	INIT_LIST_HEAD(&xprt->मुक्त);
	xprt->recv_queue = RB_ROOT;
	INIT_LIST_HEAD(&xprt->xmit_queue);
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
	spin_lock_init(&xprt->bc_pa_lock);
	INIT_LIST_HEAD(&xprt->bc_pa_list);
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */
	INIT_LIST_HEAD(&xprt->xprt_चयन);

	xprt->last_used = jअगरfies;
	xprt->cwnd = RPC_INITCWND;
	xprt->bind_index = 0;

	rpc_init_रुको_queue(&xprt->binding, "xprt_binding");
	rpc_init_रुको_queue(&xprt->pending, "xprt_pending");
	rpc_init_रुको_queue(&xprt->sending, "xprt_sending");
	rpc_init_priority_रुको_queue(&xprt->backlog, "xprt_backlog");

	xprt_init_xid(xprt);

	xprt->xprt_net = get_net(net);
पूर्ण

/**
 * xprt_create_transport - create an RPC transport
 * @args: rpc transport creation arguments
 *
 */
काष्ठा rpc_xprt *xprt_create_transport(काष्ठा xprt_create *args)
अणु
	काष्ठा rpc_xprt	*xprt;
	स्थिर काष्ठा xprt_class *t;

	t = xprt_class_find_by_ident(args->ident);
	अगर (!t) अणु
		dprपूर्णांकk("RPC: transport (%d) not supported\n", args->ident);
		वापस ERR_PTR(-EIO);
	पूर्ण

	xprt = t->setup(args);
	xprt_class_release(t);

	अगर (IS_ERR(xprt))
		जाओ out;
	अगर (args->flags & XPRT_CREATE_NO_IDLE_TIMEOUT)
		xprt->idle_समयout = 0;
	INIT_WORK(&xprt->task_cleanup, xprt_स्वतःबंद);
	अगर (xprt_has_समयr(xprt))
		समयr_setup(&xprt->समयr, xprt_init_स्वतःdisconnect, 0);
	अन्यथा
		समयr_setup(&xprt->समयr, शून्य, 0);

	अगर (म_माप(args->servername) > RPC_MAXNETNAMELEN) अणु
		xprt_destroy(xprt);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	xprt->servername = kstrdup(args->servername, GFP_KERNEL);
	अगर (xprt->servername == शून्य) अणु
		xprt_destroy(xprt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rpc_xprt_debugfs_रेजिस्टर(xprt);

	trace_xprt_create(xprt);
out:
	वापस xprt;
पूर्ण

अटल व्योम xprt_destroy_cb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_xprt *xprt =
		container_of(work, काष्ठा rpc_xprt, task_cleanup);

	trace_xprt_destroy(xprt);

	rpc_xprt_debugfs_unरेजिस्टर(xprt);
	rpc_destroy_रुको_queue(&xprt->binding);
	rpc_destroy_रुको_queue(&xprt->pending);
	rpc_destroy_रुको_queue(&xprt->sending);
	rpc_destroy_रुको_queue(&xprt->backlog);
	kमुक्त(xprt->servername);
	/*
	 * Destroy any existing back channel
	 */
	xprt_destroy_backchannel(xprt, अच_पूर्णांक_उच्च);

	/*
	 * Tear करोwn transport state and मुक्त the rpc_xprt
	 */
	xprt->ops->destroy(xprt);
पूर्ण

/**
 * xprt_destroy - destroy an RPC transport, समाप्तing off all requests.
 * @xprt: transport to destroy
 *
 */
अटल व्योम xprt_destroy(काष्ठा rpc_xprt *xprt)
अणु
	/*
	 * Exclude transport connect/disconnect handlers and स्वतःबंद
	 */
	रुको_on_bit_lock(&xprt->state, XPRT_LOCKED, TASK_UNINTERRUPTIBLE);

	del_समयr_sync(&xprt->समयr);

	/*
	 * Destroy sockets etc from the प्रणाली workqueue so they can
	 * safely flush receive work running on rpciod.
	 */
	INIT_WORK(&xprt->task_cleanup, xprt_destroy_cb);
	schedule_work(&xprt->task_cleanup);
पूर्ण

अटल व्योम xprt_destroy_kref(काष्ठा kref *kref)
अणु
	xprt_destroy(container_of(kref, काष्ठा rpc_xprt, kref));
पूर्ण

/**
 * xprt_get - वापस a reference to an RPC transport.
 * @xprt: poपूर्णांकer to the transport
 *
 */
काष्ठा rpc_xprt *xprt_get(काष्ठा rpc_xprt *xprt)
अणु
	अगर (xprt != शून्य && kref_get_unless_zero(&xprt->kref))
		वापस xprt;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(xprt_get);

/**
 * xprt_put - release a reference to an RPC transport.
 * @xprt: poपूर्णांकer to the transport
 *
 */
व्योम xprt_put(काष्ठा rpc_xprt *xprt)
अणु
	अगर (xprt != शून्य)
		kref_put(&xprt->kref, xprt_destroy_kref);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_put);
