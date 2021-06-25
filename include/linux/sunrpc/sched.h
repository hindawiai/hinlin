<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/sched.h
 *
 * Scheduling primitives क्रम kernel Sun RPC.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _LINUX_SUNRPC_SCHED_H_
#घोषणा _LINUX_SUNRPC_SCHED_H_

#समावेश <linux/समयr.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/sunrpc/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको_bit.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sunrpc/xdr.h>

/*
 * This is the actual RPC procedure call info.
 */
काष्ठा rpc_procinfo;
काष्ठा rpc_message अणु
	स्थिर काष्ठा rpc_procinfo *rpc_proc;	/* Procedure inक्रमmation */
	व्योम *			rpc_argp;	/* Arguments */
	व्योम *			rpc_resp;	/* Result */
	स्थिर काष्ठा cred *	rpc_cred;	/* Credentials */
पूर्ण;

काष्ठा rpc_call_ops;
काष्ठा rpc_रुको_queue;
काष्ठा rpc_रुको अणु
	काष्ठा list_head	list;		/* रुको queue links */
	काष्ठा list_head	links;		/* Links to related tasks */
	काष्ठा list_head	समयr_list;	/* Timer list */
पूर्ण;

/*
 * This is the RPC task काष्ठा
 */
काष्ठा rpc_task अणु
	atomic_t		tk_count;	/* Reference count */
	पूर्णांक			tk_status;	/* result of last operation */
	काष्ठा list_head	tk_task;	/* global list of tasks */

	/*
	 * callback	to be executed after waking up
	 * action	next procedure क्रम async tasks
	 */
	व्योम			(*tk_callback)(काष्ठा rpc_task *);
	व्योम			(*tk_action)(काष्ठा rpc_task *);

	अचिन्हित दीर्घ		tk_समयout;	/* समयout क्रम rpc_sleep() */
	अचिन्हित दीर्घ		tk_runstate;	/* Task run status */

	काष्ठा rpc_रुको_queue 	*tk_रुकोqueue;	/* RPC रुको queue we're on */
	जोड़ अणु
		काष्ठा work_काष्ठा	tk_work;	/* Async task work queue */
		काष्ठा rpc_रुको		tk_रुको;	/* RPC रुको */
	पूर्ण u;

	पूर्णांक			tk_rpc_status;	/* Result of last RPC operation */

	/*
	 * RPC call state
	 */
	काष्ठा rpc_message	tk_msg;		/* RPC call info */
	व्योम *			tk_calldata;	/* Caller निजी data */
	स्थिर काष्ठा rpc_call_ops *tk_ops;	/* Caller callbacks */

	काष्ठा rpc_clnt *	tk_client;	/* RPC client */
	काष्ठा rpc_xprt *	tk_xprt;	/* Transport */
	काष्ठा rpc_cred *	tk_op_cred;	/* cred being operated on */

	काष्ठा rpc_rqst *	tk_rqstp;	/* RPC request */

	काष्ठा workqueue_काष्ठा	*tk_workqueue;	/* Normally rpciod, but could
						 * be any workqueue
						 */
	kसमय_प्रकार			tk_start;	/* RPC task init बारtamp */

	pid_t			tk_owner;	/* Process id क्रम batching tasks */
	अचिन्हित लघु		tk_flags;	/* misc flags */
	अचिन्हित लघु		tk_समयouts;	/* maj समयouts */

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG) || IS_ENABLED(CONFIG_TRACEPOINTS)
	अचिन्हित लघु		tk_pid;		/* debugging aid */
#पूर्ण_अगर
	अचिन्हित अक्षर		tk_priority : 2,/* Task priority */
				tk_garb_retry : 2,
				tk_cred_retry : 2,
				tk_rebind_retry : 2;
पूर्ण;

प्रकार व्योम			(*rpc_action)(काष्ठा rpc_task *);

काष्ठा rpc_call_ops अणु
	व्योम (*rpc_call_prepare)(काष्ठा rpc_task *, व्योम *);
	व्योम (*rpc_call_करोne)(काष्ठा rpc_task *, व्योम *);
	व्योम (*rpc_count_stats)(काष्ठा rpc_task *, व्योम *);
	व्योम (*rpc_release)(व्योम *);
पूर्ण;

काष्ठा rpc_task_setup अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_clnt *rpc_client;
	काष्ठा rpc_xprt *rpc_xprt;
	काष्ठा rpc_cred *rpc_op_cred;	/* credential being operated on */
	स्थिर काष्ठा rpc_message *rpc_message;
	स्थिर काष्ठा rpc_call_ops *callback_ops;
	व्योम *callback_data;
	काष्ठा workqueue_काष्ठा *workqueue;
	अचिन्हित लघु flags;
	चिन्हित अक्षर priority;
पूर्ण;

/*
 * RPC task flags
 */
#घोषणा RPC_TASK_ASYNC		0x0001		/* is an async task */
#घोषणा RPC_TASK_SWAPPER	0x0002		/* is swapping in/out */
#घोषणा RPC_TASK_शून्यCREDS	0x0010		/* Use AUTH_शून्य credential */
#घोषणा RPC_CALL_MAJORSEEN	0x0020		/* major समयout seen */
#घोषणा RPC_TASK_ROOTCREDS	0x0040		/* क्रमce root creds */
#घोषणा RPC_TASK_DYNAMIC	0x0080		/* task was kदो_स्मृति'ed */
#घोषणा	RPC_TASK_NO_ROUND_ROBIN	0x0100		/* send requests on "main" xprt */
#घोषणा RPC_TASK_SOFT		0x0200		/* Use soft समयouts */
#घोषणा RPC_TASK_SOFTCONN	0x0400		/* Fail अगर can't connect */
#घोषणा RPC_TASK_SENT		0x0800		/* message was sent */
#घोषणा RPC_TASK_TIMEOUT	0x1000		/* fail with ETIMEDOUT on समयout */
#घोषणा RPC_TASK_NOCONNECT	0x2000		/* वापस ENOTCONN अगर not connected */
#घोषणा RPC_TASK_NO_RETRANS_TIMEOUT	0x4000		/* रुको क्रमever क्रम a reply */
#घोषणा RPC_TASK_CRED_NOREF	0x8000		/* No refcount on the credential */

#घोषणा RPC_IS_ASYNC(t)		((t)->tk_flags & RPC_TASK_ASYNC)
#घोषणा RPC_IS_SWAPPER(t)	((t)->tk_flags & RPC_TASK_SWAPPER)
#घोषणा RPC_IS_SOFT(t)		((t)->tk_flags & (RPC_TASK_SOFT|RPC_TASK_TIMEOUT))
#घोषणा RPC_IS_SOFTCONN(t)	((t)->tk_flags & RPC_TASK_SOFTCONN)
#घोषणा RPC_WAS_SENT(t)		((t)->tk_flags & RPC_TASK_SENT)

#घोषणा RPC_TASK_RUNNING	0
#घोषणा RPC_TASK_QUEUED		1
#घोषणा RPC_TASK_ACTIVE		2
#घोषणा RPC_TASK_NEED_XMIT	3
#घोषणा RPC_TASK_NEED_RECV	4
#घोषणा RPC_TASK_MSG_PIN_WAIT	5
#घोषणा RPC_TASK_SIGNALLED	6

#घोषणा RPC_IS_RUNNING(t)	test_bit(RPC_TASK_RUNNING, &(t)->tk_runstate)
#घोषणा rpc_set_running(t)	set_bit(RPC_TASK_RUNNING, &(t)->tk_runstate)
#घोषणा rpc_test_and_set_running(t) \
				test_and_set_bit(RPC_TASK_RUNNING, &(t)->tk_runstate)
#घोषणा rpc_clear_running(t)	\
	करो अणु \
		smp_mb__beक्रमe_atomic(); \
		clear_bit(RPC_TASK_RUNNING, &(t)->tk_runstate); \
		smp_mb__after_atomic(); \
	पूर्ण जबतक (0)

#घोषणा RPC_IS_QUEUED(t)	test_bit(RPC_TASK_QUEUED, &(t)->tk_runstate)
#घोषणा rpc_set_queued(t)	set_bit(RPC_TASK_QUEUED, &(t)->tk_runstate)
#घोषणा rpc_clear_queued(t)	\
	करो अणु \
		smp_mb__beक्रमe_atomic(); \
		clear_bit(RPC_TASK_QUEUED, &(t)->tk_runstate); \
		smp_mb__after_atomic(); \
	पूर्ण जबतक (0)

#घोषणा RPC_IS_ACTIVATED(t)	test_bit(RPC_TASK_ACTIVE, &(t)->tk_runstate)

#घोषणा RPC_SIGNALLED(t)	test_bit(RPC_TASK_SIGNALLED, &(t)->tk_runstate)

/*
 * Task priorities.
 * Note: अगर you change these, you must also change
 * the task initialization definitions below.
 */
#घोषणा RPC_PRIORITY_LOW	(-1)
#घोषणा RPC_PRIORITY_NORMAL	(0)
#घोषणा RPC_PRIORITY_HIGH	(1)
#घोषणा RPC_PRIORITY_PRIVILEGED	(2)
#घोषणा RPC_NR_PRIORITY		(1 + RPC_PRIORITY_PRIVILEGED - RPC_PRIORITY_LOW)

काष्ठा rpc_समयr अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ expires;
	काष्ठा delayed_work dwork;
पूर्ण;

/*
 * RPC synchronization objects
 */
काष्ठा rpc_रुको_queue अणु
	spinlock_t		lock;
	काष्ठा list_head	tasks[RPC_NR_PRIORITY];	/* task queue क्रम each priority level */
	अचिन्हित अक्षर		maxpriority;		/* maximum priority (0 अगर queue is not a priority queue) */
	अचिन्हित अक्षर		priority;		/* current priority */
	अचिन्हित अक्षर		nr;			/* # tasks reमुख्यing क्रम cookie */
	अचिन्हित लघु		qlen;			/* total # tasks रुकोing in queue */
	काष्ठा rpc_समयr	समयr_list;
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG) || IS_ENABLED(CONFIG_TRACEPOINTS)
	स्थिर अक्षर *		name;
#पूर्ण_अगर
पूर्ण;

/*
 * This is the # requests to send consecutively
 * from a single cookie.  The aim is to improve
 * perक्रमmance of NFS operations such as पढ़ो/ग_लिखो.
 */
#घोषणा RPC_IS_PRIORITY(q)		((q)->maxpriority > 0)

/*
 * Function prototypes
 */
काष्ठा rpc_task *rpc_new_task(स्थिर काष्ठा rpc_task_setup *);
काष्ठा rpc_task *rpc_run_task(स्थिर काष्ठा rpc_task_setup *);
काष्ठा rpc_task *rpc_run_bc_task(काष्ठा rpc_rqst *req);
व्योम		rpc_put_task(काष्ठा rpc_task *);
व्योम		rpc_put_task_async(काष्ठा rpc_task *);
व्योम		rpc_संकेत_task(काष्ठा rpc_task *);
व्योम		rpc_निकास_task(काष्ठा rpc_task *);
व्योम		rpc_निकास(काष्ठा rpc_task *, पूर्णांक);
व्योम		rpc_release_calldata(स्थिर काष्ठा rpc_call_ops *, व्योम *);
व्योम		rpc_समाप्तall_tasks(काष्ठा rpc_clnt *);
व्योम		rpc_execute(काष्ठा rpc_task *);
व्योम		rpc_init_priority_रुको_queue(काष्ठा rpc_रुको_queue *, स्थिर अक्षर *);
व्योम		rpc_init_रुको_queue(काष्ठा rpc_रुको_queue *, स्थिर अक्षर *);
व्योम		rpc_destroy_रुको_queue(काष्ठा rpc_रुको_queue *);
अचिन्हित दीर्घ	rpc_task_समयout(स्थिर काष्ठा rpc_task *task);
व्योम		rpc_sleep_on_समयout(काष्ठा rpc_रुको_queue *queue,
					काष्ठा rpc_task *task,
					rpc_action action,
					अचिन्हित दीर्घ समयout);
व्योम		rpc_sleep_on(काष्ठा rpc_रुको_queue *, काष्ठा rpc_task *,
					rpc_action action);
व्योम		rpc_sleep_on_priority_समयout(काष्ठा rpc_रुको_queue *queue,
					काष्ठा rpc_task *task,
					अचिन्हित दीर्घ समयout,
					पूर्णांक priority);
व्योम		rpc_sleep_on_priority(काष्ठा rpc_रुको_queue *,
					काष्ठा rpc_task *,
					पूर्णांक priority);
व्योम		rpc_wake_up_queued_task(काष्ठा rpc_रुको_queue *,
					काष्ठा rpc_task *);
व्योम		rpc_wake_up_queued_task_set_status(काष्ठा rpc_रुको_queue *,
						   काष्ठा rpc_task *,
						   पूर्णांक);
व्योम		rpc_wake_up(काष्ठा rpc_रुको_queue *);
काष्ठा rpc_task *rpc_wake_up_next(काष्ठा rpc_रुको_queue *);
काष्ठा rpc_task *rpc_wake_up_first_on_wq(काष्ठा workqueue_काष्ठा *wq,
					काष्ठा rpc_रुको_queue *,
					bool (*)(काष्ठा rpc_task *, व्योम *),
					व्योम *);
काष्ठा rpc_task *rpc_wake_up_first(काष्ठा rpc_रुको_queue *,
					bool (*)(काष्ठा rpc_task *, व्योम *),
					व्योम *);
व्योम		rpc_wake_up_status(काष्ठा rpc_रुको_queue *, पूर्णांक);
व्योम		rpc_delay(काष्ठा rpc_task *, अचिन्हित दीर्घ);
पूर्णांक		rpc_दो_स्मृति(काष्ठा rpc_task *);
व्योम		rpc_मुक्त(काष्ठा rpc_task *);
पूर्णांक		rpciod_up(व्योम);
व्योम		rpciod_करोwn(व्योम);
पूर्णांक		__rpc_रुको_क्रम_completion_task(काष्ठा rpc_task *task, रुको_bit_action_f *);
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
काष्ठा net;
व्योम		rpc_show_tasks(काष्ठा net *);
#पूर्ण_अगर
पूर्णांक		rpc_init_mempool(व्योम);
व्योम		rpc_destroy_mempool(व्योम);
बाह्य काष्ठा workqueue_काष्ठा *rpciod_workqueue;
बाह्य काष्ठा workqueue_काष्ठा *xprtiod_workqueue;
व्योम		rpc_prepare_task(काष्ठा rpc_task *task);

अटल अंतरभूत पूर्णांक rpc_रुको_क्रम_completion_task(काष्ठा rpc_task *task)
अणु
	वापस __rpc_रुको_क्रम_completion_task(task, शून्य);
पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG) || IS_ENABLED(CONFIG_TRACEPOINTS)
अटल अंतरभूत स्थिर अक्षर * rpc_qname(स्थिर काष्ठा rpc_रुको_queue *q)
अणु
	वापस ((q && q->name) ? q->name : "unknown");
पूर्ण

अटल अंतरभूत व्योम rpc_assign_रुकोqueue_name(काष्ठा rpc_रुको_queue *q,
		स्थिर अक्षर *name)
अणु
	q->name = name;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rpc_assign_रुकोqueue_name(काष्ठा rpc_रुको_queue *q,
		स्थिर अक्षर *name)
अणु
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SUNRPC_SWAP)
पूर्णांक rpc_clnt_swap_activate(काष्ठा rpc_clnt *clnt);
व्योम rpc_clnt_swap_deactivate(काष्ठा rpc_clnt *clnt);
#अन्यथा
अटल अंतरभूत पूर्णांक
rpc_clnt_swap_activate(काष्ठा rpc_clnt *clnt)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
rpc_clnt_swap_deactivate(काष्ठा rpc_clnt *clnt)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_SWAP */

#पूर्ण_अगर /* _LINUX_SUNRPC_SCHED_H_ */
