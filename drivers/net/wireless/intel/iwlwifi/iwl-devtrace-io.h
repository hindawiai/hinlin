<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2016-2017 Intel Deutschland GmbH
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर !defined(__IWLWIFI_DEVICE_TRACE_IO) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __IWLWIFI_DEVICE_TRACE_IO

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/pci.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iwlwअगरi_io

TRACE_EVENT(iwlwअगरi_dev_ioपढ़ो32,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 offs, u32 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] read io[%#x] = %#x",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioग_लिखो8,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 offs, u8 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, offs)
		__field(u8, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write io[%#x] = %#x)",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioग_लिखो32,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 offs, u32 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write io[%#x] = %#x)",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioग_लिखो64,
	TP_PROTO(स्थिर काष्ठा device *dev, u64 offs, u64 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u64, offs)
		__field(u64, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write io[%llu] = %llu)",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioग_लिखो_prph32,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 offs, u32 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write PRPH[%#x] = %#x)",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioग_लिखो_prph64,
	TP_PROTO(स्थिर काष्ठा device *dev, u64 offs, u64 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u64, offs)
		__field(u64, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] write PRPH[%llu] = %llu)",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_ioपढ़ो_prph32,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 offs, u32 val),
	TP_ARGS(dev, offs, val),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, offs)
		__field(u32, val)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->offs = offs;
		__entry->val = val;
	),
	TP_prपूर्णांकk("[%s] read PRPH[%#x] = %#x",
		  __get_str(dev), __entry->offs, __entry->val)
);

TRACE_EVENT(iwlwअगरi_dev_irq,
	TP_PROTO(स्थिर काष्ठा device *dev),
	TP_ARGS(dev),
	TP_STRUCT__entry(
		DEV_ENTRY
	),
	TP_fast_assign(
		DEV_ASSIGN;
	),
	/* TP_prपूर्णांकk("") करोesn't compile */
	TP_prपूर्णांकk("%d", 0)
);

TRACE_EVENT(iwlwअगरi_dev_irq_msix,
	TP_PROTO(स्थिर काष्ठा device *dev, काष्ठा msix_entry *msix_entry,
		 bool defirq, u32 पूर्णांकa_fh, u32 पूर्णांकa_hw),
	TP_ARGS(dev, msix_entry, defirq, पूर्णांकa_fh, पूर्णांकa_hw),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, entry)
		__field(u8, defirq)
		__field(u32, पूर्णांकa_fh)
		__field(u32, पूर्णांकa_hw)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->entry = msix_entry->entry;
		__entry->defirq = defirq;
		__entry->पूर्णांकa_fh = पूर्णांकa_fh;
		__entry->पूर्णांकa_hw = पूर्णांकa_hw;
	),
	TP_prपूर्णांकk("entry:%d defirq:%d fh:0x%x, hw:0x%x",
		  __entry->entry, __entry->defirq,
		  __entry->पूर्णांकa_fh, __entry->पूर्णांकa_hw)
);

TRACE_EVENT(iwlwअगरi_dev_ict_पढ़ो,
	TP_PROTO(स्थिर काष्ठा device *dev, u32 index, u32 value),
	TP_ARGS(dev, index, value),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u32, index)
		__field(u32, value)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->index = index;
		__entry->value = value;
	),
	TP_prपूर्णांकk("[%s] read ict[%d] = %#.8x",
		  __get_str(dev), __entry->index, __entry->value)
);
#पूर्ण_अगर /* __IWLWIFI_DEVICE_TRACE_IO */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता iwl-devtrace-io
#समावेश <trace/define_trace.h>
