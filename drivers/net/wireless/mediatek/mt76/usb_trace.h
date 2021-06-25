<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर !defined(__MT76_USB_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __MT76_USB_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "mt76.h"

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mt76_usb

#घोषणा MAXNAME		32
#घोषणा DEV_ENTRY	__array(अक्षर, wiphy_name, 32)
#घोषणा DEV_ASSIGN	strlcpy(__entry->wiphy_name,	\
				wiphy_name(dev->hw->wiphy), MAXNAME)
#घोषणा DEV_PR_FMT	"%s "
#घोषणा DEV_PR_ARG	__entry->wiphy_name

#घोषणा REG_ENTRY	__field(u32, reg) __field(u32, val)
#घोषणा REG_ASSIGN	__entry->reg = reg; __entry->val = val
#घोषणा REG_PR_FMT	"reg:0x%04x=0x%08x"
#घोषणा REG_PR_ARG	__entry->reg, __entry->val

DECLARE_EVENT_CLASS(dev_reg_evt,
	TP_PROTO(काष्ठा mt76_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		REG_ENTRY
	),
	TP_fast_assign(
		DEV_ASSIGN;
		REG_ASSIGN;
	),
	TP_prपूर्णांकk(
		DEV_PR_FMT REG_PR_FMT,
		DEV_PR_ARG, REG_PR_ARG
	)
);

DEFINE_EVENT(dev_reg_evt, usb_reg_rr,
	TP_PROTO(काष्ठा mt76_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val)
);

DEFINE_EVENT(dev_reg_evt, usb_reg_wr,
	TP_PROTO(काष्ठा mt76_dev *dev, u32 reg, u32 val),
	TP_ARGS(dev, reg, val)
);

DECLARE_EVENT_CLASS(urb_transfer,
	TP_PROTO(काष्ठा mt76_dev *dev, काष्ठा urb *u),
	TP_ARGS(dev, u),
	TP_STRUCT__entry(
		DEV_ENTRY __field(अचिन्हित पूर्णांक, pipe) __field(u32, len)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->pipe = u->pipe;
		__entry->len = u->transfer_buffer_length;
	),
	TP_prपूर्णांकk(DEV_PR_FMT "p:%08x len:%u",
		  DEV_PR_ARG, __entry->pipe, __entry->len)
);

DEFINE_EVENT(urb_transfer, submit_urb,
	TP_PROTO(काष्ठा mt76_dev *dev, काष्ठा urb *u),
	TP_ARGS(dev, u)
);

DEFINE_EVENT(urb_transfer, rx_urb,
	TP_PROTO(काष्ठा mt76_dev *dev, काष्ठा urb *u),
	TP_ARGS(dev, u)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता usb_trace

#समावेश <trace/define_trace.h>
