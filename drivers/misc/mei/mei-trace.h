<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015-2016, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#अगर !defined(_MEI_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _MEI_TRACE_H_

#समावेश <linux/stringअगरy.h>
#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <linux/device.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mei

TRACE_EVENT(mei_reg_पढ़ो,
	TP_PROTO(स्थिर काष्ठा device *dev, स्थिर अक्षर *reg, u32 offs, u32 val),
	TP_ARGS(dev, reg, offs, val),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(स्थिर अक्षर *, reg)
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev))
		__entry->reg  = reg;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] read %s:[%#x] = %#x",
		  __get_str(dev), __entry->reg, __entry->offs, __entry->val)
);

TRACE_EVENT(mei_reg_ग_लिखो,
	TP_PROTO(स्थिर काष्ठा device *dev, स्थिर अक्षर *reg, u32 offs, u32 val),
	TP_ARGS(dev, reg, offs, val),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(स्थिर अक्षर *, reg)
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev))
		__entry->reg = reg;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write %s[%#x] = %#x",
		  __get_str(dev), __entry->reg,  __entry->offs, __entry->val)
);

TRACE_EVENT(mei_pci_cfg_पढ़ो,
	TP_PROTO(स्थिर काष्ठा device *dev, स्थिर अक्षर *reg, u32 offs, u32 val),
	TP_ARGS(dev, reg, offs, val),
	TP_STRUCT__entry(
		__string(dev, dev_name(dev))
		__field(स्थिर अक्षर *, reg)
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		__assign_str(dev, dev_name(dev))
		__entry->reg  = reg;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] pci cfg read %s:[%#x] = %#x",
		  __get_str(dev), __entry->reg, __entry->offs, __entry->val)
);

#पूर्ण_अगर /* _MEI_TRACE_H_ */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता mei-trace
#समावेश <trace/define_trace.h>
