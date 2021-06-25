<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UTSNAME_H
#घोषणा _LINUX_UTSNAME_H


#समावेश <linux/sched.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/err.h>
#समावेश <uapi/linux/utsname.h>

क्रमागत uts_proc अणु
	UTS_PROC_OSTYPE,
	UTS_PROC_OSRELEASE,
	UTS_PROC_VERSION,
	UTS_PROC_HOSTNAME,
	UTS_PROC_DOMAINNAME,
पूर्ण;

काष्ठा user_namespace;
बाह्य काष्ठा user_namespace init_user_ns;

काष्ठा uts_namespace अणु
	काष्ठा new_utsname name;
	काष्ठा user_namespace *user_ns;
	काष्ठा ucounts *ucounts;
	काष्ठा ns_common ns;
पूर्ण __अक्रमomize_layout;
बाह्य काष्ठा uts_namespace init_uts_ns;

#अगर_घोषित CONFIG_UTS_NS
अटल अंतरभूत व्योम get_uts_ns(काष्ठा uts_namespace *ns)
अणु
	refcount_inc(&ns->ns.count);
पूर्ण

बाह्य काष्ठा uts_namespace *copy_utsname(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा uts_namespace *old_ns);
बाह्य व्योम मुक्त_uts_ns(काष्ठा uts_namespace *ns);

अटल अंतरभूत व्योम put_uts_ns(काष्ठा uts_namespace *ns)
अणु
	अगर (refcount_dec_and_test(&ns->ns.count))
		मुक्त_uts_ns(ns);
पूर्ण

व्योम uts_ns_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम get_uts_ns(काष्ठा uts_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत व्योम put_uts_ns(काष्ठा uts_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत काष्ठा uts_namespace *copy_utsname(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा uts_namespace *old_ns)
अणु
	अगर (flags & CLONE_NEWUTS)
		वापस ERR_PTR(-EINVAL);

	वापस old_ns;
पूर्ण

अटल अंतरभूत व्योम uts_ns_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_SYSCTL
बाह्य व्योम uts_proc_notअगरy(क्रमागत uts_proc proc);
#अन्यथा
अटल अंतरभूत व्योम uts_proc_notअगरy(क्रमागत uts_proc proc)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा new_utsname *utsname(व्योम)
अणु
	वापस &current->nsproxy->uts_ns->name;
पूर्ण

अटल अंतरभूत काष्ठा new_utsname *init_utsname(व्योम)
अणु
	वापस &init_uts_ns.name;
पूर्ण

बाह्य काष्ठा rw_semaphore uts_sem;

#पूर्ण_अगर /* _LINUX_UTSNAME_H */
