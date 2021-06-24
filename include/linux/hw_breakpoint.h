<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HW_BREAKPOINT_H
#घोषणा _LINUX_HW_BREAKPOINT_H

#समावेश <linux/perf_event.h>
#समावेश <uapi/linux/hw_अवरोधpoपूर्णांक.h>

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT

बाह्य पूर्णांक __init init_hw_अवरोधpoपूर्णांक(व्योम);

अटल अंतरभूत व्योम hw_अवरोधpoपूर्णांक_init(काष्ठा perf_event_attr *attr)
अणु
	स_रखो(attr, 0, माप(*attr));

	attr->type = PERF_TYPE_BREAKPOINT;
	attr->size = माप(*attr);
	/*
	 * As it's क्रम in-kernel or ptrace use, we want it to be pinned
	 * and to call its callback every hits.
	 */
	attr->pinned = 1;
	attr->sample_period = 1;
पूर्ण

अटल अंतरभूत व्योम ptrace_अवरोधpoपूर्णांक_init(काष्ठा perf_event_attr *attr)
अणु
	hw_अवरोधpoपूर्णांक_init(attr);
	attr->exclude_kernel = 1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hw_अवरोधpoपूर्णांक_addr(काष्ठा perf_event *bp)
अणु
	वापस bp->attr.bp_addr;
पूर्ण

अटल अंतरभूत पूर्णांक hw_अवरोधpoपूर्णांक_type(काष्ठा perf_event *bp)
अणु
	वापस bp->attr.bp_type;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hw_अवरोधpoपूर्णांक_len(काष्ठा perf_event *bp)
अणु
	वापस bp->attr.bp_len;
पूर्ण

बाह्य काष्ठा perf_event *
रेजिस्टर_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context,
			    काष्ठा task_काष्ठा *tsk);

/* FIXME: only change from the attr, and करोn't unरेजिस्टर */
बाह्य पूर्णांक
modअगरy_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp, काष्ठा perf_event_attr *attr);
बाह्य पूर्णांक
modअगरy_user_hw_अवरोधpoपूर्णांक_check(काष्ठा perf_event *bp, काष्ठा perf_event_attr *attr,
				bool check);

/*
 * Kernel अवरोधpoपूर्णांकs are not associated with any particular thपढ़ो.
 */
बाह्य काष्ठा perf_event *
रेजिस्टर_wide_hw_अवरोधpoपूर्णांक_cpu(काष्ठा perf_event_attr *attr,
				perf_overflow_handler_t	triggered,
				व्योम *context,
				पूर्णांक cpu);

बाह्य काष्ठा perf_event * __percpu *
रेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context);

बाह्य पूर्णांक रेजिस्टर_perf_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
बाह्य व्योम unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
बाह्य व्योम unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event * __percpu *cpu_events);

बाह्य पूर्णांक dbg_reserve_bp_slot(काष्ठा perf_event *bp);
बाह्य पूर्णांक dbg_release_bp_slot(काष्ठा perf_event *bp);
बाह्य पूर्णांक reserve_bp_slot(काष्ठा perf_event *bp);
बाह्य व्योम release_bp_slot(काष्ठा perf_event *bp);
पूर्णांक hw_अवरोधpoपूर्णांक_weight(काष्ठा perf_event *bp);
पूर्णांक arch_reserve_bp_slot(काष्ठा perf_event *bp);
व्योम arch_release_bp_slot(काष्ठा perf_event *bp);
व्योम arch_unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);

बाह्य व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत काष्ठा arch_hw_अवरोधpoपूर्णांक *counter_arch_bp(काष्ठा perf_event *bp)
अणु
	वापस &bp->hw.info;
पूर्ण

#अन्यथा /* !CONFIG_HAVE_HW_BREAKPOINT */

अटल अंतरभूत पूर्णांक __init init_hw_अवरोधpoपूर्णांक(व्योम) अणु वापस 0; पूर्ण

अटल अंतरभूत काष्ठा perf_event *
रेजिस्टर_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context,
			    काष्ठा task_काष्ठा *tsk)	अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक
modअगरy_user_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp,
			  काष्ठा perf_event_attr *attr)	अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक
modअगरy_user_hw_अवरोधpoपूर्णांक_check(काष्ठा perf_event *bp, काष्ठा perf_event_attr *attr,
				bool check)	अणु वापस -ENOSYS; पूर्ण

अटल अंतरभूत काष्ठा perf_event *
रेजिस्टर_wide_hw_अवरोधpoपूर्णांक_cpu(काष्ठा perf_event_attr *attr,
				perf_overflow_handler_t	 triggered,
				व्योम *context,
				पूर्णांक cpu)		अणु वापस शून्य; पूर्ण
अटल अंतरभूत काष्ठा perf_event * __percpu *
रेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event_attr *attr,
			    perf_overflow_handler_t triggered,
			    व्योम *context)		अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक
रेजिस्टर_perf_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)	अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp)	अणु पूर्ण
अटल अंतरभूत व्योम
unरेजिस्टर_wide_hw_अवरोधpoपूर्णांक(काष्ठा perf_event * __percpu *cpu_events)	अणु पूर्ण
अटल अंतरभूत पूर्णांक
reserve_bp_slot(काष्ठा perf_event *bp)			अणुवापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम release_bp_slot(काष्ठा perf_event *bp) 		अणु पूर्ण

अटल अंतरभूत व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)	अणु पूर्ण

अटल अंतरभूत काष्ठा arch_hw_अवरोधpoपूर्णांक *counter_arch_bp(काष्ठा perf_event *bp)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
#पूर्ण_अगर /* _LINUX_HW_BREAKPOINT_H */
