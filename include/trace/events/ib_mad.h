<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */

/*
 * Copyright (c) 2018 Intel Corporation.  All rights reserved.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM ib_mad

#अगर !defined(_TRACE_IB_MAD_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_IB_MAD_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <rdma/ib_mad.h>

#अगर_घोषित CONFIG_TRACEPOINTS
काष्ठा trace_event_raw_ib_mad_send_ढाँचा;
अटल व्योम create_mad_addr_info(काष्ठा ib_mad_send_wr_निजी *mad_send_wr,
			  काष्ठा ib_mad_qp_info *qp_info,
			  काष्ठा trace_event_raw_ib_mad_send_ढाँचा *entry);
#पूर्ण_अगर

DECLARE_EVENT_CLASS(ib_mad_send_ढाँचा,
	TP_PROTO(काष्ठा ib_mad_send_wr_निजी *wr,
		 काष्ठा ib_mad_qp_info *qp_info),
	TP_ARGS(wr, qp_info),

	TP_STRUCT__entry(
		__field(u8,             base_version)
		__field(u8,             mgmt_class)
		__field(u8,             class_version)
		__field(u8,             port_num)
		__field(u32,            qp_num)
		__field(u8,             method)
		__field(u8,             sl)
		__field(u16,            attr_id)
		__field(u32,            attr_mod)
		__field(u64,            wrtid)
		__field(u64,            tid)
		__field(u16,            status)
		__field(u16,            class_specअगरic)
		__field(u32,            length)
		__field(u32,            dlid)
		__field(u32,            rqpn)
		__field(u32,            rqkey)
		__field(u32,            dev_index)
		__field(व्योम *,         agent_priv)
		__field(अचिन्हित दीर्घ,  समयout)
		__field(पूर्णांक,            retries_left)
		__field(पूर्णांक,            max_retries)
		__field(पूर्णांक,            retry)
		__field(u16,            pkey)
	),

	TP_fast_assign(
		__entry->dev_index = wr->mad_agent_priv->agent.device->index;
		__entry->port_num = wr->mad_agent_priv->agent.port_num;
		__entry->qp_num = wr->mad_agent_priv->qp_info->qp->qp_num;
		__entry->agent_priv = wr->mad_agent_priv;
		__entry->wrtid = wr->tid;
		__entry->max_retries = wr->max_retries;
		__entry->retries_left = wr->retries_left;
		__entry->retry = wr->retry;
		__entry->समयout = wr->समयout;
		__entry->length = wr->send_buf.hdr_len +
				  wr->send_buf.data_len;
		__entry->base_version =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->base_version;
		__entry->mgmt_class =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->mgmt_class;
		__entry->class_version =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->class_version;
		__entry->method =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->method;
		__entry->status =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->status;
		__entry->class_specअगरic =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->class_specअगरic;
		__entry->tid = ((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->tid;
		__entry->attr_id =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->attr_id;
		__entry->attr_mod =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->attr_mod;
		create_mad_addr_info(wr, qp_info, __entry);
	),

	TP_prपूर्णांकk("%d:%d QP%d agent %p: " \
		  "wrtid 0x%llx; %d/%d retries(%d); timeout %lu length %d : " \
		  "hdr : base_ver 0x%x class 0x%x class_ver 0x%x " \
		  "method 0x%x status 0x%x class_specific 0x%x tid 0x%llx " \
		  "attr_id 0x%x attr_mod 0x%x  => dlid 0x%08x sl %d "\
		  "pkey 0x%x rpqn 0x%x rqpkey 0x%x",
		__entry->dev_index, __entry->port_num, __entry->qp_num,
		__entry->agent_priv, be64_to_cpu(__entry->wrtid),
		__entry->retries_left, __entry->max_retries,
		__entry->retry, __entry->समयout, __entry->length,
		__entry->base_version, __entry->mgmt_class,
		__entry->class_version,
		__entry->method, be16_to_cpu(__entry->status),
		be16_to_cpu(__entry->class_specअगरic),
		be64_to_cpu(__entry->tid), be16_to_cpu(__entry->attr_id),
		be32_to_cpu(__entry->attr_mod),
		be32_to_cpu(__entry->dlid), __entry->sl, __entry->pkey,
		__entry->rqpn, __entry->rqkey
	)
);

DEFINE_EVENT(ib_mad_send_ढाँचा, ib_mad_error_handler,
	TP_PROTO(काष्ठा ib_mad_send_wr_निजी *wr,
		 काष्ठा ib_mad_qp_info *qp_info),
	TP_ARGS(wr, qp_info));
DEFINE_EVENT(ib_mad_send_ढाँचा, ib_mad_ib_send_mad,
	TP_PROTO(काष्ठा ib_mad_send_wr_निजी *wr,
		 काष्ठा ib_mad_qp_info *qp_info),
	TP_ARGS(wr, qp_info));
DEFINE_EVENT(ib_mad_send_ढाँचा, ib_mad_send_करोne_resend,
	TP_PROTO(काष्ठा ib_mad_send_wr_निजी *wr,
		 काष्ठा ib_mad_qp_info *qp_info),
	TP_ARGS(wr, qp_info));

TRACE_EVENT(ib_mad_send_करोne_handler,
	TP_PROTO(काष्ठा ib_mad_send_wr_निजी *wr, काष्ठा ib_wc *wc),
	TP_ARGS(wr, wc),

	TP_STRUCT__entry(
		__field(u8,             port_num)
		__field(u8,             base_version)
		__field(u8,             mgmt_class)
		__field(u8,             class_version)
		__field(u32,            qp_num)
		__field(u64,            wrtid)
		__field(u16,            status)
		__field(u16,            wc_status)
		__field(u32,            length)
		__field(व्योम *,         agent_priv)
		__field(अचिन्हित दीर्घ,  समयout)
		__field(u32,            dev_index)
		__field(पूर्णांक,            retries_left)
		__field(पूर्णांक,            max_retries)
		__field(पूर्णांक,            retry)
		__field(u8,             method)
	),

	TP_fast_assign(
		__entry->dev_index = wr->mad_agent_priv->agent.device->index;
		__entry->port_num = wr->mad_agent_priv->agent.port_num;
		__entry->qp_num = wr->mad_agent_priv->qp_info->qp->qp_num;
		__entry->agent_priv = wr->mad_agent_priv;
		__entry->wrtid = wr->tid;
		__entry->max_retries = wr->max_retries;
		__entry->retries_left = wr->retries_left;
		__entry->retry = wr->retry;
		__entry->समयout = wr->समयout;
		__entry->base_version =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->base_version;
		__entry->mgmt_class =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->mgmt_class;
		__entry->class_version =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->class_version;
		__entry->method =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->method;
		__entry->status =
			((काष्ठा ib_mad_hdr *)wr->send_buf.mad)->status;
		__entry->wc_status = wc->status;
		__entry->length = wc->byte_len;
	),

	TP_prपूर्णांकk("%d:%d QP%d : SEND WC Status %d : agent %p: " \
		  "wrtid 0x%llx %d/%d retries(%d) timeout %lu length %d: " \
		  "hdr : base_ver 0x%x class 0x%x class_ver 0x%x " \
		  "method 0x%x status 0x%x",
		__entry->dev_index, __entry->port_num, __entry->qp_num,
		__entry->wc_status,
		__entry->agent_priv, be64_to_cpu(__entry->wrtid),
		__entry->retries_left, __entry->max_retries,
		__entry->retry, __entry->समयout,
		__entry->length,
		__entry->base_version, __entry->mgmt_class,
		__entry->class_version, __entry->method,
		be16_to_cpu(__entry->status)
	)
);

TRACE_EVENT(ib_mad_recv_करोne_handler,
	TP_PROTO(काष्ठा ib_mad_qp_info *qp_info, काष्ठा ib_wc *wc,
		 काष्ठा ib_mad_hdr *mad_hdr),
	TP_ARGS(qp_info, wc, mad_hdr),

	TP_STRUCT__entry(
		__field(u8,             base_version)
		__field(u8,             mgmt_class)
		__field(u8,             class_version)
		__field(u8,             port_num)
		__field(u32,            qp_num)
		__field(u16,            status)
		__field(u16,            class_specअगरic)
		__field(u32,            length)
		__field(u64,            tid)
		__field(u8,             method)
		__field(u8,             sl)
		__field(u16,            attr_id)
		__field(u32,            attr_mod)
		__field(u16,            src_qp)
		__field(u16,            wc_status)
		__field(u32,            slid)
		__field(u32,            dev_index)
		__field(u16,            pkey)
	),

	TP_fast_assign(
		__entry->dev_index = qp_info->port_priv->device->index;
		__entry->port_num = qp_info->port_priv->port_num;
		__entry->qp_num = qp_info->qp->qp_num;
		__entry->length = wc->byte_len;
		__entry->base_version = mad_hdr->base_version;
		__entry->mgmt_class = mad_hdr->mgmt_class;
		__entry->class_version = mad_hdr->class_version;
		__entry->method = mad_hdr->method;
		__entry->status = mad_hdr->status;
		__entry->class_specअगरic = mad_hdr->class_specअगरic;
		__entry->tid = mad_hdr->tid;
		__entry->attr_id = mad_hdr->attr_id;
		__entry->attr_mod = mad_hdr->attr_mod;
		__entry->slid = wc->slid;
		__entry->src_qp = wc->src_qp;
		__entry->sl = wc->sl;
		ib_query_pkey(qp_info->port_priv->device,
			      qp_info->port_priv->port_num,
			      wc->pkey_index, &__entry->pkey);
		__entry->wc_status = wc->status;
	),

	TP_prपूर्णांकk("%d:%d QP%d : RECV WC Status %d : length %d : hdr : " \
		  "base_ver 0x%02x class 0x%02x class_ver 0x%02x " \
		  "method 0x%02x status 0x%04x class_specific 0x%04x " \
		  "tid 0x%016llx attr_id 0x%04x attr_mod 0x%08x " \
		  "slid 0x%08x src QP%d, sl %d pkey 0x%04x",
		__entry->dev_index, __entry->port_num, __entry->qp_num,
		__entry->wc_status,
		__entry->length,
		__entry->base_version, __entry->mgmt_class,
		__entry->class_version, __entry->method,
		be16_to_cpu(__entry->status),
		be16_to_cpu(__entry->class_specअगरic),
		be64_to_cpu(__entry->tid), be16_to_cpu(__entry->attr_id),
		be32_to_cpu(__entry->attr_mod),
		__entry->slid, __entry->src_qp, __entry->sl, __entry->pkey
	)
);

DECLARE_EVENT_CLASS(ib_mad_agent_ढाँचा,
	TP_PROTO(काष्ठा ib_mad_agent_निजी *agent),
	TP_ARGS(agent),

	TP_STRUCT__entry(
		__field(u32,            dev_index)
		__field(u32,            hi_tid)
		__field(u8,             port_num)
		__field(u8,             mgmt_class)
		__field(u8,             mgmt_class_version)
	),

	TP_fast_assign(
		__entry->dev_index = agent->agent.device->index;
		__entry->port_num = agent->agent.port_num;
		__entry->hi_tid = agent->agent.hi_tid;

		अगर (agent->reg_req) अणु
			__entry->mgmt_class = agent->reg_req->mgmt_class;
			__entry->mgmt_class_version =
				agent->reg_req->mgmt_class_version;
		पूर्ण अन्यथा अणु
			__entry->mgmt_class = 0;
			__entry->mgmt_class_version = 0;
		पूर्ण
	),

	TP_prपूर्णांकk("%d:%d mad agent : hi_tid 0x%08x class 0x%02x class_ver 0x%02x",
		__entry->dev_index, __entry->port_num,
		__entry->hi_tid, __entry->mgmt_class,
		__entry->mgmt_class_version
	)
);
DEFINE_EVENT(ib_mad_agent_ढाँचा, ib_mad_recv_करोne_agent,
	TP_PROTO(काष्ठा ib_mad_agent_निजी *agent),
	TP_ARGS(agent));
DEFINE_EVENT(ib_mad_agent_ढाँचा, ib_mad_send_करोne_agent,
	TP_PROTO(काष्ठा ib_mad_agent_निजी *agent),
	TP_ARGS(agent));
DEFINE_EVENT(ib_mad_agent_ढाँचा, ib_mad_create_agent,
	TP_PROTO(काष्ठा ib_mad_agent_निजी *agent),
	TP_ARGS(agent));
DEFINE_EVENT(ib_mad_agent_ढाँचा, ib_mad_unरेजिस्टर_agent,
	TP_PROTO(काष्ठा ib_mad_agent_निजी *agent),
	TP_ARGS(agent));



DECLARE_EVENT_CLASS(ib_mad_opa_smi_ढाँचा,
	TP_PROTO(काष्ठा opa_smp *smp),
	TP_ARGS(smp),

	TP_STRUCT__entry(
		__field(u64,            mkey)
		__field(u32,            dr_slid)
		__field(u32,            dr_dlid)
		__field(u8,             hop_ptr)
		__field(u8,             hop_cnt)
		__array(u8,             initial_path, OPA_SMP_MAX_PATH_HOPS)
		__array(u8,             वापस_path, OPA_SMP_MAX_PATH_HOPS)
	),

	TP_fast_assign(
		__entry->hop_ptr = smp->hop_ptr;
		__entry->hop_cnt = smp->hop_cnt;
		__entry->mkey = smp->mkey;
		__entry->dr_slid = smp->route.dr.dr_slid;
		__entry->dr_dlid = smp->route.dr.dr_dlid;
		स_नकल(__entry->initial_path, smp->route.dr.initial_path,
			OPA_SMP_MAX_PATH_HOPS);
		स_नकल(__entry->वापस_path, smp->route.dr.वापस_path,
			OPA_SMP_MAX_PATH_HOPS);
	),

	TP_prपूर्णांकk("OPA SMP: hop_ptr %d hop_cnt %d " \
		  "mkey 0x%016llx dr_slid 0x%08x dr_dlid 0x%08x " \
		  "initial_path %*ph return_path %*ph ",
		__entry->hop_ptr, __entry->hop_cnt,
		be64_to_cpu(__entry->mkey), be32_to_cpu(__entry->dr_slid),
		be32_to_cpu(__entry->dr_dlid),
		OPA_SMP_MAX_PATH_HOPS, __entry->initial_path,
		OPA_SMP_MAX_PATH_HOPS, __entry->वापस_path
	)
);

DEFINE_EVENT(ib_mad_opa_smi_ढाँचा, ib_mad_handle_opa_smi,
	TP_PROTO(काष्ठा opa_smp *smp),
	TP_ARGS(smp));
DEFINE_EVENT(ib_mad_opa_smi_ढाँचा, ib_mad_handle_out_opa_smi,
	TP_PROTO(काष्ठा opa_smp *smp),
	TP_ARGS(smp));


DECLARE_EVENT_CLASS(ib_mad_opa_ib_ढाँचा,
	TP_PROTO(काष्ठा ib_smp *smp),
	TP_ARGS(smp),

	TP_STRUCT__entry(
		__field(u64,            mkey)
		__field(u32,            dr_slid)
		__field(u32,            dr_dlid)
		__field(u8,             hop_ptr)
		__field(u8,             hop_cnt)
		__array(u8,             initial_path, IB_SMP_MAX_PATH_HOPS)
		__array(u8,             वापस_path, IB_SMP_MAX_PATH_HOPS)
	),

	TP_fast_assign(
		__entry->hop_ptr = smp->hop_ptr;
		__entry->hop_cnt = smp->hop_cnt;
		__entry->mkey = smp->mkey;
		__entry->dr_slid = smp->dr_slid;
		__entry->dr_dlid = smp->dr_dlid;
		स_नकल(__entry->initial_path, smp->initial_path,
			IB_SMP_MAX_PATH_HOPS);
		स_नकल(__entry->वापस_path, smp->वापस_path,
			IB_SMP_MAX_PATH_HOPS);
	),

	TP_prपूर्णांकk("OPA SMP: hop_ptr %d hop_cnt %d " \
		  "mkey 0x%016llx dr_slid 0x%04x dr_dlid 0x%04x " \
		  "initial_path %*ph return_path %*ph ",
		__entry->hop_ptr, __entry->hop_cnt,
		be64_to_cpu(__entry->mkey), be16_to_cpu(__entry->dr_slid),
		be16_to_cpu(__entry->dr_dlid),
		IB_SMP_MAX_PATH_HOPS, __entry->initial_path,
		IB_SMP_MAX_PATH_HOPS, __entry->वापस_path
	)
);

DEFINE_EVENT(ib_mad_opa_ib_ढाँचा, ib_mad_handle_ib_smi,
	TP_PROTO(काष्ठा ib_smp *smp),
	TP_ARGS(smp));
DEFINE_EVENT(ib_mad_opa_ib_ढाँचा, ib_mad_handle_out_ib_smi,
	TP_PROTO(काष्ठा ib_smp *smp),
	TP_ARGS(smp));

#पूर्ण_अगर /* _TRACE_IB_MAD_H */

#समावेश <trace/define_trace.h>
