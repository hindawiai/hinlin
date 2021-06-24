<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright 2011 Florian Tobias Schandinat <FlorianSchandinat@gmx.de>
 */
/*
 * infraकाष्ठाure क्रम devices connected via I2C
 */

#अगर_अघोषित __VIA_AUX_H__
#घोषणा __VIA_AUX_H__


#समावेश <linux/list.h>
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>


काष्ठा via_aux_bus अणु
	काष्ठा i2c_adapter *adap;	/* the I2C device to access the bus */
	काष्ठा list_head drivers;	/* drivers क्रम devices on this bus */
पूर्ण;

काष्ठा via_aux_drv अणु
	काष्ठा list_head chain;		/* chain to support multiple drivers */

	काष्ठा via_aux_bus *bus;	/* the I2C bus used */
	u8 addr;			/* the I2C slave address */

	स्थिर अक्षर *name;	/* human पढ़ोable name of the driver */
	व्योम *data;		/* निजी data of this driver */

	व्योम (*cleanup)(काष्ठा via_aux_drv *drv);
	स्थिर काष्ठा fb_videomode* (*get_preferred_mode)
		(काष्ठा via_aux_drv *drv);
पूर्ण;


काष्ठा via_aux_bus *via_aux_probe(काष्ठा i2c_adapter *adap);
व्योम via_aux_मुक्त(काष्ठा via_aux_bus *bus);
स्थिर काष्ठा fb_videomode *via_aux_get_preferred_mode(काष्ठा via_aux_bus *bus);


अटल अंतरभूत bool via_aux_add(काष्ठा via_aux_drv *drv)
अणु
	काष्ठा via_aux_drv *data = kदो_स्मृति(माप(*data), GFP_KERNEL);

	अगर (!data)
		वापस false;

	*data = *drv;
	list_add_tail(&data->chain, &data->bus->drivers);
	वापस true;
पूर्ण

अटल अंतरभूत bool via_aux_पढ़ो(काष्ठा via_aux_drv *drv, u8 start, u8 *buf,
	u8 len)
अणु
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = drv->addr, .flags = 0, .len = 1, .buf = &startपूर्ण,
		अणु.addr = drv->addr, .flags = I2C_M_RD, .len = len, .buf = bufपूर्ण पूर्ण;

	वापस i2c_transfer(drv->bus->adap, msg, 2) == 2;
पूर्ण


/* probe functions of existing drivers - should only be called in via_aux.c */
व्योम via_aux_ch7301_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_edid_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_sii164_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1636_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1632_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1631_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1625_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1622_probe(काष्ठा via_aux_bus *bus);
व्योम via_aux_vt1621_probe(काष्ठा via_aux_bus *bus);


#पूर्ण_अगर /* __VIA_AUX_H__ */
