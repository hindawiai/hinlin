<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Perक्रमmance event support - hardware-specअगरic disambiguation
 *
 * For now this is a compile-समय decision, but eventually it should be
 * runसमय.  This would allow multiplatक्रमm perf event support क्रम e300 (fsl
 * embedded perf counters) plus server/classic, and would accommodate
 * devices other than the core which provide their own perक्रमmance counters.
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 */

#अगर_घोषित CONFIG_PPC_PERF_CTRS
#समावेश <यंत्र/perf_event_server.h>
#अन्यथा
अटल अंतरभूत bool is_sier_available(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ get_pmcs_ext_regs(पूर्णांक idx) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSL_EMB_PERF_EVENT
#समावेश <यंत्र/perf_event_fsl_emb.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PERF_EVENTS
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/reg.h>

#घोषणा perf_arch_bpf_user_pt_regs(regs) &regs->user_regs

/*
 * Overload regs->result to specअगरy whether we should use the MSR (result
 * is zero) or the SIAR (result is non zero).
 */
#घोषणा perf_arch_fetch_caller_regs(regs, __ip)			\
	करो अणु							\
		(regs)->result = 0;				\
		(regs)->nip = __ip;				\
		(regs)->gpr[1] = current_stack_frame();		\
		यंत्र अस्थिर("mfmsr %0" : "=r" ((regs)->msr));	\
	पूर्ण जबतक (0)

/* To support perf_regs sier update */
बाह्य bool is_sier_available(व्योम);
बाह्य अचिन्हित दीर्घ get_pmcs_ext_regs(पूर्णांक idx);
/* To define perf extended regs mask value */
बाह्य u64 PERF_REG_EXTENDED_MASK;
#घोषणा PERF_REG_EXTENDED_MASK	PERF_REG_EXTENDED_MASK
#पूर्ण_अगर
