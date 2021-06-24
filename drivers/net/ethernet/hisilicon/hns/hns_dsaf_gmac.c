<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/delay.h>
#समावेश <linux/of_mdपन.स>
#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_gmac.h"

अटल स्थिर काष्ठा mac_stats_string g_gmac_stats_string[] = अणु
	अणु"gmac_rx_octets_total_ok", MAC_STATS_FIELD_OFF(rx_good_bytes)पूर्ण,
	अणु"gmac_rx_octets_bad", MAC_STATS_FIELD_OFF(rx_bad_bytes)पूर्ण,
	अणु"gmac_rx_uc_pkts", MAC_STATS_FIELD_OFF(rx_uc_pkts)पूर्ण,
	अणु"gmac_rx_mc_pkts", MAC_STATS_FIELD_OFF(rx_mc_pkts)पूर्ण,
	अणु"gmac_rx_bc_pkts", MAC_STATS_FIELD_OFF(rx_bc_pkts)पूर्ण,
	अणु"gmac_rx_pkts_64octets", MAC_STATS_FIELD_OFF(rx_64bytes)पूर्ण,
	अणु"gmac_rx_pkts_65to127", MAC_STATS_FIELD_OFF(rx_65to127)पूर्ण,
	अणु"gmac_rx_pkts_128to255", MAC_STATS_FIELD_OFF(rx_128to255)पूर्ण,
	अणु"gmac_rx_pkts_256to511", MAC_STATS_FIELD_OFF(rx_256to511)पूर्ण,
	अणु"gmac_rx_pkts_512to1023", MAC_STATS_FIELD_OFF(rx_512to1023)पूर्ण,
	अणु"gmac_rx_pkts_1024to1518", MAC_STATS_FIELD_OFF(rx_1024to1518)पूर्ण,
	अणु"gmac_rx_pkts_1519tomax", MAC_STATS_FIELD_OFF(rx_1519tomax)पूर्ण,
	अणु"gmac_rx_fcs_errors", MAC_STATS_FIELD_OFF(rx_fcs_err)पूर्ण,
	अणु"gmac_rx_tagged", MAC_STATS_FIELD_OFF(rx_vlan_pkts)पूर्ण,
	अणु"gmac_rx_data_err", MAC_STATS_FIELD_OFF(rx_data_err)पूर्ण,
	अणु"gmac_rx_align_errors", MAC_STATS_FIELD_OFF(rx_align_err)पूर्ण,
	अणु"gmac_rx_long_errors", MAC_STATS_FIELD_OFF(rx_oversize)पूर्ण,
	अणु"gmac_rx_jabber_errors", MAC_STATS_FIELD_OFF(rx_jabber_err)पूर्ण,
	अणु"gmac_rx_pause_maccontrol", MAC_STATS_FIELD_OFF(rx_pfc_tc0)पूर्ण,
	अणु"gmac_rx_unknown_maccontrol", MAC_STATS_FIELD_OFF(rx_unknown_ctrl)पूर्ण,
	अणु"gmac_rx_very_long_err", MAC_STATS_FIELD_OFF(rx_दीर्घ_err)पूर्ण,
	अणु"gmac_rx_runt_err", MAC_STATS_FIELD_OFF(rx_mपूर्णांकo64)पूर्ण,
	अणु"gmac_rx_short_err", MAC_STATS_FIELD_OFF(rx_under_min)पूर्ण,
	अणु"gmac_rx_filt_pkt", MAC_STATS_FIELD_OFF(rx_filter_pkts)पूर्ण,
	अणु"gmac_rx_octets_total_filt", MAC_STATS_FIELD_OFF(rx_filter_bytes)पूर्ण,
	अणु"gmac_rx_overrun_cnt", MAC_STATS_FIELD_OFF(rx_fअगरo_overrun_err)पूर्ण,
	अणु"gmac_rx_length_err", MAC_STATS_FIELD_OFF(rx_len_err)पूर्ण,
	अणु"gmac_rx_fail_comma", MAC_STATS_FIELD_OFF(rx_comma_err)पूर्ण,

	अणु"gmac_tx_octets_ok", MAC_STATS_FIELD_OFF(tx_good_bytes)पूर्ण,
	अणु"gmac_tx_octets_bad", MAC_STATS_FIELD_OFF(tx_bad_bytes)पूर्ण,
	अणु"gmac_tx_uc_pkts", MAC_STATS_FIELD_OFF(tx_uc_pkts)पूर्ण,
	अणु"gmac_tx_mc_pkts", MAC_STATS_FIELD_OFF(tx_mc_pkts)पूर्ण,
	अणु"gmac_tx_bc_pkts", MAC_STATS_FIELD_OFF(tx_bc_pkts)पूर्ण,
	अणु"gmac_tx_pkts_64octets", MAC_STATS_FIELD_OFF(tx_64bytes)पूर्ण,
	अणु"gmac_tx_pkts_65to127", MAC_STATS_FIELD_OFF(tx_65to127)पूर्ण,
	अणु"gmac_tx_pkts_128to255", MAC_STATS_FIELD_OFF(tx_128to255)पूर्ण,
	अणु"gmac_tx_pkts_256to511", MAC_STATS_FIELD_OFF(tx_256to511)पूर्ण,
	अणु"gmac_tx_pkts_512to1023", MAC_STATS_FIELD_OFF(tx_512to1023)पूर्ण,
	अणु"gmac_tx_pkts_1024to1518", MAC_STATS_FIELD_OFF(tx_1024to1518)पूर्ण,
	अणु"gmac_tx_pkts_1519tomax", MAC_STATS_FIELD_OFF(tx_1519tomax)पूर्ण,
	अणु"gmac_tx_excessive_length_drop", MAC_STATS_FIELD_OFF(tx_jabber_err)पूर्ण,
	अणु"gmac_tx_underrun", MAC_STATS_FIELD_OFF(tx_underrun_err)पूर्ण,
	अणु"gmac_tx_tagged", MAC_STATS_FIELD_OFF(tx_vlan)पूर्ण,
	अणु"gmac_tx_crc_error", MAC_STATS_FIELD_OFF(tx_crc_err)पूर्ण,
	अणु"gmac_tx_pause_frames", MAC_STATS_FIELD_OFF(tx_pfc_tc0)पूर्ण
पूर्ण;

अटल व्योम hns_gmac_enable(व्योम *mac_drv, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	/*enable GE rX/tX */
	अगर (mode == MAC_COMM_MODE_TX || mode == MAC_COMM_MODE_RX_AND_TX)
		dsaf_set_dev_bit(drv, GMAC_PORT_EN_REG, GMAC_PORT_TX_EN_B, 1);

	अगर (mode == MAC_COMM_MODE_RX || mode == MAC_COMM_MODE_RX_AND_TX) अणु
		/* enable rx pcs */
		dsaf_set_dev_bit(drv, GMAC_PCS_RX_EN_REG, 0, 0);
		dsaf_set_dev_bit(drv, GMAC_PORT_EN_REG, GMAC_PORT_RX_EN_B, 1);
	पूर्ण
पूर्ण

अटल व्योम hns_gmac_disable(व्योम *mac_drv, क्रमागत mac_commom_mode mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	/*disable GE rX/tX */
	अगर (mode == MAC_COMM_MODE_TX || mode == MAC_COMM_MODE_RX_AND_TX)
		dsaf_set_dev_bit(drv, GMAC_PORT_EN_REG, GMAC_PORT_TX_EN_B, 0);

	अगर (mode == MAC_COMM_MODE_RX || mode == MAC_COMM_MODE_RX_AND_TX) अणु
		/* disable rx pcs */
		dsaf_set_dev_bit(drv, GMAC_PCS_RX_EN_REG, 0, 1);
		dsaf_set_dev_bit(drv, GMAC_PORT_EN_REG, GMAC_PORT_RX_EN_B, 0);
	पूर्ण
पूर्ण

/* hns_gmac_get_en - get port enable
 * @mac_drv:mac device
 * @rx:rx enable
 * @tx:tx enable
 */
अटल व्योम hns_gmac_get_en(व्योम *mac_drv, u32 *rx, u32 *tx)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	u32 porten;

	porten = dsaf_पढ़ो_dev(drv, GMAC_PORT_EN_REG);
	*tx = dsaf_get_bit(porten, GMAC_PORT_TX_EN_B);
	*rx = dsaf_get_bit(porten, GMAC_PORT_RX_EN_B);
पूर्ण

अटल व्योम hns_gmac_मुक्त(व्योम *mac_drv)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा dsaf_device *dsaf_dev
		= (काष्ठा dsaf_device *)dev_get_drvdata(drv->dev);

	u32 mac_id = drv->mac_id;

	dsaf_dev->misc_op->ge_srst(dsaf_dev, mac_id, 0);
पूर्ण

अटल व्योम hns_gmac_set_tx_स्वतः_छोड़ो_frames(व्योम *mac_drv, u16 newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_set_dev_field(drv, GMAC_FC_TX_TIMER_REG, GMAC_FC_TX_TIMER_M,
			   GMAC_FC_TX_TIMER_S, newval);
पूर्ण

अटल व्योम hns_gmac_get_tx_स्वतः_छोड़ो_frames(व्योम *mac_drv, u16 *newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*newval = dsaf_get_dev_field(drv, GMAC_FC_TX_TIMER_REG,
				     GMAC_FC_TX_TIMER_M, GMAC_FC_TX_TIMER_S);
पूर्ण

अटल व्योम hns_gmac_config_max_frame_length(व्योम *mac_drv, u16 newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_set_dev_field(drv, GMAC_MAX_FRM_SIZE_REG, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);

	dsaf_set_dev_field(drv, GAMC_RX_MAX_FRAME, GMAC_MAX_FRM_SIZE_M,
			   GMAC_MAX_FRM_SIZE_S, newval);
पूर्ण

अटल व्योम hns_gmac_config_pad_and_crc(व्योम *mac_drv, u8 newval)
अणु
	u32 tx_ctrl;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	tx_ctrl = dsaf_पढ़ो_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	dsaf_set_bit(tx_ctrl, GMAC_TX_PAD_EN_B, !!newval);
	dsaf_set_bit(tx_ctrl, GMAC_TX_CRC_ADD_B, !!newval);
	dsaf_ग_लिखो_dev(drv, GMAC_TRANSMIT_CONTROL_REG, tx_ctrl);
पूर्ण

अटल व्योम hns_gmac_config_an_mode(व्योम *mac_drv, u8 newval)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_TRANSMIT_CONTROL_REG,
			 GMAC_TX_AN_EN_B, !!newval);
पूर्ण

अटल व्योम hns_gmac_tx_loop_pkt_dis(व्योम *mac_drv)
अणु
	u32 tx_loop_pkt_pri;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	tx_loop_pkt_pri = dsaf_पढ़ो_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_EN_B, 1);
	dsaf_set_bit(tx_loop_pkt_pri, GMAC_TX_LOOP_PKT_HIG_PRI_B, 0);
	dsaf_ग_लिखो_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG, tx_loop_pkt_pri);
पूर्ण

अटल व्योम hns_gmac_get_duplex_type(व्योम *mac_drv,
				     क्रमागत hns_gmac_duplex_mकरोe *duplex_mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*duplex_mode = (क्रमागत hns_gmac_duplex_mकरोe)dsaf_get_dev_bit(
		drv, GMAC_DUPLEX_TYPE_REG, GMAC_DUPLEX_TYPE_B);
पूर्ण

अटल व्योम hns_gmac_get_port_mode(व्योम *mac_drv, क्रमागत hns_port_mode *port_mode)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*port_mode = (क्रमागत hns_port_mode)dsaf_get_dev_field(
		drv, GMAC_PORT_MODE_REG, GMAC_PORT_MODE_M, GMAC_PORT_MODE_S);
पूर्ण

अटल व्योम hns_gmac_port_mode_get(व्योम *mac_drv,
				   काष्ठा hns_gmac_port_mode_cfg *port_mode)
अणु
	u32 tx_ctrl;
	u32 recv_ctrl;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	port_mode->port_mode = (क्रमागत hns_port_mode)dsaf_get_dev_field(
		drv, GMAC_PORT_MODE_REG, GMAC_PORT_MODE_M, GMAC_PORT_MODE_S);

	tx_ctrl = dsaf_पढ़ो_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	recv_ctrl = dsaf_पढ़ो_dev(drv, GMAC_RECV_CONTROL_REG);

	port_mode->max_frm_size =
		dsaf_get_dev_field(drv, GMAC_MAX_FRM_SIZE_REG,
				   GMAC_MAX_FRM_SIZE_M, GMAC_MAX_FRM_SIZE_S);
	port_mode->लघु_runts_thr =
		dsaf_get_dev_field(drv, GMAC_SHORT_RUNTS_THR_REG,
				   GMAC_SHORT_RUNTS_THR_M,
				   GMAC_SHORT_RUNTS_THR_S);

	port_mode->pad_enable = dsaf_get_bit(tx_ctrl, GMAC_TX_PAD_EN_B);
	port_mode->crc_add = dsaf_get_bit(tx_ctrl, GMAC_TX_CRC_ADD_B);
	port_mode->an_enable = dsaf_get_bit(tx_ctrl, GMAC_TX_AN_EN_B);

	port_mode->runt_pkt_en =
		dsaf_get_bit(recv_ctrl, GMAC_RECV_CTRL_RUNT_PKT_EN_B);
	port_mode->strip_pad_en =
		dsaf_get_bit(recv_ctrl, GMAC_RECV_CTRL_STRIP_PAD_EN_B);
पूर्ण

अटल व्योम hns_gmac_छोड़ो_frm_cfg(व्योम *mac_drv, u32 rx_छोड़ो_en,
				   u32 tx_छोड़ो_en)
अणु
	u32 छोड़ो_en;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	छोड़ो_en = dsaf_पढ़ो_dev(drv, GMAC_PAUSE_EN_REG);
	dsaf_set_bit(छोड़ो_en, GMAC_PAUSE_EN_RX_FDFC_B, !!rx_छोड़ो_en);
	dsaf_set_bit(छोड़ो_en, GMAC_PAUSE_EN_TX_FDFC_B, !!tx_छोड़ो_en);
	dsaf_ग_लिखो_dev(drv, GMAC_PAUSE_EN_REG, छोड़ो_en);
पूर्ण

अटल व्योम hns_gmac_get_छोड़ोfrm_cfg(व्योम *mac_drv, u32 *rx_छोड़ो_en,
				      u32 *tx_छोड़ो_en)
अणु
	u32 छोड़ो_en;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	छोड़ो_en = dsaf_पढ़ो_dev(drv, GMAC_PAUSE_EN_REG);

	*rx_छोड़ो_en = dsaf_get_bit(छोड़ो_en, GMAC_PAUSE_EN_RX_FDFC_B);
	*tx_छोड़ो_en = dsaf_get_bit(छोड़ो_en, GMAC_PAUSE_EN_TX_FDFC_B);
पूर्ण

अटल bool hns_gmac_need_adjust_link(व्योम *mac_drv, क्रमागत mac_speed speed,
				      पूर्णांक duplex)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा hns_mac_cb *mac_cb = drv->mac_cb;

	वापस (mac_cb->speed != speed) ||
		(mac_cb->half_duplex == duplex);
पूर्ण

अटल पूर्णांक hns_gmac_adjust_link(व्योम *mac_drv, क्रमागत mac_speed speed,
				u32 full_duplex)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	dsaf_set_dev_bit(drv, GMAC_DUPLEX_TYPE_REG,
			 GMAC_DUPLEX_TYPE_B, !!full_duplex);

	चयन (speed) अणु
	हाल MAC_SPEED_10:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x6);
		अवरोध;
	हाल MAC_SPEED_100:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x7);
		अवरोध;
	हाल MAC_SPEED_1000:
		dsaf_set_dev_field(
			drv, GMAC_PORT_MODE_REG,
			GMAC_PORT_MODE_M, GMAC_PORT_MODE_S, 0x8);
		अवरोध;
	शेष:
		dev_err(drv->dev,
			"hns_gmac_adjust_link fail, speed%d mac%d\n",
			speed, drv->mac_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_gmac_set_uc_match(व्योम *mac_drv, u16 en)
अणु
	काष्ठा mac_driver *drv = mac_drv;

	dsaf_set_dev_bit(drv, GMAC_REC_FILT_CONTROL_REG,
			 GMAC_UC_MATCH_EN_B, !en);
	dsaf_set_dev_bit(drv, GMAC_STATION_ADDR_HIGH_2_REG,
			 GMAC_ADDR_EN_B, !en);
पूर्ण

अटल व्योम hns_gmac_set_promisc(व्योम *mac_drv, u8 en)
अणु
	काष्ठा mac_driver *drv = mac_drv;

	अगर (drv->mac_cb->mac_type == HNAE_PORT_DEBUG)
		hns_gmac_set_uc_match(mac_drv, en);
पूर्ण

अटल पूर्णांक hns_gmac_रुको_fअगरo_clean(व्योम *mac_drv)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	पूर्णांक रुको_cnt;
	u32 val;

	रुको_cnt = 0;
	जबतक (रुको_cnt++ < HNS_MAX_WAIT_CNT) अणु
		val = dsaf_पढ़ो_dev(drv, GMAC_FIFO_STATE_REG);
		/* bit5~bit0 is not send complete pkts */
		अगर ((val & 0x3f) == 0)
			अवरोध;
		usleep_range(100, 200);
	पूर्ण

	अगर (रुको_cnt >= HNS_MAX_WAIT_CNT) अणु
		dev_err(drv->dev,
			"hns ge %d fifo was not idle.\n", drv->mac_id);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_gmac_init(व्योम *mac_drv)
अणु
	u32 port;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा dsaf_device *dsaf_dev
		= (काष्ठा dsaf_device *)dev_get_drvdata(drv->dev);

	port = drv->mac_id;

	dsaf_dev->misc_op->ge_srst(dsaf_dev, port, 0);
	mdelay(10);
	dsaf_dev->misc_op->ge_srst(dsaf_dev, port, 1);
	mdelay(10);
	hns_gmac_disable(mac_drv, MAC_COMM_MODE_RX_AND_TX);
	hns_gmac_tx_loop_pkt_dis(mac_drv);
	अगर (drv->mac_cb->mac_type == HNAE_PORT_DEBUG)
		hns_gmac_set_uc_match(mac_drv, 0);

	hns_gmac_config_pad_and_crc(mac_drv, 1);

	dsaf_set_dev_bit(drv, GMAC_MODE_CHANGE_EN_REG,
			 GMAC_MODE_CHANGE_EB_B, 1);

	/* reduce gmac tx water line to aव्योम gmac hang-up
	 * in speed 100M and duplex half.
	 */
	dsaf_set_dev_field(drv, GMAC_TX_WATER_LINE_REG, GMAC_TX_WATER_LINE_MASK,
			   GMAC_TX_WATER_LINE_SHIFT, 8);
पूर्ण

अटल व्योम hns_gmac_update_stats(व्योम *mac_drv)
अणु
	काष्ठा mac_hw_stats *hw_stats = शून्य;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	hw_stats = &drv->mac_cb->hw_stats;

	/* RX */
	hw_stats->rx_good_bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_TOTAL_OK_REG);
	hw_stats->rx_bad_bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_BAD_REG);
	hw_stats->rx_uc_pkts += dsaf_पढ़ो_dev(drv, GMAC_RX_UC_PKTS_REG);
	hw_stats->rx_mc_pkts += dsaf_पढ़ो_dev(drv, GMAC_RX_MC_PKTS_REG);
	hw_stats->rx_bc_pkts += dsaf_पढ़ो_dev(drv, GMAC_RX_BC_PKTS_REG);
	hw_stats->rx_64bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_64OCTETS_REG);
	hw_stats->rx_65to127
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_65TO127OCTETS_REG);
	hw_stats->rx_128to255
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_128TO255OCTETS_REG);
	hw_stats->rx_256to511
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_255TO511OCTETS_REG);
	hw_stats->rx_512to1023
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_512TO1023OCTETS_REG);
	hw_stats->rx_1024to1518
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_1024TO1518OCTETS_REG);
	hw_stats->rx_1519tomax
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_1519TOMAXOCTETS_REG);
	hw_stats->rx_fcs_err += dsaf_पढ़ो_dev(drv, GMAC_RX_FCS_ERRORS_REG);
	hw_stats->rx_vlan_pkts += dsaf_पढ़ो_dev(drv, GMAC_RX_TAGGED_REG);
	hw_stats->rx_data_err += dsaf_पढ़ो_dev(drv, GMAC_RX_DATA_ERR_REG);
	hw_stats->rx_align_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_ALIGN_ERRORS_REG);
	hw_stats->rx_oversize
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_LONG_ERRORS_REG);
	hw_stats->rx_jabber_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_JABBER_ERRORS_REG);
	hw_stats->rx_pfc_tc0
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_PAUSE_MACCTRL_FRAM_REG);
	hw_stats->rx_unknown_ctrl
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG);
	hw_stats->rx_दीर्घ_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_VERY_LONG_ERR_CNT_REG);
	hw_stats->rx_mपूर्णांकo64
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_RUNT_ERR_CNT_REG);
	hw_stats->rx_under_min
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_SHORT_ERR_CNT_REG);
	hw_stats->rx_filter_pkts
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_FILT_PKT_CNT_REG);
	hw_stats->rx_filter_bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_TOTAL_FILT_REG);
	hw_stats->rx_fअगरo_overrun_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_OVERRUN_CNT_REG);
	hw_stats->rx_len_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_LENGTHFIELD_ERR_CNT_REG);
	hw_stats->rx_comma_err
		+= dsaf_पढ़ो_dev(drv, GMAC_RX_FAIL_COMMA_CNT_REG);

	/* TX */
	hw_stats->tx_good_bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_OCTETS_TRANSMITTED_OK_REG);
	hw_stats->tx_bad_bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_OCTETS_TRANSMITTED_BAD_REG);
	hw_stats->tx_uc_pkts += dsaf_पढ़ो_dev(drv, GMAC_TX_UC_PKTS_REG);
	hw_stats->tx_mc_pkts += dsaf_पढ़ो_dev(drv, GMAC_TX_MC_PKTS_REG);
	hw_stats->tx_bc_pkts += dsaf_पढ़ो_dev(drv, GMAC_TX_BC_PKTS_REG);
	hw_stats->tx_64bytes
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_64OCTETS_REG);
	hw_stats->tx_65to127
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_65TO127OCTETS_REG);
	hw_stats->tx_128to255
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_128TO255OCTETS_REG);
	hw_stats->tx_256to511
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_255TO511OCTETS_REG);
	hw_stats->tx_512to1023
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_512TO1023OCTETS_REG);
	hw_stats->tx_1024to1518
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_1024TO1518OCTETS_REG);
	hw_stats->tx_1519tomax
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_1519TOMAXOCTETS_REG);
	hw_stats->tx_jabber_err
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_EXCESSIVE_LENGTH_DROP_REG);
	hw_stats->tx_underrun_err
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_UNDERRUN_REG);
	hw_stats->tx_vlan += dsaf_पढ़ो_dev(drv, GMAC_TX_TAGGED_REG);
	hw_stats->tx_crc_err += dsaf_पढ़ो_dev(drv, GMAC_TX_CRC_ERROR_REG);
	hw_stats->tx_pfc_tc0
		+= dsaf_पढ़ो_dev(drv, GMAC_TX_PAUSE_FRAMES_REG);
पूर्ण

अटल व्योम hns_gmac_set_mac_addr(व्योम *mac_drv, अक्षर *mac_addr)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	u32 high_val = mac_addr[1] | (mac_addr[0] << 8);

	u32 low_val = mac_addr[5] | (mac_addr[4] << 8)
		| (mac_addr[3] << 16) | (mac_addr[2] << 24);

	u32 val = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG);
	u32 sta_addr_en = dsaf_get_bit(val, GMAC_ADDR_EN_B);

	dsaf_ग_लिखो_dev(drv, GMAC_STATION_ADDR_LOW_2_REG, low_val);
	dsaf_ग_लिखो_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG,
		       high_val | (sta_addr_en << GMAC_ADDR_EN_B));
पूर्ण

अटल पूर्णांक hns_gmac_config_loopback(व्योम *mac_drv, क्रमागत hnae_loop loop_mode,
				    u8 enable)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	चयन (loop_mode) अणु
	हाल MAC_INTERNALLOOP_MAC:
		dsaf_set_dev_bit(drv, GMAC_LOOP_REG, GMAC_LP_REG_CF2MI_LP_EN_B,
				 !!enable);
		अवरोध;
	शेष:
		dev_err(drv->dev, "loop_mode error\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hns_gmac_get_info(व्योम *mac_drv, काष्ठा mac_info *mac_info)
अणु
	क्रमागत hns_gmac_duplex_mकरोe duplex;
	क्रमागत hns_port_mode speed;
	u32 rx_छोड़ो;
	u32 tx_छोड़ो;
	u32 rx;
	u32 tx;
	u16 fc_tx_समयr;
	काष्ठा hns_gmac_port_mode_cfg port_mode = अणु GMAC_10M_MII, 0 पूर्ण;

	hns_gmac_port_mode_get(mac_drv, &port_mode);
	mac_info->pad_and_crc_en = port_mode.crc_add && port_mode.pad_enable;
	mac_info->स्वतः_neg = port_mode.an_enable;

	hns_gmac_get_tx_स्वतः_छोड़ो_frames(mac_drv, &fc_tx_समयr);
	mac_info->tx_छोड़ो_समय = fc_tx_समयr;

	hns_gmac_get_en(mac_drv, &rx, &tx);
	mac_info->port_en = rx && tx;

	hns_gmac_get_duplex_type(mac_drv, &duplex);
	mac_info->duplex = duplex;

	hns_gmac_get_port_mode(mac_drv, &speed);
	चयन (speed) अणु
	हाल GMAC_10M_SGMII:
		mac_info->speed = MAC_SPEED_10;
		अवरोध;
	हाल GMAC_100M_SGMII:
		mac_info->speed = MAC_SPEED_100;
		अवरोध;
	हाल GMAC_1000M_SGMII:
		mac_info->speed = MAC_SPEED_1000;
		अवरोध;
	शेष:
		mac_info->speed = 0;
		अवरोध;
	पूर्ण

	hns_gmac_get_छोड़ोfrm_cfg(mac_drv, &rx_छोड़ो, &tx_छोड़ो);
	mac_info->rx_छोड़ो_en = rx_छोड़ो;
	mac_info->tx_छोड़ो_en = tx_छोड़ो;
पूर्ण

अटल व्योम hns_gmac_स्वतःneg_stat(व्योम *mac_drv, u32 *enable)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*enable = dsaf_get_dev_bit(drv, GMAC_TRANSMIT_CONTROL_REG,
				   GMAC_TX_AN_EN_B);
पूर्ण

अटल व्योम hns_gmac_get_link_status(व्योम *mac_drv, u32 *link_stat)
अणु
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	*link_stat = dsaf_get_dev_bit(drv, GMAC_AN_NEG_STATE_REG,
				      GMAC_AN_NEG_STAT_RX_SYNC_OK_B);
पूर्ण

अटल व्योम hns_gmac_get_regs(व्योम *mac_drv, व्योम *data)
अणु
	u32 *regs = data;
	पूर्णांक i;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;

	/* base config रेजिस्टरs */
	regs[0] = dsaf_पढ़ो_dev(drv, GMAC_DUPLEX_TYPE_REG);
	regs[1] = dsaf_पढ़ो_dev(drv, GMAC_FD_FC_TYPE_REG);
	regs[2] = dsaf_पढ़ो_dev(drv, GMAC_FC_TX_TIMER_REG);
	regs[3] = dsaf_पढ़ो_dev(drv, GMAC_FD_FC_ADDR_LOW_REG);
	regs[4] = dsaf_पढ़ो_dev(drv, GMAC_FD_FC_ADDR_HIGH_REG);
	regs[5] = dsaf_पढ़ो_dev(drv, GMAC_IPG_TX_TIMER_REG);
	regs[6] = dsaf_पढ़ो_dev(drv, GMAC_PAUSE_THR_REG);
	regs[7] = dsaf_पढ़ो_dev(drv, GMAC_MAX_FRM_SIZE_REG);
	regs[8] = dsaf_पढ़ो_dev(drv, GMAC_PORT_MODE_REG);
	regs[9] = dsaf_पढ़ो_dev(drv, GMAC_PORT_EN_REG);
	regs[10] = dsaf_पढ़ो_dev(drv, GMAC_PAUSE_EN_REG);
	regs[11] = dsaf_पढ़ो_dev(drv, GMAC_SHORT_RUNTS_THR_REG);
	regs[12] = dsaf_पढ़ो_dev(drv, GMAC_AN_NEG_STATE_REG);
	regs[13] = dsaf_पढ़ो_dev(drv, GMAC_TX_LOCAL_PAGE_REG);
	regs[14] = dsaf_पढ़ो_dev(drv, GMAC_TRANSMIT_CONTROL_REG);
	regs[15] = dsaf_पढ़ो_dev(drv, GMAC_REC_FILT_CONTROL_REG);
	regs[16] = dsaf_पढ़ो_dev(drv, GMAC_PTP_CONFIG_REG);

	/* rx अटल रेजिस्टरs */
	regs[17] = dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_TOTAL_OK_REG);
	regs[18] = dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_BAD_REG);
	regs[19] = dsaf_पढ़ो_dev(drv, GMAC_RX_UC_PKTS_REG);
	regs[20] = dsaf_पढ़ो_dev(drv, GMAC_RX_MC_PKTS_REG);
	regs[21] = dsaf_पढ़ो_dev(drv, GMAC_RX_BC_PKTS_REG);
	regs[22] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_64OCTETS_REG);
	regs[23] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_65TO127OCTETS_REG);
	regs[24] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_128TO255OCTETS_REG);
	regs[25] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_255TO511OCTETS_REG);
	regs[26] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_512TO1023OCTETS_REG);
	regs[27] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_1024TO1518OCTETS_REG);
	regs[28] = dsaf_पढ़ो_dev(drv, GMAC_RX_PKTS_1519TOMAXOCTETS_REG);
	regs[29] = dsaf_पढ़ो_dev(drv, GMAC_RX_FCS_ERRORS_REG);
	regs[30] = dsaf_पढ़ो_dev(drv, GMAC_RX_TAGGED_REG);
	regs[31] = dsaf_पढ़ो_dev(drv, GMAC_RX_DATA_ERR_REG);
	regs[32] = dsaf_पढ़ो_dev(drv, GMAC_RX_ALIGN_ERRORS_REG);
	regs[33] = dsaf_पढ़ो_dev(drv, GMAC_RX_LONG_ERRORS_REG);
	regs[34] = dsaf_पढ़ो_dev(drv, GMAC_RX_JABBER_ERRORS_REG);
	regs[35] = dsaf_पढ़ो_dev(drv, GMAC_RX_PAUSE_MACCTRL_FRAM_REG);
	regs[36] = dsaf_पढ़ो_dev(drv, GMAC_RX_UNKNOWN_MACCTRL_FRAM_REG);
	regs[37] = dsaf_पढ़ो_dev(drv, GMAC_RX_VERY_LONG_ERR_CNT_REG);
	regs[38] = dsaf_पढ़ो_dev(drv, GMAC_RX_RUNT_ERR_CNT_REG);
	regs[39] = dsaf_पढ़ो_dev(drv, GMAC_RX_SHORT_ERR_CNT_REG);
	regs[40] = dsaf_पढ़ो_dev(drv, GMAC_RX_FILT_PKT_CNT_REG);
	regs[41] = dsaf_पढ़ो_dev(drv, GMAC_RX_OCTETS_TOTAL_FILT_REG);

	/* tx अटल रेजिस्टरs */
	regs[42] = dsaf_पढ़ो_dev(drv, GMAC_OCTETS_TRANSMITTED_OK_REG);
	regs[43] = dsaf_पढ़ो_dev(drv, GMAC_OCTETS_TRANSMITTED_BAD_REG);
	regs[44] = dsaf_पढ़ो_dev(drv, GMAC_TX_UC_PKTS_REG);
	regs[45] = dsaf_पढ़ो_dev(drv, GMAC_TX_MC_PKTS_REG);
	regs[46] = dsaf_पढ़ो_dev(drv, GMAC_TX_BC_PKTS_REG);
	regs[47] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_64OCTETS_REG);
	regs[48] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_65TO127OCTETS_REG);
	regs[49] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_128TO255OCTETS_REG);
	regs[50] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_255TO511OCTETS_REG);
	regs[51] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_512TO1023OCTETS_REG);
	regs[52] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_1024TO1518OCTETS_REG);
	regs[53] = dsaf_पढ़ो_dev(drv, GMAC_TX_PKTS_1519TOMAXOCTETS_REG);
	regs[54] = dsaf_पढ़ो_dev(drv, GMAC_TX_EXCESSIVE_LENGTH_DROP_REG);
	regs[55] = dsaf_पढ़ो_dev(drv, GMAC_TX_UNDERRUN_REG);
	regs[56] = dsaf_पढ़ो_dev(drv, GMAC_TX_TAGGED_REG);
	regs[57] = dsaf_पढ़ो_dev(drv, GMAC_TX_CRC_ERROR_REG);
	regs[58] = dsaf_पढ़ो_dev(drv, GMAC_TX_PAUSE_FRAMES_REG);

	regs[59] = dsaf_पढ़ो_dev(drv, GAMC_RX_MAX_FRAME);
	regs[60] = dsaf_पढ़ो_dev(drv, GMAC_LINE_LOOP_BACK_REG);
	regs[61] = dsaf_पढ़ो_dev(drv, GMAC_CF_CRC_STRIP_REG);
	regs[62] = dsaf_पढ़ो_dev(drv, GMAC_MODE_CHANGE_EN_REG);
	regs[63] = dsaf_पढ़ो_dev(drv, GMAC_SIXTEEN_BIT_CNTR_REG);
	regs[64] = dsaf_पढ़ो_dev(drv, GMAC_LD_LINK_COUNTER_REG);
	regs[65] = dsaf_पढ़ो_dev(drv, GMAC_LOOP_REG);
	regs[66] = dsaf_पढ़ो_dev(drv, GMAC_RECV_CONTROL_REG);
	regs[67] = dsaf_पढ़ो_dev(drv, GMAC_VLAN_CODE_REG);
	regs[68] = dsaf_पढ़ो_dev(drv, GMAC_RX_OVERRUN_CNT_REG);
	regs[69] = dsaf_पढ़ो_dev(drv, GMAC_RX_LENGTHFIELD_ERR_CNT_REG);
	regs[70] = dsaf_पढ़ो_dev(drv, GMAC_RX_FAIL_COMMA_CNT_REG);

	regs[71] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_0_REG);
	regs[72] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_0_REG);
	regs[73] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_1_REG);
	regs[74] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_1_REG);
	regs[75] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_2_REG);
	regs[76] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_2_REG);
	regs[77] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_3_REG);
	regs[78] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_3_REG);
	regs[79] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_4_REG);
	regs[80] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_4_REG);
	regs[81] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_5_REG);
	regs[82] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_5_REG);
	regs[83] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_MSK_0_REG);
	regs[84] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_MSK_0_REG);
	regs[85] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_LOW_MSK_1_REG);
	regs[86] = dsaf_पढ़ो_dev(drv, GMAC_STATION_ADDR_HIGH_MSK_1_REG);
	regs[87] = dsaf_पढ़ो_dev(drv, GMAC_MAC_SKIP_LEN_REG);
	regs[88] = dsaf_पढ़ो_dev(drv, GMAC_TX_LOOP_PKT_PRI_REG);

	/* mark end of mac regs */
	क्रम (i = 89; i < 96; i++)
		regs[i] = 0xaaaaaaaa;
पूर्ण

अटल व्योम hns_gmac_get_stats(व्योम *mac_drv, u64 *data)
अणु
	u32 i;
	u64 *buf = data;
	काष्ठा mac_driver *drv = (काष्ठा mac_driver *)mac_drv;
	काष्ठा mac_hw_stats *hw_stats = शून्य;

	hw_stats = &drv->mac_cb->hw_stats;

	क्रम (i = 0; i < ARRAY_SIZE(g_gmac_stats_string); i++) अणु
		buf[i] = DSAF_STATS_READ(hw_stats,
			g_gmac_stats_string[i].offset);
	पूर्ण
पूर्ण

अटल व्योम hns_gmac_get_strings(u32 stringset, u8 *data)
अणु
	u8 *buff = data;
	u32 i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(g_gmac_stats_string); i++)
		ethtool_प्र_लिखो(&buff, g_gmac_stats_string[i].desc);
पूर्ण

अटल पूर्णांक hns_gmac_get_sset_count(पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS)
		वापस ARRAY_SIZE(g_gmac_stats_string);

	वापस 0;
पूर्ण

अटल पूर्णांक hns_gmac_get_regs_count(व्योम)
अणु
	वापस ETH_GMAC_DUMP_NUM;
पूर्ण

व्योम *hns_gmac_config(काष्ठा hns_mac_cb *mac_cb, काष्ठा mac_params *mac_param)
अणु
	काष्ठा mac_driver *mac_drv;

	mac_drv = devm_kzalloc(mac_cb->dev, माप(*mac_drv), GFP_KERNEL);
	अगर (!mac_drv)
		वापस शून्य;

	mac_drv->mac_init = hns_gmac_init;
	mac_drv->mac_enable = hns_gmac_enable;
	mac_drv->mac_disable = hns_gmac_disable;
	mac_drv->mac_मुक्त = hns_gmac_मुक्त;
	mac_drv->adjust_link = hns_gmac_adjust_link;
	mac_drv->need_adjust_link = hns_gmac_need_adjust_link;
	mac_drv->set_tx_स्वतः_छोड़ो_frames = hns_gmac_set_tx_स्वतः_छोड़ो_frames;
	mac_drv->config_max_frame_length = hns_gmac_config_max_frame_length;
	mac_drv->mac_छोड़ोfrm_cfg = hns_gmac_छोड़ो_frm_cfg;

	mac_drv->mac_id = mac_param->mac_id;
	mac_drv->mac_mode = mac_param->mac_mode;
	mac_drv->io_base = mac_param->vaddr;
	mac_drv->dev = mac_param->dev;
	mac_drv->mac_cb = mac_cb;

	mac_drv->set_mac_addr = hns_gmac_set_mac_addr;
	mac_drv->set_an_mode = hns_gmac_config_an_mode;
	mac_drv->config_loopback = hns_gmac_config_loopback;
	mac_drv->config_pad_and_crc = hns_gmac_config_pad_and_crc;
	mac_drv->get_info = hns_gmac_get_info;
	mac_drv->स्वतःneg_stat = hns_gmac_स्वतःneg_stat;
	mac_drv->get_छोड़ो_enable = hns_gmac_get_छोड़ोfrm_cfg;
	mac_drv->get_link_status = hns_gmac_get_link_status;
	mac_drv->get_regs = hns_gmac_get_regs;
	mac_drv->get_regs_count = hns_gmac_get_regs_count;
	mac_drv->get_ethtool_stats = hns_gmac_get_stats;
	mac_drv->get_sset_count = hns_gmac_get_sset_count;
	mac_drv->get_strings = hns_gmac_get_strings;
	mac_drv->update_stats = hns_gmac_update_stats;
	mac_drv->set_promiscuous = hns_gmac_set_promisc;
	mac_drv->रुको_fअगरo_clean = hns_gmac_रुको_fअगरo_clean;

	वापस (व्योम *)mac_drv;
पूर्ण
