<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित _HNS_DSAF_RCB_H
#घोषणा _HNS_DSAF_RCB_H

#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "hnae.h"
#समावेश "hns_dsaf_main.h"

काष्ठा rcb_common_cb;

#घोषणा HNS_RCB_IRQ_NUM_PER_QUEUE		2
#घोषणा HNS_RCB_IRQ_IDX_TX			0
#घोषणा HNS_RCB_IRQ_IDX_RX			1
#घोषणा HNS_RCB_TX_REG_OFFSET			0x40

#घोषणा HNS_RCB_SERVICE_NW_ENGINE_NUM		DSAF_COMM_CHN
#घोषणा HNS_RCB_DEBUG_NW_ENGINE_NUM		1
#घोषणा HNS_RCB_RING_MAX_BD_PER_PKT		3
#घोषणा HNS_RCB_RING_MAX_TXBD_PER_PKT		3
#घोषणा HNS_RCBV2_RING_MAX_TXBD_PER_PKT		8
#घोषणा HNS_RCB_MAX_PKT_SIZE MAC_MAX_MTU

#घोषणा HNS_RCB_RING_MAX_PENDING_BD		1024
#घोषणा HNS_RCB_RING_MIN_PENDING_BD		16

#घोषणा HNS_RCB_REG_OFFSET			0x10000

#घोषणा HNS_RCB_TX_FRAMES_LOW		1
#घोषणा HNS_RCB_RX_FRAMES_LOW		1
#घोषणा HNS_RCB_TX_FRAMES_HIGH		1023
#घोषणा HNS_RCB_RX_FRAMES_HIGH		1023
#घोषणा HNS_RCB_TX_USECS_LOW		1
#घोषणा HNS_RCB_RX_USECS_LOW		1
#घोषणा HNS_RCB_TX_USECS_HIGH		1023
#घोषणा HNS_RCB_RX_USECS_HIGH		1023
#घोषणा HNS_RCB_MAX_COALESCED_FRAMES		1023
#घोषणा HNS_RCB_MIN_COALESCED_FRAMES		1
#घोषणा HNS_RCB_DEF_RX_COALESCED_FRAMES		50
#घोषणा HNS_RCB_DEF_TX_COALESCED_FRAMES		1
#घोषणा HNS_RCB_CLK_FREQ_MHZ			350
#घोषणा HNS_RCB_MAX_COALESCED_USECS		0x3ff
#घोषणा HNS_RCB_DEF_COALESCED_USECS		30
#घोषणा HNS_RCB_DEF_GAP_TIME_USECS		20
#घोषणा HNS_RCB_TX_PKTLINE_OFFSET		8

#घोषणा HNS_RCB_COMMON_ENDIAN			1

#घोषणा HNS_BD_SIZE_512_TYPE			0
#घोषणा HNS_BD_SIZE_1024_TYPE			1
#घोषणा HNS_BD_SIZE_2048_TYPE			2
#घोषणा HNS_BD_SIZE_4096_TYPE			3

#घोषणा HNS_RCB_COMMON_DUMP_REG_NUM 80
#घोषणा HNS_RCB_RING_DUMP_REG_NUM 40
#घोषणा HNS_RING_STATIC_REG_NUM 28

#घोषणा HNS_DUMP_REG_NUM			500
#घोषणा HNS_STATIC_REG_NUM			12

#घोषणा HNS_TSO_MODE_8BD_32K			1
#घोषणा HNS_TSO_MDOE_4BD_16K			0

क्रमागत rcb_पूर्णांक_flag अणु
	RCB_INT_FLAG_TX = 0x1,
	RCB_INT_FLAG_RX = (0x1 << 1),
	RCB_INT_FLAG_MAX = (0x1 << 2),	/*must be the last element */
पूर्ण;

काष्ठा hns_ring_hw_stats अणु
	u64 tx_pkts;
	u64 ppe_tx_ok_pkts;
	u64 ppe_tx_drop_pkts;
	u64 rx_pkts;
	u64 ppe_rx_ok_pkts;
	u64 ppe_rx_drop_pkts;
पूर्ण;

काष्ठा ring_pair_cb अणु
	काष्ठा rcb_common_cb *rcb_common;	/*  ring beदीर्घs to */
	काष्ठा device *dev;	/*device क्रम DMA mapping */
	काष्ठा hnae_queue q;

	u16 index;	/* global index in a rcb common device */
	u16 buf_size;

	पूर्णांक virq[HNS_RCB_IRQ_NUM_PER_QUEUE];

	u8 port_id_in_comm;
	u8 used_by_vf;

	काष्ठा hns_ring_hw_stats hw_stats;
पूर्ण;

काष्ठा rcb_common_cb अणु
	u8 __iomem *io_base;
	phys_addr_t phy_base;
	काष्ठा dsaf_device *dsaf_dev;
	u16 max_vfn;
	u16 max_q_per_vf;

	u8 comm_index;
	u32 ring_num;
	u32 desc_num; /*  desc num per queue*/

	काष्ठा ring_pair_cb ring_pair_cb[];
पूर्ण;

पूर्णांक hns_rcb_buf_size2type(u32 buf_size);

पूर्णांक hns_rcb_common_get_cfg(काष्ठा dsaf_device *dsaf_dev, पूर्णांक comm_index);
व्योम hns_rcb_common_मुक्त_cfg(काष्ठा dsaf_device *dsaf_dev, u32 comm_index);
पूर्णांक hns_rcb_common_init_hw(काष्ठा rcb_common_cb *rcb_common);
व्योम hns_rcb_start(काष्ठा hnae_queue *q, u32 val);
पूर्णांक hns_rcb_get_cfg(काष्ठा rcb_common_cb *rcb_common);
व्योम hns_rcb_get_queue_mode(क्रमागत dsaf_mode dsaf_mode,
			    u16 *max_vfn, u16 *max_q_per_vf);

व्योम hns_rcb_common_init_commit_hw(काष्ठा rcb_common_cb *rcb_common);

व्योम hns_rcb_ring_enable_hw(काष्ठा hnae_queue *q, u32 val);
व्योम hns_rcb_पूर्णांक_clr_hw(काष्ठा hnae_queue *q, u32 flag);
व्योम hns_rcb_पूर्णांक_ctrl_hw(काष्ठा hnae_queue *q, u32 flag, u32 enable);
व्योम hns_rcbv2_पूर्णांक_ctrl_hw(काष्ठा hnae_queue *q, u32 flag, u32 mask);
व्योम hns_rcbv2_पूर्णांक_clr_hw(काष्ठा hnae_queue *q, u32 flag);

व्योम hns_rcb_init_hw(काष्ठा ring_pair_cb *ring);
व्योम hns_rcb_reset_ring_hw(काष्ठा hnae_queue *q);
व्योम hns_rcb_रुको_fbd_clean(काष्ठा hnae_queue **qs, पूर्णांक q_num, u32 flag);
पूर्णांक hns_rcb_रुको_tx_ring_clean(काष्ठा hnae_queue *qs);
u32 hns_rcb_get_rx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx);
u32 hns_rcb_get_tx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx);
u32 hns_rcb_get_coalesce_usecs(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx);
पूर्णांक hns_rcb_set_coalesce_usecs(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 समयout);
पूर्णांक hns_rcb_set_rx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames);
पूर्णांक hns_rcb_set_tx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames);
व्योम hns_rcb_update_stats(काष्ठा hnae_queue *queue);

व्योम hns_rcb_get_stats(काष्ठा hnae_queue *queue, u64 *data);

व्योम hns_rcb_get_common_regs(काष्ठा rcb_common_cb *rcb_common, व्योम *data);

पूर्णांक hns_rcb_get_ring_sset_count(पूर्णांक stringset);
पूर्णांक hns_rcb_get_common_regs_count(व्योम);
पूर्णांक hns_rcb_get_ring_regs_count(व्योम);

व्योम hns_rcb_get_ring_regs(काष्ठा hnae_queue *queue, व्योम *data);

व्योम hns_rcb_get_strings(पूर्णांक stringset, u8 *data, पूर्णांक index);
व्योम hns_rcb_set_rx_ring_bs(काष्ठा hnae_queue *q, u32 buf_size);
व्योम hns_rcb_set_tx_ring_bs(काष्ठा hnae_queue *q, u32 buf_size);

#पूर्ण_अगर /* _HNS_DSAF_RCB_H */
