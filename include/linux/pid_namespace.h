<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PID_NS_H
#घोषणा _LINUX_PID_NS_H

#समावेश <linux/sched.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/idr.h>

/* MAX_PID_NS_LEVEL is needed क्रम limiting size of 'struct pid' */
#घोषणा MAX_PID_NS_LEVEL 32

काष्ठा fs_pin;

काष्ठा pid_namespace अणु
	काष्ठा idr idr;
	काष्ठा rcu_head rcu;
	अचिन्हित पूर्णांक pid_allocated;
	काष्ठा task_काष्ठा *child_reaper;
	काष्ठा kmem_cache *pid_cachep;
	अचिन्हित पूर्णांक level;
	काष्ठा pid_namespace *parent;
#अगर_घोषित CONFIG_BSD_PROCESS_ACCT
	काष्ठा fs_pin *bacct;
#पूर्ण_अगर
	काष्ठा user_namespace *user_ns;
	काष्ठा ucounts *ucounts;
	पूर्णांक reboot;	/* group निकास code अगर this pidns was rebooted */
	काष्ठा ns_common ns;
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा pid_namespace init_pid_ns;

#घोषणा PIDNS_ADDING (1U << 31)

#अगर_घोषित CONFIG_PID_NS
अटल अंतरभूत काष्ठा pid_namespace *get_pid_ns(काष्ठा pid_namespace *ns)
अणु
	अगर (ns != &init_pid_ns)
		refcount_inc(&ns->ns.count);
	वापस ns;
पूर्ण

बाह्य काष्ठा pid_namespace *copy_pid_ns(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा pid_namespace *ns);
बाह्य व्योम zap_pid_ns_processes(काष्ठा pid_namespace *pid_ns);
बाह्य पूर्णांक reboot_pid_ns(काष्ठा pid_namespace *pid_ns, पूर्णांक cmd);
बाह्य व्योम put_pid_ns(काष्ठा pid_namespace *ns);

#अन्यथा /* !CONFIG_PID_NS */
#समावेश <linux/err.h>

अटल अंतरभूत काष्ठा pid_namespace *get_pid_ns(काष्ठा pid_namespace *ns)
अणु
	वापस ns;
पूर्ण

अटल अंतरभूत काष्ठा pid_namespace *copy_pid_ns(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा pid_namespace *ns)
अणु
	अगर (flags & CLONE_NEWPID)
		ns = ERR_PTR(-EINVAL);
	वापस ns;
पूर्ण

अटल अंतरभूत व्योम put_pid_ns(काष्ठा pid_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत व्योम zap_pid_ns_processes(काष्ठा pid_namespace *ns)
अणु
	BUG();
पूर्ण

अटल अंतरभूत पूर्णांक reboot_pid_ns(काष्ठा pid_namespace *pid_ns, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PID_NS */

बाह्य काष्ठा pid_namespace *task_active_pid_ns(काष्ठा task_काष्ठा *tsk);
व्योम pidhash_init(व्योम);
व्योम pid_idr_init(व्योम);

#पूर्ण_अगर /* _LINUX_PID_NS_H */
