<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2021 Lorenzo Bianconi <lorenzo@kernel.org>
 */

#अगर !defined(__MT7921_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MT7921_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mt7921.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mt7921

#घोषणा MAXNAME		32
#घोषणा DEV_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा DEV_ASSIGN	strlcpy(__entry->wiphy_name,	\
				wiphy_name(mt76_hw(dev)->wiphy), MAXNAME)
#घोषणा DEV_PR_FMT	"%s"
#घोषणा DEV_PR_ARG	__entry->wiphy_name
#घोषणा LP_STATE_PR_ARG	__entry->lp_state ? "lp ready" : "lp not ready"

TRACE_EVENT(lp_event,
	TP_PROTO(काष्ठा mt7921_dev *dev, u8 lp_state),

	TP_ARGS(dev, lp_state),

	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u8, lp_state)
	),

	TP_fast_assign(
		DEV_ASSIGN;
		__entry->lp_state = lp_state;
	),

	TP_prपूर्णांकk(
		DEV_PR_FMT " %s",
		DEV_PR_ARG, LP_STATE_PR_ARG
	)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता mt7921_trace

#समावेश <trace/define_trace.h>
