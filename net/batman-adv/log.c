<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner
 */

#समावेश "log.h"
#समावेश "main.h"

#समावेश <मानकतर्क.स>

#समावेश "trace.h"

/**
 * batadv_debug_log() - Add debug log entry
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @fmt: क्रमmat string
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_debug_log(काष्ठा batadv_priv *bat_priv, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	trace_batadv_dbg(bat_priv, &vaf);

	बहु_पूर्ण(args);

	वापस 0;
पूर्ण
