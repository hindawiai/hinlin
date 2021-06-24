<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CIMaX SP2/HF CI driver
 *
 * Copyright (C) 2014 Olli Salonen <olli.salonen@iki.fi>
 */

#अगर_अघोषित SP2_H
#घोषणा SP2_H

#समावेश <media/dvb_ca_en50221.h>

/*
 * I2C address
 * 0x40 (port 0)
 * 0x41 (port 1)
 */
काष्ठा sp2_config अणु
	/* dvb_adapter to attach the ci to */
	काष्ठा dvb_adapter *dvb_adap;

	/* function ci_control handles the device specअगरic ci ops */
	व्योम *ci_control;

	/* priv is passed back to function ci_control */
	व्योम *priv;
पूर्ण;

बाह्य पूर्णांक sp2_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, पूर्णांक addr);
बाह्य पूर्णांक sp2_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, पूर्णांक addr, u8 data);
बाह्य पूर्णांक sp2_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, u8 addr);
बाह्य पूर्णांक sp2_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, u8 addr, u8 data);
बाह्य पूर्णांक sp2_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक sp2_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक sp2_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot);
बाह्य पूर्णांक sp2_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *en50221,
					पूर्णांक slot, पूर्णांक खोलो);

#पूर्ण_अगर
