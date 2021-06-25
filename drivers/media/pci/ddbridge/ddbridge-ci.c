<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge-ci.c: Digital Devices bridge CI (DuoFlex, CI Bridge) support
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *                         Ralph Metzler <rjkm@metzlerbros.de>
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

#समावेश "ddbridge.h"
#समावेश "ddbridge-regs.h"
#समावेश "ddbridge-ci.h"
#समावेश "ddbridge-io.h"
#समावेश "ddbridge-i2c.h"

#समावेश "cxd2099.h"

/* Octopus CI पूर्णांकernal CI पूर्णांकerface */

अटल पूर्णांक रुको_ci_पढ़ोy(काष्ठा ddb_ci *ci)
अणु
	u32 count = 10;

	ndelay(500);
	करो अणु
		अगर (ddbपढ़ोl(ci->port->dev,
			     CI_CONTROL(ci->nr)) & CI_READY)
			अवरोध;
		usleep_range(1, 2);
		अगर ((--count) == 0)
			वापस -1;
	पूर्ण जबतक (1);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
			      पूर्णांक slot, पूर्णांक address)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	u32 val, off = (address >> 1) & (CI_BUFFER_SIZE - 1);

	अगर (address > CI_BUFFER_SIZE)
		वापस -1;
	ddbग_लिखोl(ci->port->dev, CI_READ_CMD | (1 << 16) | address,
		  CI_DO_READ_ATTRIBUTES(ci->nr));
	रुको_ci_पढ़ोy(ci);
	val = 0xff & ddbपढ़ोl(ci->port->dev, CI_BUFFER(ci->nr) + off);
	वापस val;
पूर्ण

अटल पूर्णांक ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
			       पूर्णांक address, u8 value)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	ddbग_लिखोl(ci->port->dev, CI_WRITE_CMD | (value << 16) | address,
		  CI_DO_ATTRIBUTE_RW(ci->nr));
	रुको_ci_पढ़ोy(ci);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca,
			    पूर्णांक slot, u8 address)
अणु
	u32 count = 100;
	काष्ठा ddb_ci *ci = ca->data;
	u32 res;

	ddbग_लिखोl(ci->port->dev, CI_READ_CMD | address,
		  CI_DO_IO_RW(ci->nr));
	ndelay(500);
	करो अणु
		res = ddbपढ़ोl(ci->port->dev, CI_READDATA(ci->nr));
		अगर (res & CI_READY)
			अवरोध;
		usleep_range(1, 2);
		अगर ((--count) == 0)
			वापस -1;
	पूर्ण जबतक (1);
	वापस 0xff & res;
पूर्ण

अटल पूर्णांक ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
			     u8 address, u8 value)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	ddbग_लिखोl(ci->port->dev, CI_WRITE_CMD | (value << 16) | address,
		  CI_DO_IO_RW(ci->nr));
	रुको_ci_पढ़ोy(ci);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	ddbग_लिखोl(ci->port->dev, CI_POWER_ON,
		  CI_CONTROL(ci->nr));
	msleep(100);
	ddbग_लिखोl(ci->port->dev, CI_POWER_ON | CI_RESET_CAM,
		  CI_CONTROL(ci->nr));
	ddbग_लिखोl(ci->port->dev, CI_ENABLE | CI_POWER_ON | CI_RESET_CAM,
		  CI_CONTROL(ci->nr));
	usleep_range(20, 25);
	ddbग_लिखोl(ci->port->dev, CI_ENABLE | CI_POWER_ON,
		  CI_CONTROL(ci->nr));
	वापस 0;
पूर्ण

अटल पूर्णांक slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	ddbग_लिखोl(ci->port->dev, 0, CI_CONTROL(ci->nr));
	msleep(300);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	u32 val = ddbपढ़ोl(ci->port->dev, CI_CONTROL(ci->nr));

	ddbग_लिखोl(ci->port->dev, val | CI_BYPASS_DISABLE,
		  CI_CONTROL(ci->nr));
	वापस 0;
पूर्ण

अटल पूर्णांक poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	u32 val = ddbपढ़ोl(ci->port->dev, CI_CONTROL(ci->nr));
	पूर्णांक stat = 0;

	अगर (val & CI_CAM_DETECT)
		stat |= DVB_CA_EN50221_POLL_CAM_PRESENT;
	अगर (val & CI_CAM_READY)
		stat |= DVB_CA_EN50221_POLL_CAM_READY;
	वापस stat;
पूर्ण

अटल काष्ठा dvb_ca_en50221 en_templ = अणु
	.पढ़ो_attribute_mem  = पढ़ो_attribute_mem,
	.ग_लिखो_attribute_mem = ग_लिखो_attribute_mem,
	.पढ़ो_cam_control    = पढ़ो_cam_control,
	.ग_लिखो_cam_control   = ग_लिखो_cam_control,
	.slot_reset          = slot_reset,
	.slot_shutकरोwn       = slot_shutकरोwn,
	.slot_ts_enable      = slot_ts_enable,
	.poll_slot_status    = poll_slot_status,
पूर्ण;

अटल व्योम ci_attach(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb_ci *ci;

	ci = kzalloc(माप(*ci), GFP_KERNEL);
	अगर (!ci)
		वापस;
	स_नकल(&ci->en, &en_templ, माप(en_templ));
	ci->en.data = ci;
	port->en = &ci->en;
	port->en_मुक्तdata = 1;
	ci->port = port;
	ci->nr = port->nr - 2;
पूर्ण

/* DuoFlex Dual CI support */

अटल पूर्णांक ग_लिखो_creg(काष्ठा ddb_ci *ci, u8 data, u8 mask)
अणु
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;

	ci->port->creg = (ci->port->creg & ~mask) | data;
	वापस i2c_ग_लिखो_reg(i2c, adr, 0x02, ci->port->creg);
पूर्ण

अटल पूर्णांक पढ़ो_attribute_mem_xo2(काष्ठा dvb_ca_en50221 *ca,
				  पूर्णांक slot, पूर्णांक address)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;
	पूर्णांक res;
	u8 val;

	res = i2c_पढ़ो_reg16(i2c, adr, 0x8000 | address, &val);
	वापस res ? res : val;
पूर्ण

अटल पूर्णांक ग_लिखो_attribute_mem_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
				   पूर्णांक address, u8 value)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;

	वापस i2c_ग_लिखो_reg16(i2c, adr, 0x8000 | address, value);
पूर्ण

अटल पूर्णांक पढ़ो_cam_control_xo2(काष्ठा dvb_ca_en50221 *ca,
				पूर्णांक slot, u8 address)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;
	u8 val;
	पूर्णांक res;

	res = i2c_पढ़ो_reg(i2c, adr, 0x20 | (address & 3), &val);
	वापस res ? res : val;
पूर्ण

अटल पूर्णांक ग_लिखो_cam_control_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot,
				 u8 address, u8 value)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;

	वापस i2c_ग_लिखो_reg(i2c, adr, 0x20 | (address & 3), value);
पूर्ण

अटल पूर्णांक slot_reset_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	dev_dbg(ci->port->dev->dev, "%s\n", __func__);
	ग_लिखो_creg(ci, 0x01, 0x01);
	ग_लिखो_creg(ci, 0x04, 0x04);
	msleep(20);
	ग_लिखो_creg(ci, 0x02, 0x02);
	ग_लिखो_creg(ci, 0x00, 0x04);
	ग_लिखो_creg(ci, 0x18, 0x18);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_shutकरोwn_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	dev_dbg(ci->port->dev->dev, "%s\n", __func__);
	ग_लिखो_creg(ci, 0x10, 0xff);
	ग_लिखो_creg(ci, 0x08, 0x08);
	वापस 0;
पूर्ण

अटल पूर्णांक slot_ts_enable_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा ddb_ci *ci = ca->data;

	dev_dbg(ci->port->dev->dev, "%s\n", __func__);
	ग_लिखो_creg(ci, 0x00, 0x10);
	वापस 0;
पूर्ण

अटल पूर्णांक poll_slot_status_xo2(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा ddb_ci *ci = ca->data;
	काष्ठा i2c_adapter *i2c = &ci->port->i2c->adap;
	u8 adr = (ci->port->type == DDB_CI_EXTERNAL_XO2) ? 0x12 : 0x13;
	u8 val = 0;
	पूर्णांक stat = 0;

	i2c_पढ़ो_reg(i2c, adr, 0x01, &val);

	अगर (val & 2)
		stat |= DVB_CA_EN50221_POLL_CAM_PRESENT;
	अगर (val & 1)
		stat |= DVB_CA_EN50221_POLL_CAM_READY;
	वापस stat;
पूर्ण

अटल काष्ठा dvb_ca_en50221 en_xo2_templ = अणु
	.पढ़ो_attribute_mem  = पढ़ो_attribute_mem_xo2,
	.ग_लिखो_attribute_mem = ग_लिखो_attribute_mem_xo2,
	.पढ़ो_cam_control    = पढ़ो_cam_control_xo2,
	.ग_लिखो_cam_control   = ग_लिखो_cam_control_xo2,
	.slot_reset          = slot_reset_xo2,
	.slot_shutकरोwn       = slot_shutकरोwn_xo2,
	.slot_ts_enable      = slot_ts_enable_xo2,
	.poll_slot_status    = poll_slot_status_xo2,
पूर्ण;

अटल व्योम ci_xo2_attach(काष्ठा ddb_port *port)
अणु
	काष्ठा ddb_ci *ci;

	ci = kzalloc(माप(*ci), GFP_KERNEL);
	अगर (!ci)
		वापस;
	स_नकल(&ci->en, &en_xo2_templ, माप(en_xo2_templ));
	ci->en.data = ci;
	port->en = &ci->en;
	port->en_मुक्तdata = 1;
	ci->port = port;
	ci->nr = port->nr - 2;
	ci->port->creg = 0;
	ग_लिखो_creg(ci, 0x10, 0xff);
	ग_लिखो_creg(ci, 0x08, 0x08);
पूर्ण

अटल स्थिर काष्ठा cxd2099_cfg cxd_cfgपंचांगpl = अणु
	.bitrate =  72000,
	.polarity = 1,
	.घड़ी_mode = 1,
	.max_i2c = 512,
पूर्ण;

अटल पूर्णांक ci_cxd2099_attach(काष्ठा ddb_port *port, u32 bitrate)
अणु
	काष्ठा cxd2099_cfg cxd_cfg = cxd_cfgपंचांगpl;
	काष्ठा i2c_client *client;

	cxd_cfg.bitrate = bitrate;
	cxd_cfg.en = &port->en;

	client = dvb_module_probe("cxd2099", शून्य, &port->i2c->adap,
				  0x40, &cxd_cfg);
	अगर (!client)
		जाओ err;

	port->dvb[0].i2c_client[0] = client;
	port->en_मुक्तdata = 0;
	वापस 0;

err:
	dev_err(port->dev->dev, "CXD2099AR attach failed\n");
	वापस -ENODEV;
पूर्ण

पूर्णांक ddb_ci_attach(काष्ठा ddb_port *port, u32 bitrate)
अणु
	पूर्णांक ret;

	चयन (port->type) अणु
	हाल DDB_CI_EXTERNAL_SONY:
		ret = ci_cxd2099_attach(port, bitrate);
		अगर (ret)
			वापस -ENODEV;
		अवरोध;
	हाल DDB_CI_EXTERNAL_XO2:
	हाल DDB_CI_EXTERNAL_XO2_B:
		ci_xo2_attach(port);
		अवरोध;
	हाल DDB_CI_INTERNAL:
		ci_attach(port);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	अगर (!port->en)
		वापस -ENODEV;
	dvb_ca_en50221_init(port->dvb[0].adap, port->en, 0, 1);
	वापस 0;
पूर्ण

व्योम ddb_ci_detach(काष्ठा ddb_port *port)
अणु
	अगर (port->dvb[0].dev)
		dvb_unरेजिस्टर_device(port->dvb[0].dev);
	अगर (port->en) अणु
		dvb_ca_en50221_release(port->en);

		dvb_module_release(port->dvb[0].i2c_client[0]);
		port->dvb[0].i2c_client[0] = शून्य;

		/* मुक्त alloc'ed memory अगर needed */
		अगर (port->en_मुक्तdata)
			kमुक्त(port->en->data);

		port->en = शून्य;
	पूर्ण
पूर्ण
