<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_RDMA_H
#घोषणा _QED_RDMA_H
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_rdma_अगर.h>
#समावेश "qed.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_hsi.h"
#समावेश "qed_iwarp.h"
#समावेश "qed_roce.h"

#घोषणा QED_RDMA_MAX_P_KEY                  (1)
#घोषणा QED_RDMA_MAX_WQE                    (0x7FFF)
#घोषणा QED_RDMA_MAX_SRQ_WQE_ELEM           (0x7FFF)
#घोषणा QED_RDMA_PAGE_SIZE_CAPS             (0xFFFFF000)
#घोषणा QED_RDMA_ACK_DELAY                  (15)
#घोषणा QED_RDMA_MAX_MR_SIZE                (0x10000000000ULL)
#घोषणा QED_RDMA_MAX_CQS                    (RDMA_MAX_CQS)
#घोषणा QED_RDMA_MAX_MRS                    (RDMA_MAX_TIDS)
/* Add 1 क्रम header element */
#घोषणा QED_RDMA_MAX_SRQ_ELEM_PER_WQE	    (RDMA_MAX_SGE_PER_RQ_WQE + 1)
#घोषणा QED_RDMA_MAX_SGE_PER_SRQ_WQE        (RDMA_MAX_SGE_PER_RQ_WQE)
#घोषणा QED_RDMA_SRQ_WQE_ELEM_SIZE          (16)
#घोषणा QED_RDMA_MAX_SRQS                   (32 * 1024)

#घोषणा QED_RDMA_MAX_CQE_32_BIT             (0x7FFFFFFF - 1)
#घोषणा QED_RDMA_MAX_CQE_16_BIT             (0x7FFF - 1)

/* Up to 2^16 XRC Doमुख्यs are supported, but the actual number of supported XRC
 * SRQs is much smaller so there's no need to have that many करोमुख्यs.
 */
#घोषणा QED_RDMA_MAX_XRCDS      (roundup_घात_of_two(RDMA_MAX_XRC_SRQS))

क्रमागत qed_rdma_toggle_bit अणु
	QED_RDMA_TOGGLE_BIT_CLEAR = 0,
	QED_RDMA_TOGGLE_BIT_SET = 1
पूर्ण;

#घोषणा QED_RDMA_MAX_BMAP_NAME	(10)
काष्ठा qed_bmap अणु
	अचिन्हित दीर्घ *biपंचांगap;
	u32 max_count;
	अक्षर name[QED_RDMA_MAX_BMAP_NAME];
पूर्ण;

काष्ठा qed_rdma_info अणु
	/* spin lock to protect biपंचांगaps */
	spinlock_t lock;

	काष्ठा qed_bmap cq_map;
	काष्ठा qed_bmap pd_map;
	काष्ठा qed_bmap xrcd_map;
	काष्ठा qed_bmap tid_map;
	काष्ठा qed_bmap qp_map;
	काष्ठा qed_bmap srq_map;
	काष्ठा qed_bmap xrc_srq_map;
	काष्ठा qed_bmap cid_map;
	काष्ठा qed_bmap tcp_cid_map;
	काष्ठा qed_bmap real_cid_map;
	काष्ठा qed_bmap dpi_map;
	काष्ठा qed_bmap toggle_bits;
	काष्ठा qed_rdma_events events;
	काष्ठा qed_rdma_device *dev;
	काष्ठा qed_rdma_port *port;
	u32 last_tid;
	u8 num_cnqs;
	u32 num_qps;
	u32 num_mrs;
	u32 num_srqs;
	u16 srq_id_offset;
	u16 queue_zone_base;
	u16 max_queue_zones;
	क्रमागत protocol_type proto;
	काष्ठा qed_iwarp_info iwarp;
	u8 active:1;
पूर्ण;

काष्ठा qed_rdma_qp अणु
	काष्ठा regpair qp_handle;
	काष्ठा regpair qp_handle_async;
	u32 qpid;
	u16 icid;
	क्रमागत qed_roce_qp_state cur_state;
	क्रमागत qed_rdma_qp_type qp_type;
	क्रमागत qed_iwarp_qp_state iwarp_state;
	bool use_srq;
	bool संकेत_all;
	bool fmr_and_reserved_lkey;

	bool incoming_rdma_पढ़ो_en;
	bool incoming_rdma_ग_लिखो_en;
	bool incoming_atomic_en;
	bool e2e_flow_control_en;

	u16 pd;
	u16 pkey;
	u32 dest_qp;
	u16 mtu;
	u16 srq_id;
	u8 traffic_class_tos;
	u8 hop_limit_ttl;
	u16 dpi;
	u32 flow_label;
	bool lb_indication;
	u16 vlan_id;
	u32 ack_समयout;
	u8 retry_cnt;
	u8 rnr_retry_cnt;
	u8 min_rnr_nak_समयr;
	bool sqd_async;
	जोड़ qed_gid sgid;
	जोड़ qed_gid dgid;
	क्रमागत roce_mode roce_mode;
	u16 udp_src_port;
	u8 stats_queue;

	/* requeseter */
	u8 max_rd_atomic_req;
	u32 sq_psn;
	u16 sq_cq_id;
	u16 sq_num_pages;
	dma_addr_t sq_pbl_ptr;
	व्योम *orq;
	dma_addr_t orq_phys_addr;
	u8 orq_num_pages;
	bool req_offloaded;
	bool has_req;

	/* responder */
	u8 max_rd_atomic_resp;
	u32 rq_psn;
	u16 rq_cq_id;
	u16 rq_num_pages;
	u16 xrcd_id;
	dma_addr_t rq_pbl_ptr;
	व्योम *irq;
	dma_addr_t irq_phys_addr;
	u8 irq_num_pages;
	bool resp_offloaded;
	u32 cq_prod;
	bool has_resp;

	u8 remote_mac_addr[6];
	u8 local_mac_addr[6];

	व्योम *shared_queue;
	dma_addr_t shared_queue_phys_addr;
	काष्ठा qed_iwarp_ep *ep;
	u8 edpm_mode;
पूर्ण;

अटल अंतरभूत bool qed_rdma_is_xrc_qp(काष्ठा qed_rdma_qp *qp)
अणु
	अगर (qp->qp_type == QED_RDMA_QP_TYPE_XRC_TGT ||
	    qp->qp_type == QED_RDMA_QP_TYPE_XRC_INI)
		वापस true;

	वापस false;
पूर्ण
#अगर IS_ENABLED(CONFIG_QED_RDMA)
व्योम qed_rdma_dpm_bar(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
व्योम qed_rdma_dpm_conf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
पूर्णांक qed_rdma_info_alloc(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_rdma_info_मुक्त(काष्ठा qed_hwfn *p_hwfn);
#अन्यथा
अटल अंतरभूत व्योम qed_rdma_dpm_conf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt) अणुपूर्ण
अटल अंतरभूत व्योम qed_rdma_dpm_bar(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt) अणुपूर्ण
अटल अंतरभूत पूर्णांक qed_rdma_info_alloc(काष्ठा qed_hwfn *p_hwfn) अणुवापस -EINVAL;पूर्ण
अटल अंतरभूत व्योम qed_rdma_info_मुक्त(काष्ठा qed_hwfn *p_hwfn) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक
qed_rdma_bmap_alloc(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_bmap *bmap, u32 max_count, अक्षर *name);

व्योम
qed_rdma_bmap_मुक्त(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_bmap *bmap, bool check);

पूर्णांक
qed_rdma_bmap_alloc_id(काष्ठा qed_hwfn *p_hwfn,
		       काष्ठा qed_bmap *bmap, u32 *id_num);

व्योम
qed_bmap_set_id(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_bmap *bmap, u32 id_num);

व्योम
qed_bmap_release_id(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_bmap *bmap, u32 id_num);

पूर्णांक
qed_bmap_test_id(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_bmap *bmap, u32 id_num);

व्योम qed_rdma_set_fw_mac(__le16 *p_fw_mac, स्थिर u8 *p_qed_mac);

bool qed_rdma_allocated_qps(काष्ठा qed_hwfn *p_hwfn);
#पूर्ण_अगर
