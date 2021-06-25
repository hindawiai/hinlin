<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Chipidea Device Mode Trace Support
 *
 * Copyright (C) 2020 NXP
 *
 * Author: Peter Chen <peter.chen@nxp.com>
 */

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

व्योम ci_log(काष्ठा ci_hdrc *ci, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	trace_ci_log(ci, &vaf);
	बहु_पूर्ण(args);
पूर्ण
