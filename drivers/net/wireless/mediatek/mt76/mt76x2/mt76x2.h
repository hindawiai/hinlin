<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर_अघोषित __MT76x2_H
#घोषणा __MT76x2_H

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/bitops.h>

#घोषणा MT7662_FIRMWARE		"mt7662.bin"
#घोषणा MT7662_ROM_PATCH	"mt7662_rom_patch.bin"
#घोषणा MT7662_EEPROM_SIZE	512

#समावेश "../mt76x02.h"
#समावेश "mac.h"

अटल अंतरभूत bool is_mt7612(काष्ठा mt76x02_dev *dev)
अणु
	वापस mt76_chip(&dev->mt76) == 0x7612;
पूर्ण

अटल अंतरभूत bool mt76x2_channel_silent(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;

	वापस ((chan->flags & IEEE80211_CHAN_RADAR) &&
		chan->dfs_state != NL80211_DFS_AVAILABLE);
पूर्ण

बाह्य स्थिर काष्ठा ieee80211_ops mt76x2_ops;

पूर्णांक mt76x2_रेजिस्टर_device(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_resume_device(काष्ठा mt76x02_dev *dev);

व्योम mt76x2_phy_घातer_on(काष्ठा mt76x02_dev *dev);
व्योम mt76x2_stop_hardware(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_eeprom_init(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_apply_calibration_data(काष्ठा mt76x02_dev *dev, पूर्णांक channel);

व्योम mt76x2_phy_set_antenna(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_phy_start(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_phy_set_channel(काष्ठा mt76x02_dev *dev,
			   काष्ठा cfg80211_chan_def *chandef);
व्योम mt76x2_phy_calibrate(काष्ठा work_काष्ठा *work);
व्योम mt76x2_phy_set_txघातer(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x2_mcu_init(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2_mcu_set_channel(काष्ठा mt76x02_dev *dev, u8 channel, u8 bw,
			   u8 bw_index, bool scan);
पूर्णांक mt76x2_mcu_load_cr(काष्ठा mt76x02_dev *dev, u8 type, u8 temp_level,
		       u8 channel);

व्योम mt76x2_cleanup(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x2_mac_reset(काष्ठा mt76x02_dev *dev, bool hard);
व्योम mt76x2_reset_wlan(काष्ठा mt76x02_dev *dev, bool enable);
व्योम mt76x2_init_txघातer(काष्ठा mt76x02_dev *dev,
			 काष्ठा ieee80211_supported_band *sband);
व्योम mt76_ग_लिखो_mac_initvals(काष्ठा mt76x02_dev *dev);

व्योम mt76x2_phy_tssi_compensate(काष्ठा mt76x02_dev *dev);
व्योम mt76x2_phy_set_txघातer_regs(काष्ठा mt76x02_dev *dev,
				 क्रमागत nl80211_band band);
व्योम mt76x2_configure_tx_delay(काष्ठा mt76x02_dev *dev,
			       क्रमागत nl80211_band band, u8 bw);
व्योम mt76x2_apply_gain_adj(काष्ठा mt76x02_dev *dev);
व्योम mt76x2_phy_update_channel_gain(काष्ठा mt76x02_dev *dev);

#पूर्ण_अगर
