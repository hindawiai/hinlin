<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCTV 452e DVB driver
 *
 * Copyright (c) 2006-2008 Dominik Kuhlen <dkuhlen@gmx.net>
 *
 * TT connect S2-3650-CI Common Interface support, MAC पढ़ोout
 * Copyright (C) 2008 Michael H. Schimek <mschimek@gmx.at>
 */

/* dvb usb framework */
#घोषणा DVB_USB_LOG_PREFIX "pctv452e"
#समावेश "dvb-usb.h"

/* Demodulator */
#समावेश "stb0899_drv.h"
#समावेश "stb0899_reg.h"
#समावेश "stb0899_cfg.h"
/* Tuner */
#समावेश "stb6100.h"
#समावेश "stb6100_cfg.h"
/* FE Power */
#समावेश "isl6423.h"
#समावेश "lnbp22.h"

#समावेश <media/dvb_ca_en50221.h>
#समावेश "ttpci-eeprom.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

#घोषणा ISOC_INTERFACE_ALTERNATIVE 3

#घोषणा SYNC_BYTE_OUT 0xaa
#घोषणा SYNC_BYTE_IN  0x55

/* guessed: (copied from ttusb-budget) */
#घोषणा PCTV_CMD_RESET 0x15
/* command to poll IR receiver */
#घोषणा PCTV_CMD_IR    0x1b
/* command to send I2C  */
#घोषणा PCTV_CMD_I2C   0x31

#घोषणा I2C_ADDR_STB0899 (0xd0 >> 1)
#घोषणा I2C_ADDR_STB6100 (0xc0 >> 1)
#घोषणा I2C_ADDR_LNBP22  (0x10 >> 1)
#घोषणा I2C_ADDR_24C16   (0xa0 >> 1)
#घोषणा I2C_ADDR_24C64   (0xa2 >> 1)


/* pctv452e sends us this amount of data क्रम each issued usb-command */
#घोषणा PCTV_ANSWER_LEN 64
/* Wait up to 1000ms क्रम device  */
#घोषणा PCTV_TIMEOUT 1000


#घोषणा PCTV_LED_GPIO   STB0899_GPIO01
#घोषणा PCTV_LED_GREEN  0x82
#घोषणा PCTV_LED_ORANGE 0x02

#घोषणा ci_dbg(क्रमmat, arg...)				\
करो अणु							\
	अगर (0)						\
		prपूर्णांकk(KERN_DEBUG DVB_USB_LOG_PREFIX	\
			": " क्रमmat "\n" , ## arg);	\
पूर्ण जबतक (0)

क्रमागत अणु
	TT3650_CMD_CI_TEST = 0x40,
	TT3650_CMD_CI_RD_CTRL,
	TT3650_CMD_CI_WR_CTRL,
	TT3650_CMD_CI_RD_ATTR,
	TT3650_CMD_CI_WR_ATTR,
	TT3650_CMD_CI_RESET,
	TT3650_CMD_CI_SET_VIDEO_PORT
पूर्ण;


अटल काष्ठा stb0899_postproc pctv45e_postproc[] = अणु
	अणु PCTV_LED_GPIO, STB0899_GPIOPULLUP पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

अटल काष्ठा isl6423_config pctv452e_isl6423_config = अणु
	.current_max		= SEC_CURRENT_515m,
	.curlim			= SEC_CURRENT_LIM_ON,
	.mod_बाह्य		= 1,
	.addr			= 0x08,
पूर्ण;

/*
 * stores all निजी variables क्रम communication with the PCTV452e DVB-S2
 */
काष्ठा pctv452e_state अणु
	काष्ठा dvb_ca_en50221 ca;
	काष्ठा mutex ca_mutex;

	u8 c;	   /* transaction counter, wraps around...  */
	u8 initialized; /* set to 1 अगर 0x15 has been sent */
	u16 last_rc_key;
पूर्ण;

अटल पूर्णांक tt3650_ci_msg(काष्ठा dvb_usb_device *d, u8 cmd, u8 *data,
			 अचिन्हित पूर्णांक ग_लिखो_len, अचिन्हित पूर्णांक पढ़ो_len)
अणु
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	u8 *buf;
	u8 id;
	अचिन्हित पूर्णांक rlen;
	पूर्णांक ret;

	अगर (!data || (ग_लिखो_len > 64 - 4) || (पढ़ो_len > 64 - 4)) अणु
		err("%s: transfer data invalid", __func__);
		वापस -EIO;
	पूर्ण

	buf = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	id = state->c++;

	buf[0] = SYNC_BYTE_OUT;
	buf[1] = id;
	buf[2] = cmd;
	buf[3] = ग_लिखो_len;

	स_नकल(buf + 4, data, ग_लिखो_len);

	rlen = (पढ़ो_len > 0) ? 64 : 0;
	ret = dvb_usb_generic_rw(d, buf, 4 + ग_लिखो_len,
				  buf, rlen, /* delay_ms */ 0);
	अगर (0 != ret)
		जाओ failed;

	ret = -EIO;
	अगर (SYNC_BYTE_IN != buf[0] || id != buf[1])
		जाओ failed;

	स_नकल(data, buf + 4, पढ़ो_len);

	kमुक्त(buf);
	वापस 0;

failed:
	err("CI error %d; %02X %02X %02X -> %*ph.",
	     ret, SYNC_BYTE_OUT, id, cmd, 3, buf);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_msg_locked(काष्ठा dvb_ca_en50221 *ca,
				u8 cmd, u8 *data, अचिन्हित पूर्णांक ग_लिखो_len,
				अचिन्हित पूर्णांक पढ़ो_len)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	पूर्णांक ret;

	mutex_lock(&state->ca_mutex);
	ret = tt3650_ci_msg(d, cmd, data, ग_लिखो_len, पढ़ो_len);
	mutex_unlock(&state->ca_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक slot, पूर्णांक address)
अणु
	u8 buf[3];
	पूर्णांक ret;

	अगर (0 != slot)
		वापस -EINVAL;

	buf[0] = (address >> 8) & 0x0F;
	buf[1] = address;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_RD_ATTR, buf, 2, 3);

	ci_dbg("%s %04x -> %d 0x%02x",
		__func__, address, ret, buf[2]);

	अगर (ret < 0)
		वापस ret;

	वापस buf[2];
पूर्ण

अटल पूर्णांक tt3650_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक slot, पूर्णांक address, u8 value)
अणु
	u8 buf[3];

	ci_dbg("%s %d 0x%04x 0x%02x",
		__func__, slot, address, value);

	अगर (0 != slot)
		वापस -EINVAL;

	buf[0] = (address >> 8) & 0x0F;
	buf[1] = address;
	buf[2] = value;

	वापस tt3650_ci_msg_locked(ca, TT3650_CMD_CI_WR_ATTR, buf, 3, 3);
पूर्ण

अटल पूर्णांक tt3650_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक			slot,
				 u8			address)
अणु
	u8 buf[2];
	पूर्णांक ret;

	अगर (0 != slot)
		वापस -EINVAL;

	buf[0] = address & 3;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_RD_CTRL, buf, 1, 2);

	ci_dbg("%s 0x%02x -> %d 0x%02x",
		__func__, address, ret, buf[1]);

	अगर (ret < 0)
		वापस ret;

	वापस buf[1];
पूर्ण

अटल पूर्णांक tt3650_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक			slot,
				 u8			address,
				 u8			value)
अणु
	u8 buf[2];

	ci_dbg("%s %d 0x%02x 0x%02x",
		__func__, slot, address, value);

	अगर (0 != slot)
		वापस -EINVAL;

	buf[0] = address;
	buf[1] = value;

	वापस tt3650_ci_msg_locked(ca, TT3650_CMD_CI_WR_CTRL, buf, 2, 2);
पूर्ण

अटल पूर्णांक tt3650_ci_set_video_port(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक			slot,
				 पूर्णांक			enable)
अणु
	u8 buf[1];
	पूर्णांक ret;

	ci_dbg("%s %d %d", __func__, slot, enable);

	अगर (0 != slot)
		वापस -EINVAL;

	enable = !!enable;
	buf[0] = enable;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_SET_VIDEO_PORT, buf, 1, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (enable != buf[0]) अणु
		err("CI not %sabled.", enable ? "en" : "dis");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tt3650_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस tt3650_ci_set_video_port(ca, slot, /* enable */ 0);
पूर्ण

अटल पूर्णांक tt3650_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस tt3650_ci_set_video_port(ca, slot, /* enable */ 1);
पूर्ण

अटल पूर्णांक tt3650_ci_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	u8 buf[1];
	पूर्णांक ret;

	ci_dbg("%s %d", __func__, slot);

	अगर (0 != slot)
		वापस -EINVAL;

	buf[0] = 0;

	mutex_lock(&state->ca_mutex);

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_RESET, buf, 1, 1);
	अगर (0 != ret)
		जाओ failed;

	msleep(500);

	buf[0] = 1;

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_RESET, buf, 1, 1);
	अगर (0 != ret)
		जाओ failed;

	msleep(500);

	buf[0] = 0; /* FTA */

	ret = tt3650_ci_msg(d, TT3650_CMD_CI_SET_VIDEO_PORT, buf, 1, 1);

 failed:
	mutex_unlock(&state->ca_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक tt3650_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक			slot,
				 पूर्णांक			खोलो)
अणु
	u8 buf[1];
	पूर्णांक ret;

	अगर (0 != slot)
		वापस -EINVAL;

	ret = tt3650_ci_msg_locked(ca, TT3650_CMD_CI_TEST, buf, 0, 1);
	अगर (0 != ret)
		वापस ret;

	अगर (1 == buf[0])
		वापस DVB_CA_EN50221_POLL_CAM_PRESENT |
			DVB_CA_EN50221_POLL_CAM_READY;

	वापस 0;

पूर्ण

अटल व्योम tt3650_ci_uninit(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा pctv452e_state *state;

	ci_dbg("%s", __func__);

	अगर (शून्य == d)
		वापस;

	state = (काष्ठा pctv452e_state *)d->priv;
	अगर (शून्य == state)
		वापस;

	अगर (शून्य == state->ca.data)
		वापस;

	/* Error ignored. */
	tt3650_ci_set_video_port(&state->ca, /* slot */ 0, /* enable */ 0);

	dvb_ca_en50221_release(&state->ca);

	स_रखो(&state->ca, 0, माप(state->ca));
पूर्ण

अटल पूर्णांक tt3650_ci_init(काष्ठा dvb_usb_adapter *a)
अणु
	काष्ठा dvb_usb_device *d = a->dev;
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	पूर्णांक ret;

	ci_dbg("%s", __func__);

	mutex_init(&state->ca_mutex);

	state->ca.owner = THIS_MODULE;
	state->ca.पढ़ो_attribute_mem = tt3650_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem = tt3650_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control = tt3650_ci_पढ़ो_cam_control;
	state->ca.ग_लिखो_cam_control = tt3650_ci_ग_लिखो_cam_control;
	state->ca.slot_reset = tt3650_ci_slot_reset;
	state->ca.slot_shutकरोwn = tt3650_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable = tt3650_ci_slot_ts_enable;
	state->ca.poll_slot_status = tt3650_ci_poll_slot_status;
	state->ca.data = d;

	ret = dvb_ca_en50221_init(&a->dvb_adap,
				   &state->ca,
				   /* flags */ 0,
				   /* n_slots */ 1);
	अगर (0 != ret) अणु
		err("Cannot initialize CI: Error %d.", ret);
		स_रखो(&state->ca, 0, माप(state->ca));
		वापस ret;
	पूर्ण

	info("CI initialized.");

	वापस 0;
पूर्ण

#घोषणा CMD_BUFFER_SIZE 0x28
अटल पूर्णांक pctv452e_i2c_msg(काष्ठा dvb_usb_device *d, u8 addr,
				स्थिर u8 *snd_buf, u8 snd_len,
				u8 *rcv_buf, u8 rcv_len)
अणु
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	u8 *buf;
	u8 id;
	पूर्णांक ret;

	buf = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	id = state->c++;

	ret = -EINVAL;
	अगर (snd_len > 64 - 7 || rcv_len > 64 - 7)
		जाओ failed;

	buf[0] = SYNC_BYTE_OUT;
	buf[1] = id;
	buf[2] = PCTV_CMD_I2C;
	buf[3] = snd_len + 3;
	buf[4] = addr << 1;
	buf[5] = snd_len;
	buf[6] = rcv_len;

	स_नकल(buf + 7, snd_buf, snd_len);

	ret = dvb_usb_generic_rw(d, buf, 7 + snd_len,
				  buf, /* rcv_len */ 64,
				  /* delay_ms */ 0);
	अगर (ret < 0)
		जाओ failed;

	/* TT USB protocol error. */
	ret = -EIO;
	अगर (SYNC_BYTE_IN != buf[0] || id != buf[1])
		जाओ failed;

	/* I2C device didn't respond as expected. */
	ret = -EREMOTEIO;
	अगर (buf[5] < snd_len || buf[6] < rcv_len)
		जाओ failed;

	स_नकल(rcv_buf, buf + 7, rcv_len);

	kमुक्त(buf);
	वापस rcv_len;

failed:
	err("I2C error %d; %02X %02X  %02X %02X %02X -> %*ph",
	     ret, SYNC_BYTE_OUT, id, addr << 1, snd_len, rcv_len,
	     7, buf);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक pctv452e_i2c_xfer(काष्ठा i2c_adapter *adapter, काष्ठा i2c_msg *msg,
				पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adapter);
	पूर्णांक i;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		u8 addr, snd_len, rcv_len, *snd_buf, *rcv_buf;
		पूर्णांक ret;

		अगर (msg[i].flags & I2C_M_RD) अणु
			addr = msg[i].addr;
			snd_buf = शून्य;
			snd_len = 0;
			rcv_buf = msg[i].buf;
			rcv_len = msg[i].len;
		पूर्ण अन्यथा अणु
			addr = msg[i].addr;
			snd_buf = msg[i].buf;
			snd_len = msg[i].len;
			rcv_buf = शून्य;
			rcv_len = 0;
		पूर्ण

		ret = pctv452e_i2c_msg(d, addr, snd_buf, snd_len, rcv_buf,
					rcv_len);
		अगर (ret < rcv_len)
			अवरोध;
	पूर्ण

	mutex_unlock(&d->i2c_mutex);
	वापस i;
पूर्ण

अटल u32 pctv452e_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल पूर्णांक pctv452e_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक i)
अणु
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	u8 *b0, *rx;
	पूर्णांक ret;

	info("%s: %d\n", __func__, i);

	अगर (!i)
		वापस 0;

	अगर (state->initialized)
		वापस 0;

	b0 = kदो_स्मृति(5 + PCTV_ANSWER_LEN, GFP_KERNEL);
	अगर (!b0)
		वापस -ENOMEM;

	rx = b0 + 5;

	/* hmm where should this should go? */
	ret = usb_set_पूर्णांकerface(d->udev, 0, ISOC_INTERFACE_ALTERNATIVE);
	अगर (ret != 0)
		info("%s: Warning set interface returned: %d\n",
			__func__, ret);

	/* this is a one-समय initialization, करोn't know where to put */
	b0[0] = 0xaa;
	b0[1] = state->c++;
	b0[2] = PCTV_CMD_RESET;
	b0[3] = 1;
	b0[4] = 0;
	/* reset board */
	ret = dvb_usb_generic_rw(d, b0, 5, rx, PCTV_ANSWER_LEN, 0);
	अगर (ret)
		जाओ ret;

	b0[1] = state->c++;
	b0[4] = 1;
	/* reset board (again?) */
	ret = dvb_usb_generic_rw(d, b0, 5, rx, PCTV_ANSWER_LEN, 0);
	अगर (ret)
		जाओ ret;

	state->initialized = 1;

ret:
	kमुक्त(b0);
	वापस ret;
पूर्ण

अटल पूर्णांक pctv452e_rc_query(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा pctv452e_state *state = (काष्ठा pctv452e_state *)d->priv;
	u8 *b, *rx;
	पूर्णांक ret, i;
	u8 id;

	b = kदो_स्मृति(CMD_BUFFER_SIZE + PCTV_ANSWER_LEN, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	rx = b + CMD_BUFFER_SIZE;

	id = state->c++;

	/* prepare command header  */
	b[0] = SYNC_BYTE_OUT;
	b[1] = id;
	b[2] = PCTV_CMD_IR;
	b[3] = 0;

	/* send ir request */
	ret = dvb_usb_generic_rw(d, b, 4, rx, PCTV_ANSWER_LEN, 0);
	अगर (ret != 0)
		जाओ ret;

	अगर (debug > 3) अणु
		info("%s: read: %2d: %*ph: ", __func__, ret, 3, rx);
		क्रम (i = 0; (i < rx[3]) && ((i+3) < PCTV_ANSWER_LEN); i++)
			info(" %02x", rx[i+3]);

		info("\n");
	पूर्ण

	अगर ((rx[3] == 9) &&  (rx[12] & 0x01)) अणु
		/* got a "press" event */
		state->last_rc_key = RC_SCANCODE_RC5(rx[7], rx[6]);
		अगर (debug > 2)
			info("%s: cmd=0x%02x sys=0x%02x\n",
				__func__, rx[6], rx[7]);

		rc_keyकरोwn(d->rc_dev, RC_PROTO_RC5, state->last_rc_key, 0);
	पूर्ण अन्यथा अगर (state->last_rc_key) अणु
		rc_keyup(d->rc_dev);
		state->last_rc_key = 0;
	पूर्ण
ret:
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक pctv452e_पढ़ो_mac_address(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	स्थिर u8 mem_addr[] = अणु 0x1f, 0xcc पूर्ण;
	u8 encoded_mac[20];
	पूर्णांक ret;

	ret = -EAGAIN;
	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		जाओ failed;

	ret = pctv452e_i2c_msg(d, I2C_ADDR_24C16,
				mem_addr + 1, /* snd_len */ 1,
				encoded_mac, /* rcv_len */ 20);
	अगर (-EREMOTEIO == ret)
		/* Caution! A 24C16 पूर्णांकerprets 0xA2 0x1F 0xCC as a
		   byte ग_लिखो अगर /WC is low. */
		ret = pctv452e_i2c_msg(d, I2C_ADDR_24C64,
					mem_addr, 2,
					encoded_mac, 20);

	mutex_unlock(&d->i2c_mutex);

	अगर (20 != ret)
		जाओ failed;

	ret = ttpci_eeprom_decode_mac(mac, encoded_mac);
	अगर (0 != ret)
		जाओ failed;

	वापस 0;

failed:
	eth_zero_addr(mac);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा stb0899_s1_reg pctv452e_init_dev[] = अणु
	अणु STB0899_DISCNTRL1,	0x26 पूर्ण,
	अणु STB0899_DISCNTRL2,	0x80 पूर्ण,
	अणु STB0899_DISRX_ST0,	0x04 पूर्ण,
	अणु STB0899_DISRX_ST1,	0x20 पूर्ण,
	अणु STB0899_DISPARITY,	0x00 पूर्ण,
	अणु STB0899_DISFIFO,	0x00 पूर्ण,
	अणु STB0899_DISF22,	0x99 पूर्ण,
	अणु STB0899_DISF22RX,	0x85 पूर्ण, /* 0xa8 */
	अणु STB0899_ACRPRESC,	0x11 पूर्ण,
	अणु STB0899_ACRDIV1,	0x0a पूर्ण,
	अणु STB0899_ACRDIV2,	0x05 पूर्ण,
	अणु STB0899_DACR1	,	0x00 पूर्ण,
	अणु STB0899_DACR2	,	0x00 पूर्ण,
	अणु STB0899_OUTCFG,	0x00 पूर्ण,
	अणु STB0899_MODECFG,	0x00 पूर्ण, /* Inversion */
	अणु STB0899_IRQMSK_3,	0xf3 पूर्ण,
	अणु STB0899_IRQMSK_2,	0xfc पूर्ण,
	अणु STB0899_IRQMSK_1,	0xff पूर्ण,
	अणु STB0899_IRQMSK_0,	0xff पूर्ण,
	अणु STB0899_I2CCFG,	0x88 पूर्ण,
	अणु STB0899_I2CRPT,	0x58 पूर्ण,
	अणु STB0899_GPIO00CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO01CFG,	0x82 पूर्ण, /* LED: 0x02 green, 0x82 orange */
	अणु STB0899_GPIO02CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO03CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO04CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO05CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO06CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO07CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO08CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO09CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO10CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO11CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO12CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO13CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO14CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO15CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO16CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO17CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO18CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO19CFG,	0x82 पूर्ण,
	अणु STB0899_GPIO20CFG,	0x82 पूर्ण,
	अणु STB0899_SDATCFG,	0xb8 पूर्ण,
	अणु STB0899_SCLTCFG,	0xba पूर्ण,
	अणु STB0899_AGCRFCFG,	0x1c पूर्ण, /* 0x11 DVB-S; 0x1c DVB-S2 (1c, rjkm) */
	अणु STB0899_GPIO22,	0x82 पूर्ण,
	अणु STB0899_GPIO21,	0x91 पूर्ण,
	अणु STB0899_सूचीCLKCFG,	0x82 पूर्ण,
	अणु STB0899_CLKOUT27CFG,	0x7e पूर्ण,
	अणु STB0899_STDBYCFG,	0x82 पूर्ण,
	अणु STB0899_CS0CFG,	0x82 पूर्ण,
	अणु STB0899_CS1CFG,	0x82 पूर्ण,
	अणु STB0899_DISEQCOCFG,	0x20 पूर्ण,
	अणु STB0899_NCOARSE,	0x15 पूर्ण, /* 0x15 27Mhz, F/3 198MHz, F/6 108MHz */
	अणु STB0899_SYNTCTRL,	0x00 पूर्ण, /* 0x00 CLKI, 0x02 XTALI */
	अणु STB0899_FILTCTRL,	0x00 पूर्ण,
	अणु STB0899_SYSCTRL,	0x00 पूर्ण,
	अणु STB0899_STOPCLK1,	0x20 पूर्ण, /* orig: 0x00 budget-ci: 0x20 */
	अणु STB0899_STOPCLK2,	0x00 पूर्ण,
	अणु STB0899_INTBUFCTRL,	0x0a पूर्ण,
	अणु STB0899_AGC2I1,	0x00 पूर्ण,
	अणु STB0899_AGC2I2,	0x00 पूर्ण,
	अणु STB0899_AGCIQIN,	0x00 पूर्ण,
	अणु STB0899_TSTRES,	0x40 पूर्ण, /* rjkm */
	अणु 0xffff,		0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stb0899_s1_reg pctv452e_init_s1_demod[] = अणु
	अणु STB0899_DEMOD,	0x00 पूर्ण,
	अणु STB0899_RCOMPC,	0xc9 पूर्ण,
	अणु STB0899_AGC1CN,	0x01 पूर्ण,
	अणु STB0899_AGC1REF,	0x10 पूर्ण,
	अणु STB0899_RTC,		0x23 पूर्ण,
	अणु STB0899_TMGCFG,	0x4e पूर्ण,
	अणु STB0899_AGC2REF,	0x34 पूर्ण,
	अणु STB0899_TLSR,		0x84 पूर्ण,
	अणु STB0899_CFD,		0xf7 पूर्ण,
	अणु STB0899_ACLC,		0x87 पूर्ण,
	अणु STB0899_BCLC,		0x94 पूर्ण,
	अणु STB0899_EQON,		0x41 पूर्ण,
	अणु STB0899_LDT,		0xf1 पूर्ण,
	अणु STB0899_LDT2,		0xe3 पूर्ण,
	अणु STB0899_EQUALREF,	0xb4 पूर्ण,
	अणु STB0899_TMGRAMP,	0x10 पूर्ण,
	अणु STB0899_TMGTHD,	0x30 पूर्ण,
	अणु STB0899_IDCCOMP,	0xfd पूर्ण,
	अणु STB0899_QDCCOMP,	0xff पूर्ण,
	अणु STB0899_POWERI,	0x0c पूर्ण,
	अणु STB0899_POWERQ,	0x0f पूर्ण,
	अणु STB0899_RCOMP,	0x6c पूर्ण,
	अणु STB0899_AGCIQIN,	0x80 पूर्ण,
	अणु STB0899_AGC2I1,	0x06 पूर्ण,
	अणु STB0899_AGC2I2,	0x00 पूर्ण,
	अणु STB0899_TLIR,		0x30 पूर्ण,
	अणु STB0899_RTF,		0x7f पूर्ण,
	अणु STB0899_DSTATUS,	0x00 पूर्ण,
	अणु STB0899_LDI,		0xbc पूर्ण,
	अणु STB0899_CFRM,		0xea पूर्ण,
	अणु STB0899_CFRL,		0x31 पूर्ण,
	अणु STB0899_NIRM,		0x2b पूर्ण,
	अणु STB0899_NIRL,		0x80 पूर्ण,
	अणु STB0899_ISYMB,	0x1d पूर्ण,
	अणु STB0899_QSYMB,	0xa6 पूर्ण,
	अणु STB0899_SFRH,		0x2f पूर्ण,
	अणु STB0899_SFRM,		0x68 पूर्ण,
	अणु STB0899_SFRL,		0x40 पूर्ण,
	अणु STB0899_SFRUPH,	0x2f पूर्ण,
	अणु STB0899_SFRUPM,	0x68 पूर्ण,
	अणु STB0899_SFRUPL,	0x40 पूर्ण,
	अणु STB0899_EQUAI1,	0x02 पूर्ण,
	अणु STB0899_EQUAQ1,	0xff पूर्ण,
	अणु STB0899_EQUAI2,	0x04 पूर्ण,
	अणु STB0899_EQUAQ2,	0x05 पूर्ण,
	अणु STB0899_EQUAI3,	0x02 पूर्ण,
	अणु STB0899_EQUAQ3,	0xfd पूर्ण,
	अणु STB0899_EQUAI4,	0x03 पूर्ण,
	अणु STB0899_EQUAQ4,	0x07 पूर्ण,
	अणु STB0899_EQUAI5,	0x08 पूर्ण,
	अणु STB0899_EQUAQ5,	0xf5 पूर्ण,
	अणु STB0899_DSTATUS2,	0x00 पूर्ण,
	अणु STB0899_VSTATUS,	0x00 पूर्ण,
	अणु STB0899_VERROR,	0x86 पूर्ण,
	अणु STB0899_IQSWAP,	0x2a पूर्ण,
	अणु STB0899_ECNT1M,	0x00 पूर्ण,
	अणु STB0899_ECNT1L,	0x00 पूर्ण,
	अणु STB0899_ECNT2M,	0x00 पूर्ण,
	अणु STB0899_ECNT2L,	0x00 पूर्ण,
	अणु STB0899_ECNT3M,	0x0a पूर्ण,
	अणु STB0899_ECNT3L,	0xad पूर्ण,
	अणु STB0899_FECAUTO1,	0x06 पूर्ण,
	अणु STB0899_FECM,		0x01 पूर्ण,
	अणु STB0899_VTH12,	0xb0 पूर्ण,
	अणु STB0899_VTH23,	0x7a पूर्ण,
	अणु STB0899_VTH34,	0x58 पूर्ण,
	अणु STB0899_VTH56,	0x38 पूर्ण,
	अणु STB0899_VTH67,	0x34 पूर्ण,
	अणु STB0899_VTH78,	0x24 पूर्ण,
	अणु STB0899_PRVIT,	0xff पूर्ण,
	अणु STB0899_VITSYNC,	0x19 पूर्ण,
	अणु STB0899_RSULC,	0xb1 पूर्ण, /* DVB = 0xb1, DSS = 0xa1 */
	अणु STB0899_TSULC,	0x42 पूर्ण,
	अणु STB0899_RSLLC,	0x41 पूर्ण,
	अणु STB0899_TSLPL,	0x12 पूर्ण,
	अणु STB0899_TSCFGH,	0x0c पूर्ण,
	अणु STB0899_TSCFGM,	0x00 पूर्ण,
	अणु STB0899_TSCFGL,	0x00 पूर्ण,
	अणु STB0899_TSOUT,	0x69 पूर्ण, /* 0x0d क्रम CAM */
	अणु STB0899_RSSYNCDEL,	0x00 पूर्ण,
	अणु STB0899_TSINHDELH,	0x02 पूर्ण,
	अणु STB0899_TSINHDELM,	0x00 पूर्ण,
	अणु STB0899_TSINHDELL,	0x00 पूर्ण,
	अणु STB0899_TSLLSTKM,	0x1b पूर्ण,
	अणु STB0899_TSLLSTKL,	0xb3 पूर्ण,
	अणु STB0899_TSULSTKM,	0x00 पूर्ण,
	अणु STB0899_TSULSTKL,	0x00 पूर्ण,
	अणु STB0899_PCKLENUL,	0xbc पूर्ण,
	अणु STB0899_PCKLENLL,	0xcc पूर्ण,
	अणु STB0899_RSPCKLEN,	0xbd पूर्ण,
	अणु STB0899_TSSTATUS,	0x90 पूर्ण,
	अणु STB0899_ERRCTRL1,	0xb6 पूर्ण,
	अणु STB0899_ERRCTRL2,	0x95 पूर्ण,
	अणु STB0899_ERRCTRL3,	0x8d पूर्ण,
	अणु STB0899_DMONMSK1,	0x27 पूर्ण,
	अणु STB0899_DMONMSK0,	0x03 पूर्ण,
	अणु STB0899_DEMAPVIT,	0x5c पूर्ण,
	अणु STB0899_PLPARM,	0x19 पूर्ण,
	अणु STB0899_PDELCTRL,	0x48 पूर्ण,
	अणु STB0899_PDELCTRL2,	0x00 पूर्ण,
	अणु STB0899_BBHCTRL1,	0x00 पूर्ण,
	अणु STB0899_BBHCTRL2,	0x00 पूर्ण,
	अणु STB0899_HYSTTHRESH,	0x77 पूर्ण,
	अणु STB0899_MATCSTM,	0x00 पूर्ण,
	अणु STB0899_MATCSTL,	0x00 पूर्ण,
	अणु STB0899_UPLCSTM,	0x00 पूर्ण,
	अणु STB0899_UPLCSTL,	0x00 पूर्ण,
	अणु STB0899_DFLCSTM,	0x00 पूर्ण,
	अणु STB0899_DFLCSTL,	0x00 पूर्ण,
	अणु STB0899_SYNCCST,	0x00 पूर्ण,
	अणु STB0899_SYNCDCSTM,	0x00 पूर्ण,
	अणु STB0899_SYNCDCSTL,	0x00 पूर्ण,
	अणु STB0899_ISI_ENTRY,	0x00 पूर्ण,
	अणु STB0899_ISI_BIT_EN,	0x00 पूर्ण,
	अणु STB0899_MATSTRM,	0xf0 पूर्ण,
	अणु STB0899_MATSTRL,	0x02 पूर्ण,
	अणु STB0899_UPLSTRM,	0x45 पूर्ण,
	अणु STB0899_UPLSTRL,	0x60 पूर्ण,
	अणु STB0899_DFLSTRM,	0xe3 पूर्ण,
	अणु STB0899_DFLSTRL,	0x00 पूर्ण,
	अणु STB0899_SYNCSTR,	0x47 पूर्ण,
	अणु STB0899_SYNCDSTRM,	0x05 पूर्ण,
	अणु STB0899_SYNCDSTRL,	0x18 पूर्ण,
	अणु STB0899_CFGPDELSTATUS1, 0x19 पूर्ण,
	अणु STB0899_CFGPDELSTATUS2, 0x2b पूर्ण,
	अणु STB0899_BBFERRORM,	0x00 पूर्ण,
	अणु STB0899_BBFERRORL,	0x01 पूर्ण,
	अणु STB0899_UPKTERRORM,	0x00 पूर्ण,
	अणु STB0899_UPKTERRORL,	0x00 पूर्ण,
	अणु 0xffff,		0xff पूर्ण,
पूर्ण;

अटल काष्ठा stb0899_config stb0899_config = अणु
	.init_dev	= pctv452e_init_dev,
	.init_s2_demod	= stb0899_s2_init_2,
	.init_s1_demod	= pctv452e_init_s1_demod,
	.init_s2_fec	= stb0899_s2_init_4,
	.init_tst	= stb0899_s1_init_5,

	.demod_address   = I2C_ADDR_STB0899, /* I2C Address */
	.block_sync_mode = STB0899_SYNC_FORCED, /* ? */

	.xtal_freq       = 27000000,	 /* Assume Hz ? */
	.inversion       = IQ_SWAP_ON,

	.lo_clk	  = 76500000,
	.hi_clk	  = 99000000,

	.ts_output_mode  = 0,	/* Use parallel mode */
	.घड़ी_polarity  = 0,
	.data_clk_parity = 0,
	.fec_mode	= 0,

	.esno_ave	    = STB0899_DVBS2_ESNO_AVE,
	.esno_quant	  = STB0899_DVBS2_ESNO_QUANT,
	.avframes_coarse     = STB0899_DVBS2_AVFRAMES_COARSE,
	.avframes_fine       = STB0899_DVBS2_AVFRAMES_FINE,
	.miss_threshold      = STB0899_DVBS2_MISS_THRESHOLD,
	.uwp_threshold_acq   = STB0899_DVBS2_UWP_THRESHOLD_ACQ,
	.uwp_threshold_track = STB0899_DVBS2_UWP_THRESHOLD_TRACK,
	.uwp_threshold_sof   = STB0899_DVBS2_UWP_THRESHOLD_SOF,
	.sof_search_समयout  = STB0899_DVBS2_SOF_SEARCH_TIMEOUT,

	.btr_nco_bits	  = STB0899_DVBS2_BTR_NCO_BITS,
	.btr_gain_shअगरt_offset = STB0899_DVBS2_BTR_GAIN_SHIFT_OFFSET,
	.crl_nco_bits	  = STB0899_DVBS2_CRL_NCO_BITS,
	.ldpc_max_iter	 = STB0899_DVBS2_LDPC_MAX_ITER,

	.tuner_get_frequency	= stb6100_get_frequency,
	.tuner_set_frequency	= stb6100_set_frequency,
	.tuner_set_bandwidth	= stb6100_set_bandwidth,
	.tuner_get_bandwidth	= stb6100_get_bandwidth,
	.tuner_set_rfsiggain	= शून्य,

	/* helper क्रम चयनing LED green/orange */
	.postproc = pctv45e_postproc
पूर्ण;

अटल काष्ठा stb6100_config stb6100_config = अणु
	.tuner_address = I2C_ADDR_STB6100,
	.refघड़ी      = 27000000
पूर्ण;


अटल काष्ठा i2c_algorithm pctv452e_i2c_algo = अणु
	.master_xfer   = pctv452e_i2c_xfer,
	.functionality = pctv452e_i2c_func
पूर्ण;

अटल पूर्णांक pctv452e_frontend_attach(काष्ठा dvb_usb_adapter *a)
अणु
	काष्ठा usb_device_id *id;

	a->fe_adap[0].fe = dvb_attach(stb0899_attach, &stb0899_config,
						&a->dev->i2c_adap);
	अगर (!a->fe_adap[0].fe)
		वापस -ENODEV;

	id = a->dev->desc->warm_ids[0];
	अगर (id->idVenकरोr == USB_VID_TECHNOTREND &&
	    id->idProduct == USB_PID_TECHNOTREND_CONNECT_S2_3650_CI) अणु
		अगर (dvb_attach(lnbp22_attach,
			       a->fe_adap[0].fe,
			       &a->dev->i2c_adap) == शून्य) अणु
			err("Cannot attach lnbp22\n");
		पूर्ण
		/* Error ignored. */
		tt3650_ci_init(a);
	पूर्ण अन्यथा अगर (dvb_attach(isl6423_attach,
			      a->fe_adap[0].fe,
			      &a->dev->i2c_adap,
			      &pctv452e_isl6423_config) == शून्य) अणु
		err("Cannot attach isl6423\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pctv452e_tuner_attach(काष्ठा dvb_usb_adapter *a)
अणु
	अगर (!a->fe_adap[0].fe)
		वापस -ENODEV;
	अगर (dvb_attach(stb6100_attach, a->fe_adap[0].fe, &stb6100_config,
					&a->dev->i2c_adap) == शून्य) अणु
		err("%s failed\n", __func__);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा usb_device_id pctv452e_usb_table[] = अणु
	अणुUSB_DEVICE(USB_VID_PINNACLE, USB_PID_PCTV_452E)पूर्ण,
	अणुUSB_DEVICE(USB_VID_TECHNOTREND, USB_PID_TECHNOTREND_CONNECT_S2_3600)पूर्ण,
	अणुUSB_DEVICE(USB_VID_TECHNOTREND,
				USB_PID_TECHNOTREND_CONNECT_S2_3650_CI)पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, pctv452e_usb_table);

अटल काष्ठा dvb_usb_device_properties pctv452e_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER, /* more ? */
	.usb_ctrl = DEVICE_SPECIFIC,

	.size_of_priv     = माप(काष्ठा pctv452e_state),

	.घातer_ctrl       = pctv452e_घातer_ctrl,

	.rc.core = अणु
		.rc_codes	= RC_MAP_DIB0700_RC5_TABLE,
		.allowed_protos	= RC_PROTO_BIT_RC5,
		.rc_query	= pctv452e_rc_query,
		.rc_पूर्णांकerval	= 100,
	पूर्ण,

	.num_adapters     = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach  = pctv452e_frontend_attach,
			.tuner_attach     = pctv452e_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type     = USB_ISOC,
				.count    = 4,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 4,
						.framesize    = 940,
						.पूर्णांकerval     = 1
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्ण पूर्ण,
	पूर्ण पूर्ण,

	.i2c_algo = &pctv452e_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 1, /* allow generice rw function */

	.num_device_descs = 1,
	.devices = अणु
		अणु .name = "PCTV HDTV USB",
		  .cold_ids = अणु शून्य, शून्य पूर्ण, /* this is a warm only device */
		  .warm_ids = अणु &pctv452e_usb_table[0], शून्य पूर्ण
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties tt_connect_s2_3600_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER, /* more ? */
	.usb_ctrl = DEVICE_SPECIFIC,

	.size_of_priv		= माप(काष्ठा pctv452e_state),

	.घातer_ctrl		= pctv452e_घातer_ctrl,
	.पढ़ो_mac_address	= pctv452e_पढ़ो_mac_address,

	.rc.core = अणु
		.rc_codes	= RC_MAP_TT_1500,
		.allowed_protos	= RC_PROTO_BIT_RC5,
		.rc_query	= pctv452e_rc_query,
		.rc_पूर्णांकerval	= 100,
	पूर्ण,

	.num_adapters		= 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु
			.frontend_attach = pctv452e_frontend_attach,
			.tuner_attach = pctv452e_tuner_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_ISOC,
				.count = 4,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.isoc = अणु
						.framesperurb = 64,
						.framesize = 940,
						.पूर्णांकerval = 1
					पूर्ण
				पूर्ण
			पूर्ण,

		पूर्ण पूर्ण,
	पूर्ण पूर्ण,

	.i2c_algo = &pctv452e_i2c_algo,

	.generic_bulk_ctrl_endpoपूर्णांक = 1, /* allow generic rw function*/

	.num_device_descs = 2,
	.devices = अणु
		अणु .name = "Technotrend TT Connect S2-3600",
		  .cold_ids = अणु शून्य, शून्य पूर्ण, /* this is a warm only device */
		  .warm_ids = अणु &pctv452e_usb_table[1], शून्य पूर्ण
		पूर्ण,
		अणु .name = "Technotrend TT Connect S2-3650-CI",
		  .cold_ids = अणु शून्य, शून्य पूर्ण,
		  .warm_ids = अणु &pctv452e_usb_table[2], शून्य पूर्ण
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम pctv452e_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);

	tt3650_ci_uninit(d);
	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण

अटल पूर्णांक pctv452e_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	अगर (0 == dvb_usb_device_init(पूर्णांकf, &pctv452e_properties,
					THIS_MODULE, शून्य, adapter_nr) ||
	    0 == dvb_usb_device_init(पूर्णांकf, &tt_connect_s2_3600_properties,
					THIS_MODULE, शून्य, adapter_nr))
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल काष्ठा usb_driver pctv452e_usb_driver = अणु
	.name       = "pctv452e",
	.probe      = pctv452e_usb_probe,
	.disconnect = pctv452e_usb_disconnect,
	.id_table   = pctv452e_usb_table,
पूर्ण;

module_usb_driver(pctv452e_usb_driver);

MODULE_AUTHOR("Dominik Kuhlen <dkuhlen@gmx.net>");
MODULE_AUTHOR("Andre Weidemann <Andre.Weidemann@web.de>");
MODULE_AUTHOR("Michael H. Schimek <mschimek@gmx.at>");
MODULE_DESCRIPTION("Pinnacle PCTV HDTV USB DVB / TT connect S2-3600 Driver");
MODULE_LICENSE("GPL");
