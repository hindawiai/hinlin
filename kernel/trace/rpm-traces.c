<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Power trace poपूर्णांकs
 *
 * Copyright (C) 2009 Ming Lei <ming.lei@canonical.com>
 */

#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/rpm.h>

EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_वापस_पूर्णांक);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_idle);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_suspend);
EXPORT_TRACEPOINT_SYMBOL_GPL(rpm_resume);
