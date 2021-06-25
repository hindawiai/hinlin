<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lib/debug_locks.c
 *
 * Generic place क्रम common debugging facilities क्रम various locks:
 * spinlocks, rwlocks, mutexes and rwsems.
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 */
#समावेश <linux/rwsem.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/debug_locks.h>

/*
 * We want to turn all lock-debugging facilities on/off at once,
 * via a global flag. The reason is that once a single bug has been
 * detected and reported, there might be cascade of followup bugs
 * that would just muddy the log. So we report the first one and
 * shut up after that.
 */
पूर्णांक debug_locks __पढ़ो_mostly = 1;
EXPORT_SYMBOL_GPL(debug_locks);

/*
 * The locking-testsuite uses <debug_locks_silent> to get a
 * 'silent failure': nothing is prपूर्णांकed to the console when
 * a locking bug is detected.
 */
पूर्णांक debug_locks_silent __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(debug_locks_silent);

/*
 * Generic 'turn off all lock debugging' function:
 */
noinstr पूर्णांक debug_locks_off(व्योम)
अणु
	अगर (debug_locks && __debug_locks_off()) अणु
		अगर (!debug_locks_silent) अणु
			console_verbose();
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(debug_locks_off);
