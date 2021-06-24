<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Sven Eckelmann
 */

#अगर !defined(_NET_BATMAN_ADV_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _NET_BATMAN_ADV_TRACE_H_

#समावेश "main.h"

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM batadv

/* provide dummy function when tracing is disabled */
#अगर !defined(CONFIG_BATMAN_ADV_TRACING)

#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) \
	अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_BATMAN_ADV_TRACING */

#घोषणा BATADV_MAX_MSG_LEN	256

TRACE_EVENT(batadv_dbg,

	    TP_PROTO(काष्ठा batadv_priv *bat_priv,
		     काष्ठा va_क्रमmat *vaf),

	    TP_ARGS(bat_priv, vaf),

	    TP_STRUCT__entry(
		    __string(device, bat_priv->soft_अगरace->name)
		    __string(driver, KBUILD_MODNAME)
		    __dynamic_array(अक्षर, msg, BATADV_MAX_MSG_LEN)
	    ),

	    TP_fast_assign(
		    __assign_str(device, bat_priv->soft_अगरace->name);
		    __assign_str(driver, KBUILD_MODNAME);
		    WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
					   BATADV_MAX_MSG_LEN,
					   vaf->fmt,
					   *vaf->va) >= BATADV_MAX_MSG_LEN);
	    ),

	    TP_prपूर्णांकk(
		    "%s %s %s",
		    __get_str(driver),
		    __get_str(device),
		    __get_str(msg)
	    )
);

#पूर्ण_अगर /* _NET_BATMAN_ADV_TRACE_H_ || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
