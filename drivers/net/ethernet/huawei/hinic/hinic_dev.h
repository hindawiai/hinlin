<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_DEV_H
#घोषणा HINIC_DEV_H

#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/bitops.h>

#समावेश "hinic_hw_dev.h"
#समावेश "hinic_tx.h"
#समावेश "hinic_rx.h"
#समावेश "hinic_sriov.h"

#घोषणा HINIC_DRV_NAME          "hinic"

#घोषणा LP_PKT_CNT		64

क्रमागत hinic_flags अणु
	HINIC_LINK_UP = BIT(0),
	HINIC_INTF_UP = BIT(1),
	HINIC_RSS_ENABLE = BIT(2),
	HINIC_LINK_DOWN = BIT(3),
	HINIC_LP_TEST = BIT(4),
पूर्ण;

काष्ठा hinic_rx_mode_work अणु
	काष्ठा work_काष्ठा      work;
	u32                     rx_mode;
पूर्ण;

काष्ठा hinic_rss_type अणु
	u8 tcp_ipv6_ext;
	u8 ipv6_ext;
	u8 tcp_ipv6;
	u8 ipv6;
	u8 tcp_ipv4;
	u8 ipv4;
	u8 udp_ipv6;
	u8 udp_ipv4;
पूर्ण;

क्रमागत hinic_rss_hash_type अणु
	HINIC_RSS_HASH_ENGINE_TYPE_XOR,
	HINIC_RSS_HASH_ENGINE_TYPE_TOEP,
	HINIC_RSS_HASH_ENGINE_TYPE_MAX,
पूर्ण;

काष्ठा hinic_पूर्णांकr_coal_info अणु
	u8	pending_limt;
	u8	coalesce_समयr_cfg;
	u8	resend_समयr_cfg;
पूर्ण;

क्रमागत hinic_dbg_type अणु
	HINIC_DBG_SQ_INFO,
	HINIC_DBG_RQ_INFO,
	HINIC_DBG_FUNC_TABLE,
पूर्ण;

काष्ठा hinic_debug_priv अणु
	काष्ठा hinic_dev	*dev;
	व्योम			*object;
	क्रमागत hinic_dbg_type	type;
	काष्ठा dentry		*root;
	पूर्णांक			field_id[64];
पूर्ण;

काष्ठा hinic_dev अणु
	काष्ठा net_device               *netdev;
	काष्ठा hinic_hwdev              *hwdev;

	u32                             msg_enable;
	अचिन्हित पूर्णांक                    tx_weight;
	अचिन्हित पूर्णांक                    rx_weight;
	u16				num_qps;
	u16				max_qps;

	अचिन्हित पूर्णांक                    flags;

	काष्ठा semaphore                mgmt_lock;
	अचिन्हित दीर्घ                   *vlan_biपंचांगap;

	काष्ठा hinic_rx_mode_work       rx_mode_work;
	काष्ठा workqueue_काष्ठा         *workq;

	काष्ठा hinic_txq                *txqs;
	काष्ठा hinic_rxq                *rxqs;
	u16				sq_depth;
	u16				rq_depth;

	काष्ठा hinic_txq_stats          tx_stats;
	काष्ठा hinic_rxq_stats          rx_stats;

	u8				rss_पंचांगpl_idx;
	u8				rss_hash_engine;
	u16				num_rss;
	u16				rss_limit;
	काष्ठा hinic_rss_type		rss_type;
	u8				*rss_hkey_user;
	s32				*rss_indir_user;
	काष्ठा hinic_पूर्णांकr_coal_info	*rx_पूर्णांकr_coalesce;
	काष्ठा hinic_पूर्णांकr_coal_info	*tx_पूर्णांकr_coalesce;
	काष्ठा hinic_sriov_info sriov_info;
	पूर्णांक				lb_test_rx_idx;
	पूर्णांक				lb_pkt_len;
	u8				*lb_test_rx_buf;

	काष्ठा dentry			*dbgfs_root;
	काष्ठा dentry			*sq_dbgfs;
	काष्ठा dentry			*rq_dbgfs;
	काष्ठा dentry			*func_tbl_dbgfs;
	काष्ठा hinic_debug_priv		*dbg;
	काष्ठा devlink			*devlink;
	bool				cable_unplugged;
	bool				module_unrecognized;
पूर्ण;

काष्ठा hinic_devlink_priv अणु
	काष्ठा hinic_hwdev		*hwdev;
	काष्ठा devlink_health_reporter  *hw_fault_reporter;
	काष्ठा devlink_health_reporter  *fw_fault_reporter;
पूर्ण;

#पूर्ण_अगर
