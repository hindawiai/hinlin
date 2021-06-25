<शैली गुरु>
/*
 *    Copyright (c) 2007 Benjamin Herrenschmidt, IBM Corporation
 *    Extracted from संकेत_32.c and संकेत_64.c
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file README.legal in the मुख्य directory of
 * this archive क्रम more details.
 */

#अगर_अघोषित _POWERPC_ARCH_SIGNAL_H
#घोषणा _POWERPC_ARCH_SIGNAL_H

व्योम __user *get_sigframe(काष्ठा kसंकेत *ksig, काष्ठा task_काष्ठा *tsk,
			  माप_प्रकार frame_size, पूर्णांक is_32);

बाह्य पूर्णांक handle_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
			   काष्ठा task_काष्ठा *tsk);

बाह्य पूर्णांक handle_rt_संकेत32(काष्ठा kसंकेत *ksig, sigset_t *oldset,
			      काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत पूर्णांक __get_user_sigset(sigset_t *dst, स्थिर sigset_t __user *src)
अणु
	BUILD_BUG_ON(माप(sigset_t) != माप(u64));

	वापस __get_user(dst->sig[0], (u64 __user *)&src->sig[0]);
पूर्ण
#घोषणा unsafe_get_user_sigset(dst, src, label) \
	unsafe_get_user((dst)->sig[0], (u64 __user *)&(src)->sig[0], label)

#अगर_घोषित CONFIG_VSX
बाह्य अचिन्हित दीर्घ copy_vsx_to_user(व्योम __user *to,
				      काष्ठा task_काष्ठा *task);
बाह्य अचिन्हित दीर्घ copy_ckvsx_to_user(व्योम __user *to,
					       काष्ठा task_काष्ठा *task);
बाह्य अचिन्हित दीर्घ copy_vsx_from_user(काष्ठा task_काष्ठा *task,
					व्योम __user *from);
बाह्य अचिन्हित दीर्घ copy_ckvsx_from_user(काष्ठा task_काष्ठा *task,
						 व्योम __user *from);
अचिन्हित दीर्घ copy_fpr_to_user(व्योम __user *to, काष्ठा task_काष्ठा *task);
अचिन्हित दीर्घ copy_ckfpr_to_user(व्योम __user *to, काष्ठा task_काष्ठा *task);
अचिन्हित दीर्घ copy_fpr_from_user(काष्ठा task_काष्ठा *task, व्योम __user *from);
अचिन्हित दीर्घ copy_ckfpr_from_user(काष्ठा task_काष्ठा *task, व्योम __user *from);

#घोषणा unsafe_copy_fpr_to_user(to, task, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)to;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NFPREG - 1 ; i++)				\
		unsafe_put_user(__t->thपढ़ो.TS_FPR(i), &buf[i], label); \
	unsafe_put_user(__t->thपढ़ो.fp_state.fpscr, &buf[i], label);	\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_vsx_to_user(to, task, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)to;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)				\
		unsafe_put_user(__t->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET], \
				&buf[i], label);\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_fpr_from_user(task, from, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)from;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NFPREG - 1; i++)				\
		unsafe_get_user(__t->thपढ़ो.TS_FPR(i), &buf[i], label); \
	unsafe_get_user(__t->thपढ़ो.fp_state.fpscr, &buf[i], label);	\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_vsx_from_user(task, from, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)from;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)				\
		unsafe_get_user(__t->thपढ़ो.fp_state.fpr[i][TS_VSRLOWOFFSET], \
				&buf[i], label);			\
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
#घोषणा unsafe_copy_ckfpr_to_user(to, task, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)to;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NFPREG - 1 ; i++)				\
		unsafe_put_user(__t->thपढ़ो.TS_CKFPR(i), &buf[i], label);\
	unsafe_put_user(__t->thपढ़ो.ckfp_state.fpscr, &buf[i], label);	\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_ckvsx_to_user(to, task, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)to;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)				\
		unsafe_put_user(__t->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET], \
				&buf[i], label);\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_ckfpr_from_user(task, from, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)from;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NFPREG - 1 ; i++)				\
		unsafe_get_user(__t->thपढ़ो.TS_CKFPR(i), &buf[i], label);\
	unsafe_get_user(__t->thपढ़ो.ckfp_state.fpscr, &buf[i], failed);	\
पूर्ण जबतक (0)

#घोषणा unsafe_copy_ckvsx_from_user(task, from, label)	करो अणु		\
	काष्ठा task_काष्ठा *__t = task;					\
	u64 __user *buf = (u64 __user *)from;				\
	पूर्णांक i;								\
									\
	क्रम (i = 0; i < ELF_NVSRHALFREG ; i++)				\
		unsafe_get_user(__t->thपढ़ो.ckfp_state.fpr[i][TS_VSRLOWOFFSET], \
				&buf[i], label);			\
पूर्ण जबतक (0)
#पूर्ण_अगर
#या_अगर defined(CONFIG_PPC_FPU_REGS)

#घोषणा unsafe_copy_fpr_to_user(to, task, label)		\
	unsafe_copy_to_user(to, (task)->thपढ़ो.fp_state.fpr,	\
			    ELF_NFPREG * माप(द्विगुन), label)

#घोषणा unsafe_copy_fpr_from_user(task, from, label)			\
	unsafe_copy_from_user((task)->thपढ़ो.fp_state.fpr, from,	\
			    ELF_NFPREG * माप(द्विगुन), label)

अटल अंतरभूत अचिन्हित दीर्घ
copy_fpr_to_user(व्योम __user *to, काष्ठा task_काष्ठा *task)
अणु
	वापस __copy_to_user(to, task->thपढ़ो.fp_state.fpr,
			      ELF_NFPREG * माप(द्विगुन));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_fpr_from_user(काष्ठा task_काष्ठा *task, व्योम __user *from)
अणु
	वापस __copy_from_user(task->thपढ़ो.fp_state.fpr, from,
			      ELF_NFPREG * माप(द्विगुन));
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
#घोषणा unsafe_copy_ckfpr_to_user(to, task, label)		\
	unsafe_copy_to_user(to, (task)->thपढ़ो.ckfp_state.fpr,	\
			    ELF_NFPREG * माप(द्विगुन), label)

अंतरभूत अचिन्हित दीर्घ copy_ckfpr_to_user(व्योम __user *to, काष्ठा task_काष्ठा *task)
अणु
	वापस __copy_to_user(to, task->thपढ़ो.ckfp_state.fpr,
			      ELF_NFPREG * माप(द्विगुन));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_ckfpr_from_user(काष्ठा task_काष्ठा *task, व्योम __user *from)
अणु
	वापस __copy_from_user(task->thपढ़ो.ckfp_state.fpr, from,
				ELF_NFPREG * माप(द्विगुन));
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */
#अन्यथा
#घोषणा unsafe_copy_fpr_to_user(to, task, label) करो अणु अगर (0) जाओ label;पूर्ण जबतक (0)

#घोषणा unsafe_copy_fpr_from_user(task, from, label) करो अणु अगर (0) जाओ label;पूर्ण जबतक (0)

अटल अंतरभूत अचिन्हित दीर्घ
copy_fpr_to_user(व्योम __user *to, काष्ठा task_काष्ठा *task)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_fpr_from_user(काष्ठा task_काष्ठा *task, व्योम __user *from)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64

बाह्य पूर्णांक handle_rt_संकेत64(काष्ठा kसंकेत *ksig, sigset_t *set,
			      काष्ठा task_काष्ठा *tsk);

#अन्यथा /* CONFIG_PPC64 */

बाह्य दीर्घ sys_rt_sigवापस(व्योम);
बाह्य दीर्घ sys_sigवापस(व्योम);

अटल अंतरभूत पूर्णांक handle_rt_संकेत64(काष्ठा kसंकेत *ksig, sigset_t *set,
				     काष्ठा task_काष्ठा *tsk)
अणु
	वापस -EFAULT;
पूर्ण

#पूर्ण_अगर /* !defined(CONFIG_PPC64) */

व्योम संकेत_fault(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		  स्थिर अक्षर *where, व्योम __user *ptr);

#पूर्ण_अगर  /* _POWERPC_ARCH_SIGNAL_H */
