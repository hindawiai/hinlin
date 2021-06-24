<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 * Copyright (C) 2008 Henrik Kurelid <henrik@kurelid.se>
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश <media/dvb_frontend.h>

#समावेश "firedtv.h"

अटल पूर्णांक fdtv_dvb_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;
	पूर्णांक err;

	/* FIXME - allocate मुक्त channel at IRM */
	fdtv->isochannel = fdtv->adapter.num;

	err = cmp_establish_pp_connection(fdtv, fdtv->subunit,
					  fdtv->isochannel);
	अगर (err) अणु
		dev_err(fdtv->device,
			"could not establish point to point connection\n");
		वापस err;
	पूर्ण

	वापस fdtv_start_iso(fdtv);
पूर्ण

अटल पूर्णांक fdtv_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;

	fdtv_stop_iso(fdtv);
	cmp_अवरोध_pp_connection(fdtv, fdtv->subunit, fdtv->isochannel);
	fdtv->isochannel = -1;
	वापस 0;
पूर्ण

#घोषणा LNBCONTROL_DONTCARE 0xff

अटल पूर्णांक fdtv_diseqc_send_master_cmd(काष्ठा dvb_frontend *fe,
				       काष्ठा dvb_diseqc_master_cmd *cmd)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;

	वापस avc_lnb_control(fdtv, LNBCONTROL_DONTCARE, LNBCONTROL_DONTCARE,
			       LNBCONTROL_DONTCARE, 1, cmd);
पूर्ण

अटल पूर्णांक fdtv_diseqc_send_burst(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_sec_mini_cmd minicmd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_set_tone(काष्ठा dvb_frontend *fe, क्रमागत fe_sec_tone_mode tone)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;

	fdtv->tone = tone;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_set_voltage(काष्ठा dvb_frontend *fe,
			    क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;

	fdtv->voltage = voltage;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;
	काष्ठा firedtv_tuner_status stat;

	अगर (avc_tuner_status(fdtv, &stat))
		वापस -EINVAL;

	अगर (stat.no_rf)
		*status = 0;
	अन्यथा
		*status = FE_HAS_SIGNAL | FE_HAS_VITERBI | FE_HAS_SYNC |
			  FE_HAS_CARRIER | FE_HAS_LOCK;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;
	काष्ठा firedtv_tuner_status stat;

	अगर (avc_tuner_status(fdtv, &stat))
		वापस -EINVAL;

	*ber = stat.ber;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;
	काष्ठा firedtv_tuner_status stat;

	अगर (avc_tuner_status(fdtv, &stat))
		वापस -EINVAL;

	*strength = stat.संकेत_strength << 8;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा firedtv *fdtv = fe->sec_priv;
	काष्ठा firedtv_tuner_status stat;

	अगर (avc_tuner_status(fdtv, &stat))
		वापस -EINVAL;

	/* C/N[dB] = -10 * log10(snr / 65535) */
	*snr = stat.carrier_noise_ratio * 257;
	वापस 0;
पूर्ण

अटल पूर्णांक fdtv_पढ़ो_uncorrected_blocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक fdtv_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा firedtv *fdtv = fe->sec_priv;

	वापस avc_tuner_dsd(fdtv, p);
पूर्ण

व्योम fdtv_frontend_init(काष्ठा firedtv *fdtv, स्थिर अक्षर *name)
अणु
	काष्ठा dvb_frontend_ops *ops = &fdtv->fe.ops;
	काष्ठा dvb_frontend_पूर्णांकernal_info *fi = &ops->info;

	ops->init			= fdtv_dvb_init;
	ops->sleep			= fdtv_sleep;

	ops->set_frontend		= fdtv_set_frontend;

	ops->पढ़ो_status		= fdtv_पढ़ो_status;
	ops->पढ़ो_ber			= fdtv_पढ़ो_ber;
	ops->पढ़ो_संकेत_strength	= fdtv_पढ़ो_संकेत_strength;
	ops->पढ़ो_snr			= fdtv_पढ़ो_snr;
	ops->पढ़ो_ucblocks		= fdtv_पढ़ो_uncorrected_blocks;

	ops->diseqc_send_master_cmd	= fdtv_diseqc_send_master_cmd;
	ops->diseqc_send_burst		= fdtv_diseqc_send_burst;
	ops->set_tone			= fdtv_set_tone;
	ops->set_voltage		= fdtv_set_voltage;

	चयन (fdtv->type) अणु
	हाल FIREDTV_DVB_S:
		ops->delsys[0]		= SYS_DVBS;

		fi->frequency_min_hz	=   950 * MHz;
		fi->frequency_max_hz	=  2150 * MHz;
		fi->frequency_stepsize_hz = 125 * kHz;
		fi->symbol_rate_min	= 1000000;
		fi->symbol_rate_max	= 40000000;

		fi->caps		= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_1_2	|
					  FE_CAN_FEC_2_3	|
					  FE_CAN_FEC_3_4	|
					  FE_CAN_FEC_5_6	|
					  FE_CAN_FEC_7_8	|
					  FE_CAN_FEC_AUTO	|
					  FE_CAN_QPSK;
		अवरोध;

	हाल FIREDTV_DVB_S2:
		ops->delsys[0]		= SYS_DVBS;
		ops->delsys[1]		= SYS_DVBS2;

		fi->frequency_min_hz	=   950 * MHz;
		fi->frequency_max_hz	=  2150 * MHz;
		fi->frequency_stepsize_hz = 125 * kHz;
		fi->symbol_rate_min	= 1000000;
		fi->symbol_rate_max	= 40000000;

		fi->caps		= FE_CAN_INVERSION_AUTO |
					  FE_CAN_FEC_1_2        |
					  FE_CAN_FEC_2_3        |
					  FE_CAN_FEC_3_4        |
					  FE_CAN_FEC_5_6        |
					  FE_CAN_FEC_7_8        |
					  FE_CAN_FEC_AUTO       |
					  FE_CAN_QPSK           |
					  FE_CAN_2G_MODULATION;
		अवरोध;

	हाल FIREDTV_DVB_C:
		ops->delsys[0]		= SYS_DVBC_ANNEX_A;

		fi->frequency_min_hz	=      47 * MHz;
		fi->frequency_max_hz	=     866 * MHz;
		fi->frequency_stepsize_hz = 62500;
		fi->symbol_rate_min	= 870000;
		fi->symbol_rate_max	= 6900000;

		fi->caps		= FE_CAN_INVERSION_AUTO |
					  FE_CAN_QAM_16		|
					  FE_CAN_QAM_32		|
					  FE_CAN_QAM_64		|
					  FE_CAN_QAM_128	|
					  FE_CAN_QAM_256	|
					  FE_CAN_QAM_AUTO;
		अवरोध;

	हाल FIREDTV_DVB_T:
		ops->delsys[0]		= SYS_DVBT;

		fi->frequency_min_hz	=  49 * MHz;
		fi->frequency_max_hz	= 861 * MHz;
		fi->frequency_stepsize_hz = 62500;

		fi->caps		= FE_CAN_INVERSION_AUTO		|
					  FE_CAN_FEC_2_3		|
					  FE_CAN_TRANSMISSION_MODE_AUTO |
					  FE_CAN_GUARD_INTERVAL_AUTO	|
					  FE_CAN_HIERARCHY_AUTO;
		अवरोध;

	शेष:
		dev_err(fdtv->device, "no frontend for model type %d\n",
			fdtv->type);
	पूर्ण
	strscpy(fi->name, name, माप(fi->name));

	fdtv->fe.dvb = &fdtv->adapter;
	fdtv->fe.sec_priv = fdtv;
पूर्ण
