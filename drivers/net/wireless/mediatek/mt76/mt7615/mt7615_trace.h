<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2019 Lorenzo Bianconi <lorenzo@kernel.org>
 */

#अगर !defined(__MT7615_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MT7615_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mt7615.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mt7615

#घोषणा MAXNAME		32
#घोषणा DEV_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा DEV_ASSIGN	strlcpy(__entry->wiphy_name,	\
				wiphy_name(mt76_hw(dev)->wiphy), MAXNAME)
#घोषणा DEV_PR_FMT	"%s"
#घोषणा DEV_PR_ARG	__entry->wiphy_name

#घोषणा TOKEN_ENTRY	__field(u16, token)
#घोषणा TOKEN_ASSIGN	__entry->token = token
#घोषणा TOKEN_PR_FMT	" %d"
#घोषणा TOKEN_PR_ARG	__entry->token

DECLARE_EVENT_CLASS(dev_token,
	TP_PROTO(काष्ठा mt7615_dev *dev, u16 token),
	TP_ARGS(dev, token),
	TP_STRUCT__entry(
		DEV_ENTRY
		TOKEN_ENTRY
	),
	TP_fast_assign(
		DEV_ASSIGN;
		TOKEN_ASSIGN;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT TOKEN_PR_FMT,
		DEV_PR_ARG, TOKEN_PR_ARG
	)
);

DEFINE_EVENT(dev_token, mac_tx_मुक्त,
	TP_PROTO(काष्ठा mt7615_dev *dev, u16 token),
	TP_ARGS(dev, token)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता mt7615_trace

#समावेश <trace/define_trace.h>
