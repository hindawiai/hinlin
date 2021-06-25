<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KCOV_H
#घोषणा _LINUX_KCOV_H

#समावेश <linux/sched.h>
#समावेश <uapi/linux/kcov.h>

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_KCOV

क्रमागत kcov_mode अणु
	/* Coverage collection is not enabled yet. */
	KCOV_MODE_DISABLED = 0,
	/* KCOV was initialized, but tracing mode hasn't been chosen yet. */
	KCOV_MODE_INIT = 1,
	/*
	 * Tracing coverage collection mode.
	 * Covered PCs are collected in a per-task buffer.
	 */
	KCOV_MODE_TRACE_PC = 2,
	/* Collecting comparison opeअक्रमs mode. */
	KCOV_MODE_TRACE_CMP = 3,
पूर्ण;

#घोषणा KCOV_IN_CTXSW	(1 << 30)

व्योम kcov_task_init(काष्ठा task_काष्ठा *t);
व्योम kcov_task_निकास(काष्ठा task_काष्ठा *t);

#घोषणा kcov_prepare_चयन(t)			\
करो अणु						\
	(t)->kcov_mode |= KCOV_IN_CTXSW;	\
पूर्ण जबतक (0)

#घोषणा kcov_finish_चयन(t)			\
करो अणु						\
	(t)->kcov_mode &= ~KCOV_IN_CTXSW;	\
पूर्ण जबतक (0)

/* See Documentation/dev-tools/kcov.rst क्रम usage details. */
व्योम kcov_remote_start(u64 handle);
व्योम kcov_remote_stop(व्योम);
u64 kcov_common_handle(व्योम);

अटल अंतरभूत व्योम kcov_remote_start_common(u64 id)
अणु
	kcov_remote_start(kcov_remote_handle(KCOV_SUBSYSTEM_COMMON, id));
पूर्ण

अटल अंतरभूत व्योम kcov_remote_start_usb(u64 id)
अणु
	kcov_remote_start(kcov_remote_handle(KCOV_SUBSYSTEM_USB, id));
पूर्ण

/*
 * The softirq flavor of kcov_remote_*() functions is पूर्णांकroduced as a temporary
 * work around क्रम kcov's lack of nested remote coverage sections support in
 * task context. Adding suport क्रम nested sections is tracked in:
 * https://bugzilla.kernel.org/show_bug.cgi?id=210337
 */

अटल अंतरभूत व्योम kcov_remote_start_usb_softirq(u64 id)
अणु
	अगर (in_serving_softirq())
		kcov_remote_start_usb(id);
पूर्ण

अटल अंतरभूत व्योम kcov_remote_stop_softirq(व्योम)
अणु
	अगर (in_serving_softirq())
		kcov_remote_stop();
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम kcov_task_init(काष्ठा task_काष्ठा *t) अणुपूर्ण
अटल अंतरभूत व्योम kcov_task_निकास(काष्ठा task_काष्ठा *t) अणुपूर्ण
अटल अंतरभूत व्योम kcov_prepare_चयन(काष्ठा task_काष्ठा *t) अणुपूर्ण
अटल अंतरभूत व्योम kcov_finish_चयन(काष्ठा task_काष्ठा *t) अणुपूर्ण
अटल अंतरभूत व्योम kcov_remote_start(u64 handle) अणुपूर्ण
अटल अंतरभूत व्योम kcov_remote_stop(व्योम) अणुपूर्ण
अटल अंतरभूत u64 kcov_common_handle(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम kcov_remote_start_common(u64 id) अणुपूर्ण
अटल अंतरभूत व्योम kcov_remote_start_usb(u64 id) अणुपूर्ण
अटल अंतरभूत व्योम kcov_remote_start_usb_softirq(u64 id) अणुपूर्ण
अटल अंतरभूत व्योम kcov_remote_stop_softirq(व्योम) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_KCOV */
#पूर्ण_अगर /* _LINUX_KCOV_H */
