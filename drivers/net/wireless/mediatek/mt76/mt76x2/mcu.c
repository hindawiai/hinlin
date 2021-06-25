<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>

#समावेश "mt76x2.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"

पूर्णांक mt76x2_mcu_set_channel(काष्ठा mt76x02_dev *dev, u8 channel, u8 bw,
			   u8 bw_index, bool scan)
अणु
	काष्ठा अणु
		u8 idx;
		u8 scan;
		u8 bw;
		u8 _pad0;

		__le16 chainmask;
		u8 ext_chan;
		u8 _pad1;

	पूर्ण __packed __aligned(4) msg = अणु
		.idx = channel,
		.scan = scan,
		.bw = bw,
		.chainmask = cpu_to_le16(dev->mphy.chainmask),
	पूर्ण;

	/* first set the channel without the extension channel info */
	mt76_mcu_send_msg(&dev->mt76, CMD_SWITCH_CHANNEL_OP, &msg,
			  माप(msg), true);

	usleep_range(5000, 10000);

	msg.ext_chan = 0xe0 + bw_index;
	वापस mt76_mcu_send_msg(&dev->mt76, CMD_SWITCH_CHANNEL_OP, &msg,
				 माप(msg), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_mcu_set_channel);

पूर्णांक mt76x2_mcu_load_cr(काष्ठा mt76x02_dev *dev, u8 type, u8 temp_level,
		       u8 channel)
अणु
	काष्ठा अणु
		u8 cr_mode;
		u8 temp;
		u8 ch;
		u8 _pad0;

		__le32 cfg;
	पूर्ण __packed __aligned(4) msg = अणु
		.cr_mode = type,
		.temp = temp_level,
		.ch = channel,
	पूर्ण;
	u32 val;

	val = BIT(31);
	val |= (mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_0) >> 8) & 0x00ff;
	val |= (mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_1) << 8) & 0xff00;
	msg.cfg = cpu_to_le32(val);

	/* first set the channel without the extension channel info */
	वापस mt76_mcu_send_msg(&dev->mt76, CMD_LOAD_CR, &msg, माप(msg),
				 true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_mcu_load_cr);

पूर्णांक mt76x2_mcu_init_gain(काष्ठा mt76x02_dev *dev, u8 channel, u32 gain,
			 bool क्रमce)
अणु
	काष्ठा अणु
		__le32 channel;
		__le32 gain_val;
	पूर्ण __packed __aligned(4) msg = अणु
		.channel = cpu_to_le32(channel),
		.gain_val = cpu_to_le32(gain),
	पूर्ण;

	अगर (क्रमce)
		msg.channel |= cpu_to_le32(BIT(31));

	वापस mt76_mcu_send_msg(&dev->mt76, CMD_INIT_GAIN_OP, &msg,
				 माप(msg), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_mcu_init_gain);

पूर्णांक mt76x2_mcu_tssi_comp(काष्ठा mt76x02_dev *dev,
			 काष्ठा mt76x2_tssi_comp *tssi_data)
अणु
	काष्ठा अणु
		__le32 id;
		काष्ठा mt76x2_tssi_comp data;
	पूर्ण __packed __aligned(4) msg = अणु
		.id = cpu_to_le32(MCU_CAL_TSSI_COMP),
		.data = *tssi_data,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, CMD_CALIBRATION_OP, &msg,
				 माप(msg), true);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_mcu_tssi_comp);
