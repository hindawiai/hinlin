<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_ethtool.c: Definition of ethertool related functions. */

#समावेश "aq_ethtool.h"
#समावेश "aq_nic.h"
#समावेश "aq_vec.h"
#समावेश "aq_ptp.h"
#समावेश "aq_filters.h"
#समावेश "aq_macsec.h"

#समावेश <linux/ptp_घड़ी_kernel.h>

अटल व्योम aq_ethtool_get_regs(काष्ठा net_device *ndev,
				काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 regs_count;

	regs_count = aq_nic_get_regs_count(aq_nic);

	स_रखो(p, 0, regs_count * माप(u32));
	aq_nic_get_regs(aq_nic, regs, p);
पूर्ण

अटल पूर्णांक aq_ethtool_get_regs_len(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 regs_count;

	regs_count = aq_nic_get_regs_count(aq_nic);

	वापस regs_count * माप(u32);
पूर्ण

अटल u32 aq_ethtool_get_link(काष्ठा net_device *ndev)
अणु
	वापस ethtool_op_get_link(ndev);
पूर्ण

अटल पूर्णांक aq_ethtool_get_link_ksettings(काष्ठा net_device *ndev,
					 काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	aq_nic_get_link_ksettings(aq_nic, cmd);
	cmd->base.speed = netअगर_carrier_ok(ndev) ?
				aq_nic_get_link_speed(aq_nic) : 0U;

	वापस 0;
पूर्ण

अटल पूर्णांक
aq_ethtool_set_link_ksettings(काष्ठा net_device *ndev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	वापस aq_nic_set_link_ksettings(aq_nic, cmd);
पूर्ण

अटल स्थिर अक्षर aq_ethtool_stat_names[][ETH_GSTRING_LEN] = अणु
	"InPackets",
	"InUCast",
	"InMCast",
	"InBCast",
	"InErrors",
	"OutPackets",
	"OutUCast",
	"OutMCast",
	"OutBCast",
	"InUCastOctets",
	"OutUCastOctets",
	"InMCastOctets",
	"OutMCastOctets",
	"InBCastOctets",
	"OutBCastOctets",
	"InOctets",
	"OutOctets",
	"InPacketsDma",
	"OutPacketsDma",
	"InOctetsDma",
	"OutOctetsDma",
	"InDroppedDma",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aq_ethtool_queue_rx_stat_names[] = अणु
	"%sQueue[%d] InPackets",
	"%sQueue[%d] InJumboPackets",
	"%sQueue[%d] InLroPackets",
	"%sQueue[%d] InErrors",
	"%sQueue[%d] AllocFails",
	"%sQueue[%d] SkbAllocFails",
	"%sQueue[%d] Polls",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aq_ethtool_queue_tx_stat_names[] = अणु
	"%sQueue[%d] OutPackets",
	"%sQueue[%d] Restarts",
पूर्ण;

#अगर IS_ENABLED(CONFIG_MACSEC)
अटल स्थिर अक्षर aq_macsec_stat_names[][ETH_GSTRING_LEN] = अणु
	"MACSec InCtlPackets",
	"MACSec InTaggedMissPackets",
	"MACSec InUntaggedMissPackets",
	"MACSec InNotagPackets",
	"MACSec InUntaggedPackets",
	"MACSec InBadTagPackets",
	"MACSec InNoSciPackets",
	"MACSec InUnknownSciPackets",
	"MACSec InCtrlPortPassPackets",
	"MACSec InUnctrlPortPassPackets",
	"MACSec InCtrlPortFailPackets",
	"MACSec InUnctrlPortFailPackets",
	"MACSec InTooLongPackets",
	"MACSec InIgpocCtlPackets",
	"MACSec InEccErrorPackets",
	"MACSec InUnctrlHitDropRedir",
	"MACSec OutCtlPackets",
	"MACSec OutUnknownSaPackets",
	"MACSec OutUntaggedPackets",
	"MACSec OutTooLong",
	"MACSec OutEccErrorPackets",
	"MACSec OutUnctrlHitDropRedir",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aq_macsec_txsc_stat_names[] = अणु
	"MACSecTXSC%d ProtectedPkts",
	"MACSecTXSC%d EncryptedPkts",
	"MACSecTXSC%d ProtectedOctets",
	"MACSecTXSC%d EncryptedOctets",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aq_macsec_txsa_stat_names[] = अणु
	"MACSecTXSC%dSA%d HitDropRedirect",
	"MACSecTXSC%dSA%d Protected2Pkts",
	"MACSecTXSC%dSA%d ProtectedPkts",
	"MACSecTXSC%dSA%d EncryptedPkts",
पूर्ण;

अटल स्थिर अक्षर * स्थिर aq_macsec_rxsa_stat_names[] = अणु
	"MACSecRXSC%dSA%d UntaggedHitPkts",
	"MACSecRXSC%dSA%d CtrlHitDrpRedir",
	"MACSecRXSC%dSA%d NotUsingSa",
	"MACSecRXSC%dSA%d UnusedSa",
	"MACSecRXSC%dSA%d NotValidPkts",
	"MACSecRXSC%dSA%d InvalidPkts",
	"MACSecRXSC%dSA%d OkPkts",
	"MACSecRXSC%dSA%d LatePkts",
	"MACSecRXSC%dSA%d DelayedPkts",
	"MACSecRXSC%dSA%d UncheckedPkts",
	"MACSecRXSC%dSA%d ValidatedOctets",
	"MACSecRXSC%dSA%d DecryptedOctets",
पूर्ण;
#पूर्ण_अगर

अटल स्थिर अक्षर aq_ethtool_priv_flag_names[][ETH_GSTRING_LEN] = अणु
	"DMASystemLoopback",
	"PKTSystemLoopback",
	"DMANetworkLoopback",
	"PHYInternalLoopback",
	"PHYExternalLoopback",
पूर्ण;

अटल u32 aq_ethtool_n_stats(काष्ठा net_device *ndev)
अणु
	स्थिर पूर्णांक rx_stat_cnt = ARRAY_SIZE(aq_ethtool_queue_rx_stat_names);
	स्थिर पूर्णांक tx_stat_cnt = ARRAY_SIZE(aq_ethtool_queue_tx_stat_names);
	काष्ठा aq_nic_s *nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg = aq_nic_get_cfg(nic);
	u32 n_stats = ARRAY_SIZE(aq_ethtool_stat_names) +
		      (rx_stat_cnt + tx_stat_cnt) * cfg->vecs * cfg->tcs;

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	n_stats += rx_stat_cnt * aq_ptp_get_ring_cnt(nic, ATL_RING_RX) +
		   tx_stat_cnt * aq_ptp_get_ring_cnt(nic, ATL_RING_TX);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MACSEC)
	अगर (nic->macsec_cfg) अणु
		n_stats += ARRAY_SIZE(aq_macsec_stat_names) +
			   ARRAY_SIZE(aq_macsec_txsc_stat_names) *
				   aq_macsec_tx_sc_cnt(nic) +
			   ARRAY_SIZE(aq_macsec_txsa_stat_names) *
				   aq_macsec_tx_sa_cnt(nic) +
			   ARRAY_SIZE(aq_macsec_rxsa_stat_names) *
				   aq_macsec_rx_sa_cnt(nic);
	पूर्ण
#पूर्ण_अगर

	वापस n_stats;
पूर्ण

अटल व्योम aq_ethtool_stats(काष्ठा net_device *ndev,
			     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	स_रखो(data, 0, aq_ethtool_n_stats(ndev) * माप(u64));
	data = aq_nic_get_stats(aq_nic, data);
#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	data = aq_ptp_get_stats(aq_nic, data);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MACSEC)
	data = aq_macsec_get_stats(aq_nic, data);
#पूर्ण_अगर
पूर्ण

अटल व्योम aq_ethtool_get_drvinfo(काष्ठा net_device *ndev,
				   काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ndev->dev.parent);
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 firmware_version;
	u32 regs_count;

	firmware_version = aq_nic_get_fw_version(aq_nic);
	regs_count = aq_nic_get_regs_count(aq_nic);

	strlcat(drvinfo->driver, AQ_CFG_DRV_NAME, माप(drvinfo->driver));

	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%u.%u.%u", firmware_version >> 24,
		 (firmware_version >> 16) & 0xFFU, firmware_version & 0xFFFFU);

	strlcpy(drvinfo->bus_info, pdev ? pci_name(pdev) : "",
		माप(drvinfo->bus_info));
	drvinfo->n_stats = aq_ethtool_n_stats(ndev);
	drvinfo->testinfo_len = 0;
	drvinfo->regdump_len = regs_count;
	drvinfo->eedump_len = 0;
पूर्ण

अटल व्योम aq_ethtool_get_strings(काष्ठा net_device *ndev,
				   u32 stringset, u8 *data)
अणु
	काष्ठा aq_nic_s *nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;
	u8 *p = data;
	पूर्णांक i, si;
#अगर IS_ENABLED(CONFIG_MACSEC)
	पूर्णांक sa;
#पूर्ण_अगर

	cfg = aq_nic_get_cfg(nic);

	चयन (stringset) अणु
	हाल ETH_SS_STATS: अणु
		स्थिर पूर्णांक rx_stat_cnt = ARRAY_SIZE(aq_ethtool_queue_rx_stat_names);
		स्थिर पूर्णांक tx_stat_cnt = ARRAY_SIZE(aq_ethtool_queue_tx_stat_names);
		अक्षर tc_string[8];
		पूर्णांक tc;

		स_रखो(tc_string, 0, माप(tc_string));
		स_नकल(p, aq_ethtool_stat_names,
		       माप(aq_ethtool_stat_names));
		p = p + माप(aq_ethtool_stat_names);

		क्रम (tc = 0; tc < cfg->tcs; tc++) अणु
			अगर (cfg->is_qos)
				snम_लिखो(tc_string, 8, "TC%d ", tc);

			क्रम (i = 0; i < cfg->vecs; i++) अणु
				क्रम (si = 0; si < rx_stat_cnt; si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
					     aq_ethtool_queue_rx_stat_names[si],
					     tc_string,
					     AQ_NIC_CFG_TCVEC2RING(cfg, tc, i));
					p += ETH_GSTRING_LEN;
				पूर्ण
				क्रम (si = 0; si < tx_stat_cnt; si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
					     aq_ethtool_queue_tx_stat_names[si],
					     tc_string,
					     AQ_NIC_CFG_TCVEC2RING(cfg, tc, i));
					p += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
		अगर (nic->aq_ptp) अणु
			स्थिर पूर्णांक rx_ring_cnt = aq_ptp_get_ring_cnt(nic, ATL_RING_RX);
			स्थिर पूर्णांक tx_ring_cnt = aq_ptp_get_ring_cnt(nic, ATL_RING_TX);
			अचिन्हित पूर्णांक ptp_ring_idx =
				aq_ptp_ring_idx(nic->aq_nic_cfg.tc_mode);

			snम_लिखो(tc_string, 8, "PTP ");

			क्रम (i = 0; i < max(rx_ring_cnt, tx_ring_cnt); i++) अणु
				क्रम (si = 0; si < rx_stat_cnt; si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
						 aq_ethtool_queue_rx_stat_names[si],
						 tc_string,
						 i ? PTP_HWST_RING_IDX : ptp_ring_idx);
					p += ETH_GSTRING_LEN;
				पूर्ण
				अगर (i >= tx_ring_cnt)
					जारी;
				क्रम (si = 0; si < tx_stat_cnt; si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
						 aq_ethtool_queue_tx_stat_names[si],
						 tc_string,
						 i ? PTP_HWST_RING_IDX : ptp_ring_idx);
					p += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MACSEC)
		अगर (!nic->macsec_cfg)
			अवरोध;

		स_नकल(p, aq_macsec_stat_names, माप(aq_macsec_stat_names));
		p = p + माप(aq_macsec_stat_names);
		क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
			काष्ठा aq_macsec_txsc *aq_txsc;

			अगर (!(test_bit(i, &nic->macsec_cfg->txsc_idx_busy)))
				जारी;

			क्रम (si = 0;
				si < ARRAY_SIZE(aq_macsec_txsc_stat_names);
				si++) अणु
				snम_लिखो(p, ETH_GSTRING_LEN,
					 aq_macsec_txsc_stat_names[si], i);
				p += ETH_GSTRING_LEN;
			पूर्ण
			aq_txsc = &nic->macsec_cfg->aq_txsc[i];
			क्रम (sa = 0; sa < MACSEC_NUM_AN; sa++) अणु
				अगर (!(test_bit(sa, &aq_txsc->tx_sa_idx_busy)))
					जारी;
				क्रम (si = 0;
				     si < ARRAY_SIZE(aq_macsec_txsa_stat_names);
				     si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
						 aq_macsec_txsa_stat_names[si],
						 i, sa);
					p += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < AQ_MACSEC_MAX_SC; i++) अणु
			काष्ठा aq_macsec_rxsc *aq_rxsc;

			अगर (!(test_bit(i, &nic->macsec_cfg->rxsc_idx_busy)))
				जारी;

			aq_rxsc = &nic->macsec_cfg->aq_rxsc[i];
			क्रम (sa = 0; sa < MACSEC_NUM_AN; sa++) अणु
				अगर (!(test_bit(sa, &aq_rxsc->rx_sa_idx_busy)))
					जारी;
				क्रम (si = 0;
				     si < ARRAY_SIZE(aq_macsec_rxsa_stat_names);
				     si++) अणु
					snम_लिखो(p, ETH_GSTRING_LEN,
						 aq_macsec_rxsa_stat_names[si],
						 i, sa);
					p += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(p, aq_ethtool_priv_flag_names,
		       माप(aq_ethtool_priv_flag_names));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक aq_ethtool_set_phys_id(काष्ठा net_device *ndev,
				  क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_hw_s *hw = aq_nic->aq_hw;
	पूर्णांक ret = 0;

	अगर (!aq_nic->aq_fw_ops->led_control)
		वापस -EOPNOTSUPP;

	mutex_lock(&aq_nic->fwreq_mutex);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		ret = aq_nic->aq_fw_ops->led_control(hw, AQ_HW_LED_BLINK |
				 AQ_HW_LED_BLINK << 2 | AQ_HW_LED_BLINK << 4);
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		ret = aq_nic->aq_fw_ops->led_control(hw, AQ_HW_LED_DEFAULT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&aq_nic->fwreq_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक aq_ethtool_get_sset_count(काष्ठा net_device *ndev, पूर्णांक stringset)
अणु
	पूर्णांक ret = 0;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		ret = aq_ethtool_n_stats(ndev);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		ret = ARRAY_SIZE(aq_ethtool_priv_flag_names);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल u32 aq_ethtool_get_rss_indir_size(काष्ठा net_device *ndev)
अणु
	वापस AQ_CFG_RSS_INसूचीECTION_TABLE_MAX;
पूर्ण

अटल u32 aq_ethtool_get_rss_key_size(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;

	cfg = aq_nic_get_cfg(aq_nic);

	वापस माप(cfg->aq_rss.hash_secret_key);
पूर्ण

अटल पूर्णांक aq_ethtool_get_rss(काष्ठा net_device *ndev, u32 *indir, u8 *key,
			      u8 *hfunc)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;
	अचिन्हित पूर्णांक i = 0U;

	cfg = aq_nic_get_cfg(aq_nic);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP; /* Toeplitz */
	अगर (indir) अणु
		क्रम (i = 0; i < AQ_CFG_RSS_INसूचीECTION_TABLE_MAX; i++)
			indir[i] = cfg->aq_rss.indirection_table[i];
	पूर्ण
	अगर (key)
		स_नकल(key, cfg->aq_rss.hash_secret_key,
		       माप(cfg->aq_rss.hash_secret_key));

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ethtool_set_rss(काष्ठा net_device *netdev, स्थिर u32 *indir,
			      स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(netdev);
	काष्ठा aq_nic_cfg_s *cfg;
	अचिन्हित पूर्णांक i = 0U;
	u32 rss_entries;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(aq_nic);
	rss_entries = cfg->aq_rss.indirection_table_size;

	/* We करो not allow change in unsupported parameters */
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;
	/* Fill out the redirection table */
	अगर (indir)
		क्रम (i = 0; i < rss_entries; i++)
			cfg->aq_rss.indirection_table[i] = indir[i];

	/* Fill out the rss hash key */
	अगर (key) अणु
		स_नकल(cfg->aq_rss.hash_secret_key, key,
		       माप(cfg->aq_rss.hash_secret_key));
		err = aq_nic->aq_hw_ops->hw_rss_hash_set(aq_nic->aq_hw,
			&cfg->aq_rss);
		अगर (err)
			वापस err;
	पूर्ण

	err = aq_nic->aq_hw_ops->hw_rss_set(aq_nic->aq_hw, &cfg->aq_rss);

	वापस err;
पूर्ण

अटल पूर्णांक aq_ethtool_get_rxnfc(काष्ठा net_device *ndev,
				काष्ठा ethtool_rxnfc *cmd,
				u32 *rule_locs)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(aq_nic);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = cfg->vecs;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = aq_get_rxnfc_count_all_rules(aq_nic);
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		err = aq_get_rxnfc_rule(aq_nic, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		err = aq_get_rxnfc_all_rules(aq_nic, cmd, rule_locs);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aq_ethtool_set_rxnfc(काष्ठा net_device *ndev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		err = aq_add_rxnfc_rule(aq_nic, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = aq_del_rxnfc_rule(aq_nic, cmd);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aq_ethtool_get_coalesce(काष्ठा net_device *ndev,
				   काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;

	cfg = aq_nic_get_cfg(aq_nic);

	अगर (cfg->itr == AQ_CFG_INTERRUPT_MODERATION_ON ||
	    cfg->itr == AQ_CFG_INTERRUPT_MODERATION_AUTO) अणु
		coal->rx_coalesce_usecs = cfg->rx_itr;
		coal->tx_coalesce_usecs = cfg->tx_itr;
		coal->rx_max_coalesced_frames = 0;
		coal->tx_max_coalesced_frames = 0;
	पूर्ण अन्यथा अणु
		coal->rx_coalesce_usecs = 0;
		coal->tx_coalesce_usecs = 0;
		coal->rx_max_coalesced_frames = 1;
		coal->tx_max_coalesced_frames = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ethtool_set_coalesce(काष्ठा net_device *ndev,
				   काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;

	cfg = aq_nic_get_cfg(aq_nic);

	/* Atlantic only supports timing based coalescing
	 */
	अगर (coal->rx_max_coalesced_frames > 1 ||
	    coal->tx_max_coalesced_frames > 1)
		वापस -EOPNOTSUPP;

	/* We करो not support frame counting. Check this
	 */
	अगर (!(coal->rx_max_coalesced_frames == !coal->rx_coalesce_usecs))
		वापस -EOPNOTSUPP;
	अगर (!(coal->tx_max_coalesced_frames == !coal->tx_coalesce_usecs))
		वापस -EOPNOTSUPP;

	अगर (coal->rx_coalesce_usecs > AQ_CFG_INTERRUPT_MODERATION_USEC_MAX ||
	    coal->tx_coalesce_usecs > AQ_CFG_INTERRUPT_MODERATION_USEC_MAX)
		वापस -EINVAL;

	cfg->itr = AQ_CFG_INTERRUPT_MODERATION_ON;

	cfg->rx_itr = coal->rx_coalesce_usecs;
	cfg->tx_itr = coal->tx_coalesce_usecs;

	वापस aq_nic_update_पूर्णांकerrupt_moderation_settings(aq_nic);
पूर्ण

अटल व्योम aq_ethtool_get_wol(काष्ठा net_device *ndev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;

	cfg = aq_nic_get_cfg(aq_nic);

	wol->supported = AQ_NIC_WOL_MODES;
	wol->wolopts = cfg->wol;
पूर्ण

अटल पूर्णांक aq_ethtool_set_wol(काष्ठा net_device *ndev,
			      काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(ndev->dev.parent);
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(aq_nic);

	अगर (wol->wolopts & ~AQ_NIC_WOL_MODES)
		वापस -EOPNOTSUPP;

	cfg->wol = wol->wolopts;

	err = device_set_wakeup_enable(&pdev->dev, !!cfg->wol);

	वापस err;
पूर्ण

अटल पूर्णांक aq_ethtool_get_ts_info(काष्ठा net_device *ndev,
				  काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	ethtool_op_get_ts_info(ndev, info);

	अगर (!aq_nic->aq_ptp)
		वापस 0;

	info->so_बारtamping |=
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;

	info->tx_types = BIT(HWTSTAMP_TX_OFF) |
			 BIT(HWTSTAMP_TX_ON);

	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE);

	info->rx_filters |= BIT(HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)
	info->phc_index = ptp_घड़ी_index(aq_ptp_get_ptp_घड़ी(aq_nic->aq_ptp));
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल u32 eee_mask_to_ethtool_mask(u32 speed)
अणु
	u32 rate = 0;

	अगर (speed & AQ_NIC_RATE_EEE_10G)
		rate |= SUPPORTED_10000baseT_Full;

	अगर (speed & AQ_NIC_RATE_EEE_1G)
		rate |= SUPPORTED_1000baseT_Full;

	अगर (speed & AQ_NIC_RATE_EEE_100M)
		rate |= SUPPORTED_100baseT_Full;

	वापस rate;
पूर्ण

अटल पूर्णांक aq_ethtool_get_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *eee)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 rate, supported_rates;
	पूर्णांक err = 0;

	अगर (!aq_nic->aq_fw_ops->get_eee_rate)
		वापस -EOPNOTSUPP;

	mutex_lock(&aq_nic->fwreq_mutex);
	err = aq_nic->aq_fw_ops->get_eee_rate(aq_nic->aq_hw, &rate,
					      &supported_rates);
	mutex_unlock(&aq_nic->fwreq_mutex);
	अगर (err < 0)
		वापस err;

	eee->supported = eee_mask_to_ethtool_mask(supported_rates);

	अगर (aq_nic->aq_nic_cfg.eee_speeds)
		eee->advertised = eee->supported;

	eee->lp_advertised = eee_mask_to_ethtool_mask(rate);

	eee->eee_enabled = !!eee->advertised;

	eee->tx_lpi_enabled = eee->eee_enabled;
	अगर ((supported_rates & rate) & AQ_NIC_RATE_EEE_MSK)
		eee->eee_active = true;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ethtool_set_eee(काष्ठा net_device *ndev, काष्ठा ethtool_eee *eee)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	u32 rate, supported_rates;
	काष्ठा aq_nic_cfg_s *cfg;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(aq_nic);

	अगर (unlikely(!aq_nic->aq_fw_ops->get_eee_rate ||
		     !aq_nic->aq_fw_ops->set_eee_rate))
		वापस -EOPNOTSUPP;

	mutex_lock(&aq_nic->fwreq_mutex);
	err = aq_nic->aq_fw_ops->get_eee_rate(aq_nic->aq_hw, &rate,
					      &supported_rates);
	mutex_unlock(&aq_nic->fwreq_mutex);
	अगर (err < 0)
		वापस err;

	अगर (eee->eee_enabled) अणु
		rate = supported_rates;
		cfg->eee_speeds = rate;
	पूर्ण अन्यथा अणु
		rate = 0;
		cfg->eee_speeds = 0;
	पूर्ण

	mutex_lock(&aq_nic->fwreq_mutex);
	err = aq_nic->aq_fw_ops->set_eee_rate(aq_nic->aq_hw, rate);
	mutex_unlock(&aq_nic->fwreq_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक aq_ethtool_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	अगर (unlikely(!aq_nic->aq_fw_ops->renegotiate))
		वापस -EOPNOTSUPP;

	अगर (netअगर_running(ndev)) अणु
		mutex_lock(&aq_nic->fwreq_mutex);
		err = aq_nic->aq_fw_ops->renegotiate(aq_nic->aq_hw);
		mutex_unlock(&aq_nic->fwreq_mutex);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम aq_ethtool_get_छोड़ोparam(काष्ठा net_device *ndev,
				      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक fc = aq_nic->aq_nic_cfg.fc.req;

	छोड़ो->स्वतःneg = 0;

	छोड़ो->rx_छोड़ो = !!(fc & AQ_NIC_FC_RX);
	छोड़ो->tx_छोड़ो = !!(fc & AQ_NIC_FC_TX);
पूर्ण

अटल पूर्णांक aq_ethtool_set_छोड़ोparam(काष्ठा net_device *ndev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	पूर्णांक err = 0;

	अगर (!aq_nic->aq_fw_ops->set_flow_control)
		वापस -EOPNOTSUPP;

	अगर (छोड़ो->स्वतःneg == AUTONEG_ENABLE)
		वापस -EOPNOTSUPP;

	अगर (छोड़ो->rx_छोड़ो)
		aq_nic->aq_hw->aq_nic_cfg->fc.req |= AQ_NIC_FC_RX;
	अन्यथा
		aq_nic->aq_hw->aq_nic_cfg->fc.req &= ~AQ_NIC_FC_RX;

	अगर (छोड़ो->tx_छोड़ो)
		aq_nic->aq_hw->aq_nic_cfg->fc.req |= AQ_NIC_FC_TX;
	अन्यथा
		aq_nic->aq_hw->aq_nic_cfg->fc.req &= ~AQ_NIC_FC_TX;

	mutex_lock(&aq_nic->fwreq_mutex);
	err = aq_nic->aq_fw_ops->set_flow_control(aq_nic->aq_hw);
	mutex_unlock(&aq_nic->fwreq_mutex);

	वापस err;
पूर्ण

अटल व्योम aq_get_ringparam(काष्ठा net_device *ndev,
			     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;

	cfg = aq_nic_get_cfg(aq_nic);

	ring->rx_pending = cfg->rxds;
	ring->tx_pending = cfg->txds;

	ring->rx_max_pending = cfg->aq_hw_caps->rxds_max;
	ring->tx_max_pending = cfg->aq_hw_caps->txds_max;
पूर्ण

अटल पूर्णांक aq_set_ringparam(काष्ठा net_device *ndev,
			    काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	स्थिर काष्ठा aq_hw_caps_s *hw_caps;
	bool ndev_running = false;
	काष्ठा aq_nic_cfg_s *cfg;
	पूर्णांक err = 0;

	cfg = aq_nic_get_cfg(aq_nic);
	hw_caps = cfg->aq_hw_caps;

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending) अणु
		err = -EOPNOTSUPP;
		जाओ err_निकास;
	पूर्ण

	अगर (netअगर_running(ndev)) अणु
		ndev_running = true;
		dev_बंद(ndev);
	पूर्ण

	cfg->rxds = max(ring->rx_pending, hw_caps->rxds_min);
	cfg->rxds = min(cfg->rxds, hw_caps->rxds_max);
	cfg->rxds = ALIGN(cfg->rxds, AQ_HW_RXD_MULTIPLE);

	cfg->txds = max(ring->tx_pending, hw_caps->txds_min);
	cfg->txds = min(cfg->txds, hw_caps->txds_max);
	cfg->txds = ALIGN(cfg->txds, AQ_HW_TXD_MULTIPLE);

	err = aq_nic_पुनः_स्मृति_vectors(aq_nic);
	अगर (err)
		जाओ err_निकास;

	अगर (ndev_running)
		err = dev_खोलो(ndev, शून्य);

err_निकास:
	वापस err;
पूर्ण

अटल u32 aq_get_msg_level(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	वापस aq_nic->msg_enable;
पूर्ण

अटल व्योम aq_set_msg_level(काष्ठा net_device *ndev, u32 data)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	aq_nic->msg_enable = data;
पूर्ण

अटल u32 aq_ethtool_get_priv_flags(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	वापस aq_nic->aq_nic_cfg.priv_flags;
पूर्ण

अटल पूर्णांक aq_ethtool_set_priv_flags(काष्ठा net_device *ndev, u32 flags)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा aq_nic_cfg_s *cfg;
	u32 priv_flags;
	पूर्णांक ret = 0;

	cfg = aq_nic_get_cfg(aq_nic);
	priv_flags = cfg->priv_flags;

	अगर (flags & ~AQ_PRIV_FLAGS_MASK)
		वापस -EOPNOTSUPP;

	अगर (hweight32((flags | priv_flags) & AQ_HW_LOOPBACK_MASK) > 1) अणु
		netdev_info(ndev, "Can't enable more than one loopback simultaneously\n");
		वापस -EINVAL;
	पूर्ण

	cfg->priv_flags = flags;

	अगर ((priv_flags ^ flags) & BIT(AQ_HW_LOOPBACK_DMA_NET)) अणु
		अगर (netअगर_running(ndev)) अणु
			dev_बंद(ndev);

			dev_खोलो(ndev, शून्य);
		पूर्ण
	पूर्ण अन्यथा अगर ((priv_flags ^ flags) & AQ_HW_LOOPBACK_MASK) अणु
		ret = aq_nic_set_loopback(aq_nic);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aq_ethtool_get_phy_tunable(काष्ठा net_device *ndev,
				      स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_EDPD: अणु
		u16 *val = data;

		*val = aq_nic->aq_nic_cfg.is_media_detect ? AQ_HW_MEDIA_DETECT_CNT : 0;
		अवरोध;
	पूर्ण
	हाल ETHTOOL_PHY_DOWNSHIFT: अणु
		u8 *val = data;

		*val = (u8)aq_nic->aq_nic_cfg.करोwnshअगरt_counter;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aq_ethtool_set_phy_tunable(काष्ठा net_device *ndev,
				      स्थिर काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	पूर्णांक err = -EOPNOTSUPP;
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);

	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_EDPD: अणु
		स्थिर u16 *val = data;

		err = aq_nic_set_media_detect(aq_nic, *val);
		अवरोध;
	पूर्ण
	हाल ETHTOOL_PHY_DOWNSHIFT: अणु
		स्थिर u8 *val = data;

		err = aq_nic_set_करोwnshअगरt(aq_nic, *val);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

स्थिर काष्ठा ethtool_ops aq_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_link            = aq_ethtool_get_link,
	.get_regs_len        = aq_ethtool_get_regs_len,
	.get_regs            = aq_ethtool_get_regs,
	.get_drvinfo         = aq_ethtool_get_drvinfo,
	.get_strings         = aq_ethtool_get_strings,
	.set_phys_id         = aq_ethtool_set_phys_id,
	.get_rxfh_indir_size = aq_ethtool_get_rss_indir_size,
	.get_wol             = aq_ethtool_get_wol,
	.set_wol             = aq_ethtool_set_wol,
	.nway_reset          = aq_ethtool_nway_reset,
	.get_ringparam       = aq_get_ringparam,
	.set_ringparam       = aq_set_ringparam,
	.get_eee             = aq_ethtool_get_eee,
	.set_eee             = aq_ethtool_set_eee,
	.get_छोड़ोparam      = aq_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam      = aq_ethtool_set_छोड़ोparam,
	.get_rxfh_key_size   = aq_ethtool_get_rss_key_size,
	.get_rxfh            = aq_ethtool_get_rss,
	.set_rxfh            = aq_ethtool_set_rss,
	.get_rxnfc           = aq_ethtool_get_rxnfc,
	.set_rxnfc           = aq_ethtool_set_rxnfc,
	.get_msglevel        = aq_get_msg_level,
	.set_msglevel        = aq_set_msg_level,
	.get_sset_count      = aq_ethtool_get_sset_count,
	.get_ethtool_stats   = aq_ethtool_stats,
	.get_priv_flags      = aq_ethtool_get_priv_flags,
	.set_priv_flags      = aq_ethtool_set_priv_flags,
	.get_link_ksettings  = aq_ethtool_get_link_ksettings,
	.set_link_ksettings  = aq_ethtool_set_link_ksettings,
	.get_coalesce	     = aq_ethtool_get_coalesce,
	.set_coalesce	     = aq_ethtool_set_coalesce,
	.get_ts_info         = aq_ethtool_get_ts_info,
	.get_phy_tunable     = aq_ethtool_get_phy_tunable,
	.set_phy_tunable     = aq_ethtool_set_phy_tunable,
पूर्ण;
