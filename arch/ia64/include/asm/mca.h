<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File:	mca.h
 * Purpose:	Machine check handling specअगरic defines
 *
 * Copyright (C) 1999, 2004 Silicon Graphics, Inc.
 * Copyright (C) Vijay Chander <vijay@engr.sgi.com>
 * Copyright (C) Srinivasa Thirumalaअक्षर <sprasad@engr.sgi.com>
 * Copyright (C) Russ Anderson <rja@sgi.com>
 */

#अगर_अघोषित _ASM_IA64_MCA_H
#घोषणा _ASM_IA64_MCA_H

#अगर !defined(__ASSEMBLY__)

#समावेश <linux/percpu.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ptrace.h>

#घोषणा IA64_MCA_RENDEZ_TIMEOUT		(20 * 1000)	/* value in milliseconds - 20 seconds */

प्रकार काष्ठा ia64_fptr अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ gp;
पूर्ण ia64_fptr_t;

प्रकार जोड़ cmcv_reg_u अणु
	u64	cmcv_regval;
	काष्ठा	अणु
		u64	cmcr_vector		: 8;
		u64	cmcr_reserved1		: 4;
		u64	cmcr_ignored1		: 1;
		u64	cmcr_reserved2		: 3;
		u64	cmcr_mask		: 1;
		u64	cmcr_ignored2		: 47;
	पूर्ण cmcv_reg_s;

पूर्ण cmcv_reg_t;

#घोषणा cmcv_mask		cmcv_reg_s.cmcr_mask
#घोषणा cmcv_vector		cmcv_reg_s.cmcr_vector

क्रमागत अणु
	IA64_MCA_RENDEZ_CHECKIN_NOTDONE	=	0x0,
	IA64_MCA_RENDEZ_CHECKIN_DONE	=	0x1,
	IA64_MCA_RENDEZ_CHECKIN_INIT	=	0x2,
	IA64_MCA_RENDEZ_CHECKIN_CONCURRENT_MCA	=	0x3,
पूर्ण;

/* Inक्रमmation मुख्यtained by the MC infraकाष्ठाure */
प्रकार काष्ठा ia64_mc_info_s अणु
	u64		imi_mca_handler;
	माप_प्रकार		imi_mca_handler_size;
	u64		imi_monarch_init_handler;
	माप_प्रकार		imi_monarch_init_handler_size;
	u64		imi_slave_init_handler;
	माप_प्रकार		imi_slave_init_handler_size;
	u8		imi_rendez_checkin[NR_CPUS];

पूर्ण ia64_mc_info_t;

/* Hanकरोver state from SAL to OS and vice versa, क्रम both MCA and INIT events.
 * Besides the hanकरोver state, it also contains some saved रेजिस्टरs from the
 * समय of the event.
 * Note: mca_यंत्र.S depends on the precise layout of this काष्ठाure.
 */

काष्ठा ia64_sal_os_state अणु

	/* SAL to OS */
	अचिन्हित दीर्घ		os_gp;			/* GP of the os रेजिस्टरed with the SAL, physical */
	अचिन्हित दीर्घ		pal_proc;		/* PAL_PROC entry poपूर्णांक, physical */
	अचिन्हित दीर्घ		sal_proc;		/* SAL_PROC entry poपूर्णांक, physical */
	अचिन्हित दीर्घ		rv_rc;			/* MCA - Rendezvous state, INIT - reason code */
	अचिन्हित दीर्घ		proc_state_param;	/* from R18 */
	अचिन्हित दीर्घ		monarch;		/* 1 क्रम a monarch event, 0 क्रम a slave */

	/* common */
	अचिन्हित दीर्घ		sal_ra;			/* Return address in SAL, physical */
	अचिन्हित दीर्घ		sal_gp;			/* GP of the SAL - physical */
	काष्ठा pal_min_state_area *pal_min_state;	/* from R17.  physical in यंत्र, भव in C */
	/* Previous values of IA64_KR(CURRENT) and IA64_KR(CURRENT_STACK).
	 * Note: अगर the MCA/INIT recovery code wants to resume to a new context
	 * then it must change these values to reflect the new kernel stack.
	 */
	अचिन्हित दीर्घ		prev_IA64_KR_CURRENT;	/* previous value of IA64_KR(CURRENT) */
	अचिन्हित दीर्घ		prev_IA64_KR_CURRENT_STACK;
	काष्ठा task_काष्ठा	*prev_task;		/* previous task, शून्य अगर it is not useful */
	/* Some पूर्णांकerrupt रेजिस्टरs are not saved in minstate, pt_regs or
	 * चयन_stack.  Because MCA/INIT can occur when पूर्णांकerrupts are
	 * disabled, we need to save the additional पूर्णांकerrupt रेजिस्टरs over
	 * MCA/INIT and resume.
	 */
	अचिन्हित दीर्घ		isr;
	अचिन्हित दीर्घ		अगरa;
	अचिन्हित दीर्घ		itir;
	अचिन्हित दीर्घ		iipa;
	अचिन्हित दीर्घ		iim;
	अचिन्हित दीर्घ		iha;

	/* OS to SAL */
	अचिन्हित दीर्घ		os_status;		/* OS status to SAL, क्रमागत below */
	अचिन्हित दीर्घ		context;		/* 0 अगर वापस to same context
							   1 अगर वापस to new context */

	/* I-resources */
	अचिन्हित दीर्घ		iip;
	अचिन्हित दीर्घ		ipsr;
	अचिन्हित दीर्घ		अगरs;
पूर्ण;

क्रमागत अणु
	IA64_MCA_CORRECTED	=	0x0,	/* Error has been corrected by OS_MCA */
	IA64_MCA_WARM_BOOT	=	-1,	/* Warm boot of the प्रणाली need from SAL */
	IA64_MCA_COLD_BOOT	=	-2,	/* Cold boot of the प्रणाली need from SAL */
	IA64_MCA_HALT		=	-3	/* System to be halted by SAL */
पूर्ण;

क्रमागत अणु
	IA64_INIT_RESUME	=	0x0,	/* Resume after वापस from INIT */
	IA64_INIT_WARM_BOOT	=	-1,	/* Warm boot of the प्रणाली need from SAL */
पूर्ण;

क्रमागत अणु
	IA64_MCA_SAME_CONTEXT	=	0x0,	/* SAL to वापस to same context */
	IA64_MCA_NEW_CONTEXT	=	-1	/* SAL to वापस to new context */
पूर्ण;

/* Per-CPU MCA state that is too big क्रम normal per-CPU variables.  */

काष्ठा ia64_mca_cpu अणु
	u64 mca_stack[KERNEL_STACK_SIZE/8];
	u64 init_stack[KERNEL_STACK_SIZE/8];
पूर्ण;

/* Array of physical addresses of each CPU's MCA area.  */
बाह्य अचिन्हित दीर्घ __per_cpu_mca[NR_CPUS];

बाह्य पूर्णांक cpe_vector;
बाह्य पूर्णांक ia64_cpe_irq;
बाह्य व्योम ia64_mca_init(व्योम);
बाह्य व्योम ia64_mca_irq_init(व्योम);
बाह्य व्योम ia64_mca_cpu_init(व्योम *);
बाह्य व्योम ia64_os_mca_dispatch(व्योम);
बाह्य व्योम ia64_os_mca_dispatch_end(व्योम);
बाह्य व्योम ia64_mca_ucmc_handler(काष्ठा pt_regs *, काष्ठा ia64_sal_os_state *);
बाह्य व्योम ia64_init_handler(काष्ठा pt_regs *,
			      काष्ठा चयन_stack *,
			      काष्ठा ia64_sal_os_state *);
बाह्य व्योम ia64_os_init_on_kdump(व्योम);
बाह्य व्योम ia64_monarch_init_handler(व्योम);
बाह्य व्योम ia64_slave_init_handler(व्योम);
बाह्य व्योम ia64_mca_cmc_vector_setup(व्योम);
बाह्य पूर्णांक  ia64_reg_MCA_extension(पूर्णांक (*fn)(व्योम *, काष्ठा ia64_sal_os_state *));
बाह्य व्योम ia64_unreg_MCA_extension(व्योम);
बाह्य अचिन्हित दीर्घ ia64_get_rnat(अचिन्हित दीर्घ *);
बाह्य व्योम ia64_set_psr_mc(व्योम);
बाह्य व्योम ia64_mca_prपूर्णांकk(स्थिर अक्षर * fmt, ...)
	 __attribute__ ((क्रमmat (म_लिखो, 1, 2)));

काष्ठा ia64_mca_notअगरy_die अणु
	काष्ठा ia64_sal_os_state *sos;
	पूर्णांक *monarch_cpu;
	पूर्णांक *data;
पूर्ण;

DECLARE_PER_CPU(u64, ia64_mca_pal_base);

#अन्यथा	/* __ASSEMBLY__ */

#घोषणा IA64_MCA_CORRECTED	0x0	/* Error has been corrected by OS_MCA */
#घोषणा IA64_MCA_WARM_BOOT	-1	/* Warm boot of the प्रणाली need from SAL */
#घोषणा IA64_MCA_COLD_BOOT	-2	/* Cold boot of the प्रणाली need from SAL */
#घोषणा IA64_MCA_HALT		-3	/* System to be halted by SAL */

#घोषणा IA64_INIT_RESUME	0x0	/* Resume after वापस from INIT */
#घोषणा IA64_INIT_WARM_BOOT	-1	/* Warm boot of the प्रणाली need from SAL */

#घोषणा IA64_MCA_SAME_CONTEXT	0x0	/* SAL to वापस to same context */
#घोषणा IA64_MCA_NEW_CONTEXT	-1	/* SAL to वापस to new context */

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_IA64_MCA_H */
