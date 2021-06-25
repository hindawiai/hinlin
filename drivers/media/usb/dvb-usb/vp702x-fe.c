<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB frontend part of the Linux driver क्रम the TwinhanDTV StarBox USB2.0
 * DVB-S receiver.
 *
 * Copyright (C) 2005 Ralph Metzler <rjkm@metzlerbros.de>
 *                    Metzler Brothers Systementwicklung GbR
 *
 * Copyright (C) 2005 Patrick Boettcher <patrick.boettcher@posteo.de>
 *
 * Thanks to Twinhan who kindly provided hardware and inक्रमmation.
 *
 * This file can be हटाओd soon, after the DST-driver is rewritten to provice
 * the frontend-controlling separately.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "vp702x.h"

काष्ठा vp702x_fe_state अणु
	काष्ठा dvb_frontend fe;
	काष्ठा dvb_usb_device *d;

	काष्ठा dvb_frontend_ops ops;

	क्रमागत fe_sec_voltage voltage;
	क्रमागत fe_sec_tone_mode tone_mode;

	u8 lnb_buf[8];

	u8 lock;
	u8 sig;
	u8 snr;

	अचिन्हित दीर्घ next_status_check;
	अचिन्हित दीर्घ status_check_पूर्णांकerval;
पूर्ण;

अटल पूर्णांक vp702x_fe_refresh_state(काष्ठा vp702x_fe_state *st)
अणु
	काष्ठा vp702x_device_state *dst = st->d->priv;
	u8 *buf;

	अगर (समय_after(jअगरfies, st->next_status_check)) अणु
		mutex_lock(&dst->buf_mutex);
		buf = dst->buf;

		vp702x_usb_in_op(st->d, READ_STATUS, 0, 0, buf, 10);
		st->lock = buf[4];

		vp702x_usb_in_op(st->d, READ_TUNER_REG_REQ, 0x11, 0, buf, 1);
		st->snr = buf[0];

		vp702x_usb_in_op(st->d, READ_TUNER_REG_REQ, 0x15, 0, buf, 1);
		st->sig = buf[0];

		mutex_unlock(&dst->buf_mutex);
		st->next_status_check = jअगरfies + (st->status_check_पूर्णांकerval*HZ)/1000;
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 vp702x_chksum(u8 *buf,पूर्णांक f, पूर्णांक count)
अणु
	u8 s = 0;
	पूर्णांक i;
	क्रम (i = f; i < f+count; i++)
		s += buf[i];
	वापस ~s+1;
पूर्ण

अटल पूर्णांक vp702x_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);
	deb_fe("%s\n",__func__);

	अगर (st->lock == 0)
		*status = FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI | FE_HAS_SIGNAL | FE_HAS_CARRIER;
	अन्यथा
		*status = 0;

	अगर (*status & FE_HAS_LOCK)
		st->status_check_पूर्णांकerval = 1000;
	अन्यथा
		st->status_check_पूर्णांकerval = 250;
	वापस 0;
पूर्ण

/* not supported by this Frontend */
अटल पूर्णांक vp702x_fe_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32 *ber)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);
	*ber = 0;
	वापस 0;
पूर्ण

/* not supported by this Frontend */
अटल पूर्णांक vp702x_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend* fe, u32 *unc)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);
	*unc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 *strength)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);

	*strength = (st->sig << 8) | st->sig;
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	u8 _snr;
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	vp702x_fe_refresh_state(st);

	_snr = (st->snr & 0x1f) * 0xff / 0x1f;
	*snr = (_snr << 8) | _snr;
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	deb_fe("%s\n",__func__);
	tune->min_delay_ms = 2000;
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fep = &fe->dtv_property_cache;
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	काष्ठा vp702x_device_state *dst = st->d->priv;
	u32 freq = fep->frequency/1000;
	/*CalFrequency*/
/*	u16 frequencyRef[16] = अणु 2, 4, 8, 16, 32, 64, 128, 256, 24, 5, 10, 20, 40, 80, 160, 320 पूर्ण; */
	u64 sr;
	u8 *cmd;

	mutex_lock(&dst->buf_mutex);

	cmd = dst->buf;
	स_रखो(cmd, 0, 10);

	cmd[0] = (freq >> 8) & 0x7f;
	cmd[1] =  freq       & 0xff;
	cmd[2] = 1; /* भागrate == 4 -> frequencyRef[1] -> 1 here */

	sr = (u64) (fep->symbol_rate/1000) << 20;
	करो_भाग(sr,88000);
	cmd[3] = (sr >> 12) & 0xff;
	cmd[4] = (sr >> 4)  & 0xff;
	cmd[5] = (sr << 4)  & 0xf0;

	deb_fe("setting frontend to: %u -> %u (%x) LNB-based GHz, symbolrate: %d -> %lu (%lx)\n",
			fep->frequency, freq, freq, fep->symbol_rate,
			(अचिन्हित दीर्घ) sr, (अचिन्हित दीर्घ) sr);

/*	अगर (fep->inversion == INVERSION_ON)
		cmd[6] |= 0x80; */

	अगर (st->voltage == SEC_VOLTAGE_18)
		cmd[6] |= 0x40;

/*	अगर (fep->symbol_rate > 8000000)
		cmd[6] |= 0x20;

	अगर (fep->frequency < 1531000)
		cmd[6] |= 0x04;

	अगर (st->tone_mode == SEC_TONE_ON)
		cmd[6] |= 0x01;*/

	cmd[7] = vp702x_chksum(cmd,0,7);

	st->status_check_पूर्णांकerval = 250;
	st->next_status_check = jअगरfies;

	vp702x_usb_inout_op(st->d, cmd, 8, cmd, 10, 100);

	अगर (cmd[2] == 0 && cmd[3] == 0)
		deb_fe("tuning failed.\n");
	अन्यथा
		deb_fe("tuning succeeded.\n");

	mutex_unlock(&dst->buf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	deb_fe("%s\n",__func__);
	vp702x_usb_in_op(st->d, RESET_TUNER, 0, 0, शून्य, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	deb_fe("%s\n",__func__);
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_send_diseqc_msg (काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_diseqc_master_cmd *m)
अणु
	u8 *cmd;
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	काष्ठा vp702x_device_state *dst = st->d->priv;

	deb_fe("%s\n",__func__);

	अगर (m->msg_len > 4)
		वापस -EINVAL;

	mutex_lock(&dst->buf_mutex);

	cmd = dst->buf;
	cmd[1] = SET_DISEQC_CMD;
	cmd[2] = m->msg_len;
	स_नकल(&cmd[3], m->msg, m->msg_len);
	cmd[7] = vp702x_chksum(cmd, 0, 7);

	vp702x_usb_inout_op(st->d, cmd, 8, cmd, 10, 100);

	अगर (cmd[2] == 0 && cmd[3] == 0)
		deb_fe("diseqc cmd failed.\n");
	अन्यथा
		deb_fe("diseqc cmd succeeded.\n");

	mutex_unlock(&dst->buf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_mini_cmd burst)
अणु
	deb_fe("%s\n",__func__);
	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_set_tone(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	काष्ठा vp702x_device_state *dst = st->d->priv;
	u8 *buf;

	deb_fe("%s\n",__func__);

	st->tone_mode = tone;

	अगर (tone == SEC_TONE_ON)
		st->lnb_buf[2] = 0x02;
	अन्यथा
		st->lnb_buf[2] = 0x00;

	st->lnb_buf[7] = vp702x_chksum(st->lnb_buf, 0, 7);

	mutex_lock(&dst->buf_mutex);

	buf = dst->buf;
	स_नकल(buf, st->lnb_buf, 8);

	vp702x_usb_inout_op(st->d, buf, 8, buf, 10, 100);
	अगर (buf[2] == 0 && buf[3] == 0)
		deb_fe("set_tone cmd failed.\n");
	अन्यथा
		deb_fe("set_tone cmd succeeded.\n");

	mutex_unlock(&dst->buf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vp702x_fe_set_voltage(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	काष्ठा vp702x_device_state *dst = st->d->priv;
	u8 *buf;
	deb_fe("%s\n",__func__);

	st->voltage = voltage;

	अगर (voltage != SEC_VOLTAGE_OFF)
		st->lnb_buf[4] = 0x01;
	अन्यथा
		st->lnb_buf[4] = 0x00;

	st->lnb_buf[7] = vp702x_chksum(st->lnb_buf, 0, 7);

	mutex_lock(&dst->buf_mutex);

	buf = dst->buf;
	स_नकल(buf, st->lnb_buf, 8);

	vp702x_usb_inout_op(st->d, buf, 8, buf, 10, 100);
	अगर (buf[2] == 0 && buf[3] == 0)
		deb_fe("set_voltage cmd failed.\n");
	अन्यथा
		deb_fe("set_voltage cmd succeeded.\n");

	mutex_unlock(&dst->buf_mutex);
	वापस 0;
पूर्ण

अटल व्योम vp702x_fe_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा vp702x_fe_state *st = fe->demodulator_priv;
	kमुक्त(st);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops vp702x_fe_ops;

काष्ठा dvb_frontend * vp702x_fe_attach(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा vp702x_fe_state *s = kzalloc(माप(काष्ठा vp702x_fe_state), GFP_KERNEL);
	अगर (s == शून्य)
		जाओ error;

	s->d = d;

	स_नकल(&s->fe.ops,&vp702x_fe_ops,माप(काष्ठा dvb_frontend_ops));
	s->fe.demodulator_priv = s;

	s->lnb_buf[1] = SET_LNB_POWER;
	s->lnb_buf[3] = 0xff; /* 0=tone burst, 2=data burst, ff=off */

	वापस &s->fe;
error:
	वापस शून्य;
पूर्ण


अटल स्थिर काष्ठा dvb_frontend_ops vp702x_fe_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name           = "Twinhan DST-like frontend (VP7021/VP7020) DVB-S",
		.frequency_min_hz       =  950 * MHz,
		.frequency_max_hz       = 2150 * MHz,
		.frequency_stepsize_hz  =    1 * MHz,
		.symbol_rate_min     = 1000000,
		.symbol_rate_max     = 45000000,
		.symbol_rate_tolerance = 500,  /* ppm */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
		FE_CAN_QPSK |
		FE_CAN_FEC_AUTO
	पूर्ण,
	.release = vp702x_fe_release,

	.init  = vp702x_fe_init,
	.sleep = vp702x_fe_sleep,

	.set_frontend = vp702x_fe_set_frontend,
	.get_tune_settings = vp702x_fe_get_tune_settings,

	.पढ़ो_status = vp702x_fe_पढ़ो_status,
	.पढ़ो_ber = vp702x_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = vp702x_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = vp702x_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = vp702x_fe_पढ़ो_unc_blocks,

	.diseqc_send_master_cmd = vp702x_fe_send_diseqc_msg,
	.diseqc_send_burst = vp702x_fe_send_diseqc_burst,
	.set_tone = vp702x_fe_set_tone,
	.set_voltage = vp702x_fe_set_voltage,
पूर्ण;
