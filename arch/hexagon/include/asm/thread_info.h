<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Thपढ़ो support क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/page.h>
#पूर्ण_अगर

#घोषणा THREAD_SHIFT		12
#घोषणा THREAD_SIZE		(1<<THREAD_SHIFT)
#घोषणा THREAD_SIZE_ORDER	(THREAD_SHIFT - PAGE_SHIFT)

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

/*
 * This is जोड़'d with the "bottom" of the kernel stack.
 * It keeps track of thपढ़ो info which is handy क्रम routines
 * to access quickly.
 */

काष्ठा thपढ़ो_info अणु
	काष्ठा task_काष्ठा	*task;		/* मुख्य task काष्ठाure */
	अचिन्हित दीर्घ		flags;          /* low level flags */
	__u32                   cpu;            /* current cpu */
	पूर्णांक                     preempt_count;  /* 0=>preemptible,<0=>BUG */
	mm_segment_t            addr_limit;     /* segmentation sux */
	/*
	 * used क्रम syscalls somehow;
	 * seems to have a function poपूर्णांकer and four arguments
	 */
	/* Poपूर्णांकs to the current pt_regs frame  */
	काष्ठा pt_regs		*regs;
	/*
	 * saved kernel sp at चयन_to समय;
	 * not sure अगर this is used (it's not in the VM model it seems;
	 * see thपढ़ो_काष्ठा)
	 */
	अचिन्हित दीर्घ		sp;
पूर्ण;

#अन्यथा /* !__ASSEMBLY__ */

#समावेश <यंत्र/यंत्र-offsets.h>

#पूर्ण_अगर  /* __ASSEMBLY__  */

#अगर_अघोषित __ASSEMBLY__

#घोषणा INIT_THREAD_INFO(tsk)                   \
अणु                                               \
	.task           = &tsk,                 \
	.flags          = 0,                    \
	.cpu            = 0,                    \
	.preempt_count  = 1,                    \
	.addr_limit     = KERNEL_DS,            \
	.sp = 0,				\
	.regs = शून्य,			\
पूर्ण

/* Tacky preprocessor trickery */
#घोषणा	qqstr(s) qstr(s)
#घोषणा qstr(s) #s
#घोषणा QUOTED_THREADINFO_REG qqstr(THREADINFO_REG)

रेजिस्टर काष्ठा thपढ़ो_info *__current_thपढ़ो_info यंत्र(QUOTED_THREADINFO_REG);
#घोषणा current_thपढ़ो_info()  __current_thपढ़ो_info

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * thपढ़ो inक्रमmation flags
 * - these are process state flags that various assembly files
 *   may need to access
 * - pending work-to-be-करोne flags are in LSW
 * - other flags in MSW
 */

#घोषणा TIF_SYSCALL_TRACE       0       /* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME       1       /* resumption notअगरication requested */
#घोषणा TIF_SIGPENDING          2       /* संकेत pending */
#घोषणा TIF_NEED_RESCHED        3       /* rescheduling necessary */
#घोषणा TIF_SINGLESTEP          4       /* restore ss @ वापस to usr mode */
#घोषणा TIF_RESTORE_SIGMASK     6       /* restore sig mask in करो_संकेत() */
#घोषणा TIF_NOTIFY_SIGNAL	7       /* संकेत notअगरications exist */
/* true अगर poll_idle() is polling TIF_NEED_RESCHED */
#घोषणा TIF_MEMDIE              17      /* OOM समाप्तer समाप्तed process */

#घोषणा _TIF_SYSCALL_TRACE      (1 << TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME      (1 << TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING         (1 << TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED       (1 << TIF_NEED_RESCHED)
#घोषणा _TIF_SINGLESTEP         (1 << TIF_SINGLESTEP)
#घोषणा _TIF_NOTIFY_SIGNAL	(1 << TIF_NOTIFY_SIGNAL)

/* work to करो on पूर्णांकerrupt/exception वापस - All but TIF_SYSCALL_TRACE */
#घोषणा _TIF_WORK_MASK          (0x0000FFFF & ~_TIF_SYSCALL_TRACE)

/* work to करो on any वापस to u-space */
#घोषणा _TIF_ALLWORK_MASK       0x0000FFFF

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर
