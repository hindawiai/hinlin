<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Kernel Concurrency Sanitizer (KCSAN) infraकाष्ठाure. For more info please
 * see Documentation/dev-tools/kcsan.rst.
 *
 * Copyright (C) 2019, Google LLC.
 */

#अगर_अघोषित _KERNEL_KCSAN_KCSAN_H
#घोषणा _KERNEL_KCSAN_KCSAN_H

#समावेश <linux/atomic.h>
#समावेश <linux/kcsan.h>
#समावेश <linux/sched.h>

/* The number of adjacent watchpoपूर्णांकs to check. */
#घोषणा KCSAN_CHECK_ADJACENT 1
#घोषणा NUM_SLOTS (1 + 2*KCSAN_CHECK_ADJACENT)

बाह्य अचिन्हित पूर्णांक kcsan_udelay_task;
बाह्य अचिन्हित पूर्णांक kcsan_udelay_पूर्णांकerrupt;

/*
 * Globally enable and disable KCSAN.
 */
बाह्य bool kcsan_enabled;

/*
 * Save/restore IRQ flags state trace dirtied by KCSAN.
 */
व्योम kcsan_save_irqtrace(काष्ठा task_काष्ठा *task);
व्योम kcsan_restore_irqtrace(काष्ठा task_काष्ठा *task);

/*
 * Statistics counters displayed via debugfs; should only be modअगरied in
 * slow-paths.
 */
क्रमागत kcsan_counter_id अणु
	/*
	 * Number of watchpoपूर्णांकs currently in use.
	 */
	KCSAN_COUNTER_USED_WATCHPOINTS,

	/*
	 * Total number of watchpoपूर्णांकs set up.
	 */
	KCSAN_COUNTER_SETUP_WATCHPOINTS,

	/*
	 * Total number of data races.
	 */
	KCSAN_COUNTER_DATA_RACES,

	/*
	 * Total number of ASSERT failures due to races. If the observed race is
	 * due to two conflicting ASSERT type accesses, then both will be
	 * counted.
	 */
	KCSAN_COUNTER_ASSERT_FAILURES,

	/*
	 * Number of बार no watchpoपूर्णांकs were available.
	 */
	KCSAN_COUNTER_NO_CAPACITY,

	/*
	 * A thपढ़ो checking a watchpoपूर्णांक raced with another checking thपढ़ो;
	 * only one will be reported.
	 */
	KCSAN_COUNTER_REPORT_RACES,

	/*
	 * Observed data value change, but ग_लिखोr thपढ़ो unknown.
	 */
	KCSAN_COUNTER_RACES_UNKNOWN_ORIGIN,

	/*
	 * The access cannot be encoded to a valid watchpoपूर्णांक.
	 */
	KCSAN_COUNTER_UNENCODABLE_ACCESSES,

	/*
	 * Watchpoपूर्णांक encoding caused a watchpoपूर्णांक to fire on mismatching
	 * accesses.
	 */
	KCSAN_COUNTER_ENCODING_FALSE_POSITIVES,

	KCSAN_COUNTER_COUNT, /* number of counters */
पूर्ण;
बाह्य atomic_दीर्घ_t kcsan_counters[KCSAN_COUNTER_COUNT];

/*
 * Returns true अगर data races in the function symbol that maps to func_addr
 * (offsets are ignored) should *not* be reported.
 */
बाह्य bool kcsan_skip_report_debugfs(अचिन्हित दीर्घ func_addr);

/*
 * Value-change states.
 */
क्रमागत kcsan_value_change अणु
	/*
	 * Did not observe a value-change, however, it is valid to report the
	 * race, depending on preferences.
	 */
	KCSAN_VALUE_CHANGE_MAYBE,

	/*
	 * Did not observe a value-change, and it is invalid to report the race.
	 */
	KCSAN_VALUE_CHANGE_FALSE,

	/*
	 * The value was observed to change, and the race should be reported.
	 */
	KCSAN_VALUE_CHANGE_TRUE,
पूर्ण;

क्रमागत kcsan_report_type अणु
	/*
	 * The thपढ़ो that set up the watchpoपूर्णांक and briefly stalled was
	 * संकेतled that another thपढ़ो triggered the watchpoपूर्णांक.
	 */
	KCSAN_REPORT_RACE_SIGNAL,

	/*
	 * A thपढ़ो found and consumed a matching watchpoपूर्णांक.
	 */
	KCSAN_REPORT_CONSUMED_WATCHPOINT,

	/*
	 * No other thपढ़ो was observed to race with the access, but the data
	 * value beक्रमe and after the stall dअगरfers.
	 */
	KCSAN_REPORT_RACE_UNKNOWN_ORIGIN,
पूर्ण;

/*
 * Prपूर्णांक a race report from thपढ़ो that encountered the race.
 */
बाह्य व्योम kcsan_report(स्थिर अस्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक access_type,
			 क्रमागत kcsan_value_change value_change,
			 क्रमागत kcsan_report_type type, पूर्णांक watchpoपूर्णांक_idx);

#पूर्ण_अगर /* _KERNEL_KCSAN_KCSAN_H */
