<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SECCOMP_H
#घोषणा _LINUX_SECCOMP_H

#समावेश <uapi/linux/seccomp.h>

#घोषणा SECCOMP_FILTER_FLAG_MASK	(SECCOMP_FILTER_FLAG_TSYNC | \
					 SECCOMP_FILTER_FLAG_LOG | \
					 SECCOMP_FILTER_FLAG_SPEC_ALLOW | \
					 SECCOMP_FILTER_FLAG_NEW_LISTENER | \
					 SECCOMP_FILTER_FLAG_TSYNC_ESRCH)

/* माप() the first published काष्ठा seccomp_notअगर_addfd */
#घोषणा SECCOMP_NOTIFY_ADDFD_SIZE_VER0 24
#घोषणा SECCOMP_NOTIFY_ADDFD_SIZE_LATEST SECCOMP_NOTIFY_ADDFD_SIZE_VER0

#अगर_घोषित CONFIG_SECCOMP

#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/seccomp.h>

काष्ठा seccomp_filter;
/**
 * काष्ठा seccomp - the state of a seccomp'ed process
 *
 * @mode:  indicates one of the valid values above क्रम controlled
 *         प्रणाली calls available to a process.
 * @filter: must always poपूर्णांक to a valid seccomp-filter or शून्य as it is
 *          accessed without locking during प्रणाली call entry.
 *
 *          @filter must only be accessed from the context of current as there
 *          is no पढ़ो locking.
 */
काष्ठा seccomp अणु
	पूर्णांक mode;
	atomic_t filter_count;
	काष्ठा seccomp_filter *filter;
पूर्ण;

#अगर_घोषित CONFIG_HAVE_ARCH_SECCOMP_FILTER
बाह्य पूर्णांक __secure_computing(स्थिर काष्ठा seccomp_data *sd);
अटल अंतरभूत पूर्णांक secure_computing(व्योम)
अणु
	अगर (unlikely(test_syscall_work(SECCOMP)))
		वापस  __secure_computing(शून्य);
	वापस 0;
पूर्ण
#अन्यथा
बाह्य व्योम secure_computing_strict(पूर्णांक this_syscall);
#पूर्ण_अगर

बाह्य दीर्घ prctl_get_seccomp(व्योम);
बाह्य दीर्घ prctl_set_seccomp(अचिन्हित दीर्घ, व्योम __user *);

अटल अंतरभूत पूर्णांक seccomp_mode(काष्ठा seccomp *s)
अणु
	वापस s->mode;
पूर्ण

#अन्यथा /* CONFIG_SECCOMP */

#समावेश <linux/त्रुटिसं.स>

काष्ठा seccomp अणु पूर्ण;
काष्ठा seccomp_filter अणु पूर्ण;
काष्ठा seccomp_data;

#अगर_घोषित CONFIG_HAVE_ARCH_SECCOMP_FILTER
अटल अंतरभूत पूर्णांक secure_computing(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक __secure_computing(स्थिर काष्ठा seccomp_data *sd) अणु वापस 0; पूर्ण
#अन्यथा
अटल अंतरभूत व्योम secure_computing_strict(पूर्णांक this_syscall) अणु वापस; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत दीर्घ prctl_get_seccomp(व्योम)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत दीर्घ prctl_set_seccomp(अचिन्हित दीर्घ arg2, अक्षर __user *arg3)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक seccomp_mode(काष्ठा seccomp *s)
अणु
	वापस SECCOMP_MODE_DISABLED;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP */

#अगर_घोषित CONFIG_SECCOMP_FILTER
बाह्य व्योम seccomp_filter_release(काष्ठा task_काष्ठा *tsk);
बाह्य व्योम get_seccomp_filter(काष्ठा task_काष्ठा *tsk);
#अन्यथा  /* CONFIG_SECCOMP_FILTER */
अटल अंतरभूत व्योम seccomp_filter_release(काष्ठा task_काष्ठा *tsk)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम get_seccomp_filter(काष्ठा task_काष्ठा *tsk)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP_FILTER */

#अगर defined(CONFIG_SECCOMP_FILTER) && defined(CONFIG_CHECKPOINT_RESTORE)
बाह्य दीर्घ seccomp_get_filter(काष्ठा task_काष्ठा *task,
			       अचिन्हित दीर्घ filter_off, व्योम __user *data);
बाह्य दीर्घ seccomp_get_metadata(काष्ठा task_काष्ठा *task,
				 अचिन्हित दीर्घ filter_off, व्योम __user *data);
#अन्यथा
अटल अंतरभूत दीर्घ seccomp_get_filter(काष्ठा task_काष्ठा *task,
				      अचिन्हित दीर्घ n, व्योम __user *data)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत दीर्घ seccomp_get_metadata(काष्ठा task_काष्ठा *task,
					अचिन्हित दीर्घ filter_off,
					व्योम __user *data)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_SECCOMP_FILTER && CONFIG_CHECKPOINT_RESTORE */

#अगर_घोषित CONFIG_SECCOMP_CACHE_DEBUG
काष्ठा seq_file;

पूर्णांक proc_pid_seccomp_cache(काष्ठा seq_file *m, काष्ठा pid_namespace *ns,
			   काष्ठा pid *pid, काष्ठा task_काष्ठा *task);
#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_SECCOMP_H */
