<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2013,2016 Qualcomm Atheros, Inc.
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश "wil6210.h"
#समावेश "trace.h"

व्योम __wil_err(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	netdev_err(wil->मुख्य_ndev, "%pV", &vaf);
	trace_wil6210_log_err(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __wil_err_ratelimited(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!net_ratelimit())
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	netdev_err(wil->मुख्य_ndev, "%pV", &vaf);
	trace_wil6210_log_err(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम wil_dbg_ratelimited(स्थिर काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (!net_ratelimit())
		वापस;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	netdev_dbg(wil->मुख्य_ndev, "%pV", &vaf);
	trace_wil6210_log_dbg(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम __wil_info(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	netdev_info(wil->मुख्य_ndev, "%pV", &vaf);
	trace_wil6210_log_info(&vaf);
	बहु_पूर्ण(args);
पूर्ण

व्योम wil_dbg_trace(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	trace_wil6210_log_dbg(&vaf);
	बहु_पूर्ण(args);
पूर्ण
