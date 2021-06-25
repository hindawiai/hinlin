<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Marvell OcteonTx2 RVU Admin Function driver tracepoपूर्णांकs
 *
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rvu

#अगर !defined(__RVU_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __RVU_TRACE_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/pci.h>

TRACE_EVENT(otx2_msg_alloc,
	    TP_PROTO(स्थिर काष्ठा pci_dev *pdev, u16 id, u64 size),
	    TP_ARGS(pdev, id, size),
	    TP_STRUCT__entry(__string(dev, pci_name(pdev))
			     __field(u16, id)
			     __field(u64, size)
	    ),
	    TP_fast_assign(__assign_str(dev, pci_name(pdev))
			   __entry->id = id;
			   __entry->size = size;
	    ),
	    TP_prपूर्णांकk("[%s] msg:(0x%x) size:%lld\n", __get_str(dev),
		      __entry->id, __entry->size)
);

TRACE_EVENT(otx2_msg_send,
	    TP_PROTO(स्थिर काष्ठा pci_dev *pdev, u16 num_msgs, u64 msg_size),
	    TP_ARGS(pdev, num_msgs, msg_size),
	    TP_STRUCT__entry(__string(dev, pci_name(pdev))
			     __field(u16, num_msgs)
			     __field(u64, msg_size)
	    ),
	    TP_fast_assign(__assign_str(dev, pci_name(pdev))
			   __entry->num_msgs = num_msgs;
			   __entry->msg_size = msg_size;
	    ),
	    TP_prपूर्णांकk("[%s] sent %d msg(s) of size:%lld\n", __get_str(dev),
		      __entry->num_msgs, __entry->msg_size)
);

TRACE_EVENT(otx2_msg_check,
	    TP_PROTO(स्थिर काष्ठा pci_dev *pdev, u16 reqid, u16 rspid, पूर्णांक rc),
	    TP_ARGS(pdev, reqid, rspid, rc),
	    TP_STRUCT__entry(__string(dev, pci_name(pdev))
			     __field(u16, reqid)
			     __field(u16, rspid)
			     __field(पूर्णांक, rc)
	    ),
	    TP_fast_assign(__assign_str(dev, pci_name(pdev))
			   __entry->reqid = reqid;
			   __entry->rspid = rspid;
			   __entry->rc = rc;
	    ),
	    TP_prपूर्णांकk("[%s] req->id:0x%x rsp->id:0x%x resp_code:%d\n",
		      __get_str(dev), __entry->reqid,
		      __entry->rspid, __entry->rc)
);

TRACE_EVENT(otx2_msg_पूर्णांकerrupt,
	    TP_PROTO(स्थिर काष्ठा pci_dev *pdev, स्थिर अक्षर *msg, u64 पूर्णांकr),
	    TP_ARGS(pdev, msg, पूर्णांकr),
	    TP_STRUCT__entry(__string(dev, pci_name(pdev))
			     __string(str, msg)
			     __field(u64, पूर्णांकr)
	    ),
	    TP_fast_assign(__assign_str(dev, pci_name(pdev))
			   __assign_str(str, msg)
			   __entry->पूर्णांकr = पूर्णांकr;
	    ),
	    TP_prपूर्णांकk("[%s] mbox interrupt %s (0x%llx)\n", __get_str(dev),
		      __get_str(str), __entry->पूर्णांकr)
);

TRACE_EVENT(otx2_msg_process,
	    TP_PROTO(स्थिर काष्ठा pci_dev *pdev, u16 id, पूर्णांक err),
	    TP_ARGS(pdev, id, err),
	    TP_STRUCT__entry(__string(dev, pci_name(pdev))
			     __field(u16, id)
			     __field(पूर्णांक, err)
	    ),
	    TP_fast_assign(__assign_str(dev, pci_name(pdev))
			   __entry->id = id;
			   __entry->err = err;
	    ),
	    TP_prपूर्णांकk("[%s] msg:(0x%x) error:%d\n", __get_str(dev),
		      __entry->id, __entry->err)
);

#पूर्ण_अगर /* __RVU_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता rvu_trace

#समावेश <trace/define_trace.h>
