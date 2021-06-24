<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/of_mdपन.स>
#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_xgmac.h"
#समावेश "hns_dsaf_reg.h"

अटल स्थिर काष्ठा mac_stats_string g_xgmac_stats_string[] = अणु
	अणु"xgmac_tx_bad_pkts_minto64", MAC_STATS_FIELD_OFF(tx_fragment_err)पूर्ण,
	अणु"xgmac_tx_good_pkts_minto64", MAC_STATS_FIELD_OFF(tx_undersize)पूर्ण,
	अणु"xgmac_tx_total_pkts_minto64",	MAC_STATS_FIELD_OFF(tx_under_min_pkts)पूर्ण,
	अणु"xgmac_tx_pkts_64", MAC_STATS_FIELD_OFF(tx_64bytes)पूर्ण,
	अणु"xgmac_tx_pkts_65to127", MAC_STATS_FIELD_OFF(tx_65to127)पूर्ण,
	अणु"xgmac_tx_pkts_128to255", MAC_STATS_FIELD_OFF(tx_128to255)पूर्ण,
	अणु"xgmac_tx_pkts_256to511", MAC_STATS_FIELD_OFF(tx_256to511)पूर्ण,
	अणु"xgmac_tx_pkts_512to1023", MAC_STATS_FIELD_OFF(tx_512to1023)पूर्ण,
	अणु"xgmac_tx_pkts_1024to1518", MAC_STATS_FIELD_OFF(tx_1024to1518)पूर्ण,
	अणु"xgmac_tx_pkts_1519tomax", MAC_STATS_FIELD_OFF(tx_1519tomax)पूर्ण,
	अणु"xgmac_tx_good_pkts_1519tomax",
		MAC_STATS_FIELD_OFF(tx_1519tomax_good)पूर्ण,
	अणु"xgmac_tx_good_pkts_untralmax", MAC_STATS_FIELD_OFF(tx_oversize)पूर्ण,
	अणु"xgmac_tx_bad_pkts_untralmax", MAC_STATS_FIELD_OFF(tx_jabber_err)पूर्ण,
	अणु"xgmac_tx_good_pkts_all", MAC_STATS_FIELD_OFF(tx_good_pkts)पूर्ण,
	अणु"xgmac_tx_good_byte_all", MAC_STATS_FIELD_OFF(tx_good_bytes)पूर्ण,
	अणु"xgmac_tx_total_pkt", MAC_STATS_FIELD_OFF(tx_total_pkts)पूर्ण,
	अणु"xgmac_tx_total_byt", MAC_STATS_FIELD_OFF(tx_total_bytes)पूर्ण,
	अणु"xgmac_tx_uc_pkt", MAC_STATS_FIELD_OFF(tx_uc_pkts)पूर्ण,
	अणु"xgmac_tx_mc_pkt", MAC_STATS_FIELD_OFF(tx_mc_pkts)पूर्ण,
	अणु"xgmac_tx_bc_pkt", MAC_STATS_FIELD_OFF(tx_bc_pkts)पूर्ण,
	अणु"xgmac_tx_pause_frame_num", MAC_STATS_FIELD_OFF(tx_pfc_tc0)पूर्ण,
	अणु"xgmac_tx_pfc_per_1pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc1)पूर्ण,
	अणु"xgmac_tx_pfc_per_2pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc2)पूर्ण,
	अणु"xgmac_tx_pfc_per_3pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc3)पूर्ण,
	अणु"xgmac_tx_pfc_per_4pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc4)पूर्ण,
	अणु"xgmac_tx_pfc_per_5pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc5)पूर्ण,
	अणु"xgmac_tx_pfc_per_6pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc6)पूर्ण,
	अणु"xgmac_tx_pfc_per_7pause_framer", MAC_STATS_FIELD_OFF(tx_pfc_tc7)पूर्ण,
	अणु"xgmac_tx_mac_ctrol_frame", MAC_STATS_FIELD_OFF(tx_ctrl)पूर्ण,
	अणु"xgmac_tx_1731_pkts", MAC_STATS_FIELD_OFF(tx_1731_pkts)पूर्ण,
	अणु"xgmac_tx_1588_pkts", MAC_STATS_FIELD_OFF(tx_1588_pkts)पूर्ण,
	अणु"xgmac_rx_good_pkt_from_dsaf", MAC_STATS_FIELD_OFF(rx_good_from_sw)पूर्ण,
	अणु"xgmac_rx_bad_pkt_from_dsaf", MAC_STATS_FIELD_OFF(rx_bad_from_sw)पूर्ण,
	अणु"xgmac_tx_bad_pkt_64tomax", MAC_STATS_FIELD_OFF(tx_bad_pkts)पूर्ण,

	अणु"xgmac_rx_bad_pkts_minto64", MAC_STATS_FIELD_OFF(rx_fragment_err)पूर्ण,
	अणु"xgmac_rx_good_pkts_minto64", MAC_STATS_FIELD_OFF(rx_undersize)पूर्ण,
	अणु"xgmac_rx_total_pkts_minto64", MAC_STATS_FIELD_OFF(rx_under_min)पूर्ण,
	अणु"xgmac_rx_pkt_64", MAC_STATS_FIELD_OFF(rx_64bytes)पूर्ण,
	अणु"xgmac_rx_pkt_65to127", MAC_STATS_FIELD_OFF(rx_65to127)पूर्ण,
	अणु"xgmac_rx_pkt_128to255", MAC_STATS_FIELD_OFF(rx_128to255)पूर्ण,
	अणु"xgmac_rx_pkt_256to511", MAC_STATS_FIELD_OFF(rx_256to511)पूर्ण,
	अणु"xgmac_rx_pkt_512to1023", MAC_STATS_FIELD_OFF(rx_512to1023)पूर्ण,
	अणु"xgmac_rx_pkt_1024to1518", MAC_STATS_FIELD_OFF(rx_1024to1518)पूर्ण,
	अणु"xgmac_rx_pkt_1519tomax", MAC_STATS_FIELD_OFF(rx_1519tomax)पूर्ण,
	अणु"xgmac_rx_good_pkt_1519tomax",	MAC_STATS_FIELD_OFF(rx_1519tomax_good)पूर्ण,
	अणु"xgmac_rx_good_pkt_untramax", MAC_STATS_FIELD_OFF(rx_oversize)पूर्ण,
	अणु"xgmac_rx_bad_pkt_untramax", MAC_STATS_FIELD_OFF(rx_jabber_err)पूर्ण,
	अणु"xgmac_rx_good_pkt", MAC_STATS_FIELD_OFF(rx_good_pkts)पूर्ण,
	अणु"xgmac_rx_good_byt", MAC_STATS_FIELD_OFF(rx_good_bytes)पूर्ण,
	अणु"xgmac_rx_pkt", MAC_STATS_FIELD_OFF(rx_total_pkts)पूर्ण,
	अणु"xgmac_rx_byt", MAC_STATS_FIELD_OFF(rx_total_bytes)पूर्ण,
	अणु"xgmac_rx_uc_pkt", MAC_STATS_FIELD_OFF(rx_uc_pkts)पूर्ण,
	अणु"xgmac_rx_mc_pkt", MAC_STATS_FIELD_OFF(rx_mc_pkts)पूर्ण,
	अणु"xgmac_rx_bc_pkt", MAC_STATS_FIELD_OFF(rx_bc_pkts)पूर्ण,
	अणु"xgmac_rx_pause_frame_num", MAC_STATS_FIELD_OFF(rx_pfc_tc0)पूर्ण,
	अणु"xgmac_rx_pfc_per_1pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc1)पूर्ण,
	अणु"xgmac_rx_pfc_per_2pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc2)पूर्ण,
	अणु"xgmac_rx_pfc_per_3pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc3)पूर्ण,
	अणु"xgmac_rx_pfc_per_4pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc4)पूर्ण,
	अणु"xgmac_rx_pfc_per_5pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc5)पूर्ण,
	अणु"xgmac_rx_pfc_per_6pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc6)पूर्ण,
	अणु"xgmac_rx_pfc_per_7pause_frame", MAC_STATS_FIELD_OFF(rx_pfc_tc7)पूर्ण,
	अणु"xgmac_rx_mac_control", MAC_STATS_FIELD_OFF(rx_unknown_ctrl)पूर्ण,
	अणु"xgmac_tx_good_pkt_todsaf", MAC_STATS_FIELD_OFF(tx_good_to_sw)पूर्ण,
	अणु"xgmac_tx_bad_pkt_todsaf", MAC_STATS_FIELD_OFF(tx_bad_to_sw)पूर्ण,
	अणु"xgmac_rx_1731_pkt", MAC_STATS_FIELD_OFF(rx_1731_pkts)पूर्ण,
	अणु"xgmac_rx_symbol_err_pkt", MAC_STATS_FIELD_OFF(rx_symbol_err)पूर्ण,
	अणु"xgmac_rx_fcs_pkt", MAC_STATS_FIELD_OFF(rx_fcs_err)पूर्ण
पूर्ण;

/**
 *hns_xgmac_tx_enable - xgmac port tx enable
 *@drv: mac driver
 *@value: value of enable
 */
अटल व्योम hns_xgmac_tx_enable(काष्ठा mac_driver *drv, u32 value)
अणु
	dsaf_set_dev_bit(drv, XGMAC_MAC_ENABLE_REG, XGMAC_ENABLE_TX_B, !!value);
पूर्ण

/**
 *hns_xgmac_rx_enable - xgmac port rx enable
 *@drv: mac driver
 *@value: value of enable
 */
अटल व्योम hns_xgmac_rx_enable(काष्ठा mac_driver *drv, u32 value)
अणु
	dsaf_set_dev_bit(drv, XGMAC_MAC_ENABLE_REG, XGMAC_ENABLE_RX_B, !!value);
पूर्ण

/**
 * hns_xgmac_tx_lf_rf_insert - insert lf rf control about xgmac
 * @mac_drv: mac driver
 * @mode: inserf rf or lf
 */
अटल व्योम hns_xgmac_lf_rf_insert(काष्ठा mac_driver *mac_drv, u32 mode)
अणु
	dsaf_set_dev_field(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG,
			   XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, mode);
पूर्ण

/**
 * hns_xgmac__lf_rf_control_init - initial the lf rf control रेजिस्टर
 * @mac_drv: mac driver
 */
अटल व्योम hns_xgmac_lf_rf_control_init(काष्ठा mac_driver *mac_drv)
अणु
	u32 val = 0;

	dsaf_set_bit(val, XGMAC_UNIसूची_EN_B, 0);
	dsaf_set_bit(val, XGMAC_RF_TX_EN_B, 1);
	dsaf_set_field(val, XGMAC_LF_RF_INSERT_M, XGMAC_LF_RF_INSERT_S, 0);
	dsaf_ग_लिखो_dev(mac_drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG, val);
पूर्ण

/**
 *hns_xgmac_enable - enable xgmac port
 *@mac_drv: mac driver
 *@mode: mode of mac port
 */
अटल व्योम hns_xgmac_enable(व्योम *mac_drv, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	hns_xgmac_lf_rf_insert(drv, HNS_XGMAC_NO_LF_RF_INSERT);

	/*enable XGE rX/tX */
	अगर (mode == MAC_COMM_MODE_TX) अणु
		hns_xgmac_tx_enable(drv, 1);
	पूर्ण अन्यथा अगर (mode == MAC_COMM_MODE_RX) अणु
		hns_xgmac_rx_enable(drv, 1);
	पूर्ण अन्यथा अगर (mode == MAC_COMM_MODE_RX_AND_TX) अणु
		hns_xgmac_tx_enable(drv, 1);
		hns_xgmac_rx_enable(drv, 1);
	पूर्ण अन्यथा अणु
		dev_err(drv->dev, "error mac mode:%d\n", mode);
	पूर्ण
पूर्ण

/**
 *hns_xgmac_disable - disable xgmac port
 *@mac_drv: mac driver
 *@mode: mode of mac port
 */
अटल व्योम hns_xgmac_disable(व्योम *mac_drv, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	अगर (mode == MAC_COMM_MODE_TX) अणु
		hns_xgmac_tx_enable(drv, 0);
	पूर्ण अन्यथा अगर (mode == MAC_COMM_MODE_RX) अणु
		hns_xgmac_rx_enable(drv, 0);
	पूर्ण अन्यथा अगर (mode == MAC_COMM_MODE_RX_AND_TX) अणु
		hns_xgmac_tx_enable(drv, 0);
		hns_xgmac_rx_enable(drv, 0);
	पूर्ण
	hns_xgmac_lf_rf_insert(drv, HNS_XGMAC_LF_INSERT);
पूर्ण

/**
 *hns_xgmac_pma_fec_enable - xgmac PMA FEC enable
 *@drv: mac driver
 *@tx_value: tx value
 *@rx_value: rx value
 *वापस status
 */
अटल व्योम hns_xgmac_pma_fec_enable(काष्ठा mac_driver *drv, u32 tx_value,
				     u32 rx_value)
अणु
	u32 origin = dsaf_पढ़ो_dev(drv, XGMAC_PMA_FEC_CONTROL_REG);

	dsaf_set_bit(origin, XGMAC_PMA_FEC_CTL_TX_B, !!tx_value);
	dsaf_set_bit(origin, XGMAC_PMA_FEC_CTL_RX_B, !!rx_value);
	dsaf_ग_लिखो_dev(drv, XGMAC_PMA_FEC_CONTROL_REG, origin);
पूर्ण

/* clr exc irq क्रम xge*/
अटल व्योम hns_xgmac_exc_irq_en(काष्ठा mac_driver *drv, u32 en)
अणु
	u32 clr_vlue = 0xfffffffful;
	u32 msk_vlue = en ? 0xfffffffful : 0; /*1 is en, 0 is dis*/

	dsaf_ग_लिखो_dev(drv, XGMAC_INT_STATUS_REG, clr_vlue);
	dsaf_ग_लिखो_dev(drv, XGMAC_INT_ENABLE_REG, msk_vlue);
पूर्ण

/**
 *hns_xgmac_init - initialize XGE
 *@mac_drv: mac driver
 */
अटल व्योम hns_xgmac_init(व्योम *mac_drv)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा dsaf_device *dsaf_dev
		= (काष्ठा dsaf_device *)dev_get_drvdata(drv->dev);
	u32 port = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 0);
	msleep(100);
	dsaf_dev->misc_op->xge_srst(dsaf_dev, port, 1);

	msleep(100);
	hns_xgmac_lf_rf_control_init(drv);
	hns_xgmac_exc_irq_en(drv, 0);

	hns_xgmac_pma_fec_enable(drv, 0x0, 0x0);

	hns_xgmac_disable(mac_drv, MAC_COMM_MODE_RX_AND_TX);
पूर्ण

/**
 *hns_xgmac_config_pad_and_crc - set xgmac pad and crc enable the same समय
 *@mac_drv: mac driver
 *@newval:enable of pad and crc
 */
अटल व्योम hns_xgmac_config_pad_and_crc(व्योम *mac_drv, u8 newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 origin = dsaf_पढ़ो_dev(drv, XGMAC_MAC_CONTROL_REG);

	dsaf_set_bit(origin, XGMAC_CTL_TX_PAD_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_TX_FCS_B, !!newval);
	dsaf_set_bit(origin, XGMAC_CTL_RX_FCS_B, !!newval);
	dsaf_ग_लिखो_dev(drv, XGMAC_MAC_CONTROL_REG, origin);
पूर्ण

/**
 *hns_xgmac_छोड़ोfrm_cfg - set छोड़ो param about xgmac
 *@mac_drv: mac driver
 *@rx_en: enable receive
 *@tx_en: enable transmit
 */
अटल व्योम hns_xgmac_छोड़ोfrm_cfg(व्योम *mac_drv, u32 rx_en, u32 tx_en)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 origin = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG);

	dsaf_set_bit(origin, XGMAC_PAUSE_CTL_TX_B, !!tx_en);
	dsaf_set_bit(origin, XGMAC_PAUSE_CTL_RX_B, !!rx_en);
	dsaf_ग_लिखो_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG, origin);
पूर्ण

अटल व्योम hns_xgmac_set_छोड़ोfrm_mac_addr(व्योम *mac_drv, अक्षर *mac_addr)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	u32 high_val = mac_addr[1] | (mac_addr[0] << 8);
	u32 low_val = mac_addr[5] | (mac_addr[4] << 8)
		| (mac_addr[3] << 16) | (mac_addr[2] << 24);
	dsaf_ग_लिखो_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_L_REG, low_val);
	dsaf_ग_लिखो_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_H_REG, high_val);
पूर्ण

/**
 *hns_xgmac_set_tx_स्वतः_छोड़ो_frames - set tx छोड़ो param about xgmac
 *@mac_drv: mac driver
 *@enable:enable tx छोड़ो param
 */
अटल व्योम hns_xgmac_set_tx_स्वतः_छोड़ो_frames(व्योम *mac_drv, u16 enable)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, XGMAC_MAC_PAUSE_CTRL_REG,
			 XGMAC_PAUSE_CTL_TX_B, !!enable);

	/*अगर enable is not zero ,set tx छोड़ो समय */
	अगर (enable)
		dsaf_ग_लिखो_dev(drv, XGMAC_MAC_PAUSE_TIME_REG, enable);
पूर्ण

/**
 *hns_xgmac_config_max_frame_length - set xgmac max frame length
 *@mac_drv: mac driver
 *@newval:xgmac max frame length
 */
अटल व्योम hns_xgmac_config_max_frame_length(व्योम *mac_drv, u16 newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_ग_लिखो_dev(drv, XGMAC_MAC_MAX_PKT_SIZE_REG, newval);
पूर्ण

अटल व्योम hns_xgmac_update_stats(व्योम *mac_drv)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा mac_hw_stats *hw_stats = &drv->mac_cb->hw_stats;

	/* TX */
	hw_stats->tx_fragment_err
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_FRAGMENT);
	hw_stats->tx_undersize
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_UNDERSIZE);
	hw_stats->tx_under_min_pkts
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_UNDERMIN);
	hw_stats->tx_64bytes = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_64OCTETS);
	hw_stats->tx_65to127
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_65TO127OCTETS);
	hw_stats->tx_128to255
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_128TO255OCTETS);
	hw_stats->tx_256to511
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_256TO511OCTETS);
	hw_stats->tx_512to1023
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_512TO1023OCTETS);
	hw_stats->tx_1024to1518
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1024TO1518OCTETS);
	hw_stats->tx_1519tomax
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETS);
	hw_stats->tx_1519tomax_good
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->tx_oversize = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_OVERSIZE);
	hw_stats->tx_jabber_err = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_JABBER);
	hw_stats->tx_good_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_GOODPKTS);
	hw_stats->tx_good_bytes = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_GOODOCTETS);
	hw_stats->tx_total_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_TOTAL_PKTS);
	hw_stats->tx_total_bytes
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_TOTALOCTETS);
	hw_stats->tx_uc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_UNICASTPKTS);
	hw_stats->tx_mc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_MULTICASTPKTS);
	hw_stats->tx_bc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_BROADCASTPKTS);
	hw_stats->tx_pfc_tc0 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI0PAUSEPKTS);
	hw_stats->tx_pfc_tc1 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI1PAUSEPKTS);
	hw_stats->tx_pfc_tc2 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI2PAUSEPKTS);
	hw_stats->tx_pfc_tc3 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI3PAUSEPKTS);
	hw_stats->tx_pfc_tc4 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI4PAUSEPKTS);
	hw_stats->tx_pfc_tc5 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI5PAUSEPKTS);
	hw_stats->tx_pfc_tc6 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI6PAUSEPKTS);
	hw_stats->tx_pfc_tc7 = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI7PAUSEPKTS);
	hw_stats->tx_ctrl = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_MACCTRLPKTS);
	hw_stats->tx_1731_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_1731PKTS);
	hw_stats->tx_1588_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_1588PKTS);
	hw_stats->rx_good_from_sw
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FROMAPPGOODPKTS);
	hw_stats->rx_bad_from_sw
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FROMAPPBADPKTS);
	hw_stats->tx_bad_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_ERRALLPKTS);

	/* RX */
	hw_stats->rx_fragment_err
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_FRAGMENT);
	hw_stats->rx_undersize
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTSUNDERSIZE);
	hw_stats->rx_under_min
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_UNDERMIN);
	hw_stats->rx_64bytes = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_64OCTETS);
	hw_stats->rx_65to127
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_65TO127OCTETS);
	hw_stats->rx_128to255
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_128TO255OCTETS);
	hw_stats->rx_256to511
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_256TO511OCTETS);
	hw_stats->rx_512to1023
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_512TO1023OCTETS);
	hw_stats->rx_1024to1518
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1024TO1518OCTETS);
	hw_stats->rx_1519tomax
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETS);
	hw_stats->rx_1519tomax_good
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETSOK);
	hw_stats->rx_oversize = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_OVERSIZE);
	hw_stats->rx_jabber_err = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_JABBER);
	hw_stats->rx_good_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_GOODPKTS);
	hw_stats->rx_good_bytes = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_GOODOCTETS);
	hw_stats->rx_total_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_TOTAL_PKTS);
	hw_stats->rx_total_bytes
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_TOTALOCTETS);
	hw_stats->rx_uc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_UNICASTPKTS);
	hw_stats->rx_mc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_MULTICASTPKTS);
	hw_stats->rx_bc_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_BROADCASTPKTS);
	hw_stats->rx_pfc_tc0 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI0PAUSEPKTS);
	hw_stats->rx_pfc_tc1 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI1PAUSEPKTS);
	hw_stats->rx_pfc_tc2 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI2PAUSEPKTS);
	hw_stats->rx_pfc_tc3 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI3PAUSEPKTS);
	hw_stats->rx_pfc_tc4 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI4PAUSEPKTS);
	hw_stats->rx_pfc_tc5 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI5PAUSEPKTS);
	hw_stats->rx_pfc_tc6 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI6PAUSEPKTS);
	hw_stats->rx_pfc_tc7 = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI7PAUSEPKTS);

	hw_stats->rx_unknown_ctrl
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_MACCTRLPKTS);
	hw_stats->tx_good_to_sw
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_SENDAPPGOODPKTS);
	hw_stats->tx_bad_to_sw
		= hns_mac_reg_पढ़ो64(drv, XGMAC_TX_SENDAPPBADPKTS);
	hw_stats->rx_1731_pkts = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_1731PKTS);
	hw_stats->rx_symbol_err
		= hns_mac_reg_पढ़ो64(drv, XGMAC_RX_SYMBOLERRPKTS);
	hw_stats->rx_fcs_err = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FCSERRPKTS);
पूर्ण

/**
 *hns_xgmac_मुक्त - मुक्त xgmac driver
 *@mac_drv: mac driver
 */
अटल व्योम hns_xgmac_मुक्त(व्योम *mac_drv)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा dsaf_device *dsaf_dev
		= (काष्ठा dsaf_device *)dev_get_drvdata(drv->dev);

	u32 mac_id = drv->mac_id;

	dsaf_dev->misc_op->xge_srst(dsaf_dev, mac_id, 0);
पूर्ण

/**
 *hns_xgmac_get_info - get xgmac inक्रमmation
 *@mac_drv: mac driver
 *@mac_info:mac inक्रमmation
 */
अटल व्योम hns_xgmac_get_info(व्योम *mac_drv, काष्ठा mac_info *mac_info)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 छोड़ो_समय, छोड़ो_ctrl, port_mode, ctrl_val;

	ctrl_val = dsaf_पढ़ो_dev(drv, XGMAC_MAC_CONTROL_REG);
	mac_info->pad_and_crc_en = dsaf_get_bit(ctrl_val, XGMAC_CTL_TX_PAD_B);
	mac_info->स्वतः_neg = 0;

	छोड़ो_समय = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_TIME_REG);
	mac_info->tx_छोड़ो_समय = छोड़ो_समय;

	port_mode = dsaf_पढ़ो_dev(drv, XGMAC_PORT_MODE_REG);
	mac_info->port_en = dsaf_get_field(port_mode, XGMAC_PORT_MODE_TX_M,
					   XGMAC_PORT_MODE_TX_S) &&
				dsaf_get_field(port_mode, XGMAC_PORT_MODE_RX_M,
					       XGMAC_PORT_MODE_RX_S);
	mac_info->duplex = 1;
	mac_info->speed = MAC_SPEED_10000;

	छोड़ो_ctrl = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG);
	mac_info->rx_छोड़ो_en = dsaf_get_bit(छोड़ो_ctrl, XGMAC_PAUSE_CTL_RX_B);
	mac_info->tx_छोड़ो_en = dsaf_get_bit(छोड़ो_ctrl, XGMAC_PAUSE_CTL_TX_B);
पूर्ण

/**
 *hns_xgmac_get_छोड़ोfrm_cfg - get xgmac छोड़ो param
 *@mac_drv: mac driver
 *@rx_en:xgmac rx छोड़ो enable
 *@tx_en:xgmac tx छोड़ो enable
 */
अटल व्योम hns_xgmac_get_छोड़ोfrm_cfg(व्योम *mac_drv, u32 *rx_en, u32 *tx_en)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 छोड़ो_ctrl;

	छोड़ो_ctrl = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG);
	*rx_en = dsaf_get_bit(छोड़ो_ctrl, XGMAC_PAUSE_CTL_RX_B);
	*tx_en = dsaf_get_bit(छोड़ो_ctrl, XGMAC_PAUSE_CTL_TX_B);
पूर्ण

/**
 *hns_xgmac_get_link_status - get xgmac link status
 *@mac_drv: mac driver
 *@link_stat: xgmac link stat
 */
अटल व्योम hns_xgmac_get_link_status(व्योम *mac_drv, u32 *link_stat)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*link_stat = dsaf_पढ़ो_dev(drv, XGMAC_LINK_STATUS_REG);
पूर्ण

/**
 *hns_xgmac_get_regs - dump xgmac regs
 *@mac_drv: mac driver
 *@data:data क्रम value of regs
 */
अटल व्योम hns_xgmac_get_regs(व्योम *mac_drv, व्योम *data)
अणु
	u32 i;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 *regs = data;
	u64 qपंचांगp;

	/* base config रेजिस्टरs */
	regs[0] = dsaf_पढ़ो_dev(drv, XGMAC_INT_STATUS_REG);
	regs[1] = dsaf_पढ़ो_dev(drv, XGMAC_INT_ENABLE_REG);
	regs[2] = dsaf_पढ़ो_dev(drv, XGMAC_INT_SET_REG);
	regs[3] = dsaf_पढ़ो_dev(drv, XGMAC_IERR_U_INFO_REG);
	regs[4] = dsaf_पढ़ो_dev(drv, XGMAC_OVF_INFO_REG);
	regs[5] = dsaf_पढ़ो_dev(drv, XGMAC_OVF_CNT_REG);
	regs[6] = dsaf_पढ़ो_dev(drv, XGMAC_PORT_MODE_REG);
	regs[7] = dsaf_पढ़ो_dev(drv, XGMAC_CLK_ENABLE_REG);
	regs[8] = dsaf_पढ़ो_dev(drv, XGMAC_RESET_REG);
	regs[9] = dsaf_पढ़ो_dev(drv, XGMAC_LINK_CONTROL_REG);
	regs[10] = dsaf_पढ़ो_dev(drv, XGMAC_LINK_STATUS_REG);

	regs[11] = dsaf_पढ़ो_dev(drv, XGMAC_SPARE_REG);
	regs[12] = dsaf_पढ़ो_dev(drv, XGMAC_SPARE_CNT_REG);
	regs[13] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_ENABLE_REG);
	regs[14] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_CONTROL_REG);
	regs[15] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_IPG_REG);
	regs[16] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MSG_CRC_EN_REG);
	regs[17] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MSG_IMG_REG);
	regs[18] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MSG_FC_CFG_REG);
	regs[19] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MSG_TC_CFG_REG);
	regs[20] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAD_SIZE_REG);
	regs[21] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MIN_PKT_SIZE_REG);
	regs[22] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MAX_PKT_SIZE_REG);
	regs[23] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_CTRL_REG);
	regs[24] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_TIME_REG);
	regs[25] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_GAP_REG);
	regs[26] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_H_REG);
	regs[27] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_LOCAL_MAC_L_REG);
	regs[28] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_PEER_MAC_H_REG);
	regs[29] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PAUSE_PEER_MAC_L_REG);
	regs[30] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_PFC_PRI_EN_REG);
	regs[31] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_1588_CTRL_REG);
	regs[32] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_1588_TX_PORT_DLY_REG);
	regs[33] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_1588_RX_PORT_DLY_REG);
	regs[34] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_1588_ASYM_DLY_REG);
	regs[35] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_1588_ADJUST_CFG_REG);

	regs[36] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_Y1731_ETH_TYPE_REG);
	regs[37] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_MIB_CONTROL_REG);
	regs[38] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_WAN_RATE_ADJUST_REG);
	regs[39] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_TX_ERR_MARK_REG);
	regs[40] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_TX_LF_RF_CONTROL_REG);
	regs[41] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_RX_LF_RF_STATUS_REG);
	regs[42] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_TX_RUNT_PKT_CNT_REG);
	regs[43] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_RX_RUNT_PKT_CNT_REG);
	regs[44] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_RX_PREAM_ERR_PKT_CNT_REG);
	regs[45] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_TX_LF_RF_TERM_PKT_CNT_REG);
	regs[46] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_TX_SN_MISMATCH_PKT_CNT_REG);
	regs[47] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_RX_ERR_MSG_CNT_REG);
	regs[48] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_RX_ERR_EFD_CNT_REG);
	regs[49] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_ERR_INFO_REG);
	regs[50] = dsaf_पढ़ो_dev(drv, XGMAC_MAC_DBG_INFO_REG);

	regs[51] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_SYNC_THD_REG);
	regs[52] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_STATUS1_REG);
	regs[53] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_STATUS1_REG);
	regs[54] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_STATUS2_REG);
	regs[55] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_SEEDA_0_REG);
	regs[56] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_SEEDA_1_REG);
	regs[57] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_SEEDB_0_REG);
	regs[58] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_SEEDB_1_REG);
	regs[59] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_TEST_CONTROL_REG);
	regs[60] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_BASER_TEST_ERR_CNT_REG);
	regs[61] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_DBG_INFO_REG);
	regs[62] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_DBG_INFO1_REG);
	regs[63] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_DBG_INFO2_REG);
	regs[64] = dsaf_पढ़ो_dev(drv, XGMAC_PCS_DBG_INFO3_REG);

	regs[65] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_ENABLE_REG);
	regs[66] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_CONTROL_REG);
	regs[67] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_SIGNAL_STATUS_REG);
	regs[68] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_DBG_INFO_REG);
	regs[69] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_FEC_ABILITY_REG);
	regs[70] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_FEC_CONTROL_REG);
	regs[71] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_FEC_CORR_BLOCK_CNT__REG);
	regs[72] = dsaf_पढ़ो_dev(drv, XGMAC_PMA_FEC_UNCORR_BLOCK_CNT__REG);

	/* status रेजिस्टरs */
#घोषणा hns_xgmac_cpy_q(p, q) \
	करो अणु\
		*(p) = (u32)(q);\
		*((p) + 1) = (u32)((q) >> 32);\
	पूर्ण जबतक (0)

	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_FRAGMENT);
	hns_xgmac_cpy_q(&regs[73], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_UNDERSIZE);
	hns_xgmac_cpy_q(&regs[75], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_UNDERMIN);
	hns_xgmac_cpy_q(&regs[77], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_64OCTETS);
	hns_xgmac_cpy_q(&regs[79], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_65TO127OCTETS);
	hns_xgmac_cpy_q(&regs[81], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_128TO255OCTETS);
	hns_xgmac_cpy_q(&regs[83], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_256TO511OCTETS);
	hns_xgmac_cpy_q(&regs[85], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_512TO1023OCTETS);
	hns_xgmac_cpy_q(&regs[87], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1024TO1518OCTETS);
	hns_xgmac_cpy_q(&regs[89], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETS);
	hns_xgmac_cpy_q(&regs[91], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_1519TOMAXOCTETSOK);
	hns_xgmac_cpy_q(&regs[93], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_OVERSIZE);
	hns_xgmac_cpy_q(&regs[95], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PKTS_JABBER);
	hns_xgmac_cpy_q(&regs[97], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_GOODPKTS);
	hns_xgmac_cpy_q(&regs[99], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_GOODOCTETS);
	hns_xgmac_cpy_q(&regs[101], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_TOTAL_PKTS);
	hns_xgmac_cpy_q(&regs[103], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_TOTALOCTETS);
	hns_xgmac_cpy_q(&regs[105], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_UNICASTPKTS);
	hns_xgmac_cpy_q(&regs[107], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_MULTICASTPKTS);
	hns_xgmac_cpy_q(&regs[109], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_BROADCASTPKTS);
	hns_xgmac_cpy_q(&regs[111], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI0PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[113], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI1PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[115], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI2PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[117], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI3PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[119], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI4PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[121], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI5PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[123], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI6PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[125], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_PRI7PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[127], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_MACCTRLPKTS);
	hns_xgmac_cpy_q(&regs[129], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_1731PKTS);
	hns_xgmac_cpy_q(&regs[131], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_1588PKTS);
	hns_xgmac_cpy_q(&regs[133], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FROMAPPGOODPKTS);
	hns_xgmac_cpy_q(&regs[135], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FROMAPPBADPKTS);
	hns_xgmac_cpy_q(&regs[137], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_ERRALLPKTS);
	hns_xgmac_cpy_q(&regs[139], qपंचांगp);

	/* RX */
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_FRAGMENT);
	hns_xgmac_cpy_q(&regs[141], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTSUNDERSIZE);
	hns_xgmac_cpy_q(&regs[143], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_UNDERMIN);
	hns_xgmac_cpy_q(&regs[145], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_64OCTETS);
	hns_xgmac_cpy_q(&regs[147], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_65TO127OCTETS);
	hns_xgmac_cpy_q(&regs[149], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_128TO255OCTETS);
	hns_xgmac_cpy_q(&regs[151], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_256TO511OCTETS);
	hns_xgmac_cpy_q(&regs[153], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_512TO1023OCTETS);
	hns_xgmac_cpy_q(&regs[155], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1024TO1518OCTETS);
	hns_xgmac_cpy_q(&regs[157], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETS);
	hns_xgmac_cpy_q(&regs[159], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_1519TOMAXOCTETSOK);
	hns_xgmac_cpy_q(&regs[161], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_OVERSIZE);
	hns_xgmac_cpy_q(&regs[163], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PKTS_JABBER);
	hns_xgmac_cpy_q(&regs[165], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_GOODPKTS);
	hns_xgmac_cpy_q(&regs[167], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_GOODOCTETS);
	hns_xgmac_cpy_q(&regs[169], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_TOTAL_PKTS);
	hns_xgmac_cpy_q(&regs[171], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_TOTALOCTETS);
	hns_xgmac_cpy_q(&regs[173], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_UNICASTPKTS);
	hns_xgmac_cpy_q(&regs[175], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_MULTICASTPKTS);
	hns_xgmac_cpy_q(&regs[177], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_BROADCASTPKTS);
	hns_xgmac_cpy_q(&regs[179], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI0PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[181], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI1PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[183], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI2PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[185], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI3PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[187], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI4PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[189], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI5PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[191], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI6PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[193], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_PRI7PAUSEPKTS);
	hns_xgmac_cpy_q(&regs[195], qपंचांगp);

	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_MACCTRLPKTS);
	hns_xgmac_cpy_q(&regs[197], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_SENDAPPGOODPKTS);
	hns_xgmac_cpy_q(&regs[199], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_TX_SENDAPPBADPKTS);
	hns_xgmac_cpy_q(&regs[201], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_1731PKTS);
	hns_xgmac_cpy_q(&regs[203], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_SYMBOLERRPKTS);
	hns_xgmac_cpy_q(&regs[205], qपंचांगp);
	qपंचांगp = hns_mac_reg_पढ़ो64(drv, XGMAC_RX_FCSERRPKTS);
	hns_xgmac_cpy_q(&regs[207], qपंचांगp);

	/* mark end of mac regs */
	क्रम (i = 208; i < 214; i++)
		regs[i] = 0xaaaaaaaa;
पूर्ण

/**
 *hns_xgmac_get_stats - get xgmac statistic
 *@mac_drv: mac driver
 *@data:data क्रम value of stats regs
 */
अटल व्योम hns_xgmac_get_stats(व्योम *mac_drv, u64 *data)
अणु
	u32 i;
	u64 *buf = data;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा mac_hw_stats *hw_stats = शून्य;

	hw_stats = &drv->mac_cb->hw_stats;

	क्रम (i = 0; i < ARRAY_SIZE(g_xgmac_stats_string); i++) अणु
		buf[i] = DSAF_STATS_READ(hw_stats,
			g_xgmac_stats_string[i].offset);
	पूर्ण
पूर्ण

/**
 *hns_xgmac_get_strings - get xgmac strings name
 *@stringset: type of values in data
 *@data:data क्रम value of string name
 */
अटल व्योम hns_xgmac_get_strings(u32 stringset, u8 *data)
अणु
	u8 *buff = data;
	u32 i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(g_xgmac_stats_string); i++)
		ethtool_प्र_लिखो(&buff, g_xgmac_stats_string[i].desc);
पूर्ण

/**
 *hns_xgmac_get_sset_count - get xgmac string set count
 *@stringset: type of values in data
 *वापस xgmac string set count
 */
अटल पूर्णांक hns_xgmac_get_sset_count(पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS || stringset == ETH_SS_PRIV_FLAGS)
		वापस ARRAY_SIZE(g_xgmac_stats_string);

	वापस 0;
पूर्ण

/**
 *hns_xgmac_get_regs_count - get xgmac regs count
 *वापस xgmac regs count
 */
अटल पूर्णांक hns_xgmac_get_regs_count(व्योम)
अणु
	वापस HNS_XGMAC_DUMP_NUM;
पूर्ण

व्योम *hns_xgmac_config(काष्ठा hns_mac_cb *mac_cb, काष्ठा mac_params *mac_param)
अणु
	काष्ठा mac_driver *mac_drv;

	mac_drv = devm_kzalloc(mac_cb->dev, माप(*mac_drv), GFP_KERNEL);
	अगर (!mac_drv)
		वापस शून्य;

	mac_drv->mac_init = hns_xgmac_init;
	mac_drv->mac_enable = hns_xgmac_enable;
	mac_drv->mac_disable = hns_xgmac_disable;

	mac_drv->mac_id = mac_param->mac_id;
	mac_drv->mac_mode = mac_param->mac_mode;
	mac_drv->io_base = mac_param->vaddr;
	mac_drv->dev = mac_param->dev;
	mac_drv->mac_cb = mac_cb;

	mac_drv->set_mac_addr = hns_xgmac_set_छोड़ोfrm_mac_addr;
	mac_drv->set_an_mode = शून्य;
	mac_drv->config_loopback = शून्य;
	mac_drv->config_pad_and_crc = hns_xgmac_config_pad_and_crc;
	mac_drv->mac_मुक्त = hns_xgmac_मुक्त;
	mac_drv->adjust_link = शून्य;
	mac_drv->set_tx_स्वतः_छोड़ो_frames = hns_xgmac_set_tx_स्वतः_छोड़ो_frames;
	mac_drv->config_max_frame_length = hns_xgmac_config_max_frame_length;
	mac_drv->mac_छोड़ोfrm_cfg = hns_xgmac_छोड़ोfrm_cfg;
	mac_drv->स्वतःneg_stat = शून्य;
	mac_drv->get_info = hns_xgmac_get_info;
	mac_drv->get_छोड़ो_enable = hns_xgmac_get_छोड़ोfrm_cfg;
	mac_drv->get_link_status = hns_xgmac_get_link_status;
	mac_drv->get_regs = hns_xgmac_get_regs;
	mac_drv->get_ethtool_stats = hns_xgmac_get_stats;
	mac_drv->get_sset_count = hns_xgmac_get_sset_count;
	mac_drv->get_regs_count = hns_xgmac_get_regs_count;
	mac_drv->get_strings = hns_xgmac_get_strings;
	mac_drv->update_stats = hns_xgmac_update_stats;

	वापस (व्योम *)mac_drv;
पूर्ण
