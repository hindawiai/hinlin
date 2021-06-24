<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-eeprom.c - eeprom access methods (currently only MAC address पढ़ोing)
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश "flexcop.h"

#अगर 0
/*EEPROM (Skystar2 has one "24LC08B" chip on board) */
अटल पूर्णांक eeprom_ग_लिखो(काष्ठा adapter *adapter, u16 addr, u8 *buf, u16 len)
अणु
	वापस flex_i2c_ग_लिखो(adapter, 0x20000000, 0x50, addr, buf, len);
पूर्ण

अटल पूर्णांक eeprom_lrc_ग_लिखो(काष्ठा adapter *adapter, u32 addr,
		u32 len, u8 *wbuf, u8 *rbuf, पूर्णांक retries)
अणु
पूर्णांक i;

क्रम (i = 0; i < retries; i++) अणु
	अगर (eeprom_ग_लिखो(adapter, addr, wbuf, len) == len) अणु
		अगर (eeprom_lrc_पढ़ो(adapter, addr, len, rbuf, retries) == 1)
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* These functions could be used to unlock SkyStar2 cards. */

अटल पूर्णांक eeprom_ग_लिखोKey(काष्ठा adapter *adapter, u8 *key, u32 len)
अणु
	u8 rbuf[20];
	u8 wbuf[20];

	अगर (len != 16)
		वापस 0;

	स_नकल(wbuf, key, len);
	wbuf[16] = 0;
	wbuf[17] = 0;
	wbuf[18] = 0;
	wbuf[19] = calc_lrc(wbuf, 19);
	वापस eeprom_lrc_ग_लिखो(adapter, 0x3e4, 20, wbuf, rbuf, 4);
पूर्ण

अटल पूर्णांक eeprom_पढ़ोKey(काष्ठा adapter *adapter, u8 *key, u32 len)
अणु
	u8 buf[20];

	अगर (len != 16)
		वापस 0;

	अगर (eeprom_lrc_पढ़ो(adapter, 0x3e4, 20, buf, 4) == 0)
		वापस 0;

	स_नकल(key, buf, len);
	वापस 1;
पूर्ण

अटल अक्षर eeprom_set_mac_addr(काष्ठा adapter *adapter, अक्षर type, u8 *mac)
अणु
	u8 पंचांगp[8];

	अगर (type != 0) अणु
		पंचांगp[0] = mac[0];
		पंचांगp[1] = mac[1];
		पंचांगp[2] = mac[2];
		पंचांगp[3] = mac[5];
		पंचांगp[4] = mac[6];
		पंचांगp[5] = mac[7];
	पूर्ण अन्यथा अणु
		पंचांगp[0] = mac[0];
		पंचांगp[1] = mac[1];
		पंचांगp[2] = mac[2];
		पंचांगp[3] = mac[3];
		पंचांगp[4] = mac[4];
		पंचांगp[5] = mac[5];
	पूर्ण

	पंचांगp[6] = 0;
	पंचांगp[7] = calc_lrc(पंचांगp, 7);

	अगर (eeprom_ग_लिखो(adapter, 0x3f8, पंचांगp, 8) == 8)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक flexcop_eeprom_पढ़ो(काष्ठा flexcop_device *fc,
		u16 addr, u8 *buf, u16 len)
अणु
	वापस fc->i2c_request(fc,FC_READ,FC_I2C_PORT_EEPROM,0x50,addr,buf,len);
पूर्ण

#पूर्ण_अगर

अटल u8 calc_lrc(u8 *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	u8 sum = 0;
	क्रम (i = 0; i < len; i++)
		sum = sum ^ buf[i];
	वापस sum;
पूर्ण

अटल पूर्णांक flexcop_eeprom_request(काष्ठा flexcop_device *fc,
	flexcop_access_op_t op, u16 addr, u8 *buf, u16 len, पूर्णांक retries)
अणु
	पूर्णांक i,ret = 0;
	u8 chipaddr =  0x50 | ((addr >> 8) & 3);
	क्रम (i = 0; i < retries; i++) अणु
		ret = fc->i2c_request(&fc->fc_i2c_adap[1], op, chipaddr,
			addr & 0xff, buf, len);
		अगर (ret == 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक flexcop_eeprom_lrc_पढ़ो(काष्ठा flexcop_device *fc, u16 addr,
		u8 *buf, u16 len, पूर्णांक retries)
अणु
	पूर्णांक ret = flexcop_eeprom_request(fc, FC_READ, addr, buf, len, retries);
	अगर (ret == 0)
		अगर (calc_lrc(buf, len - 1) != buf[len - 1])
			ret = -EINVAL;
	वापस ret;
पूर्ण

/* JJ's comment about extended == 1: it is not presently used anywhere but was
 * added to the low-level functions क्रम possible support of EUI64 */
पूर्णांक flexcop_eeprom_check_mac_addr(काष्ठा flexcop_device *fc, पूर्णांक extended)
अणु
	u8 buf[8];
	पूर्णांक ret = 0;

	अगर ((ret = flexcop_eeprom_lrc_पढ़ो(fc,0x3f8,buf,8,4)) == 0) अणु
		अगर (extended != 0) अणु
			err("TODO: extended (EUI64) MAC addresses aren't completely supported yet");
			ret = -EINVAL;
		पूर्ण अन्यथा
			स_नकल(fc->dvb_adapter.proposed_mac,buf,6);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(flexcop_eeprom_check_mac_addr);
