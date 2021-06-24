<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_TIMENS_H
#घोषणा _LINUX_TIMENS_H


#समावेश <linux/sched.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/err.h>

काष्ठा user_namespace;
बाह्य काष्ठा user_namespace init_user_ns;

काष्ठा समयns_offsets अणु
	काष्ठा बारpec64 monotonic;
	काष्ठा बारpec64 bootसमय;
पूर्ण;

काष्ठा समय_namespace अणु
	काष्ठा user_namespace	*user_ns;
	काष्ठा ucounts		*ucounts;
	काष्ठा ns_common	ns;
	काष्ठा समयns_offsets	offsets;
	काष्ठा page		*vvar_page;
	/* If set prevents changing offsets after any task joined namespace. */
	bool			frozen_offsets;
पूर्ण __अक्रमomize_layout;

बाह्य काष्ठा समय_namespace init_समय_ns;

#अगर_घोषित CONFIG_TIME_NS
बाह्य पूर्णांक vdso_join_समयns(काष्ठा task_काष्ठा *task,
			    काष्ठा समय_namespace *ns);
बाह्य व्योम समयns_commit(काष्ठा task_काष्ठा *tsk, काष्ठा समय_namespace *ns);

अटल अंतरभूत काष्ठा समय_namespace *get_समय_ns(काष्ठा समय_namespace *ns)
अणु
	refcount_inc(&ns->ns.count);
	वापस ns;
पूर्ण

काष्ठा समय_namespace *copy_समय_ns(अचिन्हित दीर्घ flags,
				    काष्ठा user_namespace *user_ns,
				    काष्ठा समय_namespace *old_ns);
व्योम मुक्त_समय_ns(काष्ठा समय_namespace *ns);
व्योम समयns_on_विभाजन(काष्ठा nsproxy *nsproxy, काष्ठा task_काष्ठा *tsk);
काष्ठा vdso_data *arch_get_vdso_data(व्योम *vvar_page);

अटल अंतरभूत व्योम put_समय_ns(काष्ठा समय_namespace *ns)
अणु
	अगर (refcount_dec_and_test(&ns->ns.count))
		मुक्त_समय_ns(ns);
पूर्ण

व्योम proc_समयns_show_offsets(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m);

काष्ठा proc_समयns_offset अणु
	पूर्णांक			घड़ीid;
	काष्ठा बारpec64	val;
पूर्ण;

पूर्णांक proc_समयns_set_offset(काष्ठा file *file, काष्ठा task_काष्ठा *p,
			   काष्ठा proc_समयns_offset *offsets, पूर्णांक n);

अटल अंतरभूत व्योम समयns_add_monotonic(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयns_offsets *ns_offsets = &current->nsproxy->समय_ns->offsets;

	*ts = बारpec64_add(*ts, ns_offsets->monotonic);
पूर्ण

अटल अंतरभूत व्योम समयns_add_bootसमय(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयns_offsets *ns_offsets = &current->nsproxy->समय_ns->offsets;

	*ts = बारpec64_add(*ts, ns_offsets->bootसमय);
पूर्ण

अटल अंतरभूत u64 समयns_add_bootसमय_ns(u64 nsec)
अणु
	काष्ठा समयns_offsets *ns_offsets = &current->nsproxy->समय_ns->offsets;

	वापस nsec + बारpec64_to_ns(&ns_offsets->bootसमय);
पूर्ण

अटल अंतरभूत व्योम समयns_sub_bootसमय(काष्ठा बारpec64 *ts)
अणु
	काष्ठा समयns_offsets *ns_offsets = &current->nsproxy->समय_ns->offsets;

	*ts = बारpec64_sub(*ts, ns_offsets->bootसमय);
पूर्ण

kसमय_प्रकार करो_समयns_kसमय_प्रकारo_host(घड़ीid_t घड़ीid, kसमय_प्रकार tim,
				काष्ठा समयns_offsets *offsets);

अटल अंतरभूत kसमय_प्रकार समयns_kसमय_प्रकारo_host(घड़ीid_t घड़ीid, kसमय_प्रकार tim)
अणु
	काष्ठा समय_namespace *ns = current->nsproxy->समय_ns;

	अगर (likely(ns == &init_समय_ns))
		वापस tim;

	वापस करो_समयns_kसमय_प्रकारo_host(घड़ीid, tim, &ns->offsets);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक vdso_join_समयns(काष्ठा task_काष्ठा *task,
				   काष्ठा समय_namespace *ns)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम समयns_commit(काष्ठा task_काष्ठा *tsk,
				 काष्ठा समय_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत काष्ठा समय_namespace *get_समय_ns(काष्ठा समय_namespace *ns)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम put_समय_ns(काष्ठा समय_namespace *ns)
अणु
पूर्ण

अटल अंतरभूत
काष्ठा समय_namespace *copy_समय_ns(अचिन्हित दीर्घ flags,
				    काष्ठा user_namespace *user_ns,
				    काष्ठा समय_namespace *old_ns)
अणु
	अगर (flags & CLONE_NEWTIME)
		वापस ERR_PTR(-EINVAL);

	वापस old_ns;
पूर्ण

अटल अंतरभूत व्योम समयns_on_विभाजन(काष्ठा nsproxy *nsproxy,
				 काष्ठा task_काष्ठा *tsk)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम समयns_add_monotonic(काष्ठा बारpec64 *ts) अणु पूर्ण
अटल अंतरभूत व्योम समयns_add_bootसमय(काष्ठा बारpec64 *ts) अणु पूर्ण

अटल अंतरभूत u64 समयns_add_bootसमय_ns(u64 nsec)
अणु
	वापस nsec;
पूर्ण

अटल अंतरभूत व्योम समयns_sub_bootसमय(काष्ठा बारpec64 *ts) अणु पूर्ण

अटल अंतरभूत kसमय_प्रकार समयns_kसमय_प्रकारo_host(घड़ीid_t घड़ीid, kसमय_प्रकार tim)
अणु
	वापस tim;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_TIMENS_H */
