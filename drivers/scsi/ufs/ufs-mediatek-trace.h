<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020 MediaTek Inc.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ufs_mtk

#अगर !defined(_TRACE_EVENT_UFS_MEDIATEK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_EVENT_UFS_MEDIATEK_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(ufs_mtk_event,
	TP_PROTO(अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक data),
	TP_ARGS(type, data),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, type)
		__field(अचिन्हित पूर्णांक, data)
	),

	TP_fast_assign(
		__entry->type = type;
		__entry->data = data;
	),

	TP_prपूर्णांकk("ufs:event=%u data=%u",
		  __entry->type, __entry->data)
	);
#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH ../../drivers/scsi/ufs/
#घोषणा TRACE_INCLUDE_खाता ufs-mediatek-trace
#समावेश <trace/define_trace.h>
