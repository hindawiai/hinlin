<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_trace.c - trace support
 *
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#घोषणा CREATE_TRACE_POINTS
#समावेश "mtu3_debug.h"
#समावेश "mtu3_trace.h"

व्योम mtu3_dbg_trace(काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	trace_mtu3_log(dev, &vaf);
	बहु_पूर्ण(args);
पूर्ण
