<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Based on arch/arm/include/यंत्र/exception.h
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_EXCEPTION_H
#घोषणा __ASM_EXCEPTION_H

#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/ptrace.h>

#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
#घोषणा __exception_irq_entry	__irq_entry
#अन्यथा
#घोषणा __exception_irq_entry	__kprobes
#पूर्ण_अगर

अटल अंतरभूत u32 disr_to_esr(u64 disr)
अणु
	अचिन्हित पूर्णांक esr = ESR_ELx_EC_SERROR << ESR_ELx_EC_SHIFT;

	अगर ((disr & DISR_EL1_IDS) == 0)
		esr |= (disr & DISR_EL1_ESR_MASK);
	अन्यथा
		esr |= (disr & ESR_ELx_ISS_MASK);

	वापस esr;
पूर्ण

यंत्रlinkage व्योम el1_sync_handler(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम el0_sync_handler(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम el0_sync_compat_handler(काष्ठा pt_regs *regs);

यंत्रlinkage व्योम noinstr enter_el1_irq_or_nmi(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम noinstr निकास_el1_irq_or_nmi(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम enter_from_user_mode(व्योम);
यंत्रlinkage व्योम निकास_to_user_mode(व्योम);
व्योम arm64_enter_nmi(काष्ठा pt_regs *regs);
व्योम arm64_निकास_nmi(काष्ठा pt_regs *regs);
व्योम करो_mem_पात(अचिन्हित दीर्घ far, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_undefinstr(काष्ठा pt_regs *regs);
व्योम करो_bti(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम bad_mode(काष्ठा pt_regs *regs, पूर्णांक reason, अचिन्हित पूर्णांक esr);
व्योम करो_debug_exception(अचिन्हित दीर्घ addr_अगर_watchpoपूर्णांक, अचिन्हित पूर्णांक esr,
			काष्ठा pt_regs *regs);
व्योम करो_fpsimd_acc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_sve_acc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_fpsimd_exc(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_sysinstr(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_sp_pc_पात(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम bad_el0_sync(काष्ठा pt_regs *regs, पूर्णांक reason, अचिन्हित पूर्णांक esr);
व्योम करो_cp15instr(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
व्योम करो_el0_svc(काष्ठा pt_regs *regs);
व्योम करो_el0_svc_compat(काष्ठा pt_regs *regs);
व्योम करो_ptrauth_fault(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr);
#पूर्ण_अगर	/* __ASM_EXCEPTION_H */
