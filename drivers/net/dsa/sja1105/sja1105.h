<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Sensor-Technik Wiedemann GmbH
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#अगर_अघोषित _SJA1105_H
#घोषणा _SJA1105_H

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <linux/dsa/sja1105.h>
#समावेश <linux/dsa/8021q.h>
#समावेश <net/dsa.h>
#समावेश <linux/mutex.h>
#समावेश "sja1105_static_config.h"

#घोषणा SJA1105_NUM_PORTS		5
#घोषणा SJA1105_NUM_TC			8
#घोषणा SJA1105ET_FDB_BIN_SIZE		4
/* The hardware value is in multiples of 10 ms.
 * The passed parameter is in multiples of 1 ms.
 */
#घोषणा SJA1105_AGEING_TIME_MS(ms)	((ms) / 10)
#घोषणा SJA1105_NUM_L2_POLICERS		45

प्रकार क्रमागत अणु
	SPI_READ = 0,
	SPI_WRITE = 1,
पूर्ण sja1105_spi_rw_mode_t;

#समावेश "sja1105_tas.h"
#समावेश "sja1105_ptp.h"

/* Keeps the dअगरferent addresses between E/T and P/Q/R/S */
काष्ठा sja1105_regs अणु
	u64 device_id;
	u64 prod_id;
	u64 status;
	u64 port_control;
	u64 rgu;
	u64 vl_status;
	u64 config;
	u64 sgmii;
	u64 rmii_pll1;
	u64 ptppinst;
	u64 ptppindur;
	u64 ptp_control;
	u64 ptpclkval;
	u64 ptpclkrate;
	u64 ptpclkcorp;
	u64 ptpsyncts;
	u64 ptpschपंचांग;
	u64 ptpegr_ts[SJA1105_NUM_PORTS];
	u64 pad_mii_tx[SJA1105_NUM_PORTS];
	u64 pad_mii_rx[SJA1105_NUM_PORTS];
	u64 pad_mii_id[SJA1105_NUM_PORTS];
	u64 cgu_iभाग[SJA1105_NUM_PORTS];
	u64 mii_tx_clk[SJA1105_NUM_PORTS];
	u64 mii_rx_clk[SJA1105_NUM_PORTS];
	u64 mii_ext_tx_clk[SJA1105_NUM_PORTS];
	u64 mii_ext_rx_clk[SJA1105_NUM_PORTS];
	u64 rgmii_tx_clk[SJA1105_NUM_PORTS];
	u64 rmii_ref_clk[SJA1105_NUM_PORTS];
	u64 rmii_ext_tx_clk[SJA1105_NUM_PORTS];
	u64 mac[SJA1105_NUM_PORTS];
	u64 mac_hl1[SJA1105_NUM_PORTS];
	u64 mac_hl2[SJA1105_NUM_PORTS];
	u64 ether_stats[SJA1105_NUM_PORTS];
	u64 qlevel[SJA1105_NUM_PORTS];
पूर्ण;

काष्ठा sja1105_info अणु
	u64 device_id;
	/* Needed क्रम distinction between P and R, and between Q and S
	 * (since the parts with/without SGMII share the same
	 * चयन core and device_id)
	 */
	u64 part_no;
	/* E/T and P/Q/R/S have partial बारtamps of dअगरferent sizes.
	 * They must be reस्थिरructed on both families anyway to get the full
	 * 64-bit values back.
	 */
	पूर्णांक ptp_ts_bits;
	/* Also SPI commands are of dअगरferent sizes to retrieve
	 * the egress बारtamps.
	 */
	पूर्णांक ptpegr_ts_bytes;
	पूर्णांक num_cbs_shapers;
	स्थिर काष्ठा sja1105_dynamic_table_ops *dyn_ops;
	स्थिर काष्ठा sja1105_table_ops *अटल_ops;
	स्थिर काष्ठा sja1105_regs *regs;
	/* Both E/T and P/Q/R/S have quirks when it comes to popping the S-Tag
	 * from द्विगुन-tagged frames. E/T will pop it only when it's equal to
	 * TPID from the General Parameters Table, जबतक P/Q/R/S will only
	 * pop it when it's equal to TPID2.
	 */
	u16 qinq_tpid;
	bool can_limit_mcast_flood;
	पूर्णांक (*reset_cmd)(काष्ठा dsa_चयन *ds);
	पूर्णांक (*setup_rgmii_delay)(स्थिर व्योम *ctx, पूर्णांक port);
	/* Prototypes from include/net/dsa.h */
	पूर्णांक (*fdb_add_cmd)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid);
	पूर्णांक (*fdb_del_cmd)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   स्थिर अचिन्हित अक्षर *addr, u16 vid);
	व्योम (*ptp_cmd_packing)(u8 *buf, काष्ठा sja1105_ptp_cmd *cmd,
				क्रमागत packing_op op);
	स्थिर अक्षर *name;
पूर्ण;

क्रमागत sja1105_key_type अणु
	SJA1105_KEY_BCAST,
	SJA1105_KEY_TC,
	SJA1105_KEY_VLAN_UNAWARE_VL,
	SJA1105_KEY_VLAN_AWARE_VL,
पूर्ण;

काष्ठा sja1105_key अणु
	क्रमागत sja1105_key_type type;

	जोड़ अणु
		/* SJA1105_KEY_TC */
		काष्ठा अणु
			पूर्णांक pcp;
		पूर्ण tc;

		/* SJA1105_KEY_VLAN_UNAWARE_VL */
		/* SJA1105_KEY_VLAN_AWARE_VL */
		काष्ठा अणु
			u64 dmac;
			u16 vid;
			u16 pcp;
		पूर्ण vl;
	पूर्ण;
पूर्ण;

क्रमागत sja1105_rule_type अणु
	SJA1105_RULE_BCAST_POLICER,
	SJA1105_RULE_TC_POLICER,
	SJA1105_RULE_VL,
पूर्ण;

क्रमागत sja1105_vl_type अणु
	SJA1105_VL_NONCRITICAL,
	SJA1105_VL_RATE_CONSTRAINED,
	SJA1105_VL_TIME_TRIGGERED,
पूर्ण;

काष्ठा sja1105_rule अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ cookie;
	अचिन्हित दीर्घ port_mask;
	काष्ठा sja1105_key key;
	क्रमागत sja1105_rule_type type;

	/* Action */
	जोड़ अणु
		/* SJA1105_RULE_BCAST_POLICER */
		काष्ठा अणु
			पूर्णांक sharindx;
		पूर्ण bcast_pol;

		/* SJA1105_RULE_TC_POLICER */
		काष्ठा अणु
			पूर्णांक sharindx;
		पूर्ण tc_pol;

		/* SJA1105_RULE_VL */
		काष्ठा अणु
			क्रमागत sja1105_vl_type type;
			अचिन्हित दीर्घ destports;
			पूर्णांक sharindx;
			पूर्णांक maxlen;
			पूर्णांक ipv;
			u64 base_समय;
			u64 cycle_समय;
			पूर्णांक num_entries;
			काष्ठा action_gate_entry *entries;
			काष्ठा flow_stats stats;
		पूर्ण vl;
	पूर्ण;
पूर्ण;

काष्ठा sja1105_flow_block अणु
	काष्ठा list_head rules;
	bool l2_policer_used[SJA1105_NUM_L2_POLICERS];
	पूर्णांक num_भव_links;
पूर्ण;

काष्ठा sja1105_bridge_vlan अणु
	काष्ठा list_head list;
	पूर्णांक port;
	u16 vid;
	bool pvid;
	bool untagged;
पूर्ण;

क्रमागत sja1105_vlan_state अणु
	SJA1105_VLAN_UNAWARE,
	SJA1105_VLAN_BEST_EFFORT,
	SJA1105_VLAN_FILTERING_FULL,
पूर्ण;

काष्ठा sja1105_निजी अणु
	काष्ठा sja1105_अटल_config अटल_config;
	bool rgmii_rx_delay[SJA1105_NUM_PORTS];
	bool rgmii_tx_delay[SJA1105_NUM_PORTS];
	bool best_efक्रमt_vlan_filtering;
	अचिन्हित दीर्घ learn_ena;
	अचिन्हित दीर्घ ucast_egress_floods;
	अचिन्हित दीर्घ bcast_egress_floods;
	स्थिर काष्ठा sja1105_info *info;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा spi_device *spidev;
	काष्ठा dsa_चयन *ds;
	काष्ठा list_head dsa_8021q_vlans;
	काष्ठा list_head bridge_vlans;
	काष्ठा sja1105_flow_block flow_block;
	काष्ठा sja1105_port ports[SJA1105_NUM_PORTS];
	/* Serializes transmission of management frames so that
	 * the चयन करोesn't confuse them with one another.
	 */
	काष्ठा mutex mgmt_lock;
	काष्ठा dsa_8021q_context *dsa_8021q_ctx;
	क्रमागत sja1105_vlan_state vlan_state;
	काष्ठा devlink_region **regions;
	काष्ठा sja1105_cbs_entry *cbs;
	काष्ठा sja1105_tagger_data tagger_data;
	काष्ठा sja1105_ptp_data ptp_data;
	काष्ठा sja1105_tas_data tas_data;
पूर्ण;

#समावेश "sja1105_dynamic_config.h"

काष्ठा sja1105_spi_message अणु
	u64 access;
	u64 पढ़ो_count;
	u64 address;
पूर्ण;

/* From sja1105_मुख्य.c */
क्रमागत sja1105_reset_reason अणु
	SJA1105_VLAN_FILTERING = 0,
	SJA1105_RX_HWTSTAMPING,
	SJA1105_AGEING_TIME,
	SJA1105_SCHEDULING,
	SJA1105_BEST_EFFORT_POLICING,
	SJA1105_VIRTUAL_LINKS,
पूर्ण;

पूर्णांक sja1105_अटल_config_reload(काष्ठा sja1105_निजी *priv,
				 क्रमागत sja1105_reset_reason reason);
पूर्णांक sja1105_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool enabled,
			   काष्ठा netlink_ext_ack *extack);
व्योम sja1105_frame_memory_partitioning(काष्ठा sja1105_निजी *priv);

/* From sja1105_devlink.c */
पूर्णांक sja1105_devlink_setup(काष्ठा dsa_चयन *ds);
व्योम sja1105_devlink_tearकरोwn(काष्ठा dsa_चयन *ds);
पूर्णांक sja1105_devlink_param_get(काष्ठा dsa_चयन *ds, u32 id,
			      काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक sja1105_devlink_param_set(काष्ठा dsa_चयन *ds, u32 id,
			      काष्ठा devlink_param_gset_ctx *ctx);
पूर्णांक sja1105_devlink_info_get(काष्ठा dsa_चयन *ds,
			     काष्ठा devlink_info_req *req,
			     काष्ठा netlink_ext_ack *extack);

/* From sja1105_spi.c */
पूर्णांक sja1105_xfer_buf(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr,
		     u8 *buf, माप_प्रकार len);
पूर्णांक sja1105_xfer_u32(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr, u32 *value,
		     काष्ठा ptp_प्रणाली_बारtamp *ptp_sts);
पूर्णांक sja1105_xfer_u64(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr, u64 *value,
		     काष्ठा ptp_प्रणाली_बारtamp *ptp_sts);
पूर्णांक अटल_config_buf_prepare_क्रम_upload(काष्ठा sja1105_निजी *priv,
					 व्योम *config_buf, पूर्णांक buf_len);
पूर्णांक sja1105_अटल_config_upload(काष्ठा sja1105_निजी *priv);
पूर्णांक sja1105_inhibit_tx(स्थिर काष्ठा sja1105_निजी *priv,
		       अचिन्हित दीर्घ port_biपंचांगap, bool tx_inhibited);

बाह्य स्थिर काष्ठा sja1105_info sja1105e_info;
बाह्य स्थिर काष्ठा sja1105_info sja1105t_info;
बाह्य स्थिर काष्ठा sja1105_info sja1105p_info;
बाह्य स्थिर काष्ठा sja1105_info sja1105q_info;
बाह्य स्थिर काष्ठा sja1105_info sja1105r_info;
बाह्य स्थिर काष्ठा sja1105_info sja1105s_info;

/* From sja1105_घड़ीing.c */

प्रकार क्रमागत अणु
	XMII_MAC = 0,
	XMII_PHY = 1,
पूर्ण sja1105_mii_role_t;

प्रकार क्रमागत अणु
	XMII_MODE_MII		= 0,
	XMII_MODE_RMII		= 1,
	XMII_MODE_RGMII		= 2,
	XMII_MODE_SGMII		= 3,
पूर्ण sja1105_phy_पूर्णांकerface_t;

प्रकार क्रमागत अणु
	SJA1105_SPEED_10MBPS	= 3,
	SJA1105_SPEED_100MBPS	= 2,
	SJA1105_SPEED_1000MBPS	= 1,
	SJA1105_SPEED_AUTO	= 0,
पूर्ण sja1105_speed_t;

पूर्णांक sja1105pqrs_setup_rgmii_delay(स्थिर व्योम *ctx, पूर्णांक port);
पूर्णांक sja1105_घड़ीing_setup_port(काष्ठा sja1105_निजी *priv, पूर्णांक port);
पूर्णांक sja1105_घड़ीing_setup(काष्ठा sja1105_निजी *priv);

/* From sja1105_ethtool.c */
व्योम sja1105_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, u64 *data);
व्योम sja1105_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 u32 stringset, u8 *data);
पूर्णांक sja1105_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);

/* From sja1105_dynamic_config.c */
पूर्णांक sja1105_dynamic_config_पढ़ो(काष्ठा sja1105_निजी *priv,
				क्रमागत sja1105_blk_idx blk_idx,
				पूर्णांक index, व्योम *entry);
पूर्णांक sja1105_dynamic_config_ग_लिखो(काष्ठा sja1105_निजी *priv,
				 क्रमागत sja1105_blk_idx blk_idx,
				 पूर्णांक index, व्योम *entry, bool keep);

क्रमागत sja1105_iotag अणु
	SJA1105_C_TAG = 0, /* Inner VLAN header */
	SJA1105_S_TAG = 1, /* Outer VLAN header */
पूर्ण;

u8 sja1105et_fdb_hash(काष्ठा sja1105_निजी *priv, स्थिर u8 *addr, u16 vid);
पूर्णांक sja1105et_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक sja1105et_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक sja1105pqrs_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक sja1105pqrs_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			स्थिर अचिन्हित अक्षर *addr, u16 vid);

/* From sja1105_flower.c */
पूर्णांक sja1105_cls_flower_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा flow_cls_offload *cls, bool ingress);
पूर्णांक sja1105_cls_flower_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा flow_cls_offload *cls, bool ingress);
पूर्णांक sja1105_cls_flower_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा flow_cls_offload *cls, bool ingress);
व्योम sja1105_flower_setup(काष्ठा dsa_चयन *ds);
व्योम sja1105_flower_tearकरोwn(काष्ठा dsa_चयन *ds);
काष्ठा sja1105_rule *sja1105_rule_find(काष्ठा sja1105_निजी *priv,
				       अचिन्हित दीर्घ cookie);

#पूर्ण_अगर
