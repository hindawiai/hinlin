<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/traps.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_TRAP_H
#घोषणा __ASM_TRAP_H

#समावेश <linux/list.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/sections.h>

काष्ठा pt_regs;

काष्ठा undef_hook अणु
	काष्ठा list_head node;
	u32 instr_mask;
	u32 instr_val;
	u64 pstate_mask;
	u64 pstate_val;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, u32 instr);
पूर्ण;

व्योम रेजिस्टर_undef_hook(काष्ठा undef_hook *hook);
व्योम unरेजिस्टर_undef_hook(काष्ठा undef_hook *hook);
व्योम क्रमce_संकेत_inject(पूर्णांक संकेत, पूर्णांक code, अचिन्हित दीर्घ address, अचिन्हित पूर्णांक err);
व्योम arm64_notअगरy_segfault(अचिन्हित दीर्घ addr);
व्योम arm64_क्रमce_sig_fault(पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ far, स्थिर अक्षर *str);
व्योम arm64_क्रमce_sig_mceerr(पूर्णांक code, अचिन्हित दीर्घ far, लघु lsb, स्थिर अक्षर *str);
व्योम arm64_क्रमce_sig_ptrace_त्रुटि_सं_trap(पूर्णांक त्रुटि_सं, अचिन्हित दीर्घ far, स्थिर अक्षर *str);

/*
 * Move regs->pc to next inकाष्ठाion and करो necessary setup beक्रमe it
 * is executed.
 */
व्योम arm64_skip_faulting_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ size);

अटल अंतरभूत पूर्णांक __in_irqentry_text(अचिन्हित दीर्घ ptr)
अणु
	वापस ptr >= (अचिन्हित दीर्घ)&__irqentry_text_start &&
	       ptr < (अचिन्हित दीर्घ)&__irqentry_text_end;
पूर्ण

अटल अंतरभूत पूर्णांक in_entry_text(अचिन्हित दीर्घ ptr)
अणु
	वापस ptr >= (अचिन्हित दीर्घ)&__entry_text_start &&
	       ptr < (अचिन्हित दीर्घ)&__entry_text_end;
पूर्ण

/*
 * CPUs with the RAS extensions have an Implementation-Defined-Syndrome bit
 * to indicate whether this ESR has a RAS encoding. CPUs without this feature
 * have a ISS-Valid bit in the same position.
 * If this bit is set, we know its not a RAS SError.
 * If its clear, we need to know अगर the CPU supports RAS. Uncategorized RAS
 * errors share the same encoding as an all-zeros encoding from a CPU that
 * करोesn't support RAS.
 */
अटल अंतरभूत bool arm64_is_ras_serror(u32 esr)
अणु
	WARN_ON(preemptible());

	अगर (esr & ESR_ELx_IDS)
		वापस false;

	अगर (this_cpu_has_cap(ARM64_HAS_RAS_EXTN))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/*
 * Return the AET bits from a RAS SError's ESR.
 *
 * It is implementation defined whether Uncategorized errors are containable.
 * We treat them as Uncontainable.
 * Non-RAS SError's are reported as Uncontained/Uncategorized.
 */
अटल अंतरभूत u32 arm64_ras_serror_get_severity(u32 esr)
अणु
	u32 aet = esr & ESR_ELx_AET;

	अगर (!arm64_is_ras_serror(esr)) अणु
		/* Not a RAS error, we can't पूर्णांकerpret the ESR. */
		वापस ESR_ELx_AET_UC;
	पूर्ण

	/*
	 * AET is RES0 अगर 'the value वापसed in the DFSC field is not
	 * [ESR_ELx_FSC_SERROR]'
	 */
	अगर ((esr & ESR_ELx_FSC) != ESR_ELx_FSC_SERROR) अणु
		/* No severity inक्रमmation : Uncategorized */
		वापस ESR_ELx_AET_UC;
	पूर्ण

	वापस aet;
पूर्ण

bool arm64_is_fatal_ras_serror(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr);
व्योम __noवापस arm64_serror_panic(काष्ठा pt_regs *regs, u32 esr);
#पूर्ण_अगर
