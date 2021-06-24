<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2014 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#अगर_अघोषित __MIPS_ASM_PM_CPS_H__
#घोषणा __MIPS_ASM_PM_CPS_H__

/*
 * The CM & CPC can only handle coherence & घातer control on a per-core basis,
 * thus in an MT प्रणाली the VP(E)s within each core are coupled and can only
 * enter or निकास states requiring CM or CPC assistance in unison.
 */
#अगर defined(CONFIG_CPU_MIPSR6)
# define coupled_coherence cpu_has_vp
#या_अगर defined(CONFIG_MIPS_MT)
# define coupled_coherence cpu_has_mipsmt
#अन्यथा
# define coupled_coherence 0
#पूर्ण_अगर

/* Enumeration of possible PM states */
क्रमागत cps_pm_state अणु
	CPS_PM_NC_WAIT,		/* MIPS रुको inकाष्ठाion, non-coherent */
	CPS_PM_CLOCK_GATED,	/* Core घड़ी gated */
	CPS_PM_POWER_GATED,	/* Core घातer gated */
	CPS_PM_STATE_COUNT,
पूर्ण;

/**
 * cps_pm_support_state - determine whether the प्रणाली supports a PM state
 * @state: the state to test क्रम support
 *
 * Returns true अगर the प्रणाली supports the given state, otherwise false.
 */
बाह्य bool cps_pm_support_state(क्रमागत cps_pm_state state);

/**
 * cps_pm_enter_state - enter a PM state
 * @state: the state to enter
 *
 * Enter the given PM state. If coupled_coherence is non-zero then it is
 * expected that this function be called at approximately the same समय on
 * each coupled CPU. Returns 0 on successful entry & निकास, otherwise -त्रुटि_सं.
 */
बाह्य पूर्णांक cps_pm_enter_state(क्रमागत cps_pm_state state);

#पूर्ण_अगर /* __MIPS_ASM_PM_CPS_H__ */
