<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_ETH_IF_H
#घोषणा _QED_ETH_IF_H

#समावेश <linux/list.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/qed/eth_common.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_iov_अगर.h>

/* 64 max queues * (1 rx + 4 tx-cos + 1 xdp) */
#घोषणा QED_MIN_L2_CONS (2 + NUM_PHYS_TCS_4PORT_K2)
#घोषणा QED_MAX_L2_CONS (64 * (QED_MIN_L2_CONS))

काष्ठा qed_queue_start_common_params अणु
	/* Should always be relative to entity sending this. */
	u8 vport_id;
	u16 queue_id;

	/* Relative, but relevant only क्रम PFs */
	u8 stats_id;

	काष्ठा qed_sb_info *p_sb;
	u8 sb_idx;

	u8 tc;
पूर्ण;

काष्ठा qed_rxq_start_ret_params अणु
	व्योम __iomem *p_prod;
	व्योम *p_handle;
पूर्ण;

काष्ठा qed_txq_start_ret_params अणु
	व्योम __iomem *p_करोorbell;
	व्योम *p_handle;
पूर्ण;

क्रमागत qed_filter_config_mode अणु
	QED_FILTER_CONFIG_MODE_DISABLE,
	QED_FILTER_CONFIG_MODE_5_TUPLE,
	QED_FILTER_CONFIG_MODE_L4_PORT,
	QED_FILTER_CONFIG_MODE_IP_DEST,
	QED_FILTER_CONFIG_MODE_IP_SRC,
पूर्ण;

काष्ठा qed_ntuple_filter_params अणु
	/* Physically mapped address containing header of buffer to be used
	 * as filter.
	 */
	dma_addr_t addr;

	/* Length of header in bytes */
	u16 length;

	/* Relative queue-id to receive classअगरied packet */
#घोषणा QED_RFS_NTUPLE_QID_RSS ((u16)-1)
	u16 qid;

	/* Identअगरier can either be according to vport-id or vfid */
	bool b_is_vf;
	u8 vport_id;
	u8 vf_id;

	/* true अगरf this filter is to be added. Else to be हटाओd */
	bool b_is_add;

	/* If flow needs to be dropped */
	bool b_is_drop;
पूर्ण;

काष्ठा qed_dev_eth_info अणु
	काष्ठा qed_dev_info common;

	u8	num_queues;
	u8	num_tc;

	u8	port_mac[ETH_ALEN];
	u16	num_vlan_filters;
	u16	num_mac_filters;

	/* Legacy VF - this affects the datapath, so qede has to know */
	bool is_legacy;

	/* Might depend on available resources [in हाल of VF] */
	bool xdp_supported;
पूर्ण;

काष्ठा qed_update_vport_rss_params अणु
	व्योम	*rss_ind_table[128];
	u32	rss_key[10];
	u8	rss_caps;
पूर्ण;

काष्ठा qed_update_vport_params अणु
	u8 vport_id;
	u8 update_vport_active_flg;
	u8 vport_active_flg;
	u8 update_tx_चयनing_flg;
	u8 tx_चयनing_flg;
	u8 update_accept_any_vlan_flg;
	u8 accept_any_vlan;
	u8 update_rss_flg;
	काष्ठा qed_update_vport_rss_params rss_params;
पूर्ण;

काष्ठा qed_start_vport_params अणु
	bool हटाओ_inner_vlan;
	bool handle_ptp_pkts;
	bool gro_enable;
	bool drop_ttl0;
	u8 vport_id;
	u16 mtu;
	bool clear_stats;
पूर्ण;

क्रमागत qed_filter_rx_mode_type अणु
	QED_FILTER_RX_MODE_TYPE_REGULAR,
	QED_FILTER_RX_MODE_TYPE_MULTI_PROMISC,
	QED_FILTER_RX_MODE_TYPE_PROMISC,
पूर्ण;

क्रमागत qed_filter_xcast_params_type अणु
	QED_FILTER_XCAST_TYPE_ADD,
	QED_FILTER_XCAST_TYPE_DEL,
	QED_FILTER_XCAST_TYPE_REPLACE,
पूर्ण;

काष्ठा qed_filter_ucast_params अणु
	क्रमागत qed_filter_xcast_params_type type;
	u8 vlan_valid;
	u16 vlan;
	u8 mac_valid;
	अचिन्हित अक्षर mac[ETH_ALEN];
पूर्ण;

काष्ठा qed_filter_mcast_params अणु
	क्रमागत qed_filter_xcast_params_type type;
	u8 num;
	अचिन्हित अक्षर mac[64][ETH_ALEN];
पूर्ण;

जोड़ qed_filter_type_params अणु
	क्रमागत qed_filter_rx_mode_type accept_flags;
	काष्ठा qed_filter_ucast_params ucast;
	काष्ठा qed_filter_mcast_params mcast;
पूर्ण;

क्रमागत qed_filter_type अणु
	QED_FILTER_TYPE_UCAST,
	QED_FILTER_TYPE_MCAST,
	QED_FILTER_TYPE_RX_MODE,
	QED_MAX_FILTER_TYPES,
पूर्ण;

काष्ठा qed_filter_params अणु
	क्रमागत qed_filter_type type;
	जोड़ qed_filter_type_params filter;
पूर्ण;

काष्ठा qed_tunn_params अणु
	u16 vxlan_port;
	u8 update_vxlan_port;
	u16 geneve_port;
	u8 update_geneve_port;
पूर्ण;

काष्ठा qed_eth_cb_ops अणु
	काष्ठा qed_common_cb_ops common;
	व्योम (*क्रमce_mac) (व्योम *dev, u8 *mac, bool क्रमced);
	व्योम (*ports_update)(व्योम *dev, u16 vxlan_port, u16 geneve_port);
पूर्ण;

#घोषणा QED_MAX_PHC_DRIFT_PPB   291666666

क्रमागत qed_ptp_filter_type अणु
	QED_PTP_FILTER_NONE,
	QED_PTP_FILTER_ALL,
	QED_PTP_FILTER_V1_L4_EVENT,
	QED_PTP_FILTER_V1_L4_GEN,
	QED_PTP_FILTER_V2_L4_EVENT,
	QED_PTP_FILTER_V2_L4_GEN,
	QED_PTP_FILTER_V2_L2_EVENT,
	QED_PTP_FILTER_V2_L2_GEN,
	QED_PTP_FILTER_V2_EVENT,
	QED_PTP_FILTER_V2_GEN
पूर्ण;

क्रमागत qed_ptp_hwtstamp_tx_type अणु
	QED_PTP_HWTSTAMP_TX_OFF,
	QED_PTP_HWTSTAMP_TX_ON,
पूर्ण;

#अगर_घोषित CONFIG_DCB
/* Prototype declaration of qed_eth_dcbnl_ops should match with the declaration
 * of dcbnl_rtnl_ops काष्ठाure.
 */
काष्ठा qed_eth_dcbnl_ops अणु
	/* IEEE 802.1Qaz std */
	पूर्णांक (*ieee_getpfc)(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc);
	पूर्णांक (*ieee_setpfc)(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc);
	पूर्णांक (*ieee_getets)(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets);
	पूर्णांक (*ieee_setets)(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets);
	पूर्णांक (*ieee_peer_getets)(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets);
	पूर्णांक (*ieee_peer_getpfc)(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc);
	पूर्णांक (*ieee_getapp)(काष्ठा qed_dev *cdev, काष्ठा dcb_app *app);
	पूर्णांक (*ieee_setapp)(काष्ठा qed_dev *cdev, काष्ठा dcb_app *app);

	/* CEE std */
	u8 (*माला_लोtate)(काष्ठा qed_dev *cdev);
	u8 (*setstate)(काष्ठा qed_dev *cdev, u8 state);
	व्योम (*getpgtccfgtx)(काष्ठा qed_dev *cdev, पूर्णांक prio, u8 *prio_type,
			     u8 *pgid, u8 *bw_pct, u8 *up_map);
	व्योम (*getpgbwgcfgtx)(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 *bw_pct);
	व्योम (*getpgtccfgrx)(काष्ठा qed_dev *cdev, पूर्णांक prio, u8 *prio_type,
			     u8 *pgid, u8 *bw_pct, u8 *up_map);
	व्योम (*getpgbwgcfgrx)(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 *bw_pct);
	व्योम (*getpfccfg)(काष्ठा qed_dev *cdev, पूर्णांक prio, u8 *setting);
	व्योम (*setpfccfg)(काष्ठा qed_dev *cdev, पूर्णांक prio, u8 setting);
	u8 (*अ_लोap)(काष्ठा qed_dev *cdev, पूर्णांक capid, u8 *cap);
	पूर्णांक (*getnumtcs)(काष्ठा qed_dev *cdev, पूर्णांक tcid, u8 *num);
	u8 (*getpfcstate)(काष्ठा qed_dev *cdev);
	पूर्णांक (*getapp)(काष्ठा qed_dev *cdev, u8 idtype, u16 id);
	u8 (*getfeatcfg)(काष्ठा qed_dev *cdev, पूर्णांक featid, u8 *flags);

	/* DCBX configuration */
	u8 (*getdcbx)(काष्ठा qed_dev *cdev);
	व्योम (*setpgtccfgtx)(काष्ठा qed_dev *cdev, पूर्णांक prio,
			     u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map);
	व्योम (*setpgtccfgrx)(काष्ठा qed_dev *cdev, पूर्णांक prio,
			     u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map);
	व्योम (*setpgbwgcfgtx)(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 bw_pct);
	व्योम (*setpgbwgcfgrx)(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 bw_pct);
	u8 (*setall)(काष्ठा qed_dev *cdev);
	पूर्णांक (*setnumtcs)(काष्ठा qed_dev *cdev, पूर्णांक tcid, u8 num);
	व्योम (*setpfcstate)(काष्ठा qed_dev *cdev, u8 state);
	पूर्णांक (*setapp)(काष्ठा qed_dev *cdev, u8 idtype, u16 idval, u8 up);
	u8 (*setdcbx)(काष्ठा qed_dev *cdev, u8 state);
	u8 (*setfeatcfg)(काष्ठा qed_dev *cdev, पूर्णांक featid, u8 flags);

	/* Peer apps */
	पूर्णांक (*peer_getappinfo)(काष्ठा qed_dev *cdev,
			       काष्ठा dcb_peer_app_info *info,
			       u16 *app_count);
	पूर्णांक (*peer_getapptable)(काष्ठा qed_dev *cdev, काष्ठा dcb_app *table);

	/* CEE peer */
	पूर्णांक (*cee_peer_getpfc)(काष्ठा qed_dev *cdev, काष्ठा cee_pfc *pfc);
	पूर्णांक (*cee_peer_getpg)(काष्ठा qed_dev *cdev, काष्ठा cee_pg *pg);
पूर्ण;
#पूर्ण_अगर

काष्ठा qed_eth_ptp_ops अणु
	पूर्णांक (*cfg_filters)(काष्ठा qed_dev *, क्रमागत qed_ptp_filter_type,
			   क्रमागत qed_ptp_hwtstamp_tx_type);
	पूर्णांक (*पढ़ो_rx_ts)(काष्ठा qed_dev *, u64 *);
	पूर्णांक (*पढ़ो_tx_ts)(काष्ठा qed_dev *, u64 *);
	पूर्णांक (*पढ़ो_cc)(काष्ठा qed_dev *, u64 *);
	पूर्णांक (*disable)(काष्ठा qed_dev *);
	पूर्णांक (*adjfreq)(काष्ठा qed_dev *, s32);
	पूर्णांक (*enable)(काष्ठा qed_dev *);
पूर्ण;

काष्ठा qed_eth_ops अणु
	स्थिर काष्ठा qed_common_ops *common;
#अगर_घोषित CONFIG_QED_SRIOV
	स्थिर काष्ठा qed_iov_hv_ops *iov;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DCB
	स्थिर काष्ठा qed_eth_dcbnl_ops *dcb;
#पूर्ण_अगर
	स्थिर काष्ठा qed_eth_ptp_ops *ptp;

	पूर्णांक (*fill_dev_info)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_dev_eth_info *info);

	व्योम (*रेजिस्टर_ops)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_eth_cb_ops *ops,
			     व्योम *cookie);

	 bool(*check_mac) (काष्ठा qed_dev *cdev, u8 *mac);

	पूर्णांक (*vport_start)(काष्ठा qed_dev *cdev,
			   काष्ठा qed_start_vport_params *params);

	पूर्णांक (*vport_stop)(काष्ठा qed_dev *cdev,
			  u8 vport_id);

	पूर्णांक (*vport_update)(काष्ठा qed_dev *cdev,
			    काष्ठा qed_update_vport_params *params);

	पूर्णांक (*q_rx_start)(काष्ठा qed_dev *cdev,
			  u8 rss_num,
			  काष्ठा qed_queue_start_common_params *params,
			  u16 bd_max_bytes,
			  dma_addr_t bd_chain_phys_addr,
			  dma_addr_t cqe_pbl_addr,
			  u16 cqe_pbl_size,
			  काष्ठा qed_rxq_start_ret_params *ret_params);

	पूर्णांक (*q_rx_stop)(काष्ठा qed_dev *cdev, u8 rss_id, व्योम *handle);

	पूर्णांक (*q_tx_start)(काष्ठा qed_dev *cdev,
			  u8 rss_num,
			  काष्ठा qed_queue_start_common_params *params,
			  dma_addr_t pbl_addr,
			  u16 pbl_size,
			  काष्ठा qed_txq_start_ret_params *ret_params);

	पूर्णांक (*q_tx_stop)(काष्ठा qed_dev *cdev, u8 rss_id, व्योम *handle);

	पूर्णांक (*filter_config)(काष्ठा qed_dev *cdev,
			     काष्ठा qed_filter_params *params);

	पूर्णांक (*fastpath_stop)(काष्ठा qed_dev *cdev);

	पूर्णांक (*eth_cqe_completion)(काष्ठा qed_dev *cdev,
				  u8 rss_id,
				  काष्ठा eth_slow_path_rx_cqe *cqe);

	व्योम (*get_vport_stats)(काष्ठा qed_dev *cdev,
				काष्ठा qed_eth_stats *stats);

	पूर्णांक (*tunn_config)(काष्ठा qed_dev *cdev,
			   काष्ठा qed_tunn_params *params);

	पूर्णांक (*ntuple_filter_config)(काष्ठा qed_dev *cdev,
				    व्योम *cookie,
				    काष्ठा qed_ntuple_filter_params *params);

	पूर्णांक (*configure_arfs_searcher)(काष्ठा qed_dev *cdev,
				       क्रमागत qed_filter_config_mode mode);
	पूर्णांक (*get_coalesce)(काष्ठा qed_dev *cdev, u16 *coal, व्योम *handle);
	पूर्णांक (*req_bulletin_update_mac)(काष्ठा qed_dev *cdev, u8 *mac);
पूर्ण;

स्थिर काष्ठा qed_eth_ops *qed_get_eth_ops(व्योम);
व्योम qed_put_eth_ops(व्योम);

#पूर्ण_अगर
