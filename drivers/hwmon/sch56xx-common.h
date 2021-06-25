<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 *   Copyright (C) 2010-2012 Hans de Goede <hdegoede@redhat.com>           *
 *                                                                         *
 ***************************************************************************/

#समावेश <linux/mutex.h>

काष्ठा sch56xx_watchकरोg_data;

पूर्णांक sch56xx_पढ़ो_भव_reg(u16 addr, u16 reg);
पूर्णांक sch56xx_ग_लिखो_भव_reg(u16 addr, u16 reg, u8 val);
पूर्णांक sch56xx_पढ़ो_भव_reg16(u16 addr, u16 reg);
पूर्णांक sch56xx_पढ़ो_भव_reg12(u16 addr, u16 msb_reg, u16 lsn_reg,
			       पूर्णांक high_nibble);

काष्ठा sch56xx_watchकरोg_data *sch56xx_watchकरोg_रेजिस्टर(काष्ठा device *parent,
	u16 addr, u32 revision, काष्ठा mutex *io_lock, पूर्णांक check_enabled);
व्योम sch56xx_watchकरोg_unरेजिस्टर(काष्ठा sch56xx_watchकरोg_data *data);
