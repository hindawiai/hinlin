<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    Retrieve encoded MAC address from ATMEL ttpci_eeprom serial 2-wire EEPROM,
    decode it and store it in associated adapter net device

    Robert Schlabbach	GMX
    Michael Glaum	KVH Industries
    Holger Waechtler	Convergence


*/

#अगर_अघोषित __TTPCI_EEPROM_H__
#घोषणा __TTPCI_EEPROM_H__

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

बाह्य पूर्णांक ttpci_eeprom_decode_mac(u8 *decodedMAC, u8 *encodedMAC);
बाह्य पूर्णांक ttpci_eeprom_parse_mac(काष्ठा i2c_adapter *adapter, u8 *propsed_mac);

#पूर्ण_अगर
