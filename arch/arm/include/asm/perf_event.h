<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/include/यंत्र/perf_event.h
 *
 *  Copyright (C) 2009 picoChip Designs Ltd, Jamie Iles
 */

#अगर_अघोषित __ARM_PERF_EVENT_H__
#घोषणा __ARM_PERF_EVENT_H__

#अगर_घोषित CONFIG_PERF_EVENTS
काष्ठा pt_regs;
बाह्य अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs);
#घोषणा perf_misc_flags(regs)	perf_misc_flags(regs)
#पूर्ण_अगर

#घोषणा perf_arch_fetch_caller_regs(regs, __ip) अणु \
	(regs)->ARM_pc = (__ip); \
	(regs)->ARM_fp = (अचिन्हित दीर्घ) __builtin_frame_address(0); \
	(regs)->ARM_sp = current_stack_poपूर्णांकer; \
	(regs)->ARM_cpsr = SVC_MODE; \
पूर्ण

#पूर्ण_अगर /* __ARM_PERF_EVENT_H__ */
