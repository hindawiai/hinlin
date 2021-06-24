<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CIMaX SP2/SP2HF (Aपंचांगel T90FJR) CI driver
 *
 * Copyright (C) 2014 Olli Salonen <olli.salonen@iki.fi>
 *
 * Heavily based on CIMax2(R) SP2 driver in conjunction with NetUp Dual
 * DVB-S2 CI card (cimax2) with following copyrights:
 *
 *  Copyright (C) 2009 NetUP Inc.
 *  Copyright (C) 2009 Igor M. Liplianin <liplianin@netup.ru>
 *  Copyright (C) 2009 Abylay Ospan <aospan@netup.ru>
 */

#समावेश "sp2_priv.h"

अटल पूर्णांक sp2_पढ़ो_i2c(काष्ठा sp2 *s, u8 reg, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = s->client;
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.buf = &reg,
			.len = 1
		पूर्ण, अणु
			.addr = client->addr,
			.flags	= I2C_M_RD,
			.buf = buf,
			.len = len
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(adap, msg, 2);

	अगर (ret != 2) अणु
		dev_err(&client->dev, "i2c read error, reg = 0x%02x, status = %d\n",
				reg, ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EIO;
	पूर्ण

	dev_dbg(&s->client->dev, "addr=0x%04x, reg = 0x%02x, data = %02x\n",
				client->addr, reg, buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक sp2_ग_लिखो_i2c(काष्ठा sp2 *s, u8 reg, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	u8 buffer[35];
	काष्ठा i2c_client *client = s->client;
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = 0,
		.buf = &buffer[0],
		.len = len + 1
	पूर्ण;

	अगर ((len + 1) > माप(buffer)) अणु
		dev_err(&client->dev, "i2c wr reg=%02x: len=%d is too big!\n",
				reg, len);
		वापस -EINVAL;
	पूर्ण

	buffer[0] = reg;
	स_नकल(&buffer[1], buf, len);

	ret = i2c_transfer(adap, &msg, 1);

	अगर (ret != 1) अणु
		dev_err(&client->dev, "i2c write error, reg = 0x%02x, status = %d\n",
				reg, ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EIO;
	पूर्ण

	dev_dbg(&s->client->dev, "addr=0x%04x, reg = 0x%02x, data = %*ph\n",
				client->addr, reg, len, buf);

	वापस 0;
पूर्ण

अटल पूर्णांक sp2_ci_op_cam(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot, u8 acs,
			u8 पढ़ो, पूर्णांक addr, u8 data)
अणु
	काष्ठा sp2 *s = en50221->data;
	u8 store;
	पूर्णांक mem, ret;
	पूर्णांक (*ci_op_cam)(व्योम*, u8, पूर्णांक, u8, पूर्णांक*) = s->ci_control;

	अगर (slot != 0)
		वापस -EINVAL;

	/*
	 * change module access type between IO space and attribute memory
	 * when needed
	 */
	अगर (s->module_access_type != acs) अणु
		ret = sp2_पढ़ो_i2c(s, 0x00, &store, 1);

		अगर (ret)
			वापस ret;

		store &= ~(SP2_MOD_CTL_ACS1 | SP2_MOD_CTL_ACS0);
		store |= acs;

		ret = sp2_ग_लिखो_i2c(s, 0x00, &store, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	s->module_access_type = acs;

	/* implementation of ci_op_cam is device specअगरic */
	अगर (ci_op_cam) अणु
		ret = ci_op_cam(s->priv, पढ़ो, addr, data, &mem);
	पूर्ण अन्यथा अणु
		dev_err(&s->client->dev, "callback not defined");
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	dev_dbg(&s->client->dev, "%s: slot=%d, addr=0x%04x, %s, data=%x",
			(पढ़ो) ? "read" : "write", slot, addr,
			(acs == SP2_CI_ATTR_ACS) ? "attr" : "io",
			(पढ़ो) ? mem : data);

	अगर (पढ़ो)
		वापस mem;
	अन्यथा
		वापस 0;

पूर्ण

पूर्णांक sp2_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
				पूर्णांक slot, पूर्णांक addr)
अणु
	वापस sp2_ci_op_cam(en50221, slot, SP2_CI_ATTR_ACS,
			SP2_CI_RD, addr, 0);
पूर्ण

पूर्णांक sp2_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *en50221,
				पूर्णांक slot, पूर्णांक addr, u8 data)
अणु
	वापस sp2_ci_op_cam(en50221, slot, SP2_CI_ATTR_ACS,
			SP2_CI_WR, addr, data);
पूर्ण

पूर्णांक sp2_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *en50221,
				पूर्णांक slot, u8 addr)
अणु
	वापस sp2_ci_op_cam(en50221, slot, SP2_CI_IO_ACS,
			SP2_CI_RD, addr, 0);
पूर्ण

पूर्णांक sp2_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *en50221,
				पूर्णांक slot, u8 addr, u8 data)
अणु
	वापस sp2_ci_op_cam(en50221, slot, SP2_CI_IO_ACS,
			SP2_CI_WR, addr, data);
पूर्ण

पूर्णांक sp2_ci_slot_reset(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा sp2 *s = en50221->data;
	u8 buf;
	पूर्णांक ret;

	dev_dbg(&s->client->dev, "slot: %d\n", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	/* RST on */
	buf = SP2_MOD_CTL_RST;
	ret = sp2_ग_लिखो_i2c(s, 0x00, &buf, 1);

	अगर (ret)
		वापस ret;

	usleep_range(500, 600);

	/* RST off */
	buf = 0x00;
	ret = sp2_ग_लिखो_i2c(s, 0x00, &buf, 1);

	अगर (ret)
		वापस ret;

	msleep(1000);

	वापस 0;
पूर्ण

पूर्णांक sp2_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा sp2 *s = en50221->data;

	dev_dbg(&s->client->dev, "slot:%d\n", slot);

	/* not implemented */
	वापस 0;
पूर्ण

पूर्णांक sp2_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *en50221, पूर्णांक slot)
अणु
	काष्ठा sp2 *s = en50221->data;
	u8 buf;

	dev_dbg(&s->client->dev, "slot:%d\n", slot);

	अगर (slot != 0)
		वापस -EINVAL;

	sp2_पढ़ो_i2c(s, 0x00, &buf, 1);

	/* disable bypass and enable TS */
	buf |= (SP2_MOD_CTL_TSOEN | SP2_MOD_CTL_TSIEN);
	वापस sp2_ग_लिखो_i2c(s, 0, &buf, 1);
पूर्ण

पूर्णांक sp2_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *en50221,
				पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा sp2 *s = en50221->data;
	u8 buf[2];
	पूर्णांक ret;

	dev_dbg(&s->client->dev, "slot:%d open:%d\n", slot, खोलो);

	/*
	 * CAM module INSERT/REMOVE processing. Slow operation because of i2c
	 * transfers. Throttle पढ़ो to one per sec.
	 */
	अगर (समय_after(jअगरfies, s->next_status_checked_समय)) अणु
		ret = sp2_पढ़ो_i2c(s, 0x00, buf, 1);
		s->next_status_checked_समय = jअगरfies +	msecs_to_jअगरfies(1000);

		अगर (ret)
			वापस 0;

		अगर (buf[0] & SP2_MOD_CTL_DET)
			s->status = DVB_CA_EN50221_POLL_CAM_PRESENT |
					DVB_CA_EN50221_POLL_CAM_READY;
		अन्यथा
			s->status = 0;
	पूर्ण

	वापस s->status;
पूर्ण

अटल पूर्णांक sp2_init(काष्ठा sp2 *s)
अणु
	पूर्णांक ret = 0;
	u8 buf;
	u8 cimax_init[34] = अणु
		0x00, /* module A control*/
		0x00, /* स्वतः select mask high A */
		0x00, /* स्वतः select mask low A */
		0x00, /* स्वतः select pattern high A */
		0x00, /* स्वतः select pattern low A */
		0x44, /* memory access समय A, 600 ns */
		0x00, /* invert input A */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* module B control*/
		0x00, /* स्वतः select mask high B */
		0x00, /* स्वतः select mask low B */
		0x00, /* स्वतः select pattern high B */
		0x00, /* स्वतः select pattern low B */
		0x44, /* memory access समय B, 600 ns */
		0x00, /* invert input B */
		0x00, /* RFU */
		0x00, /* RFU */
		0x00, /* स्वतः select mask high Ext */
		0x00, /* स्वतः select mask low Ext */
		0x00, /* स्वतः select pattern high Ext */
		0x00, /* स्वतः select pattern low Ext */
		0x00, /* RFU */
		0x02, /* destination - module A */
		0x01, /* घातer control reg, VCC घातer on */
		0x00, /* RFU */
		0x00, /* पूर्णांक status पढ़ो only */
		0x00, /* Interrupt Mask Register */
		0x05, /* EXTINT=active-high, INT=push-pull */
		0x00, /* USCG1 */
		0x04, /* ack active low */
		0x00, /* LOCK = 0 */
		0x22, /* unknown */
		0x00, /* synchronization? */
	पूर्ण;

	dev_dbg(&s->client->dev, "\n");

	s->ca.owner = THIS_MODULE;
	s->ca.पढ़ो_attribute_mem = sp2_ci_पढ़ो_attribute_mem;
	s->ca.ग_लिखो_attribute_mem = sp2_ci_ग_लिखो_attribute_mem;
	s->ca.पढ़ो_cam_control = sp2_ci_पढ़ो_cam_control;
	s->ca.ग_लिखो_cam_control = sp2_ci_ग_लिखो_cam_control;
	s->ca.slot_reset = sp2_ci_slot_reset;
	s->ca.slot_shutकरोwn = sp2_ci_slot_shutकरोwn;
	s->ca.slot_ts_enable = sp2_ci_slot_ts_enable;
	s->ca.poll_slot_status = sp2_ci_poll_slot_status;
	s->ca.data = s;
	s->module_access_type = 0;

	/* initialize all regs */
	ret = sp2_ग_लिखो_i2c(s, 0x00, &cimax_init[0], 34);
	अगर (ret)
		जाओ err;

	/* lock रेजिस्टरs */
	buf = 1;
	ret = sp2_ग_लिखो_i2c(s, 0x1f, &buf, 1);
	अगर (ret)
		जाओ err;

	/* घातer on slots */
	ret = sp2_ग_लिखो_i2c(s, 0x18, &buf, 1);
	अगर (ret)
		जाओ err;

	ret = dvb_ca_en50221_init(s->dvb_adap, &s->ca, 0, 1);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_dbg(&s->client->dev, "init failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sp2_निकास(काष्ठा i2c_client *client)
अणु
	काष्ठा sp2 *s;

	dev_dbg(&client->dev, "\n");

	अगर (!client)
		वापस 0;

	s = i2c_get_clientdata(client);
	अगर (!s)
		वापस 0;

	अगर (!s->ca.data)
		वापस 0;

	dvb_ca_en50221_release(&s->ca);

	वापस 0;
पूर्ण

अटल पूर्णांक sp2_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sp2_config *cfg = client->dev.platक्रमm_data;
	काष्ठा sp2 *s;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	s->client = client;
	s->dvb_adap = cfg->dvb_adap;
	s->priv = cfg->priv;
	s->ci_control = cfg->ci_control;

	i2c_set_clientdata(client, s);

	ret = sp2_init(s);
	अगर (ret)
		जाओ err;

	dev_info(&s->client->dev, "CIMaX SP2 successfully attached\n");
	वापस 0;
err:
	dev_dbg(&client->dev, "init failed=%d\n", ret);
	kमुक्त(s);

	वापस ret;
पूर्ण

अटल पूर्णांक sp2_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा sp2 *s = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");
	sp2_निकास(client);
	kमुक्त(s);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sp2_id[] = अणु
	अणु"sp2", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sp2_id);

अटल काष्ठा i2c_driver sp2_driver = अणु
	.driver = अणु
		.name	= "sp2",
	पूर्ण,
	.probe		= sp2_probe,
	.हटाओ		= sp2_हटाओ,
	.id_table	= sp2_id,
पूर्ण;

module_i2c_driver(sp2_driver);

MODULE_DESCRIPTION("CIMaX SP2/HF CI driver");
MODULE_AUTHOR("Olli Salonen <olli.salonen@iki.fi>");
MODULE_LICENSE("GPL");
