<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x2.h"

व्योम mt76x2_mac_stop(काष्ठा mt76x02_dev *dev, bool क्रमce)
अणु
	bool stopped = false;
	u32 rts_cfg;
	पूर्णांक i;

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);
	mt76_clear(dev, MT_TXOP_HLDR_ET, MT_TXOP_HLDR_TX40M_BLK_EN);

	mt76_wr(dev, MT_MAC_SYS_CTRL, 0);

	rts_cfg = mt76_rr(dev, MT_TX_RTS_CFG);
	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg & ~MT_TX_RTS_CFG_RETRY_LIMIT);

	/* Wait क्रम MAC to become idle */
	क्रम (i = 0; i < 300; i++) अणु
		अगर ((mt76_rr(dev, MT_MAC_STATUS) &
		     (MT_MAC_STATUS_RX | MT_MAC_STATUS_TX)) ||
		    mt76_rr(dev, MT_BBP(IBI, 12))) अणु
			udelay(1);
			जारी;
		पूर्ण

		stopped = true;
		अवरोध;
	पूर्ण

	अगर (क्रमce && !stopped) अणु
		mt76_set(dev, MT_BBP(CORE, 4), BIT(1));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(1));

		mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
		mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));
	पूर्ण

	mt76_wr(dev, MT_TX_RTS_CFG, rts_cfg);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_mac_stop);
