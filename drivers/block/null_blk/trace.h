<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * null_blk device driver tracepoपूर्णांकs.
 *
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nullb

#अगर !defined(_TRACE_शून्यB_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_शून्यB_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/trace_seq.h>

#समावेश "null_blk.h"

स्थिर अक्षर *nullb_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name);

#घोषणा __prपूर्णांक_disk_name(name) nullb_trace_disk_name(p, name)

#अगर_अघोषित TRACE_HEADER_MULTI_READ
अटल अंतरभूत व्योम __assign_disk_name(अक्षर *name, काष्ठा gendisk *disk)
अणु
	अगर (disk)
		स_नकल(name, disk->disk_name, DISK_NAME_LEN);
	अन्यथा
		स_रखो(name, 0, DISK_NAME_LEN);
पूर्ण
#पूर्ण_अगर

TRACE_EVENT(nullb_zone_op,
	    TP_PROTO(काष्ठा nullb_cmd *cmd, अचिन्हित पूर्णांक zone_no,
		     अचिन्हित पूर्णांक zone_cond),
	    TP_ARGS(cmd, zone_no, zone_cond),
	    TP_STRUCT__entry(
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(क्रमागत req_opf, op)
		__field(अचिन्हित पूर्णांक, zone_no)
		__field(अचिन्हित पूर्णांक, zone_cond)
	    ),
	    TP_fast_assign(
		__entry->op = req_op(cmd->rq);
		__entry->zone_no = zone_no;
		__entry->zone_cond = zone_cond;
		__assign_disk_name(__entry->disk, cmd->rq->rq_disk);
	    ),
	    TP_prपूर्णांकk("%s req=%-15s zone_no=%u zone_cond=%-10s",
		      __prपूर्णांक_disk_name(__entry->disk),
		      blk_op_str(__entry->op),
		      __entry->zone_no,
		      blk_zone_cond_str(__entry->zone_cond))
);

TRACE_EVENT(nullb_report_zones,
	    TP_PROTO(काष्ठा nullb *nullb, अचिन्हित पूर्णांक nr_zones),
	    TP_ARGS(nullb, nr_zones),
	    TP_STRUCT__entry(
		__array(अक्षर, disk, DISK_NAME_LEN)
		__field(अचिन्हित पूर्णांक, nr_zones)
	    ),
	    TP_fast_assign(
		__entry->nr_zones = nr_zones;
		__assign_disk_name(__entry->disk, nullb->disk);
	    ),
	    TP_prपूर्णांकk("%s nr_zones=%u",
		      __prपूर्णांक_disk_name(__entry->disk), __entry->nr_zones)
);

#पूर्ण_अगर /* _TRACE_शून्यB_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
