<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2099.c: Driver क्रम the Sony CXD2099AR Common Interface Controller
 *
 * Copyright (C) 2010-2013 Digital Devices GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पन.स>

#समावेश "cxd2099.h"

अटल पूर्णांक buffermode;
module_param(buffermode, पूर्णांक, 0444);
MODULE_PARM_DESC(buffermode, "Enable CXD2099AR buffer mode (default: disabled)");

अटल पूर्णांक पढ़ो_data(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 *ebuf, पूर्णांक ecount);

काष्ठा cxd अणु
	काष्ठा dvb_ca_en50221 en;

	काष्ठा cxd2099_cfg cfg;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;

	u8     regs[0x23];
	u8     lastaddress;
	u8     clk_reg_f;
	u8     clk_reg_b;
	पूर्णांक    mode;
	पूर्णांक    पढ़ोy;
	पूर्णांक    dr;
	पूर्णांक    ग_लिखो_busy;
	पूर्णांक    slot_stat;

	u8     amem[1024];
	पूर्णांक    amem_पढ़ो;

	पूर्णांक    cammode;
	काष्ठा mutex lock; /* device access lock */

	u8     rbuf[1028];
	u8     wbuf[1028];
पूर्ण;

अटल पूर्णांक पढ़ो_block(काष्ठा cxd *ci, u8 adr, u8 *data, u16 n)
अणु
	पूर्णांक status = 0;

	अगर (ci->lastaddress != adr)
		status = regmap_ग_लिखो(ci->regmap, 0, adr);
	अगर (!status) अणु
		ci->lastaddress = adr;

		जबतक (n) अणु
			पूर्णांक len = n;

			अगर (ci->cfg.max_i2c && len > ci->cfg.max_i2c)
				len = ci->cfg.max_i2c;
			status = regmap_raw_पढ़ो(ci->regmap, 1, data, len);
			अगर (status)
				वापस status;
			data += len;
			n -= len;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक पढ़ो_reg(काष्ठा cxd *ci, u8 reg, u8 *val)
अणु
	वापस पढ़ो_block(ci, reg, val, 1);
पूर्ण

अटल पूर्णांक पढ़ो_pccard(काष्ठा cxd *ci, u16 address, u8 *data, u8 n)
अणु
	पूर्णांक status;
	u8 addr[2] = अणुaddress & 0xff, address >> 8पूर्ण;

	status = regmap_raw_ग_लिखो(ci->regmap, 2, addr, 2);
	अगर (!status)
		status = regmap_raw_पढ़ो(ci->regmap, 3, data, n);
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_pccard(काष्ठा cxd *ci, u16 address, u8 *data, u8 n)
अणु
	पूर्णांक status;
	u8 addr[2] = अणुaddress & 0xff, address >> 8पूर्ण;

	status = regmap_raw_ग_लिखो(ci->regmap, 2, addr, 2);
	अगर (!status) अणु
		u8 buf[256];

		स_नकल(buf, data, n);
		status = regmap_raw_ग_लिखो(ci->regmap, 3, buf, n);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक पढ़ो_io(काष्ठा cxd *ci, u16 address, अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक status;
	u8 addr[2] = अणुaddress & 0xff, address >> 8पूर्ण;

	status = regmap_raw_ग_लिखो(ci->regmap, 2, addr, 2);
	अगर (!status)
		status = regmap_पढ़ो(ci->regmap, 3, val);
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_io(काष्ठा cxd *ci, u16 address, u8 val)
अणु
	पूर्णांक status;
	u8 addr[2] = अणुaddress & 0xff, address >> 8पूर्ण;

	status = regmap_raw_ग_लिखो(ci->regmap, 2, addr, 2);
	अगर (!status)
		status = regmap_ग_लिखो(ci->regmap, 3, val);
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_regm(काष्ठा cxd *ci, u8 reg, u8 val, u8 mask)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक regval;

	अगर (ci->lastaddress != reg)
		status = regmap_ग_लिखो(ci->regmap, 0, reg);
	अगर (!status && reg >= 6 && reg <= 8 && mask != 0xff) अणु
		status = regmap_पढ़ो(ci->regmap, 1, &regval);
		ci->regs[reg] = regval;
	पूर्ण
	ci->lastaddress = reg;
	ci->regs[reg] = (ci->regs[reg] & (~mask)) | val;
	अगर (!status)
		status = regmap_ग_लिखो(ci->regmap, 1, ci->regs[reg]);
	अगर (reg == 0x20)
		ci->regs[reg] &= 0x7f;
	वापस status;
पूर्ण

अटल पूर्णांक ग_लिखो_reg(काष्ठा cxd *ci, u8 reg, u8 val)
अणु
	वापस ग_लिखो_regm(ci, reg, val, 0xff);
पूर्ण

अटल पूर्णांक ग_लिखो_block(काष्ठा cxd *ci, u8 adr, u8 *data, u16 n)
अणु
	पूर्णांक status = 0;
	u8 *buf = ci->wbuf;

	अगर (ci->lastaddress != adr)
		status = regmap_ग_लिखो(ci->regmap, 0, adr);
	अगर (status)
		वापस status;

	ci->lastaddress = adr;
	जबतक (n) अणु
		पूर्णांक len = n;

		अगर (ci->cfg.max_i2c && (len + 1 > ci->cfg.max_i2c))
			len = ci->cfg.max_i2c - 1;
		स_नकल(buf, data, len);
		status = regmap_raw_ग_लिखो(ci->regmap, 1, buf, len);
		अगर (status)
			वापस status;
		n -= len;
		data += len;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम set_mode(काष्ठा cxd *ci, पूर्णांक mode)
अणु
	अगर (mode == ci->mode)
		वापस;

	चयन (mode) अणु
	हाल 0x00: /* IO mem */
		ग_लिखो_regm(ci, 0x06, 0x00, 0x07);
		अवरोध;
	हाल 0x01: /* ATT mem */
		ग_लिखो_regm(ci, 0x06, 0x02, 0x07);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ci->mode = mode;
पूर्ण

अटल व्योम cam_mode(काष्ठा cxd *ci, पूर्णांक mode)
अणु
	u8 dummy;

	अगर (mode == ci->cammode)
		वापस;

	चयन (mode) अणु
	हाल 0x00:
		ग_लिखो_regm(ci, 0x20, 0x80, 0x80);
		अवरोध;
	हाल 0x01:
		अगर (!ci->en.पढ़ो_data)
			वापस;
		ci->ग_लिखो_busy = 0;
		dev_info(&ci->client->dev, "enable cam buffer mode\n");
		ग_लिखो_reg(ci, 0x0d, 0x00);
		ग_लिखो_reg(ci, 0x0e, 0x01);
		ग_लिखो_regm(ci, 0x08, 0x40, 0x40);
		पढ़ो_reg(ci, 0x12, &dummy);
		ग_लिखो_regm(ci, 0x08, 0x80, 0x80);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ci->cammode = mode;
पूर्ण

अटल पूर्णांक init(काष्ठा cxd *ci)
अणु
	पूर्णांक status;

	mutex_lock(&ci->lock);
	ci->mode = -1;
	करो अणु
		status = ग_लिखो_reg(ci, 0x00, 0x00);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x01, 0x00);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x02, 0x10);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x03, 0x00);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x05, 0xFF);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x06, 0x1F);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x07, 0x1F);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x08, 0x28);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x14, 0x20);
		अगर (status < 0)
			अवरोध;

		/* TOSTRT = 8, Mode B (gated घड़ी), falling Edge,
		 * Serial, POL=HIGH, MSB
		 */
		status = ग_लिखो_reg(ci, 0x0A, 0xA7);
		अगर (status < 0)
			अवरोध;

		status = ग_लिखो_reg(ci, 0x0B, 0x33);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x0C, 0x33);
		अगर (status < 0)
			अवरोध;

		status = ग_लिखो_regm(ci, 0x14, 0x00, 0x0F);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x15, ci->clk_reg_b);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_regm(ci, 0x16, 0x00, 0x0F);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x17, ci->clk_reg_f);
		अगर (status < 0)
			अवरोध;

		अगर (ci->cfg.घड़ी_mode == 2) अणु
			/* bitrate*2^13/ 72000 */
			u32 reg = ((ci->cfg.bitrate << 13) + 71999) / 72000;

			अगर (ci->cfg.polarity) अणु
				status = ग_लिखो_reg(ci, 0x09, 0x6f);
				अगर (status < 0)
					अवरोध;
			पूर्ण अन्यथा अणु
				status = ग_लिखो_reg(ci, 0x09, 0x6d);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			status = ग_लिखो_reg(ci, 0x20, 0x08);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x21, (reg >> 8) & 0xff);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x22, reg & 0xff);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अगर (ci->cfg.घड़ी_mode == 1) अणु
			अगर (ci->cfg.polarity) अणु
				status = ग_लिखो_reg(ci, 0x09, 0x6f); /* D */
				अगर (status < 0)
					अवरोध;
			पूर्ण अन्यथा अणु
				status = ग_लिखो_reg(ci, 0x09, 0x6d);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			status = ग_लिखो_reg(ci, 0x20, 0x68);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x21, 0x00);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x22, 0x02);
			अगर (status < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (ci->cfg.polarity) अणु
				status = ग_लिखो_reg(ci, 0x09, 0x4f); /* C */
				अगर (status < 0)
					अवरोध;
			पूर्ण अन्यथा अणु
				status = ग_लिखो_reg(ci, 0x09, 0x4d);
				अगर (status < 0)
					अवरोध;
			पूर्ण
			status = ग_लिखो_reg(ci, 0x20, 0x28);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x21, 0x00);
			अगर (status < 0)
				अवरोध;
			status = ग_लिखो_reg(ci, 0x22, 0x07);
			अगर (status < 0)
				अवरोध;
		पूर्ण

		status = ग_लिखो_regm(ci, 0x20, 0x80, 0x80);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_regm(ci, 0x03, 0x02, 0x02);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x01, 0x04);
		अगर (status < 0)
			अवरोध;
		status = ग_लिखो_reg(ci, 0x00, 0x31);
		अगर (status < 0)
			अवरोध;

		/* Put TS in bypass */
		status = ग_लिखो_regm(ci, 0x09, 0x08, 0x08);
		अगर (status < 0)
			अवरोध;
		ci->cammode = -1;
		cam_mode(ci, 0);
	पूर्ण जबतक (0);
	mutex_unlock(&ci->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
			      पूर्णांक slot, पूर्णांक address)
अणु
	काष्ठा cxd *ci = ca->data;
	u8 val;

	mutex_lock(&ci->lock);
	set_mode(ci, 1);
	पढ़ो_pccard(ci, address, &val, 1);
	mutex_unlock(&ci->lock);
	वापस val;
पूर्ण

अटल पूर्णांक ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
			       पूर्णांक address, u8 value)
अणु
	काष्ठा cxd *ci = ca->data;

	mutex_lock(&ci->lock);
	set_mode(ci, 1);
	ग_लिखो_pccard(ci, address, &value, 1);
	mutex_unlock(&ci->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca,
			    पूर्णांक slot, u8 address)
अणु
	काष्ठा cxd *ci = ca->data;
	अचिन्हित पूर्णांक val;

	mutex_lock(&ci->lock);
	set_mode(ci, 0);
	पढ़ो_io(ci, address, &val);
	mutex_unlock(&ci->lock);
	वापस val;
पूर्ण

अटल पूर्णांक ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
			     u8 address, u8 value)
अणु
	काष्ठा cxd *ci = ca->data;

	mutex_lock(&ci->lock);
	set_mode(ci, 0);
	ग_लिखो_io(ci, address, value);
	mutex_unlock(&ci->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा cxd *ci = ca->data;

	अगर (ci->cammode)
		पढ़ो_data(ca, slot, ci->rbuf, 0);

	mutex_lock(&ci->lock);
	cam_mode(ci, 0);
	ग_लिखो_reg(ci, 0x00, 0x21);
	ग_लिखो_reg(ci, 0x06, 0x1F);
	ग_लिखो_reg(ci, 0x00, 0x31);
	ग_लिखो_regm(ci, 0x20, 0x80, 0x80);
	ग_लिखो_reg(ci, 0x03, 0x02);
	ci->पढ़ोy = 0;
	ci->mode = -1;
	अणु
		पूर्णांक i;

		क्रम (i = 0; i < 100; i++) अणु
			usleep_range(10000, 11000);
			अगर (ci->पढ़ोy)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ci->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा cxd *ci = ca->data;

	dev_dbg(&ci->client->dev, "%s\n", __func__);
	अगर (ci->cammode)
		पढ़ो_data(ca, slot, ci->rbuf, 0);
	mutex_lock(&ci->lock);
	ग_लिखो_reg(ci, 0x00, 0x21);
	ग_लिखो_reg(ci, 0x06, 0x1F);
	msleep(300);

	ग_लिखो_regm(ci, 0x09, 0x08, 0x08);
	ग_लिखो_regm(ci, 0x20, 0x80, 0x80); /* Reset CAM Mode */
	ग_लिखो_regm(ci, 0x06, 0x07, 0x07); /* Clear IO Mode */

	ci->mode = -1;
	ci->ग_लिखो_busy = 0;
	mutex_unlock(&ci->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा cxd *ci = ca->data;

	mutex_lock(&ci->lock);
	ग_लिखो_regm(ci, 0x09, 0x00, 0x08);
	set_mode(ci, 0);
	cam_mode(ci, 1);
	mutex_unlock(&ci->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक campoll(काष्ठा cxd *ci)
अणु
	u8 istat;

	पढ़ो_reg(ci, 0x04, &istat);
	अगर (!istat)
		वापस 0;
	ग_लिखो_reg(ci, 0x05, istat);

	अगर (istat & 0x40)
		ci->dr = 1;
	अगर (istat & 0x20)
		ci->ग_लिखो_busy = 0;

	अगर (istat & 2) अणु
		u8 slotstat;

		पढ़ो_reg(ci, 0x01, &slotstat);
		अगर (!(2 & slotstat)) अणु
			अगर (!ci->slot_stat) अणु
				ci->slot_stat |=
					      DVB_CA_EN50221_POLL_CAM_PRESENT;
				ग_लिखो_regm(ci, 0x03, 0x08, 0x08);
			पूर्ण

		पूर्ण अन्यथा अणु
			अगर (ci->slot_stat) अणु
				ci->slot_stat = 0;
				ग_लिखो_regm(ci, 0x03, 0x00, 0x08);
				dev_info(&ci->client->dev, "NO CAM\n");
				ci->पढ़ोy = 0;
			पूर्ण
		पूर्ण
		अगर ((istat & 8) &&
		    ci->slot_stat == DVB_CA_EN50221_POLL_CAM_PRESENT) अणु
			ci->पढ़ोy = 1;
			ci->slot_stat |= DVB_CA_EN50221_POLL_CAM_READY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा cxd *ci = ca->data;
	u8 slotstat;

	mutex_lock(&ci->lock);
	campoll(ci);
	पढ़ो_reg(ci, 0x01, &slotstat);
	mutex_unlock(&ci->lock);

	वापस ci->slot_stat;
पूर्ण

अटल पूर्णांक पढ़ो_data(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 *ebuf, पूर्णांक ecount)
अणु
	काष्ठा cxd *ci = ca->data;
	u8 msb, lsb;
	u16 len;

	mutex_lock(&ci->lock);
	campoll(ci);
	mutex_unlock(&ci->lock);

	अगर (!ci->dr)
		वापस 0;

	mutex_lock(&ci->lock);
	पढ़ो_reg(ci, 0x0f, &msb);
	पढ़ो_reg(ci, 0x10, &lsb);
	len = ((u16)msb << 8) | lsb;
	अगर (len > ecount || len < 2) अणु
		/* पढ़ो it anyway or cxd may hang */
		पढ़ो_block(ci, 0x12, ci->rbuf, len);
		mutex_unlock(&ci->lock);
		वापस -EIO;
	पूर्ण
	पढ़ो_block(ci, 0x12, ebuf, len);
	ci->dr = 0;
	mutex_unlock(&ci->lock);
	वापस len;
पूर्ण

अटल पूर्णांक ग_लिखो_data(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, u8 *ebuf, पूर्णांक ecount)
अणु
	काष्ठा cxd *ci = ca->data;

	अगर (ci->ग_लिखो_busy)
		वापस -EAGAIN;
	mutex_lock(&ci->lock);
	ग_लिखो_reg(ci, 0x0d, ecount >> 8);
	ग_लिखो_reg(ci, 0x0e, ecount & 0xff);
	ग_लिखो_block(ci, 0x11, ebuf, ecount);
	ci->ग_लिखो_busy = 1;
	mutex_unlock(&ci->lock);
	वापस ecount;
पूर्ण

अटल स्थिर काष्ठा dvb_ca_en50221 en_templ = अणु
	.पढ़ो_attribute_mem  = पढ़ो_attribute_mem,
	.ग_लिखो_attribute_mem = ग_लिखो_attribute_mem,
	.पढ़ो_cam_control    = पढ़ो_cam_control,
	.ग_लिखो_cam_control   = ग_लिखो_cam_control,
	.slot_reset          = slot_reset,
	.slot_shutकरोwn       = slot_shutकरोwn,
	.slot_ts_enable      = slot_ts_enable,
	.poll_slot_status    = poll_slot_status,
	.पढ़ो_data           = पढ़ो_data,
	.ग_लिखो_data          = ग_लिखो_data,
पूर्ण;

अटल पूर्णांक cxd2099_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cxd *ci;
	काष्ठा cxd2099_cfg *cfg = client->dev.platक्रमm_data;
	अटल स्थिर काष्ठा regmap_config rm_cfg = अणु
		.reg_bits = 8,
		.val_bits = 8,
	पूर्ण;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ci = kzalloc(माप(*ci), GFP_KERNEL);
	अगर (!ci) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	ci->client = client;
	स_नकल(&ci->cfg, cfg, माप(ci->cfg));

	ci->regmap = regmap_init_i2c(client, &rm_cfg);
	अगर (IS_ERR(ci->regmap)) अणु
		ret = PTR_ERR(ci->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	ret = regmap_पढ़ो(ci->regmap, 0x00, &val);
	अगर (ret < 0) अणु
		dev_info(&client->dev, "No CXD2099AR detected at 0x%02x\n",
			 client->addr);
		जाओ err_rmनिकास;
	पूर्ण

	mutex_init(&ci->lock);
	ci->lastaddress = 0xff;
	ci->clk_reg_b = 0x4a;
	ci->clk_reg_f = 0x1b;

	ci->en = en_templ;
	ci->en.data = ci;
	init(ci);
	dev_info(&client->dev, "Attached CXD2099AR at 0x%02x\n", client->addr);

	*cfg->en = &ci->en;

	अगर (!buffermode) अणु
		ci->en.पढ़ो_data = शून्य;
		ci->en.ग_लिखो_data = शून्य;
	पूर्ण अन्यथा अणु
		dev_info(&client->dev, "Using CXD2099AR buffer mode");
	पूर्ण

	i2c_set_clientdata(client, ci);

	वापस 0;

err_rmनिकास:
	regmap_निकास(ci->regmap);
err_kमुक्त:
	kमुक्त(ci);
err:

	वापस ret;
पूर्ण

अटल पूर्णांक cxd2099_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cxd *ci = i2c_get_clientdata(client);

	regmap_निकास(ci->regmap);
	kमुक्त(ci);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cxd2099_id[] = अणु
	अणु"cxd2099", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cxd2099_id);

अटल काष्ठा i2c_driver cxd2099_driver = अणु
	.driver = अणु
		.name	= "cxd2099",
	पूर्ण,
	.probe		= cxd2099_probe,
	.हटाओ		= cxd2099_हटाओ,
	.id_table	= cxd2099_id,
पूर्ण;

module_i2c_driver(cxd2099_driver);

MODULE_DESCRIPTION("Sony CXD2099AR Common Interface controller driver");
MODULE_AUTHOR("Ralph Metzler");
MODULE_LICENSE("GPL v2");
