<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __IPC_NAMESPACE_H__
#घोषणा __IPC_NAMESPACE_H__

#समावेश <linux/err.h>
#समावेश <linux/idr.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rhashtable-types.h>

काष्ठा user_namespace;

काष्ठा ipc_ids अणु
	पूर्णांक in_use;
	अचिन्हित लघु seq;
	काष्ठा rw_semaphore rwsem;
	काष्ठा idr ipcs_idr;
	पूर्णांक max_idx;
	पूर्णांक last_idx;	/* For wrap around detection */
#अगर_घोषित CONFIG_CHECKPOINT_RESTORE
	पूर्णांक next_id;
#पूर्ण_अगर
	काष्ठा rhashtable key_ht;
पूर्ण;

काष्ठा ipc_namespace अणु
	काष्ठा ipc_ids	ids[3];

	पूर्णांक		sem_ctls[4];
	पूर्णांक		used_sems;

	अचिन्हित पूर्णांक	msg_ctlmax;
	अचिन्हित पूर्णांक	msg_ctlmnb;
	अचिन्हित पूर्णांक	msg_ctlmni;
	atomic_t	msg_bytes;
	atomic_t	msg_hdrs;

	माप_प्रकार		shm_ctlmax;
	माप_प्रकार		shm_ctlall;
	अचिन्हित दीर्घ	shm_tot;
	पूर्णांक		shm_ctlmni;
	/*
	 * Defines whether IPC_RMID is क्रमced क्रम _all_ shm segments regardless
	 * of shmctl()
	 */
	पूर्णांक		shm_rmid_क्रमced;

	काष्ठा notअगरier_block ipcns_nb;

	/* The kern_mount of the mqueuefs sb.  We take a ref on it */
	काष्ठा vfsmount	*mq_mnt;

	/* # queues in this ns, रक्षित by mq_lock */
	अचिन्हित पूर्णांक    mq_queues_count;

	/* next fields are set through sysctl */
	अचिन्हित पूर्णांक    mq_queues_max;   /* initialized to DFLT_QUEUESMAX */
	अचिन्हित पूर्णांक    mq_msg_max;      /* initialized to DFLT_MSGMAX */
	अचिन्हित पूर्णांक    mq_msgsize_max;  /* initialized to DFLT_MSGSIZEMAX */
	अचिन्हित पूर्णांक    mq_msg_शेष;
	अचिन्हित पूर्णांक    mq_msgsize_शेष;

	/* user_ns which owns the ipc ns */
	काष्ठा user_namespace *user_ns;
	काष्ठा ucounts *ucounts;

	काष्ठा llist_node mnt_llist;

	काष्ठा ns_common ns;
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा ipc_namespace init_ipc_ns;
बाह्य spinlock_t mq_lock;

#अगर_घोषित CONFIG_SYSVIPC
बाह्य व्योम shm_destroy_orphaned(काष्ठा ipc_namespace *ns);
#अन्यथा /* CONFIG_SYSVIPC */
अटल अंतरभूत व्योम shm_destroy_orphaned(काष्ठा ipc_namespace *ns) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SYSVIPC */

#अगर_घोषित CONFIG_POSIX_MQUEUE
बाह्य पूर्णांक mq_init_ns(काष्ठा ipc_namespace *ns);
/*
 * POSIX Message Queue शेष values:
 *
 * MIN_*: Lowest value an admin can set the maximum unprivileged limit to
 * DFLT_*MAX: Default values क्रम the maximum unprivileged limits
 * DFLT_अणुMSG,MSGSIZEपूर्ण: Default values used when the user करोesn't supply
 *   an attribute to the खोलो call and the queue must be created
 * HARD_*: Highest value the maximums can be set to.  These are enक्रमced
 *   on CAP_SYS_RESOURCE apps as well making them inviolate (so make them
 *   suitably high)
 *
 * POSIX Requirements:
 *   Per app minimum खोलोable message queues - 8.  This करोes not map well
 *     to the fact that we limit the number of queues on a per namespace
 *     basis instead of a per app basis.  So, make the शेष high enough
 *     that no given app should have a hard समय खोलोing 8 queues.
 *   Minimum maximum क्रम HARD_MSGMAX - 32767.  I bumped this to 65536.
 *   Minimum maximum क्रम HARD_MSGSIZEMAX - POSIX is silent on this.  However,
 *     we have run पूर्णांकo a situation where running applications in the wild
 *     require this to be at least 5MB, and preferably 10MB, so I set the
 *     value to 16MB in hopes that this user is the worst of the bunch and
 *     the new maximum will handle anyone अन्यथा.  I may have to revisit this
 *     in the future.
 */
#घोषणा DFLT_QUEUESMAX		      256
#घोषणा MIN_MSGMAX			1
#घोषणा DFLT_MSG		       10U
#घोषणा DFLT_MSGMAX		       10
#घोषणा HARD_MSGMAX		    65536
#घोषणा MIN_MSGSIZEMAX		      128
#घोषणा DFLT_MSGSIZE		     8192U
#घोषणा DFLT_MSGSIZEMAX		     8192
#घोषणा HARD_MSGSIZEMAX	    (16*1024*1024)
#अन्यथा
अटल अंतरभूत पूर्णांक mq_init_ns(काष्ठा ipc_namespace *ns) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_IPC_NS)
बाह्य काष्ठा ipc_namespace *copy_ipcs(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा ipc_namespace *ns);

अटल अंतरभूत काष्ठा ipc_namespace *get_ipc_ns(काष्ठा ipc_namespace *ns)
अणु
	अगर (ns)
		refcount_inc(&ns->ns.count);
	वापस ns;
पूर्ण

बाह्य व्योम put_ipc_ns(काष्ठा ipc_namespace *ns);
#अन्यथा
अटल अंतरभूत काष्ठा ipc_namespace *copy_ipcs(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा ipc_namespace *ns)
अणु
	अगर (flags & CLONE_NEWIPC)
		वापस ERR_PTR(-EINVAL);

	वापस ns;
पूर्ण

अटल अंतरभूत काष्ठा ipc_namespace *get_ipc_ns(काष्ठा ipc_namespace *ns)
अणु
	वापस ns;
पूर्ण

अटल अंतरभूत व्योम put_ipc_ns(काष्ठा ipc_namespace *ns)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_POSIX_MQUEUE_SYSCTL

काष्ठा ctl_table_header;
बाह्य काष्ठा ctl_table_header *mq_रेजिस्टर_sysctl_table(व्योम);

#अन्यथा /* CONFIG_POSIX_MQUEUE_SYSCTL */

अटल अंतरभूत काष्ठा ctl_table_header *mq_रेजिस्टर_sysctl_table(व्योम)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_POSIX_MQUEUE_SYSCTL */
#पूर्ण_अगर
