<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* thपढ़ो_info.h: sparc64 low-level thपढ़ो inक्रमmation
 *
 * Copyright (C) 2002  David S. Miller (davem@redhat.com)
 */

#अगर_अघोषित _ASM_THREAD_INFO_H
#घोषणा _ASM_THREAD_INFO_H

#अगर_घोषित __KERNEL__

#घोषणा NSWINS		7

#घोषणा TI_FLAG_BYTE_FAULT_CODE		0
#घोषणा TI_FLAG_FAULT_CODE_SHIFT	56
#घोषणा TI_FLAG_BYTE_WSTATE		1
#घोषणा TI_FLAG_WSTATE_SHIFT		48
#घोषणा TI_FLAG_BYTE_NOERROR		2
#घोषणा TI_FLAG_BYTE_NOERROR_SHIFT	40
#घोषणा TI_FLAG_BYTE_FPDEPTH		3
#घोषणा TI_FLAG_FPDEPTH_SHIFT		32
#घोषणा TI_FLAG_BYTE_CWP		4
#घोषणा TI_FLAG_CWP_SHIFT		24
#घोषणा TI_FLAG_BYTE_WSAVED		5
#घोषणा TI_FLAG_WSAVED_SHIFT		16

#समावेश <यंत्र/page.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>

काष्ठा task_काष्ठा;

काष्ठा thपढ़ो_info अणु
	/* D$ line 1 */
	काष्ठा task_काष्ठा	*task;
	अचिन्हित दीर्घ		flags;
	__u8			fpsaved[7];
	__u8			status;
	अचिन्हित दीर्घ		ksp;

	/* D$ line 2 */
	अचिन्हित दीर्घ		fault_address;
	काष्ठा pt_regs		*kregs;
	पूर्णांक			preempt_count;	/* 0 => preemptable, <0 => BUG */
	__u8			new_child;
	__u8			current_ds;
	__u16			cpu;

	अचिन्हित दीर्घ		*utraps;

	काष्ठा reg_winकरोw 	reg_winकरोw[NSWINS];
	अचिन्हित दीर्घ 		rwbuf_stkptrs[NSWINS];

	अचिन्हित दीर्घ		gsr[7];
	अचिन्हित दीर्घ		xfsr[7];

	काष्ठा pt_regs		*kern_una_regs;
	अचिन्हित पूर्णांक		kern_una_insn;

	अचिन्हित दीर्घ		fpregs[(7 * 256) / माप(अचिन्हित दीर्घ)]
		__attribute__ ((aligned(64)));
पूर्ण;

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* offsets पूर्णांकo the thपढ़ो_info काष्ठा क्रम assembly code access */
#घोषणा TI_TASK		0x00000000
#घोषणा TI_FLAGS	0x00000008
#घोषणा TI_FAULT_CODE	(TI_FLAGS + TI_FLAG_BYTE_FAULT_CODE)
#घोषणा TI_WSTATE	(TI_FLAGS + TI_FLAG_BYTE_WSTATE)
#घोषणा TI_CWP		(TI_FLAGS + TI_FLAG_BYTE_CWP)
#घोषणा TI_FPDEPTH	(TI_FLAGS + TI_FLAG_BYTE_FPDEPTH)
#घोषणा TI_WSAVED	(TI_FLAGS + TI_FLAG_BYTE_WSAVED)
#घोषणा TI_SYS_NOERROR	(TI_FLAGS + TI_FLAG_BYTE_NOERROR)
#घोषणा TI_FPSAVED	0x00000010
#घोषणा TI_KSP		0x00000018
#घोषणा TI_FAULT_ADDR	0x00000020
#घोषणा TI_KREGS	0x00000028
#घोषणा TI_PRE_COUNT	0x00000030
#घोषणा TI_NEW_CHILD	0x00000034
#घोषणा TI_CURRENT_DS	0x00000035
#घोषणा TI_CPU		0x00000036
#घोषणा TI_UTRAPS	0x00000038
#घोषणा TI_REG_WINDOW	0x00000040
#घोषणा TI_RWIN_SPTRS	0x000003c0
#घोषणा TI_GSR		0x000003f8
#घोषणा TI_XFSR		0x00000430
#घोषणा TI_KUNA_REGS	0x00000468
#घोषणा TI_KUNA_INSN	0x00000470
#घोषणा TI_FPREGS	0x00000480

/* We embed this in the uppermost byte of thपढ़ो_info->flags */
#घोषणा FAULT_CODE_WRITE	0x01	/* Write access, implies D-TLB	   */
#घोषणा FAULT_CODE_DTLB		0x02	/* Miss happened in D-TLB	   */
#घोषणा FAULT_CODE_ITLB		0x04	/* Miss happened in I-TLB	   */
#घोषणा FAULT_CODE_WINFIXUP	0x08	/* Miss happened during spill/fill */
#घोषणा FAULT_CODE_BLKCOMMIT	0x10	/* Use blk-commit ASI in copy_page */
#घोषणा	FAULT_CODE_BAD_RA	0x20	/* Bad RA क्रम sun4v		   */

#अगर PAGE_SHIFT == 13
#घोषणा THREAD_SIZE (2*PAGE_SIZE)
#घोषणा THREAD_SHIFT (PAGE_SHIFT + 1)
#अन्यथा /* PAGE_SHIFT == 13 */
#घोषणा THREAD_SIZE PAGE_SIZE
#घोषणा THREAD_SHIFT PAGE_SHIFT
#पूर्ण_अगर /* PAGE_SHIFT == 13 */

/*
 * macros/functions क्रम gaining access to the thपढ़ो inक्रमmation काष्ठाure
 */
#अगर_अघोषित __ASSEMBLY__

#घोषणा INIT_THREAD_INFO(tsk)				\
अणु							\
	.task		=	&tsk,			\
	.current_ds	=	ASI_P,			\
	.preempt_count	=	INIT_PREEMPT_COUNT,	\
	.kregs		=	(काष्ठा pt_regs *)(init_stack+THREAD_SIZE)-1 \
पूर्ण

/* how to get the thपढ़ो inक्रमmation काष्ठा from C */
#अगर_अघोषित BUILD_VDSO
रेजिस्टर काष्ठा thपढ़ो_info *current_thपढ़ो_info_reg यंत्र("g6");
#घोषणा current_thपढ़ो_info()	(current_thपढ़ो_info_reg)
#अन्यथा
बाह्य काष्ठा thपढ़ो_info *current_thपढ़ो_info(व्योम);
#पूर्ण_अगर

/* thपढ़ो inक्रमmation allocation */
#अगर PAGE_SHIFT == 13
#घोषणा THREAD_SIZE_ORDER	1
#अन्यथा /* PAGE_SHIFT == 13 */
#घोषणा THREAD_SIZE_ORDER	0
#पूर्ण_अगर /* PAGE_SHIFT == 13 */

#घोषणा __thपढ़ो_flag_byte_ptr(ti)	\
	((अचिन्हित अक्षर *)(&((ti)->flags)))
#घोषणा __cur_thपढ़ो_flag_byte_ptr	__thपढ़ो_flag_byte_ptr(current_thपढ़ो_info())

#घोषणा get_thपढ़ो_fault_code()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_FAULT_CODE])
#घोषणा set_thपढ़ो_fault_code(val)	(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_FAULT_CODE] = (val))
#घोषणा get_thपढ़ो_wstate()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_WSTATE])
#घोषणा set_thपढ़ो_wstate(val)		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_WSTATE] = (val))
#घोषणा get_thपढ़ो_cwp()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_CWP])
#घोषणा set_thपढ़ो_cwp(val)		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_CWP] = (val))
#घोषणा get_thपढ़ो_noerror()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_NOERROR])
#घोषणा set_thपढ़ो_noerror(val)		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_NOERROR] = (val))
#घोषणा get_thपढ़ो_fpdepth()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_FPDEPTH])
#घोषणा set_thपढ़ो_fpdepth(val)		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_FPDEPTH] = (val))
#घोषणा get_thपढ़ो_wsaved()		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_WSAVED])
#घोषणा set_thपढ़ो_wsaved(val)		(__cur_thपढ़ो_flag_byte_ptr[TI_FLAG_BYTE_WSAVED] = (val))
#पूर्ण_अगर /* !(__ASSEMBLY__) */

/*
 * Thपढ़ो inक्रमmation flags, only 16 bits are available as we encode
 * other values पूर्णांकo the upper 6 bytes.
 *
 * On trap वापस we need to test several values:
 *
 * user:	need_resched, notअगरy_resume, संक_बाकी, wsaved
 * kernel:	fpdepth
 *
 * So to check क्रम work in the kernel हाल we simply load the fpdepth
 * byte out of the flags and test it.  For the user हाल we encode the
 * lower 3 bytes of flags as follows:
 *	----------------------------------------
 *	| wsaved | flags byte 1 | flags byte 2 |
 *	----------------------------------------
 * This optimizes the user test पूर्णांकo:
 *	ldx		[%g6 + TI_FLAGS], REG1
 *	sethi		%hi(_TIF_USER_WORK_MASK), REG2
 *	or		REG2, %lo(_TIF_USER_WORK_MASK), REG2
 *	andcc		REG1, REG2, %g0
 *	be,pt		no_work_to_करो
 *	 nop
 */
#घोषणा TIF_SYSCALL_TRACE	0	/* syscall trace active */
#घोषणा TIF_NOTIFY_RESUME	1	/* callback beक्रमe वापसing to user */
#घोषणा TIF_SIGPENDING		2	/* संकेत pending */
#घोषणा TIF_NEED_RESCHED	3	/* rescheduling necessary */
#घोषणा TIF_NOTIFY_SIGNAL	4	/* संकेत notअगरications exist */
#घोषणा TIF_UNALIGNED		5	/* allowed to करो unaligned accesses */
#घोषणा TIF_UPROBE		6	/* अवरोधpoपूर्णांकed or singlestepped */
#घोषणा TIF_32BIT		7	/* 32-bit binary */
#घोषणा TIF_NOHZ		8	/* in adaptive nohz mode */
#घोषणा TIF_SECCOMP		9	/* secure computing */
#घोषणा TIF_SYSCALL_AUDIT	10	/* syscall auditing active */
#घोषणा TIF_SYSCALL_TRACEPOINT	11	/* syscall tracepoपूर्णांक instrumentation */
/* NOTE: Thपढ़ो flags >= 12 should be ones we have no पूर्णांकerest
 *       in using in assembly, अन्यथा we can't use the mask as
 *       an immediate value in inकाष्ठाions such as andcc.
 */
#घोषणा TIF_MCDPER		12	/* Precise MCD exception */
#घोषणा TIF_MEMDIE		13	/* is terminating due to OOM समाप्तer */
#घोषणा TIF_POLLING_NRFLAG	14

#घोषणा _TIF_SYSCALL_TRACE	(1<<TIF_SYSCALL_TRACE)
#घोषणा _TIF_NOTIFY_RESUME	(1<<TIF_NOTIFY_RESUME)
#घोषणा _TIF_SIGPENDING		(1<<TIF_SIGPENDING)
#घोषणा _TIF_NEED_RESCHED	(1<<TIF_NEED_RESCHED)
#घोषणा _TIF_NOTIFY_SIGNAL	(1<<TIF_NOTIFY_SIGNAL)
#घोषणा _TIF_UNALIGNED		(1<<TIF_UNALIGNED)
#घोषणा _TIF_UPROBE		(1<<TIF_UPROBE)
#घोषणा _TIF_32BIT		(1<<TIF_32BIT)
#घोषणा _TIF_NOHZ		(1<<TIF_NOHZ)
#घोषणा _TIF_SECCOMP		(1<<TIF_SECCOMP)
#घोषणा _TIF_SYSCALL_AUDIT	(1<<TIF_SYSCALL_AUDIT)
#घोषणा _TIF_SYSCALL_TRACEPOINT	(1<<TIF_SYSCALL_TRACEPOINT)
#घोषणा _TIF_POLLING_NRFLAG	(1<<TIF_POLLING_NRFLAG)

#घोषणा _TIF_USER_WORK_MASK	((0xff << TI_FLAG_WSAVED_SHIFT) | \
				 _TIF_DO_NOTIFY_RESUME_MASK | \
				 _TIF_NEED_RESCHED)
#घोषणा _TIF_DO_NOTIFY_RESUME_MASK	(_TIF_NOTIFY_RESUME | \
					 _TIF_SIGPENDING | _TIF_UPROBE | \
					 _TIF_NOTIFY_SIGNAL)

#घोषणा is_32bit_task()	(test_thपढ़ो_flag(TIF_32BIT))

/*
 * Thपढ़ो-synchronous status.
 *
 * This is dअगरferent from the flags in that nobody अन्यथा
 * ever touches our thपढ़ो-synchronous status, so we करोn't
 * have to worry about atomic accesses.
 *
 * Note that there are only 8 bits available.
 */

#अगर_अघोषित __ASSEMBLY__

#घोषणा thपढ़ो32_stack_is_64bit(__SP) (((__SP) & 0x1) != 0)
#घोषणा test_thपढ़ो_64bit_stack(__SP) \
	((test_thपढ़ो_flag(TIF_32BIT) && !thपढ़ो32_stack_is_64bit(__SP)) ? \
	 false : true)

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _ASM_THREAD_INFO_H */
