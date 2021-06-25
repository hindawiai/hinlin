<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power trace poपूर्णांकs
 *
 * Copyright (C) 2009 Arjan van de Ven <arjan@linux.पूर्णांकel.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/घातer.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(suspend_resume);
EXPORT_TRACEPOINT_SYMBOL_GPL(cpu_idle);
EXPORT_TRACEPOINT_SYMBOL_GPL(cpu_frequency);
EXPORT_TRACEPOINT_SYMBOL_GPL(घातernv_throttle);

