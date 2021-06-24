<शैली गुरु>
// SPDX-License-Identअगरier: ISC

#समावेश <linux/of.h>
#समावेश "mt7603.h"
#समावेश "eeprom.h"

अटल पूर्णांक
mt7603_efuse_पढ़ो(काष्ठा mt7603_dev *dev, u32 base, u16 addr, u8 *data)
अणु
	u32 val;
	पूर्णांक i;

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	val &= ~(MT_EFUSE_CTRL_AIN |
		 MT_EFUSE_CTRL_MODE);
	val |= FIELD_PREP(MT_EFUSE_CTRL_AIN, addr & ~0xf);
	val |= MT_EFUSE_CTRL_KICK;
	mt76_wr(dev, base + MT_EFUSE_CTRL, val);

	अगर (!mt76_poll(dev, base + MT_EFUSE_CTRL, MT_EFUSE_CTRL_KICK, 0, 1000))
		वापस -ETIMEDOUT;

	udelay(2);

	val = mt76_rr(dev, base + MT_EFUSE_CTRL);
	अगर ((val & MT_EFUSE_CTRL_AOUT) == MT_EFUSE_CTRL_AOUT ||
	    WARN_ON_ONCE(!(val & MT_EFUSE_CTRL_VALID))) अणु
		स_रखो(data, 0xff, 16);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		val = mt76_rr(dev, base + MT_EFUSE_RDATA(i));
		put_unaligned_le32(val, data + 4 * i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7603_efuse_init(काष्ठा mt7603_dev *dev)
अणु
	u32 base = mt7603_reg_map(dev, MT_EFUSE_BASE);
	पूर्णांक len = MT7603_EEPROM_SIZE;
	व्योम *buf;
	पूर्णांक ret, i;

	अगर (mt76_rr(dev, base + MT_EFUSE_BASE_CTRL) & MT_EFUSE_BASE_CTRL_EMPTY)
		वापस 0;

	dev->mt76.otp.data = devm_kzalloc(dev->mt76.dev, len, GFP_KERNEL);
	dev->mt76.otp.size = len;
	अगर (!dev->mt76.otp.data)
		वापस -ENOMEM;

	buf = dev->mt76.otp.data;
	क्रम (i = 0; i + 16 <= len; i += 16) अणु
		ret = mt7603_efuse_पढ़ो(dev, base, i, buf + i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
mt7603_has_cal_मुक्त_data(काष्ठा mt7603_dev *dev, u8 *efuse)
अणु
	अगर (!efuse[MT_EE_TEMP_SENSOR_CAL])
		वापस false;

	अगर (get_unaligned_le16(efuse + MT_EE_TX_POWER_0_START_2G) == 0)
		वापस false;

	अगर (get_unaligned_le16(efuse + MT_EE_TX_POWER_1_START_2G) == 0)
		वापस false;

	अगर (!efuse[MT_EE_CP_FT_VERSION])
		वापस false;

	अगर (!efuse[MT_EE_XTAL_FREQ_OFFSET])
		वापस false;

	अगर (!efuse[MT_EE_XTAL_WF_RFCAL])
		वापस false;

	वापस true;
पूर्ण

अटल व्योम
mt7603_apply_cal_मुक्त_data(काष्ठा mt7603_dev *dev, u8 *efuse)
अणु
	अटल स्थिर u8 cal_मुक्त_bytes[] = अणु
		MT_EE_TEMP_SENSOR_CAL,
		MT_EE_CP_FT_VERSION,
		MT_EE_XTAL_FREQ_OFFSET,
		MT_EE_XTAL_WF_RFCAL,
		/* Skip क्रम MT7628 */
		MT_EE_TX_POWER_0_START_2G,
		MT_EE_TX_POWER_0_START_2G + 1,
		MT_EE_TX_POWER_1_START_2G,
		MT_EE_TX_POWER_1_START_2G + 1,
	पूर्ण;
	काष्ठा device_node *np = dev->mt76.dev->of_node;
	u8 *eeprom = dev->mt76.eeprom.data;
	पूर्णांक n = ARRAY_SIZE(cal_मुक्त_bytes);
	पूर्णांक i;

	अगर (!np || !of_property_पढ़ो_bool(np, "mediatek,eeprom-merge-otp"))
		वापस;

	अगर (!mt7603_has_cal_मुक्त_data(dev, efuse))
		वापस;

	अगर (is_mt7628(dev))
		n -= 4;

	क्रम (i = 0; i < n; i++) अणु
		पूर्णांक offset = cal_मुक्त_bytes[i];

		eeprom[offset] = efuse[offset];
	पूर्ण
पूर्ण

अटल पूर्णांक
mt7603_eeprom_load(काष्ठा mt7603_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76_eeprom_init(&dev->mt76, MT7603_EEPROM_SIZE);
	अगर (ret < 0)
		वापस ret;

	वापस mt7603_efuse_init(dev);
पूर्ण

अटल पूर्णांक mt7603_check_eeprom(काष्ठा mt76_dev *dev)
अणु
	u16 val = get_unaligned_le16(dev->eeprom.data);

	चयन (val) अणु
	हाल 0x7628:
	हाल 0x7603:
	हाल 0x7600:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_mt7688(काष्ठा mt7603_dev *dev)
अणु
	वापस mt76_rr(dev, MT_EFUSE_BASE + 0x64) & BIT(4);
पूर्ण

पूर्णांक mt7603_eeprom_init(काष्ठा mt7603_dev *dev)
अणु
	u8 *eeprom;
	पूर्णांक ret;

	ret = mt7603_eeprom_load(dev);
	अगर (ret < 0)
		वापस ret;

	अगर (dev->mt76.otp.data) अणु
		अगर (mt7603_check_eeprom(&dev->mt76) == 0)
			mt7603_apply_cal_मुक्त_data(dev, dev->mt76.otp.data);
		अन्यथा
			स_नकल(dev->mt76.eeprom.data, dev->mt76.otp.data,
			       MT7603_EEPROM_SIZE);
	पूर्ण

	eeprom = (u8 *)dev->mt76.eeprom.data;
	dev->mphy.cap.has_2ghz = true;
	स_नकल(dev->mphy.macaddr, eeprom + MT_EE_MAC_ADDR, ETH_ALEN);

	/* Check क्रम 1SS devices */
	dev->mphy.antenna_mask = 3;
	अगर (FIELD_GET(MT_EE_NIC_CONF_0_RX_PATH, eeprom[MT_EE_NIC_CONF_0]) == 1 ||
	    FIELD_GET(MT_EE_NIC_CONF_0_TX_PATH, eeprom[MT_EE_NIC_CONF_0]) == 1 ||
	    is_mt7688(dev))
		dev->mphy.antenna_mask = 1;

	mt76_eeprom_override(&dev->mphy);

	वापस 0;
पूर्ण
