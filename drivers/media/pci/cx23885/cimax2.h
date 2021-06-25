<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cimax2.h
 *
 * CIMax(R) SP2 driver in conjunction with NetUp Dual DVB-S2 CI card
 *
 * Copyright (C) 2009 NetUP Inc.
 * Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 * Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#अगर_अघोषित CIMAX2_H
#घोषणा CIMAX2_H
#समावेश <media/dvb_ca_en50221.h>

बाह्य पूर्णांक netup_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, पूर्णांक addr);
बाह्य पूर्णांक netup_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, पूर्णांक addr, u8 data);
बाह्य पूर्णांक netup_ci_पढ़ो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, u8 addr);
बाह्य पूर्णांक netup_ci_ग_लिखो_cam_ctl(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, u8 addr, u8 data);
बाह्य पूर्णांक netup_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक netup_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक netup_ci_slot_ts_ctl(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक netup_ci_slot_status(काष्ठा cx23885_dev *dev, u32 pci_status);
बाह्य पूर्णांक netup_poll_ci_slot_status(काष्ठा dvb_ca_en50221 *en50221,
						पूर्णांक slot, पूर्णांक खोलो);
बाह्य पूर्णांक netup_ci_init(काष्ठा cx23885_tsport *port);
बाह्य व्योम netup_ci_निकास(काष्ठा cx23885_tsport *port);

#पूर्ण_अगर
