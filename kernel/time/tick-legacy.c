<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Timer tick function क्रम architectures that lack generic घड़ीevents,
 * consolidated here from m68k/ia64/parisc/arm.
 */

#समावेश <linux/irq.h>
#समावेश <linux/profile.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>

#समावेश "tick-internal.h"

/**
 * legacy_समयr_tick() - advances the समयkeeping infraकाष्ठाure
 * @ticks:	number of ticks, that have elapsed since the last call.
 *
 * This is used by platक्रमms that have not been converted to
 * generic घड़ीevents.
 *
 * If 'ticks' is zero, the CPU is not handling समयkeeping, so
 * only perक्रमm process accounting and profiling.
 *
 * Must be called with पूर्णांकerrupts disabled.
 */
व्योम legacy_समयr_tick(अचिन्हित दीर्घ ticks)
अणु
	अगर (ticks) अणु
		raw_spin_lock(&jअगरfies_lock);
		ग_लिखो_seqcount_begin(&jअगरfies_seq);
		करो_समयr(ticks);
		ग_लिखो_seqcount_end(&jअगरfies_seq);
		raw_spin_unlock(&jअगरfies_lock);
		update_wall_समय();
	पूर्ण
	update_process_बार(user_mode(get_irq_regs()));
	profile_tick(CPU_PROFILING);
पूर्ण
