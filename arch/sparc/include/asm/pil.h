<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_PIL_H
#घोषणा _SPARC64_PIL_H

/* To aव्योम some locking problems, we hard allocate certain PILs
 * क्रम SMP cross call messages that must करो a etrap/rtrap.
 *
 * A local_irq_disable() करोes not block the cross call delivery, so
 * when SMP locking is an issue we reschedule the event पूर्णांकo a PIL
 * पूर्णांकerrupt which is blocked by local_irq_disable().
 *
 * In fact any XCALL which has to etrap/rtrap has a problem because
 * it is dअगरficult to prevent rtrap from running BH's, and that would
 * need to be करोne अगर the XCALL arrived जबतक %pil==PIL_NORMAL_MAX.
 *
 * Finally, in order to handle profiling events even when a
 * local_irq_disable() is in progress, we only disable up to level 14
 * पूर्णांकerrupts.  Profile counter overflow पूर्णांकerrupts arrive at level
 * 15.
 */
#घोषणा PIL_SMP_CALL_FUNC	1
#घोषणा PIL_SMP_RECEIVE_SIGNAL	2
#घोषणा PIL_SMP_CAPTURE		3
#घोषणा PIL_DEVICE_IRQ		5
#घोषणा PIL_SMP_CALL_FUNC_SNGL	6
#घोषणा PIL_DEFERRED_PCR_WORK	7
#घोषणा PIL_KGDB_CAPTURE	8
#घोषणा PIL_NORMAL_MAX		14
#घोषणा PIL_NMI			15

#पूर्ण_अगर /* !(_SPARC64_PIL_H) */
