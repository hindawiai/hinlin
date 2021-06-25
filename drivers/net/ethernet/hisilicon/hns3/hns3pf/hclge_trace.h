<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2018-2020 Hisilicon Limited. */

/* This must be outside अगरdef _HCLGE_TRACE_H */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hns3

#अगर !defined(_HCLGE_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _HCLGE_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा PF_GET_MBX_LEN	(माप(काष्ठा hclge_mbx_vf_to_pf_cmd) / माप(u32))
#घोषणा PF_SEND_MBX_LEN	(माप(काष्ठा hclge_mbx_pf_to_vf_cmd) / माप(u32))

TRACE_EVENT(hclge_pf_mbx_get,
	TP_PROTO(
		काष्ठा hclge_dev *hdev,
		काष्ठा hclge_mbx_vf_to_pf_cmd *req),
	TP_ARGS(hdev, req),

	TP_STRUCT__entry(
		__field(u8, vfid)
		__field(u8, code)
		__field(u8, subcode)
		__string(pciname, pci_name(hdev->pdev))
		__string(devname, &hdev->vport[0].nic.kinfo.netdev->name)
		__array(u32, mbx_data, PF_GET_MBX_LEN)
	),

	TP_fast_assign(
		__entry->vfid = req->mbx_src_vfid;
		__entry->code = req->msg.code;
		__entry->subcode = req->msg.subcode;
		__assign_str(pciname, pci_name(hdev->pdev));
		__assign_str(devname, &hdev->vport[0].nic.kinfo.netdev->name);
		स_नकल(__entry->mbx_data, req,
		       माप(काष्ठा hclge_mbx_vf_to_pf_cmd));
	),

	TP_prपूर्णांकk(
		"%s %s vfid:%u code:%u subcode:%u data:%s",
		__get_str(pciname), __get_str(devname), __entry->vfid,
		__entry->code, __entry->subcode,
		__prपूर्णांक_array(__entry->mbx_data, PF_GET_MBX_LEN, माप(u32))
	)
);

TRACE_EVENT(hclge_pf_mbx_send,
	TP_PROTO(
		काष्ठा hclge_dev *hdev,
		काष्ठा hclge_mbx_pf_to_vf_cmd *req),
	TP_ARGS(hdev, req),

	TP_STRUCT__entry(
		__field(u8, vfid)
		__field(u16, code)
		__string(pciname, pci_name(hdev->pdev))
		__string(devname, &hdev->vport[0].nic.kinfo.netdev->name)
		__array(u32, mbx_data, PF_SEND_MBX_LEN)
	),

	TP_fast_assign(
		__entry->vfid = req->dest_vfid;
		__entry->code = req->msg.code;
		__assign_str(pciname, pci_name(hdev->pdev));
		__assign_str(devname, &hdev->vport[0].nic.kinfo.netdev->name);
		स_नकल(__entry->mbx_data, req,
		       माप(काष्ठा hclge_mbx_pf_to_vf_cmd));
	),

	TP_prपूर्णांकk(
		"%s %s vfid:%u code:%u data:%s",
		__get_str(pciname), __get_str(devname), __entry->vfid,
		__entry->code,
		__prपूर्णांक_array(__entry->mbx_data, PF_SEND_MBX_LEN, माप(u32))
	)
);

#पूर्ण_अगर /* _HCLGE_TRACE_H_ */

/* This must be outside अगरdef _HCLGE_TRACE_H */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता hclge_trace
#समावेश <trace/define_trace.h>
