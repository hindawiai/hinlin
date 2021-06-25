<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	CA-driver क्रम TwinHan DST Frontend/Card

	Copyright (C) 2004, 2005 Manu Abraham (manu@kromtek.com)

*/

#अगर_अघोषित _DST_CA_H_
#घोषणा _DST_CA_H_

#घोषणा RETRIES			5


#घोषणा	CA_APP_INFO_ENQUIRY	0x9f8020
#घोषणा	CA_APP_INFO		0x9f8021
#घोषणा	CA_ENTER_MENU		0x9f8022
#घोषणा CA_INFO_ENQUIRY		0x9f8030
#घोषणा	CA_INFO			0x9f8031
#घोषणा CA_PMT			0x9f8032
#घोषणा CA_PMT_REPLY		0x9f8033

#घोषणा CA_CLOSE_MMI		0x9f8800
#घोषणा CA_DISPLAY_CONTROL	0x9f8801
#घोषणा CA_DISPLAY_REPLY	0x9f8802
#घोषणा CA_TEXT_LAST		0x9f8803
#घोषणा CA_TEXT_MORE		0x9f8804
#घोषणा CA_KEYPAD_CONTROL	0x9f8805
#घोषणा CA_KEYPRESS		0x9f8806

#घोषणा CA_ENQUIRY		0x9f8807
#घोषणा CA_ANSWER		0x9f8808
#घोषणा CA_MENU_LAST		0x9f8809
#घोषणा CA_MENU_MORE		0x9f880a
#घोषणा CA_MENU_ANSWER		0x9f880b
#घोषणा CA_LIST_LAST		0x9f880c
#घोषणा CA_LIST_MORE		0x9f880d


काष्ठा dst_ca_निजी अणु
	काष्ठा dst_state *dst;
	काष्ठा dvb_device *dvbdev;
पूर्ण;


#पूर्ण_अगर
