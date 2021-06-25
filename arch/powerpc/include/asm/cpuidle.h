<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_CPUIDLE_H
#घोषणा _ASM_POWERPC_CPUIDLE_H

#अगर_घोषित CONFIG_PPC_POWERNV
/* Thपढ़ो state used in घातernv idle state management */
#घोषणा PNV_THREAD_RUNNING              0
#घोषणा PNV_THREAD_NAP                  1
#घोषणा PNV_THREAD_SLEEP                2
#घोषणा PNV_THREAD_WINKLE               3

/*
 * Core state used in घातernv idle क्रम POWER8.
 *
 * The lock bit synchronizes updates to the state, as well as parts of the
 * sleep/wake code (see kernel/idle_book3s.S).
 *
 * Bottom 8 bits track the idle state of each thपढ़ो. Bit is cleared beक्रमe
 * the thपढ़ो executes an idle inकाष्ठाion (nap/sleep/winkle).
 *
 * Then there is winkle tracking. A core करोes not lose complete state
 * until every thपढ़ो is in winkle. So the winkle count field counts the
 * number of thपढ़ोs in winkle (small winकरोw of false positives is okay
 * around the sleep/wake, so दीर्घ as there are no false negatives).
 *
 * When the winkle count reaches 8 (the COUNT_ALL_BIT becomes set), then
 * the THREAD_WINKLE_BITS are set, which indicate which thपढ़ोs have not
 * yet woken from the winkle state.
 */
#घोषणा NR_PNV_CORE_IDLE_LOCK_BIT		28
#घोषणा PNV_CORE_IDLE_LOCK_BIT			(1ULL << NR_PNV_CORE_IDLE_LOCK_BIT)

#घोषणा PNV_CORE_IDLE_WINKLE_COUNT_SHIFT	16
#घोषणा PNV_CORE_IDLE_WINKLE_COUNT		0x00010000
#घोषणा PNV_CORE_IDLE_WINKLE_COUNT_BITS		0x000F0000
#घोषणा PNV_CORE_IDLE_THREAD_WINKLE_BITS_SHIFT	8
#घोषणा PNV_CORE_IDLE_THREAD_WINKLE_BITS	0x0000FF00

#घोषणा PNV_CORE_IDLE_THREAD_BITS       	0x000000FF

/*
 * ============================ NOTE =================================
 * The older firmware populates only the RL field in the psscr_val and
 * sets the psscr_mask to 0xf. On such a firmware, the kernel sets the
 * reमुख्यing PSSCR fields to शेष values as follows:
 *
 * - ESL and EC bits are to 1. So wakeup from any stop state will be
 *   at vector 0x100.
 *
 * - MTL and PSLL are set to the maximum allowed value as per the ISA,
 *    i.e. 15.
 *
 * - The Transition Rate, TR is set to the Maximum value 3.
 */
#घोषणा PSSCR_HV_DEFAULT_VAL    (PSSCR_ESL | PSSCR_EC |		    \
				PSSCR_PSLL_MASK | PSSCR_TR_MASK |   \
				PSSCR_MTL_MASK)

#घोषणा PSSCR_HV_DEFAULT_MASK   (PSSCR_ESL | PSSCR_EC |		    \
				PSSCR_PSLL_MASK | PSSCR_TR_MASK |   \
				PSSCR_MTL_MASK | PSSCR_RL_MASK)
#घोषणा PSSCR_EC_SHIFT    20
#घोषणा PSSCR_ESL_SHIFT   21
#घोषणा GET_PSSCR_EC(x)   (((x) & PSSCR_EC) >> PSSCR_EC_SHIFT)
#घोषणा GET_PSSCR_ESL(x)  (((x) & PSSCR_ESL) >> PSSCR_ESL_SHIFT)
#घोषणा GET_PSSCR_RL(x)   ((x) & PSSCR_RL_MASK)

#घोषणा ERR_EC_ESL_MISMATCH		-1
#घोषणा ERR_DEEP_STATE_ESL_MISMATCH	-2

#अगर_अघोषित __ASSEMBLY__

#घोषणा PNV_IDLE_NAME_LEN    16
काष्ठा pnv_idle_states_t अणु
	अक्षर name[PNV_IDLE_NAME_LEN];
	u32 latency_ns;
	u32 residency_ns;
	u64 psscr_val;
	u64 psscr_mask;
	u32 flags;
	bool valid;
पूर्ण;

बाह्य काष्ठा pnv_idle_states_t *pnv_idle_states;
बाह्य पूर्णांक nr_pnv_idle_states;

अचिन्हित दीर्घ pnv_cpu_offline(अचिन्हित पूर्णांक cpu);
पूर्णांक validate_psscr_val_mask(u64 *psscr_val, u64 *psscr_mask, u32 flags);
अटल अंतरभूत व्योम report_invalid_psscr_val(u64 psscr_val, पूर्णांक err)
अणु
	चयन (err) अणु
	हाल ERR_EC_ESL_MISMATCH:
		pr_warn("Invalid psscr 0x%016llx : ESL,EC bits unequal",
			psscr_val);
		अवरोध;
	हाल ERR_DEEP_STATE_ESL_MISMATCH:
		pr_warn("Invalid psscr 0x%016llx : ESL cleared for deep stop-state",
			psscr_val);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर
