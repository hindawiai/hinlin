<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * musb_trace.c - MUSB Controller Trace Support
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Author: Bin Liu <b-liu@ti.com>
 */

#घोषणा CREATE_TRACE_POINTS
#समावेश "musb_trace.h"

व्योम musb_dbg(काष्ठा musb *musb, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	trace_musb_log(musb, &vaf);

	बहु_पूर्ण(args);
पूर्ण
