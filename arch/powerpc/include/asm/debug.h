<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1999 Cort Dougan <cort@cs.nmt.edu>
 */
#अगर_अघोषित _ASM_POWERPC_DEBUG_H
#घोषणा _ASM_POWERPC_DEBUG_H

#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

काष्ठा pt_regs;

#अगर defined(CONFIG_DEBUGGER) || defined(CONFIG_KEXEC_CORE)

बाह्य पूर्णांक (*__debugger)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_ipi)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_bpt)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_sstep)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_iabr_match)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_अवरोध_match)(काष्ठा pt_regs *regs);
बाह्य पूर्णांक (*__debugger_fault_handler)(काष्ठा pt_regs *regs);

#घोषणा DEBUGGER_BOILERPLATE(__NAME) \
अटल अंतरभूत पूर्णांक __NAME(काष्ठा pt_regs *regs) \
अणु \
	अगर (unlikely(__ ## __NAME)) \
		वापस __ ## __NAME(regs); \
	वापस 0; \
पूर्ण

DEBUGGER_BOILERPLATE(debugger)
DEBUGGER_BOILERPLATE(debugger_ipi)
DEBUGGER_BOILERPLATE(debugger_bpt)
DEBUGGER_BOILERPLATE(debugger_sstep)
DEBUGGER_BOILERPLATE(debugger_iabr_match)
DEBUGGER_BOILERPLATE(debugger_अवरोध_match)
DEBUGGER_BOILERPLATE(debugger_fault_handler)

#अन्यथा
अटल अंतरभूत पूर्णांक debugger(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_ipi(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_bpt(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_sstep(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_iabr_match(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_अवरोध_match(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक debugger_fault_handler(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
#पूर्ण_अगर

व्योम __set_अवरोधpoपूर्णांक(पूर्णांक nr, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk);
bool ppc_अवरोधpoपूर्णांक_available(व्योम);
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
बाह्य व्योम करो_send_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
			 अचिन्हित दीर्घ error_code, पूर्णांक brkpt);
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_POWERPC_DEBUG_H */
