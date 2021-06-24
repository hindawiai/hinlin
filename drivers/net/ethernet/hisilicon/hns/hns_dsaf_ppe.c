<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "hns_dsaf_ppe.h"

व्योम hns_ppe_set_tso_enable(काष्ठा hns_ppe_cb *ppe_cb, u32 value)
अणु
	dsaf_set_dev_bit(ppe_cb, PPEV2_CFG_TSO_EN_REG, 0, !!value);
पूर्ण

व्योम hns_ppe_set_rss_key(काष्ठा hns_ppe_cb *ppe_cb,
			 स्थिर u32 rss_key[HNS_PPEV2_RSS_KEY_NUM])
अणु
	u32 key_item;

	क्रम (key_item = 0; key_item < HNS_PPEV2_RSS_KEY_NUM; key_item++)
		dsaf_ग_लिखो_dev(ppe_cb, PPEV2_RSS_KEY_REG + key_item * 0x4,
			       rss_key[key_item]);
पूर्ण

व्योम hns_ppe_set_indir_table(काष्ठा hns_ppe_cb *ppe_cb,
			     स्थिर u32 rss_tab[HNS_PPEV2_RSS_IND_TBL_SIZE])
अणु
	पूर्णांक i;
	पूर्णांक reg_value;

	क्रम (i = 0; i < (HNS_PPEV2_RSS_IND_TBL_SIZE / 4); i++) अणु
		reg_value = dsaf_पढ़ो_dev(ppe_cb,
					  PPEV2_INDRECTION_TBL_REG + i * 0x4);

		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N0_M,
			       PPEV2_CFG_RSS_TBL_4N0_S,
			       rss_tab[i * 4 + 0] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N1_M,
			       PPEV2_CFG_RSS_TBL_4N1_S,
				rss_tab[i * 4 + 1] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N2_M,
			       PPEV2_CFG_RSS_TBL_4N2_S,
				rss_tab[i * 4 + 2] & 0x1F);
		dsaf_set_field(reg_value, PPEV2_CFG_RSS_TBL_4N3_M,
			       PPEV2_CFG_RSS_TBL_4N3_S,
				rss_tab[i * 4 + 3] & 0x1F);
		dsaf_ग_लिखो_dev(
			ppe_cb, PPEV2_INDRECTION_TBL_REG + i * 0x4, reg_value);
	पूर्ण
पूर्ण

अटल u8 __iomem *
hns_ppe_common_get_ioaddr(काष्ठा ppe_common_cb *ppe_common)
अणु
	वापस ppe_common->dsaf_dev->ppe_base + PPE_COMMON_REG_OFFSET;
पूर्ण

/**
 * hns_ppe_common_get_cfg - get ppe common config
 * @dsaf_dev: dasf device
 * @comm_index: common index
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_ppe_common_get_cfg(काष्ठा dsaf_device *dsaf_dev, पूर्णांक comm_index)
अणु
	काष्ठा ppe_common_cb *ppe_common;
	पूर्णांक ppe_num;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev))
		ppe_num = HNS_PPE_SERVICE_NW_ENGINE_NUM;
	अन्यथा
		ppe_num = HNS_PPE_DEBUG_NW_ENGINE_NUM;

	ppe_common = devm_kzalloc(dsaf_dev->dev,
				  काष्ठा_size(ppe_common, ppe_cb, ppe_num),
				  GFP_KERNEL);
	अगर (!ppe_common)
		वापस -ENOMEM;

	ppe_common->ppe_num = ppe_num;
	ppe_common->dsaf_dev = dsaf_dev;
	ppe_common->comm_index = comm_index;
	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev))
		ppe_common->ppe_mode = PPE_COMMON_MODE_SERVICE;
	अन्यथा
		ppe_common->ppe_mode = PPE_COMMON_MODE_DEBUG;
	ppe_common->dev = dsaf_dev->dev;

	ppe_common->io_base = hns_ppe_common_get_ioaddr(ppe_common);

	dsaf_dev->ppe_common[comm_index] = ppe_common;

	वापस 0;
पूर्ण

अटल व्योम
hns_ppe_common_मुक्त_cfg(काष्ठा dsaf_device *dsaf_dev, u32 comm_index)
अणु
	dsaf_dev->ppe_common[comm_index] = शून्य;
पूर्ण

अटल u8 __iomem *hns_ppe_get_iobase(काष्ठा ppe_common_cb *ppe_common,
				      पूर्णांक ppe_idx)
अणु
	वापस ppe_common->dsaf_dev->ppe_base + ppe_idx * PPE_REG_OFFSET;
पूर्ण

अटल व्योम hns_ppe_get_cfg(काष्ठा ppe_common_cb *ppe_common)
अणु
	u32 i;
	काष्ठा hns_ppe_cb *ppe_cb;
	u32 ppe_num = ppe_common->ppe_num;

	क्रम (i = 0; i < ppe_num; i++) अणु
		ppe_cb = &ppe_common->ppe_cb[i];
		ppe_cb->dev = ppe_common->dev;
		ppe_cb->next = शून्य;
		ppe_cb->ppe_common_cb = ppe_common;
		ppe_cb->index = i;
		ppe_cb->io_base = hns_ppe_get_iobase(ppe_common, i);
		ppe_cb->virq = 0;
	पूर्ण
पूर्ण

अटल व्योम hns_ppe_cnt_clr_ce(काष्ठा hns_ppe_cb *ppe_cb)
अणु
	dsaf_set_dev_bit(ppe_cb, PPE_TNL_0_5_CNT_CLR_CE_REG,
			 PPE_CNT_CLR_CE_B, 1);
पूर्ण

अटल व्योम hns_ppe_set_vlan_strip(काष्ठा hns_ppe_cb *ppe_cb, पूर्णांक en)
अणु
	dsaf_ग_लिखो_dev(ppe_cb, PPEV2_VLAN_STRIP_EN_REG, en);
पूर्ण

/**
 * hns_ppe_checksum_hw - set ppe checksum caculate
 * @ppe_cb: ppe device
 * @value: value
 */
अटल व्योम hns_ppe_checksum_hw(काष्ठा hns_ppe_cb *ppe_cb, u32 value)
अणु
	dsaf_set_dev_field(ppe_cb, PPE_CFG_PRO_CHECK_EN_REG,
			   0xfffffff, 0, value);
पूर्ण

अटल व्योम hns_ppe_set_qid_mode(काष्ठा ppe_common_cb *ppe_common,
				 क्रमागत ppe_qid_mode qid_mकरोe)
अणु
	dsaf_set_dev_field(ppe_common, PPE_COM_CFG_QID_MODE_REG,
			   PPE_CFG_QID_MODE_CF_QID_MODE_M,
			   PPE_CFG_QID_MODE_CF_QID_MODE_S, qid_mकरोe);
पूर्ण

/**
 * hns_ppe_set_qid - set ppe qid
 * @ppe_common: ppe common device
 * @qid: queue id
 */
अटल व्योम hns_ppe_set_qid(काष्ठा ppe_common_cb *ppe_common, u32 qid)
अणु
	u32 qid_mod = dsaf_पढ़ो_dev(ppe_common, PPE_COM_CFG_QID_MODE_REG);

	अगर (!dsaf_get_field(qid_mod, PPE_CFG_QID_MODE_DEF_QID_M,
			    PPE_CFG_QID_MODE_DEF_QID_S)) अणु
		dsaf_set_field(qid_mod, PPE_CFG_QID_MODE_DEF_QID_M,
			       PPE_CFG_QID_MODE_DEF_QID_S, qid);
		dsaf_ग_लिखो_dev(ppe_common, PPE_COM_CFG_QID_MODE_REG, qid_mod);
	पूर्ण
पूर्ण

/**
 * hns_ppe_set_port_mode - set port mode
 * @ppe_cb: ppe device
 * @mode: port mode
 */
अटल व्योम hns_ppe_set_port_mode(काष्ठा hns_ppe_cb *ppe_cb,
				  क्रमागत ppe_port_mode mode)
अणु
	dsaf_ग_लिखो_dev(ppe_cb, PPE_CFG_XGE_MODE_REG, mode);
पूर्ण

/**
 * hns_ppe_common_init_hw - init ppe common device
 * @ppe_common: ppe common device
 *
 * Return 0 on success, negative on failure
 */
अटल पूर्णांक hns_ppe_common_init_hw(काष्ठा ppe_common_cb *ppe_common)
अणु
	क्रमागत ppe_qid_mode qid_mode;
	काष्ठा dsaf_device *dsaf_dev = ppe_common->dsaf_dev;
	क्रमागत dsaf_mode dsaf_mode = dsaf_dev->dsaf_mode;

	dsaf_dev->misc_op->ppe_comm_srst(dsaf_dev, 0);
	msleep(100);
	dsaf_dev->misc_op->ppe_comm_srst(dsaf_dev, 1);
	msleep(100);

	अगर (ppe_common->ppe_mode == PPE_COMMON_MODE_SERVICE) अणु
		चयन (dsaf_mode) अणु
		हाल DSAF_MODE_ENABLE_FIX:
		हाल DSAF_MODE_DISABLE_FIX:
			qid_mode = PPE_QID_MODE0;
			hns_ppe_set_qid(ppe_common, 0);
			अवरोध;
		हाल DSAF_MODE_ENABLE_0VM:
		हाल DSAF_MODE_DISABLE_2PORT_64VM:
			qid_mode = PPE_QID_MODE3;
			अवरोध;
		हाल DSAF_MODE_ENABLE_8VM:
		हाल DSAF_MODE_DISABLE_2PORT_16VM:
			qid_mode = PPE_QID_MODE4;
			अवरोध;
		हाल DSAF_MODE_ENABLE_16VM:
		हाल DSAF_MODE_DISABLE_6PORT_0VM:
			qid_mode = PPE_QID_MODE5;
			अवरोध;
		हाल DSAF_MODE_ENABLE_32VM:
		हाल DSAF_MODE_DISABLE_6PORT_16VM:
			qid_mode = PPE_QID_MODE2;
			अवरोध;
		हाल DSAF_MODE_ENABLE_128VM:
		हाल DSAF_MODE_DISABLE_6PORT_4VM:
			qid_mode = PPE_QID_MODE1;
			अवरोध;
		हाल DSAF_MODE_DISABLE_2PORT_8VM:
			qid_mode = PPE_QID_MODE7;
			अवरोध;
		हाल DSAF_MODE_DISABLE_6PORT_2VM:
			qid_mode = PPE_QID_MODE6;
			अवरोध;
		शेष:
			dev_err(ppe_common->dev,
				"get ppe queue mode failed! dsaf_mode=%d\n",
				dsaf_mode);
			वापस -EINVAL;
		पूर्ण
		hns_ppe_set_qid_mode(ppe_common, qid_mode);
	पूर्ण

	dsaf_set_dev_bit(ppe_common, PPE_COM_COMMON_CNT_CLR_CE_REG,
			 PPE_COMMON_CNT_CLR_CE_B, 1);

	वापस 0;
पूर्ण

/*clr ppe exception irq*/
अटल व्योम hns_ppe_exc_irq_en(काष्ठा hns_ppe_cb *ppe_cb, पूर्णांक en)
अणु
	u32 clr_vlue = 0xfffffffful;
	u32 msk_vlue = en ? 0xfffffffful : 0; /*1 is en, 0 is dis*/
	u32 vld_msk = 0;

	/*only care bit 0,1,7*/
	dsaf_set_bit(vld_msk, 0, 1);
	dsaf_set_bit(vld_msk, 1, 1);
	dsaf_set_bit(vld_msk, 7, 1);

	/*clr sts**/
	dsaf_ग_लिखो_dev(ppe_cb, PPE_RINT_REG, clr_vlue);

	/*क्रम some reserved bits, so set 0**/
	dsaf_ग_लिखो_dev(ppe_cb, PPE_INTEN_REG, msk_vlue & vld_msk);
पूर्ण

पूर्णांक hns_ppe_रुको_tx_fअगरo_clean(काष्ठा hns_ppe_cb *ppe_cb)
अणु
	पूर्णांक रुको_cnt;
	u32 val;

	रुको_cnt = 0;
	जबतक (रुको_cnt++ < HNS_MAX_WAIT_CNT) अणु
		val = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_TX_FIFO0_REG) & 0x3ffU;
		अगर (!val)
			अवरोध;

		usleep_range(100, 200);
	पूर्ण

	अगर (रुको_cnt >= HNS_MAX_WAIT_CNT) अणु
		dev_err(ppe_cb->dev, "hns ppe tx fifo clean wait timeout, still has %u pkt.\n",
			val);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ppe_init_hw - init ppe
 * @ppe_cb: ppe device
 */
अटल व्योम hns_ppe_init_hw(काष्ठा hns_ppe_cb *ppe_cb)
अणु
	काष्ठा ppe_common_cb *ppe_common_cb = ppe_cb->ppe_common_cb;
	u32 port = ppe_cb->index;
	काष्ठा dsaf_device *dsaf_dev = ppe_common_cb->dsaf_dev;
	पूर्णांक i;

	/* get शेष RSS key */
	netdev_rss_key_fill(ppe_cb->rss_key, HNS_PPEV2_RSS_KEY_SIZE);

	dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 0);
	mdelay(10);
	dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 1);

	/* clr and msk except irq*/
	hns_ppe_exc_irq_en(ppe_cb, 0);

	अगर (ppe_common_cb->ppe_mode == PPE_COMMON_MODE_DEBUG) अणु
		hns_ppe_set_port_mode(ppe_cb, PPE_MODE_GE);
		dsaf_ग_लिखो_dev(ppe_cb, PPE_CFG_PAUSE_IDLE_CNT_REG, 0);
	पूर्ण अन्यथा अणु
		hns_ppe_set_port_mode(ppe_cb, PPE_MODE_XGE);
	पूर्ण

	hns_ppe_checksum_hw(ppe_cb, 0xffffffff);
	hns_ppe_cnt_clr_ce(ppe_cb);

	अगर (!AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		hns_ppe_set_vlan_strip(ppe_cb, 0);

		dsaf_ग_लिखो_dev(ppe_cb, PPE_CFG_MAX_FRAME_LEN_REG,
			       HNS_PPEV2_MAX_FRAME_LEN);

		/* set शेष RSS key in h/w */
		hns_ppe_set_rss_key(ppe_cb, ppe_cb->rss_key);

		/* Set शेष indrection table in h/w */
		क्रम (i = 0; i < HNS_PPEV2_RSS_IND_TBL_SIZE; i++)
			ppe_cb->rss_indir_table[i] = i;
		hns_ppe_set_indir_table(ppe_cb, ppe_cb->rss_indir_table);
	पूर्ण
पूर्ण

/**
 * ppe_uninit_hw - uninit ppe
 * @ppe_cb: ppe device
 */
अटल व्योम hns_ppe_uninit_hw(काष्ठा hns_ppe_cb *ppe_cb)
अणु
	u32 port;

	अगर (ppe_cb->ppe_common_cb) अणु
		काष्ठा dsaf_device *dsaf_dev = ppe_cb->ppe_common_cb->dsaf_dev;

		port = ppe_cb->index;
		dsaf_dev->misc_op->ppe_srst(dsaf_dev, port, 0);
	पूर्ण
पूर्ण

अटल व्योम hns_ppe_uninit_ex(काष्ठा ppe_common_cb *ppe_common)
अणु
	u32 i;

	क्रम (i = 0; i < ppe_common->ppe_num; i++) अणु
		अगर (ppe_common->dsaf_dev->mac_cb[i])
			hns_ppe_uninit_hw(&ppe_common->ppe_cb[i]);
		स_रखो(&ppe_common->ppe_cb[i], 0, माप(काष्ठा hns_ppe_cb));
	पूर्ण
पूर्ण

व्योम hns_ppe_uninit(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 i;

	क्रम (i = 0; i < HNS_PPE_COM_NUM; i++) अणु
		अगर (dsaf_dev->ppe_common[i])
			hns_ppe_uninit_ex(dsaf_dev->ppe_common[i]);
		hns_rcb_common_मुक्त_cfg(dsaf_dev, i);
		hns_ppe_common_मुक्त_cfg(dsaf_dev, i);
	पूर्ण
पूर्ण

/**
 * hns_ppe_reset - reinit ppe/rcb hw
 * @dsaf_dev: dasf device
 * @ppe_common_index: the index
 * वापस व्योम
 */
व्योम hns_ppe_reset_common(काष्ठा dsaf_device *dsaf_dev, u8 ppe_common_index)
अणु
	u32 i;
	पूर्णांक ret;
	काष्ठा ppe_common_cb *ppe_common;

	ppe_common = dsaf_dev->ppe_common[ppe_common_index];
	ret = hns_ppe_common_init_hw(ppe_common);
	अगर (ret)
		वापस;

	क्रम (i = 0; i < ppe_common->ppe_num; i++) अणु
		/* We only need to initiate ppe when the port exists */
		अगर (dsaf_dev->mac_cb[i])
			hns_ppe_init_hw(&ppe_common->ppe_cb[i]);
	पूर्ण

	ret = hns_rcb_common_init_hw(dsaf_dev->rcb_common[ppe_common_index]);
	अगर (ret)
		वापस;

	hns_rcb_common_init_commit_hw(dsaf_dev->rcb_common[ppe_common_index]);
पूर्ण

व्योम hns_ppe_update_stats(काष्ठा hns_ppe_cb *ppe_cb)
अणु
	काष्ठा hns_ppe_hw_stats *hw_stats = &ppe_cb->hw_stats;

	hw_stats->rx_pkts_from_sw
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_SW_PKT_CNT_REG);
	hw_stats->rx_pkts
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_WR_BD_OK_PKT_CNT_REG);
	hw_stats->rx_drop_no_bd
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_NO_BUF_CNT_REG);
	hw_stats->rx_alloc_buf_fail
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_APP_BUF_FAIL_CNT_REG);
	hw_stats->rx_alloc_buf_रुको
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_APP_BUF_WAIT_CNT_REG);
	hw_stats->rx_drop_no_buf
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_DROP_FUL_CNT_REG);
	hw_stats->rx_err_fअगरo_full
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_DROP_PRT_CNT_REG);

	hw_stats->tx_bd_क्रमm_rcb
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_BD_CNT_REG);
	hw_stats->tx_pkts_from_rcb
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_CNT_REG);
	hw_stats->tx_pkts
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_OK_CNT_REG);
	hw_stats->tx_err_fअगरo_empty
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_EPT_CNT_REG);
	hw_stats->tx_err_checksum
		+= dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_CS_FAIL_CNT_REG);
पूर्ण

पूर्णांक hns_ppe_get_sset_count(पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS)
		वापस ETH_PPE_STATIC_NUM;
	वापस 0;
पूर्ण

पूर्णांक hns_ppe_get_regs_count(व्योम)
अणु
	वापस ETH_PPE_DUMP_NUM;
पूर्ण

/**
 * ppe_get_strings - get ppe srting
 * @ppe_cb: ppe device
 * @stringset: string set type
 * @data: output string
 */
व्योम hns_ppe_get_strings(काष्ठा hns_ppe_cb *ppe_cb, पूर्णांक stringset, u8 *data)
अणु
	पूर्णांक index = ppe_cb->index;
	u8 *buff = data;

	ethtool_प्र_लिखो(&buff, "ppe%d_rx_sw_pkt", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_pkt_ok", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_drop_pkt_no_bd", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_alloc_buf_fail", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_alloc_buf_wait", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_pkt_drop_no_buf", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_rx_pkt_err_fifo_full", index);

	ethtool_प्र_लिखो(&buff, "ppe%d_tx_bd", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_tx_pkt", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_tx_pkt_ok", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_tx_pkt_err_fifo_empty", index);
	ethtool_प्र_लिखो(&buff, "ppe%d_tx_pkt_err_csum_fail", index);
पूर्ण

व्योम hns_ppe_get_stats(काष्ठा hns_ppe_cb *ppe_cb, u64 *data)
अणु
	u64 *regs_buff = data;
	काष्ठा hns_ppe_hw_stats *hw_stats = &ppe_cb->hw_stats;

	regs_buff[0] = hw_stats->rx_pkts_from_sw;
	regs_buff[1] = hw_stats->rx_pkts;
	regs_buff[2] = hw_stats->rx_drop_no_bd;
	regs_buff[3] = hw_stats->rx_alloc_buf_fail;
	regs_buff[4] = hw_stats->rx_alloc_buf_रुको;
	regs_buff[5] = hw_stats->rx_drop_no_buf;
	regs_buff[6] = hw_stats->rx_err_fअगरo_full;

	regs_buff[7] = hw_stats->tx_bd_क्रमm_rcb;
	regs_buff[8] = hw_stats->tx_pkts_from_rcb;
	regs_buff[9] = hw_stats->tx_pkts;
	regs_buff[10] = hw_stats->tx_err_fअगरo_empty;
	regs_buff[11] = hw_stats->tx_err_checksum;
पूर्ण

/**
 * hns_ppe_init - init ppe device
 * @dsaf_dev: dasf device
 * वापस 0 - success , negative --fail
 */
पूर्णांक hns_ppe_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < HNS_PPE_COM_NUM; i++) अणु
		ret = hns_ppe_common_get_cfg(dsaf_dev, i);
		अगर (ret)
			जाओ get_cfg_fail;

		ret = hns_rcb_common_get_cfg(dsaf_dev, i);
		अगर (ret)
			जाओ get_cfg_fail;

		hns_ppe_get_cfg(dsaf_dev->ppe_common[i]);

		ret = hns_rcb_get_cfg(dsaf_dev->rcb_common[i]);
		अगर (ret)
			जाओ get_cfg_fail;
	पूर्ण

	क्रम (i = 0; i < HNS_PPE_COM_NUM; i++)
		hns_ppe_reset_common(dsaf_dev, i);

	वापस 0;

get_cfg_fail:
	क्रम (i = 0; i < HNS_PPE_COM_NUM; i++) अणु
		hns_rcb_common_मुक्त_cfg(dsaf_dev, i);
		hns_ppe_common_मुक्त_cfg(dsaf_dev, i);
	पूर्ण

	वापस ret;
पूर्ण

व्योम hns_ppe_get_regs(काष्ठा hns_ppe_cb *ppe_cb, व्योम *data)
अणु
	काष्ठा ppe_common_cb *ppe_common = ppe_cb->ppe_common_cb;
	u32 *regs = data;
	u32 i;
	u32 offset;

	/* ppe common रेजिस्टरs */
	regs[0] = dsaf_पढ़ो_dev(ppe_common, PPE_COM_CFG_QID_MODE_REG);
	regs[1] = dsaf_पढ़ो_dev(ppe_common, PPE_COM_INTEN_REG);
	regs[2] = dsaf_पढ़ो_dev(ppe_common, PPE_COM_RINT_REG);
	regs[3] = dsaf_पढ़ो_dev(ppe_common, PPE_COM_INTSTS_REG);
	regs[4] = dsaf_पढ़ो_dev(ppe_common, PPE_COM_COMMON_CNT_CLR_CE_REG);

	क्रम (i = 0; i < DSAF_TOTAL_QUEUE_NUM; i++) अणु
		offset = PPE_COM_HIS_RX_PKT_QID_DROP_CNT_REG + 0x4 * i;
		regs[5 + i] = dsaf_पढ़ो_dev(ppe_common, offset);
		offset = PPE_COM_HIS_RX_PKT_QID_OK_CNT_REG + 0x4 * i;
		regs[5 + i + DSAF_TOTAL_QUEUE_NUM]
				= dsaf_पढ़ो_dev(ppe_common, offset);
		offset = PPE_COM_HIS_TX_PKT_QID_ERR_CNT_REG + 0x4 * i;
		regs[5 + i + DSAF_TOTAL_QUEUE_NUM * 2]
				= dsaf_पढ़ो_dev(ppe_common, offset);
		offset = PPE_COM_HIS_TX_PKT_QID_OK_CNT_REG + 0x4 * i;
		regs[5 + i + DSAF_TOTAL_QUEUE_NUM * 3]
				= dsaf_पढ़ो_dev(ppe_common, offset);
	पूर्ण

	/* mark end of ppe regs */
	क्रम (i = 521; i < 524; i++)
		regs[i] = 0xeeeeeeee;

	/* ppe channel रेजिस्टरs */
	regs[525] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_TX_FIFO_THRSLD_REG);
	regs[526] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_FIFO_THRSLD_REG);
	regs[527] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_FIFO_PAUSE_THRSLD_REG);
	regs[528] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_FIFO_SW_BP_THRSLD_REG);
	regs[529] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_PAUSE_IDLE_CNT_REG);
	regs[530] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_BUS_CTRL_REG);
	regs[531] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_TNL_TO_BE_RST_REG);
	regs[532] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_TNL_CAN_RST_REG);

	regs[533] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_XGE_MODE_REG);
	regs[534] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_MAX_FRAME_LEN_REG);
	regs[535] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_PKT_MODE_REG);
	regs[536] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_VLAN_TAG_REG);
	regs[537] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_TAG_GEN_REG);
	regs[538] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_PARSE_TAG_REG);
	regs[539] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_PRO_CHECK_EN_REG);

	regs[540] = dsaf_पढ़ो_dev(ppe_cb, PPE_INTEN_REG);
	regs[541] = dsaf_पढ़ो_dev(ppe_cb, PPE_RINT_REG);
	regs[542] = dsaf_पढ़ो_dev(ppe_cb, PPE_INTSTS_REG);
	regs[543] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_RX_PKT_INT_REG);

	regs[544] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_HEAT_DECT_TIME0_REG);
	regs[545] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_HEAT_DECT_TIME1_REG);

	/* ppe अटल */
	regs[546] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_SW_PKT_CNT_REG);
	regs[547] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_WR_BD_OK_PKT_CNT_REG);
	regs[548] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_NO_BUF_CNT_REG);
	regs[549] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_BD_CNT_REG);
	regs[550] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_CNT_REG);
	regs[551] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_OK_CNT_REG);
	regs[552] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_EPT_CNT_REG);
	regs[553] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TX_PKT_CS_FAIL_CNT_REG);
	regs[554] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_APP_BUF_FAIL_CNT_REG);
	regs[555] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_APP_BUF_WAIT_CNT_REG);
	regs[556] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_DROP_FUL_CNT_REG);
	regs[557] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_RX_PKT_DROP_PRT_CNT_REG);

	regs[558] = dsaf_पढ़ो_dev(ppe_cb, PPE_TNL_0_5_CNT_CLR_CE_REG);
	regs[559] = dsaf_पढ़ो_dev(ppe_cb, PPE_CFG_AXI_DBG_REG);
	regs[560] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_PRO_ERR_REG);
	regs[561] = dsaf_पढ़ो_dev(ppe_cb, PPE_HIS_TNL_FIFO_ERR_REG);
	regs[562] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_CFF_DATA_NUM_REG);
	regs[563] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_RX_ST_REG);
	regs[564] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_TX_ST_REG);
	regs[565] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_RX_FIFO0_REG);
	regs[566] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_RX_FIFO1_REG);
	regs[567] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_TX_FIFO0_REG);
	regs[568] = dsaf_पढ़ो_dev(ppe_cb, PPE_CURR_TX_FIFO1_REG);
	regs[569] = dsaf_पढ़ो_dev(ppe_cb, PPE_ECO0_REG);
	regs[570] = dsaf_पढ़ो_dev(ppe_cb, PPE_ECO1_REG);
	regs[571] = dsaf_पढ़ो_dev(ppe_cb, PPE_ECO2_REG);

	/* mark end of ppe regs */
	क्रम (i = 572; i < 576; i++)
		regs[i] = 0xeeeeeeee;
पूर्ण
