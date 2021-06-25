<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Retrieve encoded MAC address from 24C16 serial 2-wire EEPROM,
    decode it and store it in the associated adapter काष्ठा क्रम
    use by dvb_net.c

    This card appear to have the 24C16 ग_लिखो protect held to ground,
    thus permitting normal पढ़ो/ग_लिखो operation. Theoretically it
    would be possible to ग_लिखो routines to burn a dअगरferent (encoded)
    MAC address पूर्णांकo the EEPROM.

    Robert Schlabbach	GMX
    Michael Glaum	KVH Industries
    Holger Waechtler	Convergence

    Copyright (C) 2002-2003 Ralph Metzler <rjkm@metzlerbros.de>
			    Metzler Brothers Systementwicklung GbR


*/

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/i2c.h>
#समावेश <linux/etherdevice.h>

#समावेश "ttpci-eeprom.h"

#अगर 1
#घोषणा dprपूर्णांकk(x...) करो अणु prपूर्णांकk(x); पूर्ण जबतक (0)
#अन्यथा
#घोषणा dprपूर्णांकk(x...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर


अटल पूर्णांक check_mac_tt(u8 *buf)
अणु
	पूर्णांक i;
	u16 पंचांगp = 0xffff;

	क्रम (i = 0; i < 8; i++) अणु
		पंचांगp  = (पंचांगp << 8) | ((पंचांगp >> 8) ^ buf[i]);
		पंचांगp ^= (पंचांगp >> 4) & 0x0f;
		पंचांगp ^= (पंचांगp << 12) ^ ((पंचांगp & 0xff) << 5);
	पूर्ण
	पंचांगp ^= 0xffff;
	वापस (((पंचांगp >> 8) ^ buf[8]) | ((पंचांगp & 0xff) ^ buf[9]));
पूर्ण

अटल पूर्णांक geपंचांगac_tt(u8 * decodedMAC, u8 * encodedMAC)
अणु
	u8 xor[20] = अणु 0x72, 0x23, 0x68, 0x19, 0x5c, 0xa8, 0x71, 0x2c,
		       0x54, 0xd3, 0x7b, 0xf1, 0x9E, 0x23, 0x16, 0xf6,
		       0x1d, 0x36, 0x64, 0x78पूर्ण;
	u8 data[20];
	पूर्णांक i;

	/* In हाल there is a sig check failure have the orig contents available */
	स_नकल(data, encodedMAC, 20);

	क्रम (i = 0; i < 20; i++)
		data[i] ^= xor[i];
	क्रम (i = 0; i < 10; i++)
		data[i] = ((data[2 * i + 1] << 8) | data[2 * i])
			>> ((data[2 * i + 1] >> 6) & 3);

	अगर (check_mac_tt(data))
		वापस -ENODEV;

	decodedMAC[0] = data[2]; decodedMAC[1] = data[1]; decodedMAC[2] = data[0];
	decodedMAC[3] = data[6]; decodedMAC[4] = data[5]; decodedMAC[5] = data[4];
	वापस 0;
पूर्ण

पूर्णांक ttpci_eeprom_decode_mac(u8 *decodedMAC, u8 *encodedMAC)
अणु
	u8 xor[20] = अणु 0x72, 0x23, 0x68, 0x19, 0x5c, 0xa8, 0x71, 0x2c,
		       0x54, 0xd3, 0x7b, 0xf1, 0x9E, 0x23, 0x16, 0xf6,
		       0x1d, 0x36, 0x64, 0x78पूर्ण;
	u8 data[20];
	पूर्णांक i;

	स_नकल(data, encodedMAC, 20);

	क्रम (i = 0; i < 20; i++)
		data[i] ^= xor[i];
	क्रम (i = 0; i < 10; i++)
		data[i] = ((data[2 * i + 1] << 8) | data[2 * i])
			>> ((data[2 * i + 1] >> 6) & 3);

	अगर (check_mac_tt(data))
		वापस -ENODEV;

	decodedMAC[0] = data[2];
	decodedMAC[1] = data[1];
	decodedMAC[2] = data[0];
	decodedMAC[3] = data[6];
	decodedMAC[4] = data[5];
	decodedMAC[5] = data[4];
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ttpci_eeprom_decode_mac);

अटल पूर्णांक ttpci_eeprom_पढ़ो_encodedMAC(काष्ठा i2c_adapter *adapter, u8 * encodedMAC)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु 0xcc पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = 0x50, .flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .addr = 0x50, .flags = I2C_M_RD, .buf = encodedMAC, .len = 20 पूर्ण
	पूर्ण;

	/* dprपूर्णांकk("%s\n", __func__); */

	ret = i2c_transfer(adapter, msg, 2);

	अगर (ret != 2)		/* Assume EEPROM isn't there */
		वापस (-ENODEV);

	वापस 0;
पूर्ण


पूर्णांक ttpci_eeprom_parse_mac(काष्ठा i2c_adapter *adapter, u8 *proposed_mac)
अणु
	पूर्णांक ret;
	u8 encodedMAC[20];
	u8 decodedMAC[6];

	ret = ttpci_eeprom_पढ़ो_encodedMAC(adapter, encodedMAC);

	अगर (ret != 0) अणु		/* Will only be -ENODEV */
		dprपूर्णांकk("Couldn't read from EEPROM: not there?\n");
		eth_zero_addr(proposed_mac);
		वापस ret;
	पूर्ण

	ret = geपंचांगac_tt(decodedMAC, encodedMAC);
	अगर( ret != 0 ) अणु
		dprपूर्णांकk("adapter failed MAC signature check\n");
		dprपूर्णांकk("encoded MAC from EEPROM was %*phC",
			(पूर्णांक)माप(encodedMAC), &encodedMAC);
		eth_zero_addr(proposed_mac);
		वापस ret;
	पूर्ण

	स_नकल(proposed_mac, decodedMAC, 6);
	dprपूर्णांकk("adapter has MAC addr = %pM\n", decodedMAC);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(ttpci_eeprom_parse_mac);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ralph Metzler, Marcus Metzler, others");
MODULE_DESCRIPTION("Decode dvb_net MAC address from EEPROM of PCI DVB cards made by Siemens, Technotrend, Hauppauge");
