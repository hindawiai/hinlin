<शैली गुरु>
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर !defined(_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "ath.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ath

#अगर !defined(CONFIG_ATH_TRACEPOINTS)

#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, ...) अटल अंतरभूत व्योम trace_ ## name(proto) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_ATH_TRACEPOINTS */

TRACE_EVENT(ath_log,

	    TP_PROTO(काष्ठा wiphy *wiphy,
		     काष्ठा va_क्रमmat *vaf),

	    TP_ARGS(wiphy, vaf),

	    TP_STRUCT__entry(
		    __string(device, wiphy_name(wiphy))
		    __string(driver, KBUILD_MODNAME)
		    __dynamic_array(अक्षर, msg, ATH_DBG_MAX_LEN)
	    ),

	    TP_fast_assign(
		    __assign_str(device, wiphy_name(wiphy));
		    __assign_str(driver, KBUILD_MODNAME);
		    WARN_ON_ONCE(vsnम_लिखो(__get_dynamic_array(msg),
					   ATH_DBG_MAX_LEN,
					   vaf->fmt,
					   *vaf->va) >= ATH_DBG_MAX_LEN);
	    ),

	    TP_prपूर्णांकk(
		    "%s %s %s",
		    __get_str(driver),
		    __get_str(device),
		    __get_str(msg)
	    )
);

#पूर्ण_अगर /* _TRACE_H || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
