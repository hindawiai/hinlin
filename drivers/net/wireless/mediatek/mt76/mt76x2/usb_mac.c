<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x2u.h"
#समावेश "eeprom.h"

अटल व्योम mt76x2u_mac_fixup_xtal(काष्ठा mt76x02_dev *dev)
अणु
	s8 offset = 0;
	u16 eep_val;

	eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_2);

	offset = eep_val & 0x7f;
	अगर ((eep_val & 0xff) == 0xff)
		offset = 0;
	अन्यथा अगर (eep_val & 0x80)
		offset = 0 - offset;

	eep_val >>= 8;
	अगर (eep_val == 0x00 || eep_val == 0xff) अणु
		eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_1);
		eep_val &= 0xff;

		अगर (eep_val == 0x00 || eep_val == 0xff)
			eep_val = 0x14;
	पूर्ण

	eep_val &= 0x7f;
	mt76_rmw_field(dev, MT_VEND_ADDR(CFG, MT_XO_CTRL5),
		       MT_XO_CTRL5_C2_VAL, eep_val + offset);
	mt76_set(dev, MT_VEND_ADDR(CFG, MT_XO_CTRL6), MT_XO_CTRL6_C2_CTRL);

	mt76_wr(dev, 0x504, 0x06000000);
	mt76_wr(dev, 0x50c, 0x08800000);
	mdelay(5);
	mt76_wr(dev, 0x504, 0x0);

	/* decrease SIFS from 16us to 13us */
	mt76_rmw_field(dev, MT_XIFS_TIME_CFG,
		       MT_XIFS_TIME_CFG_OFDM_SIFS, 0xd);
	mt76_rmw_field(dev, MT_BKOFF_SLOT_CFG, MT_BKOFF_SLOT_CFG_CC_DELAY, 1);

	/* init fce */
	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	eep_val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	चयन (FIELD_GET(MT_EE_NIC_CONF_2_XTAL_OPTION, eep_val)) अणु
	हाल 0:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1fee80);
		अवरोध;
	हाल 1:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1feed0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mt76x2u_mac_reset(काष्ठा mt76x02_dev *dev)
अणु
	mt76_wr(dev, MT_WPDMA_GLO_CFG, BIT(4) | BIT(5));

	/* init pbf regs */
	mt76_wr(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_wr(dev, MT_PBF_RX_MAX_PCNT, 0xfebf);

	mt76_ग_लिखो_mac_initvals(dev);

	mt76_wr(dev, MT_TX_LINK_CFG, 0x1020);
	mt76_wr(dev, MT_AUTO_RSP_CFG, 0x13);
	mt76_wr(dev, MT_MAX_LEN_CFG, 0x2f00);

	mt76_wr(dev, MT_WMM_AIFSN, 0x2273);
	mt76_wr(dev, MT_WMM_CWMIN, 0x2344);
	mt76_wr(dev, MT_WMM_CWMAX, 0x34aa);

	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_RESET_CSR |
		   MT_MAC_SYS_CTRL_RESET_BBP);

	अगर (is_mt7612(dev))
		mt76_clear(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0xf000);
	mt76_clear(dev, MT_TX_ALC_CFG_4, BIT(31));

	mt76x2u_mac_fixup_xtal(dev);

	वापस 0;
पूर्ण

पूर्णांक mt76x2u_mac_stop(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i, count = 0, val;
	bool stopped = false;
	u32 rts_cfg;

	अगर (test_bit(MT76_REMOVED, &dev->mphy.state))
		वापस -EIO;

	rts_cfg = mt76_rr(dev, MT_TX_RTS_CFG);
	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg & ~MT_TX_RTS_CFG_RETRY_LIMIT);

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_clear(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);

	/* रुको tx dma to stop */
	क्रम (i = 0; i < 2000; i++) अणु
		val = mt76_rr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG));
		अगर (!(val & MT_USB_DMA_CFG_TX_BUSY) && i > 10)
			अवरोध;
		usleep_range(50, 100);
	पूर्ण

	/* page count on TxQ */
	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(mt76_rr(dev, 0x0438) & 0xffffffff) &&
		    !(mt76_rr(dev, 0x0a30) & 0x000000ff) &&
		    !(mt76_rr(dev, 0x0a34) & 0xff00ff00))
			अवरोध;
		usleep_range(10, 20);
	पूर्ण

	/* disable tx-rx */
	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_ENABLE_RX |
		   MT_MAC_SYS_CTRL_ENABLE_TX);

	/* Wait क्रम MAC to become idle */
	क्रम (i = 0; i < 1000; i++) अणु
		अगर (!(mt76_rr(dev, MT_MAC_STATUS) & MT_MAC_STATUS_TX) &&
		    !mt76_rr(dev, MT_BBP(IBI, 12))) अणु
			stopped = true;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण

	अगर (!stopped) अणु
		mt76_set(dev, MT_BBP(CORE, 4), BIT(1));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(1));

		mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));
	पूर्ण

	/* page count on RxQ */
	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(mt76_rr(dev, 0x0430) & 0x00ff0000) &&
		    !(mt76_rr(dev, 0x0a30) & 0xffffffff) &&
		    !(mt76_rr(dev, 0x0a34) & 0xffffffff) &&
		    ++count > 10)
			अवरोध;
		msleep(50);
	पूर्ण

	अगर (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_RX, 0, 2000))
		dev_warn(dev->mt76.dev, "MAC RX failed to stop\n");

	/* रुको rx dma to stop */
	क्रम (i = 0; i < 2000; i++) अणु
		val = mt76_rr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG));
		अगर (!(val & MT_USB_DMA_CFG_RX_BUSY) && i > 10)
			अवरोध;
		usleep_range(50, 100);
	पूर्ण

	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg);

	वापस 0;
पूर्ण
