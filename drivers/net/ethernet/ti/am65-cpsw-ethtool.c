<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Texas Instruments K3 AM65 Ethernet Switch SubSystem Driver ethtool ops
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 */

#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "am65-cpsw-nuss.h"
#समावेश "cpsw_ale.h"
#समावेश "am65-cpts.h"

#घोषणा AM65_CPSW_REGDUMP_VER 0x1

क्रमागत अणु
	AM65_CPSW_REGDUMP_MOD_NUSS = 1,
	AM65_CPSW_REGDUMP_MOD_RGMII_STATUS = 2,
	AM65_CPSW_REGDUMP_MOD_MDIO = 3,
	AM65_CPSW_REGDUMP_MOD_CPSW = 4,
	AM65_CPSW_REGDUMP_MOD_CPSW_P0 = 5,
	AM65_CPSW_REGDUMP_MOD_CPSW_P1 = 6,
	AM65_CPSW_REGDUMP_MOD_CPSW_CPTS = 7,
	AM65_CPSW_REGDUMP_MOD_CPSW_ALE = 8,
	AM65_CPSW_REGDUMP_MOD_CPSW_ALE_TBL = 9,
	AM65_CPSW_REGDUMP_MOD_LAST,
पूर्ण;

/**
 * काष्ठा am65_cpsw_regdump_hdr - regdump record header
 *
 * @module_id: CPSW module ID
 * @len: CPSW module रेजिस्टरs space length in u32
 */

काष्ठा am65_cpsw_regdump_hdr अणु
	u32 module_id;
	u32 len;
पूर्ण;

/**
 * काष्ठा am65_cpsw_regdump_item - regdump module description
 *
 * @hdr: CPSW module header
 * @start_ofs: CPSW module रेजिस्टरs start addr
 * @end_ofs: CPSW module रेजिस्टरs end addr
 *
 * Registers dump provided in the क्रमmat:
 *  u32 : module ID
 *  u32 : dump length
 *  u32[..len]: रेजिस्टरs values
 */
काष्ठा am65_cpsw_regdump_item अणु
	काष्ठा am65_cpsw_regdump_hdr hdr;
	u32 start_ofs;
	u32 end_ofs;
पूर्ण;

#घोषणा AM65_CPSW_REGDUMP_REC(mod, start, end) अणु \
	.hdr.module_id = (mod), \
	.hdr.len = (((u32 *)(end)) - ((u32 *)(start)) + 1) * माप(u32) * 2 + \
		   माप(काष्ठा am65_cpsw_regdump_hdr), \
	.start_ofs = (start), \
	.end_ofs = end, \
पूर्ण

अटल स्थिर काष्ठा am65_cpsw_regdump_item am65_cpsw_regdump[] = अणु
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_NUSS, 0x0, 0x1c),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_RGMII_STATUS, 0x30, 0x4c),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_MDIO, 0xf00, 0xffc),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW, 0x20000, 0x2011c),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW_P0, 0x21000, 0x21320),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW_P1, 0x22000, 0x223a4),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW_CPTS,
			      0x3d000, 0x3d048),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW_ALE, 0x3e000, 0x3e13c),
	AM65_CPSW_REGDUMP_REC(AM65_CPSW_REGDUMP_MOD_CPSW_ALE_TBL, 0, 0),
पूर्ण;

काष्ठा am65_cpsw_stats_regs अणु
	u32	rx_good_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	rx_छोड़ो_frames;		/* slave */
	u32	rx_crc_errors;
	u32	rx_align_code_errors;		/* slave */
	u32	rx_oversized_frames;
	u32	rx_jabber_frames;		/* slave */
	u32	rx_undersized_frames;
	u32	rx_fragments;			/* slave */
	u32	ale_drop;
	u32	ale_overrun_drop;
	u32	rx_octets;
	u32	tx_good_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	tx_छोड़ो_frames;		/* slave */
	u32	tx_deferred_frames;		/* slave */
	u32	tx_collision_frames;		/* slave */
	u32	tx_single_coll_frames;		/* slave */
	u32	tx_mult_coll_frames;		/* slave */
	u32	tx_excessive_collisions;	/* slave */
	u32	tx_late_collisions;		/* slave */
	u32	rx_ipg_error;			/* slave 10G only */
	u32	tx_carrier_sense_errors;	/* slave */
	u32	tx_octets;
	u32	tx_64B_frames;
	u32	tx_65_to_127B_frames;
	u32	tx_128_to_255B_frames;
	u32	tx_256_to_511B_frames;
	u32	tx_512_to_1023B_frames;
	u32	tx_1024B_frames;
	u32	net_octets;
	u32	rx_bottom_fअगरo_drop;
	u32	rx_port_mask_drop;
	u32	rx_top_fअगरo_drop;
	u32	ale_rate_limit_drop;
	u32	ale_vid_ingress_drop;
	u32	ale_da_eq_sa_drop;
	u32	ale_block_drop;			/* K3 */
	u32	ale_secure_drop;		/* K3 */
	u32	ale_auth_drop;			/* K3 */
	u32	ale_unknown_ucast;
	u32	ale_unknown_ucast_bytes;
	u32	ale_unknown_mcast;
	u32	ale_unknown_mcast_bytes;
	u32	ale_unknown_bcast;
	u32	ale_unknown_bcast_bytes;
	u32	ale_pol_match;
	u32	ale_pol_match_red;
	u32	ale_pol_match_yellow;
	u32	ale_mcast_sa_drop;		/* K3 */
	u32	ale_dual_vlan_drop;		/* K3 */
	u32	ale_len_err_drop;		/* K3 */
	u32	ale_ip_next_hdr_drop;		/* K3 */
	u32	ale_ipv4_frag_drop;		/* K3 */
	u32	__rsvd_1[24];
	u32	iet_rx_assembly_err;		/* K3 slave */
	u32	iet_rx_assembly_ok;		/* K3 slave */
	u32	iet_rx_smd_err;			/* K3 slave */
	u32	iet_rx_frag;			/* K3 slave */
	u32	iet_tx_hold;			/* K3 slave */
	u32	iet_tx_frag;			/* K3 slave */
	u32	__rsvd_2[9];
	u32	tx_mem_protect_err;
	/* following NU only */
	u32	tx_pri0;
	u32	tx_pri1;
	u32	tx_pri2;
	u32	tx_pri3;
	u32	tx_pri4;
	u32	tx_pri5;
	u32	tx_pri6;
	u32	tx_pri7;
	u32	tx_pri0_bcnt;
	u32	tx_pri1_bcnt;
	u32	tx_pri2_bcnt;
	u32	tx_pri3_bcnt;
	u32	tx_pri4_bcnt;
	u32	tx_pri5_bcnt;
	u32	tx_pri6_bcnt;
	u32	tx_pri7_bcnt;
	u32	tx_pri0_drop;
	u32	tx_pri1_drop;
	u32	tx_pri2_drop;
	u32	tx_pri3_drop;
	u32	tx_pri4_drop;
	u32	tx_pri5_drop;
	u32	tx_pri6_drop;
	u32	tx_pri7_drop;
	u32	tx_pri0_drop_bcnt;
	u32	tx_pri1_drop_bcnt;
	u32	tx_pri2_drop_bcnt;
	u32	tx_pri3_drop_bcnt;
	u32	tx_pri4_drop_bcnt;
	u32	tx_pri5_drop_bcnt;
	u32	tx_pri6_drop_bcnt;
	u32	tx_pri7_drop_bcnt;
पूर्ण;

काष्ठा am65_cpsw_ethtool_stat अणु
	अक्षर desc[ETH_GSTRING_LEN];
	पूर्णांक offset;
पूर्ण;

#घोषणा AM65_CPSW_STATS(prefix, field)			\
अणु							\
	#prefix#field,					\
	दुरत्व(काष्ठा am65_cpsw_stats_regs, field)	\
पूर्ण

अटल स्थिर काष्ठा am65_cpsw_ethtool_stat am65_host_stats[] = अणु
	AM65_CPSW_STATS(p0_, rx_good_frames),
	AM65_CPSW_STATS(p0_, rx_broadcast_frames),
	AM65_CPSW_STATS(p0_, rx_multicast_frames),
	AM65_CPSW_STATS(p0_, rx_crc_errors),
	AM65_CPSW_STATS(p0_, rx_oversized_frames),
	AM65_CPSW_STATS(p0_, rx_undersized_frames),
	AM65_CPSW_STATS(p0_, ale_drop),
	AM65_CPSW_STATS(p0_, ale_overrun_drop),
	AM65_CPSW_STATS(p0_, rx_octets),
	AM65_CPSW_STATS(p0_, tx_good_frames),
	AM65_CPSW_STATS(p0_, tx_broadcast_frames),
	AM65_CPSW_STATS(p0_, tx_multicast_frames),
	AM65_CPSW_STATS(p0_, tx_octets),
	AM65_CPSW_STATS(p0_, tx_64B_frames),
	AM65_CPSW_STATS(p0_, tx_65_to_127B_frames),
	AM65_CPSW_STATS(p0_, tx_128_to_255B_frames),
	AM65_CPSW_STATS(p0_, tx_256_to_511B_frames),
	AM65_CPSW_STATS(p0_, tx_512_to_1023B_frames),
	AM65_CPSW_STATS(p0_, tx_1024B_frames),
	AM65_CPSW_STATS(p0_, net_octets),
	AM65_CPSW_STATS(p0_, rx_bottom_fअगरo_drop),
	AM65_CPSW_STATS(p0_, rx_port_mask_drop),
	AM65_CPSW_STATS(p0_, rx_top_fअगरo_drop),
	AM65_CPSW_STATS(p0_, ale_rate_limit_drop),
	AM65_CPSW_STATS(p0_, ale_vid_ingress_drop),
	AM65_CPSW_STATS(p0_, ale_da_eq_sa_drop),
	AM65_CPSW_STATS(p0_, ale_block_drop),
	AM65_CPSW_STATS(p0_, ale_secure_drop),
	AM65_CPSW_STATS(p0_, ale_auth_drop),
	AM65_CPSW_STATS(p0_, ale_unknown_ucast),
	AM65_CPSW_STATS(p0_, ale_unknown_ucast_bytes),
	AM65_CPSW_STATS(p0_, ale_unknown_mcast),
	AM65_CPSW_STATS(p0_, ale_unknown_mcast_bytes),
	AM65_CPSW_STATS(p0_, ale_unknown_bcast),
	AM65_CPSW_STATS(p0_, ale_unknown_bcast_bytes),
	AM65_CPSW_STATS(p0_, ale_pol_match),
	AM65_CPSW_STATS(p0_, ale_pol_match_red),
	AM65_CPSW_STATS(p0_, ale_pol_match_yellow),
	AM65_CPSW_STATS(p0_, ale_mcast_sa_drop),
	AM65_CPSW_STATS(p0_, ale_dual_vlan_drop),
	AM65_CPSW_STATS(p0_, ale_len_err_drop),
	AM65_CPSW_STATS(p0_, ale_ip_next_hdr_drop),
	AM65_CPSW_STATS(p0_, ale_ipv4_frag_drop),
	AM65_CPSW_STATS(p0_, tx_mem_protect_err),
	AM65_CPSW_STATS(p0_, tx_pri0),
	AM65_CPSW_STATS(p0_, tx_pri1),
	AM65_CPSW_STATS(p0_, tx_pri2),
	AM65_CPSW_STATS(p0_, tx_pri3),
	AM65_CPSW_STATS(p0_, tx_pri4),
	AM65_CPSW_STATS(p0_, tx_pri5),
	AM65_CPSW_STATS(p0_, tx_pri6),
	AM65_CPSW_STATS(p0_, tx_pri7),
	AM65_CPSW_STATS(p0_, tx_pri0_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri1_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri2_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri3_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri4_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri5_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri6_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri7_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri0_drop),
	AM65_CPSW_STATS(p0_, tx_pri1_drop),
	AM65_CPSW_STATS(p0_, tx_pri2_drop),
	AM65_CPSW_STATS(p0_, tx_pri3_drop),
	AM65_CPSW_STATS(p0_, tx_pri4_drop),
	AM65_CPSW_STATS(p0_, tx_pri5_drop),
	AM65_CPSW_STATS(p0_, tx_pri6_drop),
	AM65_CPSW_STATS(p0_, tx_pri7_drop),
	AM65_CPSW_STATS(p0_, tx_pri0_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri1_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri2_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri3_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri4_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri5_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri6_drop_bcnt),
	AM65_CPSW_STATS(p0_, tx_pri7_drop_bcnt),
पूर्ण;

अटल स्थिर काष्ठा am65_cpsw_ethtool_stat am65_slave_stats[] = अणु
	AM65_CPSW_STATS(, rx_good_frames),
	AM65_CPSW_STATS(, rx_broadcast_frames),
	AM65_CPSW_STATS(, rx_multicast_frames),
	AM65_CPSW_STATS(, rx_छोड़ो_frames),
	AM65_CPSW_STATS(, rx_crc_errors),
	AM65_CPSW_STATS(, rx_align_code_errors),
	AM65_CPSW_STATS(, rx_oversized_frames),
	AM65_CPSW_STATS(, rx_jabber_frames),
	AM65_CPSW_STATS(, rx_undersized_frames),
	AM65_CPSW_STATS(, rx_fragments),
	AM65_CPSW_STATS(, ale_drop),
	AM65_CPSW_STATS(, ale_overrun_drop),
	AM65_CPSW_STATS(, rx_octets),
	AM65_CPSW_STATS(, tx_good_frames),
	AM65_CPSW_STATS(, tx_broadcast_frames),
	AM65_CPSW_STATS(, tx_multicast_frames),
	AM65_CPSW_STATS(, tx_छोड़ो_frames),
	AM65_CPSW_STATS(, tx_deferred_frames),
	AM65_CPSW_STATS(, tx_collision_frames),
	AM65_CPSW_STATS(, tx_single_coll_frames),
	AM65_CPSW_STATS(, tx_mult_coll_frames),
	AM65_CPSW_STATS(, tx_excessive_collisions),
	AM65_CPSW_STATS(, tx_late_collisions),
	AM65_CPSW_STATS(, rx_ipg_error),
	AM65_CPSW_STATS(, tx_carrier_sense_errors),
	AM65_CPSW_STATS(, tx_octets),
	AM65_CPSW_STATS(, tx_64B_frames),
	AM65_CPSW_STATS(, tx_65_to_127B_frames),
	AM65_CPSW_STATS(, tx_128_to_255B_frames),
	AM65_CPSW_STATS(, tx_256_to_511B_frames),
	AM65_CPSW_STATS(, tx_512_to_1023B_frames),
	AM65_CPSW_STATS(, tx_1024B_frames),
	AM65_CPSW_STATS(, net_octets),
	AM65_CPSW_STATS(, rx_bottom_fअगरo_drop),
	AM65_CPSW_STATS(, rx_port_mask_drop),
	AM65_CPSW_STATS(, rx_top_fअगरo_drop),
	AM65_CPSW_STATS(, ale_rate_limit_drop),
	AM65_CPSW_STATS(, ale_vid_ingress_drop),
	AM65_CPSW_STATS(, ale_da_eq_sa_drop),
	AM65_CPSW_STATS(, ale_block_drop),
	AM65_CPSW_STATS(, ale_secure_drop),
	AM65_CPSW_STATS(, ale_auth_drop),
	AM65_CPSW_STATS(, ale_unknown_ucast),
	AM65_CPSW_STATS(, ale_unknown_ucast_bytes),
	AM65_CPSW_STATS(, ale_unknown_mcast),
	AM65_CPSW_STATS(, ale_unknown_mcast_bytes),
	AM65_CPSW_STATS(, ale_unknown_bcast),
	AM65_CPSW_STATS(, ale_unknown_bcast_bytes),
	AM65_CPSW_STATS(, ale_pol_match),
	AM65_CPSW_STATS(, ale_pol_match_red),
	AM65_CPSW_STATS(, ale_pol_match_yellow),
	AM65_CPSW_STATS(, ale_mcast_sa_drop),
	AM65_CPSW_STATS(, ale_dual_vlan_drop),
	AM65_CPSW_STATS(, ale_len_err_drop),
	AM65_CPSW_STATS(, ale_ip_next_hdr_drop),
	AM65_CPSW_STATS(, ale_ipv4_frag_drop),
	AM65_CPSW_STATS(, iet_rx_assembly_err),
	AM65_CPSW_STATS(, iet_rx_assembly_ok),
	AM65_CPSW_STATS(, iet_rx_smd_err),
	AM65_CPSW_STATS(, iet_rx_frag),
	AM65_CPSW_STATS(, iet_tx_hold),
	AM65_CPSW_STATS(, iet_tx_frag),
	AM65_CPSW_STATS(, tx_mem_protect_err),
	AM65_CPSW_STATS(, tx_pri0),
	AM65_CPSW_STATS(, tx_pri1),
	AM65_CPSW_STATS(, tx_pri2),
	AM65_CPSW_STATS(, tx_pri3),
	AM65_CPSW_STATS(, tx_pri4),
	AM65_CPSW_STATS(, tx_pri5),
	AM65_CPSW_STATS(, tx_pri6),
	AM65_CPSW_STATS(, tx_pri7),
	AM65_CPSW_STATS(, tx_pri0_bcnt),
	AM65_CPSW_STATS(, tx_pri1_bcnt),
	AM65_CPSW_STATS(, tx_pri2_bcnt),
	AM65_CPSW_STATS(, tx_pri3_bcnt),
	AM65_CPSW_STATS(, tx_pri4_bcnt),
	AM65_CPSW_STATS(, tx_pri5_bcnt),
	AM65_CPSW_STATS(, tx_pri6_bcnt),
	AM65_CPSW_STATS(, tx_pri7_bcnt),
	AM65_CPSW_STATS(, tx_pri0_drop),
	AM65_CPSW_STATS(, tx_pri1_drop),
	AM65_CPSW_STATS(, tx_pri2_drop),
	AM65_CPSW_STATS(, tx_pri3_drop),
	AM65_CPSW_STATS(, tx_pri4_drop),
	AM65_CPSW_STATS(, tx_pri5_drop),
	AM65_CPSW_STATS(, tx_pri6_drop),
	AM65_CPSW_STATS(, tx_pri7_drop),
	AM65_CPSW_STATS(, tx_pri0_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri1_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri2_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri3_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri4_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri5_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri6_drop_bcnt),
	AM65_CPSW_STATS(, tx_pri7_drop_bcnt),
पूर्ण;

/* Ethtool priv_flags */
अटल स्थिर अक्षर am65_cpsw_ethtool_priv_flags[][ETH_GSTRING_LEN] = अणु
#घोषणा	AM65_CPSW_PRIV_P0_RX_PTYPE_RROBIN	BIT(0)
	"p0-rx-ptype-rrobin",
पूर्ण;

अटल पूर्णांक am65_cpsw_ethtool_op_begin(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(common->dev);
	अगर (ret < 0) अणु
		dev_err(common->dev, "ethtool begin failed %d\n", ret);
		pm_runसमय_put_noidle(common->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम am65_cpsw_ethtool_op_complete(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	पूर्णांक ret;

	ret = pm_runसमय_put(common->dev);
	अगर (ret < 0 && ret != -EBUSY)
		dev_err(common->dev, "ethtool complete failed %d\n", ret);
पूर्ण

अटल व्योम am65_cpsw_get_drvinfo(काष्ठा net_device *ndev,
				  काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

	strlcpy(info->driver, dev_driver_string(common->dev),
		माप(info->driver));
	strlcpy(info->bus_info, dev_name(common->dev), माप(info->bus_info));
पूर्ण

अटल u32 am65_cpsw_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_ndev_priv *priv = am65_ndev_to_priv(ndev);

	वापस priv->msg_enable;
पूर्ण

अटल व्योम am65_cpsw_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा am65_cpsw_ndev_priv *priv = am65_ndev_to_priv(ndev);

	priv->msg_enable = value;
पूर्ण

अटल व्योम am65_cpsw_get_channels(काष्ठा net_device *ndev,
				   काष्ठा ethtool_channels *ch)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

	ch->max_rx = AM65_CPSW_MAX_RX_QUEUES;
	ch->max_tx = AM65_CPSW_MAX_TX_QUEUES;
	ch->rx_count = AM65_CPSW_MAX_RX_QUEUES;
	ch->tx_count = common->tx_ch_num;
पूर्ण

अटल पूर्णांक am65_cpsw_set_channels(काष्ठा net_device *ndev,
				  काष्ठा ethtool_channels *chs)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

	अगर (!chs->rx_count || !chs->tx_count)
		वापस -EINVAL;

	/* Check अगर पूर्णांकerface is up. Can change the num queues when
	 * the पूर्णांकerface is करोwn.
	 */
	अगर (common->usage_count)
		वापस -EBUSY;

	am65_cpsw_nuss_हटाओ_tx_chns(common);

	वापस am65_cpsw_nuss_update_tx_chns(common, chs->tx_count);
पूर्ण

अटल व्योम am65_cpsw_get_ringparam(काष्ठा net_device *ndev,
				    काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

	/* not supported */
	ering->tx_pending = common->tx_chns[0].descs_num;
	ering->rx_pending = common->rx_chns.descs_num;
पूर्ण

अटल व्योम am65_cpsw_get_छोड़ोparam(काष्ठा net_device *ndev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	छोड़ो->स्वतःneg = AUTONEG_DISABLE;
	छोड़ो->rx_छोड़ो = salve->rx_छोड़ो ? true : false;
	छोड़ो->tx_छोड़ो = salve->tx_छोड़ो ? true : false;
पूर्ण

अटल पूर्णांक am65_cpsw_set_छोड़ोparam(काष्ठा net_device *ndev,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy)
		वापस -EINVAL;

	अगर (!phy_validate_छोड़ो(salve->phy, छोड़ो))
		वापस -EINVAL;

	salve->rx_छोड़ो = छोड़ो->rx_छोड़ो ? true : false;
	salve->tx_छोड़ो = छोड़ो->tx_छोड़ो ? true : false;

	phy_set_asym_छोड़ो(salve->phy, salve->rx_छोड़ो, salve->tx_छोड़ो);

	वापस 0;
पूर्ण

अटल व्योम am65_cpsw_get_wol(काष्ठा net_device *ndev,
			      काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (salve->phy)
		phy_ethtool_get_wol(salve->phy, wol);
पूर्ण

अटल पूर्णांक am65_cpsw_set_wol(काष्ठा net_device *ndev,
			     काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy)
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_set_wol(salve->phy, wol);
पूर्ण

अटल पूर्णांक am65_cpsw_get_link_ksettings(काष्ठा net_device *ndev,
					काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy)
		वापस -EOPNOTSUPP;

	phy_ethtool_ksettings_get(salve->phy, ecmd);
	वापस 0;
पूर्ण

अटल पूर्णांक
am65_cpsw_set_link_ksettings(काष्ठा net_device *ndev,
			     स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy || phy_is_pseuकरो_fixed_link(salve->phy))
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_ksettings_set(salve->phy, ecmd);
पूर्ण

अटल पूर्णांक am65_cpsw_get_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy || phy_is_pseuकरो_fixed_link(salve->phy))
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_get_eee(salve->phy, edata);
पूर्ण

अटल पूर्णांक am65_cpsw_set_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy || phy_is_pseuकरो_fixed_link(salve->phy))
		वापस -EOPNOTSUPP;

	वापस phy_ethtool_set_eee(salve->phy, edata);
पूर्ण

अटल पूर्णांक am65_cpsw_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_slave_data *salve = am65_ndev_to_slave(ndev);

	अगर (!salve->phy || phy_is_pseuकरो_fixed_link(salve->phy))
		वापस -EOPNOTSUPP;

	वापस phy_restart_aneg(salve->phy);
पूर्ण

अटल पूर्णांक am65_cpsw_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 ale_entries, i, regdump_len = 0;

	ale_entries = cpsw_ale_get_num_entries(common->ale);
	क्रम (i = 0; i < ARRAY_SIZE(am65_cpsw_regdump); i++) अणु
		अगर (am65_cpsw_regdump[i].hdr.module_id ==
		    AM65_CPSW_REGDUMP_MOD_CPSW_ALE_TBL) अणु
			regdump_len += माप(काष्ठा am65_cpsw_regdump_hdr);
			regdump_len += ale_entries *
				       ALE_ENTRY_WORDS * माप(u32);
			जारी;
		पूर्ण
		regdump_len += am65_cpsw_regdump[i].hdr.len;
	पूर्ण

	वापस regdump_len;
पूर्ण

अटल व्योम am65_cpsw_get_regs(काष्ठा net_device *ndev,
			       काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 ale_entries, i, j, pos, *reg = p;

	/* update CPSW IP version */
	regs->version = AM65_CPSW_REGDUMP_VER;
	ale_entries = cpsw_ale_get_num_entries(common->ale);

	pos = 0;
	क्रम (i = 0; i < ARRAY_SIZE(am65_cpsw_regdump); i++) अणु
		reg[pos++] = am65_cpsw_regdump[i].hdr.module_id;

		अगर (am65_cpsw_regdump[i].hdr.module_id ==
		    AM65_CPSW_REGDUMP_MOD_CPSW_ALE_TBL) अणु
			u32 ale_tbl_len = ale_entries *
					  ALE_ENTRY_WORDS * माप(u32) +
					  माप(काष्ठा am65_cpsw_regdump_hdr);
			reg[pos++] = ale_tbl_len;
			cpsw_ale_dump(common->ale, &reg[pos]);
			pos += ale_tbl_len;
			जारी;
		पूर्ण

		reg[pos++] = am65_cpsw_regdump[i].hdr.len;

		j = am65_cpsw_regdump[i].start_ofs;
		करो अणु
			reg[pos++] = j;
			reg[pos++] = पढ़ोl_relaxed(common->ss_base + j);
			j += माप(u32);
		पूर्ण जबतक (j <= am65_cpsw_regdump[i].end_ofs);
	पूर्ण
पूर्ण

अटल पूर्णांक am65_cpsw_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(am65_host_stats) +
		       ARRAY_SIZE(am65_slave_stats);
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(am65_cpsw_ethtool_priv_flags);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम am65_cpsw_get_strings(काष्ठा net_device *ndev,
				  u32 stringset, u8 *data)
अणु
	स्थिर काष्ठा am65_cpsw_ethtool_stat *hw_stats;
	u32 i, num_stats;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		num_stats = ARRAY_SIZE(am65_host_stats);
		hw_stats = am65_host_stats;
		क्रम (i = 0; i < num_stats; i++) अणु
			स_नकल(p, hw_stats[i].desc, ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		num_stats = ARRAY_SIZE(am65_slave_stats);
		hw_stats = am65_slave_stats;
		क्रम (i = 0; i < num_stats; i++) अणु
			स_नकल(p, hw_stats[i].desc, ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		num_stats = ARRAY_SIZE(am65_cpsw_ethtool_priv_flags);

		क्रम (i = 0; i < num_stats; i++) अणु
			स_नकल(p, am65_cpsw_ethtool_priv_flags[i],
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम am65_cpsw_get_ethtool_stats(काष्ठा net_device *ndev,
					काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	स्थिर काष्ठा am65_cpsw_ethtool_stat *hw_stats;
	काष्ठा am65_cpsw_host *host_p;
	काष्ठा am65_cpsw_port *port;
	u32 i, num_stats;

	host_p = am65_common_get_host(common);
	port = am65_ndev_to_port(ndev);
	num_stats = ARRAY_SIZE(am65_host_stats);
	hw_stats = am65_host_stats;
	क्रम (i = 0; i < num_stats; i++)
		*data++ = पढ़ोl_relaxed(host_p->stat_base +
					hw_stats[i].offset);

	num_stats = ARRAY_SIZE(am65_slave_stats);
	hw_stats = am65_slave_stats;
	क्रम (i = 0; i < num_stats; i++)
		*data++ = पढ़ोl_relaxed(port->stat_base +
					hw_stats[i].offset);
पूर्ण

अटल पूर्णांक am65_cpsw_get_ethtool_ts_info(काष्ठा net_device *ndev,
					 काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);

	अगर (!IS_ENABLED(CONFIG_TI_K3_AM65_CPTS))
		वापस ethtool_op_get_ts_info(ndev, info);

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = am65_cpts_phc_index(common->cpts);
	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);
	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE) | BIT(HWTSTAMP_FILTER_ALL);
	वापस 0;
पूर्ण

अटल u32 am65_cpsw_get_ethtool_priv_flags(काष्ठा net_device *ndev)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	u32 priv_flags = 0;

	अगर (common->pf_p0_rx_ptype_rrobin)
		priv_flags |= AM65_CPSW_PRIV_P0_RX_PTYPE_RROBIN;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक am65_cpsw_set_ethtool_priv_flags(काष्ठा net_device *ndev, u32 flags)
अणु
	काष्ठा am65_cpsw_common *common = am65_ndev_to_common(ndev);
	पूर्णांक rrobin;

	rrobin = !!(flags & AM65_CPSW_PRIV_P0_RX_PTYPE_RROBIN);

	अगर (common->usage_count)
		वापस -EBUSY;

	अगर (common->est_enabled && rrobin) अणु
		netdev_err(ndev,
			   "p0-rx-ptype-rrobin flag conflicts with QOS\n");
		वापस -EINVAL;
	पूर्ण

	common->pf_p0_rx_ptype_rrobin = rrobin;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops am65_cpsw_ethtool_ops_slave = अणु
	.begin			= am65_cpsw_ethtool_op_begin,
	.complete		= am65_cpsw_ethtool_op_complete,
	.get_drvinfo		= am65_cpsw_get_drvinfo,
	.get_msglevel		= am65_cpsw_get_msglevel,
	.set_msglevel		= am65_cpsw_set_msglevel,
	.get_channels		= am65_cpsw_get_channels,
	.set_channels		= am65_cpsw_set_channels,
	.get_ringparam		= am65_cpsw_get_ringparam,
	.get_regs_len		= am65_cpsw_get_regs_len,
	.get_regs		= am65_cpsw_get_regs,
	.get_sset_count		= am65_cpsw_get_sset_count,
	.get_strings		= am65_cpsw_get_strings,
	.get_ethtool_stats	= am65_cpsw_get_ethtool_stats,
	.get_ts_info		= am65_cpsw_get_ethtool_ts_info,
	.get_priv_flags		= am65_cpsw_get_ethtool_priv_flags,
	.set_priv_flags		= am65_cpsw_set_ethtool_priv_flags,

	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= am65_cpsw_get_link_ksettings,
	.set_link_ksettings	= am65_cpsw_set_link_ksettings,
	.get_छोड़ोparam		= am65_cpsw_get_छोड़ोparam,
	.set_छोड़ोparam		= am65_cpsw_set_छोड़ोparam,
	.get_wol		= am65_cpsw_get_wol,
	.set_wol		= am65_cpsw_set_wol,
	.get_eee		= am65_cpsw_get_eee,
	.set_eee		= am65_cpsw_set_eee,
	.nway_reset		= am65_cpsw_nway_reset,
पूर्ण;
