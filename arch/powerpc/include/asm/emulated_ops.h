<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright 2007 Sony Corporation
 */

#अगर_अघोषित _ASM_POWERPC_EMULATED_OPS_H
#घोषणा _ASM_POWERPC_EMULATED_OPS_H

#समावेश <linux/atomic.h>
#समावेश <linux/perf_event.h>


#अगर_घोषित CONFIG_PPC_EMULATED_STATS

काष्ठा ppc_emulated_entry अणु
	स्थिर अक्षर *name;
	atomic_t val;
पूर्ण;

बाह्य काष्ठा ppc_emulated अणु
#अगर_घोषित CONFIG_ALTIVEC
	काष्ठा ppc_emulated_entry altivec;
#पूर्ण_अगर
	काष्ठा ppc_emulated_entry dcba;
	काष्ठा ppc_emulated_entry dcbz;
	काष्ठा ppc_emulated_entry fp_pair;
	काष्ठा ppc_emulated_entry isel;
	काष्ठा ppc_emulated_entry mcrxr;
	काष्ठा ppc_emulated_entry mfpvr;
	काष्ठा ppc_emulated_entry multiple;
	काष्ठा ppc_emulated_entry popcntb;
	काष्ठा ppc_emulated_entry spe;
	काष्ठा ppc_emulated_entry string;
	काष्ठा ppc_emulated_entry sync;
	काष्ठा ppc_emulated_entry unaligned;
#अगर_घोषित CONFIG_MATH_EMULATION
	काष्ठा ppc_emulated_entry math;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	काष्ठा ppc_emulated_entry vsx;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	काष्ठा ppc_emulated_entry mfdscr;
	काष्ठा ppc_emulated_entry mtdscr;
	काष्ठा ppc_emulated_entry lq_stq;
	काष्ठा ppc_emulated_entry lxvw4x;
	काष्ठा ppc_emulated_entry lxvh8x;
	काष्ठा ppc_emulated_entry lxvd2x;
	काष्ठा ppc_emulated_entry lxvb16x;
#पूर्ण_अगर
पूर्ण ppc_emulated;

बाह्य u32 ppc_warn_emulated;

बाह्य व्योम ppc_warn_emulated_prपूर्णांक(स्थिर अक्षर *type);

#घोषणा __PPC_WARN_EMULATED(type)					 \
	करो अणु								 \
		atomic_inc(&ppc_emulated.type.val);			 \
		अगर (ppc_warn_emulated)					 \
			ppc_warn_emulated_prपूर्णांक(ppc_emulated.type.name); \
	पूर्ण जबतक (0)

#अन्यथा /* !CONFIG_PPC_EMULATED_STATS */

#घोषणा __PPC_WARN_EMULATED(type)	करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* !CONFIG_PPC_EMULATED_STATS */

#घोषणा PPC_WARN_EMULATED(type, regs)					\
	करो अणु								\
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,		\
			1, regs, 0);					\
		__PPC_WARN_EMULATED(type);				\
	पूर्ण जबतक (0)

#घोषणा PPC_WARN_ALIGNMENT(type, regs)					\
	करो अणु								\
		perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS,		\
			1, regs, regs->dar);				\
		__PPC_WARN_EMULATED(type);				\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_POWERPC_EMULATED_OPS_H */
