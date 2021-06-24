<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant linux driver क्रम MSI Mega Sky 580 DVB-T USB2.0 receiver
 *
 * Copyright (C) 2006 Aapo Tahkola (aet@rasterburn.org)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#समावेश "m920x.h"

#समावेश "mt352.h"
#समावेश "mt352_priv.h"
#समावेश "qt1010.h"
#समावेश "tda1004x.h"
#समावेश "tda827x.h"
#समावेश "mt2060.h"

#समावेश <media/tuner.h>
#समावेश "tuner-simple.h"
#समावेश <यंत्र/unaligned.h>

/* debug */
अटल पूर्णांक dvb_usb_m920x_debug;
module_param_named(debug,dvb_usb_m920x_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=rc (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

अटल पूर्णांक m920x_set_filter(काष्ठा dvb_usb_device *d, पूर्णांक type, पूर्णांक idx, पूर्णांक pid);

अटल अंतरभूत पूर्णांक m920x_पढ़ो(काष्ठा usb_device *udev, u8 request, u16 value,
			     u16 index, व्योम *data, पूर्णांक size)
अणु
	पूर्णांक ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      request, USB_TYPE_VENDOR | USB_सूची_IN,
			      value, index, data, size, 2000);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_INFO "m920x_read = error: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ret != size) अणु
		deb("m920x_read = no data\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक m920x_ग_लिखो(काष्ठा usb_device *udev, u8 request,
			      u16 value, u16 index)
अणु
	वापस usb_control_msg(udev, usb_sndctrlpipe(udev, 0), request,
			       USB_TYPE_VENDOR | USB_सूची_OUT, value, index,
			       शून्य, 0, 2000);
पूर्ण

अटल अंतरभूत पूर्णांक m920x_ग_लिखो_seq(काष्ठा usb_device *udev, u8 request,
				  काष्ठा m920x_inits *seq)
अणु
	पूर्णांक ret;
	करो अणु
		ret = m920x_ग_लिखो(udev, request, seq->data, seq->address);
		अगर (ret != 0)
			वापस ret;

		seq++;
	पूर्ण जबतक (seq->address);

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_init(काष्ठा dvb_usb_device *d, काष्ठा m920x_inits *rc_seq)
अणु
	पूर्णांक ret, i, epi, flags = 0;
	पूर्णांक adap_enabled[M9206_MAX_ADAPTERS] = अणु 0 पूर्ण;

	/* Remote controller init. */
	अगर (d->props.rc.legacy.rc_query || d->props.rc.core.rc_query) अणु
		deb("Initialising remote control\n");
		ret = m920x_ग_लिखो_seq(d->udev, M9206_CORE, rc_seq);
		अगर (ret != 0) अणु
			deb("Initialising remote control failed\n");
			वापस ret;
		पूर्ण

		deb("Initialising remote control success\n");
	पूर्ण

	क्रम (i = 0; i < d->props.num_adapters; i++)
		flags |= d->adapter[i].props.fe[0].caps;

	/* Some devices(Dposh) might crash अगर we attempt touch at all. */
	अगर (flags & DVB_USB_ADAP_HAS_PID_FILTER) अणु
		क्रम (i = 0; i < d->props.num_adapters; i++) अणु
			epi = d->adapter[i].props.fe[0].stream.endpoपूर्णांक - 0x81;

			अगर (epi < 0 || epi >= M9206_MAX_ADAPTERS) अणु
				prपूर्णांकk(KERN_INFO "m920x: Unexpected adapter endpoint!\n");
				वापस -EINVAL;
			पूर्ण

			adap_enabled[epi] = 1;
		पूर्ण

		क्रम (i = 0; i < M9206_MAX_ADAPTERS; i++) अणु
			अगर (adap_enabled[i])
				जारी;

			अगर ((ret = m920x_set_filter(d, 0x81 + i, 0, 0x0)) != 0)
				वापस ret;

			अगर ((ret = m920x_set_filter(d, 0x81 + i, 0, 0x02f5)) != 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_init_ep(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *alt;

	अगर ((alt = usb_altnum_to_altsetting(पूर्णांकf, 1)) == शून्य) अणु
		deb("No alt found!\n");
		वापस -ENODEV;
	पूर्ण

	वापस usb_set_पूर्णांकerface(udev, alt->desc.bInterfaceNumber,
				 alt->desc.bAlternateSetting);
पूर्ण

अटल अंतरभूत व्योम m920x_parse_rc_state(काष्ठा dvb_usb_device *d, u8 rc_state,
					पूर्णांक *state)
अणु
	काष्ठा m920x_state *m = d->priv;

	चयन (rc_state) अणु
	हाल 0x80:
		*state = REMOTE_NO_KEY_PRESSED;
		अवरोध;

	हाल 0x88: /* framing error or "invalid code" */
	हाल 0x99:
	हाल 0xc0:
	हाल 0xd8:
		*state = REMOTE_NO_KEY_PRESSED;
		m->rep_count = 0;
		अवरोध;

	हाल 0x93:
	हाल 0x92:
	हाल 0x83: /* pinnacle PCTV310e */
	हाल 0x82:
		m->rep_count = 0;
		*state = REMOTE_KEY_PRESSED;
		अवरोध;

	हाल 0x91:
	हाल 0x81: /* pinnacle PCTV310e */
		/* prevent immediate स्वतः-repeat */
		अगर (++m->rep_count > 2)
			*state = REMOTE_KEY_REPEAT;
		अन्यथा
			*state = REMOTE_NO_KEY_PRESSED;
		अवरोध;

	शेष:
		deb("Unexpected rc state %02x\n", rc_state);
		*state = REMOTE_NO_KEY_PRESSED;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक m920x_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
	पूर्णांक i, ret = 0;
	u8 *rc_state;

	rc_state = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!rc_state)
		वापस -ENOMEM;

	ret = m920x_पढ़ो(d->udev, M9206_CORE, 0x0, M9206_RC_STATE,
			 rc_state, 1);
	अगर (ret != 0)
		जाओ out;

	ret = m920x_पढ़ो(d->udev, M9206_CORE, 0x0, M9206_RC_KEY,
			 rc_state + 1, 1);
	अगर (ret != 0)
		जाओ out;

	m920x_parse_rc_state(d, rc_state[0], state);

	क्रम (i = 0; i < d->props.rc.legacy.rc_map_size; i++)
		अगर (rc5_data(&d->props.rc.legacy.rc_map_table[i]) == rc_state[1]) अणु
			*event = d->props.rc.legacy.rc_map_table[i].keycode;
			जाओ out;
		पूर्ण

	अगर (rc_state[1] != 0)
		deb("Unknown rc key %02x\n", rc_state[1]);

	*state = REMOTE_NO_KEY_PRESSED;

 out:
	kमुक्त(rc_state);
	वापस ret;
पूर्ण

अटल पूर्णांक m920x_rc_core_query(काष्ठा dvb_usb_device *d)
अणु
	पूर्णांक ret = 0;
	u8 *rc_state;
	पूर्णांक state;

	rc_state = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!rc_state)
		वापस -ENOMEM;

	अगर ((ret = m920x_पढ़ो(d->udev, M9206_CORE, 0x0, M9206_RC_STATE, &rc_state[0], 1)) != 0)
		जाओ out;

	अगर ((ret = m920x_पढ़ो(d->udev, M9206_CORE, 0x0, M9206_RC_KEY, &rc_state[1], 1)) != 0)
		जाओ out;

	deb("state=0x%02x keycode=0x%02x\n", rc_state[0], rc_state[1]);

	m920x_parse_rc_state(d, rc_state[0], &state);

	अगर (state == REMOTE_NO_KEY_PRESSED)
		rc_keyup(d->rc_dev);
	अन्यथा अगर (state == REMOTE_KEY_REPEAT)
		rc_repeat(d->rc_dev);
	अन्यथा
		rc_keyकरोwn(d->rc_dev, RC_PROTO_UNKNOWN, rc_state[1], 0);

out:
	kमुक्त(rc_state);
	वापस ret;
पूर्ण

/* I2C */
अटल पूर्णांक m920x_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0)
		वापस -EAGAIN;

	क्रम (i = 0; i < num; i++) अणु
		अगर (msg[i].flags & (I2C_M_NO_RD_ACK | I2C_M_IGNORE_NAK | I2C_M_TEN) || msg[i].len == 0) अणु
			/* For a 0 byte message, I think sending the address
			 * to index 0x80|0x40 would be the correct thing to
			 * करो.  However, zero byte messages are only used क्रम
			 * probing, and since we करोn't know how to get the
			 * slave's ack, we can't probe. */
			ret = -ENOTSUPP;
			जाओ unlock;
		पूर्ण
		/* Send START & address/RW bit */
		अगर (!(msg[i].flags & I2C_M_NOSTART)) अणु
			अगर ((ret = m920x_ग_लिखो(d->udev, M9206_I2C,
					(msg[i].addr << 1) |
					(msg[i].flags & I2C_M_RD ? 0x01 : 0), 0x80)) != 0)
				जाओ unlock;
			/* Should check क्रम ack here, अगर we knew how. */
		पूर्ण
		अगर (msg[i].flags & I2C_M_RD) अणु
			क्रम (j = 0; j < msg[i].len; j++) अणु
				/* Last byte of transaction?
				 * Send STOP, otherwise send ACK. */
				पूर्णांक stop = (i+1 == num && j+1 == msg[i].len) ? 0x40 : 0x01;

				अगर ((ret = m920x_पढ़ो(d->udev, M9206_I2C, 0x0,
						      0x20 | stop,
						      &msg[i].buf[j], 1)) != 0)
					जाओ unlock;
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < msg[i].len; j++) अणु
				/* Last byte of transaction? Then send STOP. */
				पूर्णांक stop = (i+1 == num && j+1 == msg[i].len) ? 0x40 : 0x00;

				अगर ((ret = m920x_ग_लिखो(d->udev, M9206_I2C, msg[i].buf[j], stop)) != 0)
					जाओ unlock;
				/* Should check क्रम ack here too. */
			पूर्ण
		पूर्ण
	पूर्ण
	ret = num;

 unlock:
	mutex_unlock(&d->i2c_mutex);

	वापस ret;
पूर्ण

अटल u32 m920x_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm m920x_i2c_algo = अणु
	.master_xfer   = m920x_i2c_xfer,
	.functionality = m920x_i2c_func,
पूर्ण;

/* pid filter */
अटल पूर्णांक m920x_set_filter(काष्ठा dvb_usb_device *d, पूर्णांक type, पूर्णांक idx, पूर्णांक pid)
अणु
	पूर्णांक ret = 0;

	अगर (pid >= 0x8000)
		वापस -EINVAL;

	pid |= 0x8000;

	अगर ((ret = m920x_ग_लिखो(d->udev, M9206_FILTER, pid, (type << 8) | (idx * 4) )) != 0)
		वापस ret;

	अगर ((ret = m920x_ग_लिखो(d->udev, M9206_FILTER, 0, (type << 8) | (idx * 4) )) != 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक m920x_update_filters(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा m920x_state *m = adap->dev->priv;
	पूर्णांक enabled = m->filtering_enabled[adap->id];
	पूर्णांक i, ret = 0, filter = 0;
	पूर्णांक ep = adap->props.fe[0].stream.endpoपूर्णांक;

	क्रम (i = 0; i < M9206_MAX_FILTERS; i++)
		अगर (m->filters[adap->id][i] == 8192)
			enabled = 0;

	/* Disable all filters */
	अगर ((ret = m920x_set_filter(adap->dev, ep, 1, enabled)) != 0)
		वापस ret;

	क्रम (i = 0; i < M9206_MAX_FILTERS; i++)
		अगर ((ret = m920x_set_filter(adap->dev, ep, i + 2, 0)) != 0)
			वापस ret;

	/* Set */
	अगर (enabled) अणु
		क्रम (i = 0; i < M9206_MAX_FILTERS; i++) अणु
			अगर (m->filters[adap->id][i] == 0)
				जारी;

			अगर ((ret = m920x_set_filter(adap->dev, ep, filter + 2, m->filters[adap->id][i])) != 0)
				वापस ret;

			filter++;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक m920x_pid_filter_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	काष्ठा m920x_state *m = adap->dev->priv;

	m->filtering_enabled[adap->id] = onoff ? 1 : 0;

	वापस m920x_update_filters(adap);
पूर्ण

अटल पूर्णांक m920x_pid_filter(काष्ठा dvb_usb_adapter *adap, पूर्णांक index, u16 pid, पूर्णांक onoff)
अणु
	काष्ठा m920x_state *m = adap->dev->priv;

	m->filters[adap->id][index] = onoff ? pid : 0;

	वापस m920x_update_filters(adap);
पूर्ण

अटल पूर्णांक m920x_firmware_करोwnload(काष्ठा usb_device *udev, स्थिर काष्ठा firmware *fw)
अणु
	u16 value, index, size;
	u8 *पढ़ो, *buff;
	पूर्णांक i, pass, ret = 0;

	buff = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (buff == शून्य)
		वापस -ENOMEM;

	पढ़ो = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!पढ़ो) अणु
		kमुक्त(buff);
		वापस -ENOMEM;
	पूर्ण

	अगर ((ret = m920x_पढ़ो(udev, M9206_FILTER, 0x0, 0x8000, पढ़ो, 4)) != 0)
		जाओ करोne;
	deb("%*ph\n", 4, पढ़ो);

	अगर ((ret = m920x_पढ़ो(udev, M9206_FW, 0x0, 0x0, पढ़ो, 1)) != 0)
		जाओ करोne;
	deb("%x\n", पढ़ो[0]);

	क्रम (pass = 0; pass < 2; pass++) अणु
		क्रम (i = 0; i + (माप(u16) * 3) < fw->size;) अणु
			value = get_unaligned_le16(fw->data + i);
			i += माप(u16);

			index = get_unaligned_le16(fw->data + i);
			i += माप(u16);

			size = get_unaligned_le16(fw->data + i);
			i += माप(u16);

			अगर (pass == 1) अणु
				/* Will stall अगर using fw->data ... */
				स_नकल(buff, fw->data + i, size);

				ret = usb_control_msg(udev, usb_sndctrlpipe(udev,0),
						      M9206_FW,
						      USB_TYPE_VENDOR | USB_सूची_OUT,
						      value, index, buff, size, 20);
				अगर (ret != size) अणु
					deb("error while uploading fw!\n");
					ret = -EIO;
					जाओ करोne;
				पूर्ण
				msleep(3);
			पूर्ण
			i += size;
		पूर्ण
		अगर (i != fw->size) अणु
			deb("bad firmware file!\n");
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण

	msleep(36);

	/* m920x will disconnect itself from the bus after this. */
	(व्योम) m920x_ग_लिखो(udev, M9206_CORE, 0x01, M9206_FW_GO);
	deb("firmware uploaded!\n");

 करोne:
	kमुक्त(पढ़ो);
	kमुक्त(buff);

	वापस ret;
पूर्ण

/* Callbacks क्रम DVB USB */
अटल पूर्णांक m920x_identअगरy_state(काष्ठा usb_device *udev,
				स्थिर काष्ठा dvb_usb_device_properties *props,
				स्थिर काष्ठा dvb_usb_device_description **desc,
				पूर्णांक *cold)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;

	alt = usb_altnum_to_altsetting(usb_अगरnum_to_अगर(udev, 0), 1);
	*cold = (alt == शून्य) ? 1 : 0;

	वापस 0;
पूर्ण

/* demod configurations */
अटल पूर्णांक m920x_mt352_demod_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	u8 config[] = अणु CONFIG, 0x3d पूर्ण;
	u8 घड़ी[] = अणु CLOCK_CTL, 0x30 पूर्ण;
	u8 reset[] = अणु RESET, 0x80 पूर्ण;
	u8 adc_ctl[] = अणु ADC_CTL_1, 0x40 पूर्ण;
	u8 agc[] = अणु AGC_TARGET, 0x1c, 0x20 पूर्ण;
	u8 sec_agc[] = अणु 0x69, 0x00, 0xff, 0xff, 0x40, 0xff, 0x00, 0x40, 0x40 पूर्ण;
	u8 unk1[] = अणु 0x93, 0x1a पूर्ण;
	u8 unk2[] = अणु 0xb5, 0x7a पूर्ण;

	deb("Demod init!\n");

	अगर ((ret = mt352_ग_लिखो(fe, config, ARRAY_SIZE(config))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, घड़ी, ARRAY_SIZE(घड़ी))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, reset, ARRAY_SIZE(reset))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, adc_ctl, ARRAY_SIZE(adc_ctl))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, agc, ARRAY_SIZE(agc))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, sec_agc, ARRAY_SIZE(sec_agc))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, unk1, ARRAY_SIZE(unk1))) != 0)
		वापस ret;
	अगर ((ret = mt352_ग_लिखो(fe, unk2, ARRAY_SIZE(unk2))) != 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा mt352_config m920x_mt352_config = अणु
	.demod_address = 0x0f,
	.no_tuner = 1,
	.demod_init = m920x_mt352_demod_init,
पूर्ण;

अटल काष्ठा tda1004x_config m920x_tda10046_08_config = अणु
	.demod_address = 0x08,
	.invert = 0,
	.invert_oclk = 0,
	.ts_mode = TDA10046_TS_SERIAL,
	.xtal_freq = TDA10046_XTAL_16M,
	.अगर_freq = TDA10046_FREQ_045,
	.agc_config = TDA10046_AGC_TDA827X,
	.gpio_config = TDA10046_GPTRI,
	.request_firmware = शून्य,
पूर्ण;

अटल काष्ठा tda1004x_config m920x_tda10046_0b_config = अणु
	.demod_address = 0x0b,
	.invert = 0,
	.invert_oclk = 0,
	.ts_mode = TDA10046_TS_SERIAL,
	.xtal_freq = TDA10046_XTAL_16M,
	.अगर_freq = TDA10046_FREQ_045,
	.agc_config = TDA10046_AGC_TDA827X,
	.gpio_config = TDA10046_GPTRI,
	.request_firmware = शून्य, /* uses firmware EEPROM */
पूर्ण;

/* tuner configurations */
अटल काष्ठा qt1010_config m920x_qt1010_config = अणु
	.i2c_address = 0x62
पूर्ण;

अटल काष्ठा mt2060_config m920x_mt2060_config = अणु
	.i2c_address = 0x60, /* 0xc0 */
	.घड़ी_out = 0,
पूर्ण;


/* Callbacks क्रम DVB USB */
अटल पूर्णांक m920x_mt352_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(mt352_attach,
					 &m920x_mt352_config,
					 &adap->dev->i2c_adap);
	अगर ((adap->fe_adap[0].fe) == शून्य)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_mt352_frontend_attach_vp7049(काष्ठा dvb_usb_adapter *adap)
अणु
	काष्ठा m920x_inits vp7049_fe_init_seq[] = अणु
		/* XXX without these commands the frontend cannot be detected,
		 * they must be sent BEFORE the frontend is attached */
		अणु 0xff28,         0x00 पूर्ण,
		अणु 0xff23,         0x00 पूर्ण,
		अणु 0xff28,         0x00 पूर्ण,
		अणु 0xff23,         0x00 पूर्ण,
		अणु 0xff21,         0x20 पूर्ण,
		अणु 0xff21,         0x60 पूर्ण,
		अणु 0xff28,         0x00 पूर्ण,
		अणु 0xff22,         0x00 पूर्ण,
		अणु 0xff20,         0x30 पूर्ण,
		अणु 0xff20,         0x20 पूर्ण,
		अणु 0xff20,         0x30 पूर्ण,
		अणु पूर्ण /* terminating entry */
	पूर्ण;
	पूर्णांक ret;

	deb("%s\n", __func__);

	ret = m920x_ग_लिखो_seq(adap->dev->udev, M9206_CORE, vp7049_fe_init_seq);
	अगर (ret != 0) अणु
		deb("Initialization of vp7049 frontend failed.");
		वापस ret;
	पूर्ण

	वापस m920x_mt352_frontend_attach(adap);
पूर्ण

अटल पूर्णांक m920x_tda10046_08_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(tda10046_attach,
					 &m920x_tda10046_08_config,
					 &adap->dev->i2c_adap);
	अगर ((adap->fe_adap[0].fe) == शून्य)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_tda10046_0b_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	adap->fe_adap[0].fe = dvb_attach(tda10046_attach,
					 &m920x_tda10046_0b_config,
					 &adap->dev->i2c_adap);
	अगर ((adap->fe_adap[0].fe) == शून्य)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_qt1010_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	अगर (dvb_attach(qt1010_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap, &m920x_qt1010_config) == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_tda8275_60_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	अगर (dvb_attach(tda827x_attach, adap->fe_adap[0].fe, 0x60, &adap->dev->i2c_adap, शून्य) == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_tda8275_61_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n",__func__);

	अगर (dvb_attach(tda827x_attach, adap->fe_adap[0].fe, 0x61, &adap->dev->i2c_adap, शून्य) == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक m920x_fmd1216me_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	dvb_attach(simple_tuner_attach, adap->fe_adap[0].fe,
		   &adap->dev->i2c_adap, 0x61,
		   TUNER_PHILIPS_FMD1216ME_MK3);
	वापस 0;
पूर्ण

अटल पूर्णांक m920x_mt2060_tuner_attach(काष्ठा dvb_usb_adapter *adap)
अणु
	deb("%s\n", __func__);

	अगर (dvb_attach(mt2060_attach, adap->fe_adap[0].fe, &adap->dev->i2c_adap,
		       &m920x_mt2060_config, 1220) == शून्य)
		वापस -ENODEV;

	वापस 0;
पूर्ण


/* device-specअगरic initialization */
अटल काष्ठा m920x_inits megasky_rc_init [] = अणु
	अणु M9206_RC_INIT2, 0xa8 पूर्ण,
	अणु M9206_RC_INIT1, 0x51 पूर्ण,
	अणु पूर्ण /* terminating entry */
पूर्ण;

अटल काष्ठा m920x_inits tvwalkertwin_rc_init [] = अणु
	अणु M9206_RC_INIT2, 0x00 पूर्ण,
	अणु M9206_RC_INIT1, 0xef पूर्ण,
	अणु 0xff28,         0x00 पूर्ण,
	अणु 0xff23,         0x00 पूर्ण,
	अणु 0xff21,         0x30 पूर्ण,
	अणु पूर्ण /* terminating entry */
पूर्ण;

अटल काष्ठा m920x_inits pinnacle310e_init[] = अणु
	/* without these the tuner करोesn't work */
	अणु 0xff20,         0x9b पूर्ण,
	अणु 0xff22,         0x70 पूर्ण,

	/* rc settings */
	अणु 0xff50,         0x80 पूर्ण,
	अणु M9206_RC_INIT1, 0x00 पूर्ण,
	अणु M9206_RC_INIT2, 0xff पूर्ण,
	अणु पूर्ण /* terminating entry */
पूर्ण;

अटल काष्ठा m920x_inits vp7049_rc_init[] = अणु
	अणु 0xff28,         0x00 पूर्ण,
	अणु 0xff23,         0x00 पूर्ण,
	अणु 0xff21,         0x70 पूर्ण,
	अणु M9206_RC_INIT2, 0x00 पूर्ण,
	अणु M9206_RC_INIT1, 0xff पूर्ण,
	अणु पूर्ण /* terminating entry */
पूर्ण;

/* ir keymaps */
अटल काष्ठा rc_map_table rc_map_megasky_table[] = अणु
	अणु 0x0012, KEY_POWER पूर्ण,
	अणु 0x001e, KEY_CYCLEWINDOWS पूर्ण, /* min/max */
	अणु 0x0002, KEY_CHANNELUP पूर्ण,
	अणु 0x0005, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0003, KEY_VOLUMEUP पूर्ण,
	अणु 0x0006, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0004, KEY_MUTE पूर्ण,
	अणु 0x0007, KEY_OK पूर्ण, /* TS */
	अणु 0x0008, KEY_STOP पूर्ण,
	अणु 0x0009, KEY_MENU पूर्ण, /* swap */
	अणु 0x000a, KEY_REWIND पूर्ण,
	अणु 0x001b, KEY_PAUSE पूर्ण,
	अणु 0x001f, KEY_FASTFORWARD पूर्ण,
	अणु 0x000c, KEY_RECORD पूर्ण,
	अणु 0x000d, KEY_CAMERA पूर्ण, /* screenshot */
	अणु 0x000e, KEY_COFFEE पूर्ण, /* "MTS" */
पूर्ण;

अटल काष्ठा rc_map_table rc_map_tvwalkertwin_table[] = अणु
	अणु 0x0001, KEY_ZOOM पूर्ण, /* Full Screen */
	अणु 0x0002, KEY_CAMERA पूर्ण, /* snapshot */
	अणु 0x0003, KEY_MUTE पूर्ण,
	अणु 0x0004, KEY_REWIND पूर्ण,
	अणु 0x0005, KEY_PLAYPAUSE पूर्ण, /* Play/Pause */
	अणु 0x0006, KEY_FASTFORWARD पूर्ण,
	अणु 0x0007, KEY_RECORD पूर्ण,
	अणु 0x0008, KEY_STOP पूर्ण,
	अणु 0x0009, KEY_TIME पूर्ण, /* Timeshअगरt */
	अणु 0x000c, KEY_COFFEE पूर्ण, /* Recall */
	अणु 0x000e, KEY_CHANNELUP पूर्ण,
	अणु 0x0012, KEY_POWER पूर्ण,
	अणु 0x0015, KEY_MENU पूर्ण, /* source */
	अणु 0x0018, KEY_CYCLEWINDOWS पूर्ण, /* TWIN PIP */
	अणु 0x001a, KEY_CHANNELDOWN पूर्ण,
	अणु 0x001b, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x001e, KEY_VOLUMEUP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_table rc_map_pinnacle310e_table[] = अणु
	अणु 0x16, KEY_POWER पूर्ण,
	अणु 0x17, KEY_FAVORITES पूर्ण,
	अणु 0x0f, KEY_TEXT पूर्ण,
	अणु 0x48, KEY_PROGRAM पूर्ण,		/* preview */
	अणु 0x1c, KEY_EPG पूर्ण,
	अणु 0x04, KEY_LIST पूर्ण,		/* record list */
	अणु 0x03, KEY_1 पूर्ण,
	अणु 0x01, KEY_2 पूर्ण,
	अणु 0x06, KEY_3 पूर्ण,
	अणु 0x09, KEY_4 पूर्ण,
	अणु 0x1d, KEY_5 पूर्ण,
	अणु 0x1f, KEY_6 पूर्ण,
	अणु 0x0d, KEY_7 पूर्ण,
	अणु 0x19, KEY_8 पूर्ण,
	अणु 0x1b, KEY_9 पूर्ण,
	अणु 0x15, KEY_0 पूर्ण,
	अणु 0x0c, KEY_CANCEL पूर्ण,
	अणु 0x4a, KEY_CLEAR पूर्ण,
	अणु 0x13, KEY_BACK पूर्ण,
	अणु 0x00, KEY_TAB पूर्ण,
	अणु 0x4b, KEY_UP पूर्ण,
	अणु 0x4e, KEY_LEFT पूर्ण,
	अणु 0x52, KEY_RIGHT पूर्ण,
	अणु 0x51, KEY_DOWN पूर्ण,
	अणु 0x4f, KEY_ENTER पूर्ण,		/* could also be KEY_OK */
	अणु 0x1e, KEY_VOLUMEUP पूर्ण,
	अणु 0x0a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x05, KEY_CHANNELUP पूर्ण,
	अणु 0x02, KEY_CHANNELDOWN पूर्ण,
	अणु 0x11, KEY_RECORD पूर्ण,
	अणु 0x14, KEY_PLAY पूर्ण,
	अणु 0x4c, KEY_PAUSE पूर्ण,
	अणु 0x1a, KEY_STOP पूर्ण,
	अणु 0x40, KEY_REWIND पूर्ण,
	अणु 0x12, KEY_FASTFORWARD पूर्ण,
	अणु 0x41, KEY_PREVIOUSSONG पूर्ण,	/* Replay */
	अणु 0x42, KEY_NEXTSONG पूर्ण,		/* Skip */
	अणु 0x54, KEY_CAMERA पूर्ण,		/* Capture */
/*	अणु 0x50, KEY_SAP पूर्ण,	*/		/* Sap */
	अणु 0x47, KEY_CYCLEWINDOWS पूर्ण,	/* Pip */
	अणु 0x4d, KEY_SCREEN पूर्ण,		/* FullScreen */
	अणु 0x08, KEY_SUBTITLE पूर्ण,
	अणु 0x0e, KEY_MUTE पूर्ण,
/*	अणु 0x49, KEY_LR पूर्ण,	*/		/* L/R */
	अणु 0x07, KEY_SLEEP पूर्ण,		/* Hibernate */
	अणु 0x08, KEY_VIDEO पूर्ण,		/* A/V */
	अणु 0x0e, KEY_MENU पूर्ण,		/* Recall */
	अणु 0x45, KEY_ZOOMIN पूर्ण,
	अणु 0x46, KEY_ZOOMOUT पूर्ण,
	अणु 0x18, KEY_RED पूर्ण,		/* Red */
	अणु 0x53, KEY_GREEN पूर्ण,		/* Green */
	अणु 0x5e, KEY_YELLOW पूर्ण,		/* Yellow */
	अणु 0x5f, KEY_BLUE पूर्ण,		/* Blue */
पूर्ण;

/* DVB USB Driver stuff */
अटल काष्ठा dvb_usb_device_properties megasky_properties;
अटल काष्ठा dvb_usb_device_properties digivox_mini_ii_properties;
अटल काष्ठा dvb_usb_device_properties tvwalkertwin_properties;
अटल काष्ठा dvb_usb_device_properties dposh_properties;
अटल काष्ठा dvb_usb_device_properties pinnacle_pctv310e_properties;
अटल काष्ठा dvb_usb_device_properties vp7049_properties;

अटल पूर्णांक m920x_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा dvb_usb_device *d = शून्य;
	पूर्णांक ret;
	काष्ठा m920x_inits *rc_init_seq = शून्य;
	पूर्णांक bInterfaceNumber = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;

	deb("Probing for m920x device at interface %d\n", bInterfaceNumber);

	अगर (bInterfaceNumber == 0) अणु
		/* Single-tuner device, or first पूर्णांकerface on
		 * multi-tuner device
		 */

		ret = dvb_usb_device_init(पूर्णांकf, &megasky_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			rc_init_seq = megasky_rc_init;
			जाओ found;
		पूर्ण

		ret = dvb_usb_device_init(पूर्णांकf, &digivox_mini_ii_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			/* No remote control, so no rc_init_seq */
			जाओ found;
		पूर्ण

		/* This configures both tuners on the TV Walker Twin */
		ret = dvb_usb_device_init(पूर्णांकf, &tvwalkertwin_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			rc_init_seq = tvwalkertwin_rc_init;
			जाओ found;
		पूर्ण

		ret = dvb_usb_device_init(पूर्णांकf, &dposh_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			/* Remote controller not supported yet. */
			जाओ found;
		पूर्ण

		ret = dvb_usb_device_init(पूर्णांकf, &pinnacle_pctv310e_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			rc_init_seq = pinnacle310e_init;
			जाओ found;
		पूर्ण

		ret = dvb_usb_device_init(पूर्णांकf, &vp7049_properties,
					  THIS_MODULE, &d, adapter_nr);
		अगर (ret == 0) अणु
			rc_init_seq = vp7049_rc_init;
			जाओ found;
		पूर्ण

		वापस ret;
	पूर्ण अन्यथा अणु
		/* Another पूर्णांकerface on a multi-tuner device */

		/* The LअगरeView TV Walker Twin माला_लो here, but काष्ठा
		 * tvwalkertwin_properties alपढ़ोy configured both
		 * tuners, so there is nothing क्रम us to करो here
		 */
	पूर्ण

 found:
	अगर ((ret = m920x_init_ep(पूर्णांकf)) < 0)
		वापस ret;

	अगर (d && (ret = m920x_init(d, rc_init_seq)) != 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल काष्ठा usb_device_id m920x_table [] = अणु
		अणु USB_DEVICE(USB_VID_MSI, USB_PID_MSI_MEGASKY580) पूर्ण,
		अणु USB_DEVICE(USB_VID_ANUBIS_ELECTRONIC,
			     USB_PID_MSI_DIGI_VOX_MINI_II) पूर्ण,
		अणु USB_DEVICE(USB_VID_ANUBIS_ELECTRONIC,
			     USB_PID_LIFEVIEW_TV_WALKER_TWIN_COLD) पूर्ण,
		अणु USB_DEVICE(USB_VID_ANUBIS_ELECTRONIC,
			     USB_PID_LIFEVIEW_TV_WALKER_TWIN_WARM) पूर्ण,
		अणु USB_DEVICE(USB_VID_DPOSH, USB_PID_DPOSH_M9206_COLD) पूर्ण,
		अणु USB_DEVICE(USB_VID_DPOSH, USB_PID_DPOSH_M9206_WARM) पूर्ण,
		अणु USB_DEVICE(USB_VID_VISIONPLUS, USB_PID_PINNACLE_PCTV310E) पूर्ण,
		अणु USB_DEVICE(USB_VID_AZUREWAVE, USB_PID_TWINHAN_VP7049) पूर्ण,
		अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE (usb, m920x_table);

अटल काष्ठा dvb_usb_device_properties megasky_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "dvb-usb-megasky-02.fw",
	.करोwnload_firmware = m920x_firmware_करोwnload,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = 100,
		.rc_map_table     = rc_map_megasky_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_megasky_table),
		.rc_query         = m920x_rc_query,
	पूर्ण,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_mt352_frontend_attach,
		.tuner_attach     = m920x_qt1010_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x81,
			.u = अणु
				.bulk = अणु
					.buffersize = 512,
				पूर्ण
			पूर्ण
		पूर्ण,
		पूर्णपूर्ण,
	पूर्णपूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "MSI Mega Sky 580 DVB-T USB2.0",
			अणु &m920x_table[0], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties digivox_mini_ii_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "dvb-usb-digivox-02.fw",
	.करोwnload_firmware = m920x_firmware_करोwnload,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_tda10046_08_frontend_attach,
		.tuner_attach     = m920x_tda8275_60_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x81,
			.u = अणु
				.bulk = अणु
					.buffersize = 0x4000,
				पूर्ण
			पूर्ण
		पूर्ण,
		पूर्णपूर्ण,
	पूर्णपूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "MSI DIGI VOX mini II DVB-T USB2.0",
			अणु &m920x_table[1], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

/* LअगरeView TV Walker Twin support by Nick Andrew <nick@nick-andrew.net>
 *
 * LअगरeView TV Walker Twin has 1 x M9206, 2 x TDA10046, 2 x TDA8275A
 * TDA10046 #0 is located at i2c address 0x08
 * TDA10046 #1 is located at i2c address 0x0b
 * TDA8275A #0 is located at i2c address 0x60
 * TDA8275A #1 is located at i2c address 0x61
 */
अटल काष्ठा dvb_usb_device_properties tvwalkertwin_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "dvb-usb-tvwalkert.fw",
	.करोwnload_firmware = m920x_firmware_करोwnload,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = 100,
		.rc_map_table     = rc_map_tvwalkertwin_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_tvwalkertwin_table),
		.rc_query         = m920x_rc_query,
	पूर्ण,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 2,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_tda10046_08_frontend_attach,
		.tuner_attach     = m920x_tda8275_60_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x81,
			.u = अणु
				 .bulk = अणु
					 .buffersize = 512,
				 पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्णपूर्ण,अणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_tda10046_0b_frontend_attach,
		.tuner_attach     = m920x_tda8275_61_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x82,
			.u = अणु
				 .bulk = अणु
					 .buffersize = 512,
				 पूर्ण
			पूर्ण
		पूर्णपूर्ण,
		पूर्ण,
	पूर्णपूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु   .name = "LifeView TV Walker Twin DVB-T USB2.0",
		    .cold_ids = अणु &m920x_table[2], शून्य पूर्ण,
		    .warm_ids = अणु &m920x_table[3], शून्य पूर्ण,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties dposh_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "dvb-usb-dposh-01.fw",
	.करोwnload_firmware = m920x_firmware_करोwnload,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु
		/* Hardware pid filters करोn't work with this device/firmware */

		.frontend_attach  = m920x_mt352_frontend_attach,
		.tuner_attach     = m920x_qt1010_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x81,
			.u = अणु
				 .bulk = अणु
					 .buffersize = 512,
				 पूर्ण
			पूर्ण
		पूर्ण,
		पूर्णपूर्ण,
	पूर्णपूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		 अणु   .name = "Dposh DVB-T USB2.0",
		     .cold_ids = अणु &m920x_table[4], शून्य पूर्ण,
		     .warm_ids = अणु &m920x_table[5], शून्य पूर्ण,
		 पूर्ण,
	 पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties pinnacle_pctv310e_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.करोwnload_firmware = शून्य,

	.rc.legacy = अणु
		.rc_पूर्णांकerval      = 100,
		.rc_map_table     = rc_map_pinnacle310e_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_pinnacle310e_table),
		.rc_query         = m920x_rc_query,
	पूर्ण,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_mt352_frontend_attach,
		.tuner_attach     = m920x_fmd1216me_tuner_attach,

		.stream = अणु
			.type = USB_ISOC,
			.count = 5,
			.endpoपूर्णांक = 0x84,
			.u = अणु
				.isoc = अणु
					.framesperurb = 128,
					.framesize = 564,
					.पूर्णांकerval = 1,
				पूर्ण
			पूर्ण
		पूर्ण,
		पूर्णपूर्ण,
	पूर्ण पूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "Pinnacle PCTV 310e",
			अणु &m920x_table[6], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dvb_usb_device_properties vp7049_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,

	.usb_ctrl = DEVICE_SPECIFIC,
	.firmware = "dvb-usb-vp7049-0.95.fw",
	.करोwnload_firmware = m920x_firmware_करोwnload,

	.rc.core = अणु
		.rc_पूर्णांकerval    = 150,
		.rc_codes       = RC_MAP_TWINHAN_VP1027_DVBS,
		.rc_query       = m920x_rc_core_query,
		.allowed_protos = RC_PROTO_BIT_UNKNOWN,
	पूर्ण,

	.size_of_priv     = माप(काष्ठा m920x_state),

	.identअगरy_state   = m920x_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणुअणु
		.num_frontends = 1,
		.fe = अणुअणु

		.caps = DVB_USB_ADAP_HAS_PID_FILTER |
			DVB_USB_ADAP_PID_FILTER_CAN_BE_TURNED_OFF,

		.pid_filter_count = 8,
		.pid_filter       = m920x_pid_filter,
		.pid_filter_ctrl  = m920x_pid_filter_ctrl,

		.frontend_attach  = m920x_mt352_frontend_attach_vp7049,
		.tuner_attach     = m920x_mt2060_tuner_attach,

		.stream = अणु
			.type = USB_BULK,
			.count = 8,
			.endpoपूर्णांक = 0x81,
			.u = अणु
				 .bulk = अणु
					 .buffersize = 512,
				 पूर्ण
			पूर्ण
		पूर्ण,
		पूर्ण पूर्ण,
	पूर्ण पूर्ण,
	.i2c_algo         = &m920x_i2c_algo,

	.num_device_descs = 1,
	.devices = अणु
		अणु   "DTV-DVB UDTT7049",
			अणु &m920x_table[7], शून्य पूर्ण,
			अणु शून्य पूर्ण,
		पूर्ण
	 पूर्ण
पूर्ण;

अटल काष्ठा usb_driver m920x_driver = अणु
	.name		= "dvb_usb_m920x",
	.probe		= m920x_probe,
	.disconnect	= dvb_usb_device_निकास,
	.id_table	= m920x_table,
पूर्ण;

module_usb_driver(m920x_driver);

MODULE_AUTHOR("Aapo Tahkola <aet@rasterburn.org>");
MODULE_DESCRIPTION("DVB Driver for ULI M920x");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
