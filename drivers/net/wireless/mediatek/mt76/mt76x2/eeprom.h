<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर_अघोषित __MT76x2_EEPROM_H
#घोषणा __MT76x2_EEPROM_H

#समावेश "../mt76x02_eeprom.h"

क्रमागत mt76x2_cal_channel_group अणु
	MT_CH_5G_JAPAN,
	MT_CH_5G_UNII_1,
	MT_CH_5G_UNII_2,
	MT_CH_5G_UNII_2E_1,
	MT_CH_5G_UNII_2E_2,
	MT_CH_5G_UNII_3,
	__MT_CH_MAX
पूर्ण;

काष्ठा mt76x2_tx_घातer_info अणु
	u8 target_घातer;

	s8 delta_bw40;
	s8 delta_bw80;

	काष्ठा अणु
		s8 tssi_slope;
		s8 tssi_offset;
		s8 target_घातer;
		s8 delta;
	पूर्ण chain[MT_MAX_CHAINS];
पूर्ण;

काष्ठा mt76x2_temp_comp अणु
	u8 temp_25_ref;
	पूर्णांक lower_bound; /* J */
	पूर्णांक upper_bound; /* J */
	अचिन्हित पूर्णांक high_slope; /* J / dB */
	अचिन्हित पूर्णांक low_slope; /* J / dB */
पूर्ण;

व्योम mt76x2_get_rate_घातer(काष्ठा mt76x02_dev *dev, काष्ठा mt76_rate_घातer *t,
			   काष्ठा ieee80211_channel *chan);
व्योम mt76x2_get_घातer_info(काष्ठा mt76x02_dev *dev,
			   काष्ठा mt76x2_tx_घातer_info *t,
			   काष्ठा ieee80211_channel *chan);
पूर्णांक mt76x2_get_temp_comp(काष्ठा mt76x02_dev *dev, काष्ठा mt76x2_temp_comp *t);
व्योम mt76x2_पढ़ो_rx_gain(काष्ठा mt76x02_dev *dev);

अटल अंतरभूत bool
mt76x2_has_ext_lna(काष्ठा mt76x02_dev *dev)
अणु
	u32 val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1);

	अगर (dev->mphy.chandef.chan->band == NL80211_BAND_2GHZ)
		वापस val & MT_EE_NIC_CONF_1_LNA_EXT_2G;
	अन्यथा
		वापस val & MT_EE_NIC_CONF_1_LNA_EXT_5G;
पूर्ण

अटल अंतरभूत bool
mt76x2_temp_tx_alc_enabled(काष्ठा mt76x02_dev *dev)
अणु
	u16 val;

	val = mt76x02_eeprom_get(dev, MT_EE_TX_POWER_EXT_PA_5G);
	अगर (!(val & BIT(15)))
		वापस false;

	वापस mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) &
	       MT_EE_NIC_CONF_1_TEMP_TX_ALC;
पूर्ण

अटल अंतरभूत bool
mt76x2_tssi_enabled(काष्ठा mt76x02_dev *dev)
अणु
	वापस !mt76x2_temp_tx_alc_enabled(dev) &&
	       (mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) &
		MT_EE_NIC_CONF_1_TX_ALC_EN);
पूर्ण

#पूर्ण_अगर
