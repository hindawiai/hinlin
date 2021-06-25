<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * netup-eeprom.h
 *
 * 24LC02 EEPROM driver in conjunction with NetUP Dual DVB-S2 CI card
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#अगर_अघोषित NETUP_EEPROM_H
#घोषणा NETUP_EEPROM_H

काष्ठा netup_port_info अणु
	u8 mac[6];/* card MAC address */
पूर्ण;

काष्ठा netup_card_info अणु
	काष्ठा netup_port_info port[2];/* ports - 1,2 */
	u8 rev;/* card revision */
पूर्ण;

बाह्य पूर्णांक netup_eeprom_पढ़ो(काष्ठा i2c_adapter *i2c_adap, u8 addr);
बाह्य पूर्णांक netup_eeprom_ग_लिखो(काष्ठा i2c_adapter *i2c_adap, u8 addr, u8 data);
बाह्य व्योम netup_get_card_info(काष्ठा i2c_adapter *i2c_adap,
				काष्ठा netup_card_info *cinfo);

#पूर्ण_अगर
