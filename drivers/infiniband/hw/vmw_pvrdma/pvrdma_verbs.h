<शैली गुरु>
/*
 * Copyright (c) 2012-2016 VMware, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of EITHER the GNU General Public License
 * version 2 as published by the Free Software Foundation or the BSD
 * 2-Clause License. This program is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License version 2 क्रम more details at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.en.hपंचांगl.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program available in the file COPYING in the मुख्य
 * directory of this source tree.
 *
 * The BSD 2-Clause License
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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __PVRDMA_VERBS_H__
#घोषणा __PVRDMA_VERBS_H__

#समावेश <linux/types.h>

जोड़ pvrdma_gid अणु
	u8	raw[16];
	काष्ठा अणु
		__be64	subnet_prefix;
		__be64	पूर्णांकerface_id;
	पूर्ण global;
पूर्ण;

क्रमागत pvrdma_link_layer अणु
	PVRDMA_LINK_LAYER_UNSPECIFIED,
	PVRDMA_LINK_LAYER_INFINIBAND,
	PVRDMA_LINK_LAYER_ETHERNET,
पूर्ण;

क्रमागत pvrdma_mtu अणु
	PVRDMA_MTU_256  = 1,
	PVRDMA_MTU_512  = 2,
	PVRDMA_MTU_1024 = 3,
	PVRDMA_MTU_2048 = 4,
	PVRDMA_MTU_4096 = 5,
पूर्ण;

क्रमागत pvrdma_port_state अणु
	PVRDMA_PORT_NOP			= 0,
	PVRDMA_PORT_DOWN		= 1,
	PVRDMA_PORT_INIT		= 2,
	PVRDMA_PORT_ARMED		= 3,
	PVRDMA_PORT_ACTIVE		= 4,
	PVRDMA_PORT_ACTIVE_DEFER	= 5,
पूर्ण;

क्रमागत pvrdma_port_cap_flags अणु
	PVRDMA_PORT_SM				= 1 <<  1,
	PVRDMA_PORT_NOTICE_SUP			= 1 <<  2,
	PVRDMA_PORT_TRAP_SUP			= 1 <<  3,
	PVRDMA_PORT_OPT_IPD_SUP			= 1 <<  4,
	PVRDMA_PORT_AUTO_MIGR_SUP		= 1 <<  5,
	PVRDMA_PORT_SL_MAP_SUP			= 1 <<  6,
	PVRDMA_PORT_MKEY_NVRAM			= 1 <<  7,
	PVRDMA_PORT_PKEY_NVRAM			= 1 <<  8,
	PVRDMA_PORT_LED_INFO_SUP		= 1 <<  9,
	PVRDMA_PORT_SM_DISABLED			= 1 << 10,
	PVRDMA_PORT_SYS_IMAGE_GUID_SUP		= 1 << 11,
	PVRDMA_PORT_PKEY_SW_EXT_PORT_TRAP_SUP	= 1 << 12,
	PVRDMA_PORT_EXTENDED_SPEEDS_SUP		= 1 << 14,
	PVRDMA_PORT_CM_SUP			= 1 << 16,
	PVRDMA_PORT_SNMP_TUNNEL_SUP		= 1 << 17,
	PVRDMA_PORT_REINIT_SUP			= 1 << 18,
	PVRDMA_PORT_DEVICE_MGMT_SUP		= 1 << 19,
	PVRDMA_PORT_VENDOR_CLASS_SUP		= 1 << 20,
	PVRDMA_PORT_DR_NOTICE_SUP		= 1 << 21,
	PVRDMA_PORT_CAP_MASK_NOTICE_SUP		= 1 << 22,
	PVRDMA_PORT_BOOT_MGMT_SUP		= 1 << 23,
	PVRDMA_PORT_LINK_LATENCY_SUP		= 1 << 24,
	PVRDMA_PORT_CLIENT_REG_SUP		= 1 << 25,
	PVRDMA_PORT_IP_BASED_GIDS		= 1 << 26,
	PVRDMA_PORT_CAP_FLAGS_MAX		= PVRDMA_PORT_IP_BASED_GIDS,
पूर्ण;

क्रमागत pvrdma_port_width अणु
	PVRDMA_WIDTH_1X		= 1,
	PVRDMA_WIDTH_4X		= 2,
	PVRDMA_WIDTH_8X		= 4,
	PVRDMA_WIDTH_12X	= 8,
पूर्ण;

क्रमागत pvrdma_port_speed अणु
	PVRDMA_SPEED_SDR	= 1,
	PVRDMA_SPEED_DDR	= 2,
	PVRDMA_SPEED_QDR	= 4,
	PVRDMA_SPEED_FDR10	= 8,
	PVRDMA_SPEED_FDR	= 16,
	PVRDMA_SPEED_EDR	= 32,
पूर्ण;

काष्ठा pvrdma_port_attr अणु
	क्रमागत pvrdma_port_state	state;
	क्रमागत pvrdma_mtu		max_mtu;
	क्रमागत pvrdma_mtu		active_mtu;
	u32			gid_tbl_len;
	u32			port_cap_flags;
	u32			max_msg_sz;
	u32			bad_pkey_cntr;
	u32			qkey_viol_cntr;
	u16			pkey_tbl_len;
	u16			lid;
	u16			sm_lid;
	u8			lmc;
	u8			max_vl_num;
	u8			sm_sl;
	u8			subnet_समयout;
	u8			init_type_reply;
	u8			active_width;
	u8			active_speed;
	u8			phys_state;
	u8			reserved[2];
पूर्ण;

काष्ठा pvrdma_global_route अणु
	जोड़ pvrdma_gid	dgid;
	u32			flow_label;
	u8			sgid_index;
	u8			hop_limit;
	u8			traffic_class;
	u8			reserved;
पूर्ण;

काष्ठा pvrdma_grh अणु
	__be32			version_tclass_flow;
	__be16			paylen;
	u8			next_hdr;
	u8			hop_limit;
	जोड़ pvrdma_gid	sgid;
	जोड़ pvrdma_gid	dgid;
पूर्ण;

क्रमागत pvrdma_ah_flags अणु
	PVRDMA_AH_GRH = 1,
पूर्ण;

क्रमागत pvrdma_rate अणु
	PVRDMA_RATE_PORT_CURRENT	= 0,
	PVRDMA_RATE_2_5_GBPS		= 2,
	PVRDMA_RATE_5_GBPS		= 5,
	PVRDMA_RATE_10_GBPS		= 3,
	PVRDMA_RATE_20_GBPS		= 6,
	PVRDMA_RATE_30_GBPS		= 4,
	PVRDMA_RATE_40_GBPS		= 7,
	PVRDMA_RATE_60_GBPS		= 8,
	PVRDMA_RATE_80_GBPS		= 9,
	PVRDMA_RATE_120_GBPS		= 10,
	PVRDMA_RATE_14_GBPS		= 11,
	PVRDMA_RATE_56_GBPS		= 12,
	PVRDMA_RATE_112_GBPS		= 13,
	PVRDMA_RATE_168_GBPS		= 14,
	PVRDMA_RATE_25_GBPS		= 15,
	PVRDMA_RATE_100_GBPS		= 16,
	PVRDMA_RATE_200_GBPS		= 17,
	PVRDMA_RATE_300_GBPS		= 18,
पूर्ण;

काष्ठा pvrdma_ah_attr अणु
	काष्ठा pvrdma_global_route	grh;
	u16				dlid;
	u16				vlan_id;
	u8				sl;
	u8				src_path_bits;
	u8				अटल_rate;
	u8				ah_flags;
	u8				port_num;
	u8				dmac[6];
	u8				reserved;
पूर्ण;

क्रमागत pvrdma_cq_notअगरy_flags अणु
	PVRDMA_CQ_SOLICITED		= 1 << 0,
	PVRDMA_CQ_NEXT_COMP		= 1 << 1,
	PVRDMA_CQ_SOLICITED_MASK	= PVRDMA_CQ_SOLICITED |
					  PVRDMA_CQ_NEXT_COMP,
	PVRDMA_CQ_REPORT_MISSED_EVENTS	= 1 << 2,
पूर्ण;

काष्ठा pvrdma_qp_cap अणु
	u32	max_send_wr;
	u32	max_recv_wr;
	u32	max_send_sge;
	u32	max_recv_sge;
	u32	max_अंतरभूत_data;
	u32	reserved;
पूर्ण;

क्रमागत pvrdma_sig_type अणु
	PVRDMA_SIGNAL_ALL_WR,
	PVRDMA_SIGNAL_REQ_WR,
पूर्ण;

क्रमागत pvrdma_qp_type अणु
	PVRDMA_QPT_SMI,
	PVRDMA_QPT_GSI,
	PVRDMA_QPT_RC,
	PVRDMA_QPT_UC,
	PVRDMA_QPT_UD,
	PVRDMA_QPT_RAW_IPV6,
	PVRDMA_QPT_RAW_ETHERTYPE,
	PVRDMA_QPT_RAW_PACKET = 8,
	PVRDMA_QPT_XRC_INI = 9,
	PVRDMA_QPT_XRC_TGT,
	PVRDMA_QPT_MAX,
पूर्ण;

क्रमागत pvrdma_qp_create_flags अणु
	PVRDMA_QP_CREATE_IPOPVRDMA_UD_LSO		= 1 << 0,
	PVRDMA_QP_CREATE_BLOCK_MULTICAST_LOOPBACK	= 1 << 1,
पूर्ण;

क्रमागत pvrdma_qp_attr_mask अणु
	PVRDMA_QP_STATE			= 1 << 0,
	PVRDMA_QP_CUR_STATE		= 1 << 1,
	PVRDMA_QP_EN_SQD_ASYNC_NOTIFY	= 1 << 2,
	PVRDMA_QP_ACCESS_FLAGS		= 1 << 3,
	PVRDMA_QP_PKEY_INDEX		= 1 << 4,
	PVRDMA_QP_PORT			= 1 << 5,
	PVRDMA_QP_QKEY			= 1 << 6,
	PVRDMA_QP_AV			= 1 << 7,
	PVRDMA_QP_PATH_MTU		= 1 << 8,
	PVRDMA_QP_TIMEOUT		= 1 << 9,
	PVRDMA_QP_RETRY_CNT		= 1 << 10,
	PVRDMA_QP_RNR_RETRY		= 1 << 11,
	PVRDMA_QP_RQ_PSN		= 1 << 12,
	PVRDMA_QP_MAX_QP_RD_ATOMIC	= 1 << 13,
	PVRDMA_QP_ALT_PATH		= 1 << 14,
	PVRDMA_QP_MIN_RNR_TIMER		= 1 << 15,
	PVRDMA_QP_SQ_PSN		= 1 << 16,
	PVRDMA_QP_MAX_DEST_RD_ATOMIC	= 1 << 17,
	PVRDMA_QP_PATH_MIG_STATE	= 1 << 18,
	PVRDMA_QP_CAP			= 1 << 19,
	PVRDMA_QP_DEST_QPN		= 1 << 20,
	PVRDMA_QP_ATTR_MASK_MAX		= PVRDMA_QP_DEST_QPN,
पूर्ण;

क्रमागत pvrdma_qp_state अणु
	PVRDMA_QPS_RESET,
	PVRDMA_QPS_INIT,
	PVRDMA_QPS_RTR,
	PVRDMA_QPS_RTS,
	PVRDMA_QPS_SQD,
	PVRDMA_QPS_SQE,
	PVRDMA_QPS_ERR,
पूर्ण;

क्रमागत pvrdma_mig_state अणु
	PVRDMA_MIG_MIGRATED,
	PVRDMA_MIG_REARM,
	PVRDMA_MIG_ARMED,
पूर्ण;

क्रमागत pvrdma_mw_type अणु
	PVRDMA_MW_TYPE_1 = 1,
	PVRDMA_MW_TYPE_2 = 2,
पूर्ण;

काष्ठा pvrdma_srq_attr अणु
	u32			max_wr;
	u32			max_sge;
	u32			srq_limit;
	u32			reserved;
पूर्ण;

काष्ठा pvrdma_qp_attr अणु
	क्रमागत pvrdma_qp_state	qp_state;
	क्रमागत pvrdma_qp_state	cur_qp_state;
	क्रमागत pvrdma_mtu		path_mtu;
	क्रमागत pvrdma_mig_state	path_mig_state;
	u32			qkey;
	u32			rq_psn;
	u32			sq_psn;
	u32			dest_qp_num;
	u32			qp_access_flags;
	u16			pkey_index;
	u16			alt_pkey_index;
	u8			en_sqd_async_notअगरy;
	u8			sq_draining;
	u8			max_rd_atomic;
	u8			max_dest_rd_atomic;
	u8			min_rnr_समयr;
	u8			port_num;
	u8			समयout;
	u8			retry_cnt;
	u8			rnr_retry;
	u8			alt_port_num;
	u8			alt_समयout;
	u8			reserved[5];
	काष्ठा pvrdma_qp_cap	cap;
	काष्ठा pvrdma_ah_attr	ah_attr;
	काष्ठा pvrdma_ah_attr	alt_ah_attr;
पूर्ण;

क्रमागत pvrdma_send_flags अणु
	PVRDMA_SEND_FENCE	= 1 << 0,
	PVRDMA_SEND_SIGNALED	= 1 << 1,
	PVRDMA_SEND_SOLICITED	= 1 << 2,
	PVRDMA_SEND_INLINE	= 1 << 3,
	PVRDMA_SEND_IP_CSUM	= 1 << 4,
	PVRDMA_SEND_FLAGS_MAX	= PVRDMA_SEND_IP_CSUM,
पूर्ण;

क्रमागत pvrdma_access_flags अणु
	PVRDMA_ACCESS_LOCAL_WRITE	= 1 << 0,
	PVRDMA_ACCESS_REMOTE_WRITE	= 1 << 1,
	PVRDMA_ACCESS_REMOTE_READ	= 1 << 2,
	PVRDMA_ACCESS_REMOTE_ATOMIC	= 1 << 3,
	PVRDMA_ACCESS_MW_BIND		= 1 << 4,
	PVRDMA_ZERO_BASED		= 1 << 5,
	PVRDMA_ACCESS_ON_DEMAND		= 1 << 6,
	PVRDMA_ACCESS_FLAGS_MAX		= PVRDMA_ACCESS_ON_DEMAND,
पूर्ण;

पूर्णांक pvrdma_query_device(काष्ठा ib_device *ibdev,
			काष्ठा ib_device_attr *props,
			काष्ठा ib_udata *udata);
पूर्णांक pvrdma_query_port(काष्ठा ib_device *ibdev, u32 port,
		      काष्ठा ib_port_attr *props);
पूर्णांक pvrdma_query_gid(काष्ठा ib_device *ibdev, u32 port,
		     पूर्णांक index, जोड़ ib_gid *gid);
पूर्णांक pvrdma_query_pkey(काष्ठा ib_device *ibdev, u32 port,
		      u16 index, u16 *pkey);
क्रमागत rdma_link_layer pvrdma_port_link_layer(काष्ठा ib_device *ibdev,
					    u32 port);
पूर्णांक pvrdma_modअगरy_device(काष्ठा ib_device *ibdev, पूर्णांक mask,
			 काष्ठा ib_device_modअगरy *props);
पूर्णांक pvrdma_modअगरy_port(काष्ठा ib_device *ibdev, u32 port,
		       पूर्णांक mask, काष्ठा ib_port_modअगरy *props);
पूर्णांक pvrdma_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक pvrdma_alloc_ucontext(काष्ठा ib_ucontext *uctx, काष्ठा ib_udata *udata);
व्योम pvrdma_dealloc_ucontext(काष्ठा ib_ucontext *context);
पूर्णांक pvrdma_alloc_pd(काष्ठा ib_pd *pd, काष्ठा ib_udata *udata);
पूर्णांक pvrdma_dealloc_pd(काष्ठा ib_pd *ibpd, काष्ठा ib_udata *udata);
काष्ठा ib_mr *pvrdma_get_dma_mr(काष्ठा ib_pd *pd, पूर्णांक acc);
काष्ठा ib_mr *pvrdma_reg_user_mr(काष्ठा ib_pd *pd, u64 start, u64 length,
				 u64 virt_addr, पूर्णांक access_flags,
				 काष्ठा ib_udata *udata);
पूर्णांक pvrdma_dereg_mr(काष्ठा ib_mr *mr, काष्ठा ib_udata *udata);
काष्ठा ib_mr *pvrdma_alloc_mr(काष्ठा ib_pd *pd, क्रमागत ib_mr_type mr_type,
			      u32 max_num_sg);
पूर्णांक pvrdma_map_mr_sg(काष्ठा ib_mr *ibmr, काष्ठा scatterlist *sg,
		     पूर्णांक sg_nents, अचिन्हित पूर्णांक *sg_offset);
पूर्णांक pvrdma_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		     काष्ठा ib_udata *udata);
पूर्णांक pvrdma_destroy_cq(काष्ठा ib_cq *cq, काष्ठा ib_udata *udata);
पूर्णांक pvrdma_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक pvrdma_req_notअगरy_cq(काष्ठा ib_cq *cq, क्रमागत ib_cq_notअगरy_flags flags);
पूर्णांक pvrdma_create_ah(काष्ठा ib_ah *ah, काष्ठा rdma_ah_init_attr *init_attr,
		     काष्ठा ib_udata *udata);
पूर्णांक pvrdma_destroy_ah(काष्ठा ib_ah *ah, u32 flags);

पूर्णांक pvrdma_create_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_init_attr *init_attr,
		      काष्ठा ib_udata *udata);
पूर्णांक pvrdma_modअगरy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_srq_attr *attr,
		      क्रमागत ib_srq_attr_mask attr_mask, काष्ठा ib_udata *udata);
पूर्णांक pvrdma_query_srq(काष्ठा ib_srq *srq, काष्ठा ib_srq_attr *srq_attr);
पूर्णांक pvrdma_destroy_srq(काष्ठा ib_srq *srq, काष्ठा ib_udata *udata);

काष्ठा ib_qp *pvrdma_create_qp(काष्ठा ib_pd *pd,
			       काष्ठा ib_qp_init_attr *init_attr,
			       काष्ठा ib_udata *udata);
पूर्णांक pvrdma_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		     पूर्णांक attr_mask, काष्ठा ib_udata *udata);
पूर्णांक pvrdma_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *qp_attr,
		    पूर्णांक qp_attr_mask, काष्ठा ib_qp_init_attr *qp_init_attr);
पूर्णांक pvrdma_destroy_qp(काष्ठा ib_qp *qp, काष्ठा ib_udata *udata);
पूर्णांक pvrdma_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		     स्थिर काष्ठा ib_send_wr **bad_wr);
पूर्णांक pvrdma_post_recv(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		     स्थिर काष्ठा ib_recv_wr **bad_wr);

#पूर्ण_अगर /* __PVRDMA_VERBS_H__ */
