<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frontend driver क्रम the GENPIX 8pks/qpsk/DCII USB2.0 DVB-S module
 *
 * Copyright (C) 2006,2007 Alan Nisota (alannisota@gmail.com)
 * Copyright (C) 2006,2007 Genpix Electronics (genpix@genpix-electronics.com)
 *
 * Thanks to GENPIX क्रम the sample code used to implement this module.
 *
 * This module is based off the vp7045 and vp702x modules
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "gp8psk-fe.h"
#समावेश <media/dvb_frontend.h>

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	अगर (debug)							\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),			\
		       __func__, ##arg);				\
पूर्ण जबतक (0)

काष्ठा gp8psk_fe_state अणु
	काष्ठा dvb_frontend fe;
	व्योम *priv;
	स्थिर काष्ठा gp8psk_fe_ops *ops;
	bool is_rev1;
	u8 lock;
	u16 snr;
	अचिन्हित दीर्घ next_status_check;
	अचिन्हित दीर्घ status_check_पूर्णांकerval;
पूर्ण;

अटल पूर्णांक gp8psk_tuned_to_DCII(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	u8 status;

	st->ops->in(st->priv, GET_8PSK_CONFIG, 0, 0, &status, 1);
	वापस status & bmDCtuned;
पूर्ण

अटल पूर्णांक gp8psk_set_tuner_mode(काष्ठा dvb_frontend *fe, पूर्णांक mode)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	वापस st->ops->out(st->priv, SET_8PSK_CONFIG, mode, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक gp8psk_fe_update_status(काष्ठा gp8psk_fe_state *st)
अणु
	u8 buf[6];
	अगर (समय_after(jअगरfies,st->next_status_check)) अणु
		st->ops->in(st->priv, GET_SIGNAL_LOCK, 0, 0, &st->lock, 1);
		st->ops->in(st->priv, GET_SIGNAL_STRENGTH, 0, 0, buf, 6);
		st->snr = (buf[1]) << 8 | buf[0];
		st->next_status_check = jअगरfies + (st->status_check_पूर्णांकerval*HZ)/1000;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	gp8psk_fe_update_status(st);

	अगर (st->lock)
		*status = FE_HAS_LOCK | FE_HAS_SYNC | FE_HAS_VITERBI | FE_HAS_SIGNAL | FE_HAS_CARRIER;
	अन्यथा
		*status = 0;

	अगर (*status & FE_HAS_LOCK)
		st->status_check_पूर्णांकerval = 1000;
	अन्यथा
		st->status_check_पूर्णांकerval = 100;
	वापस 0;
पूर्ण

/* not supported by this Frontend */
अटल पूर्णांक gp8psk_fe_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32 *ber)
अणु
	(व्योम) fe;
	*ber = 0;
	वापस 0;
पूर्ण

/* not supported by this Frontend */
अटल पूर्णांक gp8psk_fe_पढ़ो_unc_blocks(काष्ठा dvb_frontend* fe, u32 *unc)
अणु
	(व्योम) fe;
	*unc = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 *snr)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	gp8psk_fe_update_status(st);
	/* snr is reported in dBu*256 */
	*snr = st->snr;
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 *strength)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	gp8psk_fe_update_status(st);
	/* snr is reported in dBu*256 */
	/* snr / 38.4 ~= 100% strength */
	/* snr * 17 वापसs 100% strength as 65535 */
	अगर (st->snr > 0xf00)
		*strength = 0xffff;
	अन्यथा
		*strength = (st->snr << 4) + st->snr; /* snr*17 */
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 800;
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 cmd[10];
	u32 freq = c->frequency * 1000;

	dprपूर्णांकk("%s()\n", __func__);

	cmd[4] = freq         & 0xff;
	cmd[5] = (freq >> 8)  & 0xff;
	cmd[6] = (freq >> 16) & 0xff;
	cmd[7] = (freq >> 24) & 0xff;

	/* backwards compatibility: DVB-S + 8-PSK were used क्रम Turbo-FEC */
	अगर (c->delivery_प्रणाली == SYS_DVBS && c->modulation == PSK_8)
		c->delivery_प्रणाली = SYS_TURBO;

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
		अगर (c->modulation != QPSK) अणु
			dprपूर्णांकk("%s: unsupported modulation selected (%d)\n",
				__func__, c->modulation);
			वापस -EOPNOTSUPP;
		पूर्ण
		c->fec_inner = FEC_AUTO;
		अवरोध;
	हाल SYS_DVBS2: /* kept क्रम backwards compatibility */
		dprपूर्णांकk("%s: DVB-S2 delivery system selected\n", __func__);
		अवरोध;
	हाल SYS_TURBO:
		dprपूर्णांकk("%s: Turbo-FEC delivery system selected\n", __func__);
		अवरोध;

	शेष:
		dprपूर्णांकk("%s: unsupported delivery system selected (%d)\n",
			__func__, c->delivery_प्रणाली);
		वापस -EOPNOTSUPP;
	पूर्ण

	cmd[0] =  c->symbol_rate        & 0xff;
	cmd[1] = (c->symbol_rate >>  8) & 0xff;
	cmd[2] = (c->symbol_rate >> 16) & 0xff;
	cmd[3] = (c->symbol_rate >> 24) & 0xff;
	चयन (c->modulation) अणु
	हाल QPSK:
		अगर (st->is_rev1)
			अगर (gp8psk_tuned_to_DCII(fe))
				st->ops->reload(st->priv);
		चयन (c->fec_inner) अणु
		हाल FEC_1_2:
			cmd[9] = 0; अवरोध;
		हाल FEC_2_3:
			cmd[9] = 1; अवरोध;
		हाल FEC_3_4:
			cmd[9] = 2; अवरोध;
		हाल FEC_5_6:
			cmd[9] = 3; अवरोध;
		हाल FEC_7_8:
			cmd[9] = 4; अवरोध;
		हाल FEC_AUTO:
			cmd[9] = 5; अवरोध;
		शेष:
			cmd[9] = 5; अवरोध;
		पूर्ण
		अगर (c->delivery_प्रणाली == SYS_TURBO)
			cmd[8] = ADV_MOD_TURBO_QPSK;
		अन्यथा
			cmd[8] = ADV_MOD_DVB_QPSK;
		अवरोध;
	हाल PSK_8: /* PSK_8 is क्रम compatibility with DN */
		cmd[8] = ADV_MOD_TURBO_8PSK;
		चयन (c->fec_inner) अणु
		हाल FEC_2_3:
			cmd[9] = 0; अवरोध;
		हाल FEC_3_4:
			cmd[9] = 1; अवरोध;
		हाल FEC_3_5:
			cmd[9] = 2; अवरोध;
		हाल FEC_5_6:
			cmd[9] = 3; अवरोध;
		हाल FEC_8_9:
			cmd[9] = 4; अवरोध;
		शेष:
			cmd[9] = 0; अवरोध;
		पूर्ण
		अवरोध;
	हाल QAM_16: /* QAM_16 is क्रम compatibility with DN */
		cmd[8] = ADV_MOD_TURBO_16QAM;
		cmd[9] = 0;
		अवरोध;
	शेष: /* Unknown modulation */
		dprपूर्णांकk("%s: unsupported modulation selected (%d)\n",
			__func__, c->modulation);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (st->is_rev1)
		gp8psk_set_tuner_mode(fe, 0);
	st->ops->out(st->priv, TUNE_8PSK, 0, 0, cmd, 10);

	st->lock = 0;
	st->next_status_check = jअगरfies;
	st->status_check_पूर्णांकerval = 200;

	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_send_diseqc_msg (काष्ठा dvb_frontend* fe,
				    काष्ठा dvb_diseqc_master_cmd *m)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (st->ops->out(st->priv, SEND_DISEQC_COMMAND, m->msg[0], 0,
			m->msg, m->msg_len)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_send_diseqc_burst(काष्ठा dvb_frontend *fe,
				       क्रमागत fe_sec_mini_cmd burst)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	u8 cmd;

	dprपूर्णांकk("%s\n", __func__);

	/* These commands are certainly wrong */
	cmd = (burst == SEC_MINI_A) ? 0x00 : 0x01;

	अगर (st->ops->out(st->priv, SEND_DISEQC_COMMAND, cmd, 0,
			&cmd, 0)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_set_tone(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	अगर (st->ops->out(st->priv, SET_22KHZ_TONE,
			 (tone == SEC_TONE_ON), 0, शून्य, 0)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_set_voltage(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	अगर (st->ops->out(st->priv, SET_LNB_VOLTAGE,
			 voltage == SEC_VOLTAGE_18, 0, शून्य, 0)) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक gp8psk_fe_enable_high_lnb_voltage(काष्ठा dvb_frontend* fe, दीर्घ onoff)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	वापस st->ops->out(st->priv, USE_EXTRA_VOLT, onoff, 0, शून्य, 0);
पूर्ण

अटल पूर्णांक gp8psk_fe_send_legacy_dish_cmd (काष्ठा dvb_frontend* fe, अचिन्हित दीर्घ sw_cmd)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;
	u8 cmd = sw_cmd & 0x7f;

	अगर (st->ops->out(st->priv, SET_DN_SWITCH, cmd, 0, शून्य, 0))
		वापस -EINVAL;

	अगर (st->ops->out(st->priv, SET_LNB_VOLTAGE, !!(sw_cmd & 0x80),
			0, शून्य, 0))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम gp8psk_fe_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा gp8psk_fe_state *st = fe->demodulator_priv;

	kमुक्त(st);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops gp8psk_fe_ops;

काष्ठा dvb_frontend *gp8psk_fe_attach(स्थिर काष्ठा gp8psk_fe_ops *ops,
				      व्योम *priv, bool is_rev1)
अणु
	काष्ठा gp8psk_fe_state *st;

	अगर (!ops || !ops->in || !ops->out || !ops->reload) अणु
		pr_err("Error! gp8psk-fe ops not defined.\n");
		वापस शून्य;
	पूर्ण

	st = kzalloc(माप(काष्ठा gp8psk_fe_state), GFP_KERNEL);
	अगर (!st)
		वापस शून्य;

	स_नकल(&st->fe.ops, &gp8psk_fe_ops, माप(काष्ठा dvb_frontend_ops));
	st->fe.demodulator_priv = st;
	st->ops = ops;
	st->priv = priv;
	st->is_rev1 = is_rev1;

	pr_info("Frontend %sattached\n", is_rev1 ? "revision 1 " : "");

	वापस &st->fe;
पूर्ण
EXPORT_SYMBOL_GPL(gp8psk_fe_attach);

अटल स्थिर काष्ठा dvb_frontend_ops gp8psk_fe_ops = अणु
	.delsys = अणु SYS_DVBS पूर्ण,
	.info = अणु
		.name			= "Genpix DVB-S",
		.frequency_min_hz	=  800 * MHz,
		.frequency_max_hz	= 2250 * MHz,
		.frequency_stepsize_hz	=  100 * kHz,
		.symbol_rate_min        = 1000000,
		.symbol_rate_max        = 45000000,
		.symbol_rate_tolerance  = 500,  /* ppm */
		.caps = FE_CAN_INVERSION_AUTO |
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			/*
			 * FE_CAN_QAM_16 is क्रम compatibility
			 * (Myth incorrectly detects Turbo-QPSK as plain QAM-16)
			 */
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_TURBO_FEC
	पूर्ण,

	.release = gp8psk_fe_release,

	.init = शून्य,
	.sleep = शून्य,

	.set_frontend = gp8psk_fe_set_frontend,

	.get_tune_settings = gp8psk_fe_get_tune_settings,

	.पढ़ो_status = gp8psk_fe_पढ़ो_status,
	.पढ़ो_ber = gp8psk_fe_पढ़ो_ber,
	.पढ़ो_संकेत_strength = gp8psk_fe_पढ़ो_संकेत_strength,
	.पढ़ो_snr = gp8psk_fe_पढ़ो_snr,
	.पढ़ो_ucblocks = gp8psk_fe_पढ़ो_unc_blocks,

	.diseqc_send_master_cmd = gp8psk_fe_send_diseqc_msg,
	.diseqc_send_burst = gp8psk_fe_send_diseqc_burst,
	.set_tone = gp8psk_fe_set_tone,
	.set_voltage = gp8psk_fe_set_voltage,
	.dishnetwork_send_legacy_command = gp8psk_fe_send_legacy_dish_cmd,
	.enable_high_lnb_voltage = gp8psk_fe_enable_high_lnb_voltage
पूर्ण;

MODULE_AUTHOR("Alan Nisota <alannisota@gamil.com>");
MODULE_DESCRIPTION("Frontend Driver for Genpix DVB-S");
MODULE_VERSION("1.1");
MODULE_LICENSE("GPL");
