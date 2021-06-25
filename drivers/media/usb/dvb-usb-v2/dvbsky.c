<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम DVBSky USB2.0 receiver
 *
 * Copyright (C) 2013 Max nibble <nibble.max@gmail.com>
 */

#समावेश "dvb_usb.h"
#समावेश "m88ds3103.h"
#समावेश "ts2020.h"
#समावेश "sp2.h"
#समावेश "si2168.h"
#समावेश "si2157.h"

#घोषणा DVBSKY_MSG_DELAY	0/*2000*/
#घोषणा DVBSKY_BUF_LEN	64

अटल पूर्णांक dvb_usb_dvbsky_disable_rc;
module_param_named(disable_rc, dvb_usb_dvbsky_disable_rc, पूर्णांक, 0644);
MODULE_PARM_DESC(disable_rc, "Disable inbuilt IR receiver.");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा dvbsky_state अणु
	u8 ibuf[DVBSKY_BUF_LEN];
	u8 obuf[DVBSKY_BUF_LEN];
	u8 last_lock;
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;
	काष्ठा i2c_client *i2c_client_ci;

	/* fe hook functions*/
	पूर्णांक (*fe_set_voltage)(काष्ठा dvb_frontend *fe,
		क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*fe_पढ़ो_status)(काष्ठा dvb_frontend *fe,
		क्रमागत fe_status *status);
पूर्ण;

अटल पूर्णांक dvbsky_usb_generic_rw(काष्ठा dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
अणु
	पूर्णांक ret;
	काष्ठा dvbsky_state *state = d_to_priv(d);

	mutex_lock(&d->usb_mutex);
	अगर (wlen != 0)
		स_नकल(state->obuf, wbuf, wlen);

	ret = dvb_usbv2_generic_rw_locked(d, state->obuf, wlen,
			state->ibuf, rlen);

	अगर (!ret && (rlen != 0))
		स_नकल(rbuf, state->ibuf, rlen);

	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dvbsky_stream_ctrl(काष्ठा dvb_usb_device *d, u8 onoff)
अणु
	काष्ठा dvbsky_state *state = d_to_priv(d);
	अटल स्थिर u8 obuf_pre[3] = अणु 0x37, 0, 0 पूर्ण;
	अटल स्थिर u8 obuf_post[3] = अणु 0x36, 3, 0 पूर्ण;
	पूर्णांक ret;

	mutex_lock(&d->usb_mutex);
	स_नकल(state->obuf, obuf_pre, 3);
	ret = dvb_usbv2_generic_ग_लिखो_locked(d, state->obuf, 3);
	अगर (!ret && onoff) अणु
		msleep(20);
		स_नकल(state->obuf, obuf_post, 3);
		ret = dvb_usbv2_generic_ग_लिखो_locked(d, state->obuf, 3);
	पूर्ण
	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक dvbsky_streaming_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);

	वापस dvbsky_stream_ctrl(d, (onoff == 0) ? 0 : 1);
पूर्ण

/* GPIO */
अटल पूर्णांक dvbsky_gpio_ctrl(काष्ठा dvb_usb_device *d, u8 gport, u8 value)
अणु
	पूर्णांक ret;
	u8 obuf[3], ibuf[2];

	obuf[0] = 0x0e;
	obuf[1] = gport;
	obuf[2] = value;
	ret = dvbsky_usb_generic_rw(d, obuf, 3, ibuf, 1);
	वापस ret;
पूर्ण

/* I2C */
अटल पूर्णांक dvbsky_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[],
	पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक ret = 0;
	u8 ibuf[64], obuf[64];

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	अगर (num > 2) अणु
		dev_err(&d->udev->dev,
		"too many i2c messages[%d], max 2.", num);
		ret = -EOPNOTSUPP;
		जाओ i2c_error;
	पूर्ण

	अगर (num == 1) अणु
		अगर (msg[0].len > 60) अणु
			dev_err(&d->udev->dev,
			"too many i2c bytes[%d], max 60.",
			msg[0].len);
			ret = -EOPNOTSUPP;
			जाओ i2c_error;
		पूर्ण
		अगर (msg[0].flags & I2C_M_RD) अणु
			/* single पढ़ो */
			obuf[0] = 0x09;
			obuf[1] = 0;
			obuf[2] = msg[0].len;
			obuf[3] = msg[0].addr;
			ret = dvbsky_usb_generic_rw(d, obuf, 4,
					ibuf, msg[0].len + 1);
			अगर (!ret)
				स_नकल(msg[0].buf, &ibuf[1], msg[0].len);
		पूर्ण अन्यथा अणु
			/* ग_लिखो */
			obuf[0] = 0x08;
			obuf[1] = msg[0].addr;
			obuf[2] = msg[0].len;
			स_नकल(&obuf[3], msg[0].buf, msg[0].len);
			ret = dvbsky_usb_generic_rw(d, obuf,
					msg[0].len + 3, ibuf, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((msg[0].len > 60) || (msg[1].len > 60)) अणु
			dev_err(&d->udev->dev,
			"too many i2c bytes[w-%d][r-%d], max 60.",
			msg[0].len, msg[1].len);
			ret = -EOPNOTSUPP;
			जाओ i2c_error;
		पूर्ण
		/* ग_लिखो then पढ़ो */
		obuf[0] = 0x09;
		obuf[1] = msg[0].len;
		obuf[2] = msg[1].len;
		obuf[3] = msg[0].addr;
		स_नकल(&obuf[4], msg[0].buf, msg[0].len);
		ret = dvbsky_usb_generic_rw(d, obuf,
			msg[0].len + 4, ibuf, msg[1].len + 1);
		अगर (!ret)
			स_नकल(msg[1].buf, &ibuf[1], msg[1].len);
	पूर्ण
i2c_error:
	mutex_unlock(&d->i2c_mutex);
	वापस (ret) ? ret : num;
पूर्ण

अटल u32 dvbsky_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm dvbsky_i2c_algo = अणु
	.master_xfer   = dvbsky_i2c_xfer,
	.functionality = dvbsky_i2c_func,
पूर्ण;

#अगर IS_ENABLED(CONFIG_RC_CORE)
अटल पूर्णांक dvbsky_rc_query(काष्ठा dvb_usb_device *d)
अणु
	u32 code = 0xffff, scancode;
	u8 rc5_command, rc5_प्रणाली;
	u8 obuf[2], ibuf[2], toggle;
	पूर्णांक ret;

	obuf[0] = 0x10;
	ret = dvbsky_usb_generic_rw(d, obuf, 1, ibuf, 2);
	अगर (ret == 0)
		code = (ibuf[0] << 8) | ibuf[1];
	अगर (code != 0xffff) अणु
		dev_dbg(&d->udev->dev, "rc code: %x\n", code);
		rc5_command = code & 0x3F;
		rc5_प्रणाली = (code & 0x7C0) >> 6;
		toggle = (code & 0x800) ? 1 : 0;
		scancode = rc5_प्रणाली << 8 | rc5_command;
		rc_keyकरोwn(d->rc_dev, RC_PROTO_RC5, scancode, toggle);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_get_rc_config(काष्ठा dvb_usb_device *d, काष्ठा dvb_usb_rc *rc)
अणु
	अगर (dvb_usb_dvbsky_disable_rc) अणु
		rc->map_name = शून्य;
		वापस 0;
	पूर्ण

	rc->allowed_protos = RC_PROTO_BIT_RC5;
	rc->query          = dvbsky_rc_query;
	rc->पूर्णांकerval       = 300;
	वापस 0;
पूर्ण
#अन्यथा
	#घोषणा dvbsky_get_rc_config शून्य
#पूर्ण_अगर

अटल पूर्णांक dvbsky_usb_set_voltage(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा dvbsky_state *state = d_to_priv(d);
	u8 value;

	अगर (voltage == SEC_VOLTAGE_OFF)
		value = 0;
	अन्यथा
		value = 1;
	dvbsky_gpio_ctrl(d, 0x80, value);

	वापस state->fe_set_voltage(fe, voltage);
पूर्ण

अटल पूर्णांक dvbsky_पढ़ो_mac_addr(काष्ठा dvb_usb_adapter *adap, u8 mac[6])
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	u8 obuf[] = अणु 0x1e, 0x00 पूर्ण;
	u8 ibuf[6] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = 0x51,
			.flags = 0,
			.buf = obuf,
			.len = 2,
		पूर्ण, अणु
			.addr = 0x51,
			.flags = I2C_M_RD,
			.buf = ibuf,
			.len = 6,
		पूर्ण
	पूर्ण;

	अगर (i2c_transfer(&d->i2c_adap, msg, 2) == 2)
		स_नकल(mac, ibuf, 6);

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_usb_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *status)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा dvbsky_state *state = d_to_priv(d);
	पूर्णांक ret;

	ret = state->fe_पढ़ो_status(fe, status);

	/* it need resync slave fअगरo when संकेत change from unlock to lock.*/
	अगर ((*status & FE_HAS_LOCK) && (!state->last_lock))
		dvbsky_stream_ctrl(d, 1);

	state->last_lock = (*status & FE_HAS_LOCK) ? 1 : 0;
	वापस ret;
पूर्ण

अटल पूर्णांक dvbsky_s960_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvbsky_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata = अणुपूर्ण;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.clk_out = 0;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.lnb_hv_pol = 1;
	m88ds3103_pdata.lnb_en_pol = 1;

	state->i2c_client_demod = dvb_module_probe("m88ds3103", शून्य,
						   &d->i2c_adap,
						   0x68, &m88ds3103_pdata);
	अगर (!state->i2c_client_demod)
		वापस -ENODEV;

	adap->fe[0] = m88ds3103_pdata.get_dvb_frontend(state->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(state->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = adap->fe[0];
	ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;

	state->i2c_client_tuner = dvb_module_probe("ts2020", शून्य,
						   i2c_adapter,
						   0x60, &ts2020_config);
	अगर (!state->i2c_client_tuner) अणु
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	adap->fe[0]->ops.पढ़ो_संकेत_strength =
			adap->fe[0]->ops.tuner_ops.get_rf_strength;

	/* hook fe: need to resync the slave fअगरo when संकेत locks. */
	state->fe_पढ़ो_status = adap->fe[0]->ops.पढ़ो_status;
	adap->fe[0]->ops.पढ़ो_status = dvbsky_usb_पढ़ो_status;

	/* hook fe: LNB off/on is control by Cypress usb chip. */
	state->fe_set_voltage = adap->fe[0]->ops.set_voltage;
	adap->fe[0]->ops.set_voltage = dvbsky_usb_set_voltage;

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_usb_ci_set_voltage(काष्ठा dvb_frontend *fe,
	क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा dvb_usb_device *d = fe_to_d(fe);
	काष्ठा dvbsky_state *state = d_to_priv(d);
	u8 value;

	अगर (voltage == SEC_VOLTAGE_OFF)
		value = 0;
	अन्यथा
		value = 1;
	dvbsky_gpio_ctrl(d, 0x00, value);

	वापस state->fe_set_voltage(fe, voltage);
पूर्ण

अटल पूर्णांक dvbsky_ci_ctrl(व्योम *priv, u8 पढ़ो, पूर्णांक addr,
					u8 data, पूर्णांक *mem)
अणु
	काष्ठा dvb_usb_device *d = priv;
	पूर्णांक ret = 0;
	u8 command[4], respond[2], command_size, respond_size;

	command[1] = (u8)((addr >> 8) & 0xff); /*high part of address*/
	command[2] = (u8)(addr & 0xff); /*low part of address*/
	अगर (पढ़ो) अणु
		command[0] = 0x71;
		command_size = 3;
		respond_size = 2;
	पूर्ण अन्यथा अणु
		command[0] = 0x70;
		command[3] = data;
		command_size = 4;
		respond_size = 1;
	पूर्ण
	ret = dvbsky_usb_generic_rw(d, command, command_size,
			respond, respond_size);
	अगर (ret)
		जाओ err;
	अगर (पढ़ो)
		*mem = respond[1];
	वापस ret;
err:
	dev_err(&d->udev->dev, "ci control failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक dvbsky_s960c_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvbsky_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata = अणुपूर्ण;
	काष्ठा ts2020_config ts2020_config = अणुपूर्ण;
	काष्ठा sp2_config sp2_config = अणुपूर्ण;

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.clk_out = 0;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_clk = 10000;
	m88ds3103_pdata.ts_clk_pol = 1;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.lnb_hv_pol = 0;
	m88ds3103_pdata.lnb_en_pol = 1;

	state->i2c_client_demod = dvb_module_probe("m88ds3103", शून्य,
						   &d->i2c_adap,
						   0x68, &m88ds3103_pdata);
	अगर (!state->i2c_client_demod)
		वापस -ENODEV;

	adap->fe[0] = m88ds3103_pdata.get_dvb_frontend(state->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(state->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = adap->fe[0];
	ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;

	state->i2c_client_tuner = dvb_module_probe("ts2020", शून्य,
						   i2c_adapter,
						   0x60, &ts2020_config);
	अगर (!state->i2c_client_tuner) अणु
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* attach ci controller */
	sp2_config.dvb_adap = &adap->dvb_adap;
	sp2_config.priv = d;
	sp2_config.ci_control = dvbsky_ci_ctrl;

	state->i2c_client_ci = dvb_module_probe("sp2", शून्य,
						&d->i2c_adap,
						0x40, &sp2_config);

	अगर (!state->i2c_client_ci) अणु
		dvb_module_release(state->i2c_client_tuner);
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* delegate संकेत strength measurement to tuner */
	adap->fe[0]->ops.पढ़ो_संकेत_strength =
			adap->fe[0]->ops.tuner_ops.get_rf_strength;

	/* hook fe: need to resync the slave fअगरo when संकेत locks. */
	state->fe_पढ़ो_status = adap->fe[0]->ops.पढ़ो_status;
	adap->fe[0]->ops.पढ़ो_status = dvbsky_usb_पढ़ो_status;

	/* hook fe: LNB off/on is control by Cypress usb chip. */
	state->fe_set_voltage = adap->fe[0]->ops.set_voltage;
	adap->fe[0]->ops.set_voltage = dvbsky_usb_ci_set_voltage;

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_t680c_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvbsky_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;
	काष्ठा sp2_config sp2_config = अणुपूर्ण;

	/* attach demod */
	si2168_config.i2c_adapter = &i2c_adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;

	state->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	अगर (!state->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	si2157_config.fe = adap->fe[0];
	si2157_config.अगर_port = 1;

	state->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
						   i2c_adapter,
						   0x60, &si2157_config);
	अगर (!state->i2c_client_tuner) अणु
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	/* attach ci controller */
	sp2_config.dvb_adap = &adap->dvb_adap;
	sp2_config.priv = d;
	sp2_config.ci_control = dvbsky_ci_ctrl;

	state->i2c_client_ci = dvb_module_probe("sp2", शून्य,
						&d->i2c_adap,
						0x40, &sp2_config);

	अगर (!state->i2c_client_ci) अणु
		dvb_module_release(state->i2c_client_tuner);
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_t330_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvbsky_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;

	/* attach demod */
	si2168_config.i2c_adapter = &i2c_adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;
	si2168_config.ts_घड़ी_gapped = true;

	state->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	अगर (!state->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	si2157_config.fe = adap->fe[0];
	si2157_config.अगर_port = 1;

	state->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
						   i2c_adapter,
						   0x60, &si2157_config);
	अगर (!state->i2c_client_tuner) अणु
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_mygica_t230c_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvbsky_state *state = adap_to_priv(adap);
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा i2c_adapter *i2c_adapter;
	काष्ठा si2168_config si2168_config = अणुपूर्ण;
	काष्ठा si2157_config si2157_config = अणुपूर्ण;

	/* attach demod */
	si2168_config.i2c_adapter = &i2c_adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;
	अगर (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_MYGICA_T230C2)
		si2168_config.ts_mode |= SI2168_TS_CLK_MANUAL;
	si2168_config.ts_घड़ी_inv = 1;

	state->i2c_client_demod = dvb_module_probe("si2168", शून्य,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	अगर (!state->i2c_client_demod)
		वापस -ENODEV;

	/* attach tuner */
	si2157_config.fe = adap->fe[0];
	अगर (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_MYGICA_T230) अणु
		si2157_config.अगर_port = 1;
		state->i2c_client_tuner = dvb_module_probe("si2157", शून्य,
							   i2c_adapter,
							   0x60,
							   &si2157_config);
	पूर्ण अन्यथा अणु
		si2157_config.अगर_port = 0;
		state->i2c_client_tuner = dvb_module_probe("si2157", "si2141",
							   i2c_adapter,
							   0x60,
							   &si2157_config);
	पूर्ण
	अगर (!state->i2c_client_tuner) अणु
		dvb_module_release(state->i2c_client_demod);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक dvbsky_identअगरy_state(काष्ठा dvb_usb_device *d, स्थिर अक्षर **name)
अणु
	dvbsky_gpio_ctrl(d, 0x04, 1);
	msleep(20);
	dvbsky_gpio_ctrl(d, 0x83, 0);
	dvbsky_gpio_ctrl(d, 0xc0, 1);
	msleep(100);
	dvbsky_gpio_ctrl(d, 0x83, 1);
	dvbsky_gpio_ctrl(d, 0xc0, 0);
	msleep(50);

	वापस WARM;
पूर्ण

अटल पूर्णांक dvbsky_init(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा dvbsky_state *state = d_to_priv(d);
	state->last_lock = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_frontend_detach(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा dvb_usb_device *d = adap_to_d(adap);
	काष्ठा dvbsky_state *state = d_to_priv(d);

	dev_dbg(&d->udev->dev, "%s: adap=%d\n", __func__, adap->id);

	dvb_module_release(state->i2c_client_tuner);
	dvb_module_release(state->i2c_client_demod);
	dvb_module_release(state->i2c_client_ci);

	वापस 0;
पूर्ण

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties dvbsky_s960_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा dvbsky_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,
	.generic_bulk_ctrl_delay = DVBSKY_MSG_DELAY,

	.i2c_algo         = &dvbsky_i2c_algo,
	.frontend_attach  = dvbsky_s960_attach,
	.frontend_detach  = dvbsky_frontend_detach,
	.init             = dvbsky_init,
	.get_rc_config    = dvbsky_get_rc_config,
	.streaming_ctrl   = dvbsky_streaming_ctrl,
	.identअगरy_state	  = dvbsky_identअगरy_state,
	.पढ़ो_mac_address = dvbsky_पढ़ो_mac_addr,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 4096),
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dvbsky_s960c_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा dvbsky_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,
	.generic_bulk_ctrl_delay = DVBSKY_MSG_DELAY,

	.i2c_algo         = &dvbsky_i2c_algo,
	.frontend_attach  = dvbsky_s960c_attach,
	.frontend_detach  = dvbsky_frontend_detach,
	.init             = dvbsky_init,
	.get_rc_config    = dvbsky_get_rc_config,
	.streaming_ctrl   = dvbsky_streaming_ctrl,
	.identअगरy_state	  = dvbsky_identअगरy_state,
	.पढ़ो_mac_address = dvbsky_पढ़ो_mac_addr,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 4096),
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dvbsky_t680c_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा dvbsky_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,
	.generic_bulk_ctrl_delay = DVBSKY_MSG_DELAY,

	.i2c_algo         = &dvbsky_i2c_algo,
	.frontend_attach  = dvbsky_t680c_attach,
	.frontend_detach  = dvbsky_frontend_detach,
	.init             = dvbsky_init,
	.get_rc_config    = dvbsky_get_rc_config,
	.streaming_ctrl   = dvbsky_streaming_ctrl,
	.identअगरy_state	  = dvbsky_identअगरy_state,
	.पढ़ो_mac_address = dvbsky_पढ़ो_mac_addr,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 4096),
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dvbsky_t330_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा dvbsky_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,
	.generic_bulk_ctrl_delay = DVBSKY_MSG_DELAY,

	.i2c_algo         = &dvbsky_i2c_algo,
	.frontend_attach  = dvbsky_t330_attach,
	.frontend_detach  = dvbsky_frontend_detach,
	.init             = dvbsky_init,
	.get_rc_config    = dvbsky_get_rc_config,
	.streaming_ctrl   = dvbsky_streaming_ctrl,
	.identअगरy_state	  = dvbsky_identअगरy_state,
	.पढ़ो_mac_address = dvbsky_पढ़ो_mac_addr,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 4096),
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties mygica_t230c_props = अणु
	.driver_name = KBUILD_MODNAME,
	.owner = THIS_MODULE,
	.adapter_nr = adapter_nr,
	.size_of_priv = माप(काष्ठा dvbsky_state),

	.generic_bulk_ctrl_endpoपूर्णांक = 0x01,
	.generic_bulk_ctrl_endpoपूर्णांक_response = 0x81,
	.generic_bulk_ctrl_delay = DVBSKY_MSG_DELAY,

	.i2c_algo         = &dvbsky_i2c_algo,
	.frontend_attach  = dvbsky_mygica_t230c_attach,
	.frontend_detach  = dvbsky_frontend_detach,
	.init             = dvbsky_init,
	.get_rc_config    = dvbsky_get_rc_config,
	.streaming_ctrl   = dvbsky_streaming_ctrl,
	.identअगरy_state	  = dvbsky_identअगरy_state,

	.num_adapters = 1,
	.adapter = अणु
		अणु
			.stream = DVB_USB_STREAM_BULK(0x82, 8, 4096),
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा usb_device_id dvbsky_id_table[] = अणु
	अणु DVB_USB_DEVICE(0x0572, 0x6831,
		&dvbsky_s960_props, "DVBSky S960/S860", RC_MAP_DVBSKY) पूर्ण,
	अणु DVB_USB_DEVICE(0x0572, 0x960c,
		&dvbsky_s960c_props, "DVBSky S960CI", RC_MAP_DVBSKY) पूर्ण,
	अणु DVB_USB_DEVICE(0x0572, 0x680c,
		&dvbsky_t680c_props, "DVBSky T680CI", RC_MAP_DVBSKY) पूर्ण,
	अणु DVB_USB_DEVICE(0x0572, 0x0320,
		&dvbsky_t330_props, "DVBSky T330", RC_MAP_DVBSKY) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_TVSTICK_CT2_4400,
		&dvbsky_t330_props, "TechnoTrend TVStick CT2-4400",
		RC_MAP_TT_1500) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_CT2_4650_CI,
		&dvbsky_t680c_props, "TechnoTrend TT-connect CT2-4650 CI",
		RC_MAP_TT_1500) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_CT2_4650_CI_2,
		&dvbsky_t680c_props, "TechnoTrend TT-connect CT2-4650 CI v1.1",
		RC_MAP_TT_1500) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TECHNOTREND,
		USB_PID_TECHNOTREND_CONNECT_S2_4650_CI,
		&dvbsky_s960c_props, "TechnoTrend TT-connect S2-4650 CI",
		RC_MAP_TT_1500) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC,
		USB_PID_TERRATEC_H7_3,
		&dvbsky_t680c_props, "Terratec H7 Rev.4",
		RC_MAP_TT_1500) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_TERRATEC, USB_PID_TERRATEC_CINERGY_S2_R4,
		&dvbsky_s960_props, "Terratec Cinergy S2 Rev.4",
		RC_MAP_DVBSKY) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230,
		&mygica_t230c_props, "MyGica Mini DVB-(T/T2/C) USB Stick T230",
		RC_MAP_TOTAL_MEDIA_IN_HAND_02) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C,
		&mygica_t230c_props, "MyGica Mini DVB-(T/T2/C) USB Stick T230C",
		RC_MAP_TOTAL_MEDIA_IN_HAND_02) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C_LITE,
		&mygica_t230c_props, "MyGica Mini DVB-(T/T2/C) USB Stick T230C Lite",
		शून्य) पूर्ण,
	अणु DVB_USB_DEVICE(USB_VID_CONEXANT, USB_PID_MYGICA_T230C2,
		&mygica_t230c_props, "MyGica Mini DVB-(T/T2/C) USB Stick T230C v2",
		RC_MAP_TOTAL_MEDIA_IN_HAND_02) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, dvbsky_id_table);

अटल काष्ठा usb_driver dvbsky_usb_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = dvbsky_id_table,
	.probe = dvb_usbv2_probe,
	.disconnect = dvb_usbv2_disconnect,
	.suspend = dvb_usbv2_suspend,
	.resume = dvb_usbv2_resume,
	.reset_resume = dvb_usbv2_reset_resume,
	.no_dynamic_id = 1,
	.soft_unbind = 1,
पूर्ण;

module_usb_driver(dvbsky_usb_driver);

MODULE_AUTHOR("Max nibble <nibble.max@gmail.com>");
MODULE_DESCRIPTION("Driver for DVBSky USB");
MODULE_LICENSE("GPL");
