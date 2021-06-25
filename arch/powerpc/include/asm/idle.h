<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_IDLE_H
#घोषणा _ASM_POWERPC_IDLE_H
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/paca.h>

#अगर_घोषित CONFIG_PPC_PSERIES
DECLARE_PER_CPU(u64, idle_spurr_cycles);
DECLARE_PER_CPU(u64, idle_entry_purr_snap);
DECLARE_PER_CPU(u64, idle_entry_spurr_snap);

अटल अंतरभूत व्योम snapshot_purr_idle_entry(व्योम)
अणु
	*this_cpu_ptr(&idle_entry_purr_snap) = mfspr(SPRN_PURR);
पूर्ण

अटल अंतरभूत व्योम snapshot_spurr_idle_entry(व्योम)
अणु
	*this_cpu_ptr(&idle_entry_spurr_snap) = mfspr(SPRN_SPURR);
पूर्ण

अटल अंतरभूत व्योम update_idle_purr_accounting(व्योम)
अणु
	u64 रुको_cycles;
	u64 in_purr = *this_cpu_ptr(&idle_entry_purr_snap);

	रुको_cycles = be64_to_cpu(get_lppaca()->रुको_state_cycles);
	रुको_cycles += mfspr(SPRN_PURR) - in_purr;
	get_lppaca()->रुको_state_cycles = cpu_to_be64(रुको_cycles);
पूर्ण

अटल अंतरभूत व्योम update_idle_spurr_accounting(व्योम)
अणु
	u64 *idle_spurr_cycles_ptr = this_cpu_ptr(&idle_spurr_cycles);
	u64 in_spurr = *this_cpu_ptr(&idle_entry_spurr_snap);

	*idle_spurr_cycles_ptr += mfspr(SPRN_SPURR) - in_spurr;
पूर्ण

अटल अंतरभूत व्योम pseries_idle_prolog(व्योम)
अणु
	ppc64_runlatch_off();
	snapshot_purr_idle_entry();
	snapshot_spurr_idle_entry();
	/*
	 * Indicate to the HV that we are idle. Now would be
	 * a good समय to find other work to dispatch.
	 */
	get_lppaca()->idle = 1;
पूर्ण

अटल अंतरभूत व्योम pseries_idle_epilog(व्योम)
अणु
	update_idle_purr_accounting();
	update_idle_spurr_accounting();
	get_lppaca()->idle = 0;
	ppc64_runlatch_on();
पूर्ण

अटल अंतरभूत u64 पढ़ो_this_idle_purr(व्योम)
अणु
	/*
	 * If we are पढ़ोing from an idle context, update the
	 * idle-purr cycles corresponding to the last idle period.
	 * Since the idle context is not yet over, take a fresh
	 * snapshot of the idle-purr.
	 */
	अगर (unlikely(get_lppaca()->idle == 1)) अणु
		update_idle_purr_accounting();
		snapshot_purr_idle_entry();
	पूर्ण

	वापस be64_to_cpu(get_lppaca()->रुको_state_cycles);
पूर्ण

अटल अंतरभूत u64 पढ़ो_this_idle_spurr(व्योम)
अणु
	/*
	 * If we are पढ़ोing from an idle context, update the
	 * idle-spurr cycles corresponding to the last idle period.
	 * Since the idle context is not yet over, take a fresh
	 * snapshot of the idle-spurr.
	 */
	अगर (get_lppaca()->idle == 1) अणु
		update_idle_spurr_accounting();
		snapshot_spurr_idle_entry();
	पूर्ण

	वापस *this_cpu_ptr(&idle_spurr_cycles);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_PSERIES */
#पूर्ण_अगर
