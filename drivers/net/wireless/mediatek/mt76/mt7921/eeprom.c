<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7921.h"
#समावेश "eeprom.h"

अटल u32 mt7921_eeprom_पढ़ो(काष्ठा mt7921_dev *dev, u32 offset)
अणु
	u8 *data = dev->mt76.eeprom.data;

	अगर (data[offset] == 0xff)
		mt7921_mcu_get_eeprom(dev, offset);

	वापस data[offset];
पूर्ण

अटल पूर्णांक mt7921_eeprom_load(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7921_EEPROM_SIZE);
	अगर (ret < 0)
		वापस ret;

	स_रखो(dev->mt76.eeprom.data, -1, MT7921_EEPROM_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7921_check_eeprom(काष्ठा mt7921_dev *dev)
अणु
	u8 *eeprom = dev->mt76.eeprom.data;
	u16 val;

	mt7921_eeprom_पढ़ो(dev, MT_EE_CHIP_ID);
	val = get_unaligned_le16(eeprom);

	चयन (val) अणु
	हाल 0x7961:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

व्योम mt7921_eeprom_parse_band_config(काष्ठा mt7921_phy *phy)
अणु
	काष्ठा mt7921_dev *dev = phy->dev;
	u32 val;

	val = mt7921_eeprom_पढ़ो(dev, MT_EE_WIFI_CONF);
	val = FIELD_GET(MT_EE_WIFI_CONF_BAND_SEL, val);

	चयन (val) अणु
	हाल MT_EE_5GHZ:
		phy->mt76->cap.has_5ghz = true;
		अवरोध;
	हाल MT_EE_2GHZ:
		phy->mt76->cap.has_2ghz = true;
		अवरोध;
	शेष:
		phy->mt76->cap.has_2ghz = true;
		phy->mt76->cap.has_5ghz = true;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mt7921_eeprom_parse_hw_cap(काष्ठा mt7921_dev *dev)
अणु
	u8 tx_mask;

	mt7921_eeprom_parse_band_config(&dev->phy);

	/* TODO: पढ़ो NSS with MCU_CMD_NIC_CAPV2 */
	tx_mask = 2;
	dev->chainmask = BIT(tx_mask) - 1;
	dev->mphy.antenna_mask = dev->chainmask;
	dev->mphy.chainmask = dev->mphy.antenna_mask;
पूर्ण

पूर्णांक mt7921_eeprom_init(काष्ठा mt7921_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt7921_eeprom_load(dev);
	अगर (ret < 0)
		वापस ret;

	ret = mt7921_check_eeprom(dev);
	अगर (ret)
		वापस ret;

	mt7921_eeprom_parse_hw_cap(dev);
	स_नकल(dev->mphy.macaddr, dev->mt76.eeprom.data + MT_EE_MAC_ADDR,
	       ETH_ALEN);

	mt76_eeprom_override(&dev->mphy);

	वापस 0;
पूर्ण
