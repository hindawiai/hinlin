<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Voltaire, Inc.  All rights reserved.
 * Copyright (c) 2006 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kref.h>
#समावेश <linux/xarray.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <rdma/ib_pack.h>
#समावेश <rdma/ib_cache.h>
#समावेश <rdma/rdma_netlink.h>
#समावेश <net/netlink.h>
#समावेश <uapi/rdma/ib_user_sa.h>
#समावेश <rdma/ib_marshall.h>
#समावेश <rdma/ib_addr.h>
#समावेश <rdma/opa_addr.h>
#समावेश "sa.h"
#समावेश "core_priv.h"

#घोषणा IB_SA_LOCAL_SVC_TIMEOUT_MIN		100
#घोषणा IB_SA_LOCAL_SVC_TIMEOUT_DEFAULT		2000
#घोषणा IB_SA_LOCAL_SVC_TIMEOUT_MAX		200000
#घोषणा IB_SA_CPI_MAX_RETRY_CNT			3
#घोषणा IB_SA_CPI_RETRY_WAIT			1000 /*msecs */
अटल पूर्णांक sa_local_svc_समयout_ms = IB_SA_LOCAL_SVC_TIMEOUT_DEFAULT;

काष्ठा ib_sa_sm_ah अणु
	काष्ठा ib_ah        *ah;
	काष्ठा kref          ref;
	u16		     pkey_index;
	u8		     src_path_mask;
पूर्ण;

क्रमागत rdma_class_port_info_type अणु
	RDMA_CLASS_PORT_INFO_IB,
	RDMA_CLASS_PORT_INFO_OPA
पूर्ण;

काष्ठा rdma_class_port_info अणु
	क्रमागत rdma_class_port_info_type type;
	जोड़ अणु
		काष्ठा ib_class_port_info ib;
		काष्ठा opa_class_port_info opa;
	पूर्ण;
पूर्ण;

काष्ठा ib_sa_classport_cache अणु
	bool valid;
	पूर्णांक retry_cnt;
	काष्ठा rdma_class_port_info data;
पूर्ण;

काष्ठा ib_sa_port अणु
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_sm_ah  *sm_ah;
	काष्ठा work_काष्ठा   update_task;
	काष्ठा ib_sa_classport_cache classport_info;
	काष्ठा delayed_work ib_cpi_work;
	spinlock_t                   classport_lock; /* protects class port info set */
	spinlock_t           ah_lock;
	u32		     port_num;
पूर्ण;

काष्ठा ib_sa_device अणु
	पूर्णांक                     start_port, end_port;
	काष्ठा ib_event_handler event_handler;
	काष्ठा ib_sa_port port[];
पूर्ण;

काष्ठा ib_sa_query अणु
	व्योम (*callback)(काष्ठा ib_sa_query *, पूर्णांक, काष्ठा ib_sa_mad *);
	व्योम (*release)(काष्ठा ib_sa_query *);
	काष्ठा ib_sa_client    *client;
	काष्ठा ib_sa_port      *port;
	काष्ठा ib_mad_send_buf *mad_buf;
	काष्ठा ib_sa_sm_ah     *sm_ah;
	पूर्णांक			id;
	u32			flags;
	काष्ठा list_head	list; /* Local svc request list */
	u32			seq; /* Local svc request sequence number */
	अचिन्हित दीर्घ		समयout; /* Local svc समयout */
	u8			path_use; /* How will the pathrecord be used */
पूर्ण;

#घोषणा IB_SA_ENABLE_LOCAL_SERVICE	0x00000001
#घोषणा IB_SA_CANCEL			0x00000002
#घोषणा IB_SA_QUERY_OPA			0x00000004

काष्ठा ib_sa_service_query अणु
	व्योम (*callback)(पूर्णांक, काष्ठा ib_sa_service_rec *, व्योम *);
	व्योम *context;
	काष्ठा ib_sa_query sa_query;
पूर्ण;

काष्ठा ib_sa_path_query अणु
	व्योम (*callback)(पूर्णांक, काष्ठा sa_path_rec *, व्योम *);
	व्योम *context;
	काष्ठा ib_sa_query sa_query;
	काष्ठा sa_path_rec *conv_pr;
पूर्ण;

काष्ठा ib_sa_guidinfo_query अणु
	व्योम (*callback)(पूर्णांक, काष्ठा ib_sa_guidinfo_rec *, व्योम *);
	व्योम *context;
	काष्ठा ib_sa_query sa_query;
पूर्ण;

काष्ठा ib_sa_classport_info_query अणु
	व्योम (*callback)(व्योम *);
	व्योम *context;
	काष्ठा ib_sa_query sa_query;
पूर्ण;

काष्ठा ib_sa_mcmember_query अणु
	व्योम (*callback)(पूर्णांक, काष्ठा ib_sa_mcmember_rec *, व्योम *);
	व्योम *context;
	काष्ठा ib_sa_query sa_query;
पूर्ण;

अटल LIST_HEAD(ib_nl_request_list);
अटल DEFINE_SPINLOCK(ib_nl_request_lock);
अटल atomic_t ib_nl_sa_request_seq;
अटल काष्ठा workqueue_काष्ठा *ib_nl_wq;
अटल काष्ठा delayed_work ib_nl_समयd_work;
अटल स्थिर काष्ठा nla_policy ib_nl_policy[LS_NLA_TYPE_MAX] = अणु
	[LS_NLA_TYPE_PATH_RECORD]	= अणु.type = NLA_BINARY,
		.len = माप(काष्ठा ib_path_rec_data)पूर्ण,
	[LS_NLA_TYPE_TIMEOUT]		= अणु.type = NLA_U32पूर्ण,
	[LS_NLA_TYPE_SERVICE_ID]	= अणु.type = NLA_U64पूर्ण,
	[LS_NLA_TYPE_DGID]		= अणु.type = NLA_BINARY,
		.len = माप(काष्ठा rdma_nla_ls_gid)पूर्ण,
	[LS_NLA_TYPE_SGID]		= अणु.type = NLA_BINARY,
		.len = माप(काष्ठा rdma_nla_ls_gid)पूर्ण,
	[LS_NLA_TYPE_TCLASS]		= अणु.type = NLA_U8पूर्ण,
	[LS_NLA_TYPE_PKEY]		= अणु.type = NLA_U16पूर्ण,
	[LS_NLA_TYPE_QOS_CLASS]		= अणु.type = NLA_U16पूर्ण,
पूर्ण;


अटल पूर्णांक ib_sa_add_one(काष्ठा ib_device *device);
अटल व्योम ib_sa_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data);

अटल काष्ठा ib_client sa_client = अणु
	.name   = "sa",
	.add    = ib_sa_add_one,
	.हटाओ = ib_sa_हटाओ_one
पूर्ण;

अटल DEFINE_XARRAY_FLAGS(queries, XA_FLAGS_ALLOC | XA_FLAGS_LOCK_IRQ);

अटल DEFINE_SPINLOCK(tid_lock);
अटल u32 tid;

#घोषणा PATH_REC_FIELD(field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा sa_path_rec, field),	\
	.काष्ठा_size_bytes   = माप_field(काष्ठा sa_path_rec, field),	\
	.field_name          = "sa_path_rec:" #field

अटल स्थिर काष्ठा ib_field path_rec_table[] = अणु
	अणु PATH_REC_FIELD(service_id),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 64 पूर्ण,
	अणु PATH_REC_FIELD(dgid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु PATH_REC_FIELD(sgid),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु PATH_REC_FIELD(ib.dlid),
	  .offset_words = 10,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु PATH_REC_FIELD(ib.slid),
	  .offset_words = 10,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु PATH_REC_FIELD(ib.raw_traffic),
	  .offset_words = 11,
	  .offset_bits  = 0,
	  .size_bits    = 1 पूर्ण,
	अणु RESERVED,
	  .offset_words = 11,
	  .offset_bits  = 1,
	  .size_bits    = 3 पूर्ण,
	अणु PATH_REC_FIELD(flow_label),
	  .offset_words = 11,
	  .offset_bits  = 4,
	  .size_bits    = 20 पूर्ण,
	अणु PATH_REC_FIELD(hop_limit),
	  .offset_words = 11,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु PATH_REC_FIELD(traffic_class),
	  .offset_words = 12,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु PATH_REC_FIELD(reversible),
	  .offset_words = 12,
	  .offset_bits  = 8,
	  .size_bits    = 1 पूर्ण,
	अणु PATH_REC_FIELD(numb_path),
	  .offset_words = 12,
	  .offset_bits  = 9,
	  .size_bits    = 7 पूर्ण,
	अणु PATH_REC_FIELD(pkey),
	  .offset_words = 12,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु PATH_REC_FIELD(qos_class),
	  .offset_words = 13,
	  .offset_bits  = 0,
	  .size_bits    = 12 पूर्ण,
	अणु PATH_REC_FIELD(sl),
	  .offset_words = 13,
	  .offset_bits  = 12,
	  .size_bits    = 4 पूर्ण,
	अणु PATH_REC_FIELD(mtu_selector),
	  .offset_words = 13,
	  .offset_bits  = 16,
	  .size_bits    = 2 पूर्ण,
	अणु PATH_REC_FIELD(mtu),
	  .offset_words = 13,
	  .offset_bits  = 18,
	  .size_bits    = 6 पूर्ण,
	अणु PATH_REC_FIELD(rate_selector),
	  .offset_words = 13,
	  .offset_bits  = 24,
	  .size_bits    = 2 पूर्ण,
	अणु PATH_REC_FIELD(rate),
	  .offset_words = 13,
	  .offset_bits  = 26,
	  .size_bits    = 6 पूर्ण,
	अणु PATH_REC_FIELD(packet_lअगरe_समय_selector),
	  .offset_words = 14,
	  .offset_bits  = 0,
	  .size_bits    = 2 पूर्ण,
	अणु PATH_REC_FIELD(packet_lअगरe_समय),
	  .offset_words = 14,
	  .offset_bits  = 2,
	  .size_bits    = 6 पूर्ण,
	अणु PATH_REC_FIELD(preference),
	  .offset_words = 14,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु RESERVED,
	  .offset_words = 14,
	  .offset_bits  = 16,
	  .size_bits    = 48 पूर्ण,
पूर्ण;

#घोषणा OPA_PATH_REC_FIELD(field) \
	.काष्ठा_offset_bytes = \
		दुरत्व(काष्ठा sa_path_rec, field), \
	.काष्ठा_size_bytes   = \
		माप_field(काष्ठा sa_path_rec, field),	\
	.field_name          = "sa_path_rec:" #field

अटल स्थिर काष्ठा ib_field opa_path_rec_table[] = अणु
	अणु OPA_PATH_REC_FIELD(service_id),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 64 पूर्ण,
	अणु OPA_PATH_REC_FIELD(dgid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु OPA_PATH_REC_FIELD(sgid),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.dlid),
	  .offset_words = 10,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.slid),
	  .offset_words = 11,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.raw_traffic),
	  .offset_words = 12,
	  .offset_bits  = 0,
	  .size_bits    = 1 पूर्ण,
	अणु RESERVED,
	  .offset_words = 12,
	  .offset_bits  = 1,
	  .size_bits    = 3 पूर्ण,
	अणु OPA_PATH_REC_FIELD(flow_label),
	  .offset_words = 12,
	  .offset_bits  = 4,
	  .size_bits    = 20 पूर्ण,
	अणु OPA_PATH_REC_FIELD(hop_limit),
	  .offset_words = 12,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु OPA_PATH_REC_FIELD(traffic_class),
	  .offset_words = 13,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु OPA_PATH_REC_FIELD(reversible),
	  .offset_words = 13,
	  .offset_bits  = 8,
	  .size_bits    = 1 पूर्ण,
	अणु OPA_PATH_REC_FIELD(numb_path),
	  .offset_words = 13,
	  .offset_bits  = 9,
	  .size_bits    = 7 पूर्ण,
	अणु OPA_PATH_REC_FIELD(pkey),
	  .offset_words = 13,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.l2_8B),
	  .offset_words = 14,
	  .offset_bits  = 0,
	  .size_bits    = 1 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.l2_10B),
	  .offset_words = 14,
	  .offset_bits  = 1,
	  .size_bits    = 1 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.l2_9B),
	  .offset_words = 14,
	  .offset_bits  = 2,
	  .size_bits    = 1 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.l2_16B),
	  .offset_words = 14,
	  .offset_bits  = 3,
	  .size_bits    = 1 पूर्ण,
	अणु RESERVED,
	  .offset_words = 14,
	  .offset_bits  = 4,
	  .size_bits    = 2 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.qos_type),
	  .offset_words = 14,
	  .offset_bits  = 6,
	  .size_bits    = 2 पूर्ण,
	अणु OPA_PATH_REC_FIELD(opa.qos_priority),
	  .offset_words = 14,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु RESERVED,
	  .offset_words = 14,
	  .offset_bits  = 16,
	  .size_bits    = 3 पूर्ण,
	अणु OPA_PATH_REC_FIELD(sl),
	  .offset_words = 14,
	  .offset_bits  = 19,
	  .size_bits    = 5 पूर्ण,
	अणु RESERVED,
	  .offset_words = 14,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु OPA_PATH_REC_FIELD(mtu_selector),
	  .offset_words = 15,
	  .offset_bits  = 0,
	  .size_bits    = 2 पूर्ण,
	अणु OPA_PATH_REC_FIELD(mtu),
	  .offset_words = 15,
	  .offset_bits  = 2,
	  .size_bits    = 6 पूर्ण,
	अणु OPA_PATH_REC_FIELD(rate_selector),
	  .offset_words = 15,
	  .offset_bits  = 8,
	  .size_bits    = 2 पूर्ण,
	अणु OPA_PATH_REC_FIELD(rate),
	  .offset_words = 15,
	  .offset_bits  = 10,
	  .size_bits    = 6 पूर्ण,
	अणु OPA_PATH_REC_FIELD(packet_lअगरe_समय_selector),
	  .offset_words = 15,
	  .offset_bits  = 16,
	  .size_bits    = 2 पूर्ण,
	अणु OPA_PATH_REC_FIELD(packet_lअगरe_समय),
	  .offset_words = 15,
	  .offset_bits  = 18,
	  .size_bits    = 6 पूर्ण,
	अणु OPA_PATH_REC_FIELD(preference),
	  .offset_words = 15,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
पूर्ण;

#घोषणा MCMEMBER_REC_FIELD(field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_sa_mcmember_rec, field),	\
	.काष्ठा_size_bytes   = माप_field(काष्ठा ib_sa_mcmember_rec, field),	\
	.field_name          = "sa_mcmember_rec:" #field

अटल स्थिर काष्ठा ib_field mcmember_rec_table[] = अणु
	अणु MCMEMBER_REC_FIELD(mgid),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु MCMEMBER_REC_FIELD(port_gid),
	  .offset_words = 4,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु MCMEMBER_REC_FIELD(qkey),
	  .offset_words = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु MCMEMBER_REC_FIELD(mlid),
	  .offset_words = 9,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु MCMEMBER_REC_FIELD(mtu_selector),
	  .offset_words = 9,
	  .offset_bits  = 16,
	  .size_bits    = 2 पूर्ण,
	अणु MCMEMBER_REC_FIELD(mtu),
	  .offset_words = 9,
	  .offset_bits  = 18,
	  .size_bits    = 6 पूर्ण,
	अणु MCMEMBER_REC_FIELD(traffic_class),
	  .offset_words = 9,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु MCMEMBER_REC_FIELD(pkey),
	  .offset_words = 10,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु MCMEMBER_REC_FIELD(rate_selector),
	  .offset_words = 10,
	  .offset_bits  = 16,
	  .size_bits    = 2 पूर्ण,
	अणु MCMEMBER_REC_FIELD(rate),
	  .offset_words = 10,
	  .offset_bits  = 18,
	  .size_bits    = 6 पूर्ण,
	अणु MCMEMBER_REC_FIELD(packet_lअगरe_समय_selector),
	  .offset_words = 10,
	  .offset_bits  = 24,
	  .size_bits    = 2 पूर्ण,
	अणु MCMEMBER_REC_FIELD(packet_lअगरe_समय),
	  .offset_words = 10,
	  .offset_bits  = 26,
	  .size_bits    = 6 पूर्ण,
	अणु MCMEMBER_REC_FIELD(sl),
	  .offset_words = 11,
	  .offset_bits  = 0,
	  .size_bits    = 4 पूर्ण,
	अणु MCMEMBER_REC_FIELD(flow_label),
	  .offset_words = 11,
	  .offset_bits  = 4,
	  .size_bits    = 20 पूर्ण,
	अणु MCMEMBER_REC_FIELD(hop_limit),
	  .offset_words = 11,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु MCMEMBER_REC_FIELD(scope),
	  .offset_words = 12,
	  .offset_bits  = 0,
	  .size_bits    = 4 पूर्ण,
	अणु MCMEMBER_REC_FIELD(join_state),
	  .offset_words = 12,
	  .offset_bits  = 4,
	  .size_bits    = 4 पूर्ण,
	अणु MCMEMBER_REC_FIELD(proxy_join),
	  .offset_words = 12,
	  .offset_bits  = 8,
	  .size_bits    = 1 पूर्ण,
	अणु RESERVED,
	  .offset_words = 12,
	  .offset_bits  = 9,
	  .size_bits    = 23 पूर्ण,
पूर्ण;

#घोषणा SERVICE_REC_FIELD(field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_sa_service_rec, field),	\
	.काष्ठा_size_bytes   = माप_field(काष्ठा ib_sa_service_rec, field),	\
	.field_name          = "sa_service_rec:" #field

अटल स्थिर काष्ठा ib_field service_rec_table[] = अणु
	अणु SERVICE_REC_FIELD(id),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 64 पूर्ण,
	अणु SERVICE_REC_FIELD(gid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु SERVICE_REC_FIELD(pkey),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु SERVICE_REC_FIELD(lease),
	  .offset_words = 7,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु SERVICE_REC_FIELD(key),
	  .offset_words = 8,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु SERVICE_REC_FIELD(name),
	  .offset_words = 12,
	  .offset_bits  = 0,
	  .size_bits    = 64*8 पूर्ण,
	अणु SERVICE_REC_FIELD(data8),
	  .offset_words = 28,
	  .offset_bits  = 0,
	  .size_bits    = 16*8 पूर्ण,
	अणु SERVICE_REC_FIELD(data16),
	  .offset_words = 32,
	  .offset_bits  = 0,
	  .size_bits    = 8*16 पूर्ण,
	अणु SERVICE_REC_FIELD(data32),
	  .offset_words = 36,
	  .offset_bits  = 0,
	  .size_bits    = 4*32 पूर्ण,
	अणु SERVICE_REC_FIELD(data64),
	  .offset_words = 40,
	  .offset_bits  = 0,
	  .size_bits    = 2*64 पूर्ण,
पूर्ण;

#घोषणा CLASSPORTINFO_REC_FIELD(field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_class_port_info, field),	\
	.काष्ठा_size_bytes   = माप_field(काष्ठा ib_class_port_info, field),	\
	.field_name          = "ib_class_port_info:" #field

अटल स्थिर काष्ठा ib_field ib_classport_info_rec_table[] = अणु
	अणु CLASSPORTINFO_REC_FIELD(base_version),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(class_version),
	  .offset_words = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(capability_mask),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(cap_mask2_resp_समय),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(redirect_gid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(redirect_tcslfl),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(redirect_lid),
	  .offset_words = 7,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(redirect_pkey),
	  .offset_words = 7,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,

	अणु CLASSPORTINFO_REC_FIELD(redirect_qp),
	  .offset_words = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(redirect_qkey),
	  .offset_words = 9,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,

	अणु CLASSPORTINFO_REC_FIELD(trap_gid),
	  .offset_words = 10,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(trap_tcslfl),
	  .offset_words = 14,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,

	अणु CLASSPORTINFO_REC_FIELD(trap_lid),
	  .offset_words = 15,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(trap_pkey),
	  .offset_words = 15,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,

	अणु CLASSPORTINFO_REC_FIELD(trap_hlqp),
	  .offset_words = 16,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु CLASSPORTINFO_REC_FIELD(trap_qkey),
	  .offset_words = 17,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
पूर्ण;

#घोषणा OPA_CLASSPORTINFO_REC_FIELD(field) \
	.काष्ठा_offset_bytes =\
		दुरत्व(काष्ठा opa_class_port_info, field),	\
	.काष्ठा_size_bytes   = \
		माप_field(काष्ठा opa_class_port_info, field),	\
	.field_name          = "opa_class_port_info:" #field

अटल स्थिर काष्ठा ib_field opa_classport_info_rec_table[] = अणु
	अणु OPA_CLASSPORTINFO_REC_FIELD(base_version),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(class_version),
	  .offset_words = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(cap_mask),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(cap_mask2_resp_समय),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_gid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_tc_fl),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_lid),
	  .offset_words = 7,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_sl_qp),
	  .offset_words = 8,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_qkey),
	  .offset_words = 9,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_gid),
	  .offset_words = 10,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_tc_fl),
	  .offset_words = 14,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_lid),
	  .offset_words = 15,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_hl_qp),
	  .offset_words = 16,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_qkey),
	  .offset_words = 17,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_pkey),
	  .offset_words = 18,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(redirect_pkey),
	  .offset_words = 18,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु OPA_CLASSPORTINFO_REC_FIELD(trap_sl_rsvd),
	  .offset_words = 19,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु RESERVED,
	  .offset_words = 19,
	  .offset_bits  = 8,
	  .size_bits    = 24 पूर्ण,
पूर्ण;

#घोषणा GUIDINFO_REC_FIELD(field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_sa_guidinfo_rec, field),	\
	.काष्ठा_size_bytes   = माप_field(काष्ठा ib_sa_guidinfo_rec, field),	\
	.field_name          = "sa_guidinfo_rec:" #field

अटल स्थिर काष्ठा ib_field guidinfo_rec_table[] = अणु
	अणु GUIDINFO_REC_FIELD(lid),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु GUIDINFO_REC_FIELD(block_num),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 8 पूर्ण,
	अणु GUIDINFO_REC_FIELD(res1),
	  .offset_words = 0,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु GUIDINFO_REC_FIELD(res2),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु GUIDINFO_REC_FIELD(guid_info_list),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 512 पूर्ण,
पूर्ण;

अटल अंतरभूत व्योम ib_sa_disable_local_svc(काष्ठा ib_sa_query *query)
अणु
	query->flags &= ~IB_SA_ENABLE_LOCAL_SERVICE;
पूर्ण

अटल अंतरभूत पूर्णांक ib_sa_query_cancelled(काष्ठा ib_sa_query *query)
अणु
	वापस (query->flags & IB_SA_CANCEL);
पूर्ण

अटल व्योम ib_nl_set_path_rec_attrs(काष्ठा sk_buff *skb,
				     काष्ठा ib_sa_query *query)
अणु
	काष्ठा sa_path_rec *sa_rec = query->mad_buf->context[1];
	काष्ठा ib_sa_mad *mad = query->mad_buf->mad;
	ib_sa_comp_mask comp_mask = mad->sa_hdr.comp_mask;
	u16 val16;
	u64 val64;
	काष्ठा rdma_ls_resolve_header *header;

	query->mad_buf->context[1] = शून्य;

	/* Conकाष्ठा the family header first */
	header = skb_put(skb, NLMSG_ALIGN(माप(*header)));
	स_नकल(header->device_name, dev_name(&query->port->agent->device->dev),
	       LS_DEVICE_NAME_MAX);
	header->port_num = query->port->port_num;

	अगर ((comp_mask & IB_SA_PATH_REC_REVERSIBLE) &&
	    sa_rec->reversible != 0)
		query->path_use = LS_RESOLVE_PATH_USE_GMP;
	अन्यथा
		query->path_use = LS_RESOLVE_PATH_USE_UNIसूचीECTIONAL;
	header->path_use = query->path_use;

	/* Now build the attributes */
	अगर (comp_mask & IB_SA_PATH_REC_SERVICE_ID) अणु
		val64 = be64_to_cpu(sa_rec->service_id);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_SERVICE_ID,
			माप(val64), &val64);
	पूर्ण
	अगर (comp_mask & IB_SA_PATH_REC_DGID)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_DGID,
			माप(sa_rec->dgid), &sa_rec->dgid);
	अगर (comp_mask & IB_SA_PATH_REC_SGID)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_SGID,
			माप(sa_rec->sgid), &sa_rec->sgid);
	अगर (comp_mask & IB_SA_PATH_REC_TRAFFIC_CLASS)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_TCLASS,
			माप(sa_rec->traffic_class), &sa_rec->traffic_class);

	अगर (comp_mask & IB_SA_PATH_REC_PKEY) अणु
		val16 = be16_to_cpu(sa_rec->pkey);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_PKEY,
			माप(val16), &val16);
	पूर्ण
	अगर (comp_mask & IB_SA_PATH_REC_QOS_CLASS) अणु
		val16 = be16_to_cpu(sa_rec->qos_class);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_QOS_CLASS,
			माप(val16), &val16);
	पूर्ण
पूर्ण

अटल पूर्णांक ib_nl_get_path_rec_attrs_len(ib_sa_comp_mask comp_mask)
अणु
	पूर्णांक len = 0;

	अगर (comp_mask & IB_SA_PATH_REC_SERVICE_ID)
		len += nla_total_size(माप(u64));
	अगर (comp_mask & IB_SA_PATH_REC_DGID)
		len += nla_total_size(माप(काष्ठा rdma_nla_ls_gid));
	अगर (comp_mask & IB_SA_PATH_REC_SGID)
		len += nla_total_size(माप(काष्ठा rdma_nla_ls_gid));
	अगर (comp_mask & IB_SA_PATH_REC_TRAFFIC_CLASS)
		len += nla_total_size(माप(u8));
	अगर (comp_mask & IB_SA_PATH_REC_PKEY)
		len += nla_total_size(माप(u16));
	अगर (comp_mask & IB_SA_PATH_REC_QOS_CLASS)
		len += nla_total_size(माप(u16));

	/*
	 * Make sure that at least some of the required comp_mask bits are
	 * set.
	 */
	अगर (WARN_ON(len == 0))
		वापस len;

	/* Add the family header */
	len += NLMSG_ALIGN(माप(काष्ठा rdma_ls_resolve_header));

	वापस len;
पूर्ण

अटल पूर्णांक ib_nl_make_request(काष्ठा ib_sa_query *query, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा nlmsghdr *nlh;
	व्योम *data;
	काष्ठा ib_sa_mad *mad;
	पूर्णांक len;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ delay;
	gfp_t gfp_flag;
	पूर्णांक ret;

	INIT_LIST_HEAD(&query->list);
	query->seq = (u32)atomic_inc_वापस(&ib_nl_sa_request_seq);

	mad = query->mad_buf->mad;
	len = ib_nl_get_path_rec_attrs_len(mad->sa_hdr.comp_mask);
	अगर (len <= 0)
		वापस -EMSGSIZE;

	skb = nlmsg_new(len, gfp_mask);
	अगर (!skb)
		वापस -ENOMEM;

	/* Put nlmsg header only क्रम now */
	data = ibnl_put_msg(skb, &nlh, query->seq, 0, RDMA_NL_LS,
			    RDMA_NL_LS_OP_RESOLVE, NLM_F_REQUEST);
	अगर (!data) अणु
		nlmsg_मुक्त(skb);
		वापस -EMSGSIZE;
	पूर्ण

	/* Add attributes */
	ib_nl_set_path_rec_attrs(skb, query);

	/* Repair the nlmsg header length */
	nlmsg_end(skb, nlh);

	gfp_flag = ((gfp_mask & GFP_ATOMIC) == GFP_ATOMIC) ? GFP_ATOMIC :
		GFP_NOWAIT;

	spin_lock_irqsave(&ib_nl_request_lock, flags);
	ret = rdma_nl_multicast(&init_net, skb, RDMA_NL_GROUP_LS, gfp_flag);

	अगर (ret)
		जाओ out;

	/* Put the request on the list.*/
	delay = msecs_to_jअगरfies(sa_local_svc_समयout_ms);
	query->समयout = delay + jअगरfies;
	list_add_tail(&query->list, &ib_nl_request_list);
	/* Start the समयout अगर this is the only request */
	अगर (ib_nl_request_list.next == &query->list)
		queue_delayed_work(ib_nl_wq, &ib_nl_समयd_work, delay);

out:
	spin_unlock_irqrestore(&ib_nl_request_lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक ib_nl_cancel_request(काष्ठा ib_sa_query *query)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_sa_query *रुको_query;
	पूर्णांक found = 0;

	spin_lock_irqsave(&ib_nl_request_lock, flags);
	list_क्रम_each_entry(रुको_query, &ib_nl_request_list, list) अणु
		/* Let the समयout to take care of the callback */
		अगर (query == रुको_query) अणु
			query->flags |= IB_SA_CANCEL;
			query->समयout = jअगरfies;
			list_move(&query->list, &ib_nl_request_list);
			found = 1;
			mod_delayed_work(ib_nl_wq, &ib_nl_समयd_work, 1);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ib_nl_request_lock, flags);

	वापस found;
पूर्ण

अटल व्योम send_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_wc *mad_send_wc);

अटल व्योम ib_nl_process_good_resolve_rsp(काष्ठा ib_sa_query *query,
					   स्थिर काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा ib_mad_send_wc mad_send_wc;
	काष्ठा ib_sa_mad *mad = शून्य;
	स्थिर काष्ठा nlattr *head, *curr;
	काष्ठा ib_path_rec_data  *rec;
	पूर्णांक len, rem;
	u32 mask = 0;
	पूर्णांक status = -EIO;

	अगर (query->callback) अणु
		head = (स्थिर काष्ठा nlattr *) nlmsg_data(nlh);
		len = nlmsg_len(nlh);
		चयन (query->path_use) अणु
		हाल LS_RESOLVE_PATH_USE_UNIसूचीECTIONAL:
			mask = IB_PATH_PRIMARY | IB_PATH_OUTBOUND;
			अवरोध;

		हाल LS_RESOLVE_PATH_USE_ALL:
		हाल LS_RESOLVE_PATH_USE_GMP:
		शेष:
			mask = IB_PATH_PRIMARY | IB_PATH_GMP |
				IB_PATH_BIसूचीECTIONAL;
			अवरोध;
		पूर्ण
		nla_क्रम_each_attr(curr, head, len, rem) अणु
			अगर (curr->nla_type == LS_NLA_TYPE_PATH_RECORD) अणु
				rec = nla_data(curr);
				/*
				 * Get the first one. In the future, we may
				 * need to get up to 6 pathrecords.
				 */
				अगर ((rec->flags & mask) == mask) अणु
					mad = query->mad_buf->mad;
					mad->mad_hdr.method |=
						IB_MGMT_METHOD_RESP;
					स_नकल(mad->data, rec->path_rec,
					       माप(rec->path_rec));
					status = 0;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		query->callback(query, status, mad);
	पूर्ण

	mad_send_wc.send_buf = query->mad_buf;
	mad_send_wc.status = IB_WC_SUCCESS;
	send_handler(query->mad_buf->mad_agent, &mad_send_wc);
पूर्ण

अटल व्योम ib_nl_request_समयout(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_sa_query *query;
	अचिन्हित दीर्घ delay;
	काष्ठा ib_mad_send_wc mad_send_wc;
	पूर्णांक ret;

	spin_lock_irqsave(&ib_nl_request_lock, flags);
	जबतक (!list_empty(&ib_nl_request_list)) अणु
		query = list_entry(ib_nl_request_list.next,
				   काष्ठा ib_sa_query, list);

		अगर (समय_after(query->समयout, jअगरfies)) अणु
			delay = query->समयout - jअगरfies;
			अगर ((दीर्घ)delay <= 0)
				delay = 1;
			queue_delayed_work(ib_nl_wq, &ib_nl_समयd_work, delay);
			अवरोध;
		पूर्ण

		list_del(&query->list);
		ib_sa_disable_local_svc(query);
		/* Hold the lock to protect against query cancellation */
		अगर (ib_sa_query_cancelled(query))
			ret = -1;
		अन्यथा
			ret = ib_post_send_mad(query->mad_buf, शून्य);
		अगर (ret) अणु
			mad_send_wc.send_buf = query->mad_buf;
			mad_send_wc.status = IB_WC_WR_FLUSH_ERR;
			spin_unlock_irqrestore(&ib_nl_request_lock, flags);
			send_handler(query->port->agent, &mad_send_wc);
			spin_lock_irqsave(&ib_nl_request_lock, flags);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ib_nl_request_lock, flags);
पूर्ण

पूर्णांक ib_nl_handle_set_समयout(काष्ठा sk_buff *skb,
			     काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक समयout, delta, असल_delta;
	स्थिर काष्ठा nlattr *attr;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_sa_query *query;
	दीर्घ delay = 0;
	काष्ठा nlattr *tb[LS_NLA_TYPE_MAX];
	पूर्णांक ret;

	अगर (!(nlh->nlmsg_flags & NLM_F_REQUEST) ||
	    !(NETLINK_CB(skb).sk))
		वापस -EPERM;

	ret = nla_parse_deprecated(tb, LS_NLA_TYPE_MAX - 1, nlmsg_data(nlh),
				   nlmsg_len(nlh), ib_nl_policy, शून्य);
	attr = (स्थिर काष्ठा nlattr *)tb[LS_NLA_TYPE_TIMEOUT];
	अगर (ret || !attr)
		जाओ समय_रखोout_out;

	समयout = *(पूर्णांक *) nla_data(attr);
	अगर (समयout < IB_SA_LOCAL_SVC_TIMEOUT_MIN)
		समयout = IB_SA_LOCAL_SVC_TIMEOUT_MIN;
	अगर (समयout > IB_SA_LOCAL_SVC_TIMEOUT_MAX)
		समयout = IB_SA_LOCAL_SVC_TIMEOUT_MAX;

	delta = समयout - sa_local_svc_समयout_ms;
	अगर (delta < 0)
		असल_delta = -delta;
	अन्यथा
		असल_delta = delta;

	अगर (delta != 0) अणु
		spin_lock_irqsave(&ib_nl_request_lock, flags);
		sa_local_svc_समयout_ms = समयout;
		list_क्रम_each_entry(query, &ib_nl_request_list, list) अणु
			अगर (delta < 0 && असल_delta > query->समयout)
				query->समयout = 0;
			अन्यथा
				query->समयout += delta;

			/* Get the new delay from the first entry */
			अगर (!delay) अणु
				delay = query->समयout - jअगरfies;
				अगर (delay <= 0)
					delay = 1;
			पूर्ण
		पूर्ण
		अगर (delay)
			mod_delayed_work(ib_nl_wq, &ib_nl_समयd_work,
					 (अचिन्हित दीर्घ)delay);
		spin_unlock_irqrestore(&ib_nl_request_lock, flags);
	पूर्ण

समय_रखोout_out:
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ib_nl_is_good_resolve_resp(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा nlattr *tb[LS_NLA_TYPE_MAX];
	पूर्णांक ret;

	अगर (nlh->nlmsg_flags & RDMA_NL_LS_F_ERR)
		वापस 0;

	ret = nla_parse_deprecated(tb, LS_NLA_TYPE_MAX - 1, nlmsg_data(nlh),
				   nlmsg_len(nlh), ib_nl_policy, शून्य);
	अगर (ret)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक ib_nl_handle_resolve_resp(काष्ठा sk_buff *skb,
			      काष्ठा nlmsghdr *nlh,
			      काष्ठा netlink_ext_ack *extack)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_sa_query *query;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_send_wc mad_send_wc;
	पूर्णांक found = 0;
	पूर्णांक ret;

	अगर ((nlh->nlmsg_flags & NLM_F_REQUEST) ||
	    !(NETLINK_CB(skb).sk))
		वापस -EPERM;

	spin_lock_irqsave(&ib_nl_request_lock, flags);
	list_क्रम_each_entry(query, &ib_nl_request_list, list) अणु
		/*
		 * If the query is cancelled, let the समयout routine
		 * take care of it.
		 */
		अगर (nlh->nlmsg_seq == query->seq) अणु
			found = !ib_sa_query_cancelled(query);
			अगर (found)
				list_del(&query->list);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		spin_unlock_irqrestore(&ib_nl_request_lock, flags);
		जाओ resp_out;
	पूर्ण

	send_buf = query->mad_buf;

	अगर (!ib_nl_is_good_resolve_resp(nlh)) अणु
		/* अगर the result is a failure, send out the packet via IB */
		ib_sa_disable_local_svc(query);
		ret = ib_post_send_mad(query->mad_buf, शून्य);
		spin_unlock_irqrestore(&ib_nl_request_lock, flags);
		अगर (ret) अणु
			mad_send_wc.send_buf = send_buf;
			mad_send_wc.status = IB_WC_GENERAL_ERR;
			send_handler(query->port->agent, &mad_send_wc);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ib_nl_request_lock, flags);
		ib_nl_process_good_resolve_rsp(query, nlh);
	पूर्ण

resp_out:
	वापस 0;
पूर्ण

अटल व्योम मुक्त_sm_ah(काष्ठा kref *kref)
अणु
	काष्ठा ib_sa_sm_ah *sm_ah = container_of(kref, काष्ठा ib_sa_sm_ah, ref);

	rdma_destroy_ah(sm_ah->ah, 0);
	kमुक्त(sm_ah);
पूर्ण

व्योम ib_sa_रेजिस्टर_client(काष्ठा ib_sa_client *client)
अणु
	atomic_set(&client->users, 1);
	init_completion(&client->comp);
पूर्ण
EXPORT_SYMBOL(ib_sa_रेजिस्टर_client);

व्योम ib_sa_unरेजिस्टर_client(काष्ठा ib_sa_client *client)
अणु
	ib_sa_client_put(client);
	रुको_क्रम_completion(&client->comp);
पूर्ण
EXPORT_SYMBOL(ib_sa_unरेजिस्टर_client);

/**
 * ib_sa_cancel_query - try to cancel an SA query
 * @id:ID of query to cancel
 * @query:query poपूर्णांकer to cancel
 *
 * Try to cancel an SA query.  If the id and query करोn't match up or
 * the query has alपढ़ोy completed, nothing is करोne.  Otherwise the
 * query is canceled and will complete with a status of -EINTR.
 */
व्योम ib_sa_cancel_query(पूर्णांक id, काष्ठा ib_sa_query *query)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_mad_send_buf *mad_buf;

	xa_lock_irqsave(&queries, flags);
	अगर (xa_load(&queries, id) != query) अणु
		xa_unlock_irqrestore(&queries, flags);
		वापस;
	पूर्ण
	agent = query->port->agent;
	mad_buf = query->mad_buf;
	xa_unlock_irqrestore(&queries, flags);

	/*
	 * If the query is still on the netlink request list, schedule
	 * it to be cancelled by the समयout routine. Otherwise, it has been
	 * sent to the MAD layer and has to be cancelled from there.
	 */
	अगर (!ib_nl_cancel_request(query))
		ib_cancel_mad(agent, mad_buf);
पूर्ण
EXPORT_SYMBOL(ib_sa_cancel_query);

अटल u8 get_src_path_mask(काष्ठा ib_device *device, u32 port_num)
अणु
	काष्ठा ib_sa_device *sa_dev;
	काष्ठा ib_sa_port   *port;
	अचिन्हित दीर्घ flags;
	u8 src_path_mask;

	sa_dev = ib_get_client_data(device, &sa_client);
	अगर (!sa_dev)
		वापस 0x7f;

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	spin_lock_irqsave(&port->ah_lock, flags);
	src_path_mask = port->sm_ah ? port->sm_ah->src_path_mask : 0x7f;
	spin_unlock_irqrestore(&port->ah_lock, flags);

	वापस src_path_mask;
पूर्ण

अटल पूर्णांक init_ah_attr_grh_fields(काष्ठा ib_device *device, u32 port_num,
				   काष्ठा sa_path_rec *rec,
				   काष्ठा rdma_ah_attr *ah_attr,
				   स्थिर काष्ठा ib_gid_attr *gid_attr)
अणु
	क्रमागत ib_gid_type type = sa_conv_pathrec_to_gid_type(rec);

	अगर (!gid_attr) अणु
		gid_attr = rdma_find_gid_by_port(device, &rec->sgid, type,
						 port_num, शून्य);
		अगर (IS_ERR(gid_attr))
			वापस PTR_ERR(gid_attr);
	पूर्ण अन्यथा
		rdma_hold_gid_attr(gid_attr);

	rdma_move_grh_sgid_attr(ah_attr, &rec->dgid,
				be32_to_cpu(rec->flow_label),
				rec->hop_limit,	rec->traffic_class,
				gid_attr);
	वापस 0;
पूर्ण

/**
 * ib_init_ah_attr_from_path - Initialize address handle attributes based on
 *   an SA path record.
 * @device: Device associated ah attributes initialization.
 * @port_num: Port on the specअगरied device.
 * @rec: path record entry to use क्रम ah attributes initialization.
 * @ah_attr: address handle attributes to initialization from path record.
 * @gid_attr: SGID attribute to consider during initialization.
 *
 * When ib_init_ah_attr_from_path() वापसs success,
 * (a) क्रम IB link layer it optionally contains a reference to SGID attribute
 * when GRH is present क्रम IB link layer.
 * (b) क्रम RoCE link layer it contains a reference to SGID attribute.
 * User must invoke rdma_destroy_ah_attr() to release reference to SGID
 * attributes which are initialized using ib_init_ah_attr_from_path().
 */
पूर्णांक ib_init_ah_attr_from_path(काष्ठा ib_device *device, u32 port_num,
			      काष्ठा sa_path_rec *rec,
			      काष्ठा rdma_ah_attr *ah_attr,
			      स्थिर काष्ठा ib_gid_attr *gid_attr)
अणु
	पूर्णांक ret = 0;

	स_रखो(ah_attr, 0, माप(*ah_attr));
	ah_attr->type = rdma_ah_find_type(device, port_num);
	rdma_ah_set_sl(ah_attr, rec->sl);
	rdma_ah_set_port_num(ah_attr, port_num);
	rdma_ah_set_अटल_rate(ah_attr, rec->rate);

	अगर (sa_path_is_roce(rec)) अणु
		ret = roce_resolve_route_from_path(rec, gid_attr);
		अगर (ret)
			वापस ret;

		स_नकल(ah_attr->roce.dmac, sa_path_get_dmac(rec), ETH_ALEN);
	पूर्ण अन्यथा अणु
		rdma_ah_set_dlid(ah_attr, be32_to_cpu(sa_path_get_dlid(rec)));
		अगर (sa_path_is_opa(rec) &&
		    rdma_ah_get_dlid(ah_attr) == be16_to_cpu(IB_LID_PERMISSIVE))
			rdma_ah_set_make_grd(ah_attr, true);

		rdma_ah_set_path_bits(ah_attr,
				      be32_to_cpu(sa_path_get_slid(rec)) &
				      get_src_path_mask(device, port_num));
	पूर्ण

	अगर (rec->hop_limit > 0 || sa_path_is_roce(rec))
		ret = init_ah_attr_grh_fields(device, port_num,
					      rec, ah_attr, gid_attr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_init_ah_attr_from_path);

अटल पूर्णांक alloc_mad(काष्ठा ib_sa_query *query, gfp_t gfp_mask)
अणु
	काष्ठा rdma_ah_attr ah_attr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&query->port->ah_lock, flags);
	अगर (!query->port->sm_ah) अणु
		spin_unlock_irqrestore(&query->port->ah_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	kref_get(&query->port->sm_ah->ref);
	query->sm_ah = query->port->sm_ah;
	spin_unlock_irqrestore(&query->port->ah_lock, flags);

	/*
	 * Always check अगर sm_ah has valid dlid asचिन्हित,
	 * beक्रमe querying क्रम class port info
	 */
	अगर ((rdma_query_ah(query->sm_ah->ah, &ah_attr) < 0) ||
	    !rdma_is_valid_unicast_lid(&ah_attr)) अणु
		kref_put(&query->sm_ah->ref, मुक्त_sm_ah);
		वापस -EAGAIN;
	पूर्ण
	query->mad_buf = ib_create_send_mad(query->port->agent, 1,
					    query->sm_ah->pkey_index,
					    0, IB_MGMT_SA_HDR, IB_MGMT_SA_DATA,
					    gfp_mask,
					    ((query->flags & IB_SA_QUERY_OPA) ?
					     OPA_MGMT_BASE_VERSION :
					     IB_MGMT_BASE_VERSION));
	अगर (IS_ERR(query->mad_buf)) अणु
		kref_put(&query->sm_ah->ref, मुक्त_sm_ah);
		वापस -ENOMEM;
	पूर्ण

	query->mad_buf->ah = query->sm_ah->ah;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_mad(काष्ठा ib_sa_query *query)
अणु
	ib_मुक्त_send_mad(query->mad_buf);
	kref_put(&query->sm_ah->ref, मुक्त_sm_ah);
पूर्ण

अटल व्योम init_mad(काष्ठा ib_sa_query *query, काष्ठा ib_mad_agent *agent)
अणु
	काष्ठा ib_sa_mad *mad = query->mad_buf->mad;
	अचिन्हित दीर्घ flags;

	स_रखो(mad, 0, माप *mad);

	अगर (query->flags & IB_SA_QUERY_OPA) अणु
		mad->mad_hdr.base_version  = OPA_MGMT_BASE_VERSION;
		mad->mad_hdr.class_version = OPA_SA_CLASS_VERSION;
	पूर्ण अन्यथा अणु
		mad->mad_hdr.base_version  = IB_MGMT_BASE_VERSION;
		mad->mad_hdr.class_version = IB_SA_CLASS_VERSION;
	पूर्ण
	mad->mad_hdr.mgmt_class    = IB_MGMT_CLASS_SUBN_ADM;
	spin_lock_irqsave(&tid_lock, flags);
	mad->mad_hdr.tid           =
		cpu_to_be64(((u64) agent->hi_tid) << 32 | tid++);
	spin_unlock_irqrestore(&tid_lock, flags);
पूर्ण

अटल पूर्णांक send_mad(काष्ठा ib_sa_query *query, अचिन्हित दीर्घ समयout_ms,
		    gfp_t gfp_mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret, id;

	xa_lock_irqsave(&queries, flags);
	ret = __xa_alloc(&queries, &id, query, xa_limit_32b, gfp_mask);
	xa_unlock_irqrestore(&queries, flags);
	अगर (ret < 0)
		वापस ret;

	query->mad_buf->समयout_ms  = समयout_ms;
	query->mad_buf->context[0] = query;
	query->id = id;

	अगर ((query->flags & IB_SA_ENABLE_LOCAL_SERVICE) &&
	    (!(query->flags & IB_SA_QUERY_OPA))) अणु
		अगर (rdma_nl_chk_listeners(RDMA_NL_GROUP_LS)) अणु
			अगर (!ib_nl_make_request(query, gfp_mask))
				वापस id;
		पूर्ण
		ib_sa_disable_local_svc(query);
	पूर्ण

	ret = ib_post_send_mad(query->mad_buf, शून्य);
	अगर (ret) अणु
		xa_lock_irqsave(&queries, flags);
		__xa_erase(&queries, id);
		xa_unlock_irqrestore(&queries, flags);
	पूर्ण

	/*
	 * It's not safe to dereference query any more, because the
	 * send may alपढ़ोy have completed and मुक्तd the query in
	 * another context.
	 */
	वापस ret ? ret : id;
पूर्ण

व्योम ib_sa_unpack_path(व्योम *attribute, काष्ठा sa_path_rec *rec)
अणु
	ib_unpack(path_rec_table, ARRAY_SIZE(path_rec_table), attribute, rec);
पूर्ण
EXPORT_SYMBOL(ib_sa_unpack_path);

व्योम ib_sa_pack_path(काष्ठा sa_path_rec *rec, व्योम *attribute)
अणु
	ib_pack(path_rec_table, ARRAY_SIZE(path_rec_table), rec, attribute);
पूर्ण
EXPORT_SYMBOL(ib_sa_pack_path);

अटल bool ib_sa_opa_pathrecord_support(काष्ठा ib_sa_client *client,
					 काष्ठा ib_sa_device *sa_dev,
					 u32 port_num)
अणु
	काष्ठा ib_sa_port *port;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	port = &sa_dev->port[port_num - sa_dev->start_port];
	spin_lock_irqsave(&port->classport_lock, flags);
	अगर (!port->classport_info.valid)
		जाओ ret;

	अगर (port->classport_info.data.type == RDMA_CLASS_PORT_INFO_OPA)
		ret = opa_get_cpi_capmask2(&port->classport_info.data.opa) &
			OPA_CLASS_PORT_INFO_PR_SUPPORT;
ret:
	spin_unlock_irqrestore(&port->classport_lock, flags);
	वापस ret;
पूर्ण

क्रमागत opa_pr_supported अणु
	PR_NOT_SUPPORTED,
	PR_OPA_SUPPORTED,
	PR_IB_SUPPORTED
पूर्ण;

/*
 * opa_pr_query_possible - Check अगर current PR query can be an OPA query.
 *
 * Retuns PR_NOT_SUPPORTED अगर a path record query is not
 * possible, PR_OPA_SUPPORTED अगर an OPA path record query
 * is possible and PR_IB_SUPPORTED अगर an IB path record
 * query is possible.
 */
अटल पूर्णांक opa_pr_query_possible(काष्ठा ib_sa_client *client,
				 काष्ठा ib_sa_device *sa_dev,
				 काष्ठा ib_device *device, u32 port_num,
				 काष्ठा sa_path_rec *rec)
अणु
	काष्ठा ib_port_attr port_attr;

	अगर (ib_query_port(device, port_num, &port_attr))
		वापस PR_NOT_SUPPORTED;

	अगर (ib_sa_opa_pathrecord_support(client, sa_dev, port_num))
		वापस PR_OPA_SUPPORTED;

	अगर (port_attr.lid >= be16_to_cpu(IB_MULTICAST_LID_BASE))
		वापस PR_NOT_SUPPORTED;
	अन्यथा
		वापस PR_IB_SUPPORTED;
पूर्ण

अटल व्योम ib_sa_path_rec_callback(काष्ठा ib_sa_query *sa_query,
				    पूर्णांक status,
				    काष्ठा ib_sa_mad *mad)
अणु
	काष्ठा ib_sa_path_query *query =
		container_of(sa_query, काष्ठा ib_sa_path_query, sa_query);

	अगर (mad) अणु
		काष्ठा sa_path_rec rec;

		अगर (sa_query->flags & IB_SA_QUERY_OPA) अणु
			ib_unpack(opa_path_rec_table,
				  ARRAY_SIZE(opa_path_rec_table),
				  mad->data, &rec);
			rec.rec_type = SA_PATH_REC_TYPE_OPA;
			query->callback(status, &rec, query->context);
		पूर्ण अन्यथा अणु
			ib_unpack(path_rec_table,
				  ARRAY_SIZE(path_rec_table),
				  mad->data, &rec);
			rec.rec_type = SA_PATH_REC_TYPE_IB;
			sa_path_set_dmac_zero(&rec);

			अगर (query->conv_pr) अणु
				काष्ठा sa_path_rec opa;

				स_रखो(&opa, 0, माप(काष्ठा sa_path_rec));
				sa_convert_path_ib_to_opa(&opa, &rec);
				query->callback(status, &opa, query->context);
			पूर्ण अन्यथा अणु
				query->callback(status, &rec, query->context);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		query->callback(status, शून्य, query->context);
पूर्ण

अटल व्योम ib_sa_path_rec_release(काष्ठा ib_sa_query *sa_query)
अणु
	काष्ठा ib_sa_path_query *query =
		container_of(sa_query, काष्ठा ib_sa_path_query, sa_query);

	kमुक्त(query->conv_pr);
	kमुक्त(query);
पूर्ण

/**
 * ib_sa_path_rec_get - Start a Path get query
 * @client:SA client
 * @device:device to send query on
 * @port_num: port number to send query on
 * @rec:Path Record to send in query
 * @comp_mask:component mask to send in query
 * @समयout_ms:समय to रुको क्रम response
 * @gfp_mask:GFP mask to use क्रम पूर्णांकernal allocations
 * @callback:function called when query completes, बार out or is
 * canceled
 * @context:opaque user context passed to callback
 * @sa_query:query context, used to cancel query
 *
 * Send a Path Record Get query to the SA to look up a path.  The
 * callback function will be called when the query completes (or
 * fails); status is 0 क्रम a successful response, -EINTR अगर the query
 * is canceled, -ETIMEDOUT is the query समयd out, or -EIO अगर an error
 * occurred sending the query.  The resp parameter of the callback is
 * only valid अगर status is 0.
 *
 * If the वापस value of ib_sa_path_rec_get() is negative, it is an
 * error code.  Otherwise it is a query ID that can be used to cancel
 * the query.
 */
पूर्णांक ib_sa_path_rec_get(काष्ठा ib_sa_client *client,
		       काष्ठा ib_device *device, u32 port_num,
		       काष्ठा sa_path_rec *rec,
		       ib_sa_comp_mask comp_mask,
		       अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
		       व्योम (*callback)(पूर्णांक status,
					काष्ठा sa_path_rec *resp,
					व्योम *context),
		       व्योम *context,
		       काष्ठा ib_sa_query **sa_query)
अणु
	काष्ठा ib_sa_path_query *query;
	काष्ठा ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	काष्ठा ib_sa_port   *port;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_mad *mad;
	क्रमागत opa_pr_supported status;
	पूर्णांक ret;

	अगर (!sa_dev)
		वापस -ENODEV;

	अगर ((rec->rec_type != SA_PATH_REC_TYPE_IB) &&
	    (rec->rec_type != SA_PATH_REC_TYPE_OPA))
		वापस -EINVAL;

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	agent = port->agent;

	query = kzalloc(माप(*query), gfp_mask);
	अगर (!query)
		वापस -ENOMEM;

	query->sa_query.port     = port;
	अगर (rec->rec_type == SA_PATH_REC_TYPE_OPA) अणु
		status = opa_pr_query_possible(client, sa_dev, device, port_num,
					       rec);
		अगर (status == PR_NOT_SUPPORTED) अणु
			ret = -EINVAL;
			जाओ err1;
		पूर्ण अन्यथा अगर (status == PR_OPA_SUPPORTED) अणु
			query->sa_query.flags |= IB_SA_QUERY_OPA;
		पूर्ण अन्यथा अणु
			query->conv_pr =
				kदो_स्मृति(माप(*query->conv_pr), gfp_mask);
			अगर (!query->conv_pr) अणु
				ret = -ENOMEM;
				जाओ err1;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = alloc_mad(&query->sa_query, gfp_mask);
	अगर (ret)
		जाओ err2;

	ib_sa_client_get(client);
	query->sa_query.client = client;
	query->callback        = callback;
	query->context         = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = callback ? ib_sa_path_rec_callback : शून्य;
	query->sa_query.release  = ib_sa_path_rec_release;
	mad->mad_hdr.method	 = IB_MGMT_METHOD_GET;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_PATH_REC);
	mad->sa_hdr.comp_mask	 = comp_mask;

	अगर (query->sa_query.flags & IB_SA_QUERY_OPA) अणु
		ib_pack(opa_path_rec_table, ARRAY_SIZE(opa_path_rec_table),
			rec, mad->data);
	पूर्ण अन्यथा अगर (query->conv_pr) अणु
		sa_convert_path_opa_to_ib(query->conv_pr, rec);
		ib_pack(path_rec_table, ARRAY_SIZE(path_rec_table),
			query->conv_pr, mad->data);
	पूर्ण अन्यथा अणु
		ib_pack(path_rec_table, ARRAY_SIZE(path_rec_table),
			rec, mad->data);
	पूर्ण

	*sa_query = &query->sa_query;

	query->sa_query.flags |= IB_SA_ENABLE_LOCAL_SERVICE;
	query->sa_query.mad_buf->context[1] = (query->conv_pr) ?
						query->conv_pr : rec;

	ret = send_mad(&query->sa_query, समयout_ms, gfp_mask);
	अगर (ret < 0)
		जाओ err3;

	वापस ret;

err3:
	*sa_query = शून्य;
	ib_sa_client_put(query->sa_query.client);
	मुक्त_mad(&query->sa_query);
err2:
	kमुक्त(query->conv_pr);
err1:
	kमुक्त(query);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_sa_path_rec_get);

अटल व्योम ib_sa_service_rec_callback(काष्ठा ib_sa_query *sa_query,
				    पूर्णांक status,
				    काष्ठा ib_sa_mad *mad)
अणु
	काष्ठा ib_sa_service_query *query =
		container_of(sa_query, काष्ठा ib_sa_service_query, sa_query);

	अगर (mad) अणु
		काष्ठा ib_sa_service_rec rec;

		ib_unpack(service_rec_table, ARRAY_SIZE(service_rec_table),
			  mad->data, &rec);
		query->callback(status, &rec, query->context);
	पूर्ण अन्यथा
		query->callback(status, शून्य, query->context);
पूर्ण

अटल व्योम ib_sa_service_rec_release(काष्ठा ib_sa_query *sa_query)
अणु
	kमुक्त(container_of(sa_query, काष्ठा ib_sa_service_query, sa_query));
पूर्ण

/**
 * ib_sa_service_rec_query - Start Service Record operation
 * @client:SA client
 * @device:device to send request on
 * @port_num: port number to send request on
 * @method:SA method - should be get, set, or delete
 * @rec:Service Record to send in request
 * @comp_mask:component mask to send in request
 * @समयout_ms:समय to रुको क्रम response
 * @gfp_mask:GFP mask to use क्रम पूर्णांकernal allocations
 * @callback:function called when request completes, बार out or is
 * canceled
 * @context:opaque user context passed to callback
 * @sa_query:request context, used to cancel request
 *
 * Send a Service Record set/get/delete to the SA to रेजिस्टर,
 * unरेजिस्टर or query a service record.
 * The callback function will be called when the request completes (or
 * fails); status is 0 क्रम a successful response, -EINTR अगर the query
 * is canceled, -ETIMEDOUT is the query समयd out, or -EIO अगर an error
 * occurred sending the query.  The resp parameter of the callback is
 * only valid अगर status is 0.
 *
 * If the वापस value of ib_sa_service_rec_query() is negative, it is an
 * error code.  Otherwise it is a request ID that can be used to cancel
 * the query.
 */
पूर्णांक ib_sa_service_rec_query(काष्ठा ib_sa_client *client,
			    काष्ठा ib_device *device, u32 port_num, u8 method,
			    काष्ठा ib_sa_service_rec *rec,
			    ib_sa_comp_mask comp_mask,
			    अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
			    व्योम (*callback)(पूर्णांक status,
					     काष्ठा ib_sa_service_rec *resp,
					     व्योम *context),
			    व्योम *context,
			    काष्ठा ib_sa_query **sa_query)
अणु
	काष्ठा ib_sa_service_query *query;
	काष्ठा ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	काष्ठा ib_sa_port   *port;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_mad *mad;
	पूर्णांक ret;

	अगर (!sa_dev)
		वापस -ENODEV;

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	agent = port->agent;

	अगर (method != IB_MGMT_METHOD_GET &&
	    method != IB_MGMT_METHOD_SET &&
	    method != IB_SA_METHOD_DELETE)
		वापस -EINVAL;

	query = kzalloc(माप(*query), gfp_mask);
	अगर (!query)
		वापस -ENOMEM;

	query->sa_query.port     = port;
	ret = alloc_mad(&query->sa_query, gfp_mask);
	अगर (ret)
		जाओ err1;

	ib_sa_client_get(client);
	query->sa_query.client = client;
	query->callback        = callback;
	query->context         = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = callback ? ib_sa_service_rec_callback : शून्य;
	query->sa_query.release  = ib_sa_service_rec_release;
	mad->mad_hdr.method	 = method;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_SERVICE_REC);
	mad->sa_hdr.comp_mask	 = comp_mask;

	ib_pack(service_rec_table, ARRAY_SIZE(service_rec_table),
		rec, mad->data);

	*sa_query = &query->sa_query;

	ret = send_mad(&query->sa_query, समयout_ms, gfp_mask);
	अगर (ret < 0)
		जाओ err2;

	वापस ret;

err2:
	*sa_query = शून्य;
	ib_sa_client_put(query->sa_query.client);
	मुक्त_mad(&query->sa_query);

err1:
	kमुक्त(query);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_sa_service_rec_query);

अटल व्योम ib_sa_mcmember_rec_callback(काष्ठा ib_sa_query *sa_query,
					पूर्णांक status,
					काष्ठा ib_sa_mad *mad)
अणु
	काष्ठा ib_sa_mcmember_query *query =
		container_of(sa_query, काष्ठा ib_sa_mcmember_query, sa_query);

	अगर (mad) अणु
		काष्ठा ib_sa_mcmember_rec rec;

		ib_unpack(mcmember_rec_table, ARRAY_SIZE(mcmember_rec_table),
			  mad->data, &rec);
		query->callback(status, &rec, query->context);
	पूर्ण अन्यथा
		query->callback(status, शून्य, query->context);
पूर्ण

अटल व्योम ib_sa_mcmember_rec_release(काष्ठा ib_sa_query *sa_query)
अणु
	kमुक्त(container_of(sa_query, काष्ठा ib_sa_mcmember_query, sa_query));
पूर्ण

पूर्णांक ib_sa_mcmember_rec_query(काष्ठा ib_sa_client *client,
			     काष्ठा ib_device *device, u32 port_num,
			     u8 method,
			     काष्ठा ib_sa_mcmember_rec *rec,
			     ib_sa_comp_mask comp_mask,
			     अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
			     व्योम (*callback)(पूर्णांक status,
					      काष्ठा ib_sa_mcmember_rec *resp,
					      व्योम *context),
			     व्योम *context,
			     काष्ठा ib_sa_query **sa_query)
अणु
	काष्ठा ib_sa_mcmember_query *query;
	काष्ठा ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	काष्ठा ib_sa_port   *port;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_mad *mad;
	पूर्णांक ret;

	अगर (!sa_dev)
		वापस -ENODEV;

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	agent = port->agent;

	query = kzalloc(माप(*query), gfp_mask);
	अगर (!query)
		वापस -ENOMEM;

	query->sa_query.port     = port;
	ret = alloc_mad(&query->sa_query, gfp_mask);
	अगर (ret)
		जाओ err1;

	ib_sa_client_get(client);
	query->sa_query.client = client;
	query->callback        = callback;
	query->context         = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = callback ? ib_sa_mcmember_rec_callback : शून्य;
	query->sa_query.release  = ib_sa_mcmember_rec_release;
	mad->mad_hdr.method	 = method;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_MC_MEMBER_REC);
	mad->sa_hdr.comp_mask	 = comp_mask;

	ib_pack(mcmember_rec_table, ARRAY_SIZE(mcmember_rec_table),
		rec, mad->data);

	*sa_query = &query->sa_query;

	ret = send_mad(&query->sa_query, समयout_ms, gfp_mask);
	अगर (ret < 0)
		जाओ err2;

	वापस ret;

err2:
	*sa_query = शून्य;
	ib_sa_client_put(query->sa_query.client);
	मुक्त_mad(&query->sa_query);

err1:
	kमुक्त(query);
	वापस ret;
पूर्ण

/* Support GuidInfoRecord */
अटल व्योम ib_sa_guidinfo_rec_callback(काष्ठा ib_sa_query *sa_query,
					पूर्णांक status,
					काष्ठा ib_sa_mad *mad)
अणु
	काष्ठा ib_sa_guidinfo_query *query =
		container_of(sa_query, काष्ठा ib_sa_guidinfo_query, sa_query);

	अगर (mad) अणु
		काष्ठा ib_sa_guidinfo_rec rec;

		ib_unpack(guidinfo_rec_table, ARRAY_SIZE(guidinfo_rec_table),
			  mad->data, &rec);
		query->callback(status, &rec, query->context);
	पूर्ण अन्यथा
		query->callback(status, शून्य, query->context);
पूर्ण

अटल व्योम ib_sa_guidinfo_rec_release(काष्ठा ib_sa_query *sa_query)
अणु
	kमुक्त(container_of(sa_query, काष्ठा ib_sa_guidinfo_query, sa_query));
पूर्ण

पूर्णांक ib_sa_guid_info_rec_query(काष्ठा ib_sa_client *client,
			      काष्ठा ib_device *device, u32 port_num,
			      काष्ठा ib_sa_guidinfo_rec *rec,
			      ib_sa_comp_mask comp_mask, u8 method,
			      अचिन्हित दीर्घ समयout_ms, gfp_t gfp_mask,
			      व्योम (*callback)(पूर्णांक status,
					       काष्ठा ib_sa_guidinfo_rec *resp,
					       व्योम *context),
			      व्योम *context,
			      काष्ठा ib_sa_query **sa_query)
अणु
	काष्ठा ib_sa_guidinfo_query *query;
	काष्ठा ib_sa_device *sa_dev = ib_get_client_data(device, &sa_client);
	काष्ठा ib_sa_port *port;
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_mad *mad;
	पूर्णांक ret;

	अगर (!sa_dev)
		वापस -ENODEV;

	अगर (method != IB_MGMT_METHOD_GET &&
	    method != IB_MGMT_METHOD_SET &&
	    method != IB_SA_METHOD_DELETE) अणु
		वापस -EINVAL;
	पूर्ण

	port  = &sa_dev->port[port_num - sa_dev->start_port];
	agent = port->agent;

	query = kzalloc(माप(*query), gfp_mask);
	अगर (!query)
		वापस -ENOMEM;

	query->sa_query.port = port;
	ret = alloc_mad(&query->sa_query, gfp_mask);
	अगर (ret)
		जाओ err1;

	ib_sa_client_get(client);
	query->sa_query.client = client;
	query->callback        = callback;
	query->context         = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = callback ? ib_sa_guidinfo_rec_callback : शून्य;
	query->sa_query.release  = ib_sa_guidinfo_rec_release;

	mad->mad_hdr.method	 = method;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_GUID_INFO_REC);
	mad->sa_hdr.comp_mask	 = comp_mask;

	ib_pack(guidinfo_rec_table, ARRAY_SIZE(guidinfo_rec_table), rec,
		mad->data);

	*sa_query = &query->sa_query;

	ret = send_mad(&query->sa_query, समयout_ms, gfp_mask);
	अगर (ret < 0)
		जाओ err2;

	वापस ret;

err2:
	*sa_query = शून्य;
	ib_sa_client_put(query->sa_query.client);
	मुक्त_mad(&query->sa_query);

err1:
	kमुक्त(query);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ib_sa_guid_info_rec_query);

काष्ठा ib_classport_info_context अणु
	काष्ठा completion	करोne;
	काष्ठा ib_sa_query	*sa_query;
पूर्ण;

अटल व्योम ib_classportinfo_cb(व्योम *context)
अणु
	काष्ठा ib_classport_info_context *cb_ctx = context;

	complete(&cb_ctx->करोne);
पूर्ण

अटल व्योम ib_sa_classport_info_rec_callback(काष्ठा ib_sa_query *sa_query,
					      पूर्णांक status,
					      काष्ठा ib_sa_mad *mad)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ib_sa_classport_info_query *query =
		container_of(sa_query, काष्ठा ib_sa_classport_info_query, sa_query);
	काष्ठा ib_sa_classport_cache *info = &sa_query->port->classport_info;

	अगर (mad) अणु
		अगर (sa_query->flags & IB_SA_QUERY_OPA) अणु
			काष्ठा opa_class_port_info rec;

			ib_unpack(opa_classport_info_rec_table,
				  ARRAY_SIZE(opa_classport_info_rec_table),
				  mad->data, &rec);

			spin_lock_irqsave(&sa_query->port->classport_lock,
					  flags);
			अगर (!status && !info->valid) अणु
				स_नकल(&info->data.opa, &rec,
				       माप(info->data.opa));

				info->valid = true;
				info->data.type = RDMA_CLASS_PORT_INFO_OPA;
			पूर्ण
			spin_unlock_irqrestore(&sa_query->port->classport_lock,
					       flags);

		पूर्ण अन्यथा अणु
			काष्ठा ib_class_port_info rec;

			ib_unpack(ib_classport_info_rec_table,
				  ARRAY_SIZE(ib_classport_info_rec_table),
				  mad->data, &rec);

			spin_lock_irqsave(&sa_query->port->classport_lock,
					  flags);
			अगर (!status && !info->valid) अणु
				स_नकल(&info->data.ib, &rec,
				       माप(info->data.ib));

				info->valid = true;
				info->data.type = RDMA_CLASS_PORT_INFO_IB;
			पूर्ण
			spin_unlock_irqrestore(&sa_query->port->classport_lock,
					       flags);
		पूर्ण
	पूर्ण
	query->callback(query->context);
पूर्ण

अटल व्योम ib_sa_classport_info_rec_release(काष्ठा ib_sa_query *sa_query)
अणु
	kमुक्त(container_of(sa_query, काष्ठा ib_sa_classport_info_query,
			   sa_query));
पूर्ण

अटल पूर्णांक ib_sa_classport_info_rec_query(काष्ठा ib_sa_port *port,
					  अचिन्हित दीर्घ समयout_ms,
					  व्योम (*callback)(व्योम *context),
					  व्योम *context,
					  काष्ठा ib_sa_query **sa_query)
अणु
	काष्ठा ib_mad_agent *agent;
	काष्ठा ib_sa_classport_info_query *query;
	काष्ठा ib_sa_mad *mad;
	gfp_t gfp_mask = GFP_KERNEL;
	पूर्णांक ret;

	agent = port->agent;

	query = kzalloc(माप(*query), gfp_mask);
	अगर (!query)
		वापस -ENOMEM;

	query->sa_query.port = port;
	query->sa_query.flags |= rdma_cap_opa_ah(port->agent->device,
						 port->port_num) ?
				 IB_SA_QUERY_OPA : 0;
	ret = alloc_mad(&query->sa_query, gfp_mask);
	अगर (ret)
		जाओ err_मुक्त;

	query->callback = callback;
	query->context = context;

	mad = query->sa_query.mad_buf->mad;
	init_mad(&query->sa_query, agent);

	query->sa_query.callback = ib_sa_classport_info_rec_callback;
	query->sa_query.release  = ib_sa_classport_info_rec_release;
	mad->mad_hdr.method	 = IB_MGMT_METHOD_GET;
	mad->mad_hdr.attr_id	 = cpu_to_be16(IB_SA_ATTR_CLASS_PORTINFO);
	mad->sa_hdr.comp_mask	 = 0;
	*sa_query = &query->sa_query;

	ret = send_mad(&query->sa_query, समयout_ms, gfp_mask);
	अगर (ret < 0)
		जाओ err_मुक्त_mad;

	वापस ret;

err_मुक्त_mad:
	*sa_query = शून्य;
	मुक्त_mad(&query->sa_query);

err_मुक्त:
	kमुक्त(query);
	वापस ret;
पूर्ण

अटल व्योम update_ib_cpi(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_sa_port *port =
		container_of(work, काष्ठा ib_sa_port, ib_cpi_work.work);
	काष्ठा ib_classport_info_context *cb_context;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/* If the classport info is valid, nothing
	 * to करो here.
	 */
	spin_lock_irqsave(&port->classport_lock, flags);
	अगर (port->classport_info.valid) अणु
		spin_unlock_irqrestore(&port->classport_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&port->classport_lock, flags);

	cb_context = kदो_स्मृति(माप(*cb_context), GFP_KERNEL);
	अगर (!cb_context)
		जाओ err_nomem;

	init_completion(&cb_context->करोne);

	ret = ib_sa_classport_info_rec_query(port, 3000,
					     ib_classportinfo_cb, cb_context,
					     &cb_context->sa_query);
	अगर (ret < 0)
		जाओ मुक्त_cb_err;
	रुको_क्रम_completion(&cb_context->करोne);
मुक्त_cb_err:
	kमुक्त(cb_context);
	spin_lock_irqsave(&port->classport_lock, flags);

	/* If the classport info is still not valid, the query should have
	 * failed क्रम some reason. Retry issuing the query
	 */
	अगर (!port->classport_info.valid) अणु
		port->classport_info.retry_cnt++;
		अगर (port->classport_info.retry_cnt <=
		    IB_SA_CPI_MAX_RETRY_CNT) अणु
			अचिन्हित दीर्घ delay =
				msecs_to_jअगरfies(IB_SA_CPI_RETRY_WAIT);

			queue_delayed_work(ib_wq, &port->ib_cpi_work, delay);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&port->classport_lock, flags);

err_nomem:
	वापस;
पूर्ण

अटल व्योम send_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	काष्ठा ib_sa_query *query = mad_send_wc->send_buf->context[0];
	अचिन्हित दीर्घ flags;

	अगर (query->callback)
		चयन (mad_send_wc->status) अणु
		हाल IB_WC_SUCCESS:
			/* No callback -- alपढ़ोy got recv */
			अवरोध;
		हाल IB_WC_RESP_TIMEOUT_ERR:
			query->callback(query, -ETIMEDOUT, शून्य);
			अवरोध;
		हाल IB_WC_WR_FLUSH_ERR:
			query->callback(query, -EINTR, शून्य);
			अवरोध;
		शेष:
			query->callback(query, -EIO, शून्य);
			अवरोध;
		पूर्ण

	xa_lock_irqsave(&queries, flags);
	__xa_erase(&queries, query->id);
	xa_unlock_irqrestore(&queries, flags);

	मुक्त_mad(query);
	अगर (query->client)
		ib_sa_client_put(query->client);
	query->release(query);
पूर्ण

अटल व्योम recv_handler(काष्ठा ib_mad_agent *mad_agent,
			 काष्ठा ib_mad_send_buf *send_buf,
			 काष्ठा ib_mad_recv_wc *mad_recv_wc)
अणु
	काष्ठा ib_sa_query *query;

	अगर (!send_buf)
		वापस;

	query = send_buf->context[0];
	अगर (query->callback) अणु
		अगर (mad_recv_wc->wc->status == IB_WC_SUCCESS)
			query->callback(query,
					mad_recv_wc->recv_buf.mad->mad_hdr.status ?
					-EINVAL : 0,
					(काष्ठा ib_sa_mad *) mad_recv_wc->recv_buf.mad);
		अन्यथा
			query->callback(query, -EIO, शून्य);
	पूर्ण

	ib_मुक्त_recv_mad(mad_recv_wc);
पूर्ण

अटल व्योम update_sm_ah(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_sa_port *port =
		container_of(work, काष्ठा ib_sa_port, update_task);
	काष्ठा ib_sa_sm_ah *new_ah;
	काष्ठा ib_port_attr port_attr;
	काष्ठा rdma_ah_attr   ah_attr;
	bool grh_required;

	अगर (ib_query_port(port->agent->device, port->port_num, &port_attr)) अणु
		pr_warn("Couldn't query port\n");
		वापस;
	पूर्ण

	new_ah = kदो_स्मृति(माप(*new_ah), GFP_KERNEL);
	अगर (!new_ah)
		वापस;

	kref_init(&new_ah->ref);
	new_ah->src_path_mask = (1 << port_attr.lmc) - 1;

	new_ah->pkey_index = 0;
	अगर (ib_find_pkey(port->agent->device, port->port_num,
			 IB_DEFAULT_PKEY_FULL, &new_ah->pkey_index))
		pr_err("Couldn't find index for default PKey\n");

	स_रखो(&ah_attr, 0, माप(ah_attr));
	ah_attr.type = rdma_ah_find_type(port->agent->device,
					 port->port_num);
	rdma_ah_set_dlid(&ah_attr, port_attr.sm_lid);
	rdma_ah_set_sl(&ah_attr, port_attr.sm_sl);
	rdma_ah_set_port_num(&ah_attr, port->port_num);

	grh_required = rdma_is_grh_required(port->agent->device,
					    port->port_num);

	/*
	 * The OPA sm_lid of 0xFFFF needs special handling so that it can be
	 * dअगरferentiated from a permissive LID of 0xFFFF.  We set the
	 * grh_required flag here so the SA can program the DGID in the
	 * address handle appropriately
	 */
	अगर (ah_attr.type == RDMA_AH_ATTR_TYPE_OPA &&
	    (grh_required ||
	     port_attr.sm_lid == be16_to_cpu(IB_LID_PERMISSIVE)))
		rdma_ah_set_make_grd(&ah_attr, true);

	अगर (ah_attr.type == RDMA_AH_ATTR_TYPE_IB && grh_required) अणु
		rdma_ah_set_ah_flags(&ah_attr, IB_AH_GRH);
		rdma_ah_set_subnet_prefix(&ah_attr,
					  cpu_to_be64(port_attr.subnet_prefix));
		rdma_ah_set_पूर्णांकerface_id(&ah_attr,
					 cpu_to_be64(IB_SA_WELL_KNOWN_GUID));
	पूर्ण

	new_ah->ah = rdma_create_ah(port->agent->qp->pd, &ah_attr,
				    RDMA_CREATE_AH_SLEEPABLE);
	अगर (IS_ERR(new_ah->ah)) अणु
		pr_warn("Couldn't create new SM AH\n");
		kमुक्त(new_ah);
		वापस;
	पूर्ण

	spin_lock_irq(&port->ah_lock);
	अगर (port->sm_ah)
		kref_put(&port->sm_ah->ref, मुक्त_sm_ah);
	port->sm_ah = new_ah;
	spin_unlock_irq(&port->ah_lock);
पूर्ण

अटल व्योम ib_sa_event(काष्ठा ib_event_handler *handler,
			काष्ठा ib_event *event)
अणु
	अगर (event->event == IB_EVENT_PORT_ERR    ||
	    event->event == IB_EVENT_PORT_ACTIVE ||
	    event->event == IB_EVENT_LID_CHANGE  ||
	    event->event == IB_EVENT_PKEY_CHANGE ||
	    event->event == IB_EVENT_SM_CHANGE   ||
	    event->event == IB_EVENT_CLIENT_REREGISTER) अणु
		अचिन्हित दीर्घ flags;
		काष्ठा ib_sa_device *sa_dev =
			container_of(handler, typeof(*sa_dev), event_handler);
		u32 port_num = event->element.port_num - sa_dev->start_port;
		काष्ठा ib_sa_port *port = &sa_dev->port[port_num];

		अगर (!rdma_cap_ib_sa(handler->device, port->port_num))
			वापस;

		spin_lock_irqsave(&port->ah_lock, flags);
		अगर (port->sm_ah)
			kref_put(&port->sm_ah->ref, मुक्त_sm_ah);
		port->sm_ah = शून्य;
		spin_unlock_irqrestore(&port->ah_lock, flags);

		अगर (event->event == IB_EVENT_SM_CHANGE ||
		    event->event == IB_EVENT_CLIENT_REREGISTER ||
		    event->event == IB_EVENT_LID_CHANGE ||
		    event->event == IB_EVENT_PORT_ACTIVE) अणु
			अचिन्हित दीर्घ delay =
				msecs_to_jअगरfies(IB_SA_CPI_RETRY_WAIT);

			spin_lock_irqsave(&port->classport_lock, flags);
			port->classport_info.valid = false;
			port->classport_info.retry_cnt = 0;
			spin_unlock_irqrestore(&port->classport_lock, flags);
			queue_delayed_work(ib_wq,
					   &port->ib_cpi_work, delay);
		पूर्ण
		queue_work(ib_wq, &sa_dev->port[port_num].update_task);
	पूर्ण
पूर्ण

अटल पूर्णांक ib_sa_add_one(काष्ठा ib_device *device)
अणु
	काष्ठा ib_sa_device *sa_dev;
	पूर्णांक s, e, i;
	पूर्णांक count = 0;
	पूर्णांक ret;

	s = rdma_start_port(device);
	e = rdma_end_port(device);

	sa_dev = kzalloc(काष्ठा_size(sa_dev, port, e - s + 1), GFP_KERNEL);
	अगर (!sa_dev)
		वापस -ENOMEM;

	sa_dev->start_port = s;
	sa_dev->end_port   = e;

	क्रम (i = 0; i <= e - s; ++i) अणु
		spin_lock_init(&sa_dev->port[i].ah_lock);
		अगर (!rdma_cap_ib_sa(device, i + 1))
			जारी;

		sa_dev->port[i].sm_ah    = शून्य;
		sa_dev->port[i].port_num = i + s;

		spin_lock_init(&sa_dev->port[i].classport_lock);
		sa_dev->port[i].classport_info.valid = false;

		sa_dev->port[i].agent =
			ib_रेजिस्टर_mad_agent(device, i + s, IB_QPT_GSI,
					      शून्य, 0, send_handler,
					      recv_handler, sa_dev, 0);
		अगर (IS_ERR(sa_dev->port[i].agent)) अणु
			ret = PTR_ERR(sa_dev->port[i].agent);
			जाओ err;
		पूर्ण

		INIT_WORK(&sa_dev->port[i].update_task, update_sm_ah);
		INIT_DELAYED_WORK(&sa_dev->port[i].ib_cpi_work,
				  update_ib_cpi);

		count++;
	पूर्ण

	अगर (!count) अणु
		ret = -EOPNOTSUPP;
		जाओ मुक्त;
	पूर्ण

	ib_set_client_data(device, &sa_client, sa_dev);

	/*
	 * We रेजिस्टर our event handler after everything is set up,
	 * and then update our cached info after the event handler is
	 * रेजिस्टरed to aव्योम any problems अगर a port changes state
	 * during our initialization.
	 */

	INIT_IB_EVENT_HANDLER(&sa_dev->event_handler, device, ib_sa_event);
	ib_रेजिस्टर_event_handler(&sa_dev->event_handler);

	क्रम (i = 0; i <= e - s; ++i) अणु
		अगर (rdma_cap_ib_sa(device, i + 1))
			update_sm_ah(&sa_dev->port[i].update_task);
	पूर्ण

	वापस 0;

err:
	जबतक (--i >= 0) अणु
		अगर (rdma_cap_ib_sa(device, i + 1))
			ib_unरेजिस्टर_mad_agent(sa_dev->port[i].agent);
	पूर्ण
मुक्त:
	kमुक्त(sa_dev);
	वापस ret;
पूर्ण

अटल व्योम ib_sa_हटाओ_one(काष्ठा ib_device *device, व्योम *client_data)
अणु
	काष्ठा ib_sa_device *sa_dev = client_data;
	पूर्णांक i;

	ib_unरेजिस्टर_event_handler(&sa_dev->event_handler);
	flush_workqueue(ib_wq);

	क्रम (i = 0; i <= sa_dev->end_port - sa_dev->start_port; ++i) अणु
		अगर (rdma_cap_ib_sa(device, i + 1)) अणु
			cancel_delayed_work_sync(&sa_dev->port[i].ib_cpi_work);
			ib_unरेजिस्टर_mad_agent(sa_dev->port[i].agent);
			अगर (sa_dev->port[i].sm_ah)
				kref_put(&sa_dev->port[i].sm_ah->ref, मुक्त_sm_ah);
		पूर्ण

	पूर्ण

	kमुक्त(sa_dev);
पूर्ण

पूर्णांक ib_sa_init(व्योम)
अणु
	पूर्णांक ret;

	get_अक्रमom_bytes(&tid, माप tid);

	atomic_set(&ib_nl_sa_request_seq, 0);

	ret = ib_रेजिस्टर_client(&sa_client);
	अगर (ret) अणु
		pr_err("Couldn't register ib_sa client\n");
		जाओ err1;
	पूर्ण

	ret = mcast_init();
	अगर (ret) अणु
		pr_err("Couldn't initialize multicast handling\n");
		जाओ err2;
	पूर्ण

	ib_nl_wq = alloc_ordered_workqueue("ib_nl_sa_wq", WQ_MEM_RECLAIM);
	अगर (!ib_nl_wq) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण

	INIT_DELAYED_WORK(&ib_nl_समयd_work, ib_nl_request_समयout);

	वापस 0;

err3:
	mcast_cleanup();
err2:
	ib_unरेजिस्टर_client(&sa_client);
err1:
	वापस ret;
पूर्ण

व्योम ib_sa_cleanup(व्योम)
अणु
	cancel_delayed_work(&ib_nl_समयd_work);
	flush_workqueue(ib_nl_wq);
	destroy_workqueue(ib_nl_wq);
	mcast_cleanup();
	ib_unरेजिस्टर_client(&sa_client);
	WARN_ON(!xa_empty(&queries));
पूर्ण
