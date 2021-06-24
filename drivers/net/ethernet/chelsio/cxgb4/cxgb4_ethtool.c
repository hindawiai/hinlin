<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2013-2015 Chelsio Communications.  All rights reserved.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/mdपन.स>

#समावेश "cxgb4.h"
#समावेश "t4_regs.h"
#समावेश "t4fw_api.h"
#समावेश "cxgb4_cudbg.h"
#समावेश "cxgb4_filter.h"
#समावेश "cxgb4_tc_flower.h"

#घोषणा EEPROM_MAGIC 0x38E2F10C

अटल u32 get_msglevel(काष्ठा net_device *dev)
अणु
	वापस netdev2adap(dev)->msg_enable;
पूर्ण

अटल व्योम set_msglevel(काष्ठा net_device *dev, u32 val)
अणु
	netdev2adap(dev)->msg_enable = val;
पूर्ण

क्रमागत cxgb4_ethtool_tests अणु
	CXGB4_ETHTOOL_LB_TEST,
	CXGB4_ETHTOOL_MAX_TEST,
पूर्ण;

अटल स्थिर अक्षर cxgb4_selftest_strings[CXGB4_ETHTOOL_MAX_TEST][ETH_GSTRING_LEN] = अणु
	"Loop back test (offline)",
पूर्ण;

अटल स्थिर अक्षर * स्थिर flash_region_strings[] = अणु
	"All",
	"Firmware",
	"PHY Firmware",
	"Boot",
	"Boot CFG",
पूर्ण;

अटल स्थिर अक्षर stats_strings[][ETH_GSTRING_LEN] = अणु
	"tx_octets_ok           ",
	"tx_frames_ok           ",
	"tx_broadcast_frames    ",
	"tx_multicast_frames    ",
	"tx_unicast_frames      ",
	"tx_error_frames        ",

	"tx_frames_64           ",
	"tx_frames_65_to_127    ",
	"tx_frames_128_to_255   ",
	"tx_frames_256_to_511   ",
	"tx_frames_512_to_1023  ",
	"tx_frames_1024_to_1518 ",
	"tx_frames_1519_to_max  ",

	"tx_frames_dropped      ",
	"tx_pause_frames        ",
	"tx_ppp0_frames         ",
	"tx_ppp1_frames         ",
	"tx_ppp2_frames         ",
	"tx_ppp3_frames         ",
	"tx_ppp4_frames         ",
	"tx_ppp5_frames         ",
	"tx_ppp6_frames         ",
	"tx_ppp7_frames         ",

	"rx_octets_ok           ",
	"rx_frames_ok           ",
	"rx_broadcast_frames    ",
	"rx_multicast_frames    ",
	"rx_unicast_frames      ",

	"rx_frames_too_long     ",
	"rx_jabber_errors       ",
	"rx_fcs_errors          ",
	"rx_length_errors       ",
	"rx_symbol_errors       ",
	"rx_runt_frames         ",

	"rx_frames_64           ",
	"rx_frames_65_to_127    ",
	"rx_frames_128_to_255   ",
	"rx_frames_256_to_511   ",
	"rx_frames_512_to_1023  ",
	"rx_frames_1024_to_1518 ",
	"rx_frames_1519_to_max  ",

	"rx_pause_frames        ",
	"rx_ppp0_frames         ",
	"rx_ppp1_frames         ",
	"rx_ppp2_frames         ",
	"rx_ppp3_frames         ",
	"rx_ppp4_frames         ",
	"rx_ppp5_frames         ",
	"rx_ppp6_frames         ",
	"rx_ppp7_frames         ",

	"rx_bg0_frames_dropped  ",
	"rx_bg1_frames_dropped  ",
	"rx_bg2_frames_dropped  ",
	"rx_bg3_frames_dropped  ",
	"rx_bg0_frames_trunc    ",
	"rx_bg1_frames_trunc    ",
	"rx_bg2_frames_trunc    ",
	"rx_bg3_frames_trunc    ",

	"tso                    ",
	"uso                    ",
	"tx_csum_offload        ",
	"rx_csum_good           ",
	"vlan_extractions       ",
	"vlan_insertions        ",
	"gro_packets            ",
	"gro_merged             ",
#अगर  IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	"tx_tls_encrypted_packets",
	"tx_tls_encrypted_bytes  ",
	"tx_tls_ctx              ",
	"tx_tls_ooo              ",
	"tx_tls_skip_no_sync_data",
	"tx_tls_drop_no_sync_data",
	"tx_tls_drop_bypass_req  ",
#पूर्ण_अगर
पूर्ण;

अटल अक्षर adapter_stats_strings[][ETH_GSTRING_LEN] = अणु
	"db_drop                ",
	"db_full                ",
	"db_empty               ",
	"write_coal_success     ",
	"write_coal_fail        ",
पूर्ण;

अटल अक्षर loopback_stats_strings[][ETH_GSTRING_LEN] = अणु
	"-------Loopback----------- ",
	"octets_ok              ",
	"frames_ok              ",
	"bcast_frames           ",
	"mcast_frames           ",
	"ucast_frames           ",
	"error_frames           ",
	"frames_64              ",
	"frames_65_to_127       ",
	"frames_128_to_255      ",
	"frames_256_to_511      ",
	"frames_512_to_1023     ",
	"frames_1024_to_1518    ",
	"frames_1519_to_max     ",
	"frames_dropped         ",
	"bg0_frames_dropped     ",
	"bg1_frames_dropped     ",
	"bg2_frames_dropped     ",
	"bg3_frames_dropped     ",
	"bg0_frames_trunc       ",
	"bg1_frames_trunc       ",
	"bg2_frames_trunc       ",
	"bg3_frames_trunc       ",
पूर्ण;

अटल स्थिर अक्षर cxgb4_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
	[PRIV_FLAG_PORT_TX_VM_BIT] = "port_tx_vm_wr",
पूर्ण;

अटल पूर्णांक get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(stats_strings) +
		       ARRAY_SIZE(adapter_stats_strings) +
		       ARRAY_SIZE(loopback_stats_strings);
	हाल ETH_SS_PRIV_FLAGS:
		वापस ARRAY_SIZE(cxgb4_priv_flags_strings);
	हाल ETH_SS_TEST:
		वापस ARRAY_SIZE(cxgb4_selftest_strings);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);

	वापस t4_get_regs_len(adap);
पूर्ण

अटल पूर्णांक get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस EEPROMSIZE;
पूर्ण

अटल व्योम get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	u32 exprom_vers;

	strlcpy(info->driver, cxgb4_driver_name, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
	info->regdump_len = get_regs_len(dev);

	अगर (adapter->params.fw_vers)
		snम_लिखो(info->fw_version, माप(info->fw_version),
			 "%u.%u.%u.%u, TP %u.%u.%u.%u",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.tp_vers));

	अगर (!t4_get_exprom_version(adapter, &exprom_vers))
		snम_लिखो(info->erom_version, माप(info->erom_version),
			 "%u.%u.%u.%u",
			 FW_HDR_FW_VER_MAJOR_G(exprom_vers),
			 FW_HDR_FW_VER_MINOR_G(exprom_vers),
			 FW_HDR_FW_VER_MICRO_G(exprom_vers),
			 FW_HDR_FW_VER_BUILD_G(exprom_vers));
	info->n_priv_flags = ARRAY_SIZE(cxgb4_priv_flags_strings);
पूर्ण

अटल व्योम get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS) अणु
		स_नकल(data, stats_strings, माप(stats_strings));
		data += माप(stats_strings);
		स_नकल(data, adapter_stats_strings,
		       माप(adapter_stats_strings));
		data += माप(adapter_stats_strings);
		स_नकल(data, loopback_stats_strings,
		       माप(loopback_stats_strings));
	पूर्ण अन्यथा अगर (stringset == ETH_SS_PRIV_FLAGS) अणु
		स_नकल(data, cxgb4_priv_flags_strings,
		       माप(cxgb4_priv_flags_strings));
	पूर्ण अन्यथा अगर (stringset == ETH_SS_TEST) अणु
		स_नकल(data, cxgb4_selftest_strings,
		       माप(cxgb4_selftest_strings));
	पूर्ण
पूर्ण

/* port stats मुख्यtained per queue of the port. They should be in the same
 * order as in stats_strings above.
 */
काष्ठा queue_port_stats अणु
	u64 tso;
	u64 uso;
	u64 tx_csum;
	u64 rx_csum;
	u64 vlan_ex;
	u64 vlan_ins;
	u64 gro_pkts;
	u64 gro_merged;
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	u64 tx_tls_encrypted_packets;
	u64 tx_tls_encrypted_bytes;
	u64 tx_tls_ctx;
	u64 tx_tls_ooo;
	u64 tx_tls_skip_no_sync_data;
	u64 tx_tls_drop_no_sync_data;
	u64 tx_tls_drop_bypass_req;
#पूर्ण_अगर
पूर्ण;

काष्ठा adapter_stats अणु
	u64 db_drop;
	u64 db_full;
	u64 db_empty;
	u64 wc_success;
	u64 wc_fail;
पूर्ण;

अटल व्योम collect_sge_port_stats(स्थिर काष्ठा adapter *adap,
				   स्थिर काष्ठा port_info *p,
				   काष्ठा queue_port_stats *s)
अणु
	स्थिर काष्ठा sge_eth_txq *tx = &adap->sge.ethtxq[p->first_qset];
	स्थिर काष्ठा sge_eth_rxq *rx = &adap->sge.ethrxq[p->first_qset];
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	स्थिर काष्ठा ch_ktls_port_stats_debug *ktls_stats;
#पूर्ण_अगर
	काष्ठा sge_eohw_txq *eohw_tx;
	अचिन्हित पूर्णांक i;

	स_रखो(s, 0, माप(*s));
	क्रम (i = 0; i < p->nqsets; i++, rx++, tx++) अणु
		s->tso += tx->tso;
		s->uso += tx->uso;
		s->tx_csum += tx->tx_cso;
		s->rx_csum += rx->stats.rx_cso;
		s->vlan_ex += rx->stats.vlan_ex;
		s->vlan_ins += tx->vlan_ins;
		s->gro_pkts += rx->stats.lro_pkts;
		s->gro_merged += rx->stats.lro_merged;
	पूर्ण

	अगर (adap->sge.eohw_txq) अणु
		eohw_tx = &adap->sge.eohw_txq[p->first_qset];
		क्रम (i = 0; i < p->nqsets; i++, eohw_tx++) अणु
			s->tso += eohw_tx->tso;
			s->uso += eohw_tx->uso;
			s->tx_csum += eohw_tx->tx_cso;
			s->vlan_ins += eohw_tx->vlan_ins;
		पूर्ण
	पूर्ण
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	ktls_stats = &adap->ch_ktls_stats.ktls_port[p->port_id];
	s->tx_tls_encrypted_packets =
		atomic64_पढ़ो(&ktls_stats->ktls_tx_encrypted_packets);
	s->tx_tls_encrypted_bytes =
		atomic64_पढ़ो(&ktls_stats->ktls_tx_encrypted_bytes);
	s->tx_tls_ctx = atomic64_पढ़ो(&ktls_stats->ktls_tx_ctx);
	s->tx_tls_ooo = atomic64_पढ़ो(&ktls_stats->ktls_tx_ooo);
	s->tx_tls_skip_no_sync_data =
		atomic64_पढ़ो(&ktls_stats->ktls_tx_skip_no_sync_data);
	s->tx_tls_drop_no_sync_data =
		atomic64_पढ़ो(&ktls_stats->ktls_tx_drop_no_sync_data);
	s->tx_tls_drop_bypass_req =
		atomic64_पढ़ो(&ktls_stats->ktls_tx_drop_bypass_req);
#पूर्ण_अगर
पूर्ण

अटल व्योम collect_adapter_stats(काष्ठा adapter *adap, काष्ठा adapter_stats *s)
अणु
	u64 val1, val2;

	स_रखो(s, 0, माप(*s));

	s->db_drop = adap->db_stats.db_drop;
	s->db_full = adap->db_stats.db_full;
	s->db_empty = adap->db_stats.db_empty;

	अगर (!is_t4(adap->params.chip)) अणु
		पूर्णांक v;

		v = t4_पढ़ो_reg(adap, SGE_STAT_CFG_A);
		अगर (STATSOURCE_T5_G(v) == 7) अणु
			val2 = t4_पढ़ो_reg(adap, SGE_STAT_MATCH_A);
			val1 = t4_पढ़ो_reg(adap, SGE_STAT_TOTAL_A);
			s->wc_success = val1 - val2;
			s->wc_fail = val2;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम get_stats(काष्ठा net_device *dev, काष्ठा ethtool_stats *stats,
		      u64 *data)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा lb_port_stats s;
	पूर्णांक i;
	u64 *p0;

	t4_get_port_stats_offset(adapter, pi->tx_chan,
				 (काष्ठा port_stats *)data,
				 &pi->stats_base);

	data += माप(काष्ठा port_stats) / माप(u64);
	collect_sge_port_stats(adapter, pi, (काष्ठा queue_port_stats *)data);
	data += माप(काष्ठा queue_port_stats) / माप(u64);
	collect_adapter_stats(adapter, (काष्ठा adapter_stats *)data);
	data += माप(काष्ठा adapter_stats) / माप(u64);

	*data++ = (u64)pi->port_id;
	स_रखो(&s, 0, माप(s));
	t4_get_lb_stats(adapter, pi->port_id, &s);

	p0 = &s.octets;
	क्रम (i = 0; i < ARRAY_SIZE(loopback_stats_strings) - 1; i++)
		*data++ = (अचिन्हित दीर्घ दीर्घ)*p0++;
पूर्ण

अटल व्योम get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
		     व्योम *buf)
अणु
	काष्ठा adapter *adap = netdev2adap(dev);
	माप_प्रकार buf_size;

	buf_size = t4_get_regs_len(adap);
	regs->version = mk_adap_vers(adap);
	t4_get_regs(adap, buf, buf_size);
पूर्ण

अटल पूर्णांक restart_स्वतःneg(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *p = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EAGAIN;
	अगर (p->link_cfg.स्वतःneg != AUTONEG_ENABLE)
		वापस -EINVAL;
	t4_restart_aneg(p->adapter, p->adapter->pf, p->tx_chan);
	वापस 0;
पूर्ण

अटल पूर्णांक identअगरy_port(काष्ठा net_device *dev,
			 क्रमागत ethtool_phys_id_state state)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा adapter *adap = netdev2adap(dev);

	अगर (state == ETHTOOL_ID_ACTIVE)
		val = 0xffff;
	अन्यथा अगर (state == ETHTOOL_ID_INACTIVE)
		val = 0;
	अन्यथा
		वापस -EINVAL;

	वापस t4_identअगरy_port(adap, adap->pf, netdev2pinfo(dev)->viid, val);
पूर्ण

/**
 *	from_fw_port_mod_type - translate Firmware Port/Module type to Ethtool
 *	@port_type: Firmware Port Type
 *	@mod_type: Firmware Module Type
 *
 *	Translate Firmware Port/Module type to Ethtool Port Type.
 */
अटल पूर्णांक from_fw_port_mod_type(क्रमागत fw_port_type port_type,
				 क्रमागत fw_port_module_type mod_type)
अणु
	अगर (port_type == FW_PORT_TYPE_BT_SGMII ||
	    port_type == FW_PORT_TYPE_BT_XFI ||
	    port_type == FW_PORT_TYPE_BT_XAUI) अणु
		वापस PORT_TP;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_FIBER_XFI ||
		   port_type == FW_PORT_TYPE_FIBER_XAUI) अणु
		वापस PORT_FIBRE;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_SFP ||
		   port_type == FW_PORT_TYPE_QSFP_10G ||
		   port_type == FW_PORT_TYPE_QSA ||
		   port_type == FW_PORT_TYPE_QSFP ||
		   port_type == FW_PORT_TYPE_CR4_QSFP ||
		   port_type == FW_PORT_TYPE_CR_QSFP ||
		   port_type == FW_PORT_TYPE_CR2_QSFP ||
		   port_type == FW_PORT_TYPE_SFP28) अणु
		अगर (mod_type == FW_PORT_MOD_TYPE_LR ||
		    mod_type == FW_PORT_MOD_TYPE_SR ||
		    mod_type == FW_PORT_MOD_TYPE_ER ||
		    mod_type == FW_PORT_MOD_TYPE_LRM)
			वापस PORT_FIBRE;
		अन्यथा अगर (mod_type == FW_PORT_MOD_TYPE_TWINAX_PASSIVE ||
			 mod_type == FW_PORT_MOD_TYPE_TWINAX_ACTIVE)
			वापस PORT_DA;
		अन्यथा
			वापस PORT_OTHER;
	पूर्ण अन्यथा अगर (port_type == FW_PORT_TYPE_KR4_100G ||
		   port_type == FW_PORT_TYPE_KR_SFP28 ||
		   port_type == FW_PORT_TYPE_KR_XLAUI) अणु
		वापस PORT_NONE;
	पूर्ण

	वापस PORT_OTHER;
पूर्ण

/**
 *	speed_to_fw_caps - translate Port Speed to Firmware Port Capabilities
 *	@speed: speed in Kb/s
 *
 *	Translates a specअगरic Port Speed पूर्णांकo a Firmware Port Capabilities
 *	value.
 */
अटल अचिन्हित पूर्णांक speed_to_fw_caps(पूर्णांक speed)
अणु
	अगर (speed == 100)
		वापस FW_PORT_CAP32_SPEED_100M;
	अगर (speed == 1000)
		वापस FW_PORT_CAP32_SPEED_1G;
	अगर (speed == 10000)
		वापस FW_PORT_CAP32_SPEED_10G;
	अगर (speed == 25000)
		वापस FW_PORT_CAP32_SPEED_25G;
	अगर (speed == 40000)
		वापस FW_PORT_CAP32_SPEED_40G;
	अगर (speed == 50000)
		वापस FW_PORT_CAP32_SPEED_50G;
	अगर (speed == 100000)
		वापस FW_PORT_CAP32_SPEED_100G;
	अगर (speed == 200000)
		वापस FW_PORT_CAP32_SPEED_200G;
	अगर (speed == 400000)
		वापस FW_PORT_CAP32_SPEED_400G;
	वापस 0;
पूर्ण

/**
 *	fw_caps_to_lmm - translate Firmware to ethtool Link Mode Mask
 *	@port_type: Firmware Port Type
 *	@fw_caps: Firmware Port Capabilities
 *	@link_mode_mask: ethtool Link Mode Mask
 *
 *	Translate a Firmware Port Capabilities specअगरication to an ethtool
 *	Link Mode Mask.
 */
अटल व्योम fw_caps_to_lmm(क्रमागत fw_port_type port_type,
			   fw_port_cap32_t fw_caps,
			   अचिन्हित दीर्घ *link_mode_mask)
अणु
	#घोषणा SET_LMM(__lmm_name) \
		करो अणु \
			__set_bit(ETHTOOL_LINK_MODE_ ## __lmm_name ## _BIT, \
				  link_mode_mask); \
		पूर्ण जबतक (0)

	#घोषणा FW_CAPS_TO_LMM(__fw_name, __lmm_name) \
		करो अणु \
			अगर (fw_caps & FW_PORT_CAP32_ ## __fw_name) \
				SET_LMM(__lmm_name); \
		पूर्ण जबतक (0)

	चयन (port_type) अणु
	हाल FW_PORT_TYPE_BT_SGMII:
	हाल FW_PORT_TYPE_BT_XFI:
	हाल FW_PORT_TYPE_BT_XAUI:
		SET_LMM(TP);
		FW_CAPS_TO_LMM(SPEED_100M, 100baseT_Full);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KX4:
	हाल FW_PORT_TYPE_KX:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP4_AP:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseR_FEC);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKX4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_FIBER_XFI:
	हाल FW_PORT_TYPE_FIBER_XAUI:
	हाल FW_PORT_TYPE_SFP:
	हाल FW_PORT_TYPE_QSFP_10G:
	हाल FW_PORT_TYPE_QSA:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		अवरोध;

	हाल FW_PORT_TYPE_BP40_BA:
	हाल FW_PORT_TYPE_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_CR_QSFP:
	हाल FW_PORT_TYPE_SFP28:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR_SFP28:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseKR_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR_XLAUI:
		SET_LMM(Backplane);
		FW_CAPS_TO_LMM(SPEED_1G, 1000baseKX_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseKR4_Full);
		अवरोध;

	हाल FW_PORT_TYPE_CR2_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseSR2_Full);
		अवरोध;

	हाल FW_PORT_TYPE_KR4_100G:
	हाल FW_PORT_TYPE_CR4_QSFP:
		SET_LMM(FIBRE);
		FW_CAPS_TO_LMM(SPEED_1G,  1000baseT_Full);
		FW_CAPS_TO_LMM(SPEED_10G, 10000baseKR_Full);
		FW_CAPS_TO_LMM(SPEED_40G, 40000baseSR4_Full);
		FW_CAPS_TO_LMM(SPEED_25G, 25000baseCR_Full);
		FW_CAPS_TO_LMM(SPEED_50G, 50000baseCR2_Full);
		FW_CAPS_TO_LMM(SPEED_100G, 100000baseCR4_Full);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (fw_caps & FW_PORT_CAP32_FEC_V(FW_PORT_CAP32_FEC_M)) अणु
		FW_CAPS_TO_LMM(FEC_RS, FEC_RS);
		FW_CAPS_TO_LMM(FEC_BASER_RS, FEC_BASER);
	पूर्ण अन्यथा अणु
		SET_LMM(FEC_NONE);
	पूर्ण

	FW_CAPS_TO_LMM(ANEG, Autoneg);
	FW_CAPS_TO_LMM(802_3_PAUSE, Pause);
	FW_CAPS_TO_LMM(802_3_ASM_सूची, Asym_Pause);

	#अघोषित FW_CAPS_TO_LMM
	#अघोषित SET_LMM
पूर्ण

/**
 *	lmm_to_fw_caps - translate ethtool Link Mode Mask to Firmware
 *	capabilities
 *	@link_mode_mask: ethtool Link Mode Mask
 *
 *	Translate ethtool Link Mode Mask पूर्णांकo a Firmware Port capabilities
 *	value.
 */
अटल अचिन्हित पूर्णांक lmm_to_fw_caps(स्थिर अचिन्हित दीर्घ *link_mode_mask)
अणु
	अचिन्हित पूर्णांक fw_caps = 0;

	#घोषणा LMM_TO_FW_CAPS(__lmm_name, __fw_name) \
		करो अणु \
			अगर (test_bit(ETHTOOL_LINK_MODE_ ## __lmm_name ## _BIT, \
				     link_mode_mask)) \
				fw_caps |= FW_PORT_CAP32_ ## __fw_name; \
		पूर्ण जबतक (0)

	LMM_TO_FW_CAPS(100baseT_Full, SPEED_100M);
	LMM_TO_FW_CAPS(1000baseT_Full, SPEED_1G);
	LMM_TO_FW_CAPS(10000baseT_Full, SPEED_10G);
	LMM_TO_FW_CAPS(40000baseSR4_Full, SPEED_40G);
	LMM_TO_FW_CAPS(25000baseCR_Full, SPEED_25G);
	LMM_TO_FW_CAPS(50000baseCR2_Full, SPEED_50G);
	LMM_TO_FW_CAPS(100000baseCR4_Full, SPEED_100G);

	#अघोषित LMM_TO_FW_CAPS

	वापस fw_caps;
पूर्ण

अटल पूर्णांक get_link_ksettings(काष्ठा net_device *dev,
			      काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा ethtool_link_settings *base = &link_ksettings->base;

	/* For the nonce, the Firmware करोesn't send up Port State changes
	 * when the Virtual Interface attached to the Port is करोwn.  So
	 * अगर it's down, let's grab any changes.
	 */
	अगर (!netअगर_running(dev))
		(व्योम)t4_update_port_info(pi);

	ethtool_link_ksettings_zero_link_mode(link_ksettings, supported);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, advertising);
	ethtool_link_ksettings_zero_link_mode(link_ksettings, lp_advertising);

	base->port = from_fw_port_mod_type(pi->port_type, pi->mod_type);

	अगर (pi->mdio_addr >= 0) अणु
		base->phy_address = pi->mdio_addr;
		base->mdio_support = (pi->port_type == FW_PORT_TYPE_BT_SGMII
				      ? ETH_MDIO_SUPPORTS_C22
				      : ETH_MDIO_SUPPORTS_C45);
	पूर्ण अन्यथा अणु
		base->phy_address = 255;
		base->mdio_support = 0;
	पूर्ण

	fw_caps_to_lmm(pi->port_type, pi->link_cfg.pcaps,
		       link_ksettings->link_modes.supported);
	fw_caps_to_lmm(pi->port_type,
		       t4_link_acaps(pi->adapter,
				     pi->lport,
				     &pi->link_cfg),
		       link_ksettings->link_modes.advertising);
	fw_caps_to_lmm(pi->port_type, pi->link_cfg.lpacaps,
		       link_ksettings->link_modes.lp_advertising);

	base->speed = (netअगर_carrier_ok(dev)
		       ? pi->link_cfg.speed
		       : SPEED_UNKNOWN);
	base->duplex = DUPLEX_FULL;

	base->स्वतःneg = pi->link_cfg.स्वतःneg;
	अगर (pi->link_cfg.pcaps & FW_PORT_CAP32_ANEG)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     supported, Autoneg);
	अगर (pi->link_cfg.स्वतःneg)
		ethtool_link_ksettings_add_link_mode(link_ksettings,
						     advertising, Autoneg);

	वापस 0;
पूर्ण

अटल पूर्णांक set_link_ksettings(काष्ठा net_device *dev,
			    स्थिर काष्ठा ethtool_link_ksettings *link_ksettings)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा link_config *lc = &pi->link_cfg;
	स्थिर काष्ठा ethtool_link_settings *base = &link_ksettings->base;
	काष्ठा link_config old_lc;
	अचिन्हित पूर्णांक fw_caps;
	पूर्णांक ret = 0;

	/* only full-duplex supported */
	अगर (base->duplex != DUPLEX_FULL)
		वापस -EINVAL;

	old_lc = *lc;
	अगर (!(lc->pcaps & FW_PORT_CAP32_ANEG) ||
	    base->स्वतःneg == AUTONEG_DISABLE) अणु
		fw_caps = speed_to_fw_caps(base->speed);

		/* Speed must be supported by Physical Port Capabilities. */
		अगर (!(lc->pcaps & fw_caps))
			वापस -EINVAL;

		lc->speed_caps = fw_caps;
		lc->acaps = fw_caps;
	पूर्ण अन्यथा अणु
		fw_caps =
			lmm_to_fw_caps(link_ksettings->link_modes.advertising);
		अगर (!(lc->pcaps & fw_caps))
			वापस -EINVAL;
		lc->speed_caps = 0;
		lc->acaps = fw_caps | FW_PORT_CAP32_ANEG;
	पूर्ण
	lc->स्वतःneg = base->स्वतःneg;

	/* If the firmware rejects the Link Configuration request, back out
	 * the changes and report the error.
	 */
	ret = t4_link_l1cfg(pi->adapter, pi->adapter->mbox, pi->tx_chan, lc);
	अगर (ret)
		*lc = old_lc;

	वापस ret;
पूर्ण

/* Translate the Firmware FEC value पूर्णांकo the ethtool value. */
अटल अंतरभूत अचिन्हित पूर्णांक fwcap_to_eth_fec(अचिन्हित पूर्णांक fw_fec)
अणु
	अचिन्हित पूर्णांक eth_fec = 0;

	अगर (fw_fec & FW_PORT_CAP32_FEC_RS)
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (fw_fec & FW_PORT_CAP32_FEC_BASER_RS)
		eth_fec |= ETHTOOL_FEC_BASER;

	/* अगर nothing is set, then FEC is off */
	अगर (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	वापस eth_fec;
पूर्ण

/* Translate Common Code FEC value पूर्णांकo ethtool value. */
अटल अंतरभूत अचिन्हित पूर्णांक cc_to_eth_fec(अचिन्हित पूर्णांक cc_fec)
अणु
	अचिन्हित पूर्णांक eth_fec = 0;

	अगर (cc_fec & FEC_AUTO)
		eth_fec |= ETHTOOL_FEC_AUTO;
	अगर (cc_fec & FEC_RS)
		eth_fec |= ETHTOOL_FEC_RS;
	अगर (cc_fec & FEC_BASER_RS)
		eth_fec |= ETHTOOL_FEC_BASER;

	/* अगर nothing is set, then FEC is off */
	अगर (!eth_fec)
		eth_fec = ETHTOOL_FEC_OFF;

	वापस eth_fec;
पूर्ण

/* Translate ethtool FEC value पूर्णांकo Common Code value. */
अटल अंतरभूत अचिन्हित पूर्णांक eth_to_cc_fec(अचिन्हित पूर्णांक eth_fec)
अणु
	अचिन्हित पूर्णांक cc_fec = 0;

	अगर (eth_fec & ETHTOOL_FEC_OFF)
		वापस cc_fec;

	अगर (eth_fec & ETHTOOL_FEC_AUTO)
		cc_fec |= FEC_AUTO;
	अगर (eth_fec & ETHTOOL_FEC_RS)
		cc_fec |= FEC_RS;
	अगर (eth_fec & ETHTOOL_FEC_BASER)
		cc_fec |= FEC_BASER_RS;

	वापस cc_fec;
पूर्ण

अटल पूर्णांक get_fecparam(काष्ठा net_device *dev, काष्ठा ethtool_fecparam *fec)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा link_config *lc = &pi->link_cfg;

	/* Translate the Firmware FEC Support पूर्णांकo the ethtool value.  We
	 * always support IEEE 802.3 "automatic" selection of Link FEC type अगर
	 * any FEC is supported.
	 */
	fec->fec = fwcap_to_eth_fec(lc->pcaps);
	अगर (fec->fec != ETHTOOL_FEC_OFF)
		fec->fec |= ETHTOOL_FEC_AUTO;

	/* Translate the current पूर्णांकernal FEC parameters पूर्णांकo the
	 * ethtool values.
	 */
	fec->active_fec = cc_to_eth_fec(lc->fec);

	वापस 0;
पूर्ण

अटल पूर्णांक set_fecparam(काष्ठा net_device *dev, काष्ठा ethtool_fecparam *fec)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा link_config *lc = &pi->link_cfg;
	काष्ठा link_config old_lc;
	पूर्णांक ret;

	/* Save old Link Configuration in हाल the L1 Configure below
	 * fails.
	 */
	old_lc = *lc;

	/* Try to perक्रमm the L1 Configure and वापस the result of that
	 * efक्रमt.  If it fails, revert the attempted change.
	 */
	lc->requested_fec = eth_to_cc_fec(fec->fec);
	ret = t4_link_l1cfg(pi->adapter, pi->adapter->mbox,
			    pi->tx_chan, lc);
	अगर (ret)
		*lc = old_lc;
	वापस ret;
पूर्ण

अटल व्योम get_छोड़ोparam(काष्ठा net_device *dev,
			   काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा port_info *p = netdev_priv(dev);

	eछोड़ो->स्वतःneg = (p->link_cfg.requested_fc & PAUSE_AUTONEG) != 0;
	eछोड़ो->rx_छोड़ो = (p->link_cfg.advertised_fc & PAUSE_RX) != 0;
	eछोड़ो->tx_छोड़ो = (p->link_cfg.advertised_fc & PAUSE_TX) != 0;
पूर्ण

अटल पूर्णांक set_छोड़ोparam(काष्ठा net_device *dev,
			  काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा port_info *p = netdev_priv(dev);
	काष्ठा link_config *lc = &p->link_cfg;

	अगर (eछोड़ो->स्वतःneg == AUTONEG_DISABLE)
		lc->requested_fc = 0;
	अन्यथा अगर (lc->pcaps & FW_PORT_CAP32_ANEG)
		lc->requested_fc = PAUSE_AUTONEG;
	अन्यथा
		वापस -EINVAL;

	अगर (eछोड़ो->rx_छोड़ो)
		lc->requested_fc |= PAUSE_RX;
	अगर (eछोड़ो->tx_छोड़ो)
		lc->requested_fc |= PAUSE_TX;
	अगर (netअगर_running(dev))
		वापस t4_link_l1cfg(p->adapter, p->adapter->mbox, p->tx_chan,
				     lc);
	वापस 0;
पूर्ण

अटल व्योम get_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा sge *s = &pi->adapter->sge;

	e->rx_max_pending = MAX_RX_BUFFERS;
	e->rx_mini_max_pending = MAX_RSPQ_ENTRIES;
	e->rx_jumbo_max_pending = 0;
	e->tx_max_pending = MAX_TXQ_ENTRIES;

	e->rx_pending = s->ethrxq[pi->first_qset].fl.size - 8;
	e->rx_mini_pending = s->ethrxq[pi->first_qset].rspq.size;
	e->rx_jumbo_pending = 0;
	e->tx_pending = s->ethtxq[pi->first_qset].q.size;
पूर्ण

अटल पूर्णांक set_sge_param(काष्ठा net_device *dev, काष्ठा ethtool_ringparam *e)
अणु
	पूर्णांक i;
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;
	काष्ठा sge *s = &adapter->sge;

	अगर (e->rx_pending > MAX_RX_BUFFERS || e->rx_jumbo_pending ||
	    e->tx_pending > MAX_TXQ_ENTRIES ||
	    e->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    e->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES || e->tx_pending < MIN_TXQ_ENTRIES)
		वापस -EINVAL;

	अगर (adapter->flags & CXGB4_FULL_INIT_DONE)
		वापस -EBUSY;

	क्रम (i = 0; i < pi->nqsets; ++i) अणु
		s->ethtxq[pi->first_qset + i].q.size = e->tx_pending;
		s->ethrxq[pi->first_qset + i].fl.size = e->rx_pending + 8;
		s->ethrxq[pi->first_qset + i].rspq.size = e->rx_mini_pending;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * set_rx_पूर्णांकr_params - set a net devices's RX पूर्णांकerrupt holकरोff paramete!
 * @dev: the network device
 * @us: the hold-off समय in us, or 0 to disable समयr
 * @cnt: the hold-off packet count, or 0 to disable counter
 *
 * Set the RX पूर्णांकerrupt hold-off parameters क्रम a network device.
 */
अटल पूर्णांक set_rx_पूर्णांकr_params(काष्ठा net_device *dev,
			      अचिन्हित पूर्णांक us, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक i, err;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_rxq *q = &adap->sge.ethrxq[pi->first_qset];

	क्रम (i = 0; i < pi->nqsets; i++, q++) अणु
		err = cxgb4_set_rspq_पूर्णांकr_params(&q->rspq, us, cnt);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक set_adaptive_rx_setting(काष्ठा net_device *dev, पूर्णांक adaptive_rx)
अणु
	पूर्णांक i;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_rxq *q = &adap->sge.ethrxq[pi->first_qset];

	क्रम (i = 0; i < pi->nqsets; i++, q++)
		q->rspq.adaptive_rx = adaptive_rx;

	वापस 0;
पूर्ण

अटल पूर्णांक get_adaptive_rx_setting(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_rxq *q = &adap->sge.ethrxq[pi->first_qset];

	वापस q->rspq.adaptive_rx;
पूर्ण

/* Return the current global Adapter SGE Doorbell Queue Timer Tick क्रम all
 * Ethernet TX Queues.
 */
अटल पूर्णांक get_dbqसमयr_tick(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;

	अगर (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		वापस 0;

	वापस adap->sge.dbqसमयr_tick;
पूर्ण

/* Return the SGE Doorbell Queue Timer Value क्रम the Ethernet TX Queues
 * associated with a Network Device.
 */
अटल पूर्णांक get_dbqसमयr(काष्ठा net_device *dev)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge_eth_txq *txq;

	txq = &adap->sge.ethtxq[pi->first_qset];

	अगर (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		वापस 0;

	/* all of the TX Queues use the same Timer Index */
	वापस adap->sge.dbqसमयr_val[txq->dbqसमयrix];
पूर्ण

/* Set the global Adapter SGE Doorbell Queue Timer Tick क्रम all Ethernet TX
 * Queues.  This is the fundamental "Tick" that sets the scale of values which
 * can be used.  Inभागidual Ethernet TX Queues index पूर्णांकo a relatively small
 * array of Tick Multipliers.  Changing the base Tick will thus change all of
 * the resulting Timer Values associated with those multipliers क्रम all
 * Ethernet TX Queues.
 */
अटल पूर्णांक set_dbqसमयr_tick(काष्ठा net_device *dev, पूर्णांक usecs)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge *s = &adap->sge;
	u32 param, val;
	पूर्णांक ret;

	अगर (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		वापस 0;

	/* वापस early अगर it's the same Timer Tick we're alपढ़ोy using */
	अगर (s->dbqसमयr_tick == usecs)
		वापस 0;

	/* attempt to set the new Timer Tick value */
	param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DBQ_TIMERTICK));
	val = usecs;
	ret = t4_set_params(adap, adap->mbox, adap->pf, 0, 1, &param, &val);
	अगर (ret)
		वापस ret;
	s->dbqसमयr_tick = usecs;

	/* अगर successful, reपढ़ो resulting dependent Timer values */
	ret = t4_पढ़ो_sge_dbqसमयrs(adap, ARRAY_SIZE(s->dbqसमयr_val),
				    s->dbqसमयr_val);
	वापस ret;
पूर्ण

/* Set the SGE Doorbell Queue Timer Value क्रम the Ethernet TX Queues
 * associated with a Network Device.  There is a relatively small array of
 * possible Timer Values so we need to pick the बंदst value available.
 */
अटल पूर्णांक set_dbqसमयr(काष्ठा net_device *dev, पूर्णांक usecs)
अणु
	पूर्णांक qix, समयrix, min_समयrix, delta, min_delta;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	काष्ठा sge *s = &adap->sge;
	काष्ठा sge_eth_txq *txq;
	u32 param, val;
	पूर्णांक ret;

	अगर (!(adap->flags & CXGB4_SGE_DBQ_TIMER))
		वापस 0;

	/* Find the SGE Doorbell Timer Value that's बंदst to the requested
	 * value.
	 */
	min_delta = पूर्णांक_उच्च;
	min_समयrix = 0;
	क्रम (समयrix = 0; समयrix < ARRAY_SIZE(s->dbqसमयr_val); समयrix++) अणु
		delta = s->dbqसमयr_val[समयrix] - usecs;
		अगर (delta < 0)
			delta = -delta;
		अगर (delta < min_delta) अणु
			min_delta = delta;
			min_समयrix = समयrix;
		पूर्ण
	पूर्ण

	/* Return early अगर it's the same Timer Index we're alपढ़ोy using.
	 * We use the same Timer Index क्रम all of the TX Queues क्रम an
	 * पूर्णांकerface so it's only necessary to check the first one.
	 */
	txq = &s->ethtxq[pi->first_qset];
	अगर (txq->dbqसमयrix == min_समयrix)
		वापस 0;

	क्रम (qix = 0; qix < pi->nqsets; qix++, txq++) अणु
		अगर (adap->flags & CXGB4_FULL_INIT_DONE) अणु
			param =
			 (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DMAQ) |
			  FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DMAQ_EQ_TIMERIX) |
			  FW_PARAMS_PARAM_YZ_V(txq->q.cntxt_id));
			val = min_समयrix;
			ret = t4_set_params(adap, adap->mbox, adap->pf, 0,
					    1, &param, &val);
			अगर (ret)
				वापस ret;
		पूर्ण
		txq->dbqसमयrix = min_समयrix;
	पूर्ण
	वापस 0;
पूर्ण

/* Set the global Adapter SGE Doorbell Queue Timer Tick क्रम all Ethernet TX
 * Queues and the Timer Value क्रम the Ethernet TX Queues associated with a
 * Network Device.  Since changing the global Tick changes all of the
 * available Timer Values, we need to करो this first beक्रमe selecting the
 * resulting बंदst Timer Value.  Moreover, since the Tick is global,
 * changing it affects the Timer Values क्रम all Network Devices on the
 * adapter.  So, beक्रमe changing the Tick, we grab all of the current Timer
 * Values क्रम other Network Devices on this Adapter and then attempt to select
 * new Timer Values which are बंद to the old values ...
 */
अटल पूर्णांक set_dbqसमयr_tickval(काष्ठा net_device *dev,
				पूर्णांक tick_usecs, पूर्णांक समयr_usecs)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	पूर्णांक समयr[MAX_NPORTS];
	अचिन्हित पूर्णांक port;
	पूर्णांक ret;

	/* Grab the other adapter Network Interface current समयrs and fill in
	 * the new one क्रम this Network Interface.
	 */
	क्रम_each_port(adap, port)
		अगर (port == pi->port_id)
			समयr[port] = समयr_usecs;
		अन्यथा
			समयr[port] = get_dbqसमयr(adap->port[port]);

	/* Change the global Tick first ... */
	ret = set_dbqसमयr_tick(dev, tick_usecs);
	अगर (ret)
		वापस ret;

	/* ... and then set all of the Network Interface Timer Values ... */
	क्रम_each_port(adap, port) अणु
		ret = set_dbqसमयr(adap->port[port], समयr[port]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक set_coalesce(काष्ठा net_device *dev,
			काष्ठा ethtool_coalesce *coalesce)
अणु
	पूर्णांक ret;

	set_adaptive_rx_setting(dev, coalesce->use_adaptive_rx_coalesce);

	ret = set_rx_पूर्णांकr_params(dev, coalesce->rx_coalesce_usecs,
				 coalesce->rx_max_coalesced_frames);
	अगर (ret)
		वापस ret;

	वापस set_dbqसमयr_tickval(dev,
				    coalesce->tx_coalesce_usecs_irq,
				    coalesce->tx_coalesce_usecs);
पूर्ण

अटल पूर्णांक get_coalesce(काष्ठा net_device *dev, काष्ठा ethtool_coalesce *c)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	स्थिर काष्ठा adapter *adap = pi->adapter;
	स्थिर काष्ठा sge_rspq *rq = &adap->sge.ethrxq[pi->first_qset].rspq;

	c->rx_coalesce_usecs = qसमयr_val(adap, rq);
	c->rx_max_coalesced_frames = (rq->पूर्णांकr_params & QINTR_CNT_EN_F) ?
		adap->sge.counter_val[rq->pktcnt_idx] : 0;
	c->use_adaptive_rx_coalesce = get_adaptive_rx_setting(dev);
	c->tx_coalesce_usecs_irq = get_dbqसमयr_tick(dev);
	c->tx_coalesce_usecs = get_dbqसमयr(dev);
	वापस 0;
पूर्ण

/* The next two routines implement eeprom पढ़ो/ग_लिखो from physical addresses.
 */
अटल पूर्णांक eeprom_rd_phys(काष्ठा adapter *adap, अचिन्हित पूर्णांक phys_addr, u32 *v)
अणु
	पूर्णांक vaddr = t4_eeprom_ptov(phys_addr, adap->pf, EEPROMPFSIZE);

	अगर (vaddr >= 0)
		vaddr = pci_पढ़ो_vpd(adap->pdev, vaddr, माप(u32), v);
	वापस vaddr < 0 ? vaddr : 0;
पूर्ण

अटल पूर्णांक eeprom_wr_phys(काष्ठा adapter *adap, अचिन्हित पूर्णांक phys_addr, u32 v)
अणु
	पूर्णांक vaddr = t4_eeprom_ptov(phys_addr, adap->pf, EEPROMPFSIZE);

	अगर (vaddr >= 0)
		vaddr = pci_ग_लिखो_vpd(adap->pdev, vaddr, माप(u32), &v);
	वापस vaddr < 0 ? vaddr : 0;
पूर्ण

#घोषणा EEPROM_MAGIC 0x38E2F10C

अटल पूर्णांक get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *e,
		      u8 *data)
अणु
	पूर्णांक i, err = 0;
	काष्ठा adapter *adapter = netdev2adap(dev);
	u8 *buf = kvzalloc(EEPROMSIZE, GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	e->magic = EEPROM_MAGIC;
	क्रम (i = e->offset & ~3; !err && i < e->offset + e->len; i += 4)
		err = eeprom_rd_phys(adapter, i, (u32 *)&buf[i]);

	अगर (!err)
		स_नकल(data, buf + e->offset, e->len);
	kvमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक set_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		      u8 *data)
अणु
	u8 *buf;
	पूर्णांक err = 0;
	u32 aligned_offset, aligned_len, *p;
	काष्ठा adapter *adapter = netdev2adap(dev);

	अगर (eeprom->magic != EEPROM_MAGIC)
		वापस -EINVAL;

	aligned_offset = eeprom->offset & ~3;
	aligned_len = (eeprom->len + (eeprom->offset & 3) + 3) & ~3;

	अगर (adapter->pf > 0) अणु
		u32 start = 1024 + adapter->pf * EEPROMPFSIZE;

		अगर (aligned_offset < start ||
		    aligned_offset + aligned_len > start + EEPROMPFSIZE)
			वापस -EPERM;
	पूर्ण

	अगर (aligned_offset != eeprom->offset || aligned_len != eeprom->len) अणु
		/* RMW possibly needed क्रम first or last words.
		 */
		buf = kvzalloc(aligned_len, GFP_KERNEL);
		अगर (!buf)
			वापस -ENOMEM;
		err = eeprom_rd_phys(adapter, aligned_offset, (u32 *)buf);
		अगर (!err && aligned_len > 4)
			err = eeprom_rd_phys(adapter,
					     aligned_offset + aligned_len - 4,
					     (u32 *)&buf[aligned_len - 4]);
		अगर (err)
			जाओ out;
		स_नकल(buf + (eeprom->offset & 3), data, eeprom->len);
	पूर्ण अन्यथा अणु
		buf = data;
	पूर्ण

	err = t4_seeprom_wp(adapter, false);
	अगर (err)
		जाओ out;

	क्रम (p = (u32 *)buf; !err && aligned_len; aligned_len -= 4, p++) अणु
		err = eeprom_wr_phys(adapter, aligned_offset, *p);
		aligned_offset += 4;
	पूर्ण

	अगर (!err)
		err = t4_seeprom_wp(adapter, true);
out:
	अगर (buf != data)
		kvमुक्त(buf);
	वापस err;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_flash_bootcfg(काष्ठा net_device *netdev,
				       स्थिर u8 *data, u32 size)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	पूर्णांक ret;

	ret = t4_load_bootcfg(adap, data, size);
	अगर (ret)
		dev_err(adap->pdev_dev, "Failed to load boot cfg image\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_flash_boot(काष्ठा net_device *netdev,
				    स्थिर u8 *bdata, u32 size)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	अचिन्हित पूर्णांक offset;
	u8 *data;
	पूर्णांक ret;

	data = kmemdup(bdata, size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	offset = OFFSET_G(t4_पढ़ो_reg(adap, PF_REG(0, PCIE_PF_EXPROM_OFST_A)));

	ret = t4_load_boot(adap, data, offset, size);
	अगर (ret)
		dev_err(adap->pdev_dev, "Failed to load boot image\n");

	kमुक्त(data);
	वापस ret;
पूर्ण

#घोषणा CXGB4_PHY_SIG 0x130000ea

अटल पूर्णांक cxgb4_validate_phy_image(स्थिर u8 *data, u32 *size)
अणु
	काष्ठा cxgb4_fw_data *header;

	header = (काष्ठा cxgb4_fw_data *)data;
	अगर (be32_to_cpu(header->signature) != CXGB4_PHY_SIG)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_flash_phy(काष्ठा net_device *netdev,
				   स्थिर u8 *data, u32 size)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	पूर्णांक ret;

	ret = cxgb4_validate_phy_image(data, शून्य);
	अगर (ret) अणु
		dev_err(adap->pdev_dev, "PHY signature mismatch\n");
		वापस ret;
	पूर्ण

	/* We have to RESET the chip/firmware because we need the
	 * chip in uninitialized state क्रम loading new PHY image.
	 * Otherwise, the running firmware will only store the PHY
	 * image in local RAM which will be lost after next reset.
	 */
	ret = t4_fw_reset(adap, adap->mbox, PIORSTMODE_F | PIORST_F);
	अगर (ret < 0) अणु
		dev_err(adap->pdev_dev,
			"Set FW to RESET for flashing PHY FW failed. ret: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = t4_load_phy_fw(adap, MEMWIN_NIC, शून्य, data, size);
	अगर (ret < 0) अणु
		dev_err(adap->pdev_dev, "Failed to load PHY FW. ret: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_flash_fw(काष्ठा net_device *netdev,
				  स्थिर u8 *data, u32 size)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	अचिन्हित पूर्णांक mbox = PCIE_FW_MASTER_M + 1;
	पूर्णांक ret;

	/* If the adapter has been fully initialized then we'll go ahead and
	 * try to get the firmware's cooperation in upgrading to the new
	 * firmware image otherwise we'll try to करो the entire job from the
	 * host ... and we always "force" the operation in this path.
	 */
	अगर (adap->flags & CXGB4_FULL_INIT_DONE)
		mbox = adap->mbox;

	ret = t4_fw_upgrade(adap, mbox, data, size, 1);
	अगर (ret)
		dev_err(adap->pdev_dev,
			"Failed to flash firmware\n");

	वापस ret;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_flash_region(काष्ठा net_device *netdev,
				      स्थिर u8 *data, u32 size, u32 region)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	पूर्णांक ret;

	चयन (region) अणु
	हाल CXGB4_ETHTOOL_FLASH_FW:
		ret = cxgb4_ethtool_flash_fw(netdev, data, size);
		अवरोध;
	हाल CXGB4_ETHTOOL_FLASH_PHY:
		ret = cxgb4_ethtool_flash_phy(netdev, data, size);
		अवरोध;
	हाल CXGB4_ETHTOOL_FLASH_BOOT:
		ret = cxgb4_ethtool_flash_boot(netdev, data, size);
		अवरोध;
	हाल CXGB4_ETHTOOL_FLASH_BOOTCFG:
		ret = cxgb4_ethtool_flash_bootcfg(netdev, data, size);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (!ret)
		dev_info(adap->pdev_dev,
			 "loading %s successful, reload cxgb4 driver\n",
			 flash_region_strings[region]);
	वापस ret;
पूर्ण

#घोषणा CXGB4_FW_SIG 0x4368656c
#घोषणा CXGB4_FW_SIG_OFFSET 0x160

अटल पूर्णांक cxgb4_validate_fw_image(स्थिर u8 *data, u32 *size)
अणु
	काष्ठा cxgb4_fw_data *header;

	header = (काष्ठा cxgb4_fw_data *)&data[CXGB4_FW_SIG_OFFSET];
	अगर (be32_to_cpu(header->signature) != CXGB4_FW_SIG)
		वापस -EINVAL;

	अगर (size)
		*size = be16_to_cpu(((काष्ठा fw_hdr *)data)->len512) * 512;

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_validate_bootcfg_image(स्थिर u8 *data, u32 *size)
अणु
	काष्ठा cxgb4_bootcfg_data *header;

	header = (काष्ठा cxgb4_bootcfg_data *)data;
	अगर (le16_to_cpu(header->signature) != BOOT_CFG_SIG)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_validate_boot_image(स्थिर u8 *data, u32 *size)
अणु
	काष्ठा cxgb4_pci_exp_rom_header *exp_header;
	काष्ठा cxgb4_pcir_data *pcir_header;
	काष्ठा legacy_pci_rom_hdr *header;
	स्थिर u8 *cur_header = data;
	u16 pcir_offset;

	exp_header = (काष्ठा cxgb4_pci_exp_rom_header *)data;

	अगर (le16_to_cpu(exp_header->signature) != BOOT_SIGNATURE)
		वापस -EINVAL;

	अगर (size) अणु
		करो अणु
			header = (काष्ठा legacy_pci_rom_hdr *)cur_header;
			pcir_offset = le16_to_cpu(header->pcir_offset);
			pcir_header = (काष्ठा cxgb4_pcir_data *)(cur_header +
				      pcir_offset);

			*size += header->size512 * 512;
			cur_header += header->size512 * 512;
		पूर्ण जबतक (!(pcir_header->indicator & CXGB4_HDR_INDI));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_ethtool_get_flash_region(स्थिर u8 *data, u32 *size)
अणु
	अगर (!cxgb4_validate_fw_image(data, size))
		वापस CXGB4_ETHTOOL_FLASH_FW;
	अगर (!cxgb4_validate_boot_image(data, size))
		वापस CXGB4_ETHTOOL_FLASH_BOOT;
	अगर (!cxgb4_validate_phy_image(data, size))
		वापस CXGB4_ETHTOOL_FLASH_PHY;
	अगर (!cxgb4_validate_bootcfg_image(data, size))
		वापस CXGB4_ETHTOOL_FLASH_BOOTCFG;

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक set_flash(काष्ठा net_device *netdev, काष्ठा ethtool_flash *ef)
अणु
	काष्ठा adapter *adap = netdev2adap(netdev);
	स्थिर काष्ठा firmware *fw;
	अचिन्हित पूर्णांक master;
	u8 master_vld = 0;
	स्थिर u8 *fw_data;
	माप_प्रकार fw_size;
	u32 size = 0;
	u32 pcie_fw;
	पूर्णांक region;
	पूर्णांक ret;

	pcie_fw = t4_पढ़ो_reg(adap, PCIE_FW_A);
	master = PCIE_FW_MASTER_G(pcie_fw);
	अगर (pcie_fw & PCIE_FW_MASTER_VLD_F)
		master_vld = 1;
	/* अगर csiostor is the master वापस */
	अगर (master_vld && (master != adap->pf)) अणु
		dev_warn(adap->pdev_dev,
			 "cxgb4 driver needs to be loaded as MASTER to support FW flash\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ef->data[माप(ef->data) - 1] = '\0';
	ret = request_firmware(&fw, ef->data, adap->pdev_dev);
	अगर (ret < 0)
		वापस ret;

	fw_data = fw->data;
	fw_size = fw->size;
	अगर (ef->region == ETHTOOL_FLASH_ALL_REGIONS) अणु
		जबतक (fw_size > 0) अणु
			size = 0;
			region = cxgb4_ethtool_get_flash_region(fw_data, &size);
			अगर (region < 0 || !size) अणु
				ret = region;
				जाओ out_मुक्त_fw;
			पूर्ण

			ret = cxgb4_ethtool_flash_region(netdev, fw_data, size,
							 region);
			अगर (ret)
				जाओ out_मुक्त_fw;

			fw_data += size;
			fw_size -= size;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = cxgb4_ethtool_flash_region(netdev, fw_data, fw_size,
						 ef->region);
	पूर्ण

out_मुक्त_fw:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *ts_info)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा  adapter *adapter = pi->adapter;

	ts_info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
				   SOF_TIMESTAMPING_RX_SOFTWARE |
				   SOF_TIMESTAMPING_SOFTWARE;

	ts_info->so_बारtamping |= SOF_TIMESTAMPING_RX_HARDWARE |
				    SOF_TIMESTAMPING_TX_HARDWARE |
				    SOF_TIMESTAMPING_RAW_HARDWARE;

	ts_info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			    (1 << HWTSTAMP_TX_ON);

	ts_info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			      (1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ);

	अगर (adapter->ptp_घड़ी)
		ts_info->phc_index = ptp_घड़ी_index(adapter->ptp_घड़ी);
	अन्यथा
		ts_info->phc_index = -1;

	वापस 0;
पूर्ण

अटल u32 get_rss_table_size(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);

	वापस pi->rss_size;
पूर्ण

अटल पूर्णांक get_rss_table(काष्ठा net_device *dev, u32 *p, u8 *key, u8 *hfunc)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	अचिन्हित पूर्णांक n = pi->rss_size;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!p)
		वापस 0;
	जबतक (n--)
		p[n] = pi->rss[n];
	वापस 0;
पूर्ण

अटल पूर्णांक set_rss_table(काष्ठा net_device *dev, स्थिर u32 *p, स्थिर u8 *key,
			 स्थिर u8 hfunc)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा port_info *pi = netdev_priv(dev);

	/* We require at least one supported parameter to be changed and no
	 * change in any of the unsupported parameters
	 */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!p)
		वापस 0;

	/* Interface must be brought up atleast once */
	अगर (pi->adapter->flags & CXGB4_FULL_INIT_DONE) अणु
		क्रम (i = 0; i < pi->rss_size; i++)
			pi->rss[i] = p[i];

		वापस cxgb4_ग_लिखो_rss(pi, pi->rss);
	पूर्ण

	वापस -EPERM;
पूर्ण

अटल काष्ठा filter_entry *cxgb4_get_filter_entry(काष्ठा adapter *adap,
						   u32 ftid)
अणु
	काष्ठा tid_info *t = &adap->tids;

	अगर (ftid >= t->hpftid_base && ftid < t->hpftid_base + t->nhpftids)
		वापस &t->hpftid_tab[ftid - t->hpftid_base];

	अगर (ftid >= t->ftid_base && ftid < t->ftid_base + t->nftids)
		वापस &t->ftid_tab[ftid - t->ftid_base];

	वापस lookup_tid(t, ftid);
पूर्ण

अटल व्योम cxgb4_fill_filter_rule(काष्ठा ethtool_rx_flow_spec *fs,
				   काष्ठा ch_filter_specअगरication *dfs)
अणु
	चयन (dfs->val.proto) अणु
	हाल IPPROTO_TCP:
		अगर (dfs->type)
			fs->flow_type = TCP_V6_FLOW;
		अन्यथा
			fs->flow_type = TCP_V4_FLOW;
		अवरोध;
	हाल IPPROTO_UDP:
		अगर (dfs->type)
			fs->flow_type = UDP_V6_FLOW;
		अन्यथा
			fs->flow_type = UDP_V4_FLOW;
		अवरोध;
	पूर्ण

	अगर (dfs->type) अणु
		fs->h_u.tcp_ip6_spec.psrc = cpu_to_be16(dfs->val.fport);
		fs->m_u.tcp_ip6_spec.psrc = cpu_to_be16(dfs->mask.fport);
		fs->h_u.tcp_ip6_spec.pdst = cpu_to_be16(dfs->val.lport);
		fs->m_u.tcp_ip6_spec.pdst = cpu_to_be16(dfs->mask.lport);
		स_नकल(&fs->h_u.tcp_ip6_spec.ip6src, &dfs->val.fip[0],
		       माप(fs->h_u.tcp_ip6_spec.ip6src));
		स_नकल(&fs->m_u.tcp_ip6_spec.ip6src, &dfs->mask.fip[0],
		       माप(fs->m_u.tcp_ip6_spec.ip6src));
		स_नकल(&fs->h_u.tcp_ip6_spec.ip6dst, &dfs->val.lip[0],
		       माप(fs->h_u.tcp_ip6_spec.ip6dst));
		स_नकल(&fs->m_u.tcp_ip6_spec.ip6dst, &dfs->mask.lip[0],
		       माप(fs->m_u.tcp_ip6_spec.ip6dst));
		fs->h_u.tcp_ip6_spec.tclass = dfs->val.tos;
		fs->m_u.tcp_ip6_spec.tclass = dfs->mask.tos;
	पूर्ण अन्यथा अणु
		fs->h_u.tcp_ip4_spec.psrc = cpu_to_be16(dfs->val.fport);
		fs->m_u.tcp_ip4_spec.psrc = cpu_to_be16(dfs->mask.fport);
		fs->h_u.tcp_ip4_spec.pdst = cpu_to_be16(dfs->val.lport);
		fs->m_u.tcp_ip4_spec.pdst = cpu_to_be16(dfs->mask.lport);
		स_नकल(&fs->h_u.tcp_ip4_spec.ip4src, &dfs->val.fip[0],
		       माप(fs->h_u.tcp_ip4_spec.ip4src));
		स_नकल(&fs->m_u.tcp_ip4_spec.ip4src, &dfs->mask.fip[0],
		       माप(fs->m_u.tcp_ip4_spec.ip4src));
		स_नकल(&fs->h_u.tcp_ip4_spec.ip4dst, &dfs->val.lip[0],
		       माप(fs->h_u.tcp_ip4_spec.ip4dst));
		स_नकल(&fs->m_u.tcp_ip4_spec.ip4dst, &dfs->mask.lip[0],
		       माप(fs->m_u.tcp_ip4_spec.ip4dst));
		fs->h_u.tcp_ip4_spec.tos = dfs->val.tos;
		fs->m_u.tcp_ip4_spec.tos = dfs->mask.tos;
	पूर्ण
	fs->h_ext.vlan_tci = cpu_to_be16(dfs->val.ivlan);
	fs->m_ext.vlan_tci = cpu_to_be16(dfs->mask.ivlan);
	fs->flow_type |= FLOW_EXT;

	अगर (dfs->action == FILTER_DROP)
		fs->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fs->ring_cookie = dfs->iq;
पूर्ण

अटल पूर्णांक cxgb4_ntuple_get_filter(काष्ठा net_device *dev,
				   काष्ठा ethtool_rxnfc *cmd,
				   अचिन्हित पूर्णांक loc)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	काष्ठा filter_entry *f;
	पूर्णांक ftid;

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE))
		वापस -EAGAIN;

	/* Check क्रम maximum filter range */
	अगर (!adap->ethtool_filters)
		वापस -EOPNOTSUPP;

	अगर (loc >= adap->ethtool_filters->nentries)
		वापस -दुस्फल;

	अगर (!test_bit(loc, adap->ethtool_filters->port[pi->port_id].bmap))
		वापस -ENOENT;

	ftid = adap->ethtool_filters->port[pi->port_id].loc_array[loc];

	/* Fetch filter_entry */
	f = cxgb4_get_filter_entry(adap, ftid);

	cxgb4_fill_filter_rule(&cmd->fs, &f->fs);

	वापस 0;
पूर्ण

अटल पूर्णांक get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
		     u32 *rules)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = netdev2adap(dev);
	अचिन्हित पूर्णांक count = 0, index = 0;
	पूर्णांक ret = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXFH: अणु
		अचिन्हित पूर्णांक v = pi->rss_mode;

		info->data = 0;
		चयन (info->flow_type) अणु
		हाल TCP_V4_FLOW:
			अगर (v & FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST |
					     RXH_L4_B_0_1 | RXH_L4_B_2_3;
			अन्यथा अगर (v & FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल UDP_V4_FLOW:
			अगर ((v & FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F) &&
			    (v & FW_RSS_VI_CONFIG_CMD_UDPEN_F))
				info->data = RXH_IP_SRC | RXH_IP_DST |
					     RXH_L4_B_0_1 | RXH_L4_B_2_3;
			अन्यथा अगर (v & FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल SCTP_V4_FLOW:
		हाल AH_ESP_V4_FLOW:
		हाल IPV4_FLOW:
			अगर (v & FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल TCP_V6_FLOW:
			अगर (v & FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST |
					     RXH_L4_B_0_1 | RXH_L4_B_2_3;
			अन्यथा अगर (v & FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल UDP_V6_FLOW:
			अगर ((v & FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F) &&
			    (v & FW_RSS_VI_CONFIG_CMD_UDPEN_F))
				info->data = RXH_IP_SRC | RXH_IP_DST |
					     RXH_L4_B_0_1 | RXH_L4_B_2_3;
			अन्यथा अगर (v & FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल SCTP_V6_FLOW:
		हाल AH_ESP_V6_FLOW:
		हाल IPV6_FLOW:
			अगर (v & FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F)
				info->data = RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	हाल ETHTOOL_GRXRINGS:
		info->data = pi->nqsets;
		वापस 0;
	हाल ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt =
		       adap->ethtool_filters->port[pi->port_id].in_use;
		वापस 0;
	हाल ETHTOOL_GRXCLSRULE:
		वापस cxgb4_ntuple_get_filter(dev, info, info->fs.location);
	हाल ETHTOOL_GRXCLSRLALL:
		info->data = adap->ethtool_filters->nentries;
		जबतक (count < info->rule_cnt) अणु
			ret = cxgb4_ntuple_get_filter(dev, info, index);
			अगर (!ret)
				rules[count++] = index;
			index++;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cxgb4_ntuple_del_filter(काष्ठा net_device *dev,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा cxgb4_ethtool_filter_info *filter_info;
	काष्ठा adapter *adapter = netdev2adap(dev);
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा filter_entry *f;
	u32 filter_id;
	पूर्णांक ret;

	अगर (!(adapter->flags & CXGB4_FULL_INIT_DONE))
		वापस -EAGAIN;  /* can still change nfilters */

	अगर (!adapter->ethtool_filters)
		वापस -EOPNOTSUPP;

	अगर (cmd->fs.location >= adapter->ethtool_filters->nentries) अणु
		dev_err(adapter->pdev_dev,
			"Location must be < %u",
			adapter->ethtool_filters->nentries);
		वापस -दुस्फल;
	पूर्ण

	filter_info = &adapter->ethtool_filters->port[pi->port_id];

	अगर (!test_bit(cmd->fs.location, filter_info->bmap))
		वापस -ENOENT;

	filter_id = filter_info->loc_array[cmd->fs.location];
	f = cxgb4_get_filter_entry(adapter, filter_id);

	अगर (f->fs.prio)
		filter_id -= adapter->tids.hpftid_base;
	अन्यथा अगर (!f->fs.hash)
		filter_id -= (adapter->tids.ftid_base - adapter->tids.nhpftids);

	ret = cxgb4_flow_rule_destroy(dev, f->fs.tc_prio, &f->fs, filter_id);
	अगर (ret)
		जाओ err;

	clear_bit(cmd->fs.location, filter_info->bmap);
	filter_info->in_use--;

err:
	वापस ret;
पूर्ण

/* Add Ethtool n-tuple filters. */
अटल पूर्णांक cxgb4_ntuple_set_filter(काष्ठा net_device *netdev,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec_input input = अणुपूर्ण;
	काष्ठा cxgb4_ethtool_filter_info *filter_info;
	काष्ठा adapter *adapter = netdev2adap(netdev);
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा ch_filter_specअगरication fs;
	काष्ठा ethtool_rx_flow_rule *flow;
	u32 tid;
	पूर्णांक ret;

	अगर (!(adapter->flags & CXGB4_FULL_INIT_DONE))
		वापस -EAGAIN;  /* can still change nfilters */

	अगर (!adapter->ethtool_filters)
		वापस -EOPNOTSUPP;

	अगर (cmd->fs.location >= adapter->ethtool_filters->nentries) अणु
		dev_err(adapter->pdev_dev,
			"Location must be < %u",
			adapter->ethtool_filters->nentries);
		वापस -दुस्फल;
	पूर्ण

	अगर (test_bit(cmd->fs.location,
		     adapter->ethtool_filters->port[pi->port_id].bmap))
		वापस -EEXIST;

	स_रखो(&fs, 0, माप(fs));

	input.fs = &cmd->fs;
	flow = ethtool_rx_flow_rule_create(&input);
	अगर (IS_ERR(flow)) अणु
		ret = PTR_ERR(flow);
		जाओ निकास;
	पूर्ण

	fs.hitcnts = 1;

	ret = cxgb4_flow_rule_replace(netdev, flow->rule, cmd->fs.location,
				      शून्य, &fs, &tid);
	अगर (ret)
		जाओ मुक्त;

	filter_info = &adapter->ethtool_filters->port[pi->port_id];

	अगर (fs.prio)
		tid += adapter->tids.hpftid_base;
	अन्यथा अगर (!fs.hash)
		tid += (adapter->tids.ftid_base - adapter->tids.nhpftids);

	filter_info->loc_array[cmd->fs.location] = tid;
	set_bit(cmd->fs.location, filter_info->bmap);
	filter_info->in_use++;

मुक्त:
	ethtool_rx_flow_rule_destroy(flow);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		ret = cxgb4_ntuple_set_filter(dev, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = cxgb4_ntuple_del_filter(dev, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_dump(काष्ठा net_device *dev, काष्ठा ethtool_dump *eth_dump)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	u32 len = 0;

	len = माप(काष्ठा cudbg_hdr) +
	      माप(काष्ठा cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += cxgb4_get_dump_length(adapter, eth_dump->flag);

	adapter->eth_dump.flag = eth_dump->flag;
	adapter->eth_dump.len = len;
	वापस 0;
पूर्ण

अटल पूर्णांक get_dump_flag(काष्ठा net_device *dev, काष्ठा ethtool_dump *eth_dump)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);

	eth_dump->flag = adapter->eth_dump.flag;
	eth_dump->len = adapter->eth_dump.len;
	eth_dump->version = adapter->eth_dump.version;
	वापस 0;
पूर्ण

अटल पूर्णांक get_dump_data(काष्ठा net_device *dev, काष्ठा ethtool_dump *eth_dump,
			 व्योम *buf)
अणु
	काष्ठा adapter *adapter = netdev2adap(dev);
	u32 len = 0;
	पूर्णांक ret = 0;

	अगर (adapter->eth_dump.flag == CXGB4_ETH_DUMP_NONE)
		वापस -ENOENT;

	len = माप(काष्ठा cudbg_hdr) +
	      माप(काष्ठा cudbg_entity_hdr) * CUDBG_MAX_ENTITY;
	len += cxgb4_get_dump_length(adapter, adapter->eth_dump.flag);
	अगर (eth_dump->len < len)
		वापस -ENOMEM;

	ret = cxgb4_cudbg_collect(adapter, buf, &len, adapter->eth_dump.flag);
	अगर (ret)
		वापस ret;

	eth_dump->flag = adapter->eth_dump.flag;
	eth_dump->len = len;
	eth_dump->version = adapter->eth_dump.version;
	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_get_module_info(काष्ठा net_device *dev,
				 काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	u8 sff8472_comp, sff_diag_type, sff_rev;
	काष्ठा adapter *adapter = pi->adapter;
	पूर्णांक ret;

	अगर (!t4_is_inserted_mod_type(pi->mod_type))
		वापस -EINVAL;

	चयन (pi->port_type) अणु
	हाल FW_PORT_TYPE_SFP:
	हाल FW_PORT_TYPE_QSA:
	हाल FW_PORT_TYPE_SFP28:
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFF_8472_COMP_ADDR,
				SFF_8472_COMP_LEN, &sff8472_comp);
		अगर (ret)
			वापस ret;
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFP_DIAG_TYPE_ADDR,
				SFP_DIAG_TYPE_LEN, &sff_diag_type);
		अगर (ret)
			वापस ret;

		अगर (!sff8472_comp || (sff_diag_type & 4)) अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		पूर्ण
		अवरोध;

	हाल FW_PORT_TYPE_QSFP:
	हाल FW_PORT_TYPE_QSFP_10G:
	हाल FW_PORT_TYPE_CR_QSFP:
	हाल FW_PORT_TYPE_CR2_QSFP:
	हाल FW_PORT_TYPE_CR4_QSFP:
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFF_REV_ADDR,
				SFF_REV_LEN, &sff_rev);
		/* For QSFP type ports, revision value >= 3
		 * means the SFP is 8636 compliant.
		 */
		अगर (ret)
			वापस ret;
		अगर (sff_rev >= 0x3) अणु
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cxgb4_get_module_eeprom(काष्ठा net_device *dev,
				   काष्ठा ethtool_eeprom *eprom, u8 *data)
अणु
	पूर्णांक ret = 0, offset = eprom->offset, len = eprom->len;
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adapter = pi->adapter;

	स_रखो(data, 0, eprom->len);
	अगर (offset + len <= I2C_PAGE_SIZE)
		वापस t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				 I2C_DEV_ADDR_A0, offset, len, data);

	/* offset + len spans 0xa0 and 0xa1 pages */
	अगर (offset <= I2C_PAGE_SIZE) अणु
		/* पढ़ो 0xa0 page */
		len = I2C_PAGE_SIZE - offset;
		ret =  t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				 I2C_DEV_ADDR_A0, offset, len, data);
		अगर (ret)
			वापस ret;
		offset = I2C_PAGE_SIZE;
		/* Reमुख्यing bytes to be पढ़ो from second page =
		 * Total length - bytes पढ़ो from first page
		 */
		len = eprom->len - len;
	पूर्ण
	/* Read additional optical diagnostics from page 0xa2 अगर supported */
	वापस t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan, I2C_DEV_ADDR_A2,
			 offset, len, &data[eprom->len - len]);
पूर्ण

अटल u32 cxgb4_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;

	वापस (adapter->eth_flags | pi->eth_flags);
पूर्ण

/**
 *	set_flags - set/unset specअगरied flags अगर passed in new_flags
 *	@cur_flags: poपूर्णांकer to current flags
 *	@new_flags: new incoming flags
 *	@flags: set of flags to set/unset
 */
अटल अंतरभूत व्योम set_flags(u32 *cur_flags, u32 new_flags, u32 flags)
अणु
	*cur_flags = (*cur_flags & ~flags) | (new_flags & flags);
पूर्ण

अटल पूर्णांक cxgb4_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adapter = pi->adapter;

	set_flags(&adapter->eth_flags, flags, PRIV_FLAGS_ADAP);
	set_flags(&pi->eth_flags, flags, PRIV_FLAGS_PORT);

	वापस 0;
पूर्ण

अटल व्योम cxgb4_lb_test(काष्ठा net_device *netdev, u64 *lb_status)
अणु
	पूर्णांक dev_state = netअगर_running(netdev);

	अगर (dev_state) अणु
		netअगर_tx_stop_all_queues(netdev);
		netअगर_carrier_off(netdev);
	पूर्ण

	*lb_status = cxgb4_selftest_lb_pkt(netdev);

	अगर (dev_state) अणु
		netअगर_tx_start_all_queues(netdev);
		netअगर_carrier_on(netdev);
	पूर्ण
पूर्ण

अटल व्योम cxgb4_self_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा port_info *pi = netdev_priv(netdev);
	काष्ठा adapter *adap = pi->adapter;

	स_रखो(data, 0, माप(u64) * CXGB4_ETHTOOL_MAX_TEST);

	अगर (!(adap->flags & CXGB4_FULL_INIT_DONE) ||
	    !(adap->flags & CXGB4_FW_OK)) अणु
		eth_test->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	अगर (eth_test->flags & ETH_TEST_FL_OFFLINE)
		cxgb4_lb_test(netdev, &data[CXGB4_ETHTOOL_LB_TEST]);

	अगर (data[CXGB4_ETHTOOL_LB_TEST])
		eth_test->flags |= ETH_TEST_FL_FAILED;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops cxgb_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_RX_MAX_FRAMES |
				     ETHTOOL_COALESCE_TX_USECS_IRQ |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_link_ksettings = get_link_ksettings,
	.set_link_ksettings = set_link_ksettings,
	.get_fecparam      = get_fecparam,
	.set_fecparam      = set_fecparam,
	.get_drvinfo       = get_drvinfo,
	.get_msglevel      = get_msglevel,
	.set_msglevel      = set_msglevel,
	.get_ringparam     = get_sge_param,
	.set_ringparam     = set_sge_param,
	.get_coalesce      = get_coalesce,
	.set_coalesce      = set_coalesce,
	.get_eeprom_len    = get_eeprom_len,
	.get_eeprom        = get_eeprom,
	.set_eeprom        = set_eeprom,
	.get_छोड़ोparam    = get_छोड़ोparam,
	.set_छोड़ोparam    = set_छोड़ोparam,
	.get_link          = ethtool_op_get_link,
	.get_strings       = get_strings,
	.set_phys_id       = identअगरy_port,
	.nway_reset        = restart_स्वतःneg,
	.get_sset_count    = get_sset_count,
	.get_ethtool_stats = get_stats,
	.get_regs_len      = get_regs_len,
	.get_regs          = get_regs,
	.get_rxnfc         = get_rxnfc,
	.set_rxnfc         = set_rxnfc,
	.get_rxfh_indir_size = get_rss_table_size,
	.get_rxfh	   = get_rss_table,
	.set_rxfh	   = set_rss_table,
	.self_test	   = cxgb4_self_test,
	.flash_device      = set_flash,
	.get_ts_info       = get_ts_info,
	.set_dump          = set_dump,
	.get_dump_flag     = get_dump_flag,
	.get_dump_data     = get_dump_data,
	.get_module_info   = cxgb4_get_module_info,
	.get_module_eeprom = cxgb4_get_module_eeprom,
	.get_priv_flags    = cxgb4_get_priv_flags,
	.set_priv_flags    = cxgb4_set_priv_flags,
पूर्ण;

व्योम cxgb4_cleanup_ethtool_filters(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_ethtool_filter_info *eth_filter_info;
	u8 i;

	अगर (!adap->ethtool_filters)
		वापस;

	eth_filter_info = adap->ethtool_filters->port;

	अगर (eth_filter_info) अणु
		क्रम (i = 0; i < adap->params.nports; i++) अणु
			kvमुक्त(eth_filter_info[i].loc_array);
			kमुक्त(eth_filter_info[i].bmap);
		पूर्ण
		kमुक्त(eth_filter_info);
	पूर्ण

	kमुक्त(adap->ethtool_filters);
पूर्ण

पूर्णांक cxgb4_init_ethtool_filters(काष्ठा adapter *adap)
अणु
	काष्ठा cxgb4_ethtool_filter_info *eth_filter_info;
	काष्ठा cxgb4_ethtool_filter *eth_filter;
	काष्ठा tid_info *tids = &adap->tids;
	u32 nentries, i;
	पूर्णांक ret;

	eth_filter = kzalloc(माप(*eth_filter), GFP_KERNEL);
	अगर (!eth_filter)
		वापस -ENOMEM;

	eth_filter_info = kसुस्मृति(adap->params.nports,
				  माप(*eth_filter_info),
				  GFP_KERNEL);
	अगर (!eth_filter_info) अणु
		ret = -ENOMEM;
		जाओ मुक्त_eth_filter;
	पूर्ण

	eth_filter->port = eth_filter_info;

	nentries = tids->nhpftids + tids->nftids;
	अगर (is_hashfilter(adap))
		nentries += tids->nhash +
			    (adap->tids.stid_base - adap->tids.tid_base);
	eth_filter->nentries = nentries;

	क्रम (i = 0; i < adap->params.nports; i++) अणु
		eth_filter->port[i].loc_array = kvzalloc(nentries, GFP_KERNEL);
		अगर (!eth_filter->port[i].loc_array) अणु
			ret = -ENOMEM;
			जाओ मुक्त_eth_finfo;
		पूर्ण

		eth_filter->port[i].bmap = kसुस्मृति(BITS_TO_LONGS(nentries),
						   माप(अचिन्हित दीर्घ),
						   GFP_KERNEL);
		अगर (!eth_filter->port[i].bmap) अणु
			ret = -ENOMEM;
			जाओ मुक्त_eth_finfo;
		पूर्ण
	पूर्ण

	adap->ethtool_filters = eth_filter;
	वापस 0;

मुक्त_eth_finfo:
	जबतक (i-- > 0) अणु
		kमुक्त(eth_filter->port[i].bmap);
		kvमुक्त(eth_filter->port[i].loc_array);
	पूर्ण
	kमुक्त(eth_filter_info);

मुक्त_eth_filter:
	kमुक्त(eth_filter);

	वापस ret;
पूर्ण

व्योम cxgb4_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &cxgb_ethtool_ops;
पूर्ण
